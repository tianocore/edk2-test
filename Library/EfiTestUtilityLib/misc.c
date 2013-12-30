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

  misc.c

Abstract:

  Misc functions

--*/

#include "lib.h"


VOID *
AllocatePool (
  IN UINTN                Size
  )
/*++

Routine Description:
  Allocates pool memory.

Arguments:
  Size                 - Size in bytes of the pool being requested.

Returns:

  EFI_SUCEESS          - The requested number of bytes were allocated.

  EFI_OUT_OF_RESOURCES - The pool requested could not be allocated.

--*/
{
  EFI_STATUS              Status;
  VOID                    *p;

  Status = tBS->AllocatePool (PoolAllocationType, Size, &p);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "AllocatePool: out of pool  %x\n", Status));
    p = NULL;
  }
  return p;
}

VOID *
AllocateCopyPool (
  IN  UINTN   AllocationSize,
  IN  VOID    *Buffer
  )
{
  VOID  *Memory;

  Memory = NULL;
  tBS->AllocatePool (PoolAllocationType, AllocationSize, &Memory);
  if (Memory != NULL) {
    tBS->CopyMem (Memory, Buffer, AllocationSize);
  }

  return Memory;
}

VOID *
AllocateZeroPool (
  IN UINTN                Size
  )
/*++

Routine Description:
  Allocates pool memory and initializes the memory to zeros.

Arguments:
  Size                 - Size in bytes of the pool being requested.

Returns:

  EFI_SUCEESS          - The requested number of bytes were allocated.

  EFI_OUT_OF_RESOURCES - The pool requested could not be allocated.

--*/
{
  VOID                    *p;

  p = AllocatePool (Size);
  if (p) {
    ZeroMem (p, Size);
  }

  return p;
}


VOID *
ReallocatePool (
  IN VOID                 *OldPool,
  IN UINTN                OldSize,
  IN UINTN                NewSize
  )
/*++

Routine Description:
  Adjusts the size of a previously allocated buffer.

Arguments:
  OldPool               - A pointer to the buffer whose size is being adjusted.
  OldSize               - The size of the current buffer.
  NewSize               - The size of the new buffer.

Returns:

  EFI_SUCEESS           - The requested number of bytes were allocated.

  EFI_OUT_OF_RESOURCES  - The pool requested could not be allocated.

  EFI_INVALID_PARAMETER - The buffer was invalid.

--*/
{
  VOID                    *NewPool;

  NewPool = NULL;
  if (NewSize) {
    NewPool = AllocatePool (NewSize);
  }

  if (OldPool) {
    if (NewPool) {
      CopyMem (NewPool, OldPool, OldSize < NewSize ? OldSize : NewSize);
    }
    FreePool (OldPool);
  }

  return NewPool;
}


VOID
FreePool (
  IN VOID                 *Buffer
  )
/*++

Routine Description:
  Releases a previously allocated buffer.

Arguments:
  Buffer                - A pointer to the buffer to free.

Returns:

  EFI_SUCEESS           - The requested number of bytes were allocated.

  EFI_INVALID_PARAMETER - The buffer was invalid.

--*/
{
  tBS->FreePool (Buffer);
}


VOID
ZeroMem (
  IN VOID     *Buffer,
  IN UINTN    Size
  )
/*++

Routine Description:
  Fills a buffer with zeros.

Arguments:
  Buffer                - A pointer to the buffer to fill with zeros.

  Size                  - Number of bytes to zero in the buffer.

Returns:

  None

--*/
{
  INT8        *pt;

  pt = Buffer;
  while (Size--) {
    *(pt++) = 0;
  }
}


VOID
SetMem (
  IN VOID     *Buffer,
  IN UINTN    Size,
  IN UINT8    Value
  )
/*++

Routine Description:
  Fills a buffer with a value.

Arguments:
  Buffer                - A pointer to the buffer to free.

  Size                  - The number of bytes in the buffer to fill.

  Value                 - The value to fill Buffer with.

Returns:

  None

--*/
{
  INT8        *pt;

  pt = Buffer;
  while (Size--) {
    *(pt++) = Value;
  }
}


VOID
CopyMem (
  IN VOID     *Dest,
  IN VOID     *Src,
  IN UINTN    len
  )
