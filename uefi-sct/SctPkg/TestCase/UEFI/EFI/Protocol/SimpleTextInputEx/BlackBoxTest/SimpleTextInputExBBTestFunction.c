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
    SimpleTextInputExBBTestFunction.c

Abstract:
    for EFI Driver Simple Text Input Ex Protocol's function Test

--*/

#include "SimpleTextInputExBBTestMain.h"

#define REPEAT_RESET    5

#define VALIDSTATENUM_READKEYTEST    7

//
//Test Cases
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
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *SimpleTextInputEx;
  
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // init
  //
  SimpleTextInputEx = (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*)ClientInterface;

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
  // Get Device Path of current Simple_Text_Input_Ex_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextInputEx (SimpleTextInputEx, &DevicePath, StandardLib);
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
      if (EFI_ERROR(Status))
        return Status;
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
  //Call check points
  //
  BBTestResetFunctionAutoTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestResetFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *SimpleTextInputEx;
  
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // init
  //
  SimpleTextInputEx = (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*)ClientInterface;

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
  // Get Device Path of current Simple_Text_Input_Ex_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextInputEx (SimpleTextInputEx, &DevicePath, StandardLib);
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
      if (EFI_ERROR(Status))
        return Status;
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
  //Call check points
  //
  BBTestResetFunctionManualTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *SimpleTextInputEx;
  
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // init
  //
  SimpleTextInputEx = (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*)ClientInterface;

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
  // Get Device Path of current Simple_Text_Input_Ex_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextInputEx (SimpleTextInputEx, &DevicePath, StandardLib);
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
      if (EFI_ERROR(Status))
        return Status;
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
  //
  //
  BBTestReadKeyStrokeExFunctionManualTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetStateFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *SimpleTextInputEx;
  
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr = NULL;

  //
  // init
  //
  SimpleTextInputEx = (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*)ClientInterface;

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
  // Get Device Path of current Simple_Text_Input_Ex_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextInputEx (SimpleTextInputEx, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      if ( DevicePathStr && IsATerminalDevice(DevicePathStr) ) {
        Status = gtBS->FreePool (DevicePathStr);
        return Status;
      }
	  BBTestSetStateFunctionManualTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status))
        return Status;
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
    BBTestSetStateFunctionManualTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
	
  }
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *SimpleTextInputEx;
  
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // init
  //
  SimpleTextInputEx = (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*)ClientInterface;

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
  // Get Device Path of current Simple_Text_Input_Ex_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextInputEx (SimpleTextInputEx, &DevicePath, StandardLib);
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
      if (EFI_ERROR(Status))
        return Status;
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
  //Call check points
  //
  BBTestRegisterKeyNotifyFunctionManualTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *SimpleTextInputEx;
  
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // init
  //
  SimpleTextInputEx = (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*)ClientInterface;

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
  // Get Device Path of current Simple_Text_Input_Ex_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextInputEx (SimpleTextInputEx, &DevicePath, StandardLib);
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
      if (EFI_ERROR(Status))
        return Status;
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
  //Call check points
  //
  BBTestUnregisterKeyNotifyFunctionManualTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL     *SimpleTextInputEx;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // init
  //
  SimpleTextInputEx = (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*)ClientInterface;

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
  // Get Device Path of current Simple_Text_Input_Ex_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimpleTextInputEx (SimpleTextInputEx, &DevicePath, StandardLib);
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
      if (EFI_ERROR(Status))
        return Status;
      DevicePathStr=NULL;
    }
  } else {
    //
    // Console Splitter/StdErr
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   L"ConsoleSplitter/TxtIn"
                   );
  }

  //
  // Call check point
  //
  BBTestReadKeyStrokeExFunctionAutoTestCheckpoint1 ( StandardLib, SimpleTextInputEx );

  return EFI_SUCCESS;
}



