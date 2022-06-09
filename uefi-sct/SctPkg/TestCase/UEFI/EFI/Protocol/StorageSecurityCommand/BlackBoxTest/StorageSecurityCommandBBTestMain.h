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

  StorageSecurityCommandBBTestMain.h

Abstract:

  BB test header file of Storage Security Command Protocol

--*/


#ifndef _STORAGE_SEC_COMMAND_BBTEST_H_
#define _STORAGE_SEC_COMMAND_BBTEST_H_

//
// Includes
//

#include "Efi.h"
#include <UEFI/Protocol/StorageSecurityCommand.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/BlockIo.h>
#include <UEFI/Protocol/DevicePathUtilities.h>
#include <UEFI/Protocol/DevicePathToText.h>

//
// Definitions
//

#define STORAGE_SECURITY_COMMAND_PROTOCOL_TEST_REVISION     0x00010000

#define MAXIMUM(a,b)                        ((a)>(b)?(a):(b))
#define MINIMUM(a,b)                        ((a)<(b)?(a):(b))

//
// Entry GUIDs
//

//
// Conformance
//
#define STORAGE_SECURITY_COMMAND_PROTOCOL_RECEIVEDATA_CONFORMANCE_AUTO_GUID \
  { 0xe091bfcd, 0x290b, 0x44c0, { 0x92, 0x57, 0xc5, 0xfa, 0x61, 0x60, 0xd9, 0x68 } }


#define STORAGE_SECURITY_COMMAND_PROTOCOL_SENDDATA_CONFORMANCE_AUTO_GUID \
  { 0xa4bae301, 0x8de8, 0x4afc, { 0xa4, 0x4a, 0x66, 0x9f, 0xbb, 0x8e, 0x33, 0xba } }

//
// Function
//


//
// Global variables
//


//
// Prototypes
//

EFI_STATUS
EFIAPI
InitializeBBTestStorageSecurityCommand (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestStorageSecurityCommandProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Conformance test case prototypes
//

EFI_STATUS
EFIAPI
BBTestReceiveDataConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestSendDataConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Function test case prototypes
//


//
// Stress test case prototypes
//


//
// Internal support function prototypes
//

#define ROUNDUP512(x) (((x) % 512 == 0) ? (x) : ((x) / 512 + 1) * 512) 

#define SECURITY_PROTOCOL_TCG      0x02
#define SECURITY_PROTOCOL_IEEE1667 0xEE

#endif

