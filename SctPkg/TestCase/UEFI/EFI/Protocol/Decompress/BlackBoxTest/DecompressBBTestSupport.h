/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DecompressBBTestSupport.h

Abstract:

  BB test support header file for Decompress protocol

--*/

#ifndef _DECOMPRESS_BBTEST_SUPPORT_H
#define _DECOMPRESS_BBTEST_SUPPORT_H

//
//global variables
//

#define MAX_STRING_LEN                 256

#define DEPENDECY_DIR_NAME             L"dependency\\DecompressBBTest"
#define DECOMPRESS_TEST_INI_FILE       L"DecompressBBTest.ini"

extern EFI_DEVICE_PATH_PROTOCOL        *gDevicePath;
extern CHAR16                          *gFilePath;
extern EFI_HANDLE                      gDeviceHandle;

//
//support function protype
//

EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_PROFILE_LIBRARY_PROTOCOL  **ProfileLib
  );

EFI_STATUS
OpenTestIniFile (
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                *FileHandle
  );

EFI_STATUS
CloseTestIniFile (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  IN  EFI_INI_FILE_HANDLE                 FileHandle
  );

EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  );

EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
GetUncompressedFileSize (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT32              *FileSize
  );

EFI_STATUS
GetCompressedFileName (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **FileName
  );

EFI_STATUS
GetUncompressedFileName (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **FileName
  );

EFI_STATUS
GetInvalidCompressedFileName (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **FileName
  );

EFI_STATUS
GetStringItemFromFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN UINTN                Order,
  IN CHAR16               *SectionName,
  IN CHAR16               *ItemName,
  OUT CHAR16              **String
  );

EFI_STATUS
OpenFileAndGetSize (
  IN  CHAR16          *FileName,
  OUT EFI_FILE_HANDLE *FileHandle,
  OUT UINT32          *FileSize
  );

 #endif
