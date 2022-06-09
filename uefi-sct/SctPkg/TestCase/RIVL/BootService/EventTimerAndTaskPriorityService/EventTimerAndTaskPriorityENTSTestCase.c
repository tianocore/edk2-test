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
  EventTimerAndTaskPriorityENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "EventTimerAndTaskPriorityENTSTestCase.h"

VOID
EFIAPI
BSNotifyFunction0 (
  EFI_EVENT Event,
  VOID      *Context
  );

VOID
EFIAPI
BSNotifyFunction1 (
  EFI_EVENT Event,
  VOID      *Context
  );

static EFI_EVENT_NOTIFY BSNotifyFunctionList[] = {
  BSNotifyFunction0,
  BSNotifyFunction1
};

//
// tBS.CreateEvent
//
static UINT32           BSCreateEventType;
static EFI_TPL          BSCreateEventNotifyTpl;
static UINTN            BSCreateEventNotifyFunction;
static VOID             *BSCreateEventNotifyContext;
static EFI_EVENT        *BSCreateEventEvent;
static EFI_STATUS       *BSCreateEventStatus;

ENTS_ARG_FIELD          BSCreateEventArgField[] = {
  {
    OCTET4,
    &BSCreateEventType
  },
  {
    OCTETN,
    &BSCreateEventNotifyTpl
  },
  {
    OCTETN,
    &BSCreateEventNotifyFunction
  },
  {
    POINTER,
    &BSCreateEventNotifyContext
  },
  {
    POINTER,
    &BSCreateEventEvent
  },
  {
    POINTER,
    &BSCreateEventStatus
  },
  0
};

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
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSCreateEventStatus = BootService->CreateEvent (
                                        BSCreateEventType,
                                        BSCreateEventNotifyTpl,
                                        (EFI_EVENT_NOTIFY) BSNotifyFunctionList[BSCreateEventNotifyFunction],
                                        BSCreateEventNotifyContext,
                                        BSCreateEventEvent
                                        );
  return EFI_SUCCESS;
}

//
// BS.CloseEvent
//
static EFI_EVENT  BSCloseEventEvent;
static EFI_STATUS *BSCloseEventStatus;

ENTS_ARG_FIELD    BSCloseEventArgField[] = {
  {
    OCTETN,
    &BSCloseEventEvent
  },
  {
    POINTER,
    &BSCloseEventStatus
  },
  0
};

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
{
  EFI_BOOT_SERVICES *BootService;

  BootService         = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSCloseEventStatus = BootService->CloseEvent (BSCloseEventEvent);
  return EFI_SUCCESS;
}

//
// tBS.SignalEvent
//
static EFI_EVENT  BSSignalEventEvent;
static EFI_STATUS *BSSignalEventStatus;

ENTS_ARG_FIELD    BSSignalEventArgField[] = {
  {
    OCTETN,
    &BSSignalEventEvent
  },
  {
    POINTER,
    &BSSignalEventStatus
  },
  0
};

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
{
  EFI_BOOT_SERVICES *BootService;

  BootService           = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSSignalEventStatus  = BootService->SignalEvent (BSSignalEventEvent);
  return EFI_SUCCESS;
}

//
// tBS.WaitForEvent
//
static UINTN      BSWaitForEventNumberOfEvents;
static EFI_EVENT  *BSWaitForEventEvent;
static UINTN      *BSWaitForEventIndex;
static EFI_STATUS *BSWaitForEventStatus;

ENTS_ARG_FIELD    BSWaitForEventArgField[] = {
  {
    OCTETN,
    &BSWaitForEventNumberOfEvents
  },
  {
    POINTER,
    &BSWaitForEventEvent
  },
  {
    POINTER,
    &BSWaitForEventIndex
  },
  {
    POINTER,
    &BSWaitForEventStatus
  },
  0
};

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
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSWaitForEventStatus = BootService->WaitForEvent (
                                        BSWaitForEventNumberOfEvents,
                                        BSWaitForEventEvent,
                                        BSWaitForEventIndex
                                        );
  return EFI_SUCCESS;
}

//
// tBS.CheckEvent
//
static EFI_EVENT  BSCheckEventEvent;
static EFI_STATUS *BSCheckEventStatus;

ENTS_ARG_FIELD    BSCheckEventArgField[] = {
  {
    OCTETN,
    &BSCheckEventEvent
  },
  {
    POINTER,
    &BSCheckEventStatus
  },
  0
};

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
{
  EFI_BOOT_SERVICES *BootService;

  BootService         = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSCheckEventStatus = BootService->CheckEvent (BSCheckEventEvent);
  return EFI_SUCCESS;
}

//
// tBS.SetTimer
//
static EFI_EVENT        BSSetTimerEvent;
static EFI_TIMER_DELAY  BSSetTimerType;
static UINT64           BSSetTimerTriggerTime;
static EFI_STATUS       *BSSetTimerStatus;

ENTS_ARG_FIELD          BSSetTimerArgField[] = {
  {
    OCTETN,
    &BSSetTimerEvent
  },
  {
    OCTETN,
    &BSSetTimerType
  },
  {
    OCTET8,
    &BSSetTimerTriggerTime
  },
  {
    POINTER,
    &BSSetTimerStatus
  },
  0
};

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
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSSetTimerStatus = BootService->SetTimer (
                                    BSSetTimerEvent,
                                    BSSetTimerType,
                                    BSSetTimerTriggerTime
                                    );
  return EFI_SUCCESS;
}

VOID
EFIAPI
BSNotifyFunction0 (
  EFI_EVENT Event,
  VOID      *Context
  )
/*++

Routine Description:

  Callback function for event notification.

Arguments:

  Event   -  EFI Event.
  Context -  Event context.

Returns:

  None.

--*/
{
  return ;
}

VOID
EFIAPI
BSNotifyFunction1 (
  EFI_EVENT Event,
  VOID      *Context
  )
/*++

Routine Description:

  Callback function for event notification.

Arguments:

  Event   -  EFI Event.
  Context -  Event context.

Returns:

  None.

--*/
{
  UINTN *NotifyTimes;

  if (Context == NULL) {
    return ;
  }

  NotifyTimes = (UINTN *) Context;
  (*NotifyTimes)++;

  return ;
}
