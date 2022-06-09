/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Byosoft Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AbsolutePointerBBTestStress.c

Abstract:

  Extensive Test Cases of Absolute Pointer Protocol

--*/


#include "SctLib.h"
#include "AbsolutePointerBBTestMain.h"


/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() Clearance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 
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
  EFI_ABSOLUTE_POINTER_PROTOCOL          *AbsolutePointer;


  EFI_TEST_ASSERTION                   AssertionType;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_ABSOLUTE_POINTER_STATE            State;
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

  AbsolutePointer = (EFI_ABSOLUTE_POINTER_PROTOCOL *)ClientInterface;


  //
  // Get Device Path of current Absolute_Pointer_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromAbsolutePointer (AbsolutePointer, &DevicePath, StandardLib);
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
    // Console Splitter/AbsolutePointer
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/AbsolutePointer"
                   );
  }

  SctPrint (L"\r\nReset Clearence Test Start!\r\n");
  WaitTimeOrKey (5);


  //
  // Assertion Point
  // Reset() without Extended Verification should clears any pending pointer actions
  //

  //
  // Call Reset() with ExtendedVerification being FALSE
  //
  Status = AbsolutePointer->Reset (AbsolutePointer, FALSE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerExtensiveTestAssertionGuid001,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call CheckEvent() on the WaitForInput event, should return EFI_NOT_READY
  //
  Status = gtBS->CheckEvent (AbsolutePointer->WaitForInput);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerExtensiveTestAssertionGuid002,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - CheckEvent on WaitForInput after Reset with FALSE",
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
  Status = gtBS->WaitForEvent (1, &(AbsolutePointer->WaitForInput), &WaitIndex);
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
  Status = AbsolutePointer->Reset (AbsolutePointer, FALSE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerExtensiveTestAssertionGuid004,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call CheckEvent on the WaitForInput Event
  //

  Status = gtBS->CheckEvent (AbsolutePointer->WaitForInput);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerExtensiveTestAssertionGuid005,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - CheckEvent after Reset with ExtendedVerification being FALSE, Clear WaitForEvent",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status ,
                 EFI_NOT_READY
                 );


  //
  // Call GetState to verify pointer state;
  //
  Status = AbsolutePointer->GetState (AbsolutePointer, &State);
  if (Status==EFI_SUCCESS) {
    //
    // State should indicate that pointer device keep silent
    //
    if (PointerKeepSilent (AbsolutePointer->Mode, &State) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAbsolutePointerExtensiveTestAssertionGuid006,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE, Pointer state check",
                   L"%a:%d: Status = %r,AbsoluteMinX=0x%lx,AbsoluteMaxX=0x%lx,CurrentX=0x%lx,AbsoluteMinY=0x%lx,AbsoluteMaxY=0x%lx,CurrentY=0x%lx,AbsoluteMinZ=0x%lx,AbsoluteMaxZ=0x%lx,CurrentZ=0x%lx,Attributes=0x%lx,ActiveButtons=0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   AbsolutePointer->Mode->AbsoluteMinX,
                   AbsolutePointer->Mode->AbsoluteMaxX,
                   State.CurrentX,
                   AbsolutePointer->Mode->AbsoluteMinY,
                   AbsolutePointer->Mode->AbsoluteMaxY,
                   State.CurrentY,
                   AbsolutePointer->Mode->AbsoluteMinZ,
                   AbsolutePointer->Mode->AbsoluteMaxZ,
                   State.CurrentZ,
                   AbsolutePointer->Mode->Attributes,
                   State.ActiveButtons
                   );

  } else if (Status==EFI_NOT_READY) {
    //
    // This is expected status, no problem
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAbsolutePointerExtensiveTestAssertionGuid007,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being FALSE",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Assertion Point
  // Reset() with Extended Verification should clears any pending pointer actions
  //

  //
  // Call Reset() with ExtendedVerification being TRUE
  //
  Status = AbsolutePointer->Reset (AbsolutePointer, TRUE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestStressAssertionGuid001,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call CheckEvent() on the WaitForInput event, should return EFI_NOT_READY
  //
  Status = gtBS->CheckEvent (AbsolutePointer->WaitForInput);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestStressAssertionGuid002,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - CheckEvent on WaitForInput after Reset with TRUE",
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
  Status = gtBS->WaitForEvent (1, &(AbsolutePointer->WaitForInput), &WaitIndex);
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
  Status = AbsolutePointer->Reset (AbsolutePointer, TRUE);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestStressAssertionGuid003,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call CheckEvent on the WaitForInput Event
  //

  Status = gtBS->CheckEvent (AbsolutePointer->WaitForInput);
  if (Status!=EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestStressAssertionGuid004,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - CheckEvent after Reset with ExtendedVerification being TRUE, Clear WaitForEvent",
                 L"%a:%d, Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status ,
                 EFI_NOT_READY
                 );


  //
  // Call GetState to verify pointer state;
  //
  Status = AbsolutePointer->GetState (AbsolutePointer, &State);
  if (Status==EFI_SUCCESS) {
    //
    // State should indicate that pointer device keep silent
    //
    if (PointerKeepSilent (AbsolutePointer->Mode, &State) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAbsolutePointerBBTestStressAssertionGuid005,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE, Pointer state check",
                   L"%a:%d: Status = %r,AbsoluteMinX=0x%lx,AbsoluteMaxX=0x%lx,CurrentX=0x%lx,AbsoluteMinY=0x%lx,AbsoluteMaxY=0x%lx,CurrentY=0x%lx,AbsoluteMinZ=0x%lx,AbsoluteMaxZ=0x%lx,CurrentZ=0x%lx,Attributes=0x%lx,ActiveButtons=0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   AbsolutePointer->Mode->AbsoluteMinX,
                   AbsolutePointer->Mode->AbsoluteMaxX,
                   State.CurrentX,
                   AbsolutePointer->Mode->AbsoluteMinY,
                   AbsolutePointer->Mode->AbsoluteMaxY,
                   State.CurrentY,
                   AbsolutePointer->Mode->AbsoluteMinZ,
                   AbsolutePointer->Mode->AbsoluteMaxZ,
                   State.CurrentZ,
                   AbsolutePointer->Mode->Attributes,
                   State.ActiveButtons
                   );

  } else if (Status==EFI_NOT_READY) {
    //
    // This is expected status, no problem
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAbsolutePointerBBTestStressAssertionGuid006,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being TRUE",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being FALSE",
                   L"%a:%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() Extensive Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 
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
  EFI_ABSOLUTE_POINTER_PROTOCOL          *AbsolutePointer;


  EFI_TEST_ASSERTION                   AssertionType;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_ABSOLUTE_POINTER_STATE           State;
  //EFI_ABSOLUTE_POINTER_MODE            Mode;
  UINTN                                WaitIndex;
  UINT64                                CurPosX, CurPosY,CurPosZ;
  BOOLEAN                              SptAltActive, SptPressureAsZ;



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

  AbsolutePointer = (EFI_ABSOLUTE_POINTER_PROTOCOL *)ClientInterface;


  //
  // Get Device Path of current Absolute_Pointer_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromAbsolutePointer (AbsolutePointer, &DevicePath, StandardLib);
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
    // Console Splitter/AbsolutePointer
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/AbsolutePointer"
                   );
  }


  SctPrint (L"\r\nGetState Stress Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Call Reset () with ExtendedVerification being TRUE
  //
  Status = AbsolutePointer->Reset (AbsolutePointer, TRUE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
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
  CurPosZ = 0;

  //
  // Capture mouse action continuously until key input
  //
  AssertionType = EFI_TEST_ASSERTION_PASSED;

  while (TRUE) {
    //
    // Wait until mouse action
    //
    Status = gtBS->WaitForEvent (1, &(AbsolutePointer->WaitForInput), &WaitIndex);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_ABSOLUTE_POINTER_PROTOCOL.WaitForInput() - WaitForEvent after WaitForInput is signaled",
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
    Status = AbsolutePointer->GetState (AbsolutePointer, &State);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      break;
    }


    if (PointerKeepSilent (AbsolutePointer->Mode, &State)==FALSE) {
      //
      // Output CurrentXYZ & CurPosXYZ
      //
      CurPosX += State.CurrentX;
      CurPosY += State.CurrentY;
      CurPosZ += State.CurrentZ;
      SctPrint (L"\r\nCurrentXYZ(%5d,%5d,%5d),CurPos(%5d,%5d,%5d)",
        State.CurrentX,
        State.CurrentY,
        State.CurrentZ,
        CurPosX,
        CurPosY,
        CurPosZ
        );
    }

    //
    // ActiveButton state TouchActive
    //
    SptAltActive = SupportAltActiveExt (AbsolutePointer->Mode,&State);
    if ( SptAltActive==FALSE) {
     SptPressureAsZ = SupportPressureAsZExt(AbsolutePointer->Mode,&State);
      if (SptPressureAsZ ==FALSE && State.CurrentZ!=0) {
        SctPrint (L"\r\nActiveButton RELEASED!");
      } else {
        SctPrint (L"\r\nActiveButton UNRELEASED!");
      }
    }

    SptAltActive = SupportAltActive(AbsolutePointer->Mode,&State);
    if (SptAltActive==TRUE) {
     SptPressureAsZ = SupportPressureAsZ(AbsolutePointer->Mode,&State);
      if (SptPressureAsZ==TRUE && State.CurrentZ==0) {
        SctPrint (L"\r\nActiveButton RELEASED!");
      } else {
        SctPrint (L"\r\nActiveButton UNRELEASED!");
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
                 gAbsolutePointerExtensiveTestAssertionGuid011,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after mouse moved or button state changed",
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
                 gAbsolutePointerExtensiveTestAssertionGuid012,
                 L"EFI_Absolute_TEXT_POINTER_PROTOCOL.GetState() - Extensive test",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  return EFI_SUCCESS;
}


