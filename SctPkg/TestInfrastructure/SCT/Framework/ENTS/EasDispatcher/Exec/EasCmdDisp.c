/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EasCmdDisp.c

Abstract:

  EAS execution services implementations.

--*/

#include "SctLib.h"
#include "Eas.h"
#include "Cpu.h"

#include EFI_TEST_PROTOCOL_DEFINITION (EntsMonitorProtocol)
#include "EftpImplement.h"
#include "Sct.h"

#include EFI_ARCH_PROTOCOL_DEFINITION (Cpu)

#define CURRENT_CHILD_NAME  L"CurrentChild"
#define DELAY_TIME_NAME     L"DelayTime"
#define EXEC_TIME_NAME      L"ExecTime"

#define CMD_ACK_KEYWORD     L" _ACK_ "
#define CMD_OUT_KEYWORD     L" _OUT_ "
#define CMD_LOG_KEYWORD     L" _LOG_ "

#define ACK_SEND_LOG

#ifndef MAX_U64_VAL
#define MAX_U64_VAL 0xffffffffffffffff
#endif

EFI_CPU_ARCH_PROTOCOL *Cpu = NULL;

//
// Local Function Definition
//
EFI_STATUS
ExecElet (
  IN OUT EFI_NETWORK_TEST_FILE    *TestFile,
  IN CHAR16                       *TestNodeName
  );

EFI_STATUS
ExecDriver (
  IN OUT EFI_NETWORK_TEST_FILE    *TestFile,
  IN CHAR16                       *TestNodeName
  );

EFI_STATUS
GetCmdDispatch (
  IN  CHAR16               *Buffer,
  OUT EFI_MONITOR_COMMAND  *Cmd
  );

EFI_STATUS
SendAppACK (
  IN EFI_MONITOR_COMMAND           *Cmd
  );

EFI_STATUS
EmptyCmd (
  IN EFI_MONITOR_COMMAND           *Cmd
  );

EFI_STATUS
LocateEntsProtocol (
  IN CHAR16                *ProtocolName,
  OUT EFI_ENTS_PROTOCOL    **EntsProtocol
  );

EFI_STATUS
LocateEntsInterface (
  IN EFI_ENTS_PROTOCOL     *EntsProtocol,
  IN CHAR16                *InterfaceName,
  OUT ENTS_INTERFACE       **EntsInterface
  );

void
RecordExecTime (
  IN UINT64       StartTick,
  IN UINT64       EndTick
  );

//
// External Function Implementation
//
EFI_STATUS
DispatchFileTransferComd (
  ENTS_CMD_TYPE FileCmdType
  )
