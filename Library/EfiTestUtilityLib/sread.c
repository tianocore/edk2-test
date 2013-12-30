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

  sread.c

Abstract:

  Simple read file access

--*/

#include "lib.h"

#define SIMPLE_READ_SIGNATURE       EFI_SIGNATURE_32('t','s','r','d')
typedef struct _SIMPLE_READ_FILE {
    UINTN               Signature;
    BOOLEAN             FreeBuffer;
    VOID                *Source;
    UINTN               SourceSize;
    EFI_FILE_HANDLE     FileHandle;
} SIMPLE_READ_HANDLE;



EFI_STATUS
OpenSimpleReadFile (
    IN BOOLEAN                        BootPolicy,
    IN VOID                           *SourceBuffer   OPTIONAL,
    IN UINTN                          SourceSize,
    IN OUT EFI_DEVICE_PATH_PROTOCOL   **FilePath,
    OUT EFI_HANDLE                    *DeviceHandle,
    OUT SIMPLE_READ_FILE              *SimpleReadHandle
    )
/*++

Routine Description:

    Opens a file for (simple) reading.  The simple read abstraction
    will access the file either from a memory copy, from a file
    system interface, or from the load file interface.

Arguments:

Returns:

    A handle to access the file

--*/
{
    SIMPLE_READ_HANDLE          *FHand;
    EFI_DEVICE_PATH_PROTOCOL    *UserFilePath;
    EFI_DEVICE_PATH_PROTOCOL    *TempFilePath;
    EFI_DEVICE_PATH_PROTOCOL    *TempFilePathPtr;
    FILEPATH_DEVICE_PATH        *FilePathNode;
    EFI_FILE_HANDLE             FileHandle, LastHandle;
    EFI_STATUS                  Status;
    EFI_LOAD_FILE_PROTOCOL      *LoadFile;

    FHand = NULL;
    UserFilePath = *FilePath;

    //
    // Allocate a new simple read handle structure
    //

    FHand = AllocateZeroPool (sizeof(SIMPLE_READ_HANDLE));
    if (!FHand) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Done;
    }

    *SimpleReadHandle = (SIMPLE_READ_FILE) FHand;
    FHand->Signature = SIMPLE_READ_SIGNATURE;

    //
    // If the caller passed a copy of the file, then just use it
    //

    if (SourceBuffer) {
        FHand->Source = SourceBuffer;
        FHand->SourceSize = SourceSize;
        *DeviceHandle = NULL;
        Status = EFI_SUCCESS;
        goto Done;
    }

    //
    // Attempt to access the file via a file system interface
    //

    FileHandle = NULL;
    Status = tBS->LocateDevicePath (&gEfiSimpleFileSystemProtocolGuid, FilePath, DeviceHandle);
    if (!EFI_ERROR(Status)) {
        FileHandle = LibOpenRoot (*DeviceHandle);
    }

    Status = FileHandle ? EFI_SUCCESS : EFI_UNSUPPORTED;

    //
    // To access as a filesystem, the filepath should only
    // contain filepath components.  Follow the filepath nodes
    // and find the target file
    //

    FilePathNode = (FILEPATH_DEVICE_PATH *) *FilePath;
    while (!IsDevicePathEnd(&FilePathNode->Header)) {

        //
        // For filesystem access each node should be a filepath component
        //

        if (DevicePathType(&FilePathNode->Header) != MEDIA_DEVICE_PATH ||
            DevicePathSubType(&FilePathNode->Header) != MEDIA_FILEPATH_DP) {
            Status = EFI_UNSUPPORTED;
        }

        //
        // If there's been an error, stop
        //

        if (EFI_ERROR(Status)) {
            break;
        }

        //
        // Open this file path node
        //

        LastHandle = FileHandle;
        FileHandle = NULL;

        Status = LastHandle->Open (
                        LastHandle,
                        &FileHandle,
                        FilePathNode->PathName,
                        EFI_FILE_MODE_READ,
                        0
                        );

        //
        // Close the last node
        //

        LastHandle->Close (LastHandle);

        //
        // Get the next node
        //

        FilePathNode = (FILEPATH_DEVICE_PATH *) NextDevicePathNode(&FilePathNode->Header);
    }

    //
    // If success, return the FHand
    //

    if (!EFI_ERROR(Status)) {
        ASSERT(FileHandle);
        FHand->FileHandle = FileHandle;
        goto Done;
    }

    //
    // Cleanup from filesystem access
    //

    if (FileHandle) {
        FileHandle->Close (FileHandle);
        FileHandle = NULL;
        *FilePath = UserFilePath;
    }

    //
    // If the error is something other then unsupported, return it
    //

    if (Status != EFI_UNSUPPORTED) {
        goto Done;
    }

    //
    // Attempt to access the file via the load file protocol
    //

    Status = LibDevicePathToInterface (&gEfiLoadFileProtocolGuid, *FilePath, (VOID*)&LoadFile);
    if (!EFI_ERROR(Status)) {

        TempFilePath = DuplicateDevicePath (*FilePath);

        TempFilePathPtr = TempFilePath;

        Status = tBS->LocateDevicePath (&gEfiLoadFileProtocolGuid, &TempFilePath, DeviceHandle);

        FreePool (TempFilePathPtr);

        //
        // Determine the size of buffer needed to hold the file
        //

        SourceSize = 0;
        Status = LoadFile->LoadFile (
                    LoadFile,
                    *FilePath,
                    BootPolicy,
                    &SourceSize,
                    NULL
                    );

        //
        // We expect a buffer too small error to inform us
        // of the buffer size needed
        //

        if (Status == EFI_BUFFER_TOO_SMALL) {
            SourceBuffer = AllocatePool (SourceSize);

            if (SourceBuffer) {
                FHand->FreeBuffer = TRUE;
                FHand->Source = SourceBuffer;
                FHand->SourceSize = SourceSize;

                Status = LoadFile->LoadFile (
                            LoadFile,
                            *FilePath,
                            BootPolicy,
                            &SourceSize,
                            SourceBuffer
                            );
            }
        }

        //
        // If success, return FHand
        //

        if (!EFI_ERROR(Status) || Status == EFI_ALREADY_STARTED) {
            goto Done;
        }
    }

    //
    // Nothing else to try
    //

    DEBUG ((EFI_D_LOAD|EFI_D_WARN, "OpenSimpleReadFile: Device did not support a known load protocol\n"));
    Status = EFI_UNSUPPORTED;

