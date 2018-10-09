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

#define IHV_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID          \
  { 0x01958114, 0xd270, 0x463b, 0xa3, 0x1d, 0xfa, 0xec, 0x34, 0x68, 0xfd, 0x71 }


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
BBTestGetDriverFunctionManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
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

#define BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GETDRIVER_FUNCTION_MANUAL_GUID  \
  { 0x3689d1c2, 0xa087, 0x4305, 0xb4, 0xbb, 0xdc, 0x64, 0xd2, 0x61, 0xb1, 0x96 }

#define BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GETDRIVER_CONFORMANCE_GUID      \
  { 0xb540355d, 0x470a, 0x4401, 0x98, 0xca, 0x6f, 0x27, 0x14, 0xeb, 0x33, 0x4b }

#endif
