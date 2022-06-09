/** @file

  Copyright 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  HttpServiceBindingENTSTest.c

Abstract:

--*/

#include "HttpServiceBindingENTSTestCase.h"

static CHAR16     gHttpServiceBindingProtocolName[] = L"HttpServiceBinding";

CHAR16            *gHttpServiceBindingRuntimeInfo;
UINTN             gHttpServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gHttpServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    HttpServiceBindingCreateChild_EntsTest,
    gHttpServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    HttpServiceBindingDestroyChild_EntsTest,
    gHttpServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gHttpServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
HttpServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
HttpServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Http service binding protocol ENTS Test.

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

  LoadedImage->Unload = HttpServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gHttpServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiHttpServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gHttpServiceBindingEntsProtocolInterface->ClientName        = gHttpServiceBindingProtocolName;
  gHttpServiceBindingEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gHttpServiceBindingEntsProtocolInterface->ClientGuid        = &gBlackBoxEfiHttpServiceBindingProtocolGuid;
  gHttpServiceBindingEntsProtocolInterface->ClientHandle      = ClientHandle;
  gHttpServiceBindingEntsProtocolInterface->ClientInterface   = NULL;
  gHttpServiceBindingEntsProtocolInterface->EntsInterfaceList = gHttpServiceBindingEntsInterfaceList;
  gHttpServiceBindingEntsProtocolInterface->RuntimeInfo       = gHttpServiceBindingRuntimeInfo;
  gHttpServiceBindingEntsProtocolInterface->RuntimeInfoSize   = gHttpServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gHttpServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gHttpServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gHttpServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
HttpServiceBindingENTSTestUnload (
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
                  gHttpServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gHttpServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gHttpServiceBindingEntsProtocolInterface);
  }

  return Status;
}
