/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ImageTest.h

Abstract:

  head file for Loaded Image Protocol Black Box Test

--*/

#ifndef _LOADED_IMAGE_BBTEST_H
#define _LOADED_IMAGE_BBTEST_H

#include <Base.h>
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include "LoadedImageBBTestProtocolDefinition.h"
#include "Guid.h"

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

#define LOADED_IMAGE_PROTOCOL_TEST_REVISION 0x00010000
//
// directory and file name definition
//
#define DEPENDENCY_DIR_NAME                 L"Dependency\\LoadedImageBBTest"

#define EFI_APPLICATION_1_NAME              L"LoadedImageApplication1.efi"
#define EFI_APPLICATION_2_NAME              L"LoadedImageApplication2.efi"

#define BOOT_SERVICES_DRIVER_1_NAME         L"LoadedImageBootServicesDriver1.efi"
#define BOOT_SERVICES_DRIVER_2_NAME         L"LoadedImageBootServicesDriver2.efi"

#define RUNTIME_SERVICES_DRIVER_1_NAME      L"LoadedImageRuntimeServicesDriver1.efi"
#define RUNTIME_SERVICES_DRIVER_2_NAME      L"LoadedImageRuntimeServicesDriver2.efi"

extern EFI_HANDLE   mImageHandle;

#define MAX_STRING_LEN      250

typedef struct {
  UINTN     ProtocolIndex;
  VOID      *Registration[6];
} NOTIFY_CONTEXT;

//////////////////////////////////////////////////////////////////////////////
//
// Test Entry GUIDs
//
#define LOADED_IMAGE_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0xdebe1157, 0x53d2, 0x42a1, {0xb6, 0xde, 0xe0, 0xd4, 0x6c, 0x9a, 0xce, 0xd7} }

#define LOADED_IMAGE_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0x524114f0, 0xfb32, 0x494b, { 0x81, 0x4d, 0x95, 0x97, 0x5, 0x9e, 0xe5, 0xc5} }

//
// Functions definitions
//
EFI_STATUS
EFIAPI
InitializeBBTestLoadedImageProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestLoadedImageProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


//
// TDS 3.1
//
EFI_STATUS
EFIAPI
BBTestLoadedImageTest1 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
EFIAPI
BBTestLoadedImageTest2 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
LoadedImageTestComposeSimpleFilePath (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib    OPTIONAL,
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT EFI_DEVICE_PATH_PROTOCOL            **FilePath
  );

VOID
TestNotifyFunction (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  );
#endif
