/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
 
  EftpDriver.c
 
Abstract:
 
--*/
#include "Efi.h"
#include "EftpDriver.h"
#include "EftpMain.h"

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
extern EFI_COMPONENT_NAME2_PROTOCOL gEftpComponentName2;
#else
extern EFI_COMPONENT_NAME_PROTOCOL gEftpComponentName;
#endif

EFI_DRIVER_BINDING_PROTOCOL         gEftpDriverBinding = {
  EftpDriverBindingSupported,
  EftpDriverBindingStart,
  EftpDriverBindingStop,
  0x10,
  NULL,
  NULL
};

EFTP_SERVICE_BINDING_PRIVATE        gEftpsbDataTemplate = {
  EFTP_SB_PRIVATE_SIGNATURE,
  {
    EftpServiceBindingCreateChild,
    EftpServiceBindingDestroyChild
  },
  NULL,
  NULL,
  NULL,
  NULL,
  0,
  {
    NULL,
    NULL
  },
  {
    0,
    0,
    0
  }
};

EFI_EFTP_PROTOCOL                   gEftpProtocolTemplate = {
  EftpGetModeData,
  EftpConfigure,
  EftpGetInfo,
  EftpParseOptions,
  EftpReadFile,
  EftpWriteFile,
  EftpReadDirectory,
  EftpPoll
};

#ifdef _EFTP_STAT_
EFTP_SERVICE_BINDING_PRIVATE  *GlobalData = NULL;
#endif

EFI_STATUS
EFIAPI
EftpDriverEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
/*++
Routine Description:

  The entry point of the Eftp driver

Arguments:

  ImageHandle    - Image handle contain the driver
  SystemTable    - System table global

Returns:

  EFI_SUCCESS    - The driver handle is successfully installed
  Others         - Failed to install the driver

--*/
{
  //
  // Install the Driver Protocols
  //
  return EfiLibInstallAllDriverProtocolsWithUnload (
          ImageHandle,
          SystemTable,
          &gEftpDriverBinding,
          ImageHandle,
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
          &gEftpComponentName2,
#else
          &gEftpComponentName,
#endif
          NULL,
          NULL
          );
}

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
{
  EFI_STATUS  Status;

  //
  // Allow EFTP driver to start if this handle has MNP.
  //
  Status = tBS->OpenProtocol (
                  Controller,
                  &gEfiManagedNetworkServiceBindingProtocolGuid,
                  (VOID **) NULL,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );

  return Status;
}

