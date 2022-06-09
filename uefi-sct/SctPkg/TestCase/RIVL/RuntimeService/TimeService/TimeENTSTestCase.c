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

  TimeENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "TimeENTSTestCase.h"

//
// RT.GetTime
//
static EFI_TIME               *RTGetTimeTime;
static EFI_TIME_CAPABILITIES  *RTGetTimeCapabilities;
static EFI_STATUS             *RTGetTimeStatus;

ENTS_ARG_FIELD                tRTGetTimeArgField[] = {
  {
    POINTER,
    &RTGetTimeTime
  },
  {
    POINTER,
    &RTGetTimeCapabilities
  },
  {
    POINTER,
    &RTGetTimeStatus
  },
  0
};

EFI_STATUS
EFIAPI
RT_GetTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  GetTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTGetTimeStatus = RuntimeService->GetTime (
                                      RTGetTimeTime,
                                      RTGetTimeCapabilities
                                      );
  return EFI_SUCCESS;
}

//
// RT.SetTime
//
static EFI_TIME   *RTSetTimeTime;
static EFI_STATUS *RTSetTimeStatus;

ENTS_ARG_FIELD    tRTSetTimeArgField[] = {
  {
    POINTER,
    &RTSetTimeTime
  },
  {
    POINTER,
    &RTSetTimeStatus
  },
  0
};

EFI_STATUS
EFIAPI
RT_SetTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SetTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService    = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTSetTimeStatus  = RuntimeService->SetTime (RTSetTimeTime);
  return EFI_SUCCESS;
}

//
// RT.GetWakeupTime
//
static BOOLEAN    *RTGetWakeupTimeEnabled;
static BOOLEAN    *RTGetWakeupTimePending;
static EFI_TIME   *RTGetWakeupTimeTime;
static EFI_STATUS *RTGetWakeupTimeStatus;

ENTS_ARG_FIELD    tRTGetWakeupTimeArgField[] = {
  {
    POINTER,
    &RTGetWakeupTimeEnabled
  },
  {
    POINTER,
    &RTGetWakeupTimePending
  },
  {
    POINTER,
    &RTGetWakeupTimeTime
  },
  {
    POINTER,
    &RTGetWakeupTimeStatus
  },
  0
};

EFI_STATUS
EFIAPI
RT_GetWakeupTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  GetWakeupTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTGetWakeupTimeStatus = RuntimeService->GetWakeupTime (
                                            RTGetWakeupTimeEnabled,
                                            RTGetWakeupTimePending,
                                            RTGetWakeupTimeTime
                                            );
  return EFI_SUCCESS;
}

//
// RT.SetWakeupTime
//
static BOOLEAN    RTSetWakeupTimeEnabled;
static EFI_TIME   *RTSetWakeupTimeTime;
static EFI_STATUS *RTSetWakeupTimeStatus;

ENTS_ARG_FIELD    tRTSetWakeupTimeArgField[] = {
  {
    BOOL,
    &RTSetWakeupTimeEnabled
  },
  {
    POINTER,
    &RTSetWakeupTimeTime
  },
  {
    POINTER,
    &RTSetWakeupTimeStatus
  },
  0
};

EFI_STATUS
EFIAPI
RT_SetWakeupTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SetWakeupTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTSetWakeupTimeStatus = RuntimeService->SetWakeupTime (
                                            RTSetWakeupTimeEnabled,
                                            RTSetWakeupTimeTime
                                            );
  return EFI_SUCCESS;
}
