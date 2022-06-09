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

  DebugPortBBTestFunction.c

Abstract:

  Interface Function Test Cases of Debug Port Protocol

--*/


#include "SctLib.h"
#include "DebugPortBBTestMain.h"

/**
 *  Entrypoint for EFI_DEBUGPORT_PROTOCOL_GUID.Reset Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1
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
  EFI_DEBUGPORT_PROTOCOL               *DebugPort;
  EFI_TEST_ASSERTION                   AssertionType;

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

  DebugPort = (EFI_DEBUGPORT_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.1.2.1
  // Invoke Reset and verify interface correctness within test case.
  //
  Status = DebugPort->Reset (DebugPort);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugPortBBTestFunctionAssertionGuid001,
                 L"EFI_DEBUGPORT_PROTOCOL.Reset - Invoke Reset and verify interface correctness within test case",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_DEBUGPORT_PROTOCOL.Write() Function Manual Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.2
//
EFI_STATUS
EFIAPI
BBTestWriteFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEBUGPORT_PROTOCOL               *DebugPort;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                BufferSize;
  CHAR16                               Buffer[20];
  UINTN                                WaitIndex;
  EFI_INPUT_KEY                        Key;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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

  DebugPort = (EFI_DEBUGPORT_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.2.2.1
  // Call Write() to send data to debug port with enough time.
  //
  BufferSize = 12;
  SctStrCpy (Buffer, L"Hello");
  Status = DebugPort->Write (DebugPort, 1000, &BufferSize, (VOID*)Buffer);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugPortBBTestFunctionAssertionGuid002,
                 L"EFI_DEBUGPORT_PROTOCOL.Write - Invoke Write and verify interface correctness with enough time",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Verify the functionality manually.
  //
  SctPrint (L"Please verify the output string is %s, right press \"Y\", wrong press \"N\"", Buffer);

  //
  // Get the input key.
  //
  while(1)
  {
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    if((Key.UnicodeChar == L'Y') || (Key.UnicodeChar == L'y') || (Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
      break;
    }
    else {
      SctPrint (L"Please press \"Y\" or \"N\"");
    }
  }
  if ((Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugPortBBTestFunctionAssertionGuid003,
                 L"EFI_DEBUGPORT_PROTOCOL.Write - Invoke Write and verify its functionality correctness with enough time",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_DEBUGPORT_PROTOCOL.Read() Function Manual Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.3
//
EFI_STATUS
EFIAPI
BBTestReadFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEBUGPORT_PROTOCOL               *DebugPort;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                BufferSize;
  CHAR8                               Buffer[20];
  UINTN                                WaitIndex;
  EFI_INPUT_KEY                        Key;

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

  DebugPort = (EFI_DEBUGPORT_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.3.2.1
  // Call Read() to send data to debug port with enough time.
  //
  BufferSize = 1;
  SctZeroMem ((VOID*)Buffer, sizeof(Buffer));

  //
  // Wait for the input data.
  //
  SctPrint (L"Please any key after input data.");
  gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
  gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);

  Status = DebugPort->Read (DebugPort, 1000, &BufferSize, (VOID*)Buffer);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugPortBBTestFunctionAssertionGuid006,
                 L"EFI_DEBUGPORT_PROTOCOL.Read - Invoke Read and verify interface correctness with enough time",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Verify the functionality manually.
  //
  SctPrint (L"Please verify the input string is %s, right press \"Y\", wrong press \"N\"", Buffer);

  //
  // Get the input key.
  //
  while(1)
  {
    gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
    gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
    if((Key.UnicodeChar == L'Y') || (Key.UnicodeChar == L'y') || (Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
      break;
    }
    else {
      SctPrint (L"Please press \"Y\" or \"N\"");
    }
  }
  if ((Key.UnicodeChar == L'N') || (Key.UnicodeChar == L'n')) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugPortBBTestFunctionAssertionGuid007,
                 L"EFI_DEBUGPORT_PROTOCOL.Read - Invoke Read and verify its functionality correctness with enough time",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_DEBUGPORT_PROTOCOL.Poll() Function Auto Test.
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
BBTestPollFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEBUGPORT_PROTOCOL               *DebugPort;
  EFI_TEST_ASSERTION                   AssertionType;
  UINTN                                WaitIndex;
  EFI_INPUT_KEY                        Key;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
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

  DebugPort = (EFI_DEBUGPORT_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.4.2.1
  // Call Poll() to check the debug port with data.
  //

  //
  // Wait for the input data.
  //
  SctPrint (L"\nPress any key after input data.");
  gtBS->WaitForEvent (1, &(gtST->ConIn->WaitForKey), &WaitIndex);
  gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);

  Status = DebugPort->Poll (DebugPort);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gDebugPortBBTestFunctionAssertionGuid010,
             L"EFI_DEBUGPORT_PROTOCOL.Poll - Call Poll() to check the debug port with data",
             L"%a:%d:Status - %r",
             __FILE__,
             (UINTN)__LINE__,
             Status
           );

  //
  // Assertion Point 3.4.2.2
  // Call Poll() to check the debug port without data.
  //

  // Call Reset() to clean the data of the debug port.
  Status = DebugPort->Reset (DebugPort);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = DebugPort->Poll (DebugPort);
  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugPortBBTestFunctionAssertionGuid011,
                 L"EFI_DEBUGPORT_PROTOCOL.Poll - Call Poll() to check the debug port without data",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
