/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MemoryAllocationServicesBBTestStress.c

Abstract:

  Combination Test Cases of Memory Allocation Boot Services

--*/

#include "SctLib.h"
#include "MemoryAllocationServicesBBTestMain.h"

#define MAX_REPEAT_TIMES 100

#define SEQ_NUM 8

INTN FreeSeqIndex1[SEQ_NUM] = {
  1, 3, 5, 7, 2, 4, 6, 8
};

INTN FreeSeqIndex2[SEQ_NUM] = {
  8, 6, 4, 2, 7, 5, 3, 1
};

/**
 *  Entrypoint for GetMemoryMap Stress Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.1
//
EFI_STATUS
EFIAPI
BBTestGetMemoryMapStressTest (
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
  UINTN                                Index;
  UINTN                                RepeatTimes;
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
    // 5.1.2.1  Stress test for GetMemoryMap.
    //
    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      MemoryMapSize = MemoryMapSizeNeeded;
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
                     gMemoryAllocationServicesCombinationTestAssertionGuid001,
                     L"BS.GetMemoryMap - Valid parameters",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );
    }
  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for AllocatePages/FreePages Stress Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.2
//
EFI_STATUS
EFIAPI
BBTestPagesStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  UINTN                                RepeatTimes;
  EFI_TPL                              OldTpl;
  EFI_PHYSICAL_ADDRESS                 Memory;
  EFI_PHYSICAL_ADDRESS                 **pMemory;
  EFI_PHYSICAL_ADDRESS                 NextMemory;
  EFI_PHYSICAL_ADDRESS                 MemoryArray[SEQ_NUM];
  UINTN                                SeqIndex;

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
    // 5.2.2.1  Stress test for Allocatepages/FreePages.
    //
    RepeatTimes = 0;
    NextMemory = 0;
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    while (1) {
      Status = gtBS->AllocatePages (
                       AllocateAnyPages,
                       EfiBootServicesData,
                       1,
                       &Memory
                       );
      RepeatTimes++;
      if (EFI_ERROR(Status)) {
        break;
      }
      if (Memory == 0) {
        Status = EFI_OUT_OF_RESOURCES;
        gtBS->FreePages (
                Memory,
                1
                );
        break;
      }
      pMemory = (EFI_PHYSICAL_ADDRESS **)&Memory;
      **pMemory = NextMemory;
      NextMemory = Memory;
    };

    if (Status != EFI_OUT_OF_RESOURCES) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    RepeatTimes = 0;
    while (NextMemory != 0) {
      Memory = NextMemory;
      pMemory = (EFI_PHYSICAL_ADDRESS **)&Memory;
      NextMemory = **pMemory;
      Status = gtBS->FreePages (
                       Memory,
                       1
                       );
      RepeatTimes++;
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
    gtBS->RestoreTPL (OldTpl);
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gMemoryAllocationServicesCombinationTestAssertionGuid002,
                   L"BS.Allocatepages/FreePages - Stress Test",
                   L"%a:%d:TPL - %d, Times - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index],
                   RepeatTimes
                   );

    //
    // 5.2.2.2  AllocatePages and FreePages with different sequences.
    //
    for (SeqIndex = 0; SeqIndex < SEQ_NUM; SeqIndex++) {
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->AllocatePages (
                       AllocateAnyPages,
                       EfiBootServicesData,
                       1,
                       &(MemoryArray[SeqIndex])
                       );
      gtBS->RestoreTPL (OldTpl);
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        MemoryArray[SeqIndex] = 0;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMemoryAllocationServicesCombinationTestAssertionGuid004,
                     L"BS.AllocatePages - Integrated Allocate 1",
                     L"%a:%d:Status - %r, TPL - %d, SeqIndex - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     SeqIndex
                     );
    }
    for (SeqIndex = 0; SeqIndex < SEQ_NUM; SeqIndex++) {
      if (MemoryArray[FreeSeqIndex1[SeqIndex]-1] != 0) {
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->FreePages (
                         MemoryArray[FreeSeqIndex1[SeqIndex]-1],
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
                       gMemoryAllocationServicesCombinationTestAssertionGuid005,
                       L"BS.FreePages - Integrated Free 1",
                       L"%a:%d:Status - %r, TPL - %d, SeqIndex - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       SeqIndex
                       );
      }
    }

    for (SeqIndex = 0; SeqIndex < SEQ_NUM; SeqIndex++) {
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->AllocatePages (
                       AllocateAnyPages,
                       EfiBootServicesData,
                       1,
                       &(MemoryArray[SeqIndex])
                       );
      gtBS->RestoreTPL (OldTpl);
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        MemoryArray[SeqIndex] = 0;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMemoryAllocationServicesCombinationTestAssertionGuid006,
                     L"BS.AllocatePages - Integrated Allocate 2",
                     L"%a:%d:Status - %r, TPL - %d, SeqIndex - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     SeqIndex
                     );
    }
    for (SeqIndex = 0; SeqIndex < SEQ_NUM; SeqIndex++) {
      if (MemoryArray[FreeSeqIndex2[SeqIndex]-1] != 0) {
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = gtBS->FreePages (
                         MemoryArray[FreeSeqIndex2[SeqIndex]-1],
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
                       gMemoryAllocationServicesCombinationTestAssertionGuid007,
                       L"BS.FreePages - Integrated Free 2",
                       L"%a:%d:Status - %r, TPL - %d, SeqIndex - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       SeqIndex
                       );
      }
    }
  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Integrated Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.3
//
EFI_STATUS
EFIAPI
BBTestPoolStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  UINTN                                RepeatTimes;
  EFI_TPL                              OldTpl;
  VOID                                 *PoolMemory;
  VOID                                 **pPoolMemory;
  VOID                                 *NextPoolMemory;

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
    // 5.3.2.1  Stress test for AllocatePool/FreePool.
    //

    // BUG:1767, FIXED
    RepeatTimes = 0;
    NextPoolMemory = NULL;
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    while (1) {
      Status = gtBS->AllocatePool (
                       EfiBootServicesData,
                       sizeof(VOID *),
                       (VOID **)&PoolMemory
                       );
      RepeatTimes++;
      if (EFI_ERROR(Status)) {
        break;
      }
      pPoolMemory = (VOID**)PoolMemory;
      *pPoolMemory = NextPoolMemory;
      NextPoolMemory = PoolMemory;
    };

    if (Status != EFI_OUT_OF_RESOURCES) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    RepeatTimes = 0;
    while (NextPoolMemory != NULL) {
      PoolMemory = NextPoolMemory;
      pPoolMemory = (VOID **)PoolMemory;
      NextPoolMemory = *pPoolMemory;
      Status = gtBS->FreePool (
                       PoolMemory
                       );
      RepeatTimes++;
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
    gtBS->RestoreTPL (OldTpl);
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gMemoryAllocationServicesCombinationTestAssertionGuid003,
                   L"BS.AllocatePool/FreePool - Stress Test",
                   L"%a:%d:TPL - %d, Times - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index],
                   RepeatTimes
                   );
  }

  FreeMemoryMap ();
  return EFI_SUCCESS;
}