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

  DeviceIoBBTestSupport.h

Abstract:

  BB test support head file of Device Io Interface.

--*/

#ifndef _DEVICE_IO_BBTEST_SUPPORT_H
#define _DEVICE_IO_BBTEST_SUPPORT_H

typedef CHAR16 WIDTHCODE[64];

typedef struct _MEMORY_POOL_MAPPING_LIST {
 struct _MEMORY_POOL_MAPPING_LIST   *Next;
  EFI_PHYSICAL_ADDRESS              HostAddress;
  VOID                              *Mapping;
} MEMORY_POOL_MAPPING_LIST;


typedef struct {
  EFI_DEVICE_IO_PROTOCOL    *DeviceIo;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
} DEVIO_DEVICE;

//
//global variables.
//
#define MAX_STRING_LEN                 256

#define DEPENDECY_DIR_NAME             L"dependency\\DeviceIoBBTest"
#define DEVICE_IO_TEST_INI_FILE        L"DeviceIoBBTest.ini"

extern EFI_DEVICE_PATH_PROTOCOL        *gDevicePath;
extern CHAR16                          *gFilePath;
extern DEVIO_DEVICE                    *gDevIoDevices;
extern UINTN                           gDevIoDevNumber;
extern WIDTHCODE                       WidthCode[];

//
//suppot function protypes.
//

EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  );

EFI_STATUS
InitializeSupportEnvironment (
  VOID
  );

EFI_STATUS
CreateAllDevIoDevices (
  VOID
  );

EFI_STATUS
GetDevIoDevicePathStr (
  IN  EFI_DEVICE_IO_PROTOCOL  *DevIo,
  IN  CHAR16                  **DevPathStr OPTIONAL
  );

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
  OUT  EFI_INI_FILE_HANDLE                FileHandle
  );

EFI_STATUS
GetSystemDevicePathStrByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **DevicePathStr
  );

EFI_STATUS
GetValidBaseAddressByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *Address
  );

EFI_STATUS
GetInvalidBaseAddressByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *Address
  );

EFI_STATUS
GetAddressLengthByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT32              *AddressLength
  );

EFI_STATUS
GetValidEfiIoWidthByFile (
  IN EFI_INI_FILE_HANDLE          FileHandle,
  IN CHAR16                       *SectionName,
  IN UINTN                        Order,
  OUT EFI_IO_WIDTH                *EfiIoWidth
  );

EFI_STATUS
GetInvalidEfiIoWidthByFile (
  IN EFI_INI_FILE_HANDLE          FileHandle,
  IN CHAR16                       *SectionName,
  IN UINTN                        Order,
  OUT EFI_IO_WIDTH                *EfiIoWidth
  );

EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
GetDataUnitsByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  UINTN                   Length,
  OUT UINT8               **DataUnits
  );

EFI_STATUS
ConvertStringToHex (
  IN CHAR16             *SrcBuffer,
  IN UINT32             Length,
  OUT UINT8             **RetBuffer
  );

UINT64
XToUint64 (
  IN CHAR16  *str
  );

#endif
