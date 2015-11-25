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

  Copyright 2006 - 2015 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2013-2014, ARM Ltd. All rights reserved.
  Copyright (c) 2015, Intel Corporation. All rights reserved.

--*/

#include "SctLibInternal.h"
#include "SctLib.h"

#define ALIGN_SIZE(a)           ((a % MIN_ALIGNMENT_SIZE) ? MIN_ALIGNMENT_SIZE - (a % MIN_ALIGNMENT_SIZE) : 0)
#define MAX_DEVICE_PATH_LENGTH  0x00010000 // SIZE_64KB

typedef struct {
  VENDOR_DEVICE_PATH              DevicePath;
  UINT8                           LegacyDriveLetter;
} UNKNOWN_DEVICE_VENDOR_DEVICE_PATH;

STATIC CONST EFI_DEVICE_PATH_PROTOCOL mEndInstanceDevicePath = {
    END_DEVICE_PATH_TYPE, END_INSTANCE_DEVICE_PATH_SUBTYPE, { END_DEVICE_PATH_LENGTH, 0 }
};

STATIC CONST EFI_DEVICE_PATH_PROTOCOL mEndDevicePath = {
    END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, { END_DEVICE_PATH_LENGTH, 0 }
};

STATIC
VOID
DumpHex (
  IN UINTN        Indent,
  IN UINTN        Offset,
  IN UINTN        DataSize,
  IN VOID         *UserData
  )
{
  CHAR8           *Data, Val[50], Str[20], c;
  UINTN           Size, Index;

  Data = UserData;
  while (DataSize) {
    Size = 16;
    if (Size > DataSize) {
        Size = DataSize;
    }

    for (Index=0; Index < Size; Index += 1) {
        c = Data[Index];
        Val[Index*3+0] = mHex[c>>4];
        Val[Index*3+1] = mHex[c&0xF];
        Val[Index*3+2] = (CHAR8)((Index == 7)?'-':' ');
        Str[Index] = (CHAR8)((c < ' ' || c > 'z') ? '.' : c);
    }

    Val[Index*3] = 0;
    Str[Index] = 0;
    SctPrint (L"%*a%X: %-.48a *%a*\n", Indent, "", Offset, Val, Str);

    Data += Size;
    Offset += Size;
    DataSize -= Size;
  }
}

UINT16
SctSetDevicePathNodeLength (
  IN OUT VOID  *Node,
  IN UINTN     Length
  )
{
  UINT16 *Node16;

  ASSERT (Node != NULL);
  ASSERT ((Length >= sizeof (EFI_DEVICE_PATH_PROTOCOL)) && (Length < MAX_DEVICE_PATH_LENGTH));

  Node16 = (UINT16 *)&((EFI_DEVICE_PATH_PROTOCOL *)(Node))->Length[0];
  return *Node16 = (UINT16)Length;
}

VOID
SctSetDevicePathEndNode (
  OUT VOID  *Node
  )
{
  ASSERT (Node != NULL);
  SctCopyMem (Node, &mEndDevicePath, sizeof (mEndDevicePath));
}

/*++

Routine Description:
  Function retrieves the next device path instance from a device path data structure.

Arguments:
  DevicePath           - A pointer to a device path data structure.

  Size                 - A pointer to the size of a device path instance in bytes.

Returns:

  This function returns a pointer to the current device path instance.
  In addition, it returns the size in bytes of the current device path instance in Size,
  and a pointer to the next device path instance in DevicePath.
  If there are no more device path instances in DevicePath, then DevicePath will be set to NULL.

--*/
EFI_DEVICE_PATH_PROTOCOL *
SctDevicePathInstance (
  IN OUT EFI_DEVICE_PATH_PROTOCOL   **DevicePath,
  OUT UINTN                         *Size
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *Start, *Next, *DevPath;
  UINTN                       Count;

  DevPath = *DevicePath;
  Start = DevPath;

  if (!DevPath) {
    return NULL;
  }

  //
  // Check for end of device path type
  //

  for (Count = 0; ; Count++) {
    Next = SctNextDevicePathNode(DevPath);

    if (SctIsDevicePathEndType(DevPath)) {
      break;
    }

    if (Count > 01000) {
      //
      // BugBug: Debug code to catch bogus device paths
      //
      DEBUG((EFI_D_ERROR, "SctDevicePathInstance: DevicePath %x Size %d", *DevicePath, ((UINT8 *) DevPath) - ((UINT8 *) Start) ));
      DumpHex (0, 0, ((UINT8 *) DevPath) - ((UINT8 *) Start), Start);
      break;
    }

    DevPath = Next;
  }

  ASSERT (SctDevicePathSubType (DevPath) == END_ENTIRE_DEVICE_PATH_SUBTYPE ||
          SctDevicePathSubType (DevPath) == END_INSTANCE_DEVICE_PATH_SUBTYPE);

  //
  // Set next position
  //

  if (SctDevicePathSubType (DevPath) == END_ENTIRE_DEVICE_PATH_SUBTYPE) {
    Next = NULL;
  }

  *DevicePath = Next;

  //
  // Return size and start of device path instance
  //
  *Size = ((UINT8 *) DevPath) - ((UINT8 *) Start) + sizeof(EFI_DEVICE_PATH_PROTOCOL);
  return Start;
}

