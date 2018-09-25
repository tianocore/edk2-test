/** @file

  Copyright 2016 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ConfigKeywordHandlerBBTestMain.c

Abstract:

  Test Driver of Config Keyword Handler Protocol

--*/

#include "ConfigKeywordHandlerBBTestMain.h"

//
// global variable for this test driver's image handle
//
EFI_HANDLE      mImageHandle;

#define EFI_CONFIG_KEYWORD_HANDLER_TEST_GUID \
  { 0x0a8badd5, 0x03b8, 0x4d19, {0xb1, 0x28, 0x7b, 0x8f, 0x0e, 0xda, 0xa5, 0x96 }}

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_REVISION,
  EFI_CONFIG_KEYWORD_HANDLER_TEST_GUID,
  L"Config Keyword Handler Protocol Test",
  L"UEFI Config Keyword Handler Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0101,
    L"SetDataFunction",
    L"Function auto test for Config Keyword Handler Protocol SetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetDataFunctionTest
  },
  {
    EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetDataFunction",
    L"Function auto test for Config Keyword Handler Protocol GetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetDataFunctionTest
  }, 
  {
    EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0201,
    L"SetDataConformance",
    L"Conformance auto test for Config Keyword Handler Protocol Protocol SetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetDataConformanceTest
  },
  {
    EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0202,
    L"GetDataConformance",
    L"Conformance auto test for Config Keyword Handler Protocol Protocol GetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetDataConformanceTest
  },
  0
};

CONST EFI_STRING FullStr = L"NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=iSCSIBootEnable&VALUE=00&NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=ChipsetSATAPortEnable:1&VALUE=01&NAMESPACE=x-UEFI-ns&PATH=01041400f4274aa000df424db55239511302113d7fff0400&KEYWORD=ChipsetSATAPortEnable:2&VALUE=01&READONLY";

EFI_STATUS
EFIAPI
InitializeConfigKeywordHandlerBBTest (
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
           UnloadConfigKeywordHandlerBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadConfigKeywordHandlerBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

/**
 *  @brief This function is used to compose a device path of a file located at disk media.
 *  @see ReleaseInvalidHandle.
 */
EFI_STATUS
LoadedImageTestComposeSimpleFilePath (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib    OPTIONAL,
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT EFI_DEVICE_PATH_PROTOCOL            **FilePath
  )
/*++
  The caller has the responsibility to free the FilePath
--*/
{
  EFI_STATUS                    Status;
  CHAR16                        *EntireFileName;
  CHAR16                        *FileNamePath;
  EFI_LOADED_IMAGE_PROTOCOL     *LoadImage;
  EFI_DEVICE_PATH_PROTOCOL      *DevicePath;

  Status = gtBS->HandleProtocol (
                   CurrentImageHandle,
                   &gBlackBoxEfiLoadedImageProtocolGuid,
                   (VOID **) &LoadImage
                   );
  if (EFI_ERROR (Status)) {
    if (StandardLib != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
    return Status;
  }

  //
  //Get system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &DevicePath,
                         &FileNamePath
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  EntireFileName = SctPoolPrint (L"%s\\%s\\%s", FileNamePath, DEPENDENCY_DIR_NAME, FileName);

  *FilePath = SctFileDevicePath (LoadImage->DeviceHandle, EntireFileName);

  SctFreePool (DevicePath);
  SctFreePool (FileNamePath);
  SctFreePool (EntireFileName);

  if (*FilePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}

