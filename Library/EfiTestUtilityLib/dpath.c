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

  dpath.c

Abstract:

  MBR & Device Path functions

--*/

#include "lib.h"

#define ALIGN_SIZE(a)   ((a % MIN_ALIGNMENT_SIZE) ? MIN_ALIGNMENT_SIZE - (a % MIN_ALIGNMENT_SIZE) : 0)
#define MAX_FILE_PATH   1024


EFI_DEVICE_PATH_PROTOCOL *
DevicePathFromHandle (
  IN EFI_HANDLE       Handle
  )
/*++

Routine Description:
  Function retrieves the device path for the specified handle.

Arguments:
  Handle           - Handle of the device

Returns:

  If Handle is valid, then a pointer to the device path is returned.
  If Handle is not valid, then NULL is returned.

--*/
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


EFI_DEVICE_PATH_PROTOCOL *
DevicePathInstance (
  IN OUT EFI_DEVICE_PATH_PROTOCOL   **DevicePath,
  OUT UINTN                         *Size
  )
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
    Next = NextDevicePathNode(DevPath);

    if (IsDevicePathEndType(DevPath)) {
      break;
    }

    if (Count > 01000) {
      //
      // BugBug: Debug code to catch bogus device paths
      //
      DEBUG((EFI_D_ERROR, "DevicePathInstance: DevicePath %x Size %d", *DevicePath, ((UINT8 *) DevPath) - ((UINT8 *) Start) ));
      DumpHex (0, 0, ((UINT8 *) DevPath) - ((UINT8 *) Start), Start);
      break;
    }

    DevPath = Next;
  }

  ASSERT (DevicePathSubType(DevPath) == END_ENTIRE_DEVICE_PATH_SUBTYPE ||
          DevicePathSubType(DevPath) == END_INSTANCE_DEVICE_PATH_SUBTYPE);

  //
  // Set next position
  //

  if (DevicePathSubType(DevPath) == END_ENTIRE_DEVICE_PATH_SUBTYPE) {
    Next = NULL;
  }

  *DevicePath = Next;

  //
  // Return size and start of device path instance
  //
  *Size = ((UINT8 *) DevPath) - ((UINT8 *) Start) + sizeof(EFI_DEVICE_PATH_PROTOCOL);
  return Start;
}


UINTN
DevicePathInstanceCount (
  IN EFI_DEVICE_PATH_PROTOCOL      *DevicePath
  )
/*++

Routine Description:
  Function is used to determine the number of device path instances that exist in a device path.

Arguments:
  DevicePath           - A pointer to a device path data structure.

Returns:

  This function counts and returns the number of device path instances in DevicePath.

--*/
{
  UINTN       Count, Size;

  Count = 0;
  while (DevicePathInstance(&DevicePath, &Size)) {
    Count += 1;
  }
  return Count;
}


EFI_DEVICE_PATH_PROTOCOL *
AppendDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL  *Src2
  )
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
{
  UINTN                       Src1Size, Src1Inst, Src2Size, Size;
  EFI_DEVICE_PATH_PROTOCOL    *Dst, *Inst;
  UINT8                       *DstPos;

  //
  // If both Src1 and Src2 are NULL end-of-device-path is returned. 
  //
  if ((Src1 == NULL) && (Src2 == NULL)) {
    Dst = (EFI_DEVICE_PATH_PROTOCOL *) AllocatePool (END_DEVICE_PATH_LENGTH);
    SetDevicePathEndNode (Dst);
    return Dst;
  }

  //
  // If there's only 1 path, just duplicate it
  //

  if (!Src1) {
    ASSERT (!IsDevicePathUnpacked (Src2));
    return DuplicateDevicePath (Src2);
  }

  if (!Src2) {
    ASSERT (!IsDevicePathUnpacked (Src1));
    return DuplicateDevicePath (Src1);
  }

  //
  // Verify we're not working with unpacked paths
  //

//    ASSERT (!IsDevicePathUnpacked (Src1));
//    ASSERT (!IsDevicePathUnpacked (Src2));

  //
  // Append Src2 to every instance in Src1
  //

  Src1Size = DevicePathSize(Src1);
  Src1Inst = DevicePathInstanceCount(Src1);
  Src2Size = DevicePathSize(Src2);
  Size = Src1Size * Src1Inst + Src2Size;
  Size -= Src1Inst * sizeof(EFI_DEVICE_PATH_PROTOCOL);

  Dst = AllocatePool (Size);
  if (Dst) {
    DstPos = (UINT8 *) Dst;

    //
    // Copy all device path instances
    //
    Inst = DevicePathInstance (&Src1, &Size);
    while (Inst) {

      CopyMem(DstPos, Inst, Size);
      DstPos += Size - sizeof(EFI_DEVICE_PATH_PROTOCOL);

      CopyMem(DstPos, Src2, Src2Size);
      DstPos += Src2Size - sizeof(EFI_DEVICE_PATH_PROTOCOL);

      CopyMem(DstPos, EndInstanceDevicePath, sizeof(EFI_DEVICE_PATH_PROTOCOL));
      DstPos += sizeof(EFI_DEVICE_PATH_PROTOCOL);

      Inst = DevicePathInstance (&Src1, &Size);
    }

    //
    // Change last end marker
    //
    DstPos -= sizeof(EFI_DEVICE_PATH_PROTOCOL);
    CopyMem(DstPos, EndDevicePath, sizeof(EFI_DEVICE_PATH_PROTOCOL));
  }

  return Dst;
}


