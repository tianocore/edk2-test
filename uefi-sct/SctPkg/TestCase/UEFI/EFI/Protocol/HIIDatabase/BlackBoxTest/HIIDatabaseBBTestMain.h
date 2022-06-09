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

  HIIDatabaseBBTestMain.h

Abstract:

  Test Driver of HII Database Protocol header file

--*/

#ifndef _HII_DATABASE_BB_TEST_MAIN
#define _HII_DATABASE_BB_TEST_MAIN

#define __UEFI_INTERNAL_FORMREPRESENTATION_H__
#include <Base.h>
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/Hii.h>
//#include "HIIDatabase.h"
#include "Guid.h"


#define EFI_HII_DATABASE_PROTOCOL_TEST_REVISION    0x00010000

//
// TestNoInterfaceProtocol2
//
#define TEST_NO_INTERFACE_PROTOCOL_2_GUID \
  {0x3fd2484, 0xa340, 0x41a7, 0xba, 0x13, 0xb4, 0x93, 0xb0, 0x67, 0xdb, 0x4c };

extern EFI_GUID mTestNoInterfaceProtocol2Guid;

//
// Entry GUIDs for Func Test
//
#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xa631c5f5, 0x991, 0x4265, { 0x97, 0x57, 0x10, 0x50, 0xaa, 0x96, 0x68, 0xd0 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0xc35dfc8e, 0xb7c9, 0x413d, { 0xa3, 0x16, 0xc4, 0x3c, 0xaf, 0x65, 0x4c, 0x26 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0xc3a3a0, 0x1a1e, 0x4609, { 0x9b, 0xf, 0xf2, 0x83, 0x53, 0x1, 0x43, 0x2e } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0x31338003, 0x325e, 0x45da, { 0x9c, 0xa9, 0x42, 0x73, 0x3, 0xee, 0xfc, 0x67 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0xf8ba647, 0x1f74, 0x4d62, { 0xab, 0x91, 0xf1, 0x52, 0x6b, 0x50, 0x7d, 0xa6 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0106 \
{ 0xf30bf618, 0xbcb6, 0x4824, { 0xa2, 0x44, 0x2b, 0x85, 0x3f, 0xe, 0xef, 0xe2 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0107 \
{ 0x29820a29, 0x18b2, 0x470d, { 0x92, 0xdd, 0x5b, 0x63, 0xf8, 0x92, 0x2b, 0x5e } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0108 \
{ 0x11d5958c, 0xbbe7, 0x4851, { 0xa0, 0x5c, 0xe0, 0x5, 0x9a, 0xa, 0x8d, 0x3a } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0109 \
{ 0x73332b8c, 0xaf68, 0x4e12, { 0x91, 0x3d, 0x5d, 0x89, 0xe8, 0xfb, 0x89, 0x25 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID01010 \
{ 0xd0126067, 0x99cd, 0x46c5, { 0x83, 0x9f, 0x43, 0xb0, 0xa9, 0xb, 0x79, 0xc5 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID01011 \
{ 0xb54b29f4, 0xb2a5, 0x49e8, { 0xbc, 0xa6, 0xf6, 0x92, 0x97, 0x33, 0xdd, 0x11 } }

//
// Entry GUIDs for Conf Test
//
#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x33f9b795, 0x7169, 0x4e51, { 0xb9, 0xc8, 0x67, 0xfd, 0x6b, 0x6b, 0x1a, 0x89 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xfea8fdc7, 0x7f40, 0x41e0, { 0xa8, 0x4b, 0xa7, 0xb, 0xe6, 0x86, 0x9a, 0xcf } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0xc8a7eff2, 0xa281, 0x4f3d, { 0x85, 0xcc, 0xba, 0x9c, 0xb4, 0xe5, 0xf6, 0xd2 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0x3df6360e, 0xab9a, 0x4cb6, { 0xbc, 0x43, 0x1c, 0xdb, 0xc8, 0xff, 0x50, 0xe9 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0xb6dce569, 0xa0e, 0x4fce, { 0x9e, 0xe0, 0x86, 0x87, 0x30, 0xf5, 0xc, 0x4d } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0206 \
{ 0x771a6282, 0xb330, 0x45db, { 0xa4, 0xc0, 0x4d, 0x80, 0x14, 0x29, 0xed, 0x1d } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0207 \
{ 0x206bb846, 0x46b6, 0x481e, { 0xa4, 0x84, 0x12, 0x1c, 0x8d, 0x72, 0xfe, 0x60 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0208 \
{ 0x3952e6c7, 0x3b3c, 0x4b24, { 0x93, 0x20, 0xe2, 0xc5, 0x3c, 0xc5, 0x50, 0x25 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID0209 \
{ 0xe8683eeb, 0x56a0, 0x401c, { 0x89, 0xc8, 0xd8, 0xba, 0x67, 0x2f, 0x40, 0xf0 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID02010 \
{ 0xba3f895d, 0xe76e, 0x4c43, { 0x8a, 0x38, 0xd9, 0x4e, 0x95, 0xd6, 0x9f, 0x42 } }

#define EFI_HII_DATABASE_PROTOCOL_TEST_ENTRY_GUID02011 \
{ 0xd51ebda6, 0x391b, 0x49bc, { 0xa4, 0xcb, 0xe, 0xaf, 0x1a, 0xe, 0x3a, 0x5 } }

//
//
//
EFI_STATUS
EFIAPI
InitializeHIIDatabaseBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadHIIDatabaseBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
EFI_STATUS
EFIAPI
DoNothingPackageNotifyFn (
  IN UINT8                           PackageType,
  IN CONST EFI_GUID                  *PackageGuid,
  IN CONST EFI_HII_PACKAGE_HEADER    *Package,
  IN EFI_HII_HANDLE                  Handle,
  IN EFI_HII_DATABASE_NOTIFY_TYPE    NotifyType
);
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestNewPackageListConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestRemovePackageListConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestUpdatePackageListConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestListPackageListsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestExportPackageListsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestRegisterPackageNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestUnregisterPackageNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestFindKeyboardLayoutsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestSetKeyboardLayoutConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetPackageListHandleConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestNewPackageListFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestRemovePackageListFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestUpdatePackageListFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestListPackageListsFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestExportPackageListsFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestRegisterPackageNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestUnregisterPackageNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestFindKeyboardLayoutsFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetKeyboardLayoutFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestSetKeyboardLayoutFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetPackageListHandleFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
#endif
