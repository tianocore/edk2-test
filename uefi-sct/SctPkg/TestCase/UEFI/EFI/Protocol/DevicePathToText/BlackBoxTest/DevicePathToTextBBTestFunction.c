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

  DevicePathToTextBBTestFunction.c

Abstract:

  Interface Function Test Cases of Device Path To Text Protocol

--*/

#include "DevicePathToTextBBTestMain.h"

STATIC
UINT32
HexStrToValue(
  IN CHAR16  *String,
  IN UINTN    *Value
  )
{
  UINT32 Index;

  *Value = 0;

  for (Index = 0; ; Index++) {
    if ((String[Index] >= L'0') && (String[Index] <= L'9')) {
      *Value = ((*Value) << 4) + (String[Index] - L'0');
    } else if ((String[Index] >= L'A') && (String[Index] <= L'F')) {
      *Value = ((*Value) << 4) + (String[Index] - L'A' + 10);
    } else if ((String[Index] >= L'a') && (String[Index] <= L'f')) {
      *Value = ((*Value) << 4) + (String[Index] - L'a' + 10);
    } else {
      break;
    }
  }

  return Index;
}

STATIC
UINT32
DecStrToValue(
  IN CHAR16  *String,
  IN UINTN    *Value
  )
{
  UINT32 Index;

  *Value = 0;

  for (Index = 0; ; Index++) {
    if ((String[Index] >= L'0') && (String[Index] <= L'9')) {
      *Value = ((*Value) * 10) + (String[Index] - L'0');
    } else {
      break;
    }
  }

  return Index;
}

STATIC
INTN
Is0XInValidPostion (
  IN CHAR16 *Str,
  IN INT32  Pos
  )
{
  if ((Pos <= 0) || ((Str[Pos - 1] != L',') && (Str[Pos - 1] != L'('))) {
    return 0;
  } else {
    return 1;
  }
}

STATIC
INTN
DevicePathCmp(
  IN CHAR16 *S1,
  IN CHAR16 *S2
  )
{
  UINT32   Idx1, Idx2;
  CHAR16  *Str1, *Str2;
  UINTN   Value1, Value2;
  INTN    RetCode;

  ASSERT(S1);
  ASSERT(S2);

  Str1 = (CHAR16 *)SctAllocatePool (2 * SctStrLen (S1) + 2);
  Str2 = (CHAR16 *)SctAllocatePool (2 * SctStrLen (S2) + 2);
  SctStrCpy (Str1, S1);
  SctStrCpy (Str2, S2);

  //
  // convert the characters in the two strings to upper case
  //
  SctStrUpr (Str1);
  SctStrUpr (Str2);

  RetCode = 0;
  Idx1 = Idx2 = 0; 
  while(Str1[Idx1] != 0 && Str2[Idx2] != 0) {
    if (Str1[Idx1] != Str2[Idx2]) {
      //
      // if not equal it must be comparing two numbers which one is HEX the other is DEC.
      //
      if ((Str1[Idx1] == L'0') && (Str1[Idx1 + 1] == L'X')) {
        if(Is0XInValidPostion(Str1, Idx1) == 0) {
          RetCode = 1;
		  break;
		}
        Idx1 += 2;
        Idx1 += HexStrToValue(Str1 + Idx1, &Value1);
		Idx2 += DecStrToValue(Str2 + Idx2, &Value2);
		if (Value1 != Value2) {
          break;
		}
        continue;
      } else if ((Str2[Idx2] == L'0') && (Str2[Idx2 + 1] == L'X')) {
        if(Is0XInValidPostion(Str2, Idx2) == 0) {
          RetCode = 1;
		  break;
		}
        Idx2 += 2;
        Idx1 += DecStrToValue(Str1 + Idx1, &Value1);
		Idx2 += HexStrToValue(Str2 + Idx2, &Value2);
		if (Value1 != Value2) {
          break;
		}
        continue;
	  } else if (Str1[Idx1] == L'X') {
        if(Is0XInValidPostion(Str1, Idx1 - 1) == 0 || (Idx2 - 1 <= 0)) {
          RetCode = 1;
		  break;
		}
        Idx1 += 1;
		Idx2--;
        Idx1 += HexStrToValue(Str1 + Idx1, &Value1);
		Idx2 += DecStrToValue(Str2 + Idx2, &Value2);
		if (Value1 != Value2) {
          break;
		}
        continue;
	  } else if (Str2[Idx2] == L'X') {
        if(Is0XInValidPostion(Str2, Idx2 - 1) == 0 || (Idx1 - 1 <= 0)) {
          RetCode = 1;
		  break;
		}
        Idx2 += 1;
		Idx1--;
        Idx1 += DecStrToValue(Str1 + Idx1, &Value1);
		Idx2 += HexStrToValue(Str2 + Idx2, &Value2);
		if (Value1 != Value2) {
          break;
		}
        continue;
      } else {
        RetCode = 1;
		break;
	  }
	}
    Idx1++;
    Idx2++;
  }

  if(Str1[Idx1] != 0 || Str2[Idx2] != 0) {
    RetCode = 1;
  }

  SctFreePool (Str1);
  SctFreePool (Str2);
  return RetCode;
}


