/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2022, ARM Limited. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  SimpleTextOutBBTestFunction_efi.c

Abstract:

  Function Test Cases of Simple Text Output Protocol

--*/


#include "SimpleTextOutBBTestMain_efi.h"


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset() Manually Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.1
//
EFI_STATUS
EFIAPI
BBTestResetFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  INT32                                Attribute;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  INT32                                DefaultAttribute;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.1.2.1
  // Reset without Extended Verification
  //

  SctPrint (L"\n\rVGA Reset without extended verification start...\n\r");
  WaitTimeOrKey (5);
  //
  // Prepare expected Mode after call Reset.
  //
  BackupMode (SimpleOut, &ModeExpected);
  ModeExpected.Mode = 0;
  ModeExpected.CursorColumn = 0;
  ModeExpected.CursorRow = 0;

  //
  // Call Reset() with ExtendedVerification as FALSE
  //
  Status = SimpleOut->Reset (SimpleOut, FALSE);
  DefaultAttribute = SimpleOut->Mode->Attribute;
  ModeExpected.Attribute = ((UINT32)SimpleOut->Mode->Attribute) & 0x0f;

  //
  // Test Mode integrity.
  //
//  if (CheckModeIntegrity(&ModeExpected, SimpleOut->Mode)==FALSE) {
   if (SimpleOut->Mode->CursorColumn != 0 || SimpleOut->Mode->CursorRow != 0 || SimpleOut->Mode->Attribute != ModeExpected.Attribute) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid001,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE, mode position integrity",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid002,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Call SetAttribute() to change the background color
  //
  Attribute = EFI_TEXT_ATTR(EFI_WHITE, EFI_BLUE);
  Status = SimpleOut->SetAttribute (SimpleOut, Attribute);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with some attribute",
                   L"%a:%d: Status = %r, Attribute=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Attribute
                   );
  }

  //
  // Call Reset with ExtendVerification as FALSE again
  //

  SctPrint (L"\n\rVGA Reset with BLUE background without extended verification start ...\n\r");
  WaitTimeOrKey (5);
  //
  // Prepare expected Mode after call Reset.
  //
  BackupMode (SimpleOut, &ModeExpected);
  ModeExpected.Mode = 0;
  ModeExpected.CursorColumn = 0;
  ModeExpected.CursorRow = 0;

  //
  // Call Reset() with ExtendedVerification as FALSE
  //
  Status = SimpleOut->Reset (SimpleOut, FALSE);
  ModeExpected.Attribute = ((UINT32)SimpleOut->Mode->Attribute) & 0x0f;

  //
  // Test Mode integrity.
  //
//  if (CheckModeIntegrity(&ModeExpected, SimpleOut->Mode)==FALSE) {
  if (SimpleOut->Mode->CursorColumn != 0 || SimpleOut->Mode->CursorRow != 0 || SimpleOut->Mode->Attribute != ModeExpected.Attribute) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid004,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE, mode position integrity",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid005,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE",
                 L"%a:%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // User's view to judge whether the behavior is correct
  //
  if (AutoJudge (5, TRUE, L"\n\rVGA Reset with Default background correct?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid006,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE, user's view",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  RestoreMode (SimpleOut, &ModeOrg, StandardLib);

  //
  // Assertion Points 4.1.1.2.2
  // Reset with Extended Verification
  //

  SctPrint (L"\n\rVGA Reset with extended verification start...\n\r");
  WaitTimeOrKey (5);
  //
  // Prepare expected Mode after call Reset.
  //
  BackupMode (SimpleOut, &ModeExpected);
  ModeExpected.Mode = 0;
  ModeExpected.CursorColumn = 0;
  ModeExpected.CursorRow = 0;

  //
  // Call Reset() with ExtendedVerification as TRUE
  //
  Status = SimpleOut->Reset (SimpleOut, TRUE);
  ModeExpected.Attribute = ((UINT32)SimpleOut->Mode->Attribute) & 0x0f;
  DefaultAttribute = SimpleOut->Mode->Attribute;

  //
  // Test Mode integrity.
  //
//  if (CheckModeIntegrity(&ModeExpected, SimpleOut->Mode)==FALSE) {
  if (SimpleOut->Mode->CursorColumn != 0 || SimpleOut->Mode->CursorRow != 0 || SimpleOut->Mode->Attribute != ModeExpected.Attribute) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid007,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as TRUE, mode position integrity",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid008,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as TRUE",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Call SetAttribute() to change the background color
  //
  Attribute = EFI_TEXT_ATTR(EFI_WHITE, EFI_BLUE);
  Status = SimpleOut->SetAttribute (SimpleOut, Attribute);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with some attribute",
                   L"%a:%d: Status = %r, Attribute=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Attribute
                   );
  }

  //
  // Call Reset with ExtendVerification as TRUE again
  //

  SctPrint (L"\n\rVGA Reset with BLUE background with extended verification start ...\n\r");
  WaitTimeOrKey (5);
  //
  // Prepare expected Mode after call Reset.
  //
  BackupMode (SimpleOut, &ModeExpected);
  ModeExpected.Mode = 0;
  ModeExpected.CursorColumn = 0;
  ModeExpected.CursorRow = 0;

  //
  // Call Reset() with ExtendedVerification as TRUE
  //
  Status = SimpleOut->Reset (SimpleOut, TRUE);
  ModeExpected.Attribute = ((UINT32)SimpleOut->Mode->Attribute) & 0x0f;

  //
  // Test Mode integrity.
  //
//  if (CheckModeIntegrity(&ModeExpected, SimpleOut->Mode)==FALSE) {
  if (SimpleOut->Mode->CursorColumn != 0 || SimpleOut->Mode->CursorRow != 0 || SimpleOut->Mode->Attribute != ModeExpected.Attribute) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid010,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as TRUE, mode position integrity",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid011,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as TRUE",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // User's view to judge whether the behavior is correct
  //
  if (AutoJudge (5, TRUE, L"\n\rVGA Reset with default background correct?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid012,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as TRUE, user's view",
                 L"%a:%d: user feedback",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);

}



/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset() auto Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.2
//
EFI_STATUS
EFIAPI
BBTestResetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  INT32                                Attribute;
  UINTN                                Mode;

  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }

  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // For each mode supported!
  //
  for (Mode = 0; Mode < (UINTN)SimpleOut->Mode->MaxMode; Mode++) {
    //
    // Change mode
    //
    Status = SimpleOut->SetMode (SimpleOut, Mode);
    if (EFI_ERROR(Status)) {
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode",
                     L"%a:%d, Status = %r, Mode = %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Mode
                     );
      continue;
    }

    //
    // Assertion Points 4.1.2.2.1
    // Reset without Extended Verification
    //

    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);
    ModeExpected.Mode = 0;
    ModeExpected.CursorColumn = 0;
    ModeExpected.CursorRow = 0;

    //
    // Call Reset() with ExtendedVerification as FALSE
    //
    Status = SimpleOut->Reset (SimpleOut, FALSE);
    ModeExpected.Attribute = ((UINT32)SimpleOut->Mode->Attribute) & 0x0f;

    //
    // Test Mode integrity.
    //