EFI_DEVICE_PATH_PROTOCOL *
AppendDevicePathNode (
  IN EFI_DEVICE_PATH_PROTOCOL  *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL  *Src2
  )
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
{
  EFI_DEVICE_PATH_PROTOCOL    *Temp, *Eop;
  UINTN                       Length;

  //
  // Build a Src2 that has a terminator on it
  //
  Length = DevicePathNodeLength(Src2);
  Temp = AllocatePool (Length + sizeof(EFI_DEVICE_PATH_PROTOCOL));
  if (!Temp) {
    return NULL;
  }

  CopyMem (Temp, Src2, Length);
  Eop = NextDevicePathNode(Temp);
  SetDevicePathEndNode(Eop);

  //
  // Append device paths
  //

  Src1 = AppendDevicePath (Src1, Temp);
  FreePool (Temp);
  return Src1;
}


EFI_DEVICE_PATH_PROTOCOL *
FileDevicePath (
  IN EFI_HANDLE       Device  OPTIONAL,
  IN CHAR16           *FileName
  )
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
{
  UINTN                       Size;
  FILEPATH_DEVICE_PATH        *FilePath;
  EFI_DEVICE_PATH_PROTOCOL    *Eop, *DevicePath;

  Size = StrSize(FileName);
  FilePath = AllocateZeroPool (Size + SIZE_OF_FILEPATH_DEVICE_PATH + sizeof(EFI_DEVICE_PATH_PROTOCOL));
  DevicePath = NULL;

  if (FilePath) {

    //
    // Build a file path
    //
    FilePath->Header.Type = MEDIA_DEVICE_PATH;
    FilePath->Header.SubType = MEDIA_FILEPATH_DP;
    SetDevicePathNodeLength (&FilePath->Header, Size + SIZE_OF_FILEPATH_DEVICE_PATH);
    CopyMem (FilePath->PathName, FileName, Size);
    Eop = NextDevicePathNode(&FilePath->Header);
    SetDevicePathEndNode(Eop);

    //
    // Append file path to device's device path
    //
    DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) FilePath;
    if (Device) {
      DevicePath = AppendDevicePath (
                        DevicePathFromHandle(Device),
                        DevicePath
                        );
      FreePool(FilePath);
    }
  }

  return DevicePath;
}



UINTN
DevicePathSize (
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
  EFI_DEVICE_PATH_PROTOCOL     *Start;

  //
  // Search for the end of the device path structure
  //

  Start = DevPath;
  while (!IsDevicePathEnd(DevPath)) {
    DevPath = NextDevicePathNode(DevPath);
  }

  //
  // Compute the size
  //
  return ((UINTN) DevPath - (UINTN) Start) + sizeof(EFI_DEVICE_PATH_PROTOCOL);
}


EFI_DEVICE_PATH_PROTOCOL *
DuplicateDevicePath (
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
  EFI_DEVICE_PATH_PROTOCOL    *NewDevPath;
  UINTN                       Size;


  //
  // Compute the size
  //
  Size = DevicePathSize (DevPath);

  //
  // Make a copy
  //
  NewDevPath = AllocatePool (Size);
  if (NewDevPath) {
    CopyMem (NewDevPath, DevPath, Size);
  }
  return NewDevPath;
}

