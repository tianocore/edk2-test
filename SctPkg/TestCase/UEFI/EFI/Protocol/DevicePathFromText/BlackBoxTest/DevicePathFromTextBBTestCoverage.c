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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DevicePathFromTextBBTestCoverage.c

Abstract:

  Interface Function Test Cases of Device Path From Text Protocol

--*/

#include "DevicePathFromTextBBTestMain.h"

#include EFI_PROTOCOL_DEFINITION (DebugPort)

#include EFI_GUID_DEFINITION (PcAnsi)

#define MaxDevicePathStrLen 200

extern EFI_GUID gBlackBoxEfiDevicePathUtilitiesProtocolGuid;
extern EFI_GUID gBlackBoxEfiDevicePathToTextProtocolGuid;

#define IS_HYPHEN(a)         ((a) == L'-')
#define IS_NULL(a)           ((a) == L'\0')

STATIC
CHAR16 *
TrimHexStr (
  IN CHAR16  *Str
  )
{
  //
  // skip preceeding white space
  //
  while (*Str && *Str == ' ') {
    Str += 1;
  }
  //
  // skip preceeding zeros
  //
  while (*Str && *Str == '0') {
    Str += 1;
  }
  //
  // skip preceeding character 'x'
  //
  if (*Str && (*Str == 'x' || *Str == 'X')) {
    Str += 1;
  }

  return Str;
}

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

  SctStrTrim (Str, L' ');

  StrLength = SctStrLen (Str);
  //
  // Check hex prefix '0x'
  //
  if (StrLength >= 2 && *Str == '0' && (*(Str + 1) == 'x' || *(Str + 1) == 'X')) {
    Str       += 2;
    StrLength -= 2;
  }

  for(Index = 0; Index < StrLength; Index++, Str++) {

    SctIsHexDigit (&Digit, *Str);

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
VOID
Xtoi64 (
  IN CHAR16  *Str,
  IN UINT64  *Data
  )
{
  UINTN  Length;

  *Data = 0;
  Length = sizeof (UINT64);
  SctHexStringToBuf ((UINT8 *) Data, &Length, TrimHexStr (Str), NULL);
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
VOID
EUI64StrToUInt64 (
  IN  CHAR16 *EUIStr, 
  OUT UINT64 *EUIdValue
  )
{
  CHAR16  *EUIStrPart[8];
  UINT64  EUId[8];
  UINT8   Index;
  UINT64  Sum;

  for (Index = 0; Index < 8; Index++) {
    EUIStrPart[Index] = SctSplitStr (&EUIStr, L'-');
	Xtoi64(EUIStrPart[Index], &EUId[Index]);
  }

  Sum = EUId[0];
  for (Index = 1; Index < 8; Index++) {
    Sum = SctLShiftU64(Sum, 8);
	Sum = Sum + EUId[Index];
  }
  *EUIdValue = Sum;
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
 
  DevicePath = SctAllocateZeroPool (NodeLength);
  if (DevicePath != NULL) {
     DevicePath->Type    = NodeType;
     DevicePath->SubType = NodeSubType;
     SctSetDevicePathNodeLength (DevicePath, NodeLength);
  }

  return DevicePath;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
ConvertFromTextVendor (
  IN CHAR16 *TextDeviceNode,
  IN UINT8  Type,
  IN UINT8  SubType
  )
{
  CHAR16              *GuidStr;
  CHAR16              *DataStr;
  UINTN               Length;
  VENDOR_DEVICE_PATH  *Vendor;

  GuidStr = SctSplitStr (&TextDeviceNode, L',');
  DataStr = SctSplitStr (&TextDeviceNode, L',');
  Length = SctStrLen (DataStr);
  //
  // Two hex characters make up 1 buffer byte
  //
  Length = (Length + 1) / 2;

  Vendor = (VENDOR_DEVICE_PATH *) CreateDeviceNode (
                                    Type,
                                    SubType,
                                    sizeof (VENDOR_DEVICE_PATH) + (UINT16) Length
                                    );

  StrToGuid (GuidStr, &Vendor->Guid);
  StrToBuf (((UINT8 *) Vendor) + sizeof (VENDOR_DEVICE_PATH), Length, DataStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Vendor;
}

typedef struct {
  BOOLEAN ClassExist;
  UINT8   Class;
  BOOLEAN SubClassExist;
  UINT8   SubClass;
} USB_CLASS_TEXT;

#define UsbClassNodeType     3
#define UsbClassNodeSubType  15

STATIC
EFI_DEVICE_PATH_PROTOCOL *
ConvertFromTextUsbClass (
  IN CHAR16         *TextDeviceNode,
  IN USB_CLASS_TEXT *UsbClassText
  )
{
  CHAR16                *VIDStr;
  CHAR16                *PIDStr;
  CHAR16                *ClassStr;
  CHAR16                *SubClassStr;
  CHAR16                *ProtocolStr;
  USB_CLASS_DEVICE_PATH *UsbClass;

  UsbClass    = (USB_CLASS_DEVICE_PATH *) CreateDeviceNode (
                                            UsbClassNodeType,
                                            UsbClassNodeSubType,
                                            sizeof (USB_CLASS_DEVICE_PATH)
                                            );

  VIDStr      = SctSplitStr (&TextDeviceNode, L',');
  PIDStr      = SctSplitStr (&TextDeviceNode, L',');
  if (UsbClassText->ClassExist) {
    ClassStr = SctSplitStr (&TextDeviceNode, L',');
    UsbClass->DeviceClass = (UINT8) SctStrToUInt (ClassStr);
  } else {
    UsbClass->DeviceClass = UsbClassText->Class;
  }
  if (UsbClassText->SubClassExist) {
    SubClassStr = SctSplitStr (&TextDeviceNode, L',');
    UsbClass->DeviceSubClass = (UINT8) SctStrToUInt (SubClassStr);
  } else {
    UsbClass->DeviceSubClass = UsbClassText->SubClass;
  }  

  ProtocolStr = SctSplitStr (&TextDeviceNode, L',');

  UsbClass->VendorId        = (UINT16) SctStrToUInt (VIDStr);
  UsbClass->ProductId       = (UINT16) SctStrToUInt (PIDStr);
  UsbClass->DeviceProtocol  = (UINT8) SctStrToUInt (ProtocolStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) UsbClass;
}

#define PcCardNodeType       1
#define PcCardNodeSubType    2

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreatePcCardDeviceNode (
  IN CHAR16                              *TextDeviceNode
  )
{
  CHAR16              *FunctionNumberStr;
  PCCARD_DEVICE_PATH  *Pccard;

  FunctionNumberStr = SctSplitStr (&TextDeviceNode, L',');
  Pccard            = (PCCARD_DEVICE_PATH *) CreateDeviceNode (
  	                                           PcCardNodeType, 
  	                                           PcCardNodeSubType, 
  	                                           sizeof(PCCARD_DEVICE_PATH)
                                               );

  Pccard->FunctionNumber  = (UINT8) SctStrToUInt (FunctionNumberStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Pccard;
}

#define MemMapNodeType       1
#define MemMapNodeSubType    3

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateMemMapDeviceNode (
  IN CHAR16                              *TextDeviceNode
  )
{
  CHAR16              *MemoryTypeStr;
  CHAR16              *StartingAddressStr;
  CHAR16              *EndingAddressStr;
  MEMMAP_DEVICE_PATH  *MemMap;

  MemoryTypeStr      = SctSplitStr (&TextDeviceNode, L',');
  StartingAddressStr = SctSplitStr (&TextDeviceNode, L',');
  EndingAddressStr   = SctSplitStr (&TextDeviceNode, L',');
  MemMap             = (MEMMAP_DEVICE_PATH *) CreateDeviceNode (
  	                                            MemMapNodeType, 
  	                                            MemMapNodeSubType, 
                                                sizeof (MEMMAP_DEVICE_PATH)
                                                );
  MemMap->MemoryType = (UINT32) SctStrToUInt (MemoryTypeStr);
  SctStrToUInt64 (StartingAddressStr, &MemMap->StartingAddress);
  SctStrToUInt64 (EndingAddressStr, &MemMap->EndingAddress);

  return (EFI_DEVICE_PATH_PROTOCOL *) MemMap;
}

#define VenHwNodeType        1
#define VenHwNodeSubType     4

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateVenHwDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  return ConvertFromTextVendor (
           TextDeviceNode,
           VenHwNodeType,
           VenHwNodeSubType
           );
}

#define CtrlNodeType         1
#define CtrlNodeSubType      5

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateCtrlDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                  *ControllerStr;
  CONTROLLER_DEVICE_PATH  *Controller;

  ControllerStr = SctSplitStr (&TextDeviceNode, L',');
  Controller    = (CONTROLLER_DEVICE_PATH *) CreateDeviceNode (
                                               CtrlNodeType,
                                               CtrlNodeSubType,
                                               sizeof (CONTROLLER_DEVICE_PATH)
                                               );
  Controller->ControllerNumber  = (UINT32) SctStrToUInt (ControllerStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Controller;
}

#define AcpiNodeType     2
#define AcpiNodeSubType  1

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreatePciRootDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                  *PciRootStr;
  ACPI_HID_DEVICE_PATH    *PciRoot;

  PciRootStr = SctSplitStr (&TextDeviceNode, L',');
  PciRoot    = (ACPI_HID_DEVICE_PATH *) CreateDeviceNode (
                                          AcpiNodeType,
                                          AcpiNodeSubType,
                                          sizeof (ACPI_HID_DEVICE_PATH)
                                          );
  PciRoot->HID  = 0x0A0341d0;
  PciRoot->UID  = (UINT32) SctStrToUInt (PciRootStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) PciRoot;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreatePcieRootDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                  *PcieRootStr;
  ACPI_HID_DEVICE_PATH    *PcieRoot;

  PcieRootStr = SctSplitStr (&TextDeviceNode, L',');
  PcieRoot    = (ACPI_HID_DEVICE_PATH *) CreateDeviceNode (
                                           AcpiNodeType,
                                           AcpiNodeSubType,
                                           sizeof (ACPI_HID_DEVICE_PATH)
                                           );
  PcieRoot->HID  = 0x0A0841d0;
  PcieRoot->UID  = (UINT32) SctStrToUInt (PcieRootStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) PcieRoot;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateFloppyDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                  *FloppyStr;
  ACPI_HID_DEVICE_PATH    *Floppy;

  FloppyStr = SctSplitStr (&TextDeviceNode, L',');
  Floppy    = (ACPI_HID_DEVICE_PATH *) CreateDeviceNode (
                                         AcpiNodeType,
                                         AcpiNodeSubType,
                                         sizeof (ACPI_HID_DEVICE_PATH)
                                         );
  Floppy->HID  = 0x060441d0;
  Floppy->UID  = (UINT32) SctStrToUInt (FloppyStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Floppy;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateKeyboardDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                  *KeyboardStr;
  ACPI_HID_DEVICE_PATH    *Keyboard;

  KeyboardStr = SctSplitStr (&TextDeviceNode, L',');
  Keyboard    = (ACPI_HID_DEVICE_PATH *) CreateDeviceNode (
                                           AcpiNodeType,
                                           AcpiNodeSubType,
                                           sizeof (ACPI_HID_DEVICE_PATH)
                                           );
  Keyboard->HID  = 0x030141d0;
  Keyboard->UID  = (UINT32) SctStrToUInt (KeyboardStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Keyboard;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateSerialDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                  *SerialStr;
  ACPI_HID_DEVICE_PATH    *Serial;

  SerialStr = SctSplitStr (&TextDeviceNode, L',');
  Serial    = (ACPI_HID_DEVICE_PATH *) CreateDeviceNode (
                                         AcpiNodeType,
                                         AcpiNodeSubType,
                                         sizeof (ACPI_HID_DEVICE_PATH)
                                         );
  Serial->HID  = 0x050141d0;
  Serial->UID  = (UINT32) SctStrToUInt (SerialStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Serial;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateParallelPortDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                  *ParallelPortStr;
  ACPI_HID_DEVICE_PATH    *ParallelPort;

  ParallelPortStr = SctSplitStr (&TextDeviceNode, L',');
  ParallelPort    = (ACPI_HID_DEVICE_PATH *) CreateDeviceNode (
                                               AcpiNodeType,
                                               AcpiNodeSubType,
                                               sizeof (ACPI_HID_DEVICE_PATH)
                                               );
  ParallelPort->HID  = 0x040141d0;
  ParallelPort->UID  = (UINT32) SctStrToUInt (ParallelPortStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) ParallelPort;
}

#define AcpiExtNodeType     2
#define AcpiExtNodeSubType  2

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateAcpiExtDeviceNode (
  IN CHAR16 *HIDStr,
  IN CHAR16 *CIDStr,
  IN CHAR16 *UIDStr,
  IN CHAR16 *HIDSTRStr,
  IN CHAR16 *CIDSTRStr,
  IN CHAR16 *UIDSTRStr
  )
{
  CHAR8                                   *AsciiStr;
  UINT16                                  Length;
  ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR  *AcpiExt;


  Length    = sizeof (ACPI_EXTENDED_HID_DEVICE_PATH) + 
                  (UINT16) SctStrLen (HIDSTRStr) + 1 +
                  (UINT16) SctStrLen (UIDSTRStr) + 1 +
                  (UINT16) SctStrLen (CIDSTRStr) + 1;
  AcpiExt = (ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *) CreateDeviceNode (
                                                         AcpiExtNodeType,
                                                         AcpiExtNodeSubType,
                                                         Length
                                                         );

  if ((HIDStr[0] == L'P') && (HIDStr[1] == L'N') && (HIDStr[2] == L'P')) {
    HIDStr += 3;
    AcpiExt->HID = EISA_PNP_ID (SctXtoi (HIDStr));
  } else {
    AcpiExt->HID = (UINT32) SctXtoi (HIDStr);
  }

  if ((CIDStr[0] == L'P') && (CIDStr[1] == L'N') && (CIDStr[2] == L'P')) {
    CIDStr += 3;
    AcpiExt->CID = EISA_PNP_ID (SctXtoi (CIDStr));
  } else {
    AcpiExt->CID = (UINT32) SctXtoi (CIDStr);
  }

  AcpiExt->UID  = (UINT32) SctXtoi (UIDStr);

  AsciiStr = AcpiExt->HidUidCidStr;
  SctStrToAscii (HIDSTRStr, AsciiStr);
  SctStrToAscii (UIDSTRStr, AsciiStr + (UINT16) SctStrLen (HIDSTRStr) + 1);
  SctStrToAscii (CIDSTRStr, AsciiStr + (UINT16) SctStrLen (HIDSTRStr) + 1 + (UINT16) SctStrLen (UIDSTRStr) + 1);
  
  return (EFI_DEVICE_PATH_PROTOCOL *) AcpiExt;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateAcpiExpDeviceNode (
  IN CHAR16 *HIDStr,
  IN CHAR16 *CIDStr,
  IN CHAR16 *UIDSTRStr
  )
{
  CHAR8                                   *AsciiStr;
  UINT16                                  Length;
  ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR  *AcpiExt;

  Length    = sizeof (ACPI_EXTENDED_HID_DEVICE_PATH) + (UINT16) SctStrLen (UIDSTRStr) + 3;
  AcpiExt   = (ACPI_EXTENDED_HID_DEVICE_PATH_WITH_STR *) CreateDeviceNode (
                                                           AcpiExtNodeType,
                                                           AcpiExtNodeSubType,
                                                           Length
                                                           );

  if ((HIDStr[0] == L'P') && (HIDStr[1] == L'N') && (HIDStr[2] == L'P')) {
    HIDStr += 3;
    AcpiExt->HID = EISA_PNP_ID (SctXtoi (HIDStr));
  } else {
    AcpiExt->HID = (UINT32) SctXtoi (HIDStr);
  }

  if ((CIDStr[0] == L'P') && (CIDStr[1] == L'N') && (CIDStr[2] == L'P')) {
    CIDStr += 3;
    AcpiExt->CID = EISA_PNP_ID (SctXtoi (CIDStr));
  } else {
    AcpiExt->CID = (UINT32) SctXtoi (CIDStr);
  }

  AcpiExt->UID = 0;

  AsciiStr = AcpiExt->HidUidCidStr;
  //
  // HID string is NULL
  //
  *AsciiStr = 0;
  //
  // Convert UID string
  //
  AsciiStr++;
  SctStrToAscii (UIDSTRStr, AsciiStr);
  //
  // CID string is NULL
  //
  AsciiStr += SctStrLen (UIDSTRStr) + 1;
  *AsciiStr = 0;

  return (EFI_DEVICE_PATH_PROTOCOL *) AcpiExt;
}


#define AcpiAdrNodeType    2
#define AcpiAdrNodeSubtype 3

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateAcpiAdrDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                        *DisplayDeviceStr;
  ACPI_ADR_DEVICE_PATH          *AcpiAdr;

  DisplayDeviceStr = SctSplitStr (&TextDeviceNode, L',');
  AcpiAdr          = (ACPI_ADR_DEVICE_PATH *) CreateDeviceNode (
                                                AcpiAdrNodeType,
                                                AcpiAdrNodeSubtype,
                                                sizeof (ACPI_ADR_DEVICE_PATH)
                                                );
  AcpiAdr->ADR = (UINT32) SctStrToUInt (DisplayDeviceStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) AcpiAdr;
}


#define ScsiNodeType    3
#define ScsiNodeSubtype 2

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateScsiDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16            *PunStr;
  CHAR16            *LunStr;
  SCSI_DEVICE_PATH  *Scsi;

  PunStr = SctSplitStr (&TextDeviceNode, L',');
  LunStr = SctSplitStr (&TextDeviceNode, L',');
  Scsi   = (SCSI_DEVICE_PATH *) CreateDeviceNode (
                                   ScsiNodeType,
                                   ScsiNodeSubtype,
                                   sizeof (SCSI_DEVICE_PATH)
                                   );

  Scsi->Pun = (UINT16) SctStrToUInt (PunStr);
  Scsi->Lun = (UINT16) SctStrToUInt (LunStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Scsi;
}

#define FibreNodeType    3
#define FibreNodeSubType 3

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateFibreDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                    *WWNStr;
  CHAR16                    *LunStr;
  FIBRECHANNEL_DEVICE_PATH  *Fibre;

  WWNStr = SctSplitStr (&TextDeviceNode, L',');
  LunStr = SctSplitStr (&TextDeviceNode, L',');
  Fibre  = (FIBRECHANNEL_DEVICE_PATH *) CreateDeviceNode (
                                          FibreNodeType,
                                          FibreNodeSubType,
                                          sizeof (FIBRECHANNEL_DEVICE_PATH)
                                          );
  Fibre->Reserved = 0;
  SctStrToUInt64 (WWNStr, &Fibre->WWN);
  SctStrToUInt64 (LunStr, &Fibre->Lun);

  return (EFI_DEVICE_PATH_PROTOCOL *) Fibre;
}

#define I1394NodeType    3
#define I1394NodeSubType 4

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateI1394DeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16            *GuidStr;
  F1394_DEVICE_PATH *F1394;

  GuidStr = SctSplitStr (&TextDeviceNode, L',');
  F1394  = (F1394_DEVICE_PATH *) CreateDeviceNode (
                                   I1394NodeType,
                                   I1394NodeSubType,
                                   sizeof (F1394_DEVICE_PATH)
                                   );
  F1394->Reserved = 0;
  Xtoi64(GuidStr, &F1394->Guid);

  return (EFI_DEVICE_PATH_PROTOCOL *) F1394;
}

#define UsbNodeType    3
#define UsbNodeSubType 5

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateUsbDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16          *PortStr;
  CHAR16          *InterfaceStr;
  USB_DEVICE_PATH *Usb;

  PortStr               = SctSplitStr (&TextDeviceNode, L',');
  InterfaceStr          = SctSplitStr (&TextDeviceNode, L',');
  Usb = (USB_DEVICE_PATH *) CreateDeviceNode (
                              UsbNodeType,
                              UsbNodeSubType,
                              sizeof (USB_DEVICE_PATH)
                              );

  Usb->ParentPortNumber = (UINT8) SctStrToUInt (PortStr);
  Usb->InterfaceNumber  = (UINT8) SctStrToUInt (InterfaceStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Usb;
}

#define I2ONodeType    3
#define I2ONodeSubType 6

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateI2ODeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16          *TIDStr;
  I2O_DEVICE_PATH *I2O;

  TIDStr    = SctSplitStr (&TextDeviceNode, L',');
  I2O = (I2O_DEVICE_PATH *) CreateDeviceNode (
                              I2ONodeType,
                              I2ONodeSubType,
                              sizeof (I2O_DEVICE_PATH)
                              );
  I2O->Tid  = (UINT32) SctStrToUInt (TIDStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) I2O;
}

#define InfiniBandNodeType    3
#define InfiniBandNodeSubType 9

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateInfiniBandDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                  *FlagsStr;
  CHAR16                  *GuidStr;
  CHAR16                  *SidStr;
  CHAR16                  *TidStr;
  CHAR16                  *DidStr;
  EFI_GUID                PortGid;
  INFINIBAND_DEVICE_PATH  *InfiniBand;

  FlagsStr   = SctSplitStr (&TextDeviceNode, L',');
  GuidStr    = SctSplitStr (&TextDeviceNode, L',');
  SidStr     = SctSplitStr (&TextDeviceNode, L',');
  TidStr     = SctSplitStr (&TextDeviceNode, L',');
  DidStr     = SctSplitStr (&TextDeviceNode, L',');
  InfiniBand = (INFINIBAND_DEVICE_PATH *) CreateDeviceNode (
                                            InfiniBandNodeType,
                                            InfiniBandNodeSubType,
                                            sizeof (INFINIBAND_DEVICE_PATH)
                                            );
  InfiniBand->ResourceFlags = (UINT32) SctStrToUInt (FlagsStr);
  StrToGuid (GuidStr, &PortGid);
  SctCopyMem (InfiniBand->PortGid, &PortGid, sizeof (EFI_GUID));
  SctStrToUInt64 (SidStr, &InfiniBand->ServiceId);
  SctStrToUInt64 (TidStr, &InfiniBand->TargetPortId);
  SctStrToUInt64 (DidStr, &InfiniBand->DeviceId);

  return (EFI_DEVICE_PATH_PROTOCOL *) InfiniBand;
}

#define VenPcAnsiNodeType    3
#define VenPcAnsiNodeSubType 10

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateVenPcAnsiDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  VENDOR_DEVICE_PATH  *Vendor;

  Vendor = (VENDOR_DEVICE_PATH *) CreateDeviceNode (
                                    VenPcAnsiNodeType,
                                    VenPcAnsiNodeSubType,
                                    sizeof (VENDOR_DEVICE_PATH));
  Vendor->Guid = gBlackBoxEfiPcAnsiGuid;

  return (EFI_DEVICE_PATH_PROTOCOL *) Vendor;
}

EFI_GUID mEfiDevicePathMessagingUartFlowControlGuid = DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL;

#define UartFlowCtrlNodeType    3
#define UartFlowCtrlNodeSubtype 10

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateUartFlowCtrlDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                        *ValueStr;
  UART_FLOW_CONTROL_DEVICE_PATH *UartFlowControl;

  ValueStr        = SctSplitStr (&TextDeviceNode, L',');
  UartFlowControl = (UART_FLOW_CONTROL_DEVICE_PATH *) CreateDeviceNode (
                                                        UartFlowCtrlNodeType,
                                                        UartFlowCtrlNodeSubtype,
                                                        sizeof (UART_FLOW_CONTROL_DEVICE_PATH)
                                                        );
  UartFlowControl->Guid = mEfiDevicePathMessagingUartFlowControlGuid;
  if (SctStrCmp (ValueStr, L"XonXoff") == 0) {
    UartFlowControl->FlowControlMap = 2;
  } else if (SctStrCmp (ValueStr, L"Hardware") == 0) {
    UartFlowControl->FlowControlMap = 1;
  } else {
    UartFlowControl->FlowControlMap = 0;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) UartFlowControl;
}

