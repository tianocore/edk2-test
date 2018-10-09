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

  IPsecConfigBBTestMain.c

Abstract:

  Test Driver of IPsec Config Protocol

--*/

#include "SctLib.h"
#include "IPsecConfigBBTestMain.h"


//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_IPSEC_CONFIG_PROTOCOL_TEST_REVISION,
  EFI_IPSEC_CONFIG_PROTOCOL_GUID,
  L"IPsec Config Protocol Test",
  L"UEFI IPsec Config Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0101,
    L"SetDataFunction",
    L"Function auto test for IPsec Config Protocol SetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetDataFunctionTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetDataFunction",
    L"Function auto test for IPsec Config Protocol GetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetDataFunctionTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0103,
    L"GetNextSelectorFunction",
    L"Function auto test for IPsec Config Protocol GetNextSelector().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextSelectorFunctionTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0104,
    L"RegisterDataNotifyFunction",
    L"Function auto test for IPsec Config Protocol RegisterDataNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterDataNotifyFunctionTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0105,
    L"UnregisterDataNotifyFunction",
    L"Function auto test for IPsec Config Protocol UnregisterDataNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterDataNotifyFunctionTest
  },  
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0201,
    L"SetDataConformance",
    L"Conformance auto test for IPsec Config Protocol SetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetDataConformanceTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0202,
    L"GetDataConformance",
    L"Conformance auto test for IPsec Config Protocol GetData().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetDataConformanceTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0203,
    L"GetNextSelectorConformance",
    L"Conformance auto test for IPsec Config Protocol GetNextSelector().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetNextSelectorConformanceTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0204,
    L"RegisterDataNotifyConformance",
    L"Conformance auto test for IPsec Config Protocol RegisterDataNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterDataNotifyConformanceTest
  },
  {
    EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0205,
    L"UnregisterDataNotifyConformance",
    L"Conformance auto test for IPsec Config Protocol UnregisterDataNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterDataNotifyConformanceTest
  },
  
  0
};


//
//
//

EFI_STATUS
EFIAPI
InitializeIPsecConfigBBTest (
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
           UnloadIPsecConfigBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadIPsecConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


VOID
EventNotifyFunc (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  //
  // do nothing
  //
  return;
}

