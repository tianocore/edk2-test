/** @file

  Copyright 2006 - 2011 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2011, Byosoft Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DriverSupportedEfiVersionBBTestMain.c

Abstract:

  Test Driver of Efi Driver Supported Efi Version Protocol

--*/


#include "SctLib.h"
#include "DriverSupportedEfiVersionBBTestMain.h"

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_TEST_REVISION,
  EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_GUID,
  L"Efi Driver Supported Efi Version Protocol Test",
  L"UEFI efi driver supported efi version Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_LENGTH_PARAMETER_AUTO_GUID,
    L"Length_Parameter",
    L"Perform auto parameter checkes of the Length",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLengthParameterAutoTest
  },
  {
    DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_FIRMWAREVERSION_PARAMETER_AUTO_GUID,
    L"FirmwareVersion_Parameter",
    L"Perform auto parameter checkes of the firmwareVersion",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFirmwareVersionParameterAutoTest
  },
  
  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestEfiVersionProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Efi Driver Supported Efi Version Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestDriverSupportedEfiVersion (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);


  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestDriverSupportedEfiVersionProtocolUnload,
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
BBTestDriverSupportedEfiVersionProtocolUnload (
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
