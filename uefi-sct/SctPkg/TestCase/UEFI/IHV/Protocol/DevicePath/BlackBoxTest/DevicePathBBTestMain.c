/** @file

  Copyright 2006 - 2011 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DevicePathBBTestMain.c

Abstract:

  Test Driver of Device Path Protocol

--*/

#include "DevicePathBBTestMain.h"

//
// Build Data structure here
//
EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  DEVICE_PATH_PROTOCOL_TEST_REVISION,
  IHV_DEVICE_PATH_PROTOCOL_GUID,
  L"Device Path Protocol Test",
  L"UEFI Device Path Protocol Test"
};

EFI_GUID                    gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    DEVICE_PATH_PROTOCOL_DEVICEPATHNODE_CONFORMANCE_AUTO_GUID,
    L"PathNode_Conf",
    L"Check whether device path node is consistent with the UEFI Spec.",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestDevicePathNodeConformanceAutoTest
  },
  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestDevicePathProtocolUnload (
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
InitializeBBTestDevicePath (
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
           BBTestDevicePathProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestDevicePathProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS  Status;

  Status = EfiUninstallAndFreeIHVBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}
