/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SecureBootBBTestSupport.c

Abstract:

  BB test support source file for Secure Boot

--*/

#include "SctLib.h"
#include "SecureBootBBTestMain.h"
#include "SecureBootBBTestSupport.h"

#define KEK_ATTRIBUTES (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                       EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)


//
// globals variables
//

EFI_DEVICE_PATH_PROTOCOL        *gDevicePath     = NULL;
CHAR16                          *gFilePath       = NULL;
EFI_HANDLE                      gDeviceHandle;
EFI_HANDLE                      mImageHandle;

//
// internal helper function.
//

/*
 *  get the system device path and file path.
 *  @param ProfileLib the Profile Library Protocol instance.
 *  @return EFI_SUCCESS the system device path and file path were gotten successfully.
 */
EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  CHAR16                      *TempFilePath;
  EFI_STATUS                  Status;

  //
  // If gFilePath and gDevicePath has been assigned, return directly.
  //
  if ((gFilePath != NULL) && (gDevicePath != NULL)) {
    return EFI_SUCCESS;
  }

  //
  // Free gFilePath or gDevicePath
  //
  if (gFilePath != NULL) {
    gtBS->FreePool (gFilePath);
    gFilePath = NULL;
  }
  if (gDevicePath != NULL) {
    gtBS->FreePool (gDevicePath);
    gDevicePath = NULL;
  }

  //
  //Get system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &TempDevicePath,
                         &TempFilePath
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //make up the file path.
  //
  gFilePath = NULL;
  gFilePath = SctPoolPrint (L"%s\\%s", TempFilePath, DEPENDECY_DIR_NAME);

  gtBS->FreePool (TempFilePath);

  if (gFilePath == NULL) {
    gtBS->FreePool (TempDevicePath);
    return EFI_OUT_OF_RESOURCES;
  }

  gDevicePath = TempDevicePath;

  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;
}


/*
 *  get the device handle.
 *  @param ImageHandle the Image Handle instance.
 *  @return EFI_SUCCESS the device handle was gotten successfully.
 */
EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  )
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *Image;

  gImageHandle = ImageHandle;

  //
  // Get the image instance from the image handle
  //
  Status = gtBS->HandleProtocol (
                   ImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **) &Image
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  gDeviceHandle = Image->DeviceHandle;


  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;
}

/**
 *  Open the file and get the file size.
 *  @param FileName the file name to be opened.
 *  @param FileHandle the opened file handle.
 *  @param FileSize the opened file size.
 *  @return EFI_SUCCESS the file was opened successfully.
 */
