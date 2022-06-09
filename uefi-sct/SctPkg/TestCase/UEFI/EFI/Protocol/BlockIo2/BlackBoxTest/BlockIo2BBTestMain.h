/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2011 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  BlockIo2BBTestMain.h

Abstract:

  BB test header file of Block I/O 2 Protocol

--*/


#ifndef _BLOCK_IO2_BBTEST_H_
#define _BLOCK_IO2_BBTEST_H_

//
// Includes
//

#include "SctLib.h"
#include "Guid.h"
#include <UEFI/Protocol/BlockIo2.h>
#include <Library/EfiTestLib.h>

//
// Definitions
//

#define BLOCK_IO2_PROTOCOL_TEST_REVISION    0x00010000

#define MAX_NUMBER_OF_READ_BLOCK_BUFFER     20
#define MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER     0x20000
#define MAX_NUMBER_OF_WRITE_BLOCK_FUNC_BUFFER    0x10

#define MAX_DIFFERENT_BUFFERSIZE_FOR_TEST   4
#define MAX_DIFFERENT_LBA_FOR_TEST          4
#define MAX_DIFFERENT_IOALIGN_FOR_TEST      4
#define MAX_REPEAT_OF_STRESS_TEST           20

#define STALL_10_SECONDS    10000000 // in microsecond unit

#define MAXIMUM(a,b)                        ((a)>(b)?(a):(b))
#define MINIMUM(a,b)                        ((a)<(b)?(a):(b))

//
// Entry GUIDs
//

//
// Conformance
//
#define BLOCK_IO2_PROTOCOL_READBLOCKSEX_CONFORMANCE_AUTO_GUID \
  { 0xb2547a54, 0x452, 0x4d45, { 0xb3, 0xc6, 0x3, 0x9a, 0xc7, 0xe4, 0x64, 0x3 } }

#define BLOCK_IO2_PROTOCOL_WRITEBLOCKSEX_CONFORMANCE_AUTO_GUID \
  { 0xadab6fcb, 0xeda8, 0x49cf, { 0xb2, 0x73, 0xfa, 0xbc, 0x75, 0x74, 0xaa, 0xf2 } }

#define BLOCK_IO2_PROTOCOL_FLUSHBLOCKSEX_CONFORMANCE_AUTO_GUID \
  { 0xa0ae19bd, 0x6877, 0x48bf, { 0xab, 0x2, 0xb0, 0xa7, 0x7d, 0x4d, 0xd0, 0xaa } }

#define BLOCK_IO2_PROTOCOL_FLUSHBLOCKSEX_CONFORMANCE_MANUAL_GUID \
  { 0x2da7b457, 0x40ca, 0x43d4, { 0x8f, 0x5d, 0x94, 0x35, 0x6e, 0x79, 0xf4, 0xe1 } }

//
// Function
//
#define BLOCK_IO2_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0xc2ea0255, 0x46da, 0x47db, { 0x94, 0x18, 0xaa, 0x83, 0xa5, 0xef, 0x96, 0x52 } }

#define BLOCK_IO2_PROTOCOL_READBLOCKSEX_FUNCTION_AUTO_GUID \
  { 0x825f3c68, 0x2ddd, 0x4459, { 0xa8, 0xd9, 0x17, 0xb4, 0xbb, 0xb5, 0xe4, 0xe5 } }

#define BLOCK_IO2_PROTOCOL_WRITEBLOCKSEX_FUNCTION_AUTO_GUID \
  { 0xa05b06c8, 0xd388, 0x42dc, { 0xa3, 0x79, 0x8b, 0xfe, 0xf, 0x40, 0xa4, 0x18 } }

#define BLOCK_IO2_PROTOCOL_FLUSHBLOCKSEX_FUNCTION_AUTO_GUID \
  { 0xdc0720ff, 0xa4ae, 0x4051, { 0xb5, 0x64, 0x2a, 0x85, 0x5d, 0xc4, 0x9b, 0x5e } }

#define BLOCK_IO2_PROTOCOL_MEDIAINFO_INTEGRITY_AUTO_GUID \
  { 0xbd03c32b, 0xb8b1, 0x4ff2, { 0xb9, 0xe1, 0x0e, 0xf5, 0x44, 0x05, 0x56, 0x03 } }

//
// Global variables
//
extern EFI_EVENT TimerEvent;


//
// Prototypes
//

EFI_STATUS
EFIAPI
InitializeBBTestBlockIo2 (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestBlockIo2ProtocolUnload (
  IN EFI_HANDLE                 ImageHandle
  );

//
// Conformance test case prototypes
//

EFI_STATUS
EFIAPI
BBTestReadBlocksExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestReadBlocksExConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestWriteBlocksExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestFlushBlocksExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Function test case prototypes
//

EFI_STATUS
EFIAPI
BBTestResetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestReadBlocksExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestWriteBlocksExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestFlushBlocksExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestMediaInfoCheckAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Internal support function prototypes
//

UINTN
VerifyBuffer(
  IN UINT8                      *Buffer1,
  IN UINT8                      *Buffer2,
  IN UINTN                      BufferSize
  );

BOOLEAN
AutoJudge(
  IN  UINTN                     Seconds,
  IN  BOOLEAN                   Default,
  IN  CHAR16                    *Message
  );

EFI_STATUS
LocateDevicePathFromBlockIo2(
  IN EFI_BLOCK_IO2_PROTOCOL               *BlockIo2,
  IN OUT EFI_DEVICE_PATH_PROTOCOL         **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
LocateBlockIo2FromDevicePath(
  IN OUT EFI_BLOCK_IO2_PROTOCOL            **BlockIo2,
  IN EFI_DEVICE_PATH_PROTOCOL             *DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
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

