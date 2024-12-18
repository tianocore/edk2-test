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

  MiscRuntimeServicesBBTestMain.c

Abstract:

  Test Driver of Miscellaneous Runtime Services

--*/

#include "SctLib.h"
#include "MiscRuntimeServicesBBTestMain.h"

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
EFIAPI
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
EFIAPI
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
EFIAPI
BBTestMiscRuntimeServicesUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
