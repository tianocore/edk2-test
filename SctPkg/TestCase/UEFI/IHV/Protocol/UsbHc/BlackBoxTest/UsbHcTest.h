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

#define IHV_USB_HC_PROTOCOL_GUID \
  { 0x91c189f3, 0xc398, 0x47df, { 0xaa, 0x44, 0x15, 0xd0, 0xfd, 0x6e, 0xde, 0xad } }

//
// Definitions
//
#define USB_HC_RESET_BASIC_AUTO_GUID \
  { 0x739ad31a, 0x5295, 0x4286, { 0x87, 0xd3, 0x86, 0x80, 0xfb, 0x65, 0xb5, 0x6c } }
#define USB_HC_GETSTATE_BASIC_AUTO_GUID  \
  { 0xeddb87b0, 0x7af, 0x4866, { 0x82, 0x98, 0x77, 0xc, 0xfc, 0x25, 0x32, 0x44 } }
#define USB_HC_SETSTATE_BASIC_AUTO_GUID \
  { 0x84858c33, 0x854, 0x4791, { 0xaa, 0x1e, 0x52, 0x76, 0x55, 0xe, 0xda, 0xa2 } }
#define USB_HC_GETROOTHUBPORTNUMBER_BASIC_MANUAL_GUID \
  { 0x813054a2, 0xad5e, 0x45a2, { 0x91, 0x53, 0xea, 0x79, 0x2c, 0x4a, 0x69, 0x3e } }
#define USB_HC_GETROOTHUBPORTSTATUS_BASIC_AUTO_GUID \
  { 0x3b051f39, 0x7f55, 0x4b41, { 0x8a, 0xbc, 0x57, 0xc8, 0xc0, 0x3d, 0x22, 0x26 } }
#define USB_HC_GETROOTHUBPORTSTATUS_BASIC_MANUAL_GUID \
  { 0xdadbca20, 0x9471, 0x469f, { 0x9c, 0xa8, 0x2, 0x4c, 0xed, 0xf5, 0x5b, 0x94 } }
#define USB_HC_SETROOTHUBPORTFEATURE_BASIC_AUTO_GUID \
  { 0x7047a247, 0xfadf, 0x4f55, { 0x87, 0xf1, 0xa3, 0xd8, 0x69, 0x7c, 0x9e, 0xdd } }
#define USB_HC_CLEARROOTHUBPORTFEATURE_BASIC_AUTO_GUID \
  { 0xddcc90e4, 0xed5, 0x454b, { 0x96, 0xf9, 0x4, 0xc3, 0x80, 0xea, 0x3d, 0xa } }
#define USB_HC_CLEARROOTHUBPORTFEATURE_BASIC_MANUAL_GUID \
  { 0xf36234a9, 0xfb05, 0x42e8, { 0x97, 0x4f, 0xf3, 0x8c, 0xee, 0x73, 0x36, 0x60 } }
#define USB_HC_RESET_CONFORMANCE_AUTO_GUID \
  { 0x741f9b76, 0x9c19, 0x4e06, { 0x94, 0x3f, 0x1c, 0xbf, 0x13, 0x24, 0x2e, 0x8a } }
#define USB_HC_GETSTATE_CONFORMANCE_AUTO_GUID \
  { 0xeda3d06a, 0x7824, 0x4c45, { 0x90, 0x4b, 0x7c, 0x18, 0x59, 0x29, 0xc0, 0x4a } }
#define USB_HC_SETSTATE_CONFORMANCE_AUTO_GUID \
  { 0x9f1efd22, 0xd62d, 0x4cc3, { 0x8a, 0x59, 0x2, 0x37, 0x36, 0x2c, 0x20, 0x5c } }
#define USB_HC_CONTROLTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0xa9fc2421, 0x5051, 0x4bf3, { 0x8c, 0x61, 0x54, 0x87, 0xd8, 0x14, 0xc4, 0x28 } }
#define USB_HC_BULKTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0xd87fb7f8, 0x7bfe, 0x4d15, { 0x95, 0xe1, 0x6a, 0xa1, 0xbf, 0xa5, 0x71, 0x65 } }
#define USB_HC_ASYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0xdbdc475b, 0x9df0, 0x4ccd, { 0xa1, 0x61, 0x0, 0x8c, 0x9b, 0xea, 0x71, 0xb3 } }
#define USB_HC_SYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0x95abe7f8, 0xfbd2, 0x4c47, { 0xb0, 0x3c, 0x1c, 0x16, 0x96, 0x81, 0xce, 0xb0 } }
#define USB_HC_ASYNCISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0x15c3d0bc, 0xd591, 0x45c2, { 0x8c, 0xcd, 0x32, 0x7d, 0xff, 0x2e, 0x3a, 0x2 } }
#define USB_HC_ISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0xdf0da8e0, 0x6d5f, 0x4431, { 0xb1, 0x16, 0xe0, 0x51, 0xa9, 0xb5, 0xc0, 0xb5 } }
#define USB_HC_GETROOTHUBPORTNUMBER_CONFORMANCE_AUTO_GUID \
  { 0xce4ae28b, 0x1aca, 0x41f7, { 0x87, 0x96, 0xbb, 0x60, 0xb8, 0xf3, 0x8, 0xec } }
#define USB_HC_GETROOTHUBPORTSTATUS_CONFORMANCE_AUTO_GUID \
  { 0x7cd3afc, 0xa4fa, 0x4c5b, { 0xae, 0xd2, 0x8f, 0x53, 0x5a, 0xaa, 0x9, 0x71 } }
#define USB_HC_SETROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID \
  { 0x55136bfb, 0x539a, 0x4a43, { 0xae, 0xef, 0xf9, 0x5e, 0x62, 0x2e, 0xe3, 0x5b } }
#define USB_HC_CLEARROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID \
{ 0x99e6f17a, 0xe68f, 0x4288, { 0xa1, 0x6b, 0x66, 0x7b, 0x10, 0xf5, 0xf0, 0x56 } }

//
// Prototypes
//

//
// TDS 4.1.1
//
EFI_STATUS
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
