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
    SimpleTextInputExBBTestConformance.c

Abstract:
    for EFI Driver Simple Text Input Ex Protocol's conformance Test

--*/

#include "SimpleTextInputExBBTestMain.h"


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExConformanceTest (
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
  BBTestReadKeyStrokeExConformanceTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
  
  BBTestReadKeyStrokeExConformanceTestCheckpoint2 ( StandardLib, SimpleTextInputEx );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetStateConformanceTest (
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
  TYPE_OF_TERMINAL                     Termi;
  UINTN                                Com;

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
      BBTestSetStateConformanceTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
      
      if ( DevicePathStr && IsTerminalDevicePath(DevicePath, &Termi, &Com) ){
        Status = gtBS->FreePool (DevicePathStr);
        return Status;
      }
      BBTestSetStateConformanceTestCheckpoint2 ( StandardLib, SimpleTextInputEx );
	  
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
    BBTestSetStateConformanceTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
  
    BBTestSetStateConformanceTestCheckpoint2 ( StandardLib, SimpleTextInputEx );
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyConformanceTest (
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
  BBTestRegisterKeyNotifyConformanceTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
  
  BBTestRegisterKeyNotifyConformanceTestCheckpoint2 ( StandardLib, SimpleTextInputEx );

  BBTestRegisterKeyNotifyConformanceTestCheckpoint3 ( StandardLib, SimpleTextInputEx );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyConformanceTest (
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
  BBTestUnregisterKeyNotifyConformanceTestCheckpoint1 ( StandardLib, SimpleTextInputEx );
  
  BBTestUnregisterKeyNotifyConformanceTestCheckpoint2 ( StandardLib, SimpleTextInputEx );

  BBTestUnregisterKeyNotifyConformanceTestCheckpoint3 ( StandardLib, SimpleTextInputEx );

  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_TPL               OldTpl;

  //
  //Call Reset to reset to console
  //
  Status = SimpleTextInputEx->Reset ( SimpleTextInputEx, FALSE );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call ReadKeyStrokeEx with KeyData being NULL
  //
  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  gtBS->RestoreTPL (OldTpl);

  if (OldTpl <= TPL_APPLICATION) {
    if (OldTpl < TPL_APPLICATION) {
      OldTpl = gtBS->RaiseTPL (TPL_APPLICATION);
      Status = SimpleTextInputEx->ReadKeyStrokeEx (
                          SimpleTextInputEx,
                          NULL
                          );
      gtBS->RestoreTPL (OldTpl);
    } else {
      Status = SimpleTextInputEx->ReadKeyStrokeEx (
                          SimpleTextInputEx,
                          NULL
                          );
    }
  }

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestConformanceAssertionGuid001 ,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStorkeEx - ReadKeyStorkeEx() returns EFI_INVALID_PARAMETER with KeyData being NULL.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestReadKeyStrokeExConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  EFI_TPL               OldTpl;

  //
  //Call Reset to reset to console
  //
  Status = SimpleTextInputEx->Reset ( SimpleTextInputEx, FALSE );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call ReadKeyStrokeEx with console just been reseted
  //
  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  gtBS->RestoreTPL (OldTpl);

  if (OldTpl <= TPL_APPLICATION) {
    if (OldTpl < TPL_APPLICATION) {
      OldTpl = gtBS->RaiseTPL (TPL_APPLICATION);
      Status = SimpleTextInputEx->ReadKeyStrokeEx (
                          SimpleTextInputEx,
                          &Key
                          );
      gtBS->RestoreTPL (OldTpl);
    } else {
      Status = SimpleTextInputEx->ReadKeyStrokeEx (
                          SimpleTextInputEx,
                          &Key
                          );
    }
  }
  
  if ( EFI_NOT_READY != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestConformanceAssertionGuid002,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStorkeEx - ReadKeyStorkeEx() returns EFI_NOT_READY with console just been reseted.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetStateConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_TPL               OldTpl;

  //
  //Call SetState with KeyToggleState being NULL
  //

  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  gtBS->RestoreTPL (OldTpl);

  if (OldTpl <= TPL_CALLBACK) {
    if (OldTpl < TPL_CALLBACK) {
      OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);
      Status = SimpleTextInputEx->SetState (
                        SimpleTextInputEx,
                        NULL
                        );
      gtBS->RestoreTPL (OldTpl);
    } else {
      Status = SimpleTextInputEx->SetState (
                        SimpleTextInputEx,
                        NULL
                        );
    }
  }

  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else if (Status != EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestConformanceAssertionGuid003,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.SetState - SetState() returns EFI_INVALID_PARAMETER with KeyToggleState being NULL.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetStateConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  EFI_TPL               OldTpl;
  
  EFI_KEY_TOGGLE_STATE  UnsupportedState[] = {
                          EFI_SCROLL_LOCK_ACTIVE,
                          EFI_NUM_LOCK_ACTIVE,
                          EFI_CAPS_LOCK_ACTIVE,
                          EFI_KEY_STATE_EXPOSED,
                          EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE | EFI_KEY_STATE_EXPOSED,
                          EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE,
                          EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE | EFI_KEY_STATE_EXPOSED,
                          EFI_SCROLL_LOCK_ACTIVE | EFI_KEY_STATE_EXPOSED | EFI_CAPS_LOCK_ACTIVE,
                          EFI_KEY_STATE_EXPOSED  | EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE,
                          EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE,
                          EFI_SCROLL_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE,
                          EFI_SCROLL_LOCK_ACTIVE | EFI_KEY_STATE_EXPOSED,
                          EFI_NUM_LOCK_ACTIVE    | EFI_CAPS_LOCK_ACTIVE,
                          EFI_NUM_LOCK_ACTIVE    | EFI_KEY_STATE_EXPOSED,
                          EFI_CAPS_LOCK_ACTIVE   | EFI_KEY_STATE_EXPOSED,
                          0
                          };

  //
  //Call SetState with KeyToggleState being a unsupported bit set
  //
  for ( Index=0; UnsupportedState[Index]; Index++ ) {

    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);

    if (OldTpl <= TPL_CALLBACK) {
      if (OldTpl < TPL_CALLBACK) {
        OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);
        Status = SimpleTextInputEx->SetState (
                            SimpleTextInputEx,
                            UnsupportedState+Index
                            );
        gtBS->RestoreTPL (OldTpl);
      } else {
        Status = SimpleTextInputEx->SetState (
                            SimpleTextInputEx,
                            UnsupportedState+Index
                            );
      }
    }
  
    if ( EFI_UNSUPPORTED != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
            StandardLib,
            AssertionType,
            gSimpleTextInputExBBTestConformanceAssertionGuid004,
            L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.SetState - SetState() returns EFI_UNSUPPORTED with KeyToggleState being a unsupported bit set.",
            L"%a:%d: Status - %r",
            __FILE__,
            (UINTN)__LINE__,
            Status
            );
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  VOID                  *NotifyHandle;
  EFI_TPL               OldTpl;

  //
  //Call RegisterKeyNotify with KeyData being NULL
  //

  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  gtBS->RestoreTPL (OldTpl);

  if (OldTpl <= TPL_CALLBACK) {
    if (OldTpl < TPL_CALLBACK) {
      OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);
      Status = SimpleTextInputEx->RegisterKeyNotify (
                        SimpleTextInputEx,
                        NULL,
                        TestRegisterNotifyFunction,
                        &NotifyHandle
                        );
      gtBS->RestoreTPL (OldTpl);
    } else {
      Status = SimpleTextInputEx->RegisterKeyNotify (
                        SimpleTextInputEx,
                        NULL,
                        TestRegisterNotifyFunction,
                        &NotifyHandle
                        );
    }
  }

  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestConformanceAssertionGuid005 ,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify - RegisterKeyNotify() returns EFI_INVALID_PARAMETER with KeyData being NULL.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  VOID                  *NotifyHandle;
  EFI_TPL               OldTpl; 

  Key.Key.UnicodeChar = 'R';
  Key.Key.ScanCode = 0X00;

  //
  //Call RegisterKeyNotify with KeyNotificationFunction being NULL
  //

  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  gtBS->RestoreTPL (OldTpl);

  if (OldTpl <= TPL_CALLBACK) {
    if (OldTpl < TPL_CALLBACK) {
      OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);
      Status = SimpleTextInputEx-> RegisterKeyNotify (
                        SimpleTextInputEx,
                        &Key,
                        NULL,
                        &NotifyHandle
                        );
      gtBS->RestoreTPL (OldTpl);
    } else {
      Status = SimpleTextInputEx-> RegisterKeyNotify (
                        SimpleTextInputEx,
                        &Key,
                        NULL,
                        &NotifyHandle
                        );
    }
  }
  
  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestConformanceAssertionGuid006,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify - RegisterKeyNotify() returns EFI_INVALID_PARAMETER with KeyNotificationFunction being NULL.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRegisterKeyNotifyConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  EFI_TPL               OldTpl;

  Key.Key.UnicodeChar = 'R';
  Key.Key.ScanCode = 0X00;

  //
  //Call RegisterKeyNotify with NotifyHandle being NULL
  //
  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  gtBS->RestoreTPL (OldTpl);

  if (OldTpl <= TPL_CALLBACK) {
    if (OldTpl < TPL_CALLBACK) {
      OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);
      Status = SimpleTextInputEx-> RegisterKeyNotify (
                        SimpleTextInputEx,
                        &Key,
                        TestRegisterNotifyFunction,
                        NULL
                        );
      gtBS->RestoreTPL (OldTpl);
    } else {
      Status = SimpleTextInputEx-> RegisterKeyNotify (
                        SimpleTextInputEx,
                        &Key,
                        TestRegisterNotifyFunction,
                        NULL
                        );
    }
  }
  
  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestConformanceAssertionGuid007,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify - RegisterKeyNotify() returns EFI_INVALID_PARAMETER with NotifyHandle being NULL.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_TPL               OldTpl;

  //
  //Call UnregisterKeyNotify with NotifyHandle being NULL
  //
  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  gtBS->RestoreTPL (OldTpl);

  if (OldTpl <= TPL_CALLBACK) {
    if (OldTpl < TPL_CALLBACK) {
      OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);
      Status = SimpleTextInputEx-> UnregisterKeyNotify (
                        SimpleTextInputEx,
                        NULL
                        );
      gtBS->RestoreTPL (OldTpl);
    } else {
      Status = SimpleTextInputEx-> UnregisterKeyNotify (
                        SimpleTextInputEx,
                        NULL
                        );
    }
  }
  
  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestConformanceAssertionGuid008,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify - UnregisterKeyNotify() returns EFI_INVALID_PARAMETER with NotifyHandle being NULL.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  VOID                  *NotifyHandle;
  EFI_TPL               OldTpl;

  Key.Key.UnicodeChar = 'R';
  Key.Key.ScanCode = 0X00;

  //
  //Call RegisterKeyNotify to register a notify function
  //
  Status = SimpleTextInputEx-> RegisterKeyNotify (
                          SimpleTextInputEx,
                          &Key,
                          TestRegisterNotifyFunction,
                          &NotifyHandle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  //Call UnregisterKeyNotify to unregister the register notify function
  //
  Status = SimpleTextInputEx-> UnregisterKeyNotify (
                          SimpleTextInputEx,
                          NotifyHandle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call UnregisterKeyNotify with the invalid NotifyHandle
  //
  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  gtBS->RestoreTPL (OldTpl);

  if (OldTpl <= TPL_CALLBACK) {
    if (OldTpl < TPL_CALLBACK) {
      OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);
      Status = SimpleTextInputEx->UnregisterKeyNotify (
                        SimpleTextInputEx,
                        NotifyHandle
                        );
      gtBS->RestoreTPL (OldTpl);
    } else {
      Status = SimpleTextInputEx->UnregisterKeyNotify (
                        SimpleTextInputEx,
                        NotifyHandle
                        );
    }
  }

  //
  // Invalid Parameter or Not Found
  //
  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestConformanceAssertionGuid009,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify - UnregisterKeyNotify() returns EFI_INVALID_PARAMETER with NotifyHandle not refer to a register notify function anymore.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestUnregisterKeyNotifyConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  VOID                  *NotifyHandle;
  VOID                  *InvalidNotifyHandle;
  EFI_TPL               OldTpl;
  
  Key.Key.UnicodeChar = 'R';
  Key.Key.ScanCode = 0X00;

  //
  //Call RegisterKeyNotify to register a notify function
  //
  Status = SimpleTextInputEx-> RegisterKeyNotify (
                          SimpleTextInputEx,
                          &Key,
                          TestRegisterNotifyFunction,
                          &NotifyHandle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  //Create a NotifyHandle with a illegal format
  //
  InvalidNotifyHandle = (VOID *)((UINT8*)(&NotifyHandle) + 8);
  
  //
  //Call UnregisterKeyNotify to unregister the register notify function
  //
  Status = SimpleTextInputEx-> UnregisterKeyNotify (
                          SimpleTextInputEx,
                          NotifyHandle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call UnregisterKeyNotify with NotifyHandle with a illegal format
  //
  OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
  gtBS->RestoreTPL (OldTpl);

  if (OldTpl <= TPL_CALLBACK) {
    if (OldTpl < TPL_CALLBACK) {
      OldTpl = gtBS->RaiseTPL (TPL_CALLBACK);
      Status = SimpleTextInputEx-> UnregisterKeyNotify (
                        SimpleTextInputEx,
                        InvalidNotifyHandle
                        );
      gtBS->RestoreTPL (OldTpl);
    } else {
      Status = SimpleTextInputEx-> UnregisterKeyNotify (
                        SimpleTextInputEx,
                        InvalidNotifyHandle
                        );
    }
  }

  
  if ( EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
           StandardLib,
           AssertionType,
           gSimpleTextInputExBBTestConformanceAssertionGuid010,
           L"SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify - UnregisterKeyNotify() returns EFI_INVALID_PARAMETER with NotifyHandle being illegal format.",
           L"%a:%d: Status - %r",
           __FILE__,
           (UINTN)__LINE__,
           Status
           );

  return EFI_SUCCESS;
}
