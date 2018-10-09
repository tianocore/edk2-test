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

  DiskIoBBTestMain.h

Abstract:

  BB test header file of Disk I/O Protocol

--*/


#ifndef _DISK_IO_BBTEST_H_
#define _DISK_IO_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/BlockIo.h>
#include <UEFI/Protocol/DiskIo.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  DISK_IO_PROTOCOL_TEST_REVISION    0x00010000

#define  IHV_DISK_IO_PROTOCOL_GUID         \
  { 0xa56caa44, 0x2c75, 0x4a9a, { 0x9c, 0x88, 0x75, 0xbb, 0x9b, 0xa0, 0xf4, 0xd4 } }

#define  MAX_NUMBER_OF_READ_DISK_BUFFER    65536
#define  MAX_DIFFERENT_BUFFERSIZE_FOR_TEST 4
#define  MAX_DIFFERENT_LBA_FOR_TEST        4
#define  MAX_DIFFERENT_IOALIGN_FOR_TEST    4
#define  MAX_REPEAT_OF_STRESS_TEST         20

extern   EFI_EVENT                         TimerEvent;

EFI_STATUS
EFIAPI
InitializeBBTestDiskIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDiskIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
BBTestReadDiskConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestWriteDiskConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestReadDiskFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteDiskFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Combination test declaration section
//

EFI_STATUS
BBTestReadDiskStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteDiskStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Other function declaration section
//
UINTN
VerifyBuffer(
  IN UINT8           *Buffer1,
  IN UINT8           *Buffer2,
  IN UINTN           BufferSize
  );

BOOLEAN
AutoJudge(
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

EFI_STATUS
LocateBlockIoFromDiskIo(
  IN EFI_DISK_IO_PROTOCOL                 *DiskIo,
  IN EFI_BLOCK_IO_PROTOCOL                **BlockIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
LocateDevicePathFromDiskIo(
  IN EFI_DISK_IO_PROTOCOL                 *DiskIo,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Entry GUIDs
//

//
// Comformance
//

#define DISK_IO_PROTOCOL_READDISK_CONFORMANCE_AUTO_GUID \
  { 0xe7605bdf, 0x44a3, 0x40ad, { 0x81, 0xfe, 0xb7, 0x82, 0x10, 0xed, 0x8d, 0xe5 } }

#define DISK_IO_PROTOCOL_WRITEDISK_CONFORMANCE_AUTO_GUID \
  { 0xe6c2aafd, 0x83ff, 0x4fc0, { 0xba, 0x38, 0x2f, 0xd9, 0xc7, 0xce, 0x55, 0x9 } }

//
// Function
//

#define DISK_IO_PROTOCOL_READDISK_FUNCTION_AUTO_GUID \
  { 0xdc851e96, 0xa36f, 0x4576, { 0x94, 0x31, 0xb2, 0x31, 0xe8, 0x49, 0x55, 0x5a } }

#define DISK_IO_PROTOCOL_WRITEDISK_FUNCTION_AUTO_GUID \
  { 0xa7e55c62, 0x65b8, 0x41df, { 0x9e, 0x9b, 0xd6, 0x54, 0xbd, 0x8f, 0x26, 0xd7 } }

//
// Combination
//
#define DISK_IO_PROTOCOL_READDISK_STRESS_AUTO_GUID \
  { 0x872cd140, 0xe551, 0x4bea, { 0x87, 0xa5, 0x1c, 0xf2, 0x5d, 0x6d, 0x62, 0x12 } }

#define DISK_IO_PROTOCOL_WRITEDISK_STRESS_AUTO_GUID \
  { 0x8b5de510, 0x7f73, 0x421d, { 0xb1, 0xa, 0x36, 0xb1, 0xe9, 0xc1, 0xd6, 0xeb } }


#endif

