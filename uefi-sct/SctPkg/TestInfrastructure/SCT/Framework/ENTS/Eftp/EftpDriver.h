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
 
  EftpDriver.h
 
Abstract:
 
--*/

#ifndef _EFI_EFTP_DRIVER_H_
#define _EFI_EFTP_DRIVER_H_

#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (Eftp)

#include <Protocol/ComponentName.h>
#include <Protocol/ManagedNetwork.h>
#include <Protocol/ServiceBinding.h>

#define EFTP_SB_PRIVATE_SIGNATURE EFI_SIGNATURE_32 ('M', 'T', 'S', 'B')
#define EFTP_SB_PRIVATE_FROM_THIS(a) \
  CR ( \
  a, \
  EFTP_SERVICE_BINDING_PRIVATE, \
  ServiceBinding, \
  EFTP_SB_PRIVATE_SIGNATURE \
  )

//
// Private data used by eftp service binding protocol
//
typedef struct _EFTP_SERVICE_BINDING_PRIVATE {
  UINTN                         Signature;
  EFI_SERVICE_BINDING_PROTOCOL  ServiceBinding;

  //
  // The controller handle eftp service binding protocol is installed on
  //
  EFI_HANDLE                    ControllerHandle;

  //
  // The handle in this driver binding protocol. It is the image handle in most cases
  //
  EFI_HANDLE                    ImageHandle;

  //
  // The instance handle on which ManagedNetwork Protocol is installed.
  //
  EFI_HANDLE                    MnpChildHandle;

  //
  // This is the pre-allocated MNP protocol, will be consumed by first EFTP instance.
  //
  EFI_MANAGED_NETWORK_PROTOCOL  *ManagedNetwork;

  //
  // The configuration for the ManagedNetwork instance.
  // (synchronization needed)
  //
  //  EFI_MANAGED_NETWORK_CONFIG_DATA       MnpConfigData;
  //
  // data member used to manage the children created from eftp service binding protocol
  //
  UINT16                        ChildrenNum;
  NET_LIST_ENTRY                ChildrenList;
  NET_LOCK                      ChildrenListLock;
} EFTP_SERVICE_BINDING_PRIVATE;

EFI_STATUS
EFIAPI
EftpDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
/*++

Routine Description:

  Test to see if this driver supports ControllerHandle. 

Arguments:

  This                - Protocol instance pointer.
  Controller          - Handle of device to test.
  RemainingDevicePath - Optional parameter use to pick a specific child device to test.

Returns:

    EFI_SUCCES          - This driver supports this device
    other               - This driver does not support this device

--*/
;

EFI_STATUS
EFIAPI
EftpDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
/*++

Routine Description:

  Start the Eftp driver.

Arguments:

  This                    - Protocol instance pointer.
  Controller              - Handle of device to test.
  RemainingDevicePath     - Optional parameter use to pick a specific child device to start.

Returns:

  EFI_ALREADY_STARTED     - The device is already started.
  EFI_OUT_OF_RESOURCES    - No enough resource
  EFI_SUCCESS             - Successfully started the driver.

--*/
;

EFI_STATUS
EFIAPI
EftpDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
/*++
 
  Routine Description:
    Stop this driver on ControllerHandle.
 
  Arguments:
    This                  - Protocol instance pointer.
    Controller            - Handle of device to stop driver on 
    NumberOfChildren      - Number of Handles in ChildHandleBuffer. If number of 
                            children is zero stop the entire bus driver.
    ChildHandleBuffer     - List of Child Handles to Stop.
 
  Returns:
    EFI_SUCCESS           - This driver is removed ControllerHandle
    EFI_DEVICE_ERROR      - Failed to remove the controller
    Other                 - Failed to remove the controller
 
--*/
;

EFI_STATUS
EFIAPI
EftpServiceBindingCreateChild (
  IN EFI_SERVICE_BINDING_PROTOCOL  *This,
  IN OUT EFI_HANDLE                *ChildHandle
  )
/*++

Routine Description:

  Create a child of Eftp driver.

Arguments:

  This           - The service binding handle of Eftp driver.
  ChildHandle    - Variable to return the child handler

Returns:

  EFI_ACCESS_DENIED      - Protocol is busy
  EFI_OUT_OF_RESOURCES   - No enough resource
  EFI_SUCCESS            - Successfully created a child of Eftp driver

--*/
;

EFI_STATUS
EFIAPI
EftpServiceBindingDestroyChild (
  IN EFI_SERVICE_BINDING_PROTOCOL      *This,
  IN EFI_HANDLE                        ChildHandle
  )
/*++

Routine Description:

  Destory a Eftp child

Arguments:

  This            - The session's service binding handler
  ChildHandle     - Child to destory
  
Returns:

  EFI_ACCESS_DENIED        - Protocol is busy
  EFI_SUCCESS              - Successfully created a child of Eftp driver

--*/
;

#endif
