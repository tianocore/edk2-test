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
    DriverDignosticsBBTestMain.c

Abstract:
    for EFI Driver Diagnostics 2 Protocol Test

--*/
#include "SctLib.h"
#include "DriverDiagnostics2BBTest.h"

EFI_HANDLE      mImageHandle;


EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_DRIVER_DIAGNOSTICS2_TEST_REVISION,
  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_GUID,
  L"Testing For UEFI Driver Diagnostics2 Protocol",
  L"Total # test cases for the EFI Driver Diagnostics Protocol"
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {

//#ifdef EFI_TEST_EXHAUSTIVE
  {
    EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_TEST_ENTRY_GUID0101,
    L"RunDiagnostics_Conf",
    L"Conformance Test for RunDiagnostics",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestRunDiagnosticsConformanceTest
  },
  {
    EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_TEST_ENTRY_GUID0102,
    L"RunDiagnostics_Func",
    L"Function Test for RunDiagnostics",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestRunDiagnosticsFunctionTest
  },
	
//#endif

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
InitializeBBTestDriverDiagnostics2 (
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
           BBTestDriverDiagnostics2Unload,
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
BBTestDriverDiagnostics2Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

EFI_STATUS
LocateLoadedImageDevicePathFromDriverDiagnostisc2 (
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL         *DriverDiagnostisc2,
  IN EFI_DEVICE_PATH_PROTOCOL                 **DevicePath,      //reuse the structure of EFI_DEVICE_PATH_PROTOCOL as EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib
  )
{
  EFI_STATUS                          Status;

  UINTN                               NoHandles, Index;
  EFI_HANDLE                          *HandleBuffer;
  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL    *OtherDriverDiagnostisc2;

  //
  // Locate the Handle that the DriverDiagnostisc2 interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                        ByProtocol,
                        &gBlackBoxEfiDriverDiagnostics2ProtocolGuid,
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
  // Find the exact handle that DriverDiagnostisc2 bound to
  //
  for (Index=0;Index<NoHandles;Index++) {
    Status = gtBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gBlackBoxEfiDriverDiagnostics2ProtocolGuid,
                        (VOID **) &OtherDriverDiagnostisc2
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

    if (OtherDriverDiagnostisc2 == DriverDiagnostisc2) {
      break;
    }
  }

  //
  // Locate the Loaded Image DevicePath Protocol bound to DriverDiagnostisc2 Protocol
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