EFI_STATUS
EFIAPI
EftpDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
/*++

Routine Description:

  Start the Eftp driver

Arguments:

  This                    - Protocol instance pointer.
  Controller              - Handle of device to test.
  RemainingDevicePath     - Optional parameter use to pick a specific child device to start.

Returns:

  EFI_ALREADY_STARTED     - The device is already started.
  EFI_OUT_OF_RESOURCES    - No enough resource
  EFI_SUCCESS             - Successfully started the driver.

--*/
{
  EFTP_SERVICE_BINDING_PRIVATE  *SbInstance;
  EFI_SERVICE_BINDING_PROTOCOL  *ManagedNetworkSb;
  EFI_STATUS                    Status;

  EFTP_DEBUG_VERBOSE ((L"DriverBindingStart: Controller = %x\n", Controller));

  //
  // Directly return if driver is already running.
  //
  Status = tBS->OpenProtocol (
                  Controller,
                  &gEfiEftpServiceBindingProtocolGuid,
                  (VOID **) NULL,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    EFTP_DEBUG_VERBOSE ((L"DriverBindingStart: already started.\n"));
    return EFI_ALREADY_STARTED;
  }

  EFTP_DEBUG_VERBOSE ((L" DriverBindingStart: Open EftpSB return %r.\n", Status));

  //
  // Allocate and initialize a new service binding instance.
  //
  SbInstance = NetAllocatePool (sizeof (EFTP_SERVICE_BINDING_PRIVATE));
  if (SbInstance == NULL) {
    EFTP_DEBUG_ERROR ((L"DriverBindingStart: Allocate service binding buffer failed.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  NetCopyMem (SbInstance, &gEftpsbDataTemplate, sizeof (EFTP_SERVICE_BINDING_PRIVATE));

  //
  // Fill in the service binding data fields
  //
  SbInstance->ControllerHandle  = Controller;
  SbInstance->ImageHandle       = This->DriverBindingHandle;
  SbInstance->ChildrenNum       = 0;
  LIST_INIT (&SbInstance->ChildrenList);
  NET_LOCK_INIT (&SbInstance->ChildrenListLock);

  //
  // Get the MNP service binding protocol and create a child
  //
  Status = tBS->OpenProtocol (
                  Controller,
                  &gEfiManagedNetworkServiceBindingProtocolGuid,
                  (VOID **) &ManagedNetworkSb,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"DriverBindingStart: Get MnpSB failed with %r.\n", Status));
    goto ReleaseSB;
  }

  Status = ManagedNetworkSb->CreateChild (
                              ManagedNetworkSb,
                              &SbInstance->MnpChildHandle
                              );
  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"DriverBindingStart:MnpSB->CreateChild failed %r.\n", Status));
    goto ReleaseSB;
  }
  //
  // Open this mnp protocol and use it as the conjunction of eftp and mnp
  //
  Status = tBS->OpenProtocol (
                  SbInstance->MnpChildHandle,
                  &gEfiManagedNetworkProtocolGuid,
                  (VOID **) &SbInstance->ManagedNetwork,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"DriverBindingStart: OpenProtocol MNP failed %r.\n", Status));
    goto CleanUp;
  }
  //
  // Close the ManagedNetworkServiceBinding Protocol
  //
  Status = tBS->CloseProtocol (
                  Controller,
                  &gEfiManagedNetworkServiceBindingProtocolGuid,
                  This->DriverBindingHandle,
                  Controller
                  );

  //
  // Install the EftpServiceBinding Protocol onto Controller
  //
  Status = tBS->InstallMultipleProtocolInterfaces (
                  &Controller,
                  &gEfiEftpServiceBindingProtocolGuid,
                  &SbInstance->ServiceBinding,
                  NULL
                  );

  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"DriverBindingStart: Install EftpServiceBinding failed %r.\n", Status));
    tBS->CloseProtocol (
          SbInstance->MnpChildHandle,
          &gEfiManagedNetworkProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );
    goto CleanUp;
  }
  //
  // Initialize the packet buffer used by Eftp instances
  //
  EftpInitPacketBuffer ();

  EFTP_DEBUG_VERBOSE ((L"DriverBindingStart: Install EftpSB return %r.\n", Status));
  return EFI_SUCCESS;

CleanUp:
  //
  // Destroy MNP child
  //
  if (SbInstance->MnpChildHandle != NULL) {
    ManagedNetworkSb->DestroyChild (ManagedNetworkSb, SbInstance->MnpChildHandle);
  }