/*++

Routine Description:
  Copies the contents of one buffer to another.

Arguments:
  Dest                - A pointer to the buffer to copy to

  Src                 - A pointer to the buffer to copy from.

  len                 - The number of bytes to copy.

Returns:

  None

--*/
{
  CHAR8    *d, *s;

  d = Dest;
  s = Src;
  while (len--) {
    *(d++) = *(s++);
  }
}


INTN
CompareMem (
  IN VOID     *Dest,
  IN VOID     *Src,
  IN UINTN    len
  )
/*++

Routine Description:
  Compares the contents of one buffer to another.

Arguments:
  Dest                - A pointer to the buffer to compare

  Src                 - A pointer to the buffer to compare

  len                 - The number of bytes to compare

Returns:

  0                   - Dest is identical to Src for len bytes.
  !=0                 - Dest is not identical to Src for len bytes.

--*/
{
  CHAR8    *d, *s;

  d = Dest;
  s = Src;
  while (len--) {
    if (*d != *s) {
      return *d - *s;
    }

    d += 1;
    s += 1;
  }

  return 0;
}


BOOLEAN
GrowBuffer(
  IN OUT EFI_STATUS   *Status,
  IN OUT VOID         **Buffer,
  IN UINTN            BufferSize
  )
/*++

Routine Description:

    Helper function called as part of the code needed
    to allocate the proper sized buffer for various
    EFI interfaces.

Arguments:

    Status      - Current status

    Buffer      - Current allocated buffer, or NULL

    BufferSize  - Current buffer size needed

Returns:

    TRUE - if the buffer was reallocated and the caller
    should try the API again.

--*/
{
  BOOLEAN         TryAgain;

  //
  // If this is an initial request, buffer will be null with a new buffer size
  //

  if (!*Buffer && BufferSize) {
    *Status = EFI_BUFFER_TOO_SMALL;
  }

  //
  // If the status code is "buffer too small", resize the buffer
  //

  TryAgain = FALSE;
  if (*Status == EFI_BUFFER_TOO_SMALL) {

    if (*Buffer) {
      FreePool (*Buffer);
    }

    *Buffer = AllocatePool (BufferSize);

    if (*Buffer) {
      TryAgain = TRUE;
    } else {
      *Status = EFI_OUT_OF_RESOURCES;
    }
  }

  //
  // If there's an error, free the buffer
  //

  if (!TryAgain && EFI_ERROR(*Status) && *Buffer) {
    FreePool (*Buffer);
    *Buffer = NULL;
  }

  return TryAgain;
}


EFI_MEMORY_DESCRIPTOR *
LibMemoryMap (
  OUT UINTN               *NoEntries,
  OUT UINTN               *MapKey,
  OUT UINTN               *DescriptorSize,
  OUT UINT32              *DescriptorVersion
  )
/*++

Routine Description:
  This function retrieves the system's current memory map.

Arguments:
  NoEntries                - A pointer to the number of memory descriptors in the system

  MapKey                   - A pointer to the current memory map key.

  DescriptorSize           - A pointer to the size in bytes of a memory descriptor

  DescriptorVersion        - A pointer to the version of the memory descriptor.

Returns:

  None

--*/
{
  EFI_STATUS              Status;
  EFI_MEMORY_DESCRIPTOR   *Buffer;
  UINTN                   BufferSize;

  //
  // Initialize for GrowBuffer loop
  //

  Buffer = NULL;
  BufferSize = sizeof(EFI_MEMORY_DESCRIPTOR);

  //
  // Call the real function
  //

  while (GrowBuffer (&Status, (VOID **) &Buffer, BufferSize)) {
    Status = tBS->GetMemoryMap (
                   &BufferSize,
                   Buffer,
                   MapKey,
                   DescriptorSize,
                   DescriptorVersion
                   );
  }

  //
  // Convert buffer size to NoEntries
  //

  if (!EFI_ERROR(Status)) {
    *NoEntries = BufferSize / *DescriptorSize;
  }

  return Buffer;
}


VOID *
LibGetVariableAndSize (
    IN CHAR16               *Name,
    IN EFI_GUID             *VendorGuid,
    OUT UINTN               *VarSize
    )
