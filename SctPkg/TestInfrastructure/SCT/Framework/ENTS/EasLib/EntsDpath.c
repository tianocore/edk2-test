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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  EntsDpath.c

Abstract:

  MBR & Device Path functions

--*/
#include "SctLib.h"
#include <Library/EntsLib.h>
#include "EntsLibPlat.h"

#define ALIGN_SIZE(a) ((a % MIN_ALIGNMENT_SIZE) ? MIN_ALIGNMENT_SIZE - (a % MIN_ALIGNMENT_SIZE) : 0)
#define MAX_FILE_PATH 1024

typedef struct {
  VENDOR_DEVICE_PATH              DevicePath;
  UINT8                           LegacyDriveLetter;
} UNKNOWN_DEVICE_VENDOR_DEVICE_PATH;

//
// VLAN Device Path SubType
// BUGBUG: this local device path definition is temporal.
// when SCT remove dependency of ECP and updated to depend on MdePkg,
// this local VLAN device path definition should be removed.
//
#define SCT_MSG_VLAN_DP               0x14
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  UINT16                          VlanId;
} SCT_VLAN_DEVICE_PATH;

STATIC
VOID
_DevPathPci (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  PCI_DEVICE_PATH *Pci;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Pci = DevPath;
  EntsCatPrint (Str, L"Pci(%x|%x)", Pci->Device, Pci->Function);
}

STATIC
VOID
_DevPathPccard (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  PCCARD_DEVICE_PATH  *Pccard;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Pccard = DevPath;
  EntsCatPrint (Str, L"Pccard(Function%x)", Pccard->FunctionNumber);
}

STATIC
VOID
_DevPathMemMap (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  MEMMAP_DEVICE_PATH  *MemMap;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  MemMap = DevPath;
  EntsCatPrint (
    Str,
    L"MemMap(%d:%lx-%lx)",
    MemMap->MemoryType,
    MemMap->StartingAddress,
    MemMap->EndingAddress
    );
}

STATIC
VOID
_DevPathController (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  CONTROLLER_DEVICE_PATH  *Controller;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Controller = DevPath;
  EntsCatPrint (
    Str,
    L"Ctrl(%d)",
#if (EFI_SPECIFICATION_VERSION >= 0x00020028)
    Controller->ControllerNumber
#else
    Controller->Controller
#endif
    );
}

STATIC
VOID
_DevPathVendor (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  VENDOR_DEVICE_PATH                *Vendor;
  CHAR16                            *Type;
  UNKNOWN_DEVICE_VENDOR_DEVICE_PATH *UnknownDevPath;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Vendor = DevPath;
  switch (SctDevicePathType (&Vendor->Header)) {
  case HARDWARE_DEVICE_PATH:
    Type = L"Hw";
    break;

  case MESSAGING_DEVICE_PATH:
    Type = L"Msg";
    break;

  case MEDIA_DEVICE_PATH:
    Type = L"Media";
    break;

  default:
    Type = L"?";
    break;
  }

  EntsCatPrint (Str, L"Ven%s(%g", Type, &Vendor->Guid);
  if (EntsCompareGuid (&Vendor->Guid, &gtEfiUnknownDeviceGuid) == 0) {
    //
    // GUID used by EFI to enumerate an EDD 1.1 device
    //
    UnknownDevPath = (UNKNOWN_DEVICE_VENDOR_DEVICE_PATH *) Vendor;
    EntsCatPrint (Str, L":%02x)", UnknownDevPath->LegacyDriveLetter);
  } else {
    EntsCatPrint (Str, L")");
  }
}

STATIC
VOID
_DevPathVlan (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  SCT_VLAN_DEVICE_PATH  *Vlan;

  Vlan = DevPath;
  EntsCatPrint (Str, L"Vlan(%d)", (UINTN) Vlan->VlanId);
}

