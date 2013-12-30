/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DevicePathToTextBBTestMain.c

Abstract:

  Test Driver of Device Path To Text Protocol

--*/

#include "DevicePathToTextBBTestMain.h"

//
// Build Data structure here
//
EFI_BB_TEST_PROTOCOL_FIELD  gBBTestProtocolField = {
  DEVICE_PATH_PROTOCOL_TEST_REVISION,
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID,
  L"Device Path To Text Protocol Test",
  L"UEFI Device Path To Text Protocol Test"
};

EFI_GUID                    gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD     gBBTestEntryField[] = {
  {
    DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICENODETOTEXT_FUNCTION_GUID,
    L"ConvertDeviceNodeToText_Functionality",
    L"Invoke the ConvertDeviceNodeToText and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathToTextConvertDeviceNodeToTextFunctionTest
  },
  {
    DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICEPATHTOTEXT_FUNCTION_GUID,
    L"ConvertDevicePathToText_Functionality",
    L"Invoke the ConvertDevicePathToText and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathToTextConvertDevicePathToTextFunctionTest
  },
  {
    DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICENODETOTEXT_CONFORMANCE_GUID,
    L"ConvertDeviceNodeToText_Conformance",
    L"Perform conformance test on the ConvertDeviceNodeToText service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathToTextConvertDeviceNodeToTextConformanceTest
  },
  {
    DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICEPATHTOTEXT_CONFORMANCE_GUID,
    L"ConvertDevicePathToText_Conformance",
    L"Perform conformance test on the ConvertDevicePathToText service",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathToTextConvertDevicePathToTextConformanceTest
  },
  {
    DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICENODETOTEXT_COVERAGE_GUID,
    L"ConvertDeviceNodeToText_Coverage",
    L"Invoke the ConvertDeviceNodeToText and ConvertTextToDeviceNode respectively or cooperatively, and verify service correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    DevicePathToTextConvertDeviceNodeToTextCoverageTest
  },
  0
};

EFI_BB_TEST_PROTOCOL        *gBBTestProtocolInterface;

EFI_STATUS
BBTestDevicePathToTextProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_DRIVER_ENTRY_POINT (InitializeBBTestDevicePathToTextProtocol)

/**
 *  Device Path Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestDevicePathToTextProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  InitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
          &ImageHandle,
          &gBBTestProtocolField,
          gBBTestEntryField,
          BBTestDevicePathToTextProtocolUnload,
          &gBBTestProtocolInterface
          );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestDevicePathToTextProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS  Status;

  Status = EfiUninstallAndFreeBBTestInterface (
            ImageHandle,
            gBBTestProtocolInterface
            );

  return Status;
}

/*-----------------------------------------------------------------*/
EFI_GUID mEfiDevicePathMessagingUartFlowControlGuid = DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL;

extern EFI_GUID mEfiDevicePathMessagingSASGuid;