/*++

Routine Description:
  Function returns the value of the specified variable and its size in bytes.

Arguments:
  Name                - A Null-terminated Unicode string that is
                        the name of the vendor's variable.

  VendorGuid          - A unique identifier for the vendor.

  VarSize             - The size of the returned environment variable in bytes.

Returns:

  None

--*/
{
  EFI_STATUS              Status;
  VOID                    *Buffer;
  UINTN                   BufferSize;

  //
  // Initialize for GrowBuffer loop
  //

  Buffer = NULL;
  BufferSize = 100;

  //
  // Call the real function
  //

  while (GrowBuffer (&Status, &Buffer, BufferSize)) {
    Status = tRT->GetVariable (
                   Name,
                   VendorGuid,
                   NULL,
                   &BufferSize,
                   Buffer
                   );
  }
  if (Buffer) {
    *VarSize = BufferSize;
  } else {
    *VarSize = 0;
  }
  return Buffer;
}


VOID *
LibGetVariable (
  IN CHAR16               *Name,
  IN EFI_GUID             *VendorGuid
    )
/*++

Routine Description:
  Function returns the value of the specified variable.

Arguments:
  Name                - A Null-terminated Unicode string that is
                        the name of the vendor's variable.

  VendorGuid          - A unique identifier for the vendor.

Returns:

  None

--*/
{
  UINTN   VarSize;

  return LibGetVariableAndSize (Name, VendorGuid, &VarSize);
}


EFI_STATUS
LibDeleteVariable (
    IN CHAR16   *VarName,
    IN EFI_GUID *VarGuid
    )
/*++

Routine Description:
  Function deletes the variable specified by VarName and VarGuid.

Arguments:
  VarName              - A Null-terminated Unicode string that is
                         the name of the vendor's variable.

  VendorGuid           - A unique identifier for the vendor.

Returns:

  EFI_SUCCESS          - The variable was found and removed

  EFI_UNSUPPORTED      - The variable store was inaccessible

  EFI_OUT_OF_RESOURCES - The temporary buffer was not available

  EFI_NOT_FOUND        - The variable was not found

--*/
{
    VOID        *VarBuf;
    EFI_STATUS  Status;

    VarBuf = LibGetVariable(VarName,VarGuid);

    Status = EFI_NOT_FOUND;

    if (VarBuf) {
        //
        // Delete variable from Storage
        //
        Status = tRT->SetVariable (
                    VarName, VarGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    0, NULL
                 );
        ASSERT (!EFI_ERROR(Status));
        FreePool(VarBuf);
    }

    return (Status);
}


EFI_STATUS
LibInsertToTailOfBootOrder (
  IN  UINT16  BootOption,
  IN  BOOLEAN OnlyInsertIfEmpty
  )
/*++

Routine Description:
  Insert BootOption to the end of VarBootOrder

Arguments:
  BootOption           - Boot option variable to add to VarBootOrder

  OnlyInsertIfEmpty    - If VarBootOrder is empty, then add if TRUE.

Returns:

  EFI_SUCCESS          - The BootOption was added to the VarBootOrder

  EFI_UNSUPPORTED      - Variable store was inaccessible or (VarBootOrder & OnlyInsertIfEmpty)

  EFI_OUT_OF_RESOURCES - The temporary buffer was not available

--*/
{
  UINT16      *BootOptionArray;
  UINT16      *NewBootOptionArray;
  UINTN       VarSize;
  UINTN       Index;
  EFI_STATUS  Status;

  BootOptionArray = LibGetVariableAndSize (VarBootOrder, &tEfiGlobalVariable, &VarSize);
  if (VarSize != 0 && OnlyInsertIfEmpty) {
    if (BootOptionArray) {
      FreePool (BootOptionArray);
    }
    return EFI_UNSUPPORTED;
  }

  VarSize += sizeof(UINT16);
  NewBootOptionArray = AllocatePool (VarSize);

  for (Index = 0; Index < ((VarSize/sizeof(UINT16)) - 1); Index++) {
    NewBootOptionArray[Index] = BootOptionArray[Index];
  }
  //
  // Insert in the tail of the array
  //
  NewBootOptionArray[Index] = BootOption;

  Status = tRT->SetVariable (
                 VarBootOrder, &tEfiGlobalVariable,
                 EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                 VarSize, (VOID*) NewBootOptionArray
                 );

  if (NewBootOptionArray) {
    FreePool (NewBootOptionArray);
  }
  if (BootOptionArray) {
    FreePool (BootOptionArray);
  }
  return Status;
}


