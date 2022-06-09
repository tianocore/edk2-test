/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    ComponentName2BBTestMain.h

Abstract:
    head file of test driver of EFI Component Name2 Protocol Test

--*/

#ifndef _COMPONENT_NAME2_TEST_MAIN_H
#define _COMPONENT_NAME2_TEST_MAIN_H


#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/ComponentName2.h>
#include "Guid.h"

#define EFI_COMPONENT_NAME2_TEST_REVISION 0x00010000

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Func Test
//
#define EFI_COMPONENT_NAME2_PROTOCOL_TEST_ENTRY_GUID0101 \
 { 0xe7d8507f, 0xe83e, 0x45f6, {0xa4, 0xd3, 0x32, 0x39, 0x5c, 0x5a, 0x61, 0xcc }}

#define EFI_COMPONENT_NAME2_PROTOCOL_TEST_ENTRY_GUID0102 \
 { 0xa87f00ba, 0x6036, 0x49d2, {0x8d, 0xff, 0x3f, 0xa0, 0x46, 0x2a, 0xa, 0xbb }}


//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define EFI_COMPONENT_NAME2_PROTOCOL_TEST_ENTRY_GUID0201 \
 { 0xefb518a, 0x5dfa, 0x448c, {0x92, 0x6e, 0xa1, 0xd4, 0x51, 0xe7, 0x58, 0xe2 }}

#define EFI_COMPONENT_NAME2_PROTOCOL_TEST_ENTRY_GUID0202 \
 { 0xd7f63771, 0x3820, 0x4b9e, {0x9c, 0xc3, 0xa1, 0xbd, 0x9a, 0xe6, 0x3a, 0x56 }}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

//
// TestNoInterfaceProtocol1
//
#define TEST_NO_INTERFACE_PROTOCOL_1_GUID \
  { 0x7362363, 0x3617, 0x4d92, {0xa1, 0xb1, 0x1d, 0x62, 0xa5, 0x78, 0x91, 0xa5 }}

extern EFI_GUID mTestNoInterfaceProtocol1Guid;

//
// TestNoInterfaceProtocol2
//
#define TEST_NO_INTERFACE_PROTOCOL_2_GUID \
  { 0x3fd2484, 0xa340, 0x41a7, {0xba, 0x13, 0xb4, 0x93, 0xb0, 0x67, 0xdb, 0x4c }}

extern EFI_GUID mTestNoInterfaceProtocol2Guid;


//
// functions declaration
//

EFI_STATUS
EFIAPI
InitializeBBTestComponentName2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestComponentName2Unload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDriverNameFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetControllerNameFuncTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDriverNameFuncTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  );

EFI_STATUS
EFIAPI
BBTestGetControllerNameFuncTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  );

EFI_STATUS
EFIAPI
BBTestGetControllerNameFuncTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  );

EFI_STATUS
EFIAPI
BBTestGetDriverNameConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDriverNameConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  );

EFI_STATUS
EFIAPI
BBTestGetDriverNameConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  );

EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  );

EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  );

EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  );
/*
EFI_STATUS
EFIAPI
BBTestGetControllerNameConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME2_PROTOCOL           *ComponentName
  );
*/

EFI_STATUS
LocateLoadedImageDevicePathFromComponentName2 (
  IN EFI_COMPONENT_NAME2_PROTOCOL             *ComponentName2,
  IN EFI_DEVICE_PATH_PROTOCOL                 **DevicePath,      //reuse the EFI_DEVICE_PATH_PROTOCOL as EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib
  );

#endif

