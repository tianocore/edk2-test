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
    ComponentNameBBTestMain.c

Abstract:
    for EFI Component Name Protocol Test

--*/

#include "SctLib.h"
#include "ComponentNameBBTest.h"

EFI_HANDLE      mImageHandle;


EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_COMPONENT_NAME_TEST_REVISION,
  EFI_COMPONENT_NAME_PROTOCOL_GUID,
  L"Testing For EFI Component Name Protocol",
  L"Total # test cases for the EFI Component Name Protocol"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_COMPONENT_NAME_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetDriverName_Func",
    L"Function Test for GetDriverName",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDriverNameBasicTest
  },
  {
    EFI_COMPONENT_NAME_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetControllerName_Func",
    L"Function Test for GetControllerName",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetControllerNameBasicTest
  },
  {
    EFI_COMPONENT_NAME_PROTOCOL_TEST_ENTRY_GUID0201,
    L"GetDriverName_Conf",
    L"Conformance Test for GetDriverName",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDriverNameConformanceTest
  },
  {
    EFI_COMPONENT_NAME_PROTOCOL_TEST_ENTRY_GUID0202,
    L"GetControllerName_Conf",
    L"Conformance Test for GetControllerName",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetControllerNameConformanceTest
  },
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
InitializeBBTestComponentName (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
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
           BBTestComponentNameUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
EFIAPI
BBTestComponentNameUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
