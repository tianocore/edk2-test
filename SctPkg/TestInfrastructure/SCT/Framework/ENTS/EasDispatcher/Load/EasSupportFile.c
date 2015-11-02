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

  EasSupportFile.c

Abstract:

  Network test file services implementations.

--*/

#include "SctLib.h"
#include "Eas.h"
#include EFI_TEST_PROTOCOL_DEFINITION (EntsMonitorProtocol)

EFI_HANDLE  mEftpTargetHandle;

//
// Local functions declarations
//
EFI_STATUS
EntsLoadSingleSupportFile (
  IN EFI_DEVICE_PATH_PROTOCOL             *DevicePath,
  IN CHAR16                               *FileName,
  OUT EFI_NETWORK_TEST_FILE               **TestFile
  );

EFI_STATUS
EntsCreateSingleSupportFile (
  IN EFI_DEVICE_PATH_PROTOCOL   *DevicePath,
  IN CHAR16                     *FileName,
  IN CHAR16                     *CmdName,
  IN EFI_HANDLE                 ImageHandle,
  IN UINTN                      Type,
  IN VOID                       *Context,
  OUT EFI_NETWORK_TEST_FILE     **TestFile
  );

EFI_STATUS
EntsUnloadSingleSupportFile (
  IN EFI_NETWORK_TEST_FILE          *TestFile
  );

EFI_STATUS
EntsLoadSingleDriverFile (
  IN EFI_DEVICE_PATH_PROTOCOL        *DevicePath,
  IN CHAR16                          *FileName
  );

EFI_STATUS
EntsLoadConnectAllDriversToAllControllers (
  VOID
  );

//
// External Functions implementations
//
EFI_STATUS
EntsLoadSupportFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN BOOLEAN                      Recursive
  )
