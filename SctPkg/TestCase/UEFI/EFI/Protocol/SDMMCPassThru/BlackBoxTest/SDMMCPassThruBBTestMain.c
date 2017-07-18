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
                                                                
  Copyright 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
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

