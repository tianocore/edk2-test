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

  SecureBootBBTestSupport.h

Abstract:

  BB test support header file for Secure Boot

--*/

#ifndef _SECUREBOOT_BBTEST_SUPPORT_H
#define _SECUREBOOT_BBTEST_SUPPORT_H

#include "SctLib.h"

//
// global variables
//

#define MAX_STRING_LEN                 256

#define DEPENDECY_DIR_NAME             L"Dependency\\SecureBootBBTest"

extern EFI_DEVICE_PATH_PROTOCOL        *gDevicePath;
extern CHAR16                          *gFilePath;
extern EFI_HANDLE                      gDeviceHandle;
extern EFI_HANDLE                      mImageHandle;

//
// support function protype
//

EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  );

EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
OpenFileAndGetSize (
  IN  CHAR16          *FileName,
  OUT EFI_FILE_HANDLE *FileHandle,
  OUT UINT32          *FileSize
  );

EFI_STATUS
GetBaseName (
  IN  CHAR16          *FileName,
  OUT CHAR16          **BaseName
  );

EFI_STATUS
SecureBootVariableCleanup (
  IN EFI_RUNTIME_SERVICES                 *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL    *LoggingLib,
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib
  );

#endif
