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

  UFSDeviceConfigBBTestMain.h

Abstract:

  Test Driver of UFS Device Config Protocol header file

--*/

#ifndef _UFS_DEVICE_CONFIG_BB_TEST_MAIN
#define _UFS_DEVICE_CONFIG_BB_TEST_MAIN

#include <Efi.h>
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/UFSDeviceConfig.h>
#include "Guid.h"


#define EFI_UFS_DEVICE_CONFIG_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Conf Test
//
#define EFI_UFS_DEVICE_CONFIG_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xd30731cd, 0xa679, 0x41fc, { 0x9f, 0xa6, 0x65, 0x27, 0xab, 0x62, 0x4a, 0x5d  }}

#define EFI_UFS_DEVICE_CONFIG_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0xecbc61af, 0x878d, 0x4215, { 0x87, 0xb, 0xed, 0xf0, 0x2c, 0xf4, 0x5a, 0x96 }}

#define EFI_UFS_DEVICE_CONFIG_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x52834ee4, 0x611e, 0x4995, { 0xae, 0xc3, 0x72, 0xf5, 0x8, 0x2b, 0x18, 0x4f }}


//
//
//
EFI_STATUS
EFIAPI
InitializeUFSDeviceConfigBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadUFSDeviceConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  ); 
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestRwUfsDescriptorConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestRwUfsFlagConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestRwUfsAttributeConfTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#endif
