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

  Udp6ServiceBindingENTSTest.c

Abstract:

--*/

#include "Udp6ServiceBindingENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gUdp6ServiceBindingProtocolName[] = L"Udp6ServiceBinding";

CHAR16            *gUdp6ServiceBindingRuntimeInfo;
UINTN             gUdp6ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gUdp6ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Udp6ServiceBindingCreateChild_EntsTest,
    gUdp6ServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    Udp6ServiceBindingDestroyChild_EntsTest,
    gUdp6ServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gUdp6ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
Udp6ServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Udp6ServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Udp6 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Udp6ServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gUdp6ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiUdp6ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gUdp6ServiceBindingEntsProtocolInterface->ClientName        = gUdp6ServiceBindingProtocolName;
  gUdp6ServiceBindingEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gUdp6ServiceBindingEntsProtocolInterface->ClientGuid        = &gBlackBoxEfiUdp6ServiceBindingProtocolGuid;
  gUdp6ServiceBindingEntsProtocolInterface->ClientHandle      = ClientHandle;
  gUdp6ServiceBindingEntsProtocolInterface->ClientInterface   = NULL;
  gUdp6ServiceBindingEntsProtocolInterface->EntsInterfaceList = gUdp6ServiceBindingEntsInterfaceList;
  gUdp6ServiceBindingEntsProtocolInterface->RuntimeInfo       = gUdp6ServiceBindingRuntimeInfo;
  gUdp6ServiceBindingEntsProtocolInterface->RuntimeInfoSize   = gUdp6ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gUdp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gUdp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gUdp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Udp6ServiceBindingENTSTestUnload (
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
                  gUdp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gUdp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gUdp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}
