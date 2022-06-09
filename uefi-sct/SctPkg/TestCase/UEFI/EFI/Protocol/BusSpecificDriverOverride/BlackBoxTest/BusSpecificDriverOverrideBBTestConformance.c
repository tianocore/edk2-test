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

  BusSpecificDriverOverrideBBTestConformance.c

Abstract:

  Interface Conformance Test Cases of BusSpecificDriverOverride Protocol

--*/


#include "SctLib.h"
#include "BusSpecificDriverOverrideBBTestMain.h"


/**
 *  Entrypoint for EFI_BUS_SPECIFIC_DRIVER_OVERRIDE.GetDriver() Conformance Test.
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
EFIAPI
BBTestGetDriverConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib;
  EFI_STATUS                                  Status;
  EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL   *BusOverride;


  EFI_TEST_ASSERTION                          AssertionType;
  EFI_HANDLE                                  DriverImageHandle;
  EFI_HANDLE                                  InvalidDriverImageHandle;
  BOOLEAN                                     Invalid;

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

  BusOverride = (EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL *)ClientInterface;

  DriverImageHandle = NULL;
  Invalid = TRUE;
  InvalidDriverImageHandle = (EFI_HANDLE)(INTN)(0x8);

  if (InvalidDriverImageHandle == DriverImageHandle) {
    Invalid = FALSE;
  }

  //
  // Circularly call GetDriver() with DriverImageHandle
  // being the one retrieved by the last call of GetDriver(),
  // until EFI_NOT_FOUND returned.
  //

  do {
    Status = BusOverride->GetDriver (
                            BusOverride,
                            &DriverImageHandle
                            );
    if (!EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBusSpecificDriverOverrideBBTestFunctionAssertionGuid001,
                     L"EFI_BUS_SPECIFIC_DRIVER_OVERRIDE.GetDriver - Verification of GetDriver interface",
                     L"%a:%d:ImageHandle:0x%x",
                     __FILE__,
                     (UINTN)__LINE__,
                     DriverImageHandle
                     );

      if (InvalidDriverImageHandle == DriverImageHandle) {
        Invalid = FALSE;
      }
    }
  } while (!EFI_ERROR (Status));

  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBusSpecificDriverOverrideBBTestConformanceAssertionGuid001,
                 L"EFI_BUS_SPECIFIC_DRIVER_OVERRIDE.GetDriver - Verification of GetDriver interface",
                 L"%a:%d:Status = %r, Expected = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_NOT_FOUND
                 );

  //
  // pass the invalid driver image handle to the GetDriver
  //
  if (Invalid == TRUE) {
    Status = BusOverride->GetDriver (
                            BusOverride,
                            &InvalidDriverImageHandle
                            );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBusSpecificDriverOverrideBBTestConformanceAssertionGuid002,
                   L"EFI_BUS_SPECIFIC_DRIVER_OVERRIDE.GetDriver - with the invalid handle, the return status should be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status = %r, Expected = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_INVALID_PARAMETER
                   );
  }

  return EFI_SUCCESS;
}
