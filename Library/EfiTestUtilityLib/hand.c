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

  hand.c

Abstract:

  Handle operation functions

--*/

#include "lib.h"


EFI_STATUS
LibLocateProtocol (
  IN  EFI_GUID    *ProtocolGuid,
  OUT VOID        **Interface
  )
/*++

Routine Description:

  Find the first instance of this Protocol in the system and return it's interface

Arguments:

  ProtocolGuid    - Provides the protocol to search for
  Interface       - On return, a pointer to the first interface that matches ProtocolGuid

Returns:

  EFI_SUCCESS     - A protocol instance matching ProtocolGuid was found

  EFI_NOT_FOUND   - No protocol instances were found that match ProtocolGuid

--*/
{
  EFI_STATUS      Status;
  UINTN           NumberHandles, Index;
  EFI_HANDLE      *Handles;


  *Interface = NULL;
  Status = LibLocateHandle (ByProtocol, ProtocolGuid, NULL, &NumberHandles, &Handles);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_INFO, "LibLocateProtocol: Handle not found\n"));
    return Status;
  }

  for (Index=0; Index < NumberHandles; Index++) {
    Status = tBS->HandleProtocol(
                   Handles[Index],
                   ProtocolGuid,
                   Interface
                   );

    if (!EFI_ERROR(Status)) {
      break;
    }
  }

  if (Handles) {
    FreePool (Handles);
  }

  return Status;
}


EFI_STATUS
LibLocateHandle (
  IN EFI_LOCATE_SEARCH_TYPE       SearchType,
  IN EFI_GUID                     *Protocol OPTIONAL,
  IN VOID                         *SearchKey OPTIONAL,
  IN OUT UINTN                    *NoHandles,
  OUT EFI_HANDLE                  **Buffer
  )
/*++

Routine Description:

  Function returns an array of handles that support the requested protocol
  in a buffer allocated from pool.

Arguments:

  SearchType           - Specifies which handle(s) are to be returned.
  Protocol             - Provides the protocol to search by.
                         This parameter is only valid for SearchType ByProtocol.
  SearchKey            - Supplies the search key depending on the SearchType.
  NoHandles            - The number of handles returned in Buffer.
  Buffer               - A pointer to the buffer to return the requested array of
                         handles that support Protocol.

Returns:

  EFI_SUCCESS           - The result array of handles was returned.
  EFI_NOT_FOUND         - No handles match the search.
  EFI_OUT_OF_RESOURCES - There is not enough pool memory to store the matching results.

--*/
{
  EFI_STATUS          Status;
  UINTN               BufferSize;

  //
  // Initialize for GrowBuffer loop
  //

  Status = EFI_SUCCESS;
  *Buffer = NULL;
  BufferSize = 50 * sizeof(EFI_HANDLE);

  //
  // Call the real function
  //

  while (GrowBuffer (&Status, (VOID **) Buffer, BufferSize)) {
    Status = tBS->LocateHandle (
                   SearchType,
                   Protocol,
                   SearchKey,
                   &BufferSize,
                   *Buffer
                   );
  }

  *NoHandles = BufferSize / sizeof (EFI_HANDLE);
  if (EFI_ERROR(Status)) {
    *NoHandles = 0;
  }

  return Status;
}

EFI_STATUS
LibLocateHandleByDiskSignature (
  IN UINT8                        MBRType,
  IN UINT8                        SignatureType,
  IN VOID                         *Signature,
  IN OUT UINTN                    *NoHandles,
  OUT EFI_HANDLE                  **Buffer
  )
