/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EAS.c

Abstract:

--*/


#include "Sct.h"
#include "Sct.h"
#include EFI_TEST_PROTOCOL_DEFINITION (EntsMonitorProtocol)

static EFI_TIME Epoch = { .Year = 1970, .Month = 1, .Day = 1 };

STATIC
EFI_STATUS
AgentTestMain (
  VOID
  );

STATIC
VOID
EmptyDelayedPostCmd (
  VOID
  );

STATIC
EFI_STATUS
SctAgentCmdDispatch (
  IN EFI_ENTS_MONITOR_PROTOCOL     *EntsMonitor,
  IN CHAR16                        *CmdString,
  IN UINTN                         CmdStrSize
  );

typedef struct _SCT_AGENT_CMD_DELAYED_POST {
  EFI_MONITOR_COMMAND              Cmd;
  EFI_STATUS                       CmdReturn;
  EFI_TIME                         StartTime;
  EFI_TIME                         EndTime;
}SCT_AGENT_CMD_DELAYED_POST;

STATIC SCT_AGENT_CMD_DELAYED_POST *SctAgentCmdDelayedPost = NULL;

EFI_STATUS
SctPassiveExecute (
  VOID
  )
/*++

Routine Description:

  Start SCT agent to enter passive mode.

Arguments:
  
  ImageHandle           - The image handle.
  SystemTable           - The system table.
  DevicePath            - The device path of the image handle.
  FilePath              - The file path of the image handle.
  MonitorName           - Monitor name for Communication layer, current we 
                          define the following three types: Mnp  Ip4  Serial
Returns:

  EFI_SUCCESS           - Agent quits successfully.
  EFI_INVALID_PARAMETER - Parameter invalid.
  Others                - Problems occur in monitor initialization, command 
                          dispatch or environment cleanup.

--*/
{
  EFI_STATUS  Status;

  EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"NetworkTest Start"));
  Status = InitResources (
             gFT->ImageHandle,
             gFT->SystemTable,
             gFT->DevicePath,
             gFT->FilePath,
             gFT->MonitorName
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"InitResources success"));

  Status = AgentTestMain ();
  if (EFI_ERROR (Status)) {
    FreeResources ();
    return Status;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"AgentTestMain success"));

  Status = FreeResources ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"FreeResources success"));

  return EFI_SUCCESS;
}

EFI_STATUS
AgentTestMain (
  VOID
  )
