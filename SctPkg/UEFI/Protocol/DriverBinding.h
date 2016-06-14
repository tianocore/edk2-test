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

  DriverBindingProtocol.h

Abstract:

  EFI Driver Binding Protocol

--*/


#ifndef _EFI_DRIVER_BINDING_H_
#define _EFI_DRIVER_BINDING_H_

//
// Global ID for the ControllerHandle Driver Protocol
//
#define EFI_DRIVER_BINDING_PROTOCOL_GUID \
  { \
    0x18a031ab, 0xb443, 0x4d1a, 0xa5, 0xc0, 0xc, 0x9, 0x26, 0x1e, 0x9f, 0x71 \
  }

typedef struct _EFI_DRIVER_BINDING_PROTOCOL EFI_DRIVER_BINDING_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_SUPPORTED) (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  )
/*++

  Routine Description:
    Test to see if this driver supports ControllerHandle.

  Arguments:
    This                - Protocol instance pointer.
    ControllerHandle    - Handle of device to test
    RemainingDevicePath - Optional parameter use to pick a specific child
                          device to start.

  Returns:
    EFI_SUCCESS         - This driver supports this device
    EFI_ALREADY_STARTED - This driver is already running on this device
    other               - This driver does not support this device

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_START) (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               * RemainingDevicePath OPTIONAL
  )
/*++

  Routine Description:
    Start this driver on ControllerHandle.

  Arguments:
    This                - Protocol instance pointer.
    ControllerHandle    - Handle of device to bind driver to
    RemainingDevicePath - Optional parameter use to pick a specific child
                          device to start.

  Returns:
    EFI_SUCCESS         - This driver is added to ControllerHandle
    EFI_ALREADY_STARTED - This driver is already running on ControllerHandle
    other               - This driver does not support this device

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_STOP) (
  IN EFI_DRIVER_BINDING_PROTOCOL            * This,
  IN  EFI_HANDLE                            ControllerHandle,
  IN  UINTN                                 NumberOfChildren,
  IN  EFI_HANDLE                            * ChildHandleBuffer
  )
/*++

  Routine Description:
    Stop this driver on ControllerHandle.

  Arguments:
    This              - Protocol instance pointer.
    ControllerHandle  - Handle of device to stop driver on
    NumberOfChildren  - Number of Handles in ChildHandleBuffer. If number of
                        children is zero stop the entire bus driver.
    ChildHandleBuffer - List of Child Handles to Stop.

  Returns:
    EFI_SUCCESS         - This driver is removed ControllerHandle
    other               - This driver was not removed from this device

--*/
;

//
// Interface structure for the ControllerHandle Driver Protocol
//
struct _EFI_DRIVER_BINDING_PROTOCOL {
  EFI_DRIVER_BINDING_SUPPORTED  Supported;
  EFI_DRIVER_BINDING_START      Start;
  EFI_DRIVER_BINDING_STOP       Stop;
  UINT32                        Version;
  EFI_HANDLE                    ImageHandle;
  EFI_HANDLE                    DriverBindingHandle;
};

extern EFI_GUID gBlackBoxEfiDriverBindingProtocolGuid;

#endif
