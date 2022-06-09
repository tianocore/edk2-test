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

  AbsolutePointerBBTestFunction.c

Abstract:

  Interface Function Test Cases of Absolute Pointer Protocol

--*/


#include "SctLib.h"
#include "AbsolutePointerBBTestMain.h"


/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.Reset Function Test.
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
BBTestResetFunctionAutoTest (
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

  EFI_ABSOLUTE_POINTER_STATE             State;


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
  // Get Device Path of current Absolute Pointer Protocol
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

  //
  // Assertion Point 
  // Reset should succeed to reset pointer device
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
                 gAbsolutePointerBBTestFunctionAssertionGuid001,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call GetState() to retrieve the current state of the pointer device
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
                   gAbsolutePointerBBTestFunctionAssertionGuid002,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE",
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
                   gAbsolutePointerBBTestFunctionAssertionGuid003,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
                   L"%a:%d: Status = %r",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


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
                 gAbsolutePointerBBTestFunctionAssertionGuid005,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call GetState() to retrieve the current state of the pointer device
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
                   gAbsolutePointerBBTestFunctionAssertionGuid006,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being TRUE",
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
                   gAbsolutePointerBBTestFunctionAssertionGuid007,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with extended verification, after State integrity check",
                   L"%a:%d: Status = %r",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
  
}




