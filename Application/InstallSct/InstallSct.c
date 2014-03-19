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
// indicates whether SCT runs in NT32 emulater 
// 
static FileVolumeState  ExistFs[INSTALL_SCT_MAX_FILE_SYSTEM];
static UINT64           FreeSpaces[SCAN_SCT_MAX_FILE_SYSTEM][VOLUMETYPENUM];

//
// Internal function declarations
//

VOID
PrintUsage (
  VOID
  );

EFI_STATUS
GetDestination (
  OUT CHAR16            **DirName
  );

EFI_STATUS
BackupTests (
  IN CHAR16             *DirName
  );

EFI_STATUS
BackupStartups (
  IN CHAR16             *DirName
  );

EFI_STATUS
InstallTest (
  IN CHAR16             *DirName
  );

EFI_STATUS
InstallStartup (
  IN CHAR16             *DirName
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
  EFI_STATUS  Status;
  CHAR16      *DirName;

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

  Status = GetDestination (&DirName);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Remove or backup the existing tests
  //
  Print (L"\nBackup the existing tests ...\n");

  Status = BackupTests (DirName);
  if (EFI_ERROR (Status)) {
    FreePool (DirName);
    return Status;
  }

  //
  // Remove or backup the startup files
  //
  Status = BackupStartups (DirName);
  if (EFI_ERROR (Status)) {
    FreePool (DirName);
    return Status;
  }

  //
  // Install the EFI SCT Harness
  //
  Print (L"\nInstalling...\n");

  Status = InstallTest (DirName);
  if (EFI_ERROR (Status)) {
    FreePool (DirName);
    return Status;
  }

  //
  // Install the startup file
  //
  Status = InstallStartup (DirName);
  if (EFI_ERROR (Status)) {
    FreePool (DirName);
    return Status;
  }

  FreePool (DirName);

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
  OUT CHAR16            **DirName
  )
{

  EFI_STATUS      Status;
  UINTN           Index;
  CHAR16          *FsName;
  UINTN           MaxExistIndex;
  CHAR16          InputBuffer[4];

  MaxExistIndex = 0;
  
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
    
    FsName = PoolPrint (L"FS%x", Index);
   
    if (FsName == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Get free space
    //
    Status = GetFreeSpace (FsName, &FreeSpaces[Index][NONE_NT32]);
    if (EFI_ERROR (Status)) {
      FreePool (FsName);
      continue;
    }

    ExistFs[MaxExistIndex].FileVoluemIndex = Index;
    ExistFs[MaxExistIndex].VolType = NONE_NT32;
    MaxExistIndex ++;
    //
    // Print system information
    //
    Print (
      L"  %d: %s: (Free Space: %d MB)\n",
      MaxExistIndex,
      FsName,
      (UINTN) DivU64x32 (FreeSpaces[Index][NONE_NT32], INSTALL_SCT_1M, NULL)
      );

    FreePool (FsName);
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
    FsName = PoolPrint (L"fsnt%x", Index);
    
    if (FsName == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
  
    //
    // Get free space
    //
    Status = GetFreeSpace (FsName, &FreeSpaces[Index][NT32]);
    if (EFI_ERROR (Status)) {
      FreePool (FsName);
      continue;
    }
  
    ExistFs[MaxExistIndex].FileVoluemIndex = Index;
    ExistFs[MaxExistIndex].VolType = NT32;
    MaxExistIndex ++;
  
    //
    // Print system information
    //
    Print (
      L"  %d: %s: (Free Space: %d MB)\n",
      MaxExistIndex,
      FsName,
      (UINTN) DivU64x32 (FreeSpaces[Index][NT32], INSTALL_SCT_1M, NULL)
      );
  
    FreePool (FsName);
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
    if (Index >= MaxExistIndex) {
      Print (L"  Only 1 to %d is valid.\n", MaxExistIndex);
      continue;
    }

    //
    // Check the free space
    //
    if (FreeSpaces[ExistFs[Index].FileVoluemIndex][ExistFs[Index].VolType] < (UINT64) INSTALL_SCT_FREE_SPACE) {
      Print (L"  Free space is not enough.\n");
      continue;
    }

    break;
  }

  //
  // Create the destination directory
  //
  if (ExistFs[Index].VolType == NT32) {
    *DirName = PoolPrint (L"fsnt%x:\\SCT", ExistFs[Index].FileVoluemIndex);
  }
  else {
    *DirName = PoolPrint (L"FS%x:\\SCT", ExistFs[Index].FileVoluemIndex);
  }
  
  if (*DirName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  
  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BackupTests (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  CHAR16      *TmpName;
  BOOLEAN     Exist;

  for (Index = 0; Index < INSTALL_SCT_MAX_FILE_SYSTEM; Index ++) {
    //
    // Create the potential existing directory name
    //
    if (Index < SCAN_SCT_MAX_FILE_SYSTEM) {
      TmpName = PoolPrint (L"FS%x:\\SCT", Index);
    }
    else {
      TmpName = PoolPrint (L"fsnt%x:\\SCT", Index - SCAN_SCT_MAX_FILE_SYSTEM);
    }
   
    if (TmpName == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Exist or not?
    //
    Status = DirFileExist (TmpName, &Exist);
    if (EFI_ERROR (Status)) {
      FreePool (TmpName);
      continue;
    }

    if (!Exist) {
      FreePool (TmpName);
      continue;
    }

    Status = ProcessExistingSctFile ("test", TmpName);
    if (EFI_ERROR (Status)) {
      FreePool (TmpName);
      return Status;
    }

    FreePool (TmpName);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
BackupStartups (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  CHAR16      *TmpName;
  BOOLEAN     Exist;

  for (Index = 0; Index < INSTALL_SCT_MAX_FILE_SYSTEM; Index ++) {
    //
    // Create the existing startup script
    //
    if (Index < SCAN_SCT_MAX_FILE_SYSTEM) {
      TmpName = PoolPrint (L"FS%x:\\startup.nsh", Index);
    }
    else {
      TmpName = PoolPrint (L"fsnt%x:\\startup.nsh", Index - SCAN_SCT_MAX_FILE_SYSTEM);
    }
    

    if (TmpName == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Exist or not?
    //
    Status = DirFileExist (TmpName, &Exist);
    if (EFI_ERROR (Status)) {
      FreePool (TmpName);
      continue;
    }

    if (!Exist) {
      FreePool (TmpName);
      continue;
    }

    Status = ProcessExistingSctFile ("startup script", TmpName);
    if (EFI_ERROR (Status)) {
      FreePool (TmpName);
      return Status;
    }

    FreePool (TmpName);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
InstallTest (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;

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

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
InstallStartup (
  IN CHAR16             *DirName
  )
{
  EFI_STATUS  Status;
  CHAR16      *FsName;
  CHAR16      *FileName;
  UINTN       Index;
  UINTN       Length;

  //
  // Split to the file system name
  //
  FsName = StrDuplicate (DirName);
  if (FsName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Length   = StrLen (DirName);

  for (Index = 0; Index < Length; Index ++) {
    if (FsName[Index] == L':') {
      FsName[Index] = L'\0';
      break;
    }
  }

  //
  // Create the startup file name
  //
  FileName = PoolPrint (L"%s:\\Startup.nsh", FsName);
  if (FileName == NULL) {
    FreePool (FsName);
    return EFI_OUT_OF_RESOURCES;
  }

  FreePool (FsName);

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

