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

  DevicePathFromTextBBTestConformance.c

Abstract:

  Interface Function Test Cases of Device Path From Text Protocol

--*/

#include "DevicePathFromTextBBTestMain.h"

//
// TDS 3.9.1
//
EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDeviceNodeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL  *DevicePathFromText;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  (VOID **) &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathFromText = (EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.9.1.2.1
  //
  pDevicePath = DevicePathFromText->ConvertTextToDeviceNode (NULL);
  if (pDevicePath == NULL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid082,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertTextToDeviceNode should return NULL with TextDeviceNode set to be NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
//
// TDS 3.9.2
//
EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDevicePathConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL  *DevicePathFromText;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  (VOID **) &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathFromText = (EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.9.2.2.1
  //
  pDevicePath = DevicePathFromText->ConvertTextToDevicePath (NULL);
  if (pDevicePath == NULL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid084,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertTextToDevicePath should return NULL with TextDevicePath set to be NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
