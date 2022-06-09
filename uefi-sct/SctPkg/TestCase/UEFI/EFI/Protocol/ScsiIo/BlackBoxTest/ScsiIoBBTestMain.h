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

  ScsiIoBBTestMain.h

Abstract:

  BB test header file of Scsi Io protocol

--*/


#ifndef _SCSI_IO_BBTEST_H_
#define _SCSI_IO_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/ScsiIo.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  SCSI_IO_PROTOCOL_TEST_REVISION    0x00010000

EFI_STATUS
EFIAPI
InitializeBBTestScsiIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestScsiIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
EFIAPI
BBTestGetDeviceTypeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDeviceLocationFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetBusFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetDeviceFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestExecuteScsiCommandFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDeviceTypeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetDeviceLocationConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetBusConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetDeviceConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestExecuteScsiCommandConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Other function declaration section
//
VOID
NotifyFunction (
  EFI_EVENT Event,
  VOID      *Context
  );

//
// Entry GUIDs
//

#define SCSI_IO_PROTOCOL_GET_DEVICE_TYPE_FUNCTION_AUTO_GUID \
  { 0x802c43b6, 0xfa33, 0x4f56, { 0xbe, 0x61, 0x40, 0x32, 0xc5, 0xa7, 0xcc, 0xb0 } }

#define SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION_FUNCTION_AUTO_GUID \
  { 0xdd173f5f, 0x3154, 0x451d, { 0xb0, 0x5f, 0x4c, 0x8, 0xed, 0xd2, 0x28, 0x13 } }

#define SCSI_IO_PROTOCOL_RESET_BUS_FUNCTION_AUTO_GUID \
  { 0xb98e8f48, 0xefbb, 0x4db4, { 0x9d, 0x21, 0xdf, 0xb0, 0x2e, 0x46, 0x37, 0xb8 } }

#define SCSI_IO_PROTOCOL_RESET_DEVICE_FUNCTION_AUTO_GUID \
  { 0xd81b5d60, 0xaad9, 0x4aea, { 0xbf, 0xe8, 0x1, 0x4e, 0xa0, 0x99, 0xb, 0xe1 } }

#define SCSI_IO_PROTOCOL_EXECUTE_SCSI_COMMAND_FUNCTION_AUTO_GUID \
  { 0xa1190b41, 0x10a4, 0x4008, { 0x91, 0x5a, 0x58, 0x39, 0x2, 0xe8, 0x7c, 0x91 } }


#define SCSI_IO_PROTOCOL_GET_DEVICE_TYPE_CONFORMANCE_AUTO_GUID \
  { 0x164a0334, 0x6def, 0x4ab5, { 0x89, 0x3a, 0x17, 0x50, 0x9c, 0x1, 0xdb, 0x2 } }

#define SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION_CONFORMANCE_AUTO_GUID \
  { 0xef04e66d, 0xedbb, 0x48ed, { 0xb0, 0xc0, 0xe1, 0x19, 0xd, 0xfc, 0xba, 0x7a } }

#define SCSI_IO_PROTOCOL_RESET_BUS_CONFORMANCE_AUTO_GUID \
  { 0x5156b2aa, 0x5606, 0x4dc8, { 0xa3, 0x67, 0x9b, 0xc4, 0x65, 0xc2, 0xb6, 0x7b } }

#define SCSI_IO_PROTOCOL_RESET_DEVICE_CONFORMANCE_AUTO_GUID \
  { 0x93bb9f0f, 0x9139, 0x400d, { 0xae, 0x16, 0x74, 0x79, 0x6f, 0x53, 0xb6, 0xca } }

#define SCSI_IO_PROTOCOL_EXECUTE_SCSI_COMMAND_CONFORMANCE_AUTO_GUID \
  { 0xc788d60e, 0x6b17, 0x46ba, { 0x84, 0xf0, 0x18, 0xd4, 0xd7, 0x87, 0x48, 0x8f } }

#endif

