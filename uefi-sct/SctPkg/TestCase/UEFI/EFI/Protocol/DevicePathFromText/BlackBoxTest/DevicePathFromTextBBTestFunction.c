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

  DevicePathFromTextBBTestFunction.c

Abstract:

  Interface Function Test Cases of Device Path From Text Protocol

--*/

#include "DevicePathFromTextBBTestMain.h"

#define MaxDevicePathStrLen 200

//
// TDS 3.8.1
//
EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDeviceNodeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL  *DevicePathFromText;
  EFI_TEST_ASSERTION                  AssertionType;
  CHAR16                              text1[MaxDevicePathStrLen];
  CHAR16                              text2[MaxDevicePathStrLen];
  CHAR16                              text3[MaxDevicePathStrLen];

  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath;
  ACPI_HID_DEVICE_PATH                *pDevicePath1;
  PCI_DEVICE_PATH                     *pDevicePath2;
  ATAPI_DEVICE_PATH                   *pDevicePath3;

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

  Status = gtBS->LocateProtocol (
                  &gBlackBoxEfiDevicePathUtilitiesProtocolGuid,
                  NULL,
                  (VOID **) &DevicePathUtilities
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathFromText = (EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.8.1.2.1
  //
  SctStrCpy (text1, L"PciRoot(0)");

  pDevicePath1 = (ACPI_HID_DEVICE_PATH *) DevicePathUtilities->CreateDeviceNode (
                                                                PCIRootNodeType,
                                                                PCIRootNodeSubType,
                                                                PCIRootNodeLength
                                                                );
  pDevicePath1->HID = EFI_PNP_ID (0x0A03);
  pDevicePath1->UID = 0;

  pDevicePath       = DevicePathFromText->ConvertTextToDeviceNode (text1);

  if (SctCompareMem (pDevicePath, pDevicePath1, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pDevicePath1)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath);
  SctFreePool (pDevicePath1);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid081,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertTextToDeviceNode must correctly set a device node structure",
                L"%a:%d: Convert PciRoot(0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.8.1.2.2
  //
  SctStrCpy (text2, L"Pci(0,0x10)");

  pDevicePath2            = (PCI_DEVICE_PATH *) DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath2->Device    = 0x00;
  pDevicePath2->Function  = 0x10;

  pDevicePath             = DevicePathFromText->ConvertTextToDeviceNode (text2);

  if (SctCompareMem (pDevicePath, pDevicePath2, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pDevicePath2)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath);
  SctFreePool (pDevicePath2);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid085,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertTextToDeviceNode must correctly set a device node structure",
                L"%a:%d: Convert Pci(0,0x10)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.8.1.2.3
  //
  SctStrCpy (text3, L"Ata(Primary,Master,0)");

  pDevicePath3 = (ATAPI_DEVICE_PATH *) DevicePathUtilities->CreateDeviceNode (
                                                              ATAPINodeType,
                                                              ATAPINodeSubType,
                                                              ATAPINodeLength
                                                              );
  pDevicePath3->PrimarySecondary  = 0x00;
  pDevicePath3->SlaveMaster       = 0x00;
  pDevicePath3->Lun               = 0x0000;

  pDevicePath                     = DevicePathFromText->ConvertTextToDeviceNode (text3);

  if (SctCompareMem (pDevicePath, pDevicePath3, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pDevicePath3)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath);
  SctFreePool (pDevicePath3);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid086,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertTextToDeviceNode must correctly set a device node structure",
                L"%a:%d: Convert Ata(Primary,Master,0)",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
//
// TDS 3.8.2
//
EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDevicePathFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL  *DevicePathFromText;
  EFI_TEST_ASSERTION                  AssertionType;
  CHAR16                              text1[MaxDevicePathStrLen];
  CHAR16                              text2[MaxDevicePathStrLen];
  CHAR16                              text3[MaxDevicePathStrLen];

  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath;
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

  Status = gtBS->LocateProtocol (
                  &gBlackBoxEfiDevicePathUtilitiesProtocolGuid,
                  NULL,
                  (VOID **) &DevicePathUtilities
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathFromText = (EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.8.2.2.1
  //
  SctStrCpy (text1, L"PciRoot(0)/Pci(0,0x10)/Floppy(0)");

  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);

  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath2)->HID  = EFI_PNP_ID (0x0A03);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath2)->UID  = 0;
  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  ((PCI_DEVICE_PATH *) pDevicePath1)->Device    = 0x00;
  ((PCI_DEVICE_PATH *) pDevicePath1)->Function  = 0x10;
  pDevicePath2 = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (ACPINodeType, ACPINodeSubType, ACPINodeLength);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath1)->HID  = EFI_PNP_ID (0x0604);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath1)->UID  = 0;
  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (pDevicePath2, pDevicePath1);
  SctFreePool (pDevicePath2);
  SctFreePool (pDevicePath1);

  pDevicePath = DevicePathFromText->ConvertTextToDevicePath (text1);

  if (SctCompareMem (pDevicePath, pDevicePath3, DevicePathUtilities->GetDevicePathSize (pDevicePath3)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath);
  SctFreePool (pDevicePath3);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid083,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertTextToDevicePath must correctly set a device path structure",
                L"%a:%d, Convert PciRoot(0)/Pci(0,0x10)/Floppy(0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.8.2.2.2
  //
  SctStrCpy (text2, L"PciRoot(0)/Pci(1,0x10)/Ata(Primary,Master,0)");

  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);

  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath2)->HID  = EFI_PNP_ID (0x0A03);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath2)->UID  = 0;
  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  ((PCI_DEVICE_PATH *) pDevicePath1)->Device    = 0x01;
  ((PCI_DEVICE_PATH *) pDevicePath1)->Function  = 0x10;
  pDevicePath2 = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (ATAPINodeType, ATAPINodeSubType, ATAPINodeLength);
  ((ATAPI_DEVICE_PATH *) pDevicePath1)->PrimarySecondary  = 0x00;
  ((ATAPI_DEVICE_PATH *) pDevicePath1)->SlaveMaster       = 0x00;
  ((ATAPI_DEVICE_PATH *) pDevicePath1)->Lun               = 0x0000;
  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (pDevicePath2, pDevicePath1);
  SctFreePool (pDevicePath2);
  SctFreePool (pDevicePath1);

  pDevicePath = DevicePathFromText->ConvertTextToDevicePath (text2);

  if (SctCompareMem (pDevicePath, pDevicePath3, DevicePathUtilities->GetDevicePathSize (pDevicePath3)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath);
  SctFreePool (pDevicePath3);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid087,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertTextToDevicePath must correctly set a device path structure",
                L"%a:%d, Convert PciRoot(0)/Pci(1,0x10)/Ata(Primary,Master,0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.8.2.2.3
  //
  SctStrCpy (text3, L"PciRoot(0)/Pci(0,0xC)/Pci(0,0)");

  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);

  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath2)->HID  = EFI_PNP_ID (0x0A03);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath2)->UID  = 0;
  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  ((PCI_DEVICE_PATH *) pDevicePath1)->Device    = 0x00;
  ((PCI_DEVICE_PATH *) pDevicePath1)->Function  = 0x0C;
  pDevicePath2 = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  ((PCI_DEVICE_PATH *) pDevicePath1)->Function  = 0x00;
  ((PCI_DEVICE_PATH *) pDevicePath1)->Device    = 0x00;
  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (pDevicePath2, pDevicePath1);
  SctFreePool (pDevicePath2);
  SctFreePool (pDevicePath1);

  pDevicePath = DevicePathFromText->ConvertTextToDevicePath (text3);

  if (SctCompareMem (pDevicePath, pDevicePath3, DevicePathUtilities->GetDevicePathSize (pDevicePath3)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath);
  SctFreePool (pDevicePath3);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid088,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertTextToDevicePath must correctly set a device path structure",
                L"%a:%d, Convert PciRoot(0)/Pci(0,0xC)/Pci(0,0)",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
