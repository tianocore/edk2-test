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

  RedfishDiscoverBBTestMain.h

Abstract:

  Test Driver of EFI Redfish Discover Protocol header file

--*/

#ifndef _REDFISH_DISCOVER_BB_TEST_MAIN_H_
#define _REDFISH_DISCOVER_BB_TEST_MAIN_H_

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include "Guid.h"
#include <UEFI/Protocol/RedfishDiscover.h>

#define EFI_REDFISH_DISCOVER_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Function Test
//
#define EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x1a2b3c4d, 0x5e6f, 0x4a70, { 0x81, 0x92, 0xa3, 0xb4, 0xc5, 0xd6, 0xe7, 0xf8 } }

#define EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x2b3c4d5e, 0x6f70, 0x4b81, { 0x92, 0xa3, 0xb4, 0xc5, 0xd6, 0xe7, 0xf8, 0x09 } }

#define EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x3c4d5e6f, 0x7081, 0x4c92, { 0xa3, 0xb4, 0xc5, 0xd6, 0xe7, 0xf8, 0x09, 0x1a } }

#define EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0x4d5e6f70, 0x8192, 0x4da3, { 0xb4, 0xc5, 0xd6, 0xe7, 0xf8, 0x09, 0x1a, 0x2b } }

//
// Entry GUIDs for Conformance Test
//
#define EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x5e6f7081, 0x92a3, 0x4eb4, { 0xc5, 0xd6, 0xe7, 0xf8, 0x09, 0x1a, 0x2b, 0x3c } }

#define EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x6f708192, 0xa3b4, 0x4fc5, { 0xd6, 0xe7, 0xf8, 0x09, 0x1a, 0x2b, 0x3c, 0x4d } }

#define EFI_REDFISH_DISCOVER_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x708192a3, 0xb4c5, 0x40d6, { 0xe7, 0xf8, 0x09, 0x1a, 0x2b, 0x3c, 0x4d, 0x5e } }

//
// Function prototypes
//
EFI_STATUS
EFIAPI
InitializeRedfishDiscoverBBTest (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );

EFI_STATUS
EFIAPI
UnloadRedfishDiscoverBBTest (
  IN EFI_HANDLE                 ImageHandle
  );

//
// Function Test Cases
//
EFI_STATUS
EFIAPI
BBTestGetNetworkInterfaceListFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestAcquireRedfishServiceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestAbortAndReleaseFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestReleaseRedfishServiceFunctionTest (
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
BBTestGetNetworkInterfaceListConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestAcquireRedfishServiceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestReleaseRedfishServiceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#endif
