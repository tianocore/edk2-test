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

  Mtftp4ServiceBindingENTSTest.c

Abstract:

--*/

#include "Mtftp4ServiceBindingENTSTestCase.h"

static CHAR16     gMtftp4ServiceBindingProtocolName[] = L"Mtftp4ServiceBinding";

CHAR16            *gMtftp4ServiceBindingRuntimeInfo;
UINTN             gMtftp4ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gMtftp4ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Mtftp4ServiceBindingCreateChild_EntsTest,
    gMtftp4ServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    Mtftp4ServiceBindingDestroyChild_EntsTest,
    gMtftp4ServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gMtftp4ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Mtftp4ServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Mtftp4ServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Mtftp4 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Mtftp4ServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gMtftp4ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiMtftp4ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gMtftp4ServiceBindingEntsProtocolInterface->ClientName        = gMtftp4ServiceBindingProtocolName;
  gMtftp4ServiceBindingEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gMtftp4ServiceBindingEntsProtocolInterface->ClientGuid        = &gBlackBoxEfiMtftp4ServiceBindingProtocolGuid;
  gMtftp4ServiceBindingEntsProtocolInterface->ClientHandle      = ClientHandle;
  gMtftp4ServiceBindingEntsProtocolInterface->ClientInterface   = NULL;
  gMtftp4ServiceBindingEntsProtocolInterface->EntsInterfaceList = gMtftp4ServiceBindingEntsInterfaceList;
  gMtftp4ServiceBindingEntsProtocolInterface->RuntimeInfo       = gMtftp4ServiceBindingRuntimeInfo;
  gMtftp4ServiceBindingEntsProtocolInterface->RuntimeInfoSize   = gMtftp4ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gMtftp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gMtftp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Mtftp4ServiceBindingENTSTestUnload (
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
                  gMtftp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gMtftp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}
