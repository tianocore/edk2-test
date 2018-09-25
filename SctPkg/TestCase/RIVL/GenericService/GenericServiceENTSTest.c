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
  GenericServiceENTSTest.c

Abstract:

--*/

#include "SctLib.h"
#include "GenericServiceENTSTestCase.h"

static CHAR16     gGenericServiceName[] = L"GS";

CHAR16            *gGenericServiceRuntimeInfo;
UINTN             gGenericServiceRuntimeInfoSize;

ENTS_INTERFACE    gGenericServiceEntsInterfaceList[] = {
  {
    L"MemCmp",
    GS_MemCmp_EntsTest,
    gGSMemCmpArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gGenericServiceEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
GenericServiceENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
GenericServiceENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Generic Service ENTS Test.

Arguments:

  ImageHandle           - The image handle.
  SystemTable           - The system table.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                Status;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;

  SctInitializeDriver (ImageHandle, SystemTable);
  EfiInitializeEntsLib (ImageHandle, SystemTable);

  tBS->HandleProtocol (
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID **) &LoadedImage
        );

  LoadedImage->Unload = GenericServiceENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gGenericServiceEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gGenericServiceEntsProtocolInterface->ClientName        = gGenericServiceName;
  gGenericServiceEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_GENERIC_SERVICE;
  gGenericServiceEntsProtocolInterface->ClientGuid        = NULL;
  gGenericServiceEntsProtocolInterface->ClientHandle      = NULL;
  gGenericServiceEntsProtocolInterface->ClientInterface   = NULL;
  gGenericServiceEntsProtocolInterface->EntsInterfaceList = gGenericServiceEntsInterfaceList;
  gGenericServiceEntsProtocolInterface->RuntimeInfo       = gGenericServiceRuntimeInfo;
  gGenericServiceEntsProtocolInterface->RuntimeInfoSize   = gGenericServiceRuntimeInfoSize;

  return tBS->InstallMultipleProtocolInterfaces (
                &ImageHandle,
                &gEfiEntsProtocolGuid,
                gGenericServiceEntsProtocolInterface,
                NULL
                );
}

EFI_STATUS
EFIAPI
GenericServiceENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  )
/*++

Routine Description:

  Unload routine.

Arguments:

  ImageHandle - The image handle.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;

  Status = tBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gGenericServiceEntsProtocolInterface,
                  NULL
                  );

  if (gGenericServiceEntsProtocolInterface != NULL) {
    tBS->FreePool (gGenericServiceEntsProtocolInterface);
  }

  return Status;
}
