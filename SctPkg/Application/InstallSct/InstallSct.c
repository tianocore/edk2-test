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
  Portions copyright (c) 2014, ARM Ltd. All rights reserved.

--*/
/*++

Module Name:

  InstallSct.c

Abstract:

  The EFI SCT installation.

--*/
#include "InstallSct.h"

//
// Global variables
//

BACKUP_POLICY mBackupPolicy = BACKUP_POLICY_UNDEFINED;

//
// Supported Filesystems on the platform
// 
STATIC SCT_FILE_VOLUME mFs[INSTALL_SCT_MAX_FILE_SYSTEM];
STATIC UINTN           mFsCount = 0;

//
// Internal function declarations
//

VOID
PrintUsage (
  VOID
  );

EFI_STATUS
GetSystemInformation (
  VOID
  );

EFI_STATUS
GetDestination (
  OUT SCT_FILE_VOLUME **SctFileVolume
  );

EFI_STATUS
BackupSct (
  VOID
  );

EFI_STATUS
InstallTest (
  IN OUT SCT_FILE_VOLUME *SctFileVolume
  );

EFI_STATUS
InstallStartup (
  IN OUT SCT_FILE_VOLUME *SctFileVolume
  );

//
// Entry point
//
EFI_STATUS
InstallSct (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS       Status;
  SCT_FILE_VOLUME *SctFileVolume;
  UINTN            Index;
  CHAR16          *FsName;
  UINTN	           Argc;
  CHAR16         **Argv;

  //
  // Initialize library
  //
  SctShellApplicationInit (ImageHandle, SystemTable);

  //
  // Check parameters
  //
  SctShellGetArguments (&Argc, &Argv);
  if (Argc > 3) {
    PrintUsage ();
    return EFI_SUCCESS;
  }

  gImageHandle = ImageHandle;

  //
  // Get the destination directory
  //
  SctPrint (L"\nGather system information ...\n");
  Status = GetSystemInformation ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // If the file system has not been given in the command line then request it
  //
  if (Argc == 1) {
    Status = GetDestination (&SctFileVolume);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else {
    // The file system must be the last argument
    FsName = Argv[Argc - 1];

    // Allocate new SctFileVolume
    SctFileVolume = SctAllocatePool (sizeof (SCT_FILE_VOLUME));

    // Save the filename
    SctCopyMem (SctFileVolume->Name, FsName, SctStrSize (FsName));

    // Ensure it is valid file system and it has enough free space
    Status = GetFreeSpace (SctFileVolume);
    if (Status == EFI_NOT_FOUND) {
      SctPrint (L"'%s' is not a valid file system.\n", FsName);
      PrintUsage ();
      SctFreePool (SctFileVolume);
      return Status;
    } else if (EFI_ERROR (Status)) {
      SctPrint (L"Fail to get free space from file system '%s'.\n", FsName);
      SctFreePool (SctFileVolume);
      return Status;
    } else if (SctFileVolume->FreeSpace < INSTALL_SCT_FREE_SPACE) {
      SctFreePool (SctFileVolume);
      SctPrint (L"The given file system '%s' is not big enough to install SCT (require %d MB).\n",
          FsName, INSTALL_SCT_FREE_SPACE_MB);
      return EFI_VOLUME_FULL;
    }

    //
    // Check the policy on existing SCT
    //

    // If not defined then SCT should not have been installed
    mBackupPolicy = BACKUP_POLICY_NONE;

    for (Index = 1; Index < Argc - 1; Index++) {
      if (SctStrCmp (Argv[Index], L"-b") == 0) {
        mBackupPolicy = BACKUP_POLICY_BACKUP_ALL;
      } else if (SctStrCmp (Argv[Index], L"-r") == 0) {
        mBackupPolicy = BACKUP_POLICY_REMOVE_ALL;
      } else {
        SctPrint (L"'%s' is not a valid option.\n", Argv[Index]);
        PrintUsage ();
        return Status;
      }
    }
  }

  //
  // Remove or backup the existing tests
  //
  SctPrint (L"\nCheck if SCT already installed ...\n");

  Status = BackupSct ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Install the EFI SCT Harness
  //
  SctPrint (L"\nInstalling...\n");

  Status = InstallTest (SctFileVolume);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Install the startup file
  //
  Status = InstallStartup (SctFileVolume);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (Argc > 3) {
    SctFreePool (SctFileVolume);
  }

  //
  // Done
  //
  SctPrint (L"\nDONE!\n");
  return EFI_SUCCESS;
}


//
// Internal function implementations
//

VOID
PrintUsage (
  VOID
  )
{
  SctPrint (
    L"Install EFI SCT Harness, Version 0.9\n"
    L"\n"
    L"Notes: Make sure the shell commands CP, DEL, MKDIR, MV, and LS are enabled.\n"
    L"       They are used in this installation.\n"
    L"\n"
    L"Usage: Install%s [[options] file_system]\n"
    L"  options:\n"
    L"    -b: automatically backup all the existing SCT on any file system.\n"
    L"    -r: automatically delete all the existing SCT on any file system.\n"
    L"    if none of these options are given InstallSct would return an error\n"
    L"    if it has already been installed.\n"
    L"  file_system: name of the filesystem where to install SCT (optional)\n"
    L"\n",
    INSTALL_SCT_PLATFORM_SHORT_NAME
    );
}

EFI_STATUS
GetSystemInformation (
  VOID
  )
{
  EFI_STATUS      Status;
  UINTN           Index;

  //
  // 1. Search each FS% file system
  //
  for (Index = 0; Index < SCAN_SCT_MAX_FILE_SYSTEM; Index ++) {
    //
    // NOTE: Here the file system name is hard coded. I don't know how to find
    // all file system names via a shell service.
    //

    //
    // Create FS% name of file system
    //
    SctSPrint (mFs[mFsCount].Name, 0, L"FS%x", Index);

    //
    // Get free space
    //
    Status = GetFreeSpace (&mFs[mFsCount]);
    if (EFI_ERROR (Status)) {
      continue;
    }

    // The file system exists, we check if SCT has already been installed
    CheckForInstalledSct (&mFs[mFsCount]);

    mFsCount++;
  }

  //
  // 2. Search each fsnt% file system
  //
  for (Index = 0; Index < SCAN_SCT_MAX_FILE_SYSTEM; Index ++) {
    //
    // NOTE: Here the file system name is hard coded. I don't know how to find
    // all file system names via a shell service.
    //
  
    //
    // Create fsnt% name of file system
    //
    SctSPrint (mFs[mFsCount].Name, 0, L"fsnt%x", Index);
  
    //
    // Get free space
    //
    Status = GetFreeSpace (&mFs[mFsCount]);
    if (EFI_ERROR (Status)) {
      continue;
    }

    // The file system exists, we check if SCT has already been installed
    CheckForInstalledSct (&mFs[mFsCount]);

    mFsCount++;
  }
  return EFI_SUCCESS;
}

EFI_STATUS
GetDestination (
  OUT SCT_FILE_VOLUME **SctFileVolume
  )
{
  UINTN           Index;
  CHAR16          InputBuffer[4];
  
  //
  // Print system information
  //
  for (Index = 0; Index < mFsCount; Index ++) {
    SctPrint (
      L"  %d: %s: (Free Space: %d MB)\n",
      Index + 1,
      mFs[Index].Name,
      (UINTN) SctDivU64x32 (mFs[Index].FreeSpace, INSTALL_SCT_1M, NULL)
      );
  }

  SctPrint (
    L"  Space Required: %d MB\n",
    INSTALL_SCT_FREE_SPACE / INSTALL_SCT_1M
    );

  //
  // User must choice a required file system
  //
  while (TRUE) {
    //
    // Input the index of destination file system
    //
    SctInput (
      L"Input index of destination FS. 'q' to exit:",
      InputBuffer,
      4
      );

    SctPrint (L"\n");

    //
    // Deal with the user input
    //
    if (SctStriCmp (InputBuffer, L"q") == 0) {
      return EFI_ABORTED;
    }

    //
    // Convert the input to an index
    //
    Index = SctAtoi (InputBuffer) - 1;
    if (Index >= mFsCount) {
      SctPrint (L"  Only 1 to %d is valid.\n", mFsCount);
      continue;
    }

    //
    // Check the free space
    //
    if (mFs[Index].FreeSpace < (UINT64) INSTALL_SCT_FREE_SPACE) {
      SctPrint (L"  Free space is not enough.\n");
      continue;
    } else {
      *SctFileVolume = &mFs[Index];
      break;
    }
  }
  
  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BackupSct (
  VOID
  )
{
  EFI_STATUS  Status;
  CHAR16      *TmpName;
  UINTN       Index;

  // Go through the list of the File System and backup/remove existing SCT
  for (Index = 0; Index < mFsCount; Index++) {
    //
    // Check for 'SCT' folder
    //
    if (mFs[Index].IsSctPresent & SCT_FOLDER) {
      // Generate the filename
      TmpName = SctPoolPrint (L"%s:\\SCT", mFs[Index].Name);
      if (TmpName == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }

      // Decide whether the file needs to be removed/backup
      Status = ProcessExistingSctFile (L"test", TmpName);
      if (EFI_ERROR (Status)) {
        SctFreePool (TmpName);
        return Status;
      }

      SctFreePool (TmpName);
    }

    //
    // Check for 'SCT' folder
    //
    if (mFs[Index].IsSctPresent & SCT_STARTUP) {
      // Generate the filename
      TmpName = SctPoolPrint (L"%s:\\startup.nsh", mFs[Index].Name);
      if (TmpName == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }

      // Decide whether the file needs to be removed/backup
      Status = ProcessExistingSctFile (L"startup script", TmpName);
      if (EFI_ERROR (Status)) {
        SctFreePool (TmpName);
        return Status;
      }

      SctFreePool (TmpName);
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
InstallTest (
  IN OUT SCT_FILE_VOLUME *SctFileVolume
  )
{
  EFI_STATUS  Status;
  CHAR16*     TargetDirName;
  CHAR16*     SourceDirName;

  TargetDirName = SctPoolPrint (L"%s:\\SCT", SctFileVolume->Name);
  if (TargetDirName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = SctExpandRelativePath (INSTALL_SCT_PLATFORM_NAME, &SourceDirName);
  if (EFI_ERROR (Status)) {
    SctFreePool (TargetDirName);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Copy the EFI SCT Harness
  //
  Status = CopyDir (SourceDirName, TargetDirName);

  SctFreePool (SourceDirName);
  SctFreePool (TargetDirName);
  return Status;
}


EFI_STATUS
InstallStartup (
  IN OUT SCT_FILE_VOLUME *SctFileVolume
  )
{
  EFI_STATUS  Status;
  CHAR16      *TargetFileName;
  CHAR16      *SourceFileName;

  //
  // Create the startup file name
  //
  TargetFileName = SctPoolPrint (L"%s:\\Startup.nsh", SctFileVolume->Name);
  if (TargetFileName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Copy the startup script file
  //
  Status = SctExpandRelativePath (INSTALL_SCT_STARTUP_FILE, &SourceFileName);
  if (EFI_ERROR (Status)) {
    SctFreePool (TargetFileName);
    return Status;
  }

  Status = CopyFile (SourceFileName, TargetFileName);
  if (EFI_ERROR (Status)) {
    SctFreePool (TargetFileName);
    return Status;
  }

  SctFreePool (TargetFileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}