BOOLEAN
ValidMBR(
  IN  MASTER_BOOT_RECORD     *Mbr,
  IN  EFI_BLOCK_IO_PROTOCOL  *BlkIo
  )
/*++

Routine Description:
  Determine if the Mbr pointer is pointing to a valid master boot record.

Arguments:
  Mbr              - A pointer to a buffer which contains a possible Master Boot Record
                     structure.

  BlkIo            - A pointer to the Block IO protocol

Returns:

  TRUE             - The Mbr pointer is pointing at a valid Master Boot Record

  FALSE            - The Mbr pointer is not pointing at a valid Master Boot Record

--*/
{
  UINT32      StartingLBA, EndingLBA;
  UINT32      NewEndingLBA;
  INTN        i, j;
  BOOLEAN     ValidMbr;

  if (Mbr->Signature != MBR_SIGNATURE) {
    //
    // The BPB also has this signature, so it can not be used alone.
    //
    return FALSE;
  }

  ValidMbr = FALSE;
  for (i=0; i<MAX_MBR_PARTITIONS; i++) {
    if ( Mbr->Partition[i].OSIndicator == 0x00 || EXTRACT_UINT32(Mbr->Partition[i].SizeInLBA) == 0 ) {
      continue;
    }
    ValidMbr = TRUE;
    StartingLBA = EXTRACT_UINT32(Mbr->Partition[i].StartingLBA);
    EndingLBA = StartingLBA + EXTRACT_UINT32(Mbr->Partition[i].SizeInLBA) - 1;
    if (EndingLBA > BlkIo->Media->LastBlock) {

      //
      // Compatability Errata:
      // Some systems try to hide drive space with thier INT 13h driver
      // This does not hide space from the OS driver. This means the MBR
      // that gets created from DOS is smaller than the MBR created from
      // a real OS (NT & Win98). This leads to BlkIo->LastBlock being
      // wrong on some systems FDISKed by the OS.
      //
      //
      if (BlkIo->Media->LastBlock < MIN_MBR_DEVICE_SIZE) {
        //
        // If this is a very small device then trust the BlkIo->LastBlock
        //
        return FALSE;
      }

      if (EndingLBA > (BlkIo->Media->LastBlock + MBR_ERRATA_PAD)) {
        return FALSE;
      }

    }
    for (j=i+1; j<MAX_MBR_PARTITIONS; j++) {
      if (Mbr->Partition[j].OSIndicator == 0x00 || EXTRACT_UINT32(Mbr->Partition[j].SizeInLBA) == 0) {
        continue;
      }
      if ( EXTRACT_UINT32(Mbr->Partition[j].StartingLBA) >= StartingLBA &&
           EXTRACT_UINT32(Mbr->Partition[j].StartingLBA) <= EndingLBA       ) {
        //
        // The Start of this region overlaps with the i'th region
        //
        return FALSE;
      }
      NewEndingLBA = EXTRACT_UINT32(Mbr->Partition[j].StartingLBA) + EXTRACT_UINT32(Mbr->Partition[j].SizeInLBA) - 1;
      if ( NewEndingLBA >= StartingLBA && NewEndingLBA <= EndingLBA ) {
        //
        // The End of this region overlaps with the i'th region
        //
        return FALSE;
      }
    }
  }
  //
  // Non of the regions overlapped so MBR is O.K.
  //
  return ValidMbr;
}


UINT8
DecimaltoBCD(
  IN  UINT8 DecValue
  )
/*++

Routine Description:
  Function converts a decimal to a BCD value.

Arguments:
  DecValue         - An 8 bit decimal value

Returns:

  UINT8            - Returns the BCD value of the DecValue

--*/
{
  UINTN   High, Low;

  High    = DecValue / 10;
  Low     = DecValue - (High * 10);

  return ((UINT8)(Low + (High << 4)));
}


UINT8
BCDtoDecimal(
  IN  UINT8 BcdValue
  )
/*++

Routine Description:
  Function converts a BCD to a decimal value.

Arguments:
  BcdValue         - An 8 bit BCD value

Returns:

  UINT8            - Returns the decimal value of the BcdValue

--*/
{
  UINTN   High, Low;

  High    = BcdValue >> 4;
  Low     = BcdValue - (High << 4);

  return ((UINT8)(Low + (High * 10)));
}

