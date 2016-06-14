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
    Status = SimpleIn->Reset (SimpleIn, FALSE);
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
   //
   //Auto test, after reset(), no key input, ReadKeyStroke() should return EFI_NOT_READY
   //
   Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);

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
                   gSimpleTextInInterfaceTestAssertionGuid002,
                   L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as TRUE",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
   //
   //Auto test, after reset(), no key input, ReadKeyStroke() should return EFI_NOT_READY
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
                  gSimpleTextInInterfaceTestAssertionGuid013,
                  L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset() with ExtendedVerification as TRUE, ReadKeyStroke() verification with no key input",
                  L"%a:%d: Status = %r, Expected = %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status,
                  EFI_NOT_READY
                  );
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
                   L"EFI_SIMPLE_TEXT_IN_PROTOCOL.Reset - Reset with ExtendedVeirification as TRUE",
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