ReleaseSB:
  //
  // Free the context data of service binding protocol
  //
  NetFreePool (SbInstance);

  return Status;

}

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
{
  EFI_EFTP_PROTOCOL                   *Eftp;
  EFI_SERVICE_BINDING_PROTOCOL        *EftpSB;
  EFI_SERVICE_BINDING_PROTOCOL        *ManagedNetworkSb;
  EFTP_SERVICE_BINDING_PRIVATE        *SBPrivate;
  EFI_HANDLE                          ParentController;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenBuffer;
  UINTN                               OpenCount;
  UINTN                               Index;
  EFI_STATUS                          Status;

  EFTP_DEBUG_VERBOSE (
    (L"DriverBindingStop: Entering with numberofchildren=%d,Controller=%x\n",
    NumberOfChildren,
    Controller)
    );

  //
  // Get the service binding private context first
  //
  Status = tBS->OpenProtocolInformation (
                  Controller,
                  &gEfiManagedNetworkProtocolGuid,
                  &OpenBuffer,
                  &OpenCount
                  );
  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"DriverBindingStop: Get Mnp Protocol failed %r.\n", Status));
    return (Status == EFI_NOT_FOUND) ? EFI_SUCCESS : Status;
  }

  ParentController = NULL;
  for (Index = 0; Index < OpenCount; Index++) {
    if (OpenBuffer[Index].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) {
      ParentController = OpenBuffer[Index].ControllerHandle;
      break;
    }
  }

  tBS->FreePool (OpenBuffer);

  if (ParentController == NULL) {
    EFTP_DEBUG_VERBOSE ((L"DriverBindingStop: No Parrent controller found.\n"));
    return EFI_SUCCESS;
  }

  EFTP_DEBUG_VERBOSE ((L"DriverBindingStop: ParentController = %x.\n", ParentController));

  //
  // Retrieve the private context data
  //
  Status = tBS->OpenProtocol (
                  ParentController,
                  &gEfiEftpServiceBindingProtocolGuid,
                  (VOID **) &EftpSB,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    Status = tBS->OpenProtocol (
                    ParentController,
                    &gEfiEftpProtocolGuid,
                    (VOID **) &Eftp,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (!EFI_ERROR (Status)) {
      EFTP_DEBUG_VERBOSE ((L"DriverBindingStop: Stop a multicast handle, now turn to stop the parent handle.\n"));
      Status = This->Stop (This, ParentController, 0, NULL);
      return Status;
    }

    EFTP_DEBUG_ERROR ((L"DriverBindingStop: Get EftpSB or EFTP failed %r.\n", Status));
    return EFI_DEVICE_ERROR;
  }

  SBPrivate = EFTP_SB_PRIVATE_FROM_THIS (EftpSB);

  //
  // When mnp protocl is uninstalled this function will be called, the handle
  // mnp on must manage no child handle
  //
  ASSERT (NumberOfChildren == 0);

  //
  // When this Eftp drivers still have some Eftp children just kill these children
  // on controller
  //
  while (SBPrivate->ChildrenNum > 0) {
    //
    // To test if there is a Eftp protocol in this controller
    //
    Status = tBS->OpenProtocol (
                    Controller,
                    &gEfiEftpProtocolGuid,
                    (VOID **) &Eftp,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (!EFI_ERROR (Status)) {
      EftpSB->DestroyChild (EftpSB, Controller);
    }
  }
  //
  // Begin to Clean MNP protocol
  //
  if (SBPrivate->MnpChildHandle) {
    //
    // Get the ManagedNetwork Service Binding Protocol
    //
    Status = tBS->OpenProtocol (
                    ParentController,
                    &gEfiManagedNetworkServiceBindingProtocolGuid,
                    (VOID **) &ManagedNetworkSb,
                    This->DriverBindingHandle,
                    ParentController,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );

    if (EFI_ERROR (Status)) {
      return Status;
    }
    //
    // Destroy the ChildHandle with the ManagedNetwork Protocol
    //
    Status = ManagedNetworkSb->DestroyChild (ManagedNetworkSb, SBPrivate->MnpChildHandle);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //
    // Invalidate the SBPrivate->MnpChildHandle and SBPrivate->ManagedNetwork pointer
    //
    SBPrivate->ManagedNetwork = NULL;
    SBPrivate->MnpChildHandle = NULL;
  }
  //
  // Uninstall the EFTP service binding protocol
  //
  Status = tBS->UninstallMultipleProtocolInterfaces (
                  ParentController,
                  &gEfiEftpServiceBindingProtocolGuid,
                  EftpSB,
                  NULL
                  );
  EFTP_DEBUG_VERBOSE ((L"DriverBindingStop: Uninstall EftpSB return %r.\n", Status));
  if (EFI_ERROR (Status)) {
    return Status;
  }

  EftpClosePacketBuffer ();
  NetFreePool (SBPrivate);

  return EFI_SUCCESS;
}

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
{
  EFTP_SERVICE_BINDING_PRIVATE  *ServiceBindingPrivate;
  EFTP_IO_PRIVATE               *IoPrivate;
  EFI_SERVICE_BINDING_PROTOCOL  *ServiceBinding;
  EFI_STATUS                    Status;

  EFTP_DEBUG_VERBOSE ((L"EftpSBCreate: Entering...\n"));
  ServiceBindingPrivate = EFTP_SB_PRIVATE_FROM_THIS (This);
  ServiceBinding        = NULL;

  //
  // Retrieve the lock for the childrenlist of this Eftp servicebinding protocol
  //
  Status = NET_TRYLOCK (&ServiceBindingPrivate->ChildrenListLock);
  if (EFI_ERROR (Status)) {
    return EFI_ACCESS_DENIED;
  }
  //
  // Allocate the memory for private data of Eftp instance
  //
  IoPrivate = NetAllocateZeroPool (sizeof (EFTP_IO_PRIVATE));
  if (IoPrivate == NULL) {
    NET_UNLOCK (&ServiceBindingPrivate->ChildrenListLock);
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // Fill in the EFTP IO private structrue.
  //
  IoPrivate->Signature        = EFTP_IO_PRIVATE_SIGNATURE;
  IoPrivate->ParentController = ServiceBindingPrivate->ControllerHandle;

  //
  // Set the Eftp interface function pointer
  //
  NetCopyMem (&IoPrivate->Eftp, &gEftpProtocolTemplate, sizeof (EFI_EFTP_PROTOCOL));

  //
  // Set the configured flag of IO Private structure
  //
  IoPrivate->Configured = FALSE;

  //
  // Set the state machine of IO Private structure
  //
  IoPrivate->State = EFTP_INIT;

  //
  // Create a MNP instance used by this Eftp instance when communicating with
  // server using unicast mode
  //
  if (ServiceBindingPrivate->ChildrenNum == 0) {
    //
    // When the servicebinding manage no child using the conjunction udp instance as the unicast udp io
    // instance
    //
    EFTP_DEBUG_VERBOSE ((L"EftpSBCreate: ChildrenNum=0 and using the conjunction Mnp handle.\n"));

    //
    // Install the Eftp protocol onto the handle the mnp instance is on
    //
    *ChildHandle = ServiceBindingPrivate->MnpChildHandle;

    //
    // Open the mnp io instance in this handle
    //
    Status = tBS->OpenProtocol (
                    ServiceBindingPrivate->MnpChildHandle,
                    &gEfiManagedNetworkProtocolGuid,
                    (VOID **) &IoPrivate->ManagedNetwork,
                    gEftpDriverBinding.DriverBindingHandle,
                    NULL,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpSBCreate: Open MNP protocol on child handler failed.\n"));
      goto ReleaseIoPrivate;
    }
  } else {

    EFTP_DEBUG_VERBOSE (
      (L"EftpSBCreate: ChildNum=%d and creat new child.\n",
      ServiceBindingPrivate->ChildrenNum)
      );

    //
    // Retrieve the mnp servicebinding prtocol.
    //
    Status = tBS->OpenProtocol (
                    ServiceBindingPrivate->ControllerHandle,
                    &gEfiManagedNetworkServiceBindingProtocolGuid,
                    (VOID **) &ServiceBinding,
                    gEftpDriverBinding.DriverBindingHandle,
                    ServiceBindingPrivate->ControllerHandle,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpSBCreate: Get MnpSb faild with %r.\n", Status));
      goto ReleaseIoPrivate;
    }

    EFTP_DEBUG_VERBOSE ((L"EftpSBCreate: Get MnpSb successfully[%x].\n", ServiceBinding));

    //
    // Create a new MNP IO instance
    //
    Status = ServiceBinding->CreateChild (ServiceBinding, ChildHandle);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpSBCreate: MnpSb->CreateChild faild with %r.\n", Status));
      goto ReleaseIoPrivate;
    }

    EFTP_DEBUG_VERBOSE ((L"EftpSBCreate: MnpSb->CreateChild successfully [child=%x].\n", *ChildHandle));

    //
    // Open the MNP IO protocol in this childhandle
    //
    Status = tBS->OpenProtocol (
                    *ChildHandle,
                    &gEfiManagedNetworkProtocolGuid,
                    (VOID **) &IoPrivate->ManagedNetwork,
                    gEftpDriverBinding.DriverBindingHandle,
                    ServiceBindingPrivate->ControllerHandle,
                    EFI_OPEN_PROTOCOL_BY_DRIVER
                    );
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpSBCreate: Open MNP protocol failed with %r.\n", Status));
      ServiceBinding->DestroyChild (ServiceBinding, *ChildHandle);
      goto ReleaseIoPrivate;
    }

    EFTP_DEBUG_VERBOSE ((L"EftpSBCreate: Get MnpIo protocol return %r.\n", Status));
  }
  //
  // Record the handle MNP IO is in and install the Eftp protocol on this handle
  //
  IoPrivate->Handle = *ChildHandle;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  ChildHandle,
                  &gEfiEftpProtocolGuid,
                  &IoPrivate->Eftp,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"EftpServiceBindingCreateChild: Install Eftp on child faild with %r.\n", Status));
    goto CleanUp;
  }
  //
  // Add this instance to the children list and update the counter.
  //
  ServiceBindingPrivate->ChildrenNum++;
  LIST_INSERT_TAIL (&ServiceBindingPrivate->ChildrenList, &IoPrivate->List);

  NET_UNLOCK (&ServiceBindingPrivate->ChildrenListLock);
  return EFI_SUCCESS;

