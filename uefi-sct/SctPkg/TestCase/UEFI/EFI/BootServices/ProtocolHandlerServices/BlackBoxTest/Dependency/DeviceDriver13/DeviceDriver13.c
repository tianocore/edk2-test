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

  DeviceDriver13.c

Abstract:

  for Protocol Handler Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "../Inc/TestDriver.h"

//
// TestDeviceDriver13:
// Consume InterfaceTestProtocol3 BY_DRIVER | EXCLUSIVE;
// Produce InterfaceTestProtocol6 on the same handle
//

//
// data definition here
//
typedef struct {
  INTERFACE_FUNCTION_TEST_PROTOCOL_6    InterfaceFunctionTestProtocol6;
  EFI_DRIVER_BINDING_PROTOCOL           DriverBinding;
} DEVICE_DRIVER_13_PRIVATE_DATA;

#define DEVICE_DRIVER_13_PRIVATE_DATA_FROM_DRIVER_BINDING(a) \
 BASE_CR(a, DEVICE_DRIVER_13_PRIVATE_DATA, DriverBinding)

DEVICE_DRIVER_13_PRIVATE_DATA          *mPrivateData;

EFI_STATUS
EFIAPI
InitializeDeviceDriver13 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
DeviceDriver13BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
DeviceDriver13BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
DeviceDriver13BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );

void
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  );

VOID
EFIAPI
Protocol6ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_6   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol6 (
  INTERFACE_FUNCTION_TEST_PROTOCOL_6     *InterfaceFunctionTestProtocol6
  );

EFI_STATUS
EFIAPI
DeviceDriver13Unload (
  IN EFI_HANDLE       ImageHandle
  );

//
// global variable for this test driver's image handle
//

EFI_STATUS
EFIAPI
InitializeDeviceDriver13 (
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
                        sizeof (DEVICE_DRIVER_13_PRIVATE_DATA),
                        (VOID**)&mPrivateData
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  gtBS->SetMem (mPrivateData,sizeof (DEVICE_DRIVER_13_PRIVATE_DATA),0);

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

  LoadedImageInfoPtr->Unload = DeviceDriver13Unload;

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
DeviceDriver13BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS        Status;

  Status = gtBS->OpenProtocol (
                      Controller,
                      &mInterfaceFunctionTestProtocol3Guid,
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
DeviceDriver13BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3    *IFTestProt3;
  DEVICE_DRIVER_13_PRIVATE_DATA         *PrivateData;

  PrivateData = DEVICE_DRIVER_13_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mInterfaceFunctionTestProtocol3Guid,
                     (VOID **) &IFTestProt3,
                     This->DriverBindingHandle,
                     Controller,
                     EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                     );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  InitializeInterfaceFunctionTestProtocol6 (&PrivateData->InterfaceFunctionTestProtocol6);

  Status = gtBS->OpenProtocol (
                  Controller,
                  &mInterfaceFunctionTestProtocol6Guid,
                  (VOID **) NULL,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (EFI_ERROR(Status)) {
    Status = gtBS->InstallProtocolInterface (
                    &Controller,
                    &mInterfaceFunctionTestProtocol6Guid,
                    EFI_NATIVE_INTERFACE,
                    &PrivateData->InterfaceFunctionTestProtocol6
                    );
  } else {
    Status = EFI_ALREADY_STARTED;
  }
  return Status;
}

EFI_STATUS
EFIAPI
DeviceDriver13BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  DEVICE_DRIVER_13_PRIVATE_DATA          *PrivateData;

  PrivateData = DEVICE_DRIVER_13_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  gtBS->UninstallProtocolInterface (
            Controller,
            &mInterfaceFunctionTestProtocol6Guid,
            &PrivateData->InterfaceFunctionTestProtocol6
            );

  gtBS->CloseProtocol (
            Controller,
            &mInterfaceFunctionTestProtocol3Guid,
            This->DriverBindingHandle,
            Controller
            );

  return EFI_SUCCESS;
}

void
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  )
{
  DriverBinding->Supported            = DeviceDriver13BindingSupported;
  DriverBinding->Start                = DeviceDriver13BindingStart;
  DriverBinding->Stop                 = DeviceDriver13BindingStop;
  DriverBinding->Version              = 0x10;
  DriverBinding->ImageHandle          = NULL;
  DriverBinding->DriverBindingHandle  = NULL;
}

VOID
EFIAPI
Protocol6ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_6   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  )
{
  *ProtocolAttributes = This->ProtocolAttributes;
}

VOID
InitializeInterfaceFunctionTestProtocol6 (
  INTERFACE_FUNCTION_TEST_PROTOCOL_6     *InterfaceFunctionTestProtocol6
  )
{
  InterfaceFunctionTestProtocol6->ReportProtocolAttributes = Protocol6ReportProtocolAttributes;
  InterfaceFunctionTestProtocol6->ProtocolAttributes.ProtocolId = InterfaceFunctionTestProtocol6Id;
  InterfaceFunctionTestProtocol6->ProtocolAttributes.ReinstallField = 0;
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
EFIAPI
DeviceDriver13Unload (
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
