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
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DevicePathUtilitiesBBTestMain.c

Abstract:

  Test Driver of Device Path Utilities Protocol

--*/

#include "SctLib.h"
#include "DevicePathUtilitiesBBTestMain.h"

//
// Build Data structure here
//
EFI_BB_TEST_PROTOCOL_FIELD  gBBTestProtocolField = {
  DEVICE_PATH_PROTOCOL_TEST_REVISION,
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID,
  L"Device Path Utilities Protocol Test",
  L"UEFI Device Path Utilities Protocol Test"
};

EFI_GUID                    gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD     gBBTestEntryField[] = {
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_CREATEDEVICENODE_FUNCTION_GUID,
    L"CreatDeviceNode_Functionality",
    L"Invoke the CreatDeviceNode and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesCreateDeviceNodeFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICENODE_FUNCTION_GUID,
    L"AppendDeviceNode_Functionality",
    L"Invoke the AppendDeviceNode and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDeviceNodeFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_GETDEVICEPATHSIZE_FUNCTION_GUID,
    L"GetDevicePathSize_Functionality",
    L"Invoke the GetDevicePathSize and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesGetDevicePathSizeFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_DUPLICATEDEVICEPATH_FUNCTION_GUID,
    L"DupilicateDevicePath_Functionality",
    L"Invoke the DupilicateDevicePath and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesDuplicateDevicePathFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATH_FUNCTION_GUID,
    L"AppendDevicePath_Functionality",
    L"Invoke the AppendDevicePath and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDevicePathFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATHINSTANCE_FUNCTION_GUID,
    L"AppendDevicePathInstance_Functionality",
    L"Invoke the AppendDevicePathInstance and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDevicePathInstanceFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_GETNEXTDEVICEPATHINSTANCE_FUNCTION_GUID,
    L"GetNextDevicePathInstance_Functionality",
    L"Invoke the GetNextDevicePathInstance and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesGetNextDevicePathInstanceFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_ISDEVICEPATHMULTIINSTANCE_FUNCTION_GUID,
    L"IsDevicePathMultiInstance_Functionality",
    L"Invoke the IsDevicePathMultiInstance and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesIsDevicePathMultiInstanceFunctionTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_CREATEDEVICENODE_CONFORMANCE_GUID,
    L"CreateDeviceNode_Conformance",
    L"Perform conformance test on the CreatDeviceNode service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesCreateDeviceNodeConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICENODE_CONFORMANCE_GUID,
    L"AppendDeviceNode_Conformance",
    L"Perform conformance test on the AppendDeviceNode service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDeviceNodeConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATH_CONFORMANCE_GUID,
    L"AppendDevicePath_Conformance",
    L"Perform conformance test on the AppendDevicePath service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDevicePathConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATHINSTANCE_CONFORMANCE_GUID,
    L"AppendDevicePathInstance_Conformance",
    L"Perform conformance test on the AppendDevicePathInstance service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesAppendDevicePathInstanceConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_GETNEXTDEVICEPATHINSTANCE_CONFORMANCE_GUID,
    L"GetNextDevicePathInstance_Conformance",
    L"Perform conformance test on the GetNextDevicePathInstance service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesGetNextDevicePathInstanceConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_GETDEVICEPATHSIZE_CONFORMANCE_GUID,
    L"GetDevicePathSize_Conformance",
    L"Perform conformance test on the GetDevicePathSize service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesGetDevicePathSizeConformanceTest
  },
  {
    DEVICE_PATH_UTILITIES_PROTOCOL_DUPLICATEDEVICEPATH_CONFORMANCE_GUID,
    L"DuplicateDevicePath_Conformance",
    L"Perform conformance test on the DuplicateDevicePath service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathUtilitiesDuplicateDevicePathConformanceTest
  },
  0
};

EFI_BB_TEST_PROTOCOL        *gBBTestProtocolInterface;

EFI_STATUS
BBTestDevicePathUtilitiesProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Device Path Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestDevicePathUtilitiesProtocol (
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
          BBTestDevicePathUtilitiesProtocolUnload,
          &gBBTestProtocolInterface
          );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestDevicePathUtilitiesProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS  Status;

  Status = EfiUninstallAndFreeBBTestInterface (
            ImageHandle,
            gBBTestProtocolInterface
            );

  return Status;
}
