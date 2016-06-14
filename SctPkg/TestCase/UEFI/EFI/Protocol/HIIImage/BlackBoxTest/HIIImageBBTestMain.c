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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
             GraphicsOutput
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
             HIIDatabase
             );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool ( HandleBuffer );
    return Status;
  }
  
  gtBS->FreePool ( HandleBuffer );
  
  return EFI_SUCCESS;
}
