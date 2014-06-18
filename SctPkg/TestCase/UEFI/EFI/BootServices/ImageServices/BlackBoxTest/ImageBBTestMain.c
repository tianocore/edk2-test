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