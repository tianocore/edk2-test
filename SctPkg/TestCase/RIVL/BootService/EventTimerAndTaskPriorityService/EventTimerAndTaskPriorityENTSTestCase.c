/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  EventTimerAndTaskPriorityENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "EventTimerAndTaskPriorityENTSTestCase.h"

VOID
BSNotifyFunction0 (
  EFI_EVENT Event,
  VOID      *Context
  );

VOID
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
                                        BSNotifyFunctionList[BSCreateEventNotifyFunction],
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
