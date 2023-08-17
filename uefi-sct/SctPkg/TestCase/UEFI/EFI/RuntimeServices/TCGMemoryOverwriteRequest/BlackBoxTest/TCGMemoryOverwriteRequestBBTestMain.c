/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2023, Arm Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

    TCG2MORTestMain.c

Abstract:

    for EFI Driver TCG MemoryOverwriteRequest Test

--*/
#include "SctLib.h"
#include "TCGMemoryOverwriteRequestBBTestMain.h"

EFI_GUID gEfiMemoryOverwriteControlDataGuid = MEMORY_ONLY_RESET_CONTROL_GUID;

EFI_GUID gEfiMemoryOverwriteRequestControlLockGuid = MEMORY_OVERWRITE_REQUEST_CONTROL_LOCK_GUID;

EFI_BB_TEST_PROTOCOL_FIELD gEfiTCGMemoryOverwriteRequestTestProtocolField = {
  TCG_MOR_TEST_REVISION,
  EFI_TCG_MOR_TEST_GUID,
  L"TCG MemoryOverwriteRequest Test",
  L"TCG MemoryOverwriteRequest Functionality Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gLoadTCGMemoryOverwriteRequestEntryField[] = {

  {
    EFI_TCG_MOR_TEST_ENTRY_GUID0101,
    L"Test MOR and MORLOCK",
    L"Test for MOR and MORLOCK EFI variables in accordance with TCG spec",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestTCGMemoryOverwriteRequestFunctionTest
  },

  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gTCGMemoryOverwriteRequestTestProt;


EFI_STATUS
EFIAPI
UnloadTCGMemoryOverwriteRequestTest (
  IN EFI_HANDLE       ImageHandle
  );

/**
 *  Creates/installs the BlackBox Interface and eminating Entry Point node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 */
EFI_STATUS
EFIAPI
InitializeTestTCGMemoryOverwriteRequest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  //
  // initialize test utility lib
  //
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gEfiTCGMemoryOverwriteRequestTestProtocolField,
           gLoadTCGMemoryOverwriteRequestEntryField,
           UnloadTCGMemoryOverwriteRequestTest,
           &gTCGMemoryOverwriteRequestTestProt
           );
}


/**
 *  Unloads the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @return EFI_SUCCESS   The interface was uninstalled successfully.
 */
EFI_STATUS
EFIAPI
UnloadTCGMemoryOverwriteRequestTest (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gTCGMemoryOverwriteRequestTestProt
           );
}
