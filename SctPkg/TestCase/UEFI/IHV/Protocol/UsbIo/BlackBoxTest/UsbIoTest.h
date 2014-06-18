/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
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

#define IHV_USB_IO_PROTOCOL_GUID  \
  { 0xcea4b8b1, 0x36ef, 0x43b1, { 0x8e, 0x8d, 0x7e, 0xe0, 0x47, 0xc3, 0x1e, 0xaf } }

//
// Definitions
//
#define USB_IO_USBCONTROLTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0x79dba639, 0x6436, 0x4e18, { 0x96, 0xe2, 0x44, 0x64, 0x26, 0x9d, 0x9d, 0x60 } }
#define USB_IO_USBBULKTRANSFER_CONFORMANCE_AUTO_GUID  \
  { 0x1e17aa36, 0x334e, 0x490d, { 0x91, 0x6e, 0xe7, 0x39, 0x99, 0x2, 0x7b, 0xe8 } }
#define USB_IO_USBASYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0x49cccafe, 0xe883, 0x4f7c, { 0x94, 0x91, 0xd3, 0xe6, 0x78, 0xdd, 0x9e, 0x4f } }
#define USB_IO_USBSYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0x633d9926, 0x645a, 0x4963, { 0xa6, 0xd7, 0x51, 0x19, 0xac, 0x88, 0xea, 0x40 } }
#define USB_IO_USBASYNCISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0x90c8eaca, 0x11d7, 0x49d9, { 0x86, 0xdd, 0xc6, 0xd, 0x30, 0x1d, 0xec, 0x90 } }
#define USB_IO_USBISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID \
  { 0x2bee890c, 0x26cf, 0x402c, { 0xa4, 0xa3, 0x87, 0x45, 0xc7, 0x1, 0x2, 0x65 } }
#define USB_IO_USBGETDEVICEDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  { 0x223a11ca, 0xf778, 0x4b0c, { 0xa0, 0x2d, 0xcb, 0xac, 0x87, 0x57, 0xbd, 0x75 } }
#define USB_IO_USBGETCONFIGDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  { 0x90560d0, 0xb3d3, 0x4b7c, { 0x97, 0x13, 0x99, 0x48, 0x91, 0xe, 0xe1, 0xf5 } }
#define USB_IO_USBGETINTERFACEDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  { 0xc27e3e7, 0x47d7, 0x41ba, { 0xa3, 0x65, 0x45, 0xbf, 0x55, 0x5f, 0xa6, 0xd } }
#define USB_IO_USBGETENDPOINTDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  { 0x6ff41e78, 0x5829, 0x4dc3, { 0x89, 0x95, 0x91, 0xb9, 0x2c, 0xf5, 0xae, 0xe4 } }
#define USB_IO_USBPORTRESET_CONFORMANCE_AUTO_GUID \
  { 0x75cdc9eb, 0x2133, 0x42da, { 0x9f, 0x89, 0x85, 0x47, 0x38, 0x59, 0xbd, 0x90 } }
#define USB_IO_USBGETSTRINGDESCRIPTOR_CONFORMANCE_AUTO_GUID \
  { 0x41e5ad2d, 0xcc4f, 0x4a1b, { 0x81, 0x6b, 0x78, 0x6d, 0x20, 0xca, 0xbb, 0x5 } }


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
UsbControlTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
UsbBulkTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3
//
EFI_STATUS
UsbAsyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.4
//
EFI_STATUS
UsbSyncInterruptTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.x
//
EFI_STATUS
UsbAsyncIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.x
//
EFI_STATUS
UsbIsochronousTransferConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.5
//
EFI_STATUS
UsbGetDeviceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.6
//
EFI_STATUS
UsbGetConfigDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.7
//
EFI_STATUS
UsbGetInterfaceDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.8
//
EFI_STATUS
UsbGetEndpointDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.9
//
EFI_STATUS
UsbPortResetConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.10
//
EFI_STATUS
UsbGetStringDescriptorConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
InitializeBBTestUsbIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestUsbIoUnload (
  IN EFI_HANDLE           ImageHandle
  );

#endif