EFI_DEVICE_PATH_PROTOCOL *
UnpackDevicePath (
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
  EFI_DEVICE_PATH_PROTOCOL    *Src, *Dest, *NewPath;
  UINTN                       Size;

  //
  // Walk device path and round sizes to valid boundries
  //

  Src = DevPath;
  Size = 0;
  for (; ;) {
    Size += DevicePathNodeLength(Src);
    Size += ALIGN_SIZE(Size);

    if (IsDevicePathEnd(Src)) {
      break;
    }

    Src = NextDevicePathNode(Src);
  }


  //
  // Allocate space for the unpacked path
  //

  NewPath = AllocateZeroPool (Size);
  if (NewPath) {

    ASSERT (((UINTN)NewPath) % MIN_ALIGNMENT_SIZE == 0);

    //
    // Copy each node
    //
    Src = DevPath;
    Dest = NewPath;
    for (; ;) {
      Size = DevicePathNodeLength(Src);
      CopyMem (Dest, Src, Size);
      Size += ALIGN_SIZE(Size);
      SetDevicePathNodeLength (Dest, Size);
      Dest->Type |= EFI_DP_TYPE_UNPACKED;
      Dest = (EFI_DEVICE_PATH_PROTOCOL *) (((UINT8 *) Dest) + Size);

      if (IsDevicePathEnd(Src)) {
        break;
      }

      Src = NextDevicePathNode(Src);
    }
  }

  return NewPath;
}


EFI_DEVICE_PATH_PROTOCOL *
AppendDevicePathInstance (
  IN EFI_DEVICE_PATH_PROTOCOL  *Src,
  IN EFI_DEVICE_PATH_PROTOCOL  *Instance
  )
/*++

Routine Description:
  Function is used to add a device path instance to a device path.

Arguments:
  Src          - A pointer to a device path data structure

  Instance     - A pointer to a device path instance.

Returns:

  This function returns a pointer to the new device path.
  If there is not enough temporary pool memory available to complete this function,
  then NULL is returned. It is up to the caller to free the memory used by Src and
  Instance if they are no longer needed.

--*/
{
  UINT8                     *Ptr;
  EFI_DEVICE_PATH_PROTOCOL  *DevPath;
  UINTN                     SrcSize;
  UINTN                     InstanceSize;

  if (Src == NULL) {
    return DuplicateDevicePath (Instance);
  }
  SrcSize = DevicePathSize(Src);
  InstanceSize = DevicePathSize(Instance);
  Ptr = AllocatePool (SrcSize + InstanceSize);
  DevPath = (EFI_DEVICE_PATH_PROTOCOL *)Ptr;
  ASSERT(DevPath);

  CopyMem (Ptr, Src, SrcSize);
//    FreePool (Src);

  while (!IsDevicePathEnd(DevPath)) {
    DevPath = NextDevicePathNode(DevPath);
  }
  //
  // Convert the End to an End Instance, since we are
  //  appending another instacne after this one its a good
  //  idea.
  //
  DevPath->SubType = END_INSTANCE_DEVICE_PATH_SUBTYPE;

  DevPath = NextDevicePathNode(DevPath);
  CopyMem (DevPath, Instance, InstanceSize);
  return (EFI_DEVICE_PATH_PROTOCOL *)Ptr;
}

