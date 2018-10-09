/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Dell Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  FirmwareManagementBBTestMain.c

Abstract:

  Firmware Management Protocol test driver.

--*/

#include "SctLib.h"
#include "FirmwareManagementBBTestMain.h"

// ****************************************************************************
//   Variables
// ****************************************************************************

EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_REVISION,
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GUID,
  L"Firmware Management Protocol Test",
  L"UEFI 2.3 Firmware Management Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  /*
  //Use for unit test only
  {
    { 0x8cdda816, 0x3f97, 0x4155, { 0xa6, 0x73, 0x86, 0x93, 0x79, 0x8f, 0xb0, 0x6d } },
	L"Unit Test Only",
	L"Verify the Assistant Function",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnitTest
  },
  */
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0101,
    L"Function_Test-GetImageInfo",
    L"Function auto test for Firmware Management Protocol GetImageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageInfoFunctionTest
  },
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0102,
    L"Function_Test-GetImage",
    L"Function auto test for Firmware Management Protocol GetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageFunctionTest
  },
/*++
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0103,
    L"Function Test - SetImage",
    L"Function auto test for Firmware Management Protocol SetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetImageFunctionTest
  },
--*/
/*++
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0104,
    L"Function Test - CheckImage",
    L"Function auto test for Firmware Management Protocol CheckImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCheckImageFunctionTest
  },
--*/
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0105,
    L"Function_Test-GetPackageInfo",
    L"Function auto test for Firmware Management Protocol GetPackageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetPackageInfoFunctionTest
  },
/*++
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0106,
    L"Function Test - SetPackageInfo",
    L"Function auto test for Firmware Management Protocol SetPackageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetPackageInfoFunctionTest
  },
--*/  
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0201,
    L"Conformance_Test-GetImageInfo",
    L"Conformance auto test for Firmware Management Protocol GetImageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageInfoConformanceTest
  },
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0202,
    L"Conformance_Test-GetImage",
    L"Conformance auto test for Firmware Management Protocol GetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageConformanceTest
  },
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0203,
    L"Conformance_Test-SetImage",
    L"Conformance auto test for Firmware Management Protocol SetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetImageConformanceTest
  },
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0204,
    L"Conformance_Test-CheckImage",
    L"Conformance auto test for Firmware Management Protocol CheckImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCheckImageConformanceTest
  },
/*++
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0205,
    L"Conformance Test - GetPackageInfo",
    L"Conformance auto test for Firmware Management Protocol GetPackageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetPackageInfoConformanceTest
  },
--*/
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0206,
    L"Conformance_Test-SetPackageInfo",
    L"Conformance auto test for Firmware Management Protocol SetPackageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetPackageInfoConformanceTest
  },
  0
};

// ****************************************************************************
//   Initialization and Unload functions
// ****************************************************************************


EFI_STATUS
EFIAPI
InitializeFirmwareManagementBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
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
           UnloadFirmwareManagementBBTest,
           &gBBTestProtocolInterface
           );
}

EFI_STATUS
EFIAPI
UnloadFirmwareManagementBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

// ****************************************************************************
//   Support functions
// ****************************************************************************

