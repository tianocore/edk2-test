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

  BusDriver3.c

Abstract:

  for Protocol Handler Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "../Inc/TestDriver.h"

//
// TestBusDriver3:
// Consume InterfaceTestProtocol1;
// Can create 2 child handles, install InterfaceTestProtocol2 onto one child,
// and install InterfaceTestProtocol3 onto another
//

//
// data definition here
//
typedef struct {
  EFI_DRIVER_BINDING_PROTOCOL           DriverBinding;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2    InterfaceFunctionTestProtocol2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3    InterfaceFunctionTestProtocol3;
} BUS_DRIVER_3_PRIVATE_DATA;

#define BUS_DRIVER_3_PRIVATE_DATA_FROM_DRIVER_BINDING(a) \
  BASE_CR(a, BUS_DRIVER_3_PRIVATE_DATA, DriverBinding)

BUS_DRIVER_3_PRIVATE_DATA          *mPrivateData;

EFI_STATUS
EFIAPI
InitializeBusDriver3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BusDriver3BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
BusDriver3BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
BusDriver3BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );

VOID
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  );

VOID
EFIAPI
Protocol2ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_2   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol2 (
  INTERFACE_FUNCTION_TEST_PROTOCOL_2     *InterfaceFunctionTestProtocol2
  );

VOID
EFIAPI
Protocol3ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_3   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol3 (
  INTERFACE_FUNCTION_TEST_PROTOCOL_3     *InterfaceFunctionTestProtocol3
  );

EFI_STATUS
EFIAPI
BusDriver3Unload (
  IN EFI_HANDLE       ImageHandle
  );

//
// global variable for this test driver's image handle
//


EFI_STATUS
EFIAPI
InitializeBusDriver3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImageInfoPtr;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // allocate memory for PrivateData
  //
  Status = gtBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof (BUS_DRIVER_3_PRIVATE_DATA),
                        (VOID**)&mPrivateData
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  gtBS->SetMem (mPrivateData,sizeof (BUS_DRIVER_3_PRIVATE_DATA),0);

  InitializeDriverBinding (&mPrivateData->DriverBinding);

  Status = gtBS->InstallProtocolInterface (
            &ImageHandle,
            &gEfiDriverBindingProtocolGuid,
            EFI_NATIVE_INTERFACE,
            &mPrivateData->DriverBinding
            );
  mPrivateData->DriverBinding.ImageHandle = ImageHandle;
  mPrivateData->DriverBinding.DriverBindingHandle = ImageHandle;
  //
  // UnLoad Function Handler
  //
  gtBS->HandleProtocol (
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID*)&LoadedImageInfoPtr
        );

  LoadedImageInfoPtr->Unload = BusDriver3Unload;

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
BusDriver3BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS        Status;

  Status = gtBS->OpenProtocol (
                      Controller,
                      &mInterfaceFunctionTestProtocol1Guid,
                      (VOID **) NULL,
                      This->DriverBindingHandle,
                      Controller,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  if (EFI_ERROR(Status)) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BusDriver3BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1    *IFTestProt1;
  BUS_DRIVER_3_PRIVATE_DATA             *PrivateData;
  EFI_HANDLE                            Handle;

  PrivateData = BUS_DRIVER_3_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     This->DriverBindingHandle,
                     Controller,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
  if (EFI_ERROR(Status) && (Status != EFI_ALREADY_STARTED)) {
    return Status;
  }

  if (Status == EFI_SUCCESS) {
    gtBS->InstallMultipleProtocolInterfaces (
                  &Controller,
                  &mBusDriver3Guid,
                  NULL,
                  NULL
                  );
  }

  InitializeInterfaceFunctionTestProtocol2 (&PrivateData->InterfaceFunctionTestProtocol2);
  Handle = NULL;
  Status = gtBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &mInterfaceFunctionTestProtocol2Guid,
                  &PrivateData->InterfaceFunctionTestProtocol2,
                  NULL
                  );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     This->DriverBindingHandle,
                     Handle,
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
  if (EFI_ERROR(Status)) {
    gtBS->UninstallMultipleProtocolInterfaces (
                    Handle,
                    &mInterfaceFunctionTestProtocol2Guid,
                    &PrivateData->InterfaceFunctionTestProtocol2,
                    NULL
                    );
    return Status;
  }

  InitializeInterfaceFunctionTestProtocol3 (&PrivateData->InterfaceFunctionTestProtocol3);
  Handle = NULL;
  Status = gtBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &mInterfaceFunctionTestProtocol3Guid,
                  &PrivateData->InterfaceFunctionTestProtocol3,
                  NULL
                  );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     This->DriverBindingHandle,
                     Handle,
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
  if (EFI_ERROR(Status)) {
    gtBS->UninstallMultipleProtocolInterfaces (
                    Handle,
                    &mInterfaceFunctionTestProtocol3Guid,
                    &PrivateData->InterfaceFunctionTestProtocol3,
                    NULL
                    );
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BusDriver3BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  BUS_DRIVER_3_PRIVATE_DATA          *PrivateData;
  //EFI_STATUS                         Status;
  EFI_STATUS                         Status1,Status2;
  BOOLEAN                            AllChildrenStopped;
  UINTN                              Index;

  PrivateData = BUS_DRIVER_3_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  if (NumberOfChildren == 0) {

    gtBS->CloseProtocol (
            Controller,
            &mInterfaceFunctionTestProtocol1Guid,
            This->DriverBindingHandle,
            Controller
            );
    gtBS->UninstallProtocolInterface (
            Controller,
            &mBusDriver3Guid,
            NULL
            );
    return EFI_SUCCESS;
  }

  AllChildrenStopped = TRUE;

  for (Index = 0; Index < NumberOfChildren; Index++) {

    gtBS->CloseProtocol (
              Controller,
              &mInterfaceFunctionTestProtocol1Guid,
              This->DriverBindingHandle,
              ChildHandleBuffer[Index]
              );

    Status1 = gtBS->UninstallMultipleProtocolInterfaces (
                  ChildHandleBuffer[Index],
                  &mInterfaceFunctionTestProtocol2Guid,
                  &PrivateData->InterfaceFunctionTestProtocol2,
                  NULL
                  );
    Status2 = gtBS->UninstallMultipleProtocolInterfaces (
                  ChildHandleBuffer[Index],
                  &mInterfaceFunctionTestProtocol3Guid,
                  &PrivateData->InterfaceFunctionTestProtocol3,
                  NULL
                  );
    if (EFI_ERROR (Status1) && EFI_ERROR(Status2)) {
      AllChildrenStopped = FALSE;
    }
  }

  if (!AllChildrenStopped) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

VOID
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  )
{
  DriverBinding->Supported            = BusDriver3BindingSupported;
  DriverBinding->Start                = BusDriver3BindingStart;
  DriverBinding->Stop                 = BusDriver3BindingStop;
  DriverBinding->Version              = 0x10;
  DriverBinding->ImageHandle          = NULL;
  DriverBinding->DriverBindingHandle  = NULL;
}

