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

  MemoryAllocationENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "MemoryAllocationENTSTestCase.h"

//
// tBS.AllocatePages
//
static EFI_ALLOCATE_TYPE    BSAllocatePagesType;
static EFI_MEMORY_TYPE      BSAllocatePagesMemoryType;
static UINTN                BSAllocatePagesPages;
static EFI_PHYSICAL_ADDRESS *BSAllocatePagesMemory;
static EFI_STATUS           *BSAllocatePagesStatus;

ENTS_ARG_FIELD              BSAllocatePagesArgField[] = {
  {
    OCTETN,
    &BSAllocatePagesType
  },
  {
    OCTETN,
    &BSAllocatePagesMemoryType
  },
  {
    OCTETN,
    &BSAllocatePagesPages
  },
  {
    POINTER,
    &BSAllocatePagesMemory
  },
  {
    POINTER,
    &BSAllocatePagesStatus
  },
  0
};

EFI_STATUS
EFIAPI
BS_AllocatePages_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 AllocatePages Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSAllocatePagesStatus = BootService->AllocatePages (
                                          BSAllocatePagesType,
                                          BSAllocatePagesMemoryType,
                                          BSAllocatePagesPages,
                                          BSAllocatePagesMemory
                                          );
  return EFI_SUCCESS;
}

//
// tBS.FreePages
//
static EFI_PHYSICAL_ADDRESS BSFreePagesMemory;
static UINTN                BSFreePagesPages;
static EFI_STATUS           *BSFreePagesStatus;

ENTS_ARG_FIELD              BSFreePagesArgField[] = {
  {
    OCTETN,
    &BSFreePagesMemory
  },
  {
    OCTETN,
    &BSFreePagesPages
  },
  {
    POINTER,
    &BSFreePagesStatus
  },
  0
};

EFI_STATUS
EFIAPI
BS_FreePages_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 FreePages Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSFreePagesStatus = BootService->FreePages (
                                      BSFreePagesMemory,
                                      BSFreePagesPages
                                      );
  return EFI_SUCCESS;
}

//
// tBS.AllocatePool
//
static EFI_MEMORY_TYPE  BSAllocatePoolPoolType;
static UINTN            BSAllocatePoolSize;
static VOID             **BSAllocatePoolBuffer;
static EFI_STATUS       *BSAllocatePoolStatus;

ENTS_ARG_FIELD              BSAllocatePoolArgField[] = {
  {
    OCTETN,
    &BSAllocatePoolPoolType
  },
  {
    OCTETN,
    &BSAllocatePoolSize
  },
  {
    POINTER,
    &BSAllocatePoolBuffer
  },
  {
    POINTER,
    &BSAllocatePoolStatus
  },
  0
};

EFI_STATUS
EFIAPI
BS_AllocatePool_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 AllocatePool Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSAllocatePoolStatus = BootService->AllocatePool (
                                        BSAllocatePoolPoolType,
                                        BSAllocatePoolSize,
                                        (VOID **) BSAllocatePoolBuffer
                                        );
  return EFI_SUCCESS;
}

//
// tBS.FreePool
//
static VOID       *BSFreePoolBuffer;
static EFI_STATUS *BSFreePoolStatus;

ENTS_ARG_FIELD    BSFreePoolArgField[] = {
  {
    POINTER,
    &BSFreePoolBuffer
  },
  {
    POINTER,
    &BSFreePoolStatus
  },
  0
};

EFI_STATUS
EFIAPI
BS_FreePool_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 FreePool Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_BOOT_SERVICES *BootService;

  BootService       = (EFI_BOOT_SERVICES *) ClientInterface;

  *BSFreePoolStatus = BootService->FreePool (BSFreePoolBuffer);
  return EFI_SUCCESS;
}
