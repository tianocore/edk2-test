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

  SimplePointerBBTestStress.c

Abstract:

  Extensive Test Cases of Simple Pointer Protocol

--*/


#include "SctLib.h"
#include "SimplePointerBBTestMain.h"


/**
 *  Entrypoint for EFI_SIMPLE_POINTER_PROTOCOL.Reset() Clearance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3.1
//
EFI_STATUS
EFIAPI
BBTestResetClearanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_POINTER_PROTOCOL          *SimplePointer;


  EFI_TEST_ASSERTION                   AssertionType;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_SIMPLE_POINTER_STATE             State;
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

  SimplePointer = (EFI_SIMPLE_POINTER_PROTOCOL *)ClientInterface;


  //
  // Get Device Path of current Simple_Pointer_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimplePointer (SimplePointer, &DevicePath, StandardLib);
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
    // Console Splitter/SimplePointer
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/SimplePointer"
                   );
  }

  SctPrint (L"\r\nReset Clearence Test Start!\r\n");
  WaitTimeOrKey (5);


  //
  // Assertion Point 4.3.1.2.1
  // Reset() without Extended Verification should clears any pending pointer actions
  //

  //
  // Call Reset() with ExtendedVerification being FALSE
  //
  Status = SimplePointer->Reset (SimplePointer, FALSE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerExtensiveTestAssertionGuid001,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call CheckEvent() on the WaitForInput event, should return EFI_NOT_READY
  //
  Status = gtBS->CheckEvent (SimplePointer->WaitForInput);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerExtensiveTestAssertionGuid002,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - CheckEvent on WaitForInput after Reset with FALSE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_READY
                 );


  //
  // Prompt user to input from pointer device
  //
  SctPrint (L"\r\nPlease move the mouse or press some button!\r\n");
  gtBS->Stall (5000000);

  //
  // Call WaitForEvent to test whether user had input
  //
  Status = gtBS->WaitForEvent (1, &(SimplePointer->WaitForInput), &WaitIndex);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"BS.WaitForEvent() - Error ",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Call Reset() with ExtendedVerification as FALSE;
  //
  Status = SimplePointer->Reset (SimplePointer, FALSE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerExtensiveTestAssertionGuid004,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call CheckEvent on the WaitForInput Event
  //

  Status = gtBS->CheckEvent (SimplePointer->WaitForInput);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerExtensiveTestAssertionGuid005,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - CheckEvent after Reset with ExtendedVerification being FALSE, Clear WaitForEvent",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status ,
                 EFI_NOT_READY
                 );


  //
  // Call GetState to verify pointer state;
  //
  Status = SimplePointer->GetState (SimplePointer, &State);
  if (Status==EFI_SUCCESS) {
    //
    // State should indicate that pointer device keep silent
    //
    if (PointerKeepSilent (SimplePointer->Mode, &State) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimplePointerExtensiveTestAssertionGuid006,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE, Pointer state check",
                   L"%a:%d, Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   SimplePointer->Mode->ResolutionX,
                   State.RelativeMovementX,
                   SimplePointer->Mode->ResolutionY,
                   State.RelativeMovementY,
                   SimplePointer->Mode->ResolutionZ,
                   State.RelativeMovementZ,
                   SimplePointer->Mode->LeftButton,
                   State.LeftButton,
                   SimplePointer->Mode->RightButton,
                   State.RightButton
                   );

  } else if (Status==EFI_NOT_READY) {
    //
    // This is expected status, no problem
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimplePointerExtensiveTestAssertionGuid007,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being FALSE",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Assertion Point 4.3.1.2.2
  // Reset() with Extended Verification should clears any pending pointer actions
  //

  //
  // Call Reset() with ExtendedVerification being TRUE
  //
  Status = SimplePointer->Reset (SimplePointer, TRUE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerBBTestStressAssertionGuid001,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call CheckEvent() on the WaitForInput event, should return EFI_NOT_READY
  //
  Status = gtBS->CheckEvent (SimplePointer->WaitForInput);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerBBTestStressAssertionGuid002,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - CheckEvent on WaitForInput after Reset with TRUE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_READY
                 );


  //
  // Prompt user to input from pointer device
  //
  SctPrint (L"\r\nPlease move mouse or press some button AGAIN!\r\n");
  gtBS->Stall (5000000);

  //
  // Call WaitForEvent to test whether user had input
  //
  Status = gtBS->WaitForEvent (1, &(SimplePointer->WaitForInput), &WaitIndex);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"BS.WaitForEvent() - Error ",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Call Reset() with ExtendedVerification as TRUE;
  //
  Status = SimplePointer->Reset (SimplePointer, TRUE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerBBTestStressAssertionGuid003,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call CheckEvent on the WaitForInput Event
  //

  Status = gtBS->CheckEvent (SimplePointer->WaitForInput);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerBBTestStressAssertionGuid004,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - CheckEvent after Reset with ExtendedVerification being TRUE, Clear WaitForEvent",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status ,
                 EFI_NOT_READY
                 );


  //
  // Call GetState to verify pointer state;
  //
  Status = SimplePointer->GetState (SimplePointer, &State);
  if (Status==EFI_SUCCESS) {
    //
    // State should indicate that pointer device keep silent
    //
    if (PointerKeepSilent (SimplePointer->Mode, &State) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimplePointerBBTestStressAssertionGuid005,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE, Pointer state check",
                   L"%a:%d, Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   SimplePointer->Mode->ResolutionX,
                   State.RelativeMovementX,
                   SimplePointer->Mode->ResolutionY,
                   State.RelativeMovementY,
                   SimplePointer->Mode->ResolutionZ,
                   State.RelativeMovementZ,
                   SimplePointer->Mode->LeftButton,
                   State.LeftButton,
                   SimplePointer->Mode->RightButton,
                   State.RightButton
                   );

  } else if (Status==EFI_NOT_READY) {
    //
    // This is expected status, no problem
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimplePointerBBTestStressAssertionGuid006,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being TRUE",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being FALSE",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_SIMPLE_POINTER_PROTOCOL.GetState() Extensive Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3.2
//
EFI_STATUS
EFIAPI
BBTestGetStateExtensiveManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_SIMPLE_POINTER_PROTOCOL          *SimplePointer;


  EFI_TEST_ASSERTION                   AssertionType;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_SIMPLE_POINTER_STATE             State;
  UINTN                                WaitIndex;
  INT32                                CurPosX, CurPosY;
  BOOLEAN                              ButtonDownL, ButtonDownR;


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

  SimplePointer = (EFI_SIMPLE_POINTER_PROTOCOL *)ClientInterface;


  //
  // Get Device Path of current Simple_Pointer_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromSimplePointer (SimplePointer, &DevicePath, StandardLib);
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
    // Console Splitter/SimplePointer
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/SimplePointer"
                   );
  }


  SctPrint (L"\r\nGetState Stress Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Call Reset () with ExtendedVerification being TRUE
  //
  Status = SimplePointer->Reset (SimplePointer, TRUE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );


  //
  // Prompt user to move or click pointer device continuously
  //
  SctPrint (L"\r\nMove or Click pointer device for test!!\r\nAny key to quit!\r\n");

  CurPosX = 0;
  CurPosY = 0;
  ButtonDownL = FALSE;
  ButtonDownR = FALSE;
  //
  // Capture mouse action continuously until key input
  //
  AssertionType = EFI_TEST_ASSERTION_PASSED;

  while (TRUE) {
    //
    // Wait until mouse action
    //
    Status = gtBS->WaitForEvent (1, &(SimplePointer->WaitForInput), &WaitIndex);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_SIMPLE_POINTER_PROTOCOL.WaitForInput() - WaitForEvent after WaitForInput is signaled",
                     L"%a:%d, Status = %r, Expected = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EFI_SUCCESS
                     );
    }

    //
    // Call GetState to retrieve the state of device
    //
    Status = SimplePointer->GetState (SimplePointer, &State);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      break;
    }


    if (PointerKeepSilent (SimplePointer->Mode, &State)==FALSE) {
      //
      // Output RelativeXYZ & CurPosXY
      //
      CurPosX += State.RelativeMovementX;
      CurPosY += State.RelativeMovementY;
      SctPrint (L"\r\nRelativeXYZ(%5d,%5d,%5d),CurPos(%5d,%5d)",
        State.RelativeMovementX,
        State.RelativeMovementY,
        State.RelativeMovementZ,
        CurPosX,
        CurPosY
        );
    }

    //
    // Left button state changed?
    //
    if (SimplePointer->Mode->LeftButton && State.LeftButton!=ButtonDownL) {
      ButtonDownL = State.LeftButton;
      if (ButtonDownL) {
        SctPrint (L"\r\nLeft button DOWN!");
      } else {
        SctPrint (L"\r\nLeft button UP!");
      }
    }

    //
    // Right button state changed?
    //
    if (SimplePointer->Mode->RightButton && State.RightButton!=ButtonDownR) {
      ButtonDownR = State.RightButton;
      if (ButtonDownR) {
        SctPrint (L"\r\nRight button DOWN!");
      } else {
        SctPrint (L"\r\nRight button UP!");
      }
    }


    //
    // If any key input, then quit the test
    //
    Status = gtBS->CheckEvent (gtST->ConIn->WaitForKey);
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerExtensiveTestAssertionGuid011,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after mouse moved or button state changed",
                 L"%a:%d, Status = %r,expected -%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );
  //
  // User's view.
  //

  if (AutoJudge (5, TRUE, L"\r\nThe state reflect mouse action correctly?\r\n")==TRUE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerExtensiveTestAssertionGuid012,
                 L"EFI_SIMPLE_TEXT_POINTER_PROTOCOL.GetState() - Extensive test",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  return EFI_SUCCESS;
}


