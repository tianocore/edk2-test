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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  SimpleTextOutBBTestConformance_uefi.c

Abstract:

  Conformance Test Cases of Simple Text Output Protocol

--*/


#include "SimpleTextOutBBTestMain_uefi.h"


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

  EFI_GRAPHICS_OUTPUT_PROTOCOL                *GraphicsOutput;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
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
    Status = LocateGopFromSimpleTextOut (SimpleOut, &GraphicsOutput, StandardLib);
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

  EFI_GRAPHICS_OUTPUT_PROTOCOL                *GraphicsOutput;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
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
  // And output device path or device name
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
    Status = LocateGopFromSimpleTextOut (SimpleOut, &GraphicsOutput, StandardLib);
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

  EFI_GRAPHICS_OUTPUT_PROTOCOL                *GraphicsOutput;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;



  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
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
    Status = LocateGopFromSimpleTextOut (SimpleOut, &GraphicsOutput, StandardLib);
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

  EFI_GRAPHICS_OUTPUT_PROTOCOL                *GraphicsOutput;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
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
    Status = LocateGopFromSimpleTextOut (SimpleOut, &GraphicsOutput, StandardLib);
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
      AssertionType = EFI_TEST_ASSERTION_FAILED;
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
                     L"%a:%d: Mode=%d, Positoin=(%d x %d) Current: Cursor Position(%d x %d), Mode=%d, MaxMode=%d, Attribute=%d, CursorVisible=%d. "\
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
                     L"EFI_SIMPLE_TEXT_OUT_PROTOCOL.SetCursorPosition - SetCursorPositoin() with invalid Position",
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