/*++

Routine Description:

  Dispatch an get_file command, download file from SCT management side.

Arguments:

  FileCmdType - File command type.

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;
  EFI_TIME    StartTime;
  EFI_TIME    EndTime;

  //
  // Perform EFTP operation.
  //
  tRT->GetTime (&StartTime, NULL);
  Status = EftpDispatchFileTransferComd (FileCmdType);
  tRT->GetTime (&EndTime, NULL);

  if (Status == EFI_OUT_OF_RESOURCES) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (FileCmdType == PUT_FILE) {
    Status = RecordMessage (
              &((gEasFT->Cmd)->ComdRuntimeInfo),
              &(gEasFT->Cmd)->ComdRuntimeInfoSize,
              L"PUT_FILE (%s) Status - %r",
              (gEasFT->Cmd)->ComdArg,
              Status
              );
  } else {
    Status = RecordMessage (
              &((gEasFT->Cmd)->ComdRuntimeInfo),
              &(gEasFT->Cmd)->ComdRuntimeInfoSize,
              L"GET_FILE (%s) Status - %r",
              (gEasFT->Cmd)->ComdArg,
              Status
              );
  }

  if (Status == EFI_OUT_OF_RESOURCES) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RecordMessage (
            &((gEasFT->Cmd)->ComdOutput),
            &(gEasFT->Cmd)->ComdOutputSize,
            L"StartTime - %02d-%02d-%04d %02d:%02d:%02d, EndTime - %02d-%02d-%04d %02d:%02d:%02d",
            StartTime.Day,
            StartTime.Month,
            StartTime.Year,
            StartTime.Hour,
            StartTime.Minute,
            StartTime.Second,
            EndTime.Day,
            EndTime.Month,
            EndTime.Year,
            EndTime.Hour,
            EndTime.Minute,
            EndTime.Second
            );
  if (Status == EFI_OUT_OF_RESOURCES) {
    return EFI_OUT_OF_RESOURCES;
  }

  return Status;
}

EFI_STATUS
DispatchInternalComd (
  VOID
  )
/*++

Routine Description:

  Dispatch internal command

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;
  UINT32      BufferSize;
  CHAR16      *Buffer;

  Status = EFI_SUCCESS;
  switch ((gEasFT->Cmd)->CmdType) {
  case RIVL_DEFTYPE:
    Status = RivlAddRivlType ((gEasFT->Cmd)->ComdArg);
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"RIVL_DEFTYPE Status - %r", Status));
      Status = RecordMessage (
                &((gEasFT->Cmd)->ComdRuntimeInfo),
                &(gEasFT->Cmd)->ComdRuntimeInfoSize,
                L"RIVL_DEFTYPE Status - %r",
                Status
                );
      if (Status == EFI_OUT_OF_RESOURCES) {
        return EFI_OUT_OF_RESOURCES;
      }
    }
    break;

  case RIVL_DELTYPE:
    Status = RivlDelRivlType ((gEasFT->Cmd)->ComdArg);
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"RIVL_DELTYPE Status - %r", Status));
      Status = RecordMessage (
                &((gEasFT->Cmd)->ComdRuntimeInfo),
                &(gEasFT->Cmd)->ComdRuntimeInfoSize,
                L"RIVL_DELTYPE Status - %r",
                Status
                );
      if (Status == EFI_OUT_OF_RESOURCES) {
        return EFI_OUT_OF_RESOURCES;
      }
    }
    break;

  case RIVL_CRTVAR:
    Status = RivlAddRivlVariable ((gEasFT->Cmd)->ComdArg);
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"RIVL_CRTVAR Status - %r", Status));
      Status = RecordMessage (
                &((gEasFT->Cmd)->ComdRuntimeInfo),
                &(gEasFT->Cmd)->ComdRuntimeInfoSize,
                L"RIVL_CRTVAR Status - %r",
                Status
                );
      if (Status == EFI_OUT_OF_RESOURCES) {
        return EFI_OUT_OF_RESOURCES;
      }
    }
    break;

  case RIVL_SETVAR:
    Status = RivlSetRivlVariable ((gEasFT->Cmd)->ComdArg);
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"RIVL_SETVAR Status - %r", Status));
      Status = RecordMessage (
                &((gEasFT->Cmd)->ComdRuntimeInfo),
                &(gEasFT->Cmd)->ComdRuntimeInfoSize,
                L"RIVL_SETVAR Status - %r",
                Status
                );
      if (Status == EFI_OUT_OF_RESOURCES) {
        return EFI_OUT_OF_RESOURCES;
      }
    }
    break;

  case RIVL_GETVAR:
    BufferSize  = 0;
    Buffer      = NULL;
    Status      = RivlGetRivlVariable ((gEasFT->Cmd)->ComdArg, &BufferSize, Buffer);
    if (Status == EFI_BUFFER_TOO_SMALL) {
      Buffer = EntsAllocatePool (BufferSize);
      if (Buffer == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        break;
      }

      Status = RivlGetRivlVariable ((gEasFT->Cmd)->ComdArg, &BufferSize, Buffer);
    }

    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Get Veriable Status - %r", Status));
      Status = RecordMessage (
                &((gEasFT->Cmd)->ComdRuntimeInfo),
                &(gEasFT->Cmd)->ComdRuntimeInfoSize,
                L"RIVL_GETVAR Status - %r",
                Status
                );
      break;
    }

    Status = RecordMessage (
              &((gEasFT->Cmd)->ComdOutput),
              &(gEasFT->Cmd)->ComdOutputSize,
              L"%s",
              Buffer
              );
	EntsFreePool(Buffer);
    break;

  case RIVL_DELVAR:
    Status = RivlDelRivlVariable ((gEasFT->Cmd)->ComdArg);
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"RIVL_DELVAR Status - %r", Status));
      Status = RecordMessage (
                &((gEasFT->Cmd)->ComdRuntimeInfo),
                &(gEasFT->Cmd)->ComdRuntimeInfoSize,
                L"RIVL_DELVAR Status - %r",
                Status
                );
      if (Status == EFI_OUT_OF_RESOURCES) {
        return EFI_OUT_OF_RESOURCES;
      }
    }
    break;

  default:
    Status = EFI_NOT_FOUND;
    break;
  }

  return Status;
}

EFI_STATUS
DispatchExecComd (
  VOID
  )
/*++

Routine Description:

  Dispatch an exec command

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;
  EFI_TIME    StartTime;
  EFI_TIME    EndTime;

  //
  // Execute Shell Command
  //
  tRT->GetTime (&StartTime, NULL);
  Status = SctShellExecute (&mImageHandle, (gEasFT->Cmd)->ComdArg, FALSE, NULL, NULL);;
  tRT->GetTime (&EndTime, NULL);
  EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"dispatch:(%s)", (gEasFT->Cmd)->ComdArg));
  SctPrint (L"dispatch:(%s) - %r\n", (gEasFT->Cmd)->ComdArg, Status);
  if (Status == EFI_OUT_OF_RESOURCES) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RecordMessage (
            &((gEasFT->Cmd)->ComdRuntimeInfo),
            &(gEasFT->Cmd)->ComdRuntimeInfoSize,
            L"TEST_EXEC (%s) Status - %r",
            (gEasFT->Cmd)->ComdArg,
            Status
            );
  if (Status == EFI_OUT_OF_RESOURCES) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RecordMessage (
            &((gEasFT->Cmd)->ComdOutput),
            &(gEasFT->Cmd)->ComdOutputSize,
            L"StartTime - %02d-%02d-%04d %02d:%02d:%02d, EndTime - %02d-%02d-%04d %02d:%02d:%02d",
            StartTime.Day,
            StartTime.Month,
            StartTime.Year,
            StartTime.Hour,
            StartTime.Minute,
            StartTime.Second,
            EndTime.Day,
            EndTime.Month,
            EndTime.Year,
            EndTime.Hour,
            EndTime.Minute,
            EndTime.Second
            );
  if (Status == EFI_OUT_OF_RESOURCES) {
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
DispatchEletComd (
  VOID
  )
/*++

Routine Description:

  Dispatch an elet command.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS            Status;
  EFI_NETWORK_TEST_FILE *TestFile;

  //
  // Execute Elet
  //
  TestFile  = (gEasFT->Cmd)->TestFile;
  Status    = ExecElet (TestFile, (gEasFT->Cmd)->ComdInterface);
  if (EFI_ERROR (Status)) {
    SctPrint (L"Error in dispatch: Exec status - %r\n", Status);
    return Status;
  }

  EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"dispatch:(%s)", TestFile->FileName));
  return EFI_SUCCESS;
}

EFI_STATUS
PreDispatch (
  IN  CHAR16               *Buffer
  )
/*++

Routine Description:

  Pre command dispatch.

Arguments:

  Buffer  - Command buffer.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;

  //
  // init comd
  //
  EmptyCmd (gEasFT->Cmd);

  //
  // Get CmdName, and parameters
  //
  Status = GetCmdDispatch (Buffer, gEasFT->Cmd);

  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"PreDispathch: Error in GetCmdDispatch - %r", Status));
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
PostDispatch (
  IN EFI_MONITOR_COMMAND           *Cmd
  )
/*++

Routine Description:

  Post command dispatch.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.
  
--*/
{
  EFI_STATUS  Status;

  //
  // Attach to global runtimeInfo buffer
  //
  Status = SendAppACK (Cmd);
  if (EFI_ERROR (Status)) {
    SctPrint (L"PostDispathch: Error in SendAppACK - %r\n", Status);
    EmptyCmd (Cmd);
    return Status;
  }

  Status = EmptyCmd (Cmd);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"PostDispathch: Error in EmptyCmd - %r", Status));
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
GetCmdType (
  IN EFI_MONITOR_COMMAND            *Cmd
  )
