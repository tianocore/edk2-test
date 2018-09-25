/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  PlatformDriverOverrideBBTestMain.c

Abstract:

  Test Driver of PlatformDriverOverride Protocol

--*/

#include "SctLib.h"
#include "PlatformDriverOverrideBBTestMain.h"

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  PLATFORM_DRIVER_OVERRIDE_PROTOCOL_TEST_REVISION,
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID,
  L"Platform Driver Override Protocol Test",
  L"UEFI Platform Driver Override Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_FUNCTION_AUTO_GUID,
    L"GetDriver_Func",
    L"Invoke GetDriver() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDriverFunctionAutoTest
  },

  {
    PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_PATH_FUNCTION_AUTO_GUID,
    L"GetDriverPath_Func",
    L"Invoke GetDriverPath() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDriverPathFunctionAutoTest
  },

  {
    PLATFORM_DRIVER_OVERRIDE_PROTOCOL_DRIVER_LOADED_FUNCTION_AUTO_GUID,
    L"DriverLoaded_Func",
    L"Invoke DriverLoaded() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestDriverLoadedFunctionAutoTest
  },

  {
    PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_CONFORMANCE_AUTO_GUID,
    L"GetDriver_Conf",
    L"Test whether GetDriver() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDriverConformanceAutoTest
  },

  {
    PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_PATH_CONFORMANCE_AUTO_GUID,
    L"GetDriverPath_Conf",
    L"Test whether GetDriverPath() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDriverPathConformanceAutoTest
  },

  {
    PLATFORM_DRIVER_OVERRIDE_PROTOCOL_DRIVER_LOADED_CONFORMANCE_AUTO_GUID,
    L"DriverLoaded_Conf",
    L"Test whether DriverLoaded() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestDriverLoadedConformanceAutoTest
  },
  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestPlatformDriverOverrideProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Platform Driver Override Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestPlatformDriverOverride (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestPlatformDriverOverrideProtocolUnload,
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
BBTestPlatformDriverOverrideProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