EFI_STATUS
LibGetSystemConfigurationTable(
  IN EFI_GUID *TableGuid,
  IN OUT VOID **Table
  )
/*++

Routine Description:
  Function returns a system configuration table that is stored in the
  EFI System Table based on the provided GUID.

Arguments:
  TableGuid        - A pointer to the table's GUID type.

  Table            - On exit, a pointer to a system configuration table.

Returns:

  EFI_SUCCESS      - A configuration table matching TableGuid was found

  EFI_NOT_FOUND    - A configuration table matching TableGuid was not found

--*/
{
  UINTN Index;

  for(Index=0;Index<tST->NumberOfTableEntries;Index++) {
    if (CompareGuid(TableGuid,&(tST->ConfigurationTable[Index].VendorGuid))==0) {
      *Table = tST->ConfigurationTable[Index].VendorTable;
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}


CHAR16 *
LibGetUiString (
  IN  EFI_HANDLE      Handle,
  IN  UI_STRING_TYPE  StringType,
  IN  ISO_639_2       *LangCode,
  IN  BOOLEAN         ReturnDevicePathStrOnMismatch
  )
/*++

Routine Description:


Arguments:
  Handle           - Handle of the device

  StringType       - String type

  LangCode         - Language Code

  ReturnDevicePathStrOnMismatch - If error, return string value of devicepath.

Returns:

  If ReturnDevicePathStrOnMismatch = True, return Printable string version of Device Path

  If ReturnDevicePathStrOnMismatch = False, return NULL

--*/
{
    UI_INTERFACE    *Ui;
    UI_STRING_TYPE  Index;
    UI_STRING_ENTRY *Array;
    EFI_STATUS      Status;

    Status = tBS->HandleProtocol (Handle, &tUiProtocol, (VOID *)&Ui);
    if (EFI_ERROR(Status)) {
        return (ReturnDevicePathStrOnMismatch) ? DevicePathToStr(DevicePathFromHandle(Handle)) : NULL;
    }

    //
    // Skip the first strings
    //
    for (Index = UiDeviceString, Array = Ui->Entry; Index < StringType; Index++, Array++) {
        while (Array->LangCode) {
            Array++;
        }
    }

    //
    // Search for the match
    //
    while (Array->LangCode) {
        if (strcmpa ((CHAR8*)Array->LangCode, (CHAR8*)LangCode) == 0) {
            return Array->UiString;
        }
    }
    return (ReturnDevicePathStrOnMismatch) ? DevicePathToStr(DevicePathFromHandle(Handle)) : NULL;
}

EFI_STATUS
LibScanHandleDatabase (
  EFI_HANDLE  DriverBindingHandle,       OPTIONAL
  UINT32      *DriverBindingHandleIndex, OPTIONAL
  EFI_HANDLE  ControllerHandle,          OPTIONAL
  UINT32      *ControllerHandleIndex,    OPTIONAL
  UINTN       *HandleCount,
  EFI_HANDLE  **HandleBuffer,
  UINT32      **HandleType
  )

{
  EFI_STATUS                           Status;
  UINTN                                HandleIndex;
  EFI_GUID                             **ProtocolGuidArray;
  UINTN                                ArrayCount;
  UINTN                                ProtocolIndex;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY  *OpenInfo;
  UINTN                                OpenInfoCount;
  UINTN                                OpenInfoIndex;
  UINTN                                ChildIndex;
  BOOLEAN                              DriverBindingHandleIndexValid;
  BOOLEAN                              ControllerHandleIndexValid;

  DriverBindingHandleIndexValid = FALSE;
  if (DriverBindingHandleIndex != NULL) {
    *DriverBindingHandleIndex = 0xffffffff;
  }
  ControllerHandleIndexValid = FALSE;
  if (ControllerHandleIndex != NULL) {
    *ControllerHandleIndex    = 0xffffffff;
  }
  *HandleCount              = 0;
  *HandleBuffer             = NULL;
  *HandleType               = NULL;

  //
  // Retrieve the list of all handles from the handle database
  //
  Status = tBS->LocateHandleBuffer (
                 AllHandles,
                 NULL,
                 NULL,
                 HandleCount,
                 HandleBuffer
                 );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = tBS->AllocatePool(
                 EfiBootServicesData,
                 *HandleCount * sizeof(UINT32),
                 (VOID **)HandleType
                 );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  for (HandleIndex = 0; HandleIndex < *HandleCount; HandleIndex++) {

    //
    // Assume that the handle type is unknown
    //
    (*HandleType)[HandleIndex] = EFI_HANDLE_TYPE_UNKNOWN;

    if (DriverBindingHandle != NULL && DriverBindingHandleIndex != NULL && (*HandleBuffer)[HandleIndex] == DriverBindingHandle) {
      *DriverBindingHandleIndex = (UINT32)HandleIndex;
      DriverBindingHandleIndexValid = TRUE;
    }

    if (ControllerHandle != NULL && ControllerHandleIndex != NULL && (*HandleBuffer)[HandleIndex] == ControllerHandle) {
      *ControllerHandleIndex = (UINT32)HandleIndex;
      ControllerHandleIndexValid = TRUE;
    }

  }

  for (HandleIndex = 0; HandleIndex < *HandleCount; HandleIndex++) {

    //
    // Retrieve the list of all the protocols on each handle
    //
    Status = tBS->ProtocolsPerHandle (
                   (*HandleBuffer)[HandleIndex],
                   &ProtocolGuidArray,
                   &ArrayCount
                   );
    if (!EFI_ERROR (Status)) {

      for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {

        if (CompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiLoadedImageProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= EFI_HANDLE_TYPE_IMAGE_HANDLE;
        }

        if (CompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiDriverBindingProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= EFI_HANDLE_TYPE_DRIVER_BINDING_HANDLE;
        }

        if (CompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiDriverConfigurationProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= EFI_HANDLE_TYPE_DRIVER_CONFIGURATION_HANDLE;
        }

        if (CompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiDriverDiagnosticsProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= EFI_HANDLE_TYPE_DRIVER_DIAGNOSTICS_HANDLE;
        }

        if (CompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiComponentNameProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= EFI_HANDLE_TYPE_COMPONENT_NAME_HANDLE;
        }

        if (CompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiDevicePathProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= EFI_HANDLE_TYPE_DEVICE_HANDLE;
        }

        //
        // Retrieve the list of agents that have opened each protocol
        //
        Status = tBS->OpenProtocolInformation (
                       (*HandleBuffer)[HandleIndex],
                       ProtocolGuidArray[ProtocolIndex],
                       &OpenInfo,
                       &OpenInfoCount
                       );
        if (!EFI_ERROR (Status)) {

          for (OpenInfoIndex=0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
            if (DriverBindingHandle != NULL && OpenInfo[OpenInfoIndex].AgentHandle == DriverBindingHandle) {
              if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                //
                // Mark the device handle as being managed by the driver specified by DriverBindingHandle
                //
                (*HandleType)[HandleIndex] |= (EFI_HANDLE_TYPE_DEVICE_HANDLE | EFI_HANDLE_TYPE_CONTROLLER_HANDLE);
                //
                // Mark the DriverBindingHandle as being a driver that is managing at least one controller
                //
                if (DriverBindingHandleIndexValid) {
                  (*HandleType)[*DriverBindingHandleIndex] |= EFI_HANDLE_TYPE_DEVICE_DRIVER;
                }
              }
              if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) == EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
                //
                // Mark the DriverBindingHandle as being a driver that is managing at least one child controller
                //
                if (DriverBindingHandleIndexValid) {
                  (*HandleType)[*DriverBindingHandleIndex] |= EFI_HANDLE_TYPE_BUS_DRIVER;
                }
              }

              if (ControllerHandle != NULL && (*HandleBuffer)[HandleIndex] == ControllerHandle) {
                if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) == EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
                  for (ChildIndex = 0; ChildIndex < *HandleCount; ChildIndex++) {
                    if ((*HandleBuffer)[ChildIndex] == OpenInfo[OpenInfoIndex].ControllerHandle) {
                      (*HandleType)[ChildIndex] |= (EFI_HANDLE_TYPE_DEVICE_HANDLE | EFI_HANDLE_TYPE_CHILD_HANDLE);
                    }
                  }
                }
              }
            }

            if (DriverBindingHandle == NULL && OpenInfo[OpenInfoIndex].ControllerHandle == ControllerHandle) {
              if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                for (ChildIndex = 0; ChildIndex < *HandleCount; ChildIndex++) {
                  if ((*HandleBuffer)[ChildIndex] == OpenInfo[OpenInfoIndex].AgentHandle) {
                    (*HandleType)[ChildIndex] |= EFI_HANDLE_TYPE_DEVICE_DRIVER;
                  }
                }
              }
              if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) == EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
                (*HandleType)[HandleIndex] |= EFI_HANDLE_TYPE_PARENT_HANDLE;
                for (ChildIndex = 0; ChildIndex < *HandleCount; ChildIndex++) {
                  if ((*HandleBuffer)[ChildIndex] == OpenInfo[OpenInfoIndex].AgentHandle) {
                    (*HandleType)[ChildIndex] |= EFI_HANDLE_TYPE_BUS_DRIVER;
                  }
                }
              }
            }
          }
          tBS->FreePool(OpenInfo);
        }
      }
      tBS->FreePool(ProtocolGuidArray);
    }
  }

  return EFI_SUCCESS;

