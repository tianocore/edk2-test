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

  MiscRuntimeServicesBBTestMain.c

Abstract:

  Test Driver of Miscellaneous Runtime Services

--*/

#include "SctLib.h"
#include "MiscRuntimeServicesBBTestMain.h"

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
EFI_GUID mEfiCapsuleHeaderGuid = EFI_CAPSULE_GUID;
#endif

EFI_TPL TplArray [TPL_ARRAY_SIZE] = {
  TPL_APPLICATION,
  TPL_CALLBACK,
  TPL_NOTIFY
};

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  MISC_RUNTIME_SERVICES_TEST_REVISION,
  MISC_RUNTIME_SERVICES_TEST_GUID,
  L"Misc Runtime Services Test",
  L"UEFI Misc Runtime Services Black-Box Test"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_GUID gSupportProtocolGuid2[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_RECOVERY_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    MISC_RUNTIME_SERVICES_RESETSYSTEM_INTERFACE_GUID,
    L"ResetSystem_Func",
    L"Interface Test for ResetSystem",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestResetSystemInterfaceTest
  },

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  {
    MISC_RUNTIME_SERVICES_QUERYCAPSULEBILITIES_INTERFACE_TEST_GUID,
    L"QueryCapsuleCapabilities_Func",
    L"Interface Test for QueryCapsuleCapabilities",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestQueryCapsuleCapabilitiesTest
  },

  {
    MISC_RUNTIME_SERVICES_UPDATECAPSULE_COFORMANCE_TEST_GUID,
    L"UpdateCapsule_Conf",
    L"Conformance Test for UpdateCapsule",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestUpdateCapsuleConformanceTest
  },

  {
    MISC_RUNTIME_SERVICES_QUERYCAPSULEBILITIES_CONFORMANCE_TEST_GUID,
    L"QueryCapsuleCapabilities_Conf",
    L"Conformance Test for QueryCapsuleCapabilities",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestQueryCapsuleCapabilitiesConformanceTest
  },
#endif

#ifdef EFI_TEST_EXHAUSTIVE
  {
    MISC_RUNTIME_SERVICES_RESETSYSTEM_MANUAL_GUID,
    L"ResetSystem_Func_Manual",
    L"Manual Test for ResetSystem",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_MANUAL,
    BBTestResetSystemManualTest
  },
  {
    MISC_RUNTIME_SERVICES_RESETSYSTEM_STRESS_TEST_GUID,
    L"ResetSystem_Stress",
    L"Stress Test for ResetSystem",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_AUTO,
    BBTestResetSystemStressTest
  },
  {
    MISC_RUNTIME_SERVICES_RESETSYSTEM_MANUAL_STRESS_TEST_GUID,
    L"ResetSystem_Stress_Manual",
    L"Manual Stress Test for ResetSystem",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid2,
    EFI_TEST_CASE_MANUAL,
    BBTestResetSystemManualStressTest
  },
#endif

  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestMiscRuntimeServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Miscellaneous Runtime Services Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestMiscRuntimeServices (
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
           BBTestMiscRuntimeServicesUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestMiscRuntimeServicesUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}