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

  RamDiskProtocolBBTestMain.h

Abstract:

  Test Driver of RamDisk Protocol header file

--*/

#ifndef _RAM_DISK_PROTOCOL_BB_TEST_MAIN_H
#define _RAM_DISK_PROTOCOL_BB_TEST_MAIN_H

#include <Efi.h>
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include "Guid.h"
#include <UEFI/Protocol/RamDisk.h>

#define EFI_RAM_DISK_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func and Conf Test
//
#define EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x7a825f36, 0x6042, 0x423e, { 0xa4, 0x66, 0x62, 0xd1, 0xf9, 0x10, 0xe4, 0x59 } }

#define EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0xba0988ad, 0x6dcc, 0x49a5, { 0xb3, 0x1b, 0xe1, 0xf2, 0xb6, 0x6a, 0xc8, 0xdd } }

#define EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xdd819f83, 0xe040, 0x4ff7, { 0xab, 0x84, 0x62, 0xa, 0xad, 0x70, 0x3f, 0x48 } }

#define EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x60505491, 0xc8a6, 0x4194, { 0xab, 0xb5, 0x31, 0xa1, 0xf7, 0xd3, 0x4e, 0xad } }


EFI_STATUS
EFIAPI
InitializeBBTestRamDiskProtocol (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadBBTestRamDiskProtocol (
  IN EFI_HANDLE                   ImageHandle
  );

//
// Prototypes: Test Cases
//
EFI_STATUS
EFIAPI
BBTestRegisterRamDiskFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
  
EFI_STATUS
EFIAPI
BBTestUnregisterRamDiskFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestRegisterRamDiskConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
  
EFI_STATUS
EFIAPI
BBTestUnregisterRamDiskConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  ); 

#endif
