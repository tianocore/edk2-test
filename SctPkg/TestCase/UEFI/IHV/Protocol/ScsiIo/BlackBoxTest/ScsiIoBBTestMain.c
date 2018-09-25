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

  ScsiIoBBTestMain.c

Abstract:

  Test Driver of Scsi Io Protocol

--*/

#include "SctLib.h"
#include "ScsiIoBBTestMain.h"

UINT8 EnterEvent;

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SCSI_IO_PROTOCOL_TEST_REVISION,
  IHV_SCSI_IO_PROTOCOL_GUID,
  L"Scsi Io Protocol Test",
  L"UEFI Scsi Io Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    SCSI_IO_PROTOCOL_GET_DEVICE_TYPE_FUNCTION_AUTO_GUID,
    L"GetDeviceType_Func",
    L"Invoke GetDeviceType() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDeviceTypeFunctionAutoTest
  },

  {
    SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION_FUNCTION_AUTO_GUID,
    L"GetDeviceLocation_Func",
    L"Invoke GetDeviceLocation() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDeviceLocationFunctionAutoTest
  },

  {
    SCSI_IO_PROTOCOL_RESET_BUS_FUNCTION_AUTO_GUID,
    L"ResetBus_Func",
    L"Invoke ResetBus() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetBusFunctionAutoTest
  },

  {
    SCSI_IO_PROTOCOL_RESET_DEVICE_FUNCTION_AUTO_GUID,
    L"ResetDevice_Func",
    L"Invoke ResetDevice() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetDeviceFunctionAutoTest
  },
  
  {
    SCSI_IO_PROTOCOL_EXECUTE_SCSI_COMMAND_FUNCTION_AUTO_GUID,
    L"ExecuteScsiCommand_Func",
    L"Invoke ExecuteScsiCommand() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestExecuteScsiCommandFunctionAutoTest
  },
  
  {
    SCSI_IO_PROTOCOL_GET_DEVICE_TYPE_CONFORMANCE_AUTO_GUID,
    L"GetDeviceType_Conf",
    L"Test whether GetDeviceType() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDeviceTypeConformanceAutoTest
  },

  {
    SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION_CONFORMANCE_AUTO_GUID,
    L"GetDeviceLocation_Conf",
    L"Test whether GetDeviceLocation() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDeviceLocationConformanceAutoTest
  },
  
  {
    SCSI_IO_PROTOCOL_EXECUTE_SCSI_COMMAND_CONFORMANCE_AUTO_GUID,
    L"ExecuteScsiCommand_Conf",
    L"Test whether ExecuteScsiCommand() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestExecuteScsiCommandConformanceAutoTest
  },
  
  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestScsiIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Scsi Io Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestScsiIo (
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
           BBTestScsiIoProtocolUnload,
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
BBTestScsiIoProtocolUnload (
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

VOID
NotifyFunction (
  EFI_EVENT Event,
  VOID      *Context
  )
{
  EnterEvent = 1;
  return;
}