EFI_STATUS
LibDevicePathToInterface (
  IN EFI_GUID                   *Protocol,
  IN EFI_DEVICE_PATH_PROTOCOL   *FilePath,
  OUT VOID                      **Interface
  )
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

    if (IsDevicePathEnd(FilePath)) {

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

VOID
_DevPathPci (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    PCI_DEVICE_PATH         *Pci;

    Pci = DevPath;
    CatPrint(Str, L"Pci(%x|%x)", Pci->Device, Pci->Function);
}

VOID
_DevPathPccard (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    PCCARD_DEVICE_PATH      *Pccard;

    Pccard = DevPath;
    CatPrint(Str, L"Pcmcia(Function%x)", Pccard->FunctionNumber);
}

VOID
_DevPathMemMap (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    MEMMAP_DEVICE_PATH      *MemMap;

    MemMap = DevPath;
    CatPrint(Str, L"MemMap(%d:%.lx-%.lx)",
        MemMap->MemoryType,
        MemMap->StartingAddress,
        MemMap->EndingAddress
        );
}

VOID
_DevPathController (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    CONTROLLER_DEVICE_PATH  *Controller;

    Controller = DevPath;
    CatPrint(Str, L"Ctrl(%d)",
        Controller->Controller
        );
}

VOID
_DevPathVendor (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    VENDOR_DEVICE_PATH                  *Vendor;
    CHAR16                              *Type;
    UNKNOWN_DEVICE_VENDOR_DEVICE_PATH   *UnknownDevPath;

    Vendor = DevPath;
    switch (DevicePathType(&Vendor->Header)) {
    case HARDWARE_DEVICE_PATH:  Type = L"Hw";        break;
    case MESSAGING_DEVICE_PATH: Type = L"Msg";       break;
    case MEDIA_DEVICE_PATH:     Type = L"Media";     break;
    default:                    Type = L"?";         break;
    }

    CatPrint(Str, L"Ven%s(%g", Type, &Vendor->Guid);
    if (CompareGuid (&Vendor->Guid, &gtEfiUnknownDeviceGuid) == 0) {
        //
        // GUID used by EFI to enumerate an EDD 1.1 device
        //
        UnknownDevPath = (UNKNOWN_DEVICE_VENDOR_DEVICE_PATH *)Vendor;
        CatPrint(Str, L":%02x)", UnknownDevPath->LegacyDriveLetter);
    } else {
        CatPrint(Str, L")");
    }
}


VOID
_DevPathAcpi (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    ACPI_HID_DEVICE_PATH        *Acpi;

    Acpi = DevPath;
    if ((Acpi->HID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
        CatPrint(Str, L"Acpi(PNP%04x,%x)", EISA_ID_TO_NUM (Acpi->HID), Acpi->UID);
    } else {
        CatPrint(Str, L"Acpi(%08x,%x)", Acpi->HID, Acpi->UID);
    }
}


VOID
_DevPathExtendedAcpi (
    IN OUT POOL_PRINT       *Str,
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

    Length = DevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) ExtendedAcpi);
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
    CatPrint (Str, L"Acpi(");
    if (HIDStrIndex != 0) {
        CatPrint (Str, L"%a,", AsChar8Array + HIDStrIndex);
    } else {
        if ((ExtendedAcpi->HID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
            CatPrint (Str, L"PNP%04x,", EISA_ID_TO_NUM (ExtendedAcpi->HID));
        } else {
            CatPrint (Str, L"%08x,", ExtendedAcpi->HID);
        }
    }

    if (CIDStrIndex != 0) {
        CatPrint (Str, L"%a,", AsChar8Array + CIDStrIndex);
    } else {
        if ((ExtendedAcpi->CID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
            CatPrint (Str, L"PNP%04x,", EISA_ID_TO_NUM (ExtendedAcpi->CID));
        } else {
            CatPrint (Str, L"%08x,", ExtendedAcpi->CID);
        }
    }

    if (UIDStrIndex != 0) {
        CatPrint (Str, L"%a)", AsChar8Array + UIDStrIndex);
    } else {
        CatPrint (Str, L"%x)", ExtendedAcpi->UID);
    }
}


VOID
_DevPathAtapi (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    ATAPI_DEVICE_PATH       *Atapi;

    Atapi = DevPath;
    CatPrint(Str, L"Ata(%s,%s)",
        Atapi->PrimarySecondary ? L"Secondary" : L"Primary",
        Atapi->SlaveMaster ? L"Slave" : L"Master"
        );
}

VOID
_DevPathScsi (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    SCSI_DEVICE_PATH        *Scsi;

    Scsi = DevPath;
    CatPrint(Str, L"Scsi(Pun%x,Lun%x)", Scsi->Pun, Scsi->Lun);
}


VOID
_DevPathFibre (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    FIBRECHANNEL_DEVICE_PATH    *Fibre;

    Fibre = DevPath;
    CatPrint(Str, L"Fibre(Wwn%lx,Lun%x)", Fibre->WWN, Fibre->Lun);
}

VOID
_DevPath1394 (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    F1394_DEVICE_PATH       *F1394;

    F1394 = DevPath;
    CatPrint(Str, L"1394(%g)", &F1394->Guid);
}



VOID
_DevPathUsb (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    USB_DEVICE_PATH         *Usb;

    Usb = DevPath;
    CatPrint(Str, L"Usb(%x, %x)", Usb->ParentPortNumber, Usb->InterfaceNumber);
}


VOID
_DevPathUsbClass (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    // tbd:
    USB_CLASS_DEVICE_PATH         *UsbClass;

    UsbClass = DevPath;
    CatPrint(Str, L"Usb Class(%x, %x, %x, %x, %x)",
              UsbClass->VendorId,
              UsbClass->ProductId,
              UsbClass->DeviceClass,
              UsbClass->DeviceSubClass,
              UsbClass->DeviceProtocol);
}



VOID
_DevPathI2O (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    I2O_DEVICE_PATH         *I2O;

    I2O = DevPath;
    CatPrint(Str, L"I2O(%x)", I2O->Tid);
}

VOID
_DevPathMacAddr (
    IN OUT POOL_PRINT       *Str,
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

    CatPrint(Str, L"Mac(");

    for(Index = 0; Index < HwAddressSize; Index++) {
        CatPrint(Str, L"%02x",MAC->MacAddress.Addr[Index]);
    }
    CatPrint(Str, L")");
}

VOID
_DevPathIPv4 (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    IPv4_DEVICE_PATH     *IP;

    IP = DevPath;
    CatPrint(Str, L"IPv4(%d.%d.%d.%d:%d)",IP->RemoteIpAddress.Addr[0],
                                       IP->RemoteIpAddress.Addr[1],
                                       IP->RemoteIpAddress.Addr[2],
                                       IP->RemoteIpAddress.Addr[3],
                                       IP->RemotePort);
}

VOID
_DevPathIPv6 (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    IPv6_DEVICE_PATH     *IP;

    IP = DevPath;
    CatPrint(Str, L"IP-v6(not-done)");
}

VOID
_DevPathInfiniBand (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    INFINIBAND_DEVICE_PATH  *InfiniBand;

    InfiniBand = DevPath;
    CatPrint(Str, L"InfiniBand(not-done)");
}

VOID
_DevPathUart (
    IN OUT POOL_PRINT       *Str,
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
        CatPrint(Str, L"Uart(DEFAULT %c",Parity);
    } else {
        CatPrint(Str, L"Uart(%d %c",Uart->BaudRate,Parity);
    }

    if (Uart->DataBits == 0) {
        CatPrint(Str, L"D");
    } else {
        CatPrint(Str, L"%d",Uart->DataBits);
    }

    switch (Uart->StopBits) {
        case 0  : CatPrint(Str, L"D)");   break;
        case 1  : CatPrint(Str, L"1)");   break;
        case 2  : CatPrint(Str, L"1.5)"); break;
        case 3  : CatPrint(Str, L"2)");   break;
        default : CatPrint(Str, L"x)");   break;
    }
}


VOID
_DevPathHardDrive (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    HARDDRIVE_DEVICE_PATH   *Hd;

    Hd = DevPath;
    switch (Hd->SignatureType) {
        case SIGNATURE_TYPE_MBR:
            CatPrint(Str, L"HD(Part%d,Sig%08x)",
                Hd->PartitionNumber,
                *((UINT32 *)(&(Hd->Signature[0])))
                );
            break;
        case SIGNATURE_TYPE_GUID:
            CatPrint(Str, L"HD(Part%d,Sig%g)",
                Hd->PartitionNumber,
                (EFI_GUID *) &(Hd->Signature[0])
                );
            break;
        default:
            CatPrint(Str, L"HD(Part%d,MBRType=%02x,SigType=%02x)",
                Hd->PartitionNumber,
                Hd->MBRType,
                Hd->SignatureType
                );
            break;
    }
}

VOID
_DevPathCDROM (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    CDROM_DEVICE_PATH       *Cd;

    Cd = DevPath;
    CatPrint(Str, L"CDROM(Entry%x)", Cd->BootEntry);
}

VOID
_DevPathFilePath (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    FILEPATH_DEVICE_PATH    *Fp;

    Fp = DevPath;
    CatPrint(Str, L"%s", Fp->PathName);
}

VOID
_DevPathMediaProtocol (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    MEDIA_PROTOCOL_DEVICE_PATH  *MediaProt;

    MediaProt = DevPath;
    CatPrint(Str, L"%g", &MediaProt->Protocol);
}

VOID
_DevPathFvFilePath (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    MEDIA_FW_VOL_FILEPATH_DEVICE_PATH   *FvFilePath;

    FvFilePath = DevPath;
    CatPrint(Str, L"%g", &FvFilePath->NameGuid);
}


VOID
_DevPathBssBss (
    IN OUT POOL_PRINT       *Str,
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

    CatPrint(Str, L"Bss-%s(%a)", Type, Bss->String);
}


VOID
_DevPathEndInstance (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    CatPrint(Str, L",");
}

VOID
_DevPathNodeUnknown (
    IN OUT POOL_PRINT       *Str,
    IN VOID                 *DevPath
    )
{
    CatPrint(Str, L"?");
}


struct {
  UINT8   Type;
  UINT8   SubType;
  VOID    (*Function)(POOL_PRINT *, VOID *);
} DevPathTable[] = {
  HARDWARE_DEVICE_PATH,   HW_PCI_DP,                        _DevPathPci,
  HARDWARE_DEVICE_PATH,   HW_PCCARD_DP,                     _DevPathPccard,
  HARDWARE_DEVICE_PATH,   HW_MEMMAP_DP,                     _DevPathMemMap,
  HARDWARE_DEVICE_PATH,   HW_VENDOR_DP,                     _DevPathVendor,
  HARDWARE_DEVICE_PATH,   HW_CONTROLLER_DP,                 _DevPathController,
  ACPI_DEVICE_PATH,       ACPI_DP,                          _DevPathAcpi,
  ACPI_DEVICE_PATH,       ACPI_EXTENDED_DP,                 _DevPathExtendedAcpi,
  MESSAGING_DEVICE_PATH,  MSG_ATAPI_DP,                     _DevPathAtapi,
  MESSAGING_DEVICE_PATH,  MSG_SCSI_DP,                      _DevPathScsi,
  MESSAGING_DEVICE_PATH,  MSG_FIBRECHANNEL_DP,              _DevPathFibre,
  MESSAGING_DEVICE_PATH,  MSG_1394_DP,                      _DevPath1394,
  MESSAGING_DEVICE_PATH,  MSG_USB_DP,                       _DevPathUsb,
  MESSAGING_DEVICE_PATH,  MSG_USB_CLASS_DP,                 _DevPathUsbClass,
  MESSAGING_DEVICE_PATH,  MSG_I2O_DP,                       _DevPathI2O,
  MESSAGING_DEVICE_PATH,  MSG_MAC_ADDR_DP,                  _DevPathMacAddr,
  MESSAGING_DEVICE_PATH,  MSG_IPv4_DP,                      _DevPathIPv4,
  MESSAGING_DEVICE_PATH,  MSG_IPv6_DP,                      _DevPathIPv6,
  MESSAGING_DEVICE_PATH,  MSG_INFINIBAND_DP,                _DevPathInfiniBand,
  MESSAGING_DEVICE_PATH,  MSG_UART_DP,                      _DevPathUart,
  MESSAGING_DEVICE_PATH,  MSG_VENDOR_DP,                    _DevPathVendor,
  MEDIA_DEVICE_PATH,      MEDIA_HARDDRIVE_DP,               _DevPathHardDrive,
  MEDIA_DEVICE_PATH,      MEDIA_CDROM_DP,                   _DevPathCDROM,
  MEDIA_DEVICE_PATH,      MEDIA_VENDOR_DP,                  _DevPathVendor,
  MEDIA_DEVICE_PATH,      MEDIA_FILEPATH_DP,                _DevPathFilePath,
  MEDIA_DEVICE_PATH,      MEDIA_PROTOCOL_DP,                _DevPathMediaProtocol,
#if (EFI_SPECIFICATION_VERSION < 0x00020000)  
  MEDIA_DEVICE_PATH,      MEDIA_FV_FILEPATH_DP,             _DevPathFvFilePath,
#endif
  BBS_DEVICE_PATH,        BBS_BBS_DP,                       _DevPathBssBss,
  END_DEVICE_PATH_TYPE,   END_INSTANCE_DEVICE_PATH_SUBTYPE, _DevPathEndInstance,
  0,                      0,                          NULL
};


CHAR16 *
DevicePathToStr (
  EFI_DEVICE_PATH_PROTOCOL     *DevPath
  )
/*++

    Turns the Device Path into a printable string.  Allcoates
    the string from pool.  The caller must FreePool the returned
    string.

--*/
{
  POOL_PRINT                  Str;
  EFI_DEVICE_PATH_PROTOCOL    *DevPathNode;
  VOID                        (*DumpNode)(POOL_PRINT *, VOID *);
  UINTN                       Index, NewSize;

  ZeroMem(&Str, sizeof(Str));

  if (DevPath == NULL) {
    goto Done;
  }

  //
  // Unpacked the device path
  //
  DevPath = UnpackDevicePath(DevPath);
  ASSERT (DevPath);


  //
  // Process each device path node
  //
  DevPathNode = DevPath;
  while (!IsDevicePathEnd(DevPathNode)) {

    //
    // Find the handler to dump this device path node
    //

    DumpNode = NULL;
    for (Index = 0; DevPathTable[Index].Function; Index += 1) {

      if (DevicePathType(DevPathNode) == DevPathTable[Index].Type &&
          DevicePathSubType(DevPathNode) == DevPathTable[Index].SubType) {
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
      CatPrint (&Str, L"/");
    }

    //
    // Print this node of the device path
    //
    DumpNode (&Str, DevPathNode);

    //
    // Next device path node
    //
    DevPathNode = NextDevicePathNode(DevPathNode);
  }

  //
  // Shrink pool used for string allocation
  //

  FreePool (DevPath);
Done:
  NewSize = (Str.len + 1) * sizeof(CHAR16);
  Str.str = ReallocatePool (Str.str, NewSize, NewSize);
  Str.str[Str.len] = 0;
  return Str.str;
}

BOOLEAN
LibMatchDevicePaths (
  IN  EFI_DEVICE_PATH_PROTOCOL *Multi,
  IN  EFI_DEVICE_PATH_PROTOCOL *Single
  )
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
{
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath, *DevicePathInst;
  UINTN                       Size;

  if (!Multi || !Single) {
    return FALSE;
  }

  DevicePath = Multi;
  DevicePathInst = DevicePathInstance (&DevicePath, &Size);
  while (DevicePathInst) {
    if (CompareMem (Single, DevicePathInst, Size - sizeof(EFI_DEVICE_PATH_PROTOCOL)) == 0) {
      return TRUE;
    }
    DevicePathInst = DevicePathInstance (&DevicePath, &Size);
  }
  return FALSE;
}

EFI_DEVICE_PATH_PROTOCOL *
LibDuplicateDevicePathInstance (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  )
/*++

Routine Description:
  Function creates a device path data structure that identically matches the
  device path passed in.

Arguments:
  DevPath      - A pointer to a device path data structure.

Returns:

  The new copy of DevPath is created to identically match the input.
  Otherwise, NULL is returned.

--*/
{
  EFI_DEVICE_PATH_PROTOCOL    *NewDevPath,*DevicePathInst,*Temp;
  UINTN                       Size;

  //
  // get the size of an instance from the input
  //
  Temp = DevPath;
  DevicePathInst = DevicePathInstance (&Temp, &Size);

  //
  // Make a copy
  //
  NewDevPath = NULL;
  if (Size) {
    NewDevPath = AllocatePool (Size);
  }

  if (NewDevPath) {
    CopyMem (NewDevPath, DevicePathInst, Size);
//    Temp = NextDevicePathNode(NewDevPath);
//    SetDevicePathEndNode(Temp);
  }
  return NewDevPath;
}

UINT16 *
DevicePathStrFromProtocol (
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
  Status      = LibLocateHandle(
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
        Str = DevicePathToStr(DevicePath);
      }
      break;
    }
  }

  return Str;
}