VOID
EFIAPI
Protocol2ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_2   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  )
{
  *ProtocolAttributes = This->ProtocolAttributes;
}

VOID
InitializeInterfaceFunctionTestProtocol2 (
  INTERFACE_FUNCTION_TEST_PROTOCOL_2     *InterfaceFunctionTestProtocol2
  )
{
  InterfaceFunctionTestProtocol2->ReportProtocolAttributes = Protocol2ReportProtocolAttributes;
  InterfaceFunctionTestProtocol2->ProtocolAttributes.ProtocolId = InterfaceFunctionTestProtocol2Id;
  InterfaceFunctionTestProtocol2->ProtocolAttributes.ReinstallField = 0;
}

VOID
EFIAPI
Protocol3ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_3   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  )
{
  *ProtocolAttributes = This->ProtocolAttributes;
}

VOID
InitializeInterfaceFunctionTestProtocol3 (
  INTERFACE_FUNCTION_TEST_PROTOCOL_3     *InterfaceFunctionTestProtocol3
  )
{
  InterfaceFunctionTestProtocol3->ReportProtocolAttributes = Protocol3ReportProtocolAttributes;
  InterfaceFunctionTestProtocol3->ProtocolAttributes.ProtocolId = InterfaceFunctionTestProtocol3Id;
  InterfaceFunctionTestProtocol3->ProtocolAttributes.ReinstallField = 0;
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
EFIAPI
BusDriver3Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
              mPrivateData->DriverBinding.DriverBindingHandle,
              &gEfiDriverBindingProtocolGuid,
              &mPrivateData->DriverBinding
              );
  gtBS->FreePool (mPrivateData);

  return EFI_SUCCESS;
}
