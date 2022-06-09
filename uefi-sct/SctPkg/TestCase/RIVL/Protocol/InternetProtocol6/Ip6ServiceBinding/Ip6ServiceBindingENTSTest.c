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

  Ip6ServiceBindingENTSTest.c

Abstract:

--*/

#include "Ip6ServiceBindingENTSTestCase.h"
#include "EfiTest.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gIp6ServiceBindingProtocolName[] = L"Ip6ServiceBinding";

CHAR16            *gIp6ServiceBindingRuntimeInfo;
UINTN             gIp6ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gIp6ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Ip6ServiceBindingCreateChild_EntsTest,
    gIp6ServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    Ip6ServiceBindingDestroyChild_EntsTest,
    gIp6ServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gIp6ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Ip6ServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Ip6ServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Ip6 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Ip6ServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gIp6ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiIp6ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gIp6ServiceBindingEntsProtocolInterface->ClientName         = gIp6ServiceBindingProtocolName;
  gIp6ServiceBindingEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gIp6ServiceBindingEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiIp6ServiceBindingProtocolGuid;
  gIp6ServiceBindingEntsProtocolInterface->ClientHandle       = ClientHandle;
  gIp6ServiceBindingEntsProtocolInterface->ClientInterface    = NULL;
  gIp6ServiceBindingEntsProtocolInterface->EntsInterfaceList  = gIp6ServiceBindingEntsInterfaceList;
  gIp6ServiceBindingEntsProtocolInterface->RuntimeInfo        = gIp6ServiceBindingRuntimeInfo;
  gIp6ServiceBindingEntsProtocolInterface->RuntimeInfoSize    = gIp6ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gIp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gIp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gIp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Ip6ServiceBindingENTSTestUnload (
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
                  gIp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gIp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gIp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}
