/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AdapterInfoBBTestMain.c

Abstract:

  Test Driver of Adapter Information Protocol

--*/

#include "AdapterInfoBBTestMain.h"
#include "SctLib.h"

//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_REVISION,
  EFI_ADAPTER_INFORMATION_PROTOCOL_GUID,
  L"Adapter Information Protocol Test",
  L"UEFI Adapter Information Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {

  //Func Entry Fields
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetInformationFunction",
    L"Function auto test for Adapter Information Protocol GetInformation().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetInformationFunctionTest
  },
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0102,
    L"SetInformationFunction",
    L"Function auto test for Adapter Information Protocol SetInformation().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetInformationFunctionTest
  },
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0103,
    L"GetSupportedTypesFunction",
    L"Function auto test for Adapter Information Protocol GetSupportedTypes().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetSupportedTypesFunctionTest
  },
  

  // Conformance Entry Fields
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0201,
    L"GetInformationConformance",
    L"Conformance auto test for Adapter Information Protocol GetInformation().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetInformationConformanceTest
  },
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0202,
    L"SetInformationConformance",
    L"Conformance auto test for Adapter Information Protocol SetInformation().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetInformationConformanceTest
  },
  {
    EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0203,
    L"GetSupportedTypesConformance",
    L"Conformance auto test for Adapter Information Protocol GetSupportedTypes().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetSupportedTypesConformanceTest
  },
 
  0
  
};


INTN
MemCmp(
  UINT8    *s1,
  UINT8    *s2,
  UINTN     n
  )
{
  UINT8    *p1, *p2;

  p1 = s1;
  p2 = s2;
  if (n != 0) {
    do {
      if (*p1++ != *p2++)
        return (*--p1 - *--p2);
    } while (--n != 0);
  }
  return (0);
}



INTN 
GuidCmp(
  EFI_GUID    GuidGiven,
  EFI_GUID    GuidNeedToCmp
  )
{
  return MemCmp((UINT8 *)&GuidGiven,(UINT8 *)&GuidNeedToCmp,16);
}


//
//Validate the BlockSize returned from function GetInfomation with the Given value
//

BOOLEAN
InfoTypeAndBlockSizeCmp( 
  EFI_GUID    InformationType,
  UINTN       InformationBlockSize
  )
{
   
  if ((!GuidCmp (InformationType,gEfiAdapterInfoMediaStateGuid) && InformationBlockSize != sizeof(EFI_ADAPTER_INFO_MEDIA_STATE)) || 
      (!GuidCmp (InformationType,gEfiAdapterInfoNetworkBootGuid) && InformationBlockSize != sizeof(EFI_ADAPTER_INFO_NETWORK_BOOT)) || 
      (!GuidCmp (InformationType,gEfiAdapterInfoSanMacAddressGuid) && InformationBlockSize != sizeof(EFI_ADAPTER_INFO_SAN_MAC_ADDRESS)) ||
      (!GuidCmp (InformationType,gEfiAdapterInfoUndiIPv6SupportGuid) && InformationBlockSize != sizeof(EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT)) ||
      (!GuidCmp (InformationType,gEfiAdapterInfoMediaTypeGuid) && InformationBlockSize != sizeof(EFI_ADAPTER_INFO_MEDIA_TYPE))) 
    return FALSE;
  else
    return TRUE;  
}


//
//
//
EFI_STATUS
EFIAPI
InitializeAdapterInfoBBTest (
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE    *SystemTable
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
             UnloadAdapterInfoBBTest,
             &gBBTestProtocolInterface
             );
}


EFI_STATUS
EFIAPI
UnloadAdapterInfoBBTest (
  IN EFI_HANDLE    ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );
}
