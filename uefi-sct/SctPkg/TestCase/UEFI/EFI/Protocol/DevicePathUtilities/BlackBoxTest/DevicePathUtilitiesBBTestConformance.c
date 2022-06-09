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

  DevicePathUtilitiesBBTestConformance.c

Abstract:

  Interface Conformance Test Cases of Device Path Utilities Protocol

--*/

#include "SctLib.h"
#include "DevicePathUtilitiesBBTestMain.h"

#define PCINodeType         1
#define PCINodeSubType      1
#define PCINodeLength       6

#define PCIRootNodeType     2
#define PCIRootNodeSubType  1
#define PCIRootNodeLength   12

#define USBNodeType         3
#define USBNodeSubType      5
#define USBNodeLength       6

#define InvalidNodeLength   3

//
// TDS 3.4.1
//
EFI_STATUS
EFIAPI
DevicePathUtilitiesCreateDeviceNodeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
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

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.4.1.2.1
  //
  pDevicePath = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, InvalidNodeLength);
  if (pDevicePath == NULL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid052,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - CreatDeviceNode should not succeed with invalid NodeLength set",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  return EFI_SUCCESS;
}
//
// TDS 3.4.2
//
EFI_STATUS
EFIAPI
DevicePathUtilitiesAppendDeviceNodeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath4;

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

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.4.2.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);

  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath4  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);

  pDevicePath3  = DevicePathUtilities->AppendDeviceNode (NULL, pDevicePath2);
  if ((pDevicePath3 != NULL) && (SctCompareMem (pDevicePath3, pDevicePath4, DevicePathUtilities->GetDevicePathSize (pDevicePath3)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (pDevicePath3 != NULL) {
    SctFreePool (pDevicePath3);
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid054,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - AppendDeviceNode should return a copy of DeviceNode if DevicePath is NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.4.2.2.2
  //
  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (pDevicePath4, NULL);
  if ((pDevicePath3 != NULL) && (SctCompareMem (pDevicePath3, pDevicePath4, DevicePathUtilities->GetDevicePathSize (pDevicePath3)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (pDevicePath2 != NULL) {
    SctFreePool (pDevicePath2);
  }
  if (pDevicePath3 != NULL) {
    SctFreePool (pDevicePath3);
  }
  if (pDevicePath4 != NULL) {
    SctFreePool (pDevicePath4);
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid055,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - AppendDeviceNode should return a copy of DevicePath if DeviceNode is NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (NULL, NULL);
  if ((pDevicePath3 != NULL) && (SctCompareMem (pDevicePath3, pDevicePath1, DevicePathUtilities->GetDevicePathSize (pDevicePath3)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath1);
  if (pDevicePath3 != NULL) {
    SctFreePool (pDevicePath3);
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid069,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - AppendDeviceNode should return end-of-device-path device node if both DevicePath and DeviceNode are NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
//
// TDS 3.4.3
//
EFI_STATUS
EFIAPI
DevicePathUtilitiesAppendDevicePathConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath4;
  UINTN                               DevicePathLen1;
  UINTN                               DevicePathLen2;
  UINTN                               DevicePathLen3;
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

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.4.3.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  SctSetDevicePathEndNode (pDevicePath1);

  pDevicePath3  = DevicePathUtilities->CreateDeviceNode (USBNodeType, USBNodeSubType, USBNodeLength);
  pDevicePath4  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath3);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath3);
  DevicePathLen2  = DevicePathUtilities->GetDevicePathSize (pDevicePath4);

  pDevicePath1    = DevicePathUtilities->AppendDevicePath (NULL, pDevicePath4);
  SctFreePool (pDevicePath4);
  DevicePathLen3 = DevicePathUtilities->GetDevicePathSize (pDevicePath1);
  SctFreePool (pDevicePath1);

  if (DevicePathLen2 == DevicePathLen3) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid059,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - SctAppendDevicePath should ignore Src1 when it is set NULL",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  //
  // TDS 3.4.3.2.2
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  DevicePathLen1  = DevicePathUtilities->GetDevicePathSize (pDevicePath1);

  pDevicePath2    = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath3    = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath2  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);
  DevicePathLen1  = DevicePathUtilities->GetDevicePathSize (pDevicePath2);

  pDevicePath1    = DevicePathUtilities->AppendDevicePath (pDevicePath2, NULL);
  SctFreePool (pDevicePath2);
  DevicePathLen3 = DevicePathUtilities->GetDevicePathSize (pDevicePath1);
  SctFreePool (pDevicePath1);

  if (DevicePathLen1 == DevicePathLen3) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid060,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - SctAppendDevicePath should ignore Src2 when it is set NULL",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  pDevicePath1    = DevicePathUtilities->AppendDevicePath (NULL, NULL);
  if ((pDevicePath1 != NULL) && (SctIsDevicePathEnd(pDevicePath1))) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid068,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - SctAppendDevicePath should return end-of-device-path if both Src1 and Src2 are NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
//
// TDS 3.4.4
//
EFI_STATUS
EFIAPI
DevicePathUtilitiesAppendDevicePathInstanceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;

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

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.4.4.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);

  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath3  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath2  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);

  pDevicePath1 = DevicePathUtilities->AppendDevicePathInstance (pDevicePath2, NULL);
  SctFreePool (pDevicePath2);

  if (pDevicePath1 == NULL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid062,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - AppendDevicePathInstance should not succeed with DevicePathInstance set to be NULL",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  return EFI_SUCCESS;
}
//
// TDS 3.4.5
//
EFI_STATUS
EFIAPI
DevicePathUtilitiesGetNextDevicePathInstanceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  UINTN                               DevicePathInstanceSize;
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

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.4.5.2.1
  //
  pDevicePath1  = NULL;
  pDevicePath2  = DevicePathUtilities->GetNextDevicePathInstance (&pDevicePath1, &DevicePathInstanceSize);
  if (pDevicePath2 == NULL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid064,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - GetNextDevicePathInstance should not succeed with DevicePathInstance set to be NULL",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DevicePathUtilitiesGetDevicePathSizeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  UINTN                               DevicePathLen;

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

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  DevicePathLen   = DevicePathUtilities->GetDevicePathSize (NULL);
  if (DevicePathLen == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid056,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - GetDevicePathSize() should return 0 if DevicePath is NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DevicePathUtilitiesDuplicateDevicePathConformanceTest (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
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

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  pDevicePath         = DevicePathUtilities->DuplicateDevicePath(NULL);
  if (pDevicePath == NULL) {
    AssertionType     = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType     = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid071,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - SctDuplicateDevicePath() should return NULL if DevicePath is NULL",
                L"%a:%d",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
