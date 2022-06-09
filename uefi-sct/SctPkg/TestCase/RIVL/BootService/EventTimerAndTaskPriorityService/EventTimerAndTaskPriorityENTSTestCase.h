/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  EventTimerAndTaskPriorityENTSTestCase.h

Abstract:

--*/

#ifndef _EVENT_TIMER_AND_TASK_PRIORITY_ENTS_TESTCASE_H_
#define _EVENT_TIMER_AND_TASK_PRIORITY_ENTS_TESTCASE_H_

#include "SctLib.h"
#include "Eas.h"

EFI_STATUS
EFIAPI
BS_CreateEvent_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  CreateEvent Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
BS_CloseEvent_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  CloseEvent Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
BS_SignalEvent_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SignalEvent Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
BS_WaitForEvent_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  WaitForEvent Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
BS_CheckEvent_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 CheckEvent Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
BS_SetTimer_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 SetTimer Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gBootServiceRuntimeInfo;
extern UINTN          gBootServiceRuntimeInfoSize;

extern ENTS_ARG_FIELD BSCreateEventArgField[];
extern ENTS_ARG_FIELD BSCloseEventArgField[];
extern ENTS_ARG_FIELD BSSignalEventArgField[];
extern ENTS_ARG_FIELD BSWaitForEventArgField[];
extern ENTS_ARG_FIELD BSCheckEventArgField[];
extern ENTS_ARG_FIELD BSSetTimerArgField[];

#endif
