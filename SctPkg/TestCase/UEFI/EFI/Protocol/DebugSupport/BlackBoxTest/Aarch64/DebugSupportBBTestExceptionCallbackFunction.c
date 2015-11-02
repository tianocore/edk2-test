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

  Copyright (c) 2011, 2012 ARM Ltd. All rights reserved.

--*/
/*++

Module Name:

  DebugSupportBBExceptionCallbackFunction.c

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
  )
{
  // Not ported to ARM yet
  ASSERT (FALSE);
}

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

  //
  // Assertion Point 3.4.2.1
  // Invoke RegisterExceptionCallback() to install an interrupt handler function.
  //
  InvokedExceptionCallback = FALSE;
  // FIXME: Is it normal that we use EXCEPT_IA32_BREAKPOINT here?
  // Shouldn't we define proper constants for ARM exceptions in DebugSupportProtocol.h file?
  Status = DebugSupport->RegisterExceptionCallback (DebugSupport, 0, ExceptionCallback, EXCEPT_IA32_BREAKPOINT);

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
  Status = DebugSupport->RegisterExceptionCallback (DebugSupport, 0, ExceptionCallback1, EXCEPT_IA32_BREAKPOINT);

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
  Status = DebugSupport->RegisterExceptionCallback (DebugSupport, 0, NULL, EXCEPT_IA32_BREAKPOINT);

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

