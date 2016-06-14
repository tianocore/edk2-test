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

  SimpleNetworkBBTestMain.c

Abstract:

  Test Driver of SimpleNetwork Protocol

--*/

#include "SctLib.h"
#include "SimpleNetworkBBTestMain.h"

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SIMPLE_NETWORK_TEST_REVISION,
  EFI_SIMPLE_NETWORK_PROTOCOL_GUID,
  L"Simple Network Protocol Test",
  L"UEFI Simple Network Protocol Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    SNP_START_FUNCTION_TEST_GUID,
    L"Start_Func",
    L"Function Test for Start",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStartFunctionTest
  },
  {
    SNP_STOP_FUNCTION_TEST_GUID,
    L"Stop_Func",
    L"Function Test for Stop",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStopFunctionTest
  },
  {
    SNP_INITIALIZE_FUNCTION_TEST_GUID,
    L"Initialize_Func",
    L"Function Test for Initialize",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInitializeFunctionTest
  },
  {
    SNP_RESET_FUNCTION_TEST_GUID,
    L"Reset_Func",
    L"Function Test for Reset",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetFunctionTest
  },
  {
    SNP_SHUTDOWN_FUNCTION_TEST_GUID,
    L"Shutdown_Func",
    L"Function Test for Shutdown",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestShutdownFunctionTest
  },
  {
    SNP_RECEIVEFILTERS_FUNCTION_TEST_GUID,
    L"ReceiveFilter_Func",
    L"Function Test for ReceiveFilter",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReceiveFilterFunctionTest
  },
  {
    SNP_STATIONADDRESS_FUNCTION_TEST_GUID,
    L"StationAddress_Func",
    L"Function Test for StationAddress",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStationAddressFunctionTest
  },
  {
    SNP_STATISTICS_FUNCTION_TEST_GUID,
    L"Statistics_Func",
    L"Function Test for Statistics",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStatisticsFunctionTest
  },
  {
    SNP_MCASTIPTOMAC_FUNCTION_TEST_GUID,
    L"MCastIpToMac_Func",
    L"Function Test for MCastIpToMac",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestMCastIpToMacFunctionTest
  },
  {
    SNP_NVDATA_FUNCTION_TEST_GUID,
    L"NVData_Func",
    L"Function Test for NVData",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestNVDataFunctionTest
  },
  {
    SNP_GETSTATUS_FUNCTION_TEST_GUID,
    L"GetStatus_Func",
    L"Function Test for GetStatus",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestGetStatusFunctionTest
  },
  {
    SNP_START_CONFORMANCE_TEST_GUID,
    L"Start_Conf",
    L"Conformance Test for Start",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStartConformanceTest
  },
  {
    SNP_STOP_CONFORMANCE_TEST_GUID,
    L"Stop_Conf",
    L"Conformance Test for Stop",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStopConformanceTest
  },
  {
    SNP_INITIALIZE_CONFORMANCE_TEST_GUID,
    L"Initialize_Conf",
    L"Conformance Test for Initialize",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInitializeConformanceTest
  },
  {
    SNP_RESET_CONFORMANCE_TEST_GUID,
    L"Reset_Conf",
    L"Conformance Test for Reset",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetConformanceTest
  },
  {
    SNP_SHUTDOWN_CONFORMANCE_TEST_GUID,
    L"Shutdown_Conf",
    L"Conformance Test for Shutdown",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestShutdownConformanceTest
  },
  {
    SNP_RECEIVEFILTERS_CONFORMANCE_TEST_GUID,
    L"ReceiveFilter_Conf",
    L"Conformance Test for ReceiveFilter",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReceiveFilterConformanceTest
  },
  {
    SNP_STATIONADDRESS_CONFORMANCE_TEST_GUID,
    L"StationAddress_Conf",
    L"Conformance Test for StationAddress",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStationAddressConformanceTest
  },
  {
    SNP_STATISTICS_CONFORMANCE_TEST_GUID,
    L"Statistics_Conf",
    L"Conformance Test for Statistics",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStatisticsConformanceTest
  },
  {
    SNP_MCASTIPTOMAC_CONFORMANCE_TEST_GUID,
    L"MCastIpToMac_Conf",
    L"Conformance Test for MCastIpToMac",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestMCastIpToMacConformanceTest
  },
  {
    SNP_NVDATA_CONFORMANCE_TEST_GUID,
    L"NVData_Conf",
    L"Conformance Test for NVData",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestNVDataConformanceTest
  },
  {
    SNP_GETSTATUS_CONFORMANCE_TEST_GUID,
    L"GetStatus_Conf",
    L"Conformance Test for GetStatus",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetStatusConformanceTest
  },
  {
    SNP_TRANSMIT_CONFORMANCE_TEST_GUID,
    L"Transmit_Conf",
    L"Conformance Test for Transmit",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestTransmitConformanceTest
  },
  {
    SNP_RECEIVE_CONFORMANCE_TEST_GUID,
    L"Receive_Conf",
    L"Conformance Test for Receive",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReceiveConformanceTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    SNP_TRANSMIT_FUNCTION_TEST_GUID,
    L"Transmit_Func_Manual",
    L"Manual Function Test for Transmit",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestTransmitFunctionTest
  },
  {
    SNP_RECEIVE_FUNCTION_TEST_GUID,
    L"Receive_Func_Manual",
    L"Manual Function Test for Receive",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestReceiveFunctionTest
  },
#endif

  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestSimpleNetworkUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  SimpleNetwork Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestSimpleNetworkProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  //
  // Initialize library
  //
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);
  SctInitializeDriver (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestSimpleNetworkUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestSimpleNetworkUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

