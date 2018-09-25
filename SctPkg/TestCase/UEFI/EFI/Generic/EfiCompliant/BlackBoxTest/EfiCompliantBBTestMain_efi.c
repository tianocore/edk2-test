/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EfiCompliantBbTestMain.c

Abstract:

  EFI Compliant Black-Box Test.

--*/

#include "SctLib.h"
#include "EfiCompliantBbTestMain_efi.h"

//
// Global variables
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_COMPLIANT_BB_TEST_REVISION,
  EFI_COMPLIANT_BB_TEST_GUID,
  L"EFI Compliant Test",
  L"UEFI 2.0 Compliant Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    REQUIRED_ELEMENTS_BB_TEST_GUID,
    L"Required Elements",
    L"Check the required elements defined in the EFI spec 2.6.1",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    RequiredElementsBbTest
  },
  {
    PLATFORM_SPECIFIC_ELEMENTS_BB_TEST_GUID,
    L"Platform Specific Elements",
    L"Check the platform specific elements defined in the EFI spec 2.6.2",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    PlatformSpecificElementsBbTest
  },
  //
  // NOTE: We didn't find a good way to check the driver specific elements
  // defined in the EFI spec 2.6.3.
  //
  /*
  {
    DRIVER_SPECIFIC_ELEMENTS_BB_TEST_GUID,
    L"Driver Specific Elements",
    L"Check the driver specific elements defined in the EFI spec 2.6.3",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    DriverSpecificElementsBbTest
  },
  */
  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

//
// Unload function declaration
//

EFI_STATUS
EfiCompliantBbTestUnload (
  IN EFI_HANDLE         ImageHandle
  );

//
// Entry point
//

EFI_STATUS
InitializeEfiCompliantBbTest (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           EfiCompliantBbTestUnload,
           &gBBTestProtocolInterface
           );
}

EFI_STATUS
EfiCompliantBbTestUnload (
  IN EFI_HANDLE         ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
