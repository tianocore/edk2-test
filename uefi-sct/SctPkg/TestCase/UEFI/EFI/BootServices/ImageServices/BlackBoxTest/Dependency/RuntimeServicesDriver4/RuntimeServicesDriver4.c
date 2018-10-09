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

  RuntimeServicesDriver4.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include <Library/EfiTestLib.h>

#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
//
// data definition here
//
typedef struct {
  EFI_HANDLE                  Handle;
  EFI_HANDLE                  OpenHandle;
  EFI_HANDLE                  ImageHandle;
  EFI_DRIVER_BINDING_PROTOCOL DriverBinding;
} BOOT_SERVICES_DRIVER_4_PRIVATE_DATA;

BOOT_SERVICES_DRIVER_4_PRIVATE_DATA   mPrivateData;

EFI_STATUS
EFIAPI
InitializeRuntimeServicesDriver4 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
RuntimeServicesDriver4BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
RuntimeServicesDriver4BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
RuntimeServicesDriver4BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );

VOID
InitializeDriverBinding (
  OUT EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  );

EFI_STATUS
EFIAPI
RuntimeServicesDriver4Unload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
EFIAPI
InitializeRuntimeServicesDriver4 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_HANDLE                            *HandleBuffer;
  UINTN                                 NoHandles;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // init
  //
  HandleBuffer = NULL;
  gtBS->SetMem (&mPrivateData,sizeof (BOOT_SERVICES_DRIVER_4_PRIVATE_DATA), 0);

  mPrivateData.ImageHandle = ImageHandle;

  InitializeDriverBinding (&(mPrivateData.DriverBinding));

  Status = gtBS->InstallProtocolInterface (
             &ImageHandle,
             &gEfiDriverBindingProtocolGuid,
             EFI_NATIVE_INTERFACE,
             &(mPrivateData.DriverBinding)
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  mPrivateData.DriverBinding.ImageHandle = ImageHandle;
  mPrivateData.DriverBinding.DriverBindingHandle = ImageHandle;

  gtBS->InstallProtocolInterface (
          &mPrivateData.Handle,
          &mImageTestNoInterfaceProtocol1Guid,
          EFI_NATIVE_INTERFACE,
          NULL
          );

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mImageTestNoInterfaceProtocol2Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status)) {
    return EFI_SUCCESS;
  }

  mPrivateData.OpenHandle = HandleBuffer[0];
  gtBS->OpenProtocol (
          mPrivateData.OpenHandle,
          &mImageTestNoInterfaceProtocol2Guid,
          (VOID **) NULL,
          ImageHandle,
          NULL,
          EFI_OPEN_PROTOCOL_TEST_PROTOCOL
          );

  gtBS->FreePool (HandleBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
RuntimeServicesDriver4BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS        Status;


  Status = gtBS->OpenProtocol (
                   Controller,
                   &mImageTestNoInterfaceProtocol3Guid,
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
RuntimeServicesDriver4BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS        Status;
  VOID              *ProtInst;

  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImageInfoPtr;

  Status = gtBS->OpenProtocol (
                   Controller,
                   &mImageTestNoInterfaceProtocol3Guid,
                   (VOID **) &ProtInst,
                   This->DriverBindingHandle,
                   Controller,
                   EFI_OPEN_PROTOCOL_BY_DRIVER
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // UnLoad Function Handler
  //
  gtBS->HandleProtocol (
          mPrivateData.ImageHandle,
          &gEfiLoadedImageProtocolGuid,
          (VOID*)&LoadedImageInfoPtr
          );

  LoadedImageInfoPtr->Unload = RuntimeServicesDriver4Unload;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
RuntimeServicesDriver4BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  gtBS->CloseProtocol (
          Controller,
          &mImageTestNoInterfaceProtocol3Guid,
          This->DriverBindingHandle,
          Controller
          );
  return EFI_SUCCESS;
}

VOID
InitializeDriverBinding (
  OUT EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  )
{
  DriverBinding->Supported            = RuntimeServicesDriver4BindingSupported;
  DriverBinding->Start                = RuntimeServicesDriver4BindingStart;
  DriverBinding->Stop                 = RuntimeServicesDriver4BindingStop;
  DriverBinding->Version              = 0x10;
  DriverBinding->ImageHandle          = NULL;
  DriverBinding->DriverBindingHandle  = NULL;
}


EFI_STATUS
EFIAPI
RuntimeServicesDriver4Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
          ImageHandle,
          &gEfiDriverBindingProtocolGuid,
          &(mPrivateData.DriverBinding)
          );
  gtBS->UninstallProtocolInterface (
          mPrivateData.Handle,
          &mImageTestNoInterfaceProtocol1Guid,
          NULL
          );
  gtBS->CloseProtocol (
          mPrivateData.OpenHandle,
          &mImageTestNoInterfaceProtocol2Guid,
          ImageHandle,
          NULL
          );

  return EFI_SUCCESS;
}
