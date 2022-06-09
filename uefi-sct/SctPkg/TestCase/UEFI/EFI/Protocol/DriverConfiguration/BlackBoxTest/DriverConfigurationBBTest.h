/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DriverConfigurationBBTest.h

Abstract:
    head file of test driver of EFI Driver Configuration Protocol Test

--*/

#ifndef _DRIVER_CONFIGURATION_TEST_H
#define _DRIVER_CONFIGURATION_TEST_H


#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/DriverConfiguration.h>
#include "Guid.h"

#define EFI_DRIVER_CONFIGURATION_TEST_REVISION 0x00010000

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define EFI_DRIVER_CONFIGURATION_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0x24a8f4cb, 0x4415, 0x4855, {0xb8, 0x45, 0xce, 0xaa, 0x83, 0xcc, 0x26, 0xa0} }

#define EFI_DRIVER_CONFIGURATION_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0xfe195e07, 0xd42c, 0x48f6, {0x9b, 0x4f, 0xd8, 0x54, 0xc0, 0x7b, 0x3a, 0xf1} }

#define EFI_DRIVER_CONFIGURATION_PROTOCOL_TEST_ENTRY_GUID0103 \
 {0xcd0131e2, 0x2d28, 0x4150, {0x9c, 0x41, 0xda, 0x7, 0x83, 0x71, 0x22, 0x68} }

//////////////////////////////////////////////////////////////////////////////

//
// TestNoInterfaceProtocol1
//
#define TEST_NO_INTERFACE_PROTOCOL_1_GUID \
  {0x7362363, 0x3617, 0x4d92, 0xa1, 0xb1, 0x1d, 0x62, 0xa5, 0x78, 0x91, 0xa5 };

extern EFI_GUID mTestNoInterfaceProtocol1Guid;

//
// TestNoInterfaceProtocol2
//
#define TEST_NO_INTERFACE_PROTOCOL_2_GUID \
  {0x3fd2484, 0xa340, 0x41a7, 0xba, 0x13, 0xb4, 0x93, 0xb0, 0x67, 0xdb, 0x4c };

extern EFI_GUID mTestNoInterfaceProtocol2Guid;


//
// functions declaration
//

EFI_STATUS
InitializeBBTestDriverConfiguration (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDriverConfigurationUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Conformance test functions
//

//
// TDS 5.2.1
//
EFI_STATUS
EFIAPI
BBTestSetOptionsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.2
//
EFI_STATUS
EFIAPI
BBTestOptionsValidConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.3
//
EFI_STATUS
EFIAPI
BBTestForceDefaultsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint functions for Conformance tests
//

//
// TDS 5.2.1.2.1
//
EFI_STATUS
EFIAPI
BBTestSetOptionsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL     *DriverConfig
  );

//
// TDS 5.2.1.2.2
//
EFI_STATUS
EFIAPI
BBTestSetOptionsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL     *DriverConfig
  );

//
// TDS 5.2.1.2.3
//
EFI_STATUS
EFIAPI
BBTestSetOptionsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL     *DriverConfig
  );

//
// TDS 5.2.2.2.1
//
EFI_STATUS
EFIAPI
BBTestOptionsValidConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL     *DriverConfig
  );

//
// TDS 5.2.2.2.2
//
EFI_STATUS
EFIAPI
BBTestOptionsValidConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL     *DriverConfig
  );

//
// TDS 5.2.3.2.1
//
EFI_STATUS
EFIAPI
BBTestForceDefaultsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL     *DriverConfig
  );

//
// TDS 5.2.3.2.2
//
EFI_STATUS
EFIAPI
BBTestForceDefaultsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL     *DriverConfig
  );

#endif