/*++

Routine Description:

  Function returns an array of handles that support the requested protocol in
  a buffer allocated from pool.

Arguments:

  MBRType              - Specifies the type of MBR to search for.  This can either
                         be the PC AT compatible MBR or an EFI Partition Table Header.
  SignatureType        - Specifies the type of signature to look for in the MBR.
                         This can either be a 32 bit signature, or a GUID signature.
  Signature            - A pointer to a 32 bit disk signature or a pointer to a GUID
                         disk signature. The type depends on SignatureType.
  NoHandles            - The number of handles returned in Buffer.
  Buffer               - A pointer to the buffer to return the requested array of
                         handles that support Protocol.

Returns:

  EFI_SUCCESS           - The result array of handles was returned.
  EFI_NOT_FOUND         - No handles match the search.
  EFI_OUT_OF_RESOURCES - There is not enough pool memory to store the matching results.

--*/
{
  EFI_STATUS                  Status;
  UINTN                       BufferSize;
  UINTN                       NoBlockIoHandles;
  EFI_HANDLE                  *BlockIoBuffer;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
  UINTN                       Index;
  EFI_DEVICE_PATH_PROTOCOL    *Start, *Next, *DevPath;
  HARDDRIVE_DEVICE_PATH       *HardDriveDevicePath;
  BOOLEAN                     Match;
  BOOLEAN                     PreviousNodeIsHardDriveDevicePath;

  //
  // Initialize for GrowBuffer loop
  //

  BlockIoBuffer = NULL;
  BufferSize = 50 * sizeof(EFI_HANDLE);

  //
  // Call the real function
  //

  while (GrowBuffer (&Status, (VOID **)&BlockIoBuffer, BufferSize)) {

    //
    // Get list of device handles that support the BLOCK_IO Protocol.
    //
    Status = tBS->LocateHandle (
                   ByProtocol,
                   &gEfiBlockIoProtocolGuid,
                   NULL,
                   &BufferSize,
                   BlockIoBuffer
                   );
  }

  NoBlockIoHandles = BufferSize / sizeof (EFI_HANDLE);
  if (EFI_ERROR(Status)) {
    NoBlockIoHandles = 0;
  }

  //
  // If there was an error or there are no device handles that support
  // the BLOCK_IO Protocol, then return.
  //
  if (NoBlockIoHandles == 0) {
    FreePool(BlockIoBuffer);
    *NoHandles = 0;
    *Buffer = NULL;
    return Status;
  }

  //
  // Loop through all the device handles that support the BLOCK_IO Protocol
  //

  *NoHandles = 0;

  for(Index=0;Index<NoBlockIoHandles;Index++) {

    Status = tBS->HandleProtocol (BlockIoBuffer[Index],
                   &gEfiDevicePathProtocolGuid,
                   (VOID*)&DevicePath
                   );

    //
    // Search DevicePath for a Hard Drive Media Device Path node.
    // If one is found, then see if it matches the signature that was
    // passed in.  If it does match, and the next node is the End of the
    // device path, and the previous node is not a Hard Drive Media Device
    // Path, then we have found a match.
    //

    Match = FALSE;

    if (DevicePath != NULL) {

      PreviousNodeIsHardDriveDevicePath = FALSE;

      DevPath = DevicePath;
      Start = DevPath;
      //
      // Check for end of device path type
      //

      for (; ;) {

        if ((DevicePathType(DevPath) == MEDIA_DEVICE_PATH) &&
           (DevicePathSubType(DevPath) == MEDIA_HARDDRIVE_DP)) {

          HardDriveDevicePath = (HARDDRIVE_DEVICE_PATH *)(DevPath);

          if (PreviousNodeIsHardDriveDevicePath == FALSE) {

            Next = NextDevicePathNode(DevPath);
            if (IsDevicePathEndType(Next)) {
              if ((HardDriveDevicePath->MBRType == MBRType) &&
                (HardDriveDevicePath->SignatureType == SignatureType)) {
                switch(SignatureType) {
                  case SIGNATURE_TYPE_MBR:
                    if (*((UINT32 *)(Signature)) == *(UINT32 *)(&(HardDriveDevicePath->Signature[0]))) {
                      Match = TRUE;
                    }
                    break;
                  case SIGNATURE_TYPE_GUID:
                    if (CompareGuid((EFI_GUID *)Signature,(EFI_GUID *)(&(HardDriveDevicePath->Signature[0]))) == 0) {
                      Match = TRUE;
                    }
                    break;
                }
              }
            }
          }
          PreviousNodeIsHardDriveDevicePath = TRUE;
        } else {
          PreviousNodeIsHardDriveDevicePath = FALSE;
        }

        if (IsDevicePathEnd(DevPath)) {
          break;
        }

        DevPath = NextDevicePathNode(DevPath);
      }

    }

    if (Match == FALSE) {
      BlockIoBuffer[Index] = NULL;
    } else {
      *NoHandles = *NoHandles + 1;
    }
  }

  //
  // If there are no matches, then return
  //

  if (*NoHandles == 0) {
    FreePool(BlockIoBuffer);
    *NoHandles = 0;
    *Buffer = NULL;
    return EFI_SUCCESS;
  }

  //
  // Allocate space for the return buffer of device handles.
  //

  *Buffer = AllocatePool(*NoHandles * sizeof(EFI_HANDLE));

  if (*Buffer == NULL) {
    FreePool(BlockIoBuffer);
    *NoHandles = 0;
    *Buffer = NULL;
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Build list of matching device handles.
  //

  *NoHandles = 0;
  for(Index=0;Index<NoBlockIoHandles;Index++) {
    if (BlockIoBuffer[Index] != NULL) {
      (*Buffer)[*NoHandles] = BlockIoBuffer[Index];
      *NoHandles = *NoHandles + 1;
    }
  }

  FreePool(BlockIoBuffer);

  return EFI_SUCCESS;
}


EFI_FILE_HANDLE
LibOpenRoot (
  IN EFI_HANDLE                   DeviceHandle
  )
/*++

Routine Description:

  Function opens and returns a file handle to the root directory of a volume.

Arguments:

  DeviceHandle         - A handle for a device

Returns:

  A valid file handle or NULL is returned

--*/
{
  EFI_STATUS                      Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume;
  EFI_FILE_HANDLE                 File;


  File = NULL;

  //
  // File the file system interface to the device
  //
  Status = tBS->HandleProtocol (
                 DeviceHandle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 (VOID*)&Volume
                 );

  //
  // Open the root directory of the volume
  //
  if (!EFI_ERROR(Status)) {
    Status = Volume->OpenVolume(
                       Volume,
                       &File
                       );
  }

  //
  // Done
  //
  return EFI_ERROR(Status) ? NULL : File;
}

EFI_FILE_INFO *
LibFileInfo (
  IN EFI_FILE_HANDLE      FHand
  )
/*++

Routine Description:

  Function gets the file information from an open file descriptor, and stores it
  in a buffer allocated from pool.

Arguments:

  Fhand         - A file handle

Returns:

  A pointer to a buffer with file information or NULL is returned

--*/
{
  EFI_STATUS              Status;
  EFI_FILE_INFO           *Buffer;
  UINTN                   BufferSize;

  //
  // Initialize for GrowBuffer loop
  //

  Buffer = NULL;
  BufferSize = SIZE_OF_EFI_FILE_INFO + 200;

  //
  // Call the real function
  //
  while (GrowBuffer (&Status, (VOID **) &Buffer, BufferSize)) {
    Status = FHand->GetInfo (
                      FHand,
                      &tGenericFileInfo,
                      &BufferSize,
                      Buffer
                      );
  }

  return Buffer;
}


EFI_FILE_SYSTEM_INFO *
LibFileSystemInfo (
  IN EFI_FILE_HANDLE      FHand
  )
/*++

Routine Description:

  Function gets the file system information from an open file descriptor,
  and stores it in a buffer allocated from pool.

Arguments:

  Fhand         - A file handle

Returns:

  A pointer to a buffer with file information or NULL is returned

--*/
{
  EFI_STATUS              Status;
  EFI_FILE_SYSTEM_INFO    *Buffer;
  UINTN                   BufferSize;

  //
  // Initialize for GrowBuffer loop
  //
  Buffer = NULL;
  BufferSize = SIZE_OF_EFI_FILE_SYSTEM_INFO + 200;

  //
  // Call the real function
  //
  while (GrowBuffer (&Status, (VOID **) &Buffer, BufferSize)) {
    Status = FHand->GetInfo (
                      FHand,
                      &gtEfiFileSystemInfoGuid,
                      &BufferSize,
                      Buffer
                      );
  }
  return Buffer;
}


EFI_FILE_SYSTEM_VOLUME_LABEL_INFO *
LibFileSystemVolumeLabelInfo (
  IN EFI_FILE_HANDLE      FHand
  )
/*++

Routine Description:

  Function gets the file system information from an open file descriptor,
  and stores it in a buffer allocated from pool.

Arguments:

  Fhand         - A file handle

Returns:

  A pointer to a buffer with file information or NULL is returned

--*/
{
  EFI_STATUS                        Status;
  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO *Buffer;
  UINTN                             BufferSize;

  //
  // Initialize for GrowBuffer loop
  //
  Buffer = NULL;
  BufferSize = SIZE_OF_EFI_FILE_SYSTEM_VOLUME_LABEL_INFO + 200;

  //
  // Call the real function
  //
  while (GrowBuffer (&Status, (VOID **) &Buffer, BufferSize)) {
    Status = FHand->GetInfo (
                      FHand,
                      &gtEfiFileSystemVolumeLabelInfoGuid,
                      &BufferSize,
                      Buffer
                      );
  }
  return Buffer;
}


EFI_STATUS
LibInstallProtocolInterfaces (
  IN OUT EFI_HANDLE           *Handle,
  ...
  )
/*++

Routine Description:

  Function installs one or more protocol interfaces into the boot services environment.

Arguments:

  Handle               - The handle to install the new protocol interfaces on, or NULL if a
                         new handle is to be allocated.

  ...                  - A variable argument list containing pairs of protocol GUIDs and
                         protocol interfaces.

Returns:

  EFI_SUCCESS           - All the protocol interfaces were installed.
  EFI_OUT_OF_RESOURCES - There was not enough memory in pool to install all the protocols.

--*/
{
  VA_LIST         args;
  EFI_STATUS      Status;
  EFI_GUID        *Protocol;
  VOID            *Interface;
  EFI_TPL         OldTpl;
  UINTN           Index;
  EFI_HANDLE      OldHandle;

  //
  // Syncronize with notifcations
  //

  OldTpl = tBS->RaiseTPL(EFI_TPL_NOTIFY);
  OldHandle = *Handle;

  //
  // Install the protocol interfaces
  //
  Index = 0;
  Status = EFI_SUCCESS;
  VA_START (args, Handle);

  while (!EFI_ERROR(Status)) {

    //
    // If protocol is NULL, then it's the end of the list
    //
    Protocol = VA_ARG (args, EFI_GUID *);
    if (!Protocol) {
      break;
    }

    Interface = VA_ARG (args, VOID *);

    //
    // Install it
    //
    DEBUG((EFI_D_INFO, "LibInstallProtocolInterface: %d %x\n", Protocol, Interface));
    Status = tBS->InstallProtocolInterface (
                   Handle,
                   Protocol,
                   EFI_NATIVE_INTERFACE,
                   Interface
                   );
    if (EFI_ERROR(Status)) {
      break;
    }

    Index += 1;
  }

  //
  // If there was an error, remove all the interfaces that were
  // installed without any errors
  //

  if (EFI_ERROR(Status)) {
    VA_START (args, Handle);
    while (Index) {
      Protocol = VA_ARG (args, EFI_GUID *);
      Interface = VA_ARG (args, VOID *);
      tBS->UninstallProtocolInterface (
            *Handle,
            Protocol,
            Interface
            );
      Index -= 1;
    }
    *Handle = OldHandle;
  }

  //
  // Done
  //

  tBS->RestoreTPL(OldTpl);
  return Status;
}


VOID
LibUninstallProtocolInterfaces (
  IN EFI_HANDLE           Handle,
  ...
  )
/*++

Routine Description:

  Function removes one or more protocol interfaces into the boot services environment.

Arguments:

  Handle               - The handle to remove the protocol interfaces from.

  ...                  - A variable argument list containing pairs of protocol GUIDs and
                         protocol interfaces.

Returns:

  EFI_SUCCESS           - All the protocol interfaces were removed.
  EFI_OUT_OF_RESOURCES - One of the protocol interfaces could not be found.

--*/
{
  VA_LIST         args;
  EFI_STATUS      Status;
  EFI_GUID        *Protocol;
  VOID            *Interface;

  VA_START (args, Handle);
  for (; ;) {

    //
    // If protocol is NULL, then it's the end of the list
    //
    Protocol = VA_ARG (args, EFI_GUID *);
    if (!Protocol) {
      break;
    }

    Interface = VA_ARG (args, VOID *);

    //
    // Uninstall it
    //
    Status = tBS->UninstallProtocolInterface (Handle, Protocol, Interface);
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR, "LibUninstallProtocolInterfaces: failed %g, %r\n", Protocol, Handle));
    }
  }
}