EFI_STATUS
OpenFileAndGetSize (
  IN  CHAR16          *FileName,
  OUT EFI_FILE_HANDLE *FileHandle,
  OUT UINT32          *FileSize
  )
{
  EFI_FILE_HANDLE     RootDir;
  EFI_FILE_HANDLE     FHandle;
  CHAR16              *FileNameBuffer;
  EFI_STATUS          Status;
  EFI_FILE_INFO       *FileInfo;

  if (FileName == NULL || FileHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  RootDir = NULL;
  //
  //Open the root directory.
  //
  RootDir = SctOpenRoot (gDeviceHandle);
  if (RootDir == NULL) {
    return EFI_NOT_FOUND;
  }
  //
  //make up the file name.
  //
  FileNameBuffer = SctPoolPrint (L"%s\\%s", gFilePath, FileName);
  if (FileNameBuffer == NULL) {
    RootDir->Close (RootDir);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RootDir->Open (
                      RootDir,
                      &FHandle,
                      FileNameBuffer,
                      EFI_FILE_MODE_READ,
                      0
                      );
  RootDir->Close (RootDir);
  gtBS->FreePool (FileNameBuffer);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //get the file size.
  //
  if (FileSize != NULL) {
    FileInfo = NULL;
    Status = SctGetFileInfo (FHandle, &FileInfo);

    if (EFI_ERROR (Status)) {
      return Status;
    }
    *FileSize = (UINT32)FileInfo->FileSize;
    gtBS->FreePool (FileInfo);
  }

  *FileHandle = FHandle;
  //
  //done successfully return EFI_SUCCESS.
  //
  return EFI_SUCCESS;
}

/**
 *  Get BaseName from a given path string
 *  @param FileName The full pathname.
 *  @param BaseName Extracted Filename.
 *  @return EFI_SUCCESS the BaseName was extracted from the full path.
 */
EFI_STATUS
GetBaseName (
  IN  CHAR16          *FileName,
  OUT CHAR16          **BaseName
  )
{
  UINT32              StrLen;
  CHAR16              *StrTail;

  StrLen = SctStrLen(FileName);

  for (StrTail = FileName + StrLen - 1; StrTail != FileName && *StrTail != L'\\'; StrTail--) {
  }

  if (StrTail == FileName) {
    return EFI_NOT_FOUND;
  }
  *BaseName = StrTail+1;

  return EFI_SUCCESS;
}

/**
 *  Restore the secure boot variables to initial values.
 *  The initial siglists are:
 *     TestKEK1.auth
 *     TestDB1.auth
 *     TestDBX1.auth
 *
 *  @param StandardLib    A pointer to EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *                        instance.
 *  @param LoggingLib     A pointer to EFI_TEST_LOGGING_LIBRARY_PROTOCOL
 *                        instance.
 *  @param ProfileLib     A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
SecureBootVariableCleanup (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  )
{
  EFI_STATUS            Status;
  EFI_FILE_HANDLE       KeyFHandle;
  UINT32                KeyFileSize;
  CHAR16                *FileName;
  VOID                  *Buffer;
  UINTN                 BufferSize;
  UINTN                 DataSize;
  UINT32                DBAttributes;
  UINT32                DBXAttributes;

  Status = EFI_SUCCESS;

  StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"SecureBootVariableCleanup: Doing cleanup of secure boot variables\n"
                     );
  //
  // Clean up KEK, delete and replace with original value
  //

  // signed, empty siglist image to delete KEK
  FileName = L"NullKEK.auth";

  //
  //read the key file into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"KEK",                    // VariableName
                     &gEfiGlobalVariableGuid,   // VendorGuid
                     KEK_ATTRIBUTES,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"SecureBootVariableCleanup: KEK delete failed\n"
                     );
    Status = EFI_NOT_FOUND;
  }

  gtBS->FreePool (Buffer);

  FileName = L"TestKEK1.auth";

  //
  //read the key file into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"KEK",                    // VariableName
                     &gEfiGlobalVariableGuid,   // VendorGuid
                     KEK_ATTRIBUTES,            // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"SecureBootVariableCleanup: KEK clean up failed\n"
                     );
    Status = EFI_NOT_FOUND;
  }

  gtBS->FreePool (Buffer);

  //
  // Clean up db, delete and replace with original value
  //

  // get db variable attributes
  DataSize = 0;
  Status = RT->GetVariable (
                 L"db",                          // VariableName
                 &gEfiImageSecurityDatabaseGuid, // VendorGuid
                 &DBAttributes,                  // Attributes
                 &DataSize,                      // DataSize
                 NULL                            // Data
                 );

  // signed, empty siglist image to delete db
  FileName = L"NullDB.auth";

  //
  // read the siglist into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"db",                    // VariableName
                     &gEfiImageSecurityDatabaseGuid,   // VendorGuid
                     DBAttributes,              // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"SecureBootVariableCleanup: db delete failed\n"
                     );
    Status = EFI_NOT_FOUND;
  }

  gtBS->FreePool (Buffer);

  FileName = L"TestDB1.auth";

  //
  // read the siglist into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"db",                     // VariableName
                     &gEfiImageSecurityDatabaseGuid,   // VendorGuid
                     DBAttributes,              // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"SecureBootVariableCleanup: db clean up failed\n"
                     );
    Status = EFI_NOT_FOUND;
  }

  gtBS->FreePool (Buffer);

  //
  // Clean up dbx, delete and replace with original value
  //

  // get dbx variable attributes
  DataSize = 0;
  Status = RT->GetVariable (
                 L"dbx",                          // VariableName
                 &gEfiImageSecurityDatabaseGuid, // VendorGuid
                 &DBXAttributes,                  // Attributes
                 &DataSize,                      // DataSize
                 NULL                            // Data
                 );

  // signed, empty siglist image to delete dbx
  FileName = L"NullDBX.auth";

  //
  // read the siglist into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"dbx",                    // VariableName
                     &gEfiImageSecurityDatabaseGuid,   // VendorGuid
                     DBXAttributes,             // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"SecureBootVariableCleanup: dbx delete failed. Status=%r\n",
                     Status
                     );
    Status = EFI_NOT_FOUND;
  }

  gtBS->FreePool (Buffer);

  FileName = L"TestDBX1.auth";

  //
  // read the siglist into memory.
  //
  Status = OpenFileAndGetSize (
             FileName,
             &KeyFHandle,
             &KeyFileSize
             );

  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  Buffer = SctAllocatePool (KeyFileSize);

  if (Buffer == NULL) {
    KeyFHandle->Close (KeyFHandle);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = KeyFileSize;

  Status = KeyFHandle->Read (
                      KeyFHandle,
                      &BufferSize,
                      Buffer
                      );

  if (EFI_ERROR(Status)) {
    KeyFHandle->Close (KeyFHandle);
    gtBS->FreePool (Buffer);
    return EFI_LOAD_ERROR;
  }

  Status = RT->SetVariable (
                     L"dbx",                     // VariableName
                     &gEfiImageSecurityDatabaseGuid,   // VendorGuid
                     DBXAttributes,             // Attributes
                     BufferSize,                // DataSize
                     Buffer                     // Data
                     );

  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"SecureBootVariableCleanup: dbx clean up failed\n"
                     );
    Status = EFI_NOT_FOUND;
  }

  gtBS->FreePool (Buffer);

  return Status;

}
