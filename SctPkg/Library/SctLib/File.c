/** @file

  Copyright 2006 - 2015 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2014, ARM Ltd. All rights reserved.<BR>
  Copyright (c) 2014 - 2015, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

#include "SctLibInternal.h"

EFI_FILE_HANDLE
SctOpenRoot (
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

/*
  Open a file by name, where the name includes a shell filesystem mapping such
  as "fs0" separated from the rest of the path by a ':'.
*/
EFI_STATUS
SctOpenFileByName (
  IN  CHAR16                            *FileName,
  OUT EFI_FILE_PROTOCOL                 **FileHandle,
  IN UINT64                             OpenMode,
  IN UINT64                             Attributes
  )
{
  EFI_STATUS                       Status;
  UINTN                            MapNameLength;
  CHAR16                          *MapName;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume;
  EFI_FILE_PROTOCOL               *Root;

  //
  // Create a copy of the map name
  //

  // Find the length of the map name
  MapNameLength = 0;
  while (FileName[MapNameLength] && FileName[MapNameLength] != L':') {
    MapNameLength++;
  }
  if (!FileName[MapNameLength]) {
    // No ':' in FileName
    return EFI_INVALID_PARAMETER;
  }

  MapName = SctAllocateCopyPool ((MapNameLength + 1) * sizeof (CHAR16), FileName);
  if (MapName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  MapName[MapNameLength] = L'\0';

  //
  // Find the filesystem
  //
  Status = SctShellMapToDevicePath (MapName, &DevicePath);
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = SctDevicePathToInterface (
             &gEfiSimpleFileSystemProtocolGuid,
             DevicePath,
             (VOID **)&Volume
             );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  //
  // Open the file
  //

  Status = Volume->OpenVolume (Volume, &Root);
  if (EFI_ERROR (Status)) {
    goto Error;
  }
  Status = Root->Open (Root, FileHandle, FileName + MapNameLength + 1, OpenMode, Attributes);

Error:
  SctFreePool (MapName);
  return Status;
}

EFI_STATUS
SctCloseFile (
  IN EFI_FILE_HANDLE     FileHandle
  )
{
  ASSERT (FileHandle != NULL);
  return FileHandle->Close (FileHandle);
}

EFI_STATUS
SctReadFile (
  IN EFI_FILE_HANDLE      FileHandle,
  IN OUT UINTN            *ReadSize,
  OUT VOID                *Buffer
  )
{
  ASSERT (FileHandle != NULL);
  return FileHandle->Read (FileHandle, ReadSize, Buffer);
}

EFI_STATUS
SctWriteFile (
  IN EFI_FILE_HANDLE    FileHandle,
  IN OUT UINTN          *BufferSize,
  OUT VOID              *Buffer
  )
{
  ASSERT (FileHandle != NULL);
  return FileHandle->Write (
                      FileHandle,
                      BufferSize,
                      Buffer
                      );
}

EFI_STATUS
SctFlushFile (
  IN EFI_FILE_HANDLE FileHandle
  )
{
  ASSERT (FileHandle != NULL);
  return FileHandle->Flush (FileHandle);
}

/*++

Routine Description:

  Function gets the file information from an open file descriptor, and stores it
  in a buffer allocated from pool.

Arguments:

  FileHandle         - A file handle

Returns:

  A pointer to a buffer with file information or NULL is returned

--*/
EFI_STATUS
SctGetFileInfo (
  IN  EFI_FILE_HANDLE      FileHandle,
  OUT EFI_FILE_INFO      **FileInfo
  )
{
  EFI_STATUS    Status;
  UINTN         BufferSize;

  ASSERT (FileHandle != NULL);
  //
  // Initialize for SctGrowBuffer loop
  //
  *FileInfo      = NULL;
  BufferSize  = SIZE_OF_EFI_FILE_INFO + 200;

  //
  // Call the real function
  //
  while (SctGrowBuffer (&Status, (VOID **) FileInfo, BufferSize)) {
    Status = FileHandle->GetInfo (
                          FileHandle,
                          &gEfiFileInfoGuid,
                          &BufferSize,
                          *FileInfo
                          );
  }
  if (EFI_ERROR (Status)) {
    SctFreePool (*FileInfo);
  }
  return Status;
}


EFI_STATUS
SctSetFileInfo (
  IN  EFI_FILE_HANDLE    FileHandle,
  IN  EFI_FILE_INFO      *FileInfo
  )
{
  EFI_STATUS    Status;
  UINTN         BufferSize;

  ASSERT (FileHandle != NULL);

  BufferSize  = (UINTN)FileInfo->Size;

  //
  // Call the real function
  //

  Status = FileHandle->SetInfo (
                          FileHandle,
                          &gEfiFileInfoGuid,
                          BufferSize,
                          FileInfo
                          );
  return Status;
}

EFI_STATUS
SctCreateDirectory (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  Create a directory.

--*/
{
  EFI_STATUS        Status;
  CHAR16            *StringEnd;
  CHAR16            CSaved;
  EFI_FILE_HANDLE   Handle;

  //
  // Try to open the directory
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                      EFI_FILE_DIRECTORY
                      );
  if (!EFI_ERROR (Status)) {
    RootDir->Close (Handle);
    return Status;
  }

  if (Status != EFI_NOT_FOUND) {
    return Status;
  }

  //
  // Create the parent directory
  //
  StringEnd = FileName + SctStrLen (FileName) - 1;
  while (StringEnd >= FileName) {
    if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
      break;
    }
    StringEnd --;
  }

  if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
    CSaved = *StringEnd;
    *StringEnd = L'\0';

    if (SctStrLen (FileName) != 0) {
      Status = SctCreateDirectory (RootDir, FileName);
      if (EFI_ERROR (Status)) {
        *StringEnd = CSaved;
        return Status;
      }
    }

    *StringEnd = CSaved;
  }

  //
  // Create the directory
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
                      EFI_FILE_DIRECTORY
                      );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  RootDir->Close (Handle);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
SctCreateFile (
  IN EFI_FILE_PROTOCOL            *RootDir,
  IN CHAR16                       *FileName,
  OUT EFI_FILE_HANDLE             *Handle
  )
/*++

Routine Description:

  Create a file.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *StringEnd;
  CHAR16      CSaved;

  //
  // Create the parent directory
  //
  StringEnd = FileName + SctStrLen (FileName) - 1;
  while (StringEnd >= FileName) {
    if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
      break;
    }
    StringEnd --;
  }

  if ((*StringEnd == L'\\') || (*StringEnd == L'/')) {
    CSaved = *StringEnd;
    *StringEnd = L'\0';

    if (SctStrLen (FileName) != 0) {
      Status = SctCreateDirectory (RootDir, FileName);
      if (EFI_ERROR (Status)) {
        *StringEnd = CSaved;
        return Status;
      }
    }

    *StringEnd = CSaved;
  }

  //
  // Open the file
  //
  Status = RootDir->Open (
                      RootDir,
                      Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                      0
                      );
  if (!EFI_ERROR (Status)) {
    //
    // If the file already exists, delete it
    //
    (*Handle)->Delete (*Handle);
  }

  //
  // Create the file
  //
  Status = RootDir->Open (
                      RootDir,
                      Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
                      0
                      );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