Done:

    //
    // If the file was not accessed, clean up
    //
    if (EFI_ERROR(Status) && (Status != EFI_ALREADY_STARTED)) {
        if (FHand) {
            if (FHand->FreeBuffer) {
                FreePool (FHand->Source);
            }

            FreePool (FHand);
        }
    }

    return Status;
}

EFI_STATUS
ReadSimpleReadFile (
    IN SIMPLE_READ_FILE     UserHandle,
    IN UINTN                Offset,
    IN OUT UINTN            *ReadSize,
    OUT VOID                *Buffer
    )
{
    UINTN                   EndPos;
    SIMPLE_READ_HANDLE      *FHand;
    EFI_STATUS              Status;

    FHand = UserHandle;
    ASSERT (FHand->Signature == SIMPLE_READ_SIGNATURE);
    if (FHand->Source) {

        //
        // Move data from our local copy of the file
        //

        EndPos = Offset + *ReadSize;
        if (EndPos > FHand->SourceSize) {
            *ReadSize = FHand->SourceSize - Offset;
            if (Offset >= FHand->SourceSize) {
                *ReadSize = 0;
            }
        }

        CopyMem (Buffer, (CHAR8 *) FHand->Source + Offset, *ReadSize);
        Status = EFI_SUCCESS;

    } else {

        //
        // Read data from the file
        //

        Status = FHand->FileHandle->SetPosition (FHand->FileHandle, Offset);

        if (!EFI_ERROR(Status)) {
            Status = FHand->FileHandle->Read (FHand->FileHandle, ReadSize, Buffer);
        }
    }

    return Status;
}


VOID
CloseSimpleReadFile (
    IN SIMPLE_READ_FILE     UserHandle
    )
{
    SIMPLE_READ_HANDLE      *FHand;

    FHand = UserHandle;
    ASSERT (FHand->Signature == SIMPLE_READ_SIGNATURE);

    //
    // Free any file handle we opened
    //

    if (FHand->FileHandle) {
        FHand->FileHandle->Close (FHand->FileHandle);
    }

    //
    // If we allocated the Source buffer, free it
    //

    if (FHand->FreeBuffer) {
        FreePool (FHand->Source);
    }

    //
    // Done with this simple read file handle
    //

    FreePool (FHand);
}
