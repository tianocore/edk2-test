/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  UsbHcTest.h

Abstract:
  Header file for Usb Host Controller Protocol Interface testing.

--*/

#ifndef _USB_HC_TEST_H
#define _USB_HC_TEST_H


#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/UsbHc.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#define USB_HC_TEST_REVISION 0x00010001

//
// Definitions
//
#define USB_HC_RESET_BASIC_AUTO_GUID \
  {0x7d9a00b1,0xf172,0x4a01, {0x82,0xb9,0x4c,0xaf,0x7d,0xb5,0xf1,0xd7}}
#define USB_HC_GETSTATE_BASIC_AUTO_GUID  \
  {0x562bd5ed,0xce71,0x4bdb, {0xbd,0x8d,0x25,0x40,0x43,0x08,0x9d,0xa6}}
#define USB_HC_SETSTATE_BASIC_AUTO_GUID \
  {0x69fbb8dc,0x9dbd,0x47f9, {0xb9,0x42,0xd9,0x21,0x32,0x2e,0x39,0x62}}
#define USB_HC_GETROOTHUBPORTNUMBER_BASIC_MANUAL_GUID \
  {0xaae92afa,0xf17b,0x456c, {0xa8,0x94,0xe3,0xaf,0xf7,0x9f,0x3a,0x06}}
#define USB_HC_GETROOTHUBPORTSTATUS_BASIC_AUTO_GUID \
  {0x39d80064,0x4cb5,0x41e9, {0x92,0x77,0xfd,0xc4,0x0d,0xad,0x41,0x63}}
#define USB_HC_GETROOTHUBPORTSTATUS_BASIC_MANUAL_GUID \
  {0x4db0442f,0xbf01,0x4eda, {0x8d,0x6f,0xb3,0x1a,0xa2,0x5f,0x0e,0x1a}}
#define USB_HC_SETROOTHUBPORTFEATURE_BASIC_AUTO_GUID \
  {0x83ea9028,0xd174,0x40b1, {0xb7,0xdb,0x47,0x45,0x9e,0x32,0x0e,0x71}}
#define USB_HC_CLEARROOTHUBPORTFEATURE_BASIC_AUTO_GUID \
  {0x4f9c0ee2,0x9941,0x43a6, {0xa7,0xfe,0x3f,0x0f,0xe6,0xb8,0x1b,0x35}}
#define USB_HC_CLEARROOTHUBPORTFEATURE_BASIC_MANUAL_GUID \
  {0x1b30c7ae,0x31ee,0x49ae, {0xbd,0x3c,0x7b,0x9e,0x3d,0x47,0xcc,0x2d}}
#define USB_HC_RESET_CONFORMANCE_AUTO_GUID \
  {0x708c4c00,0xda7c,0x43dc, {0x81,0x00,0xf2,0xac,0x33,0x51,0x2d,0xae}}
#define USB_HC_GETSTATE_CONFORMANCE_AUTO_GUID \
  {0x8f3f4030,0xd364,0x4d13, {0xab,0xb1,0x01,0xf5,0x40,0x13,0x15,0xcb}}
#define USB_HC_SETSTATE_CONFORMANCE_AUTO_GUID \
  {0xcd71a385,0x8269,0x4cd2, {0x96,0x0f,0x19,0xa4,0xb9,0x2b,0xcf,0x11}}
#define USB_HC_CONTROLTRANSFER_CONFORMANCE_AUTO_GUID \
  {0x37775660,0x9008,0x4833, {0xb7,0x63,0x51,0x6f,0x99,0x6c,0x2d,0xd6}}
#define USB_HC_BULKTRANSFER_CONFORMANCE_AUTO_GUID \
  {0x2703642f,0x6374,0x4e28, {0xae,0xe9,0xe4,0x46,0x2b,0x98,0x2b,0x5d}}
#define USB_HC_ASYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  {0x13241f1f,0x69a0,0x4058, {0x8c,0xbb,0x41,0x98,0x6f,0x7e,0x52,0x0b}}
#define USB_HC_SYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  {0xf9bc08fc,0x7418,0x417d, {0x8a,0x4d,0x6b,0xfe,0x3a,0x6d,0x44,0x79}}
#define USB_HC_ASYNCISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  {0x4c190471,0x7814,0x4e83, {0x87,0x45,0x82,0xed,0xf3,0xb0,0x34,0xc6}}
#define USB_HC_ISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  {0x9b2a839f,0x1029,0x4eaf, {0xa3,0xb7,0x5c,0xa0,0x89,0x06,0x4c,0x38}}
#define USB_HC_GETROOTHUBPORTNUMBER_CONFORMANCE_AUTO_GUID \
  {0x2ed308db,0xd601,0x4072, {0xa1,0xec,0x84,0x25,0x10,0x1c,0x68,0x42}}
#define USB_HC_GETROOTHUBPORTSTATUS_CONFORMANCE_AUTO_GUID \
  {0xa803eabd,0x3fc2,0x4b55, {0x82,0x89,0x02,0xa3,0x15,0x69,0x80,0xb4}}
#define USB_HC_SETROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID \
  {0x58e658ef,0x9203,0x4883, {0x8c,0xe6,0xe4,0x51,0x1d,0xfc,0xbb,0x97}}
#define USB_HC_CLEARROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID \
  {0x68cbb330,0x232a,0x471d, {0xbe,0x34,0x63,0xb9,0xb9,0x46,0x50,0x5f}}


//
// Prototypes
//

//
// TDS 4.1.1
//
EFI_STATUS
EFIAPI
UsbHcResetBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1.2
//
EFI_STATUS
EFIAPI
UsbHcGetStateBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1.3
//
EFI_STATUS
EFIAPI
UsbHcSetStateBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1.4
//
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortNumberBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1.5
//
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1.6
//
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1.7
//
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1.8
//
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureBasicAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1.9
//
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureBasicManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.1
//
EFI_STATUS
EFIAPI
UsbHcResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.2
//
EFI_STATUS
EFIAPI
UsbHcGetStateConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.3
//
EFI_STATUS
EFIAPI
UsbHcSetStateConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.4
//
EFI_STATUS
EFIAPI
UsbHcControlTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.5
//
EFI_STATUS
EFIAPI
UsbHcBulkTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.6
//
EFI_STATUS
EFIAPI
UsbHcAsyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.7
//
EFI_STATUS
EFIAPI
UsbHcSyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.x
//
EFI_STATUS
EFIAPI
UsbHcAsyncIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.x
//
EFI_STATUS
EFIAPI
UsbHcIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.8
//
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortNumberConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.9
//
EFI_STATUS
EFIAPI
UsbHcGetRootHubPortStatusConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.10
//
EFI_STATUS
EFIAPI
UsbHcSetRootHubPortFeatureConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2.11
//
EFI_STATUS
EFIAPI
UsbHcClearRootHubPortFeatureConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
InitializeBBTestUsbHc (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestUsbHcUnload (
  IN EFI_HANDLE           ImageHandle
  );

VOID StallForChangeDevice(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN UINTN Time
  );

VOID MaskTimerInterrupt();

VOID UnmaskTimerInterrupt();

BOOLEAN
AutoJudge(
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

#endif
