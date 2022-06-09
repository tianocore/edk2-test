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

  MiscRuntimeServicesBBTestStress.c

Abstract:

  Combination Test Cases of Miscellaneous Runtime Services

--*/

#include "SctLib.h"
#include "MiscRuntimeServicesBBTestMain.h"

#define MAX_REPEAT_TIMES 2

/**
 *  Entrypoint for gtRT->ResetSystem() Stress Test.
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
BBTestResetSystemStressTest (
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
  UINT32                               RepeatTimes;
  EFI_TPL                              OldTpl;
  UINT8                                Buffer[1024];
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

  if ( EFI_ERROR(Status) ) {
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

  if ( EFI_ERROR(Status) ) {
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
                          Buffer
                          );
  ResetData = (RESET_DATA *)Buffer;
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
      RepeatTimes = ResetData->RepeatTimes;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto StressTestStep2;
    }
  } else if (ResetData->Step == 2) {
    //
    // Step 3
    //
    if (ResetData->TplIndex < TPL_ARRAY_SIZE) {
      Index = ResetData->TplIndex;
      RepeatTimes = ResetData->RepeatTimes;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto StressTestStep3;
    }
  } else {
    return EFI_LOAD_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 5.1.2.1  Stress test for ResetSystem
    //
    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      ResetData->Step = 1;
      ResetData->TplIndex = Index;
      ResetData->RepeatTimes = RepeatTimes;
      Status = RecoveryLib->WriteResetRecord(
                              RecoveryLib,
                              sizeof (RESET_DATA),
                              Buffer
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

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      gtRT->ResetSystem(
              EfiResetCold,
              EFI_SUCCESS,
              0,
              NULL
              );
      gtBS->RestoreTPL (OldTpl);
      AssertionType = EFI_TEST_ASSERTION_FAILED;

StressTestStep2:
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMiscRuntimeServicesCombinationTestAssertionGuid001,
                     L"RT.ResetSystem - Stress EfiResetCold",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );
    }

    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      ResetData->Step = 2;
      ResetData->TplIndex = Index;
      ResetData->RepeatTimes = RepeatTimes;
      Status = RecoveryLib->WriteResetRecord (
                              RecoveryLib,
                              sizeof (RESET_DATA),
                              Buffer
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
      SctPrint (L"System will warm reset after 1 second...");
      gtBS->Stall (1000000);

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      gtRT->ResetSystem (
              EfiResetWarm,
              EFI_SUCCESS,
              0,
              NULL
              );
      gtBS->RestoreTPL (OldTpl);
      AssertionType = EFI_TEST_ASSERTION_FAILED;

StressTestStep3:
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMiscRuntimeServicesCombinationTestAssertionGuid002,
                     L"RT.ResetSystem - Stress EfiResetWarm",
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
 *  Entrypoint for gtRT->ResetSystem() Manual Stress Test.
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
BBTestResetSystemManualStressTest (
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
  UINT32                               RepeatTimes;
  EFI_TPL                              OldTpl;
  UINT8                                Buffer[1024];
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

  if ( EFI_ERROR(Status) ) {
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

  if ( EFI_ERROR(Status) ) {
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
                          Buffer
                          );
  ResetData = (RESET_DATA *)Buffer;
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
      RepeatTimes = ResetData->RepeatTimes;
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      goto ManualStressTestStep2;
    }
  } else {
    return EFI_LOAD_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 5.2.2.1  Stress test for ResetSystem when ResetType is EfiResetShutdown
    //
    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      ResetData->Step = 1;
      ResetData->TplIndex = Index;
      ResetData->RepeatTimes = RepeatTimes;
      Status = RecoveryLib->WriteResetRecord(
                              RecoveryLib,
                              sizeof (RESET_DATA),
                              Buffer
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
      SctPrint (L"System may shut down (or cold reset) after 1 second...");
      SctPrint (L"Note: On some platforms, you may have to manually turn\
    		    on the System again after few seconds...");
      gtBS->Stall (1000000);

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      gtRT->ResetSystem (
              EfiResetShutdown,
              EFI_SUCCESS,
              0,
              NULL
              );
      gtBS->RestoreTPL (OldTpl);
      AssertionType = EFI_TEST_ASSERTION_FAILED;

ManualStressTestStep2:
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gMiscRuntimeServicesCombinationTestAssertionGuid007,
                     L"RT.ResetSystem - Stress EfiResetShutdown",
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