//    if (CheckModeIntegrity(&ModeExpected, SimpleOut->Mode)==FALSE) {
    if (SimpleOut->Mode->CursorColumn != 0 || SimpleOut->Mode->CursorRow != 0 || SimpleOut->Mode->Attribute != ModeExpected.Attribute) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid014,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE, mode position integrity, Backgroud color is black",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L"Expected:Cursor Position(%d x %d), MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Status check should be after all other integrity
    //
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid015,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE, check return code",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    //
    // Call SetAttribute() to change the background color
    //
    Attribute = EFI_TEXT_ATTR(EFI_WHITE, EFI_BLUE);
    Status = SimpleOut->SetAttribute (SimpleOut, Attribute);

    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with some attribute",
                     L"%a:%d: Status = %r, Attribute=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Attribute
                     );
    }

    //
    // Call Reset with ExtendVerification as FALSE again
    //

    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);
    ModeExpected.Mode = 0;
    ModeExpected.CursorColumn = 0;
    ModeExpected.CursorRow = 0;

    //
    // Call Reset () with ExtendedVerification as FALSE
    //
    Status = SimpleOut->Reset (SimpleOut, FALSE);
    ModeExpected.Attribute = ((UINT32)SimpleOut->Mode->Attribute) & 0x0f;

    //
    // Test Mode integrity.
    //
//    if (CheckModeIntegrity(&ModeExpected, SimpleOut->Mode)==FALSE) {
    if (SimpleOut->Mode->CursorColumn != 0 || SimpleOut->Mode->CursorRow != 0 || SimpleOut->Mode->Attribute != ModeExpected.Attribute) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid017,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE, mode position integrity, background color is black",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L"Expected:Cursor Position(%d x %d), MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Status check should be after all other integrity
    //
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid018,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE, check return code",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    RestoreMode (SimpleOut, &ModeOrg, StandardLib);

    //
    // Assertion Points 4.1.2.2.2
    // Reset with Extended Verification
    //

    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);
    ModeExpected.Mode = 0;
    ModeExpected.CursorColumn = 0;
    ModeExpected.CursorRow = 0;

    //
    // Call Reset() with ExtendedVerification as TRUE
    //
    Status = SimpleOut->Reset (SimpleOut, TRUE);
    ModeExpected.Attribute = ((UINT32)SimpleOut->Mode->Attribute) & 0x0f;

    //
    // Test Mode integrity.
    //
//    if (CheckModeIntegrity(&ModeExpected, SimpleOut->Mode)==FALSE) {
    if (SimpleOut->Mode->CursorColumn != 0 || SimpleOut->Mode->CursorRow != 0 || SimpleOut->Mode->Attribute != ModeExpected.Attribute) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid019,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as TRUE, mode position integrity, background color is black",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L" Expected:Cursor Position(%d x %d), MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Status check should be after all other integrity
    //
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid020,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as TRUE, check return code",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    //
    // Call SetAttribute() to change the background color
    //
    Attribute = EFI_TEXT_ATTR(EFI_WHITE, EFI_BLUE);
    Status = SimpleOut->SetAttribute (SimpleOut, Attribute);

    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with some attribute",
                     L"%a:%d: Status = %r, Attribute=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Attribute
                     );
    }

    //
    // Call Reset with ExtendVerification as TRUE again
    //

    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);
    ModeExpected.Mode = 0;
    ModeExpected.CursorColumn = 0;
    ModeExpected.CursorRow = 0;

    //
    // Call Reset() with ExtendedVerification as TRUE
    //
    Status = SimpleOut->Reset (SimpleOut, TRUE);
    ModeExpected.Attribute = ((UINT32)SimpleOut->Mode->Attribute) & 0x0f;

    //
    // Test Mode integrity.
    //
//    if (CheckModeIntegrity(&ModeExpected, SimpleOut->Mode)==FALSE) {
    if (SimpleOut->Mode->CursorColumn != 0 || SimpleOut->Mode->CursorRow != 0 || SimpleOut->Mode->Attribute != ModeExpected.Attribute) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid022,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as TRUE, mode position integrity, background color is black",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L"Expected:Cursor Position(%d x %d), MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Status check should be after all other integrity
    //
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid023,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.Reset - Reset with ExtendedVerification as FALSE, check return code",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}