EFI_GUID mEfiDevicePathMessagingSASGuid = DEVICE_PATH_MESSAGING_SAS;

#define SASNodeType     3
#define SASNodeSubType  10

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateSASDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16          *AddressStr;
  CHAR16          *LunStr;
  CHAR16          *RTPStr;
  CHAR16          *SASSATAStr;
  CHAR16          *LocationStr;
  CHAR16          *ConnectStr;
  CHAR16          *DriveBayStr;
  CHAR16          *ReservedStr;
  UINT16          Info;
  SAS_DEVICE_PATH *Sas;

  AddressStr  = SctSplitStr (&TextDeviceNode, L',');
  LunStr      = SctSplitStr (&TextDeviceNode, L',');
  RTPStr      = SctSplitStr (&TextDeviceNode, L',');
  SASSATAStr  = SctSplitStr (&TextDeviceNode, L',');
  LocationStr = SctSplitStr (&TextDeviceNode, L',');
  ConnectStr  = SctSplitStr (&TextDeviceNode, L',');
  DriveBayStr = SctSplitStr (&TextDeviceNode, L',');
  ReservedStr = SctSplitStr (&TextDeviceNode, L',');
  Info        = 0x0000;
  Sas         = (SAS_DEVICE_PATH *) CreateDeviceNode (
                                      SASNodeType,
                                      SASNodeSubType,
                                      sizeof (SAS_DEVICE_PATH)
                                      );
  Sas->Guid         = mEfiDevicePathMessagingSASGuid;
  SctStrToUInt64 (AddressStr, &Sas->SasAddress);
  SctStrToUInt64 (LunStr, &Sas->Lun);
  Sas->RelativeTargetPort = (UINT16) SctStrToUInt (RTPStr);
  if (SctStrCmp (SASSATAStr, L"NoTopology") == 0)
    ;
  else {
    if (SctStrCmp (DriveBayStr, L"0") == 0) {
      Info |= 0x0001;
    } else {
      Info |= 0x0002;
      Info |= ((SctStrToUInt (DriveBayStr) - 1) << 8);
    }

    if (SctStrCmp (SASSATAStr, L"SATA") == 0) {
      Info |= 0x0010;
    }
    if (SctStrCmp (LocationStr, L"External") == 0) {
      Info |= 0x0020;
    }
    if (SctStrCmp (ConnectStr, L"Expanded") == 0) {
      Info |= 0x0040;
    }
  }

  Sas->DeviceTopology = Info;
  Sas->Reserved       = (UINT32) SctStrToUInt (ReservedStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Sas;
}