EFI_STATUS
LibReinstallProtocolInterfaces (
  IN OUT EFI_HANDLE           *Handle,
  ...
  )
/*++

Routine Description:

  Function replaces one or more protocol interfaces into the boot services environment.

Arguments:

  Handle               - The handle to reinstall the protocol interfaces to.

  ...                  - A variable argument list containing pairs of protocol GUIDs and
                         protocol interfaces.

Returns:

  EFI_SUCCESS           - All the protocol interfaces were replaced.
  EFI_OUT_OF_RESOURCES - One of the protocol interfaces could not be found.

--*/
{
  VA_LIST         args;
  EFI_STATUS      Status;
  EFI_GUID        *Protocol;
  VOID            *OldInterface, *NewInterface;
  EFI_TPL         OldTpl;
  UINTN           Index;

  //
  // Syncronize with notifcations
  //
  OldTpl = tBS->RaiseTPL(EFI_TPL_NOTIFY);

  //
  // Install the protocol interfaces
  //
  Index = 0;
  Status = EFI_SUCCESS;
  VA_START (args, Handle);

  while (!EFI_ERROR(Status)) {

    //
    // If protocol is NULL, then it's the end of the list
    //
    Protocol = VA_ARG (args, EFI_GUID *);
    if (!Protocol) {
      break;
    }

    OldInterface = VA_ARG (args, VOID *);
    NewInterface = VA_ARG (args, VOID *);

    //
    // Reinstall it
    //
    Status = tBS->ReinstallProtocolInterface (
                   Handle,
                   Protocol,
                   OldInterface,
                   NewInterface
                   );
    if (EFI_ERROR(Status)) {
      break;
    }
    Index += 1;
  }

  //
  // If there was an error, undo all the interfaces that were
  // reinstalled without any errors
  //
  if (EFI_ERROR(Status)) {
    VA_START (args, Handle);
    while (Index) {
      Protocol = VA_ARG (args, EFI_GUID *);
      OldInterface = VA_ARG (args, VOID *);
      NewInterface = VA_ARG (args, VOID *);

      tBS->ReinstallProtocolInterface (
            Handle,
            Protocol,
            NewInterface,
            OldInterface
            );

      Index -= 1;
    }
  }

  //
  // Done
  //

  tBS->RestoreTPL(OldTpl);
  return Status;
}
