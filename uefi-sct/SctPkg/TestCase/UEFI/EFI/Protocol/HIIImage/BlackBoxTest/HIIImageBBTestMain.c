/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  HIIImageBBTestMain.c

Abstract:

  Test Driver of HII Image Protocol

--*/

#include "HIIImageBBTestMain.h"

//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_HII_IMAGE_PROTOCOL_TEST_REVISION,
  EFI_HII_IMAGE_PROTOCOL_GUID,
  L"HII Image Protocol Test",
  L"UEFI HII Image Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0101,
    L"NewImageFunction",
    L"Function auto test for HII Image Protocol NewImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestNewImageFunctionTest
  },
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetImageFunction",
    L"Function auto test for HII Image Protocol GetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageFunctionTest
  },
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0103,
    L"SetImageFunction",
    L"Function auto test for HII Image Protocol SetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetImageFunctionTest
  },
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0104,
    L"DrawImageFunction",
    L"Function auto test for HII Image Protocol DrawImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestDrawImageFunctionTest
  },
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0105,
    L"DrawImageIdFunction",
    L"Function auto test for HII Image Protocol DrawImageId().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestDrawImageIdFunctionTest
  },
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0201,
    L"NewImageConformance",
    L"Conformance auto test for HII Image Protocol NewImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestNewImageConformanceTest
  },
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0202,
    L"GetImageConformance",
    L"Conformance auto test for HII Image Protocol GetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageConformanceTest
  },
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0203,
    L"SetImageConformance",
    L"Conformance auto test for HII Image Protocol SetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetImageConformanceTest
  },
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0204,
    L"DrawImageConformance",
    L"Conformance auto test for HII Image Protocol DrawImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestDrawImageConformanceTest
  },
  {
    EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0205,
    L"DrawImageIdConformance",
    L"Conformance auto test for HII Image Protocol DrawImageId().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestDrawImageIdConformanceTest
  },
  0
};

//
//
//

EFI_STATUS
EFIAPI
InitializeHIIImageBBTest (
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
           UnloadHIIImageBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadHIIImageBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

EFI_STATUS
GetGraphicsOutputInterface (
  OUT EFI_GRAPHICS_OUTPUT_PROTOCOL    **GraphicsOutput
  )
{
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer;
  EFI_STATUS            Status;
  
  Status = gtBS->LocateHandleBuffer (
                        ByProtocol,
                        &gBlackBoxEfiGraphicsOutputProtocolGuid,
                        NULL,
                        &NoHandles,
                        &HandleBuffer
                        );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  if ( NoHandles <= 0 ) {
    return EFI_UNSUPPORTED;
  }
  
  Status = gtBS->HandleProtocol (
             HandleBuffer[0],
             &gBlackBoxEfiGraphicsOutputProtocolGuid,
             (VOID **) GraphicsOutput
             );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool ( HandleBuffer );
    return Status;
  }
  
  gtBS->FreePool ( HandleBuffer );
  
  return EFI_SUCCESS;
}

EFI_STATUS
GetHIIDatabaseInterface (
  OUT EFI_HII_DATABASE_PROTOCOL    **HIIDatabase
  )
{
  UINTN                                 NoHandles;
  EFI_HANDLE                            *HandleBuffer;
  EFI_STATUS                            Status;
  
  //
  // Get the HII Database Protocol interface
  //
  Status = gtBS->LocateHandleBuffer (
                        ByProtocol,
                        &gBlackBoxEfiHIIDatabaseProtocolGuid,
                        NULL,
                        &NoHandles,
                        &HandleBuffer
                        );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  if ( NoHandles <= 0 ) {
    return EFI_DEVICE_ERROR;
  }
  
  Status = gtBS->HandleProtocol (
             HandleBuffer[0],
             &gBlackBoxEfiHIIDatabaseProtocolGuid,
             (VOID **) HIIDatabase
             );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool ( HandleBuffer );
    return Status;
  }
  
  gtBS->FreePool ( HandleBuffer );
  
  return EFI_SUCCESS;
}
