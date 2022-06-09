/** @file

  Copyright 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EraseBlockBBTestMain.h

Abstract:

  Test Driver of Erase Block Protocol header file

--*/

#ifndef _ERASE_BLOCK_BB_TEST_MAIN
#define _ERASE_BLOCK_BB_TEST_MAIN

#include <Efi.h>
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/EraseBlock.h>
#include <UEFI/Protocol/BlockIo.h>
#include <UEFI/Protocol/BlockIo2.h>
#include "Guid.h"


#define EFI_ERASE_BLOCK_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_ERASE_BLOCK_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x2e54c9ba, 0xf0e0, 0x4cef, { 0x8c, 0xe6, 0x18, 0x15, 0x79, 0xfe, 0x5f, 0xc }}

//
// Entry GUIDs for Conf Test
//
#define EFI_ERASE_BLOCK_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xd0a834d6, 0xad31, 0x43d2, { 0xa7, 0x6a, 0x9f, 0x1a, 0xd6, 0x9e, 0x6f, 0x15 }}


#define MINIMUM(a,b)                        ((a)<(b)?(a):(b))
#define MAX_NUMBER_OF_READ_BLOCK_BUFFER     20

//
//
//
EFI_STATUS
EFIAPI
InitializeEraseBlockBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadEraseBlockBBTest (
  IN EFI_HANDLE                   ImageHandle
  ); 
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestEraseBlocksConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

  
EFI_STATUS
EFIAPI
BBTestEraseBlocksFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
LocateBlockIoFromEraseBlock (
  IN EFI_ERASE_BLOCK_PROTOCOL              *EraseBlock,
  IN OUT EFI_BLOCK_IO_PROTOCOL             **BlockIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib
  );

EFI_STATUS
LocateBlockIo2FromEraseBlock (
  IN EFI_ERASE_BLOCK_PROTOCOL              *EraseBlock,
  IN OUT EFI_BLOCK_IO2_PROTOCOL            **BlockIo2,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib
  );

VOID
NotifyFunction (
  EFI_EVENT    Event,
  VOID         *Context
  );

VOID *
AllocateAlignedPool (
  IN EFI_MEMORY_TYPE  PoolType,
  IN UINTN            AllocationSize,
  IN UINTN            Alignment
  );

EFI_STATUS
FreeAlignedPool (
  IN VOID   *Buffer
  );

#endif

