/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  HIIStringBBTestMain.c

Abstract:

  Test Driver of HII String Protocol

--*/

#include "HIIStringBBTestMain.h"


//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_HII_STRING_PROTOCOL_TEST_REVISION,
  EFI_HII_STRING_PROTOCOL_GUID,
  L"HII String Protocol Test",
  L"UEFI HII String Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0101,
    L"NewStringFunction",
    L"Function auto test for HII String Protocol NewString().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestNewStringFunctionTest
  },
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetStringFunction",
    L"Function auto test for HII String Protocol GetString().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetStringFunctionTest
  },
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0103,
    L"SetStringFunction",
    L"Function auto test for HII String Protocol SetString().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetStringFunctionTest
  },
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0104,
    L"GetLanguagesFunction",
    L"Function auto test for HII String Protocol GetLanguages().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetLanguagesFunctionTest
  },
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0105,
    L"GetSecondaryLanguagesFunction",
    L"Function auto test for HII String Protocol GetSecondaryLanguages().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetSecondaryLanguagesFunctionTest
  },
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0201,
    L"NewStringConformance",
    L"Conformance auto test for HII String Protocol NewString().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestNewStringConformanceTest
  },
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0202,
    L"GetStringConformance",
    L"Conformance auto test for HII String Protocol GetString().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetStringConformanceTest
  },
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0203,
    L"SetStringConformance",
    L"Conformance auto test for HII String Protocol SetString().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetStringConformanceTest
  },
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0204,
    L"GetLanguagesConformance",
    L"Conformance auto test for HII String Protocol GetLanguages().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetLanguagesConformanceTest
  },
  {
    EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0205,
    L"GetSecondaryLanguagesConformance",
    L"Conformance auto test for HII String Protocol GetSecondaryLanguages().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestGetSecondaryLanguagesConformanceTest
  },	
  0
};

//
//
//

EFI_STATUS
EFIAPI
InitializeHIIStringBBTest (
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
           UnloadHIIStringBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
EFIAPI
UnloadHIIStringBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

EFI_STATUS
GetHIIDatabaseInterface (
  OUT EFI_HII_DATABASE_PROTOCOL    **HIIDatabase
  )
{
  UINTN                                 NoHandles;
  EFI_HANDLE                            *HandleBuffer;
  EFI_STATUS                            Status;
  
  //
  // Get the HII Database Protocol interface
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiHIIDatabaseProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  if ( NoHandles <= 0 ) {
    return EFI_DEVICE_ERROR;
  }
  
  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gBlackBoxEfiHIIDatabaseProtocolGuid,
                   (VOID **) HIIDatabase
                   );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool ( HandleBuffer );
    return Status;
  }
  
  gtBS->FreePool ( HandleBuffer );
  
  return EFI_SUCCESS;
}
