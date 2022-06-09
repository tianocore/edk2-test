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

  DriverDiagnosticsBBTest.h

Abstract:
    head file of test driver of EFI Driver Diagnostics Protocol Test

--*/

#ifndef _DRIVER_DIAGNOSTICS_TEST_H
#define _DRIVER_DIAGNOSTICS_TEST_H


#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/DriverDiagnostics.h>
#include "Guid.h"

#define EFI_DRIVER_DIAGNOSTICS_TEST_REVISION 0x00010000

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define EFI_DRIVER_DIAGNOSTICS_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0xfba051d8, 0xbd27, 0x405c, {0x9f, 0xff, 0x6, 0xb4, 0x59, 0x7a, 0xc2, 0xe0} }


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
InitializeBBTestDriverDiagnostics (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDriverDiagnosticsUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Conformance test functions
//

//
// TDS 7.2.1
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

//
// TDS 7.2.1.2.1
//
EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics
  );

//
// TDS 7.2.1.2.2
//
EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics
  );

//
// TDS 7.2.1.2.3
//
EFI_STATUS
EFIAPI
BBTestRunDiagnosticsConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics
  );

#endif