#define SASExNodeType     3
#define SASExNodeSubType  22

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateSASExDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16               *AddressStr;
  CHAR16               *LunStr;
  CHAR16               *RTPStr;
  CHAR16               *SASSATAStr;
  CHAR16               *LocationStr;
  CHAR16               *ConnectStr;
  CHAR16               *DriveBayStr;
  UINT16               Info;
  SASEX_DEVICE_PATH    *SasEx;

  AddressStr  = SctSplitStr (&TextDeviceNode, L',');
  LunStr      = SctSplitStr (&TextDeviceNode, L',');
  RTPStr      = SctSplitStr (&TextDeviceNode, L',');
  SASSATAStr  = SctSplitStr (&TextDeviceNode, L',');
  LocationStr = SctSplitStr (&TextDeviceNode, L',');
  ConnectStr  = SctSplitStr (&TextDeviceNode, L',');
  DriveBayStr = SctSplitStr (&TextDeviceNode, L',');
  Info        = 0x0000;
  SasEx       = (SASEX_DEVICE_PATH *) CreateDeviceNode (
                                        SASExNodeType,
                                        SASExNodeSubType,
                                        sizeof (SASEX_DEVICE_PATH)
                                        );

  StrToUInt8Array (AddressStr, SasEx->SasAddress);
  StrToUInt8Array (LunStr, SasEx->Lun);
  SasEx->RelativeTargetPort = (UINT16) SctStrToUInt (RTPStr);
  if (SctStrCmp (SASSATAStr, L"NoTopology") == 0)
    ;
  else {
    if (SctStrCmp (DriveBayStr, L"0") == 0) {
      Info |= 0x0001;
    } else {
      Info |= 0x0002;
      Info |= ((SctStrToUInt (DriveBayStr) - 1) << 8);
    }

    if (SctStrCmp (SASSATAStr, L"SATA") == 0) {
      Info |= 0x0010;
    }
    if (SctStrCmp (LocationStr, L"External") == 0) {
      Info |= 0x0020;
    }
    if (SctStrCmp (ConnectStr, L"Expanded") == 0) {
      Info |= 0x0040;
    }
  }

  SasEx->DeviceTopology = Info;

  return (EFI_DEVICE_PATH_PROTOCOL *) SasEx;
}

