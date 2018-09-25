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

  ImageBBTestMain.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "SctLib.h"
#include "Misc.h"

//
// global variable for this test driver's image handle
//

//
// Build Data structure here
//
EFI_TPL TplArray [TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE] = {
  TPL_APPLICATION,
  TPL_CALLBACK
};

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  IMAGE_BOOT_SERVICES_TEST_REVISION,
  IMAGE_BOOT_SERVICES_TEST_GUID,
  L"Image Services Test",
  L"UEFI Image Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid1[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0101,
    L"LoadImage_Conf",
    L"Conformance Test for LoadImage",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLoadImageConsistencyTest
  },
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0102,
    L"StartImage_Conf",
    L"Conformance Test for StartImage",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStartImageConsistencyTest
  },
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0103,
    L"UnloadImage_Conf",
    L"Conformance Test for UnloadImage",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestUnloadImageConsistencyTest
  },
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0104,
    L"Exit_Conf",
    L"Conformance Test for Exit",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestExitConsistencyTest
  },
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0105,
    L"ExitBootServices_Conf",
    L"Conformance Test for ExitBootServices",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestExitBootServicesConsistencyTest
  },
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0200,
    L"LoadImage_Func",
    L"Interface Function Test for LoadImage",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO | EFI_TEST_CASE_RESET_REQUIRED,
    BBTestLoadImageInterfaceTest
  },
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0201,
    L"StartImage_Func",
    L"Interface Function Test for StartImage",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStartImageInterfaceTest
  },
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0203,
    L"UnloadImage_Func",
    L"Interface Function Test for UnloadImage",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestUnloadImageInterfaceTest
  },
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0204,
    L"Exit_Func",
    L"Interface Function Test for Exit",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestExitInterfaceTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0301,
    L"Combination_Stress",
    L"Load, Start, Unload images recursively",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestImageServicesCombinationTest1
  },
#endif

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
InitializeBBTestImageBootServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  InitializeGlobalData ();

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestImageBootServicesUnload,
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
BBTestImageBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  ReleaseGlobalData ();

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
