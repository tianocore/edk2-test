/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  HIIStringBBTestMain.h

Abstract:

  Test Driver of HII String Protocol header file

--*/

#ifndef _HII_STRING_BB_TEST_MAIN
#define _HII_STRING_BB_TEST_MAIN

#define __UEFI_INTERNAL_FORMREPRESENTATION_H__
#include <Base.h>
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/Hii.h>
#include "Guid.h"


#define EFI_HII_STRING_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xf5050750, 0x8e84, 0x46db, { 0xa3, 0xe3, 0x62, 0x7, 0x34, 0x13, 0xa5, 0x69 } }

#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x4dfdbdfc, 0xb23f, 0x49db, { 0x91, 0x70, 0x7d, 0x69, 0xfd, 0xf8, 0x88, 0x68 } }

#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x2ec82b5d, 0x49f7, 0x4b3e, { 0xb8, 0x84, 0xa5, 0xeb, 0x17, 0x1e, 0x23, 0x69 } }

#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0x5ce20b3c, 0xcb59, 0x412f, { 0xa1, 0x37, 0xbb, 0xe5, 0x94, 0x22, 0xf8, 0x60 } }

#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0x75a47073, 0x8ba9, 0x4b56, { 0x8d, 0xf1, 0x54, 0xa1, 0x00, 0x63, 0xf6, 0xa1 } }

//
// Entry GUIDs for Conf Test
//
#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x94971a6a, 0xb0eb, 0x4c86, { 0xb3, 0x4a, 0x86, 0x68, 0x86, 0x80, 0x1d, 0xf9 } }

#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x9d28a801, 0x49d8, 0x4a7f, { 0x89, 0x5e, 0x73, 0x2e, 0x43, 0x6b, 0xdf, 0x3c } }

#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x69ddddbb, 0xdce4, 0x4afc, { 0x90, 0x60, 0x26, 0xb4, 0x99, 0x8e, 0x7d, 0xc1 } }

#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0x24e0cca8, 0x80f0, 0x4391, { 0x88, 0x16, 0x3b, 0xcc, 0x21, 0x61, 0x6e, 0x54 } }

#define EFI_HII_STRING_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0xaa37eddc, 0x68ee, 0x4d69, { 0x8d, 0x0b, 0xa4, 0x31, 0xf1, 0xe7, 0xb8, 0x0f } }

//
//
//
EFI_STATUS
EFIAPI
InitializeHIIStringBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
  
EFI_STATUS
EFIAPI
UnloadHIIStringBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestNewStringConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetStringConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestSetStringConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetLanguagesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetSecondaryLanguagesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestNewStringFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetStringFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestSetStringFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetLanguagesFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetSecondaryLanguagesFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//
//
EFI_STATUS
GetHIIDatabaseInterface (
  OUT EFI_HII_DATABASE_PROTOCOL    **HIIDatabase
  );
  
#endif