/*++

Routine Description:
  Function is used to determine the number of device path instances that exist in a device path.

Arguments:
  DevicePath           - A pointer to a device path data structure.

Returns:

  This function counts and returns the number of device path instances in DevicePath.

--*/
UINTN
SctDevicePathInstanceCount (
  IN EFI_DEVICE_PATH_PROTOCOL      *DevicePath
  )
{
  UINTN       Count, Size;

  Count = 0;
  while (SctDevicePathInstance (&DevicePath, &Size)) {
    Count += 1;
  }
  return Count;
}

/*++

Routine Description:
  Function retrieves the device path for the specified handle.

Arguments:
  Handle           - Handle of the device

Returns:

  If Handle is valid, then a pointer to the device path is returned.
  If Handle is not valid, then NULL is returned.

--*/
EFI_DEVICE_PATH_PROTOCOL *
SctDevicePathFromHandle (
  IN EFI_HANDLE       Handle
  )
{
  EFI_STATUS                  Status;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath;

  Status = tBS->HandleProtocol (
                 Handle,
                 &gEfiDevicePathProtocolGuid,
                 (VOID*)&DevicePath
                 );

  if (EFI_ERROR(Status)) {
    DevicePath = NULL;
  }

  return DevicePath;
}

UINT16 *
SctDevicePathStrFromProtocol (
  IN VOID        *Protocol,
  IN EFI_GUID    *Guid
  )
{
  EFI_STATUS                          Status;
  UINTN                                HandleNum;
  EFI_HANDLE                          *HandleBuffer;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  UINTN                               Index;
  UINT16                              *Str;
  VOID                                *Interface;
  //BOOLEAN                             Found;

  //Found = FALSE;
  Str = NULL;
  HandleNum    = 0;
  Status      = SctLocateHandle(
                  ByProtocol,
                  Guid,
                  NULL,
                  &HandleNum,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status) || HandleNum == 0) {
    return NULL;
  }

  for ( Index = 0 ; Index < HandleNum ; Index ++ ) {
    Status = tBS->HandleProtocol (HandleBuffer[Index], Guid, &Interface);
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (Interface == Protocol) {
      Status = tBS->HandleProtocol (HandleBuffer[Index], &gEfiDevicePathProtocolGuid, (VOID**)&DevicePath);
      if (!EFI_ERROR(Status)) {
        //Found = TRUE;
        Str = SctDevicePathToStr(DevicePath);
      }
      break;
    }
  }

  return Str;
}

