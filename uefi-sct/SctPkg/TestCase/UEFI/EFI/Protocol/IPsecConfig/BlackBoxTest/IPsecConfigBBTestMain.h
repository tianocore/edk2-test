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

  IPsecConfigBBTestMain.h

Abstract:

  Test Driver of IPsec Config Protocol header file

--*/

#ifndef _IPSEC_CONFIG_BB_TEST_MAIN
#define _IPSEC_CONFIG_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/IPsecConfig.h>
#include "Guid.h"


#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_REVISION    0x00010000


//
// Entry GUIDs for Func Test
//
#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xd69baaa6, 0xa7a6, 0x4e15, { 0x9d, 0x3e, 0xa5, 0x77, 0xb8, 0x3b, 0xc2, 0x48 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x1944aae7, 0x4325, 0x45cf, { 0x82, 0x54, 0x5b, 0xb6, 0xd5, 0xa7, 0xa2, 0x6f } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x6e1a3e05, 0xd689, 0x465b, { 0xbb, 0x20, 0xb6, 0x67, 0x99, 0x25, 0x3f, 0x7a } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0xfe966b77, 0x5eb2, 0x4f97, { 0xa0, 0x64, 0xec, 0xf9, 0xc6, 0xd8, 0x6e, 0x3d } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0x44187ec6, 0x3b4a, 0x4909, { 0x81, 0x7b, 0xe7, 0xe8, 0xbc, 0x86, 0xe2, 0xde } }

//
// Entry GUIDs for Conf Test
//
#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xd44836ca, 0x4bc9, 0x4a37, { 0x97, 0x49, 0x70, 0xe8, 0x07, 0x8d, 0x84, 0xf7 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xacbf8376, 0xbea7, 0x4ad4, { 0x88, 0xb1, 0xb5, 0x44, 0xee, 0x29, 0xfb, 0xa7 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0xf8c735ac, 0xa588, 0x44a3, { 0xab, 0x7d, 0x36, 0x2c, 0xc0, 0xe7, 0xfa, 0x50 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0xb3342367, 0x9cf2, 0x4f32, { 0xbe, 0x58, 0x59, 0x8b, 0x4f, 0xc3, 0xcd, 0x80 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0x27b9dc40, 0x84ef, 0x43ad, { 0xbc, 0xcd, 0x3e, 0xa4, 0x61, 0x2c, 0xe3, 0x86 } }

//
//
//
EFI_STATUS
EFIAPI
InitializeIPsecConfigBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadIPsecConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestSetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestRegisterDataNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestSetDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetNextSelectorFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestRegisterDataNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

VOID
EventNotifyFunc (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );


#endif
