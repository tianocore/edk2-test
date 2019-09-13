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

  DevicePathUtilitiesBBTestMain.c

Abstract:

  Test Driver of Device Path Utilities Protocol

--*/

#include "SctLib.h"
#include "DevicePathUtilitiesBBTestMain.h"

//
// Build Data structure here
//
EFI_BB_TEST_PROTOCOL_FIELD  gBBTestProtocolField = {
  DEVICE_PATH_PROTOCOL_TEST_REVISION,
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID,
  L"Device Path Utilities Protocol Test",
  L"UEFI Device Path Utilities Protocol Test"
};

EFI_GUID                    gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD     gBBTestEntryField[] = {
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_CREATEDEVICENODE_FUNCTION_GUID,
    L"CreatDeviceNode_Functionality",
    L"Invoke the CreatDeviceNode and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesCreateDeviceNodeFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICENODE_FUNCTION_GUID,
    L"AppendDeviceNode_Functionality",
    L"Invoke the AppendDeviceNode and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDeviceNodeFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_GETDEVICEPATHSIZE_FUNCTION_GUID,
    L"GetDevicePathSize_Functionality",
    L"Invoke the GetDevicePathSize and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesGetDevicePathSizeFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_DUPLICATEDEVICEPATH_FUNCTION_GUID,
    L"DuplicateDevicePath_Functionality",
    L"Invoke the DuplicateDevicePath and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesDuplicateDevicePathFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATH_FUNCTION_GUID,
    L"AppendDevicePath_Functionality",
    L"Invoke the AppendDevicePath and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDevicePathFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATHINSTANCE_FUNCTION_GUID,
    L"AppendDevicePathInstance_Functionality",
    L"Invoke the AppendDevicePathInstance and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDevicePathInstanceFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_GETNEXTDEVICEPATHINSTANCE_FUNCTION_GUID,
    L"GetNextDevicePathInstance_Functionality",
    L"Invoke the GetNextDevicePathInstance and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesGetNextDevicePathInstanceFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_ISDEVICEPATHMULTIINSTANCE_FUNCTION_GUID,
    L"IsDevicePathMultiInstance_Functionality",
    L"Invoke the IsDevicePathMultiInstance and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesIsDevicePathMultiInstanceFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_CREATEDEVICENODE_CONFORMANCE_GUID,
    L"CreateDeviceNode_Conformance",
    L"Perform conformance test on the CreatDeviceNode service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesCreateDeviceNodeConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICENODE_CONFORMANCE_GUID,
    L"AppendDeviceNode_Conformance",
    L"Perform conformance test on the AppendDeviceNode service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDeviceNodeConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATH_CONFORMANCE_GUID,
    L"AppendDevicePath_Conformance",
    L"Perform conformance test on the AppendDevicePath service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDevicePathConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATHINSTANCE_CONFORMANCE_GUID,
    L"AppendDevicePathInstance_Conformance",
    L"Perform conformance test on the AppendDevicePathInstance service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDevicePathInstanceConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_GETNEXTDEVICEPATHINSTANCE_CONFORMANCE_GUID,
    L"GetNextDevicePathInstance_Conformance",
    L"Perform conformance test on the GetNextDevicePathInstance service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesGetNextDevicePathInstanceConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_GETDEVICEPATHSIZE_CONFORMANCE_GUID,
    L"GetDevicePathSize_Conformance",
    L"Perform conformance test on the GetDevicePathSize service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesGetDevicePathSizeConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_DUPLICATEDEVICEPATH_CONFORMANCE_GUID,
    L"DuplicateDevicePath_Conformance",
    L"Perform conformance test on the DuplicateDevicePath service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesDuplicateDevicePathConformanceTest
  },
  0
};

EFI_BB_TEST_PROTOCOL        *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestDevicePathUtilitiesProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Device Path Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestDevicePathUtilitiesProtocol (
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
          BBTestDevicePathUtilitiesProtocolUnload,
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
BBTestDevicePathUtilitiesProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS  Status;

  Status = EfiUninstallAndFreeBBTestInterface (
            ImageHandle,
            gBBTestProtocolInterface
            );

  return Status;
}
