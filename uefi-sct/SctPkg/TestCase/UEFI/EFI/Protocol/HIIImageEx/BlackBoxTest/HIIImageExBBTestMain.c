/** @file

  Copyright 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2017, Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  HIIImageExBBTestMain.c

Abstract:

  Test Driver of HII ImageEX Protocol

--*/

#include "HIIImageExBBTestMain.h"

//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_HII_IMAGE_EX_PROTOCOL_TEST_REVISION,
  EFI_HII_IMAGE_EX_PROTOCOL_GUID,
  L"HII ImageEx Protocol Test",
  L"UEFI HII ImageEx Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0101,
    L"NewImageExFunction",
    L"Function auto test for HII Image Ex Protocol NewImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestNewImageExFunctionTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetImageExFunction",
    L"Function auto test for HII Image Ex Protocol GetImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageExFunctionTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0103,
    L"SetImageExFunction",
    L"Function auto test for HII Image Ex Protocol SetImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetImageExFunctionTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0104,
    L"DrawImageExFunction",
    L"Function auto test for HII Image Ex Protocol DrawImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestDrawImageExFunctionTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0105,
    L"DrawImageIdExFunction",
    L"Function auto test for HII Image Ex Protocol DrawImageIdEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestDrawImageIdExFunctionTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0106,
    L"GetImageInfoFunction",
    L"Function auto test for HII Image Ex Protocol GetImageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageInfoFunctionTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0201,
    L"NewImageExConformance",
    L"Conformance auto test for HII Image Ex Protocol NewImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestNewImageExConformanceTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0202,
    L"GetImageExConformance",
    L"Conformance auto test for HII Image Ex Protocol GetImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageExConformanceTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0203,
    L"SetImageExConformance",
    L"Conformance auto test for HII Image Ex Protocol SetImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetImageExConformanceTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0204,
    L"DrawImageExConformance",
    L"Conformance auto test for HII Image Ex Protocol DrawImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestDrawImageExConformanceTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0205,
    L"DrawImageIdExConformance",
    L"Conformance auto test for HII Image Ex Protocol DrawImageIdEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestDrawImageIdExConformanceTest
  },
  {
    EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0206,
    L"GetImageInfoConformance",
    L"Conformance auto test for HII Image Ex Protocol GetImageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageInfoConformanceTest
  },
  0
};

//
//
//

EFI_STATUS
EFIAPI
InitializeHIIImageExBBTest (
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
           UnloadHIIImageExBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadHIIImageExBBTest (
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
