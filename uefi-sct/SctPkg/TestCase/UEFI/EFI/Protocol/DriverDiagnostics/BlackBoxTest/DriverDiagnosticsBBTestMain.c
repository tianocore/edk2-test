/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    DriverDignosticsBBTestMain.c

Abstract:
    for EFI Driver Diagnostics Protocol Test

--*/
#include "SctLib.h"
#include "DriverDiagnosticsBBTest.h"

EFI_HANDLE      mImageHandle;


EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_DRIVER_DIAGNOSTICS_TEST_REVISION,
  EFI_DRIVER_DIAGNOSTICS_PROTOCOL_GUID,
  L"Testing For EFI Driver Diagnostics Protocol",
  L"Total # test cases for the EFI Driver Diagnostics Protocol"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {

#ifdef EFI_TEST_EXHAUSTIVE
  {
    EFI_DRIVER_DIAGNOSTICS_PROTOCOL_TEST_ENTRY_GUID0101,
    L"RunDiagnostics_Conf",
    L"Conformance Test for RunDiagnostics",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestRunDiagnosticsConformanceTest
  },
#endif

  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

/**
 *  Creates/installs the BlackBox Interface and eminating Entry Point
 *  node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 */
EFI_STATUS
InitializeBBTestDriverDiagnostics (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //
  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestDriverDiagnosticsUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
EFIAPI
BBTestDriverDiagnosticsUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