/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString() Manually Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.3
//
EFI_STATUS
EFIAPI
BBTestOutputStringFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Column, Row;
  UINTN                                DestColumn, DestRow;
  UINTN                                DestPosition;
  UINT16                               Index;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  UINT16 CntlStr[]             = { 'a', 'b', CHAR_TAB, 'c', 'd', CHAR_BACKSPACE,  'e', 'f', 'g', 'h', CHAR_LINEFEED,  'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', CHAR_CARRIAGE_RETURN, CHAR_NULL};

  CHAR16 DrawingStr[]          = { 0x2500, 0x2502, 0x250c, 0x2510, 0x2514, 0x2518, 0x251c, 0x2524, 0x252c, 0x2534, 0x253c, 0x2550,
                                   0x2551, 0x2552, 0x2553, 0x2554, 0x2555, 0x2556, 0x2557, 0x2558, 0x2559, 0x255a, 0x255b, 0x255c,
                                   0x255d, 0x255e, 0x255f, 0x2560, 0x2561, 0x2562, 0x2563, 0x2564, 0x2565, 0x2566, 0x2567, 0x2568,
                                   0x2569, 0x256a, 0x256b, 0x256c, 0x2588, 0x2591, 0x25b2, 0x25ba, 0x25bc, 0x25c4, 0x2191, 0x2193, 0};


  CHAR16 UnicodeStr[]          = { 'a', 'b', 'c', 'd', 0 };
  CHAR16 *LongStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.3.2.1
  // Output String with Normal Unicode strings
  //

  SctPrint (L"\n\rOutputString with normal Unicode strings starts\n\r");

  //
  // clear screen for test
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Get current mode, and it's boundary of screen for test the destine cursor position
  //
  Status = SimpleOut->QueryMode (SimpleOut, (UINTN)ModeOrg.Mode, &Column, &Row);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() on current mode",
                   L"%a:%d: Status = %r, Mode = %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ModeOrg.Mode
                   );

    return Status;
  }

  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call OutputString with String as some Unicode string
  // That is composed of characters within current language set.
  //

  Status = SimpleOut->OutputString (SimpleOut, UnicodeStr);

  //
  //calculate the destine cursor position
  //
  DestPosition = sizeof (UnicodeStr) / sizeof (CHAR16) - 1;
  if (DestPosition > Column * Row) {
    DestRow = Row - 1;
    DestColumn = DestPosition % Column;
  } else {
    DestRow = DestPosition / Column;
    DestColumn = DestPosition % Column;
  }
  ModeExpected.CursorRow = (INT32)DestRow;
  ModeExpected.CursorColumn = (INT32)DestColumn;


  //
  // Test Mode integrity.
  //
  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid026,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with normal Unicode string, check cursor position",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid027,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString() with normal Unicode string, check return code",
                 L"%a:%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  RestoreMode (SimpleOut, &ModeOrg, StandardLib);

  BackupMode (SimpleOut, &ModeOrg);

  //
  // Compliment Assertion Points for TDS 4.1.3.2.1
  // Output String with very long Unicode strings
  //

  SctPrint (L"\n\rOutputString with very long Unicode strings starts\n\r");


  //
  // clear screen for test
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Get current mode, and it's boundary of screen for test the destine cursor position
  //
  Status = SimpleOut->QueryMode (SimpleOut, (UINTN)ModeOrg.Mode, &Column, &Row);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() on current mode",
                   L"%a:%d: Status = %r, Mode = %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ModeOrg.Mode
                   );

    return Status;
  }

  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call OutputString with String as some Unicode string
  // That is composed of characters within current language set.
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   (Column * Row + 2) * sizeof (CHAR16),
                   (VOID **)&LongStr
                   );
  for (Index = 0; Index < Column * Row + 1; Index++){
    LongStr[Index]=L'a';
  }
  LongStr[Column * Row + 1]=0;

  Status = SimpleOut->OutputString (SimpleOut, LongStr);

  //
  //calculate the destine cursor position
  //
  DestPosition = Column * Row + 1;
  if (DestPosition > Column * Row) {
    DestRow = Row - 1;
    DestColumn = DestPosition % Column;
  } else {
    DestRow = DestPosition / Column;
    DestColumn = DestPosition % Column;
  }
  ModeExpected.CursorRow = (INT32)DestRow;
  ModeExpected.CursorColumn = (INT32)DestColumn;
  gtBS->FreePool (LongStr);
  //
  // Test Mode integrity.
  //
  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid120,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with very long Unicode string, mode integrity, check cursor position",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid121,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString() with very long Unicode string",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  RestoreMode (SimpleOut, &ModeOrg, StandardLib);

  //
  // Assertion Point 4.1.3.2.2
  // OutputString() with Drawing Chars
  //

  SctPrint (L"\n\rOutputString with Drawing Unicode strings starts\n\r");

  //
  // clear screen for test
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call OutputString with String as some  Drawing Unicode string
  // That is composed of characters within current language set.
  //

  Status = SimpleOut->OutputString (SimpleOut, DrawingStr);

  //
  //calculate the destine cursor position
  //
  DestPosition = sizeof(DrawingStr) / sizeof(CHAR16) - 1;
  if (DestPosition > Column * Row) {
    DestRow = Row - 1;
    DestColumn = DestPosition % Column;
  } else {
    DestRow = DestPosition / Column;
    DestColumn = DestPosition % Column;
  }

  ModeExpected.CursorRow = (INT32)DestRow;
  ModeExpected.CursorColumn = (INT32)DestColumn;


  //
  // Test Mode integrity.
  //
  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid030,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with  Drawing Unicode string, mode integrity, check cursor position",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid031,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString() with  Drawing Unicode string",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  RestoreMode (SimpleOut, &ModeOrg, StandardLib);


  //
  // Assertion Point 4.1.3.2.3
  // OutputString() with Cursor Control Chars
  //

  SctPrint (L"\n\rOutputString with CursorControl Unicode strings starts\n\r");


  //
  // clear screen for test
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call OutputString with String as some CursorControl Unicode string
  // That is composed of characters within current language set.
  //

  Status = SimpleOut->OutputString (SimpleOut, CntlStr);

  //
  //calculate the destine cursor position
  //
  DestColumn = DestRow = 0;
  DestPosition = sizeof (CntlStr) / sizeof (UINT16) - 1;
  for (Index = 0; Index < DestPosition; Index++){
    switch (CntlStr[Index]) {
      case CHAR_BACKSPACE:
        DestColumn = ((DestColumn - 1)>=0)? (DestColumn - 1):DestColumn;
        break;
      case  CHAR_CARRIAGE_RETURN:
        DestColumn = 0;
        break;
      case  CHAR_LINEFEED:
        DestRow = DestRow>=Row - 1 ? DestRow:DestRow + 1;
        break;
      default:
        DestColumn ++ ;
        if (DestColumn>=Column) {
          DestColumn = 0;
          DestRow = DestRow>=Row - 1 ? DestRow:DestRow + 1;
        }
        break;
    }
  }

  ModeExpected.CursorRow = (INT32)DestRow;
  ModeExpected.CursorColumn = (INT32)DestColumn;


  //
  // Test Mode integrity.
  //
  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid034,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with  CursorControl Unicode string, mode integrity, check cursor position",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid035,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString() with  CursorControl Unicode string",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);


}
EFI_STATUS
EFIAPI
BBTestOutputStringFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Column, Row, DestColumn, DestRow;
  UINTN                                DestPosition;
  UINT16                               Index;
  UINTN                                WaitIndex;
  EFI_INPUT_KEY                        Key;
  CHAR16                               KeyInput[2];

  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  UINT16 CntlStr[]             = { 'a', 'b', CHAR_TAB, 'c', 'd', CHAR_BACKSPACE,  'e', 'f', 'g', 'h', CHAR_LINEFEED,  'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', CHAR_CARRIAGE_RETURN, CHAR_NULL};

  CHAR16 DrawingStr[]          = { 0x2500, 0x2502, 0x250c, 0x2510, 0x2514, 0x2518, 0x251c, 0x2524, 0x252c, 0x2534, 0x253c, 0x2550,
                                   0x2551, 0x2552, 0x2553, 0x2554, 0x2555, 0x2556, 0x2557, 0x2558, 0x2559, 0x255a, 0x255b, 0x255c,
                                   0x255d, 0x255e, 0x255f, 0x2560, 0x2561, 0x2562, 0x2563, 0x2564, 0x2565, 0x2566, 0x2567, 0x2568,
                                   0x2569, 0x256a, 0x256b, 0x256c, 0x2588, 0x2591, 0x25b2, 0x25ba, 0x25bc, 0x25c4, 0x2191, 0x2193, 0};


  CHAR16 UnicodeStr[]          = { 'a', 'b', 'c', 'd', 0 };
  CHAR16 *LongStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.3.2.1
  // Output String with Normal Unicode strings
  //

  SctPrint (L"\n\rOutputString with normal Unicode strings starts\n\r");
  WaitTimeOrKey (5);

  //
  // clear screen for test
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Get current mode, and it's boundary of screen for test the destine cursor position
  //
  Status = SimpleOut->QueryMode (SimpleOut, (UINTN)ModeOrg.Mode, &Column, &Row);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() on current mode",
                   L"%a:%d: Status = %r, Mode = %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ModeOrg.Mode
                   );

    return Status;
  }

  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call OutputString with String as some Unicode string
  // That is composed of characters within current language set.
  //

  Status = SimpleOut->OutputString (SimpleOut, UnicodeStr);

  //
  //calculate the destine cursor position
  //
  DestPosition = sizeof (UnicodeStr) / sizeof (CHAR16) - 1;
  if (DestPosition > Column * Row) {
    DestRow = Row - 1;
    DestColumn = DestPosition % Column;
  } else {
    DestRow = DestPosition / Column;
    DestColumn = DestPosition % Column;
  }
  ModeExpected.CursorRow = (INT32)DestRow;
  ModeExpected.CursorColumn = (INT32)DestColumn;


  //
  // Test Mode integrity.
  //
  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid026,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with normal Unicode string, check cursor position",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid027,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString() with normal Unicode string, check return code",
                 L"%a:%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // User's view to judge whether the behavior is correct
  //
  if (AutoJudge (5, TRUE, L"\n\rOutputString normal Unicode string correctly?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid028,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with normal Unicode String, user's view",
                 L"%a:%d: TRUE - Pass, FALSE - Failure",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  RestoreMode (SimpleOut, &ModeOrg, StandardLib);

  BackupMode (SimpleOut, &ModeOrg);

  //
  // Compliment Assertion Points for TDS 4.1.3.2.1
  // Output String with very long Unicode strings
  //

  SctPrint (L"\n\rOutputString with very long Unicode strings starts\n\r");
  WaitTimeOrKey (5);

  //
  // clear screen for test
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Get current mode, and it's boundary of screen for test the destine cursor position
  //
  Status = SimpleOut->QueryMode (SimpleOut, (UINTN)ModeOrg.Mode, &Column, &Row);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode () on current mode",
                   L"%a:%d: Status = %r, Mode = %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ModeOrg.Mode
                   );

    return Status;
  }

  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call OutputString with String as some Unicode string
  // That is composed of characters within current language set.
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   (Column * Row + 2) * sizeof (CHAR16),
                   (VOID **)&LongStr
                   );
  for (Index = 0; Index < Column * Row + 1; Index++){
    LongStr[Index]=L'a';
  }
  LongStr[Column * Row + 1]=0;

  Status = SimpleOut->OutputString (SimpleOut, LongStr);

  //
  //calculate the destine cursor position
  //
  DestPosition = Column * Row + 1;
  if (DestPosition > Column * Row) {
    DestRow = Row - 1;
    DestColumn = DestPosition % Column;
  } else {
    DestRow = DestPosition / Column;
    DestColumn = DestPosition % Column;
  }
  ModeExpected.CursorRow = (INT32)DestRow;
  ModeExpected.CursorColumn = (INT32)DestColumn;
  gtBS->FreePool (LongStr);
  //
  // Test Mode integrity.
  //
  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid120,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with very long Unicode string, mode integrity, check cursor position",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid121,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString() with very long Unicode string",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // User's view to judge whether the behavior is correct
  //
  if (AutoJudge (5, TRUE, L"\n\rOutputString very long string correctly?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid122,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with very long Unicode String, user's view",
                 L"%a:%d: TRUE - Pass, FALSE - Failure",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  RestoreMode (SimpleOut, &ModeOrg, StandardLib);

  //
  // Assertion Point 4.1.3.2.2
  // OutputString() with Drawing Chars
  //

  SctPrint (L"\n\rOutputString with Drawing Unicode strings starts\n\r");
  WaitTimeOrKey (5);

  //
  // clear screen for test
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call OutputString with String as some  Drawing Unicode string
  // That is composed of characters within current language set.
  //

  Status = SimpleOut->OutputString (SimpleOut, DrawingStr);

  //
  //calculate the destine cursor position
  //
  DestPosition = sizeof (DrawingStr) / sizeof (CHAR16) - 1;
  if (DestPosition > Column * Row) {
    DestRow = Row - 1;
    DestColumn = DestPosition % Column;
  } else {
    DestRow = DestPosition / Column;
    DestColumn = DestPosition % Column;
  }

  ModeExpected.CursorRow = (INT32)DestRow;
  ModeExpected.CursorColumn = (INT32)DestColumn;


  //
  // Test Mode integrity.
  //
  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid030,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with  Drawing Unicode string, mode integrity, check cursor position",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid031,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString() with  Drawing Unicode string",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // User's view to judge whether the behavior is correct
  //
  if (AutoJudge (5, TRUE, L"\n\rOutputString Drawing Unicode string correctly?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid032,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with Drawing Unicode String, user's view",
                 L"%a:%d: TRUE - Pass, FALSE - Failure",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  RestoreMode (SimpleOut, &ModeOrg, StandardLib);


  //
  // Assertion Point 4.1.3.2.3
  // OutputString() with Cursor Control Chars
  //

  SctPrint (L"\n\rOutputString with CursorControl Unicode strings starts\n\r");
  WaitTimeOrKey (5);

  //
  // clear screen for test
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call OutputString with String as some CursorControl Unicode string
  // That is composed of characters within current language set.
  //

  Status = SimpleOut->OutputString (SimpleOut, CntlStr);

  //
  //calculate the destine cursor position
  //
  DestColumn = DestRow = 0;
  DestPosition = sizeof (CntlStr) / sizeof (UINT16) - 1;
  for (Index = 0; Index < DestPosition; Index++){
    switch (CntlStr[Index]) {
      case CHAR_BACKSPACE:
        DestColumn = ((DestColumn - 1)>=0)? (DestColumn - 1):DestColumn;
        break;
      case  CHAR_CARRIAGE_RETURN:
        DestColumn = 0;
        break;
      case  CHAR_LINEFEED:
        DestRow = DestRow>=Row - 1 ? DestRow:DestRow + 1;
        break;
      default:
        DestColumn ++ ;
        if (DestColumn>=Column) {
          DestColumn = 0;
          DestRow = DestRow>=Row - 1 ? DestRow:DestRow + 1;
        }
        break;
    }
  }

  ModeExpected.CursorRow = (INT32)DestRow;
  ModeExpected.CursorColumn = (INT32)DestColumn;


  //
  // Test Mode integrity.
  //
  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid034,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with  CursorControl Unicode string, mode integrity, check cursor position",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid035,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString() with  CursorControl Unicode string",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // User's view to judge whether the behavior is correct
  //
  if (AutoJudge (5, TRUE, L"\n\rOutputString CursorControl Unicode string correctly?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid036,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with CursorControl Unicode String, user's view",
                 L"%a:%d: TRUE - Pass, FALSE - Failure",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  RestoreMode (SimpleOut, &ModeOrg, StandardLib);

  //
  // Assertion Point 4.1.3.2.4
  // OutputString() with Mixed chars
  //

  SctPrint (L"\n\rOutputString with input Unicode strings starts\n\r");
  SctPrint (L"\n\rInput character and echo on screen. press \"Esc\" key to exit this test\n\r");
  WaitTimeOrKey (5);

  //
  // clear screen for test
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  while (1) {
    Status = gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.WaitForEvent - WaitForEvent",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto RestoreEnvironment;
    }

    Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"ST.ReadKeyStroke - ReadKeyStroke",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto RestoreEnvironment;
    }
    if (Key.ScanCode == SCAN_ESC) {
      break;
    }
    KeyInput[0]=Key.UnicodeChar;
    KeyInput[1]=0;

    //
    //echo input key
    //
    Status = SimpleOut->OutputString (SimpleOut, KeyInput);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid038,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString -- OutputString() with Mix chars",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    if (Key.UnicodeChar == CHAR_BACKSPACE) {
      //
      //clear current char at cursor
      //
      Status = SimpleOut->OutputString (SimpleOut, L" ");
      Status |= SimpleOut->OutputString (SimpleOut, KeyInput);
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextOutputFunctionTestAssertionGuid039,
                       L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString -- OutputString() with Mix chars - BackSpace",
                       L"%a:%d: Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
      }
    }
  }

  //
  // User's view to judge whether the behavior is correct
  //
  if (AutoJudge (5, TRUE, L"\n\rOutputString Mix char's behavior correct?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid040,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.OutputString - OutputString with Mixed Unicode String, user's view",
                 L"%a:%d: TRUE - Pass, FALSE - Failure",
                 __FILE__,
                 (UINTN)__LINE__
                 );


RestoreEnvironment:
  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);

}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.TestString() Automaticly Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.4
//
EFI_STATUS
EFIAPI
BBTestTestStringFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  CHAR16                               NormalStr[]={
                                         //CHAR_BACKSPACE,CHAR_LINEFEED,CHAR_CARRIAGE_RETURN, CHAR_NULL,
                                         /*
                                         0x2500, 0x2502, 0x250c, 0x2510, 0x2514, 0x2518, 0x251c, 0x2524, 0x252c, 0x2534, 0x253c, 0x2550,
                                         0x2551, 0x2552, 0x2553, 0x2554, 0x2555, 0x2556, 0x2557, 0x2558, 0x2559, 0x255a, 0x255b, 0x255c,
                                         0x255d, 0x255e, 0x255f, 0x2560, 0x2561, 0x2562, 0x2563, 0x2564, 0x2565, 0x2566, 0x2567, 0x2568,
                                         0x2569, 0x256a, 0x256b, 0x256c, 0x2588, 0x2591, 0x25b2, 0x25ba, 0x25bc, 0x25c4, 0x2191, 0x2193,*/
                                         'a', 'b', 'c', 0};


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

   //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter / StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
      //return EFI_SUCCESS;
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
      //return EFI_SUCCESS;
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.4.2.1
  // TestString on valid normal string
  //

  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call TestString with String as some normal Unicode string
  // That is composed of characters within current language set.
  //
  Status = SimpleOut->TestString (SimpleOut, NormalStr);

  //
  // Test Mode integrity.
  //
  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid041,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.TestString - TestString with normal Unicode string, mode integrity",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Status check should be after all other integrity
  //
  if (Status!=EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid042,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.TestString - TestString() with normal Unicode string",
                 L"%a:%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  RestoreMode (SimpleOut, &ModeOrg, StandardLib);

  //
  // Assertion Point 4.1.4.2.2
  // TestString() with Unsupported chars
  //

  //
  // Prepare Mode expected
  //
  BackupMode (SimpleOut, &ModeExpected);

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode() Automatically Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.5
//
EFI_STATUS
EFIAPI
BBTestQueryModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Column, Row;
  UINTN                                Index;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    SctPrint (L"Current testing console device:\r\n");
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      SctPrint (DevicePathStr);
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.5.2.1
  // QueryMode()
  //


  //
  // For all available mode , perform test
  //
  for (Index = 0; Index < (UINTN)SimpleOut->Mode->MaxMode; Index++) {
    //
    // Clear Screen
    //
    SimpleOut->ClearScreen (SimpleOut);

    //
    // Prepare Mode expected
    //
    BackupMode (SimpleOut, &ModeExpected);


    Status = SimpleOut->QueryMode (SimpleOut, Index, &Column, &Row);
    //
    // Mode integrity check
    //

    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid045,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode, mode should not be changed",
                   L"%a:%d: Mode=%d, Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid123,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode, mode 1 can be unsupported",
                     L"%a:%d: Status = %r, Mode=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      continue;
    }
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid046,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode",
                   L"%a:%d: Status = %r, Mode=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );


    if (Index==0) {
      //
      // for Mode 0; dimensions must be 80*25
      //
      if (Column!=80 || Row!= 25) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextOutputFunctionTestAssertionGuid047,
                       L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode, check mode 0",
                       L"%a:%d, Status = %r, Mode=%d, Dimension=(%d x %d), expected dimension=(80 x 25)",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index,
                       Column,
                       Row
                       );
      }
    } else if (Index==1) {
      //
      // for Mode 1; dimensions must be 80*50
      //

      //
      // following is commented out due to waiting for spec changed!
      //

      if (Column!=80 || Row!= 50) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextOutputFunctionTestAssertionGuid048,
                       L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode, check mode 1",
                       L"%a:%d: Status = %r, Mode = %d, Dimension=(%d x %d), expected dimension=(80 x 50)",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index,
                       Column,
                       Row
                       );
      }
    }
  }

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/*
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode() Manually Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.6
//
EFI_STATUS
EFIAPI
BBTestSetModeFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Column, Row;
  UINTN                                Index;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }

  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.6.2.1
  // SetMode()
  //

  SctPrint (L"\n\rSetMode test start...\n\r");
  WaitTimeOrKey (5);


  //
  // For all available mode , perform test
  //
  for (Index = 0; Index < (UINTN)SimpleOut->Mode->MaxMode; Index++) {
    //
    // Get mode's dimensions
    //
    Status = SimpleOut->QueryMode (SimpleOut, Index, &Column, &Row);
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode",
                     L"%a:%d: Status = %r, Mode=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      continue;
    }

    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode",
                     L"%a:%d: Status = %r, Mode=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      continue;
    }

    //
    // Prepare Mode expected
    //
    BackupMode (SimpleOut, &ModeExpected);

    //
    // Call SetMode (Index) to change mode
    //
    Status = SimpleOut->SetMode (SimpleOut, Index);

    //
    // Mode integrity check
    //
    ModeExpected.CursorRow = 0;
    ModeExpected.CursorColumn = 0;
    ModeExpected.Mode= (INT32)Index;
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid050,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode - Mode integrity check",
                   L"%a:%d: Mode=%d,Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Return status check
    //
    if (EFI_ERROR(Status)) {
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid051,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode",
                   L"%a:%d: Status = %r, Mode=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );

    //
    // Call SetCursorPosition with dimension boundary values to verify that
    // the cursor position cannot be set outside the screen rectangle;
    //
    Status = SimpleOut->SetCursorPosition (SimpleOut, Column - 1, Row - 1);

    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid052,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode, Valid screen boundary testing",
                   L"%a:%d: Status = %r, Mode = %d,Position=(%d x %d) ",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index,
                   Column - 1,
                   Row - 1
                   );

    Status = SimpleOut->SetCursorPosition (SimpleOut, Column, Row - 1);
    if (Status!=EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid053,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode, Invalid screen boundary testing",
                   L"%a:%d: Status = %r, Mode = %d,Position=(%d x %d) ",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index,
                   Column,
                   Row - 1
                   );

    Status = SimpleOut->SetCursorPosition (SimpleOut, Column - 1, Row);
    if (Status!=EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid054,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode, Invalid screen boundary testing",
                   L"%a:%d: Status = %r, Mode=%d,Position=(%d x %d) ",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index,
                   Column - 1,
                   Row
                   );
    if (Status!=EFI_UNSUPPORTED) {
      continue;
    }

    //
    // clear the screen
    //
    Status = SimpleOut->ClearScreen (SimpleOut);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen, - ClearScreen()",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    //
    // Output mode screen boundary for user's view
    //
    SctPrint (L"Current screen resolution:(%d x %d)", Column, Row);
    if (AutoJudge (5, TRUE, L"\n\rSetMode correct?\r\n") != TRUE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid056,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode, user's view",
                   L"%a:%d: Mode=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index
                   );
  }

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode() Automatical Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.7
//
EFI_STATUS
EFIAPI
BBTestSetModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                Column, Row;
  UINTN                                Index;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }

  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.7.2.1
  // SetMode()
  //


  //
  // For all available mode , perform test
  //
  for (Index = 0; Index < (UINTN)SimpleOut->Mode->MaxMode; Index++) {
    //
    // Get mode's dimensions
    //
    Status = SimpleOut->QueryMode (SimpleOut, Index, &Column, &Row);
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode",
                     L"%a:%d: Status = %r, Mode=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      continue;
    }
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid057,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode",
                     L"%a:%d: Status = %r, Mode=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      continue;
    }

    //
    // Prepare Mode expected
    //
    BackupMode (SimpleOut, &ModeExpected);

    //
    // Call SetMode(Index) to change mode
    //
    Status = SimpleOut->SetMode (SimpleOut, Index);

    //
    // Mode integrity check
    //
    ModeExpected.CursorRow = 0;
    ModeExpected.CursorColumn = 0;
    ModeExpected.Mode = (INT32)Index;
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid058,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode",
                   L"%a:%d: Mode=%d, Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Return status check
    //
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid059,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode",
                   L"%a:%d: Status = %r, Mode=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );

    //
    // Call SetCursorPosition with dimension boundary values to verify that
    // the cursor position cannot be set outside the screen rectangle;
    //
    Status = SimpleOut->SetCursorPosition (SimpleOut, Column - 1, Row - 1);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid060,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode, Valid screen boundary testing",
                     L"%a:%d: Status = %r, Mode=%d,Position=(%d x %d) ",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index,
                     Column - 1,
                     Row - 1
                     );
      continue;
    }
    Status = SimpleOut->SetCursorPosition (SimpleOut, Column, Row - 1);
    if (Status!=EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid061,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode, Invalid screen boundary testing",
                     L"%a:%d: Status = %r, Mode=%d,Position=(%d x %d) ",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index,
                     Column,
                     Row-1
                     );
      continue;
    }
    Status = SimpleOut->SetCursorPosition (SimpleOut, Column - 1, Row);
    if (Status!=EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid062,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode, Invalid screen boundary testing",
                   L"%a:%d: Mode=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index
                   );
    if (Status!=EFI_UNSUPPORTED) {
      continue;
    }
  }

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute() Manually Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.8
//
EFI_STATUS
EFIAPI
BBTestSetAttributeFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  UINT16                               IndexBack, IndexFore;
  UINTN                                Attribute;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;
  BOOLEAN                              Result;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.8.2.1
  // SetAttbiute()
  //

  SctPrint (L"\n\rSetAttribute test start...\n\r");
  WaitTimeOrKey (5);

  //
  // For each background color
  //
  for (IndexBack = 0; IndexBack < 8; IndexBack++) {
    //
    // Set background color
    //
    Attribute = EFI_TEXT_ATTR((IndexBack + 1) % 16 , IndexBack);
    Status = SimpleOut->SetAttribute (SimpleOut, Attribute);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid063,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with valid attribute",
                   L"%a:%d: Status = %r, Attribute = %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Attribute
                   );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    // Clear screen with current background color
    //
    Status = SimpleOut->ClearScreen (SimpleOut);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen() ",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // Output Current Screen background description
    //
    SctPrint (L"\r\nCurrent background color %s\r\n", mAttribStr[IndexBack]);

    //
    // for each foreground color
    //
    Result = TRUE;
    for (IndexFore = 0; IndexFore < 16; IndexFore++) {
      //
      // Prepare expected mode
      //
      BackupMode (SimpleOut, &ModeExpected);

      //
      // Set foreground color
      //
      Attribute = EFI_TEXT_ATTR(IndexFore, IndexBack);
      Status = SimpleOut->SetAttribute (SimpleOut, Attribute);
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextOutputFunctionTestAssertionGuid065,
                       L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with valid attribute",
                       L"%a:%d: Status = %r, Attribute = %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Attribute
                       );
        Result = FALSE;
        continue;
      }

      //
      // Check whether Mode->Attribute reflects the current attribute.
      //
      ModeExpected.CursorRow = SimpleOut->Mode->CursorRow;
      ModeExpected.CursorColumn = SimpleOut->Mode->CursorColumn;
      ModeExpected.Attribute = (INT32)Attribute;
      if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextOutputFunctionTestAssertionGuid066,
                       L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with valid Attribute",
                       L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                       L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                       __FILE__,
                       (UINTN)__LINE__,
                       SimpleOut->Mode->CursorColumn,
                       SimpleOut->Mode->CursorRow,
                       SimpleOut->Mode->Mode,
                       SimpleOut->Mode->MaxMode,
                       SimpleOut->Mode->Attribute,
                       SimpleOut->Mode->CursorVisible,
                       ModeExpected.CursorColumn,
                       ModeExpected.CursorRow,
                       ModeExpected.Mode,
                       ModeExpected.MaxMode,
                       ModeExpected.Attribute,
                       ModeExpected.CursorVisible
                       );
        Result = FALSE;
      }

      //
      // Output current foreground color
      //
      SctPrint (L"%s\r\n", mAttribStr[IndexFore]);
    }
    if (Result==TRUE) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid067,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with valid attribute",
                     L"%a:%d: Background Color=%s",
                     __FILE__,
                     (UINTN)__LINE__,
                     mAttribStr[IndexBack]
                     );
    }

    //
    // Wait for some time to change next background color
    //
    gtBS->Stall (100000);
  }

  //
  // User's view
  //
  SctPrint (L"\r\nThe screen output with changed background and foreground color correct?\r\n");

  if (AutoJudge (5, TRUE, L"\n\rSetAttribute correct?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid068,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with valid Attribute, user's view",
                 L"%a:%d: user feedback",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute() Auto Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.9
//
EFI_STATUS
EFIAPI
BBTestSetAttributeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  UINT16                               IndexBack, IndexFore;
  UINTN                                Attribute;
  UINTN                                Mode;

  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;
  BOOLEAN                              Result;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // For each mode supported!
  //
  for (Mode = 0; Mode < (UINTN)SimpleOut->Mode->MaxMode; Mode++) {
    //
    // Change mode
    //
    Status = SimpleOut->SetMode (SimpleOut, Mode);
    if (EFI_ERROR(Status)) {
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode",
                     L"%a:%d: Status = %r, Mode = %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Mode
                     );
      continue;
    }


    //
    // Assertion Points 4.1.9.2.1
    // SetAttribute()
    //


    //
    // For each background color
    //
    for (IndexBack = 0; IndexBack < 8; IndexBack++) {
      //
      // Set background color
      //
      Attribute = EFI_TEXT_ATTR((IndexBack + 1) % 16 , IndexBack);
      Status = SimpleOut->SetAttribute (SimpleOut, Attribute);
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid070,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with valid attribute",
                     L"%a:%d: Status = %r, Attribute = %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Attribute
                     );
      if (EFI_ERROR(Status)) {
        continue;
      }

      //
      // Clear screen with current background color
      //
      Status = SimpleOut->ClearScreen (SimpleOut);
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextOutputFunctionTestAssertionGuid071,
                       L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen() ",
                       L"%a:%d: Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        continue;
      }

      //
      // Output Current Screen background description
      //
      SctPrint (L"\r\nCurrent background color %s\r\n", mAttribStr[IndexBack]);

      //
      // for each foreground color
      //
      Result = TRUE;
      for (IndexFore = 0; IndexFore < 16; IndexFore++) {
        //
        // Prepare expected mode
        //
        BackupMode (SimpleOut, &ModeExpected);

        //
        // Set foreground color
        //
        Attribute = EFI_TEXT_ATTR(IndexFore, IndexBack);
        Status = SimpleOut->SetAttribute (SimpleOut, Attribute);
        if (EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gSimpleTextOutputFunctionTestAssertionGuid072,
                         L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with valid attribute",
                         L"%a:%d: Status = %r, Attribute = 0x%lx",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         (UINT64)Attribute
                         );
          Result = FALSE;
          continue;
        }

        //
        // Check whether Mode->Attribute reflects the current attribute.
        //
        ModeExpected.CursorRow = SimpleOut->Mode->CursorRow;
        ModeExpected.CursorColumn = SimpleOut->Mode->CursorColumn;
        ModeExpected.Attribute = (INT32)Attribute;
        if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gSimpleTextOutputFunctionTestAssertionGuid073,
                         L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with valid Attribute",
                         L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                         L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                         __FILE__,
                         (UINTN)__LINE__,
                         SimpleOut->Mode->CursorColumn,
                         SimpleOut->Mode->CursorRow,
                         SimpleOut->Mode->Mode,
                         SimpleOut->Mode->MaxMode,
                         SimpleOut->Mode->Attribute,
                         SimpleOut->Mode->CursorVisible,
                         ModeExpected.CursorColumn,
                         ModeExpected.CursorRow,
                         ModeExpected.Mode,
                         ModeExpected.MaxMode,
                         ModeExpected.Attribute,
                         ModeExpected.CursorVisible
                         );
          Result = FALSE;
        }

        //
        // Output current foreground color
        //
        SctPrint (L"%s\r\n", mAttribStr[IndexFore]);
      }
      if (Result==TRUE) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextOutputFunctionTestAssertionGuid074,
                       L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with valid attribute, summary check of all colors",
                       L"%a:%d: Background Color=%s",
                       __FILE__,
                       (UINTN)__LINE__,
                       mAttribStr[IndexBack]
                       );
      }
    }
  }

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen() Manually Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.10
//
EFI_STATUS
EFIAPI
BBTestClearScreenFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }

  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.10.2.1
  // ClearScreen()
  //

  SctPrint (L"\n\rClearScreen test start...\n\r");
  WaitTimeOrKey (5);

  //
  // Prepare expected Mode after call Reset.
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Clear screen with current background color
  //
  Status = SimpleOut->ClearScreen (SimpleOut);

  //
  // Check mode integrity
  //
  ModeExpected.CursorRow = 0;
  ModeExpected.CursorColumn = 0;

  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid075,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen(), check cursor position",
                 L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                 L" Expected: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                 __FILE__,
                 (UINTN)__LINE__,
                 SimpleOut->Mode->CursorColumn,
                 SimpleOut->Mode->CursorRow,
                 SimpleOut->Mode->Mode,
                 SimpleOut->Mode->MaxMode,
                 SimpleOut->Mode->Attribute,
                 SimpleOut->Mode->CursorVisible,
                 ModeExpected.CursorColumn,
                 ModeExpected.CursorRow,
                 ModeExpected.Mode,
                 ModeExpected.MaxMode,
                 ModeExpected.Attribute,
                 ModeExpected.CursorVisible
                 );

  //
  // Returned status check
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid076,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen() ",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // ClearScreen again with no success assertion record
  //

  //
  // Prepare expected Mode after call Reset.
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Clear screen with current background color
  //
  Status = SimpleOut->ClearScreen (SimpleOut);

  //
  // Check mode integrity
  //
  ModeExpected.CursorRow = 0;
  ModeExpected.CursorColumn = 0;

  if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid077,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen() ,Check cursor position",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );
  }

  //
  // Returned status check
  //
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid078,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen() ",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // User's view
  //
  if (AutoJudge (5, TRUE, L"\n\rClearScreen correct?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid079,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - user's view",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen() Auto Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.11
//
EFI_STATUS
EFIAPI
BBTestClearScreenFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;
  UINTN                                Mode;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // For each mode supported!
  //
  for (Mode = 0; Mode < (UINTN)SimpleOut->Mode->MaxMode; Mode++) {
    //
    // Change mode
    //
    Status = SimpleOut->SetMode (SimpleOut, Mode);
    if (EFI_ERROR(Status)) {
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode",
                     L"%a:%d: Status = %r, Mode = %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Mode
                     );
      continue;
    }


    //
    // Assertion Points 4.1.11.2.1
    // ClearScreen()
    //

    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);

    //
    // Clear screen with current background color
    //
    Status = SimpleOut->ClearScreen (SimpleOut);

    //
    // Check mode integrity
    //
    ModeExpected.CursorRow = 0;
    ModeExpected.CursorColumn = 0;

    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid081,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen(),check cursor postion ",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L"Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Returned status check
    //
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid082,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen() ",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition() Manually Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.12
//
EFI_STATUS
EFIAPI
BBTestSetCursorPositionFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                IndexRow, IndexColumn;
  BOOLEAN                              Result;
  UINTN                                Column, Row;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.12.2.1
  // SetCursorPosition()
  //

  SctPrint (L"\n\rSetCursorPosition test start...\n\r");
  WaitTimeOrKey (5);

  //
  // Enable cursor
  //
  Status = SimpleOut->EnableCursor (SimpleOut, TRUE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() to set cursor visible",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    //
    // No need perform next action
    //
    return Status;
  }

  //
  // Get current mode, and it's boundary of screen for test the destine cursor position
  //
  Status = SimpleOut->QueryMode (SimpleOut, (UINTN)SimpleOut->Mode->Mode, &Column, &Row);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() on current mode",
                   L"%a:%d, Status = %r, Mode = %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   SimpleOut->Mode->Mode
                   );

    return Status;
  }

  //
  // Clear screen for testing
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  Result = TRUE;

  //
  // Move the cursor
  //
  for (IndexRow = 0; IndexRow < Row; IndexRow++) {
    for (IndexColumn = 0; IndexColumn < Column; IndexColumn++) {
      //
      // Prepare expected Mode after call Reset.
      //
      BackupMode (SimpleOut, &ModeExpected);

      //
      // Set cursor position to (IndexRow * IndexColumn)
      //
      Status = SimpleOut->SetCursorPosition (SimpleOut, IndexColumn, IndexRow);

      //
      // Mode integrity check
      //
      ModeExpected.CursorRow = (INT32)IndexRow;
      ModeExpected.CursorColumn = (INT32)IndexColumn;
      if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextOutputFunctionTestAssertionGuid086,
                       L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPosition() with valid position, Mode integrity check",
                       L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                       L"Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                       __FILE__,
                       (UINTN)__LINE__,
                       SimpleOut->Mode->CursorColumn,
                       SimpleOut->Mode->CursorRow,
                       SimpleOut->Mode->Mode,
                       SimpleOut->Mode->MaxMode,
                       SimpleOut->Mode->Attribute,
                       SimpleOut->Mode->CursorVisible,
                       ModeExpected.CursorColumn,
                       ModeExpected.CursorRow,
                       ModeExpected.Mode,
                       ModeExpected.MaxMode,
                       ModeExpected.Attribute,
                       ModeExpected.CursorVisible
                       );
        Result = FALSE;
      }

      //
      // Returned status check
      //
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextOutputFunctionTestAssertionGuid087,
                       L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPosition() with valid position",
                       L"%a:%d: Status = %r, Position=(%d x %d)",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IndexColumn,
                       IndexRow
                       );
        Result = FALSE;
      }

      //
      // Wait for a little time
      //
      gtBS->Stall (1000);
    }
  }

  if (Result == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid088,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPosition()  with valid position",
                   L"%a:%d: summary check for all position",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  }


  //
  // User's view
  //
  if (AutoJudge (5, TRUE, L"\n\rSetCursorPosition correct?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid089,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPosition()  user's view",
                 L"%a:%d: user feedback",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition() Auto Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.13
//
EFI_STATUS
EFIAPI
BBTestSetCursorPositionFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                IndexRow, IndexColumn;
  BOOLEAN                              Result;
  UINTN                                Column, Row;
  UINTN                                Mode;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // For each mode supported!
  //
  for (Mode = 0; Mode < (UINTN)SimpleOut->Mode->MaxMode; Mode++) {
    //
    // Change mode
    //
    Status = SimpleOut->SetMode (SimpleOut, Mode);
    if (EFI_ERROR(Status)) {
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode",
                     L"%a:%d: Status = %r, Mode = %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Mode
                     );
      continue;
    }

    //
    // Assertion Points 4.1.12.2.1
    // SetCursorPosition()
    //

    //
    // Enable cursor
    //
    Status = SimpleOut->EnableCursor (SimpleOut, TRUE);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor () to set cursor visible",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      //
      // No need perform next action
      //
      return Status;
    }

    //
    // Get current mode, and it's boundary of screen for test the destine cursor position
    //
    Status = SimpleOut->QueryMode (SimpleOut, Mode, &Column, &Row);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() on current mode",
                     L"%a:%d: Status = %r, Mode = %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Mode
                     );
      return Status;
    }

    //
    // Clear screen for testing
    //
    Status = SimpleOut->ClearScreen (SimpleOut);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    Result = TRUE;

    //
    // Move the cursor
    //
    for (IndexRow = 0; IndexRow < Row; IndexRow++) {
      for (IndexColumn = 0; IndexColumn < Column; IndexColumn++) {
        //
        // Prepare expected Mode after call Reset.
        //
        BackupMode (SimpleOut, &ModeExpected);

        //
        // Set cursor position to (IndexRow * IndexColumn)
        //
        Status = SimpleOut->SetCursorPosition (SimpleOut, IndexColumn, IndexRow);

        //
        // Mode integrity check
        //
        ModeExpected.CursorRow = (INT32)IndexRow;
        ModeExpected.CursorColumn = (INT32)IndexColumn;
        if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gSimpleTextOutputFunctionTestAssertionGuid094,
                         L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPosition() with valid position, Mode integrity check",
                         L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                         L"Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                         __FILE__,
                         (UINTN)__LINE__,
                         SimpleOut->Mode->CursorColumn,
                         SimpleOut->Mode->CursorRow,
                         SimpleOut->Mode->Mode,
                         SimpleOut->Mode->MaxMode,
                         SimpleOut->Mode->Attribute,
                         SimpleOut->Mode->CursorVisible,
                         ModeExpected.CursorColumn,
                         ModeExpected.CursorRow,
                         ModeExpected.Mode,
                         ModeExpected.MaxMode,
                         ModeExpected.Attribute,
                         ModeExpected.CursorVisible
                         );
          Result = FALSE;
        }

        //
        // Returned status check
        //
        if (EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gSimpleTextOutputFunctionTestAssertionGuid095,
                         L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPosition() with valid position",
                         L"%a:%d: Status = %r, Position=(%d x %d)",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         IndexColumn,
                         IndexRow
                         );
          Result = FALSE;
        }
      }
    }

    if (Result == TRUE) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid096,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPosition() with valid position",
                     L"%a:%d: check summary for all position",
                     __FILE__,
                     (UINTN)__LINE__
                     );
    }
  }
  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor() Manually Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.14
//
EFI_STATUS
EFIAPI
BBTestEnableCursorFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // Assertion Points 4.1.14.2.1
  // EnableCursor() with Visible as TRUE to make cursor visible
  //

  SctPrint (L"\n\rEnableCursor test start...\n\r");
  WaitTimeOrKey (5);

  //
  // Clear screen for testing
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  //
  // Prepare expected Mode after call Reset.
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call EnableCursor() with Visible as TRUE
  //
  Status = SimpleOut->EnableCursor (SimpleOut, TRUE);

  if (Status==EFI_SUCCESS) {
    //
    // Mode integrity check.
    //
    ModeExpected.CursorVisible = TRUE;
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid098,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being TRUE, Mode integrity check",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L"Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Return status assertion!
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid099,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being TRUE",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else if (Status == EFI_UNSUPPORTED) {
    //
    // Ask for user's view.
    //
    SctPrint (L"EnableCursor(TRUE) return EFI_UNSUPPORTED!");
    if (AutoJudge (5, TRUE, L"\n\rCorrect?\r\n") != TRUE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid100,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor(TRUE) return EFI_UNSUPPORTED as user's view",
                   L"%a:%d: USER FEEDBACK",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // Mode integrity check.
    //
    ModeExpected.CursorRow = SimpleOut->Mode->CursorRow;
    ModeExpected.CursorColumn = SimpleOut->Mode->CursorColumn;
    ModeExpected.CursorVisible = SimpleOut->Mode->CursorVisible;
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid101,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being TRUE, UNSUPPORTED, Mode integrity check",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L"Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );
    goto AssertionPoint2;
  } else {
    //
    // Return status assertion!
    //
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid102,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being TRUE",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto AssertionPoint2;
  }

  //
  // User's view
  //
  if (AutoJudge (5, TRUE, L"\n\rCursor Visible?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid103,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible as TRUE, user's view",
                 L"%a:%d: USER FEEDBACK",
                 __FILE__,
                 (UINTN)__LINE__
                 );

AssertionPoint2:
  //
  // Assertion Points 4.1.14.2.2
  // EnableCursor() with Visible as FALSE to make cursor invisible
  //

  //
  // Clear screen for testing
  //
  Status = SimpleOut->ClearScreen (SimpleOut);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  //
  // Prepare expected Mode after call Reset.
  //
  BackupMode (SimpleOut, &ModeExpected);

  //
  // Call EnableCursor () with Visible as FALSE
  //
  Status = SimpleOut->EnableCursor (SimpleOut, FALSE);

  if (Status==EFI_SUCCESS) {
    //
    // Mode integrity check.
    //
    ModeExpected.CursorVisible = FALSE;
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid105,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being FALSE, Mode integrity check",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L"Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Return status assertion!
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid106,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being FALSE",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else if (Status == EFI_UNSUPPORTED) {
    //
    // Ask for user's view.
    //
    SctPrint (L"EnableCursor(FALSE) return EFI_UNSUPPORTED!");
    if (AutoJudge (5, TRUE, L"\n\rCorrect?\r\n") != TRUE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid107,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor(FALSE) return EFI_UNSUPPORTED as user's view",
                   L"%a:%d: USER FEEDBACK",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // Mode integrity check.
    //
    ModeExpected.CursorRow = SimpleOut->Mode->CursorRow;
    ModeExpected.CursorColumn = SimpleOut->Mode->CursorColumn;
    ModeExpected.CursorVisible = SimpleOut->Mode->CursorVisible;
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid108,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being FALSE, UNSUPPORTED, Mode integrity check",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L"Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );
    goto RestoreEnvironment;
  } else {
    //
    // Return status assertion!
    //
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid109,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being FALSE",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto RestoreEnvironment;
  }

  //
  // User's view
  //
  if (AutoJudge (5, TRUE, L"\n\rCursor Invisible?\r\n") != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextOutputFunctionTestAssertionGuid110,
                 L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible as FALSE user's view",
                 L"%a:%d: USER FEEDBACK",
                 __FILE__,
                 (UINTN)__LINE__
                 );

RestoreEnvironment:
  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor() Auto Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.15
//
EFI_STATUS
EFIAPI
BBTestEnableCursorFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;

  EFI_TEST_ASSERTION                   AssertionType;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;
  UINTN                                Mode;

  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SimpleOut = (EFI_SIMPLE_TEXT_OUT_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_Output_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextOut (SimpleOut, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    Status = LocateUgaDrawFromSimpleTextOut (SimpleOut, &UgaDraw, StandardLib);
    if (EFI_ERROR(Status)) {
      //
      // Console Splitter/StdErr
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/StdErr"
                     );
    } else {
      //
      // Console Splitter/ConOut
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: ConsoleSplitter/ConOut"
                     );
    }
  }


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  //
  // For each mode supported!
  //
  for (Mode = 0; Mode < (UINTN)SimpleOut->Mode->MaxMode; Mode++) {
    //
    // Change mode
    //
    Status = SimpleOut->SetMode (SimpleOut, Mode);
    if (EFI_ERROR(Status)) {
      if (EFI_UNSUPPORTED == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with valid mode",
                     L"%a:%d: Status = %r, Mode = %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Mode
                     );
      continue;
    }

    //
    // Assertion Points 4.1.15.2.1
    // EnableCursor() with Visible as TRUE to make cursor visible
    //

    //
    // Clear screen for testing
    //
    Status = SimpleOut->ClearScreen (SimpleOut);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }


    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);

    //
    // Call EnableCursor() with Visible as TRUE
    //
    Status = SimpleOut->EnableCursor (SimpleOut, TRUE);

    if (Status!=EFI_SUCCESS && Status!=EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid113,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being TRUE",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto AssertionPoint2;
    }

    //
    // Mode integrity check.
    //
    if (Status==EFI_SUCCESS) {
      ModeExpected.CursorVisible = TRUE;
    } else {
      //
      // Skip CursorVisible integrity check
      //
      ModeExpected.CursorVisible = SimpleOut->Mode->CursorVisible;
    }
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid114,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being TRUE, Mode integrity check",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L"Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid115,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being TRUE",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


  AssertionPoint2:
    //
    // Assertion Points 4.1.14.2.2
    // EnableCursor() with Visible as FALSE to make cursor invisible
    //

    //
    // Clear screen for testing
    //
    Status = SimpleOut->ClearScreen (SimpleOut);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.ClearScreen - ClearScreen()",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }


    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);

    //
    // Call EnableCursor() with Visible as FALSE
    //
    Status = SimpleOut->EnableCursor (SimpleOut, FALSE);

    if (Status!=EFI_SUCCESS && Status!=EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputFunctionTestAssertionGuid117,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being FAlSE",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      RestoreMode (SimpleOut, &ModeOrg, StandardLib);
      continue;
    }

    //
    // Mode integrity check.
    //
    if (Status==EFI_SUCCESS) {
      ModeExpected.CursorVisible = FALSE;
    } else {
      //
      // Skip CursorVisible integrity check
      //
      ModeExpected.CursorVisible = SimpleOut->Mode->CursorVisible;
    }
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode)==FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid118,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being FALSE, Mode integrity check",
                   L"%a:%d: Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );


    AssertionType = EFI_TEST_ASSERTION_PASSED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputFunctionTestAssertionGuid119,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.EnableCursor - EnableCursor() with Visible being FALSE",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  }

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}