/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() Interface Test.
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
BBTestResetFunctionManualTest (
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

  EFI_ABSOLUTE_POINTER_STATE             State;


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

  SctPrint (L"\r\nReset Without Extend Verification Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 
  // Reset without Extended Verification should succeed to reset pointer device
  //

  //
  // Step 2.
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
                 gAbsolutePointerBBTestFunctionAssertionGuid009,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Step 3.
  // Call GetState() to retrieve the current state of the pointer device
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
                   gAbsolutePointerBBTestFunctionAssertionGuid010,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE",
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
                   gAbsolutePointerBBTestFunctionAssertionGuid011,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
                   L"%a:%d: Status = %r",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Step 4.
  // Prompt user to move or click corresponding pointer device
  //
  SctPrint (L"\r\nMove or click pointer device\r\n");

  if (WaitTimeOrPointer (10, AbsolutePointer) != TRUE) {
    goto AssertionPoints2;
  }

  //
  // Step 5.
  // Call Reset() with ExtendedVerification being FALSE again
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
                 gAbsolutePointerBBTestFunctionAssertionGuid013,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Step 6.
  // Call GetState() to retrieve the current state of the pointer device
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
                   gAbsolutePointerBBTestFunctionAssertionGuid014,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE",
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
                   gAbsolutePointerBBTestFunctionAssertionGuid015,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
                   L"%a:%d: Status = %r",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Step 7.
  // Prompt user to move or click corresponding pointer device
  //
  SctPrint (L"\r\nMove or click pointer device AGAIN\r\n");

  if (WaitTimeOrPointer (10, AbsolutePointer) != TRUE) {
    goto AssertionPoints2;
  }

  //
  // Step 8.
  // Call GetState() to retrieve the current state of the pointer device
  //
  Status = AbsolutePointer->GetState (AbsolutePointer, &State);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after mouse move",
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



  //
  // Step 9
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
                 gAbsolutePointerBBTestFunctionAssertionGuid018,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Step 10.
  // Call GetState() to retrieve the current state of the pointer device
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
                   gAbsolutePointerBBTestFunctionAssertionGuid019,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
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
                   gAbsolutePointerBBTestFunctionAssertionGuid020,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
                   L"%a:%d: Status = %r",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


AssertionPoints2:

  SctPrint (L"\r\nReset With Extend Verification Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 
  // Reset without Extended Verification should succeed to reset pointer device
  //

  //
  // Step 2.
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
                 gAbsolutePointerBBTestFunctionAssertionGuid022,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Step 3.
  // Call GetState() to retrieve the current state of the pointer device
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
                   gAbsolutePointerBBTestFunctionAssertionGuid023,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
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
                   gAbsolutePointerBBTestFunctionAssertionGuid024,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with extended verification, after State integrity check",
                   L"%a:%d: Status = %r",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Step 4.
  // Prompt user to move or click corresponding pointer device
  //
  SctPrint (L"\r\nMove or click pointer device!\r\n");

  if (WaitTimeOrPointer (10, AbsolutePointer) != TRUE) {
    return EFI_SUCCESS;
  }

  //
  // Step 5.
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
                 gAbsolutePointerBBTestFunctionAssertionGuid026,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Step 6.
  // Call GetState() to retrieve the current state of the pointer device
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
                   gAbsolutePointerBBTestFunctionAssertionGuid027,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
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
                   gAbsolutePointerBBTestFunctionAssertionGuid028,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with extended verification, after State integrity check",
                   L"%a:%d: Status = %r",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Step 7.
  // Prompt user to move or click corresponding pointer device
  //
  SctPrint (L"\r\nMove or click pointer device AGAIN\r\n");

  if (WaitTimeOrPointer (10, AbsolutePointer) != TRUE) {
    return EFI_SUCCESS;
  }

  //
  // Step 8.
  // Call GetState() to retrieve the current state of the pointer device
  //
  Status = AbsolutePointer->GetState (AbsolutePointer, &State);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid030,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after mouse move",
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
  //
  // Step 9.
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
                 gAbsolutePointerBBTestFunctionAssertionGuid031,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Step 10.
  // Call GetState() to retrieve the current state of the pointer device
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
                   gAbsolutePointerBBTestFunctionAssertionGuid032,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
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
                   gAbsolutePointerBBTestFunctionAssertionGuid033,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with extended verification, after State integrity check",
                   L"%a:%d: Status = %r",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}



/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.GetState Function Test.
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
BBTestGetStateFunctionAutoTest (
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
  EFI_TEST_ASSERTION                   GetStateReturnAssertion;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_ABSOLUTE_POINTER_STATE             State;
  UINTN                                Index;


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


  //
  // Assertion Point 
  // GetState() should succeed to retrieve the proper state
  // When pointer device keep silent
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
                 gTestGenericFailureGuid,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset () - Reset with ExtendedVerification being FALSE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call GetState() to retrieve the current state of the pointer device
  //

  for (Index=0;Index<5;Index++) {
    GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;

    Status = AbsolutePointer->GetState (AbsolutePointer, &State);

    if (Status==EFI_SUCCESS) {

      //
      //only the first calling can return EFI_SUCCESS.
      //
      if (Index != 0) {
        GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
      }

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
                     gAbsolutePointerBBTestFunctionAssertionGuid036,
                     L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being FALSE",
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

    } else if (Status==EFI_NOT_READY||Status == EFI_DEVICE_ERROR) {
      //
      // This is expected status, no problem
      //
      GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;
      if (Status == EFI_DEVICE_ERROR){
         GetStateReturnAssertion = EFI_TEST_ASSERTION_WARNING;
      }

    } else {
      GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   GetStateReturnAssertion,
                   gAbsolutePointerBBTestFunctionAssertionGuid038,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
                   L"%a:%d: Status = %r, Index = %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );

  }

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
                   gTestGenericFailureGuid,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                   L"%a:%d: Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_SUCCESS
                   );


  for (Index=0;Index<5;Index++) {
    //
    // Call GetState() to retrieve the current state of the pointer device
    //
    GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;

    Status = AbsolutePointer->GetState (AbsolutePointer, &State);
    if (Status==EFI_SUCCESS) {

      GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;

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
                     gAbsolutePointerBBTestFunctionAssertionGuid040,
                     L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being TRUE",
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

    } else if (Status==EFI_NOT_READY||Status == EFI_DEVICE_ERROR) {
      //
      // This is expected status, no problem
      //
      GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;
      if (Status == EFI_DEVICE_ERROR){
          GetStateReturnAssertion = EFI_TEST_ASSERTION_WARNING;
      }
    } else {
      GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   GetStateReturnAssertion,
                   gAbsolutePointerBBTestFunctionAssertionGuid042,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
                   L"%a:%d: Status = %r,Index = %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index
                   );

  }
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() Interface Test.
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
BBTestGetStateFunctionManualTest (
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
  EFI_TEST_ASSERTION                   GetStateReturnAssertion;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_ABSOLUTE_POINTER_STATE             State;



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

  SctPrint (L"\r\nGetState Function Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 
  // GetState() should succeed to retrieve the proper state
  // When pointer device keep inputting
  //

  //
  // Step 2
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
                 gTestGenericFailureGuid,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Step 3
  // Call GetState() to retrieve the current state of the pointer device
  //
  GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;
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
                   gAbsolutePointerBBTestFunctionAssertionGuid044,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being FALSE",
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

  } else if (Status != EFI_NOT_READY) {
    //
    // This is expected status, no problem
    //
    GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 GetStateReturnAssertion,
                 gAbsolutePointerBBTestFunctionAssertionGuid046,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Step 4
  // Wait for User input or timeout (Move Only!!)
  //
  SctPrint (L"\r\nMove the pointer device and NO(!!) button pressed in 10 seconds\r\n");
  if (WaitTimeOrPointer (10, AbsolutePointer) == FALSE) {
    goto Step7;
  }

  //
  // Step 5
  // Call GetState() to retrieve the state of the pointer device
  //

  Status = AbsolutePointer->GetState (AbsolutePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid047,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState() ",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // State should indicate that pointer device Only Move
  //
  if (PointerMovedExt (AbsolutePointer->Mode, &State) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid048,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState when device moved",
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

  //
  // Call Reset to clear mouse movement
  //

  Status = AbsolutePointer->Reset (AbsolutePointer, TRUE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                   L"%a:%d: Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_SUCCESS
                   );
  }

  //
  // Step 6.1
  // Call GetState() to retrieve the state of the pointer device
  // just to clear buffer
  //

  AbsolutePointer->GetState (AbsolutePointer, &State);


  //
  // Step 7
  // Wait for User input or timeout (touch sensor!!)
  //
  Step7:
  SctPrint (L"\r\nIf device supports alternate button input, Please Touch/Input and No move in 10 seconds\r\n");
  if (WaitTimeOrPointer (10, AbsolutePointer) == FALSE) {
    goto Step13;
  }

  //
  // Step 8
  // Call GetState() to retrieve the state of the pointer device
  //

  Status = AbsolutePointer->GetState (AbsolutePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid053,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState() with touch sensor avtive",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // State should indicate that pointer device supports an alternate button input
  //
  if (SupportAltActiveExt (AbsolutePointer->Mode, &State) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid054,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState when touch sensor avtived",
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
  
  if (SupportPressureAsZExt (AbsolutePointer->Mode, &State) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid056,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState when touch sensor avtived",
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

  //
  // Step 9
  // Call GetState again!
  //
  GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;

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
                   gAbsolutePointerBBTestFunctionAssertionGuid055,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after GetState",
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
  

  } else if (Status != EFI_NOT_READY) {
    //
    // This is expected status, no problem
    //
    GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 GetStateReturnAssertion,
                 gAbsolutePointerBBTestFunctionAssertionGuid057,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after GetState",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Step 9.1
  // Wait for User to release touch sensor
  //
  SctPrint (L"\r\nPlease release device's alternate button in 10 seconds\r\n");
  if (WaitTimeOrPointer (10, AbsolutePointer) == FALSE) {
    goto Step13;
  }

  Status = AbsolutePointer->GetState (AbsolutePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid058,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState() with touch sensor not active ",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );


  //
  // State should indicate that pointer device with  touch sensor not active
  //
  if (SupportAltActive (AbsolutePointer->Mode, &State) == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid059,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState when touch sensor not active",
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

  if (SupportPressureAsZ (AbsolutePointer->Mode, &State) == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid060,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState when touch sensor not active",
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

  //
  // Reset the pointer device
  //
  Status = AbsolutePointer->Reset (AbsolutePointer, TRUE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                   L"%a:%d: Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_SUCCESS
                   );
  }

Step13:
  //
  // Step 13
  // Wait for User input or timeout ()
  //
  SctPrint (L"\r\nMove the pointer device AND click buttons in 10 seconds\r\n");
  if (WaitTimeOrPointer (10, AbsolutePointer) == FALSE) {
    return EFI_SUCCESS;
  }

  //
  // Step 14
  // Call GetState() to retrieve the state of the pointer device
  //

  Status = AbsolutePointer->GetState (AbsolutePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid069,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState() with mouse action",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // State should indicate that pointer device NOT keep silent
  //
  if (PointerKeepSilent (AbsolutePointer->Mode, &State) == FALSE ||
      (SupportPressureAsZ (AbsolutePointer->Mode, &State) != FALSE &&
      SupportAltActive (AbsolutePointer->Mode, &State) == TRUE) )
  {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid070,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState with pointer input",
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

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_ABSOLUTE_POINTER_PROTOCOL.WaitForInput() Interface Test.
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
BBTestWaitForInputFunctionManualTest (
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
  UINTN                                WaitIndex;

  EFI_ABSOLUTE_POINTER_STATE             State;



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


  SctPrint (L"\r\nWaitForInput Function Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 
  // WaitForInput event should be signaled on pointer input
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
                 gTestGenericFailureGuid,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call GetState() to retrieve the current state of the pointer device
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
                   gTestGenericFailureGuid,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE, Pointer state check",
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
                   gTestGenericFailureGuid,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
                   L"%a:%d: Status = %r",
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
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Repeat until user move or click buttons
  //
  while (TRUE) {
    SctPrint (L"\r\nMove the pointer device or click buttons \r\n");
    SctPrint (L"\r\nPress Any key to quit! \r\n");

    //
    // Whether there are some keys pressed?
    //
    Status = gtBS->CheckEvent (gtST->ConIn->WaitForKey);
    if (Status==EFI_SUCCESS) {
      break;
    }
    //
    // Call WaitForEvent on WaitForInput
    //
    Status = gtBS->WaitForEvent (1, &(AbsolutePointer->WaitForInput), &WaitIndex);

    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAbsolutePointerBBTestFunctionAssertionGuid064,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.WaitForEvent with WaitForInput after there is mouse move or key pressed",
                   L"%a:%d: Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_SUCCESS
                   );

    //
    // Call GetState to Retrieve pointer device state
    //
    Status = AbsolutePointer->GetState (AbsolutePointer, &State);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAbsolutePointerBBTestFunctionAssertionGuid068,
                   L"EFI_ABSOLUTE_POINTER_PROTOCOL.GetState() - GetState() with pointer input",
                   L"%a:%d: Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_SUCCESS
                   );
  }

  SctPrint (L"\r\nPlease Don't move or press any button of the the mouse\r\n");

  gtBS->Stall (2000000);
  //
  //clear current state.
  //
  AbsolutePointer->GetState (AbsolutePointer, &State);
  gtBS->Stall (3000000);

  Status = gtBS->CheckEvent (AbsolutePointer->WaitForInput);

  if (Status==EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gAbsolutePointerBBTestFunctionAssertionGuid060,
                 L"EFI_ABSOLUTE_POINTER_PROTOCOL.WaitForInput - CheckEvent when there is no mouse move or button press",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_READY
                 );


  return EFI_SUCCESS;
}



