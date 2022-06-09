/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Byosoft Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DriverSupportedEfiVersionBBTestMain.h

Abstract:

  BB test header file of Efi Driver Support Efi Version Protocol

--*/


#ifndef _DRIVER_SUPPORTED_EFI_VERSION_BBTEST_H_
#define _DRIVER_SUPPORTED_EFI_VERSION_BBTEST_H_


#include "Efi.h"
#include "Guid.h"
#include <UEFI/Protocol/DriverSupportedEfiVersion.h>
#include <Library/EfiTestLib.h>

#define  DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_TEST_REVISION    0x00010000




EFI_STATUS
InitializeBBTestDriverSupportedEfiVersion (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDriverSupportedEfiVersionProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
EFIAPI
BBTestLengthParameterAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestFirmwareVersionParameterAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Entry GUIDs
//

#define DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_LENGTH_PARAMETER_AUTO_GUID \
  { 0xe1ba41cb, 0xb085, 0x4776, { 0x81, 0xd3, 0x9e, 0x46, 0xb7, 0x63, 0x1, 0xf7 } }

#define DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_FIRMWAREVERSION_PARAMETER_AUTO_GUID \
  { 0x4a448316, 0xff41, 0x4e2c, { 0x84, 0x3, 0x4e, 0x30, 0x91, 0xfc, 0x57, 0xb5 } }

#endif

