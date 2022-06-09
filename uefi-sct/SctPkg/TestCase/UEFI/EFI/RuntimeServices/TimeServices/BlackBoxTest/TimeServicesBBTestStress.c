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

  TimeServicesBBTestStress.c

Abstract:

  Combination Test Cases of Time Services

--*/

#include "SctLib.h"
#include "TimeServicesBBTestMain.h"

#define MAX_REPEAT_TIMES 100

/**
 *  Entrypoint for GetTime Stress Test.
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
BBTestGetTimeStressTest (
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
  EFI_TIME                             Time;
  EFI_TIME_CAPABILITIES                Capabilities;

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
    // 5.1.2.1  Stress test for GetTime
    //
    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtRT->GetTime (
                       &Time,
                       &Capabilities
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
                     gTimeServicesBBTestStressAssertionGuid001,
                     L"RT.GetTime - Valid parameters",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );
      if (TimeFieldsValid (&Time)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTimeServicesBBTestStressAssertionGuid002,
                     L"RT.GetTime - Verify returned time",
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
 *  Entrypoint for GetWakeupTime Stress Test.
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
BBTestGetWakeupTimeStressTest (
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
  EFI_TIME                             Time;
  BOOLEAN                              Enable;
  BOOLEAN                              Pending;

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
    // 5.2.2.1  Stress test for GetWakeupTime
    //
    for (RepeatTimes = 0; RepeatTimes < MAX_REPEAT_TIMES; RepeatTimes++) {
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtRT->GetWakeupTime (
                       &Enable,
                       &Pending,
                       &Time
                       );
      gtBS->RestoreTPL (OldTpl);
      if (Status == EFI_UNSUPPORTED) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_WARNING,
                       gTestGenericFailureGuid,
                       L"RT.GetWakeupTime - Unsupported",
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
                     gTimeServicesBBTestStressAssertionGuid003,
                     L"RT.GetWakeupTime - Valid parameters",
                     L"%a:%d:Status - %r, TPL - %d, Times - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     RepeatTimes
                     );
      if (Enable == TRUE) {
        if (TimeFieldsValid (&Time)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTimeServicesBBTestStressAssertionGuid004,
                       L"RT.GetWakeupTime - Verify returned time",
                       L"%a:%d:Status - %r, TPL - %d, Times - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index],
                       RepeatTimes
                       );
      }
    }
  }

  return EFI_SUCCESS;
}