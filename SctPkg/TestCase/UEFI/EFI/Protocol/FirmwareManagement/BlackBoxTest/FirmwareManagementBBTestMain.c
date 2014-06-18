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
                                                                
  Copyright (c) 2010 - 2012, Dell Inc.  All rights reserved.   
   
--*/

/*++

Module Name:

  FirmwareManagementBBTestMain.c

Abstract:

  Firmware Management Protocol test driver.

--*/

#include "SctLib.h"
#include "FirmwareManagementBBTestMain.h"

// ****************************************************************************
//   Variables
// ****************************************************************************

EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_REVISION,
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GUID,
  L"Firmware Management Protocol Test",
  L"UEFI 2.3 Firmware Management Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  /*
  //Use for unit test only
  {
    { 0x8cdda816, 0x3f97, 0x4155, { 0xa6, 0x73, 0x86, 0x93, 0x79, 0x8f, 0xb0, 0x6d } },
	L"Unit Test Only",
	L"Verify the Assistant Function",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnitTest
  },
  */
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0101,
    L"Function_Test-GetImageInfo",
    L"Function auto test for Firmware Management Protocol GetImageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageInfoFunctionTest
  },
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0102,
    L"Function_Test-GetImage",
    L"Function auto test for Firmware Management Protocol GetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageFunctionTest
  },
/*++
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0103,
    L"Function Test - SetImage",
    L"Function auto test for Firmware Management Protocol SetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetImageFunctionTest
  },
--*/
/*++
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0104,
    L"Function Test - CheckImage",
    L"Function auto test for Firmware Management Protocol CheckImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCheckImageFunctionTest
  },
--*/
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0105,
    L"Function_Test-GetPackageInfo",
    L"Function auto test for Firmware Management Protocol GetPackageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetPackageInfoFunctionTest
  },
/*++
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0106,
    L"Function Test - SetPackageInfo",
    L"Function auto test for Firmware Management Protocol SetPackageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetPackageInfoFunctionTest
  },
--*/  
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0201,
    L"Conformance_Test-GetImageInfo",
    L"Conformance auto test for Firmware Management Protocol GetImageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageInfoConformanceTest
  },
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0202,
    L"Conformance_Test-GetImage",
    L"Conformance auto test for Firmware Management Protocol GetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetImageConformanceTest
  },
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0203,
    L"Conformance_Test-SetImage",
    L"Conformance auto test for Firmware Management Protocol SetImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetImageConformanceTest
  },
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0204,
    L"Conformance_Test-CheckImage",
    L"Conformance auto test for Firmware Management Protocol CheckImage().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCheckImageConformanceTest
  },
/*++
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0205,
    L"Conformance Test - GetPackageInfo",
    L"Conformance auto test for Firmware Management Protocol GetPackageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetPackageInfoConformanceTest
  },
--*/
  {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0206,
    L"Conformance_Test-SetPackageInfo",
    L"Conformance auto test for Firmware Management Protocol SetPackageInfo().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetPackageInfoConformanceTest
  },
  0
};

// ****************************************************************************
//   Initialization and Unload functions
// ****************************************************************************


EFI_STATUS
InitializeFirmwareManagementBBTest (
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
           UnloadFirmwareManagementBBTest,
           &gBBTestProtocolInterface
           );
}

EFI_STATUS
UnloadFirmwareManagementBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

// ****************************************************************************
//   Support functions
// ****************************************************************************

