/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EasCmdDisp.h

Abstract:

  SCT extended data services declarations.

--*/

#ifndef _EAS_CMD_DISP_H_
#define _EAS_CMD_DISP_H_

//
// External functions declarations
//
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
;

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
;

EFI_STATUS
GetCmdDispatch (
  IN  CHAR16               *Buffer,
  OUT EFI_MONITOR_COMMAND  *Cmd
  );

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
;

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
;

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
;

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
;

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
;

#endif
