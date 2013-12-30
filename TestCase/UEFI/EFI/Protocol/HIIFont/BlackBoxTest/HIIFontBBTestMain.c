/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
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

#define EFI_HII_STRING_PROTOCOL_GUID \
	{0xfd96974, 0x23aa, 0x4cdc, 0xb9, 0xcb, 0x98, 0xd1, 0x77, 0x50, 0x32, 0x2a}

#define EFI_HII_DATABASE_PROTOCOL_GUID \
	{0xef9fc172, 0xa1b2, 0x4693, 0xb3, 0x27, 0x6d, 0x32, 0xfc, 0x41, 0x60, 0x42}

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
    {0x9042a9de, 0x23dc, 0x4a38, 0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}

EFI_GUID  gEfiHIIStringProtocolGuid = EFI_HII_STRING_PROTOCOL_GUID;
EFI_GUID  gEfiHIIDatabaseProtocolGuid = EFI_HII_DATABASE_PROTOCOL_GUID;
#ifndef EFIARM
EFI_GUID  gEfiGraphicsOutputProtocolGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
#endif

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
EFI_DRIVER_ENTRY_POINT(InitializeHIIFontBBTest)

EFI_STATUS
InitializeHIIFontBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  InitializeLib (ImageHandle, SystemTable);

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
                   &gEfiGraphicsOutputProtocolGuid,
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
                   &gEfiGraphicsOutputProtocolGuid,
                   GraphicsOutput
                   );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool( HandleBuffer );
    return Status;
  }
  
  gtBS->FreePool( HandleBuffer );
  
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
                   &gEfiHIIDatabaseProtocolGuid,
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
                   &gEfiHIIDatabaseProtocolGuid,
                   HIIDatabase
                   );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool( HandleBuffer );
    return Status;
  }
  
  gtBS->FreePool( HandleBuffer );
  
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
                   &gEfiHIIStringProtocolGuid,
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
                   &gEfiHIIStringProtocolGuid,
                   HIIString
                   );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool( HandleBuffer );
    return Status;
  }
  
  gtBS->FreePool( HandleBuffer );
  
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
                   &gEfiHIIPackageListProtocolGuid,
                   &PackageListTemp
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
