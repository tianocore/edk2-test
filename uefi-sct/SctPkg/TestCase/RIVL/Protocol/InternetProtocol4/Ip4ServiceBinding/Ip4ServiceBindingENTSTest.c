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

  Ip4ServiceBindingENTSTest.c

Abstract:

--*/

#include "Ip4ServiceBindingENTSTestCase.h"

static CHAR16     gIp4ServiceBindingProtocolName[] = L"Ip4ServiceBinding";

CHAR16            *gIp4ServiceBindingRuntimeInfo;
UINTN             gIp4ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gIp4ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Ip4ServiceBindingCreateChild_EntsTest,
    gIp4ServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    Ip4ServiceBindingDestroyChild_EntsTest,
    gIp4ServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gIp4ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Ip4ServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Ip4ServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Ip4 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Ip4ServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gIp4ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiIp4ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gIp4ServiceBindingEntsProtocolInterface->ClientName         = gIp4ServiceBindingProtocolName;
  gIp4ServiceBindingEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gIp4ServiceBindingEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiIp4ServiceBindingProtocolGuid;
  gIp4ServiceBindingEntsProtocolInterface->ClientHandle       = ClientHandle;
  gIp4ServiceBindingEntsProtocolInterface->ClientInterface    = NULL;
  gIp4ServiceBindingEntsProtocolInterface->EntsInterfaceList  = gIp4ServiceBindingEntsInterfaceList;
  gIp4ServiceBindingEntsProtocolInterface->RuntimeInfo        = gIp4ServiceBindingRuntimeInfo;
  gIp4ServiceBindingEntsProtocolInterface->RuntimeInfoSize    = gIp4ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gIp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gIp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Ip4ServiceBindingENTSTestUnload (
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
                  gIp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gIp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}
