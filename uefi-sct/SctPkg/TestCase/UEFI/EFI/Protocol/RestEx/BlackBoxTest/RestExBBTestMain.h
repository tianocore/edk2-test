/** @file

  Copyright 2006 - 2026 Unified EFI, Inc.<BR>
  Copyright (c) 2026, AMD Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  RestExBBTestMain.h

Abstract:

  Test Driver of EFI REST EX Protocol header file

--*/

#ifndef _REST_EX_BB_TEST_MAIN_H_
#define _REST_EX_BB_TEST_MAIN_H_

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include "Guid.h"
#include <UEFI/Protocol/RestEx.h>

#define EFI_REST_EX_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Function Test
//
#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xa3c1d7b2, 0x4e5f, 0x4a91, { 0xb8, 0x2c, 0xd1, 0x3e, 0x6a, 0x9f, 0x05, 0x73 } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0xb4d2e8c3, 0x5f60, 0x4b02, { 0xc9, 0x3d, 0xe2, 0x4f, 0x7b, 0xa0, 0x16, 0x84 } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0xc5e3f9d4, 0x6071, 0x4c13, { 0xda, 0x4e, 0xf3, 0x50, 0x8c, 0xb1, 0x27, 0x95 } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0xd6f400e5, 0x7182, 0x4d24, { 0xeb, 0x5f, 0x04, 0x61, 0x9d, 0xc2, 0x38, 0xa6 } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0xe7050116, 0x8293, 0x4e35, { 0xfc, 0x60, 0x15, 0x72, 0xae, 0xd3, 0x49, 0xb8 } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0106 \
{ 0xf8160227, 0x93a4, 0x4f46, { 0x0d, 0x71, 0x26, 0x83, 0xbf, 0xe4, 0x5a, 0xc9 } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0107 \
{ 0x09270338, 0xa4b5, 0x4057, { 0x1e, 0x82, 0x37, 0x94, 0xc0, 0xf5, 0x6b, 0xda } }

//
// Entry GUIDs for Conformance Test
//
#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xe7050116, 0x8293, 0x4e35, { 0xfc, 0x60, 0x15, 0x72, 0xae, 0xd3, 0x49, 0xb7 } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xf8160227, 0x93a4, 0x4f46, { 0x0d, 0x71, 0x26, 0x83, 0xbf, 0xe4, 0x5a, 0xc8 } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x09270338, 0xa4b5, 0x4057, { 0x1e, 0x82, 0x37, 0x94, 0xc0, 0xf5, 0x6b, 0xd9 } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0x1a380449, 0xb5c6, 0x4168, { 0x2f, 0x93, 0x48, 0xa5, 0xd1, 0x06, 0x7c, 0xea } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0x2b49055a, 0xc6d7, 0x4279, { 0x30, 0xa4, 0x59, 0xb6, 0xe2, 0x17, 0x8d, 0xfb } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0206 \
{ 0x3c5a166b, 0xd7e8, 0x438a, { 0x41, 0xb5, 0x6a, 0xc7, 0xf3, 0x28, 0x9e, 0x0c } }

#define EFI_REST_EX_PROTOCOL_TEST_ENTRY_GUID0207 \
{ 0x4d6b277c, 0xe8f9, 0x449b, { 0x52, 0xc6, 0x7b, 0xd8, 0x04, 0x39, 0xaf, 0x1d } }

//
// Function prototypes
//
EFI_STATUS
EFIAPI
InitializeRestExBBTest (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadRestExBBTest (
  IN EFI_HANDLE                 ImageHandle
  );

//
// Function Test Cases
//
EFI_STATUS
EFIAPI
BBTestGetServiceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetModeDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestConfigureFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSendReceiveFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetServiceTimeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestAyncSendReceiveFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestEventServiceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Conformance Test Cases
//
EFI_STATUS
EFIAPI
BBTestGetServiceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetModeDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestConfigureConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSendReceiveConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestAyncSendReceiveConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetServiceTimeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestEventServiceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#endif
