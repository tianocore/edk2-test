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

  ArpServiceBindingENTSTest.c

Abstract:

--*/

#include "ArpServiceBindingENTSTestCase.h"

static CHAR16     gArpServiceBindingProtocolName[] = L"ArpServiceBinding";

CHAR16            *gArpServiceBindingRuntimeInfo;
UINTN             gArpServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gArpServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    ArpServiceBindingCreateChild_EntsTest,
    gArpServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    ArpServiceBindingDestroyChild_EntsTest,
    gArpServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gArpServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
ArpServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
ArpServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for ARP ServiceBinding protocol ENTS Test.

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

  LoadedImage->Unload = ArpServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gArpServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiArpServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gArpServiceBindingEntsProtocolInterface->ClientName         = gArpServiceBindingProtocolName;
  gArpServiceBindingEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gArpServiceBindingEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiArpServiceBindingProtocolGuid;
  gArpServiceBindingEntsProtocolInterface->ClientHandle       = ClientHandle;
  gArpServiceBindingEntsProtocolInterface->ClientInterface    = NULL;
  gArpServiceBindingEntsProtocolInterface->EntsInterfaceList  = gArpServiceBindingEntsInterfaceList;
  gArpServiceBindingEntsProtocolInterface->RuntimeInfo        = gArpServiceBindingRuntimeInfo;
  gArpServiceBindingEntsProtocolInterface->RuntimeInfoSize    = gArpServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gArpServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gArpServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gArpServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
ArpServiceBindingENTSTestUnload (
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
                  gArpServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gArpServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gArpServiceBindingEntsProtocolInterface);
  }

  return Status;
}
