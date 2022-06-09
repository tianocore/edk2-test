/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AdapterInfoBBTestMain.h

Abstract:

  Test Driver of Adapter Information Protocol header file

--*/

#ifndef _ADAPTER_INFORMATION_BB_TEST_MAIN
#define _ADAPTER_INFORMATION_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/AdapterInfo.h>
#include "Guid.h"


#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_REVISION    0x00010000



//
// Entry GUIDs for Func Test
//
#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xfeb5d3b9, 0x23ef, 0x4cfb, { 0xb9, 0x1a, 0x43, 0xd2, 0xf, 0x4b, 0x8b, 0x3 } }

#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x69891f7e, 0xdb2c, 0x4d00, { 0x92, 0xd3, 0x58, 0x84, 0x22, 0x86, 0xb, 0x2d } }

#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0xd8fe3070, 0xc23e, 0x46c9, { 0xb7, 0x1b, 0x6c, 0x8c, 0xb6, 0xb4, 0x26, 0xd } }


//
// Entry GUIDs for Conf Test
//
#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x72555bc1, 0x8da6, 0x4814, { 0xb1, 0xd9, 0x98, 0xb4, 0xab, 0xda, 0x90, 0xde } }

#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xad52c0e, 0x9b39, 0x41dc, { 0xae, 0xf8, 0x12, 0x30, 0x48, 0x33, 0x67, 0x13 } }

#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0xd1f31918, 0xf989, 0x4874, { 0xaa, 0xa4, 0x4b, 0x48, 0x63, 0x2a, 0x29, 0x2a } }
                           
                                
//
//GuidCmp
//

INTN 
GuidCmp(
  EFI_GUID                      GuidGiven,
  EFI_GUID                      GuidNeedToCmp
  );
//
//InfoTypeAndBlockSizeCmp
//
BOOLEAN
InfoTypeAndBlockSizeCmp( 
  EFI_GUID                      InformationType,
  UINTN                         InformationBlockSize
  );





//
//
//
EFI_STATUS
EFIAPI
InitializeAdapterInfoBBTest (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadAdapterInfoBBTest (
  IN EFI_HANDLE                 ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestGetInformationConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestSetInformationConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetSupportedTypesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

  
EFI_STATUS
EFIAPI
BBTestGetInformationFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSetInformationFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetSupportedTypesFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


VOID
SctInitializeLib (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );


#endif