//
//added by kevin for test cases
//
/**
 *  get the device path and file path based on the loaded image name.
 *  @param Name the iamge file name such as framework.efi
 *  @param DevicePath the Device path of this file is loaded from.
 *  @param FilePath the file path of this file.
 *  @return EFI_SUCCESS the device path and file path was found successfully.
 *  @return EFI_INVALID_PARAMETER the Parameter is invalid
 */
EFI_STATUS
GetFilePathByName (
  IN CHAR16                       *Name,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  OUT CHAR16                      **FilePath
  )
{
  EFI_STATUS                  Status;
  UINTN                       Index;
  EFI_LOADED_IMAGE_PROTOCOL   *Image;
  EFI_HANDLE                  *HandleBuffer;
  UINTN                       HandleNum;
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL    *TempDeviceNode;
  CHAR16                      *TempFilePath;
  CHAR16                      FullFilePath[MAX_FILE_PATH];
  BOOLEAN                     Found;

  //
  //verify parameters.
  //
  if (Name == NULL || DevicePath == NULL || FilePath == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (StrLen (Name) == 0) {
    return EFI_INVALID_PARAMETER;
  }

  //
  //get all the load image protocol instance.
  //
  Found        = FALSE;
  HandleNum    = 0;
  HandleBuffer = NULL;

  Status  = LibLocateHandle(
                  ByProtocol,
                  &gEfiLoadedImageProtocolGuid,
                  NULL,
                  &HandleNum,
                  &HandleBuffer
                  );

  if (EFI_ERROR(Status) || HandleNum == 0) {
    return EFI_ABORTED;
  }

  //
  //for all the LoadedImage protocol found the image file name to match the
  //given file name.
  //
  TempDevicePath = NULL;
  for (Index = 0; Index < HandleNum; Index ++ ) {

    FullFilePath[0] = '\0';

    //
    // Get the image instance from the image handle
    //
    Status = tBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gEfiLoadedImageProtocolGuid,
                     (VOID**)&Image
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }

    if (Image->FilePath == NULL) {
      continue;
    }

    //
    //get the file path and parse the file name.
    //
    TempDevicePath = UnpackDevicePath (Image->FilePath);
    TempFilePath   = NULL;
    TempDeviceNode = TempDevicePath;

    while (!IsDevicePathEnd(TempDeviceNode)) {
      if ((DevicePathType(TempDeviceNode) == MEDIA_DEVICE_PATH) &&
          (DevicePathSubType(TempDeviceNode) == MEDIA_FILEPATH_DP)) {
        StrCat(FullFilePath, L"\\");
        TempFilePath = ((FILEPATH_DEVICE_PATH *)TempDeviceNode)->PathName;

        if (StrLen (TempFilePath) == 1 && TempFilePath[0] == '\\') {
          //
          //if this the "\\" path then we need not append it,or else there will
          //have 3 '\\' in the device path.
          //
          ;
        } else {
          StrCat(FullFilePath, TempFilePath);
        }
      }
      TempDeviceNode = NextDevicePathNode (TempDeviceNode);
    }

    tBS->FreePool (TempDevicePath);

    if (StrLen (FullFilePath) <= StrLen (Name)) {
      continue;
    }

    TempFilePath = FullFilePath + (StrLen(FullFilePath) - StrLen(Name));

    if ((*(TempFilePath - 1)) == L'\\' && StriCmp (TempFilePath, Name) == 0) {

      TempFilePath[0] = '\0';
      //
      // Get the device instance from the device handle
      //
      Status = tBS->HandleProtocol (
                     Image->DeviceHandle,
                     &gEfiDevicePathProtocolGuid,
                     (VOID**)&TempDevicePath
                     );
      if (EFI_ERROR(Status)) {
        return Status;
      }

      Found = TRUE;
      break;
    }
  }

  if (HandleBuffer != NULL) {
    tBS->FreePool (HandleBuffer);
  }

  if (!Found) {
    return EFI_NOT_FOUND;
  }


  //
  // If the file path is only a root directory "\\", remove it
  //
  if (StrLen(FullFilePath) > 1) {
    if (FullFilePath[StrLen(FullFilePath) - 1] == L'\\') {
     FullFilePath[StrLen(FullFilePath) - 1] = '\0';
    }
  }

  *DevicePath = DuplicateDevicePath (TempDevicePath);
  if (*DevicePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //skip the first '\\'.
  //
  *FilePath = StrDuplicate (FullFilePath + 1);
  if (*FilePath == NULL) {
    tBS->FreePool (*DevicePath);
    *DevicePath = NULL;
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;

}
