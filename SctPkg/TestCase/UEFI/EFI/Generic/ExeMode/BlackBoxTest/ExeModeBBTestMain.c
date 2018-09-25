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

  ExeModeBBTestMain.c

Abstract:

  BB test file for UEFI processor execution mode

--*/
#include "SctLib.h"
#include "ExeModeBBTest.h"



EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EXE_MODE_TEST_REVISION,
  EFI_EXE_MODE_TEST_GUID,
  L"Testing For required CPU execution mode",
  L"Test cases for the CPU execution mode"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};


EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EXE_MODE_TEST_ENTRY_GUID0101,
    L"FPUControlWordCheck",
    L"Check the value of FPU control word",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFpuControlWordTest
  },
  {
    EXE_MODE_TEST_ENTRY_GUID0102,
    L"MXCSRCheck",
    L"Check the value of MX CSR",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestMxCsrTest
  },
  
  0
};   
  
EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

/**
 *  Creates/installs the BlackBox Interface and eminating Entry Point 
 *  node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 */
EFI_STATUS
EFIAPI
InitializeBBTestExeMode (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  
  return EfiInitAndInstallBBTestInterface (
              &ImageHandle,
              &gBBTestProtocolField,
              gBBTestEntryField,
              BBTestExeModeUnload,
              &gBBTestProtocolInterface
              );
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
EFIAPI
BBTestExeModeUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
            ImageHandle,
            gBBTestProtocolInterface
            );
}
