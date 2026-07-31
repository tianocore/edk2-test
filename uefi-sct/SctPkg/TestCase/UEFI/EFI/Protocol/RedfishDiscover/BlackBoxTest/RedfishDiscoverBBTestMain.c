/** @file

  Copyright 2006 - 2026 Unified EFI, Inc.<BR>
  Copyright (c) 2026, AMD Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  RedfishDiscoverBBTestMain.c

Abstract:

  Test Driver of EFI Redfish Discover Protocol

--*/

#include "RedfishDiscoverBBTestMain.h"
#include "SctLib.h"

EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_REDFISH_DISCOVER_PROTOCOL_TEST_REVISION,
  EFI_REDFISH_DISCOVER_PROTOCOL_GUID,
  L"Redfish Discover Protocol Test",
  L"UEFI Redfish Discover Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {

  //
  // Function Test Entries
  //
  {
    EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetNetworkInterfaceListFunction",
    L"Function auto test for Redfish Discover Protocol GetNetworkInterfaceList().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNetworkInterfaceListFunctionTest
  },
  {
    EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0102,
    L"AcquireRedfishServiceFunction",
    L"Function auto test for Redfish Discover Protocol AcquireRedfishService().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestAcquireRedfishServiceFunctionTest
  },
  {
    EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0103,
    L"AbortAndReleaseFunction",
    L"Function auto test for Redfish Discover Protocol AbortAcquireRedfishService() and ReleaseRedfishService().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestAbortAndReleaseFunctionTest
  },

  //
  // Conformance Test Entries
  //
  {
    EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0201,
    L"GetNetworkInterfaceListConformance",
    L"Conformance auto test for Redfish Discover Protocol GetNetworkInterfaceList().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNetworkInterfaceListConformanceTest
  },
  {
    EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0202,
    L"AcquireRedfishServiceConformance",
    L"Conformance auto test for Redfish Discover Protocol AcquireRedfishService().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestAcquireRedfishServiceConformanceTest
  },
  {
    EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0203,
    L"ReleaseRedfishServiceConformance",
    L"Conformance auto test for Redfish Discover Protocol ReleaseRedfishService().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestReleaseRedfishServiceConformanceTest
  },

  0
};


EFI_STATUS
EFIAPI
InitializeRedfishDiscoverBBTest (
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE    *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
             &ImageHandle,
             &gBBTestProtocolField,
             gBBTestEntryField,
             UnloadRedfishDiscoverBBTest,
             &gBBTestProtocolInterface
             );
}


EFI_STATUS
EFIAPI
UnloadRedfishDiscoverBBTest (
  IN EFI_HANDLE    ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );
}
