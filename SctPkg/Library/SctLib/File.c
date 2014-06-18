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

  Copyright 2006 - 2012 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2013-2014, ARM Ltd. All rights reserved.

--*/

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
  //TODO: Fixme
  return EFI_UNSUPPORTED;
}

EFI_STATUS
SctReadFile (
  IN EFI_FILE_HANDLE      FileHandle,
  IN OUT UINTN            *ReadSize,
  OUT VOID                *Buffer
  )
{
  //TODO: Fixme
  return EFI_UNSUPPORTED;
}

EFI_STATUS
SctWriteFile (
  IN EFI_FILE_HANDLE    FileHandle,
  IN OUT UINTN          *BufferSize,
  OUT VOID              *Buffer
  )
{
  //TODO: Fixme
  return EFI_UNSUPPORTED;
}

EFI_STATUS
SctFlushFile (
  IN EFI_FILE_HANDLE FileHandle
  )
{
  //TODO: Fixme
  return EFI_UNSUPPORTED;
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
