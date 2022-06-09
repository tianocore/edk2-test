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

  TimeServicesBBTestFunction.c

Abstract:

  Interface Test Cases of Time Services

--*/

#include "SctLib.h"
#include "TimeServicesBBTestMain.h"

/**
 *  Entrypoint for gtRT->GetTime() Interface Test.
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
BBTestGetTimeInterfaceTest (
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
    // 4.1.2.1  GetTime must succeed with valid parameters
    //
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
                   Index==0? \
                   gTimeServicesBBTestFunctionAssertionGuid001: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid002: \
                    gTimeServicesBBTestFunctionAssertionGuid003),
                   L"RT.GetTime - Valid parameters",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (TimeFieldsValid (&Time)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gTimeServicesBBTestFunctionAssertionGuid004: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid005: \
                    gTimeServicesBBTestFunctionAssertionGuid006),
                   L"RT.GetTime - Verify returned time",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // 4.1.2.2  GetTime must succeed with Capabilities set to NULL
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtRT->GetTime (
                     &Time,
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
                   Index==0? \
                   gTimeServicesBBTestFunctionAssertionGuid007: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid008: \
                    gTimeServicesBBTestFunctionAssertionGuid009),
                   L"RT.GetTime - Capabilities set to NULL",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (TimeFieldsValid (&Time)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gTimeServicesBBTestFunctionAssertionGuid010: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid011: \
                    gTimeServicesBBTestFunctionAssertionGuid012),
                   L"RT.GetTime - Verify returned time",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtRT->SetTime() Interface Test.
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
BBTestSetTimeInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{  
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib;
  EFI_STATUS                          Status;
  EFI_TEST_ASSERTION                  AssertionType;
  UINTN                               Index;
  EFI_TPL                             OldTpl;
  EFI_TIME                            OldTime;
  EFI_TIME                            NewTime;
  EFI_TIME                            Time;
  UINTN                               RecoveryDataSize;
  UINT8                               *RecoveryData;

  //
  // Get test support library interfaces
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &RecoveryLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Allocate memory for recovery data
  //
  Status = gtBS->AllocatePool (
                   EfiLoaderData,
                   1024,
                   (VOID **)&RecoveryData
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Read reset record
  //
  RecoveryDataSize = 1024;
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &RecoveryDataSize,
                          RecoveryData
                          );
  if (!EFI_ERROR(Status) && (RecoveryDataSize > 0)) {
    switch (RecoveryData[0]) {
    case 1:
      goto step1;
    case 2:
      goto step2;
    case 3:
      goto step3;
    case 4:
      goto step4;
    default:
      goto step5;
    }
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.2.2.1  SetTime must succeed with valid parameters
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
                     L"RT.GetTime - Get time",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      continue;
    }

    //
    // Change year
    // NOTES: The new year must be set as a leap year.
    //
    Time = OldTime;
    if (Time.Year != 2012) {
      Time.Year = 2012;
    } else {
      Time.Year = 2016;
    }
    // skip 2012 12  31 11:59:59 corner case  
    Time.Day = 1;
    
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtRT->SetTime (
                     &Time
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
                   gTimeServicesBBTestFunctionAssertionGuid013: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid014: \
                    gTimeServicesBBTestFunctionAssertionGuid015),
                   L"RT.SetTime - Change year",
                   L"%a:%d:Status - %r, TPL - %d, Year - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index],
                   OldTime.Year
                   );

	//
	// Write reset record 
	//
    RecoveryData[0] = 1;
	RecoveryData[1] = (UINT8)(Index);
	gtBS->CopyMem (&RecoveryData[2], &OldTime, sizeof(EFI_TIME));
    RecoveryLib->WriteResetRecord (RecoveryLib, sizeof(EFI_TIME)+2, RecoveryData);
	gtBS->FreePool (RecoveryData);
    //
    // Prompt the user about the cold reset and reset the system
    //
    if (LoggingLib != NULL) {
      LoggingLib->EnterFunction (
                    LoggingLib,
                    L"\r\nSetTime Test",
                    L"System will cold reset after 1 second..."
                    );
    }
    gtBS->Stall (1000000);
    gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);

step1:
    //
    // Restore the env
    //
    RecoveryData[0] = 0;
    Index = RecoveryData[1];
    gtBS->CopyMem (&OldTime, &RecoveryData[2], sizeof(EFI_TIME));

	//
	// Call GetTime() to check the result of SetTime()
	//
    Status = gtRT->GetTime (
                     &NewTime,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"RT.GetTime - Get new time 1",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    } else {
      if (((OldTime.Year == 2012) && (NewTime.Year == 2016)) ||
          ((OldTime.Year != 2012) && (NewTime.Year == 2012))) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gTimeServicesBBTestFunctionAssertionGuid016: \
                     (Index == 1? \
                      gTimeServicesBBTestFunctionAssertionGuid017: \
                      gTimeServicesBBTestFunctionAssertionGuid018),
                     L"RT.SetTime - Verify year after change",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }

    //
    // Change month
    //
    Time = OldTime;
    if (Time.Month != 1) {
      Time.Month = 1;
    } else {
      Time.Month = 12;
    }
    
    // skip 2012 12  31 11:59:59 corner case  
    Time.Day = 1;
    
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtRT->SetTime (
                     &Time
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
                   gTimeServicesBBTestFunctionAssertionGuid019: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid020: \
                    gTimeServicesBBTestFunctionAssertionGuid021),
                   L"RT.SetTime - Change month",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

	//
	// Write reset record 
	//
    RecoveryData[0] = 2;
	RecoveryData[1] = (UINT8)Index;
	gtBS->CopyMem (&RecoveryData[2], &OldTime, sizeof(EFI_TIME));
    RecoveryLib->WriteResetRecord (RecoveryLib, sizeof(EFI_TIME)+2, RecoveryData);
    gtBS->FreePool (RecoveryData);
    //
    // Prompt the user about the cold reset and reset the system
    //
    if (LoggingLib != NULL) {
      LoggingLib->EnterFunction (
                    LoggingLib,
                    L"\r\nSetTime Test",
                    L"System will cold reset after 1 second..."
                    );
    }
    gtBS->Stall (1000000);
    gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);


step2:
    //
    // Restore the env
    //
    RecoveryData[0] = 0;
	Index = RecoveryData[1];
    gtBS->CopyMem (&OldTime, &RecoveryData[2], sizeof(EFI_TIME));

	//
	// Call GetTime() to check the result of SetTime()
	//	
    Status = gtRT->GetTime (
                     &NewTime,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"RT.GetTime - Get new time 2",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    } else {
      if (((OldTime.Month == 1) && (NewTime.Month == 12)) ||
          ((OldTime.Month != 1) && (NewTime.Month == 1))) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gTimeServicesBBTestFunctionAssertionGuid022: \
                     (Index == 1? \
                      gTimeServicesBBTestFunctionAssertionGuid023: \
                      gTimeServicesBBTestFunctionAssertionGuid024),
                     L"RT.SetTime - Verify month after change",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }

    //
    // Change daylight
    //
    Time = OldTime;
    if (Time.Daylight & EFI_TIME_ADJUST_DAYLIGHT) {
      Time.Daylight &= ~EFI_TIME_ADJUST_DAYLIGHT;
    } else {
      Time.Daylight |= EFI_TIME_ADJUST_DAYLIGHT;
    }
    // reverse EFI_TIME_IN_DAYLIGHT bit
    Time.Daylight ^= EFI_TIME_IN_DAYLIGHT;
   
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtRT->SetTime (
                     &Time
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
                   gTimeServicesBBTestFunctionAssertionGuid025: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid026: \
                    gTimeServicesBBTestFunctionAssertionGuid027),
                   L"RT.SetTime - Change daylight",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
	
	//
	// Write reset record 
	//
    RecoveryData[0] = 3;
	RecoveryData[1] = (UINT8)Index;
	gtBS->CopyMem (&RecoveryData[2], &OldTime, sizeof(EFI_TIME));
    RecoveryLib->WriteResetRecord (RecoveryLib, sizeof(EFI_TIME)+2, RecoveryData);
    gtBS->FreePool (RecoveryData);
    //
    // Prompt the user about the cold reset and reset the system
    //
    if (LoggingLib != NULL) {
      LoggingLib->EnterFunction (
                    LoggingLib,
                    L"\r\nSetTime Test",
                    L"System will cold reset after 1 second..."
                    );
    }
    gtBS->Stall (1000000);
    gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);

step3:
    //
    // Restore the env
    //
    RecoveryData[0] = 0;
	Index = RecoveryData[1];
    gtBS->CopyMem (&OldTime, &RecoveryData[2], sizeof(EFI_TIME));

	//
	// Call GetTime() to check the result of SetTime()
	//
    Status = gtRT->GetTime (
                     &NewTime,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"RT.GetTime - Get new time 3",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    } else {
      if ((OldTime.Daylight ^ NewTime.Daylight) == (EFI_TIME_ADJUST_DAYLIGHT | EFI_TIME_IN_DAYLIGHT)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gTimeServicesBBTestFunctionAssertionGuid028: \
                     (Index == 1? \
                      gTimeServicesBBTestFunctionAssertionGuid029: \
                      gTimeServicesBBTestFunctionAssertionGuid030),
                     L"RT.SetTime - Verify daylight after change",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }

    //
    // Change time zone
    //
    Time = OldTime;
    if (Time.TimeZone != 0) {
      Time.TimeZone = 0;
    } else {
      Time.TimeZone = 1;
    }
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtRT->SetTime (
                     &Time
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
                   gTimeServicesBBTestFunctionAssertionGuid031: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid032: \
                    gTimeServicesBBTestFunctionAssertionGuid033),
                   L"RT.SetTime - Change time zone",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

	//
	// Write reset record 
	//
    RecoveryData[0] = 4;
	RecoveryData[1] = (UINT8)Index;
	gtBS->CopyMem (&RecoveryData[2], &OldTime, sizeof(EFI_TIME));
    RecoveryLib->WriteResetRecord (RecoveryLib, sizeof(EFI_TIME)+2, RecoveryData);
    gtBS->FreePool (RecoveryData);
    //
    // Prompt the user about the cold reset and reset the system
    //
    if (LoggingLib != NULL) {
      LoggingLib->EnterFunction (
                    LoggingLib,
                    L"\r\nSetTime Test",
                    L"System will cold reset after 1 second..."
                    );
    }
//	SctPrint (L"System will cold reset after 1 second...");
    gtBS->Stall (1000000);
    gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);

step4:
    //
    // Restore the env
    //
    RecoveryData[0] = 0;
	Index = RecoveryData[1];
    gtBS->CopyMem (&OldTime, &RecoveryData[2], sizeof(EFI_TIME));

	//
	// Call GetTime() to check the result of SetTime()
	//
    Status = gtRT->GetTime (
                     &NewTime,
                     NULL
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"RT.GetTime - Get new time 4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    } else {
      if (((OldTime.TimeZone == 0) && (NewTime.TimeZone == 1)) ||
          ((OldTime.TimeZone != 0) && (NewTime.TimeZone == 0))) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gTimeServicesBBTestFunctionAssertionGuid034: \
                     (Index == 1? \
                      gTimeServicesBBTestFunctionAssertionGuid035: \
                      gTimeServicesBBTestFunctionAssertionGuid036),
                     L"RT.SetTime - Verify time zone after change",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }

    //
    // Restore the time
    //
    Status = gtRT->SetTime (
                     &OldTime
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"RT.SetTime - Restore time",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }
  }

step5:
  gtBS->FreePool (RecoveryData);

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtRT->GetWakeupTime() Interface Test.
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
BBTestGetWakeupTimeInterfaceTest (
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
  EFI_TPL                              OldTpl;
  BOOLEAN                              Enable;
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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.3.2.1  GetWakeupTime must succeed with valid parameters
    //
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
    } else if (Status == EFI_DEVICE_ERROR) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gTimeServicesBBTestFunctionAssertionGuid037: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid038: \
                    gTimeServicesBBTestFunctionAssertionGuid039),
                   L"RT.GetWakeupTime - Valid parameters",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
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
                     Index==0? \
                     gTimeServicesBBTestFunctionAssertionGuid040: \
                     (Index == 1? \
                      gTimeServicesBBTestFunctionAssertionGuid041: \
                      gTimeServicesBBTestFunctionAssertionGuid042),
                     L"RT.GetWakeupTime - Verify returned time",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for gtRT->SetWakeupTime() Interface Test.
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
BBTestSetWakeupTimeInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL   *RecoveryLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Index;
  EFI_TPL                              OldTpl;
  EFI_TIME                             OldTime;
  EFI_TIME                             NewTime;
  BOOLEAN                              Enable;
  BOOLEAN                              Pending;
  UINTN                                RecoveryDataSize;
  UINT8                                *RecoveryData;

  //
  // Get test support library interfaces
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &RecoveryLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Allocate memory for recovery data
  //
  Status = gtBS->AllocatePool (
                   EfiLoaderData,
                   1024,
                   (VOID **)&RecoveryData
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Read reset record
  //
  RecoveryDataSize = 1024;
  Status = RecoveryLib->ReadResetRecord (
                          RecoveryLib,
                          &RecoveryDataSize,
                          RecoveryData
                          );
  if (!EFI_ERROR(Status) && (RecoveryDataSize > 0)) {
    switch (RecoveryData[0]) {
    case 1:
      goto step1;
    case 2:
      goto step2;
    default:
      goto step3;
    }
  }
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // 4.4.2.1  SetWakeupTime must succeed when set the system wakeup alarm clock
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
                     L"RT.GetTime - Get time",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      continue;
    }

    //
    // Change hour
    //
    AddOneHour (&OldTime);
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtRT->SetWakeupTime (
                     TRUE,
                     &OldTime
                     );
    gtBS->RestoreTPL (OldTpl);
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
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gTimeServicesBBTestFunctionAssertionGuid043: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid044: \
                    gTimeServicesBBTestFunctionAssertionGuid045),
                   L"RT.SetWakeupTime - Set wakeup time",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
	//
	// Write reset record 
	//
    RecoveryData[0] = 1;
	RecoveryData[1] = (UINT8)(Index);
	gtBS->CopyMem (&RecoveryData[2], &OldTime, sizeof(EFI_TIME));
    RecoveryLib->WriteResetRecord (RecoveryLib, sizeof(EFI_TIME)+2, RecoveryData);
	gtBS->FreePool (RecoveryData);
    //
    // Prompt the user about the cold reset and reset the system
    //
    if (LoggingLib != NULL) {
      LoggingLib->EnterFunction (
                    LoggingLib,
                    L"\r\nSetTime Test",
                    L"System will cold reset after 1 second..."
                    );
    }
    gtBS->Stall (1000000);
    gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);

step1:

    //
    // Restore the env
    //
    RecoveryData[0] = 0;
    Index = RecoveryData[1];
    gtBS->CopyMem (&OldTime, &RecoveryData[2], sizeof(EFI_TIME));
	
    Status = gtRT->GetWakeupTime (
                     &Enable,
                     &Pending,
                     &NewTime
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"RT.GetTime - Get wakeup time 1",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    } else {
      if (Enable == TRUE) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gTimeServicesBBTestFunctionAssertionGuid046: \
                     (Index == 1? \
                      gTimeServicesBBTestFunctionAssertionGuid047: \
                      gTimeServicesBBTestFunctionAssertionGuid048),
                     L"RT.SetWakeupTime - Wakeup timer should be enabled",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (Pending == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gTimeServicesBBTestFunctionAssertionGuid049: \
                     (Index == 1? \
                      gTimeServicesBBTestFunctionAssertionGuid050: \
                      gTimeServicesBBTestFunctionAssertionGuid051),
                     L"RT.SetWakeupTime - Timer should not be pending",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if ((OldTime.Year != NewTime.Year) || (OldTime.Month != NewTime.Month) || (OldTime.Day != NewTime.Day) || 
  	    (OldTime.Hour != NewTime.Hour) || (OldTime.Minute != NewTime.Minute) || (OldTime.Second != NewTime.Second) ||
  	    (OldTime.TimeZone != NewTime.TimeZone) || (OldTime.Daylight != NewTime.Daylight)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gTimeServicesBBTestFunctionAssertionGuid052: \
                     (Index == 1? \
                      gTimeServicesBBTestFunctionAssertionGuid053: \
                      gTimeServicesBBTestFunctionAssertionGuid054),
                     L"RT.SetWakeupTime - Verify wakeup time after change",
                     L"%a:%d:Status - %r, TPL - %d, YMD-%d,%d,%d,%d,%d,%d, HMS-%d,%d,%d,%d,%d,%d, NDT-%d,%d,%d,%d,%d,%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index],
                     OldTime.Year, NewTime.Year,
                     OldTime.Month, NewTime.Month,
                     OldTime.Day, NewTime.Day,
                     OldTime.Hour, NewTime.Hour,
                     OldTime.Minute, NewTime.Minute,
                     OldTime.Second, NewTime.Second,
                     OldTime.Nanosecond, NewTime.Nanosecond,
                     OldTime.Daylight, NewTime.Daylight,
                     OldTime.TimeZone, NewTime.TimeZone
                     );
    }

    //
    // 4.4.2.2  SetWakeupTime must succeed when disable the wakeup alarm clock
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtRT->SetWakeupTime (
                     FALSE,
                     NULL
                     );
    gtBS->RestoreTPL (OldTpl);
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
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   Index==0? \
                   gTimeServicesBBTestFunctionAssertionGuid055: \
                   (Index == 1? \
                    gTimeServicesBBTestFunctionAssertionGuid056: \
                    gTimeServicesBBTestFunctionAssertionGuid057),
                   L"RT.SetWakeupTime - Disable wakeup time",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
	
	//
	// Write reset record 
	//
    RecoveryData[0] = 2;
	RecoveryData[1] = (UINT8)(Index);
    RecoveryLib->WriteResetRecord (RecoveryLib, 2, RecoveryData);
	gtBS->FreePool (RecoveryData);
    //
    // Prompt the user about the cold reset and reset the system
    //
    if (LoggingLib != NULL) {
      LoggingLib->EnterFunction (
                    LoggingLib,
                    L"\r\nSetTime Test",
                    L"System will cold reset after 1 second..."
                    );
    }
    gtBS->Stall (1000000);
    gtRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
	
step2:
	
    //
    // Restore the env
    //
    RecoveryData[0] = 0;
    Index = RecoveryData[1];
	
    Status = gtRT->GetWakeupTime (
                     &Enable,
                     &Pending,
                     &NewTime
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"RT.GetTime - Get wakeup time 2",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    } else {
      if (Enable == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     Index==0? \
                     gTimeServicesBBTestFunctionAssertionGuid058: \
                     (Index == 1? \
                      gTimeServicesBBTestFunctionAssertionGuid059: \
                      gTimeServicesBBTestFunctionAssertionGuid060),
                     L"RT.SetWakeupTime - Wakeup timer should be disabled",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
    }
  }

step3:
  gtBS->FreePool (RecoveryData);

  return EFI_SUCCESS;
}

