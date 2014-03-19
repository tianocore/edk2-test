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
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  InstallSctSupport.c

Abstract:

  This file provides the support services for the EFI SCT installation.

--*/

#include "InstallSct.h"

//
// External function implementation
//

EFI_STATUS
GetFreeSpace (
  IN CHAR16             *FsName,
  OUT UINT64            *FreeSpace
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
  DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) ShellGetMap (FsName);
  if (DevicePath == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Locate the file system protocol
  //
  Status = LibDevicePathToInterface (
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

  SystemInfo = (EFI_FILE_SYSTEM_INFO *) AllocatePool (SystemInfoSize);
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
    FreePool (SystemInfo);
    RootFs->Close (RootFs);
    return Status;
  }

  *FreeSpace = SystemInfo->FreeSpace;

  FreePool (SystemInfo);
  RootFs->Close (RootFs);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
DirFileExist (
  IN CHAR16             *Name,
  OUT BOOLEAN           *Exist
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;

  //
  // Create command line to list the directory or file
  //
  CmdLine = PoolPrint (
              L"LS \"%s\" > NUL",
              Name
              );
  if (CmdLine == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Execute shell command
  //
  Status = ShellExecute (
             gImageHandle,
             CmdLine,
             FALSE
             );

  if (Status == EFI_INVALID_PARAMETER) {
    Print (L"Error: Could not execute \"%s\"\n", CmdLine);
    FreePool (CmdLine);
    return Status;
  }

  //
  // Exist or not?
  //
  if (EFI_ERROR (Status)) {
    *Exist = FALSE;
  } else {
    *Exist = TRUE;
  }

  FreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CreateDir (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;
  CHAR16      *TmpName;
  UINTN       Index;
  BOOLEAN     Done;
  BOOLEAN     Exist;

  //
  // Create the temp name
  //
  TmpName = StrDuplicate (DirName);
  if (TmpName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create the directory one by one layer
  //
  Done = FALSE;

  for (Index = 0; !Done; Index ++) {
    if (TmpName[Index] == L'\0') {
      Done = TRUE;
    }

    if ((TmpName[Index] == L'\\') || (TmpName[Index] == L'\0')){
      TmpName[Index] = L'\0';

      //
      // Exist or not?
      //
      Status = DirFileExist (TmpName, &Exist);
      if (EFI_ERROR (Status)) {
        FreePool (TmpName);
        return Status;
      }

      if (Exist) {
        TmpName[Index] = L'\\';
        continue;
      }

      //
      // Create command line to create this directory
      //
      CmdLine = PoolPrint (
                  L"MKDIR \"%s\"",
                  TmpName
                  );
      if (CmdLine == NULL) {
        FreePool (TmpName);
        return EFI_OUT_OF_RESOURCES;
      }

      //
      // Execute shell command
      //
      Status = ShellExecute (
                 gImageHandle,
                 CmdLine,
                 FALSE
                 );
      if (EFI_ERROR (Status)) {
        Print (L"Error: Could not execute \"%s\"\n", CmdLine);
        FreePool (CmdLine);
        FreePool (TmpName);
        return Status;
      }

      FreePool (CmdLine);
      TmpName[Index] = L'\\';
    }
  }

  FreePool (TmpName);

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

  //
  // Create command line to delete this directory or file
  //
  CmdLine = PoolPrint (
              L"DEL -q \"%s\"",
              Name
              );
  if (CmdLine == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Execute this shell command
  //
  Status = ShellExecute (
             gImageHandle,
             CmdLine,
             FALSE
             );
  if (EFI_ERROR (Status)) {
    Print (L"Error: Could not execute \"%s\"\n", CmdLine);
    FreePool (CmdLine);
    return Status;
  }

  FreePool (CmdLine);

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
  PathName = StrDuplicate (Name);
  if (PathName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Length   = StrLen (PathName);
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
    TmpName = PoolPrint (
                L"\"%s\\bak%d.%s\"",
                PathName,
                Index,
                FileName
                );
    if (TmpName == NULL) {
      FreePool (PathName);
      return EFI_OUT_OF_RESOURCES;
    }

    Status = DirFileExist (TmpName, &Exist);
    if (EFI_ERROR (Status)) {
      FreePool (TmpName);
      FreePool (PathName);
      return Status;
    }

    FreePool (TmpName);

    if (!Exist) {
      break;
    }
  }

  //
  // Check the latest backup number
  //
  if (Index == INSTALL_SCT_MAX_BACKUP) {
    FreePool (PathName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Create command line to backup it
  //
  CmdLine = PoolPrint (
              L"MV \"%s\" \"%s\\bak%d.%s\"",
              Name,
              PathName,
              Index,
              FileName
              );
  if (CmdLine == NULL) {
    FreePool (PathName);
    return EFI_OUT_OF_RESOURCES;
  }

  FreePool (PathName);

  //
  // Execute shell command
  //
  Status = ShellExecute (
             gImageHandle,
             CmdLine,
             FALSE
             );
  if (EFI_ERROR (Status)) {
    Print (L"Error: Could not execute \"%s\"\n", CmdLine);
    FreePool (CmdLine);
    return Status;
  }

  FreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CopyDirFile (
  IN CHAR16             *SrcName,
  IN CHAR16             *DstName,
  IN BOOLEAN            Recursive
  )
{
  EFI_STATUS  Status;
  CHAR16      *CmdLine;
  CHAR16      *PathName;
  UINTN       Index;
  UINTN       Length;

  //
  // Split to the path name
  //
  PathName = StrDuplicate (DstName);
  if (PathName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Length   = StrLen (PathName);

  for (Index = 0; Index < Length; Index ++) {
    if (PathName[Length - Index - 1] == L'\\') {
      PathName[Length - Index - 1] = L'\0';
      break;
    }
  }

  //
  // Create the parent directory
  //
  Status = CreateDir (PathName);
  if (EFI_ERROR (Status)) {
    FreePool (PathName);
    return Status;
  }

  FreePool (PathName);

  //
  // Create command line to copy it
  //
  CmdLine = PoolPrint (
              L"CP %s -q \"%s\" \"%s\"",
              Recursive ? L"-r" : L"",
              SrcName,
              DstName
              );
  if (CmdLine == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Execute shell command
  //
  Status = ShellExecute (
             gImageHandle,
             CmdLine,
             FALSE
             );
  if (EFI_ERROR (Status)) {
    Print (L"Error: Could not execute \"%s\"\n", CmdLine);
    FreePool (CmdLine);
    return Status;
  }

  FreePool (CmdLine);

  //
  // Done
  //
  return EFI_SUCCESS;
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
      (mBackupPolicy != BACKUP_POLICY_REMOVE_ALL)) {
    //
    // Initialize the input buffer
    //
    InputBuffer[0] = L'\0';

    //
    // User input his selection
    //
    Prompt = PoolPrint (
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
      Input (
        Prompt,
        InputBuffer,
        2
        );
      Print (L"\n");

      //
      // Deal with the user input
      //
      if (StriCmp (InputBuffer, L"q") == 0) {
        mBackupPolicy = BACKUP_POLICY_UNDEFINED;
        break;
      } else if (StriCmp (InputBuffer, L"b") == 0) {
        mBackupPolicy = BACKUP_POLICY_BACKUP;
        break;
      } else if (StriCmp (InputBuffer, L"a") == 0) {
        mBackupPolicy = BACKUP_POLICY_BACKUP_ALL;
        break;
      } else if (StriCmp (InputBuffer, L"r") == 0) {
        mBackupPolicy = BACKUP_POLICY_REMOVE;
        break;
      } else if (StriCmp (InputBuffer, L"l") == 0) {
        mBackupPolicy = BACKUP_POLICY_REMOVE_ALL;
        break;
      }
    }

    FreePool (Prompt);
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

  default:
    Status = EFI_ABORTED;
  }

  return Status;
}
