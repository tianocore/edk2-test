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

  DriverBindingBBTest.h

Abstract:

  head file of test driver of EFI Driver Binding Protocol Test

--*/

#ifndef _DRIVER_BINDING_TEST_H
#define _DRIVER_BINDING_TEST_H


#include "Efi.h"
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/DriverBinding.h>
#include "Guid.h"
#include "Print.h"

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

#define IHV_DRIVER_BINDING_TEST_REVISION    0x00010000

#define IHV_DRIVER_BINDING_PROTOCOL_GUID    \
  { 0x6f36a19d, 0x44d0, 0x4334, 0x94, 0x5d, 0x37, 0xbb, 0x5a, 0x55, 0xbf, 0x32 }


//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for test entry
//
#define EFI_DRIVER_BINDING_PROTOCOL_TEST_ENTRY_GUID0101   \
  { 0x50de666c, 0xee1a, 0x4f22, 0x94, 0xca, 0x92, 0xd4, 0xaf, 0xad, 0xd2, 0x58 }

#define SYSTEMLOG 0
#define CASELOG   1
#define SYSTEMKEY 2
#define CASEKEY   3

//
// functions declaration
//

EFI_STATUS
EFIAPI
InitializeBBTestDriverBinding (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDriverBindingUnload (
  IN EFI_HANDLE       ImageHandle
  );


//
// Test function
//

EFI_STATUS
BBTestDriverBindingFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

#endif
