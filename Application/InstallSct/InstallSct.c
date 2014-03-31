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

EFI_HANDLE    gImageHandle  = NULL_HANDLE;
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
EFI_DRIVER_ENTRY_POINT(InstallSct)

EFI_STATUS
InstallSct (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS       Status;
  SCT_FILE_VOLUME *SctFileVolume;

  //
  // Initialize library
  //
  EFI_SHELL_APP_INIT (ImageHandle, SystemTable);

  //
  // Check parameters
  //
  if (SI->Argc != 1) {
    PrintUsage ();
    return EFI_SUCCESS;
  }

  gImageHandle = ImageHandle;

  //
  // Get the destination directory
  //
  Print (L"\nGather system information ...\n");

  Status = GetDestination (&SctFileVolume);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Remove or backup the existing tests
  //
  Print (L"\nBackup the existing tests ...\n");

  Status = BackupSct ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Install the EFI SCT Harness
  //
  Print (L"\nInstalling...\n");

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

  //
  // Done
  //
  Print (L"\nDONE!\n");
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
  Print (
    L"Install EFI SCT Harness, Version 0.9\n"
    L"\n"
    L"Notes: Make sure the shell commands CP, DEL, MKDIR, MV, and LS are enabled.\n"
    L"       They are used in this installation.\n"
    L"\n"
    L"Usage: Install%s\n"
    L"\n",
    INSTALL_SCT_PLATFORM_SHORT_NAME
    );
}


EFI_STATUS
GetDestination (
  OUT SCT_FILE_VOLUME **SctFileVolume
  )
{

  EFI_STATUS      Status;
  UINTN           Index;
  CHAR16          InputBuffer[4];

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
    SPrint (mFs[mFsCount].Name, 0, L"FS%x", Index);

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
    SPrint (mFs[mFsCount].Name, 0, L"fsnt%x", Index);
  
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
  // Print system information
  //
  for (Index = 0; Index < mFsCount; Index ++) {
    Print (
      L"  %d: %s: (Free Space: %d MB)\n",
      Index + 1,
      mFs[Index].Name,
      (UINTN) DivU64x32 (mFs[Index].FreeSpace, INSTALL_SCT_1M, NULL)
      );
  }

  Print (
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
    Input (
      L"Input index of destination FS. 'q' to exit:",
      InputBuffer,
      4
      );

    Print (L"\n");

    //
    // Deal with the user input
    //
    if (StriCmp (InputBuffer, L"q") == 0) {
      return EFI_ABORTED;
    }

    //
    // Convert the input to an index
    //
    Index = Atoi(InputBuffer) - 1;
    if (Index >= mFsCount) {
      Print (L"  Only 1 to %d is valid.\n", mFsCount);
      continue;
    }

    //
    // Check the free space
    //
    if (mFs[Index].FreeSpace < (UINT64) INSTALL_SCT_FREE_SPACE) {
      Print (L"  Free space is not enough.\n");
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
  BOOLEAN     Exist;
  UINTN       Index;

  // Go through the list of the File System and backup/remove existing SCT
  for (Index = 0; Index < mFsCount; Index++) {
    //
    // Check for 'SCT' folder
    //
    if (mFs[Index].IsSctPresent & SCT_FOLDER) {
      // Generate the filename
      TmpName = PoolPrint (L"%s:\\SCT", mFs[Index].Name);
      if (TmpName == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }

      // Decide whether the file needs to be removed/backup
      Status = ProcessExistingSctFile (L"test", TmpName);
      if (EFI_ERROR (Status)) {
        FreePool (TmpName);
        return Status;
      }

      FreePool (TmpName);
    }

    //
    // Check for 'SCT' folder
    //
    if (mFs[Index].IsSctPresent & SCT_STARTUP) {
      // Generate the filename
      TmpName = PoolPrint (L"%s:\\startup.nsh", mFs[Index].Name);
      if (TmpName == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }

      // Decide whether the file needs to be removed/backup
      Status = ProcessExistingSctFile (L"startup script", TmpName);
      if (EFI_ERROR (Status)) {
        FreePool (TmpName);
        return Status;
      }

      FreePool (TmpName);
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
  CHAR16*     DirName;

  DirName = PoolPrint (L"%s:\\SCT", SctFileVolume->Name);
  if (DirName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Copy the EFI SCT Harness
  //
  Status = CopyDirFile (
             INSTALL_SCT_PLATFORM_NAME,
             DirName,
             TRUE                           // Recursive
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  FreePool (DirName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
InstallStartup (
  IN OUT SCT_FILE_VOLUME *SctFileVolume
  )
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Create the startup file name
  //
  FileName = PoolPrint (L"%s:\\Startup.nsh", SctFileVolume->Name);
  if (FileName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Copy the startup script file
  //
  Status = CopyDirFile (
             INSTALL_SCT_STARTUP_FILE,
             FileName,
             FALSE                          // Not recursive
             );
  if (EFI_ERROR (Status)) {
    FreePool (FileName);
    return Status;
  }

  FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}

