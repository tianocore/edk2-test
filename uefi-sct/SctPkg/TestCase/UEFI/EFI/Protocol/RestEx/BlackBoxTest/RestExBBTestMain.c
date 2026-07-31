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

  RestExBBTestMain.c

Abstract:

  Test Driver of EFI REST EX Protocol

--*/

#include "RestExBBTestMain.h"
#include "SctLib.h"

EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_REST_EX_PROTOCOL_TEST_REVISION,
  EFI_REST_EX_PROTOCOL_GUID,
  L"REST EX Protocol Test",
  L"UEFI REST EX Protocol Black-Box Test"
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
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetServiceFunction",
    L"Function auto test for REST EX Protocol GetService().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetServiceFunctionTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0102,
    L"ConfigureFunction",
    L"Function auto test for REST EX Protocol Configure().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestConfigureFunctionTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0103,
    L"GetModeDataFunction",
    L"Function auto test for REST EX Protocol GetModeData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetModeDataFunctionTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0104,
    L"SendReceiveFunction",
    L"Function auto test for REST EX Protocol SendReceive().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSendReceiveFunctionTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0105,
    L"GetServiceTimeFunction",
    L"Function auto test for REST EX Protocol GetServiceTime().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetServiceTimeFunctionTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0106,
    L"AyncSendReceiveFunction",
    L"Function auto test for REST EX Protocol AyncSendReceive().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestAyncSendReceiveFunctionTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0107,
    L"EventServiceFunction",
    L"Function auto test for REST EX Protocol EventService().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEventServiceFunctionTest
  },

  //
  // Conformance Test Entries
  //
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0201,
    L"GetServiceConformance",
    L"Conformance auto test for REST EX Protocol GetService().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetServiceConformanceTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0202,
    L"GetModeDataConformance",
    L"Conformance auto test for REST EX Protocol GetModeData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetModeDataConformanceTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0203,
    L"ConfigureConformance",
    L"Conformance auto test for REST EX Protocol Configure().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestConfigureConformanceTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0204,
    L"SendReceiveConformance",
    L"Conformance auto test for REST EX Protocol SendReceive().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSendReceiveConformanceTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0205,
    L"AyncSendReceiveConformance",
    L"Conformance auto test for REST EX Protocol AyncSendReceive().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestAyncSendReceiveConformanceTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0206,
    L"GetServiceTimeConformance",
    L"Conformance auto test for REST EX Protocol GetServiceTime().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetServiceTimeConformanceTest
  },
  {
    EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0207,
    L"EventServiceConformance",
    L"Conformance auto test for REST EX Protocol EventService().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEventServiceConformanceTest
  },

  0
};


EFI_STATUS
EFIAPI
InitializeRestExBBTest (
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
             UnloadRestExBBTest,
             &gBBTestProtocolInterface
             );
}


EFI_STATUS
EFIAPI
UnloadRestExBBTest (
  IN EFI_HANDLE    ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );
}
