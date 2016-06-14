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
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  ProtocolHandlerBBTestMain.c

Abstract:

  for Protocol Handler Boot Services Black Box Test

--*/

#include "SctLib.h"
#include "ProtocolHandlerBBTest.h"


//
// global variable
//
EFI_HANDLE                  mImageHandle;

//
// Build Data structure here
//
EFI_TPL TplArray[TPL_ARRAY_SIZE] = {
  TPL_APPLICATION,
  TPL_CALLBACK,
  TPL_NOTIFY
};

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  PROTOCOL_HANDLER_BOOT_SERVICES_TEST_REVISION,
  PROTOCOL_HANDLER_BOOT_SERVICES_TEST_GUID,
  L"Protocol Handler Boot Services Test",
  L"UEFI Protocol Handler Boot Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0101,
    L"InstallProtocolInterface_Conf",
    L"Conformance Test for InstallProtocolInterface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInstallProtocolInterfaceConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0102,
    L"UninstallProtocolInterface_Conf",
    L"Conformance Test for UninstallProtocolInterface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestUninstallProtocolInterfaceConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0103,
    L"ReinstallProtocolInterface_Conf",
    L"Conformance Test for ReinstallProtocolInterface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReinstallProtocolInterfaceConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0104,
    L"RegisterProtocolNotify_Conf",
    L"Conformance Test for RegisterProtocolNotify",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterProtocolNotifyConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0105,
    L"InstallMultipleProtocolInterfaces_Conf",
    L"Conformance Test for InstallMultipleProtocolInterfaces",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInstallMultipleProtocolInterfacesConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0106,
    L"UninstallMultipleProtocolInterfaces_Conf",
    L"Conformance Test for UninstallMultipleProtocolInterfaces",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestUninstallMultipleProtocolInterfacesConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0107,
    L"LocateHandle_Conf",
    L"Conformance Test for LocateHandle",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLocateHandleConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0108,
    L"LocateHandleBuffer_Conf",
    L"Conformance Test for LocateHandleBuffer",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLocateHandleBufferConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0109,
    L"HandleProtocol_Conf",
    L"Conformance Test for HandleProtocol",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestHandleProtocolConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0110,
    L"LocateProtocol_Conf",
    L"Conformance Test for LocateProtocol",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLocateProtocolConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0111,
    L"LocateDevicePath_Conf",
    L"Conformance Test for LocateDevicePath",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLocateDevicePathConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0112,
    L"ProtocolsPerHandle_Conf",
    L"Conformance Test for ProtocolsPerHandle",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestProtocolsPerHandleConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0113,
    L"OpenProtocol_Conf",
    L"Conformance Test for OpenProtocol",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenProtocolConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0114,
    L"CloseProtocol_Conf",
    L"Conformance Test for CloseProtocol",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCloseProtocolConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0115,
    L"OpenProtocolInformation_Conf",
    L"Conformance Test for OpenProtocolInformation",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenProtocolInformationConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0116,
    L"ConnectController_Conf",
    L"Conformance Test for ConnectController",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestConnectControllerConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0117,
    L"DisconnectController_Conf",
    L"Conformance Test for DisconnectController",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestDisconnectControllerConsistencyTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0200,
    L"InstallProtocolInterface_Func",
    L"Interface Function Test for InstallProtocolInterface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInstallProtocolInterfaceInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0201,
    L"UninstallProtocolInterface_Func",
    L"Interface Function Test for UninstallProtocolInterface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestUninstallProtocolInterfaceInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0203,
    L"ReinstallProtocolInterface_Func",
    L"Interface Function Test for ReinstallProtocolInterface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestReinstallProtocolInterfaceInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0204,
    L"RegisterProtocolNotify_Func",
    L"Interface Function Test for RegisterProtocolNotify",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterProtocolNotifyInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0205,
    L"InstallMultipleProtocolInterfaces_Func",
    L"Interface Function Test for InstallMultipleProtocolInterfaces",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestInstallMultipleProtocolInterfacesInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0206,
    L"UninstallMultipleProtocolInterfaces_Func",
    L"Interface Function Test for UninstallMultipleProtocolInterfaces",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestUninstallMultipleProtocolInterfacesInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0207,
    L"LocateHandle_Func",
    L"Interface Function Test for LocateHandle",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLocateHandleInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0208,
    L"LocateHandleBuffer_Func",
    L"Interface Function Test for LocateHandleBuffer",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLocateHandleBufferInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0209,
    L"HandleProtocol_Func",
    L"Interface Function Test for HandleProtocol",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestHandleProtocolInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0210,
    L"LocateProtocol_Func",
    L"Interface Function Test for LocateProtocol",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLocateProtocolInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0211,
    L"LocateDevicePath_Func",
    L"Interface Function Test for LocateDevicePath",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLocateDevicePathInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0212,
    L"ProtocolsPerHandle_Func",
    L"Interface Function Test for ProtocolsPerHandle",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestProtocolsPerHandleInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0213,
    L"OpenProtocol_Func_1",
    L"Interface Function Test within test case only for OpenProtocol",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenProtocolInterfaceTest111
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0214,
    L"OpenProtocol_Func_2",
    L"Interface Function Test with non-EFI driver model driver for OpenProtocol",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenProtocolInterfaceTest222
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0215,
    L"OpenProtocol_Func_3",
    L"Interface Function Test with test drivers following EFI driver model for OpenProtocol",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenProtocolInterfaceTest333
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0216,
    L"CloseProtocol_Func",
    L"Interface Function Test for CloseProtocol",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCloseProtocolInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0217,
    L"OpenProtocolInformation_Func",
    L"Interface Function Test for OpenProtocolInformation",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestOpenProtocolInformationInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0218,
    L"ConnectController_Func",
    L"Interface Function Test for ConnectController",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestConnectControllerInterfaceTest
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0219,
    L"DisconnectController_Func",
    L"Interface Function Test for DisconnectController",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestDisconnectControllerInterfaceTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0301,
    L"Combination1_Stress",
    L"Combination Test 1 - Traverse the entire handle database",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCombinationTest1
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0302,
    L"Combination2_Stress",
    L"Combination Test 2 - Stress test",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCombinationTest2
  },
  {
    PROTOCOL_HANDLER_BOOT_SERVICES_TEST_ENTRY_GUID0303,
    L"Combination3_Stress",
    L"Combination Test 3 - Integrated test on driver model support",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestCombinationTest3
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
InitializeBBTestProtocolHandlerBootServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //
  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  Status = InitializeGlobalData ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestProtocolHandlerBootServicesUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
BBTestProtocolHandlerBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  ReleaseGlobalData ();

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

EFI_STATUS
InitializeGlobalData ()
{
  CHAR16                              *FilePath;
  EFI_STATUS                          Status;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib;

  //
  // init
  //
  mFilePath = NULL;
  mDevicePath = NULL;
  FilePath = NULL;

  //
  // Use profile lib at here just for less effect on the current system. It is
  // dependent on the implementation of test framework. So need to be updated
  // later.
  //
  Status = gtBS->LocateProtocol (
                   &gEfiTestProfileLibraryGuid,
                   NULL,
                   (VOID **) &ProfileLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &mDevicePath,
                         &FilePath
                         );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  mFilePath = SctPoolPrint (L"%s\\%s", FilePath, DEPENDENCY_DIR_NAME);

  SctFreePool (FilePath);

  return EFI_SUCCESS;
}

VOID
ReleaseGlobalData ()
{
  if (mFilePath != NULL) {
    SctFreePool (mFilePath);
  }

  if (mDevicePath != NULL) {
    SctFreePool (mDevicePath);
  }
}