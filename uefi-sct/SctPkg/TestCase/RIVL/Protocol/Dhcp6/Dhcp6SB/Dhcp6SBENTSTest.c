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

  Dhcp6SBENTSTest.c

Abstract:

--*/

#include "Dhcp6SBENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gDhcp6ServiceBindingProtocolName[] = L"Dhcp6ServiceBinding";

CHAR16            *gDhcp6ServiceBindingRuntimeInfo;
UINTN             gDhcp6ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gDhcp6ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Dhcp6CreateChild_EntsTest,
    gDhcp6CreateChildArgField
  },
  {
    L"DestroyChild",
    Dhcp6DestroyChild_EntsTest,
    gDhcp6DestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gDhcp6ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
Dhcp6SBENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Dhcp6SBENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Dhcp6 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Dhcp6SBENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gDhcp6ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiDhcp6ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gDhcp6ServiceBindingEntsProtocolInterface->ClientName         = gDhcp6ServiceBindingProtocolName;
  gDhcp6ServiceBindingEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gDhcp6ServiceBindingEntsProtocolInterface->ClientHandle       = ClientHandle;
  gDhcp6ServiceBindingEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiDhcp6ServiceBindingProtocolGuid;
  gDhcp6ServiceBindingEntsProtocolInterface->ClientInterface    = NULL;
  gDhcp6ServiceBindingEntsProtocolInterface->EntsInterfaceList  = gDhcp6ServiceBindingEntsInterfaceList;
  gDhcp6ServiceBindingEntsProtocolInterface->RuntimeInfo        = gDhcp6ServiceBindingRuntimeInfo;
  gDhcp6ServiceBindingEntsProtocolInterface->RuntimeInfoSize    = gDhcp6ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gDhcp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gDhcp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Dhcp6SBENTSTestUnload (
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
        gDhcp6ServiceBindingEntsProtocolInterface,
        NULL
        );
  if (gDhcp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp6ServiceBindingEntsProtocolInterface);
  }

  return EFI_SUCCESS;
}