#define DebugPortNodeType    3
#define DebugPortNodeSubType 10

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateDebugPortDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  VENDOR_DEFINED_MESSAGING_DEVICE_PATH  *Vend;

  Vend = (VENDOR_DEFINED_MESSAGING_DEVICE_PATH *) CreateDeviceNode (
                                                    DebugPortNodeType,
                                                    DebugPortNodeSubType,
                                                    sizeof(VENDOR_DEFINED_MESSAGING_DEVICE_PATH)
                                                    );
  Vend->Guid = gBlackBoxEfiDebugPortProtocolGuid;

  return (EFI_DEVICE_PATH_PROTOCOL *) Vend;
}

#define MACNodeType     3
#define MACNodeSubType  11

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateMACDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                *AddressStr;
  CHAR16                *IfTypeStr;
  UINTN                 Length;
  MAC_ADDR_DEVICE_PATH  *MAC;

  AddressStr    = SctSplitStr (&TextDeviceNode, L',');
  IfTypeStr     = SctSplitStr (&TextDeviceNode, L',');
  MAC           = (MAC_ADDR_DEVICE_PATH *) CreateDeviceNode (
                                             MACNodeType,
                                             MACNodeSubType,
                                             sizeof (MAC_ADDR_DEVICE_PATH)
                                             );
  MAC->IfType   = (UINT8) SctStrToUInt (IfTypeStr);
  Length = sizeof (EFI_MAC_ADDRESS);
  StrToBuf (&MAC->MacAddress.Addr[0], Length, AddressStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) MAC;
}

#define Ipv4NodeType     3
#define Ipv4NodeSubType  12

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateIPv4DeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16            *RemoteIPStr;
  CHAR16            *ProtocolStr;
  CHAR16            *TypeStr;
  CHAR16            *LocalIPStr;
  CHAR16            *GatewayStr;
  CHAR16            *SubnetStr;
  IPV4_DEVICE_PATH  *IPv4;

  RemoteIPStr           = SctSplitStr (&TextDeviceNode, L',');
  ProtocolStr           = SctSplitStr (&TextDeviceNode, L',');
  TypeStr               = SctSplitStr (&TextDeviceNode, L',');
  LocalIPStr            = SctSplitStr (&TextDeviceNode, L',');
  GatewayStr            = SctSplitStr (&TextDeviceNode, L',');
  SubnetStr             = SctSplitStr (&TextDeviceNode, L',');
  IPv4                  = (IPV4_DEVICE_PATH *) CreateDeviceNode (
                                                 Ipv4NodeType,
                                                 Ipv4NodeSubType,
                                                 sizeof (IPV4_DEVICE_PATH)
                                                 );

  SctStrToIPv4Addr (&RemoteIPStr, &IPv4->RemoteIpAddress);
  IPv4->Protocol = (SctStrCmp (ProtocolStr, L"UDP") == 0) ? (UINT16) 0x11 : (UINT16) 0x06;
  if (SctStrCmp (TypeStr, L"Static") == 0) {
    IPv4->StaticIpAddress = TRUE;
  } else {
    IPv4->StaticIpAddress = FALSE;
  }
  SctStrToIPv4Addr (&LocalIPStr, &IPv4->LocalIpAddress);
  IPv4->LocalPort       = 0;
  IPv4->RemotePort      = 0;
  SctStrToIPv4Addr (&GatewayStr, &IPv4->GatewayIPAddress);
  SctStrToIPv4Addr (&SubnetStr,  &IPv4->SubnetMask);

  return (EFI_DEVICE_PATH_PROTOCOL *) IPv4;
}

#define Ipv6NodeType    3
#define Ipv6NodeSubType 13

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateIPv6DeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16            *RemoteIPStr;
  CHAR16            *ProtocolStr;
  CHAR16            *IPAddressOriginStr;
  CHAR16            *LocalIPStr;
  CHAR16            *PrefixLengthStr;
  CHAR16            *GatewayIPAddressStr;
  IPV6_DEVICE_PATH  *IPv6;

  RemoteIPStr           = SctSplitStr (&TextDeviceNode, L',');
  ProtocolStr           = SctSplitStr (&TextDeviceNode, L',');
  IPAddressOriginStr    = SctSplitStr (&TextDeviceNode, L',');
  LocalIPStr            = SctSplitStr (&TextDeviceNode, L',');
  PrefixLengthStr       = SctSplitStr (&TextDeviceNode, L',');
  GatewayIPAddressStr   = SctSplitStr (&TextDeviceNode, L',');
  IPv6                  = (IPV6_DEVICE_PATH *) CreateDeviceNode (
                                                 Ipv6NodeType,
                                                 Ipv6NodeSubType,
                                                 sizeof (IPV6_DEVICE_PATH)
                                                 );
  SctStrToIPv6Addr (&RemoteIPStr, &IPv6->RemoteIpAddress);
  IPv6->Protocol        = (SctStrCmp (ProtocolStr, L"UDP") == 0) ? (UINT16) 0x11 : (UINT16) 0x06;

  IPv6->IPAddressOrigin = (SctStrCmp (IPAddressOriginStr, L"Static") == 0) ? 0 : (SctStrCmp(IPAddressOriginStr, L"StatelessAutoConfigure") == 0) ? 1 : 2;
  SctStrToIPv6Addr (&LocalIPStr, &IPv6->LocalIpAddress);
  IPv6->LocalPort       = 0;
  IPv6->RemotePort      = 0;
  IPv6->PrefixLength    = (UINT8) SctStrToUInt (PrefixLengthStr);
  SctStrToIPv6Addr (&GatewayIPAddressStr, &IPv6->GatewayIPAddress);

  return (EFI_DEVICE_PATH_PROTOCOL *) IPv6;
}

