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
                                                                
  Copyright 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
  { 0x77f0f6ac, 0x16b1, 0x45d5, {0x9f, 0xf3, 0xa0, 0x29, 0x15, 0xfc, 0x6, 0x46 }}

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
                   &LoadImage
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