/*++

Routine Description:
  Function is used to append a device path to all the instances in another device path.

Arguments:
  Src1           - A pointer to a device path data structure.

  Src2           - A pointer to a device path data structure.

Returns:

  A pointer to the new device path is returned.
  NULL is returned if space for the new device path could not be allocated from pool.
  It is up to the caller to free the memory used by Src1 and Src2 if they are no longer needed.

  Src1 may have multiple "instances" and each instance is appended
  Src2 is appended to each instance is Src1.  (E.g., it's possible
  to append a new instance to the complete device path by passing
  it in Src2)

--*/
EFI_DEVICE_PATH_PROTOCOL *
SctAppendDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL  *Src2
  )
{
  UINTN                       Src1Size, Src1Inst, Src2Size, Size;
  EFI_DEVICE_PATH_PROTOCOL    *Dst, *Inst;
  UINT8                       *DstPos;

  //
  // If both Src1 and Src2 are NULL end-of-device-path is returned.
  //
  if ((Src1 == NULL) && (Src2 == NULL)) {
    Dst = (EFI_DEVICE_PATH_PROTOCOL *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
    SctSetDevicePathEndNode (Dst);
    return Dst;
  }

  //
  // If there's only 1 path, just duplicate it
  //

  if (!Src1) {
    ASSERT (!IsDevicePathUnpacked (Src2));
    return SctDuplicateDevicePath (Src2);
  }

  if (!Src2) {
    ASSERT (!IsDevicePathUnpacked (Src1));
    return SctDuplicateDevicePath (Src1);
  }

  //
  // Verify we're not working with unpacked paths
  //

//    ASSERT (!IsDevicePathUnpacked (Src1));
//    ASSERT (!IsDevicePathUnpacked (Src2));

  //
  // Append Src2 to every instance in Src1
  //

  Src1Size = SctDevicePathSize(Src1);
  Src1Inst = SctDevicePathInstanceCount(Src1);
  Src2Size = SctDevicePathSize(Src2);
  Size = Src1Size * Src1Inst + Src2Size;
  Size -= Src1Inst * sizeof(EFI_DEVICE_PATH_PROTOCOL);

  Dst = SctAllocatePool (Size);
  if (Dst) {
    DstPos = (UINT8 *) Dst;

    //
    // Copy all device path instances
    //
    Inst = SctDevicePathInstance (&Src1, &Size);
    while (Inst) {

      SctCopyMem (DstPos, Inst, Size);
      DstPos += Size - sizeof(EFI_DEVICE_PATH_PROTOCOL);

      SctCopyMem (DstPos, (VOID *) Src2, Src2Size);
      DstPos += Src2Size - sizeof(EFI_DEVICE_PATH_PROTOCOL);

      SctCopyMem (
        DstPos,
        &mEndInstanceDevicePath,
        sizeof(EFI_DEVICE_PATH_PROTOCOL)
        );
      DstPos += sizeof(EFI_DEVICE_PATH_PROTOCOL);

      Inst = SctDevicePathInstance (&Src1, &Size);
    }

    //
    // Change last end marker
    //
    DstPos -= sizeof(EFI_DEVICE_PATH_PROTOCOL);
    SctCopyMem (DstPos, &mEndDevicePath, sizeof(EFI_DEVICE_PATH_PROTOCOL));
  }

  return Dst;
}

/*++

Routine Description:
  Function is used to append a device path node to all the instances in another device path.

Arguments:
  Src1           - A pointer to a device path data structure.

  Src2           - A pointer to a device path data structure.

Returns:

  This function returns a pointer to the new device path.
  If there is not enough temporary pool memory available to complete this function,
  then NULL is returned.

  Src1 may have multiple "instances" and each instance is appended
  Src2 is a signal device path node (without a terminator) that is
  appended to each instance is Src1.

--*/
EFI_DEVICE_PATH_PROTOCOL *
SctAppendDevicePathNode (
  IN EFI_DEVICE_PATH_PROTOCOL  *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL  *Src2
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *Temp, *Eop;
  UINTN                       Length;

  //
  // Build a Src2 that has a terminator on it
  //
  Length = SctDevicePathNodeLength(Src2);
  Temp = SctAllocatePool (Length + sizeof(EFI_DEVICE_PATH_PROTOCOL));
  if (!Temp) {
    return NULL;
  }

  SctCopyMem (Temp, Src2, Length);
  Eop = SctNextDevicePathNode(Temp);
  SctSetDevicePathEndNode(Eop);

  //
  // Append device paths
  //

  Src1 = SctAppendDevicePath (Src1, Temp);
  SctFreePool (Temp);
  return Src1;
}

/*++

Routine Description:
  Function returns the size of a device path in bytes.

Arguments:
  DevPath        - A pointer to a device path data structure

Returns:

  Size is returned.

--*/
UINTN
SctDevicePathSize (
    IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
    )
{
  EFI_DEVICE_PATH_PROTOCOL     *Start;

  //
  // Search for the end of the device path structure
  //

  Start = DevPath;
  while (!SctIsDevicePathEnd(DevPath)) {
    DevPath = SctNextDevicePathNode(DevPath);
  }

  //
  // Compute the size
  //
  return ((UINTN) DevPath - (UINTN) Start) + sizeof(EFI_DEVICE_PATH_PROTOCOL);
}

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
EFI_DEVICE_PATH_PROTOCOL *
SctDuplicateDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *NewDevPath;
  UINTN                       Size;


  //
  // Compute the size
  //
  Size = SctDevicePathSize (DevPath);

  //
  // Make a copy
  //
  NewDevPath = SctAllocatePool (Size);
  if (NewDevPath) {
    SctCopyMem (NewDevPath, DevPath, Size);
  }
  return NewDevPath;
}

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
EFI_DEVICE_PATH_PROTOCOL *
SctUnpackDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *Src, *Dest, *NewPath;
  UINTN                       Size;

  //
  // Walk device path and round sizes to valid boundries
  //

  Src = DevPath;
  Size = 0;
  for (; ;) {
    Size += SctDevicePathNodeLength(Src);
    Size += ALIGN_SIZE (Size);

    if (SctIsDevicePathEnd(Src)) {
      break;
    }

    Src = SctNextDevicePathNode(Src);
  }


  //
  // Allocate space for the unpacked path
  //

  NewPath = SctAllocateZeroPool (Size);
  if (NewPath) {

    ASSERT (((UINTN)NewPath) % MIN_ALIGNMENT_SIZE == 0);

    //
    // Copy each node
    //
    Src = DevPath;
    Dest = NewPath;
    for (; ;) {
      Size = SctDevicePathNodeLength(Src);
      SctCopyMem (Dest, Src, Size);
      Size += ALIGN_SIZE(Size);
      SctSetDevicePathNodeLength (Dest, Size);
      Dest->Type |= EFI_DP_TYPE_UNPACKED;
      Dest = (EFI_DEVICE_PATH_PROTOCOL *) (((UINT8 *) Dest) + Size);

      if (SctIsDevicePathEnd(Src)) {
        break;
      }

      Src = SctNextDevicePathNode(Src);
    }
  }

  return NewPath;
}

