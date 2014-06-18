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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    SimpleTextInputExBBTestConformance.c

Abstract:
    for EFI Driver Simple Text Input Ex Protocol's conformance Test

--*/
#include "SctLib.h"
#include "SimpleTextInputExBBTestMain.h"


EFI_STATUS
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
                   &StandardLib
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
                   &StandardLib
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
                   &StandardLib
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
                   &StandardLib
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
BBTestReadKeyStrokeExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

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
  Status = SimpleTextInputEx->ReadKeyStrokeEx (
                          SimpleTextInputEx,
                          NULL
                          );
  
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
BBTestReadKeyStrokeExConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;

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
  Status = SimpleTextInputEx->ReadKeyStrokeEx (
                          SimpleTextInputEx,
                          &Key
                          );
  
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
BBTestSetStateConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  //
  //Call SetState with KeyToggleState being NULL
  //
  Status = SimpleTextInputEx-> SetState (
                        SimpleTextInputEx,
                        NULL
                        );
  
  if ( EFI_INVALID_PARAMETER != Status) {
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
BBTestSetStateConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 Index;
  
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
    Status = SimpleTextInputEx->SetState (
                            SimpleTextInputEx,
                            UnsupportedState+Index
                            );
  
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
BBTestRegisterKeyNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  VOID                  *NotifyHandle;


  //
  //Call RegisterKeyNotify with KeyData being NULL
  //
  Status = SimpleTextInputEx-> RegisterKeyNotify (
                        SimpleTextInputEx,
                        NULL,
                        TestRegisterNotifyFunction,
                        &NotifyHandle
                        );
  
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
BBTestRegisterKeyNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  VOID                  *NotifyHandle;

  Key.Key.UnicodeChar = 'R';
  Key.Key.ScanCode = 0X00;

  //
  //Call RegisterKeyNotify with KeyNotificationFunction being NULL
  //
  Status = SimpleTextInputEx-> RegisterKeyNotify (
                        SimpleTextInputEx,
                        &Key,
                        NULL,
                        &NotifyHandle
                        );
  
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
BBTestRegisterKeyNotifyConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;

  Key.Key.UnicodeChar = 'R';
  Key.Key.ScanCode = 0X00;

  //
  //Call RegisterKeyNotify with NotifyHandle being NULL
  //
  Status = SimpleTextInputEx-> RegisterKeyNotify (
                        SimpleTextInputEx,
                        &Key,
                        TestRegisterNotifyFunction,
                        NULL
                        );
  
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
BBTestUnregisterKeyNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  //
  //Call UnregisterKeyNotify with NotifyHandle being NULL
  //
  Status = SimpleTextInputEx-> UnregisterKeyNotify (
                        SimpleTextInputEx,
                        NULL
                        );
  
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
BBTestUnregisterKeyNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL          *SimpleTextInputEx
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_KEY_DATA          Key;
  VOID                  *NotifyHandle;

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
  Status = SimpleTextInputEx-> UnregisterKeyNotify (
                        SimpleTextInputEx,
                        NotifyHandle
                        );
  
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
  Status = SimpleTextInputEx-> UnregisterKeyNotify (
                        SimpleTextInputEx,
                        InvalidNotifyHandle
                        );
  
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