#define UartNodeType    3
#define UartNodeSubType 14

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateUartDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16            *BaudStr;
  CHAR16            *DataBitsStr;
  CHAR16            *ParityStr;
  CHAR16            *StopBitsStr;
  UART_DEVICE_PATH  *Uart;

  BaudStr         = SctSplitStr (&TextDeviceNode, L',');
  DataBitsStr     = SctSplitStr (&TextDeviceNode, L',');
  ParityStr       = SctSplitStr (&TextDeviceNode, L',');
  StopBitsStr     = SctSplitStr (&TextDeviceNode, L',');
  Uart            = (UART_DEVICE_PATH *) CreateDeviceNode (
                                           UartNodeType,
                                           UartNodeSubType,
                                           sizeof(UART_DEVICE_PATH)
                                           );
  Uart->BaudRate  = (SctStrCmp (BaudStr, L"DEFAULT") == 0) ? 115200 : (UINT64) SctAtoi (BaudStr);
  Uart->DataBits  = (SctStrCmp (DataBitsStr, L"DEFAULT") == 0) ? (UINT8) 8 : (UINT8) SctAtoi (DataBitsStr);
  switch (*ParityStr) {
  case L'D':
    Uart->Parity = 0;
    break;
  case L'N':
    Uart->Parity = 1;
    break;
  case L'E':
    Uart->Parity = 2;
    break;
  case L'O':
    Uart->Parity = 3;
    break;
  case L'M':
    Uart->Parity = 4;
    break;
  case L'S':
    Uart->Parity = 5;
	break;
  default:
    Uart->Parity = 0xff;
  }

  if (SctStrCmp (StopBitsStr, L"D") == 0) {
    Uart->StopBits = (UINT8) 0;
  } else if (SctStrCmp (StopBitsStr, L"1") == 0) {
    Uart->StopBits = (UINT8) 1;
  } else if (SctStrCmp (StopBitsStr, L"1.5") == 0) {
    Uart->StopBits = (UINT8) 2;
  } else if (SctStrCmp (StopBitsStr, L"2") == 0) {
    Uart->StopBits = (UINT8) 3;
  } else {
    Uart->StopBits = 0xff;
  }

  return (EFI_DEVICE_PATH_PROTOCOL *) Uart;
}

#define VlanNodeType    3
#define VlanNodeSubtype 20

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateVlanDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                        *VlanIdStr;
  VLAN_DEVICE_PATH              *Vlan;

  VlanIdStr = SctSplitStr (&TextDeviceNode, L',');
  Vlan = (VLAN_DEVICE_PATH *) CreateDeviceNode (
                                VlanNodeType,
                                VlanNodeSubtype,
                                sizeof (VLAN_DEVICE_PATH)
                                );
  Vlan->VlanId = (UINT16) SctStrToUInt (VlanIdStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Vlan;
}

#define FibreExNodeType    3
#define FibreExNodeSubType 21

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateFibreExDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                      *WWNStr;
  CHAR16                      *LunStr;
  FIBRECHANNELEX_DEVICE_PATH  *FibreEx;

  WWNStr  = SctSplitStr (&TextDeviceNode, L',');
  LunStr  = SctSplitStr (&TextDeviceNode, L',');
  FibreEx = (FIBRECHANNELEX_DEVICE_PATH *) CreateDeviceNode (
                                             FibreExNodeType,
                                             FibreExNodeSubType,
                                             sizeof (FIBRECHANNELEX_DEVICE_PATH)
                                             );
  FibreEx->Reserved = 0;
  StrToUInt8Array (WWNStr, FibreEx->WWN);
  StrToUInt8Array (LunStr, FibreEx->Lun);

  return (EFI_DEVICE_PATH_PROTOCOL *) FibreEx;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateUsbClassDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = TRUE;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateUsbVideoDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = 14;
  UsbClassText.SubClassExist = TRUE;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

#define UsbTestAndMeasurementNodeType     3
#define UsbTestAndMeasurementNodeSubType  15

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateUsbTestAndMeasurementDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  USB_CLASS_TEXT  UsbClassText;

  UsbClassText.ClassExist    = FALSE;
  UsbClassText.Class         = 254;
  UsbClassText.SubClassExist = FALSE;
  UsbClassText.SubClass      = 3;

  return ConvertFromTextUsbClass (TextDeviceNode, &UsbClassText);
}

#define UnitNodeType     3
#define UnitNodeSubType  17

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateUnitDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                          *LunStr;
  DEVICE_LOGICAL_UNIT_DEVICE_PATH *LogicalUnit;

  LunStr      = SctSplitStr (&TextDeviceNode, L',');
  LogicalUnit = (DEVICE_LOGICAL_UNIT_DEVICE_PATH *) CreateDeviceNode (
                                                      UnitNodeType,
                                                      UnitNodeSubType,
                                                      sizeof (DEVICE_LOGICAL_UNIT_DEVICE_PATH)
                                                      );
  LogicalUnit->Lun  = (UINT8) SctStrToUInt (LunStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) LogicalUnit;
}

#define iSCSINodeType     3
#define iSCSINodeSubType 19

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateiScsiDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  UINT16                      Options;
  CHAR16                      *NameStr;
  CHAR16                      *PortalGroupStr;
  CHAR16                      *LunStr;
  CHAR16                      *HeaderDigestStr;
  CHAR16                      *DataDigestStr;
  CHAR16                      *AuthenticationStr;
  CHAR16                      *ProtocolStr;
  UINT64                      LunNum;
  ISCSI_DEVICE_PATH_WITH_NAME *iSCSI;

  NameStr           = SctSplitStr (&TextDeviceNode, L',');
  PortalGroupStr    = SctSplitStr (&TextDeviceNode, L',');
  LunStr            = SctSplitStr (&TextDeviceNode, L',');
  HeaderDigestStr   = SctSplitStr (&TextDeviceNode, L',');
  DataDigestStr     = SctSplitStr (&TextDeviceNode, L',');
  AuthenticationStr = SctSplitStr (&TextDeviceNode, L',');
  ProtocolStr       = SctSplitStr (&TextDeviceNode, L',');
  iSCSI             = (ISCSI_DEVICE_PATH_WITH_NAME *) CreateDeviceNode (
                                                        iSCSINodeType,
                                                        iSCSINodeSubType,
                                                        sizeof (ISCSI_DEVICE_PATH_WITH_NAME) + (UINT16) SctStrLen (NameStr)
                                                        );
  SctUnicodeToAscii (iSCSI->iSCSITargetName, NameStr, SctStrLen (NameStr));
  iSCSI->TargetPortalGroupTag = (UINT16) SctStrToUInt (PortalGroupStr);
  SctStrToUInt64 (LunStr, &LunNum);
  iSCSI->Lun = LunNum;

  Options = 0x0000;
  if (SctStrCmp (HeaderDigestStr, L"CRC32C") == 0) {
    Options |= 0x0002;
  }
  if (SctStrCmp (DataDigestStr, L"CRC32C") == 0) {
    Options |= 0x0008;
  }
  if (SctStrCmp (AuthenticationStr, L"None") == 0) {
    Options |= 0x0800;
  }
  if (SctStrCmp (AuthenticationStr, L"CHAP_UNI") == 0) {
    Options |= 0x1000;
  }
  iSCSI->LoginOption      = (UINT16) Options;
  iSCSI->NetworkProtocol  = (UINT16) SctStrCmp (ProtocolStr, L"TCP");

  return (EFI_DEVICE_PATH_PROTOCOL *) iSCSI;
}

#define NVMeNodeType    3
#define NVMeNodeSubType 23

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateNVMEDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16              *NSIDStr;
  CHAR16              *EUIStr;
  NVME_DEVICE_PATH    *NVMe;

  NSIDStr = SctSplitStr (&TextDeviceNode, L',');
  EUIStr  = SctSplitStr (&TextDeviceNode, L',');
  NVMe  = (NVME_DEVICE_PATH *) CreateDeviceNode (
                                 NVMeNodeType,
                                 NVMeNodeSubType,
                                 sizeof (NVME_DEVICE_PATH)
                                 );

  NVMe->NamespaceId = (UINT32) SctStrToUInt (NSIDStr);

  EUI64StrToUInt64 (EUIStr, &NVMe->EUId);

  return (EFI_DEVICE_PATH_PROTOCOL *) NVMe;
}

#define HdNodeType     4
#define HdNodeSubType  1

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateHdDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                *PartitionStr;
  CHAR16                *TypeStr;
  CHAR16                *SignatureStr;
  CHAR16                *StartStr;
  CHAR16                *SizeStr;
  UINT32                Signature32;
  EFI_GUID              SignatureGuid;
  HARDDRIVE_DEVICE_PATH *Hd;

  PartitionStr        = SctSplitStr (&TextDeviceNode, L',');
  TypeStr             = SctSplitStr (&TextDeviceNode, L',');
  SignatureStr        = SctSplitStr (&TextDeviceNode, L',');
  StartStr            = SctSplitStr (&TextDeviceNode, L',');
  SizeStr             = SctSplitStr (&TextDeviceNode, L',');
  Hd                  = (HARDDRIVE_DEVICE_PATH *) CreateDeviceNode (
                                                    HdNodeType,
                                                    HdNodeSubType,
                                                    sizeof (HARDDRIVE_DEVICE_PATH)
                                                    );

  Hd->PartitionNumber = (UINT32) SctAtoi (PartitionStr);

  SctZeroMem (Hd->Signature, 16);
  Hd->MBRType = (UINT8) 0;

  if (SctStrCmp (TypeStr, L"MBR") == 0) {
    Hd->SignatureType = SIGNATURE_TYPE_MBR;
    Hd->MBRType       = 0x01;

    Signature32       = (UINT32) SctStrToUInt (SignatureStr);
    SctCopyMem (Hd->Signature, &Signature32, sizeof (UINT32));
  } else if (SctStrCmp (TypeStr, L"GPT") == 0) {
    Hd->SignatureType = SIGNATURE_TYPE_GUID;
    Hd->MBRType       = 0x02;

    StrToGuid (SignatureStr, &SignatureGuid);
    SctCopyMem (Hd->Signature, &SignatureGuid, sizeof (EFI_GUID));
  } else {
    Hd->SignatureType = (UINT8) SctStrToUInt (TypeStr);
  }

  SctStrToUInt64 (StartStr, &Hd->PartitionStart);
  SctStrToUInt64 (SizeStr, &Hd->PartitionSize);

  return (EFI_DEVICE_PATH_PROTOCOL *) Hd;
}