/*++

Routine Description:

  Analize the command type.

Arguments:

  None

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - Command name not found.
  Others        - Some failure happened.

--*/
{
  EFI_STATUS  Status;

  if (Cmd == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Is it TEST_ABOUT
  //
  if (SctCompareMem (Cmd->ComdName, EFI_NETWORK_ABORT_COMMAND, SctStrLen (EFI_NETWORK_ABORT_COMMAND) * 2) == 0) {
    Cmd->CmdType = ABORT;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", EFI_NETWORK_ABORT_COMMAND));
    return EFI_SUCCESS;
  }
  //
  // Is it TEST_EXEC
  //
  if (SctCompareMem (Cmd->ComdName, EFI_NETWORK_EXEC_COMMAND, SctStrLen (EFI_NETWORK_EXEC_COMMAND) * 2) == 0) {
    Cmd->CmdType = EXECUTE;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", EFI_NETWORK_EXEC_COMMAND));
    return EFI_SUCCESS;
  }
  //
  // Is it GET_FILE
  //
  if (SctCompareMem (Cmd->ComdName, EFI_NETWORK_GET_FILE, SctStrLen (EFI_NETWORK_GET_FILE) * 2) == 0) {
    Cmd->CmdType = GET_FILE;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", EFI_NETWORK_GET_FILE));
    return EFI_SUCCESS;
  }
  //
  // Is it PUT_FILE
  //
  if (SctCompareMem (Cmd->ComdName, EFI_NETWORK_PUT_FILE, SctStrLen (EFI_NETWORK_PUT_FILE) * 2) == 0) {
    Cmd->CmdType = PUT_FILE;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", EFI_NETWORK_PUT_FILE));
    return EFI_SUCCESS;
  }
  //
  // Is it RIVL_DEFTYPE
  //
  if (SctCompareMem (Cmd->ComdName, RIVL_DEFTYPE_CMD, SctStrLen (RIVL_DEFTYPE_CMD) * 2) == 0) {
    Cmd->CmdType = RIVL_DEFTYPE;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", RIVL_DEFTYPE_CMD));
    return EFI_SUCCESS;
  }
  //
  // Is it RIVL_CRTVAR
  //
  if (SctCompareMem (Cmd->ComdName, RIVL_CRTVAR_CMD, SctStrLen (RIVL_CRTVAR_CMD) * 2) == 0) {
    Cmd->CmdType = RIVL_CRTVAR;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", RIVL_CRTVAR_CMD));
    return EFI_SUCCESS;
  }
  //
  // Is it RIVL_DELTYPE
  //
  if (SctCompareMem (Cmd->ComdName, RIVL_DELTYPE_CMD, SctStrLen (RIVL_DELTYPE_CMD) * 2) == 0) {
    Cmd->CmdType = RIVL_DELTYPE;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", RIVL_DELTYPE_CMD));
    return EFI_SUCCESS;
  }
  //
  // Is it RIVL_DELVAR
  //
  if (SctCompareMem (Cmd->ComdName, RIVL_DELVAR_CMD, SctStrLen (RIVL_DELVAR_CMD) * 2) == 0) {
    Cmd->CmdType = RIVL_DELVAR;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", RIVL_DELVAR_CMD));
    return EFI_SUCCESS;
  }
  //
  // Is it RIVL_SETVAR
  //
  if (SctCompareMem (Cmd->ComdName, RIVL_SETVAR_CMD, SctStrLen (RIVL_SETVAR_CMD) * 2) == 0) {
    Cmd->CmdType = RIVL_SETVAR;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", RIVL_SETVAR_CMD));
    return EFI_SUCCESS;
  }
  //
  // Is it RIVL_GETVAR
  //
  if (SctCompareMem (Cmd->ComdName, RIVL_GETVAR_CMD, SctStrLen (RIVL_GETVAR_CMD) * 2) == 0) {
    Cmd->CmdType = RIVL_GETVAR;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"GetRemoteCmd: %s", RIVL_GETVAR_CMD));
    return EFI_SUCCESS;
  }

  Status = EntsFindTestFileByName (Cmd->ComdName, &(Cmd->TestFile));
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Can't find file:%s", Cmd->ComdName));
    return EFI_NOT_FOUND;
  }

  Cmd->CmdType = ELET_CMD;

  return EFI_SUCCESS;
}

