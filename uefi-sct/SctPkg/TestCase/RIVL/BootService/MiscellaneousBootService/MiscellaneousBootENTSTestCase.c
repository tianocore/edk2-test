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

  MiscellaneousBootENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "MiscellaneousBootENTSTestCase.h"

//
// tBS.SetWatchdogTimer
//
static UINTN      BSSetWatchdogTimerTimeout;
static UINT64     BSSetWatchdogTimerWatchdogCode;
static UINTN      BSSetWatchdogTimerDataSize;
static CHAR16     *BSSetWatchdogTimerWatchdogData;
static EFI_STATUS *BSSetWatchdogTimerStatus;

ENTS_ARG_FIELD    BSSetWatchdogTimerArgField[] = {
  {
    OCTETN,
    &BSSetWatchdogTimerTimeout
  },
  {
    OCTET8,
    &BSSetWatchdogTimerWatchdogCode
  },
  {
    OCTETN,
    &BSSetWatchdogTimerDataSize
  },
  {
    POINTER,
    &BSSetWatchdogTimerWatchdogData
  },
  {
    POINTER,
    &BSSetWatchdogTimerStatus
  },
  0
};

EFI_STATUS
EFIAPI
BS_SetWatchdogTimer_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 SetWatchdogTimer Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSSetWatchdogTimerStatus = BootService->SetWatchdogTimer (
                                            BSSetWatchdogTimerTimeout,
                                            BSSetWatchdogTimerWatchdogCode,
                                            BSSetWatchdogTimerDataSize,
                                            BSSetWatchdogTimerWatchdogData
                                            );
  return EFI_SUCCESS;
}

//
// tBS.Stall
//
static UINTN      BSStallMicroseconds;
static EFI_STATUS *BSStallStatus;

ENTS_ARG_FIELD    BSStallArgField[] = {
  {
    OCTETN,
    &BSStallMicroseconds
  },
  {
    POINTER,
    &BSStallStatus
  },
  0
};

EFI_STATUS
EFIAPI
BS_Stall_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 Stall Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService     = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSStallStatus  = BootService->Stall (BSStallMicroseconds);
  return EFI_SUCCESS;
}

//
// tBS.CopyMem
//
static VOID     *BSCopyMemDestination;
static VOID     *BSCopyMemSource;
static UINTN    BSCopyMemLength;

ENTS_ARG_FIELD  BSCopyMemArgField[] = {
  {
    POINTER,
    &BSCopyMemDestination
  },
  {
    POINTER,
    &BSCopyMemSource
  },
  {
    OCTETN,
    &BSCopyMemLength
  },
  0
};

EFI_STATUS
EFIAPI
BS_CopyMem_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 CopyMem Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  BootService->CopyMem (
                BSCopyMemDestination,
                BSCopyMemSource,
                BSCopyMemLength
                );
  return EFI_SUCCESS;
}

//
// tBS.SetMem
//
static VOID     *BSSetMemBuffer;
static UINTN    BSSetMemSize;
static UINT8    BSSetMemValue;

ENTS_ARG_FIELD  BSSetMemArgField[] = {
  {
    POINTER,
    &BSSetMemBuffer
  },
  {
    OCTETN,
    &BSSetMemSize
  },
  {
    OCTET1,
    &BSSetMemValue
  },
  0
};

EFI_STATUS
EFIAPI
BS_SetMem_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 SetMem Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  BootService->SetMem (
                BSSetMemBuffer,
                BSSetMemSize,
                BSSetMemValue
                );
  return EFI_SUCCESS;
}
