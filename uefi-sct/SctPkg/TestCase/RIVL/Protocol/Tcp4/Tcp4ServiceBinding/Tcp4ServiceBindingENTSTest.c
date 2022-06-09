/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Tcp4ServiceBindingENTSTest.c

Abstract:

--*/

#include "Tcp4ServiceBindingENTSTestCase.h"

static CHAR16     gTcp4ServiceBindingProtocolName[] = L"Tcp4ServiceBinding";

CHAR16            *gTcp4ServiceBindingRuntimeInfo;
UINTN             gTcp4ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gTcp4ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Tcp4ServiceBindingCreateChild_EntsTest,
    gTcp4ServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    Tcp4ServiceBindingDestroyChild_EntsTest,
    gTcp4ServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gTcp4ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
Tcp4ServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Tcp4ServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Tcp4 service binding protocol ENTS Test.

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
  EFI_HANDLE                ClientHandle;

  SctInitializeDriver (ImageHandle, SystemTable);
  EfiInitializeEntsLib (ImageHandle, SystemTable);

  tBS->HandleProtocol (
        ImageHandle,
        &gBlackBoxEfiLoadedImageProtocolGuid,
        (VOID **) &LoadedImage
        );

  LoadedImage->Unload = Tcp4ServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gTcp4ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiTcp4ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gTcp4ServiceBindingEntsProtocolInterface->ClientName        = gTcp4ServiceBindingProtocolName;
  gTcp4ServiceBindingEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gTcp4ServiceBindingEntsProtocolInterface->ClientGuid        = &gBlackBoxEfiTcp4ServiceBindingProtocolGuid;
  gTcp4ServiceBindingEntsProtocolInterface->ClientHandle      = ClientHandle;
  gTcp4ServiceBindingEntsProtocolInterface->ClientInterface   = NULL;
  gTcp4ServiceBindingEntsProtocolInterface->EntsInterfaceList = gTcp4ServiceBindingEntsInterfaceList;
  gTcp4ServiceBindingEntsProtocolInterface->RuntimeInfo       = gTcp4ServiceBindingRuntimeInfo;
  gTcp4ServiceBindingEntsProtocolInterface->RuntimeInfoSize   = gTcp4ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gTcp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gTcp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Tcp4ServiceBindingENTSTestUnload (
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
                  gTcp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gTcp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}