EFI_STATUS
SendAppACK (
  IN EFI_MONITOR_COMMAND           *Cmd
  )
/*++

Routine Description:

  Send application result info back to manager.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                Status;
  CHAR16                    *AppResultTmp;
  UINTN                     Len;
  UINTN                     OutputLen;
  UINTN                     RuntimeInfoLen;
  EFI_ENTS_MONITOR_PROTOCOL *EntsMonitor;

  EntsMonitor = gEasFT->Monitor;

  //
  // AR: need to diff InternalSendACK and EletSendACK: how to store runtimeInfo
  //
  Len = SctStrLen (CMD_ACK_KEYWORD) + 10;
  if (Cmd->ComdOutput != NULL) {
    OutputLen = SctStrLen (Cmd->ComdOutput);
    Len += SctStrLen (CMD_OUT_KEYWORD) + OutputLen;
  }

  if (Cmd->ComdRuntimeInfo != NULL) {
    RuntimeInfoLen = SctStrLen (Cmd->ComdRuntimeInfo);
    Len += SctStrLen (CMD_LOG_KEYWORD) + RuntimeInfoLen;
  }

  AppResultTmp = EntsAllocatePool (Len * 2);
  if (AppResultTmp == NULL) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in SendAppACK: EFI_OUT_OF_RESOURCES"));
    return EFI_OUT_OF_RESOURCES;
  }

  AppResultTmp[0] = L'\0';

  //
  // Add Result Message Header
  //
  SctStrCat (AppResultTmp, CMD_ACK_KEYWORD);

  //
  // Add PASS/FAIL
  //
  if (Cmd->ComdResult == PASS) {
    SctStrCat (AppResultTmp, L"P ");
  } else {
    SctStrCat (AppResultTmp, L"F ");
  }
  //
  // Add _OUT_
  //
  if (Cmd->ComdOutput != NULL) {
    SctStrCat (AppResultTmp, CMD_OUT_KEYWORD);
    SctStrCat (AppResultTmp, Cmd->ComdOutput);
  }
  //
  // Add _LOG_
  //
#ifdef ACK_SEND_LOG
  if (Cmd->ComdRuntimeInfo != NULL) {
    SctStrCat (AppResultTmp, CMD_LOG_KEYWORD);
    SctStrCat (AppResultTmp, Cmd->ComdRuntimeInfo);
  }
#endif

  Status = EntsMonitor->MonitorSender (EntsMonitor, AppResultTmp);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"in SendResult: sender error Status - %r\n", Status));
  }

  if (AppResultTmp) {
    EntsFreePool(AppResultTmp);
  }

  return Status;
}

EFI_STATUS
EmptyCmd (
  IN EFI_MONITOR_COMMAND           *Cmd
  )
/*++

Routine Description:

  Clear data in cmd data structure.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  if (Cmd->ComdName != NULL) {
  	EntsFreePool(Cmd->ComdName);
    Cmd->ComdName = NULL;
  }

  if (Cmd->ComdArg != NULL) {
  	EntsFreePool(Cmd->ComdArg);
    Cmd->ComdArg = NULL;
  }

  if (Cmd->ComdRuntimeInfo != NULL) {
  	EntsFreePool(Cmd->ComdRuntimeInfo);
    Cmd->ComdRuntimeInfo      = NULL;
    Cmd->ComdRuntimeInfoSize  = 0;
  }

  if (Cmd->ComdOutput != NULL) {
  	EntsFreePool(Cmd->ComdOutput);
    Cmd->ComdOutput     = NULL;
    Cmd->ComdOutputSize = 0;
  }

  Cmd->TestFile = NULL;

  if (Cmd->ComdInterface != NULL) {
  	EntsFreePool(Cmd->ComdInterface);
    Cmd->ComdInterface = NULL;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
GetCmdDispatch (
  IN  CHAR16               *Buffer,
  OUT EFI_MONITOR_COMMAND  *Cmd
  )
/*++

Routine Description:

  Find cmd info from input buffer.

Arguments:

  Buffer  - Command buffer.
  Cmd     - Pointer to EFI_MONITOR_COMMAND structure.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_OUT_OF_RESOURCES  - Memory allocation failed.
  EFI_NOT_FOUND         - Can't find CmdName.
  Others                - Some failure happened.
  
--*/
{
  UINTN       Index;
  CHAR16      *BufferTmp;
  EFI_STATUS  Status;
  CHAR16      *TestNodeName;
  CHAR16      *TempCmdArg = NULL;
  
  if (Cmd == NULL) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in GetCmdDisPatch: null Cmd"));
    return EFI_INVALID_PARAMETER;
  }
  //
  // get cmd name
  //
  //
  // Skip space at the beginning
  //
  for (BufferTmp = Buffer; *BufferTmp; BufferTmp++) {
    if ((*BufferTmp != L' ') && (*BufferTmp != L'\t')) {
      break;
    }
  }

  if (*BufferTmp == 0) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"GetCmdDispatch: Can't find CmdName"));
    return EFI_NOT_FOUND;
  }

  Index = EntsStrStr (BufferTmp, L" ");
  if (Index == 0) {
    Index = EntsStrStr (BufferTmp, L"\t");
  }
  //
  // Copy comd name skipping the space character
  //
  if (Index == 0) {
    Cmd->ComdName = EntsStrDuplicate (BufferTmp);
    if (Cmd->ComdName == NULL) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"GetCmdDispatch: Can't find CmdName"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    Cmd->ComdName = EntsAllocatePool (Index * 2);
    if (Cmd->ComdName == NULL) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"GetCmdDispatch: EFI_OUT_OF_RESOURCES"));
      return EFI_OUT_OF_RESOURCES;
    }

    SctSetMem (Cmd->ComdName, Index * 2, 0);
    SctCopyMem (Cmd->ComdName, BufferTmp, (Index - 1) * 2);
  }
  //
  // Get Cmd Input
  //
  if (SctStrLen (BufferTmp + SctStrLen (Cmd->ComdName)) != 0) {
  	 TempCmdArg = BufferTmp + SctStrLen (Cmd->ComdName) + 1;

    //
    // Skip ' ' & '\t' letters 
    //
    for (; *TempCmdArg == L' ' || *TempCmdArg == L'\t'; TempCmdArg++);

    //
    // Only pactch TEST_EXEC sct xxx command 
    //
    if (SctCompareMem (Cmd->ComdName, 
    	               EFI_NETWORK_EXEC_COMMAND, 
    	               SctStrLen (EFI_NETWORK_EXEC_COMMAND) * 2) == 0
    	&& (TempCmdArg[0] == L's' || TempCmdArg[0] == L'S')
    	&& (TempCmdArg[1] == L'c' || TempCmdArg[1] == L'C')
    	&& (TempCmdArg[2] == L't' || TempCmdArg[2] == L'T')     
    	&& (TempCmdArg[3] == L' ' || TempCmdArg[3] == L'\t')
    	&& gFT->ConfigData->EnableScreenOutput == FALSE) {
      //
      // screen output silent mode, add -v switch
      //
      Cmd->ComdArg = (CHAR16 *) SctAllocateZeroPool (SctStrSize (TempCmdArg) + SctStrLen (L" -v"));
      if ( Cmd->ComdArg == NULL ){
      	 EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"GetCmdDispatch: EFI_OUT_OF_RESOURCES"));
        return  EFI_OUT_OF_RESOURCES;
      }
      EntsCopyMem(Cmd->ComdArg, TempCmdArg, SctStrLen (TempCmdArg) * sizeof(*TempCmdArg));
      EntsCopyMem(Cmd->ComdArg + SctStrLen (TempCmdArg), L" -v", SctStrSize (L" -v"));
    } else { 
       Cmd->ComdArg = EntsStrDuplicate (TempCmdArg);
      if (Cmd->ComdArg == NULL) {
        EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"GetCmdDispatch: EFI_OUT_OF_RESOURCES"));
        return EFI_OUT_OF_RESOURCES;
      }
     
    }
  }
  

  //
  // get the test interface name
  //
  TestNodeName = Cmd->ComdName;
  while (*TestNodeName != 0) {
    if ((*TestNodeName == L'-') && (*(TestNodeName + 1) == L'>')) {
      break;
    }

    TestNodeName++;
  }

  if (*TestNodeName != 0) {
    //
    // get it
    //
    *TestNodeName = 0;
    TestNodeName += 2;
    Cmd->ComdInterface = EntsStrDuplicate (TestNodeName);
    if (Cmd->ComdInterface == NULL) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"GetCmdDispatch: EFI_OUT_OF_RESOURCES"));
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    Cmd->ComdInterface = NULL;
  }
  //
  // Find Cmd Type
  //
  Status = GetCmdType (Cmd);

  return Status;
}

