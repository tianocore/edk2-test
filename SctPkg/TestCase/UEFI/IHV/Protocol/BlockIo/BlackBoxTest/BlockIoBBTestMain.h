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

  BlockIoBBTestMain.h

Abstract:

  BB test header file of Block I/O Protocol

--*/


#ifndef _BLOCK_IO_BBTEST_H_
#define _BLOCK_IO_BBTEST_H_

//
// Includes
//

#include "Efi.h"
#include <UEFI/Protocol/BlockIo.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>
//
// Definitions
//

#define BLOCK_IO_PROTOCOL_TEST_REVISION     0x00010000

#define IHV_BLOCK_IO_PROTOCOL_GUID          \
  { 0x67c2de14, 0x9b48, 0x496c, { 0x9e, 0x1b, 0xf7, 0xd5, 0x9, 0xfb, 0xce, 0xa2 } }

#define MAX_NUMBER_OF_READ_BLOCK_BUFFER     20
#define MAX_DIFFERENT_BUFFERSIZE_FOR_TEST   4
#define MAX_DIFFERENT_LBA_FOR_TEST          4
#define MAX_DIFFERENT_IOALIGN_FOR_TEST      4
#define MAX_REPEAT_OF_STRESS_TEST           20

#define MAXIMUM(a,b)                        ((a)>(b)?(a):(b))
#define MINIMUM(a,b)                        ((a)<(b)?(a):(b))

//
// Entry GUIDs
//

//
// Conformance
//
#define BLOCK_IO_PROTOCOL_READBLOCKS_CONFORMANCE_AUTO_GUID \
  { 0xce936d6c, 0x58e6, 0x485d, { 0x81, 0x9b, 0xc3, 0x5d, 0x29, 0x93, 0x63, 0xd6 } }

#define BLOCK_IO_PROTOCOL_READBLOCKS_CONFORMANCE_MANUAL_GUID \
{ 0xa1166508, 0xd0b1, 0x4fdb, { 0x92, 0xa2, 0xe4, 0xe4, 0xaa, 0xea, 0x64, 0x36 } }

#define BLOCK_IO_PROTOCOL_WRITEBLOCKS_CONFORMANCE_AUTO_GUID \
  { 0xae014be9, 0xcaea, 0x4855, { 0xbc, 0x2c, 0x7e, 0x46, 0xf6, 0x4f, 0xc1, 0xd } }

#define BLOCK_IO_PROTOCOL_WRITEBLOCKS_CONFORMANCE_MANUAL_GUID \
  { 0xc770e5d3, 0xba7d, 0x449e, { 0x80, 0xef, 0x80, 0x79, 0xcf, 0x50, 0x79, 0x35 } }

#define BLOCK_IO_PROTOCOL_FLUSHBLOCKS_CONFORMANCE_AUTO_GUID \
  { 0xd07accee, 0x2fa8, 0x4391, { 0xa9, 0xa0, 0x5d, 0x29, 0xaa, 0xea, 0x29, 0x82 } }

#define BLOCK_IO_PROTOCOL_FLUSHBLOCKS_CONFORMANCE_MANUAL_GUID \
  { 0x21dc25a4, 0x9db, 0x44b1, { 0x80, 0xf8, 0x7b, 0x34, 0x35, 0x2c, 0x1d, 0xf8 } }

//
// Function
//
#define BLOCK_IO_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0x9579d2bd, 0x891d, 0x46fb, { 0x8e, 0xcc, 0xe1, 0x30, 0xd0, 0x49, 0x15, 0x97 } }

#define BLOCK_IO_PROTOCOL_READBLOCKS_FUNCTION_AUTO_GUID \
  { 0xec5294ec, 0xd411, 0x4ca8, { 0xa7, 0xb1, 0x7c, 0xc7, 0xba, 0x16, 0xf4, 0x93 } }

#define BLOCK_IO_PROTOCOL_WRITEBLOCKS_FUNCTION_AUTO_GUID \
  { 0x519f8f9f, 0x2fde, 0x4f79, { 0xa9, 0xa4, 0x5, 0x88, 0xbc, 0xf4, 0xcf, 0x56 } }

#define BLOCK_IO_PROTOCOL_MEDIA_INTEGRITY_MANUAL_GUID \
  { 0x34f138ce, 0x75c4, 0x4378, { 0x91, 0xb8, 0xd1, 0xb5, 0xc9, 0x20, 0x84, 0xdf } }

#define BLOCK_IO_PROTOCOL_FLUSHBLOCKS_FUNCTION_AUTO_GUID \
  { 0x62bba850, 0x9d9c, 0x4927, { 0x90, 0xdb, 0xaf, 0x48, 0x58, 0xdc, 0xce, 0x48 } }

#define BLOCK_IO_PROTOCOL_MEDIAINFO_INTEGRITY_AUTO_GUID \
  { 0x621f2a78, 0x6a6c, 0x44e7, { 0xb2, 0x1c, 0x45, 0x50, 0xcd, 0x77, 0x7c, 0x66 } }

//
// Combination
//
#define BLOCK_IO_PROTOCOL_RESET_STRESS_AUTO_GUID \
  { 0xfc00f351, 0x339f, 0x4345, { 0xa8, 0x69, 0x16, 0x90, 0x8d, 0xc3, 0x76, 0x8b } }

#define BLOCK_IO_PROTOCOL_READBLOCKS_STRESS_AUTO_GUID \
  { 0xd576354d, 0x139e, 0x4d8a, { 0x9d, 0x12, 0xf4, 0x33, 0x81, 0x73, 0xc9, 0xbd } }

#define BLOCK_IO_PROTOCOL_WRITEBLOCKS_STRESS_AUTO_GUID \
  { 0xc0cf2cc3, 0x384b, 0x434e, { 0x88, 0x4d, 0xab, 0x36, 0x93, 0x1d, 0x6e, 0x36 } }

//
// Global variables
//

extern   EFI_EVENT                         TimerEvent;

//
// Prototypes
//

EFI_STATUS
EFIAPI
InitializeBBTestBlockIo (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestBlockIoProtocolUnload (
  IN EFI_HANDLE                 ImageHandle
  );

//
// Conformance test case prototypes
//

EFI_STATUS
BBTestReadBlocksConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestReadBlocksConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteBlocksConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteBlocksConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFlushBlocksConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestFlushBlocksConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Function test case prototypes
//

EFI_STATUS
BBTestResetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestReadBlocksFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteBlocksFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFlushBlocksFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestMediaInfoCheckAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestMediaIntegrityManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Stress test case prototypes
//

EFI_STATUS
BBTestResetStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestReadBlocksStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteBlocksStressAutoTest (
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
LocateDevicePathFromBlockIo(
  IN EFI_BLOCK_IO_PROTOCOL                *BlockIo,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
LocateBlockIoFromDevicePath(
  IN EFI_BLOCK_IO_PROTOCOL                **BlockIo,
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

