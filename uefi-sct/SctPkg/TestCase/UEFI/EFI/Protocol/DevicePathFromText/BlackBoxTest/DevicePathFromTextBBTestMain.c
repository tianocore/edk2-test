/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DevicePathFromTextBBTestMain.c

Abstract:

  Test Driver of Device Path From Text Protocol

--*/

#include "DevicePathFromTextBBTestMain.h"

//
// Build Data structure here
//
EFI_BB_TEST_PROTOCOL_FIELD  gBBTestProtocolField = {
  DEVICE_PATH_PROTOCOL_TEST_REVISION,
  EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID,
  L"Device Path From Text Protocol Test",
  L"UEFI Device Path From Text Protocol Test"
};

EFI_GUID                    gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD     gBBTestEntryField[] = {
  {
    DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICENODEFROMTEXT_FUNCTION_GUID,
    L"ConvertTextToDeviceNode_Functionality",
    L"Invoke the ConvertTextToDeviceNode and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathFromTextConvertTextToDeviceNodeFunctionTest
  },
  {
    DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICEPATHFROMTEXT_FUNCTION_GUID,
    L"ConvertTextToDevicePath_Functionality",
    L"Invoke ConvertTextToDevicePath and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathFromTextConvertTextToDevicePathFunctionTest
  },
  {
    DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICENODEFROMTEXT_CONFORMANCE_GUID,
    L"ConvertTextToDeviceNode_Conformance",
    L"Perform conformance test on the ConvertTextToDeviceNode service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathFromTextConvertTextToDeviceNodeConformanceTest
  },
  {
    DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICEPATHFROMTEXT_CONFORMANCE_GUID,
    L"ConvertTextToDevicePath_Conformance",
    L"Perform conformance test on the ConvertTextToDevicePath service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathFromTextConvertTextToDevicePathConformanceTest
  },
  {
    DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICENODEFROMTEXT_COVERAGE_GUID,
    L"ConvertTextToDeviceNode_Coverage",
    L"Invoke the ConvertDeviceNodeToText and ConvertTextToDeviceNode respectively or cooperatively, and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathFromTextConvertTextToDeviceNodeCoverageTest
  },
  {
    DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICEPATHFROMTEXT_COVERAGE_GUID,
    L"ConvertTextToDevicePath_Coverage",
    L"Invoke the ConvertDevicePathToText and ConvertTextToDevicePath respectively or cooperatively, and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathFromTextConvertTextToDevicePathCoverageTest
  },
  0
};

EFI_BB_TEST_PROTOCOL        *gBBTestProtocolInterface;

EFI_STATUS
BBTestDevicePathFromTextProtocolUnload (
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
InitializeBBTestDevicePathFromTextProtocol (
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
          BBTestDevicePathFromTextProtocolUnload,
          &gBBTestProtocolInterface
          );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestDevicePathFromTextProtocolUnload (
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
