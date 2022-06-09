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

  PlatformDriverOverrideBBTestMain.h

Abstract:

  BB test header file of Platform Driver Override protocol

--*/


#ifndef _PLATFORM_DRIVER_OVERRIDE_BBTEST_H_
#define _PLATFORM_DRIVER_OVERRIDE_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/PlatformDriverOverride.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  PLATFORM_DRIVER_OVERRIDE_PROTOCOL_TEST_REVISION    0x00010000

EFI_STATUS
EFIAPI
InitializeBBTestPlatformDriverOverride (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestPlatformDriverOverrideProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
EFIAPI
BBTestGetDriverFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDriverPathFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestDriverLoadedFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDriverConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDriverPathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestDriverLoadedConformanceAutoTest (
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
#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_FUNCTION_AUTO_GUID \
  { 0x6ac7f144, 0xb20, 0x4354, { 0xaf, 0xc1, 0xa1, 0xba, 0xcc, 0x3, 0x36, 0x5f } }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_PATH_FUNCTION_AUTO_GUID \
  { 0x34e4def5, 0x827c, 0x43b4, { 0xb1, 0xac, 0xfd, 0x27, 0x88, 0x1e, 0x89, 0x76 } }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_DRIVER_LOADED_FUNCTION_AUTO_GUID \
  { 0x20f6c57e, 0x6504, 0x46e3, { 0x95, 0x12, 0xad, 0xfd, 0x5a, 0x2c, 0x68, 0xa3 } }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_CONFORMANCE_AUTO_GUID \
  { 0xa8e3ccb9, 0xf627, 0x40e6, { 0x8f, 0x9, 0xe0, 0xc5, 0xec, 0x1a, 0xa2, 0xfa } }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_PATH_CONFORMANCE_AUTO_GUID \
  { 0x2c57e24b, 0x5940, 0x4c75, { 0x8c, 0x75, 0x8f, 0xe4, 0x61, 0x3, 0x24, 0x73 } }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_DRIVER_LOADED_CONFORMANCE_AUTO_GUID \
  { 0xb1aa38a3, 0x9b7, 0x424c, { 0x82, 0x68, 0x99, 0xd4, 0x40, 0x8d, 0xf4, 0xb3 } }


#endif

