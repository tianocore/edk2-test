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

  StorageSecurityCommandBBTestMain.c

Abstract:

  Test Driver of Storage Security Command Protocol

--*/

#include "SctLib.h"
#include "StorageSecurityCommandBBTestMain.h"

EFI_EVENT TimerEvent = NULL;

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  STORAGE_SECURITY_COMMAND_PROTOCOL_TEST_REVISION,
  IHV_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID,
  L"Storage Security Command Protocol Test",
  L"Ihv Storage Security Command Protocol Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  //
  // Conformance test section
  //
  {
    STORAGE_SECURITY_COMMAND_PROTOCOL_RECEIVEDATA_CONFORMANCE_AUTO_GUID,
    L"ReceiveData_Conf",
    L"Perform auto consistency checkes on the ReceiveData interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReceiveDataConformanceAutoTest
  },
  {
    STORAGE_SECURITY_COMMAND_PROTOCOL_SENDDATA_CONFORMANCE_AUTO_GUID,
    L"SendData_Conf",
    L"Perform auto consistency checkes on the SendData interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSendDataConformanceAutoTest
  },

  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestBlockIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Entry Point Declaration
//

/**
 *  Storage Security Command Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestStorageSecurityCommand (
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
           BBTestStorageSecurityCommandProtocolUnload,
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
BBTestStorageSecurityCommandProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS          Status;

  Status = EfiUninstallAndFreeIHVBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}
