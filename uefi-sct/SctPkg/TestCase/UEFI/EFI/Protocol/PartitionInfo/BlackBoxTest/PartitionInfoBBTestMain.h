/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  PartitionInfoBBTestMain.h

Abstract:

  Test Driver of Partition Info Protocol header file

--*/

#ifndef _PARTITION_INFO_BB_TEST_MAIN
#define _PARTITION_INFO_BB_TEST_MAIN

#include <Efi.h>
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/PartitionInfo.h>
#include "Guid.h"


#define EFI_PARTITION_INFO_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_PARTITION_INFO_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xf53c074a, 0x4625, 0x4380, { 0x90, 0x91, 0x4f, 0xfe, 0xd7, 0xf0, 0x3, 0x23 }}


//
//
//
EFI_STATUS
EFIAPI
InitializePartitionInfoBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadPartitionInfoBBTest (
  IN EFI_HANDLE                   ImageHandle
  ); 
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestPartitionInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

INTN 
GuidCmp(
  EFI_GUID                      GuidGiven,
  EFI_GUID                      GuidNeedToCmp
  );

#endif
