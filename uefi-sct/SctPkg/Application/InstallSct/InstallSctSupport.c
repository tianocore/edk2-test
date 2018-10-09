/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>
  Portions copyright (c) 2014, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  InstallSctSupport.c

Abstract:

  This file provides the support services for the EFI SCT installation.

--*/

#include "InstallSct.h"

#include <Guid/FileSystemInfo.h>

//
// External function implementation
//

EFI_STATUS
GetFreeSpace (
  IN OUT SCT_FILE_VOLUME *FileVolume
  )
{
  EFI_STATUS                        Status;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_FILE_HANDLE                   RootFs;
  EFI_FILE_SYSTEM_INFO              *SystemInfo;
  UINTN                             SystemInfoSize;

  //
  // Get the device path of file system
  //
  Status = SctShellMapToDevicePath (FileVolume->Name, &DevicePath);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Locate the file system protocol
  //
  Status = SctDevicePathToInterface (
             &gEfiSimpleFileSystemProtocolGuid,
             DevicePath,
             (VOID **)&Vol
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Open the file system
  //
  Status = Vol->OpenVolume (Vol, &RootFs);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the system information
  //
  SystemInfoSize = SIZE_OF_EFI_FILE_SYSTEM_INFO + 100;

  SystemInfo = (EFI_FILE_SYSTEM_INFO *) SctAllocatePool (SystemInfoSize);
  if (SystemInfo == NULL) {
    RootFs->Close (RootFs);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RootFs->GetInfo (
                     RootFs,
                     &gEfiFileSystemInfoGuid,
                     &SystemInfoSize,
                     SystemInfo
                     );
  if (EFI_ERROR (Status)) {
    SctFreePool (SystemInfo);
    RootFs->Close (RootFs);
    return Status;
  }

  FileVolume->FreeSpace = SystemInfo->FreeSpace;

  SctFreePool (SystemInfo);
  RootFs->Close (RootFs);

  //
  // Done
  //
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
DirFileExist (
  IN CHAR16             *Name,
  OUT BOOLEAN           *Exist
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;
  EFI_STATUS  CmdStatus;

  //
  // Create command line to list the directory or file
  //
  CmdLine = SctPoolPrint (
              L"LS \"%s\" > NUL",
              Name
              );
  if (CmdLine == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Execute shell command
  //
  Status = SctShellExecute (&gImageHandle,
             CmdLine,
             FALSE,
             NULL,
             &CmdStatus
             );

  if (EFI_ERROR (Status)) {
    SctPrint (L"Error: Could not execute \"%s\"\n", CmdLine);
    SctFreePool (CmdLine);
    return Status;
  }

  //
  // Exist or not?
  //
  if (EFI_ERROR (CmdStatus)) {
    *Exist = FALSE;
  } else {
    *Exist = TRUE;
  }

  SctFreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}


STATIC
EFI_STATUS
RemoveDirFile (
  IN CHAR16             *Name
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;
  EFI_STATUS  CmdStatus;

  //
  // Create command line to delete this directory or file
  //
  CmdLine = SctPoolPrint (
              L"del -q \"%s\"",
              Name
              );
  if (CmdLine == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Execute this shell command
  //
  Status = SctShellExecute (
             &gImageHandle,
             CmdLine,
             FALSE,
             NULL,
             &CmdStatus
             );
  if (EFI_ERROR (Status) || EFI_ERROR (CmdStatus)) {
    SctPrint (L"Error: Could not execute \"%s\"\n", CmdLine);
    SctFreePool (CmdLine);
    return Status;
  }

  SctFreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
BackupDirFile (
  IN CHAR16             *Name
  )
{
  EFI_STATUS  Status;
  EFI_STATUS  CmdStatus;
  CHAR16      *CmdLine;
  CHAR16      *PathName;
  CHAR16      *FileName;
  CHAR16      *TmpName;
  UINTN       Index;
  UINTN       Length;
  BOOLEAN     Exist;

  //
  // Split to the path name and the file name
  //
  PathName = SctStrDuplicate (Name);
  if (PathName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Length   = SctStrLen (PathName);
  FileName = PathName + Length;

  for (Index = 0; Index < Length; Index ++) {
    if (PathName[Length - Index - 1] == L'\\') {
      PathName[Length - Index - 1] = L'\0';
      FileName = PathName + Length - Index;
      break;
    }
  }

  //
  // Find the latest backup number
  //
  for (Index = 0; Index < INSTALL_SCT_MAX_BACKUP; Index ++) {
    //
    // Create the backup file name
    //
    TmpName = SctPoolPrint (
                L"\"%s\\%s.bak%d\"",
                PathName,
                Index,
                FileName
                );
    if (TmpName == NULL) {
      SctFreePool (PathName);
      return EFI_OUT_OF_RESOURCES;
    }

    Status = DirFileExist (TmpName, &Exist);
    if (EFI_ERROR (Status)) {
      SctFreePool (TmpName);
      SctFreePool (PathName);
      return Status;
    }

    SctFreePool (TmpName);

    if (!Exist) {
      break;
    }
  }

  //
  // Check the latest backup number
  //
  if (Index == INSTALL_SCT_MAX_BACKUP) {
    SctFreePool (PathName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create command line to backup it
  //
  CmdLine = SctPoolPrint (
              L"MV \"%s\" \"%s\\%s.bak%d\"",
              Name,
              PathName,
              Index,
              FileName
              );
  if (CmdLine == NULL) {
    SctFreePool (PathName);
    return EFI_OUT_OF_RESOURCES;
  }

  SctFreePool (PathName);

  //
  // Execute shell command
  //
  Status = SctShellExecute (
             &gImageHandle,
             CmdLine,
             FALSE,
             NULL,
             &CmdStatus
             );
  if (EFI_ERROR (Status) || EFI_ERROR (CmdStatus)) {
    SctPrint (L"Error: Could not execute \"%s\"\n", CmdLine);
    SctFreePool (CmdLine);
    return Status;
  }

  SctFreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}

// TODO share this code
STATIC
BOOLEAN
IsDirectory (
  EFI_FILE_PROTOCOL *File
  )
{
  BOOLEAN        Return;
  EFI_FILE_INFO *FileInfo;
  EFI_STATUS     Status;

  Status = SctGetFileInfo ((EFI_FILE_HANDLE) File, &FileInfo);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "IsDirectory(): %r\n", Status));
    return FALSE;
  }

  if ((FileInfo->Attribute & EFI_FILE_DIRECTORY) != 0) {
    Return = TRUE;
  } else {
    Return = FALSE;
  }

  SctFreePool (FileInfo);

  return Return;
}

STATIC
EFI_STATUS
CopyFileWorker (
  IN EFI_FILE_PROTOCOL *Src,
  IN EFI_FILE_PROTOCOL *Dst
  )
{
  EFI_STATUS Status;
  VOID      *Buffer;
  UINTN      BufferSize;

  // TODO WAT
  #define BUFFER_SIZE 0x10000

  if (IsDirectory (Src) || IsDirectory (Dst)) {
    return EFI_INVALID_PARAMETER;
  }

  Buffer = SctAllocatePool (BUFFER_SIZE);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  while (TRUE) {
    BufferSize = BUFFER_SIZE;

    Status = Src->Read (Src, &BufferSize, Buffer);
    if (EFI_ERROR (Status)) {
      break;
    }

    if (BufferSize == 0) {
      break;
    }

    Status = Dst->Write (Dst, &BufferSize, Buffer);
    if (EFI_ERROR (Status)) {
      break;
    }
  }

  Status = Dst->Flush (Dst);

  SctFreePool (Buffer);
  return Status;
}

EFI_STATUS
CopyFile (
  IN CHAR16             *SrcFullPath,
  IN CHAR16             *DstFullPath
  )
{
  EFI_STATUS                       Status;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  CHAR16                          *DstName;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume;
  EFI_FILE_PROTOCOL               *DstRoot;
  EFI_FILE_PROTOCOL               *DstFile;
  EFI_FILE_PROTOCOL               *SrcFile;

  //
  // Open the root directory of the destination filesystem
  //
  Status = SctGetFilesystemDevicePath (DstFullPath, &DevicePath, &DstName);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = SctDevicePathToInterface (
             &gEfiSimpleFileSystemProtocolGuid,
             DevicePath,
             (VOID **) &Volume
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Volume->OpenVolume (Volume, &DstRoot);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Open/Create the destination file
  Status = SctCreateFile (DstRoot, DstName, &DstFile);

  //
  // Open the source file
  //
  Status = SctOpenFileByName (SrcFullPath, &SrcFile, EFI_FILE_MODE_READ, 0);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return CopyFileWorker (SrcFile, DstFile);
}

/*
  Helper function to allocate and read an EFI_FILE_INFO out of a directory
*/
STATIC
EFI_STATUS
ReadDirectoryEntry (
  IN      EFI_FILE_PROTOCOL *Directory,
  IN  OUT UINTN             *BufferSize,
  IN  OUT EFI_FILE_INFO    **FileInfo     OPTIONAL
  )
{
  EFI_STATUS  Status;

  Status = Directory->Read (Directory, BufferSize, *FileInfo);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return Status;
  }

  //
  // Allocate a new buffer of suitable size
  //

  // Free the old buffer if required
  if (*FileInfo != NULL) {
    SctFreePool (*FileInfo);
  }

  *FileInfo = SctAllocatePool (*BufferSize);
  if (*FileInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  return Directory->Read (Directory, BufferSize, *FileInfo);
}

/*
  Worker function for CopyDir
*/
STATIC
EFI_STATUS
InternalRecursiveCopy (
  IN EFI_FILE_PROTOCOL *SrcDir,
  IN EFI_FILE_PROTOCOL *DstDir
  )
{
  EFI_STATUS         Status;
  EFI_FILE_PROTOCOL *SubCopyDst;
  EFI_FILE_PROTOCOL *SubCopySrc;
  UINTN              BufferSize;
  EFI_FILE_INFO     *FileInfo;

  BufferSize = 0;
  FileInfo = NULL;

  // Loop through each file in the subdirectory
  while (TRUE) {
    Status = ReadDirectoryEntry (SrcDir, &BufferSize, &FileInfo);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    if (BufferSize == 0) {
      break;
    }

    // Skip "." and ".."
    if (SctStrCmp (FileInfo->FileName, L".") == 0 ||
        SctStrCmp (FileInfo->FileName, L"..") == 0) {
      continue;
    }

    // Open source file
    Status = SrcDir->Open (
                       SrcDir,
                       &SubCopySrc,
                       FileInfo->FileName,
                       EFI_FILE_MODE_READ,
                       0
              );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      break;
    }

    // Open/Create destination file
    Status = DstDir->Open (
                        DstDir,
                        &SubCopyDst,
                        FileInfo->FileName,
                        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
                        FileInfo->Attribute
                        );
    if (EFI_ERROR (Status)) {
      break;
    }

    if (FileInfo->Attribute & EFI_FILE_DIRECTORY) {
      //
      // Recursively copy subdirectory
      //

      // The destination file may already have existed. Check it is a directory.
      if (!IsDirectory (SubCopyDst)) {
        // File previously existed and wasn't a directory
        // TODO Handle this
        DEBUG ((EFI_D_ERROR, "NOPE\n"));
        Status = EFI_ABORTED;
        break;
      }

        DEBUG ((EFI_D_ERROR, "Descending into %s...\n", FileInfo->FileName));
        InternalRecursiveCopy (SubCopySrc, SubCopyDst);
        DEBUG ((EFI_D_ERROR, "...Returning from %s\n", FileInfo->FileName));
      } else {
        DEBUG ((EFI_D_ERROR, "Copying %s...\n", FileInfo->FileName));
        CopyFileWorker (SubCopySrc, SubCopyDst);
      }

      SubCopySrc->Close (SubCopySrc);
      SubCopyDst->Close (SubCopyDst);
    }

    SctFreePool (FileInfo);
    return Status;
  }

/*
  Recursively copy the contents of the source directory to the destination
  directory. Equivalent to "cp -r SrcName\* DstName" in the UEFI Shell.
*/
EFI_STATUS
CopyDir (
  IN CHAR16             *SrcName,
  IN CHAR16             *DstName
  )
{
  EFI_STATUS                       Status;
  EFI_FILE_PROTOCOL               *SrcFile;
  EFI_FILE_PROTOCOL               *DstFile;

  //
  // Open the source and destination files
  //

  Status = SctOpenFileByName (
                  DstName,
                  &DstFile,
                  EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
                  EFI_FILE_DIRECTORY
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = SctOpenFileByName (SrcName, &SrcFile, EFI_FILE_MODE_READ, 0);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Check both files are directories
  if (!IsDirectory (SrcFile) || !IsDirectory (DstFile)) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((EFI_D_ERROR, "Copying %s to %s\n", SrcName, DstName));

  // Do the recursive copy
  return InternalRecursiveCopy (SrcFile, DstFile);
}

EFI_STATUS
ProcessExistingSctFile (
  IN  CHAR16*         Name,
  IN  CHAR16*         FileName
  )
{
  EFI_STATUS  Status;
  CHAR16      *Prompt;
  CHAR16      InputBuffer[2];

  // If it is not a 'ALL' policy then we need to get the user input
  if ((mBackupPolicy != BACKUP_POLICY_BACKUP_ALL) &&
      (mBackupPolicy != BACKUP_POLICY_REMOVE_ALL) &&
      (mBackupPolicy != BACKUP_POLICY_NONE)) {
    //
    // Initialize the input buffer
    //
    InputBuffer[0] = L'\0';

    //
    // User input his selection
    //
    Prompt = SctPoolPrint (
               L"Found the existing %s '%s'.\n"
               L"Select (B)ackup, Backup (A)ll, (R)emove, Remove A(l)l. 'q' to exit:",
               Name, FileName
               );
    if (Prompt == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // User must input a selection
    //
    while (TRUE) {
      SctInput (
        Prompt,
        InputBuffer,
        2
        );
      SctPrint (L"\n");

      //
      // Deal with the user input
      //
      if (SctStriCmp (InputBuffer, L"q") == 0) {
        mBackupPolicy = BACKUP_POLICY_UNDEFINED;
        break;
      } else if (SctStriCmp (InputBuffer, L"b") == 0) {
        mBackupPolicy = BACKUP_POLICY_BACKUP;
        break;
      } else if (SctStriCmp (InputBuffer, L"a") == 0) {
        mBackupPolicy = BACKUP_POLICY_BACKUP_ALL;
        break;
      } else if (SctStriCmp (InputBuffer, L"r") == 0) {
        mBackupPolicy = BACKUP_POLICY_REMOVE;
        break;
      } else if (SctStriCmp (InputBuffer, L"l") == 0) {
        mBackupPolicy = BACKUP_POLICY_REMOVE_ALL;
        break;
      }
    }

    SctFreePool (Prompt);
  }

  switch (mBackupPolicy) {
  case BACKUP_POLICY_BACKUP:
  case BACKUP_POLICY_BACKUP_ALL:
    Status = BackupDirFile (FileName);
    break;

  case BACKUP_POLICY_REMOVE:
  case BACKUP_POLICY_REMOVE_ALL:
    Status = RemoveDirFile (FileName);
    break;

  case BACKUP_POLICY_NONE:
    SctPrint (L"Error: An instance of SCT (%s) has been found. "
           L"Please remove or backup it before to install a new one.\n",
           FileName);

  default:
    Status = EFI_ABORTED;
  }

  return Status;
}

EFI_STATUS
CheckForInstalledSct (
  IN OUT SCT_FILE_VOLUME *FileVolume
  )
{
  EFI_STATUS  Status;
  CHAR16      *TmpName;
  BOOLEAN     Exist;

  FileVolume->IsSctPresent = 0;

  //
  // Check for 'SCT' folder
  //
  TmpName = SctPoolPrint (L"%s:\\SCT", FileVolume->Name);
  if (TmpName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  // Exist or not?
  Status = DirFileExist (TmpName, &Exist);
  if (EFI_ERROR (Status)) {
    SctFreePool (TmpName);
    return Status;
  }

  if (Exist) {
    FileVolume->IsSctPresent |= SCT_FOLDER;
  }
  SctFreePool (TmpName);

  //
  // Check for SCT startup script
  //
  TmpName = SctPoolPrint (L"%s:\\startup.nsh", FileVolume->Name);
  if (TmpName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  // Exist or not?
  Status = DirFileExist (TmpName, &Exist);
  if (EFI_ERROR (Status)) {
    SctFreePool (TmpName);
    return Status;
  }

  if (Exist) {
    FileVolume->IsSctPresent |= SCT_STARTUP;
  }
  SctFreePool (TmpName);

  return EFI_SUCCESS;
}
