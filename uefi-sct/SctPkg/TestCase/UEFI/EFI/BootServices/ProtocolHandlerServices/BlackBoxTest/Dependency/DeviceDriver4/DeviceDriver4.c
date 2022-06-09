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

  DeviceDriver4.c

Abstract:

  for Protocol Handler Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "../Inc/TestDriver.h"

//
// TestDeviceDriver4:
// Consume InterfaceTestProtocol1;
// Produce InterfaceTestProtocol3 on the same handle
// And TestDeviceDriver4's DriverBinding Version = 0x30, which is greater than
// that of TestDeviceDriver1's (0x20)

//
// data definition here
//
typedef struct {
  INTERFACE_FUNCTION_TEST_PROTOCOL_3    InterfaceFunctionTestProtocol3;
  EFI_DRIVER_BINDING_PROTOCOL           DriverBinding;
} DEVICE_DRIVER_4_PRIVATE_DATA;

#define DEVICE_DRIVER_4_PRIVATE_DATA_FROM_DRIVER_BINDING(a) \
 BASE_CR(a, DEVICE_DRIVER_4_PRIVATE_DATA, DriverBinding)

DEVICE_DRIVER_4_PRIVATE_DATA          *mPrivateData;

EFI_STATUS
EFIAPI
InitializeDeviceDriver4 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
DeviceDriver4BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
DeviceDriver4BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
DeviceDriver4BindingStop (
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
DeviceDriver4Unload (
  IN EFI_HANDLE       ImageHandle
  );


//
// global variable for this test driver's image handle
//

EFI_STATUS
EFIAPI
InitializeDeviceDriver4 (
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
                        sizeof (DEVICE_DRIVER_4_PRIVATE_DATA),
                        (VOID**)&mPrivateData
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  gtBS->SetMem (mPrivateData,sizeof (DEVICE_DRIVER_4_PRIVATE_DATA),0);

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

  LoadedImageInfoPtr->Unload = DeviceDriver4Unload;

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
DeviceDriver4BindingSupported (
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
DeviceDriver4BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1    *IFTestProt1;
  DEVICE_DRIVER_4_PRIVATE_DATA          *PrivateData;

  PrivateData = DEVICE_DRIVER_4_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mInterfaceFunctionTestProtocol1Guid,
                     (VOID **) &IFTestProt1,
                     This->DriverBindingHandle,
                     Controller,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeInterfaceFunctionTestProtocol3 (&PrivateData->InterfaceFunctionTestProtocol3);

  Status = gtBS->InstallProtocolInterface (
                  &Controller,
                  &mInterfaceFunctionTestProtocol3Guid,
                  EFI_NATIVE_INTERFACE,
                  &PrivateData->InterfaceFunctionTestProtocol3
                  );
  return Status;
}

EFI_STATUS
EFIAPI
DeviceDriver4BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  DEVICE_DRIVER_4_PRIVATE_DATA          *PrivateData;

  PrivateData = DEVICE_DRIVER_4_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  gtBS->UninstallProtocolInterface (
            Controller,
            &mInterfaceFunctionTestProtocol3Guid,
            &PrivateData->InterfaceFunctionTestProtocol3
            );

  gtBS->CloseProtocol (
            Controller,
            &mInterfaceFunctionTestProtocol1Guid,
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
  DriverBinding->Supported            = DeviceDriver4BindingSupported;
  DriverBinding->Start                = DeviceDriver4BindingStart;
  DriverBinding->Stop                 = DeviceDriver4BindingStop;
  DriverBinding->Version              = 0x30;
  DriverBinding->ImageHandle          = NULL;
  DriverBinding->DriverBindingHandle  = NULL;
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
DeviceDriver4Unload (
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
