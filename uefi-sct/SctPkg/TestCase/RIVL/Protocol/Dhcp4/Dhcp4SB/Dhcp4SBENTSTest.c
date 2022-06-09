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

  Dhcp4SBENTSTest.c

Abstract:

--*/

#include "Dhcp4SBENTSTestCase.h"

static CHAR16     gDhcp4ServiceBindingProtocolName[] = L"Dhcp4ServiceBinding";

CHAR16            *gDhcp4ServiceBindingRuntimeInfo;
UINTN             gDhcp4ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gDhcp4ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Dhcp4CreateChild_EntsTest,
    gDhcp4CreateChildArgField
  },
  {
    L"DestroyChild",
    Dhcp4DestroyChild_EntsTest,
    gDhcp4DestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gDhcp4ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Dhcp4SBENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Dhcp4SBENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Dhcp4 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Dhcp4SBENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gDhcp4ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiDhcp4ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gDhcp4ServiceBindingEntsProtocolInterface->ClientName         = gDhcp4ServiceBindingProtocolName;
  gDhcp4ServiceBindingEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gDhcp4ServiceBindingEntsProtocolInterface->ClientHandle       = ClientHandle;
  gDhcp4ServiceBindingEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiDhcp4ServiceBindingProtocolGuid;
  gDhcp4ServiceBindingEntsProtocolInterface->ClientInterface    = NULL;
  gDhcp4ServiceBindingEntsProtocolInterface->EntsInterfaceList  = gDhcp4ServiceBindingEntsInterfaceList;
  gDhcp4ServiceBindingEntsProtocolInterface->RuntimeInfo        = gDhcp4ServiceBindingRuntimeInfo;
  gDhcp4ServiceBindingEntsProtocolInterface->RuntimeInfoSize    = gDhcp4ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gDhcp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gDhcp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Dhcp4SBENTSTestUnload (
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
  tBS->UninstallMultipleProtocolInterfaces (
        ImageHandle,
        &gEfiEntsProtocolGuid,
        gDhcp4ServiceBindingEntsProtocolInterface,
        NULL
        );
  if (gDhcp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp4ServiceBindingEntsProtocolInterface);
  }

  return EFI_SUCCESS;
}