//
// TDS 3.5.1
//
EFI_STATUS
EFIAPI
DevicePathToTextConvertDeviceNodeToTextFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL    *DevicePathToText;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevNode;
  ACPI_HID_DEVICE_PATH                *pAcpiDevNode;
  PCI_DEVICE_PATH                     *pPciDevNode;
  ATAPI_DEVICE_PATH                   *pAtapiDevNode;
  CHAR16                              *text;

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

  DevicePathToText = (EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.5.1.2.1
  //
  pAcpiDevNode = (ACPI_HID_DEVICE_PATH *) DevicePathUtilities->CreateDeviceNode (
                                                                PCIRootNodeType,
                                                                PCIRootNodeSubType,
                                                                PCIRootNodeLength
                                                                );
  pAcpiDevNode->HID = EFI_PNP_ID (0x0A03);
  pAcpiDevNode->UID = 0;

  text     = DevicePathToText->ConvertDeviceNodeToText ((EFI_DEVICE_PATH *) pAcpiDevNode, FALSE, FALSE);
  pDevNode = SctConvertTextToDeviceNode(text);

  if ((pDevNode != NULL) && (SctCompareMem (pDevNode, pAcpiDevNode, SctDevicePathNodeLength((EFI_DEVICE_PATH *) pAcpiDevNode)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid081,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly set a string to describe the device node structure",
                L"%a:%d: Convert result: %s - Expected: Acpi(PNP0A03,0)",
                __FILE__,
                (UINTN)__LINE__,
                text
                );
  SctFreePool (pAcpiDevNode);
  SctFreePool (pDevNode);
  SctFreePool (text);

  //
  // TDS 3.5.1.2.2
  //
  pPciDevNode = (PCI_DEVICE_PATH *) DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pPciDevNode->Device    = 0x00;
  pPciDevNode->Function  = 0x10;

  text     = DevicePathToText->ConvertDeviceNodeToText ((EFI_DEVICE_PATH *) pPciDevNode, FALSE, FALSE);
  pDevNode = SctConvertTextToDeviceNode(text);

  if ((pDevNode != NULL) && (SctCompareMem (pDevNode, pPciDevNode, SctDevicePathNodeLength((EFI_DEVICE_PATH *) pPciDevNode)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid085,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly set a string to describe the device node structure",
                L"%a:%d:Convert result: %s - Expected: Pci(0,0x10)",
                __FILE__,
                (UINTN)__LINE__,
                text
                );
  SctFreePool (pPciDevNode);
  SctFreePool (pDevNode);
  SctFreePool (text);

  //
  // TDS 3.5.1.2.3
  //
  pAtapiDevNode = (ATAPI_DEVICE_PATH *) DevicePathUtilities->CreateDeviceNode (
                                                              ATAPINodeType,
                                                              ATAPINodeSubType,
                                                              ATAPINodeLength
                                                              );
  pAtapiDevNode->PrimarySecondary  = 0x00;
  pAtapiDevNode->SlaveMaster       = 0x00;
  pAtapiDevNode->Lun               = 0x0000;

  text     = DevicePathToText->ConvertDeviceNodeToText ((EFI_DEVICE_PATH *) pAtapiDevNode, FALSE, FALSE);
  pDevNode = SctConvertTextToDeviceNode(text);

  if ((pDevNode != NULL) && (SctCompareMem (pDevNode, pAtapiDevNode, SctDevicePathNodeLength((EFI_DEVICE_PATH *) pAtapiDevNode)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid086,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly set a string to describe the device node structure",
                L"%a:%d:Convert result: %s - Expected: Ata(Primary,Master,0)",
                __FILE__,
                (UINTN)__LINE__,
                text
                );
  SctFreePool (pAtapiDevNode);
  SctFreePool (pDevNode);
  SctFreePool (text);

  return EFI_SUCCESS;
}

//
// TDS 3.5.2
//
EFI_STATUS
EFIAPI
DevicePathToTextConvertDevicePathToTextFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;

  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL    *DevicePathToText;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  CHAR16                              *text;

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

  DevicePathToText = (EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.5.2.2.1
  //
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
  ((PCI_DEVICE_PATH *) pDevicePath1)->Function  = 0x10;
  ((PCI_DEVICE_PATH *) pDevicePath1)->Device    = 0x00;
  pDevicePath2 = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (ACPINodeType, ACPINodeSubType, ACPINodeLength);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath1)->HID  = EFI_PNP_ID (0x0604);
  ((ACPI_HID_DEVICE_PATH *) pDevicePath1)->UID  = 0;
  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (pDevicePath2, pDevicePath1);
  SctFreePool (pDevicePath2);
  SctFreePool (pDevicePath1);

  text        = DevicePathToText->ConvertDevicePathToText (pDevicePath3, FALSE, FALSE);
  pDevicePath = SctConvertTextToDevicePath(text);

  if ((pDevicePath != NULL) && (SctCompareMem (pDevicePath, pDevicePath3, SctDevicePathNodeLength (pDevicePath3)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid083,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly set a string to describe the device path structure",
                L"%a:%d:Convert result: %s - Expected: Acpi(PNP0A03,0)/Pci(0,0x10)/Acpi(PNP0604,0)",
                __FILE__,
                (UINTN)__LINE__,
                text
                );
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath);
  SctFreePool (text);

  //
  // TDS 3.5.2.2.2
  //
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
  ((PCI_DEVICE_PATH *) pDevicePath1)->Function  = 0x10;
  ((PCI_DEVICE_PATH *) pDevicePath1)->Device    = 0x01;
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

  text        = DevicePathToText->ConvertDevicePathToText (pDevicePath3, FALSE, FALSE);
  pDevicePath = SctConvertTextToDevicePath(text);

  if ((pDevicePath != NULL) && (SctCompareMem (pDevicePath, pDevicePath3, SctDevicePathNodeLength(pDevicePath3)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid087,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly set a string to describe the device path structure",
                L"%a:%d:Convert result: %s - Expected: Acpi(PNP0A03,0)/Pci(1,0x10)/Ata(Primary,Master,0)",
                __FILE__,
                (UINTN)__LINE__,
                text
                );
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath);
  SctFreePool (text);

  //
  // TDS 3.5.2.2.3
  //
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
  ((PCI_DEVICE_PATH *) pDevicePath1)->Function  = 0x0C;
  ((PCI_DEVICE_PATH *) pDevicePath1)->Device    = 0x00;
  pDevicePath2 = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);

  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  ((PCI_DEVICE_PATH *) pDevicePath1)->Function  = 0x00;
  ((PCI_DEVICE_PATH *) pDevicePath1)->Device    = 0x00;
  pDevicePath3 = DevicePathUtilities->AppendDeviceNode (pDevicePath2, pDevicePath1);
  SctFreePool (pDevicePath2);
  SctFreePool (pDevicePath1);

  text        = DevicePathToText->ConvertDevicePathToText (pDevicePath3, FALSE, FALSE);
  pDevicePath = SctConvertTextToDevicePath(text);

  if ((pDevicePath != NULL) && (SctCompareMem (pDevicePath, pDevicePath3, SctDevicePathNodeLength (pDevicePath3)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid088,
                L"EFI_DEVICE_PATH_TO_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly set a string to describe the device path structure",
                L"%a:%d:Convert result: %s - Expected: Acpi(PNP0A03,0)/Pci(0,0xC)/Pci(0,0)",
                __FILE__,
                (UINTN)__LINE__,
                text
                );
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath);
  SctFreePool (text);

  return EFI_SUCCESS;
}
