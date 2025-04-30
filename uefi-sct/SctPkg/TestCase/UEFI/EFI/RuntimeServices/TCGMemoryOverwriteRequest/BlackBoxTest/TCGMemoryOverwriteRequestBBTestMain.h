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

  TCGMemoryOverwriteRequestTest.h

Abstract:

  Test Driver of TCG MOR and MORLOCK EFI variables that are defined inside
  TCG Platform Reset Attack Mitigation v1.10 Section 4 (UEFI Interface)

--*/

#ifndef _TCG_MOR_BB_TEST_MAIN
#define _TCG_MOR_BB_TEST_MAIN

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <Guid/MemoryOverwriteControl.h>
#include <IndustryStandard/MemoryOverwriteRequestControlLock.h>
#include <SctLib.h>

typedef struct _RESET_DATA {
  UINTN           Step;
  UINTN           CheckpointStep;
} RESET_DATA;

#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)

#define TCG_MOR_TEST_REVISION             0x00010000

#define MOR_BIT_LOW                       0x0
#define MOR_BIT_HIGH                      0x1

#define MOR_LOCK_DATA_UNLOCKED            0x0
#define MOR_LOCK_DATA_LOCKED_WITHOUT_KEY  0x1
#define MOR_LOCK_DATA_LOCKED_WITH_KEY     0x2

#define MOR_LOCK_NO_KEY_SIZE              1
#define MOR_LOCK_WITH_KEY_SIZE            8

#define MOR_LOCK_TEST_KEY                 0x11111111
#define MOR_LOCK_INVALID_TEST_KEY         0x22222222

//
// TEST GUID for TCG Platform Reset Attack Mitigation MemoryOverwriteRequest (MOR) Test
//
#define EFI_TCG_MOR_TEST_GUID \
  { 0x265e661d, 0xd51e, 0x454b, {0xbb, 0xc9, 0x66, 0x5f, 0x46, 0xec, 0x0a, 0x04 }}

EFI_STATUS
EFIAPI
InitializeTestTCGMemoryOverwriteRequest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadTCGMemoryOverwriteRequestTest (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
EFIAPI
BBTestTCGMemoryOverwriteRequestFunctionTest (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  );

EFI_STATUS
TCGMemoryOverwriteRequestPlatformResetCheck (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  );

EFI_STATUS
TCGMemoryOverwriteRequestControlSetVariable (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  );

EFI_STATUS
TCGMemoryOverwriteRequestControlLockSetVariable (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  );

EFI_STATUS
TCGMemoryOverwriteRequestControlLockUnlockedState (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
);

EFI_STATUS
TCGMemoryOverwriteRequestControlLockLockedNoKeyState (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  );

EFI_STATUS
TCGMemoryOverwriteRequestControlLockLockedWithKeyState (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL       *RecoveryLib,
  IN RESET_DATA                               *ResetData
  );

// ****************************************************************************
//   Entry GUIDs for Test
// ****************************************************************************

#define EFI_TCG_MOR_TEST_ENTRY_GUID0101 \
  { 0x2104436a, 0x77c8, 0x4514, {0xb7, 0xd7, 0xaa, 0x8a, 0x6b, 0xd1, 0x8d, 0xa4 }}

#endif
