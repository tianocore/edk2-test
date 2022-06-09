/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  UFSDeviceConfigBBTestMain.c

Abstract:

  Test Driver of UFS Device Config Protocol

--*/


#include "UFSDeviceConfigBBTestMain.h"

#define EFI_UFS_DEVICE_CONFIG_TEST_GUID \
  { 0xb81bfab0, 0xeb3, 0x4cf9, { 0x84, 0x65, 0x7f, 0xa9, 0x86, 0x36, 0x16, 0x64}}

//
// Global variables
//
EFI_HANDLE mImageHandle;


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_UFS_DEVICE_CONFIG_PROTOCOL_TEST_REVISION,
  EFI_UFS_DEVICE_CONFIG_TEST_GUID,
  L"UFS Device Config Protocol Test",
  L"UEFI UFS Device Config Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_UFS_DEVICE_CONFIG_PROTOCOL_TEST_ENTRY_GUID0101,
    L"RwUfsDescriptorConformance",
    L"Conformance auto test for RwUfsDescriptor",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRwUfsDescriptorConfTest
  },
    {
    EFI_UFS_DEVICE_CONFIG_PROTOCOL_TEST_ENTRY_GUID0102,
    L"RwUfsFlagConformance",
    L"Conformance auto test for RwUfsFlag",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRwUfsFlagConfTest
  },
    {
    EFI_UFS_DEVICE_CONFIG_PROTOCOL_TEST_ENTRY_GUID0103,
    L"RwUfsAttributeConformance",
    L"Conformance auto test for RwUfsAttribute",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRwUfsAttributeConfTest
  },
 0
};


EFI_STATUS
EFIAPI
InitializeUFSDeviceConfigBBTest (
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
             UnloadUFSDeviceConfigBBTest,
             &gBBTestProtocolInterface
             );

}


EFI_STATUS
EFIAPI
UnloadUFSDeviceConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

