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

#define  IHV_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID         \
  { 0x5e344e28, 0x3bc0, 0x4c23, 0x8d, 0x5f, 0xfb, 0xed, 0x3f, 0xb2, 0x7e, 0x72 }

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
BBTestGetDriverFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDriverPathFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestDriverLoadedFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDriverConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDriverPathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
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
#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_FUNCTION_AUTO_GUID         \
  { 0x898caad7, 0xf932, 0x4f13, 0x8b, 0x42, 0x2e, 0x2b, 0x7c, 0x53, 0x52, 0xb3 }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_PATH_FUNCTION_AUTO_GUID    \
  { 0xd4db9e09, 0x3da8, 0x42c9, 0xbc, 0x85, 0x4f, 0x9c, 0xbc, 0x63, 0x36, 0xcc }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_DRIVER_LOADED_FUNCTION_AUTO_GUID      \
  { 0xe6db5b7f, 0x289f, 0x4731, 0xaf, 0x1a, 0x17, 0xa2, 0x4e, 0x30, 0xeb, 0x4f }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_CONFORMANCE_AUTO_GUID      \
  { 0x719b0d60, 0x5606, 0x47ab, 0x88, 0xf9, 0x9e, 0x4a, 0xe1, 0xf5, 0x98, 0x29 }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GET_DRIVER_PATH_CONFORMANCE_AUTO_GUID \
  { 0xa1578d06, 0xd8e2, 0x427d, 0x9a, 0x20, 0x57, 0x8d, 0x0a, 0x4a, 0x12, 0x73 }

#define PLATFORM_DRIVER_OVERRIDE_PROTOCOL_DRIVER_LOADED_CONFORMANCE_AUTO_GUID   \
  { 0x7f57365f, 0xdd8b, 0x4094, 0x8b, 0xeb, 0xaa, 0xda, 0x63, 0x10, 0x68, 0x15 }


#endif

