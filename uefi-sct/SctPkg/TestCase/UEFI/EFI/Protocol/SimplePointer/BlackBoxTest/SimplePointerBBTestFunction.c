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

  SimplePointerBBTestFunction.c

Abstract:

  Interface Test Cases of Simple Pointer Protocol

--*/


#include "SctLib.h"
#include "SimplePointerBBTestMain.h"


/**
 *  Entrypoint for EFI_SIMPLE_POINTER_PROTOCOL.Reset() Interface Test.
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
  EFI_SIMPLE_POINTER_PROTOCOL          *SimplePointer;


  EFI_TEST_ASSERTION                   AssertionType;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_SIMPLE_POINTER_STATE             State;


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

  //
  // Assertion Point 4.1.1
  // Reset should succeed to reset pointer device
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
                 gSimplePointerInterfaceTestAssertionGuid001,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call GetState() to retrieve the current state of the pointer device
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
                   gSimplePointerInterfaceTestAssertionGuid002,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
                   gSimplePointerInterfaceTestAssertionGuid003,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
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
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }


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
                 gSimplePointerInterfaceTestAssertionGuid005,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call GetState() to retrieve the current state of the pointer device
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
                   gSimplePointerInterfaceTestAssertionGuid006,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being TRUE",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
                   gSimplePointerInterfaceTestAssertionGuid007,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with extended verification, after State integrity check",
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
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_SIMPLE_POINTER_PROTOCOL.Reset() Interface Test.
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
  EFI_SIMPLE_POINTER_PROTOCOL          *SimplePointer;


  EFI_TEST_ASSERTION                   AssertionType;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_SIMPLE_POINTER_STATE             State;


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

  SctPrint (L"\r\nReset Without Extend Verification Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 4.1.2
  // Reset without Extended Verification should succeed to reset pointer device
  //

  //
  // Step 2.
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
                 gSimplePointerInterfaceTestAssertionGuid009,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
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
                   gSimplePointerInterfaceTestAssertionGuid010,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
                   gSimplePointerInterfaceTestAssertionGuid011,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
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
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
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

  if (WaitTimeOrPointer (10, SimplePointer) != TRUE) {
    goto AssertionPoints2;
  }

  //
  // Step 5.
  // Call Reset() with ExtendedVerification being FALSE again
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
                 gSimplePointerInterfaceTestAssertionGuid013,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
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
                   gSimplePointerInterfaceTestAssertionGuid014,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - GetState after Reset with ExtendedVerification being FALSE",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
                   gSimplePointerInterfaceTestAssertionGuid015,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
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
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
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

  if (WaitTimeOrPointer (10, SimplePointer) != TRUE) {
    goto AssertionPoints2;
  }

  //
  // Step 8.
  // Call GetState() to retrieve the current state of the pointer device
  //
  Status = SimplePointer->GetState (SimplePointer, &State);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after mouse move",
                 L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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



  //
  // Step 9
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
                 gSimplePointerInterfaceTestAssertionGuid018,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
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
                   gSimplePointerInterfaceTestAssertionGuid019,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
                   gSimplePointerInterfaceTestAssertionGuid020,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
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
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
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
  // Assertion Point 4.1.2.2.2
  // Reset without Extended Verification should succeed to reset pointer device
  //

  //
  // Step 2.
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
                 gSimplePointerInterfaceTestAssertionGuid022,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
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
                   gSimplePointerInterfaceTestAssertionGuid023,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
                   gSimplePointerInterfaceTestAssertionGuid024,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with extended verification, after State integrity check",
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
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
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

  if (WaitTimeOrPointer (10, SimplePointer) != TRUE) {
    return EFI_SUCCESS;
  }

  //
  // Step 5.
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
                 gSimplePointerInterfaceTestAssertionGuid026,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
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
                   gSimplePointerInterfaceTestAssertionGuid027,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
                   gSimplePointerInterfaceTestAssertionGuid028,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with extended verification, after State integrity check",
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
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
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

  if (WaitTimeOrPointer (10, SimplePointer) != TRUE) {
    return EFI_SUCCESS;
  }

  //
  // Step 8.
  // Call GetState() to retrieve the current state of the pointer device
  //
  Status = SimplePointer->GetState (SimplePointer, &State);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid030,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after mouse move",
                 L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
  //
  // Step 9.
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
                 gSimplePointerInterfaceTestAssertionGuid031,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
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
                   gSimplePointerInterfaceTestAssertionGuid032,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
                   gSimplePointerInterfaceTestAssertionGuid033,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with extended verification, after State integrity check",
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
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_POINTER_PROTOCOL.GetState() Interface Test.
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
BBTestGetStateFunctionAutoTest (
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
  EFI_TEST_ASSERTION                   GetStateReturnAssertion;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_SIMPLE_POINTER_STATE             State;
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


  //
  // Assertion Point 4.1.3.2.1
  // GetState() should succeed to retrieve the proper state
  // When pointer device keep silent
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
                 gTestGenericFailureGuid,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset () - Reset with ExtendedVerification being FALSE",
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

    Status = SimplePointer->GetState (SimplePointer, &State);

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

      if (PointerKeepSilent (SimplePointer->Mode, &State) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimplePointerInterfaceTestAssertionGuid036,
                     L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being FALSE",
                     L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
      GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;

    } else {
      GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   GetStateReturnAssertion,
                   gSimplePointerInterfaceTestAssertionGuid038,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
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

    Status = SimplePointer->GetState (SimplePointer, &State);
    if (Status==EFI_SUCCESS) {

      GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;

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
                     gSimplePointerInterfaceTestAssertionGuid040,
                     L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being TRUE",
                     L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
      GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;

    } else {
      GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   GetStateReturnAssertion,
                   gSimplePointerInterfaceTestAssertionGuid042,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset with extended verification",
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
 *  Entrypoint for EFI_SIMPLE_POINTER_PROTOCOL.GetState() Interface Test.
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
BBTestGetStateFunctionManualTest (
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
  EFI_TEST_ASSERTION                   GetStateReturnAssertion;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_SIMPLE_POINTER_STATE             State;



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

  SctPrint (L"\r\nGetState Function Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 4.1.4.2.1
  // GetState() should succeed to retrieve the proper state
  // When pointer device keep inputting
  //

  //
  // Step 2
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
                 gTestGenericFailureGuid,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
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
                   gSimplePointerInterfaceTestAssertionGuid044,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after Reset with ExtendedVerification being FALSE",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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

  } else if (Status != EFI_NOT_READY) {
    //
    // This is expected status, no problem
    //
    GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 GetStateReturnAssertion,
                 gSimplePointerInterfaceTestAssertionGuid046,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
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
  if (WaitTimeOrPointer (10, SimplePointer) == FALSE) {
    goto Step10;
  }

  //
  // Step 5
  // Call GetState() to retrieve the state of the pointer device
  //

  Status = SimplePointer->GetState (SimplePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid047,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState() ",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // State should indicate that pointer device Only Move
  //
  if (PointerMovedExt (SimplePointer->Mode, &State) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid048,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState when device moved",
                 L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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

  //
  // Call Reset to clear mouse movement
  //

  Status = SimplePointer->Reset (SimplePointer, TRUE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
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

  SimplePointer->GetState (SimplePointer, &State);


  //
  // Step 7
  // Wait for User input or timeout (Right Button Pressed Only!!)
  //
  SctPrint (L"\r\nPlease Press Right button not release and No move in 10 seconds\r\n");
  if (WaitTimeOrPointer (10, SimplePointer) == FALSE) {
    goto Step10;
  }

  //
  // Step 8
  // Call GetState() to retrieve the state of the pointer device
  //

  Status = SimplePointer->GetState (SimplePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid053,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState() with right button pressed ",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // State should indicate that pointer device with Right Button pressed
  //
  if (PointerRButtonPressedExt (SimplePointer->Mode, &State) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid054,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState when Right Button pressed",
                 L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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

  //
  // Step 9
  // Call GetState again!
  //
  GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;

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
                   gSimplePointerInterfaceTestAssertionGuid055,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after GetState",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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

  } else if (Status != EFI_NOT_READY) {
    //
    // This is expected status, no problem
    //
    GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 GetStateReturnAssertion,
                 gSimplePointerInterfaceTestAssertionGuid057,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after GetState",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Step 9.1
  // Wait for User to release right button pressed
  //
  SctPrint (L"\r\nPlease release Right button in 10 seconds\r\n");
  if (WaitTimeOrPointer (10, SimplePointer) == FALSE) {
    goto Step13;
  }

  Status = SimplePointer->GetState (SimplePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid058,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState() with right button released ",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );


  //
  // State should indicate that pointer device without Right Button pressed
  //
  if (PointerRButtonPressed (SimplePointer->Mode, &State) == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid059,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState when Right Button released",
                 L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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

  //
  // Reset the pointer device
  //
  Status = SimplePointer->Reset (SimplePointer, TRUE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
                   L"%a:%d: Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_SUCCESS
                   );
  }

Step10:
  //
  // Step 10
  // Wait for User input or timeout (Left Button Pressed Only!!)
  //
  SctPrint (L"\r\nPlease Press Left button not release and NO move in 10 seconds\r\n");
  if (WaitTimeOrPointer (10, SimplePointer) == FALSE) {
    goto Step13;
  }

  //
  // Step 11
  // Call GetState() to retrieve the state of the pointer device
  //

  Status = SimplePointer->GetState (SimplePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid061,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState() with left button pressed",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // State should indicate that pointer device with Left Button pressed
  //
  if (PointerLButtonPressedExt (SimplePointer->Mode, &State) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid062,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState when Left Button pressed",
                 L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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

  //
  // Step 12
  // Call GetState again!
  //
  GetStateReturnAssertion = EFI_TEST_ASSERTION_PASSED;

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
                   gSimplePointerInterfaceTestAssertionGuid063,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after GetState",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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

  } else if (Status!=EFI_NOT_READY) {
    //
    // This is expected status, no problem
    //
    GetStateReturnAssertion = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 GetStateReturnAssertion,
                 gSimplePointerInterfaceTestAssertionGuid065,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after GetState",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Step 12.1
  // Wait for User to release Left button pressed
  //
  SctPrint (L"\r\nPlease release Left button in 10 seconds\r\n");
  if (WaitTimeOrPointer (10, SimplePointer) == FALSE) {
    return EFI_SUCCESS;
  }

  Status = SimplePointer->GetState (SimplePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid066,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState() with left button released",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );


  //
  // State should indicate that pointer device without Left Button pressed
  //
  if (PointerLButtonPressed (SimplePointer->Mode, &State) == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid067,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState when Left Button released",
                 L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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


  //
  // Reset the pointer device
  //
  Status = SimplePointer->Reset (SimplePointer, TRUE);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being TRUE",
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
  if (WaitTimeOrPointer (10, SimplePointer) == FALSE) {
    return EFI_SUCCESS;
  }

  //
  // Step 14
  // Call GetState() to retrieve the state of the pointer device
  //

  Status = SimplePointer->GetState (SimplePointer, &State);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid069,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState() with mouse action",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // State should indicate that pointer device NOT keep silent
  //
  if (PointerKeepSilent (SimplePointer->Mode, &State) == FALSE ||
      PointerLButtonPressed (SimplePointer->Mode, &State) == TRUE ||
      PointerRButtonPressed (SimplePointer->Mode, &State) == TRUE)
  {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid070,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState with pointer input",
                 L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_SIMPLE_POINTER_PROTOCOL.WaitForInput() Interface Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.5
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
  EFI_SIMPLE_POINTER_PROTOCOL          *SimplePointer;


  EFI_TEST_ASSERTION                   AssertionType;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;
  UINTN                                WaitIndex;

  EFI_SIMPLE_POINTER_STATE             State;



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


  SctPrint (L"\r\nWaitForInput Function Test Start!\r\n");
  WaitTimeOrKey (5);

  //
  // Assertion Point 4.1.5.2.1
  // WaitForInput event should be signaled on pointer input
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
                 gTestGenericFailureGuid,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_SUCCESS
                 );

  //
  // Call GetState() to retrieve the current state of the pointer device
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
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset with ExtendedVerification being FALSE, Pointer state check",
                   L"%a:%d: Status = %r,ResolutionX=0x%lx,RelativeX=%d,ResolutionY=0x%lx,RelativeY=%d,ResolutionZ=0x%lx,RelativeZ=%d,LButtonSupport=%d,LButtonMove=%d,RButtonSupport=%d,RButtonMove=%d",
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
                   gTestGenericFailureGuid,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.Reset() - Reset without extended verification, after State integrity check",
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
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState after reset without extended verification",
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
    SctPrint (L"\r\nAny key to quit! \r\n");

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
    Status = gtBS->WaitForEvent (1, &(SimplePointer->WaitForInput), &WaitIndex);

    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimplePointerInterfaceTestAssertionGuid064,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.WaitForEvent with WaitForInput after there is mouse move or key pressed",
                   L"%a:%d: Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_SUCCESS
                   );

    //
    // Call GetState to Retrieve pointer device state
    //
    Status = SimplePointer->GetState (SimplePointer, &State);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimplePointerInterfaceTestAssertionGuid068,
                   L"EFI_SIMPLE_POINTER_PROTOCOL.GetState() - GetState() with pointer input",
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
  SimplePointer->GetState (SimplePointer, &State);
  gtBS->Stall (3000000);

  Status = gtBS->CheckEvent (SimplePointer->WaitForInput);

  if (Status==EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimplePointerInterfaceTestAssertionGuid060,
                 L"EFI_SIMPLE_POINTER_PROTOCOL.WaitForInput - CheckEvent when there is no mouse move or button press",
                 L"%a:%d: Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_READY
                 );


  return EFI_SUCCESS;
}