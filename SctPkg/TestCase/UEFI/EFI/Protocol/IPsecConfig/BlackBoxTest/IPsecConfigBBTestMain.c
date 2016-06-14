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

  IPsecConfigBBTestMain.c

Abstract:

  Test Driver of IPsec Config Protocol

--*/

#include "SctLib.h"
#include "IPsecConfigBBTestMain.h"


//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_IPSEC_CONFIG_PROTOCOL_TEST_REVISION,
  EFI_IPSEC_CONFIG_PROTOCOL_GUID,
  L"IPsec Config Protocol Test",
  L"UEFI IPsec Config Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0101,
    L"SetDataFunction",
    L"Function auto test for IPsec Config Protocol SetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetDataFunctionTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetDataFunction",
    L"Function auto test for IPsec Config Protocol GetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetDataFunctionTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0103,
    L"GetNextSelectorFunction",
    L"Function auto test for IPsec Config Protocol GetNextSelector().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextSelectorFunctionTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0104,
    L"RegisterDataNotifyFunction",
    L"Function auto test for IPsec Config Protocol RegisterDataNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterDataNotifyFunctionTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0105,
    L"UnregisterDataNotifyFunction",
    L"Function auto test for IPsec Config Protocol UnregisterDataNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterDataNotifyFunctionTest
  },  
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0201,
    L"SetDataConformance",
    L"Conformance auto test for IPsec Config Protocol SetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetDataConformanceTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0202,
    L"GetDataConformance",
    L"Conformance auto test for IPsec Config Protocol GetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetDataConformanceTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0203,
    L"GetNextSelectorConformance",
    L"Conformance auto test for IPsec Config Protocol GetNextSelector().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextSelectorConformanceTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0204,
    L"RegisterDataNotifyConformance",
    L"Conformance auto test for IPsec Config Protocol RegisterDataNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterDataNotifyConformanceTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0205,
    L"UnregisterDataNotifyConformance",
    L"Conformance auto test for IPsec Config Protocol UnregisterDataNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterDataNotifyConformanceTest
  },
  
  0
};


//
//
//

EFI_STATUS
InitializeIPsecConfigBBTest (
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
           UnloadIPsecConfigBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
UnloadIPsecConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


VOID
EventNotifyFunc (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  //
  // do nothing
  //
  return;
}

