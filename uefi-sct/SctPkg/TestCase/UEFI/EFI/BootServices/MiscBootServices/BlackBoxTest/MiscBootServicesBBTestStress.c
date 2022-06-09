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

  MiscBootServicesBBTestStress.c

Abstract:

  Combination Test Cases of Miscellaneous Boot Services

--*/

#include "SctLib.h"
#include "MiscBootServicesBBTestMain.h"

#define MAX_REPEAT_TIMES 20

/**
 *  Entrypoint for SetWatchdogTimer Stress Test.
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
BBTestSetWatchdogTimerStressTest (
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
  UINT64                               RepeatTimes;
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 5.1.2.1  Stress test for SetWatchdogTimer.
    //
    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      //
      // enable watchdog timer
      //
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->SetWatchdogTimer (
                       5,
                       0x10000,
                       0,
                       NULL
                       );
      gtBS->RestoreTPL (OldTpl);
      if (Status == EFI_UNSUPPORTED) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_WARNING,
                       gTestGenericFailureGuid,
                       L"BS.SetWatchdogTimer - Unsupported",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return EFI_SUCCESS;
      }
      if (Status == EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMiscBootServicesCombinationTestAssertionGuid001,
                     L"BS.SetWatchdogTimer - enable watchdog timer",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );
      //
      // disable watchdog timer
      //
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->SetWatchdogTimer (
                       0,
                       0x10000,
                       0,
                       NULL
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
                     gMiscBootServicesCombinationTestAssertionGuid002,
                     L"BS.SetWatchdogTimer - disable watchdog timer",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );
    }
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Stall Stress Test.
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
BBTestStallStressTest (
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
  UINT64                               RepeatTimes;
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 5.2.2.1  Stress test for Stall.
    //

    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->Stall (
                       1000000
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
                     gMiscBootServicesCombinationTestAssertionGuid003,
                     L"BS.Stall - 1 seconds",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );

    }

  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for CopyMem Stress Test.
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
BBTestCopyMemStressTest (
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
  UINT64                               RepeatTimes;
  EFI_TPL                              OldTpl;
  UINT8                                *Buffer;
  EFI_PHYSICAL_ADDRESS                 BufferAddress;
  UINT8                                *Src;
  UINT8                                *Dest;

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

  //
  // Allocate buffer
  //
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   EfiBootServicesData,
                   1,
                   &BufferAddress
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePages - 1 page EfiBootServicesData",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  Buffer = (UINT8*)(UINTN)BufferAddress;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 5.3.2.1  Stress test for CopyMem.
    //
    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      Dest = Buffer + 50;
      SetTestMem (Dest, 50, (UINT8)(RepeatTimes + 1));
      Src = Buffer;
      SetTestMem (Src, 50, (UINT8)RepeatTimes);
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      gtBS->CopyMem (
              (VOID *)Dest,
              (VOID *)Src,
              50
              );
      gtBS->RestoreTPL (OldTpl);
      Status = CheckTestMem (Dest, 50, (UINT8)RepeatTimes);
      if (Status == EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMiscBootServicesCombinationTestAssertionGuid005,
                     L"BS.CopyMem",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );
    }
  }

  //
  // Free the buffer
  //

  Status = gtBS->FreePages (
                   BufferAddress,
                   1
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePages - 1 page",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for SetMem Stress Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.4
//
EFI_STATUS
EFIAPI
BBTestSetMemStressTest (
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
  UINT64                               RepeatTimes;
  EFI_TPL                              OldTpl;
  UINT8                                *Buffer;
  EFI_PHYSICAL_ADDRESS                 BufferAddress;
  UINT8                                *Dest;

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

  //
  // Allocate buffer
  //
  Status = gtBS->AllocatePages (
                   AllocateAnyPages,
                   EfiBootServicesData,
                   1,
                   &BufferAddress
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePages - 1 page EfiBootServicesData",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  Buffer = (UINT8*)(UINTN)BufferAddress;

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 5.4.2.1  Stress test for SetMem.
    //
    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      Dest = Buffer;
      SetTestMem (Dest, 50, (UINT8)(RepeatTimes + 1));
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      gtBS->SetMem (
              (VOID *)Dest,
              50,
              (UINT8)RepeatTimes
              );
      gtBS->RestoreTPL (OldTpl);
      Status = CheckTestMem (Dest, 50, (UINT8)RepeatTimes);
      if (Status == EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMiscBootServicesCombinationTestAssertionGuid006,
                     L"BS.SetMem",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );

    }
  }

  //
  // Free the buffer
  //

  Status = gtBS->FreePages (
                   BufferAddress,
                   1
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePages - 1 page",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for GetNextMonotonicCount Stress Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.5
//
EFI_STATUS
EFIAPI
BBTestGetNextMonotonicCountStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL   *RecoveryLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  UINT64                               RepeatTimes;
  EFI_TPL                              OldTpl;
  UINT64                               Count;
  UINT64                               OldCount;
  UINT8                                ResetBuffer[1024];
  RESET_DATA                           *ResetData;
  UINTN                                Size;

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

  //
  // Get the Recovery Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   (VOID **) &RecoveryLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle recovery library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Read reset record
  //
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &Size,
                          ResetBuffer
                          );
  ResetData = (RESET_DATA *)&ResetBuffer;
  if (EFI_ERROR(Status) || (Size < sizeof(RESET_DATA))) {
    //
    // Step 1
    //
  } else if (ResetData->Step == 1) {
    //
    // Step 2
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      OldCount = ResetData->Count;
      goto StressTestStep2;
    }
  } else {
    return EFI_LOAD_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 5.5.2.1  Stress test for GetNextMonotonicCount.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetNextMonotonicCount (
                     &OldCount
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
                   gMiscBootServicesCombinationTestAssertionGuid007,
                   L"BS.GetNextMonotonicCount - get current count",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->GetNextMonotonicCount (
                       &Count
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
                     gMiscBootServicesCombinationTestAssertionGuid008,
                     L"BS.GetNextMonotonicCount - get next count",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );
      if (Count == OldCount + 1) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMiscBootServicesCombinationTestAssertionGuid009,
                     L"BS.GetNextMonotonicCount - Count == OldCount + 1",
                     L"%a:%d:Status - %r, TPL - %d, Count - %lx, OldCount - %lx, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     Count,
                     OldCount,
                     RepeatTimes
                     );
      OldCount = Count;
    }

    //
    //  save the high 32 bit and reset system
    //
    ResetData->Step     = 1;
    ResetData->TplIndex = Index;
    ResetData->Count    = OldCount;
    Status = RecoveryLib->WriteResetRecord (
                            RecoveryLib,
                            sizeof (RESET_DATA),
                            ResetBuffer
                            );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"TestRecoveryLib - WriteResetRecord",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      return Status;
    }

    //
    // Print out some information to avoid the user thought it is an error
    //
    SctPrint (L"System will cold reset after 1 second...");
    gtBS->Stall (1000000);

    gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);

StressTestStep2:

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->GetNextMonotonicCount (
                     &Count
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
                   gMiscBootServicesCombinationTestAssertionGuid010,
                   L"BS.GetNextMonotonicCount - get count after reset",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    if (SctRShiftU64 (Count, 32) == SctRShiftU64 (OldCount, 32) + 1) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gMiscBootServicesCombinationTestAssertionGuid012,
                   L"BS.GetNextMonotonicCount - high 32 bit increase by 1",
                   L"%a:%d:OldCount - %lx, Count - %lx, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   OldCount,
                   Count,
                   TplArray[Index]
                   );

  }

  return EFI_SUCCESS;
}