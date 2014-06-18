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

  TestFile.c

Abstract:

  This file provides the services to load/unload the test drivers.

--*/

#include "Sct.h"

//
// Internal functions declaration
//

EFI_STATUS
LoadSingleTestImageFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_SCT_TEST_FILE           **TestFile
  );

EFI_STATUS
LoadSingleTestScriptFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_SCT_TEST_FILE           **TestFile
  );

EFI_STATUS
CreateSingleTestFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SCT_TEST_FILE_TYPE       Type,
  IN VOID                         *Context,
  OUT EFI_SCT_TEST_FILE           **TestFile
  );

EFI_STATUS
UnloadSingleTestFile (
  IN EFI_SCT_TEST_FILE            *TestFile
  );


//
// External functions implementation
//

EFI_STATUS
LoadTestFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN BOOLEAN                      Recursive,
  OUT SCT_LIST_ENTRY              *TestFileList
  )
/*++

Routine Description:

  Load all test files.

Arguments:

  DevicePath    - Device path of the test files.
  FilePath      - Path of the test files.
  Recursive     - Resursively.
  TestFileList  - Pointer to a test file list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        DeviceHandle;
  EFI_FILE_HANDLE                   RootDir;
  EFI_FILE_HANDLE                   TestDir;
  CHAR16                            *SubDir;
  CHAR16                            *FileName;
  UINTN                             FileInfoSize;
  EFI_FILE_INFO                     *FileInfo;
  EFI_SCT_TEST_FILE                 *TestFile;
  EFI_DEVICE_PATH_PROTOCOL          *RemainderPath;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Vol;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FilePath == NULL) || (TestFileList == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Load test files from <%s>", FilePath));

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
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Locate device handle - %r", Status));
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
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Locate file system - %r", Status));
    return Status;
  }

  //
  // Open the root volume
  //
  Status = Vol->OpenVolume (Vol, &RootDir);
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open file volume - %r", Status));
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
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Open test directory - %r", Status));
    RootDir->Close (RootDir);
    return Status;
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
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    TestDir->Close (TestDir);
    return Status;
  }

  //
  // Walk through each file in the test directory
  //
  while (TRUE) {
    //
    // Read a file entry
    //
    FileInfoSize = sizeof(EFI_FILE_INFO) + 1024;

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
      // This is a file
      //
      if (SctStrEndWith (FileInfo->FileName, L".efi")) {
        //
        // Load the test image file
        //
        FileName = SctPoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);
        if (FileName == NULL) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pool print - %r", EFI_OUT_OF_RESOURCES));
          break;
        }

        Status = LoadSingleTestImageFile (
                   DevicePath,
                   FileName,
                   &TestFile
                   );
        if (EFI_ERROR (Status)) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load a test image file - %r", Status));
          tBS->FreePool (FileName);
          continue;
        }

        tBS->FreePool (FileName);

        //
        // Add the test file to the test file list
        //
        SctInsertTailList (TestFileList, &TestFile->Link);

      } else if (SctStrEndWith (FileInfo->FileName, L".nsh")) {
        //
        // Load the test script file
        //
        FileName = SctPoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);
        if (FileName == NULL) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pool print - %r", EFI_OUT_OF_RESOURCES));
          break;
        }

        Status = LoadSingleTestScriptFile (
                   DevicePath,
                   FileName,
                   &TestFile
                   );
        if (EFI_ERROR (Status)) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load a test script file - %r", Status));
          tBS->FreePool (FileName);
          continue;
        }

        tBS->FreePool (FileName);

        //
        // Add the test file to the test file list
        //
        SctInsertTailList (TestFileList, &TestFile->Link);
      }

    } else {
      if (Recursive) {
        //
        // Skip the '.' and '..' dir
        //
        if ((SctStrCmp (FileInfo->FileName, L".")  == 0) ||
            (SctStrCmp (FileInfo->FileName, L"..") == 0)) {
          continue;
        }

        //
        // Load the test files under the sub directory
        //
        SubDir = SctPoolPrint (L"%s\\%s", FilePath, FileInfo->FileName);
        if (SubDir == NULL) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Pool print - %r", EFI_OUT_OF_RESOURCES));
          break;
        }

        Status = LoadTestFiles (
                   DevicePath,
                   SubDir,
                   Recursive,
                   TestFileList
                   );
        if (EFI_ERROR (Status)) {
          EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load test files - %r", Status));
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
UnloadTestFiles (
  IN SCT_LIST_ENTRY               *TestFileList
  )
/*++

Routine Description:

  Unload all test files.

Arguments:

  TestFileList  - Pointer to the test file list.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_SCT_TEST_FILE   *TestFile;

  //
  // Check parameters
  //
  if (TestFileList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Unload test files"));

  //
  // Walk through all test files
  //
  while (!SctIsListEmpty (TestFileList)) {
    TestFile = CR (TestFileList->ForwardLink, EFI_SCT_TEST_FILE, Link, EFI_SCT_TEST_FILE_SIGNATURE);

    SctRemoveEntryList (&TestFile->Link);
    UnloadSingleTestFile (TestFile);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FindTestFileByCaseGuid (
  IN EFI_GUID                     *Guid,
  OUT EFI_SCT_TEST_FILE           **TestFile,
  OUT VOID                        **TestProtocol,
  OUT VOID                        **TestEntry
  )
/*++

Routine Description:

  Search the test file based on the test case's GUID.

Arguments:

  Guid          - Specifies GUID to search by.
  TestFile      - Pointer to the test file.
  TestProtocol  - Pointer to the test protocol.
  TestEntry     - Pointer to the test entry.

Returns:

  EFI_SUCCESS   - Successfully.
  EFI_NOT_FOUND - Not found.
  Other value   - Something failed.

--*/
{
  SCT_LIST_ENTRY          *Link;
  EFI_SCT_TEST_FILE       *TempTestFile;
  EFI_BB_TEST_PROTOCOL    *BbTest;
  EFI_BB_TEST_ENTRY       *BbEntry;
  EFI_WB_TEST_PROTOCOL    *WbTest;
  EFI_WB_TEST_ENTRY       *WbEntry;
  EFI_AP_TEST_INTERFACE   *ApTest;
  EFI_AP_TEST_ENTRY       *ApEntry;

  //
  // Check parameters
  //
  if ((Guid         == NULL) || (TestFile  == NULL) ||
      (TestProtocol == NULL) || (TestEntry == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Walk through all test files
  //
  for (Link = gFT->TestFileList.ForwardLink; Link != &gFT->TestFileList; Link = Link->ForwardLink) {
    TempTestFile = CR (Link, EFI_SCT_TEST_FILE, Link, EFI_SCT_TEST_FILE_SIGNATURE);

    //
    // Deal with the different kinds of test files
    //
    switch (TempTestFile->Type) {
    case EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX:
    case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
      //
      // Black-box test file
      //
      BbTest = (EFI_BB_TEST_PROTOCOL *) TempTestFile->Context;

      for (BbEntry = BbTest->EntryList; BbEntry != NULL; BbEntry = BbEntry->Next) {
        if (SctCompareGuid (Guid, &BbEntry->EntryId) == 0) {
          break;
        }
      }

      if (BbEntry != NULL) {
        *TestFile     = TempTestFile;
        *TestProtocol = BbTest;
        *TestEntry    = BbEntry;

        return EFI_SUCCESS;
      }

      break;

    case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
      //
      // White-box test file
      //
      WbTest = (EFI_WB_TEST_PROTOCOL *) TempTestFile->Context;

      for (WbEntry = WbTest->EntryList; WbEntry != NULL; WbEntry = WbEntry->Next) {
        if (SctCompareGuid (Guid, &WbEntry->EntryId) == 0) {
          break;
        }
      }

      if (WbEntry != NULL) {
        *TestFile     = TempTestFile;
        *TestProtocol = WbTest;
        *TestEntry    = WbEntry;

        return EFI_SUCCESS;
      }

      break;

    case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
    case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
      //
      // EFI application or script test file
      //
      ApTest = (EFI_AP_TEST_INTERFACE *) TempTestFile->Context;

      for (ApEntry = ApTest->EntryList; ApEntry != NULL; ApEntry = ApEntry->Next) {
        if (SctCompareGuid (Guid, &ApEntry->EntryId) == 0) {
          break;
        }
      }

      if (ApEntry != NULL) {
        *TestFile     = TempTestFile;
        *TestProtocol = ApTest;
        *TestEntry    = ApEntry;

        return EFI_SUCCESS;
      }

      break;

    default:
      //
      // Unsupported file
      //
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupported file"));
      return EFI_UNSUPPORTED;
    }
  }

  //
  // Not found
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Not found"));
  return EFI_NOT_FOUND;
}


//
// Internal functions implementation
//

EFI_STATUS
LoadSingleTestImageFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_SCT_TEST_FILE           **TestFile
  )
/*++

Routine Description:

  Load a single test image file.

--*/
{
  EFI_STATUS                  Status;
  EFI_HANDLE                  ImageHandle;
  EFI_DEVICE_PATH_PROTOCOL    *FileNode;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  CHAR16                      *ApFileName;
  EFI_BB_TEST_PROTOCOL        *BbTest;
  EFI_WB_TEST_PROTOCOL        *WbTest;
  EFI_AP_TEST_INTERFACE       *ApTest;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (TestFile == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Load test image file <%s>", FileName));

  //
  // Add the file path to the device path
  //
  FileNode = SctFileDevicePath (NULL, FileName);
  if (FileNode == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctFileDevicePath: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = SctAppendDevicePath (DevicePath, FileNode);
  if (FilePath == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctAppendDevicePath: Out of resources"));
    tBS->FreePool (FileNode);
    return EFI_OUT_OF_RESOURCES;
  }

  tBS->FreePool (FileNode);

  //
  // Load the test image file
  //
  Status = tBS->LoadImage (
                 FALSE,
                 gFT->ImageHandle,
                 FilePath,
                 NULL,
                 0,
                 &ImageHandle
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Load image - %r", Status));
    tBS->FreePool (FilePath);
    return Status;
  }

  tBS->FreePool (FilePath);

  //
  // Check the image is a driver or an application
  //
  Status = tBS->HandleProtocol (
                 ImageHandle,
                 &gEfiLoadedImageProtocolGuid,
                 (VOID **)&LoadedImage
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Locate loaded image - %r", Status));
    return Status;
  }

  if ((LoadedImage->ImageCodeType == EfiBootServicesCode   ) ||
      (LoadedImage->ImageCodeType == EfiRuntimeServicesCode)) {
    //
    // It is a driver
    //
    Status = tBS->StartImage (
                   ImageHandle,
                   &ExitDataSize,
                   &ExitData
                   );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Start image - %r", Status));
      return Status;
    }

    //
    // Is it a black-box test?
    //
    Status = tBS->HandleProtocol (
                   ImageHandle,
                   &gEfiBbTestGuid,
                   (VOID **)&BbTest
                   );
    if (!EFI_ERROR (Status)) {
      Status = CreateSingleTestFile (
                 DevicePath,
                 FileName,
                 ImageHandle,
                 EFI_SCT_TEST_FILE_TYPE_BLACK_BOX,
                 BbTest,
                 TestFile
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test file - %r", Status));
        tBS->UnloadImage (ImageHandle);
        return Status;
      }

      return EFI_SUCCESS;
    }

    //
    // Is it a white-box test?
    //
    Status = tBS->HandleProtocol (
                   ImageHandle,
                   &gEfiWbTestGuid,
                   (VOID **)&WbTest
                   );
    if (!EFI_ERROR (Status)) {
      Status = CreateSingleTestFile (
                 DevicePath,
                 FileName,
                 ImageHandle,
                 EFI_SCT_TEST_FILE_TYPE_WHITE_BOX,
                 WbTest,
                 TestFile
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test file - %r", Status));
        tBS->UnloadImage (ImageHandle);
        return Status;
      }

      return EFI_SUCCESS;
    }

    //
    // Is it a IHV black-box test?
    //
    Status = tBS->HandleProtocol (
                   ImageHandle,
                   &gEfiIHVBbTestGuid,
                   (VOID **)&BbTest
                   );
    if (!EFI_ERROR (Status)) {
      Status = CreateSingleTestFile (
                 DevicePath,
                 FileName,
                 ImageHandle,
                 EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX,
                 BbTest,
                 TestFile
                 );
      if (EFI_ERROR (Status)) {
        EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test file - %r", Status));
        tBS->UnloadImage (ImageHandle);
        return Status;
      }

      return EFI_SUCCESS;
    }

    tBS->UnloadImage (ImageHandle);
  } else {
    //
    // It is an application
    //
    ApFileName = SctStrEndReplace (FileName, L"ini");
    if (ApFileName == NULL) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Load the application test interface
    //
    Status = LoadApTest (
               DevicePath,
               ApFileName,
               &ApTest
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Unsupported file"));
      tBS->FreePool (ApFileName);
      return EFI_UNSUPPORTED;
    }

    tBS->FreePool (ApFileName);

    Status = CreateSingleTestFile (
               DevicePath,
               FileName,
               NULL,
               EFI_SCT_TEST_FILE_TYPE_APPLICATION,
               ApTest,
               TestFile
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test file - %r", Status));
      FreeApTest (ApTest);
      return Status;
    }

    return EFI_SUCCESS;
  }

  //
  // Unsupported file
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Unsupported file"));
  return EFI_UNSUPPORTED;
}


EFI_STATUS
LoadSingleTestScriptFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  OUT EFI_SCT_TEST_FILE           **TestFile
  )
/*++

Routine Description:

  Load a test script file.

--*/
{
  EFI_STATUS                  Status;
  CHAR16                      *ApFileName;
  EFI_AP_TEST_INTERFACE       *ApTest;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) || (TestFile == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Debug information
  //
  EFI_SCT_DEBUG ((EFI_SCT_D_TRACE, L"Load test script file <%s>", FileName));

  //
  // It is a script
  //
  ApFileName = SctStrEndReplace (FileName, L"ini");
  if (ApFileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Load the application test interface
  //
  Status = LoadApTest (
             DevicePath,
             ApFileName,
             &ApTest
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"Unsupported test file"));
    tBS->FreePool (ApFileName);
    return EFI_UNSUPPORTED;
  }

  Status = CreateSingleTestFile (
             DevicePath,
             FileName,
             NULL,
             EFI_SCT_TEST_FILE_TYPE_SCRIPT,
             ApTest,
             TestFile
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Create a test file - %r", Status));
    FreeApTest (ApTest);
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
CreateSingleTestFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName,
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SCT_TEST_FILE_TYPE       Type,
  IN VOID                         *Context,
  OUT EFI_SCT_TEST_FILE           **TestFile
  )
/*++

Routine Description:

  Create a single test file data structure.

--*/
{
  EFI_STATUS  Status;

  //
  // Check parameters
  //
  if ((DevicePath == NULL) || (FileName == NULL) ||
      (Context    == NULL) || (TestFile == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // ALlocate memory for the test file
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_TEST_FILE),
                 (VOID **)TestFile
                 );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Allocate pool - %r", Status));
    return Status;
  }

  SctZeroMem (*TestFile, sizeof(EFI_SCT_TEST_FILE));

  //
  // Initialize the items of test file
  //
  (*TestFile)->Signature    = EFI_SCT_TEST_FILE_SIGNATURE;
  (*TestFile)->Revision     = EFI_SCT_TEST_FILE_REVISION;

  (*TestFile)->DevicePath   = SctDuplicateDevicePath (DevicePath);
  (*TestFile)->FileName     = SctStrDuplicate (FileName);
  (*TestFile)->ImageHandle  = ImageHandle;
  (*TestFile)->Type         = Type;
  (*TestFile)->Context      = Context;

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
UnloadSingleTestFile (
  IN EFI_SCT_TEST_FILE            *TestFile
  )
/*++

Routine Description:

  Unload a single test file.

--*/
{
  //
  // Free the items of test file
  //
  if (TestFile->DevicePath != NULL) {
    tBS->FreePool (TestFile->DevicePath);
    TestFile->DevicePath = NULL;
  }

  if (TestFile->FileName != NULL) {
    tBS->FreePool (TestFile->FileName);
    TestFile->FileName = NULL;
  }

  switch (TestFile->Type) {
  case EFI_SCT_TEST_FILE_TYPE_IHV_BLACK_BOX:
  case EFI_SCT_TEST_FILE_TYPE_BLACK_BOX:
  case EFI_SCT_TEST_FILE_TYPE_WHITE_BOX:
    //
    // Black-box or White-box test file
    //
    tBS->UnloadImage (TestFile->ImageHandle);
    break;

  case EFI_SCT_TEST_FILE_TYPE_APPLICATION:
  case EFI_SCT_TEST_FILE_TYPE_SCRIPT:
    //
    // Application or script test file
    //
    FreeApTest ((EFI_AP_TEST_INTERFACE *)TestFile->Context);
    break;

  default:
    //
    // Unsupported file
    //
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"Unsupport file"));
    return EFI_UNSUPPORTED;
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