EFI_STATUS
ExecElet (
  IN OUT EFI_NETWORK_TEST_FILE    *TestFile,
  IN CHAR16                       *TestNodeName
  )
/*++

Routine Description:

  Execute an application.

Arguments:

  TestFile      - Pointer to the EFI_EFI_NETWORK_TEST_FILE structure.
  TestNodeName  - Test node name string.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_UNSUPPORTED      - Unsupported test file.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.
  
--*/
{
  EFI_STATUS                Status;
  UINTN                     ExitDataSize;
  CHAR16                    *ExitData;
  EFI_HANDLE                ImageHandle;
  EFI_DEVICE_PATH_PROTOCOL  *FileNode;
  EFI_DEVICE_PATH_PROTOCOL  *FilePath;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
//  UINT64                    StartTick;
//  UINT64                    StopTick;

  if ((TestFile->Type == EFI_NETWORK_TEST_FILE_APPLICATION) && (TestNodeName == NULL)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"in ExecElet:begin exe (%s)", TestFile->FileName));

    //
    // Add the file path to the device path
    //
    FileNode = SctFileDevicePath (NULL, TestFile->FileName);
    if (FileNode == NULL) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"in ExecElet:Create file device path - %r", EFI_OUT_OF_RESOURCES));
      return EFI_OUT_OF_RESOURCES;
    }

    FilePath = SctAppendDevicePath (gEasFT->DevicePath, FileNode);
    if (FilePath == NULL) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"in ExecElet:Append file device path - %r", EFI_OUT_OF_RESOURCES));
      tBS->FreePool (FileNode);
      return EFI_OUT_OF_RESOURCES;
    }

    tBS->FreePool (FileNode);

    //
    // Load the test file
    //
    Status = tBS->LoadImage (
                  FALSE,
                  gEasFT->ImageHandle,
                  FilePath,
                  NULL,
                  0,
                  &ImageHandle
                  );
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"in ExecElet:Load image - %r", Status));
      tBS->FreePool (FilePath);
      return Status;
    }

    tBS->FreePool (FilePath);
    EFI_ENTS_STATUS ((L"in ExecElet: Finish Loading image file <%s>", TestFile->FileName));

    //
    // Verify the image is an application or not
    //
    Status = tBS->HandleProtocol (
                  ImageHandle,
                  &gEfiLoadedImageProtocolGuid,
                  (void **)&LoadedImage
                  );
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"in ExecElet: HandleProtocol - %r", Status));
	  tBS->UnloadImage(ImageHandle);
      return Status;
    }

    if (LoadedImage->ImageCodeType == EfiLoaderCode) {
      //
      // It is an application
      //
//      StartTick = SctReadTsc ();
      Status = tBS->StartImage (
                    ImageHandle,
                    &ExitDataSize,
                    &ExitData
                    );
//      StopTick = SctReadTsc ();
//      RecordExecTime (StartTick, StopTick);
      if (EFI_ERROR (Status)) {
        EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in ExecElet: Start image - %r\n", Status));
      }
    } else {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_WARNING, L"Unsupported test file"));
      Status = EFI_UNSUPPORTED;
    }
	tBS->UnloadImage(ImageHandle);
	return Status;
  } else if ((TestFile->Type == EFI_NETWORK_TEST_FILE_DRIVER) && (TestNodeName != NULL)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"in ExecElet:begin exe (%s->%s)", TestFile->CmdName, TestNodeName));

    Status = ExecDriver (TestFile, TestNodeName);
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in ExecDriver: Status - %r\n", Status));
      return Status;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ExecDriver (
  IN OUT EFI_NETWORK_TEST_FILE    *TestFile,
  IN CHAR16                       *TestNodeName
  )
