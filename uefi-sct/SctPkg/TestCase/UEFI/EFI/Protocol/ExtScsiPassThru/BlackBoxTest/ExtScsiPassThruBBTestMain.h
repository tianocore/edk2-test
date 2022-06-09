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

  ExtScsiPassThruBBTestMain.h

Abstract:

  BB test header file of Extended Scsi Pass Through protocol

--*/


#ifndef _EXT_SCSI_PASS_THRU_BBTEST_H_
#define _EXT_SCSI_PASS_THRU_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/ExtScsiPassThru.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  EXT_SCSI_PASS_THRU_PROTOCOL_TEST_REVISION    0x00010000

EFI_STATUS
EFIAPI
InitializeBBTestExtScsiPassThru (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestExtScsiPassThruProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
EFIAPI
BBTestGetNextTargetLunFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestBuildDevicePathFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetTargetLunFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetChannelFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetTargetLunFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetNextTargetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestPassThruFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetNextTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestBuildDevicePathConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestResetTargetLunConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetNextTargetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestPassThruConformanceAutoTest (
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

EFI_STATUS
BufToUHexString (
  IN OUT CHAR16                    *Str,
  IN OUT UINTN                     *HexStringBufferLength,
  IN     UINT8                     *Buf,
  IN     UINTN                      Len
  );

EFI_STATUS
GetInvalidTargetLun(
  IN    EFI_EXT_SCSI_PASS_THRU_PROTOCOL  *ExtScsiPassThru,
  IN OUT   UINT8                         *TargetAddr,
  IN OUT   UINT64                        *Lun
);


 EFI_STATUS
GetPresentTargetLun(
  IN    EFI_EXT_SCSI_PASS_THRU_PROTOCOL  *ExtScsiPassThru,
  IN OUT   UINT8                         *TargetAddr,
  IN OUT   UINT64                        *Lun
);

//
// Entry GUIDs
//

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0xacc59919, 0xf5a5, 0x4afd, { 0x94, 0x4a, 0xb1, 0x56, 0xbe, 0x57, 0x11, 0x4b } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_FUNCTION_AUTO_GUID \
  { 0xbdfb7a19, 0x1c3b, 0x4d83, { 0xa0, 0x4a, 0xf1, 0x45, 0x3d, 0xea, 0x2b, 0xb6 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0x5c119d86, 0xe670, 0x4959, { 0x9c, 0x21, 0xab, 0xac, 0xdb, 0xcc, 0x7b, 0xe1 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_RESET_CHANNEL_FUNCTION_AUTO_GUID \
  { 0xe8de6d6a, 0x609a, 0x4d57, { 0xa6, 0xc5, 0xc4, 0xb0, 0xc6, 0x5f, 0xbf, 0x73 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_LUN_FUNCTION_AUTO_GUID \
  { 0xa7930dd1, 0x1c27, 0x48c4, { 0x8a, 0x84, 0xbb, 0x22, 0x62, 0x95, 0xe8, 0x24 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_FUNCTION_AUTO_GUID \
  { 0xe745ccbe, 0x1182, 0x4068, { 0xa9, 0xbc, 0x58, 0xc4, 0xba, 0x33, 0xa6, 0xc4 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_PASS_THRU_FUNCTION_AUTO_GUID \
  { 0x5fc224f5, 0x8026, 0x4e7f, { 0x81, 0x54, 0xb5, 0x92, 0x4a, 0xf8, 0x2b, 0xd5 } }


#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0xb4c77246, 0x1855, 0x4f4f, { 0xb7, 0xb1, 0x1, 0x4b, 0x7d, 0xda, 0x29, 0x41 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_BUILD_DEVICE_PATH_CONFORMANCE_AUTO_GUID \
  { 0xe13aeea0, 0x104f, 0x4a54, { 0x8c, 0x5b, 0xa8, 0x34, 0x4a, 0x99, 0x55, 0xe2 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0x8a2ebb7, 0x309f, 0x4587, { 0x80, 0xe, 0xe5, 0xa5, 0x28, 0x9d, 0xd, 0x1 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_RESET_TARGET_LUN_CONFORMANCE_AUTO_GUID \
  { 0x7608672a, 0x98f1, 0x485c, { 0x8e, 0x11, 0x19, 0x5a, 0x7e, 0x2c, 0xc8, 0x9b } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_GET_NEXT_TARGET_CONFORMANCE_AUTO_GUID \
  { 0x5b7ee5e0, 0xcee, 0x4981, { 0xa2, 0x83, 0x35, 0x37, 0x68, 0xe4, 0xcc, 0xf5 } }

#define EXT_SCSI_PASS_THRU_PROTOCOL_PASS_THRU_CONFORMANCE_AUTO_GUID \
  { 0xab534381, 0x9a15, 0x4de2, { 0xae, 0x98, 0x83, 0x88, 0x87, 0xe3, 0xdc, 0x3a } }

#endif

