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

  SimpleTextOutBBTestConformance_efi.c

Abstract:

  Conformance Test Cases of Simple Text Output Protocol

--*/


#include "SimpleTextOutBBTestMain_efi.h"


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode() Auto Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.3
//
EFI_STATUS
EFIAPI
BBTestQueryModeConformanceAutoTest (
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

  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeExpected;
  UINTN                                ModeNumber[5];
  UINTN                                Column, Row;
  UINTN                                Index;

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
  // Prepare test data
  //
  ModeNumber[0] = SimpleOut->Mode->MaxMode;
  ModeNumber[1] = SimpleOut->Mode->MaxMode + 1;
  ModeNumber[2] = SimpleOut->Mode->MaxMode + 2;
  ModeNumber[3] = SimpleOut->Mode->MaxMode + 100;

  Column = 0;
  Row = 0;
  for (Index = 0; Index <= 3; Index++) {
    //
    // Clear Screen
    //
    SimpleOut->ClearScreen (SimpleOut);

    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);

    //
    // Call QueryMode with invalid ModeNumber
    //
    Status = SimpleOut->QueryMode (SimpleOut, ModeNumber[Index], &Column, &Row);

    //
    // Mode itegrity test
    //
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputConformanceTestAssertionGuid001,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with invalid ModeNumber, mode position integrity",
                   L"%a:%d: ModeNumber=%d Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeNumber[Index],
                   SimpleOut->Mode->CursorColumn,
                   SimpleOut->Mode->CursorRow,
                   SimpleOut->Mode->Mode,
                   SimpleOut->Mode->Attribute,
                   SimpleOut->Mode->MaxMode,
                   SimpleOut->Mode->CursorVisible,
                   ModeExpected.CursorColumn,
                   ModeExpected.CursorRow,
                   ModeExpected.Mode,
                   ModeExpected.MaxMode,
                   ModeExpected.Attribute,
                   ModeExpected.CursorVisible
                   );

    //
    // Status check
    //
    if (Status!=EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputConformanceTestAssertionGuid002,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with invalid ModeNumber",
                   L"%a:%d: Status = %r, ModeNumber = %d, MaxModeNumber=%d, Column=%d, Row=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ModeNumber[Index],
                   SimpleOut->Mode->MaxMode,
                   Column,
                   Row
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode() Auto Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.4
//
EFI_STATUS
EFIAPI
BBTestSetModeConformanceAutoTest (
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
  UINTN                                ModeNumber[11];

  UINTN                                Index;

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
  // Prepare test data
  //
  ModeNumber[0] = SimpleOut->Mode->MaxMode;
  ModeNumber[1] = SimpleOut->Mode->MaxMode + 1;
  ModeNumber[2] = SimpleOut->Mode->MaxMode + 2;
  ModeNumber[3] = SimpleOut->Mode->MaxMode + 3;
  ModeNumber[4] = SimpleOut->Mode->MaxMode + 4;
  ModeNumber[5] = SimpleOut->Mode->MaxMode + 5;
  ModeNumber[6] = SimpleOut->Mode->MaxMode + 6;
  ModeNumber[7] = SimpleOut->Mode->MaxMode + 7;
  ModeNumber[8] = SimpleOut->Mode->MaxMode + 8;
  ModeNumber[9] = SimpleOut->Mode->MaxMode + 9;
  ModeNumber[10] = SimpleOut->Mode->MaxMode + 100;


  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  for (Index = 0; Index < 11; Index++) {
    //
    // Clear Screen
    //
    // SimpleOut->ClearScreen(SimpleOut);

    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);

    //
    // Call SetMode with invalid ModeNumber
    //
    Status = SimpleOut->SetMode (SimpleOut, ModeNumber[Index]);

    //
    // Mode itegrity test
    //
    ModeExpected.CursorColumn = SimpleOut->Mode->CursorColumn;
    ModeExpected.CursorRow = SimpleOut->Mode->CursorRow;
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputConformanceTestAssertionGuid003,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with invalid ModeNumber, mode position integrity",
                   L"%a:%d: ModeNumber=%d Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeNumber[Index],
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
    // Status check
    //
    if (Status!=EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputConformanceTestAssertionGuid004,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetMode - SetMode() with invalid ModeNumber",
                   L"%a:%d: Status = %r, ModeNumber = %d, MaxModeNumber=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ModeNumber[Index],
                   SimpleOut->Mode->MaxMode
                   );
  }

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute() Auto Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.5
//
EFI_STATUS
EFIAPI
BBTestSetAttributeConformanceAutoTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  //
  // This test case should be obsolete according to Spec changed.
  //

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL         *SimpleOut;
  EFI_TEST_ASSERTION                   AssertionType;

  EFI_SIMPLE_TEXT_OUTPUT_MODE          ModeOrg, ModeExpected;
  UINTN                                Attribute[10];

  UINTN                                Index;

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
  // Prepare test data
  //

  Attribute[0] = 0xB3;
  Attribute[1] = 0x80;
  Attribute[2] = 0x91;
  Attribute[3] = 0xA2;
  Attribute[4] = 65538;

  //
  // Backup Mode
  //
  BackupMode (SimpleOut, &ModeOrg);

  for (Index = 0; Index < 5; Index++) {
    //
    // Prepare expected Mode after call Reset.
    //
    BackupMode (SimpleOut, &ModeExpected);

    //
    // Call SetAttribute with invalid Attribute
    //
    Status = SimpleOut->SetAttribute (SimpleOut, Attribute[Index]);

    //
    // Mode itegrity test
    //
    ModeExpected.CursorColumn = SimpleOut->Mode->CursorColumn;
    ModeExpected.CursorRow = SimpleOut->Mode->CursorRow;
    if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputConformanceTestAssertionGuid005,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with invalid Attribute, mode position integrity",
                   L"%a:%d: Attribute=%x Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                   L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                   __FILE__,
                   (UINTN)__LINE__,
                   Attribute[Index],
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
    // Status check
    //
    if (Status!=EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextOutputConformanceTestAssertionGuid006,
                   L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetAttribute - SetAttribute() with invalid Attribute",
                   L"%a:%d: Status = %r, Attribute = %x",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Attribute[Index]
                   );
  }

  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition() Auto Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.6
//
EFI_STATUS
EFIAPI
BBTestSetCursorPositionConformanceAutoTest (
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
  INT32                                Mode;
  UINTN                                ColumnTest[10], RowTest[10];
  UINTN                                Column, Row;

  UINTN                                Index;

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
  for (Mode = 0; Mode < SimpleOut->Mode->MaxMode; Mode++) {
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
    // Get Mode's screen boundary
    //
    Status = SimpleOut->QueryMode (SimpleOut, Mode, &Column, &Row);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.QueryMode - QueryMode() with valid mode",
                     L"%a:%d: Status = %r, Mode = %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Mode
                     );
      continue;
    }

    //
    // Prepare test data
    //
    ColumnTest[0] = Column;
    RowTest[0]    = Row - 1;
    ColumnTest[1] = Column;
    RowTest[1]    = 0;
    ColumnTest[2] = Column + 1;
    RowTest[2]    = Row - 1;
    ColumnTest[3] = Column + 1;
    RowTest[3]    = 0;
    ColumnTest[4] = 0;
    RowTest[4]    = Row;
    ColumnTest[5] = Column - 1;
    RowTest[5]    = Row;
    ColumnTest[6] = Column - 1;
    RowTest[6]    = Row + 1;
    ColumnTest[7] = 0;
    RowTest[7]    = Row + 1;

    for (Index = 0; Index < 8; Index++) {
      //
      // Prepare expected Mode after call Reset.
      //
      BackupMode (SimpleOut, &ModeExpected);

      //
      // Call SetAttribute with invalid Attribute
      //
      Status = SimpleOut->SetCursorPosition (SimpleOut, ColumnTest[Index], RowTest[Index]);

      //
      // Mode itegrity test
      //
      if (CheckModeIntegrity (&ModeExpected, SimpleOut->Mode) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputConformanceTestAssertionGuid009,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPosition() with invalid position, mode position integrity",
                     L"%a:%d: Mode=%d, Position=(%d x %d) Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
                     L" Expected:Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d.",
                     __FILE__,
                     (UINTN)__LINE__,
                     Mode,
                     ColumnTest[Index],
                     RowTest[Index],
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
      // Status check
      //
      if (Status!=EFI_UNSUPPORTED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextOutputConformanceTestAssertionGuid010,
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPosition() with invalid Position",
                     L"%a:%d: Status = %r, Mode = %d, Position = (%d x %d)",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Mode,
                     ColumnTest[Index],
                     RowTest[Index]
                     );
    }
  }
  return RestoreMode (SimpleOut, &ModeOrg, StandardLib);
}