/*++

Routine Description:

  Execute a driver.

Arguments:

  TestFile      - Pointer to the EFI_EFI_NETWORK_TEST_FILE structure.
  TestNodeName  - Test node name string.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.

--*/
{
  EFI_ENTS_PROTOCOL *EntsProtocol;
  ENTS_INTERFACE    *EntsInterface;
  EFI_STATUS        Status;
  EFI_STATUS        TestStatus;
  RIVL_VARIABLE     *DelayTimeVariable;
//  UINT64            StartTick;
//  UINT64            StopTick;

  //
  // Find the EntsProtocol instance by name
  // and install the client instance by index
  //
  Status  = LocateEntsProtocol (TestFile->CmdName, &EntsProtocol);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in LocateEntsProtocol: Status - %r\n", Status));
    return Status;
  }
  //
  // Find the EntsInterface by name
  //
  Status = LocateEntsInterface (EntsProtocol, TestNodeName, &EntsInterface);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in LocateEntsInterface: Status - %r\n", Status));
    return Status;
  }
  //
  // Parse the argument list
  //
  Status = ParseArg (EntsInterface->ArgFieldList);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in ParseArg: Status - %r\n", Status));
    return Status;
  }
  //
  // Find variable (DelayTime)
  //
  DelayTimeVariable = SearchRivlVariable (DELAY_TIME_NAME);
  if (DelayTimeVariable != NULL) {
    tBS->Stall (*(UINTN *) DelayTimeVariable->Address);
  }
  //
  // Call the entry point
  //
//  StartTick = SctReadTsc ();
  TestStatus  = EntsInterface->EntsInterfaceEntry (EntsProtocol->ClientInterface);