STATIC
VOID
_DevPathAcpi (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  ACPI_HID_DEVICE_PATH  *Acpi;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Acpi = DevPath;
  if ((Acpi->HID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
    EntsCatPrint (Str, L"Acpi(PNP%04x,%x)", EISA_ID_TO_NUM (Acpi->HID), Acpi->UID);
  } else {
    EntsCatPrint (Str, L"Acpi(%08x,%x)", Acpi->HID, Acpi->UID);
  }
}

STATIC
VOID
_DevPathExtendedAcpi (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  ACPI_EXTENDED_HID_DEVICE_PATH   *ExtendedAcpi;
  //
  // Index for HID, UID and CID strings, 0 for non-exist
  //
  UINT16                          HIDSTRIdx;
  UINT16                          UIDSTRIdx;
  UINT16                          CIDSTRIdx;
  UINT16                          Index;
  UINT16                          Length;
  UINT16                          Anchor;
  CHAR8                           *AsChar8Array;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  HIDSTRIdx    = 0;
  UIDSTRIdx    = 0;
  CIDSTRIdx    = 0;
  ExtendedAcpi = DevPath;
  Length       = SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) ExtendedAcpi);

  ASSERT (Length >= 19);
  AsChar8Array = (CHAR8 *) ExtendedAcpi;

  //
  // find HIDSTR
  //
  Anchor = 16;
  for (Index = Anchor; Index < Length && AsChar8Array[Index]; Index++) {
    ;
  }
  if (Index > Anchor) {
    HIDSTRIdx = Anchor;
  }
  //
  // find UIDSTR
  //
  Anchor = Index + 1;
  for (Index = Anchor; Index < Length && AsChar8Array[Index]; Index++) {
    ;
  }
  if (Index > Anchor) {
    UIDSTRIdx = Anchor;
  }
  //
  // find CIDSTR
  //
  Anchor = Index + 1;
  for (Index = Anchor; Index < Length && AsChar8Array[Index]; Index++) {
    ;
  }
  if (Index > Anchor) {
    CIDSTRIdx = Anchor;
  }
  
  if (HIDSTRIdx == 0 && CIDSTRIdx == 0 && ExtendedAcpi->UID == 0) {
    EntsCatPrint (Str, L"AcpiExp(");
    if ((ExtendedAcpi->HID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
      EntsCatPrint (Str, L"PNP%04x,", EISA_ID_TO_NUM (ExtendedAcpi->HID));
    } else {
      EntsCatPrint (Str, L"%08x,", ExtendedAcpi->HID);
    }
    if ((ExtendedAcpi->CID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
      EntsCatPrint (Str, L"PNP%04x,", EISA_ID_TO_NUM (ExtendedAcpi->CID));
    } else {
      EntsCatPrint (Str, L"%08x,", ExtendedAcpi->CID);
    }
    if (UIDSTRIdx != 0) {
      EntsCatPrint (Str, L"%a)", AsChar8Array + UIDSTRIdx);
    } else {
      EntsCatPrint (Str, L"\"\")");
    }
  } else {
    EntsCatPrint (Str, L"AcpiEx(");
    if ((ExtendedAcpi->HID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
      EntsCatPrint (Str, L"PNP%04x,", EISA_ID_TO_NUM (ExtendedAcpi->HID));
    } else {
      EntsCatPrint (Str, L"%08x,", ExtendedAcpi->HID);
    }
    if ((ExtendedAcpi->CID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
      EntsCatPrint (Str, L"PNP%04x,", EISA_ID_TO_NUM (ExtendedAcpi->CID));
    } else {
      EntsCatPrint (Str, L"%08x,", ExtendedAcpi->CID);
    }
    EntsCatPrint (Str, L"%x,", ExtendedAcpi->UID);

    if (HIDSTRIdx != 0) {
      EntsCatPrint (Str, L"%a,", AsChar8Array + HIDSTRIdx);
    } else {
      EntsCatPrint (Str, L"\"\",");
    }
    if (CIDSTRIdx != 0) {
      EntsCatPrint (Str, L"%a,", AsChar8Array + CIDSTRIdx);
    } else {
      EntsCatPrint (Str, L"\"\",");
    }
    if (UIDSTRIdx != 0) {
      EntsCatPrint (Str, L"%a)", AsChar8Array + UIDSTRIdx);
    } else {
      EntsCatPrint (Str, L"\"\")");
    }
  }

}

STATIC
VOID
_DevPathAdrAcpi (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  ACPI_ADR_DEVICE_PATH    *AcpiAdr;
  UINT16                  Index;
  UINT16                  Length;
  UINT16                  AdditionalAdrCount;

  AcpiAdr            = DevPath;
  Length             = SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) AcpiAdr);
  AdditionalAdrCount = (Length - 8) / 4;

  EntsCatPrint (Str, L"AcpiAdr(%x", AcpiAdr->ADR);
  for (Index = 0; Index < AdditionalAdrCount; Index++) {
    EntsCatPrint (Str, L",%x", *(UINT32 *) ((UINT8 *) AcpiAdr + 8 + Index * 4));
  }
  EntsCatPrint (Str, L")");
}

STATIC
VOID
_DevPathAtapi (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  ATAPI_DEVICE_PATH *Atapi;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Atapi = DevPath;
  EntsCatPrint (
    Str,
    L"Ata(%s,%s)",
    Atapi->PrimarySecondary ? L"Secondary" : L"Primary",
    Atapi->SlaveMaster ? L"Slave" : L"Master"
    );
}

STATIC
VOID
_DevPathScsi (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  SCSI_DEVICE_PATH  *Scsi;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Scsi = DevPath;
  EntsCatPrint (Str, L"Scsi(Pun%x,Lun%x)", Scsi->Pun, Scsi->Lun);
}

STATIC
VOID
_DevPathFibre (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  FIBRECHANNEL_DEVICE_PATH  *Fibre;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Fibre = DevPath;
  EntsCatPrint (Str, L"Fibre(Wwn%lx,Lun%lx)", Fibre->WWN, Fibre->Lun);
}

STATIC
VOID
_DevPath1394 (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  F1394_DEVICE_PATH *F1394;
  
  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  F1394 = DevPath;
  EntsCatPrint (Str, L"1394(%lx)", &F1394->Guid);
}

STATIC
VOID
_DevPathUsb (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  USB_DEVICE_PATH *Usb;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Usb = DevPath;
  EntsCatPrint (Str, L"Usb(%x,%x)", Usb->ParentPortNumber, Usb->InterfaceNumber);
}

STATIC
VOID
_DevPathUsbClass (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  //
  // tbd:
  //
  USB_CLASS_DEVICE_PATH *UsbClass;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  UsbClass = DevPath;
  EntsCatPrint (
    Str,
    L"Usb Class(%x,%x,%x,%x,%x)",
    UsbClass->VendorId,
    UsbClass->ProductId,
    UsbClass->DeviceClass,
    UsbClass->DeviceSubClass,
    UsbClass->DeviceProtocol
    );
}

STATIC
VOID
_DevPathI2O (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  I2O_DEVICE_PATH *I2O;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  I2O = DevPath;
  EntsCatPrint (Str, L"I2O(%x)", I2O->Tid);
}

STATIC
VOID
_DevPathMacAddr (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  MAC_ADDR_DEVICE_PATH  *MAC;
  UINTN                 HwAddressSize;
  UINTN                 Index;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  MAC           = DevPath;

  HwAddressSize = sizeof (EFI_MAC_ADDRESS);
  if (MAC->IfType == 0x01 || MAC->IfType == 0x00) {
    HwAddressSize = 6;
  }

  EntsCatPrint (Str, L"Mac(");

  for (Index = 0; Index < HwAddressSize; Index++) {
    EntsCatPrint (Str, L"%02x", MAC->MacAddress.Addr[Index]);
  }

  EntsCatPrint (Str, L")");
}

STATIC
VOID
_DevPathIPv4 (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  IPv4_DEVICE_PATH  *IP;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  IP = DevPath;
  EntsCatPrint (
    Str,
    L"IPv4(%d.%d.%d.%d:%d)",
    IP->RemoteIpAddress.Addr[0],
    IP->RemoteIpAddress.Addr[1],
    IP->RemoteIpAddress.Addr[2],
    IP->RemoteIpAddress.Addr[3],
    IP->RemotePort
    );
}

STATIC
VOID
_DevPathIPv6 (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  ASSERT (Str != NULL);

  EntsCatPrint (Str, L"IP-v6(not-done)");
}

STATIC
VOID
_DevPathInfiniBand (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  ASSERT (Str != NULL);

  EntsCatPrint (Str, L"InfiniBand(not-done)");
}

STATIC
VOID
_DevPathUart (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  UART_DEVICE_PATH  *Uart;
  CHAR8             Parity;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Uart = DevPath;
  switch (Uart->Parity) {
  case 0:
    Parity = 'D';
    break;

  case 1:
    Parity = 'N';
    break;

  case 2:
    Parity = 'E';
    break;

  case 3:
    Parity = 'O';
    break;

  case 4:
    Parity = 'M';
    break;

  case 5:
    Parity = 'S';
    break;

  default:
    Parity = 'x';
    break;
  }

  if (Uart->BaudRate == 0) {
    EntsCatPrint (Str, L"Uart(DEFAULT,%c,", Parity);
  } else {
    EntsCatPrint (Str, L"Uart(%ld,%c,", Uart->BaudRate, Parity);
  }

  if (Uart->DataBits == 0) {
    EntsCatPrint (Str, L"D,");
  } else {
    EntsCatPrint (Str, L"%d,", Uart->DataBits);
  }

  switch (Uart->StopBits) {
  case 0:
    EntsCatPrint (Str, L"D)");
    break;

  case 1:
    EntsCatPrint (Str, L"1)");
    break;

  case 2:
    EntsCatPrint (Str, L"1.5)");
    break;

  case 3:
    EntsCatPrint (Str, L"2)");
    break;

  default:
    EntsCatPrint (Str, L"x)");
    break;
  }
}

STATIC
VOID
_DevPathHardDrive (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  HARDDRIVE_DEVICE_PATH *Hd;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Hd = DevPath;
  switch (Hd->SignatureType) {
  case SIGNATURE_TYPE_MBR:
    EntsCatPrint (
      Str,
      L"HD(Part%d,Sig%08x)",
      Hd->PartitionNumber,
      *((UINT32 *) (&(Hd->Signature[0])))
      );
    break;

  case SIGNATURE_TYPE_GUID:
    EntsCatPrint (
      Str,
      L"HD(Part%d,Sig%g)",
      Hd->PartitionNumber,
      (EFI_GUID *) &(Hd->Signature[0])
      );
    break;

  default:
    EntsCatPrint (
      Str,
      L"HD(Part%d,MBRType=%02x,SigType=%02x)",
      Hd->PartitionNumber,
      Hd->MBRType,
      Hd->SignatureType
      );
    break;
  }
}

STATIC
VOID
_DevPathCDROM (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  CDROM_DEVICE_PATH *Cd;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Cd = DevPath;
  EntsCatPrint (Str, L"CDROM(Entry%x)", Cd->BootEntry);
}

STATIC
VOID
_DevPathFilePath (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  FILEPATH_DEVICE_PATH  *Fp;
  UINTN                 Length;
  CHAR16                *NewPath;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  Fp      = DevPath;
  Length  = SctDevicePathNodeLength (((EFI_DEVICE_PATH_PROTOCOL *) DevPath)) - 4;
  NewPath = EntsAllocateZeroPool (Length + sizeof (CHAR16));
  EntsCopyMem (NewPath, Fp->PathName, Length);
  EntsStrTrim (NewPath, L' ');
  EntsCatPrint (Str, L"%s", NewPath);
  EntsFreePool (NewPath);
}

STATIC
VOID
_DevPathMediaProtocol (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  MEDIA_PROTOCOL_DEVICE_PATH  *MediaProt;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  MediaProt = DevPath;
  EntsCatPrint (Str, L"%g", &MediaProt->Protocol);
}

#if (EFI_SPECIFICATION_VERSION < 0x00020000)
STATIC
VOID
_DevPathFvFilePath (
  IN OUT ENTS_POOL_PRINT       *Str,
  IN VOID                 *DevPath
  )
{
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *FvFilePath;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  FvFilePath = DevPath;
  EntsCatPrint (Str, L"%g", &FvFilePath->NameGuid);
}
#endif

STATIC
VOID
_DevPathBssBss (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  BBS_BBS_DEVICE_PATH *BBS;
  CHAR16              *Type;

  ASSERT (Str != NULL);
  ASSERT (DevPath != NULL);

  BBS = DevPath;
  switch (BBS->DeviceType) {
  case BBS_TYPE_FLOPPY:
    Type = L"Floppy";
    break;

  case BBS_TYPE_HARDDRIVE:
    Type = L"Harddrive";
    break;

  case BBS_TYPE_CDROM:
    Type = L"CDROM";
    break;

  case BBS_TYPE_PCMCIA:
    Type = L"PCMCIA";
    break;

  case BBS_TYPE_USB:
    Type = L"Usb";
    break;

  case BBS_TYPE_EMBEDDED_NETWORK:
    Type = L"Net";
    break;

  default:
    Type = L"?";
    break;
  }

  EntsCatPrint (Str, L"BBS-%s(%a)", Type, BBS->String);
}

STATIC
VOID
_DevPathEndInstance (
  IN OUT ENTS_POOL_PRINT  *Str,
  IN VOID                 *DevPath
  )
{
  ASSERT (Str != NULL);

  EntsCatPrint (Str, L",");
}

STATIC
VOID
_DevPathNodeUnknown (
  IN OUT ENTS_POOL_PRINT       *Str,
  IN VOID                 *DevPath
  )
{
  ASSERT (Str != NULL);

  EntsCatPrint (Str, L"?");
}

STATIC
struct {
  UINT8 Type;
  UINT8 SubType;
  VOID (*Function) (ENTS_POOL_PRINT *, VOID *);
} DevPathTable[] = {
  HARDWARE_DEVICE_PATH,  HW_PCI_DP,                         _DevPathPci,
  HARDWARE_DEVICE_PATH,  HW_PCCARD_DP,                      _DevPathPccard,
  HARDWARE_DEVICE_PATH,  HW_MEMMAP_DP,                      _DevPathMemMap,
  HARDWARE_DEVICE_PATH,  HW_VENDOR_DP,                      _DevPathVendor,
  HARDWARE_DEVICE_PATH,  HW_CONTROLLER_DP,                  _DevPathController,
  ACPI_DEVICE_PATH,      ACPI_DP,                           _DevPathAcpi,
  ACPI_DEVICE_PATH,      ACPI_EXTENDED_DP,                  _DevPathExtendedAcpi,
  ACPI_DEVICE_PATH,      ACPI_ADR_DP,                       _DevPathAdrAcpi,
  MESSAGING_DEVICE_PATH, MSG_ATAPI_DP,                      _DevPathAtapi,
  MESSAGING_DEVICE_PATH, MSG_SCSI_DP,                       _DevPathScsi,
  MESSAGING_DEVICE_PATH, MSG_FIBRECHANNEL_DP,               _DevPathFibre,
  MESSAGING_DEVICE_PATH, MSG_1394_DP,                       _DevPath1394,
  MESSAGING_DEVICE_PATH, MSG_USB_DP,                        _DevPathUsb,
  MESSAGING_DEVICE_PATH, MSG_USB_CLASS_DP,                  _DevPathUsbClass,
  MESSAGING_DEVICE_PATH, MSG_I2O_DP,                        _DevPathI2O,
  MESSAGING_DEVICE_PATH, MSG_MAC_ADDR_DP,                   _DevPathMacAddr,
  MESSAGING_DEVICE_PATH, MSG_IPv4_DP,                       _DevPathIPv4,
  MESSAGING_DEVICE_PATH, MSG_IPv6_DP,                       _DevPathIPv6,
  MESSAGING_DEVICE_PATH, MSG_INFINIBAND_DP,                 _DevPathInfiniBand,
  MESSAGING_DEVICE_PATH, MSG_UART_DP,                       _DevPathUart,
  MESSAGING_DEVICE_PATH, MSG_VENDOR_DP,                     _DevPathVendor,
  MESSAGING_DEVICE_PATH, SCT_MSG_VLAN_DP,                   _DevPathVlan,
  MEDIA_DEVICE_PATH,     MEDIA_HARDDRIVE_DP,                _DevPathHardDrive,
  MEDIA_DEVICE_PATH,     MEDIA_CDROM_DP,                    _DevPathCDROM,
  MEDIA_DEVICE_PATH,     MEDIA_VENDOR_DP,                   _DevPathVendor,
  MEDIA_DEVICE_PATH,     MEDIA_FILEPATH_DP,                 _DevPathFilePath,
  MEDIA_DEVICE_PATH,     MEDIA_PROTOCOL_DP,                 _DevPathMediaProtocol,
#if (EFI_SPECIFICATION_VERSION < 0x00020000)
  MEDIA_DEVICE_PATH,     MEDIA_FV_FILEPATH_DP,              _DevPathFvFilePath,
#endif
  BBS_DEVICE_PATH,       BBS_BBS_DP,                        _DevPathBssBss,
  END_DEVICE_PATH_TYPE,  END_INSTANCE_DEVICE_PATH_SUBTYPE,  _DevPathEndInstance,
  0,                     0,                                 NULL
};

UINTN
EntsDevicePathSize (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  )
/*++

Routine Description:
  Function returns the size of a device path in bytes.

Arguments:
  DevPath        - A pointer to a device path data structure

Returns:

  Size is returned.

--*/
{
  EFI_DEVICE_PATH_PROTOCOL  *Start;

  //
  // Search for the end of the device path structure
  //
  Start = DevPath;
  while (!SctIsDevicePathEnd (DevPath)) {
    DevPath = SctNextDevicePathNode (DevPath);
  }
  //
  // Compute the size
  //
  return ((UINTN) DevPath - (UINTN) Start) + sizeof (EFI_DEVICE_PATH_PROTOCOL);
}

EFI_DEVICE_PATH_PROTOCOL *
EntsDuplicateDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  )
/*++

Routine Description:

  Function creates a duplicate copy of an existing device path.

Arguments:

  DevPath        - A pointer to a device path data structure

Returns:

  If the memory is successfully allocated, then the contents of DevPath are copied
  to the newly allocated buffer, and a pointer to that buffer is returned.
  Otherwise, NULL is returned.

--*/
{
  EFI_DEVICE_PATH_PROTOCOL  *NewDevPath;
  UINTN                     Size;

  //
  // Compute the size
  //
  Size = EntsDevicePathSize (DevPath);

  //
  // Make a copy
  //
  NewDevPath = EntsAllocatePool (Size);
  if (NewDevPath) {
    EntsCopyMem (NewDevPath, DevPath, Size);
  }

  return NewDevPath;
}

