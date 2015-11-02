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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  UsbIoProtocol.h

Abstract:

  UsbIo Protocol (define according to the EFI Spec 1.1 )

--*/

#ifndef _EFI_USB_IO_FOR_TEST_H_
#define _EFI_USB_IO_FOR_TEST_H_

#include <IndustryStandard/Usb.h>

#define EFI_USB_IO_PROTOCOL_GUID \
  {0x2B2F68D6,0x0CD2,0x44cf,0x8E,0x8B,0xBB,0xA2,0x0B,0x1B,0x5B,0x75}

typedef struct _EFI_USB_IO_PROTOCOL EFI_USB_IO_PROTOCOL;;

//
// Related Definition for EFI USB I/O protocol
//

//
// USB standard descriptors and reqeust
//
typedef USB_DEVICE_REQUEST        EFI_USB_DEVICE_REQUEST;
typedef USB_DEVICE_DESCRIPTOR     EFI_USB_DEVICE_DESCRIPTOR;
typedef USB_CONFIG_DESCRIPTOR     EFI_USB_CONFIG_DESCRIPTOR;
typedef USB_INTERFACE_DESCRIPTOR  EFI_USB_INTERFACE_DESCRIPTOR;
typedef USB_ENDPOINT_DESCRIPTOR   EFI_USB_ENDPOINT_DESCRIPTOR;

///
/// USB data transfer direction
///
typedef enum {
  EfiUsbDataIn,
  EfiUsbDataOut,
  EfiUsbNoData
} EFI_USB_DATA_DIRECTION;

typedef
EFI_STATUS
(EFIAPI * EFI_ASYNC_USB_TRANSFER_CALLBACK) (
  IN VOID   *Data,
  IN UINTN  DataLength,
  IN VOID   *Context,
  IN UINT32 Status
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_CONTROL_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL    *This,
  IN EFI_USB_DEVICE_REQUEST *Request,
  IN EFI_USB_DATA_DIRECTION Direction,
  IN UINT32                 Timeout,
  IN OUT VOID               *Data OPTIONAL,
  IN UINTN                  DataLength OPTIONAL,
  OUT UINT32                *Status
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_BULK_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL    *This,
  IN UINT8                  DeviceEndpoint,
  IN OUT VOID               *Data,
  IN OUT UINTN              *DataLength,
  IN UINTN                  Timeout,
  OUT UINT32                *Status
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_ASYNC_INTERRUPT_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL              *This,
  IN UINT8                            DeviceEndpoint,
  IN BOOLEAN                          IsNewTransfer,
  IN UINTN                            PollingInterval OPTIONAL,
  IN UINTN                            DataLength OPTIONAL,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  InterruptCallBack OPTIONAL,
  IN VOID                             *Context OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_SYNC_INTERRUPT_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL    *This,
  IN UINT8                  DeviceEndpoint,
  IN OUT VOID               *Data,
  IN OUT UINTN              *DataLength,
  IN UINTN                  Timeout,
  OUT UINT32                *Status
);

typedef
EFI_STATUS
(EFIAPI * EFI_USB_IO_ISOCHRONOUS_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL  *This,
  IN UINT8                DeviceEndpoint,
  IN OUT VOID             *Data,
  IN UINTN                DataLength,
  OUT UINT32              *Status
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_ASYNC_ISOCHRONOUS_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL              *This,
  IN UINT8                            DeviceEndpoint,
  IN OUT VOID                         *Data,
  IN UINTN                            DataLength,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  IsochronousCallBack,
  IN VOID                             *Context OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_GET_DEVICE_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL        *This,
  OUT EFI_USB_DEVICE_DESCRIPTOR *DeviceDescriptor
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_GET_CONFIG_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL        *This,
  OUT EFI_USB_CONFIG_DESCRIPTOR *ConfigurationDescriptor
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_GET_INTERFACE_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL            *This,
  OUT EFI_USB_INTERFACE_DESCRIPTOR  *InterfaceDescriptor
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_GET_ENDPOINT_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL            *This,
  IN UINT8                          EndpointIndex,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR   *EndpointDescriptor
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_GET_STRING_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL  *This,
  IN UINT16               LangID,
  IN UINT8                StringID,
  OUT CHAR16              **String
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_GET_SUPPORTED_LANGUAGES) (
  IN EFI_USB_IO_PROTOCOL  *This,
  OUT UINT16              **LangIDTable,
  OUT UINT16              *TableSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_IO_PORT_RESET) (
  IN EFI_USB_IO_PROTOCOL  *This
);

struct _EFI_USB_IO_PROTOCOL {
  EFI_USB_IO_CONTROL_TRANSFER           UsbControlTransfer;
  EFI_USB_IO_BULK_TRANSFER              UsbBulkTransfer;
  EFI_USB_IO_ASYNC_INTERRUPT_TRANSFER   UsbAsyncInterruptTransfer;
  EFI_USB_IO_SYNC_INTERRUPT_TRANSFER    UsbSyncInterruptTransfer;
  EFI_USB_IO_ISOCHRONOUS_TRANSFER       UsbIsochronousTransfer;
  EFI_USB_IO_ASYNC_ISOCHRONOUS_TRANSFER UsbAsyncIsochronousTransfer;
  EFI_USB_IO_GET_DEVICE_DESCRIPTOR      UsbGetDeviceDescriptor;
  EFI_USB_IO_GET_CONFIG_DESCRIPTOR      UsbGetConfigDescriptor;
  EFI_USB_IO_GET_INTERFACE_DESCRIPTOR   UsbGetInterfaceDescriptor;
  EFI_USB_IO_GET_ENDPOINT_DESCRIPTOR    UsbGetEndpointDescriptor;
  EFI_USB_IO_GET_STRING_DESCRIPTOR      UsbGetStringDescriptor;
  EFI_USB_IO_GET_SUPPORTED_LANGUAGES    UsbGetSupportedLanguages;
  EFI_USB_IO_PORT_RESET                 UsbPortReset;
};

#endif
