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

  LoadFileBBTestMain.h

Abstract:

  Test Driver of LoadFile Protocol

--*/

#ifndef __EFI_LOAD_FILE_TEST_H__
#define __EFI_LOAD_FILE_TEST_H__


#include "Efi.h"
#include "Guid.h"

#include EFI_PROTOCOL_DEFINITION (LoadFile)

#include <Library/EfiTestLib.h>

#define LOAD_FILE_TEST_REVISION 0x00010000

#define LOAD_FILE_FUNCTION_TEST_GUID \
  { 0x31248834, 0xca1b, 0x4004, {0xab, 0x7e, 0x39, 0xea, 0x5f, 0x2, 0x46, 0xe7 }}

EFI_STATUS
EFIAPI
InitializeLoadFileTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadLoadFileTest (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
EFIAPI
BBTestLoadFileFunctionTest (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

VOID
LoadFileTestWaitForAnyInput (
  );

#define SAMPLE_BOOT_FILE_SIZE 27
#endif
