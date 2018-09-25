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
    RuntimeServicesDriver1.c

Abstract:
    for Loaded Image Protocol Black Box Test

--*/

#include "Efi.h"
#include <Library/EfiTestLib.h>

extern EFI_GUID gBlackBoxEfiLoadedImageProtocolGuid;

EFI_STATUS
EFIAPI
InitializeRuntimeServicesDriver1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
RuntimeServicesDriver1Unload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
EFIAPI
InitializeRuntimeServicesDriver1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImage;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // UnLoad Function Handler
  //
  Status = gtBS->HandleProtocol (
                   ImageHandle,
                   &gBlackBoxEfiLoadedImageProtocolGuid,
                   (VOID*)&LoadedImage
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  LoadedImage->Unload = RuntimeServicesDriver1Unload;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
RuntimeServicesDriver1Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EFI_SUCCESS;
}
