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

  BootServiceDriver3.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include <Library/EfiTestLib.h>

//
// data definition here
//
typedef struct {
  EFI_HANDLE      Handle;
  EFI_HANDLE      OpenHandle;
} BOOT_SERVICES_DRIVER_3_PRIVATE_DATA;

BOOT_SERVICES_DRIVER_3_PRIVATE_DATA   mPrivateData;

EFI_STATUS
EFIAPI
InitializeBootServicesDriver3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BootServicesDriver3Unload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
EFIAPI
InitializeBootServicesDriver3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_HANDLE                            *HandleBuffer;
  UINTN                                 NoHandles;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImageInfoPtr;

  mPrivateData.Handle = NULL;
  mPrivateData.OpenHandle = NULL;
  HandleBuffer = NULL;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // UnLoad Function Handler
  //
  gtBS->HandleProtocol (
          ImageHandle,
          &gEfiLoadedImageProtocolGuid,
          (VOID*)&LoadedImageInfoPtr
          );

  LoadedImageInfoPtr->Unload = BootServicesDriver3Unload;

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
BootServicesDriver3Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
          mPrivateData.Handle,
          &mImageTestNoInterfaceProtocol1Guid,
          NULL
          );

  return EFI_DEVICE_ERROR;
}