#define CdromNodeType     4
#define CdromNodeSubType  2

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateCdromDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16            *EntryStr;
  CHAR16            *StartStr;
  CHAR16            *SizeStr;
  CDROM_DEVICE_PATH *CDROM;

  EntryStr              = SctSplitStr (&TextDeviceNode, L',');
  StartStr              = SctSplitStr (&TextDeviceNode, L',');
  SizeStr               = SctSplitStr (&TextDeviceNode, L',');
  CDROM                 = (CDROM_DEVICE_PATH *) CreateDeviceNode (
                                                  MEDIA_DEVICE_PATH,
                                                  MEDIA_CDROM_DP,
                                                  sizeof (CDROM_DEVICE_PATH)
                                                  );
  CDROM->BootEntry      = (UINT32) SctStrToUInt (EntryStr);
  SctStrToUInt64 (StartStr, &CDROM->PartitionStart);
  SctStrToUInt64 (SizeStr, &CDROM->PartitionSize);

  return (EFI_DEVICE_PATH_PROTOCOL *) CDROM;
}

#define TextFileNodeType     4
#define TextFileNodeSubType  4

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateTextFileDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  FILEPATH_DEVICE_PATH  *File;

  File = (FILEPATH_DEVICE_PATH *) CreateDeviceNode (
                                    TextFileNodeType,
                                    TextFileNodeSubType,
                                    sizeof (FILEPATH_DEVICE_PATH) + (UINT16) (SctStrLen (TextDeviceNode) * 2)
                                    );

  SctStrCpy (File->PathName, TextDeviceNode);

  return (EFI_DEVICE_PATH_PROTOCOL *) File;
}

#define VenMEDIANodeType     4
#define VenMEDIANodeSubType  5

STATIC

EFI_DEVICE_PATH_PROTOCOL *
CreateMediaDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                      *GuidStr;
  MEDIA_PROTOCOL_DEVICE_PATH  *Media;

  GuidStr = SctSplitStr (&TextDeviceNode, L',');
  Media   = (MEDIA_PROTOCOL_DEVICE_PATH *) CreateDeviceNode (
                                             VenMEDIANodeType,
                                             VenMEDIANodeSubType,
                                             sizeof (MEDIA_PROTOCOL_DEVICE_PATH)
                                             );

  StrToGuid (GuidStr, &Media->Protocol);

  return (EFI_DEVICE_PATH_PROTOCOL *) Media;
}