EFI_DEVICE_PATH_PROTOCOL *
EntsUnpackDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  )
/*++

Routine Description:

  Function unpacks a device path data structure so that all the nodes of a device path
  are naturally aligned.

Arguments:

  DevPath        - A pointer to a device path data structure

Returns:

  If the memory for the device path is successfully allocated, then a pointer to the
  new device path is returned.  Otherwise, NULL is returned.

--*/
{
  EFI_DEVICE_PATH_PROTOCOL  *Src;

  EFI_DEVICE_PATH_PROTOCOL  *Dest;

  EFI_DEVICE_PATH_PROTOCOL  *NewPath;
  UINTN                     Size;

  //
  // Walk device path and round sizes to valid boundries
  //
  Src   = DevPath;
  Size  = 0;
  for (;;) {
    Size += SctDevicePathNodeLength (Src);
    Size += ALIGN_SIZE (Size);

    if (SctIsDevicePathEnd (Src)) {
      break;
    }

    Src = SctNextDevicePathNode (Src);
  }
  //
  // Allocate space for the unpacked path
  //
  NewPath = EntsAllocateZeroPool (Size);
  if (NewPath) {

    ASSERT (((UINTN) NewPath) % MIN_ALIGNMENT_SIZE == 0);

    //
    // Copy each node
    //
    Src   = DevPath;
    Dest  = NewPath;
    for (;;) {
      Size = SctDevicePathNodeLength (Src);
      EntsCopyMem (Dest, Src, Size);
      Size += ALIGN_SIZE (Size);
      SctSetDevicePathNodeLength (Dest, Size);
      Dest->Type |= EFI_DP_TYPE_UNPACKED;
      Dest = (EFI_DEVICE_PATH_PROTOCOL *) (((UINT8 *) Dest) + Size);

      if (SctIsDevicePathEnd (Src)) {
        break;
      }

      Src = SctNextDevicePathNode (Src);
    }
  }

  return NewPath;
}