CleanUp:
  //
  // Clean up all the resource assoiated with the Eftp instance
  //
  if (*ChildHandle != NULL && *ChildHandle != ServiceBindingPrivate->MnpChildHandle) {
    tBS->CloseProtocol (
          *ChildHandle,
          &gEfiManagedNetworkProtocolGuid,
          gEftpDriverBinding.DriverBindingHandle,
          ServiceBindingPrivate->ControllerHandle
          );
    ServiceBinding->DestroyChild (ServiceBinding, *ChildHandle);
  }

ReleaseIoPrivate:
  NetFreePool (IoPrivate);

  NET_UNLOCK (&ServiceBindingPrivate->ChildrenListLock);
  return Status;
}

EFI_STATUS
EFIAPI
EftpServiceBindingDestroyChild (
  IN EFI_SERVICE_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                      ChildHandle
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
{
  EFTP_SERVICE_BINDING_PRIVATE  *ServiceBindingPrivate;
  EFTP_IO_PRIVATE               *IoPrivate;
  EFI_SERVICE_BINDING_PROTOCOL  *ServiceBinding;
  EFI_EFTP_PROTOCOL             *Eftp;
  EFI_STATUS                    Status;

  ServiceBindingPrivate = EFTP_SB_PRIVATE_FROM_THIS (This);

  EFTP_DEBUG_VERBOSE ((L"DestroyChild: Entering with child=%x\n", ChildHandle));

  //
  // Retrieve the Eftp protocol interface
  //
  Status = tBS->OpenProtocol (
                  ChildHandle,
                  &gEfiEftpProtocolGuid,
                  (VOID **) &Eftp,
                  gEftpDriverBinding.DriverBindingHandle,
                  ChildHandle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"DestroyChild: Get Eftp interface failed %r.\n", Status));
    return Status;
  }
  //
  // Destroy function begin
  //
  IoPrivate = EFTP_IO_PRIVATE_FROM_THIS (Eftp);
  if (IoPrivate->Destroyed == TRUE) {
    EFTP_DEBUG_VERBOSE ((L"DestroyChild: This child is in destroy process, return directly.\n"));
    return EFI_SUCCESS;
  }

  IoPrivate->Destroyed = TRUE;

