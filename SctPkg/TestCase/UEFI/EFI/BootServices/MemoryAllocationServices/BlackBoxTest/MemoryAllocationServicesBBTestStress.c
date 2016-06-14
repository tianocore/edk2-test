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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
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