CHAR16 *
EntsDevicePathToStr (
  EFI_DEVICE_PATH_PROTOCOL     *DevPath
  )
{
  ENTS_POOL_PRINT             Str;
  EFI_DEVICE_PATH_PROTOCOL    *DevPathNode;
  VOID                        (*DumpNode)(ENTS_POOL_PRINT *, VOID *);
  UINTN                       Index, NewSize;

  EntsZeroMem(&Str, sizeof(Str));

  if (DevPath == NULL) {
    goto Done;
  }

  //
  // Unpacked the device path
  //
  DevPath = EntsUnpackDevicePath(DevPath);
  ASSERT (DevPath);


  //
  // Process each device path node
  //
  DevPathNode = DevPath;
  while (!SctIsDevicePathEnd(DevPathNode)) {

    //
    // Find the handler to dump this device path node
    //

    DumpNode = NULL;
    for (Index = 0; DevPathTable[Index].Function; Index += 1) {

      if (SctDevicePathType (DevPathNode) == DevPathTable[Index].Type &&
          SctDevicePathSubType (DevPathNode) == DevPathTable[Index].SubType) {
        DumpNode = DevPathTable[Index].Function;
        break;
      }
    }

    //
    // If not found, use a generic function
    //
    if (!DumpNode) {
      DumpNode = _DevPathNodeUnknown;
    }

    //
    //  Put a path seperator in if needed
    //
    if (Str.len  &&  DumpNode != _DevPathEndInstance) {
      EntsCatPrint (&Str, L"/");
    }

    //
    // Print this node of the device path
    //
    DumpNode (&Str, DevPathNode);

    //
    // Next device path node
    //
    DevPathNode = SctNextDevicePathNode(DevPathNode);
  }

  //
  // Shrink pool used for string allocation
  //

  EntsFreePool (DevPath);
Done:
  NewSize = (Str.len + 1) * sizeof(CHAR16);
  Str.str = EntsReallocatePool (Str.str, NewSize, NewSize);
  Str.str[Str.len] = 0;
  return Str.str;
}
