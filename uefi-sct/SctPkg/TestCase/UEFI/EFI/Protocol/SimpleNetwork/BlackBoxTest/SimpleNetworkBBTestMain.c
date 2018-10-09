/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
EFIAPI
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
EFIAPI
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
EFIAPI
BBTestSimpleNetworkUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

