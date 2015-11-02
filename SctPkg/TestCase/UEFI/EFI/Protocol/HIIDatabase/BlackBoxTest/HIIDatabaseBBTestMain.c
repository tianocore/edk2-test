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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  HIIDatabaseBBTestMain.c

Abstract:

  Test Driver of HII Database Protocol

--*/

#include "HIIDatabaseBBTestMain.h"


//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_HII_DATABASE_PROTOCOL_TEST_REVISION,
  EFI_HII_DATABASE_PROTOCOL_GUID,
  L"HII Database Protocol Test",
  L"UEFI 2.1 HII Database Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0101,
    L"NewPackageListFunction",
    L"Function auto test for HII Database Protocol NewPackageList().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestNewPackageListFunctionTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0102,
    L"RemovePackageListFunction",
    L"Function auto test for HII Database Protocol RemovePackageList().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRemovePackageListFunctionTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0103,
    L"UpdatePackageListFunction",
    L"Function auto test for HII Database Protocol UpdatePackageList().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUpdatePackageListFunctionTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0104,
    L"ListPackageListsFunction",
    L"Function auto test for HII Database Protocol ListPackageLists().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestListPackageListsFunctionTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0105,
    L"ExportPackageListsFunction",
    L"Function auto test for HII Database Protocol ExportPackageLists().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestExportPackageListsFunctionTest
  },
  /*
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0106,
    L"RegisterPackageNotifyFunction",
    L"Function auto test for HII Database Protocol RegisterPackageNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterPackageNotifyFunctionTest
  },*/
  /*
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0107,
    L"UnregisterPackageNotifyFunction",
    L"Function auto test for HII Database Protocol UnregisterPackageNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterPackageNotifyFunctionTest
  },
  */
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0108,
    L"FindKeyboardLayoutsFunction",
    L"Function auto test for HII Database Protocol FindKeyboardLayouts().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestFindKeyboardLayoutsFunctionTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0109,
    L"GetKeyboardLayoutFunction",
    L"Function auto test for HII Database Protocol GetKeyboardLayout().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetKeyboardLayoutFunctionTest
  },
  
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID01010,
    L"SetKeyboardLayoutFunction",
    L"Function auto test for HII Database Protocol SetKeyboardLayout().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetKeyboardLayoutFunctionTest
  },
  
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID01011,
    L"GetPackageListHandleFunction",
    L"Function auto test for HII Database Protocol GetPackageListHandle().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetPackageListHandleFunctionTest
  },
  
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0201,
    L"NewPackageListConformance",
    L"Conformance auto test for HII Database Protocol NewPackageList().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestNewPackageListConformanceTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0202,
    L"RemovePackageListConformance",
    L"Conformance auto test for HII Database Protocol RemovePackageList().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRemovePackageListConformanceTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0203,
    L"UpdatePackageListConformance",
    L"Conformance auto test for HII Database Protocol UpdatePackageList().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUpdatePackageListConformanceTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0204,
    L"ListPackageListsConformance",
    L"Conformance auto test for HII Database Protocol ListPackageLists().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestListPackageListsConformanceTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0205,
    L"ExportPackageListsConformance",
    L"Conformance auto test for HII Database Protocol ExportPackageLists().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestExportPackageListsConformanceTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0206,
    L"RegisterPackageNotifyConformance",
    L"Conformance auto test for HII Database Protocol RegisterPackageNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterPackageNotifyConformanceTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0207,
    L"UnregisterPackageNotifyConformance",
    L"Conformance auto test for HII Database Protocol UnregisterPackageNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterPackageNotifyConformanceTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0208,
    L"FindKeyboardLayoutsConformance",
    L"Conformance auto test for HII Database Protocol FindKeyboardLayouts().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestFindKeyboardLayoutsConformanceTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0209,
    L"GetKeyboardLayoutConformance",
    L"Conformance auto test for HII Database Protocol GetKeyboardLayout().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetKeyboardLayoutConformanceTest
  },
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID02010,
    L"SetKeyboardLayoutConformance",
    L"Conformance auto test for HII Database Protocol SetKeyboardLayout().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetKeyboardLayoutConformanceTest
  },
  
  {
    EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID02011,
    L"GetPackageListHandleConformance",
    L"Conformance auto test for HII Database Protocol GetPackageListHandle().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetPackageListHandleConformanceTest
  },
  
  0
};

//
//
//

EFI_STATUS
InitializeHIIDatabaseBBTest (
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
           UnloadHIIDatabaseBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
UnloadHIIDatabaseBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


EFI_STATUS
DoNothingPackageNotifyFn (
  IN UINT8                           PackageType,
  IN CONST EFI_GUID                  *PackageGuid,
  IN CONST EFI_HII_PACKAGE_HEADER    *Package,
  IN EFI_HII_HANDLE                  Handle,
  IN EFI_HII_DATABASE_NOTIFY_TYPE    NotifyType
)
{
  return EFI_SUCCESS;
}