//  StopTick = SctReadTsc ();
//  RecordExecTime (StartTick, StopTick);

  if (EntsProtocol->RuntimeInfo != NULL) {
    (gEasFT->Cmd)->ComdRuntimeInfo = EntsStrDuplicate (EntsProtocol->RuntimeInfo);
    if ((gEasFT->Cmd)->ComdRuntimeInfo == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    (gEasFT->Cmd)->ComdRuntimeInfoSize = (SctStrLen (EntsProtocol->RuntimeInfo) + 1) * 2;
    tBS->FreePool (EntsProtocol->RuntimeInfo);
	EntsProtocol->RuntimeInfo = NULL;
	EntsProtocol->RuntimeInfoSize = 0;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
LocateEntsProtocol (
  IN CHAR16                *ProtocolName,
  OUT EFI_ENTS_PROTOCOL    **EntsProtocol
  )
/*++

Routine Description:

  Locate ents protocol instance.

Arguments:

  ProtocolName  - Protocol name string.
  Index         - Index number.
  EntsProtocol  - Pointer to EFI_ENTS_PROTOCOL instance.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_NOT_FOUND         - EntsProtocol instance not found.
  EFI_INVALID_PARAMETER - Memory allocation failed.
  Others                - Some failure happened.
  
--*/
{
  UINTN             NoHandles;
  UINTN             HandleIndex;
  EFI_HANDLE        *HandleBuffer;
  EFI_ENTS_PROTOCOL *Interface;
  EFI_STATUS        Status;
  RIVL_VARIABLE     *CurrentChildVariable;

  //
  // Locate EntsProtocol
  //
  Status = tBS->LocateHandleBuffer (
                ByProtocol,
                &gEfiEntsProtocolGuid,
                NULL,
                &NoHandles,
                &HandleBuffer
                );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Not found EntsProtocol instance"));
    return EFI_NOT_FOUND;
  }
  //
  // Walk through each instance need to be tested
  //
  for (HandleIndex = 0; HandleIndex < NoHandles; HandleIndex++) {
    Status = tBS->HandleProtocol (
                  HandleBuffer[HandleIndex],
                  &gEfiEntsProtocolGuid,
                  (VOID **)&Interface
                  );
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Handle protocol - %r, Index - %d", Status, HandleIndex));
      goto ExitLocateEntsProtocol;
    }
    //
    // match the instance
    //
    if (SctStrCmp (Interface->ClientName, ProtocolName) == 0) {
      //
      // find it
      //
      *EntsProtocol = Interface;

      switch (Interface->ClientAttribute) {
      case ENTS_PROTOCOL_ATTRIBUTE_BOOT_SERVICE:
        Interface->ClientInterface = tBS;
        Status = EFI_SUCCESS;
        goto ExitLocateEntsProtocol;

      case ENTS_PROTOCOL_ATTRIBUTE_RUNTIME_SERVICE:
        Interface->ClientInterface = tRT;
        Status = EFI_SUCCESS;
        goto ExitLocateEntsProtocol;

      case ENTS_PROTOCOL_ATTRIBUTE_GENERIC_SERVICE:
        Interface->ClientInterface = NULL;
        Status = EFI_SUCCESS;
        goto ExitLocateEntsProtocol;

      case ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED:
        //
        // Find variable
        //
        CurrentChildVariable = SearchRivlVariable (CURRENT_CHILD_NAME);
        if (CurrentChildVariable != NULL) {
          Interface->ClientHandle = *((EFI_HANDLE *) CurrentChildVariable->Address);
        }

      case ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL:
        if (Interface->ClientHandle != NULL) {
          Status = tBS->HandleProtocol (
                        Interface->ClientHandle,
                        Interface->ClientGuid,
                        (VOID **) &Interface->ClientInterface
                        );
          if (EFI_ERROR (Status)) {
            EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Handle protocol - %r", Status));
          }

          goto ExitLocateEntsProtocol;
        }

        Status = EntsNetworkServiceBindingGetControllerHandle (Interface->ClientGuid, &Interface->ClientHandle);
        if (EFI_ERROR(Status)) {
          EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"EntsNetworkServiceBindingGetControllerHandle Error - %r", Status));
          return Status;
        }

        Status = tBS->HandleProtocol (
                       Interface->ClientHandle,
                       Interface->ClientGuid,
                       (VOID **) &Interface->ClientInterface
                       );
        if (EFI_ERROR(Status)) {
          EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"HandleProtocol Error - %r", Status));
          return Status;
        }

        goto ExitLocateEntsProtocol;
      default:
        break;
      }
    }
  }

  Status = EFI_NOT_FOUND;

ExitLocateEntsProtocol:
  if(NULL != HandleBuffer) {
    tBS->FreePool (HandleBuffer);
  }
  return Status;
}

EFI_STATUS
LocateEntsInterface (
  IN EFI_ENTS_PROTOCOL     *EntsProtocol,
  IN CHAR16                *InterfaceName,
  OUT ENTS_INTERFACE       **EntsInterface
  )
/*++

Routine Description:

  LocateEntsInterface.

Arguments:

  EntsProtocol  - Pointer to EFI_ENTS_PROTOCOL instance.
  InterfaceName - InterfaceName string.
  EntsInterface - Pointer to ENTS_INTERFACE instance.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No ents interface found.

--*/
{
  ENTS_INTERFACE  *Interface;

  Interface = EntsProtocol->EntsInterfaceList;

  //
  // Walk through each interface need to be tested
  //
  while (Interface->InterfaceName[0] != 0) {
    //
    // match the interface
    //
    if (SctStrCmp (Interface->InterfaceName, InterfaceName) == 0) {
      //
      // find it
      //
      *EntsInterface = Interface;
      return EFI_SUCCESS;
    }

    Interface++;
  }

  return EFI_NOT_FOUND;
}

VOID
RecordExecTime (
  IN UINT64       StartTick,
  IN UINT64       EndTick
  )
