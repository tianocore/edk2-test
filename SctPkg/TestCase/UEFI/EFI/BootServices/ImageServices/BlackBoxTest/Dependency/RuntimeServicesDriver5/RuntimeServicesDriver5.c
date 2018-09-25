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

  RuntimeServicesDriver5.c

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
} RUNTIME_SERVICES_DRIVER_5_PRIVATE_DATA;

RUNTIME_SERVICES_DRIVER_5_PRIVATE_DATA   mPrivateData;

EFI_STATUS
EFIAPI
InitializeRuntimeServicesDriver5 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
RuntimeServicesDriver5Unload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
EFIAPI
InitializeRuntimeServicesDriver5 (
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

  LoadedImageInfoPtr->Unload = RuntimeServicesDriver5Unload;

  gtBS->InstallProtocolInterface (
          &mPrivateData.Handle,
          &mImageTestNoInterfaceProtocol3Guid,
          EFI_NATIVE_INTERFACE,
          NULL
          );

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mImageTestNoInterfaceProtocol4Guid,
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
          &mImageTestNoInterfaceProtocol4Guid,
          (VOID **) NULL,
          ImageHandle,
          NULL,
          EFI_OPEN_PROTOCOL_TEST_PROTOCOL
          );

  gtBS->FreePool (HandleBuffer);

  gtBS->Exit (ImageHandle, EFI_SUCCESS, 0, NULL);

  //
  //the code should not arrive here so we add a variable to verify if the Exit
  //return control to StartImage correctly.
  //

  //
  //first make sure there is no duplicated variable exist so we first delete once.
  //
  gtRT->SetVariable (
          IMAGE_RUNTIMESERVICESDRIVER5_CALLED_AFTER_EXIT,
          &mImageTestVariableVendorGuid,
          EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
          0,
          (VOID*)&ImageHandle
          );

  //
  //then call SetVariable to set a variable.
  //

  gtRT->SetVariable (
          IMAGE_RUNTIMESERVICESDRIVER5_CALLED_AFTER_EXIT,
          &mImageTestVariableVendorGuid,
          EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
          sizeof(EFI_HANDLE),
          (VOID*)&ImageHandle
          );

  //
  // actually should not arrive here. Just to pass compiling.
  //
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
RuntimeServicesDriver5Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
          mPrivateData.Handle,
          &mImageTestNoInterfaceProtocol3Guid,
          NULL
          );
  gtBS->CloseProtocol (
          mPrivateData.OpenHandle,
          &mImageTestNoInterfaceProtocol4Guid,
          ImageHandle,
          NULL
          );

  return EFI_SUCCESS;
}
