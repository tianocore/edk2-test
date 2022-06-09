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

  TimeStampBBTestMain.h

Abstract:

  Test Driver of Time Stamp Protocol header file

--*/

#ifndef _TIME_STAMP_BB_TEST_MAIN
#define _TIME_STAMP_BB_TEST_MAIN


#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/TimeStamp.h>
#include "Guid.h"


#define EFI_TIMESTAMP_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_TIME_STAMP_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x52aefe36, 0x0d62, 0x4bfa, { 0xb8, 0x8c, 0x64, 0x8d, 0xf8, 0x51, 0x6a, 0xbf } }

#define EFI_TIME_STAMP_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x9092eb07, 0x1e6e, 0x4d6f, { 0xa7, 0xec, 0x56, 0x16, 0x36, 0xd3, 0x59, 0x95 } }

//
// Entry GUIDs for Conf Test
//
#define EFI_TIME_STAMP_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x7cbc4a50, 0x82c2, 0x4765, { 0xae, 0x35, 0x51, 0xbc, 0x85, 0x3d, 0x1f, 0x49 } }



//
//
//
EFI_STATUS
EFIAPI
InitializeTimeStampBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
  
EFI_STATUS
EFIAPI
UnloadTimeStampBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestGetTimestampFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetPropertiesFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestGetPropertiesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


#endif