Error:
  if (*HandleType != NULL) {
    tBS->FreePool(*HandleType);
  }
  if (*HandleBuffer != NULL) {
    tBS->FreePool(*HandleBuffer);
  }
  *HandleCount = 0;
  *HandleBuffer = NULL;
  *HandleType   = NULL;

  return Status;
}

EFI_STATUS
LibGetHandleDatabaseSubset (
  EFI_HANDLE  DriverBindingHandle,
  EFI_HANDLE  ControllerHandle,
  UINT32      Mask,
  UINTN       *MatchingHandleCount,
  EFI_HANDLE  **MatchingHandleBuffer
  )

{
  EFI_STATUS  Status;
  UINTN       HandleCount;
  EFI_HANDLE  *HandleBuffer;
  UINT32      *HandleType;
  UINTN       HandleIndex;

  *MatchingHandleCount  = 0;
  if (MatchingHandleBuffer != NULL) {
    *MatchingHandleBuffer = NULL;
  }

  HandleBuffer = NULL;
  HandleType   = NULL;

  Status = LibScanHandleDatabase (
             DriverBindingHandle,
             NULL,
             ControllerHandle,
             NULL,
             &HandleCount,
             &HandleBuffer,
             &HandleType
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Count the number of handles that match the attributes in Mask
  //
  for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
    if ((HandleType[HandleIndex] & Mask) == Mask) {
      (*MatchingHandleCount)++;
    }
  }

  //
  // If no handles match the attributes in Mask then return EFI_NOT_FOUND
  //
  if (*MatchingHandleCount == 0) {
    Status = EFI_NOT_FOUND;
    goto Done;
  }

  if (MatchingHandleBuffer == NULL) {
    Status = EFI_SUCCESS;
    goto Done;
  }

  //
  // Allocate a handle buffer for the number of handles that matched the attributes in Mask
  //
  Status = tBS->AllocatePool(
                 EfiBootServicesData,
                 *MatchingHandleCount * sizeof (EFI_HANDLE),
                 (VOID **)MatchingHandleBuffer
                 );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Fill the allocated buffer with the handles that matched the attributes in Mask
  //
  *MatchingHandleCount = 0;
  for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
    if ((HandleType[HandleIndex] & Mask) == Mask) {
      (*MatchingHandleBuffer)[(*MatchingHandleCount)++] = HandleBuffer[HandleIndex];
    }
  }

  Status = EFI_SUCCESS;

