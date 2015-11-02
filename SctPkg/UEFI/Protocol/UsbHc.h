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

  UsbHcProtocol.h

Abstract:

  UsbHc Protocol (define according to the EFI Spec 1.1 )

--*/

#ifndef _EFI_USB_HC_FOR_TEST_H_
#define _EFI_USB_HC_FOR_TEST_H_

#include <UEFI/Protocol/UsbIo.h>

#define EFI_USB_HC_PROTOCOL_GUID \
  {0xF5089266,0x1AA0,0x4953,0x97,0xD8,0x56,0x2F,0x8A,0x73,0xB5,0x19}

typedef struct _EFI_USB_HC_PROTOCOL EFI_USB_HC_PROTOCOL;;

typedef enum {
  EfiUsbHcStateHalt,
  EfiUsbHcStateOperational,
  EfiUsbHcStateSuspend,
  EfiUsbHcStateMaximum
} EFI_USB_HC_STATE;

typedef struct {
  UINT16          PortStatus;        ///< Contains current port status bitmap.
  UINT16          PortChangeStatus;  ///< Contains current port status change bitmap.
} EFI_USB_PORT_STATUS;

///
/// Usb port features value
/// Each value indicates its bit index in the port status and status change bitmaps,
/// if combines these two bitmaps into a 32-bit bitmap.
///
typedef enum {
  EfiUsbPortEnable            = 1,
  EfiUsbPortSuspend           = 2,
  EfiUsbPortReset             = 4,
  EfiUsbPortPower             = 8,
  EfiUsbPortOwner             = 13,
  EfiUsbPortConnectChange     = 16,
  EfiUsbPortEnableChange      = 17,
  EfiUsbPortSuspendChange     = 18,
  EfiUsbPortOverCurrentChange = 19,
  EfiUsbPortResetChange       = 20
} EFI_USB_PORT_FEATURE;

#define EFI_USB_HC_RESET_GLOBAL 0x0001
#define EFI_USB_HC_RESET_HOST_CONTROLLER 0x0002


typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_RESET) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT16               Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_GET_STATE) (
  IN EFI_USB_HC_PROTOCOL  *This,
  OUT EFI_USB_HC_STATE    *State
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_SET_STATE) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN EFI_USB_HC_STATE     State
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_CONTROL_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL    *This,
  IN UINT8                  DeviceAddress,
  IN BOOLEAN                IsSlowDevice,
  IN UINT8                  MaximumPacketLength,
  IN EFI_USB_DEVICE_REQUEST *Request,
  IN EFI_USB_DATA_DIRECTION TransferDirection,
  IN OUT VOID               *Data OPTIONAL,
  IN OUT UINTN              *DataLength         OPTIONAL,
  IN UINTN                  TimeOut,
  OUT UINT32                *TransferResult
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_BULK_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                DeviceAddress,
  IN UINT8                EndPointAddress,
  IN UINT8                MaximumPacketLength,
  IN OUT VOID             *Data,
  IN OUT UINTN            *DataLength,
  IN OUT UINT8            *DataToggle,
  IN UINTN                TimeOut,
  OUT UINT32              *TransferResult
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL              *This,
  IN UINT8                            DeviceAddress,
  IN UINT8                            EndPointAddress,
  IN BOOLEAN                          IsSlowDevice,
  IN UINT8                            MaxiumPacketLength,
  IN BOOLEAN                          IsNewTransfer,
  IN OUT UINT8                        *DataToggle,
  IN UINTN                            PollingInterval OPTIONAL,
  IN UINTN                            DataLength OPTIONAL,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  CallBackFunction OPTIONAL,
  IN VOID                             *Context OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_SYNC_INTERRUPT_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                DeviceAddress,
  IN UINT8                EndPointAddress,
  IN BOOLEAN              IsSlowDevice,
  IN UINT8                MaximumPacketLength,
  IN OUT VOID             *Data,
  IN OUT UINTN            *DataLength,
  IN OUT UINT8            *DataToggle,
  IN UINTN                TimeOut,
  OUT UINT32              *TransferResult
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_ISOCHRONOUS_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                DeviceAddress,
  IN UINT8                EndPointAddress,
  IN UINT8                MaximumPacketLength,
  IN OUT VOID             *Data,
  IN UINTN                DataLength,
  OUT UINT32              *TransferResult
);

typedef
EFI_STATUS
(EFIAPI * EFI_USB_HC_PROTOCOL_ASYNC_ISOCHRONOUS_TRANSFER) (
  IN EFI_USB_HC_PROTOCOL              *This,
  IN UINT8                            DeviceAddress,
  IN UINT8                            EndPointAddress,
  IN UINT8                            MaximumPacketLength,
  IN OUT VOID                         *Data,
  IN UINTN                            DataLength,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  IsochronousCallBack,
  IN VOID                             *Context OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_GET_ROOTHUB_PORT_NUMBER) (
  IN EFI_USB_HC_PROTOCOL  *This,
  OUT UINT8               *PortNumber
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_GET_ROOTHUB_PORT_STATUS) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                PortNumber,
  OUT EFI_USB_PORT_STATUS *PortStatus
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_SET_ROOTHUB_PORT_FEATURE) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                PortNumber,
  IN EFI_USB_PORT_FEATURE PortFeature
);

typedef
EFI_STATUS
(EFIAPI *EFI_USB_HC_PROTOCOL_CLEAR_ROOTHUB_PORT_FEATURE) (
  IN EFI_USB_HC_PROTOCOL  *This,
  IN UINT8                PortNumber,
  IN EFI_USB_PORT_FEATURE PortFeature
);

struct _EFI_USB_HC_PROTOCOL {
  EFI_USB_HC_PROTOCOL_RESET                       Reset;
  EFI_USB_HC_PROTOCOL_GET_STATE                   GetState;
  EFI_USB_HC_PROTOCOL_SET_STATE                   SetState;
  EFI_USB_HC_PROTOCOL_CONTROL_TRANSFER            ControlTransfer;
  EFI_USB_HC_PROTOCOL_BULK_TRANSFER               BulkTransfer;
  EFI_USB_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER    AsyncInterruptTransfer;
  EFI_USB_HC_PROTOCOL_SYNC_INTERRUPT_TRANSFER     SyncInterruptTransfer;
  EFI_USB_HC_PROTOCOL_ISOCHRONOUS_TRANSFER        IsochronousTransfer;
  EFI_USB_HC_PROTOCOL_ASYNC_ISOCHRONOUS_TRANSFER  AsyncIsochronousTransfer;
  EFI_USB_HC_PROTOCOL_GET_ROOTHUB_PORT_NUMBER     GetRootHubPortNumber;
  EFI_USB_HC_PROTOCOL_GET_ROOTHUB_PORT_STATUS     GetRootHubPortStatus;
  EFI_USB_HC_PROTOCOL_SET_ROOTHUB_PORT_FEATURE    SetRootHubPortFeature;
  EFI_USB_HC_PROTOCOL_CLEAR_ROOTHUB_PORT_FEATURE  ClearRootHubPortFeature;
  UINT16                                          MajorRevision;
  UINT16                                          MinorRevision;
};

extern EFI_GUID gBlackBoxEfiUsbHcProtocolGuid;

#endif
