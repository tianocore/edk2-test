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

  VlanConfigBBTestMain.h

Abstract:

  Test Driver of Vlan Config Protocol header file

--*/

#ifndef _VLAN_CONFIG_BB_TEST_MAIN
#define _VLAN_CONFIG_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/VlanConfig.h>
#include "Guid.h"


#define EFI_VLAN_CONFIG_PROTOCOL_TEST_REVISION    0x00010000


//
// Entry GUIDs for Func Test
//
#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xe7bbe8f0, 0x22c6, 0x4e6d, { 0x92, 0xb7, 0xf0, 0xc2, 0xab, 0x2c, 0xd4, 0xde } }

#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x8c9f551e, 0xe931, 0x45dc, { 0x87, 0xdb, 0xd7, 0x78, 0xfa, 0x08, 0x44, 0x66 } }

#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0xa4d0f821, 0xaa43, 0x4764, { 0xb2, 0x10, 0x37, 0xb7, 0x8b, 0xea, 0x31, 0x11 } }


//
// Entry GUIDs for Conf Test
//
#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xab5d2897, 0x915b, 0x4339, { 0x9c, 0x43, 0x45, 0xb5, 0x07, 0x61, 0x61, 0xc9 } }

#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x3155723f, 0xc0c0, 0x4a94, { 0x81, 0x94, 0x52, 0x67, 0xb1, 0x75, 0x57, 0xc1 } }

#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x8c7bcbdc, 0x06a8, 0x416c, { 0x92, 0x42, 0x21, 0x58, 0x50, 0x59, 0xd2, 0x1b } }


//
// Get a valid VlanId
//
EFI_STATUS
GetAValidVlanId (
  EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig,
  UINT16                                     *VlanId
  );

//
// Get a Invalid VlanId
//
EFI_STATUS
GetAnInvalidVlanId (
  EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig,
  UINT16                                     *VlanId
  );

//
//
//
EFI_STATUS
EFIAPI
InitializeVlanConfigBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadVlanConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestSetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestFindConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestRemoveConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

  
EFI_STATUS
EFIAPI
BBTestSetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestFindFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestRemoveFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#endif
