/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2021, ARM Limited. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MemoryAllocationServicesBBTestFunction.c

Abstract:

  Interface Test Cases of Memory Allocation Boot Services

--*/

#include "SctLib.h"
#include "MemoryAllocationServicesBBTestMain.h"

#define ALLOCATEPAGES_MEMORYTYPE_NUM 16

EFI_MEMORY_TYPE AllocatePagesMemoryType[ALLOCATEPAGES_MEMORYTYPE_NUM] = {
  EfiLoaderCode,
  EfiLoaderData,
  EfiRuntimeServicesCode,
  EfiRuntimeServicesData,
  EfiBootServicesCode,
  EfiBootServicesData,
  EfiUnusableMemory,
  EfiACPIReclaimMemory,
  EfiACPIMemoryNVS,
  EfiMemoryMappedIO,
  EfiMemoryMappedIOPortSpace,
  EfiPalCode,
  EfiReservedMemoryType,
  0x80000000,
  0xC0000000,
  0xFFFFFFFF
};

#define ALLOCATEPOOL_MEMORYTYPE_NUM 16

EFI_MEMORY_TYPE AllocatePoolMemoryType[ALLOCATEPOOL_MEMORYTYPE_NUM] = {
  EfiLoaderCode,
  EfiLoaderData,
  EfiRuntimeServicesCode,
  EfiRuntimeServicesData,
  EfiBootServicesCode,
  EfiBootServicesData,
  EfiUnusableMemory,
  EfiACPIReclaimMemory,
  EfiACPIMemoryNVS,
  EfiMemoryMappedIO,
  EfiMemoryMappedIOPortSpace,
  EfiPalCode,
  EfiReservedMemoryType,
  0x80000000,
  0xC0000000,
  0xFFFFFFFF
};

