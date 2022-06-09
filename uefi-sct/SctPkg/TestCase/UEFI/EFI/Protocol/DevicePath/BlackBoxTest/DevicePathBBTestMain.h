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

  DevicePathBBTestMain.h

Abstract:

  BB test header file of Device Path protocol

--*/

#ifndef _DEVICE_PATH_BBTEST_H_
#define _DEVICE_PATH_BBTEST_H_

#include <Base.h>
#include "SctLib.h"
#include <UEFI/Protocol/DevicePath.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define DEVICE_PATH_PROTOCOL_TEST_REVISION  0x00010001

EFI_STATUS
EFIAPI
InitializeBBTestDevicePathProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDevicePathProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//
EFI_STATUS
EFIAPI
BBTestDevicePathNodeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Other function declaration section
//
//
// Entry GUIDs
//
#define DEVICE_PATH_PROTOCOL_DEVICEPATHNODE_CONFORMANCE_AUTO_GUID \
  { \
    0xc24c24fa, 0x4a52, 0x4968, \
    { \
      0xba, 0x54, 0x16, 0x57, 0xf, 0x9, 0xbc, 0xa3 \
    } \
  }


#endif
