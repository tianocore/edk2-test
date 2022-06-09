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

  MemoryAllocationServicesBBTestConformance.c

Abstract:

  Consistency Test Cases of Memory Allocation Boot Services

--*/

#include "SctLib.h"
#include "MemoryAllocationServicesBBTestMain.h"

/**
 *  Entrypoint for gtBS->GetMemoryMap() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1
//
EFI_STATUS
EFIAPI
BBTestGetMemoryMapConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  UINTN                                MemoryMapSize;
  UINTN                                MapKey;
  UINTN                                DescriptorSize;
  UINT32                               DescriptorVersion;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_STATUS                           Status2;
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

  //
  // 3.1.2.1 GetMemoryMap should not succeed when MemoryMapSize is NULL
  //

  MemoryMapSize = MemoryMapSizeNeeded;
  Status = gtBS->GetMemoryMap (
                   NULL, // &MemoryMapSize
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid001,
                 L"BS.GetMemoryMap - MemoryMapSize is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.1.2.2  GetMemoryMap should not succeed when MemoryMap is NULL
  //

  MemoryMapSize = MemoryMapSizeNeeded;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   NULL, // (EFI_MEMORY_DESCRIPTOR *)MemoryMap
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid002,
                 L"BS.GetMemoryMap - MemoryMap is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.1.2.3  GetMemoryMap should not succeed when MapKey is NULL
  //
  /*
  MemoryMapSize = MemoryMapSizeNeeded;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   NULL, // &MapKey
                   &DescriptorSize,
                   &DescriptorVersion
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid003,
                 L"BS.GetMemoryMap - MapKey is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );
  */

  //
  // 3.1.2.4  GetMemoryMap should not succeed when DescriptorSize is NULL
  //
  /*
  MemoryMapSize = MemoryMapSizeNeeded;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   &MapKey,
                   NULL, // &DescriptorSize
                   &DescriptorVersion
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid004,
                 L"BS.GetMemoryMap - DescriptorSize is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );
  */

  //
  // 3.1.2.5  GetMemoryMap should not succeed when DescriptorVersion is NULL
  //
  /*
  MemoryMapSize = MemoryMapSizeNeeded;
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   NULL // &DescriptorVersion
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid005,
                 L"BS.GetMemoryMap - DescriptorVersion is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );
  */

  //
  // 3.1.2.6  GetMemoryMap should not succeed when MemoryMapSize is too small
  //
  OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);

  Status        = EFI_SUCCESS;
  Status2       = EFI_SUCCESS;
  MemoryMapSize = 0;
  
  Status = gtBS->GetMemoryMap (
                   &MemoryMapSize,
                   (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                   &MapKey,
                   &DescriptorSize,
                   &DescriptorVersion
                   );

  if (Status == EFI_BUFFER_TOO_SMALL) {
    MemoryMapSize = MemoryMapSize - 1;

    Status2 = gtBS->GetMemoryMap (
                     &MemoryMapSize,
                     (EFI_MEMORY_DESCRIPTOR *)MemoryMap,
                     &MapKey,
                     &DescriptorSize,
                     &DescriptorVersion
                     );
  }
  gtBS->RestoreTPL (OldTpl);

  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid006,
                 L"BS.GetMemoryMap - MemoryMapSize is 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Status2 == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid007,
                 L"BS.GetMemoryMap - MemoryMapSize is MemoryMapSizeNeeded-1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 ); 

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->AllocatePages() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.2
//
EFI_STATUS
EFIAPI
BBTestAllocatePagesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_PHYSICAL_ADDRESS                 Memory;
  EFI_MEMORY_DESCRIPTOR                Descriptor;
  EFI_TEST_ASSERTION                   AssertionType;

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

  //
  // AllocatePages should not succeed with an NULL Memory
  //
  Status = gtBS->AllocatePages (
                   AllocateAnyPages, 
                   EfiBootServicesData,
                   1,
                   NULL
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesBBTestConformanceAssertionGuid006,
                 L"BS.AllocatePages - Memory is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.2.2.1  AllocatePages should not succeed with an invalid Type
  //
  Status = gtBS->AllocatePages (
                   MaxAllocateType, // invalid
                   EfiBootServicesData,
                   1,
                   &Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid008,
                 L"BS.AllocatePages - Type is MaxAllocateType",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = gtBS->AllocatePages (
                   MaxAllocateType + 1, // invalid
                   EfiBootServicesData,
                   1,
                   &Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid009,
                 L"BS.AllocatePages - Type is MaxAllocateType + 1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = gtBS->AllocatePages (
                   -1, // invalid
                   EfiBootServicesData,
                   1,
                   &Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid010,
                 L"BS.AllocatePages - Type is -1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.2.2.2  AllocatePages should not succeed with an invalid MemoryType
  //
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   EfiMaxMemoryType, // invalid
                   1,
                   &Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid016,
                 L"BS.AllocatePages - MemoryType is EfiMaxMemoryType",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   EfiMaxMemoryType + 1, // invalid
                   1,
                   &Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid017,
                 L"BS.AllocatePages - MemoryType is EfiMaxMemoryType + 1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   14, //EfiPersistentMemory., // invalid
                   1,
                   &Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesBBTestConformanceAssertionGuid008,
                 L"BS.AllocatePages - MemoryType is EfiPersistentMemory",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   0x6ffffffe, // invalid
                   1,
                   &Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesBBTestConformanceAssertionGuid001,
                 L"BS.AllocatePages - MemoryType is 0x6ffffffe",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   0x6fffffff, // invalid
                   1,
                   &Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesBBTestConformanceAssertionGuid002,
                 L"BS.AllocatePages - MemoryType is 0x6fffffff",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.2.2.3  AllocatePages should not succeed when out of resources
  //
  Status = GetMaxFreeMemoryDescriptor (&Descriptor);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Status = gtBS->AllocatePages (
                     AllocateAnyPages,
                     EfiBootServicesData,
                     (UINTN)Descriptor.NumberOfPages + 1,
                     &Memory
                     );
    if (Status == EFI_OUT_OF_RESOURCES) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gMemoryAllocationServicesConsistencyTestAssertionGuid020,
                   L"BS.AllocatePages - Not enough memory",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // 3.2.2.4  AllocatePages should not succeed when the requested pages
  //          could not be found
  //
  Status = GetMaxAddressMemoryDescriptor (&Descriptor);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.GetMemoryMap - GetMaxAddressMemoryDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Memory = Descriptor.PhysicalStart +
             SctLShiftU64 (Descriptor.NumberOfPages, EFI_PAGE_SHIFT);
    Status = gtBS->AllocatePages (
                     AllocateAddress,
                     EfiBootServicesData,
                     1,
                     &Memory // invalid
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gMemoryAllocationServicesConsistencyTestAssertionGuid021,
                   L"BS.AllocatePages - Not Existent Memory",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // 3.2.2.5  AllocatePages should not succeed when the requested pages
  //          have been allocated
  //
  Status = GetAllocatedMemoryDescriptor (&Descriptor);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.GetMemoryMap - GetAllocatedMemoryDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Memory = Descriptor.PhysicalStart;
    Status = gtBS->AllocatePages (
                     AllocateAddress,
                     EfiBootServicesData,
                     1,
                     &Memory // invalid
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gMemoryAllocationServicesBBTestConformanceAssertionGuid005,
                   L"BS.AllocatePages - Allocated Memory",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->FreePages() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.3
//
EFI_STATUS
EFIAPI
BBTestFreePagesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_MEMORY_DESCRIPTOR                Descriptor;
  EFI_PHYSICAL_ADDRESS                 Memory;
  EFI_TEST_ASSERTION                   AssertionType;

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

  //
  // 3.3.2.1  FreePages should not succeed when the requested memory pages
  //          were not allocated with AllocatePages
  //
  Status = GetMaxAddressMemoryDescriptor (&Descriptor);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.GetMemoryMap - GetMaxAddressMemoryDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Memory = Descriptor.PhysicalStart +
             SctLShiftU64 (Descriptor.NumberOfPages, EFI_PAGE_SHIFT);
    Status = gtBS->FreePages (
                     Memory, // invalid
                     1
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gMemoryAllocationServicesConsistencyTestAssertionGuid025,
                   L"BS.FreePages - Not Existent Memory",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  Status = GetMaxFreeMemoryDescriptor (&Descriptor);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Memory = Descriptor.PhysicalStart;
    Status = gtBS->FreePages (
                     Memory, // invalid
                     1
                     );
    if (Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gMemoryAllocationServicesConsistencyTestAssertionGuid026,
                   L"BS.FreePages - EfiConventionalMemory memory",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // 3.3.2.2  FreePages should not succeed when the Memory is not a
  //          page-aligned address
  //
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   EfiBootServicesData,
                   2,
                   &Memory
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePages - 2 pages EfiBootServicesData",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Memory = Memory + 1;
    Status = gtBS->FreePages (
                     Memory,      // invalid
                     1
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gMemoryAllocationServicesConsistencyTestAssertionGuid027,
                   L"BS.FreePages - Memory is not page-aligned",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->AllocatePool () Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.4
//
EFI_STATUS
EFIAPI
BBTestAllocatePoolConsistencyTest (
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
  UINTN                                Size;
  EFI_MEMORY_DESCRIPTOR                Descriptor;

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

  //
  // AllocatePool should not succeed with an NULL Buffer
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData, // invalid
                   1000,
                   (VOID **) NULL
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesBBTestConformanceAssertionGuid007,
                 L"BS.AllocatePool - Buffer is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // 3.4.2.1  AllocatePool should not succeed with an invalid PoolType
  //
  Status = gtBS->AllocatePool (
                   EfiMaxMemoryType, // invalid
                   1,
                   (VOID **)&Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid038,
                 L"BS.AllocatePool - Type is EfiMaxMemoryType",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = gtBS->AllocatePool (
                   EfiMaxMemoryType + 1, // invalid
                   1,
                   (VOID **)&Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid039,
                 L"BS.AllocatePool - Type is EfiMaxMemoryType + 1",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = gtBS->AllocatePool (
                   14, //EfiPersistentMemory, // invalid
                   1,
                   (VOID **)&Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesBBTestConformanceAssertionGuid009,
                 L"BS.AllocatePool - Type is EfiPersistentMemory",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = gtBS->AllocatePool (
                   0x6ffffffe, // invalid
                   1,
                   (VOID **)&Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesBBTestConformanceAssertionGuid003,
                 L"BS.AllocatePool - Type is 0x6ffffffe",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = gtBS->AllocatePool (
                   0x6fffffff, // invalid
                   1,
                   (VOID **)&Memory
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesBBTestConformanceAssertionGuid004,
                 L"BS.AllocatePool - Type is 0x6fffffff",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.4.2.2  AllocatePool should not succeed when out of resources
  //

  Status = GetMaxFreeMemoryDescriptor (&Descriptor);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.GetMemoryMap - GetMaxFreeMemoryDescriptor",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Size = (UINTN)-1;
    if (SctLShiftU64 (Descriptor.NumberOfPages, EFI_PAGE_SHIFT) + 1 < (UINT64)Size) {
      Status = gtBS->AllocatePool (
                       EfiBootServicesData,
                       (UINTN)SctLShiftU64 (Descriptor.NumberOfPages, EFI_PAGE_SHIFT) + 1,
                       (VOID **)&Memory
                       );
      if (Status == EFI_OUT_OF_RESOURCES) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMemoryAllocationServicesConsistencyTestAssertionGuid041,
                     L"BS.AllocatePool - Not enough memory",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtBS->FreePool () Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.5
//
EFI_STATUS
EFIAPI
BBTestFreePoolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  //VOID                                 *Memory;
  EFI_TEST_ASSERTION                   AssertionType;

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

  //
  // 3.5.2.1  FreePool should not succeed when the Buffer is NULL
  //
  Status = gtBS->FreePool (
                   NULL // invalid
                   );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMemoryAllocationServicesConsistencyTestAssertionGuid042,
                 L"BS.FreePool - Buffer is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  FreeMemoryMap ();
  return EFI_SUCCESS;
}