#define BbsNodeType     5
#define BbsNodeSubType  1

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateBBSDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16              *TypeStr;
  CHAR16              *IdStr;
  CHAR16              *FlagsStr;
  BBS_BBS_DEVICE_PATH *Bbs;

  TypeStr   = SctSplitStr (&TextDeviceNode, L',');
  IdStr     = SctSplitStr (&TextDeviceNode, L',');
  FlagsStr  = SctSplitStr (&TextDeviceNode, L',');
  Bbs       = (BBS_BBS_DEVICE_PATH *) CreateDeviceNode (
                                        BbsNodeType,
                                        BbsNodeSubType,
                                        sizeof (BBS_BBS_DEVICE_PATH) + (UINT16) (SctStrLen (IdStr))
                                        );
  if (SctStrCmp (TypeStr, L"Floppy") == 0) {
    Bbs->DeviceType = BBS_TYPE_FLOPPY;
  } else if (SctStrCmp (TypeStr, L"HD") == 0) {
    Bbs->DeviceType = BBS_TYPE_HARDDRIVE;
  } else if (SctStrCmp (TypeStr, L"CDROM") == 0) {
    Bbs->DeviceType = BBS_TYPE_CDROM;
  } else if (SctStrCmp (TypeStr, L"PCMCIA") == 0) {
    Bbs->DeviceType = BBS_TYPE_PCMCIA;
  } else if (SctStrCmp (TypeStr, L"USB") == 0) {
    Bbs->DeviceType = BBS_TYPE_USB;
  } else if (SctStrCmp (TypeStr, L"Network") == 0) {
    Bbs->DeviceType = BBS_TYPE_EMBEDDED_NETWORK;
  } else {
    Bbs->DeviceType = BBS_TYPE_UNKNOWN;
  }
  SctStrToAscii (IdStr, Bbs->String);
  Bbs->StatusFlag = (UINT16) SctStrToUInt (FlagsStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Bbs;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateMediaRelativeOffsetRangeDeviceNode (
  IN CHAR16 *TextDeviceNode
  )
{
  CHAR16                    *StartingOffsetStr;
  CHAR16                    *EndingOffsetStr;
  MEDIA_OFFSET_DEVICE_PATH  *Offset;

  StartingOffsetStr = SctSplitStr (&TextDeviceNode, L',');
  EndingOffsetStr   = SctSplitStr (&TextDeviceNode, L',');
  Offset            = (MEDIA_OFFSET_DEVICE_PATH *) CreateDeviceNode (
                                                     MEDIA_DEVICE_PATH,
                                                     MEDIA_RELATIVE_OFFSET_RANGE_DP,
                                                     sizeof (MEDIA_OFFSET_DEVICE_PATH)
                                                     );

  Offset->Reserved = 0;
  SctStrToUInt64 (StartingOffsetStr, &Offset->StartingOffset);
  SctStrToUInt64 (EndingOffsetStr, &Offset->EndingOffset);

  return (EFI_DEVICE_PATH_PROTOCOL *) Offset;
}

//
// TDS 3.10.1
//
EFI_STATUS
DevicePathFromTextConvertTextToDeviceNodeCoverageTest (
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
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL    *DevicePathToText;
  EFI_TEST_ASSERTION                  AssertionType;
  CHAR16                              text[MaxDevicePathStrLen];
  EFI_DEVICE_PATH_PROTOCOL            *pReDevicePath;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gtBS->LocateProtocol (
                  &gBlackBoxEfiDevicePathUtilitiesProtocolGuid,
                  NULL,
                  &DevicePathUtilities
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gtBS->LocateProtocol (
                  &gBlackBoxEfiDevicePathToTextProtocolGuid,
                  NULL,
                  &DevicePathToText
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathFromText = (EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.10.1.2.1
  //
  SctStrCpy (text, L"0x2A");
  pDevicePath = CreatePcCardDeviceNode(text);

  SctStrCpy (text, L"PcCard(0x2A)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid089,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert PcCard(0x2A)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.2
  //
  SctSPrint(text, MaxDevicePathStrLen * 2, L"%d,0x123456789ABCDEF,0xFEDCBA9876543210", EfiMaxMemoryType);
  pDevicePath = CreateMemMapDeviceNode(text);

  SctSPrint(text, MaxDevicePathStrLen * 2, L"MemoryMapped(%d,0x123456789ABCDEF,0xFEDCBA9876543210)", EfiMaxMemoryType);
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid090,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert MemoryMapped(%d,0x123456789ABCDEF,0xFEDCBA9876543210)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.3
  //
  SctStrCpy (text, L"5AF6C71E-1261-4637-9838-C4E9913D1DBB,0123456789ABCDEF");
  pDevicePath = CreateVenHwDeviceNode(text);

  SctStrCpy (text, L"VenHw(5AF6C71E-1261-4637-9838-C4E9913D1DBB,0123456789ABCDEF)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid091,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert VenHw(5AF6C71E-1261-4637-9838-C4E9913D1DBB,0123456789ABCDEF)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.4
  //
  SctStrCpy (text, L"0x1234ABCD");
  pDevicePath = CreateCtrlDeviceNode(text);

  SctStrCpy (text, L"Ctrl(0x1234ABCD)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid092,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Ctrl(0x1234ABCD)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.5
  //
  SctStrCpy (text, L"AcpiEx(PNPABCD,PNP0000,0,,1234,5678)");
  pDevicePath = CreateAcpiExtDeviceNode(
                      L"PNPABCD", 
                      L"PNP0000", 
                      L"0", 
                      L"", 
                      L"1234", 
                      L"5678"
                      );

  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid093,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d:Status - %r",
                __FILE__,
                __LINE__,
                EFI_SUCCESS
                );

  //
  // TDS 3.10.1.2.6
  //
  SctStrCpy (text, L"AcpiExp(PNPABCD,PNP0001,5678)");
  pDevicePath = CreateAcpiExpDeviceNode(
                      L"PNPABCD", 
                      L"PNP0001",
                      L"5678"
                      );

  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid094,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d:Status - %r",
                __FILE__,
                __LINE__,
                EFI_SUCCESS
                );

  //
  // TDS 3.10.1.2.7
  //
  SctStrCpy (text, L"1234,0xABCD");
  pDevicePath = CreateScsiDeviceNode(text);

  SctStrCpy (text, L"Scsi(1234,0xABCD)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid095,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Scsi(1234,0xABCD)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.8
  //
  SctStrCpy (text, L"0x123456789ABCDEF0,0xABCDEF1234567890");
  pDevicePath = CreateFibreDeviceNode(text);

  SctStrCpy (text, L"Fibre(0x123456789ABCDEF0,0xABCDEF1234567890)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid096,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Fibre(0x123456789ABCDEF0,0xABCDEF1234567890)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.9
  //
  SctStrCpy (text, L"ACDE48234567ABCD");
  pDevicePath = CreateI1394DeviceNode(text);

  SctStrCpy (text, L"I1394(ACDE48234567ABCD)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid097,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert I1394(ACDE48234567ABCD)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.10
  //
  SctStrCpy (text, L"12,0xAB");
  pDevicePath = CreateUsbDeviceNode(text);

  SctStrCpy (text, L"USB(12,0xAB)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid098,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert USB(12,0xAB)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.11
  //
  SctStrCpy (text, L"0x1234ABCD");
  pDevicePath = CreateI2ODeviceNode(text);

  SctStrCpy (text, L"I2O(0x1234ABCD)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid099,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert I2O(0x1234ABCD)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.12
  //
  SctStrCpy (text, L"10,A1ED07B9-5BDC-4741-ADCF-CA1E8681DD1A,1234,5678,0xABCD");
  pDevicePath = CreateInfiniBandDeviceNode(text);

  SctStrCpy (text, L"Infiniband(10,A1ED07B9-5BDC-4741-ADCF-CA1E8681DD1A,1234,5678,0xABCD)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid100,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Infiniband(10,A1ED07B9-5BDC-4741-ADCF-CA1E8681DD1A,1234,5678,0xABCD)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.13
  //
  SctStrCpy (text, L"");
  pDevicePath = CreateVenPcAnsiDeviceNode(text);

  SctStrCpy (text, L"VenPcAnsi()");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid101,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert VenPcAnsi()",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.14
  //
  SctStrCpy (text, L"Hardware");
  pDevicePath = CreateUartFlowCtrlDeviceNode(text);

  SctStrCpy (text, L"UartFlowCtrl(Hardware)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid102,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert UartFlowCtrl(Hardware)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.15
  //
  SctStrCpy (text, L"1234567890,0xABCDEF,2000,SAS,External,Direct,0x6A,0");
  pDevicePath = CreateSASDeviceNode(text);

  SctStrCpy (text, L"SAS(1234567890,0xABCDEF,2000,SAS,External,Direct,0x6A,0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid103,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert SAS(1234567890,0xABCDEF,2000,SAS,External,Direct,0x6A,0)",
                __FILE__,
                (UINTN)__LINE__
                );
  //
  // TDS 3.10.1.2.16
  //
  SctStrCpy (text, L"");
  pDevicePath = CreateDebugPortDeviceNode(text);

  SctStrCpy (text, L"DebugPort()");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid104,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert DebugPort()",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.17
  //
  SctStrCpy (text, L"12345678ABCD12345678ABCD12345678ABCD12345678ABCD12345678ABCD1234,2");
  pDevicePath = CreateMACDeviceNode(text);

  SctStrCpy (text, L"MAC(12345678ABCD12345678ABCD12345678ABCD12345678ABCD12345678ABCD1234,2)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid105,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert MAC(12345678ABCD12345678ABCD12345678ABCD12345678ABCD12345678ABCD1234,2)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.18
  //
  SctStrCpy (text, L"12.34.56.78,TCP,Static,192.168.67.89,192.168.67.1,255.255.255.0");
  pDevicePath = CreateIPv4DeviceNode(text);

  SctStrCpy (text, L"IPv4(12.34.56.78,TCP,Static,192.168.67.89,192.168.67.1,255.255.255.0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid106,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert IPv4(12.34.56.78,TCP,Static,192.168.67.89,192.168.67.1,255.255.255.0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.19
  //
  SctStrCpy (text, L"1234:5678:ABCD:1234:5678:ABCD:1234:5678,UDP,Static,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD,8,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD");
  pDevicePath = CreateIPv6DeviceNode(text);

  SctStrCpy (text, L"IPv6(1234:5678:ABCD:1234:5678:ABCD:1234:5678,UDP,Static,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD,8,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid107,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert IPv6(1234:5678:ABCD:1234:5678:ABCD:1234:5678,UDP,Static,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD,8,5678:ABCD:1234:5678:ABCD:1234:5678:ABCD)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.20
  //
  SctStrCpy (text, L"115200,8,D,1.5");
  pDevicePath = CreateUartDeviceNode(text);

  SctStrCpy (text, L"Uart(115200,8,D,1.5)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid108,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Uart(115200,8,D,1.5)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.21
  //
  SctStrCpy (text, L"1234,5678,14,1,0");
  pDevicePath = CreateUsbClassDeviceNode(text);

  SctStrCpy (text, L"UsbClass(1234,5678,14,1,0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid109,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert UsbClass(1234,5678,14,1,0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.22
  //
  SctStrCpy (text, L"1234,5678,1,0");
  pDevicePath = CreateUsbVideoDeviceNode(text);

  SctStrCpy (text, L"UsbVideo(1234,5678,1,0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid110,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert UsbVideo(1234,5678,1,0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.23
  //
  SctStrCpy (text, L"1234,5678,1");
  pDevicePath = CreateUsbTestAndMeasurementDeviceNode(text);

  SctStrCpy (text, L"UsbTestAndMeasurement(1234,5678,1)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid111,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert UsbTestAndMeasurement(1234,5678,1)",
                __FILE__,
                (UINTN)__LINE__
                );
  //
  // TDS 3.10.1.2.25
  //
  SctStrCpy (text, L"0xAB");
  pDevicePath = CreateUnitDeviceNode(text);

  SctStrCpy (text, L"Unit(0xAB)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid113,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Unit(0xAB)",
                __FILE__,
                (UINTN)__LINE__
                );
  //
  // TDS 3.10.1.2.26
  //
  SctStrCpy (text, L"MyTargetName,0x12AB,5678,CRC32C,None,CHAP_BI,TCP");
  pDevicePath = CreateiScsiDeviceNode(text);

  SctStrCpy (text, L"iSCSI(MyTargetName,0x12AB,5678,CRC32C,None,CHAP_BI,TCP)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid114,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert iSCSI(MyTargetName,0x12AB,5678,CRC32C,None,CHAP_BI,TCP)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.27
  //
  SctStrCpy (text, L"6,GPT,E8AAED38-1815-4E4F-BCB5-2E3DBD160C9C,12345678,0xABCD1234");
  pDevicePath = CreateHdDeviceNode(text);

  SctStrCpy (text, L"HD(6,GPT,E8AAED38-1815-4E4F-BCB5-2E3DBD160C9C,12345678,0xABCD1234)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid115,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert HD(6,GPT,E8AAED38-1815-4E4F-BCB5-2E3DBD160C9C,12345678,0xABCD1234)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.28
  //
  SctStrCpy (text, L"6,MBR,0x56789ABC,12345678,0xABCD1234");
  pDevicePath = CreateHdDeviceNode(text);

  SctStrCpy (text, L"HD(6,MBR,0x56789ABC,12345678,0xABCD1234)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid116,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert HD(6,MBR,0x56789ABC,12345678,0xABCD1234)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.29
  //
  SctStrCpy (text, L"12340000,12345678,0xABCD1234");
  pDevicePath = CreateCdromDeviceNode(text);

  SctStrCpy (text, L"CDROM(12340000,12345678,0xABCD1234)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid117,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert CDROM(12340000,12345678,0xABCD1234)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.30
  //
  SctStrCpy (text, L"MyFilePath\\filepath");
  pDevicePath = CreateTextFileDeviceNode(text);

  SctStrCpy (text, L"MyFilePath\\filepath");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid118,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert MyFilePath\\filepath",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.31
  //
  SctStrCpy (text, L"BA3A77E6-39A2-4375-A39A-108BFFCCE1AA");
  pDevicePath = CreateMediaDeviceNode(text);

  SctStrCpy (text, L"Media(BA3A77E6-39A2-4375-A39A-108BFFCCE1AA)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid119,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Media(BA3A77E6-39A2-4375-A39A-108BFFCCE1AA)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // TDS 3.10.1.2.32
  //
  SctStrCpy (text, L"Floppy,MyId,0x12AB");
  pDevicePath = CreateBBSDeviceNode(text);

  SctStrCpy (text, L"BBS(Floppy,MyId,0x12AB)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid120,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert BBS(Floppy,MyId,0x12AB)",
                __FILE__,
                (UINTN)__LINE__
                );

  SctStrCpy (text, L"0xFF, 0xFFFF");
  pDevicePath = CreateMediaRelativeOffsetRangeDeviceNode(text);

  SctStrCpy (text, L"Offset(0xFF, 0xFFFF)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid121,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Offset(0xFF, 0xFFFF)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // Vlan 
  //
  SctStrCpy (text, L"0x12");
  pDevicePath = CreateVlanDeviceNode(text);

  SctStrCpy (text, L"Vlan(0x12)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid122,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Vlan(0x12)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // AcpiAdr(0x80010100)
  //
  SctStrCpy (text, L"0x80010100");
  pDevicePath = CreateAcpiAdrDeviceNode(text);

  SctStrCpy (text, L"AcpiAdr(0x80010100)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid112,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert AcpiAdr(0x80010100)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // PciRoot(0x0)
  //
  SctStrCpy (text, L"0x0");
  pDevicePath = CreatePciRootDeviceNode(text);

  SctStrCpy (text, L"PciRoot(0x0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid123,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert PciRoot(0x0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // PcieRoot(0x0)
  //
  SctStrCpy (text, L"0x0");
  pDevicePath = CreatePcieRootDeviceNode(text);

  SctStrCpy (text, L"PcieRoot(0x0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid124,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert PcieRoot(0x0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // Floppy(0x0)
  //
  SctStrCpy (text, L"0x0");
  pDevicePath = CreateFloppyDeviceNode(text);

  SctStrCpy (text, L"Floppy(0x0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid125,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Floppy(0x0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // Keyboard(0x0)
  //
  SctStrCpy (text, L"0x0");
  pDevicePath = CreateKeyboardDeviceNode(text);

  SctStrCpy (text, L"Keyboard(0x0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid126,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Keyboard(0x0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // Serial(0x0)
  //
  SctStrCpy (text, L"0x0");
  pDevicePath = CreateSerialDeviceNode(text);

  SctStrCpy (text, L"Serial(0x0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid127,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert Serial(0x0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // ParallelPort(0x0)
  //
  SctStrCpy (text, L"0x0");
  pDevicePath = CreateParallelPortDeviceNode(text);

  SctStrCpy (text, L"ParallelPort(0x0)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid128,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert ParallelPort(0x0)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // FibreEx(0x123456789ABCDEF0,0xABCDEF1234567890)
  //
  SctStrCpy (text, L"0x123456789ABCDEF0,0xABCDEF1234567890");
  pDevicePath = CreateFibreExDeviceNode(text);

  SctStrCpy (text, L"FibreEx(0x123456789ABCDEF0,0xABCDEF1234567890)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid129,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert FibreEx(0x123456789ABCDEF0,0xABCDEF1234567890)",
                __FILE__,
                (UINTN)__LINE__
                );

  //
  // SasEx(0x1234567890ABCDEF,0x1234567890ABCDEF,2000,SAS,External,Direct,0x6A)
  //
  SctStrCpy (text, L"0x1234567890ABCDEF,0x1234567890ABCDEF,2000,SAS,External,Direct,0x6A");
  pDevicePath = CreateSASExDeviceNode(text);

  SctStrCpy (text, L"SasEx(0x1234567890ABCDEF,0x1234567890ABCDEF,2000,SAS,External,Direct,0x6A)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid130,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert SASEx(0x1234567890ABCDEF,0x1234567890ABCDEF,2000,SAS,External,Direct,0x6A)",
                __FILE__,
                (UINTN)__LINE__
                );


  //
  // NVMe(0xAB124BEF,AB-CD-EF-01-23-45-67-89)
  //
 
  SctStrCpy (text, L"0xAB124BEF,AB-CD-EF-01-23-45-67-89");
  pDevicePath = CreateNVMEDeviceNode(text);

  SctStrCpy (text, L"NVMe(0xAB124BEF,AB-CD-EF-01-23-45-67-89)");
  pReDevicePath = DevicePathFromText->ConvertTextToDeviceNode (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid131,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert NVMe(0xAB124BEF,AB-CD-EF-01-23-45-67-89)",
                __FILE__,
                (UINTN)__LINE__
                );


  return EFI_SUCCESS;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
ConvertDevNodeFromTextPciRoot (
  IN EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities,
  IN CHAR16                              *TextDeviceNode
  )
{
  ACPI_HID_DEVICE_PATH  *Acpi;
  CHAR16                *UIDStr;

  UIDStr = SctSplitStr (&TextDeviceNode, L',');
  Acpi   = (ACPI_HID_DEVICE_PATH *) DevicePathUtilities->CreateDeviceNode (2, 1, sizeof (ACPI_HID_DEVICE_PATH));

  Acpi->HID = EISA_PNP_ID(0x0a03);
  Acpi->UID = (UINT32) SctStrToUInt (UIDStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Acpi;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
ConvertDevNodeFromTextPci (
  IN EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities,
  IN CHAR16                              *TextDeviceNode
  )
{
  CHAR16          *FunctionStr;
  CHAR16          *DeviceStr;
  PCI_DEVICE_PATH *Pci;

  FunctionStr = SctSplitStr (&TextDeviceNode, L',');
  DeviceStr   = SctSplitStr (&TextDeviceNode, L',');
  Pci         = (PCI_DEVICE_PATH *) DevicePathUtilities->CreateDeviceNode (1, 1, sizeof (PCI_DEVICE_PATH));

  Pci->Function = (UINT8) SctStrToUInt (FunctionStr);
  Pci->Device   = (UINT8) SctStrToUInt (DeviceStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Pci;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
ConvertDevNodeFromTextFloppy (
  IN EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities,
  IN CHAR16                              *TextDeviceNode
  )
{
  CHAR16                *UIDStr;
  ACPI_HID_DEVICE_PATH  *Acpi;

  UIDStr = SctSplitStr (&TextDeviceNode, L',');
  Acpi   = (ACPI_HID_DEVICE_PATH *) DevicePathUtilities->CreateDeviceNode (2, 1, sizeof (ACPI_HID_DEVICE_PATH));

  Acpi->HID = EISA_PNP_ID(0x0604);
  Acpi->UID = (UINT32) SctStrToUInt (UIDStr);

  return (EFI_DEVICE_PATH_PROTOCOL *) Acpi;
}

STATIC
EFI_DEVICE_PATH_PROTOCOL *
CreateFloppyDevicePath (
  IN EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities
  )
{
  EFI_DEVICE_PATH_PROTOCOL *pDevPathNode;
  EFI_DEVICE_PATH_PROTOCOL *pDevPath;

  pDevPath = (EFI_DEVICE_PATH_PROTOCOL *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  SctSetDevicePathEndNode (pDevPath);

  pDevPathNode    = ConvertDevNodeFromTextPciRoot(DevicePathUtilities, L"PciRoot(0)");
  pDevPath        = DevicePathUtilities->AppendDeviceNode (pDevPath, pDevPathNode);
  pDevPathNode    = ConvertDevNodeFromTextPci(DevicePathUtilities, L"Pci(0,10)");
  pDevPath        = DevicePathUtilities->AppendDeviceNode (pDevPath, pDevPathNode);
  pDevPathNode    = ConvertDevNodeFromTextFloppy(DevicePathUtilities, L"Floppy(0)");
  pDevPath        = DevicePathUtilities->AppendDeviceNode (pDevPath, pDevPathNode);

  return pDevPath;
}

//
// TDS 3.10.2
//
EFI_STATUS
DevicePathFromTextConvertTextToDevicePathCoverageTest (
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
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL    *DevicePathToText;
  EFI_TEST_ASSERTION                  AssertionType;
  CHAR16                              text[MaxDevicePathStrLen];
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath;
  EFI_DEVICE_PATH_PROTOCOL            *pReDevicePath;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gtBS->LocateProtocol (
                  &gBlackBoxEfiDevicePathUtilitiesProtocolGuid,
                  NULL,
                  &DevicePathUtilities
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gtBS->LocateProtocol (
                  &gBlackBoxEfiDevicePathToTextProtocolGuid,
                  NULL,
                  &DevicePathToText
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathFromText = (EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *) ClientInterface;

  //
  // TDS 3.10.2.2.1
  //
  SctStrCpy (text, L"PciRoot(0)/Pci(0,10)/Floppy(0)");
  pDevicePath = CreateFloppyDevicePath(DevicePathUtilities);

  pReDevicePath = DevicePathFromText->ConvertTextToDevicePath (text);
  if (SctCompareMem (pDevicePath, pReDevicePath, SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) pReDevicePath)) == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath);
  SctFreePool (pReDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathFromTextBBTestFunctionAssertionGuid180,
                L"EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL - ConvertDeviceNodeToText must correctly recover the converting ConvertTextToDeviceNode has acted on the device node string",
                L"%a:%d, Convert PciRoot(0)/Pci(0,10)/Floppy(0)",
                __FILE__,
                (UINTN)__LINE__
                );

  return EFI_SUCCESS;
}
