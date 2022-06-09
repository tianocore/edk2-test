/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SimpleTextInBBTestFunction.c

Abstract:

  Interface Test Cases of Simple Input Protocol

--*/


#include "SimpleTextInBBTestMain.h"


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset() Interface Test.
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
BBTestResetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_IN_PROTOCOL          *SimpleIn;


  EFI_TEST_ASSERTION                   AssertionType;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  UINTN                                Index;
  EFI_INPUT_KEY                        Key;
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

  SimpleIn = (EFI_SIMPLE_TEXT_IN_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_In_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextIn (SimpleIn, &DevicePath, StandardLib);
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
      DevicePathStr=NULL;
    }
  } else {
    //
    // Console Splitter/StdErr
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/TxtIn"
                   );
  }


  //
  // Assertion Point 4.1.1.2.1
  // Reset without Extended Verification & Reset with Extended Verification
  //

  for (Index=0;Index<REPEAT_EXECUTE_OF_TEST;Index++) {
    //
    // Call SimpleTextIn.Reset() with ExtendedVerification as FALSE
    //
    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);
    if (OldTpl <= TPL_APPLICATION) {
      if (OldTpl < TPL_APPLICATION) {
        OldTpl = gtBS->RaiseTPL (TPL_APPLICATION);
        Status = SimpleIn->Reset (SimpleIn, FALSE);
        gtBS->RestoreTPL (OldTpl);
       } else {
        Status = SimpleIn->Reset (SimpleIn, FALSE);
       }
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextInInterfaceTestAssertionGuid001,
                     L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as FALSE",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
    //
    //Auto test, after reset(), no key input, ReadKeyStroke() should return EFI_NOT_READY
    //
    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);
    if (OldTpl <= TPL_APPLICATION) {
      if (OldTpl < TPL_APPLICATION) {
        OldTpl = gtBS->RaiseTPL (TPL_APPLICATION);
        Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
        gtBS->RestoreTPL (OldTpl);
      } else {
        Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
      }
      if (Status != EFI_NOT_READY) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextInInterfaceTestAssertionGuid012,
                     L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as FALSE, ReadKeyStroke() verification with no key input",
                     L"%a:%d: Status = %r, Expected = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EFI_NOT_READY
                     );
    } 
    //
    // Call SimpleTextIn.Reset() with ExtendedVerification as TRUE
    //
    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);
    if (OldTpl <= TPL_APPLICATION) {
       if (OldTpl < TPL_APPLICATION) {
        OldTpl = gtBS->RaiseTPL (TPL_APPLICATION);
        Status = SimpleIn->Reset (SimpleIn, TRUE);
        gtBS->RestoreTPL (OldTpl);
       } else {
        Status = SimpleIn->Reset (SimpleIn, TRUE);
       }
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextInInterfaceTestAssertionGuid002,
                     L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as TRUE",
                     L"%a:%d: Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    //
    //Auto test, after reset(), no key input, ReadKeyStroke() should return EFI_NOT_READY
    //
    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);
    if (OldTpl <= TPL_APPLICATION) {
       if (OldTpl < TPL_APPLICATION) {
         OldTpl = gtBS->RaiseTPL (TPL_APPLICATION);
        Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
        gtBS->RestoreTPL (OldTpl);
       } else {
        Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
       }
      if (Status != EFI_NOT_READY) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextInInterfaceTestAssertionGuid013,
                     L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as TRUE, ReadKeyStroke() verification with no key input",
                     L"%a:%d: Status = %r, Expected = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EFI_NOT_READY
                     );
    } 
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset() Interface Test.
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
BBTestResetFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_IN_PROTOCOL          *SimpleIn;


  EFI_TEST_ASSERTION                   AssertionType;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_INPUT_KEY                        Key;


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

  SimpleIn = (EFI_SIMPLE_TEXT_IN_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_In_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextIn (SimpleIn, &DevicePath, StandardLib);
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
      DevicePathStr=NULL;
    }
  } else {
    //
    // Console Splitter/StdErr
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/TxtIn"
                   );
  }

  SctPrint (L"\r\nReset Function Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 4.1.2.2.1
  // Reset without Extended Verification & Reset with Extended Verification
  //


  //
  // Call SimpleTextIn.Reset() with ExtendedVerification as FALSE
  //
  Status = SimpleIn->Reset (SimpleIn, FALSE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInInterfaceTestAssertionGuid003,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as FALSE",
                 L"%a:%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Prompt tester to input some characters
  //
  SctPrint (L"Press some displayble keys in 5 second!");

  //
  // Wait 5 seconds
  //
  gtBS->Stall (5000000);

  //
  // Call SimpleTextIn.Reset with ExtendedVerification as FALSE again
  //
  Status = SimpleIn->Reset (SimpleIn, FALSE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInInterfaceTestAssertionGuid004,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as FALSE",
                 L"%a:%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call SimpleTextIn.ReadKeyStroke() to check key buffer
  //
  Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);

  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInInterfaceTestAssertionGuid005,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as FALSE, ReadKeyStroke() verification",
                 L"%a:%d, Status = %r, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_READY
                 );

  //
  // Assertion Point 4.1.2.2.2
  //

  //
  // Call SimpleTextIn.Reset() with ExtendedVerification as TRUE
  //
  Status = SimpleIn->Reset (SimpleIn, TRUE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInInterfaceTestAssertionGuid006,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as TRUE",
                 L"%a:%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Prompt tester to input some characters
  //
  SctPrint (L"Press some displayble keys in 5 second AGAIN!");

  //
  // Wait 5 seconds
  //
  gtBS->Stall (5000000);

  //
  // Call SimpleTextIn.Reset with ExtendedVerification as TRUE again
  //
  Status = SimpleIn->Reset (SimpleIn, TRUE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInInterfaceTestAssertionGuid007,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as TRUE",
                 L"%a:%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call SimpleTextIn.ReadKeyStroke() to check key buffer
  //
  Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);

  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInInterfaceTestAssertionGuid008,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as TRUE, ReadKeyStroke() verification",
                 L"%a:%d, Status = %r, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_READY
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke() Interface Test.
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
BBTestReadKeyStrokeFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_IN_PROTOCOL          *SimpleIn;


  EFI_TEST_ASSERTION                   AssertionType;
  EFI_INPUT_KEY                        Key;


  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  BOOLEAN                              KeyPressed=FALSE, EscPressed=FALSE;

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

  SimpleIn = (EFI_SIMPLE_TEXT_IN_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_In_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextIn (SimpleIn, &DevicePath, StandardLib);
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
      DevicePathStr=NULL;
    }
  } else {
    //
    // Console Splitter/StdErr
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/TxtIn"
                   );
  }

  //
  // wait for times
  //
  SctPrint (L"\r\nReadKeyStroke Function Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 4.1.3.2.1
  // ReadKeyStroke()
  //

  SctPrint (L"\r\nPress any key and wait for echo. Two ESC keys to quit");
  while (TRUE) {
    KeyPressed = WaitTimeOrKeySimpleIn (SimpleIn, 1);
    if (KeyPressed==TRUE) {
      SctPrint (L"\r\nKey Pressed--");
      //
      // Key Pressed!
      //

      //
      // Call ReadKeyStroke to retrieve the key
      //
      Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextInInterfaceTestAssertionGuid009,
                       L"EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke - ReadKeyStroke() with key input",
                       L"%a:%d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
      }

      //
      // Output what user input
      //
      if (Key.ScanCode==0) {
        //
        // Unicode character
        //
        SctAPrint ((char*)(&Key.UnicodeChar));
      } else {
        //
        // Scan code character
        //
        SctPrint (ScanCodeDesc (Key.ScanCode));
      }
      if (Key.ScanCode==SCAN_ESC) {
        if (EscPressed==TRUE) {
          break;
        }
        EscPressed = TRUE;
      } else {
        EscPressed=FALSE;
      }
    }

  }


  if (AutoJudge (5, TRUE, L"\r\nEcho correct?\r\n")==TRUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInInterfaceTestAssertionGuid010,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke - ReadKeyStroke() with key input, user's view",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_IN_PROTOCOL.WaitForKey() Interface Test.
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
BBTestWaitForKeyFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_IN_PROTOCOL          *SimpleIn;


  EFI_TEST_ASSERTION                   AssertionType;
  EFI_INPUT_KEY                        Key;


  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

 // BOOLEAN                              KeyPressed=FALSE, EscPressed=FALSE;
    UINTN                                WaitIndex;


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

  SimpleIn = (EFI_SIMPLE_TEXT_IN_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Simple_Text_In_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextIn (SimpleIn, &DevicePath, StandardLib);
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
      DevicePathStr=NULL;
    }
  } else {
    //
    // Console Splitter/StdErr
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/TxtIn"
                   );
  }

  //
  // wait for times
  //
  SctPrint (L"\r\nWaitForKey Function Test Start!\r\n");
  WaitTimeOrKey (5);

  Status = SimpleIn->Reset (SimpleIn, TRUE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset with ExtendedVerification as TRUE",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  //
  // Assertion Point 4.1.4.2.1
  // WaitForKey()
  //
  SctPrint (L"Press ONE displayable key! and NO More!");

  //
  // WaitForKey event
  //
  Status = gtBS->WaitForEvent (1, &(SimpleIn->WaitForKey), &WaitIndex);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInInterfaceTestAssertionGuid011,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.WaitForKey - Wait for event with key input",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );


  //
  // Call ReadKeyStroke repeatedly to receive the character.
  //
  Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInInterfaceTestAssertionGuid014,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke - ReadKeyStroke() with key input",
                 L"%a:%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
