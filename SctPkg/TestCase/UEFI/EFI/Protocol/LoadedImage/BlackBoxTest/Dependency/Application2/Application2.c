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

  Application2.c

Abstract:

  for Loaded Image Protocol Black Box Test

--*/

#include "LoadedImageBBTestProtocolDefinition.h"
#include <Library/EfiTestLib.h>

//
// data definition here
//

EFI_STATUS
EFIAPI
InitializeEfiApplication2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );


EFI_STATUS
EFIAPI
InitializeEfiApplication2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              Handle;
  UINTN                   *Options;

  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;

  Handle = NULL;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  Status = gtBS->HandleProtocol (
                   ImageHandle,
                   &gBlackBoxEfiLoadedImageProtocolGuid,
                   (VOID **) &LoadedImage
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Options = (UINTN*)(LoadedImage->LoadOptions);

  if (Options == NULL) {
    return EFI_SUCCESS;
  }

  if (*Options == 1) {

    gtBS->InstallProtocolInterface (
            &Handle,
            &mLoadedImageTestNoInterfaceProtocol1Guid,
            EFI_NATIVE_INTERFACE,
            NULL
            );
  } else if (*Options == 2) {
    gtBS->InstallProtocolInterface (
            &Handle,
            &mLoadedImageTestNoInterfaceProtocol2Guid,
            EFI_NATIVE_INTERFACE,
            NULL
            );
  }


  gtBS->UninstallProtocolInterface (
          Handle,
          &mLoadedImageTestNoInterfaceProtocol1Guid,
          NULL
          );
  gtBS->UninstallProtocolInterface (
          Handle,
          &mLoadedImageTestNoInterfaceProtocol2Guid,
          NULL
          );
  return EFI_SUCCESS;
}

