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
  UsbIoTest.h

Abstract:
  Header file for Usb I/O Protocol Interface testing.

--*/

#ifndef _USB_IO_TEST_H
#define _USB_IO_TEST_H


#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/UsbIo.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#define USB_IO_TEST_REVISION 0x00010001

//
// Definitions
//
#define USB_IO_USBCONTROLTRANSFER_CONFORMANCE_AUTO_GUID \
  {0xba920a1f,0xdda9,0x4adb, {0xa6,0x67,0x1c,0x74,0x28,0x4e,0xed,0xc0}}
#define USB_IO_USBBULKTRANSFER_CONFORMANCE_AUTO_GUID  \
  {0x10b21512,0x9f9e,0x4b9d, {0xb8,0x99,0x32,0xfb,0xb9,0x86,0x08,0x92}}
#define USB_IO_USBASYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  {0x8e2c14fe,0x9ed9,0x4365, {0xa9,0xf1,0x51,0x9e,0xcf,0xe6,0x7a,0x3a}}
#define USB_IO_USBSYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  {0xe9fe1709,0x17be,0x40f9, {0xb3,0xc2,0x87,0x56,0xa1,0x90,0xd4,0xa2}}
#define USB_IO_USBASYNCISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  {0xcf24b302,0xe529,0x4085, {0xbf,0x16,0x89,0xad,0x79,0x25,0xba,0xca}}
#define USB_IO_USBISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  {0xb5052347,0x1bb1,0x49af, {0xa8,0xe0,0xdb,0xaa,0x8e,0x2f,0x28,0x23}}
#define USB_IO_USBGETDEVICEDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0x75d43e12,0x1268,0x426a, {0xba,0x46,0xf6,0x9a,0xb7,0xd0,0xf1,0x66}}
#define USB_IO_USBGETCONFIGDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0xa0d33285,0x3071,0x4cba, {0x8a,0x57,0x2e,0xec,0x14,0xfc,0x49,0x14}}
#define USB_IO_USBGETINTERFACEDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0x4ce53ccb,0x6431,0x4bde, {0x90,0x20,0xf4,0xbf,0xbe,0xd8,0x34,0xcd}}
#define USB_IO_USBGETENDPOINTDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0xcb32ea3d,0x468d,0x4bd7, {0x96,0xde,0x30,0xec,0x30,0x87,0xc9,0xee}}
#define USB_IO_USBPORTRESET_CONFORMANCE_AUTO_GUID \
  {0x1b8d123a,0x807a,0x433d, {0x9f,0x09,0xc5,0x68,0x2e,0xc1,0xf8,0x2c}}
#define USB_IO_USBGETSTRINGDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  {0x73f1b45f,0x9426,0x4512, {0xb5,0x3e,0xbe,0x1f,0x13,0x72,0x9c,0x92}}


typedef struct {
  //
  // Put Interface at the first field to make it easy to distinguish BOT/CBI Protocol instance
  //
  EFI_USB_INTERFACE_DESCRIPTOR  *Interface;
  EFI_USB_ENDPOINT_DESCRIPTOR   *BulkInEndpoint;
  EFI_USB_ENDPOINT_DESCRIPTOR   *BulkOutEndpoint;
  UINT32                        CbwTag;
  EFI_USB_IO_PROTOCOL           *UsbIo;
} USB_BOT_PROTOCOL;


typedef struct {
  UINT8             OpCode;
  UINT8             Lun;            ///< Lun (High 3 bits)
  UINT8             Lba[4];         ///< Logical block address
  UINT8             Reserved0;
  UINT8             TransferLen[2]; ///< Transfer length
  UINT8             Reserverd1;
  UINT8             Pad[2];
} USB_BOOT_READ10_CMD;

//
// The opcodes of various USB boot commands:
// INQUIRY/REQUEST_SENSE are "No Timeout Commands" as specified
// by Multi-Media Commands (MMC) set.
// Others are "Group 1 Timeout Commands". That is,
// they should be retried if driver is ready. 
//
#define USB_BOOT_INQUIRY_OPCODE         0x12
#define USB_BOOT_REQUEST_SENSE_OPCODE   0x03
#define USB_BOOT_MODE_SENSE10_OPCODE    0x5A
#define USB_BOOT_READ_CAPACITY_OPCODE   0x25
#define USB_BOOT_TEST_UNIT_READY_OPCODE 0x00
#define USB_BOOT_READ10_OPCODE          0x28
#define USB_BOOT_WRITE10_OPCODE         0x2A


//
// Usb Bulk-Only class specfic request
//
#define USB_BOT_RESET_REQUEST    0xFF       ///< Bulk-Only Mass Storage Reset
#define USB_BOT_GETLUN_REQUEST   0xFE       ///< Get Max Lun
#define USB_BOT_CBW_SIGNATURE    0x43425355 ///< dCBWSignature, tag the packet as CBW
#define USB_BOT_CSW_SIGNATURE    0x53425355 ///< dCSWSignature, tag the packet as CSW
#define USB_BOT_MAX_LUN          0x0F       ///< Lun number is from 0 to 15
#define USB_BOT_MAX_CMDLEN       16         ///< Maxium number of command from command set