/*++

Routine Description:

  Load all support files.

Arguments:

  DevicePath  - Device path of the test files.
  FilePath    - Path of the test files.
  Recursive   - Resursively.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                      Status;
  EFI_HANDLE                      DeviceHandle;
  EFI_FILE_HANDLE                 RootDir;
  EFI_FILE_HANDLE                 TestDir;
  CHAR16                          *SubDir;
  CHAR16                          *FileName;
  UINTN                           FileInfoSize;
  EFI_FILE_INFO                   *FileInfo;
  EFI_DEVICE_PATH_PROTOCOL        *RemainderPath;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Vol;
  EFI_NETWORK_TEST_FILE           *TestFile;

  //
  // Trace information
  //
  SctPrint (L"Load support files ...\n");
  EFI_ENTS_STATUS ((L"Load support files ..."));
  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FilePath == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Locate the device handle from the device path
  //
  RemainderPath = DevicePath;

  Status = tBS->LocateDevicePath (
                &gEfiSimpleFileSystemProtocolGuid,
                &RemainderPath,
                &DeviceHandle
                );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"in LoadTestFile: Locate device handle - %r", Status));
    return Status;
  }
  //
  // Locate the volume of the file system
  //
  Status = tBS->HandleProtocol (
                DeviceHandle,
                &gEfiSimpleFileSystemProtocolGuid,
                (VOID **)&Vol
                );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"in LoadTestFile: Locate file volume - %r", Status));
    return Status;
  }
  //
  // Open the root volume
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Open file volume - %r", Status));
    return Status;
  }
  //
  // Open the test dir
  //
  Status = RootDir->Open (
                      RootDir,
                      &TestDir,
                      FilePath,
                      EFI_FILE_MODE_READ,
                      EFI_FILE_DIRECTORY
                      );
  if (EFI_ERROR (Status)) {
    RootDir->Close (RootDir);
    return Status;
  }

  RootDir->Close (RootDir);

  //
  // Allocate memory for the entries in the directory
  //
  FileInfoSize = sizeof (EFI_FILE_INFO) + ENTS_MAX_BUFFER_SIZE * 4;

  Status = tBS->AllocatePool (
                EfiBootServicesData,
                FileInfoSize,
                (VOID **)&FileInfo
                );
  if (EFI_ERROR (Status)) {
    TestDir->Close (TestDir);
    return Status;
  }
  //
  // Walk through each file in the test directory
  //
  EFI_ENTS_STATUS ((L"reading a file entry.."));
  while (TRUE) {
    TestFile = NULL;

    //
    // Read a file entry
    //
    FileInfoSize = sizeof (EFI_FILE_INFO) + ENTS_MAX_BUFFER_SIZE * 4;

    Status = TestDir->Read (
                        TestDir,
                        &FileInfoSize,
                        FileInfo
                        );
    if (EFI_ERROR (Status) || (FileInfoSize == 0)) {
      break;
    }

    if ((FileInfo->Attribute & EFI_FILE_DIRECTORY) == 0) {
      //
      // Initialize Filename
      //
      FileName = SctPoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);
      if (FileName == NULL) {
        EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Pool print - %r", EFI_OUT_OF_RESOURCES));
        break;
      }
      //
      // This is a .efi file
      //
      if (EntsStrEndWith (FileInfo->FileName, L".efi")) {
        //
        // Load Eftp support driver.
        //
        if (EntsStrEndWith (FileInfo->FileName, L"Eftp.efi")) {
          Status = EntsLoadSingleDriverFile (DevicePath, FileName);
          if (EFI_ERROR (Status)) {
            EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Load Eftp support driver (%s) - %r", FileName, Status));
            tBS->FreePool (FileName);
            continue;
          }
        } else {
          //
          // load other support drivers.
          //
          Status = EntsLoadSingleSupportFile (
                    DevicePath,
                    FileName,
                    &TestFile
                    );

          if (EFI_ERROR (Status)) {
            EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Load a test file(%s) - %r", FileName, Status));
            tBS->FreePool (FileName);
            continue;
          }

          tBS->FreePool (FileName);
          //
          // Add the test file to the test file list
          //
          SctInsertTailList (&gEasFT->SupportList, &TestFile->Link);
        }
      }
    } else {
      if (Recursive) {
        //
        // Skip the '.' and '..' dir
        //
        if ((SctStrCmp (FileInfo->FileName, L".") == 0) || (SctStrCmp (FileInfo->FileName, L"..") == 0)) {
          continue;
        }
        //
        // Load the test files under the sub directory
        //
        SubDir = SctPoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);
        if (SubDir == NULL) {
          EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Pool print - %r", EFI_OUT_OF_RESOURCES));
          break;
        }

        Status = EntsLoadSupportFiles (
                  DevicePath,
                  SubDir,
                  Recursive
                  );
        if (EFI_ERROR (Status)) {
          tBS->FreePool (SubDir);
          continue;
        }

        tBS->FreePool (SubDir);
      }
    }
  }
  //
  // Free resources
  //
  tBS->FreePool (FileInfo);
  TestDir->Close (TestDir);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EntsUnloadSupportFiles (
  IN SCT_LIST_ENTRY               *TestAppList
  )
/*++

Routine Description:

  Unload all support files.

Arguments:

  TestAppList - Pointer to the test file list.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_NETWORK_TEST_FILE *TestFile;
  EFI_STATUS            Status;

  Status = EFI_SUCCESS;

  //
  // Unload Eftp Driver
  //
  if (mEftpTargetHandle != NULL) {
    tBS->UnloadImage (mEftpTargetHandle);
    mEftpTargetHandle = NULL;
  }

  //
  // Trace information
  //
  EFI_ENTS_STATUS ((L"Unload support files ..."));
  while (!SctIsListEmpty (TestAppList)) {
    TestFile = CR (TestAppList->ForwardLink, EFI_NETWORK_TEST_FILE, Link, EFI_NETWORK_TEST_FILE_SIGNATURE);

    SctRemoveEntryList (&TestFile->Link);
    Status = EntsUnloadSingleSupportFile (TestFile);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}
//
// Local Functions implementations
//
EFI_STATUS
EntsLoadSingleSupportFile (
  IN EFI_DEVICE_PATH_PROTOCOL        *DevicePath,
  IN CHAR16                          *FileName,
  OUT EFI_NETWORK_TEST_FILE          **TestFile
  )
/*++

Routine Description:

  Load a single support file.

Arguments:

  DevicePath  - Device path of the test file.
  FileName    - Name of the test file.
  TestFile    - Pointer to the test file structure's pointer.
  
Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_OUT_OF_RESOURCES  - FileNode is NULL or FilePath is NULL.
  EFI_UNSUPPORTED       - File was not supported.
  Others                - Some failure happened.
  
--*/
{
  EFI_STATUS                Status;
  EFI_HANDLE                ImageHandle;
  EFI_DEVICE_PATH_PROTOCOL  *FileNode;
  EFI_DEVICE_PATH_PROTOCOL  *FilePath;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
  UINTN                     ExitDataSize;
  CHAR16                    *ExitData;
  EFI_ENTS_MONITOR_PROTOCOL *EntsMonitorProtocol;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (TestFile == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Add the file path to the device path
  //
  FileNode = SctFileDevicePath (NULL, FileName);
  if (FileNode == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = SctAppendDevicePath (DevicePath, FileNode);
  if (FilePath == NULL) {
    tBS->FreePool (FileNode);
    return EFI_OUT_OF_RESOURCES;
  }

  tBS->FreePool (FileNode);

  //
  // Load the test file
  //
  Status = tBS->LoadImage (
                FALSE,
                gEasFT->ImageHandle,
                FilePath,
                NULL,
                0,
                &ImageHandle
                );
  if (EFI_ERROR (Status)) {
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);

  //
  // Verify the image is a driver or not
  //
  Status = tBS->HandleProtocol (
                ImageHandle,
                &gEfiLoadedImageProtocolGuid,
                (VOID **)&LoadedImage
                );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if ((LoadedImage->ImageCodeType == EfiBootServicesCode) || (LoadedImage->ImageCodeType == EfiRuntimeServicesCode)) {
    //
    // It is a driver
    //
    Status = tBS->StartImage (
                  ImageHandle,
                  &ExitDataSize,
                  &ExitData
                  );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = tBS->HandleProtocol (
                  ImageHandle,
                  &gEfiEntsMonitorProtocolGuid,
                  (VOID **)&EntsMonitorProtocol
                  );
    if (!EFI_ERROR (Status)) {
      Status = EntsCreateSingleSupportFile (
                DevicePath,
                FileName,
                EntsMonitorProtocol->MonitorName,
                ImageHandle,
                EFI_NETWORK_TEST_FILE_DRIVER,
                NULL,
                TestFile
                );
      if (EFI_ERROR (Status)) {
        return Status;
      }
    } else {
      return EFI_UNSUPPORTED;
    }
  } else {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EntsLoadSingleDriverFile (
  IN EFI_DEVICE_PATH_PROTOCOL        *DevicePath,
  IN CHAR16                          *FileName
  )
/*++

Routine Description:

  Load support driver need to be connected.

Arguments:

  DevicePath  - Device path of the support driver file.
  FileName    - Name of the test file.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_OUT_OF_RESOURCES  - FileNode is NULL or FilePath is NULL.
  EFI_UNSUPPORTED       - File was not supported.
  Others                - Some failure happened.
  
--*/
{
  EFI_STATUS                Status;
  EFI_HANDLE                ImageHandle;
  EFI_DEVICE_PATH_PROTOCOL  *FileNode;
  EFI_DEVICE_PATH_PROTOCOL  *FilePath;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
  UINTN                     ExitDataSize;
  CHAR16                    *ExitData;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Add the file path to the device path
  //
  FileNode = SctFileDevicePath (NULL, FileName);
  if (FileNode == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = SctAppendDevicePath (DevicePath, FileNode);
  if (FilePath == NULL) {
    tBS->FreePool (FileNode);
    return EFI_OUT_OF_RESOURCES;
  }

  tBS->FreePool (FileNode);

  //
  // Load the driver file
  //
  Status = tBS->LoadImage (
                FALSE,
                gEasFT->ImageHandle,
                FilePath,
                NULL,
                0,
                &ImageHandle
                );
  if (EFI_ERROR (Status)) {
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);

  //
  // Verify the image is a driver or not
  //
  Status = tBS->HandleProtocol (
                ImageHandle,
                &gEfiLoadedImageProtocolGuid,
                (VOID **)&LoadedImage
                );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if ((LoadedImage->ImageCodeType == EfiBootServicesCode) || (LoadedImage->ImageCodeType == EfiRuntimeServicesCode)) {
    //
    // It is a driver
    //
    Status = tBS->StartImage (
                  ImageHandle,
                  &ExitDataSize,
                  &ExitData
                  );
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //
    // Connect driver to all controllers.
    //
    mEftpTargetHandle = ImageHandle;
    Status            = EntsLoadConnectAllDriversToAllControllers ();
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EntsUnloadSingleSupportFile (
  IN EFI_NETWORK_TEST_FILE          *TestFile
  )
/*++

Routine Description:

  Unload a single support file.

Arguments:

  TestFile  - Pointer to the test file structure.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  //
  // Free the items of the test file
  //
  if (TestFile->DevicePath != NULL) {
    tBS->FreePool (TestFile->DevicePath);
    TestFile->DevicePath = NULL;
  }

  if (TestFile->FileName != NULL) {
    tBS->FreePool (TestFile->FileName);
    TestFile->FileName = NULL;
  }

  if (TestFile->CmdName != NULL) {
    tBS->FreePool (TestFile->CmdName);
    TestFile->CmdName = NULL;
  }

  if (TestFile->Type == EFI_NETWORK_TEST_FILE_DRIVER) {
    tBS->UnloadImage (TestFile->ImageHandle);
  }
  //
  // Free the test file itself
  //
  tBS->FreePool (TestFile);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EntsCreateSingleSupportFile (
  IN EFI_DEVICE_PATH_PROTOCOL   *DevicePath,
  IN CHAR16                     *FileName,
  IN CHAR16                     *CmdName,
  IN EFI_HANDLE                 ImageHandle,
  IN UINTN                      Type,
  IN VOID                       *Context,
  OUT EFI_NETWORK_TEST_FILE     **TestFile
  )
/*++

Routine Description:

  Create a single support file.

Arguments:

  DevicePath  - Device path of the test file.
  FileName    - Name of the test file.
  CmdName     - Command name string.
  ImageHandle - The image handle.
  Type        - Type of the test file.
  Context     - Context of the test file.
  TestFile    - Pointer to the test file structure's pointer.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  Others                - Some failure happened.

--*/
{
  EFI_STATUS  Status;

  //
  // Check parameter
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (TestFile == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Allocate memory for the test file
  //
  Status = tBS->AllocatePool (
                EfiBootServicesData,
                sizeof (EFI_NETWORK_TEST_FILE),
                (VOID **)TestFile
                );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  SctZeroMem (*TestFile, sizeof (EFI_NETWORK_TEST_FILE));

  //
  // Initialize the test file
  //
  (*TestFile)->Signature    = EFI_NETWORK_TEST_FILE_SIGNATURE;
  (*TestFile)->Version      = EFI_NETWORK_TEST_FILE_VERSION;

  (*TestFile)->DevicePath   = SctDuplicateDevicePath (DevicePath);
  (*TestFile)->FileName     = EntsStrDuplicate (FileName);
  (*TestFile)->CmdName      = EntsStrDuplicate (CmdName);
  (*TestFile)->ImageHandle  = ImageHandle;
  (*TestFile)->Type         = Type;
  (*TestFile)->Context      = Context;
  SctInitializeListHead (&(*TestFile)->Link);

  //
  // Done
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EntsLoadConnectAllDriversToAllControllers (
  VOID
  )
/*++

Routine Description:

  Connect all drivers to all controllers.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others - Operation failed.

--*/
{
  EFI_STATUS  Status;
  UINTN       AllHandleCount;
  EFI_HANDLE  *AllHandleBuffer;
  UINTN       Index;
  UINTN       HandleCount;
  EFI_HANDLE  *HandleBuffer;
  UINT32      *HandleType;
  UINTN       HandleIndex;
  BOOLEAN     Parent;
  BOOLEAN     Device;

  Status = SctLocateHandle (
            AllHandles,
            NULL,
            NULL,
            &AllHandleCount,
            &AllHandleBuffer
            );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  for (Index = 0; Index < AllHandleCount; Index++) {
    if (SctShellGetExecutionBreak ()) {
      Status = EFI_ABORTED;
      goto Done;
    }
    //
    // Scan the handle database
    //
    Status = SctScanHandleDatabase (
              NULL,
              NULL,
              AllHandleBuffer[Index],
              NULL,
              &HandleCount,
              &HandleBuffer,
              &HandleType
              );
    if (EFI_ERROR (Status)) {
      goto Done;
    }

    Device = TRUE;
    if (HandleType[Index] & SCT_HANDLE_TYPE_DRIVER_BINDING_HANDLE) {
      Device = FALSE;
    }

    if (HandleType[Index] & SCT_HANDLE_TYPE_IMAGE_HANDLE) {
      Device = FALSE;
    }

    if (Device) {
      Parent = FALSE;
      for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        if (HandleType[HandleIndex] & SCT_HANDLE_TYPE_PARENT_HANDLE) {
          Parent = TRUE;
        }
      }

      if (!Parent) {
        if (HandleType[Index] & SCT_HANDLE_TYPE_DEVICE_HANDLE) {
          Status = tBS->ConnectController (
                        AllHandleBuffer[Index],
                        NULL,
                        NULL,
                        TRUE
                        );
        }
      }
    }

    tBS->FreePool (HandleBuffer);
	tBS->FreePool (HandleType);
  }

Done:
  tBS->FreePool (AllHandleBuffer);
  return Status;
}
