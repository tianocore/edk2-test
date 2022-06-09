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

  RiscVBootBBTestMain.c

Abstract:

  Test Driver of RISC-V Boot Protocol

--*/

#include "SctLib.h"
#include "RiscVBootProtocolBBTestMain.h"

#define RISCV_EFI_BOOT_PROTOCOL_TEST_REVISION    0x00010000

//
// Global variables
//

EFI_HANDLE mImageHandle;


EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  RISCV_EFI_BOOT_PROTOCOL_TEST_REVISION,
  RISCV_EFI_BOOT_PROTOCOL_GUID,
  L"RISC-V Boot Protocol Test",
  L"UEFI RISC-V Boot Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    RISCV_EFI_BOOT_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetBootHartIdFunction",
    L"Function test for RISC-V Boot Protocol GetBootHartId().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetBootHartIdFunctionTest
  },
  {
    RISCV_EFI_BOOT_PROTOCOL_TEST_ENTRY_GUID0201,
    L"GetBootHartIdConformance",
    L"Conformance test for RISC-V Boot Protocol GetBootHartId().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetBootHartIdConformanceTest
  },
  0
};

EFI_BB_TEST_PROTOCOL                  *gBBTestProtocolInterface;

//
// Unload function
//

EFI_STATUS
EFIAPI
UnloadBBTestRiscVBootProtocol (
  IN EFI_HANDLE                   ImageHandle
  );


EFI_STATUS
EFIAPI
InitializeBBTestRiscVBootProtocol (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadBBTestRiscVBootProtocol,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadBBTestRiscVBootProtocol (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