#define IS_HYPHEN(a)         ((a) == L'-')
#define IS_NULL(a)           ((a) == L'\0')

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

    IsHexDigit (&Digit, *Str);

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
StrToUInt16 (
  IN  CHAR16    *Str,
  OUT UINT16    *Result
  )
{
  UINTN     Index;
  UINTN     StrLength;
  UINT8     Digit;
  UINT16    Base;

  StrTrim (Str, L' ');

  StrLength = StrLen (Str);
  Base      = 10;
  //
  // Check hex prefix '0x'
  //
  if (StrLength >= 2 && *Str == '0' && (*(Str + 1) == 'x' || *(Str + 1) == 'X')) {
    Str       += 2;
    StrLength -= 2;
    Base       = 16;
  }

  for(Index = 0; Index < StrLength; Index++) {
    if (IsHexDigit (&Digit, Str[Index]) == FALSE) {
      return EFI_INVALID_PARAMETER;
    }
  }

  if (Base == 10) {
    *Result = (UINT16) Atoi(Str);
  } else {
    *Result = (UINT16) xtoi(Str);
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
  Status = HexStringToBuf ((UINT8 *) &Guid->Data1, &BufferLength, Str, &ConvertedStrLen);
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
  Status = HexStringToBuf ((UINT8 *) &Guid->Data2, &BufferLength, Str, &ConvertedStrLen);
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
  Status = HexStringToBuf ((UINT8 *) &Guid->Data3, &BufferLength, Str, &ConvertedStrLen);
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
EFI_STATUS
UnicodeToAscii (
  IN CHAR16                       *UnicodeStr,
  OUT CHAR8                       *AsciiStr
  )
{
  if ((UnicodeStr == NULL) || (AsciiStr == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  while (*UnicodeStr != L'\0') {
    *AsciiStr = (CHAR8) *UnicodeStr;
    UnicodeStr ++;
    AsciiStr ++;
  }

  *AsciiStr = '\0';

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
GetIdentifierStrAndValue (
  IN  CHAR16               *ParamStr,
  OUT CHAR16               **ParamIdentifierStr,
  OUT CHAR16               **ParamIdentifierVal
  )
{
  CHAR16                   *ValStr;

  *ParamIdentifierStr = NULL;
  *ParamIdentifierVal = ParamStr;

  ValStr = StrChr(ParamStr, L'=');
  if (ValStr != NULL) {
    *ValStr = L'\0';
    *ParamIdentifierStr = ParamStr;
    *ParamIdentifierVal = ValStr + 1;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
GetNextRequiredParam (
  IN OUT CHAR16                     **ParamStr,
  IN  CHAR16                        *IdentiferStr,
  OUT CHAR16                        **ParamIdentifierStr,
  OUT CHAR16                        **ParamIdentifierVal
  )
{
  CHAR16                            *Str;

  *ParamIdentifierStr = NULL;
  *ParamIdentifierVal = NULL;

  if ((*ParamStr == NULL) || (**ParamStr == L'\0')) {
    return EFI_SUCCESS;
  }

  Str = StrChr(*ParamStr, L',');
  if (Str != NULL) {
    *Str = L'\0';
    GetIdentifierStrAndValue(*ParamStr, ParamIdentifierStr, ParamIdentifierVal);
	*ParamStr = Str + 1;
  } else {
    //
    // The last parameter
    //
    GetIdentifierStrAndValue(*ParamStr, ParamIdentifierStr, ParamIdentifierVal);
    *ParamStr = NULL;
  }

  if ((*ParamIdentifierStr != NULL) && (StrCmp(*ParamIdentifierStr, IdentiferStr) != 0)) {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

STATIC
VOID
GetNextOptionalParam (
  IN OUT CHAR16                     **ParamStr,
  OUT CHAR16                        **ParamIdentifierStr,
  OUT CHAR16                        **ParamIdentifierVal
  )
{
  CHAR16                            *Str;

  *ParamIdentifierStr = NULL;
  *ParamIdentifierVal = NULL;

  if ((*ParamStr == NULL) || (**ParamStr == L'\0')) {
    *ParamStr = NULL;
    return ;
  }

  Str = StrChr(*ParamStr, L',');
  if (Str != NULL) {
    *Str = L'\0';
    GetIdentifierStrAndValue(*ParamStr, ParamIdentifierStr, ParamIdentifierVal);
    *ParamStr = Str + 1;
  } else {
    //
    // The last parameter
    //
    GetIdentifierStrAndValue(*ParamStr, ParamIdentifierStr, ParamIdentifierVal);
    *ParamStr = NULL;
  }

}

STATIC
UINT32
GetParamTotalNum (
  IN CHAR16                     *ParamStr
  )
{
  CHAR16                        *Str;
  UINT32                        Num;

  Str = ParamStr;
  Num = 0;

  while ((Str != NULL) && (*Str != L'\0')) {
    Str = StrChr(Str, L',');
    if (Str != NULL) {
      Str++;
    }
    Num++;
  }

  return Num;
}

STATIC
VOID
StrToUInt8Array (
  IN  CHAR16    *Str,
  OUT UINT8     *Result
  )
{
  UINTN    Index;
  UINTN    StrLength;
  UINT8    Digit;
  UINT8    Byte;

  StrTrim (Str, L' ');

  StrLength = StrLen (Str);
  //
  // Check hex prefix '0x'
  //
  if (StrLength >= 2 && *Str == '0' && (*(Str + 1) == 'x' || *(Str + 1) == 'X')) {
    Str       += 2;
    StrLength -= 2;
  }

  for(Index = 0; Index < StrLength; Index++, Str++) {

    IsHexDigit (&Digit, *Str);

    //
    // For odd charaters, write the upper nibble for each buffer byte,
    // and for even characters, the lower nibble.
    //
    if ((Index & 1) == 0) {
      Byte = Digit << 4;
    } else {
      Byte = Result[Index / 2];
      Byte &= 0xF0;
      Byte |= Digit;
    }

    Result[Index / 2] = Byte;
  }

}

STATIC
BOOLEAN
CheckParamIdentiferValid (
  IN CHAR16                         *ParamIdentifierStr,
  IN CHAR16                         *Identifier,
  IN UINT32                         ExpectOptionalParamIndex,
  IN UINT32                         CurrentOptionalParamIndex
  )
{
  if ((ExpectOptionalParamIndex > CurrentOptionalParamIndex) || 
  	  ((Identifier != NULL) && StrCmp(ParamIdentifierStr, Identifier) != 0)) {
    return FALSE;
  }

  return TRUE;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateDeviceNode (
  IN UINT8                           NodeType,
  IN UINT8                           NodeSubType,
  IN UINT16                          NodeLength
  )
{
  EFI_DEVICE_PATH_PROTOCOL      *DevicePath;

  if (NodeLength < sizeof (EFI_DEVICE_PATH_PROTOCOL)) {
    return NULL;
  }
 
  DevicePath = AllocateZeroPool (NodeLength);
  if (DevicePath != NULL) {
     DevicePath->Type    = NodeType;
     DevicePath->SubType = NodeSubType;
     SetDevicePathNodeLength (DevicePath, NodeLength);
  }

  return DevicePath;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateEndDeviceNode(
  VOID
  )
{
  EFI_DEVICE_PATH_PROTOCOL *DevPath;

  DevPath = (EFI_DEVICE_PATH_PROTOCOL *) AllocateZeroPool (sizeof(EFI_DEVICE_PATH_PROTOCOL));
  if (DevPath == NULL) {
    return NULL;
  }
  SetDevicePathEndNode (DevPath);

  return DevPath;
}

STATIC
UINT32
ConvertEisaIDFromStr (
  IN CHAR16             *Str
  )
{
  if ((Str[0] == L'P') && (Str[1] == L'N') && (Str[2] == L'P')) {
    return EISA_PNP_ID(xtoi(Str + 3));
  }
  return (UINT32)xtoi(Str);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
ConvertFromTextAcpi (
  IN CHAR16             *TextDeviceNode,
  IN UINT32             Hid
  )
{
  CHAR16                *ParamIdentifierStr;
  CHAR16                *ParamIdentifierVal;
  ACPI_HID_DEVICE_PATH  *Acpi;
  UINT32                OptionalParamIndex;

  Acpi   = (ACPI_HID_DEVICE_PATH *) CreateDeviceNode (0x2, 0x1, sizeof (ACPI_HID_DEVICE_PATH));
  if (Acpi == NULL) {
    return NULL;
  }

  Acpi->HID = Hid;
  Acpi->UID = 0;

  for (OptionalParamIndex = 0; OptionalParamIndex < 1; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid (ParamIdentifierStr, L"UID", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
        Acpi->UID = (UINT32) StrToUInt (ParamIdentifierVal);
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // UID
        Acpi->UID = (UINT32) StrToUInt (ParamIdentifierVal);
        break;

      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Acpi;
InValidText:
  FreePool(Acpi);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildPciRootDeviceNode (
  IN CHAR16             *TextDeviceNode
  )
{
  return ConvertFromTextAcpi (TextDeviceNode, 0x0a0341d0);
}

STATIC EFI_DEVICE_PATH_PROTOCOL *
BuildPcieRootDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  return ConvertFromTextAcpi (TextDeviceNode, 0x0a0841d0);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildFloppyDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  return ConvertFromTextAcpi (TextDeviceNode, 0x060441d0);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildKeyboardDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  return ConvertFromTextAcpi (TextDeviceNode, 0x030141d0);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildSerialDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  return ConvertFromTextAcpi (TextDeviceNode, 0x050141d0);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildParallelPortDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  return ConvertFromTextAcpi (TextDeviceNode, 0x040141d0);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildPciDeviceNode (
  IN CHAR16             *TextDeviceNode
  )
{
  EFI_STATUS            Status;
  CHAR16                *ParamIdentifierStr;
  CHAR16                *ParamIdentifierVal;
  PCI_DEVICE_PATH       *Pci;

  Pci = (PCI_DEVICE_PATH *) CreateDeviceNode (0x1, 0x1, sizeof (PCI_DEVICE_PATH));
  if (Pci == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Device", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Pci->Device = (UINT8) StrToUInt (ParamIdentifierVal);
  } else {
    goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Function", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Pci->Function = (UINT8) StrToUInt (ParamIdentifierVal);
  } else {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Pci;
InValidText:
  FreePool(Pci);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildPcCardDeviceNode (
  IN CHAR16                *TextDeviceNode
  )
{
  EFI_STATUS               Status;
  CHAR16                   *ParamIdentifierStr;
  CHAR16                   *ParamIdentifierVal;
  PCCARD_DEVICE_PATH       *Pccard;

  Pccard = (PCCARD_DEVICE_PATH *) CreateDeviceNode (0x1, 0x2, sizeof (PCCARD_DEVICE_PATH));
  if (Pccard == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Function", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Pccard->FunctionNumber = (UINT8) StrToUInt (ParamIdentifierVal);
  } else {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Pccard;
InValidText:
  FreePool(Pccard);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildMemoryMappedDeviceNode (
  IN CHAR16                *TextDeviceNode
  )
{
  EFI_STATUS               Status;
  CHAR16                   *ParamIdentifierStr;
  CHAR16                   *ParamIdentifierVal;
  MEMMAP_DEVICE_PATH       *MemMap;

  MemMap             = (MEMMAP_DEVICE_PATH *) CreateDeviceNode (0x1, 0x3, sizeof (MEMMAP_DEVICE_PATH));
  if (MemMap == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"EfiMemoryType", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    MemMap->MemoryType = (UINT32) StrToUInt (ParamIdentifierVal);
  } else {
    goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"StartingAddress", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64 (ParamIdentifierVal, &MemMap->StartingAddress);
  } else {
    goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"EndingAddress", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64 (ParamIdentifierVal, &MemMap->EndingAddress);
  } else {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) MemMap;
InValidText:
  FreePool(MemMap);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildCtrlDeviceNode (
  IN CHAR16               *TextDeviceNode
  )
{
  EFI_STATUS               Status;
  CHAR16                   *ParamIdentifierStr;
  CHAR16                   *ParamIdentifierVal;
  CONTROLLER_DEVICE_PATH   *Controller;

  Controller = (CONTROLLER_DEVICE_PATH *) CreateDeviceNode (0x1, 0x5, sizeof (CONTROLLER_DEVICE_PATH));
  if (Controller == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Controller", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Controller->Controller = (UINT32) StrToUInt(ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Controller;
InValidText:
  FreePool(Controller);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildAcpiDeviceNode (
  IN CHAR16             *TextDeviceNode
  )
{
  EFI_STATUS               Status;
  CHAR16                   *ParamIdentifierStr;
  CHAR16                   *ParamIdentifierVal;
  UINT32                   OptionalParamIndex;
  ACPI_HID_DEVICE_PATH     *Acpi;

  Acpi   = (ACPI_HID_DEVICE_PATH *) CreateDeviceNode (0x2, 0x1, sizeof (ACPI_HID_DEVICE_PATH));
  if (Acpi == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"HID", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Acpi->HID  = (UINT32) ConvertEisaIDFromStr(ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  Acpi->UID = 0;

  for (OptionalParamIndex = 0; OptionalParamIndex < 1; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid (ParamIdentifierStr, L"UID", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
	    Acpi->UID = (UINT32) StrToUInt(ParamIdentifierVal);
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // UID
	    Acpi->UID = (UINT32) StrToUInt(ParamIdentifierVal);
        break;

      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Acpi;
InValidText:
  FreePool(Acpi);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildAcpiExDeviceNode (
  IN CHAR16                               *TextDeviceNode
  )
{
  EFI_STATUS                              Status;
  CHAR16                                  *ParamIdentifierStr;
  CHAR16                                  *ParamIdentifierVal;
  ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR  *AcpiExt;
  UINT16                                  Length;
  CHAR16                                  *HIDStr;
  CHAR16                                  *CIDStr;
  CHAR16                                  *UIDStr;
  CHAR16                                  *HIDSTRStr;
  CHAR16                                  *CIDSTRStr;
  CHAR16                                  *UIDSTRStr;

  Status = GetNextRequiredParam(&TextDeviceNode, L"HID", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    HIDStr = ParamIdentifierVal;
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"CID", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    CIDStr = ParamIdentifierVal;
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"UID", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    UIDStr = ParamIdentifierVal;
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"HIDSTR", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    HIDSTRStr = ParamIdentifierVal;
  } else {
  	goto InValidText;
  }

  if (0 == ConvertEisaIDFromStr(CIDStr)) {
    Status = GetNextRequiredParam(&TextDeviceNode, L"CIDSTR", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      CIDSTRStr = ParamIdentifierVal;
    } else {
      goto InValidText;
    }
  } else {
    CIDSTRStr = L"\0";
  }

  if (0 == StrToUInt(UIDStr)) {
    Status = GetNextRequiredParam(&TextDeviceNode, L"UIDSTR", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      UIDSTRStr = ParamIdentifierVal;
    } else {
      goto InValidText;
    }
  } else {
    UIDSTRStr = L"\0";
  }

  Length    = sizeof (ACPI_EXTENDED_HID_DEVICE_PATH) + 
                  (UINT16) EfiStrLen (HIDSTRStr) + 1 +
                  (UINT16) EfiStrLen (UIDSTRStr) + 1 +
                  (UINT16) EfiStrLen (CIDSTRStr) + 1;

  AcpiExt = (ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *) CreateDeviceNode (0x2, 0x2, Length);
  if (AcpiExt == NULL) {
    return NULL;
  }

  AcpiExt->HID  = ConvertEisaIDFromStr(HIDStr);
  AcpiExt->CID  = ConvertEisaIDFromStr(CIDStr);
  AcpiExt->UID  = (UINT32) StrToUInt (UIDStr);

  StrToAscii (HIDSTRStr, AcpiExt->HidUidCidStr);
  StrToAscii (CIDSTRStr, AcpiExt->HidUidCidStr + (UINT16) EfiStrLen (HIDSTRStr) + 1);
  StrToAscii (UIDSTRStr, AcpiExt->HidUidCidStr + (UINT16) EfiStrLen (CIDSTRStr) + 1);

  return (EFI_DEVICE_PATH_PROTOCOL *) AcpiExt;
InValidText:
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildAcpiExpDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  EFI_STATUS                              Status;
  CHAR16                                  *ParamIdentifierStr;
  CHAR16                                  *ParamIdentifierVal;
  UINT32                                  OptionalParamIndex;
  ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR  *AcpiExp;
  UINT16                                  Length;
  CHAR16                                  *HIDStr;
  CHAR16                                  *CIDStr;
  CHAR16                                  *UIDSTRStr;

  Status = GetNextRequiredParam(&TextDeviceNode, L"HID", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    HIDStr = ParamIdentifierVal;
  } else {
  	goto InValidText;
  }

  CIDStr    = L"0";
  UIDSTRStr = L"\0";

  for (OptionalParamIndex = 0; OptionalParamIndex < 2; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid(ParamIdentifierStr, L"CID", OptionalParamIndex, 0)) {
	  	OptionalParamIndex = 0;
	    CIDStr = ParamIdentifierVal;
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"UIDSTR", OptionalParamIndex, 1)) {
        OptionalParamIndex = 1;
        UIDSTRStr = ParamIdentifierVal;
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // CID
	    CIDStr = ParamIdentifierVal;
        break;
      case 1:  // UIDSTR
        UIDSTRStr = ParamIdentifierVal;
        break;
      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  Length    = sizeof (ACPI_EXTENDED_HID_DEVICE_PATH) + (UINT16) EfiStrLen (UIDSTRStr) + 3;

  AcpiExp   = (ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *) CreateDeviceNode (0x2, 0x2, Length);
  if (AcpiExp == NULL) {
    return NULL;
  }

  AcpiExp->HID = ConvertEisaIDFromStr(HIDStr);
  AcpiExp->CID = ConvertEisaIDFromStr(CIDStr);
  AcpiExp->UID = 0;                               // UID = 0
  AcpiExp->HidUidCidStr[0] = '\0';                // HIDSTR = empty
  StrToAscii (UIDSTRStr, &AcpiExp->HidUidCidStr[1]);
  AcpiExp->HidUidCidStr[2+(UINT16) EfiStrLen (UIDSTRStr)] = '\0';    // CIDSTR = empty
  

  return (EFI_DEVICE_PATH_PROTOCOL *) AcpiExp;
InValidText:
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildAcpiAdrDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  EFI_STATUS            Status;
  CHAR16                *ParamIdentifierStr;
  CHAR16                *ParamIdentifierVal;
  ACPI_ADR_DEVICE_PATH  *AcpiAdr;

  AcpiAdr = (ACPI_ADR_DEVICE_PATH *) CreateDeviceNode (0x2, 0x3, sizeof (ACPI_ADR_DEVICE_PATH));
  if (AcpiAdr == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"DisplayDevice", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    AcpiAdr->ADR = (UINT32) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) AcpiAdr;
InValidText:
  FreePool(AcpiAdr);
  return NULL;
}



STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildAtaDeviceNode (
  IN CHAR16             *TextDeviceNode
  )
{
  EFI_STATUS            Status;
  CHAR16                *ParamIdentifierStr;
  CHAR16                *ParamIdentifierVal;
  ATAPI_DEVICE_PATH     *Atapi;

  Atapi = (ATAPI_DEVICE_PATH *) CreateDeviceNode (0x3, 0x1, sizeof (ATAPI_DEVICE_PATH));
  if (Atapi == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Controller", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
  	if ((StrCmp (ParamIdentifierVal, L"Primary") == 0) || (StrCmp(ParamIdentifierVal, L"0"))) {
      Atapi->PrimarySecondary = 0;
    } else if ((StrCmp (ParamIdentifierVal, L"Secondary") == 0) || (StrCmp(ParamIdentifierVal, L"1"))) {
      Atapi->PrimarySecondary = 1;
    } else {
      goto InValidText;
    }
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Drive", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
  	if ((StrCmp (ParamIdentifierVal, L"Master") == 0) || (StrCmp(ParamIdentifierVal, L"0"))) {
      Atapi->SlaveMaster = 0;
    } else if ((StrCmp (ParamIdentifierVal, L"Slave") == 0) || (StrCmp(ParamIdentifierVal, L"1"))) {
      Atapi->SlaveMaster = 1;
    } else {
      goto InValidText;
    }
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"LUN", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Atapi->Lun = (UINT16) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Atapi;
InValidText:
  FreePool(Atapi);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildScsiDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  EFI_STATUS            Status;
  CHAR16                *ParamIdentifierStr;
  CHAR16                *ParamIdentifierVal;
  SCSI_DEVICE_PATH      *Scsi;

  Scsi   = (SCSI_DEVICE_PATH *) CreateDeviceNode (0x3, 0x2, sizeof (SCSI_DEVICE_PATH));
  if (Scsi == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"PUN", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Scsi->Pun = (UINT16) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"LUN", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Scsi->Lun = (UINT16) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Scsi;
InValidText:
  FreePool(Scsi);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildFibreDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  EFI_STATUS                Status;
  CHAR16                    *ParamIdentifierStr;
  CHAR16                    *ParamIdentifierVal;
  FIBRECHANNEL_DEVICE_PATH  *Fibre;

  Fibre  = (FIBRECHANNEL_DEVICE_PATH *) CreateDeviceNode (0x3, 0x3, sizeof (FIBRECHANNEL_DEVICE_PATH));
  if (Fibre == NULL) {
    return NULL;
  }

  Fibre->Reserved = 0;

  Status = GetNextRequiredParam(&TextDeviceNode, L"WWN", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64(ParamIdentifierVal, &Fibre->WWN);
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"LUN", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64 (ParamIdentifierVal, &Fibre->Lun);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Fibre;
InValidText:
  FreePool(Fibre);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildFibreExDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  EFI_STATUS                  Status;
  CHAR16                      *ParamIdentifierStr;
  CHAR16                      *ParamIdentifierVal;
  FIBRECHANNELEX_DEVICE_PATH  *FibreEx;

  FibreEx  = (FIBRECHANNELEX_DEVICE_PATH *) CreateDeviceNode (0x3, 0x15, sizeof (FIBRECHANNELEX_DEVICE_PATH));
  if (FibreEx == NULL) {
    return NULL;
  }

  FibreEx->Reserved = 0;

  Status = GetNextRequiredParam(&TextDeviceNode, L"WWN", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt8Array(ParamIdentifierVal, FibreEx->WWN);
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"LUN", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt8Array (ParamIdentifierVal, FibreEx->Lun);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) FibreEx;
InValidText:
  FreePool(FibreEx);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
Build1394DeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  EFI_STATUS                Status;
  CHAR16                    *ParamIdentifierStr;
  CHAR16                    *ParamIdentifierVal;
  F1394_DEVICE_PATH         *F1394;

  F1394  = (F1394_DEVICE_PATH *) CreateDeviceNode (0x3, 0x4, sizeof (F1394_DEVICE_PATH));
  if (F1394 == NULL) {
    return NULL;
  }

  F1394->Reserved = 0;

  Status = GetNextRequiredParam(&TextDeviceNode, L"GUID", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64(ParamIdentifierVal, &F1394->Guid);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) F1394;
InValidText:
  FreePool(F1394);
  return NULL;
}

EFI_DEVICE_PATH_PROTOCOL *
BuildUsbDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  EFI_STATUS                Status;
  CHAR16                    *ParamIdentifierStr;
  CHAR16                    *ParamIdentifierVal;
  USB_DEVICE_PATH           *Usb;

  Usb = (USB_DEVICE_PATH *) CreateDeviceNode (0x3, 0x5, sizeof (USB_DEVICE_PATH));
  if (Usb == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Port", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Usb->ParentPortNumber = (UINT8) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Interface", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Usb->InterfaceNumber  = (UINT8) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Usb;
InValidText:
  FreePool(Usb);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildI2ODeviceNode (
  IN CHAR16                 *TextDeviceNode
  )
{
  EFI_STATUS                Status;
  CHAR16                    *ParamIdentifierStr;
  CHAR16                    *ParamIdentifierVal;
  I2O_DEVICE_PATH           *I2O;

  I2O = (I2O_DEVICE_PATH *) CreateDeviceNode (0x3, 0x6, sizeof (I2O_DEVICE_PATH));
  if (I2O == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"TID", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    I2O->Tid = (UINT32) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) I2O;
InValidText:
  FreePool(I2O);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildVlanDeviceNode (
  IN CHAR16                 *TextDeviceNode
  )
{
  EFI_STATUS                Status;
  CHAR16                    *ParamIdentifierStr;
  CHAR16                    *ParamIdentifierVal;
  VLAN_DEVICE_PATH          *Vlan;

  Vlan = (VLAN_DEVICE_PATH *) CreateDeviceNode (0x3, 0x14, sizeof (VLAN_DEVICE_PATH));
  if (Vlan == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"VlanId", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    Vlan->VlanId = (UINT16) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Vlan;
InValidText:
  FreePool(Vlan);
  return NULL;
}


STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildInfinibandDeviceNode (
  IN CHAR16               *TextDeviceNode
  )
{
  EFI_STATUS                Status;
  CHAR16                    *ParamIdentifierStr;
  CHAR16                    *ParamIdentifierVal;
  INFINIBAND_DEVICE_PATH    *InfiniBand;
  EFI_GUID                  PortGid;

  InfiniBand = (INFINIBAND_DEVICE_PATH *) CreateDeviceNode (0x3, 0x9, sizeof (INFINIBAND_DEVICE_PATH));
  if (InfiniBand == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Flags", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    InfiniBand->ResourceFlags = (UINT32) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Guid", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToGuid (ParamIdentifierVal, &PortGid);
    CopyMem (InfiniBand->PortGid, &PortGid, sizeof (EFI_GUID));
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"ServiceId", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64(ParamIdentifierVal, &InfiniBand->ServiceId);
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"TargetId", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64(ParamIdentifierVal, &InfiniBand->TargetPortId);
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"DeviceId", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64(ParamIdentifierVal, &InfiniBand->DeviceId);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) InfiniBand;
InValidText:
  FreePool(InfiniBand);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
ConvertFromTextVendor (
  IN CHAR16                *TextDeviceNode,
  IN UINT8                 Type,
  IN UINT8                 SubType
  )
{
  EFI_STATUS               Status;
  CHAR16                   *ParamIdentifierStr;
  CHAR16                   *ParamIdentifierVal;
  VENDOR_DEVICE_PATH       *VenHw;
  CHAR16                   *GuidStr;
  CHAR16                   *DataStr;
  UINTN                    Length;
  UINT32                   OptionalParamIndex;

  Length = 0;

  Status = GetNextRequiredParam(&TextDeviceNode, L"Guid", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    GuidStr = ParamIdentifierVal;
  } else {
  	goto InValidText;
  }

  DataStr = NULL;

  for (OptionalParamIndex = 0;OptionalParamIndex < 1; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid(ParamIdentifierStr, L"Data", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
        DataStr = ParamIdentifierVal;
        Length = (EfiStrLen (DataStr) + 1) / 2;
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // Data
        DataStr = ParamIdentifierVal;
        Length = (EfiStrLen (DataStr) + 1) / 2;
		break;

      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  VenHw = (VENDOR_DEVICE_PATH *) CreateDeviceNode (Type, SubType, sizeof (VENDOR_DEVICE_PATH) + (UINT16)Length);
  if (VenHw == NULL) {
    return NULL;
  }

  StrToGuid (GuidStr, &VenHw->Guid);
  if (DataStr != NULL) {
    StrToBuf (((UINT8 *) VenHw) + sizeof (VENDOR_DEVICE_PATH), Length, DataStr);
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) VenHw;
InValidText:
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildVenHwDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  return ConvertFromTextVendor (TextDeviceNode, 0x1, 0x4);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildVenMsgDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  return ConvertFromTextVendor (TextDeviceNode, 0x3, 0x0a);
}

EFI_DEVICE_PATH_PROTOCOL *
BuildVenMEDIADeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  return ConvertFromTextVendor (TextDeviceNode, 0x4, 0x3);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildVenPcAnsiDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  VENDOR_DEVICE_PATH       *Vendor;

  Vendor = (VENDOR_DEVICE_PATH *) CreateDeviceNode (0x3, 0xa, sizeof (VENDOR_DEVICE_PATH));
  if (Vendor == NULL) {
    return NULL;
  }

  Vendor->Guid = gEfiPcAnsiGuid;

  return (EFI_DEVICE_PATH_PROTOCOL *) Vendor;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildVenVt100DeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  VENDOR_DEVICE_PATH  *Vendor;

  Vendor = (VENDOR_DEVICE_PATH *) CreateDeviceNode (0x3, 0xa, sizeof (VENDOR_DEVICE_PATH));
  if (Vendor == NULL) {
    return NULL;
  }

  Vendor->Guid = gEfiVT100Guid;

  return (EFI_DEVICE_PATH_PROTOCOL *) Vendor;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildVenVt100PlusDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  VENDOR_DEVICE_PATH  *Vendor;

  Vendor = (VENDOR_DEVICE_PATH *) CreateDeviceNode (0x3, 0xa, sizeof (VENDOR_DEVICE_PATH));
  if (Vendor == NULL) {
    return NULL;
  }

  Vendor->Guid = gEfiVT100PlusGuid;

  return (EFI_DEVICE_PATH_PROTOCOL *) Vendor;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildVenUtf8DeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  VENDOR_DEVICE_PATH  *Vendor;

  Vendor = (VENDOR_DEVICE_PATH *) CreateDeviceNode (0x3, 0xa, sizeof (VENDOR_DEVICE_PATH));
  if (Vendor == NULL) {
    return NULL;
  }

  Vendor->Guid = gEfiVTUTF8Guid;

  return (EFI_DEVICE_PATH_PROTOCOL *) Vendor;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUartFlowCtrlDeviceNode (
  IN CHAR16                      *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  UART_FLOW_CONTROL_DEVICE_PATH  *UartFlowControl;

  UartFlowControl = (UART_FLOW_CONTROL_DEVICE_PATH *) CreateDeviceNode (0x3, 0x0a, sizeof (UART_FLOW_CONTROL_DEVICE_PATH));
  if (UartFlowControl == NULL) {
    return NULL;
  }

  UartFlowControl->Guid = mEfiDevicePathMessagingUartFlowControlGuid;

  Status = GetNextRequiredParam(&TextDeviceNode, L"Value", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    if ((StrCmp(ParamIdentifierVal, L"XonXoff") == 0) || (StrCmp(ParamIdentifierVal, L"2") == 0)) {
      UartFlowControl->FlowControlMap = 2;
    } else if ((StrCmp(ParamIdentifierVal, L"Hardware") == 0) || (StrCmp(ParamIdentifierVal, L"1") == 0)) {
      UartFlowControl->FlowControlMap = 1;
    } else if ((StrCmp(ParamIdentifierVal, L"None") == 0) || (StrCmp(ParamIdentifierVal, L"0") == 0)) {
      UartFlowControl->FlowControlMap = 0;
    } else {
      goto InValidText;
    }
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) UartFlowControl;
InValidText:
  FreePool(UartFlowControl);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildDebugPortDeviceNode (
  IN CHAR16                             *TextDeviceNode
  )
{
  VENDOR_DEFINED_MESSAGING_DEVICE_PATH  *Vend;

  Vend = (VENDOR_DEFINED_MESSAGING_DEVICE_PATH *) CreateDeviceNode (0x3, 0x0a, sizeof (VENDOR_DEFINED_MESSAGING_DEVICE_PATH));

  Vend->Guid = gEfiDebugPortProtocolGuid;

  return (EFI_DEVICE_PATH_PROTOCOL *) Vend;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildMACDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  UINT32                         OptionalParamIndex;
  MAC_ADDR_DEVICE_PATH           *MAC;

  MAC = (MAC_ADDR_DEVICE_PATH *) CreateDeviceNode (0x3, 0x0b, sizeof(MAC_ADDR_DEVICE_PATH));
  if (MAC == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"MacAddr", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToBuf (&MAC->MacAddress.Addr[0], sizeof (EFI_MAC_ADDRESS), ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  for (OptionalParamIndex = 0;OptionalParamIndex < 1; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid(ParamIdentifierStr, L"IfType", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
        MAC->IfType = (UINT8) StrToUInt (ParamIdentifierVal);
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // IfType
        MAC->IfType = (UINT8) StrToUInt (ParamIdentifierVal);
		break;

      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) MAC;
InValidText:
  FreePool(MAC);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildIPv4DeviceNode (
  IN CHAR16                      *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  UINT32                         OptionalParamIndex;
  IPV4_DEVICE_PATH               *IPv4;

  IPv4   = (IPV4_DEVICE_PATH *) CreateDeviceNode (0x3, 0xc, sizeof (IPV4_DEVICE_PATH));
  if (IPv4 == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"RemoteIp", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToIPv4Addr (&ParamIdentifierVal, &IPv4->RemoteIpAddress);
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Protocol", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    IPv4->Protocol = (StrCmp (ParamIdentifierVal, L"UDP") == 0) ? (UINT16) 17 : (UINT16) 6;
  } else {
  	goto InValidText;
  }

  IPv4->LocalPort       = 0;
  IPv4->RemotePort      = 0;
  IPv4->StaticIpAddress = 0;

  for (OptionalParamIndex = 0;OptionalParamIndex < 4; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid(ParamIdentifierStr, L"Type", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
        IPv4->StaticIpAddress = (StrCmp(ParamIdentifierVal, L"Static") == 0) ? TRUE : FALSE;
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"LocalIp", OptionalParamIndex, 1)) {
        OptionalParamIndex = 1;
        StrToIPv4Addr (&ParamIdentifierVal, &IPv4->LocalIpAddress);
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // IfType
        IPv4->StaticIpAddress = (StrCmp(ParamIdentifierVal, L"Static") == 0) ? TRUE : FALSE;
        break;

      case 1:  // LocalIp
        StrToIPv4Addr (&ParamIdentifierVal, &IPv4->LocalIpAddress);
        break;

      case 2:  //Gateway
        StrToIPv4Addr (&ParamIdentifierVal, &IPv4->GatewayIPAddress);
        break;

      case 3:  //Subnet
        StrToIPv4Addr (&ParamIdentifierVal, &IPv4->SubnetMask);
        break;

      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) IPv4;
InValidText:
  FreePool(IPv4);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildIPv6DeviceNode (
  IN CHAR16         *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  UINT16                         PrefixLength;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  UINT32                         OptionalParamIndex;
  IPV6_DEVICE_PATH               *IPv6;

  IPv6   = (IPV6_DEVICE_PATH *) CreateDeviceNode (0x3, 0xd, sizeof (IPV6_DEVICE_PATH));
  if (IPv6 == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"RemoteIp", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToIPv6Addr (&ParamIdentifierVal, &IPv6->RemoteIpAddress);
  } else {
  	goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Protocol", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    IPv6->Protocol = (StrCmp (ParamIdentifierVal, L"UDP") == 0) ? (UINT16) 17 : (UINT16) 6;
  } else {
  	goto InValidText;
  }

  IPv6->LocalPort       = 0;
  IPv6->RemotePort      = 0;
  IPv6->IPAddressOrigin = 0;

  for (OptionalParamIndex = 0;OptionalParamIndex < 4; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid(ParamIdentifierStr, L"Type", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"LocalIp", OptionalParamIndex, 1)) {
        OptionalParamIndex = 1;
        StrToIPv6Addr (&ParamIdentifierVal, &IPv6->LocalIpAddress);
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // IPAddressOrigin
        IPv6->IPAddressOrigin = (StrCmp(ParamIdentifierVal, L"Static") == 0) ? 0 : (StrCmp(ParamIdentifierVal, L"StatelessAutoConfigure") == 0) ? 1 : 2;
        break;

      case 1:  // LocalIp
        StrToIPv6Addr (&ParamIdentifierVal, &IPv6->LocalIpAddress);
        break;

      case 2:  // PrefixLength 
        Status = StrToUInt16 (ParamIdentifierVal, &PrefixLength);
        if (EFI_ERROR (Status)) {
          goto InValidText;
        }
		IPv6->PrefixLength = (UINT8)PrefixLength;
        break;

      case 3:  // GatewayIPAddress 
        StrToIPv6Addr (&ParamIdentifierVal, &IPv6->GatewayIPAddress);
        break;

      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) IPv6;
InValidText:
  FreePool(IPv6);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUartDeviceNode (
  IN CHAR16                      *TextDeviceNode
  )
{
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  UINT32                         OptionalParamIndex;
  UART_DEVICE_PATH               *Uart;

  Uart  = (UART_DEVICE_PATH *) CreateDeviceNode (0x3, 0xe, sizeof (UART_DEVICE_PATH));
  if (Uart == NULL) {
    return NULL;
  }

  Uart->BaudRate = 115200;
  Uart->DataBits = 8;

  for (OptionalParamIndex = 0;OptionalParamIndex < 6; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid(ParamIdentifierStr, L"Baud", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
        Uart->BaudRate  = (StrCmp (ParamIdentifierVal, L"DEFAULT") == 0) ? 115200 : Atoi (ParamIdentifierVal);
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"DataBits", OptionalParamIndex, 1)) {
        OptionalParamIndex = 1;
        Uart->DataBits  = (StrCmp (ParamIdentifierVal, L"DEFAULT") == 0) ? (UINT8) 8 : (UINT8) Atoi (ParamIdentifierVal);
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"Parity", OptionalParamIndex, 2)) {
        OptionalParamIndex = 2;
        switch (*ParamIdentifierVal) {
        case L'D': Uart->Parity = 0; break;
        case L'N': Uart->Parity = 1; break;
        case L'E': Uart->Parity = 2; break;
        case L'O': Uart->Parity = 3; break;
        case L'M': Uart->Parity = 4; break;
        case L'S': Uart->Parity = 5; break;
        default: Uart->Parity = 0xff;
        }
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"StopBits", OptionalParamIndex, 3)) {
        OptionalParamIndex = 3;
        if (StrCmp (ParamIdentifierVal, L"D") == 0) {
          Uart->StopBits = (UINT8) 0;
        } else if (StrCmp (ParamIdentifierVal, L"1") == 0) {
          Uart->StopBits = (UINT8) 1;
        } else if (StrCmp (ParamIdentifierVal, L"1.5") == 0) {
          Uart->StopBits = (UINT8) 2;
        } else if (StrCmp (ParamIdentifierVal, L"2") == 0) {
          Uart->StopBits = (UINT8) 3;
        } else {
          Uart->StopBits = 0xff;
        }
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // Baud
        Uart->BaudRate  = (StrCmp (ParamIdentifierVal, L"DEFAULT") == 0) ? 115200 : Atoi (ParamIdentifierVal);
		break;

      case 1:  // DataBits
        Uart->DataBits  = (StrCmp (ParamIdentifierVal, L"DEFAULT") == 0) ? (UINT8) 8 : (UINT8) Atoi (ParamIdentifierVal);
        break;

      case 2:  // Parity
        switch (*ParamIdentifierVal) {
        case L'D': Uart->Parity = 0; break;
        case L'N': Uart->Parity = 1; break;
        case L'E': Uart->Parity = 2; break;
        case L'O': Uart->Parity = 3; break;
        case L'M': Uart->Parity = 4; break;
        case L'S': Uart->Parity = 5; break;
        default: Uart->Parity = 0xff;
        }
        break;

      case 3:  // StopBits
        if (StrCmp (ParamIdentifierVal, L"D") == 0) {
          Uart->StopBits = (UINT8) 0;
        } else if (StrCmp (ParamIdentifierVal, L"1") == 0) {
          Uart->StopBits = (UINT8) 1;
        } else if (StrCmp (ParamIdentifierVal, L"1.5") == 0) {
          Uart->StopBits = (UINT8) 2;
        } else if (StrCmp (ParamIdentifierVal, L"2") == 0) {
          Uart->StopBits = (UINT8) 3;
        } else {
          Uart->StopBits = 0xff;
        }
        break;

      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Uart;
InValidText:
  FreePool(Uart);
  return NULL;
}

typedef struct {
  BOOLEAN ClassExist;
  UINT8   Class;
  BOOLEAN SubClassExist;
  UINT8   SubClass;
} USB_CLASS_TEXT;

STATIC
EFI_DEVICE_PATH_PROTOCOL *
ConvertFromTextUsbClass (
  IN CHAR16                      *TextDeviceNode,
  IN USB_CLASS_TEXT              *UsbClassText
  )
{
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  UINT32                         OptionalParamIndex;
  USB_CLASS_DEVICE_PATH          *UsbClass;

  UsbClass    = (USB_CLASS_DEVICE_PATH *) CreateDeviceNode (0x3, 0xf, sizeof (USB_CLASS_DEVICE_PATH));
  if (UsbClass == NULL) {
    return NULL;
  }

  UsbClass->VendorId       = 0xFFFF;
  UsbClass->ProductId      = 0xFFFF;
  UsbClass->DeviceClass    = (UsbClassText->ClassExist == FALSE) ? (UsbClassText->Class) : 0xFF;
  UsbClass->DeviceSubClass = (UsbClassText->SubClassExist == FALSE) ? (UsbClassText->SubClassExist) : 0xFF;
  UsbClass->DeviceProtocol = 0xFF;

  for (OptionalParamIndex = 0;OptionalParamIndex < 5; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid(ParamIdentifierStr, L"VID", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
        UsbClass->VendorId = (UINT16) StrToUInt (ParamIdentifierVal);
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"PID", OptionalParamIndex, 1)) {
        OptionalParamIndex = 1;
        UsbClass->ProductId = (UINT16) StrToUInt (ParamIdentifierVal);
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"Class", OptionalParamIndex, 2)) {
        OptionalParamIndex = 2;
        if ((UsbClassText->ClassExist == FALSE) && 
			((ParamIdentifierStr != NULL) && StrCmp(ParamIdentifierStr, L"Class") == 0)) {
          goto InValidText;
        }
        UsbClass->DeviceClass = (UINT8) StrToUInt (ParamIdentifierVal);
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"SubClass", OptionalParamIndex, 3)) {
        OptionalParamIndex = 3;
        if ((UsbClassText->SubClassExist == FALSE) &&
			((ParamIdentifierStr != NULL) && StrCmp(ParamIdentifierStr, L"SubClass") == 0)) {
          goto InValidText;
        }
		UsbClass->DeviceSubClass = (UINT8) StrToUInt (ParamIdentifierVal);
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"Protocol", OptionalParamIndex, 4)) {
        OptionalParamIndex = 4;
        UsbClass->DeviceProtocol = (UINT8) StrToUInt (ParamIdentifierVal);
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // VID
        UsbClass->VendorId = (UINT16) StrToUInt (ParamIdentifierVal);
		break;

      case 1:  // PID
        UsbClass->ProductId = (UINT16) StrToUInt (ParamIdentifierVal);
        break;

      case 2:  // Class
        OptionalParamIndex = 2;
        if (UsbClassText->ClassExist == TRUE) {
          UsbClass->DeviceClass    = (UINT8) StrToUInt (ParamIdentifierVal);
          continue;
        }
      case 3:  // SubClass
        OptionalParamIndex = 3;
        if (UsbClassText->SubClassExist == TRUE) {
		  UsbClass->DeviceSubClass = (UINT8) StrToUInt (ParamIdentifierVal);
          continue;
        }
      case 4:  // Protocol
        OptionalParamIndex = 4;
        UsbClass->DeviceProtocol = (UINT8) StrToUInt (ParamIdentifierVal);
        break;

      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) UsbClass;
InValidText:
  FreePool(UsbClass);
  return NULL;
}


EFI_DEVICE_PATH_PROTOCOL *
BuildUsbClassDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = TRUE;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

EFI_DEVICE_PATH_PROTOCOL *
BuildUsbAudioDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_AUDIO;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

EFI_DEVICE_PATH_PROTOCOL *
BuildUsbCDCControlDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_CDCCONTROL;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

EFI_DEVICE_PATH_PROTOCOL *
BuildUsbHIDControlDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_HID;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbImageDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_IMAGE;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbPrinterDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_PRINTER;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbMassStorageDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_MASS_STORAGE;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbHubDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_HUB;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbCDCDataDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_CDCDATA;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbSmartCardDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_SMART_CARD;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbVideoDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_VIDEO;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbDiagnosticDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_DIAGNOSTIC;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbWirelessDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_WIRELESS;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbDeviceFirmwareUpdateDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_RESERVE;
  UsbClassText.SubClassExist = FALSE;
  UsbClassText.SubClass      = USB_SUBCLASS_FW_UPDATE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbIrdaBridgeDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_RESERVE;
  UsbClassText.SubClassExist = FALSE;
  UsbClassText.SubClass      = USB_SUBCLASS_IRDA_BRIDGE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUsbTestAndMeasurementDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = USB_CLASS_RESERVE;
  UsbClassText.SubClassExist = FALSE;
  UsbClassText.SubClass      = USB_SUBCLASS_TEST;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildUnitDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  DEVICE_LOGICAL_UNIT_DEVICE_PATH *LogicalUnit;

  LogicalUnit = (DEVICE_LOGICAL_UNIT_DEVICE_PATH *) CreateDeviceNode (0x3, 0x11, sizeof (DEVICE_LOGICAL_UNIT_DEVICE_PATH));
  if (LogicalUnit == NULL) {
    return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"LUN", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    LogicalUnit->Lun = (UINT8) StrToUInt (ParamIdentifierVal);
  } else {
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) LogicalUnit;
InValidText:
  FreePool(LogicalUnit);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildiSCSIDeviceNode (
  IN CHAR16                      *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  UINT32                         OptionalParamIndex;
  ISCSI_DEVICE_PATH_WITH_NAME    *iSCSI;
  UINT16                         Length;
  CHAR16                         *NameStr;
  CHAR16                         *PortalGroupStr;
  CHAR16                         *LunStr;
  UINT16                         Options;
  UINT64                         LunNum;

  Status = GetNextRequiredParam(&TextDeviceNode, L"TargetName", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    NameStr = ParamIdentifierVal;
  } else {
  	return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"PortalGroup", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    PortalGroupStr = ParamIdentifierVal;
  } else {
  	return NULL;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"LUN", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    LunStr = ParamIdentifierVal;
  } else {
  	return NULL;
  }

  Length = sizeof (ISCSI_DEVICE_PATH_WITH_NAME) + (UINT16) (EfiStrLen (NameStr) * 2 + 2);
  iSCSI = (ISCSI_DEVICE_PATH_WITH_NAME *) CreateDeviceNode (0x3, 0x13, Length);
  if (iSCSI == NULL) {
  	return NULL;
  }

  Options = 0x0000;

  for (OptionalParamIndex = 0;OptionalParamIndex < 5; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid(ParamIdentifierStr, L"HeaderDigest", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
        if (StrCmp (ParamIdentifierVal, L"CRC32C") == 0) {
          Options |= 0x0002;
        }
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"DataDigest", OptionalParamIndex, 1)) {
        OptionalParamIndex = 1;
        if (StrCmp (ParamIdentifierVal, L"CRC32C") == 0) {
          Options |= 0x0008;
        }
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"Authentication", OptionalParamIndex, 2)) {
        OptionalParamIndex = 2;
        if (StrCmp (ParamIdentifierVal, L"None") == 0) {
          Options |= 0x0800;
        }
        if (StrCmp (ParamIdentifierVal, L"CHAP_UNI") == 0) {
          Options |= 0x1000;
        }
      } else if (CheckParamIdentiferValid(ParamIdentifierStr, L"Protocol", OptionalParamIndex, 3)) {
        OptionalParamIndex = 3;
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // HeaderDigest
        if (StrCmp (ParamIdentifierVal, L"CRC32C") == 0) {
          Options |= 0x0002;
        }
		break;

      case 1:  // DataDigest
        if (StrCmp (ParamIdentifierVal, L"CRC32C") == 0) {
          Options |= 0x0008;
        }
        break;

      case 2:  // Authentication
        if (StrCmp (ParamIdentifierVal, L"None") == 0) {
          Options |= 0x0800;
        }
        if (StrCmp (ParamIdentifierVal, L"CHAP_UNI") == 0) {
          Options |= 0x1000;
        }
        break;

      case 3:  // Protocol
        iSCSI->NetworkProtocol  = (UINT16) StrCmp (ParamIdentifierVal, L"TCP");
        break;

      default:
        goto InValidText;
      }
    }else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  UnicodeToAscii (NameStr, iSCSI->iSCSITargetName);
  iSCSI->TargetPortalGroupTag = (UINT16) StrToUInt (PortalGroupStr);
  StrToUInt64 (LunStr, &LunNum);
  iSCSI->Lun = LunNum;
  iSCSI->LoginOption = (UINT16) Options;

  return (EFI_DEVICE_PATH_PROTOCOL *) iSCSI;
InValidText:
  FreePool(iSCSI);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildHDDeviceNode (
  IN CHAR16                      *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  UINT32                         TotalParamNum;
  HARDDRIVE_DEVICE_PATH          *Hd;
  UINT32                         Signature32;
  EFI_GUID                       SignatureGuid;

  Hd = (HARDDRIVE_DEVICE_PATH *) CreateDeviceNode (0x4, 0x1, sizeof (HARDDRIVE_DEVICE_PATH));
  if (Hd == NULL) {
    return NULL;
  }

  Hd->PartitionNumber = 0;
  Hd->SignatureType   = SIGNATURE_TYPE_GUID;
  Hd->MBRType         = 0x02;

  TotalParamNum = GetParamTotalNum(TextDeviceNode);
  switch (TotalParamNum) {
  case 1: // HD(Signature)
    Status = GetNextRequiredParam(&TextDeviceNode, L"Signature", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      StrToGuid (ParamIdentifierVal, &SignatureGuid);
      CopyMem (Hd->Signature, &SignatureGuid, sizeof (EFI_GUID));
    } else {
      goto InValidText;
    }
    break;

  case 2: // HD(Type,Signature) | HD(Partition == 0,Signature)
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierVal == NULL) {
      goto InValidText;
    } else if (StrCmp(ParamIdentifierVal, L"0") == 0) {
      if ((ParamIdentifierStr != NULL) && (StrCmp(ParamIdentifierStr, L"Partition") != 0)) {
        goto InValidText;
      }
    } else if ((StrCmp(ParamIdentifierVal, L"1") == 0) || (StrCmp(ParamIdentifierVal, L"MBR") == 0)) {
      if ((ParamIdentifierStr != NULL) && (StrCmp(ParamIdentifierStr, L"Type") != 0)) {
        goto InValidText;
      }
      Hd->SignatureType = SIGNATURE_TYPE_MBR;
      Hd->MBRType       = 0x01;
      Signature32       = (UINT32) StrToUInt (ParamIdentifierVal);
      CopyMem (Hd->Signature, &Signature32, sizeof (UINT32));
    } else if ((StrCmp(ParamIdentifierVal, L"2") == 0) || (StrCmp(ParamIdentifierVal, L"GPT") == 0)) {
      if ((ParamIdentifierStr != NULL) && (StrCmp(ParamIdentifierStr, L"Type") != 0)) {
        goto InValidText;
      }
      Hd->SignatureType = SIGNATURE_TYPE_GUID;
      Hd->MBRType       = 0x02;
      StrToGuid (ParamIdentifierVal, &SignatureGuid);
      CopyMem (Hd->Signature, &SignatureGuid, sizeof (EFI_GUID));
    } else {
      goto InValidText;
    }

    Status = GetNextRequiredParam(&TextDeviceNode, L"Signature", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      StrToGuid (ParamIdentifierVal, &SignatureGuid);
      CopyMem (Hd->Signature, &SignatureGuid, sizeof (EFI_GUID));
    } else {
      goto InValidText;
    }
    break;

  case 3: // HD(Partition == 0,Type,Signature)
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if ((ParamIdentifierVal == NULL) || (StrCmp(ParamIdentifierVal, L"0") != 0) ||
        ((ParamIdentifierStr != NULL) && (StrCmp(ParamIdentifierStr, L"Partition") != 0))) {
      goto InValidText;
    }

    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
	if ((ParamIdentifierVal == NULL) ||
		((ParamIdentifierStr != NULL) && (StrCmp(ParamIdentifierStr, L"Type") != 0))) {
      goto InValidText;
	}
    if ((StrCmp(ParamIdentifierVal, L"1") == 0) || (StrCmp(ParamIdentifierVal, L"MBR") == 0)) {
      Hd->SignatureType = SIGNATURE_TYPE_MBR;
      Hd->MBRType       = 0x01;
    } else if ((StrCmp(ParamIdentifierVal, L"2") == 0) || (StrCmp(ParamIdentifierVal, L"GPT") == 0)) {
      Hd->SignatureType = SIGNATURE_TYPE_GUID;
      Hd->MBRType       = 0x02;
    } else {
      goto InValidText;
    }

    Status = GetNextRequiredParam(&TextDeviceNode, L"Signature", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      StrToGuid (ParamIdentifierVal, &SignatureGuid);
      CopyMem (Hd->Signature, &SignatureGuid, sizeof (EFI_GUID));
    } else {
      goto InValidText;
    }
    break;

  case 4: // HD(Partition != 0,Signature,Start, Size)
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if ((ParamIdentifierVal == NULL) || (StrCmp(ParamIdentifierVal, L"0") == 0) ||
		((ParamIdentifierStr != NULL) && (StrCmp(ParamIdentifierStr, L"Partition") != 0))) {
      goto InValidText;
    }
    Hd->PartitionNumber = (UINT32) StrToUInt(ParamIdentifierVal);

    Status = GetNextRequiredParam(&TextDeviceNode, L"Signature", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      StrToGuid (ParamIdentifierVal, &SignatureGuid);
      CopyMem (Hd->Signature, &SignatureGuid, sizeof (EFI_GUID));
    } else {
      goto InValidText;
    }
    Status = GetNextRequiredParam(&TextDeviceNode, L"Start", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      StrToUInt64 (ParamIdentifierVal, &Hd->PartitionStart);
    } else {
      goto InValidText;
    }
    Status = GetNextRequiredParam(&TextDeviceNode, L"Size", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      StrToUInt64 (ParamIdentifierVal, &Hd->PartitionSize);
    } else {
      goto InValidText;
    }

    break;

  case 5: // HD(Partition != 0,Type,Signature,Start, Size)
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if ((ParamIdentifierVal == NULL) || (StrCmp(ParamIdentifierVal, L"0") == 0) || 
		((ParamIdentifierStr != NULL) && (StrCmp(ParamIdentifierStr, L"Partition") != 0))) {
      goto InValidText;
    }
    Hd->PartitionNumber = (UINT32) StrToUInt(ParamIdentifierVal);

    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if ((ParamIdentifierVal == NULL) ||
		((ParamIdentifierStr != NULL) && (StrCmp(ParamIdentifierStr, L"Type") != 0))) {
      goto InValidText;
    }
    if ((StrCmp(ParamIdentifierVal, L"1") == 0) || (StrCmp(ParamIdentifierVal, L"MBR") == 0)) {
      Hd->SignatureType = SIGNATURE_TYPE_MBR;
      Hd->MBRType       = 0x01;
    } else if ((StrCmp(ParamIdentifierVal, L"2") == 0) || (StrCmp(ParamIdentifierVal, L"GPT") == 0)) {
      Hd->SignatureType = SIGNATURE_TYPE_GUID;
      Hd->MBRType       = 0x02;
    } else {
      goto InValidText;
    }

    Status = GetNextRequiredParam(&TextDeviceNode, L"Signature", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      StrToGuid (ParamIdentifierVal, &SignatureGuid);
      CopyMem (Hd->Signature, &SignatureGuid, sizeof (EFI_GUID));
    } else {
      goto InValidText;
    }
    Status = GetNextRequiredParam(&TextDeviceNode, L"Start", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      StrToUInt64 (ParamIdentifierVal, &Hd->PartitionStart);
    } else {
      goto InValidText;
    }
    Status = GetNextRequiredParam(&TextDeviceNode, L"Size", &ParamIdentifierStr, &ParamIdentifierVal);
    if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
      StrToUInt64 (ParamIdentifierVal, &Hd->PartitionSize);
    } else {
      goto InValidText;
    }

    break;

  default:
  	goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Hd;
InValidText:
  FreePool(Hd);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildCDROMDeviceNode (
  IN CHAR16                      *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  UINT32                         TotalParamNum;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  CDROM_DEVICE_PATH              *CDROM;

  CDROM = (CDROM_DEVICE_PATH *) CreateDeviceNode (0x4, 0x2, sizeof (CDROM_DEVICE_PATH));
  if (CDROM == NULL) {
    return NULL;
  }

  TotalParamNum = GetParamTotalNum(TextDeviceNode);
  switch (TotalParamNum) {
  case 3: // CDROM(Entry,Start,Size)
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if ((ParamIdentifierStr != NULL) && (StrCmp(L"Entry", ParamIdentifierStr) != 0)) {
      goto InValidText;
    } else {
      CDROM->BootEntry = (UINT32) StrToUInt (ParamIdentifierVal);
    }
    break;

  case 2: // CDROM(Start,Size)
    CDROM->BootEntry = 0;
    break;

  default:
    goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Start", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64 (ParamIdentifierVal, &CDROM->PartitionStart);
  } else {
    goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Size", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64 (ParamIdentifierVal, &CDROM->PartitionSize);
  } else {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) CDROM;
InValidText:
  FreePool(CDROM);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildMediaDeviceNode (
  IN CHAR16                   *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  MEDIA_PROTOCOL_DEVICE_PATH     *Media;

  Media = (MEDIA_PROTOCOL_DEVICE_PATH *) CreateDeviceNode (0x4, 0x5, sizeof (MEDIA_PROTOCOL_DEVICE_PATH));

  Status = GetNextRequiredParam(&TextDeviceNode, L"Guid", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToGuid (ParamIdentifierVal, &Media->Protocol);
  } else {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Media;
InValidText:
  FreePool(Media);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildBBSDeviceNode (
  IN CHAR16                      *TextDeviceNode
  )
{
  EFI_STATUS                     Status;
  CHAR16                         *ParamIdentifierStr;
  CHAR16                         *ParamIdentifierVal;
  UINT32                         OptionalParamIndex;
  BBS_BBS_DEVICE_PATH            *Bbs;
  CHAR16                         *TypeStr;
  CHAR16                         *IdStr;
  CHAR16                         *FlagsStr;

  Status = GetNextRequiredParam(&TextDeviceNode, L"Type", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    TypeStr = ParamIdentifierVal;
  } else {
    goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"Id", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    IdStr = ParamIdentifierVal;
  } else {
    goto InValidText;
  }

  FlagsStr = L"0";

  for (OptionalParamIndex = 0;OptionalParamIndex < 1; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierStr != NULL) {
      if (CheckParamIdentiferValid (ParamIdentifierStr, L"Flags", OptionalParamIndex, 0)) {
        OptionalParamIndex = 0;
        FlagsStr = ParamIdentifierVal;
      } else {
        goto InValidText;
      }
    } else if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // Flags
        FlagsStr = ParamIdentifierVal;
        break;

      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }
  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  Bbs = (BBS_BBS_DEVICE_PATH *) CreateDeviceNode (0x5, 0x1, sizeof (BBS_BBS_DEVICE_PATH) + (UINT16) (EfiStrLen (IdStr)));
  if (Bbs == NULL) {
    return NULL;
  }

  if (StrCmp (TypeStr, L"Floppy") == 0) {
    Bbs->DeviceType = BBS_TYPE_FLOPPY;
  } else if (StrCmp (TypeStr, L"HD") == 0) {
    Bbs->DeviceType = BBS_TYPE_HARDDRIVE;
  } else if (StrCmp (TypeStr, L"CDROM") == 0) {
    Bbs->DeviceType = BBS_TYPE_CDROM;
  } else if (StrCmp (TypeStr, L"PCMCIA") == 0) {
    Bbs->DeviceType = BBS_TYPE_PCMCIA;
  } else if (StrCmp (TypeStr, L"USB") == 0) {
    Bbs->DeviceType = BBS_TYPE_USB;
  } else if (StrCmp (TypeStr, L"Network") == 0) {
    Bbs->DeviceType = BBS_TYPE_EMBEDDED_NETWORK;
  } else {
    Bbs->DeviceType = BBS_TYPE_UNKNOWN;
  }
  StrToAscii (IdStr, &Bbs->String[0]);
  Bbs->StatusFlag = (UINT16) StrToUInt (FlagsStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Bbs;
InValidText:
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildTextFileDeviceNode (
  IN CHAR16                       *TextDeviceNode
  )
{
  FILEPATH_DEVICE_PATH            *File;

  File = (FILEPATH_DEVICE_PATH *) CreateDeviceNode (0x4, 0x4, sizeof (FILEPATH_DEVICE_PATH) + (UINT16) (EfiStrLen (TextDeviceNode) * 2));
  EfiStrCpy (File->PathName, TextDeviceNode);

  return (EFI_DEVICE_PATH_PROTOCOL *) File;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildMediaRelativeOffsetRangeDeviceNode (
  IN CHAR16                       *TextDeviceNode
  )
{
  EFI_STATUS               Status;
  CHAR16                   *ParamIdentifierStr;
  CHAR16                   *ParamIdentifierVal;
  CHAR16                   *StartingOffsetStr;
  CHAR16                   *EndingOffsetStr;
  MEDIA_OFFSET_DEVICE_PATH *Offset;

  Status = GetNextRequiredParam(&TextDeviceNode, L"StartingOffset", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StartingOffsetStr = ParamIdentifierVal;
  } else {
    goto InValidText;
  }

  Status = GetNextRequiredParam(&TextDeviceNode, L"EndingOffset", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    EndingOffsetStr = ParamIdentifierVal;
  } else {
    goto InValidText;
  }

  Offset            = (MEDIA_OFFSET_DEVICE_PATH *) CreateDeviceNode (
                                                     MEDIA_DEVICE_PATH,
                                                     MEDIA_RELATIVE_OFFSET_RANGE_DP,
                                                     sizeof (MEDIA_OFFSET_DEVICE_PATH)
                                                     );

  Offset->Reserved = 0;
  StrToUInt64 (StartingOffsetStr, &Offset->StartingOffset);
  StrToUInt64 (EndingOffsetStr, &Offset->EndingOffset);

  return (EFI_DEVICE_PATH_PROTOCOL *) Offset;

InValidText:
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildSASDeviceNode (
  IN CHAR16    *TextDeviceNode
  )
{
  EFI_STATUS         Status;
  CHAR16             *ParamIdentifierStr;
  CHAR16             *ParamIdentifierVal;
  UINT32             OptionalParamIndex;
  SAS_DEVICE_PATH    *SAS;
  UINT16             DriveBay;

  SAS   = (SAS_DEVICE_PATH *) CreateDeviceNode (0x3, 0xa, sizeof (SAS_DEVICE_PATH));
  if (SAS == NULL) {
    return NULL;
  }

  SAS->Guid     = mEfiDevicePathMessagingSASGuid;
  SAS->DeviceTopology = 0;

  Status = GetNextRequiredParam(&TextDeviceNode, L"Address", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt64 (ParamIdentifierVal, &SAS->SasAddress);
  } else {
  	goto InValidText;
  }

  for (OptionalParamIndex = 0; OptionalParamIndex < 4; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // LUN
        StrToUInt64 (ParamIdentifierVal, &SAS->Lun);
        break;

      case 1:  // RTP
        Status = StrToUInt16 (ParamIdentifierVal, &SAS->RelativeTargetPort);
        if (EFI_ERROR (Status)) {
          goto InValidText;
        }
        break;

      case 2:
        if (StrCmp (ParamIdentifierVal, L"NoTopology") == 0) {
          SAS->DeviceTopology = 0x0000;
        } else if(StrCmp (ParamIdentifierVal, L"SAS") == 0) {
          Status = GetNextRequiredParam(&TextDeviceNode, L"Location", &ParamIdentifierStr, &ParamIdentifierVal);
          if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
            if ((StrCmp (ParamIdentifierVal, L"Internal") == 0) || (StrCmp (ParamIdentifierVal, L"0") == 0)) {
              SAS->DeviceTopology |= 0x0000;
            } else if ((StrCmp (ParamIdentifierVal, L"External") == 0) || (StrCmp (ParamIdentifierVal, L"1") == 0)) {
              SAS->DeviceTopology |= 0x0020;
            } else {
              goto InValidText;
            }
          } else {
            goto InValidText;
          }

          Status = GetNextRequiredParam(&TextDeviceNode, L"Connect", &ParamIdentifierStr, &ParamIdentifierVal);
          if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
            if ((StrCmp (ParamIdentifierVal, L"Direct") == 0) || (StrCmp (ParamIdentifierVal, L"0") == 0)) {
              SAS->DeviceTopology |= 0x0000;
            } else if ((StrCmp (ParamIdentifierVal, L"Expanded") == 0) || (StrCmp (ParamIdentifierVal, L"1") == 0)) {
              SAS->DeviceTopology |= 0x0040;
            } else {
              goto InValidText;
            }
          } else {
            goto InValidText;
          }

          GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
          if (ParamIdentifierVal != NULL) {
            SAS->DeviceTopology |= 0x0002;
            Status = StrToUInt16 (ParamIdentifierVal, &DriveBay);
            if (EFI_ERROR (Status) || ((DriveBay - 1) > 0xFF)) {
              goto InValidText;
            }
            SAS->DeviceTopology |= (DriveBay - 1) << 8;
          } else {
            SAS->DeviceTopology |= 0x0001;
          }

        } else if (StrCmp (ParamIdentifierVal, L"SATA") == 0) {
          Status = GetNextRequiredParam(&TextDeviceNode, L"Location", &ParamIdentifierStr, &ParamIdentifierVal);
          if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
            if ((StrCmp (ParamIdentifierVal, L"Internal") == 0) || (StrCmp (ParamIdentifierVal, L"0") == 0)) {
              SAS->DeviceTopology |= 0x0010;
            } else if ((StrCmp (ParamIdentifierVal, L"External") == 0) || (StrCmp (ParamIdentifierVal, L"1") == 0)) {
              SAS->DeviceTopology |= 0x0030;
            } else {
              goto InValidText;
            }
          } else {
            goto InValidText;
          }

          Status = GetNextRequiredParam(&TextDeviceNode, L"Connect", &ParamIdentifierStr, &ParamIdentifierVal);
          if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
            if ((StrCmp (ParamIdentifierVal, L"Direct") == 0) || (StrCmp (ParamIdentifierVal, L"0") == 0)) {
              SAS->DeviceTopology |= 0x0000;
            } else if ((StrCmp (ParamIdentifierVal, L"Expanded") == 0) || (StrCmp (ParamIdentifierVal, L"1") == 0)) {
              SAS->DeviceTopology |= 0x0040;
            } else {
              goto InValidText;
            }
          } else {
            goto InValidText;
          }

          GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
          if (ParamIdentifierVal != NULL) {
            SAS->DeviceTopology |= 0x0002;
            Status = StrToUInt16 (ParamIdentifierVal, &DriveBay);
            if (EFI_ERROR (Status) || ((DriveBay - 1) > 0xFF)) {
              goto InValidText;
            }
            SAS->DeviceTopology |= (DriveBay - 1) << 8;
          } else {
            SAS->DeviceTopology |= 0x0001;
          }

        } else {
          Status = StrToUInt16(ParamIdentifierVal, &SAS->DeviceTopology);
          if (EFI_ERROR (Status)) {
            goto InValidText;
          } 
        }
        break;
        
      case 3: //Reserved
        Status = StrToUInt16 (ParamIdentifierVal, (UINT16 *)&SAS->Reserved);
        if (EFI_ERROR (Status)) {
          goto InValidText;
        }
        break;
        
      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }

  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) SAS;

InValidText:
  FreePool(SAS);
  return NULL;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
BuildSASExDeviceNode (
  IN CHAR16    *TextDeviceNode
  )
{
  EFI_STATUS           Status;
  CHAR16               *ParamIdentifierStr;
  CHAR16               *ParamIdentifierVal;
  UINT32               OptionalParamIndex;
  SASEX_DEVICE_PATH    *SASEx;
  UINT16               DriveBay;

  SASEx   = (SASEX_DEVICE_PATH *) CreateDeviceNode (0x3, 0x16, sizeof (SASEX_DEVICE_PATH));
  if (SASEx == NULL) {
    return NULL;
  }

  SASEx->DeviceTopology = 0;

  Status = GetNextRequiredParam(&TextDeviceNode, L"Address", &ParamIdentifierStr, &ParamIdentifierVal);
  if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
    StrToUInt8Array (ParamIdentifierVal, SASEx->SasAddress);
  } else {
  	goto InValidText;
  }

  for (OptionalParamIndex = 0; OptionalParamIndex < 3; OptionalParamIndex++) {
    GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
    if (ParamIdentifierVal != NULL) {
      switch(OptionalParamIndex) {
      case 0:  // LUN
        StrToUInt8Array (ParamIdentifierVal, SASEx->Lun);
        break;

      case 1:  // RTP
        Status = StrToUInt16 (ParamIdentifierVal, &SASEx->RelativeTargetPort);
        if (EFI_ERROR (Status)) {
          goto InValidText;
        }
        break;

      case 2:
        if (StrCmp (ParamIdentifierVal, L"NoTopology") == 0) {
          SASEx->DeviceTopology = 0x0000;
        } else if(StrCmp (ParamIdentifierVal, L"SAS") == 0) {
          Status = GetNextRequiredParam(&TextDeviceNode, L"Location", &ParamIdentifierStr, &ParamIdentifierVal);
          if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
            if ((StrCmp (ParamIdentifierVal, L"Internal") == 0) || (StrCmp (ParamIdentifierVal, L"0") == 0)) {
              SASEx->DeviceTopology |= 0x0000;
            } else if ((StrCmp (ParamIdentifierVal, L"External") == 0) || (StrCmp (ParamIdentifierVal, L"1") == 0)) {
              SASEx->DeviceTopology |= 0x0020;
            } else {
              goto InValidText;
            }
          } else {
            goto InValidText;
          }

          Status = GetNextRequiredParam(&TextDeviceNode, L"Connect", &ParamIdentifierStr, &ParamIdentifierVal);
          if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
            if ((StrCmp (ParamIdentifierVal, L"Direct") == 0) || (StrCmp (ParamIdentifierVal, L"0") == 0)) {
              SASEx->DeviceTopology |= 0x0000;
            } else if ((StrCmp (ParamIdentifierVal, L"Expanded") == 0) || (StrCmp (ParamIdentifierVal, L"1") == 0)) {
              SASEx->DeviceTopology |= 0x0040;
            } else {
              goto InValidText;
            }
          } else {
            goto InValidText;
          }

          GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
          if (ParamIdentifierVal != NULL) {
            SASEx->DeviceTopology |= 0x0002;
            Status = StrToUInt16 (ParamIdentifierVal, &DriveBay);
            if (EFI_ERROR (Status) || ((DriveBay - 1) > 0xFF)) {
              goto InValidText;
            }
            SASEx->DeviceTopology |= (DriveBay - 1) << 8;
          } else {
            SASEx->DeviceTopology |= 0x0001;
          }

        } else if (StrCmp (ParamIdentifierVal, L"SATA") == 0) {
          Status = GetNextRequiredParam(&TextDeviceNode, L"Location", &ParamIdentifierStr, &ParamIdentifierVal);
          if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
            if ((StrCmp (ParamIdentifierVal, L"Internal") == 0) || (StrCmp (ParamIdentifierVal, L"0") == 0)) {
              SASEx->DeviceTopology |= 0x0010;
            } else if ((StrCmp (ParamIdentifierVal, L"External") == 0) || (StrCmp (ParamIdentifierVal, L"1") == 0)) {
              SASEx->DeviceTopology |= 0x0030;
            } else {
              goto InValidText;
            }
          } else {
            goto InValidText;
          }

          Status = GetNextRequiredParam(&TextDeviceNode, L"Connect", &ParamIdentifierStr, &ParamIdentifierVal);
          if ((!EFI_ERROR(Status)) && (ParamIdentifierVal != NULL)) {
            if ((StrCmp (ParamIdentifierVal, L"Direct") == 0) || (StrCmp (ParamIdentifierVal, L"0") == 0)) {
              SASEx->DeviceTopology |= 0x0000;
            } else if ((StrCmp (ParamIdentifierVal, L"Expanded") == 0) || (StrCmp (ParamIdentifierVal, L"1") == 0)) {
              SASEx->DeviceTopology |= 0x0040;
            } else {
              goto InValidText;
            }
          } else {
            goto InValidText;
          }

          GetNextOptionalParam(&TextDeviceNode, &ParamIdentifierStr, &ParamIdentifierVal);
          if (ParamIdentifierVal != NULL) {
            SASEx->DeviceTopology |= 0x0002;
            Status = StrToUInt16 (ParamIdentifierVal, &DriveBay);
            if (EFI_ERROR (Status) || ((DriveBay - 1) > 0xFF)) {
              goto InValidText;
            }
            SASEx->DeviceTopology |= (DriveBay - 1) << 8;
          } else {
            SASEx->DeviceTopology |= 0x0001;
          }

        } else {
          Status = StrToUInt16(ParamIdentifierVal, &SASEx->DeviceTopology);
          if (EFI_ERROR (Status)) {
            goto InValidText;
          } 
        }
        break;
        
      default:
        goto InValidText;
      }
    } else {
      break;
    }
  }

  if (TextDeviceNode != NULL) {
    goto InValidText;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) SASEx;

InValidText:
  FreePool(SASEx);
  return NULL;
}

STATIC DEVICE_PATH_FROM_TEXT_TABLE BuildDevPathNodeFuncTable[] = {
  L"PciRoot",
  BuildPciRootDeviceNode,
  L"PcieRoot", 
  BuildPcieRootDeviceNode,
  L"Pci",
  BuildPciDeviceNode,
  L"PcCard",
  BuildPcCardDeviceNode,
  L"MemoryMapped",
  BuildMemoryMappedDeviceNode,
  L"VenHw",
  BuildVenHwDeviceNode,
  L"Ctrl",
  BuildCtrlDeviceNode,
  L"Acpi",
  BuildAcpiDeviceNode,
  L"Floppy",
  BuildFloppyDeviceNode,
  L"Keyboard",
  BuildKeyboardDeviceNode,
  L"Serial",
  BuildSerialDeviceNode,
  L"ParallelPort",
  BuildParallelPortDeviceNode,
  L"AcpiEx",
  BuildAcpiExDeviceNode,
  L"AcpiExp",
  BuildAcpiExpDeviceNode,
  L"AcpiAdr",
  BuildAcpiAdrDeviceNode,
  L"Ata",
  BuildAtaDeviceNode,
  L"Scsi",
  BuildScsiDeviceNode,
  L"Fibre",
  BuildFibreDeviceNode,
  L"I1394",
  Build1394DeviceNode,
  L"USB",
  BuildUsbDeviceNode,
  L"I2O",
  BuildI2ODeviceNode,
  L"Vlan",
  BuildVlanDeviceNode,
  L"FibreEx",
  BuildFibreExDeviceNode,
  L"Infiniband",
  BuildInfinibandDeviceNode,
  L"VenMsg",
  BuildVenMsgDeviceNode,
  L"VenMedia",
  BuildVenMEDIADeviceNode,
  L"VenPcAnsi",
  BuildVenPcAnsiDeviceNode,
  L"VenVt100",
  BuildVenVt100DeviceNode,
  L"VenVt100Plus",
  BuildVenVt100PlusDeviceNode,
  L"VenUtf8",
  BuildVenUtf8DeviceNode,
  L"UartFlowCtrl",
  BuildUartFlowCtrlDeviceNode,
  L"DebugPort",
  BuildDebugPortDeviceNode,
  L"MAC",
  BuildMACDeviceNode,
  L"IPv4",
  BuildIPv4DeviceNode,
  L"IPv6",
  BuildIPv6DeviceNode,
  L"SAS",
  BuildSASDeviceNode,
  L"SasEx",
  BuildSASExDeviceNode,
  L"Uart",
  BuildUartDeviceNode,
  L"UsbClass",
  BuildUsbClassDeviceNode,
  L"UsbAudio",
  BuildUsbAudioDeviceNode,
  L"UsbCDCControl",
  BuildUsbCDCControlDeviceNode,
  L"UsbHID",
  BuildUsbHIDControlDeviceNode,
  L"UsbImage",
  BuildUsbImageDeviceNode,
  L"UsbPrinter",
  BuildUsbPrinterDeviceNode,
  L"UsbMassStorage",
  BuildUsbMassStorageDeviceNode,
  L"UsbHub",
  BuildUsbHubDeviceNode,
  L"UsbCDCData",
  BuildUsbCDCDataDeviceNode,
  L"UsbSmartCard",
  BuildUsbSmartCardDeviceNode,
  L"UsbVideo",
  BuildUsbVideoDeviceNode,
  L"UsbDiagnostic",
  BuildUsbDiagnosticDeviceNode,
  L"UsbWireless",
  BuildUsbWirelessDeviceNode,
  L"UsbDeviceFirmwareUpdate",
  BuildUsbDeviceFirmwareUpdateDeviceNode,
  L"UsbIrdaBridge",
  BuildUsbIrdaBridgeDeviceNode,
  L"UsbTestAndMeasurement",
  BuildUsbTestAndMeasurementDeviceNode,
  L"Unit",
  BuildUnitDeviceNode,
  L"iSCSI",
  BuildiSCSIDeviceNode,
  L"HD",
  BuildHDDeviceNode,
  L"CDROM",
  BuildCDROMDeviceNode,
  L"Media",
  BuildMediaDeviceNode,
  L"BBS",
  BuildBBSDeviceNode, 
  L"TextFile",
  BuildTextFileDeviceNode,
  L"Offset",
  BuildMediaRelativeOffsetRangeDeviceNode,
  NULL, NULL
};

STATIC
EFI_STATUS
GetDevicePathTypeAndParam (
  IN  CHAR16                   *DevicePathStr,
  OUT CHAR16                   **DevicePathTypeStr,
  OUT CHAR16                   **DevicePathParamStr
  )
{
  CHAR16                   *ParamStart;
  CHAR16                   *ParamEnd;

  *DevicePathTypeStr  = NULL;
  *DevicePathParamStr = NULL;

  if (DevicePathStr == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ParamStart = StrChr(DevicePathStr, L'(');
  ParamEnd   = StrChr(DevicePathStr, L')');

  if ((ParamStart == NULL) && (ParamEnd == NULL)) {
    *DevicePathTypeStr  = L"TextFile";
    *DevicePathParamStr = DevicePathStr;
    return EFI_SUCCESS;
  }

  if (((ParamStart == NULL) && (ParamEnd != NULL)) || 
  	  ((ParamStart != NULL) && (ParamEnd == NULL))) {
    *DevicePathTypeStr  = NULL;
    *DevicePathParamStr = NULL;
    return EFI_INVALID_PARAMETER;
  }

  *ParamStart = L'\0';
  *ParamEnd   = L'\0';

  *DevicePathTypeStr  = DevicePathStr;
  *DevicePathParamStr = ParamStart + 1;
  return EFI_SUCCESS;
}

STATIC
CHAR16 *
GetNextDeviceNodeStr (
  IN OUT CHAR16                 **DevicePath
  )
{
  CHAR16                        *DeviceNode;

  if ((DevicePath == NULL) || (*DevicePath == NULL) || (**DevicePath == L'\0')) {
    return NULL;
  }

  //
  // Skip the leading '/', '\'
  //
  for (; (**DevicePath != L'\0') && ((**DevicePath == L'\\') || (**DevicePath == L'/')); (*DevicePath)++) {
    ;
  }

  if (**DevicePath == L'\0') {
    return NULL;
  }

  DeviceNode = *DevicePath;
  while(**DevicePath != L'\0') {
    if ((**DevicePath == L'\\') || (**DevicePath == L'/')) {
      **DevicePath = L'\0';
      (*DevicePath)++;
	  break;
    }
    (*DevicePath)++;
  }

  return DeviceNode;
}

EFI_DEVICE_PATH_PROTOCOL *
SctConvertTextToDeviceNode (
  IN CHAR16                *TextDevicePath
  )
{
  EFI_STATUS               Status;
  EFI_DEVICE_PATH_PROTOCOL *(*BuildDevPathNodeFunc) (CHAR16 *);
  UINTN                    Index;
  CHAR16                   *DeviceNodeStr;
  CHAR16                   *DeviceNodeTypeStr;
  CHAR16                   *DeviceNodeParamStr;
  EFI_DEVICE_PATH_PROTOCOL *DeviceNode;

  if ((TextDevicePath == NULL) || (IS_NULL (*TextDevicePath))) {
    return NULL;
  }

  DeviceNode           = NULL;
  DeviceNodeStr        = StrDuplicate (TextDevicePath);
  BuildDevPathNodeFunc = NULL;

  Status = GetDevicePathTypeAndParam(DeviceNodeStr, &DeviceNodeTypeStr, &DeviceNodeParamStr);
  if (EFI_ERROR(Status)) {
    goto ConvertError;
  }

  if (DeviceNodeTypeStr != NULL) {
    for (BuildDevPathNodeFunc = NULL, Index = 0; BuildDevPathNodeFuncTable[Index].DevicePathNodeText != NULL; Index++) {
      if (StrCmp(BuildDevPathNodeFuncTable[Index].DevicePathNodeText, DeviceNodeTypeStr) == 0) {
        BuildDevPathNodeFunc = BuildDevPathNodeFuncTable[Index].Function;
        break;
      }
    }
  }

  if (BuildDevPathNodeFunc != NULL) {
    DeviceNode = BuildDevPathNodeFunc(DeviceNodeParamStr);
  }

  return DeviceNode;
ConvertError:
  FreePool(DeviceNodeStr);
  return NULL;
}

EFI_DEVICE_PATH_PROTOCOL *
SctConvertTextToDevicePath (
  IN CHAR16                *TextDevicePath
  )
{
  EFI_DEVICE_PATH_PROTOCOL *DeviceNode;
  EFI_DEVICE_PATH_PROTOCOL *DevicePath;
  CHAR16                   *DevicePathStr;
  CHAR16                   *DevicePathTmpStr;
  CHAR16                   *DeviceNodeStr;
  EFI_DEVICE_PATH_PROTOCOL *NewDevicePath;

  if ((TextDevicePath == NULL) || (*TextDevicePath == L'\0')) {
    return NULL;
  }

  DevicePath       = CreateEndDeviceNode();
  DevicePathStr    = StrDuplicate (TextDevicePath);
  DevicePathTmpStr = DevicePathStr;

  while ((DeviceNodeStr = GetNextDeviceNodeStr (&DevicePathTmpStr)) != NULL) {
    DeviceNode    = SctConvertTextToDeviceNode(DeviceNodeStr);
    if (DeviceNode == NULL) {
      goto ConvertError;
    }

    NewDevicePath = AppendDevicePathNode (DevicePath, DeviceNode);
    FreePool (DevicePath);
    FreePool (DeviceNode);
    DevicePath    = NewDevicePath;
  }

  FreePool (DevicePathStr);

  return DevicePath;
ConvertError:
  FreePool(DevicePathStr);
  return NULL;
}

