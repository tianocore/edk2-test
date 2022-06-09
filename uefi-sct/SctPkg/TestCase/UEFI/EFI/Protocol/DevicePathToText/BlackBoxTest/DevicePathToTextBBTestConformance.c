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

  DevicePathToTextBBTestConformance.c

Abstract:

  Interface Function Test Cases of Device Path To Text Protocol

--*/

#include "DevicePathToTextBBTestMain.h"

//
// TDS 3.6.1
//
EFI_STATUS
EFIAPI
DevicePathToTextConvertDeviceNodeToTextConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL    *DevicePathToText;
  EFI_TEST_ASSERTION                  AssertionType;

  CHAR16                              *text1;
  CHAR16                              *text2;
  CHAR16                              *text3;
  CHAR16                              *text4;
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

  DevicePathToText = (EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.6.1.2.1
  //
  text1 = DevicePathToText->ConvertDeviceNodeToText (NULL, FALSE, FALSE);
  text2 = DevicePathToText->ConvertDeviceNodeToText (NULL, TRUE, FALSE);
  text3 = DevicePathToText->ConvertDeviceNodeToText (NULL, FALSE, TRUE);
  text4 = DevicePathToText->ConvertDeviceNodeToText (NULL, TRUE, TRUE);

  if ((text1 == NULL) && (text2 == NULL) && (text3 == NULL) && (text4 == NULL)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid082,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDeviceNodeToText should return NULL with DeviceNode set to be NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
//
// TDS 3.6.2
//
EFI_STATUS
EFIAPI
DevicePathToTextConvertDevicePathToTextConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL    *DevicePathToText;
  EFI_TEST_ASSERTION                  AssertionType;

  CHAR16                              *text1;
  CHAR16                              *text2;
  CHAR16                              *text3;
  CHAR16                              *text4;
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

  DevicePathToText = (EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.6.2.2.1
  //
  text1 = DevicePathToText->ConvertDevicePathToText (NULL, FALSE, TRUE);
  text2 = DevicePathToText->ConvertDevicePathToText (NULL, TRUE, FALSE);
  text3 = DevicePathToText->ConvertDevicePathToText (NULL, FALSE, TRUE);
  text4 = DevicePathToText->ConvertDevicePathToText (NULL, TRUE, TRUE);

  if ((text1 == NULL) && (text2 == NULL) && (text3 == NULL) && (text4 == NULL)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid084,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDevicePathToText should return NULL with DevicePath set to be NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