/*++

Routine Description:

  Record execution time.

Arguments:

  StartTick - Start tick number.
  EndTick   - End tick number.

Returns:

  None.

--*/
{
  UINT64        ExecTime;
  //
  // the unit is nano-second
  //
  UINT64        ExecTick;
  //
  // the unit is cpu-cycle
  //
  UINT64        CurrentTicker;
  UINT64        TimerPeriod;
  EFI_STATUS    Status;
  RIVL_VARIABLE *ExecTimeVariable;

  ExecTimeVariable = SearchRivlVariable (EXEC_TIME_NAME);
  if (ExecTimeVariable == NULL) {
    //
    // If the caller doesn't want to make statistics of
    // Interface-Call/Application-Exec time, just return
    //
    return ;
  }

  if (Cpu == NULL) {
    //
    // Locate CpuArch protocol
    //
    Status = tBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **)&Cpu);
    if (EFI_ERROR (Status)) {
      SctPrint (L"Locate CpuArch protocol error\n");
    }
  }

  Status = Cpu->GetTimerValue (Cpu, 0, &(CurrentTicker), &TimerPeriod);
  if (EFI_ERROR (Status)) {
    SctPrint (L"Get Timer Vaule error\n");
  }
  //
  // TimePeriod: according to the implementation, the meaning of 'TimerPeriod'
  //   Nano-seconds while CPU executes 1,000,000 cycles
  //
  if (EndTick > StartTick) {
    ExecTick = EndTick - StartTick;
  } else {
    ExecTick = MAX_U64_VAL - StartTick + EndTick;
  }
  //
  // ExecTime = SctMultU64x32(SctDivU64x32(ExecTick, 1000000, NULL), (UINTN)TimerPeriod);
  //
  ExecTime = SctDivU64x32 (SctMultU64x32 (ExecTick, (UINTN) TimerPeriod), 1000000, NULL);
  SctPrint (
    L"StartTick: %d, EndTick: %d, TimePeriod: %d, ExecTime: %d\n",
    (UINTN) StartTick,
    (UINTN) EndTick,
    (UINTN) TimerPeriod,
    (UINTN) ExecTime
    );
  //
  // Copy the value of ExecTime to the RIVL variable, it's the Caller's responsibility
  // to guarantee the Type of 'EXEC_TIME_NAME' should be UINT64
  //
  SctCopyMem (ExecTimeVariable->Address, &ExecTime, ExecTimeVariable->TypeSize);
  return ;
}

#if 0
EFI_STATUS
ResumeExecComd (
  VOID
  )
/*++

Routine Description:

  Resume SCT execution by executing "sct -c" in sct passive mode.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others      - Some failure happened.
  
--*/
{
  EFI_STATUS  Status;
  EFI_TIME    StartTime;
  EFI_TIME    EndTime;
  CHAR16      *Buffer;

  Buffer = EFI_SCT_CONTINUE_EXECUTION_NAME;
  //
  // PreDispatch: to get cmd and parameters
  //
  Status = PreDispatch (Buffer);
  if (EFI_ERROR (Status)) {
    (gEasFT->Cmd)->ComdResult = FAIL;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in ResumeExecComd: PreDispatch error - %r", Status));
    Status = PostDispatch ();
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in ResumeExecComd: PostDispatch status - %r\n", Status));
    }

    return Status;
  }
  //
  // Resume SCT execution by executing "sct -c" in sct passive mode.
  //
  tRT->GetTime (&StartTime, NULL);
  Status = SctShellExecute (&mImageHandle, (gEasFT->Cmd)->ComdArg, FALSE, NULL, NULL);;
  tRT->GetTime (&EndTime, NULL);
  EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"dispatch:(%s)", (gEasFT->Cmd)->ComdArg));
  SctPrint (L"dispatch:(%s) - %r\n", (gEasFT->Cmd)->ComdArg, Status);
  if (Status == EFI_OUT_OF_RESOURCES) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RecordMessage (
            &((gEasFT->Cmd)->ComdRuntimeInfo),
            &(gEasFT->Cmd)->ComdRuntimeInfoSize,
            L"TEST_EXEC (%s) Status - %r",
            (gEasFT->Cmd)->ComdArg,
            Status
            );
  if (Status == EFI_OUT_OF_RESOURCES) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RecordMessage (
            &((gEasFT->Cmd)->ComdOutput),
            &(gEasFT->Cmd)->ComdOutputSize,
            L"StartTime - %02d-%02d-%04d %02d:%02d:%02d, EndTime - %02d-%02d-%04d %02d:%02d:%02d",
            StartTime.Day,
            StartTime.Month,
            StartTime.Year,
            StartTime.Hour,
            StartTime.Minute,
            StartTime.Second,
            EndTime.Day,
            EndTime.Month,
            EndTime.Year,
            EndTime.Hour,
            EndTime.Minute,
            EndTime.Second
            );
  if (Status == EFI_OUT_OF_RESOURCES) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // For remote SCT execution, the potential reset during the execution will cause no ACK generation, so
  // after "sct -c" execution finish, corresponding ACK needs to be sent to inform remote EMS side application.
  //
  Status = PostDispatch ();
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in ResumeExecComd: PostDispatch status - %r\n", Status));
  }

  return Status;
}
#endif
