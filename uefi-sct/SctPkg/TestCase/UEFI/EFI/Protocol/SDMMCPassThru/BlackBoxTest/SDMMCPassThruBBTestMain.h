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

  SDMMCPassThruBBTestMain.h

Abstract:

  Test Driver of SDMMC Pass Thru Protocol header file

--*/

#ifndef _SDMMC_PASS_THRU_BB_TEST_MAIN
#define _SDMMC_PASS_THRU_BB_TEST_MAIN

#include <Efi.h>
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/SDMMCPassThru.h>
#include "Guid.h"


#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_REVISION    0x00010000

//
// Generic time out value, 1 microsecond as unit.
//
#define SD_MMC_HC_GENERIC_TIMEOUT     1 * 1000 * 1000




//
// Entry GUIDs for Func Test
//
#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xeadf100d, 0xf3b2, 0x44c2, { 0xbd, 0x45, 0xc4, 0x52, 0xe6, 0x48, 0x3e, 0xc1 } }

#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0xb97743f0, 0xefb3, 0x470c, { 0x91, 0xd5, 0xfe, 0xc7, 0xc3, 0x34, 0x2e, 0x54 } }

#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x59ae8aac, 0x1eed, 0x4f6a, { 0xa2, 0xee, 0xa8, 0xf5, 0xef, 0x32, 0xd5, 0xe7 } }

#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0x2d830291, 0x9537, 0x4bef, { 0x99, 0xa8, 0xb2, 0x89, 0xab, 0xbc, 0x12, 0x20 } }

#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0xd8605648, 0x902, 0x4c2d, { 0xb3, 0x89, 0x6a, 0xfb, 0x88, 0xec, 0xa7, 0x62 } }


//
// Entry GUIDs for Conf Test
//
#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xf80e4799, 0x995, 0x47b6, { 0x9c, 0x63, 0x2b, 0xf, 0x50, 0xe6, 0xc1, 0x7c } }

#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x3da054b4, 0xa9fc, 0x47af, { 0x83, 0x65, 0x87, 0x7, 0xce, 0x9e, 0x79, 0x26 } }

#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0xaf4bf459, 0x9e09, 0x42ce, { 0x97, 0xeb, 0x55, 0xf0, 0x24, 0x65, 0x9e, 0xe6 } }

#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0x15aa8e52, 0x4e37, 0x4533, { 0xab, 0x6f, 0xaa, 0x2f, 0x6b, 0x24, 0xa1, 0x85 } }

#define EFI_SDMMC_PASS_THRU_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0xf4dc85ba, 0xbb42, 0x431f, { 0xa6, 0x62, 0xc3, 0xa0, 0x19, 0xa0, 0x25, 0x64 } }


//
//
//
EFI_STATUS
EFIAPI
InitializeSDMMCPassThruBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadSDMMCPassThruBBTest (
  IN EFI_HANDLE                   ImageHandle
  ); 
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestPassThruConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetNextSlotConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestBuildDevicePathConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetSlotNumberConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetDeviceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

  
EFI_STATUS
EFIAPI
BBTestPassThruFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetNextSlotFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestBuildDevicePathFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetSlotNumberFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetDeviceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
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

