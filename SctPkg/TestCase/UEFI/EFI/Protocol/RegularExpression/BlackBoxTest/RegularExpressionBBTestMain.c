/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  (C) Copyright 2016 - 2017 Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    RegularExpressionBBTestMain.c

Abstract:
    for EFI Regular Expression Protocol Test

--*/

#include "RegularExpressionBBTest.h"

EFI_HANDLE      mImageHandle;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_REGULAR_EXPRESSION_TEST_REVISION,
  EFI_REGULAR_EXPRESSION_PROTOCOL_GUID,
  L"Testing For EFI Regular Expression Protocol",
  L"Total # test cases for the EFI Regular Expression Protocol"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetInfo_Func",
    L"Function Test for GetInfo",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestRegExGetInfoFunctionTest
  },
  {
    EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0102,
    L"MatchString_Func",
    L"Function Test for MatchString",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestMatchStringFunctionTest
  },
  {
    EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0201,
    L"GetInfo_Conf",
    L"Conformance Test for GetInfo",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetInfoConformanceTest
  },
  {
    EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0202,
    L"MatchString_Conf",
    L"Conformance Test for MatchString",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestMatchStringConformanceTest
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
EFIAPI
InitializeBBTestRegularExpression (
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
           BBTestRegularExpressionUnload,
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
BBTestRegularExpressionUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