#ifdef _EFTP_STAT_
  EFTP_DEBUG_VERBOSE (
    (L"EftpDestroy: RcvdPkts == %ld, DroppedPkts == %ld, Timeouts == %ld",
    IoPrivate->RcvdPkts,
    IoPrivate->DroppedPkts,
    IoPrivate->Timeouts)
    );
#endif
  //
  // Stop pending operation.
  //
  Eftp->Configure (Eftp, NULL);

  //
  // Remove the Eftp instance from the childernlist of service binding data
  //
  if (EFI_ERROR (NET_TRYLOCK (&ServiceBindingPrivate->ChildrenListLock))) {
    IoPrivate->Destroyed = FALSE;
    return EFI_ACCESS_DENIED;
  }

  ASSERT (ServiceBindingPrivate->ChildrenNum >= 1);
  LIST_REMOVE_ENTRY (&IoPrivate->List);
  ServiceBindingPrivate->ChildrenNum--;

  NET_UNLOCK (&ServiceBindingPrivate->ChildrenListLock);

  //
  // Uninstall the Eftp protocol from the childhandle
  //
  tBS->UninstallMultipleProtocolInterfaces (
        ChildHandle,
        &gEfiEftpProtocolGuid,
        Eftp,
        NULL
        );

  //
  // Destroy the MNP child handle if it is not the last one
  //
  EFTP_DEBUG_VERBOSE ((L"DestroyChild: Try to destroy the MNP child handle.\n"));
  Status = tBS->OpenProtocol (
                  ServiceBindingPrivate->ControllerHandle,
                  &gEfiManagedNetworkServiceBindingProtocolGuid,
                  (VOID **) &ServiceBinding,
                  gEftpDriverBinding.DriverBindingHandle,
                  ServiceBindingPrivate->ControllerHandle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"DestroyChild: Get MnpSb failed with %r.\n", Status));
    IoPrivate->Destroyed = FALSE;
    return Status;
  }
  //
  // Destroy the unicast MNP instance if needed
  //
  if (ServiceBindingPrivate->ChildrenNum > 0) {
    EFTP_DEBUG_VERBOSE (
      (L"DestroyChild: ChildrenNum = %d, so destroy the MNP child.\n",
      ServiceBindingPrivate->ChildrenNum)
      );

    //
    // Close MNP protocol
    //
    tBS->CloseProtocol (
          ChildHandle,
          &gEfiManagedNetworkProtocolGuid,
          gEftpDriverBinding.DriverBindingHandle,
          ServiceBindingPrivate->ControllerHandle
          );
    ServiceBinding->DestroyChild (ServiceBinding, ChildHandle);

  } else {
    //
    // Keep the last one as a conjunction between MNP and EFTP
    //
    EFTP_DEBUG_VERBOSE ((L"DestroyChild: Keep the last MNP child for conjunction use.\n"));
    ServiceBindingPrivate->MnpChildHandle = ChildHandle;

  }

  NetFreePool (IoPrivate);

  return EFI_SUCCESS;
}