Done:

  //
  // Free the buffers alocated by LibScanHandleDatabase()
  //
  if (HandleBuffer != NULL) {
    tBS->FreePool(HandleBuffer);
  }

  if (HandleType != NULL) {
    tBS->FreePool(HandleType);
  }

  return Status;
}


EFI_STATUS
LibGetManagingDriverBindingHandles (
  EFI_HANDLE  ControllerHandle,
  UINTN       *DriverBindingHandleCount,
  EFI_HANDLE  **DriverBindingHandleBuffer
  )

{
  return LibGetHandleDatabaseSubset (
           NULL,
           ControllerHandle,
           EFI_HANDLE_TYPE_DRIVER_BINDING_HANDLE | EFI_HANDLE_TYPE_DEVICE_DRIVER,
           DriverBindingHandleCount,
           DriverBindingHandleBuffer
           );
}

EFI_STATUS
LibGetParentControllerHandles (
  EFI_HANDLE  ControllerHandle,
  UINTN       *ParentControllerHandleCount,
  EFI_HANDLE  **ParentControllerHandleBuffer
  )

{
  return LibGetHandleDatabaseSubset (
           NULL,
           ControllerHandle,
           EFI_HANDLE_TYPE_PARENT_HANDLE,
           ParentControllerHandleCount,
           ParentControllerHandleBuffer
           );
}

