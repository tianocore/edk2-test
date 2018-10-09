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

  HIIFontBBTestMain.c

Abstract:

  Test Driver of HII Font Protocol

--*/

#include "HIIFontBBTestMain.h"


//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_HII_FONT_PROTOCOL_TEST_REVISION,
  EFI_HII_FONT_PROTOCOL_GUID,
  L"HII Font Protocol Test",
  L"UEFI HII Font Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0101,
    L"StringToImageFunction",
    L"Function auto test for HII Font Protocol StringToImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestStringToImageFunctionTest
  },
  {
    EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0102,
    L"StringIdToImageFunction",
    L"Function auto test for HII Font Protocol StringIdToImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestStringIdToImageFunctionTest
  },
  {
    EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0103,
    L"GetGlyphFunction",
    L"Function auto test for HII Font Protocol GetGlyph().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetGlyphFunctionTest
  },
  {
    EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0104,
    L"GetFontInfoFunction",
    L"Function auto test for HII Font Protocol GetFontInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetFontInfoFunctionTest
  },
  {
    EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0201,
    L"StringToImageConformance",
    L"Conformance auto test for HII Font Protocol StringToImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestStringToImageConformanceTest
  },
  {
    EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0202,
    L"StringIdToImageConformance",
    L"Conformance auto test for HII Font Protocol StringIdToImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestStringIdToImageConformanceTest
  },
  {
    EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0203,
    L"GetGlyphConformance",
    L"Conformance auto test for HII Font Protocol GetGlyph().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetGlyphConformanceTest
  },
  {
    EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0204,
    L"GetFontInfoConformance",
    L"Conformance auto test for HII Font Protocol GetFontInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetFontInfoConformanceTest
  },
  0
};

//
//
//

EFI_STATUS
EFIAPI
InitializeHIIFontBBTest (
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
           UnloadHIIFontBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadHIIFontBBTest (
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
