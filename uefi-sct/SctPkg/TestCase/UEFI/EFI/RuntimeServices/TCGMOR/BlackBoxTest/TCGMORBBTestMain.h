/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2023, Arm Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  TCGMORTest.h

Abstract:

  Test Driver of TCG MOR EFI variables from TCG spec

--*/

#ifndef _TCG_MOR_BB_TEST_MAIN
#define _TCG_MOR_BB_TEST_MAIN

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <SctLib.h>

typedef struct _RESET_DATA {
  UINTN           Step;
  UINTN           TplIndex;
  UINT32          RepeatTimes;
} RESET_DATA;

#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)

#define TCG_MOR_TEST_REVISION 0x00010000

#define EFI_TCG_MOR_TEST_GUID \
  { 0x265e661d, 0xd51e, 0x454b, {0xbb, 0xc9, 0x66, 0x5f, 0x46, 0xec, 0x0a, 0x04 }}

#define MEMORY_ONLY_RESET_CONTROL_GUID \
  { 0xE20939BE, 0x32D4, 0x41BE, {0xA1, 0x50, 0x89, 0x7F, 0x85, 0xD4, 0x98, 0x29 }}

#define MEMORY_OVERWRITE_REQUEST_CONTROL_LOCK_GUID \
  { 0xBB983CCF, 0x151D, 0x40E1, {0xA0, 0x7B, 0x4A, 0x17, 0xBE, 0x16, 0x82, 0x92 }}

extern EFI_GUID gEfiMemoryOverwriteControlDataGuid;

extern EFI_GUID gEfiMemoryOverwriteRequestControlLockGuid;

EFI_STATUS
EFIAPI
InitializeTestTCGMOR (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadTCGMORTest (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
BBTestTCGMORFunctionTest (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

EFI_STATUS
TCGMORPlatformResetCheck (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib
  );

EFI_STATUS
TCGMORSetVariable (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib
  );

// ****************************************************************************
//   Entry GUIDs for Test
// ****************************************************************************

#define EFI_TCG_MOR_TEST_ENTRY_GUID0101 \
  { 0x2104436a, 0x77c8, 0x4514, {0xb7, 0xd7, 0xaa, 0x8a, 0x6b, 0xd1, 0x8d, 0xa4 }}

#endif
