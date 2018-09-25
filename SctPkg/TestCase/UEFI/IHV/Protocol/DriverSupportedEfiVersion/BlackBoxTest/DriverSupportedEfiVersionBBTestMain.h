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

#define IHV_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_GUID        \
{                  \
        0xcd0463ca, 0x97cf, 0x499b, 0xb9, 0xf3, 0x8c, 0x82, 0x90, 0x9c, 0x7, 0x89       \
}


EFI_STATUS
InitializeBBTestDriverSupportedEfiVersion (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDriverSupportedEfiVersionProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
BBTestLengthParameterAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
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
  { 0xecbbdc3, 0x286b, 0x484c, 0x8b, 0x14, 0x67, 0x90, 0x39, 0x50, 0x97, 0xef }

#define DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_FIRMWAREVERSION_PARAMETER_AUTO_GUID \
  { 0xc5a6f8f6, 0x8092, 0x4c0e, 0x90, 0xa5, 0x7a, 0x54, 0xee, 0xc0, 0xd3, 0xc3 }

#endif

