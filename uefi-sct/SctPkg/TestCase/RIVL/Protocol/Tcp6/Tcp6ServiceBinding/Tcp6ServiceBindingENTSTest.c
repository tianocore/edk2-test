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

  Tcp6ServiceBindingENTSTest.c

Abstract:

--*/

#include "Tcp6ServiceBindingENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gTcp6ServiceBindingProtocolName[] = L"Tcp6ServiceBinding";

CHAR16            *gTcp6ServiceBindingRuntimeInfo;
UINTN             gTcp6ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gTcp6ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Tcp6ServiceBindingCreateChild_EntsTest,
    gTcp6ServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    Tcp6ServiceBindingDestroyChild_EntsTest,
    gTcp6ServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gTcp6ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
Tcp6ServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Tcp6ServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Tcp6 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Tcp6ServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **) &gTcp6ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiTcp6ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gTcp6ServiceBindingEntsProtocolInterface->ClientName        = gTcp6ServiceBindingProtocolName;
  gTcp6ServiceBindingEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gTcp6ServiceBindingEntsProtocolInterface->ClientGuid        = &gBlackBoxEfiTcp6ServiceBindingProtocolGuid;
  gTcp6ServiceBindingEntsProtocolInterface->ClientHandle      = ClientHandle;
  gTcp6ServiceBindingEntsProtocolInterface->ClientInterface   = NULL;
  gTcp6ServiceBindingEntsProtocolInterface->EntsInterfaceList = gTcp6ServiceBindingEntsInterfaceList;
  gTcp6ServiceBindingEntsProtocolInterface->RuntimeInfo       = gTcp6ServiceBindingRuntimeInfo;
  gTcp6ServiceBindingEntsProtocolInterface->RuntimeInfoSize   = gTcp6ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gTcp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gTcp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Tcp6ServiceBindingENTSTestUnload (
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
                  gTcp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gTcp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}
