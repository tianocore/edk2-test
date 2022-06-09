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

  BusSpecificDriverOverrideBBTestMain.h

Abstract:

  BB test header file of Bus Specific Driver Override Protocol

--*/


#ifndef _BUS_SPECIFIC_DRIVER_OVERRIDE_BBTEST_H_
#define _BUS_SPECIFIC_DRIVER_OVERRIDE_BBTEST_H_


#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/BusSpecificDriverOverride.h>

#define  BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_TEST_REVISION    0x00010000


extern   EFI_EVENT                         TimerEvent;

EFI_STATUS
EFIAPI
InitializeBBTestBusSpecificDriverOverride (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestBusSpecificDriverOverrideProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );


EFI_STATUS
EFIAPI
BBTestGetDriverFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDriverConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
LocateDevicePathFromBusOverride(
  IN EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL    *BusOverride,
  IN EFI_DEVICE_PATH_PROTOCOL                     **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib
  );

//
// Entry GUIDs
//

#define BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GETDRIVER_FUNCTION_MANUAL_GUID \
  { 0xaa0ec76e, 0x28c, 0x4fde, { 0xac, 0x44, 0xe3, 0xd4, 0x9b, 0x7c, 0x67, 0x33 } }

#define BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GETDRIVER_CONFORMANCE_GUID \
  { 0x4a1352a6, 0x49a2, 0x4075, { 0xa0, 0x6f, 0xd8, 0x9, 0xb4, 0x6e, 0x5e, 0xf2 } }

#endif
