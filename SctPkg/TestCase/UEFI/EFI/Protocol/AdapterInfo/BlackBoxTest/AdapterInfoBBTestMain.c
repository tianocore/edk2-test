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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  AdapterInfoBBTestMain.c

Abstract:

  Test Driver of Adapter Information Protocol

--*/

#include "AdapterInfoBBTestMain.h"


//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_REVISION,
  EFI_ADAPTER_INFORMATION_PROTOCOL_GUID,
  L"Adapter Information Protocol Test",
  L"UEFI Adapter Information Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {

  //Func Entry Fields
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetInformationFunction",
    L"Function auto test for Adapter Information Protocol GetInformation().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetInformationFunctionTest
  },
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0102,
    L"SetInformationFunction",
    L"Function auto test for Adapter Information Protocol SetInformation().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetInformationFunctionTest
  },
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0103,
    L"GetSupportedTypesFunction",
    L"Function auto test for Adapter Information Protocol GetSupportedTypes().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetSupportedTypesFunctionTest
  },
  

  // Conformance Entry Fields
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0201,
    L"GetInformationConformance",
    L"Conformance auto test for Adapter Information Protocol GetInformation().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetInformationConformanceTest
  },
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0202,
    L"SetInformationConformance",
    L"Conformance auto test for Adapter Information Protocol SetInformation().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetInformationConformanceTest
  },
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0203,
    L"GetSupportedTypesConformance",
    L"Conformance auto test for Adapter Information Protocol GetSupportedTypes().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetSupportedTypesConformanceTest
  },
 
  0
  
};


INTN
MemCmp(
  UINT8    *s1,
  UINT8    *s2,
  UINTN     n
  )
{
  UINT8    *p1, *p2;

  p1 = s1;
  p2 = s2;
  if (n != 0) {
    do {
      if (*p1++ != *p2++)
        return (*--p1 - *--p2);
    } while (--n != 0);
  }
  return (0);
}



INTN 
GuidCmp(
  EFI_GUID    GuidGiven,
  EFI_GUID    GuidNeedToCmp
  )
{
  return MemCmp((UINT8 *)&GuidGiven,(UINT8 *)&GuidNeedToCmp,16);
}


//
//Validate the BlockSize returned from function GetInfomation with the Given value
//

BOOLEAN
InfoTypeAndBlockSizeCmp( 
  EFI_GUID    InformationType,
  UINTN       InformationBlockSize
  )
{
   
  if ((!GuidCmp (InformationType,gEfiAdapterInfoMediaStateGuid) && InformationBlockSize == sizeof(EFI_ADAPTER_INFO_MEDIA_STATE)) || 
      (!GuidCmp (InformationType,gEfiAdapterInfoNetworkBootGuid) && InformationBlockSize == sizeof(EFI_ADAPTER_INFO_NETWORK_BOOT)) || 
      (!GuidCmp (InformationType,gEfiAdapterInfoSanMacAddressGuid) && InformationBlockSize == sizeof(EFI_ADAPTER_INFO_SAN_MAC_ADDRESS))) 
    return TRUE;
  else
    return FALSE;  
}


//
//
//
EFI_STATUS
InitializeAdapterInfoBBTest (
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE    *SystemTable
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
             UnloadAdapterInfoBBTest,
             &gBBTestProtocolInterface
             );
}


EFI_STATUS
UnloadAdapterInfoBBTest (
  IN EFI_HANDLE    ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );
}
