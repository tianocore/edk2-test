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
    ComponentName2BBTestMain.c

Abstract:
    for EFI Component Name2 Protocol Test

--*/
#include "SctLib.h"
#include "ComponentName2BBTestMain.h"

EFI_HANDLE      mImageHandle;


EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_COMPONENT_NAME2_TEST_REVISION,
  EFI_COMPONENT_NAME2_PROTOCOL_GUID,
  L"Testing For EFI Component Name2 Protocol",
  L"Total # test cases for the EFI Component Name2 Protocol"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_COMPONENT_NAME2_PROTOCOL_TEST_ENTRY_GUID0101,
    L"GetDriverName_Func",
    L"Function Test for GetDriverName",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDriverNameFuncTest
  },
  {
    EFI_COMPONENT_NAME2_PROTOCOL_TEST_ENTRY_GUID0102,
    L"GetControllerName_Func",
    L"Function Test for GetControllerName",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetControllerNameFuncTest
  },
  {
    EFI_COMPONENT_NAME2_PROTOCOL_TEST_ENTRY_GUID0201,
    L"GetDriverName_Conf",
    L"Conformance Test for GetDriverName",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetDriverNameConformanceTest
  },
  {
    EFI_COMPONENT_NAME2_PROTOCOL_TEST_ENTRY_GUID0202,
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
EFIAPI
InitializeBBTestComponentName2 (
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
           BBTestComponentName2Unload,
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
BBTestComponentName2Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

EFI_STATUS
LocateLoadedImageDevicePathFromComponentName2 (
  IN EFI_COMPONENT_NAME2_PROTOCOL             *ComponentName2,
  IN EFI_DEVICE_PATH_PROTOCOL                 **DevicePath,      //reuse the EFI_DEVICE_PATH_PROTOCOL as EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib
  )
{
  EFI_STATUS                      Status;

  UINTN                           NoHandles, Index;
  EFI_HANDLE                      *HandleBuffer;
  EFI_COMPONENT_NAME2_PROTOCOL    *OtherComponentName2;

  //
  // Locate the Handle that the ComponentName2 interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                        ByProtocol,
                        &gBlackBoxEfiComponentName2ProtocolGuid,
                        NULL,
                        &NoHandles,
                        &HandleBuffer
                        );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"BS.LocateHandle - LocateHandle",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                );
    return Status;
  }

  if (NoHandles<=0) {
    StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"BS.LocateHandle - LocateHandle",
                  L"%a:%d:Device Error",
                  __FILE__,
                  (UINTN)__LINE__
                );
    return EFI_DEVICE_ERROR;
  }

  //
  // Find the exact handle that ComponentName2 bound to
  //
  for (Index=0;Index<NoHandles;Index++) {
    Status = gtBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gBlackBoxEfiComponentName2ProtocolGuid,
                        (VOID **) &OtherComponentName2
                        );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"BS.HandleProtocol - HandleProtocol",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                );

      gtBS->FreePool (HandleBuffer);
      return Status;
    }

    if (OtherComponentName2 == ComponentName2) {
      break;
    }
  }

  //
  // Locate the Loaded Image DevicePath Protocol bound to ComponentName2 Protocol
  //
  if (Index>=NoHandles) {
    //
    // No Handle Found!!
    //
    gtBS->FreePool (HandleBuffer);
    return EFI_DEVICE_ERROR;
  }

  Status = gtBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gBlackBoxEfiLoadedImageDevicePathProtocolGuid,
                      (VOID **) DevicePath
                      );

  gtBS->FreePool (HandleBuffer);
  return Status;
}


