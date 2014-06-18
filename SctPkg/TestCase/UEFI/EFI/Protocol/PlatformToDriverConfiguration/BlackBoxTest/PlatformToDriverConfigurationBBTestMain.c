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
                                                                
  Copyright (c) 2010 - 2012, Byosoft Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  PlatformToDriverConfigurationBBTestMain.c

Abstract:

  Test Driver of Platform To Driver Configuration Protocol

--*/

#include "SctLib.h"
#include "PlatformToDriverConfigurationBBTestMain.h"

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_TEST_REVISION,
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID,
  L"Platform To Driver Configuration Protocol Test",
  L"UEFI Platform To Driver Configuration Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_QUERY_FUNCTION_AUTO_GUID,
    L"Query_Func",
    L"Invoke Query() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestQueryFunctionAutoTest
  },

  {
    PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_RESPONSE_FUNCTION_AUTO_GUID,
    L"Response_Func",
    L"Invoke Response() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResponseFunctionAutoTest
  },

  {
    PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_QUERY_CONFORMANCE_AUTO_GUID,
    L"Query_Conf",
    L"Test whether Query() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestQueryConformanceAutoTest
  },

  {
    PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_RESPONSE_CONFORMANCE_AUTO_GUID,
    L"Response_Conf",
    L"Test whether Response() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResponseConformanceAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPCOMMAND_AUTO_GUID,
    L"CLPCommand",
    L"Perform auto parameter checkes of CLPCommand",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPCommandAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPRETURNSTRING_AUTO_GUID,
    L"CLPRetuenString",
    L"Perform auto parameter checkes of the firmwareVersion",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPReturnStringAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPRETURNSTATUS_AUTO_GUID,
    L"CLPReturnStatus",
    L"Perform auto parameter checkes of CLPReturnStatus",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPCmdStatusAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPERRORVALUE_AUTO_GUID,
    L"CLPErrorValue",
    L"Perform auto parameter checkes of CLPErrorValue",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPErrorValueAutoTest
  },
  {
    CONFIGURE_CLP_PARAMETER_BLK_PROTOCOL_CLPMESSAGECODE_AUTO_GUID,
    L"CLPMessageCode",
    L"Perform auto parameter checkes of CLPMessageCode",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCLPMessageCodeAutoTest
  },
  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestPlatformToDriverConfigurationProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Platform To Driver Configuration Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestPlatformToDriverConfiguration (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestPlatformToDriverConfigurationProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestPlatformToDriverConfigurationProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

