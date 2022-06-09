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

  TimeServicesBBTestConformance.c

Abstract:

  Consistency Test Cases of Time Services

--*/

#include "SctLib.h"
#include "TimeServicesBBTestMain.h"

/**
 *  Entrypoint for gtRT->GetTime() Consistency Test.
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
BBTestGetTimeConsistencyTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
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

  //
  // 3.1.2.1  GetTime should not succeed when Time is NULL
  //
  // BUG:2744
  Status = gtRT->GetTime (
                   NULL,
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
                 gTimeServicesBBTestConformanceAssertionGuid001,
                 L"RT.GetTime - Time is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtRT->SetTime() Consistency Test.
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
BBTestSetTimeConsistencyTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_TIME                             Time;
  EFI_TIME                             OldTime;

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
  // 3.2.2.1  SetTime should not succeed when a time field is out of range
  //
  Status = gtRT->GetTime (
                   &OldTime,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"RT.SetTime - GetTime",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Time = OldTime;
    Time.Year = 1899;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid002,
                   L"RT.SetTime - Time.Year is 1899",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Year = 10000;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid003,
                   L"RT.SetTime - Time.Year is 10000",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Year = (UINT16)-1;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid004,
                   L"RT.SetTime - Time.Year is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Month = 0;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid005,
                   L"RT.SetTime - Time.Month is 0",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Month = 13;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid006,
                   L"RT.SetTime - Time.Month is 13",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Month = (UINT8)-1;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid007,
                   L"RT.SetTime - Time.Month is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Day = 0;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid008,
                   L"RT.SetTime - Time.Day is 0",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Day = 32;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid009,
                   L"RT.SetTime - Time.Day is 32",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Day = (UINT8)-1;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid010,
                   L"RT.SetTime - Time.Day is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Month = 4;
    Time.Day = 31;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid011,
                   L"RT.SetTime - Time.Month is 4 and Time.Day is 31",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Hour = 24;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid012,
                   L"RT.SetTime - Time.Hour is 24",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Hour = (UINT8)-1;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid013,
                   L"RT.SetTime - Time.Hour is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Minute = 60;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid014,
                   L"RT.SetTime - Time.Minute is 60",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Minute = (UINT8)-1;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid015,
                   L"RT.SetTime - Time.Minute is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Second = 60;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid016,
                   L"RT.SetTime - Time.Second is 60",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Second = (UINT8)-1;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid017,
                   L"RT.SetTime - Time.Second is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Nanosecond = 1000000000;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid018,
                   L"RT.SetTime - Time.Nanosecond is 1000000000",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Nanosecond = (UINT32)-1;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid019,
                   L"RT.SetTime - Time.Nanosecond is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.TimeZone = -1441;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid020,
                   L"RT.SetTime - Time.TimeZone is -1441",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.TimeZone = 1441;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid021,
                   L"RT.SetTime - Time.TimeZone is 1441",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Year = 2001;
    Time.Month = 2;
    Time.Day = 29;
    Status = gtRT->SetTime (
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid022,
                   L"RT.SetTime - Time is 2001/2/29",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    // restore the time
    //
    Status = gtRT->SetTime (
                     &OldTime
                     );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtRT->GetWakeupTime() Consistency Test.
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
BBTestGetWakeupTimeConsistencyTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  BOOLEAN                              Enabled;
  BOOLEAN                              Pending;
  EFI_TIME                             Time;

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
  // 3.3.2.1  GetWakeupTime should not succeed when Enabled is NULL
  //
  // BUG:2745
  Status = gtRT->GetWakeupTime (
                   NULL,  // invalid
                   &Pending,
                   &Time
                   );
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
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTimeServicesBBTestConformanceAssertionGuid023,
                 L"RT.GetWakeupTime - Enabled is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.3.2.2  GetWakeupTime should not succeed when Pending is NULL
  //
  // BUG:2746
  Status = gtRT->GetWakeupTime (
                   &Enabled,
                   NULL,  // invalid
                   &Time
                   );
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
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTimeServicesBBTestConformanceAssertionGuid024,
                 L"RT.GetWakeupTime - Pending is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // 3.3.2.3  GetWakeupTime should not succeed when Time is NULL
  //
  // BUG:2747
  Status = gtRT->GetWakeupTime (
                   &Enabled,
                   &Pending,
                   NULL   // invalid
                   );
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
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTimeServicesBBTestConformanceAssertionGuid025,
                 L"RT.GetWakeupTime - Time is NULL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtRT->SetWakeupTime() Consistency Test.
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
BBTestSetWakeupTimeConsistencyTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_TIME                             Time;
  EFI_TIME                             OldTime;

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
  // 3.4.2.1  SetWakeTime should not succeed when a time field is out of range
  //
  Status = gtRT->GetTime (
                   &OldTime,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"RT.SetWakeupTime - GetTime",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    Time = OldTime;
    Time.Year = 1899;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_UNSUPPORTED) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"RT.SetWakeupTime - Unsupported",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return EFI_SUCCESS;
    }
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid026,
                   L"RT.SetWakeupTime - Time.Year is 1899",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Year = 10000;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid027,
                   L"RT.SetWakeupTime - Time.Year is 10000",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Year = (UINT16)-1;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid028,
                   L"RT.SetWakeupTime - Time.Year is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Month = 0;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid029,
                   L"RT.SetWakeupTime - Time.Month is 0",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Month = 13;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid030,
                   L"RT.SetWakeupTime - Time.Month is 13",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Month = (UINT8)-1;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid031,
                   L"RT.SetWakeupTime - Time.Month is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Day = 0;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid032,
                   L"RT.SetWakeupTime - Time.Day is 0",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Day = 32;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid033,
                   L"RT.SetWakeupTime - Time.Day is 32",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Day = (UINT8)-1;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid034,
                   L"RT.SetWakeupTime - Time.Day is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Month = 4;
    Time.Day = 31;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid035,
                   L"RT.SetWakeupTime - Time.Month is 4 and Time.Day is 31",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Hour = 24;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid036,
                   L"RT.SetWakeupTime - Time.Hour is 24",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Hour = (UINT8)-1;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid037,
                   L"RT.SetWakeupTime - Time.Hour is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Minute = 60;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid038,
                   L"RT.SetWakeupTime - Time.Minute is 60",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Minute = (UINT8)-1;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid039,
                   L"RT.SetWakeupTime - Time.Minute is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Second = 60;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid040,
                   L"RT.SetWakeupTime - Time.Second is 60",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Second = (UINT8)-1;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid041,
                   L"RT.SetWakeupTime - Time.Second is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Nanosecond = 1000000000;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid042,
                   L"RT.SetWakeupTime - Time.Nanosecond is 1000000000",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Nanosecond = (UINT32)-1;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid043,
                   L"RT.SetWakeupTime - Time.Nanosecond is -1",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.TimeZone = -1441;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid044,
                   L"RT.SetWakeupTime - Time.TimeZone is -1441",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.TimeZone = 1441;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid045,
                   L"RT.SetWakeupTime - Time.TimeZone is 1441",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Time = OldTime;
    Time.Year = 2001;
    Time.Month = 2;
    Time.Day = 29;
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &Time
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTimeServicesBBTestConformanceAssertionGuid046,
                   L"RT.SetWakeupTime - Time is 2001/2/29",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  }

  return EFI_SUCCESS;
}

