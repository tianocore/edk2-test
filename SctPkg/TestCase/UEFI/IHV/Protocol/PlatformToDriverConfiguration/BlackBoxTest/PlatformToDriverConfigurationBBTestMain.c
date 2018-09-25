/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Byosoft Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  PlatformToDriverConfigurationBBTestMain.c

Abstract:

  Test Driver of Platform To Driver Configuration Protocol

--*/

#include "SctLib.h"
#include "PlatformToDriverConfigurationBBTestMain.h"

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_TEST_REVISION,
  IHV_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID,
  L"Platform To Driver Configuration Protocol Test",
  L"UEFI Platform To Driver Configuration Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_QUERY_FUNCTION_AUTO_GUID,
    L"Query_Func",
    L"Invoke Query() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestQueryFunctionAutoTest
  },

  {
    PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_RESPONSE_FUNCTION_AUTO_GUID,
    L"Response_Func",
    L"Invoke Response() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResponseFunctionAutoTest
  },

  {
    PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_QUERY_CONFORMANCE_AUTO_GUID,
    L"Query_Conf",
    L"Test whether Query() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestQueryConformanceAutoTest
  },

  {
    PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_RESPONSE_CONFORMANCE_AUTO_GUID,
    L"Response_Conf",
    L"Test whether Response() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResponseConformanceAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPCOMMAND_AUTO_GUID,
    L"CLPCommand",
    L"Perform auto parameter checkes of CLPCommand",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPCommandAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPRETURNSTRING_AUTO_GUID,
    L"CLPRetuenString",
    L"Perform auto parameter checkes of the firmwareVersion",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPReturnStringAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPRETURNSTATUS_AUTO_GUID,
    L"CLPReturnStatus",
    L"Perform auto parameter checkes of CLPReturnStatus",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPCmdStatusAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPERRORVALUE_AUTO_GUID,
    L"CLPErrorValue",
    L"Perform auto parameter checkes of CLPErrorValue",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPErrorValueAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPMESSAGECODE_AUTO_GUID,
    L"CLPMessageCode",
    L"Perform auto parameter checkes of CLPMessageCode",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPMessageCodeAutoTest
  },
  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestPlatformToDriverConfigurationProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Platform To Driver Configuration Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestPlatformToDriverConfiguration (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallIHVBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestPlatformToDriverConfigurationProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
EFIAPI
BBTestPlatformToDriverConfigurationProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeIHVBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

