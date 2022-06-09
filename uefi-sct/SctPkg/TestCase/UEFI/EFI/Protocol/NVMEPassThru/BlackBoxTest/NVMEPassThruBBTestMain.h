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

  NVMEPassThruBBTestMain.h

Abstract:

  Test Driver of NVME PassThru Protocol header file

--*/

#ifndef _NVME_PASSTHRU_BB_TEST_MAIN
#define _NVME_PASSTHRU_BB_TEST_MAIN

#include <Efi.h>
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/NVMEPassThru.h>
#include "Guid.h"


#define EFI_NVME_PASSTHRU_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_NVME_PASSTHRU_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xc31b2082, 0x4bbc, 0x4581, {0x98, 0x68, 0xaf, 0xc0, 0x4b, 0xf, 0x67, 0x7f }}

#define EFI_NVME_PASSTHRU_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x5e4de7d8, 0x4266, 0x4446, {0x96, 0x1f, 0xb1, 0x13, 0x63, 0x8a, 0x3b, 0xba }}

#define EFI_NVME_PASSTHRU_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x7af73c69, 0x1817, 0x453d, {0xae, 0xda, 0xc3, 0x9e, 0x14, 0x87, 0x26, 0xf7 }}

#define EFI_NVME_PASSTHRU_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0x2cb12498, 0xe72d, 0x4d56, {0x8f, 0xf2, 0xcd, 0x77, 0x6c, 0xce, 0x84, 0x4f }}


//
// Entry GUIDs for Conf Test
//
#define EFI_NVME_PASSTHRU_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xba5e592f, 0xa0b9, 0x4d6b, {0xb0, 0xc5, 0xd1, 0x65, 0xb9, 0x83, 0x3c, 0xe4 }}

#define EFI_NVME_PASSTHRU_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x8644fd7e, 0xecd8, 0x4a2f, {0x9a, 0x4, 0x78, 0x77, 0xc0, 0xf6, 0x54, 0x2b }}

#define EFI_NVME_PASSTHRU_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x8a44094b, 0xe65b, 0x406d, {0x8e, 0x26, 0xae, 0x83, 0xd2, 0xde, 0x75, 0xce }}

#define EFI_NVME_PASSTHRU_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0xedab7937, 0x7a09, 0x4812, { 0xa0, 0xee, 0xe, 0x79, 0x5a, 0x9b, 0x6b, 0x23 }}


typedef struct {
  UINT16 Ms;                /* Metadata Size */
  UINT8  Lbads;             /* LBA Data Size */
  UINT8  Rp:2;              /* Relative Performance */
    #define LBAF_RP_BEST      00b
    #define LBAF_RP_BETTER    01b
    #define LBAF_RP_GOOD      10b
    #define LBAF_RP_DEGRADED  11b
  UINT8  Rsvd1:6;           /* Reserved as of Nvm Express 1.1 Spec */
} NVME_LBAFORMAT;

typedef struct {
  //
  // NVM Command Set Specific
  //
  UINT64 Nsze;                /* Namespace Size (total number of blocks in formatted namespace) */
  UINT64 Ncap;                /* Namespace Capacity (max number of logical blocks) */
  UINT64 Nuse;                /* Namespace Utilization */
  UINT8  Nsfeat;              /* Namespace Features */
  UINT8  Nlbaf;               /* Number of LBA Formats */
  UINT8  Flbas;               /* Formatted LBA size */
  UINT8  Mc;                  /* Metadata Capabilities */
  UINT8  Dpc;                 /* End-to-end Data Protection capabilities */
  UINT8  Dps;                 /* End-to-end Data Protection Type Settings */
  UINT8  Nmic;                /* Namespace Multi-path I/O and Namespace Sharing Capabilities */
  UINT8  Rescap;              /* Reservation Capabilities */
  UINT8  Rsvd1[88];           /* Reserved as of Nvm Express 1.1 Spec */
  UINT64 Eui64;               /* IEEE Extended Unique Identifier */
  //
  // LBA Format
  //
  NVME_LBAFORMAT LbaFormat[16];

  UINT8 Rsvd2[192];           /* Reserved as of Nvm Express 1.1 Spec */
  UINT8 VendorData[3712];     /* Vendor specific data */
} NVME_ADMIN_NAMESPACE_DATA;


//
//
//
EFI_STATUS
EFIAPI
InitializeNVMEPassThruBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadNVMEPassThruBBTest (
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
BBTestGetNextNamespaceConformanceTest (
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
BBTestGetNamespaceConformanceTest (
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
BBTestGetNextNamespaceFunctionTest (
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
BBTestGetNamespaceFunctionTest (
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

