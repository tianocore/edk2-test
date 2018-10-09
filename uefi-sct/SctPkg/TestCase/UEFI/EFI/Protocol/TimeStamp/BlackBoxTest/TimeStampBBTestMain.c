/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  TimeStampBBTestMain.c

Abstract:

  Test Driver of Time Stamp Protocol

--*/

#include "TimeStampBBTestMain.h"




EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_TIMESTAMP_PROTOCOL_TEST_REVISION,
  EFI_TIMESTAMP_PROTOCOL_GUID,
  L"Time Stamp Protocol Test",
  L"UEFI Time Stamp Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_TIME_STAMP_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetTimestampFunctionAuto",
    L"Function auto test for Time Stamp Protocol GetTimestamp().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetTimestampFunctionAutoTest
  },
  {
    EFI_TIME_STAMP_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetPropertiesFunctionAuto",
    L"Function auto test for Time Stamp Protocol GetProperties().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetPropertiesFunctionAutoTest
  },
  {
    EFI_TIME_STAMP_PROTOCOL_TEST_ENTRY_GUID0201,
    L"GetPropertiesConformanceAuto",
    L"Conformance auto test for Time Stamp Protocol GetProperties().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetPropertiesConformanceTest
  },
  0
};


//
//
//
EFI_STATUS
EFIAPI
InitializeTimeStampBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
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
           UnloadTimeStampBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadTimeStampBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}