//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestResetFunctionAutoTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            ResetStatus;
  EFI_STATUS            ReadKeyStatus;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  UINTN                 ExtendedIndex;
  EFI_KEY_DATA          Key;
  EFI_TPL               OldTpl;
  
  BOOLEAN               ExtendedVerification[] = {
                          TRUE,
                          FALSE
                        };

  ResetStatus = EFI_SUCCESS;
  ReadKeyStatus = EFI_NOT_READY;

  //
  // Call Reset with ExtendedVerification being TRUE or FALSE
  //
  for ( ExtendedIndex=0; ExtendedIndex<2; ExtendedIndex++ ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for ( Index=0; Index<REPEAT_RESET; Index++ ) {
      //
      //Call Reset to reset to console
      //
      OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
      gtBS->RestoreTPL (OldTpl);

      if (OldTpl <= TPL_APPLICATION) {
        if (OldTpl < TPL_APPLICATION) {
          OldTpl = gtBS->RaiseTPL (TPL_APPLICATION);
          ResetStatus = SimpleTextInputEx->Reset (
                                    SimpleTextInputEx,
                                    ExtendedVerification[ExtendedIndex]
                                    );
          gtBS->RestoreTPL (OldTpl);
        } else {
          ResetStatus = SimpleTextInputEx->Reset (
                                    SimpleTextInputEx,
                                    ExtendedVerification[ExtendedIndex]
                                    );
        }
      

        if ( EFI_SUCCESS != ResetStatus ) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
      
      //
      //Call ReadKeyStrokeEx to check if the console has been reset
      //
      OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
      gtBS->RestoreTPL (OldTpl);

      if (OldTpl <= TPL_APPLICATION) {
        if (OldTpl < TPL_APPLICATION) {
          OldTpl = gtBS->RaiseTPL (TPL_APPLICATION);
          ReadKeyStatus = SimpleTextInputEx->ReadKeyStrokeEx (
                                    SimpleTextInputEx,
                                    &Key
                                    );
          gtBS->RestoreTPL (OldTpl);
        } else {
          ReadKeyStatus = SimpleTextInputEx->ReadKeyStrokeEx (
                                    SimpleTextInputEx,
                                    &Key
                                    );
        }
      

        if ( EFI_NOT_READY != ReadKeyStatus ) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
    }
    
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInputExBBTestFunctionAssertionGuid001,
                 L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.Reset - Reset() returns EFI_SUCCESS and ReadKeyStrokeEx return EFI_NOT_READY.",
                 L"%a:%d: Reset Status - %r, ReadKeyStrokeEx Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 ResetStatus,
                 ReadKeyStatus
                 );
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestResetFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            ResetStatus;
  EFI_STATUS            ReadKeyStatus;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 ExtendedIndex;
  EFI_KEY_DATA          Key;
  UINTN                 WaitIndex;
  BOOLEAN               ExtendedVerification[] = {
                          TRUE,
                          FALSE
                        };


  ResetStatus = EFI_SUCCESS;
  ReadKeyStatus = EFI_NOT_READY;

  //
  // Call Reset with ExtendedVerification being TRUE or FALSE
  //
  for ( ExtendedIndex=0; ExtendedIndex<2; ExtendedIndex++) {

    ResetStatus = SimpleTextInputEx->Reset (
                                SimpleTextInputEx,
                                ExtendedVerification[ExtendedIndex]
                                );
    if ( EFI_ERROR( ResetStatus ) )
      return ResetStatus;

    //
    // Prompt tester to input some characters
    //
    SctPrint (L"Press some printable keys!");

    //
    // Wait for a input key
    //
    gtBS->WaitForEvent( 1, &(SimpleTextInputEx->WaitForKeyEx), &WaitIndex );

    //
    //Call Reset to reset to console
    //
    ResetStatus = SimpleTextInputEx->Reset (
                                SimpleTextInputEx,
                                ExtendedVerification[ExtendedIndex]
                                );
    if ( EFI_SUCCESS != ResetStatus ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    //Call ReadKeyStrokeEx to check if the console has been reset
    //
    if ( AssertionType == EFI_TEST_ASSERTION_PASSED ) {
      ReadKeyStatus = SimpleTextInputEx->ReadKeyStrokeEx (
                                    SimpleTextInputEx,
                                    &Key
                                    );
      if ( EFI_NOT_READY != ReadKeyStatus ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
    }

    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInputExBBTestFunctionAssertionGuid002,
                 L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.Reset - Reset() returns EFI_SUCCESS and ReadKeyStrokeEx return EFI_NOT_READY.",
                 L"%a:%d: Reset Status - %r, ReadKeyStrokeEx Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 ResetStatus,
                 ReadKeyStatus
                 );
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  BOOLEAN               KeyPressed=FALSE, EscPressed=FALSE;
  
 
  //
  //Reset the console
  //
  Status = SimpleTextInputEx->Reset( SimpleTextInputEx, FALSE );
  if ( EFI_ERROR(Status) )
    return Status;
    
  //
  //Prompt the tester to start the test
  //
  SctPrint(L"\r\nPress any key and wait for echo. Two ESC keys to quit.");
  while (TRUE) {
    KeyPressed = WaitTimeOrKey( SimpleTextInputEx, 1 );

    if ( KeyPressed==TRUE ) {
      SctPrint( L"\r\nKey Pressed--" );

      //
      // Call ReadKeyStroke to retrieve the key
      //
      Status = SimpleTextInputEx->ReadKeyStrokeEx( SimpleTextInputEx, &Key );
      if ( EFI_ERROR(Status) ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleTextInputExBBTestFunctionAssertionGuid003,
                       L"EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStroke - ReadKeyStroke()  return EFI_SUCCESS with key input",
                       L"%a:%d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }

      //
      // Output what user input
      //
      if (Key.Key.ScanCode==0) {
        //
        // Unicode character
        //
        SctAPrint( (char*)(&Key.Key.UnicodeChar) );
      } else {
        //
        // Scan code character
        //
        SctPrint( ScanCodeDesc( Key.Key.ScanCode ) );
      }
      //
      // Output the KeyState
      //
      KeyStatePrint( Key.KeyState );

      if (Key.Key.ScanCode==TEST_SCAN_ESC) {
        if (EscPressed==TRUE) {
          break;
        }
        EscPressed = TRUE;
      } else {
        EscPressed = FALSE;
      }
    }

  }


  if (AutoJudge (SimpleTextInputEx, 5, TRUE, L"\r\nEcho correct?\r\n")==TRUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInputExBBTestFunctionAssertionGuid004,
                 L"EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStroke - ReadKeyStroke() with key input, user's view",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  return EFI_SUCCESS;
 
}


EFI_STATUS
EFIAPI
BBTestSetStateFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  UINTN                 WaitIndex;
  EFI_KEY_DATA          Key;
  
  EFI_KEY_TOGGLE_STATE  ValidState[] = {
                          EFI_TOGGLE_STATE_VALID,
                          EFI_TOGGLE_STATE_VALID | EFI_SCROLL_LOCK_ACTIVE,
                          EFI_TOGGLE_STATE_VALID | EFI_NUM_LOCK_ACTIVE,
                          EFI_TOGGLE_STATE_VALID | EFI_CAPS_LOCK_ACTIVE,
                          EFI_TOGGLE_STATE_VALID | EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE,
                          EFI_TOGGLE_STATE_VALID | EFI_SCROLL_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE,
                          EFI_TOGGLE_STATE_VALID | EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE,
                          EFI_TOGGLE_STATE_VALID | EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE,
                          //EFI_TOGGLE_STATE_VALID | EFI_TOGGLE_UNSUPPORTED1,
                          //EFI_TOGGLE_STATE_VALID | EFI_TOGGLE_UNSUPPORTED2,
                          //EFI_TOGGLE_STATE_VALID | EFI_TOGGLE_UNSUPPORTED3,
                          0
                          };

  //
  //Call SetState with KeyToggleState being valid state
  //
  for ( Index=0; ValidState[Index]; Index++ ) {
    Status = SimpleTextInputEx-> SetState (
                            SimpleTextInputEx,
                            ValidState+Index
                            );
  
    if ( EFI_UNSUPPORTED != Status && EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
        StandardLib,
        AssertionType,
        gSimpleTextInputExBBTestFunctionAssertionGuid005,
        L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.SetState - SetState() returns EFI_UNSUPPORTED or EFI_SUCCESS with a valid bit set.",
        L"%a:%d: Status - %r",
        __FILE__,
        (UINTN)__LINE__,
        Status
        );
    } else {
      Key.KeyState.KeyToggleState = 0;
      if ( EFI_SUCCESS == Status ) {
        SimpleTextInputEx->Reset( SimpleTextInputEx, FALSE );
        Status = SimpleTextInputEx-> SetState (
                                       SimpleTextInputEx,
                                       ValidState+Index
                                       );		
        SctPrint( L"Please press a printable key." );
        gtBS->WaitForEvent( 1, &(SimpleTextInputEx->WaitForKeyEx), &WaitIndex );
        Status = SimpleTextInputEx->ReadKeyStrokeEx( SimpleTextInputEx, &Key );
        if ( EFI_ERROR(Status) )
          return Status;
        if ( Key.KeyState.KeyToggleState != ValidState[Index] ) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }
      } else {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      }
      StandardLib->RecordAssertion (
        StandardLib,
        AssertionType,
        gSimpleTextInputExBBTestFunctionAssertionGuid005,
        L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.SetState - SetState() returns EFI_UNSUPPORTED or EFI_SUCCESS with a valid bit set and the KeyToggleState has been set right.",
        L"%a:%d: Status - %r SetState - %d ReadKeyState - %d",
        __FILE__,
        (UINTN)__LINE__,
        Status,
        ValidState[Index],
        Key.KeyState.KeyToggleState
        );
    }

  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  EFI_KEY_DATA          RegisterKey;
  VOID                  *NotifyHandle;
  UINTN                 WaitIndex;

  //
  //Reset the console
  //
  Status = SimpleTextInputEx->Reset( SimpleTextInputEx, FALSE );
  if ( EFI_ERROR(Status) )
    return Status;

  //Read the input key used to register the notify function
  SctPrint( L"\r\nPress one key to register the notify function." );
  gtBS->WaitForEvent( 1, &(SimpleTextInputEx->WaitForKeyEx), &WaitIndex );
  Status = SimpleTextInputEx->ReadKeyStrokeEx( SimpleTextInputEx, &RegisterKey );
  if ( EFI_ERROR(Status) )
    return Status;
  
  //
  //Call RegisterKeyNotify to register a notify function
  //
  Status = SimpleTextInputEx->RegisterKeyNotify(
                          SimpleTextInputEx,
                          &RegisterKey,
                          FunctionTestNotifyFunction,
                          &NotifyHandle
                          );
  if ( EFI_SUCCESS != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion(
             StandardLib,
             AssertionType,
             gSimpleTextInputExBBTestFunctionAssertionGuid006,
             L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify - RegisterKeyNotify() returns EFI_SUCCESS.",
             L"%a:%d: Status - %r",
             __FILE__,
             (UINTN)__LINE__,
             Status
             );
    return EFI_SUCCESS;
  }

  BeenExecuted = FALSE;
  //
  //Prompt the teseter to input the specific key to register the notify function
  //
  while ( TRUE ) {
    //
    //Reset the console
    //
    Status = SimpleTextInputEx->Reset( SimpleTextInputEx, FALSE );
    if ( EFI_ERROR(Status) )
      return Status;
      
    SctPrint(L"\r\nPress the same key you used to register the notify function.");
    gtBS->WaitForEvent( 1, &(SimpleTextInputEx->WaitForKeyEx), &WaitIndex );
  
    //
    //Check the input key
    //
    Status = SimpleTextInputEx->ReadKeyStrokeEx( SimpleTextInputEx, &Key );
    if ( EFI_SUCCESS != Status )
      return Status;
    if ( (Key.Key.UnicodeChar == RegisterKey.Key.UnicodeChar) && 
         (Key.Key.ScanCode == RegisterKey.Key.ScanCode) &&
         (Key.KeyState.KeyShiftState == RegisterKey.KeyState.KeyShiftState) && 
         (Key.KeyState.KeyToggleState == RegisterKey.KeyState.KeyToggleState) ) {
      break;
    }
    SctPrint( L"\r\nThe key pressed not match the registed key!" );
  }

  //
  //Check if the notify function has been invoked
  //
  if ( TRUE != BeenExecuted ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestFunctionAssertionGuid007,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify - RegisterKeyNotify() returns EFI_SUCCESS and notify function has been invoked.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  Status = SimpleTextInputEx->UnregisterKeyNotify( SimpleTextInputEx, NotifyHandle );
  if ( EFI_ERROR(Status) )
    return Status;

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyFunctionManualTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  EFI_KEY_DATA          RegisterKey;
  VOID                  *NotifyHandle;
  UINTN                 WaitIndex;

  //AssertionType = EFI_TEST_ASSERTION_PASSED;
  
  //
  //Reset the console
  //
  Status = SimpleTextInputEx->Reset( SimpleTextInputEx, FALSE );
  if ( EFI_ERROR(Status) )
    return Status;

  //Read the input key used to register the notify function
  SctPrint( L"\r\nPress one key to register the notify function." );
  gtBS->WaitForEvent( 1, &(SimpleTextInputEx->WaitForKeyEx), &WaitIndex );
  Status = SimpleTextInputEx->ReadKeyStrokeEx( SimpleTextInputEx, &RegisterKey );
  if ( EFI_ERROR(Status) )
    return Status;

  //
  //Call RegisterKeyNotify to register a notify function
  //
  Status = SimpleTextInputEx->RegisterKeyNotify(
                          SimpleTextInputEx,
                          &RegisterKey,
                          FunctionTestNotifyFunction,
                          &NotifyHandle
                          );
  if ( EFI_ERROR(Status) )
    return Status;

  //
  //Call UnregisterKeyNotify to unregister the registed notify function
  //
  Status = SimpleTextInputEx->UnregisterKeyNotify(
                          SimpleTextInputEx,
                          NotifyHandle
                          );
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gSimpleTextInputExBBTestFunctionAssertionGuid008,
             L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify - UnregisterKeyNotify() returns EFI_SUCCESS.",
             L"%a:%d: Status - %r",
             __FILE__,
             (UINTN)__LINE__,
             Status
             );
    return EFI_SUCCESS;
  }

  BeenExecuted = FALSE;

   //
  //Prompt the teseter to input the specific key to register the notify function
  //
  while ( TRUE ) {
    //
    //Reset the console
    //
    Status = SimpleTextInputEx->Reset( SimpleTextInputEx, FALSE );
    if ( EFI_ERROR(Status) )
      return Status;
      
    SctPrint(L"\r\nPress the same key you used to register the notify function.");
    gtBS->WaitForEvent( 1, &(SimpleTextInputEx->WaitForKeyEx), &WaitIndex );
  
    //
    //Check the input key
    //
    Status = SimpleTextInputEx->ReadKeyStrokeEx( SimpleTextInputEx, &Key );
    if ( EFI_SUCCESS != Status )
      return Status;
    if ( (Key.Key.UnicodeChar == RegisterKey.Key.UnicodeChar) && 
         (Key.Key.ScanCode == RegisterKey.Key.ScanCode) &&
         (Key.KeyState.KeyShiftState == RegisterKey.KeyState.KeyShiftState) && 
         (Key.KeyState.KeyToggleState == RegisterKey.KeyState.KeyToggleState) ) {
      break;
    }
    SctPrint( L"\r\nThe key pressed not match the registed key!" );
  }

  //
  //Check if the notify function has not been invoked
  //
  if ( FALSE != BeenExecuted ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestFunctionAssertionGuid009,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify - UnregisterKeyNotify() returns EFI_SUCCESS and notify function has not been invoked.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExFunctionAutoTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  UINT8                 Index;
  EFI_KEY_TOGGLE_STATE  State;
  EFI_KEY_TOGGLE_STATE  ValidState[VALIDSTATENUM_READKEYTEST];

  State = EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED;

  ValidState[0] = EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED | EFI_SCROLL_LOCK_ACTIVE;
  ValidState[1] = EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED | EFI_NUM_LOCK_ACTIVE;
  ValidState[2] = EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED | EFI_CAPS_LOCK_ACTIVE;
  ValidState[3] = EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED | EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE;
  ValidState[4] = EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED | EFI_SCROLL_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE;
  ValidState[5] = EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED | EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE;
  ValidState[6] = EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED | EFI_SCROLL_LOCK_ACTIVE |EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE;

  //
  //Read next keystroke from the input device
  //
  Status = SimpleTextInputEx->ReadKeyStrokeEx (
                                SimpleTextInputEx,
                                &Key
                                );
  if ((Status != EFI_SUCCESS) && (Status != EFI_NOT_READY)) {
    return Status;
  }

  if ((Key.KeyState.KeyToggleState & EFI_TOGGLE_STATE_VALID) == 0) {
    return EFI_UNSUPPORTED;
  }

  //
  //Set the KEY_STATE_EXPOSED to check the imcomplete keystroke support
  //
  Status = SimpleTextInputEx->SetState (
                                SimpleTextInputEx,
                                &State
                                );
  if (Status == EFI_UNSUPPORTED) {
    return EFI_UNSUPPORTED;
  }

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.SetState - SetState() doesn't return EFI_SUCCESS with EFI_KEY_STATE_EXPOSED",
                   L"%a:%d, Status = %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  for (Index=0; Index<VALIDSTATENUM_READKEYTEST; Index++) {

    //
    // Set the valid KeyToggleState
    // With EFI_KEY_STATE_EXPOSED bit enabled
    //
    Status = SimpleTextInputEx->SetState (
                                  SimpleTextInputEx,
                                  ValidState + Index
                                  );

    if (Status != EFI_SUCCESS) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.SetState - SetState() doesn't return EFI_SUCCESS with the valid KeyToggleState",
                     L"%a:%d, Status = %r, KeyToggleState = %x\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ValidState[Index]
                     );
      continue;
    }

    //
    // Get the KeyToggleState, and return status should be EFI_NOT_READY.
    // the ReadKeyStrokeEx function will allow the return of
    // incomplete keystrokes such as there is no Key data.
    //
    Status = SimpleTextInputEx->ReadKeyStrokeEx (
                                  SimpleTextInputEx,
                                  &Key
                                  );

    if (Status != EFI_NOT_READY) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextInputExBBTestFunctionAssertionGuid010,
                     L"EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStrokeEx - ReadKeyStrokeEx() doesn't return EFI_NOT_READY when there is no Key data and EFI_KEY_STATE_EXPOSED is enabled",
                     L"%a:%d, Status = %r, Index = %d, KeyToggleState = %x\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index,
                     ValidState[Index]
                     );

    } else {
      if ((Key.KeyState.KeyToggleState == ValidState[Index]) &&
        ((Key.KeyState.KeyShiftState == 0) || (Key.KeyState.KeyShiftState == EFI_SHIFT_STATE_VALID)) &&
        ((Key.Key.ScanCode == 0) && (Key.Key.UnicodeChar == 0))) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleTextInputExBBTestFunctionAssertionGuid011,
                     L"EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStrokeEx - ReadKeyStrokeEx() should get the ValidState with EFI_NOT_READY and other field is zero",
                     L"%a:%d, Status = %r, Index = %d, KeyToggleState = %x, expect State = %x\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index,
                     Key.KeyState.KeyToggleState,
                     ValidState[Index]
                     );

    }
  }

  return EFI_SUCCESS;
}