/*++

Routine Description:

  Entry point of AgentTestMain.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                Status;
  CHAR16                    *Buffer;
  UINTN                     BufferSize;
  EFI_ENTS_MONITOR_PROTOCOL *EntsMonitor;

  SctPrint (L"\n!!!Enter Main\n");

  BufferSize  = 0;
  Buffer      = NULL;
  Status      = EFI_SUCCESS;
  EntsMonitor = gEasFT->Monitor;

  Status = PostSctAgentDelayedCmd();
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"PostSctAgentDelayedCmd error - %r", Status));
    return Status;
  }

  EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"PostSctAgentDelayedCmd succes"));

  while (TRUE) {
    if (Buffer) {
      EntsFreePool(Buffer);
      Buffer      = NULL;
      BufferSize  = 0;
    }

    Status = EntsMonitor->MonitorListener (EntsMonitor, &BufferSize, &Buffer);
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in AgentTestMain: Listen error - %r", Status));
      break;
    }

    if (EntsMonitor->CleanUpEnvironmentFlag) {
      RivlDelRivlType (NULL);
      RivlDelRivlVariable (NULL);
      EntsMonitor->CleanUpEnvironmentFlag = FALSE;
      continue;
    }

    Status = SctAgentCmdDispatch(EntsMonitor, Buffer, BufferSize);
    if (Status == EFI_ABORTED) {
      Status = EFI_SUCCESS;
      break;
    }
  }

  if (Buffer != NULL) {
    EntsFreePool(Buffer);
    Buffer      = NULL;
    BufferSize  = 0;
  }

  return Status;
}

EFI_STATUS
SctAgentCmdDispatch (
  IN EFI_ENTS_MONITOR_PROTOCOL     *EntsMonitor,
  IN CHAR16                        *CmdString,
  IN UINTN                         CmdStrSize
  )
{
  EFI_STATUS                       Status;
  EFI_MONITOR_COMMAND              *MonitorCmd;

  if ((CmdString == NULL) || (CmdStrSize == 0)) {
    return EFI_INVALID_PARAMETER;
  }

  EntsOutput (L"listened:(%s)\n", CmdString);

  MonitorCmd  = gEasFT->Cmd;

  //
  // PreDispatch: to get cmd and parameters
  //
  Status = PreDispatch (CmdString);
  if (EFI_ERROR (Status)) {
    MonitorCmd->ComdResult = FAIL;
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in AgentTestMain: PreDispatch error - %r", Status));
    Status = PostDispatch (MonitorCmd);
    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in AgentTestMain: PostDispatch status - %r\n", Status));
    }
    return Status;
  }

  //
  // Dispatch
  //
  switch(MonitorCmd->CmdType) {
  case ABORT:
    //
    // Should exit the SCT Agent
    //
    RivlDelRivlType (NULL);
    RivlDelRivlVariable (NULL);
    return EFI_ABORTED;

  case ELET_CMD:
    Status = DispatchEletComd ();
    break;

  case EXECUTE:
    EntsMonitor->MonitorSaveContext(EntsMonitor);
    FreeDebugServices();
    Status = DispatchExecComd ();
    InitializeDebugServices();
    EntsMonitor->MonitorRestoreContext(EntsMonitor);
    break;

  case GET_FILE:
  case PUT_FILE:
    Status = DispatchFileTransferComd (MonitorCmd->CmdType);
    break;

  default:
    Status = DispatchInternalComd ();
  }

  if (Status == EFI_OUT_OF_RESOURCES) {
    //
    // Should exit the SCT Agent
    //
    return EFI_ABORTED;
  }

  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in AgentTestMain: Dispatch status - %r\n", Status));
    MonitorCmd->ComdResult = FAIL;
  } else {
    MonitorCmd->ComdResult = PASS;
  }

  Status = PostDispatch (MonitorCmd);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in AgentTestMain: PostDispatch status - %r\n", Status));
  }

  return Status;
}

EFI_STATUS
DelaySctAgentCmdPost (
  IN CHAR16                         *CmdBuffer,
  IN EFI_STATUS                     CmdReturn,
  IN ENTS_CMD_RESULT                CmdResult
  )
{
  EFI_STATUS                        Status;

  if (CmdBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  SctAgentCmdDelayedPost = (SCT_AGENT_CMD_DELAYED_POST *)EntsAllocateZeroPool(sizeof(SCT_AGENT_CMD_DELAYED_POST));
  if (SctAgentCmdDelayedPost == NULL) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Allocate pool for delayed command fail"));
	return EFI_OUT_OF_RESOURCES;
  }

  SctAgentCmdDelayedPost->Cmd.Signature = EFI_MONITOR_COMMAND_SIGNATURE;
  SctAgentCmdDelayedPost->Cmd.Version   = EFI_MONITOR_COMMAND_VERSION;
  Status = GetCmdDispatch(CmdBuffer, &SctAgentCmdDelayedPost->Cmd);
  if (EFI_ERROR(Status)) {
    EntsFreePool(SctAgentCmdDelayedPost);
	SctAgentCmdDelayedPost = NULL;
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"GetCmdDispatch Error - %r", Status));
    return Status;
  }
  SctAgentCmdDelayedPost->CmdReturn      = CmdReturn;
  SctAgentCmdDelayedPost->Cmd.ComdResult = CmdResult;
  if (tRT->GetTime (&SctAgentCmdDelayedPost->StartTime, NULL) != EFI_SUCCESS)
    SctAgentCmdDelayedPost->StartTime = Epoch;

  return Status;
}

EFI_STATUS
PostSctAgentDelayedCmd (
  VOID
  )
{
  EFI_STATUS                        Status;
  EFI_ENTS_MONITOR_PROTOCOL         *EntsMonitor;

  if (SctAgentCmdDelayedPost == NULL) {
    return EFI_SUCCESS;
  }

  if (tRT->GetTime (&SctAgentCmdDelayedPost->EndTime, NULL) != EFI_SUCCESS)
    SctAgentCmdDelayedPost->EndTime = Epoch;

  Status = RecordMessage (
            &SctAgentCmdDelayedPost->Cmd.ComdRuntimeInfo,
            &SctAgentCmdDelayedPost->Cmd.ComdRuntimeInfoSize,
            L"TEST_EXEC (%s) Status - %r",
            SctAgentCmdDelayedPost->Cmd.ComdArg,
            SctAgentCmdDelayedPost->CmdReturn
            );
  if (Status == EFI_OUT_OF_RESOURCES) {
    goto RecordMessageReturn;
  }

  Status = RecordMessage (
            &SctAgentCmdDelayedPost->Cmd.ComdOutput,
            &SctAgentCmdDelayedPost->Cmd.ComdOutputSize,
            L"StartTime - %02d-%02d-%04d %02d:%02d:%02d, EndTime - %02d-%02d-%04d %02d:%02d:%02d",
            SctAgentCmdDelayedPost->StartTime.Day,
            SctAgentCmdDelayedPost->StartTime.Month,
            SctAgentCmdDelayedPost->StartTime.Year,
            SctAgentCmdDelayedPost->StartTime.Hour,
            SctAgentCmdDelayedPost->StartTime.Minute,
            SctAgentCmdDelayedPost->StartTime.Second,
            SctAgentCmdDelayedPost->EndTime.Day,
            SctAgentCmdDelayedPost->EndTime.Month,
            SctAgentCmdDelayedPost->EndTime.Year,
            SctAgentCmdDelayedPost->EndTime.Hour,
            SctAgentCmdDelayedPost->EndTime.Minute,
            SctAgentCmdDelayedPost->EndTime.Second
            );
  if (Status == EFI_OUT_OF_RESOURCES) {
    goto RecordMessageReturn;
  }

  EntsMonitor = gEasFT->Monitor;
  EntsMonitor->MonitorRestoreContext(EntsMonitor);

  Status = PostDispatch (&SctAgentCmdDelayedPost->Cmd);
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"PostDispatch fail - %r", Status));
  }

RecordMessageReturn:
  EmptyDelayedPostCmd();
  return Status;
}

STATIC
VOID
EmptyDelayedPostCmd (
  VOID
  )
{
  EFI_MONITOR_COMMAND              *Cmd;

  Cmd = &SctAgentCmdDelayedPost->Cmd;

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
}

