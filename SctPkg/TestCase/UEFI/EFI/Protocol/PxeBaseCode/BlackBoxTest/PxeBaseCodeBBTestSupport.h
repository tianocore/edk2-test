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

  CpuIoBBTestSupport.h

Abstract:

  BB test support head file of Cpu Io Interface.

--*/

#ifndef _PXE_BASE_CODE_BBTEST_SUPPORT_H
#define _PXE_BASE_CODE_BBTEST_SUPPORT_H

#define MAX_STRING_LEN                256
#define DEPENDECY_DIR_NAME            L"dependency\\PxeBaseCodeBBTest"
#define PXE_BC_TEST_INI_FILE          L"PxeBaseCodeBBTest.ini"

extern EFI_DEVICE_PATH_PROTOCOL        *gDevicePath;
extern CHAR16                          *gFilePath;

#define STR_TO_UINT8(Buffer) \
        1 ? \
        (UINT8)(SctXtoi (Buffer)) : (UINT8)(SctAtoi (Buffer))

#define STR_TO_INT(Buffer) \
        (Buffer[0] == '0' && ((Buffer[1] == 'x') || (Buffer[1] == 'X'))) ? \
        (UINT32)SctXtoi (Buffer) : (UINT32)SctAtoi (Buffer)

//
//suppot function protypes.
//

EFI_STATUS
GetTestSupportLibrary (
  IN  EFI_HANDLE                            SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL    **StandardLib,
  OUT EFI_TEST_PROFILE_LIBRARY_PROTOCOL     **ProfileLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL     **LoggingLib
  );

EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
OpenTestIniFile (
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                *FileHandle
  );

EFI_STATUS
CloseTestIniFile (
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                FileHandle
  );

EFI_STATUS
GetIpAddrFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT EFI_IP_ADDRESS        *Ip
  );

EFI_STATUS
GetBooleanVarFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT BOOLEAN               *Val
  );

EFI_STATUS
GetUINTNVarFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT UINTN*                Val
  );

EFI_STATUS
GetUINT32VarFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT UINT32                *Val
  );

EFI_STATUS
GetUINT16ValFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT UINT16                *Val
  );

EFI_STATUS
GetUdpPortFromFile (
  IN  EFI_INI_FILE_HANDLE           FileHandle,
  IN  CHAR16                        *SectionName,
  IN  CHAR16                        *ItemName,
  IN  UINT32                        Order,
  OUT EFI_PXE_BASE_CODE_UDP_PORT*   Val
  );

EFI_STATUS
GetUnicodeStringFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT CHAR16                **String
  );

EFI_STATUS
GetAsciiStringFromFile(
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT CHAR8                 **String
  );

EFI_STATUS
GetRawDataFromFile (
  IN     EFI_INI_FILE_HANDLE  FileHandle,
  IN     CHAR16               *SectionName,
  IN     CHAR16               *ItemName,
  IN     UINT32               Order,
  IN OUT UINTN                *BufferSize,
  IN OUT VOID                 *BufferPtr
);

EFI_STATUS
ReadMtftpFile (
  IN OUT VOID   **Buffer,
  IN OUT UINTN  *Size
  );

#endif
