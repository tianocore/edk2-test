/** @file

  Copyright 2016 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  RamDiskProtocolBBTestMain.c

Abstract:

  Test Driver of RamDisk Protocol

--*/

#include "RamDiskProtocolBBTestMain.h"

//
// Global variables
//

EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_RAM_DISK_PROTOCOL_TEST_REVISION,
  EFI_RAM_DISK_PROTOCOL_GUID,
  L"RamDisk Protocol Test",
  L"UEFI RamDisk Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0101,
    L"RegisterRamDiskFunction",
    L"Function test for RamDisk Protocol Register().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterRamDiskFunctionTest
  },
  {
    EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0102,
    L"UnregisterRamDiskFunction",
    L"Function test for RamDisk Protocol Unregister().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterRamDiskFunctionTest
  },
  {
    EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0201,
    L"RegisterRamDiskConformance",
    L"Conformance test for RamDisk Protocol Register().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterRamDiskConformanceTest
  },
  {
    EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0202,
    L"UnregisterRamDiskConformance",
    L"Conformance test for RamDisk Protocol Unregister().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterRamDiskConformanceTest
  },
  0
};

EFI_BB_TEST_PROTOCOL                  *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
InitializeBBTestRamDiskProtocol (
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
           UnloadBBTestRamDiskProtocol,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadBBTestRamDiskProtocol (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
