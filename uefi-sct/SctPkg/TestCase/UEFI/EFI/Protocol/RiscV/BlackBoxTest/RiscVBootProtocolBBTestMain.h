/** @file

  Copyright (c) 2022, Ventana Micro Systems Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  RiscVBootProtocolBBTestMain.h

Abstract:

  Test Driver of RISC-V Boot Protocol header file

--*/

#ifndef _RISCV_BOOT_PROTOCOL_BB_TEST_MAIN_H
#define _RISCV_BOOT_PROTOCOL_BB_TEST_MAIN_H


#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/RiscVBoot.h>
#include "Guid.h"


//
// One private signature
//
#define UEFI_SCTT_TABLE_SIGNATURE    EFI_SIGNATURE_32 ('S', 'C', 'T', 'T')

//
// Entry GUIDs for Func Test
//
#define RISCV_EFI_BOOT_PROTOCOL_TEST_ENTRY_GUID0101 \
{0xa17fc0c9, 0x82d8, 0x499f, { 0x81, 0x03, 0xe1, 0x3c, 0x7d, 0x08, 0xed, 0x57 } }

//
// Entry GUIDs for Conf Test
//
#define RISCV_EFI_BOOT_PROTOCOL_TEST_ENTRY_GUID0201 \
{0x69378fba, 0x4f73, 0x4632, { 0xad, 0x1e, 0x5b, 0x1c, 0x18, 0x84, 0x99, 0x88 } }



EFI_STATUS
EFIAPI
InitializeBBTestRiscVBootProtocol (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadBBTestRiscVBootProtocol (
  IN EFI_HANDLE                   ImageHandle
  );

//
// Prototypes: Test Cases
//

EFI_STATUS
BBTestGetBootHartIdConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetBootHartIdConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN RISCV_EFI_BOOT_PROTOCOL               *RiscVBoot
  );

EFI_STATUS
BBTestGetBootHartIdConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN RISCV_EFI_BOOT_PROTOCOL               *RiscVBoot
  );

EFI_STATUS
BBTestGetBootHartIdConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN RISCV_EFI_BOOT_PROTOCOL               *RiscVBoot
  );

EFI_STATUS
BBTestGetBootHartIdFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetBootHartIdFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN RISCV_EFI_BOOT_PROTOCOL               *RiscVBoot
  );

#endif