//
// Usb mass storage protocol code, specify the transport protocol
//
#define USB_MASS_STORE_CBI0     0x00 ///< CBI protocol with command completion interrupt
#define USB_MASS_STORE_CBI1     0x01 ///< CBI protocol without command completion interrupt
#define USB_MASS_STORE_BOT      0x50 ///< Bulk-Only Transport

//
// USB endpoint types: 00: control, 01: isochronous, 10: bulk, 11: interrupt
//
#define USB_ENDPOINT_CONTROL    0x00
#define USB_ENDPOINT_ISO        0x01
#define USB_ENDPOINT_BULK       0x02
#define USB_ENDPOINT_INTERRUPT  0x03

#define USB_ENDPOINT_TYPE_MASK  0x03
#define USB_ENDPOINT_DIR_IN     0x80

#define  BIT0     0x00000001
#define  BIT1     0x00000002
#define  BIT2     0x00000004
#define  BIT3     0x00000008
#define  BIT4     0x00000010
#define  BIT5     0x00000020
#define  BIT6     0x00000040
#define  BIT7     0x00000080

#define USB_IS_IN_ENDPOINT(EndPointAddr)      (((EndPointAddr) & BIT7) == BIT7)
#define USB_IS_OUT_ENDPOINT(EndPointAddr)     (((EndPointAddr) & BIT7) == 0)
#define USB_IS_BULK_ENDPOINT(Attribute)       (((Attribute) & (BIT0 | BIT1)) == USB_ENDPOINT_BULK)
#define USB_IS_INTERRUPT_ENDPOINT(Attribute)  (((Attribute) & (BIT0 | BIT1)) == USB_ENDPOINT_INTERRUPT)
#define USB_IS_ERROR(Result, Error)           (((Result) & (Error)) != 0)

#pragma pack(1)
///
/// The CBW (Command Block Wrapper) structures used by the USB BOT protocol.
///
typedef struct {
  UINT32              Signature;
  UINT32              Tag;
  UINT32              DataLen;  ///< Length of data between CBW and CSW
  UINT8               Flag;     ///< Bit 7, 0 ~ Data-Out, 1 ~ Data-In
  UINT8               Lun;      ///< Lun number. Bits 0~3 are used
  UINT8               CmdLen;   ///< Length of the command. Bits 0~4 are used
  UINT8               CmdBlock[USB_BOT_MAX_CMDLEN];
} USB_BOT_CBW;

///
/// The and CSW (Command Status Wrapper) structures used by the USB BOT protocol.
///
typedef struct {
  UINT32              Signature;
  UINT32              Tag;
  UINT32              DataResidue;
  UINT8               CmdStatus;
} USB_BOT_CSW;
#pragma pack()


//
// IPF Specific Functions
//
typedef struct {
  UINT64                    Status;
  UINT64                    r9;
  UINT64                    r10;
  UINT64                    r11;
} PAL_CALL_RETURN;



//
// Prototypes
//

//
// TDS 5.1
//
EFI_STATUS
EFIAPI
UsbControlTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbControlTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.2
//
EFI_STATUS
EFIAPI
UsbBulkTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbBulkTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.3
//
EFI_STATUS
EFIAPI
UsbAsyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbAsyncInterruptTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.4
//
EFI_STATUS
EFIAPI
UsbSyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbSyncInterruptTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.x
//
EFI_STATUS
EFIAPI
UsbAsyncIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbAsyncIsochronousTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.x
//
EFI_STATUS
EFIAPI
UsbIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbIsochronousTransfer() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.5
//
EFI_STATUS
EFIAPI
UsbGetDeviceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetDeviceDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.6
//
EFI_STATUS
EFIAPI
UsbGetConfigDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetConfigDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.7
//
EFI_STATUS
EFIAPI
UsbGetInterfaceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetInterfaceDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.8
//
EFI_STATUS
EFIAPI
UsbGetEndpointDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetEndpointDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.9
//
EFI_STATUS
EFIAPI
UsbPortResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbPortReset() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

//
// TDS 5.10
//
EFI_STATUS
EFIAPI
UsbGetStringDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entry point for UsbIo->UsbGetStringDescriptor() Conformance Auto Test.

Arguments:

  This                 - A pointer to the EFI_BB_TEST_PROTOCOL instance.
  ClientInterface      - A pointer to the interface to be tested.
  TestLevel            - Test "thoroughness" control.
  SupportHandle        - A handle containing support protocols.

Returns:

  EFI_SUCCESS          - Successfully.
  Other value          - Something failed.

--*/
;

EFI_STATUS
EFIAPI
InitializeBBTestUsbIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
/*++

Routine Description:

  Creates/installs the BlackBox Interface and the Entry Point list.

Arguments:

 ImageHandle             - The image handle.
 SystemTable             - The system table.
 

Returns:

 EFI_SUCCESS             - The interface was installed successfully.
 EFI_OUT_OF_RESOURCES    - Failed due to the lack of resources.
 EFI_INVALID_PARAMETER   - One of parameters is invalid.

--*/
;

EFI_STATUS
EFIAPI
BBTestUsbIoUnload (
  IN EFI_HANDLE           ImageHandle
  )
/*++

Routine Description:

  Unloads the BlackBox Interface and the Entry Point list.

Arguments:

  ImageHandle      - The image handle.

Returns:

  EFI_SUCCESS      - The interface was uninstalled successfully.

--*/
;

#endif
