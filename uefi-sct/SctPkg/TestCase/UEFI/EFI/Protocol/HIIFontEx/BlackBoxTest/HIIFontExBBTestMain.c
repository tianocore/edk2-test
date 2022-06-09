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

  HIIFontExBBTestMain.c

Abstract:

  Test Driver of HII FontEx Protocol

--*/

#include "HIIFontExBBTestMain.h"


//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_HII_FONT_EX_PROTOCOL_TEST_REVISION,
  EFI_HII_FONT_EX_PROTOCOL_GUID,
  L"HII FontEx Protocol Test",
  L"UEFI HII FontEx Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0101,
    L"StringToImageExFunction",
    L"Function auto test for HII FontEx Protocol StringToImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestStringToImageExFunctionTest
  },
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0102,
    L"StringIdToImageExFunction",
    L"Function auto test for HII FontEx Protocol StringIdToImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestStringIdToImageExFunctionTest
  },
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0103,
    L"GetGlyphExFunction",
    L"Function auto test for HII FontEx Protocol GetGlyphEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetGlyphExFunctionTest
  },
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0104,
    L"GetFontInfoExFunction",
    L"Function auto test for HII FontEx Protocol GetFontInfoEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetFontInfoExFunctionTest
  },
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0105,
    L"GetGlyphInfoFunction",
    L"Function auto test for HII FontEx Protocol GetGlyphInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetGlyphInfoFunctionTest
  },
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0201,
    L"StringToImageExConformance",
    L"Conformance auto test for HII FontEx Protocol StringToImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestStringToImageExConformanceTest
  },
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0202,
    L"StringIdToImageExConformance",
    L"Conformance auto test for HII FontEx Protocol StringIdToImageEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestStringIdToImageExConformanceTest
  },
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0203,
    L"GetGlyphExConformance",
    L"Conformance auto test for HII FontEx Protocol GetGlyphEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetGlyphExConformanceTest
  },
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0204,
    L"GetFontInfoExConformance",
    L"Conformance auto test for HII FontEx Protocol GetFontInfoEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetFontInfoExConformanceTest
  },
  {
    EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0205,
    L"GetGlyphInfoConformance",
    L"Conformance auto test for HII FontEx Protocol GetGlyphInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetGlyphInfoConformanceTest
  },
  0
};

//
//
//

EFI_STATUS
EFIAPI
InitializeHIIFontExBBTest (
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
           UnloadHIIFontExBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadHIIFontExBBTest (
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
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer;
  EFI_STATUS            Status;
  
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
    return EFI_UNSUPPORTED;
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

EFI_STATUS
GetHIIStringInterface (
  OUT EFI_HII_STRING_PROTOCOL    **HIIString
  )
{
  UINTN                 NoHandles;
  EFI_HANDLE            *HandleBuffer;
  EFI_STATUS            Status;
  
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiHIIStringProtocolGuid,
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
                   &gBlackBoxEfiHIIStringProtocolGuid,
                   (VOID **) HIIString
                   );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool ( HandleBuffer );
    return Status;
  }
  
  gtBS->FreePool ( HandleBuffer );
  
  return EFI_SUCCESS;
}

#if 0
EFI_STATUS
GetPackageListHeader (
  OUT EFI_HANDLE                    *DriverHandle,
  OUT EFI_HII_PACKAGE_LIST_HEADER    **PackageList
  )
{
  EFI_HII_PACKAGE_LIST_HEADER    **PackageListTemp;
  
  //
  // Load the image and get DriverHandle
  //
  
  //
  // Get PackageListTemp
  //
  Status = gtBS->HandleProtocol(
                   *DriverHandle,
                   &gBlackBoxEfiHIIPackageListProtocolGuid,
                   (VOID **) &PackageListTemp
                   );
  if ( EFI_ERROR(Status) ) {
    //
    // Release the resource of DriverHandle
    //

    return Status;
  }
  
  *PackageList = *PackageListTemp;
  
  return EFI_SUCCESS;
}
#endif
