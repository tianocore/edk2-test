/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2019, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DevicePathToTextBBTestCoverage.c

Abstract:

  Interface Function Test Cases of Device Path To Text Protocol

--*/

#include "DevicePathToTextBBTestMain.h"

#define MaxDevicePathStrLen 200

#define IS_HYPHEN(a)         ((a) == L'-')
#define IS_NULL(a)           ((a) == L'\0')

EFI_GUID mEfiDevicePathMessagingSASGuid             = DEVICE_PATH_MESSAGING_SAS;
EFI_GUID mEfiDevicePathMessagingUARTFLOWCONTROLGuid = DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL;

STATIC
EFI_STATUS 
StrToBuf (
  OUT UINT8    *Buf,
  IN  UINTN    BufferLength,
  IN  CHAR16   *Str
  )
{
  UINTN       Index;
  UINTN       StrLength;
  UINT8       Digit;
  UINT8       Byte;

  //
  // Two hex char make up one byte
  //
  StrLength = BufferLength * sizeof (CHAR16);

  for(Index = 0; Index < StrLength; Index++, Str++) {

    SctIsHexDigit (&Digit, *Str);

    //
    // For odd charaters, write the upper nibble for each buffer byte,
    // and for even characters, the lower nibble.
    //
    if ((Index & 1) == 0) {
      Byte = Digit << 4;
    } else {
      Byte = Buf[Index / 2];
      Byte &= 0xF0;
      Byte |= Digit;
    }

    Buf[Index / 2] = Byte;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
StrToGuid (
  IN  CHAR16   *Str,
  OUT EFI_GUID *Guid
  )
{
  UINTN       BufferLength;
  UINTN       ConvertedStrLen;
  EFI_STATUS  Status;

  BufferLength = sizeof (Guid->Data1);
  Status = SctHexStringToBuf ((UINT8 *) &Guid->Data1, &BufferLength, Str, &ConvertedStrLen);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Str += ConvertedStrLen;
  if (IS_HYPHEN (*Str)) {
    Str++;   
  } else {
    return EFI_UNSUPPORTED;
  }

  BufferLength = sizeof (Guid->Data2);
  Status = SctHexStringToBuf ((UINT8 *) &Guid->Data2, &BufferLength, Str, &ConvertedStrLen);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Str += ConvertedStrLen;
  if (IS_HYPHEN (*Str)) {
    Str++;
  } else {
    return EFI_UNSUPPORTED;
  }

  BufferLength = sizeof (Guid->Data3);
  Status = SctHexStringToBuf ((UINT8 *) &Guid->Data3, &BufferLength, Str, &ConvertedStrLen);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Str += ConvertedStrLen;
  if (IS_HYPHEN (*Str)) {
    Str++;
  } else {
    return EFI_UNSUPPORTED;
  }

  StrToBuf (&Guid->Data4[0], 2, Str);
  //
  // Skip 2 byte hex chars
  //
  Str += 2 * 2;

  if (IS_HYPHEN (*Str)) {
    Str++;
  } else {
    return EFI_UNSUPPORTED;
  }
  StrToBuf (&Guid->Data4[2], 6, Str);

  return EFI_SUCCESS;
}

STATIC
UINT32
ConvertEisaIDFromStr (
  IN CHAR16             *Str
  )
{
  if ((Str[0] == L'P') && (Str[1] == L'N') && (Str[2] == L'P')) {
    return EISA_PNP_ID(SctXtoi (Str + 3));
  }
  return (UINT32)SctXtoi (Str);
}

STATIC
VOID
ConvertStrToIPv4Addr (
  IN OUT CHAR16           *Str,
  OUT    EFI_IPv4_ADDRESS *IPv4Addr
  )
{
  UINTN   Index;
  CHAR16  *AddrStart;
  CHAR16  *AddrEnd;

  AddrStart = (CHAR16 *)SctAllocateCopyPool (SctStrLen (Str) * 2 + 2, Str);
  for (Index = 0; Index < 4; Index++) {
    AddrEnd   = SctStrChr (AddrStart, L'.');
    if (AddrEnd != NULL) {
      *AddrEnd  = L'\0';
    }
    IPv4Addr->Addr[Index] = (UINT8) SctAtoi (AddrStart);
    AddrStart = AddrEnd + 1;
  }
}

STATIC
VOID
ConvertStrToIPv6Addr (
  IN OUT CHAR16           *Str,
  OUT    EFI_IPv6_ADDRESS *IPv6Addr
  )
{
  UINTN   Index;
  CHAR16  *AddrStart;
  CHAR16  *AddrEnd;
  UINT16  Data;

  AddrStart = (CHAR16 *)SctAllocateCopyPool (SctStrLen (Str) * 2 + 2, Str);
  for (Index = 0; Index < 8; Index++) {
    AddrEnd   = SctStrChr (AddrStart, L':');
    if (AddrEnd != NULL) {
      *AddrEnd  = L'\0';
    }
    Data = (UINT16) SctXtoi (AddrStart);
    IPv6Addr->Addr[Index * 2]     = (UINT8) (Data >> 8);
    IPv6Addr->Addr[Index * 2 + 1] = (UINT8) (Data & 0xff);
    AddrStart = AddrEnd + 1;
  }
}

//
// TDS 3.7.1
//
EFI_STATUS
EFIAPI
DevicePathToTextConvertDeviceNodeToTextCoverageTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL    *DevicePathToText;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_DEVICE_PATH                     *pDeviceNode1;
  EFI_DEVICE_PATH                     *pDeviceNode2;
  CHAR16                              *Text;
  UINTN                               Length;
  EFI_GUID                            TmpGuid;

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
  // PcCard(0x2A)
  // 
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (1, 2, 5);
  ((PCCARD_DEVICE_PATH *)pDeviceNode1)->FunctionNumber = 0x2A;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid089,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: PcCard(0x2A)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // MemoryMapped(14,0x123456789ABCDEF,0xFEDCBA9876543210)
  // 
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x1, 0x3, 24);
  ((MEMMAP_DEVICE_PATH *)pDeviceNode1)->MemoryType      = 14;
  ((MEMMAP_DEVICE_PATH *)pDeviceNode1)->StartingAddress = 0x123456789ABCDEF;
  ((MEMMAP_DEVICE_PATH *)pDeviceNode1)->EndingAddress   = 0xFEDCBA9876543210;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid090,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: MemoryMapped(14,0x123456789ABCDEF,0xFEDCBA9876543210)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // VenHw(5AF6C71E-1261-4637-9838-C4E9913D1DBB,0123456789ABCDEF)
  //
  Length = (SctStrLen (L"0123456789ABCDEF") + 1) / 2;
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x1, 0x4, 20 + (UINT16)Length);
  StrToGuid (L"5AF6C71E-1261-4637-9838-C4E9913D1DBB", &((VENDOR_DEVICE_PATH *)pDeviceNode1)->Guid);
  StrToBuf (((UINT8 *) pDeviceNode1) + 20, Length, L"0123456789ABCDEF");

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid091,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: VenHw(5AF6C71E-1261-4637-9838-C4E9913D1DBB,0123456789ABCDEF)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Ctrl(0x1234ABCD)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x1, 0x5, 0x8);
  ((CONTROLLER_DEVICE_PATH *)pDeviceNode1)->ControllerNumber = 0x1234ABCD;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid092,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Ctrl(0x1234ABCD)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // BMC(11, 0xC0000000D0000000)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x1, 0x6, 13);
  ((BMC_DEVICE_PATH *)pDeviceNode1)->InterfaceType = 11;
  ((BMC_DEVICE_PATH *)pDeviceNode1)->BaseAddress[0] = 0x00;
  ((BMC_DEVICE_PATH *)pDeviceNode1)->BaseAddress[1] = 0x00;
  ((BMC_DEVICE_PATH *)pDeviceNode1)->BaseAddress[2] = 0x00;
  ((BMC_DEVICE_PATH *)pDeviceNode1)->BaseAddress[3] = 0xD0;
  ((BMC_DEVICE_PATH *)pDeviceNode1)->BaseAddress[4] = 0x00;
  ((BMC_DEVICE_PATH *)pDeviceNode1)->BaseAddress[5] = 0x00;
  ((BMC_DEVICE_PATH *)pDeviceNode1)->BaseAddress[6] = 0x00;
  ((BMC_DEVICE_PATH *)pDeviceNode1)->BaseAddress[7] = 0xC0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid125,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: BMC(11, 0xC0000000D0000000)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }


  //
  // AcpiEx(HID,CID,UID,HIDSTR,CIDSTR,UIDSTR)
  // AcpiEx(PNP0A03,PNP0A03,0x6789A,,,)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x2, 19);
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HID = ConvertEisaIDFromStr(L"PNP0A03");
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->CID = ConvertEisaIDFromStr(L"PNP0A03");
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->UID = 0x6789A;
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HidUidCidStr[0] = '\0';
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HidUidCidStr[1] = '\0';
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HidUidCidStr[2] = '\0';

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid093,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: AcpiEx(PNP0A03,PNP0A03,0x6789A,,,)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // AcpiEx(HID,CID,UID,HIDSTR,CIDSTR,UIDSTR)
  // AcpiEx(PNP0A03,PNP0A03,,,,)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x2, 19);
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HID = ConvertEisaIDFromStr(L"PNP0A03");
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->CID = ConvertEisaIDFromStr(L"PNP0A03");
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->UID = 0;
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HidUidCidStr[0] = '\0';
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HidUidCidStr[1] = '\0';
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HidUidCidStr[2] = '\0';

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid094,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: AcpiEx(PNP0A03,PNP0A03,,,,)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // AcpiExp(HID,CID,UIDSTR)
  // AcpiExp(PNP0A03,PNP0A03,2)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x2, 20);
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HID = ConvertEisaIDFromStr(L"PNP0A03");
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->CID = ConvertEisaIDFromStr(L"PNP0A03");
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->UID = 0;
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HidUidCidStr[0] = '\0';
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HidUidCidStr[1] = '2';
  ((ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *)pDeviceNode1)->HidUidCidStr[2] = '\0';

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid103,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: AcpiExp(PNP0A03,PNP0A03,2)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // AcpiAdr(0x80010100)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x3, 0x8);
  ((ACPI_ADR_DEVICE_PATH *)pDeviceNode1)->ADR = 0x80010100;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid097,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: AcpiAdr(0x80010100)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Scsi(1234,0xABCD)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x2, 0x8);
  ((SCSI_DEVICE_PATH *)pDeviceNode1)->Pun = 1234;
  ((SCSI_DEVICE_PATH *)pDeviceNode1)->Lun = 0xABCD;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid095,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Scsi(1234,0xABCD)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Fibre(0x123456789ABCDEF0,0xABCDEF1234567890)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x3, 24);
  ((FIBRECHANNEL_DEVICE_PATH *)pDeviceNode1)->WWN      = 0x123456789ABCDEF0;
  ((FIBRECHANNEL_DEVICE_PATH *)pDeviceNode1)->Lun      = 0xABCDEF1234567890;
  ((FIBRECHANNEL_DEVICE_PATH *)pDeviceNode1)->Reserved = 0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid096,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Fibre(0x123456789ABCDEF0,0xABCDEF1234567890)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // USB(12,0xAB)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x5, 6);
  ((USB_DEVICE_PATH *)pDeviceNode1)->ParentPortNumber = 12;
  ((USB_DEVICE_PATH *)pDeviceNode1)->InterfaceNumber  = 0xAB;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid098,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: USB(12,0xAB)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // I2O(0x1234ABCD)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x6, 8);
  ((I2O_DEVICE_PATH *)pDeviceNode1)->Tid = 0x1234ABCD;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid099,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: I2O(0x1234ABCD)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Infiniband(10,A1ED07B9-5BDC-4741-ADCF-CA1E8681DD1A,1234,5678,0xABCD)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x9, 48);
  ((INFINIBAND_DEVICE_PATH *)pDeviceNode1)->ResourceFlags = 10;
  StrToGuid (L"A1ED07B9-5BDC-4741-ADCF-CA1E8681DD1A", &TmpGuid);
  SctCopyMem (&((INFINIBAND_DEVICE_PATH *)pDeviceNode1)->PortGid, &TmpGuid, sizeof (EFI_GUID));
  ((INFINIBAND_DEVICE_PATH *)pDeviceNode1)->ServiceId     = 1234;
  ((INFINIBAND_DEVICE_PATH *)pDeviceNode1)->TargetPortId  = 5678;
  ((INFINIBAND_DEVICE_PATH *)pDeviceNode1)->DeviceId      = 0xABCD;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid100,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Infiniband(10,A1ED07B9-5BDC-4741-ADCF-CA1E8681DD1A,1234,5678,0xABCD)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // VenPcAnsi()
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0xa, 20);
  ((VENDOR_DEVICE_PATH *)pDeviceNode1)->Guid = gBlackBoxEfiPcAnsiGuid;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, TRUE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid101,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: VenPcAnsi()",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // UartFlowCtrl(Hardware)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0xa, 24);
  ((UART_FLOW_CONTROL_DEVICE_PATH *)pDeviceNode1)->Guid           = mEfiDevicePathMessagingUARTFLOWCONTROLGuid;
  ((UART_FLOW_CONTROL_DEVICE_PATH *)pDeviceNode1)->FlowControlMap = 1;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, TRUE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid102,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: UartFlowCtrl(Hardware)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // MAC(12345678ABCD12345678ABCD12345678ABCD12345678ABCD12345678ABCD1234,2)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0xb, 37);
  StrToBuf (&((MAC_ADDR_DEVICE_PATH *)pDeviceNode1)->MacAddress.Addr[0], sizeof (EFI_MAC_ADDRESS), L"12345678ABCD12345678ABCD12345678ABCD12345678ABCD12345678ABCD1234");
  ((MAC_ADDR_DEVICE_PATH *)pDeviceNode1)->IfType = 2;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid105,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: MAC(12345678ABCD12345678ABCD12345678ABCD12345678ABCD12345678ABCD1234,2)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // IPv4(12.34.56.78,TCP,Static,192.168.67.89,192.168.67.1,255.255.255.0)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0xc, 27);
  ConvertStrToIPv4Addr (L"12.34.56.78", &((IPV4_DEVICE_PATH *)pDeviceNode1)->RemoteIpAddress);
  ((IPV4_DEVICE_PATH *)pDeviceNode1)->Protocol        = 6;
  ((IPV4_DEVICE_PATH *)pDeviceNode1)->StaticIpAddress = TRUE;
  ((IPV4_DEVICE_PATH *)pDeviceNode1)->LocalPort       = 0;
  ((IPV4_DEVICE_PATH *)pDeviceNode1)->RemotePort      = 0;
  ConvertStrToIPv4Addr (L"192.168.67.89", &((IPV4_DEVICE_PATH *)pDeviceNode1)->LocalIpAddress);
  ConvertStrToIPv4Addr (L"192.168.67.1", &((IPV4_DEVICE_PATH *)pDeviceNode1)->GatewayIPAddress);
  ConvertStrToIPv4Addr (L"255.255.255.0", &((IPV4_DEVICE_PATH *)pDeviceNode1)->SubnetMask);

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid106,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: IPv4(12.34.56.78,TCP,Static,192.168.67.89,192.168.67.1,255.255.255.0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // IPv6(1234:5678:ABCD:1234:5678:ABCD:1234:5678,UDP,Static,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD,8,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0xd, 60);
  ConvertStrToIPv6Addr (L"1234:5678:ABCD:1234:5678:ABCD:1234:5678", &((IPV6_DEVICE_PATH *)pDeviceNode1)->RemoteIpAddress);
  ((IPV6_DEVICE_PATH *)pDeviceNode1)->Protocol        = 17;
  ((IPV6_DEVICE_PATH *)pDeviceNode1)->IPAddressOrigin = 0;
  ((IPV6_DEVICE_PATH *)pDeviceNode1)->LocalPort       = 0;
  ((IPV6_DEVICE_PATH *)pDeviceNode1)->RemotePort      = 0;
  ConvertStrToIPv6Addr (L"5678:ABCD:1234:5678:ABCD:1234:5678:ABCD", &((IPV6_DEVICE_PATH *)pDeviceNode1)->LocalIpAddress);
  ((IPV6_DEVICE_PATH *)pDeviceNode1)->PrefixLength    = 8;
  ConvertStrToIPv6Addr (L"5678:ABCD:1234:5678:ABCD:1234:5678:ABCD", &((IPV6_DEVICE_PATH *)pDeviceNode1)->GatewayIPAddress);

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid107,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: IPv6(1234:5678:ABCD:1234:5678:ABCD:1234:5678,UDP,Static,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD,8,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Uart(115200,8,O,1.5)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0xe, 19);
  ((UART_DEVICE_PATH *)pDeviceNode1)->Reserved = 0;
  ((UART_DEVICE_PATH *)pDeviceNode1)->BaudRate = 115200;
  ((UART_DEVICE_PATH *)pDeviceNode1)->DataBits = 8;
  ((UART_DEVICE_PATH *)pDeviceNode1)->Parity   = 3;
  ((UART_DEVICE_PATH *)pDeviceNode1)->StopBits = 2;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid108,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Uart(115200,8,O,1.5)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // UsbVideo(0x4D2,0x162E,0x1,0x0)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0xf, 11);
  ((USB_CLASS_DEVICE_PATH *)pDeviceNode1)->VendorId       = 1234;
  ((USB_CLASS_DEVICE_PATH *)pDeviceNode1)->ProductId      = 5678;
  ((USB_CLASS_DEVICE_PATH *)pDeviceNode1)->DeviceClass    = 14;
  ((USB_CLASS_DEVICE_PATH *)pDeviceNode1)->DeviceSubClass = 1;
  ((USB_CLASS_DEVICE_PATH *)pDeviceNode1)->DeviceProtocol = 0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid109,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: UsbVideo(0x4D2,0x162E,0x1,0x0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Unit(0xAB)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x11, 5);
  ((DEVICE_LOGICAL_UNIT_DEVICE_PATH *)pDeviceNode1)->Lun  = 0xAB;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid113,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Unit(0xAB)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // HD(6,GPT,E8AAED38-1815-4E4F-BCB5-2E3DBD160C9C,12345678,0xABCD1234)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x4, 0x1, 42);
  ((HARDDRIVE_DEVICE_PATH *)pDeviceNode1)->PartitionNumber = 6;
  ((HARDDRIVE_DEVICE_PATH *)pDeviceNode1)->MBRType         = 2;
  ((HARDDRIVE_DEVICE_PATH *)pDeviceNode1)->PartitionStart  = 12345678;
  ((HARDDRIVE_DEVICE_PATH *)pDeviceNode1)->PartitionSize   = 0xABCD1234;
  ((HARDDRIVE_DEVICE_PATH *)pDeviceNode1)->SignatureType   = 2;
  StrToGuid (L"E8AAED38-1815-4E4F-BCB5-2E3DBD160C9C", &TmpGuid);
  SctCopyMem (&((HARDDRIVE_DEVICE_PATH *)pDeviceNode1)->Signature, &TmpGuid, sizeof (EFI_GUID));

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid115,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: HD(6,GPT,E8AAED38-1815-4E4F-BCB5-2E3DBD160C9C,12345678,0xABCD1234)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // CDROM(12340000,12345678,0xABCD1234)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x4, 0x2, 24);
  ((CDROM_DEVICE_PATH *)pDeviceNode1)->BootEntry      = 12340000;
  ((CDROM_DEVICE_PATH *)pDeviceNode1)->PartitionStart = 12345678;
  ((CDROM_DEVICE_PATH *)pDeviceNode1)->PartitionSize  = 0xABCD1234;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid117,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: CDROM(12340000,12345678,0xABCD1234)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Media(BA3A77E6-39A2-4375-A39A-108BFFCCE1AA)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x4, 0x5, 20);
  StrToGuid (L"BA3A77E6-39A2-4375-A39A-108BFFCCE1AA", &((MEDIA_PROTOCOL_DEVICE_PATH *)pDeviceNode1)->Protocol);

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid119,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Media(BA3A77E6-39A2-4375-A39A-108BFFCCE1AA)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Offset(0xFF, 0xFFFF)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x4, 0x8, sizeof(MEDIA_OFFSET_DEVICE_PATH));
  ((MEDIA_OFFSET_DEVICE_PATH *)pDeviceNode1)->Reserved = 0;
  ((MEDIA_OFFSET_DEVICE_PATH *)pDeviceNode1)->StartingOffset = 0x12;
  ((MEDIA_OFFSET_DEVICE_PATH *)pDeviceNode1)->EndingOffset = 0x1234;
  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);
  if (pDeviceNode2 &&
      *((UINT16*)((MEDIA_OFFSET_DEVICE_PATH *)pDeviceNode2)->Header.Length) ==
      sizeof(MEDIA_OFFSET_DEVICE_PATH)) {
    ((MEDIA_OFFSET_DEVICE_PATH *)pDeviceNode2)->Reserved = 0;
  }
  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid121,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Offset(0x12, 0x1234)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // RamDisk(0xA0000000B0000000,0xA0000000BFFFFFFF,3,BA3A77E6-39A2-4375-A39A-108BFFCCE1AA)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x4, 0x9, sizeof(RAM_DISK_DEVICE_PATH));
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[0] = 0xB0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[1] = 0xA0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[0] = 0xBFFFFFFF;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[1] = 0xA0000000;
  StrToGuid (L"BA3A77E6-39A2-4375-A39A-108BFFCCE1AA", &((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->RamDiskType);
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->DiskInstance = 3;
  
  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid126,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: RamDisk(0xA0000000B0000000,0xA0000000BFFFFFFF,3,BA3A77E6-39A2-4375-A39A-108BFFCCE1AA)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // VirtualDisk(0xA0000000B0000000,0xA0000000BFFFFFFF,3)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x4, 0x9, sizeof(RAM_DISK_DEVICE_PATH));
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[0] = 0xB0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[1] = 0xA0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[0] = 0xBFFFFFFF;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[1] = 0xA0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->RamDiskType = gDevicePathToTextBBTestVirtualDiskGuid;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->DiskInstance = 3;
  
  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid126,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: VirtualDisk(0xA0000000B0000000,0xA0000000BFFFFFFF,3)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // VirtualCD(0xA0000000B0000000,0xA0000000BFFFFFFF,3)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x4, 0x9, sizeof(RAM_DISK_DEVICE_PATH));
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[0] = 0xB0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[1] = 0xA0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[0] = 0xBFFFFFFF;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[1] = 0xA0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->RamDiskType = gDevicePathToTextBBTestVirtualCDGuid;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->DiskInstance = 3;
  
  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid126,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: VirtualCD(0xA0000000B0000000,0xA0000000BFFFFFFF,3)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // PersistentVirtualDisk(0xA0000000B0000000,0xA0000000BFFFFFFF,3)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x4, 0x9, sizeof(RAM_DISK_DEVICE_PATH));
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[0] = 0xB0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[1] = 0xA0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[0] = 0xBFFFFFFF;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[1] = 0xA0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->RamDiskType = gDevicePathToTextBBTestPresistentVirtualDiskGuid;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->DiskInstance = 3;
  
  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid126,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: PersistentVirtualDisk(0xA0000000B0000000,0xA0000000BFFFFFFF,3)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // PersistentVirtualCD(0xA0000000B0000000,0xA0000000BFFFFFFF,3)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x4, 0x9, sizeof(RAM_DISK_DEVICE_PATH));
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[0] = 0xB0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->StartingAddr[1] = 0xA0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[0] = 0xBFFFFFFF;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->EndingAddr[1] = 0xA0000000;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->RamDiskType = gDevicePathToTextBBTestPresistentVirtualCDGuid;
  ((RAM_DISK_DEVICE_PATH *)pDeviceNode1)->DiskInstance = 3;
  
  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid126,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: PersistentVirtualCD(0xA0000000B0000000,0xA0000000BFFFFFFF,3)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Vlan(18)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x14, 6);
  ((VLAN_DEVICE_PATH *)pDeviceNode1)->VlanId = 0x12;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid122,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Vlan(18)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // PciRoot(0x0)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x1, 12);
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->HID = 0x0A0341D0;
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->UID = 0x0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);
  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid104,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: PciRoot(0x0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }


  //
  // PcieRoot(0x0)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x1, 12);
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->HID = 0x0A0841D0;
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->UID = 0x0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);
  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid110,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: PcieRoot(0x0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Floppy(0x0)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x1, 12);
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->HID = 0x060441D0;
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->UID = 0x0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);
  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid111,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Floppy(0x0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Keyboard(0x0)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x1, 12);
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->HID = 0x030141D0;
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->UID = 0x0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);
  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid112,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Keyboard(0x0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Serial(0x0)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x1, 12);
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->HID = 0x050141D0;
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->UID = 0x0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);
  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid114,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Serial(0x0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // ParallelPort(0x0)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x2, 0x1, 12);
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->HID = 0x040141D0;
  ((ACPI_HID_DEVICE_PATH *)pDeviceNode1)->UID = 0x0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);
  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid116,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: ParallelPort(0x0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // FibreEx(0x123456789ABCDEF0,0xABCDEF1234567890)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x15, 24);
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->WWN[0] = 0x12;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->WWN[1] = 0x34;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->WWN[2] = 0x56;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->WWN[3] = 0x78;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->WWN[4] = 0x9A;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->WWN[5] = 0xBC;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->WWN[6] = 0xDE;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->WWN[7] = 0xF0;
    
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->Lun[0] = 0xAB;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->Lun[1] = 0xCD;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->Lun[2] = 0xEF;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->Lun[3] = 0x12;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->Lun[4] = 0x34;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->Lun[5] = 0x56;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->Lun[6] = 0x78;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->Lun[7] = 0x90;
  ((FIBRECHANNELEX_DEVICE_PATH *)pDeviceNode1)->Reserved = 0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid118,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: FibreEx(0x123456789ABCDEF0,0xABCDEF1234567890)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // SAS(0x31000004CF13F6BD,0xABCDEF,0x0,SAS,External,Direct,0x6A,0x0)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0xa, 44);
  StrToGuid (L"D487DDB4-008B-11D9-AFDC-001083FFCA4D", &((SAS_DEVICE_PATH *)pDeviceNode1)->Guid);
  ((SAS_DEVICE_PATH *)pDeviceNode1)->Reserved           = 0x0;
  ((SAS_DEVICE_PATH *)pDeviceNode1)->SasAddress         = 0x31000004CF13F6BD;
  ((SAS_DEVICE_PATH *)pDeviceNode1)->Lun                = 0xABCDEF;
  ((SAS_DEVICE_PATH *)pDeviceNode1)->DeviceTopology     = 0x6922;
  ((SAS_DEVICE_PATH *)pDeviceNode1)->RelativeTargetPort = 0x0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, TRUE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid120,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: SAS(0x31000004CF13F6BD,0xABCDEF,0x0,SAS,External,Direct,0x6A,0x0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // SasEx(0x0123456789ABCDEF,0xABCDEF0123456789,0x0,SAS,External,Direct,0x6A)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x16, 24);
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->SasAddress[0]      = 0x01;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->SasAddress[1]      = 0x23;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->SasAddress[2]      = 0x45;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->SasAddress[3]      = 0x67;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->SasAddress[4]      = 0x89;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->SasAddress[5]      = 0xAB;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->SasAddress[6]      = 0xCD;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->SasAddress[7]      = 0xEF;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->Lun[0]             = 0xAB;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->Lun[1]             = 0xCD;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->Lun[2]             = 0xEF;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->Lun[3]             = 0x01;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->Lun[4]             = 0x23;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->Lun[5]             = 0x45;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->Lun[6]             = 0x67;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->Lun[7]             = 0x89;
  
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->DeviceTopology     = 0x6922;
  ((SASEX_DEVICE_PATH *)pDeviceNode1)->RelativeTargetPort = 0x0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid123,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: SasEx(0x0123456789ABCDEF,0xABCDEF0123456789,0x0,SAS,External,Direct,0x6A)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // NVMe(0xAB124BEF,AB-CD-EF-01-23-45-67-89)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x17, 16);  
  ((NVME_DEVICE_PATH *)pDeviceNode1)->NamespaceId = 0xAB124BEF;
  ((NVME_DEVICE_PATH *)pDeviceNode1)->EUId        = 0xABCDEF0123456789;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid124,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: NVMe(0xAB124BEF,AB-CD-EF-01-23-45-67-89)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Uri(Uri)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x18, 7); 
  ((URI_DEVICE_PATH *)pDeviceNode1)->Uri[0] = 'U';
  ((URI_DEVICE_PATH *)pDeviceNode1)->Uri[1] = 'r';
  ((URI_DEVICE_PATH *)pDeviceNode1)->Uri[2] = 'i';

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid127,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Uri(Uri)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // UFS(0,3) UFS 2.0 spec
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x19, 6);  
  ((UFS_DEVICE_PATH *)pDeviceNode1)->TargetID = 0;
  ((UFS_DEVICE_PATH *)pDeviceNode1)->LUN      = 3;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid133,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: UFS(0,3)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // SD(3) 
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x1A, 5);  
  ((SD_DEVICE_PATH *)pDeviceNode1)->SlotNumber = 3;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid128,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: SD(3)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Bluetooth(77FAF5201300) 
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x1B, 10);  
  ((BLUETOOTH_DEVICE_PATH *)pDeviceNode1)->BD_ADDR.Address[0] = 0x77;
  ((BLUETOOTH_DEVICE_PATH *)pDeviceNode1)->BD_ADDR.Address[1] = 0xFA;
  ((BLUETOOTH_DEVICE_PATH *)pDeviceNode1)->BD_ADDR.Address[2] = 0xF5;
  ((BLUETOOTH_DEVICE_PATH *)pDeviceNode1)->BD_ADDR.Address[3] = 0x20;
  ((BLUETOOTH_DEVICE_PATH *)pDeviceNode1)->BD_ADDR.Address[4] = 0x13;
  ((BLUETOOTH_DEVICE_PATH *)pDeviceNode1)->BD_ADDR.Address[5] = 0x00;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid129,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Bluetooth(77FAF5201300)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Wi-Fi(It's a SSID)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x1C, 36);
  SctZeroMem(&((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[0], sizeof(SSID));
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[0] = 'I';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[1] = 't';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[2] = '\'';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[3] = 's';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[4] = ' ';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[5] = 'a';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[6] = ' ';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[7] = 'S';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[8] = 'S';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[9] = 'I';
  ((WIFI_DEVICE_PATH *)pDeviceNode1)->SSId.Id[10] = 'D';

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid130,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Wi-Fi(It's a SSID)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // eMMC(3) 
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x1D, 5);  
  ((EMMC_DEVICE_PATH *)pDeviceNode1)->SlotNumber = 3;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid131,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: eMMC(3)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }


  //
  // BluetoothLE(77FAF5201300,0) 
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x1E, 11);  
  ((BLUETOOTH_LE_DEVICE_PATH *)pDeviceNode1)->LEAddress.Address[0] = 0x77;
  ((BLUETOOTH_LE_DEVICE_PATH *)pDeviceNode1)->LEAddress.Address[1] = 0xFA;
  ((BLUETOOTH_LE_DEVICE_PATH *)pDeviceNode1)->LEAddress.Address[2] = 0xF5;
  ((BLUETOOTH_LE_DEVICE_PATH *)pDeviceNode1)->LEAddress.Address[3] = 0x20;
  ((BLUETOOTH_LE_DEVICE_PATH *)pDeviceNode1)->LEAddress.Address[4] = 0x13;
  ((BLUETOOTH_LE_DEVICE_PATH *)pDeviceNode1)->LEAddress.Address[5] = 0x00;
  ((BLUETOOTH_LE_DEVICE_PATH *)pDeviceNode1)->LEAddress.Type = 0;

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid134,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: BluetoothLE(77FAF5201300,0)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Dns(192.168.22.100,192.168.22.101)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x1F, sizeof(DNS_DEVICE_PATH) + 2 * sizeof(EFI_IP_ADDRESS));
  ((DNS_DEVICE_PATH *)pDeviceNode1)->IsIPv6 = 0;

  ConvertStrToIPv4Addr (L"192.168.22.100", ((EFI_IPv4_ADDRESS *)((UINT8 *)pDeviceNode1 + sizeof(DNS_DEVICE_PATH))));
  ConvertStrToIPv4Addr (L"192.168.22.101", ((EFI_IPv4_ADDRESS *)((UINT8 *)pDeviceNode1 + sizeof(DNS_DEVICE_PATH) + sizeof(EFI_IP_ADDRESS))));


  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);  

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid132,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Dns(192.168.22.100,192.168.22.101)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // Dns(1234:5678:ABCD:1234:5678:ABCD:1234:5678,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD)
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x1F, sizeof(DNS_DEVICE_PATH) + 2 * sizeof(EFI_IP_ADDRESS));
  ((DNS_DEVICE_PATH *)pDeviceNode1)->IsIPv6 = 1;

  ConvertStrToIPv6Addr (L"1234:5678:ABCD:1234:5678:ABCD:1234:5678", ((EFI_IPv6_ADDRESS *)((UINT8 *)pDeviceNode1 + sizeof(DNS_DEVICE_PATH))));
  ConvertStrToIPv6Addr (L"5678:ABCD:1234:5678:ABCD:1234:5678:ABCD", ((EFI_IPv6_ADDRESS *)((UINT8 *)pDeviceNode1 + sizeof(DNS_DEVICE_PATH) + sizeof(EFI_IP_ADDRESS))));


  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);  

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid132,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected: Dns(1234:5678:ABCD:1234:5678:ABCD:1234:5678,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  //
  // The stardand Text in spec is iSCSI(TargetName, PortalGroup, LUN, HeaderDigest, DataDigest, Authentication, Protocol)
  // The test use iSCSI(Name,0x12AB,0x0000005678000000,CRC32C,None,CHAP_BI,TCP) as the input to check binary/text convertion
  //
  // sizeof (ISCSI_DEVICE_PATH_WITH_NAME) + 4 is the length of iSCSI Device Path Node plus Target Name
  // The Targat Name is "Name" in this case
  // The default protocol used by iSCSI is TCP(0), and 1+ is reserved in UEFI 2.7 spec
  // The combination of HeaderDigest, DataDigest and Authentication in this case is 0002
  // The Lun is 0x0000007856000000 in this case to detect the possible display order issue
  // please refer to section 10.3.5.21 and Table 102 of UEFI 2.7 Spec for detail.
  //
  pDeviceNode1 = DevicePathUtilities->CreateDeviceNode (0x3, 0x13, sizeof (ISCSI_DEVICE_PATH_WITH_NAME) + 4);
  ((ISCSI_DEVICE_PATH_WITH_NAME *)pDeviceNode1)->NetworkProtocol = 0x0;
  ((ISCSI_DEVICE_PATH_WITH_NAME *)pDeviceNode1)->LoginOption = 0x0002;
  ((ISCSI_DEVICE_PATH_WITH_NAME *)pDeviceNode1)->Lun = 0x0000007856000000;
  ((ISCSI_DEVICE_PATH_WITH_NAME *)pDeviceNode1)->TargetPortalGroupTag = 0x12AB;
  ((ISCSI_DEVICE_PATH_WITH_NAME *)pDeviceNode1)->iSCSITargetName[0] = 'N';
  ((ISCSI_DEVICE_PATH_WITH_NAME *)pDeviceNode1)->iSCSITargetName[1] = 'a';
  ((ISCSI_DEVICE_PATH_WITH_NAME *)pDeviceNode1)->iSCSITargetName[2] = 'm';
  ((ISCSI_DEVICE_PATH_WITH_NAME *)pDeviceNode1)->iSCSITargetName[3] = 'e';

  Text = DevicePathToText->ConvertDeviceNodeToText (pDeviceNode1, FALSE, FALSE);
  pDeviceNode2 = SctConvertTextToDeviceNode(Text);

  if ((pDeviceNode2 != NULL) && (SctCompareMem (pDeviceNode2, pDeviceNode1, SctDevicePathNodeLength(pDeviceNode1)) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathToTextBBTestFunctionAssertionGuid135,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d: Convert result: %s - Expected:iSCSI(MyTargetName,0x12AB,0x0000005678000000,CRC32C,None,CHAP_BI,TCP)",
                __FILE__,
                (UINTN)__LINE__,
                Text
                );
  if (pDeviceNode1 != NULL) {
    SctFreePool (pDeviceNode1);
  }
  if (pDeviceNode2 != NULL) {
    SctFreePool (pDeviceNode2);
  }
  if (Text != NULL) {
    SctFreePool (Text);
  }

  return EFI_SUCCESS;
}

