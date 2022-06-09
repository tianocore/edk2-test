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

  EbcBBTestConformance.c

Abstract:

  Conformance Test Cases of Ebc Protocol

--*/

#include "EbcBBTestMain.h"

/**
 *  Entrypoint for EFI_EBC_PROTOCOL.CreateThunk() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestCreateThunkConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_EBC_PROTOCOL                      *EbcInterface;
  VOID                                  *EbcEntryPoint;
  EFI_IMAGE_ENTRY_POINT                 ThunkEntryPoint;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_EBC_PROTOCOL Protocol interface to be tested
  //
  EbcInterface = (EFI_EBC_PROTOCOL *)ClientInterface;

  //
  // Register a callback for flushing the instruction cache so that created
  // thunks can be flushed.
  //
  Status = EbcInterface->RegisterICacheFlush (EbcInterface, FlushICache);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_EBC_PROTOCOL.RegisterICacheFlush - Can't register callback function",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Load Ebc Driver
  //
  Status = LoadEbcDriver (&EbcEntryPoint);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"LoadEbcDriver - Can't load Ebc Driver and get the entry point",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    UnloadEbcDriver();
    return Status;
  }

  //
  // 4.1.2.1 Call CreateThunk() with Invalid Parameters
  //
  Status = EbcInterface->CreateThunk (
                           EbcInterface,
                           gDummyImageHandle,
                           (VOID *)((UINTN)EbcEntryPoint+1),   // invalid
                           (VOID **)&ThunkEntryPoint
                           );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEbcBBTestConformanceAssertionGuid001,
                 L"EFI_EBC_PROTOCOL.CreateThunk - Call CreateThunk() with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  UnloadEbcDriver();

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EBC_PROTOCOL.UnloadImage() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestUnloadImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EBC_PROTOCOL                     *EbcInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_EBC_PROTOCOL Protocol interface to be tested
  //
  EbcInterface = (EFI_EBC_PROTOCOL *)ClientInterface;

  //
  // 4.2.2.1 Call UnloadImage() with Invalid Parameters
  //
  Status = EbcInterface->UnloadImage (EbcInterface, (EFI_HANDLE)((UINTN)gDummyImageHandle+1));
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEbcBBTestConformanceAssertionGuid002,
                 L"EFI_EBC_PROTOCOL.UnloadImage - Call UnloadImage() with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EBC_PROTOCOL.GetVersion() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestGetVersionConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EBC_PROTOCOL                     *EbcInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Get the EFI_EBC_PROTOCOL Protocol interface to be tested
  //
  EbcInterface = (EFI_EBC_PROTOCOL *)ClientInterface;

  //
  // 4.3.2.1 Call GetVersion() with Invalid Parameters
  //
  Status = EbcInterface->GetVersion(EbcInterface, NULL);
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEbcBBTestConformanceAssertionGuid003,
                 L"EFI_EBC_PROTOCOL.GetVersion - Call GetVersion() with Invalid Parameters",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
