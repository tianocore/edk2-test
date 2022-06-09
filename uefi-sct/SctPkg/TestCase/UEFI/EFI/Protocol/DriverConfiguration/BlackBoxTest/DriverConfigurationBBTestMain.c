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
    DriverConfigurationBBTestMain.c

Abstract:
    for EFI Driver Configuration Protocol Test

--*/
#include "SctLib.h"
#include "DriverConfigurationBBTest.h"

EFI_HANDLE      mImageHandle;


EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_DRIVER_CONFIGURATION_TEST_REVISION,
  EFI_DRIVER_CONFIGURATION_PROTOCOL_GUID,
  L"Testing For EFI Driver Configuration Protocol",
  L"Total # test cases for the EFI Driver Configuration Protocol"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {

#ifdef EFI_TEST_EXHAUSTIVE
  {
    EFI_DRIVER_CONFIGURATION_PROTOCOL_TEST_ENTRY_GUID0101,
    L"SetOptions_Conf",
    L"Conformance Test for SetOptions",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSetOptionsConformanceTest
  },
  {
    EFI_DRIVER_CONFIGURATION_PROTOCOL_TEST_ENTRY_GUID0102,
    L"OptionsValid_Conf",
    L"Conformance Test for OptionsValid",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestOptionsValidConformanceTest
  },
  {
    EFI_DRIVER_CONFIGURATION_PROTOCOL_TEST_ENTRY_GUID0103,
    L"ForceDefaults_Conf",
    L"Conformance Test for ForceDefaults",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestForceDefaultsConformanceTest
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
InitializeBBTestDriverConfiguration (
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
           BBTestDriverConfigurationUnload,
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
BBTestDriverConfigurationUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