STATIC
VOID
_DevPathPci (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    PCI_DEVICE_PATH         *Pci;

    Pci = DevPath;
    SctCatPrint(Str, L"Pci(%x|%x)", Pci->Device, Pci->Function);
}

STATIC
VOID
_DevPathPccard (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    PCCARD_DEVICE_PATH      *Pccard;

    Pccard = DevPath;
    SctCatPrint(Str, L"Pcmcia(Function%x)", Pccard->FunctionNumber);
}

STATIC
VOID
_DevPathMemMap (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    MEMMAP_DEVICE_PATH      *MemMap;

    MemMap = DevPath;
    SctCatPrint(Str, L"MemMap(%d:%.lx-%.lx)",
        MemMap->MemoryType,
        MemMap->StartingAddress,
        MemMap->EndingAddress
        );
}

STATIC
VOID
_DevPathController (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    CONTROLLER_DEVICE_PATH  *Controller;

    Controller = DevPath;
    SctCatPrint(Str, L"Ctrl(%d)",
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
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    VENDOR_DEVICE_PATH                  *Vendor;
    CHAR16                              *Type;
    UNKNOWN_DEVICE_VENDOR_DEVICE_PATH   *UnknownDevPath;

    Vendor = DevPath;
    switch (SctDevicePathType (&Vendor->Header)) {
    case HARDWARE_DEVICE_PATH:  Type = L"Hw";        break;
    case MESSAGING_DEVICE_PATH: Type = L"Msg";       break;
    case MEDIA_DEVICE_PATH:     Type = L"Media";     break;
    default:                    Type = L"?";         break;
    }

    SctCatPrint(Str, L"Ven%s(%g", Type, &Vendor->Guid);
    if (SctCompareGuid (&Vendor->Guid, &mEfiUnknownDeviceGuid) == 0) {
        //
        // GUID used by EFI to enumerate an EDD 1.1 device
        //
        UnknownDevPath = (UNKNOWN_DEVICE_VENDOR_DEVICE_PATH *)Vendor;
        SctCatPrint(Str, L":%02x)", UnknownDevPath->LegacyDriveLetter);
    } else {
        SctCatPrint(Str, L")");
    }
}

STATIC
VOID
_DevPathAcpi (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    ACPI_HID_DEVICE_PATH        *Acpi;

    Acpi = DevPath;
    if ((Acpi->HID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
        SctCatPrint(Str, L"Acpi(PNP%04x,%x)", EISA_ID_TO_NUM (Acpi->HID), Acpi->UID);
    } else {
        SctCatPrint(Str, L"Acpi(%08x,%x)", Acpi->HID, Acpi->UID);
    }
}

STATIC
VOID
_DevPathExtendedAcpi (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    ACPI_EXTENDED_HID_DEVICE_PATH   *ExtendedAcpi;
    UINTN                           HIDStrIndex;
    UINTN                           UIDStrIndex;
    UINTN                           CIDStrIndex;
    UINTN                           Index;
    UINTN                           Length;
    UINTN                           Anchor;
    CHAR8                           *AsChar8Array;

    ASSERT (Str != NULL);
    ASSERT (DevPath != NULL);

    ExtendedAcpi = DevPath;

    Length = SctDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) ExtendedAcpi);
    ASSERT (Length >= 19);

    AsChar8Array = (CHAR8 *) ExtendedAcpi;
    HIDStrIndex  = 0;
    UIDStrIndex  = 0;
    CIDStrIndex  = 0;

    //
    // Find the HIDSTR's location
    //
    Anchor = 16;
    for (Index = Anchor; (Index < Length) && (AsChar8Array[Index] != 0); Index++) {
        ;
    }
    if (Index > Anchor) {
        HIDStrIndex = Anchor;
    }

    //
    // Find the UIDSTR's location
    Anchor = Index + 1;
    for (Index = Anchor; (Index < Length) && (AsChar8Array[Index] != 0); Index++) {
        ;
    }
    if (Index > Anchor) {
        UIDStrIndex = Anchor;
    }

    //
    // Find the CIDSTR's location
    //
    Anchor = Index + 1;
    for (Index = Anchor; (Index < Length) && (AsChar8Array[Index] != 0); Index++) {
        ;
    }
    if (Index > Anchor) {
        CIDStrIndex = Anchor;
    }

    //
    // Print out the device path string
    //
    SctCatPrint (Str, L"Acpi(");
    if (HIDStrIndex != 0) {
        SctCatPrint (Str, L"%a,", AsChar8Array + HIDStrIndex);
    } else {
        if ((ExtendedAcpi->HID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
            SctCatPrint (Str, L"PNP%04x,", EISA_ID_TO_NUM (ExtendedAcpi->HID));
        } else {
            SctCatPrint (Str, L"%08x,", ExtendedAcpi->HID);
        }
    }

    if (CIDStrIndex != 0) {
        SctCatPrint (Str, L"%a,", AsChar8Array + CIDStrIndex);
    } else {
        if ((ExtendedAcpi->CID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
            SctCatPrint (Str, L"PNP%04x,", EISA_ID_TO_NUM (ExtendedAcpi->CID));
        } else {
            SctCatPrint (Str, L"%08x,", ExtendedAcpi->CID);
        }
    }

    if (UIDStrIndex != 0) {
        SctCatPrint (Str, L"%a)", AsChar8Array + UIDStrIndex);
    } else {
        SctCatPrint (Str, L"%x)", ExtendedAcpi->UID);
    }
}


STATIC
VOID
_DevPathAtapi (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    ATAPI_DEVICE_PATH       *Atapi;

    Atapi = DevPath;
    SctCatPrint(Str, L"Ata(%s,%s)",
        Atapi->PrimarySecondary ? L"Secondary" : L"Primary",
        Atapi->SlaveMaster ? L"Slave" : L"Master"
        );
}

STATIC
VOID
_DevPathScsi (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    SCSI_DEVICE_PATH        *Scsi;

    Scsi = DevPath;
    SctCatPrint(Str, L"Scsi(Pun%x,Lun%x)", Scsi->Pun, Scsi->Lun);
}

STATIC
VOID
_DevPathFibre (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    FIBRECHANNEL_DEVICE_PATH    *Fibre;

    Fibre = DevPath;
    SctCatPrint(Str, L"Fibre(Wwn%lx,Lun%x)", Fibre->WWN, Fibre->Lun);
}

STATIC
VOID
_DevPath1394 (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    F1394_DEVICE_PATH       *F1394;

    F1394 = DevPath;
    SctCatPrint(Str, L"1394(%g)", &F1394->Guid);
}

STATIC
VOID
_DevPathUsb (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    USB_DEVICE_PATH         *Usb;

    Usb = DevPath;
    SctCatPrint(Str, L"Usb(%x, %x)", Usb->ParentPortNumber, Usb->InterfaceNumber);
}

STATIC
VOID
_DevPathUsbClass (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    // tbd:
    USB_CLASS_DEVICE_PATH         *UsbClass;

    UsbClass = DevPath;
    SctCatPrint(Str, L"Usb Class(%x, %x, %x, %x, %x)",
              UsbClass->VendorId,
              UsbClass->ProductId,
              UsbClass->DeviceClass,
              UsbClass->DeviceSubClass,
              UsbClass->DeviceProtocol);
}

STATIC
VOID
_DevPathI2O (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    I2O_DEVICE_PATH         *I2O;

    I2O = DevPath;
    SctCatPrint(Str, L"I2O(%x)", I2O->Tid);
}

STATIC
VOID
_DevPathMacAddr (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    MAC_ADDR_DEVICE_PATH    *MAC;
    UINTN                   HwAddressSize;
    UINTN                   Index;

    MAC = DevPath;

    HwAddressSize = sizeof(EFI_MAC_ADDRESS);
    if (MAC->IfType == 0x01 || MAC->IfType == 0x00) {
        HwAddressSize = 6;
    }

    SctCatPrint(Str, L"Mac(");

    for(Index = 0; Index < HwAddressSize; Index++) {
        SctCatPrint(Str, L"%02x",MAC->MacAddress.Addr[Index]);
    }
    SctCatPrint(Str, L")");
}

STATIC
VOID
_DevPathIPv4 (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    IPv4_DEVICE_PATH     *IP;

    IP = DevPath;
    SctCatPrint(Str, L"IPv4(%d.%d.%d.%d:%d)",IP->RemoteIpAddress.Addr[0],
                                       IP->RemoteIpAddress.Addr[1],
                                       IP->RemoteIpAddress.Addr[2],
                                       IP->RemoteIpAddress.Addr[3],
                                       IP->RemotePort);
}

STATIC
VOID
_DevPathIPv6 (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    SctCatPrint(Str, L"IP-v6(not-done)");
}

STATIC
VOID
_DevPathInfiniBand (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    SctCatPrint(Str, L"InfiniBand(not-done)");
}

STATIC
VOID
_DevPathUart (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    UART_DEVICE_PATH  *Uart;
    CHAR8             Parity;

    Uart = DevPath;
    switch (Uart->Parity) {
        case 0  : Parity = 'D'; break;
        case 1  : Parity = 'N'; break;
        case 2  : Parity = 'E'; break;
        case 3  : Parity = 'O'; break;
        case 4  : Parity = 'M'; break;
        case 5  : Parity = 'S'; break;
        default : Parity = 'x'; break;
    }

    if (Uart->BaudRate == 0) {
        SctCatPrint(Str, L"Uart(DEFAULT %c",Parity);
    } else {
        SctCatPrint(Str, L"Uart(%d %c",Uart->BaudRate,Parity);
    }

    if (Uart->DataBits == 0) {
        SctCatPrint(Str, L"D");
    } else {
        SctCatPrint(Str, L"%d",Uart->DataBits);
    }

    switch (Uart->StopBits) {
        case 0  : SctCatPrint(Str, L"D)");   break;
        case 1  : SctCatPrint(Str, L"1)");   break;
        case 2  : SctCatPrint(Str, L"1.5)"); break;
        case 3  : SctCatPrint(Str, L"2)");   break;
        default : SctCatPrint(Str, L"x)");   break;
    }
}

STATIC
VOID
_DevPathHardDrive (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    HARDDRIVE_DEVICE_PATH   *Hd;

    Hd = DevPath;
    switch (Hd->SignatureType) {
        case SIGNATURE_TYPE_MBR:
            SctCatPrint(Str, L"HD(Part%d,Sig%08x)",
                Hd->PartitionNumber,
                *((UINT32 *)(&(Hd->Signature[0])))
                );
            break;
        case SIGNATURE_TYPE_GUID:
            SctCatPrint(Str, L"HD(Part%d,Sig%g)",
                Hd->PartitionNumber,
                (EFI_GUID *) &(Hd->Signature[0])
                );
            break;
        default:
            SctCatPrint(Str, L"HD(Part%d,MBRType=%02x,SigType=%02x)",
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
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    CDROM_DEVICE_PATH       *Cd;

    Cd = DevPath;
    SctCatPrint(Str, L"CDROM(Entry%x)", Cd->BootEntry);
}

STATIC
VOID
_DevPathFilePath (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    FILEPATH_DEVICE_PATH    *Fp;

    Fp = DevPath;
    SctCatPrint(Str, L"%s", Fp->PathName);
}

STATIC
VOID
_DevPathMediaProtocol (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    MEDIA_PROTOCOL_DEVICE_PATH  *MediaProt;

    MediaProt = DevPath;
    SctCatPrint(Str, L"%g", &MediaProt->Protocol);
}

#if (EFI_SPECIFICATION_VERSION < 0x00020000)
VOID
_DevPathFvFilePath (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    MEDIA_FW_VOL_FILEPATH_DEVICE_PATH   *FvFilePath;

    FvFilePath = DevPath;
    SctCatPrint(Str, L"%g", &FvFilePath->NameGuid);
}
#endif

VOID
_DevPathBssBss (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    BBS_BBS_DEVICE_PATH     *Bss;
    CHAR16                  *Type;

    Bss = DevPath;
    switch (Bss->DeviceType) {
    case BBS_TYPE_FLOPPY:               Type = L"Floppy";       break;
    case BBS_TYPE_HARDDRIVE:            Type = L"Harddrive";    break;
    case BBS_TYPE_CDROM:                Type = L"CDROM";        break;
    case BBS_TYPE_PCMCIA:               Type = L"PCMCIA";       break;
    case BBS_TYPE_USB:                  Type = L"Usb";          break;
    case BBS_TYPE_EMBEDDED_NETWORK:     Type = L"Net";          break;
    default:                            Type = L"?";            break;
    }

    SctCatPrint(Str, L"Bss-%s(%a)", Type, Bss->String);
}

STATIC
VOID
_DevPathEndInstance (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    SctCatPrint(Str, L",");
}

STATIC
VOID
_DevPathNodeUnknown (
    IN OUT SCT_POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    SctCatPrint(Str, L"?");
}

STATIC CONST
struct {
  UINT8   Type;
  UINT8   SubType;
  VOID    (*Function)(SCT_POOL_PRINT *, VOID *);
} mDevPathTable[] = {
  { HARDWARE_DEVICE_PATH,   HW_PCI_DP,                        _DevPathPci },
  { HARDWARE_DEVICE_PATH,   HW_PCCARD_DP,                     _DevPathPccard },
  { HARDWARE_DEVICE_PATH,   HW_MEMMAP_DP,                     _DevPathMemMap },
  { HARDWARE_DEVICE_PATH,   HW_VENDOR_DP,                     _DevPathVendor },
  { HARDWARE_DEVICE_PATH,   HW_CONTROLLER_DP,                 _DevPathController },
  { ACPI_DEVICE_PATH,       ACPI_DP,                          _DevPathAcpi },
  { ACPI_DEVICE_PATH,       ACPI_EXTENDED_DP,                 _DevPathExtendedAcpi },
  { MESSAGING_DEVICE_PATH,  MSG_ATAPI_DP,                     _DevPathAtapi },
  { MESSAGING_DEVICE_PATH,  MSG_SCSI_DP,                      _DevPathScsi },
  { MESSAGING_DEVICE_PATH,  MSG_FIBRECHANNEL_DP,              _DevPathFibre },
  { MESSAGING_DEVICE_PATH,  MSG_1394_DP,                      _DevPath1394 },
  { MESSAGING_DEVICE_PATH,  MSG_USB_DP,                       _DevPathUsb },
  { MESSAGING_DEVICE_PATH,  MSG_USB_CLASS_DP,                 _DevPathUsbClass },
  { MESSAGING_DEVICE_PATH,  MSG_I2O_DP,                       _DevPathI2O },
  { MESSAGING_DEVICE_PATH,  MSG_MAC_ADDR_DP,                  _DevPathMacAddr },
  { MESSAGING_DEVICE_PATH,  MSG_IPv4_DP,                      _DevPathIPv4 },
  { MESSAGING_DEVICE_PATH,  MSG_IPv6_DP,                      _DevPathIPv6 },
  { MESSAGING_DEVICE_PATH,  MSG_INFINIBAND_DP,                _DevPathInfiniBand },
  { MESSAGING_DEVICE_PATH,  MSG_UART_DP,                      _DevPathUart },
  { MESSAGING_DEVICE_PATH,  MSG_VENDOR_DP,                    _DevPathVendor },
  { MEDIA_DEVICE_PATH,      MEDIA_HARDDRIVE_DP,               _DevPathHardDrive },
  { MEDIA_DEVICE_PATH,      MEDIA_CDROM_DP,                   _DevPathCDROM },
  { MEDIA_DEVICE_PATH,      MEDIA_VENDOR_DP,                  _DevPathVendor },
  { MEDIA_DEVICE_PATH,      MEDIA_FILEPATH_DP,                _DevPathFilePath },
  { MEDIA_DEVICE_PATH,      MEDIA_PROTOCOL_DP,                _DevPathMediaProtocol },
#if (EFI_SPECIFICATION_VERSION < 0x00020000)
  { MEDIA_DEVICE_PATH,      MEDIA_FV_FILEPATH_DP,             _DevPathFvFilePath },
#endif
  { BBS_DEVICE_PATH,        BBS_BBS_DP,                       _DevPathBssBss },
  { END_DEVICE_PATH_TYPE,   END_INSTANCE_DEVICE_PATH_SUBTYPE, _DevPathEndInstance },
  { 0,                      0,                          NULL }
};

/*++

    Turns the Device Path into a printable string.  Allcoates
    the string from pool.  The caller must FreePool the returned
    string.

--*/
CHAR16 *
SctDevicePathToStr (
  EFI_DEVICE_PATH_PROTOCOL     *DevPath
  )
{
  SCT_POOL_PRINT                  Str;
  EFI_DEVICE_PATH_PROTOCOL    *DevPathNode;
  VOID                        (*DumpNode)(SCT_POOL_PRINT *, VOID *);
  UINTN                       Index, NewSize;

  SctZeroMem (&Str, sizeof(Str));

  if (DevPath == NULL) {
    goto Done;
  }

  //
  // Unpacked the device path
  //
  DevPath = SctUnpackDevicePath(DevPath);
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
    for (Index = 0; mDevPathTable[Index].Function; Index += 1) {

      if (SctDevicePathType (DevPathNode) == mDevPathTable[Index].Type &&
          SctDevicePathSubType (DevPathNode) == mDevPathTable[Index].SubType) {
        DumpNode = mDevPathTable[Index].Function;
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
      SctCatPrint (&Str, L"/");
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

  SctFreePool (DevPath);
Done:
  NewSize = (Str.len + 1) * sizeof(CHAR16);
  Str.str = SctReallocatePool (Str.str, NewSize, NewSize);
  Str.str[Str.len] = 0;
  return Str.str;
}

/*++

Routine Description:
  Function compares a device path data structure to that of all the nodes of a
  second device path instance.

Arguments:
  Multi        - A pointer to a multi-instance device path data structure.

  Single       - A pointer to a single-instance device path data structure.

Returns:

  The function returns TRUE if the Single is contained within Multi.
  Otherwise, FALSE is returned.

--*/
BOOLEAN
SctMatchDevicePaths (
  IN  EFI_DEVICE_PATH_PROTOCOL *Multi,
  IN  EFI_DEVICE_PATH_PROTOCOL *Single
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath, *DevicePathInst;
  UINTN                       Size;

  if (!Multi || !Single) {
    return FALSE;
  }

  DevicePath = Multi;
  DevicePathInst = SctDevicePathInstance (&DevicePath, &Size);
  while (DevicePathInst) {
    if (SctCompareMem (Single, DevicePathInst, Size - sizeof(EFI_DEVICE_PATH_PROTOCOL)) == 0) {
      return TRUE;
    }
    DevicePathInst = SctDevicePathInstance (&DevicePath, &Size);
  }
  return FALSE;
}

/*++

Routine Description:
  Function allocates a device path for a file and appends it to an existing device path.

Arguments:
  Device         - A pointer to a device handle.

  FileName       - A pointer to a Null-terminated Unicode string.

Returns:

  If Device is not a valid device handle, then a device path for the file specified
  by FileName is allocated and returned.

  Results are allocated from pool.  The caller must FreePool the resulting device path
  structure

--*/
EFI_DEVICE_PATH_PROTOCOL *
SctFileDevicePath (
  IN EFI_HANDLE       Device  OPTIONAL,
  IN CHAR16           *FileName
  )
{
  UINTN                       Size;
  FILEPATH_DEVICE_PATH        *FilePath;
  EFI_DEVICE_PATH_PROTOCOL    *Eop, *DevicePath;

  Size = SctStrSize (FileName);
  FilePath = SctAllocateZeroPool (Size + SIZE_OF_FILEPATH_DEVICE_PATH + sizeof(EFI_DEVICE_PATH_PROTOCOL));
  DevicePath = NULL;

  if (FilePath) {

    //
    // Build a file path
    //
    FilePath->Header.Type = MEDIA_DEVICE_PATH;
    FilePath->Header.SubType = MEDIA_FILEPATH_DP;
    SctSetDevicePathNodeLength (&FilePath->Header, Size + SIZE_OF_FILEPATH_DEVICE_PATH);
    SctCopyMem (FilePath->PathName, FileName, Size);
    Eop = SctNextDevicePathNode(&FilePath->Header);
    SctSetDevicePathEndNode(Eop);

    //
    // Append file path to device's device path
    //
    DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) FilePath;
    if (Device) {
      DevicePath = SctAppendDevicePath (
                        SctDevicePathFromHandle(Device),
                        DevicePath
                        );
      SctFreePool (FilePath);
    }
  }

  return DevicePath;
}

/*++

Routine Description:
  Function retrieves a protocol interface for a device.

Arguments:
  Protocol     - The published unique identifier of the protocol.

  FilePath     - A pointer to a device path data structure.

  Interface    - Supplies and address where a pointer to the requested
                 Protocol interface is returned.

Returns:

  If a match is found, then the protocol interface of that device is
  returned in Interface.  Otherwise, Interface is set to NULL.

--*/
EFI_STATUS
SctDevicePathToInterface (
  IN EFI_GUID                   *Protocol,
  IN EFI_DEVICE_PATH_PROTOCOL   *FilePath,
  OUT VOID                      **Interface
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              Device;

  Status = tBS->LocateDevicePath (
                 Protocol,
                 &FilePath,
                 &Device
                 );

  if (!EFI_ERROR(Status)) {

    //
    // If we didn't get a direct match return not found
    //
    Status = EFI_NOT_FOUND;

    if (SctIsDevicePathEnd(FilePath)) {

      //
      // It was a direct match, lookup the protocol interface
      //
      Status = tBS->HandleProtocol (
                     Device,
                     Protocol,
                     Interface
                     );
      }
  }

  //
  // If there was an error, do not return an interface
  //

  if (EFI_ERROR(Status)) {
    *Interface = NULL;
  }

  return Status;
}
