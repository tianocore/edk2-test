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

  MnpSBENTSTest.c

Abstract:

--*/

#include "MnpSBENTSTestCase.h"

static CHAR16     gMnpServiceBindingProtocolName[] = L"MnpServiceBinding";

CHAR16            *gMnpServiceBindingRuntimeInfo;
UINTN             gMnpServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gMnpServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    MnpCreateChild_EntsTest,
    gMnpCreateChildArgField
  },
  {
    L"DestroyChild",
    MnpDestroyChild_EntsTest,
    gMnpDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gMnpServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
MnpSBENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
MnpSBENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Mnp service binding protocol ENTS Test.

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

  LoadedImage->Unload = MnpSBENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gMnpServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiManagedNetworkServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gMnpServiceBindingEntsProtocolInterface->ClientName         = gMnpServiceBindingProtocolName;
  gMnpServiceBindingEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gMnpServiceBindingEntsProtocolInterface->ClientHandle       = ClientHandle;
  gMnpServiceBindingEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiManagedNetworkServiceBindingProtocolGuid;
  gMnpServiceBindingEntsProtocolInterface->ClientInterface    = NULL;
  gMnpServiceBindingEntsProtocolInterface->EntsInterfaceList  = gMnpServiceBindingEntsInterfaceList;
  gMnpServiceBindingEntsProtocolInterface->RuntimeInfo        = gMnpServiceBindingRuntimeInfo;
  gMnpServiceBindingEntsProtocolInterface->RuntimeInfoSize    = gMnpServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gMnpServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gMnpServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gMnpServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
MnpSBENTSTestUnload (
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
        gMnpServiceBindingEntsProtocolInterface,
        NULL
        );
  if (gMnpServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gMnpServiceBindingEntsProtocolInterface);
  }

  return EFI_SUCCESS;
}
