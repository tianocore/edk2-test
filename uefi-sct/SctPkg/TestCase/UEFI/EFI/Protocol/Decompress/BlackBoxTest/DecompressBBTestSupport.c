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

  DecompressBBTestSupport.c

Abstract:

  BB test support source file for Decompress protocol

--*/

#include "SctLib.h"
#include "DecompressBBTestMain.h"
#include "DecompressBBTestSupport.h"

//
//const
//

#define COMPRESSED_FILE_NAME_ITEM           L"CompressedFileName"
#define UNCOMPRESSED_FILE_NAME_ITEM         L"UncompressedFileName"
#define INVALID_COMPRESSED_FILE_NAME_ITEM   L"InvalidCompressedFileName"

//
//globals variables
//

EFI_DEVICE_PATH_PROTOCOL        *gDevicePath     = NULL;
CHAR16                          *gFilePath       = NULL;
EFI_HANDLE                      gDeviceHandle;


//
//internal helper function.
//

/**
 *  Support function - Get test support protocol library.
 *  @param SupportHandle  A handle containing support protocols.
 *  @param StandardLib    A pointer to Standard Test Support Protocol.
 *  @param ProfileLib    A pointer to Test Profile Support Protocol.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetTestSupportLibrary (
  IN  EFI_HANDLE                          SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_PROFILE_LIBRARY_PROTOCOL   **ProfileLib
  )
{
  EFI_STATUS            Status;

  //
  // Get the standard test support library interface
  //
  if (StandardLib != NULL) {
    *StandardLib = NULL;
    Status = gtBS->HandleProtocol (
                     SupportHandle,
                     &gEfiStandardTestLibraryGuid,
                     (VOID **) StandardLib
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }
  //
  // Get the test profile support library interface
  //
  if (ProfileLib != NULL) {
    *ProfileLib = NULL;
    Status = gtBS->HandleProtocol (
                     SupportHandle,
                     &gEfiTestProfileLibraryGuid,
                     (VOID **) ProfileLib
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Support function - Open Test .ini file.
 *  @param ProfileLib    A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @param FileHandle     A pointer to EFI_INI_FILE_HANDLE instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
OpenTestIniFile (
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                *FileHandle
  )
{
  CHAR16     *FilePath;
  EFI_STATUS Status;

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, DECOMPRESS_TEST_INI_FILE);

  if (FilePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //open the profile.
  //
  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        FileHandle
                        );

  //
  //free the file path not to be used.
  //

  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //done successfully.
  //
  return EFI_SUCCESS;
}

/**
 *  Support Function - Close the test ini file.
 *  @param ProfileLib    A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @param FileHandle the ini File Handle to be closed.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
CloseTestIniFile (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  IN  EFI_INI_FILE_HANDLE                 FileHandle
  )
{
 return ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );

}

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
 *  get the Uncompressed File Size from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param FileSize the returned file size.
 *  @return EFI_SUCCESS the file size was gotten successfully.
 */
EFI_STATUS
GetUncompressedFileSize (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT32              *FileSize
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || FileSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"UncompressedFileSize",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  *FileSize = (UINT32)SctAtoi (Buffer);

  return EFI_SUCCESS;
}

/**
 *  get the Compressed File Name from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param FileName the returned file Name.
 *  @return EFI_SUCCESS the file Name was gotten successfully.
 */
EFI_STATUS
GetCompressedFileName (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **FileName
  )
{
  return GetStringItemFromFile (
           FileHandle,
           Order,
           SectionName,
           COMPRESSED_FILE_NAME_ITEM,
           FileName
           );
}

/**
 *  get the Uncompressed File Name from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param FileName the returned file Name.
 *  @return EFI_SUCCESS the file Name was gotten successfully.
 */
EFI_STATUS
GetUncompressedFileName (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **FileName
  )
{
  return GetStringItemFromFile (
           FileHandle,
           Order,
           SectionName,
           UNCOMPRESSED_FILE_NAME_ITEM,
           FileName
           );
}

/**
 *  get the Invalid Compressed File Name from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param FileName the returned file Name.
 *  @return EFI_SUCCESS the file Name was gotten successfully.
 */
EFI_STATUS
GetInvalidCompressedFileName (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **FileName
  )
{
  return GetStringItemFromFile (
           FileHandle,
           Order,
           SectionName,
           INVALID_COMPRESSED_FILE_NAME_ITEM,
           FileName
           );
}

/**
 *  get the String from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param ItemName the Item to be gotten.
 *  @param String the returned string.
 *  @return EFI_SUCCESS the string was gotten successfully.
 */
EFI_STATUS
GetStringItemFromFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN UINTN                Order,
  IN CHAR16               *SectionName,
  IN CHAR16               *ItemName,
  OUT CHAR16              **String
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;
  CHAR16          *TempStr;

  if (SectionName == NULL || ItemName == NULL || String == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         ItemName,
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  TempStr = NULL;
  TempStr = SctStrDuplicate (Buffer);
  if (TempStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  *String = TempStr;

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
