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

  SimpleTextInBBTestConformance.c

Abstract:

  Conformance Test Cases of Simple Input Protocol

--*/


#include "SimpleTextInBBTestMain.h"


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.1
//
EFI_STATUS
BBTestReadKeyStrokeConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_TEXT_IN_PROTOCOL          *SimpleIn;

  UINTN                                Index;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_INPUT_KEY                        Key;
  CHAR16                               KeyBuffer[MAX_KEY_BUFFER_SIZE];

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
  SctPrint (L"\r\nReadKeyStroke Conformance Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 4.2.1.2.1
  // ReadKeyStroke()
  //

  //
  // Call Reset with ExtendedVerification as TRUE
  //
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
  // Call ReadKeyStroke() for 10 times
  //
  for (Index=0; Index<10; Index++) {
    Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
    if (Status!=EFI_NOT_READY) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextInConformanceTestAssertionGuid002,
                   L"EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke - ReadKeyStroke() when no key input",
                   L"%a:%d, Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_NOT_READY
                   );
  }

  //
  // Call Reset with ExtendedVerification as TRUE
  //
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
  // Prompt tester to input a large number of characters
  //
  SctPrint (L"\r\nPlease input some displayabed characters in 5 seconds\r\n");

  gtBS->Stall (5000000);

  //
  // Assume user has input some key, go on verification
  // Read all key
  //
  Index=0;
  do {
    Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
    if (Status==EFI_SUCCESS) {
      KeyBuffer[Index++]=Key.UnicodeChar;
    }

  } while (Status==EFI_SUCCESS && Index<MAX_KEY_BUFFER_SIZE);

  //
  // Echo the input keys
  //
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleTextInConformanceTestAssertionGuid003,
                   L"EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke - ReadKeyStroke() when no key input",
                   L"%a:%d, Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_NOT_READY
                   );
  }

  KeyBuffer[Index]=0;

  SctPrint (L"The keys input are:%s", KeyBuffer);

  //
  // Let's do it again
  //
  if (AutoJudge (5, TRUE, L"\r\nEcho correct?\r\n")==TRUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInConformanceTestAssertionGuid004,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.ReadKeyStroke - ReadKeyStroke() with key input, user's view",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  //
  // Just clear key buffer
  //

  Index=0;
  do {
    Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
    if (Status==EFI_SUCCESS) {
      KeyBuffer[Index++]=Key.UnicodeChar;
    }

  } while (Status==EFI_SUCCESS && Index<MAX_KEY_BUFFER_SIZE);

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_SIMPLE_TEXT_IN_PROTOCOL.WaitForKey() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.2
//
EFI_STATUS
BBTestWaitForKeyConformanceManualTest (
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
  SctPrint (L"\r\nWaitForKey Conformance Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 4.2.2.2.1
  // ReadKeyStroke()
  //

  //
  // Call Reset with ExtendedVerification as TRUE
  //
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
  // Call CheckEvent() on the WaitForKey event
  //
  Status = gtBS->CheckEvent (SimpleIn->WaitForKey);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInConformanceTestAssertionGuid007,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.WaitForKey - Event check before key input",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_READY
                 );

  //
  // Prompt tester to input some character
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
                 gSimpleTextInConformanceTestAssertionGuid008,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.WaitForKey - Wait for event with key input",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );


  SctPrint (L"\r\nThe key(s) input:");
  //
  // Call ReadKeyStroke repeatedly to receive the character.
  //
  while (TRUE) {
    //
    // Call ReadKeyStroke to retrieve the key
    //
    Status = SimpleIn->ReadKeyStroke (SimpleIn, &Key);
    if (EFI_ERROR(Status)) {
      break;
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
  }

  //
  // Wait 2 second for user to check the key echoed.
  //
  gtBS->Stall (2000000);

  //
  // Call CheckEvent() on the WaitForKey event
  //
  Status = gtBS->CheckEvent (SimpleIn->WaitForKey);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleTextInConformanceTestAssertionGuid010,
                 L"EFI_SIMPLE_TEXT_IN_PROTOCOL.WaitForKey - Event check after key read stroken",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_READY
                 );

  return EFI_SUCCESS;
}

