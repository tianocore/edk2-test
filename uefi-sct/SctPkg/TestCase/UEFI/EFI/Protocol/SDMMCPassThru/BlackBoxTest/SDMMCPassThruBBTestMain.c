/** @file

  Copyright 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SDMMCPassThruBBTestMain.c

Abstract:

  Test Driver of SDMMC Pass Thru Protocol

--*/


#include "SDMMCPassThruBBTestMain.h"

#define EFI_SDMMC_PASS_THRU_TEST_GUID \
  {0x716ef0d9, 0xff83, 0x4f69, {0x81, 0xe9, 0x51, 0x8b, 0xd3, 0x9a, 0x8e, 0x70} }

//
// Global variables
//
EFI_HANDLE mImageHandle;

UINT8      EnterEvent;


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_REVISION,
  EFI_SDMMC_PASS_THRU_TEST_GUID,
  L"SDMMC Pass Thru Protocol Test",
  L"UEFI SDMMC Pass Thru Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0101,
    L"PassThruFunction",
    L"Function auto test for SDMMC Pass Thru Protocol PassThru().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestPassThruFunctionTest
  },

  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetNextSlotFunction",
    L"Function auto test for SDMMC Pass Thru Protocol GetNextSlot().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextSlotFunctionTest
  },

  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0103,
    L"BuildDevicePathFunction",
    L"Function auto test for SDMMC Pass Thru Protocol BuildDevicePath().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathFunctionTest
  },

  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0104,
    L"GetSlotNumberFunction",
    L"Function auto test for SDMMC Pass Thru Protocol GetSlotNumber().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetSlotNumberFunctionTest
  },

  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0105,
    L"ResetDeviceFunction",
    L"Function auto test for SDMMC Pass Thru Protocol ResetDevice().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestResetDeviceFunctionTest
  },
    
  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0201,
    L"PassThruConformance",
    L"Conformance auto test for SDMMC Pass Thru Protocol PassThru().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestPassThruConformanceTest
  },

  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0202,
    L"GetNextSlotConformance",
    L"Conformance auto test for SDMMC Pass Thru Protocol GetNextSlot().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextSlotConformanceTest
  },

  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0203,
    L"BuildDevicePathConformance",
    L"Conformance auto test for SDMMC Pass Thru Protocol BuildDevicePath().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestBuildDevicePathConformanceTest
  },

  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0204,
    L"GetSlotNumberConformance",
    L"Conformance auto test for SDMMC Pass Thru Protocol GetSlotNumber().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetSlotNumberConformanceTest
  },

  {
    EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0205,
    L"ResetDeviceConformance",
    L"Conformance auto test for SDMMC Pass Thru Protocol ResetDevice().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestResetDeviceConformanceTest
  },
 0
};


EFI_STATUS
EFIAPI
InitializeSDMMCPassThruBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
             &ImageHandle,
             &gBBTestProtocolField,
             gBBTestEntryField,
             UnloadSDMMCPassThruBBTest,
             &gBBTestProtocolInterface
             );

}


EFI_STATUS
EFIAPI
UnloadSDMMCPassThruBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


/**
  Allocates a buffer of a certain pool type at a specified alignment.

  Allocates the number bytes specified by AllocationSize of a certain pool type with an alignment
  specified by Alignment.  The allocated buffer is returned.  If AllocationSize is 0, then a valid
  buffer of 0 size is returned.  If there is not enough memory at the specified alignment remaining
  to satisfy the request, then NULL is returned.
  If Alignment is not a power of two and Alignment is not zero, then ASSERT().

  @param  PoolType              The type of pool to allocate.
  @param  AllocationSize        The number of bytes to allocate.
  @param  Alignment             The requested alignment of the allocation.  Must be a power of two.                            If Alignment is zero, then byte alignment is used.
                                If Alignment is zero, then byte alignment is used.

  @return A pointer to the allocated buffer or NULL if allocation fails.

**/
VOID *
AllocateAlignedPool (
  IN EFI_MEMORY_TYPE  PoolType,
  IN UINTN            AllocationSize,
  IN UINTN            Alignment
  )
{
  EFI_STATUS  Status;
  VOID        *RawAddress;
  UINTN       AlignedAddress;
  UINTN       AlignmentMask;
  UINTN       OverAllocationSize;
  UINTN       RealAllocationSize;
  VOID        **FreePointer;

  //
  // Alignment must be a power of two or zero.
  //
  ASSERT ((Alignment & (Alignment - 1)) == 0);
  
  if (Alignment == 0) {
    AlignmentMask = Alignment;
  } else {
    AlignmentMask = Alignment - 1;
  }
  //
  // Calculate the extra memory size, over-allocate memory pool and get the aligned memory address. 
  //
  OverAllocationSize  = sizeof (RawAddress) + AlignmentMask;
  RealAllocationSize  = AllocationSize + OverAllocationSize;
  //
  // Make sure that AllocationSize plus OverAllocationSize does not overflow. 
  //
  ASSERT (RealAllocationSize > AllocationSize); 

  Status = gtBS->AllocatePool (PoolType, RealAllocationSize, (VOID **) &RawAddress);
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  AlignedAddress      = ((UINTN) RawAddress + OverAllocationSize) & ~AlignmentMask;
  //
  // Save the original memory address just before the aligned address.
  //
  FreePointer         = (VOID **)(AlignedAddress - sizeof (RawAddress));
  *FreePointer        = RawAddress;

  return (VOID *) AlignedAddress;
}


/**
  Frees a buffer that was previously allocated with one of the aligned pool allocation functions 
  in the Memory Allocation Library.

  Frees the buffer specified by Buffer.  Buffer must have been allocated on a previous call to the
  aligned pool allocation services of the Memory Allocation Library.
  If Buffer was not allocated with an aligned pool allocation function in the Memory Allocation
  Library, then ASSERT().

  @param  Buffer                Pointer to the buffer to free.

  @return free aligned pool function status

**/
EFI_STATUS
FreeAlignedPool (
  IN VOID   *Buffer
  )
{
  VOID        *RawAddress;
  VOID        **FreePointer;
  EFI_STATUS  Status;

  //
  // Get the pre-saved original address in the over-allocate pool.
  //
  FreePointer = (VOID **)((UINTN) Buffer - sizeof (RawAddress));
  RawAddress  = *FreePointer;

  Status = gtBS->FreePool (RawAddress);

  return Status;
}

VOID
NotifyFunction (
  EFI_EVENT    Event,
  VOID         *Context
  )
{
  EnterEvent = 1;
  return;
}

