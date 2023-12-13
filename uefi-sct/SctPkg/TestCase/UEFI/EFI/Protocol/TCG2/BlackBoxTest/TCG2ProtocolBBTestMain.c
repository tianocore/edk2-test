/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2021 - 2023, Arm Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:
    TCG2ProtocolBBTestMain.c

Abstract:
    for EFI TCG2 Protocol Test

--*/

#include "TCG2ProtocolBBTest.h"

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_TCG2_TEST_REVISION,
  EFI_TCG2_PROTOCOL_GUID,
  L"Testing For EFI TCG2 Protocol",
  L"Total # test cases for the EFI TCG2 Protocol"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetCapability_Conf",
    L"Test the GetCapablity API",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetCapabilityConformanceTest
  },
  {
    EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetActivePcrBanks_Conf",
    L"Test the GetActivePcrBanks API",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetActivePcrBanksConformanceTest
  },
  {
    EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0103,
    L"HashLogExtendEvent_Conf",
    L"Test the HashLogExtendEvent API",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestHashLogExtendEventConformanceTest
  },
  {
    EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0104,
    L"SubmitCommand_Conf",
    L"Test the SubmitCommmand API",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSubmitCommandConformanceTest
  },
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
EFIAPI
InitializeBBTestTCG2Protocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //
  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestTCG2ProtocolUnload,
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
BBTestTCG2ProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
