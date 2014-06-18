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

  Reset.c

Abstract:

  This file provides the services to deal with the system reset, the test
  execution reset, and so on.

--*/

#include "Sct.h"

//
// Internal functions declaration
//

EFI_STATUS
RemoveMetaFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN CHAR16                       *MetaName
  );

EFI_STATUS
RemoveFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName
  );


//
// External functions implementation
//

EFI_STATUS
RemoveRecoveryFile (
  VOID
  )
/*++

Routine Description:

  Remove the recovery file.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Create the name of recovery file
  //
  FileName = SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_RECOVERY);
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Remove it
  //
  Status = RemoveFile (gFT->DevicePath, FileName);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove file - %r", Status));
    tBS->FreePool (FileName);
    return Status;
  }

  tBS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ResetAllTestResults (
  VOID
  )
/*++

Routine Description:

  Reset all test results, including the recovery file, the test results of
  test cases, and the test log files.

  It is used to clean up all test information.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;
  CHAR16      *FilePath;

  //
  // Reset the order and test results of all test case
  //
  Status = ResetTestCaseOrderAndResults ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Reset test case order and results - %r", Status));
    return Status;
  }

  Status = SaveTestCases ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Save test cases - %r", Status));
    return Status;
  }
  
  Status = RemoveFile (
             gFT->DevicePath,
             gFT->TestCaseFileName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove TestCase.ini - %r", Status));
    return Status;
  }

  //
  // Remove the skipped case
  //
  FileName = SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_SKIPPED_CASE);
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }
  
  Status = RemoveFile (
             gFT->DevicePath,
             FileName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove SkippedCase.ini - %r", Status));
    tBS->FreePool (FileName);
    return Status;
  }
  

  tBS->FreePool (FileName);  

  //
  // Remove the recovery file
  //
  Status = RemoveRecoveryFile ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove recovery file - %r", Status));
    return Status;
  }

  //
  // Remove Overall
  //
  FilePath = SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_PATH_OVERALL);
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }
  
  Status = RemoveMetaFiles (
             gFT->DevicePath,
             FilePath,
             L"*"
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove mata files - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  Status = RemoveFile (
             gFT->DevicePath,
             FilePath
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove Overall Directory - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);
  
  //
  // Remove the Sct.log and Sct.cfg
  //
  FilePath = SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_LOG);
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }
  
  Status = RemoveFile (
             gFT->DevicePath,
             FilePath
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove Sct.log - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);

  FilePath = SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_CFG);
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }
  
  Status = RemoveFile (
             gFT->DevicePath,
             FilePath
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove Sct.cfg - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);  

  //
  // Remove the log files
  //
  FilePath = SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_PATH_LOG);
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RemoveMetaFiles (
             gFT->DevicePath,
             FilePath,
             L"*"                     // All files
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove meta files - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  //
  // Remove the Log Directory
  //
  Status = RemoveFile (
             gFT->DevicePath,
             FilePath
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove Log Directory - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }  

  tBS->FreePool (FilePath);

  //
  // Remove the .verbose.mode File
  //
  FilePath = SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_PATH_VERBOSE);
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }
  Status = RemoveFile (
             gFT->DevicePath, 
             FilePath);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Remove .verbose.mode files - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
ResetExecuteTestResults (
  IN EFI_SCT_EXECUTE_INFO         *ExecuteInfo
  )
/*++

Routine Description:

  Reset the test results of test cases to be executed.

  It is used to prepare the test environment for the next execution.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS            Status;
  CHAR16                *FilePath;
  CHAR16                *MetaName;
  CHAR16                *TempName;

  //
  // Set the running state
  //
  ExecuteInfo->TestCase->Passes   = EFI_SCT_TEST_CASE_RUNNING;
  ExecuteInfo->TestCase->Failures = EFI_SCT_TEST_CASE_RUNNING;

  Status = SaveTestCases ();
  if (EFI_ERROR(Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Save test cases - %r", Status));
    return Status;
  }

  //
  // Remove the recovery file
  //
  Status = RemoveRecoveryFile ();
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove recovery file - %r", Status));
    return Status;
  }

  //
  // Remove the log files
  //
  Status = GetFileMetaName (
             ExecuteInfo,
             &FilePath,
             &MetaName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Get test meta name - %r", Status));
    return Status;
  }

  //
  // Convert the meta name with wildcard character '*'
  //
  TempName = SctPoolPrint (MetaName, L"*", L"*", L"*");
  if (TempName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"SctPoolPrint: Out of resource"));
    tBS->FreePool (FilePath);
    tBS->FreePool (MetaName);
    return EFI_OUT_OF_RESOURCES;
  }

  tBS->FreePool (MetaName);

  //
  // Remove the log and key files
  //
  Status = RemoveMetaFiles (
             gFT->DevicePath,
             FilePath,
             TempName
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Remove meta files - %r", Status));
    tBS->FreePool (FilePath);
    tBS->FreePool (TempName);
    return Status;
  }

  tBS->FreePool (FilePath);
  tBS->FreePool (TempName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Internal functions implementation
//

EFI_STATUS
RemoveMetaFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN CHAR16                       *MetaName
  )
/*++

Routine Description:

  Remove meta files (with wildcard characters in file name).

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   Handle;
  EFI_FILE_HANDLE                   ChildHandle;
  UINTN                             FileInfoSize;
  EFI_FILE_INFO                     *FileInfo;
  CHAR16                            *SubDir;
  EFI_DEVICE_PATH_PROTOCOL          *RemainderDevicePath;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FilePath == NULL) || (MetaName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Locate the device handle from the device path
  //
  RemainderDevicePath = DevicePath;

  Status = tBS->LocateDevicePath (
                 &gEfiSimpleFileSystemProtocolGuid,
                 &RemainderDevicePath,
                 &DeviceHandle
                 );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Locate system volume from the device handle
  //
  Status = tBS->HandleProtocol (
                 DeviceHandle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 (VOID **)&Vol
                 );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Open the root directory
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Open the file
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FilePath,
                      EFI_FILE_MODE_READ,
                      EFI_FILE_DIRECTORY
                      );
  if (EFI_ERROR(Status)) {
    //
    // Not found, misson complete!
    //
    RootDir->Close (RootDir);
    return EFI_SUCCESS;
  }

  RootDir->Close (RootDir);

  //
  // Allocate memory for the entries in the directory
  //
  FileInfoSize = sizeof(EFI_FILE_INFO) + 1024;

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 FileInfoSize,
                 (VOID **)&FileInfo
                 );
  if (EFI_ERROR(Status)) {
    Handle->Close (Handle);
    return Status;
  }

  //
  // Walk through each file in the directory
  //
  while (TRUE) {
    //
    // Read a file entry
    //
    FileInfoSize = sizeof(EFI_FILE_INFO) + 1024;

    Status = Handle->Read (
                       Handle,
                       &FileInfoSize,
                       FileInfo
                       );
    if (EFI_ERROR(Status) || (FileInfoSize == 0)) {
      break;
    }

    //
    // Skip the '.' and '..'
    //
    if ((SctStrCmp (FileInfo->FileName, L".")  == 0) ||
        (SctStrCmp (FileInfo->FileName, L"..") == 0)) {
      continue;
    }

    if ((FileInfo->Attribute & EFI_FILE_DIRECTORY) != 0) {
      //
      // It is a directory
      //
      SubDir = SctPoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);

      Status = RemoveMetaFiles (
                 DevicePath,
                 SubDir,
                 MetaName
                 );
      if (EFI_ERROR(Status)) {
        tBS->FreePool (SubDir);
        continue;
      }

      tBS->FreePool (SubDir);
    }

    //
    // Remove the file or the directory
    //
    if (SctMetaiMatch (FileInfo->FileName, MetaName)) {
      Status = Handle->Open (
                         Handle,
                         &ChildHandle,
                         FileInfo->FileName,
                         EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                         0
                         );
      if (EFI_ERROR(Status)) {
        continue;
      }

      Status = ChildHandle->Delete (ChildHandle);
      if (Status != EFI_SUCCESS) {
        //
        // NOTE: A warning status will be returned from Delete()
        //
        continue;
      }
    }
  }

  //
  // Free resources
  //
  tBS->FreePool (FileInfo);
  Handle->Close (Handle);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
RemoveFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName
  )
/*++

Routine Description:

  Remove a file.

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   Handle;
  EFI_DEVICE_PATH_PROTOCOL          *RemainderDevicePath;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // locate the device handle from the device path
  //
  RemainderDevicePath = DevicePath;

  Status = tBS->LocateDevicePath (
                 &gEfiSimpleFileSystemProtocolGuid,
                 &RemainderDevicePath,
                 &DeviceHandle
                 );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Locate system volume from the device handle
  //
  Status = tBS->HandleProtocol (
                 DeviceHandle,
                 &gEfiSimpleFileSystemProtocolGuid,
                 (VOID **)&Vol
                 );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Open the root directory
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Open the file
  //
  Status = RootDir->Open (
                      RootDir,
                      &Handle,
                      FileName,
                      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                      0
                      );
  if (Status == EFI_NOT_FOUND) {
    //
    // Not found, misson complete!
    //
    RootDir->Close (RootDir);
    return EFI_SUCCESS;
  }

  //
  // Delete the file
  //
  Status = Handle->Delete (Handle);
  if (Status != EFI_SUCCESS) {
    //
    // NOTE: A warning status will be returned from Delete()
    //
    RootDir->Close (RootDir);
    return EFI_UNSUPPORTED;
  }

  //
  // Close the root directory
  //
  RootDir->Close (RootDir);

  //
  // Done
  //
  return EFI_SUCCESS;
}