EFI_STATUS
LibGetManagedChildControllerHandles (
  EFI_HANDLE  DriverBindingHandle,
  EFI_HANDLE  ControllerHandle,
  UINTN       *ChildControllerHandleCount,
  EFI_HANDLE  **ChildControllerHandleBuffer
  )

{
  return LibGetHandleDatabaseSubset (
           DriverBindingHandle,
           ControllerHandle,
           EFI_HANDLE_TYPE_CHILD_HANDLE | EFI_HANDLE_TYPE_DEVICE_HANDLE,
           ChildControllerHandleCount,
           ChildControllerHandleBuffer
           );
}

EFI_STATUS
LibGetManagedControllerHandles (
  EFI_HANDLE  DriverBindingHandle,
  UINTN       *ControllerHandleCount,
  EFI_HANDLE  **ControllerHandleBuffer
  )

{
  return LibGetHandleDatabaseSubset (
           DriverBindingHandle,
           NULL,
           EFI_HANDLE_TYPE_CONTROLLER_HANDLE | EFI_HANDLE_TYPE_DEVICE_HANDLE,
           ControllerHandleCount,
           ControllerHandleBuffer
           );
}

EFI_STATUS
LibGetChildControllerHandles (
  EFI_HANDLE  ControllerHandle,
  UINTN       *HandleCount,
  EFI_HANDLE  **HandleBuffer
  )

{
  EFI_STATUS  Status;
  UINTN       HandleIndex;
  UINTN       DriverBindingHandleCount;
  EFI_HANDLE  *DriverBindingHandleBuffer;
  UINTN       DriverBindingHandleIndex;
  UINTN       ChildControllerHandleCount;
  EFI_HANDLE  *ChildControllerHandleBuffer;
  UINTN       ChildControllerHandleIndex;
  BOOLEAN     Found;

  *HandleCount  = 0;
  *HandleBuffer = NULL;

  Status = LibGetManagingDriverBindingHandles (
             ControllerHandle,
             &DriverBindingHandleCount,
             &DriverBindingHandleBuffer
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = tBS->LocateHandleBuffer (
                 AllHandles,
                 NULL,
                 NULL,
                 HandleCount,
                 HandleBuffer
                 );
  if (EFI_ERROR (Status)) {
    tBS->FreePool (DriverBindingHandleBuffer);
    return Status;
  }

  *HandleCount = 0;
  for (DriverBindingHandleIndex = 0; DriverBindingHandleIndex < DriverBindingHandleCount; DriverBindingHandleIndex++) {
    Status = LibGetManagedChildControllerHandles (
               DriverBindingHandleBuffer[DriverBindingHandleIndex],
               ControllerHandle,
               &ChildControllerHandleCount,
               &ChildControllerHandleBuffer
               );
    if (EFI_ERROR (Status)) {
      continue;
    }

    for (ChildControllerHandleIndex = 0; ChildControllerHandleIndex < ChildControllerHandleCount; ChildControllerHandleIndex++) {
      Found = FALSE;
      for (HandleIndex = 0; HandleIndex < *HandleCount; HandleIndex++) {
        if ((*HandleBuffer)[HandleIndex] == ChildControllerHandleBuffer[ChildControllerHandleIndex]) {
          Found = TRUE;
        }
      }
      if (!Found) {
        (*HandleBuffer)[(*HandleCount)++] = ChildControllerHandleBuffer[ChildControllerHandleIndex];
      }
    }

    tBS->FreePool (ChildControllerHandleBuffer);
  }

  tBS->FreePool (DriverBindingHandleBuffer);

  return EFI_SUCCESS;
}

