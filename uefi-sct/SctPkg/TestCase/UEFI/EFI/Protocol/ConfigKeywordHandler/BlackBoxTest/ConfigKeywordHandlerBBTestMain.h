/** @file

  Copyright 2016 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Hash2BBTestMain.h

Abstract:

  Test Driver of Config Keyword Handler Protocol header file

--*/

#ifndef _CONFIG_KEYWORD_HANDLER_BB_TEST_MAIN
#define _CONFIG_KEYWORD_HANDLER_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/ConfigKeywordHandler.h>
#include "Guid.h"
#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_REVISION    0x00010000


#define DEPENDENCY_DIR_NAME                 L"Dependency\\ConfigKeywordHandlerBBTest"

#define DRIVER_SAMPLE_NAME                  L"DriverSample.efi"

extern EFI_GUID gBlackBoxEfiLoadedImageProtocolGuid;

//
// Entry GUIDs for Func Test
//
#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x3d2238a7, 0xc736, 0x436b, {0xbd, 0xff, 0xb2, 0x36, 0x1c, 0xfd, 0x21, 0x17 }}

#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x631624c4, 0x62bd, 0x4fdf, {0xae, 0x7e, 0x74, 0x30, 0x41, 0x5e, 0xc6, 0x6c }}


//
// Entry GUIDs for Conf Test
//
#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xa180b9b0, 0xcea8, 0x472f, {0x8e, 0x31, 0xc7, 0x89, 0x6c, 0x79, 0xb5, 0x1 }}

#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x3269d631, 0x42a0, 0x464e, {0xbd, 0x5d, 0xcc, 0x3c, 0xc8, 0xd, 0x8e, 0x3a }}


//
//
//
EFI_STATUS
EFIAPI
InitializeConfigKeywordHandlerBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadConfigKeywordHandlerBBTest (
  IN EFI_HANDLE                   ImageHandle
  );

EFI_STATUS
LoadedImageTestComposeSimpleFilePath (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib    OPTIONAL,
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT EFI_DEVICE_PATH_PROTOCOL            **FilePath
  );
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestSetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestSetDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#endif

