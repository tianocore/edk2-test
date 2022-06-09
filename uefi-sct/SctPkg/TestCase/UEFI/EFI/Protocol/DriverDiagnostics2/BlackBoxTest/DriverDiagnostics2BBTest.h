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
    Test.h

Abstract:
    head file of test driver of EFI Driver Diagnostics2 Protocol Test

--*/

#ifndef _DRIVER_DIAGNOSTICS2_TEST_H
#define _DRIVER_DIAGNOSTICS2_TEST_H


#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/DriverDiagnostics2.h>
#include "Guid.h"

#define EFI_DRIVER_DIAGNOSTICS2_TEST_REVISION 0x00020000

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x595b5ad0, 0x304e, 0x420d, { 0x82, 0x5d, 0x6f, 0x43, 0x1c, 0x80, 0xb6, 0x5f } }

//
// Entry GUIDs for Function Test
//
#define EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x96a6c558, 0x7b86, 0x4e54, { 0x90, 0xec, 0xd5, 0x9a, 0xa2, 0x07, 0x52, 0x92 } }


//////////////////////////////////////////////////////////////////////////////

//
// TestNoInterfaceProtocol1
//
#define TEST_NO_INTERFACE_PROTOCOL_1_GUID \
{ 0x595b5ad0, 0x304e, 0x420d, {0x82, 0x5d, 0x6f, 0x43, 0x1c, 0x80, 0xb6, 0x5f }}


extern EFI_GUID mTestNoInterfaceProtocol1Guid;

//
// TestNoInterfaceProtocol2
//
#define TEST_NO_INTERFACE_PROTOCOL_2_GUID \
{ 0x6a46e658, 0xf5ca, 0x4c54, {0x98, 0x24, 0xd1, 0x12, 0xc9, 0x33, 0x70, 0xe6 }}

extern EFI_GUID mTestNoInterfaceProtocol2Guid;

//
// functions declaration
//

EFI_STATUS
EFIAPI
InitializeBBTestDriverDiagnostics2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDriverDiagnostics2Unload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Conformance test functions
//


EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint functions for Conformance tests
//


EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  );


EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  );


EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  );

EFI_STATUS
EFIAPI
BBTestRunDiagnosticsFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestRunDiagnosticsFuncTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  );

EFI_STATUS
EFIAPI
BBTestRunDiagnosticsFuncTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL      *DriverDiagnostics2
  );

EFI_STATUS
LocateLoadedImageDevicePathFromDriverDiagnostisc2 (
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL         *DriverDiagnostisc2,
  IN EFI_DEVICE_PATH_PROTOCOL                 **DevicePath,      //reuse the structure of EFI_DEVICE_PATH_PROTOCOL as EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib
  );

#endif
