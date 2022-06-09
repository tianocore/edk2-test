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

  DebugSupportBBTestExceptionCallbackFunction.c

Abstract:

  Interface Function Test Cases of Debug Support Protocol

--*/


#include "DebugSupportBBTestMain.h"

extern volatile  UINTN InvokedExceptionCallback;
extern volatile  UINTN InvokedPeriodicCallback;

extern EFI_INSTRUCTION_SET_ARCHITECTURE PlatformIsa;

void
SoftwareBreak (
  void
  );

/**
 *  Entrypoint for EFI_DEBUG_SUPPORT_PROTOCOL.RegisterExceptionCallback() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.4
//
EFI_STATUS
EFIAPI
BBTestRegisterExceptionCallbackFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEBUG_SUPPORT_PROTOCOL           *DebugSupport;
  EFI_TEST_ASSERTION                   AssertionType;

  DebugSupport = (EFI_DEBUG_SUPPORT_PROTOCOL *)ClientInterface;

  if (DebugSupport->Isa != PlatformIsa) {
    return EFI_SUCCESS;
  }

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

  //
  // Assertion Point 3.4.2.1
  // Invoke RegisterExceptionCallback() to install an interrupt handler function.
  //
  InvokedExceptionCallback = FALSE;
  Status = DebugSupport->RegisterExceptionCallback (DebugSupport, 0, ExceptionCallback, EXCEPT_X64_BREAKPOINT);

  if ((Status == EFI_SUCCESS) || (Status == EFI_ALREADY_STARTED)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid009,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterExceptionCallback - Invoke this function and verify interface correctness",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // If the callback function is already registed, return
  //
  if (EFI_ERROR(Status)) {
    return EFI_SUCCESS;
  }

  //
  // Test the callback function registed.
  //

  //
  // Call SoftwareBreak to invoke the interrupt handler function.
  //
  SoftwareBreak ();

  if (InvokedExceptionCallback == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid010,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterExceptionCallback - Verify the callback function was invoked.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Assertion Point 3.4.2.2
  // Invoke RegisterPeriodicCallback() to install the Periodic interrupt handler function.
  // Verify the two callback functions can be both invoked.
  //
  InvokedExceptionCallback = FALSE;
  InvokedPeriodicCallback  = FALSE;

  Status = DebugSupport->RegisterPeriodicCallback (DebugSupport, 0, PeriodicCallback);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Wait the PeriodicCallback to be invoked.
  //
  gtBS->Stall (500000);

  //
  // Call SoftwareBreak to invoke the interrupt handler function.
  //
  SoftwareBreak ();

  if ((InvokedExceptionCallback == TRUE) && (InvokedPeriodicCallback == TRUE)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid011,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterExceptionCallback - Verify the two callback functions can be both invoked.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Uninstall the Periodic callback function.
  //
  Status = DebugSupport->RegisterPeriodicCallback (DebugSupport, 0, NULL);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Assertion Point 3.4.2.3
  // Invoke RegisterExceptionCallback() to install another interrupt handler function.
  //
  Status = DebugSupport->RegisterExceptionCallback (DebugSupport, 0, ExceptionCallback1, EXCEPT_X64_BREAKPOINT);

  if (Status != EFI_ALREADY_STARTED) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid012,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterExceptionCallback - Register another callback function.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Assertion Point 3.4.2.4
  // Invoke RegisterExceptionCallback() to unstall the interrupt handler function.
  //
  Status = DebugSupport->RegisterExceptionCallback (DebugSupport, 0, NULL, EXCEPT_X64_BREAKPOINT);

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid013,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterExceptionCallback - Invoke this function to uninstall the interrupt handler function",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  InvokedExceptionCallback = FALSE;

  //
  // Call SoftwareBreak to invoke the interrupt handler function.
  //
  SoftwareBreak ();

  if (InvokedExceptionCallback != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid014,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterExceptionCallback - Verify the callback function wasn't invoked",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

