/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Udp4ServiceBindingENTSTest.c

Abstract:

--*/

#include "Udp4ServiceBindingENTSTestCase.h"

static CHAR16     gUdp4ServiceBindingProtocolName[] = L"Udp4ServiceBinding";

CHAR16            *gUdp4ServiceBindingRuntimeInfo;
UINTN             gUdp4ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gUdp4ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Udp4ServiceBindingCreateChild_EntsTest,
    gUdp4ServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    Udp4ServiceBindingDestroyChild_EntsTest,
    gUdp4ServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gUdp4ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Udp4ServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Udp4ServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Udp4 service binding protocol ENTS Test.

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
        (VOID *) &LoadedImage
        );

  LoadedImage->Unload = Udp4ServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **) &gUdp4ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiUdp4ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gUdp4ServiceBindingEntsProtocolInterface->ClientName        = gUdp4ServiceBindingProtocolName;
  gUdp4ServiceBindingEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gUdp4ServiceBindingEntsProtocolInterface->ClientGuid        = &gBlackBoxEfiUdp4ServiceBindingProtocolGuid;
  gUdp4ServiceBindingEntsProtocolInterface->ClientHandle      = ClientHandle;
  gUdp4ServiceBindingEntsProtocolInterface->ClientInterface   = NULL;
  gUdp4ServiceBindingEntsProtocolInterface->EntsInterfaceList = gUdp4ServiceBindingEntsInterfaceList;
  gUdp4ServiceBindingEntsProtocolInterface->RuntimeInfo       = gUdp4ServiceBindingRuntimeInfo;
  gUdp4ServiceBindingEntsProtocolInterface->RuntimeInfoSize   = gUdp4ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gUdp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gUdp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gUdp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Udp4ServiceBindingENTSTestUnload (
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
                  gUdp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gUdp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gUdp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}