/**
 *  Entrypoint for gtBS->GetMemoryMap() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestGetMemoryMapInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  UINTN                                MemoryMapSize;
  UINTN                                MapKey, MapKey2, MapKey3;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  EFI_PHYSICAL_ADDRESS                 Memory;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = InitMemoryMap ();
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InitMemoryMap - Allocate memory map buffer",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.1.2.1  GetMemoryMap must succeed with valid parameters.
    //
    MemoryMapSize = MemoryMapSizeNeeded;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetMemoryMap (
                     &MemoryMapSize,
                     (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                     &MapKey,
                     &DescriptorSize,
                     &DescriptorVersion
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMemoryAllocationServicesInterfaceTestAssertionGuid001: \
                   (Index == 1? \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid001: \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid002),
                   L"BS.GetMemoryMap - Valid parameters",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // 4.1.2.2  GetMemoryMap should return different MapKey when memory map
    //          is changed.
    //
    MemoryMapSize = MemoryMapSizeNeeded;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetMemoryMap (
                     &MemoryMapSize,
                     (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                     &MapKey,
                     &DescriptorSize,
                     &DescriptorVersion
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      MapKey = 0;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMemoryAllocationServicesInterfaceTestAssertionGuid002: \
                   (Index == 1? \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid003: \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid004),
                   L"BS.GetMemoryMap - Get first map key",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    Status = gtBS->AllocatePages (
                     AllocateAnyPages,
                     EfiBootServicesData,
                     1,
                     &Memory
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.AllocatePages - 1 page EfiBootServicesData",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      continue;
    }
    MemoryMapSize = MemoryMapSizeNeeded;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetMemoryMap (
                     &MemoryMapSize,
                     (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                     &MapKey2,
                     &DescriptorSize,
                     &DescriptorVersion
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      MapKey2 = 0;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMemoryAllocationServicesInterfaceTestAssertionGuid003: \
                   (Index == 1? \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid005: \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid006),
                   L"BS.GetMemoryMap - Get second map key",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    Status = gtBS->FreePages (
                     Memory,
                     1
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.FreePages - 1 page EfiBootServicesData",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      continue;
    }
    MemoryMapSize = MemoryMapSizeNeeded;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetMemoryMap (
                     &MemoryMapSize,
                     (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                     &MapKey3,
                     &DescriptorSize,
                     &DescriptorVersion
                     );
    gtBS->RestoreTPL (OldTpl);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      MapKey3 = 0;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMemoryAllocationServicesInterfaceTestAssertionGuid005: \
                   (Index == 1? \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid009: \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid010),
                   L"BS.GetMemoryMap - Get third map key",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if ((MapKey != 0) && (MapKey2 != 0) && (MapKey3 != 0)
         && (MapKey != MapKey2) && (MapKey2 != MapKey3)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gMemoryAllocationServicesInterfaceTestAssertionGuid006: \
                   (Index == 1? \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid011: \
                    gMemoryAllocationServicesBBTestFunctionAssertionGuid012),
                   L"BS.GetMemoryMap - Different MapKey",
                   L"%a:%d:TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->AllocatePages() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestAllocatePagesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_PHYSICAL_ADDRESS                 Start;
  EFI_PHYSICAL_ADDRESS                 Memory;
  EFI_PHYSICAL_ADDRESS                 Memory2;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  UINTN                                TypeIndex;
  EFI_TPL                              OldTpl;
  EFI_MEMORY_DESCRIPTOR                Descriptor;
  UINTN                                PageNum;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = InitMemoryMap ();
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InitMemoryMap - Allocate memory map buffer",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.2.2.1  AllocatePages must succeed with valid parameters when Type
    //          is AllocateAnyPages.
    //
    for (TypeIndex = 0; TypeIndex < ALLOCATEPAGES_MEMORYTYPE_NUM; TypeIndex++) {
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->AllocatePages (
                       AllocateAnyPages,
                       AllocatePagesMemoryType[TypeIndex],
                       1,
                       &Memory
                       );
      gtBS->RestoreTPL (OldTpl);
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        Memory = 0;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gMemoryAllocationServicesInterfaceTestAssertionGuid007: \
                     (Index == 1? \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid013: \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid014),
                     L"BS.AllocatePages - Type is AllocateAnyPages",
                     L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     (UINTN)AllocatePagesMemoryType[TypeIndex]
                     );
      if (!(Memory & EFI_PAGE_MASK)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gMemoryAllocationServicesInterfaceTestAssertionGuid008: \
                     (Index == 1? \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid015: \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid016),
                     L"BS.AllocatePages - AllocateAnyPages address page-aligned",
                     L"%a:%d:TPL - %d, MemType - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     TplArray[Index],
                     (UINTN)AllocatePagesMemoryType[TypeIndex]
                     );
      if (Memory != 0) {
        Status = gtBS->FreePages (
                         Memory,
                         1
                         );
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"BS.FreePages - 1 page",
                         L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         TplArray[Index],
                         (UINTN)AllocatePagesMemoryType[TypeIndex]
                         );
        }
      }
    }

    //
    // 4.2.2.2  AllocatePages must succeed with valid parameters when
    //          Type is AllocateMaxAddress.
    //
    for (TypeIndex = 0; TypeIndex < ALLOCATEPAGES_MEMORYTYPE_NUM; TypeIndex++) {
      Status = GetMaxFreeMemoryDescriptor (&Descriptor);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
      } else {
        PageNum = (UINTN)Descriptor.NumberOfPages;
        Memory = Descriptor.PhysicalStart +
                 SctLShiftU64 (Descriptor.NumberOfPages, EFI_PAGE_SHIFT);
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->AllocatePages (
                         AllocateMaxAddress,
                         AllocatePagesMemoryType[TypeIndex],
                         PageNum/3,
                         &Memory
                         );
        gtBS->RestoreTPL (OldTpl);
        if (!EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Memory = 0;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid009: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid017: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid018),
                       L"BS.AllocatePages - Type is AllocateMaxAddress",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (!(Memory & EFI_PAGE_MASK)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid010: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid019: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid020),
                       L"BS.AllocatePages - AllocateMaxAddress address page-aligned",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory <= Descriptor.PhysicalStart +
             SctLShiftU64 (Descriptor.NumberOfPages, EFI_PAGE_SHIFT) -
             SctLShiftU64 (PageNum/3, EFI_PAGE_SHIFT)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid011: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid021: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid022),
                       L"BS.AllocatePages - AllocateMaxAddress return Address",
                       L"%a:%d:TPL - %d, MemType - %d, PhysicalStart - 0x%LX, NumberOfPages - 0x%LX, Memory - 0x%LX",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex],
                       Descriptor.PhysicalStart,
                       Descriptor.NumberOfPages,
                       Memory
                       );
        Memory2 = Descriptor.PhysicalStart +
                 SctLShiftU64 (Descriptor.NumberOfPages, EFI_PAGE_SHIFT);
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->AllocatePages (
                         AllocateMaxAddress,
                         AllocatePagesMemoryType[TypeIndex],
                         PageNum/3,
                         &Memory2
                         );
        gtBS->RestoreTPL (OldTpl);
        if (!EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Memory2 = 0;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid012: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid023: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid024),
                       L"BS.AllocatePages - Type is AllocateMaxAddress 2",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (!(Memory2 & EFI_PAGE_MASK)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid013: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid025: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid026),
                       L"BS.AllocatePages - AllocateMaxAddress address 2 page-aligned",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if ( Memory2 <= Descriptor.PhysicalStart +
             SctLShiftU64 (Descriptor.NumberOfPages, EFI_PAGE_SHIFT) -
             SctLShiftU64 (PageNum/3, EFI_PAGE_SHIFT)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid014: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid027: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid028),
                       L"BS.AllocatePages - AllocateMaxAddress return Address2",
                       L"%a:%d:TPL - %d, MemType - %d, Memory2 - 0x%LX",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex],
                       Memory2
                       );
        if (Memory != 0) {
          Status = gtBS->FreePages (
                           Memory,
                           PageNum/3
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.FreePages - first PageNum/3",
                           L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index],
                           (UINTN)AllocatePagesMemoryType[TypeIndex]
                           );
          }
        }
        if (Memory2 != 0) {
          Status = gtBS->FreePages (
                           Memory2,
                           PageNum/3
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.FreePages - second PageNum/3",
                           L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index],
                           (UINTN)AllocatePagesMemoryType[TypeIndex]
                           );
          }
        }
      }
    }

    //
    // 4.2.2.3  AllocatePages must succeed with valid parameters at when
    //          Type is AllocateAddress.
    //
    for (TypeIndex = 0; TypeIndex < ALLOCATEPAGES_MEMORYTYPE_NUM; TypeIndex++) {
      Status = GetSecondMaxFreeMemoryDescriptor (&Descriptor);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
      } else {
        PageNum = (UINTN)Descriptor.NumberOfPages;
        Start   = Descriptor.PhysicalStart;

        //
        // Calculate New Start address and PageNum with 64k alignment to
        // cover the case that some memory types' alignment is more than
        // 4k. If the available memory is less than 192k, the memory
        // allocation call will be skipped.
        //
        if (PageNum < (3 * EFI_SIZE_TO_PAGES(0x10000))) {
          break;
        }
        Start   = (Start + 0xFFFF) & 0xFFFFFFFFFFFF0000;
        PageNum = PageNum - (2 * EFI_SIZE_TO_PAGES(0x10000));

        Memory  = Start;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->AllocatePages (
                         AllocateAddress,
                         AllocatePagesMemoryType[TypeIndex],
                         PageNum,
                         &Memory
                         );
        gtBS->RestoreTPL (OldTpl);
        if (!EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Memory = 0;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid015: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid029: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid030),
                       L"BS.AllocatePages - Type is AllocateAddress",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (!(Memory & EFI_PAGE_MASK)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid016: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid031: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid032),
                       L"BS.AllocatePages - AllocateAddress address page-aligned",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory == Start) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid017: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid033: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid034),
                       L"BS.AllocatePages - AllocateAddress return Address",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory != 0) {
          Status = gtBS->FreePages (
                           Memory,
                           PageNum
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.FreePages - PageNum",
                           L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index],
                           (UINTN)AllocatePagesMemoryType[TypeIndex]
                           );
          }
        }
      }
    }

    //
    // 4.2.2.4  AllocatePages must succeed when request different part memory
    //          in a memory descriptor.
    //
    for (TypeIndex = 0; TypeIndex < ALLOCATEPAGES_MEMORYTYPE_NUM; TypeIndex++) {
      //
      // Allocate font range
      //
      Status = GetMaxFreeMemoryDescriptor (&Descriptor);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
      } else {
        PageNum = (UINTN)Descriptor.NumberOfPages;
        Start   = Descriptor.PhysicalStart;

        //
        // Calculate New Start address and PageNum with 64k alignment to
        // cover the case that some memory types' alignment is more than
        // 4k. If the available memory is less than 192k, the memory
        // allocation call will be skipped.
        //
        if (PageNum < (3 * EFI_SIZE_TO_PAGES(0x10000))) {
          break;
        }
        Start   = (Start + 0xFFFF) & 0xFFFFFFFFFFFF0000;
        PageNum = PageNum - (2 * EFI_SIZE_TO_PAGES(0x10000));

        Memory  = Start;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->AllocatePages (
                         AllocateAddress,
                         AllocatePagesMemoryType[TypeIndex],
                         PageNum/3,
                         &Memory
                         );
        gtBS->RestoreTPL (OldTpl);
        if (!EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Memory = 0;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid018: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid035: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid036),
                       L"BS.AllocatePages - front range",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (!(Memory & EFI_PAGE_MASK)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid019: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid037: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid038),
                       L"BS.AllocatePages - front range address page-aligned",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory == Start) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid020: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid039: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid040),
                       L"BS.AllocatePages - front range return Address",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory != 0) {
          Status = gtBS->FreePages (
                           Memory,
                           PageNum/3
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.FreePages - PageNum/3",
                           L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index],
                           (UINTN)AllocatePagesMemoryType[TypeIndex]
                           );
          }
        }
      }
      //
      // Allocate middle range
      //
      Status = GetMaxFreeMemoryDescriptor (&Descriptor);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
      } else {
        PageNum = (UINTN)Descriptor.NumberOfPages;
        Start   = Descriptor.PhysicalStart;

        //
        // Calculate New Start address and PageNum with 64k alignment to
        // cover the case that some memory types' alignment is more than
        // 4k. If the available memory is less than 192k, the memory
        // allocation call will be skipped.
        //
        if (PageNum < (3 * EFI_SIZE_TO_PAGES(0x10000))) {
          break;
        }
        Start   = (Start + 0xFFFF) & 0xFFFFFFFFFFFF0000;
        PageNum = PageNum - (2 * EFI_SIZE_TO_PAGES(0x10000));

        Memory = Start + (SctLShiftU64 (PageNum/3, EFI_PAGE_SHIFT) & 0xFFFFFFFFFFFF0000);

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->AllocatePages (
                         AllocateAddress,
                         AllocatePagesMemoryType[TypeIndex],
                         PageNum/3,
                         &Memory
                         );
        gtBS->RestoreTPL (OldTpl);
        if (!EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Memory = 0;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid021: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid041: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid042),
                       L"BS.AllocatePages - middle range",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (!(Memory & EFI_PAGE_MASK)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid022: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid043: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid044),
                       L"BS.AllocatePages - middle range address page-aligned",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory == Start + (SctLShiftU64 (PageNum/3, EFI_PAGE_SHIFT) & 0xFFFFFFFFFFFF0000)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid023: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid045: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid046),
                       L"BS.AllocatePages - middle range return Address",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory != 0) {
          Status = gtBS->FreePages (
                           Memory,
                           PageNum/3
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.FreePages - PageNum/3",
                           L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index],
                           (UINTN)AllocatePagesMemoryType[TypeIndex]
                           );
          }
        }
      }
      //
      // Allocate back range
      //
      Status = GetMaxFreeMemoryDescriptor (&Descriptor);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
      } else {
        PageNum = (UINTN)Descriptor.NumberOfPages;
        Start   = Descriptor.PhysicalStart;

        //
        // Calculate New Start address and PageNum with 64k alignment to
        // cover the case that some memory types' alignment is more than
        // 4k. If the available memory is less than 192k, the memory
        // allocation call will be skipped.
        //
        if (PageNum < (3 * EFI_SIZE_TO_PAGES(0x10000))) {
          break;
        }
        Start   = (Start + 0xFFFF) & 0xFFFFFFFFFFFF0000;
        PageNum = PageNum - (2 * EFI_SIZE_TO_PAGES(0x10000));

        Memory  = Start + (SctLShiftU64 (PageNum * 2 / 3, EFI_PAGE_SHIFT) & 0xFFFFFFFFFFFF0000);

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->AllocatePages (
                         AllocateAddress,
                         AllocatePagesMemoryType[TypeIndex],
                         PageNum/3,
                         &Memory
                         );
        gtBS->RestoreTPL (OldTpl);
        if (!EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Memory = 0;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid024: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid047: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid048),
                       L"BS.AllocatePages - back range",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (!(Memory & EFI_PAGE_MASK)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid025: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid049: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid050),
                       L"BS.AllocatePages - back range address page-aligned",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory == Start + (SctLShiftU64 (PageNum * 2 / 3, EFI_PAGE_SHIFT) & 0xFFFFFFFFFFFF0000)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid026: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid051: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid052),
                       L"BS.AllocatePages - back range return Address",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory != 0) {
          Status = gtBS->FreePages (
                           Memory,
                           PageNum/3
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.FreePages - PageNum/3",
                           L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index],
                           (UINTN)AllocatePagesMemoryType[TypeIndex]
                           );
          }
        }
      }
    }

    //
    // 4.2.2.5  AllocatePages must succeed when request different size memory
    //          in a memory descriptor.
    //
    for (TypeIndex = 0; TypeIndex < ALLOCATEPAGES_MEMORYTYPE_NUM; TypeIndex++) {
      //
      // Allocate 1 page
      //
      Status = GetSecondMaxFreeMemoryDescriptor (&Descriptor);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
      } else {
        PageNum = (UINTN)Descriptor.NumberOfPages;
        Start   = Descriptor.PhysicalStart;

        //
        // Calculate New Start address and PageNum with 64k alignment to
        // cover the case that some memory types' alignment is more than
        // 4k. If the available memory is less than 192k, the memory
        // allocation call will be skipped.
        //
        if (PageNum < (3 * EFI_SIZE_TO_PAGES(0x10000))) {
          break;
        }
        Start   = (Start + 0xFFFF) & 0xFFFFFFFFFFFF0000;
        PageNum = PageNum - (2 * EFI_SIZE_TO_PAGES(0x10000));

        Memory  = Start;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->AllocatePages (
                         AllocateAddress,
                         AllocatePagesMemoryType[TypeIndex],
                         1,
                         &Memory
                         );
        gtBS->RestoreTPL (OldTpl);
        if (!EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Memory = 0;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid027: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid053: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid054),
                       L"BS.AllocatePages - 1 page",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (!(Memory & EFI_PAGE_MASK)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid028: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid055: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid056),
                       L"BS.AllocatePages - 1 page address page-aligned",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory == Start) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid029: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid057: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid058),
                       L"BS.AllocatePages - 1 page return Address",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory != 0) {
          Status = gtBS->FreePages (
                           Memory,
                           1
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.FreePages - 1",
                           L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index],
                           (UINTN)AllocatePagesMemoryType[TypeIndex]
                           );
          }
        }
      }
      //
      // Allocate PageNum-1 pages
      //
      Status = GetSecondMaxFreeMemoryDescriptor (&Descriptor);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
      } else {
        PageNum = (UINTN)Descriptor.NumberOfPages;
        Start   = Descriptor.PhysicalStart;

        //
        // Calculate New Start address and PageNum with 64k alignment to
        // cover the case that some memory types' alignment is more than
        // 4k. If the available memory is less than 192k, the memory
        // allocation call will be skipped.
        //
        if (PageNum < (3 * EFI_SIZE_TO_PAGES(0x10000))) {
          break;
        }
        Start   = (Start + 0xFFFF) & 0xFFFFFFFFFFFF0000;
        PageNum = PageNum - (2 * EFI_SIZE_TO_PAGES(0x10000));

        Memory  = Start;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        if (PageNum != 1) {
          Status = gtBS->AllocatePages (
                           AllocateAddress,
                           AllocatePagesMemoryType[TypeIndex],
                           PageNum - 1,
                           &Memory
                           );
        } else {
          Status = gtBS->AllocatePages (
                           AllocateAddress,
                           AllocatePagesMemoryType[TypeIndex],
                           PageNum,
                           &Memory
                           );
        }
        gtBS->RestoreTPL (OldTpl);
        if (!EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Memory = 0;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid030: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid059: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid060),
                       L"BS.AllocatePages - PageNum-1 pages",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (!(Memory & EFI_PAGE_MASK)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid031: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid061: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid062),
                       L"BS.AllocatePages - PageNum-1 pages address page-aligned",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory == Start) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid032: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid063: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid064),
                       L"BS.AllocatePages - PageNum-1 pages return Address",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory != 0) {
          if (PageNum != 1) {
            Status = gtBS->FreePages (
                             Memory,
                             PageNum - 1
                             );
          } else {
            Status = gtBS->FreePages (
                             Memory,
                             PageNum
                             );
          }
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.FreePages - PageNum-1",
                           L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index],
                           (UINTN)AllocatePagesMemoryType[TypeIndex]
                           );
          }
        }
      }
      //
      // Allocate PageNum pages
      //
      Status = GetSecondMaxFreeMemoryDescriptor (&Descriptor);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
      } else {
        PageNum = (UINTN)Descriptor.NumberOfPages;
        Start   = Descriptor.PhysicalStart;

        //
        // Calculate New Start address and PageNum with 64k alignment to
        // cover the case that some memory types' alignment is more than
        // 4k. If the available memory is less than 192k, the memory
        // allocation call will be skipped.
        //
        if (PageNum < (3 * EFI_SIZE_TO_PAGES(0x10000))) {
          break;
        }
        Start   = (Start + 0xFFFF) & 0xFFFFFFFFFFFF0000;
        PageNum = PageNum - (2 * EFI_SIZE_TO_PAGES(0x10000));

        Memory  = Start;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->AllocatePages (
                         AllocateAddress,
                         AllocatePagesMemoryType[TypeIndex],
                         PageNum,
                         &Memory
                         );
        gtBS->RestoreTPL (OldTpl);
        if (!EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Memory = 0;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid033: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid065: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid066),
                       L"BS.AllocatePages - PageNum pages",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (!(Memory & EFI_PAGE_MASK)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid034: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid067: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid068),
                       L"BS.AllocatePages - PageNum pages address page-aligned",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory == Start) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       Index==0? \
                       gMemoryAllocationServicesInterfaceTestAssertionGuid035: \
                       (Index == 1? \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid069: \
                        gMemoryAllocationServicesBBTestFunctionAssertionGuid070),
                       L"BS.AllocatePages - PageNum pages return Address",
                       L"%a:%d:TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        if (Memory != 0) {
          Status = gtBS->FreePages (
                           Memory,
                           PageNum
                           );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.FreePages - PageNum",
                           L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status,
                           TplArray[Index],
                           (UINTN)AllocatePagesMemoryType[TypeIndex]
                           );
          }
        }
      }
    }

  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->FreePages() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestFreePagesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_PHYSICAL_ADDRESS                 Memory;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  UINTN                                TypeIndex;
  EFI_TPL                              OldTpl;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = InitMemoryMap ();
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InitMemoryMap - Allocate memory map buffer",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.3.2.1  FreePages must succeed with valid parameters.
    //
    for (TypeIndex = 0; TypeIndex < ALLOCATEPAGES_MEMORYTYPE_NUM; TypeIndex++) {
      Status = gtBS->AllocatePages (
                       AllocateAnyPages,
                       AllocatePagesMemoryType[TypeIndex],
                       1,
                       &Memory
                       );

      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.AllocatePages - Type is AllocateAnyPages",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       (UINTN)AllocatePagesMemoryType[TypeIndex]
                       );
        continue;
      }
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->FreePages (
                       Memory,
                       1
                       );
      gtBS->RestoreTPL (OldTpl);
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gMemoryAllocationServicesInterfaceTestAssertionGuid036: \
                     (Index == 1? \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid071: \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid072),
                     L"BS.FreePages - 1 page",
                     L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     (UINTN)AllocatePagesMemoryType[TypeIndex]
                     );
    }

  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->AllocatePool () Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.4
//
EFI_STATUS
EFIAPI
BBTestAllocatePoolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  VOID                                 *Memory;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  UINTN                                TypeIndex;
  EFI_TPL                              OldTpl;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = InitMemoryMap ();
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InitMemoryMap - Allocate memory map buffer",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.4.2.1  AllocatePool must succeed with valid parameters.
    //
    for (TypeIndex = 0; TypeIndex < ALLOCATEPOOL_MEMORYTYPE_NUM; TypeIndex++) {
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->AllocatePool (
                       AllocatePoolMemoryType[TypeIndex],
                       1,
                       (VOID **)&Memory
                       );
      gtBS->RestoreTPL (OldTpl);
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        Memory = NULL;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gMemoryAllocationServicesInterfaceTestAssertionGuid037: \
                     (Index == 1? \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid073: \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid074),
                     L"BS.AllocatePool - 1 byte",
                     L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     AllocatePoolMemoryType[TypeIndex]
                     );
      if (Memory != NULL) {
        Status = gtBS->FreePool (
                         Memory
                         );
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"BS.FreePool - 1 byte",
                         L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         TplArray[Index],
                         AllocatePoolMemoryType[TypeIndex]
                         );
        }
      }
    }

  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->FreePool () Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.5
//
EFI_STATUS
EFIAPI
BBTestFreePoolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  VOID                                 *Memory;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  UINTN                                TypeIndex;
  EFI_TPL                              OldTpl;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = InitMemoryMap ();
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InitMemoryMap - Allocate memory map buffer",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.5.2.1  FreePool must succeed with valid parameters.
    //
    for (TypeIndex = 0; TypeIndex < ALLOCATEPOOL_MEMORYTYPE_NUM; TypeIndex++) {
      Status = gtBS->AllocatePool (
                       AllocatePoolMemoryType[TypeIndex],
                       1,
                       (VOID **)&Memory
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.AllocatePool - 1 byte",
                       L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       AllocatePoolMemoryType[TypeIndex]
                       );
        continue;
      }
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->FreePool (
                       Memory
                       );
      gtBS->RestoreTPL (OldTpl);
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gMemoryAllocationServicesInterfaceTestAssertionGuid038: \
                     (Index == 1? \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid075: \
                      gMemoryAllocationServicesBBTestFunctionAssertionGuid076),
                     L"BS.FreePool - 1 byte",
                     L"%a:%d:Status - %r, TPL - %d, MemType - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     AllocatePoolMemoryType[TypeIndex]
                     );
    }

  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}
