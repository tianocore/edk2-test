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

  Mtftp6ServiceBindingENTSTest.c

Abstract:

--*/

#include "Mtftp6ServiceBindingENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gMtftp6ServiceBindingProtocolName[] = L"Mtftp6ServiceBinding";

CHAR16            *gMtftp6ServiceBindingRuntimeInfo;
UINTN             gMtftp6ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gMtftp6ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Mtftp6ServiceBindingCreateChild_EntsTest,
    gMtftp6ServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    Mtftp6ServiceBindingDestroyChild_EntsTest,
    gMtftp6ServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gMtftp6ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Mtftp6ServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Mtftp6ServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Mtftp6 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Mtftp6ServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gMtftp6ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiMtftp6ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gMtftp6ServiceBindingEntsProtocolInterface->ClientName        = gMtftp6ServiceBindingProtocolName;
  gMtftp6ServiceBindingEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gMtftp6ServiceBindingEntsProtocolInterface->ClientGuid        = &gBlackBoxEfiMtftp6ServiceBindingProtocolGuid;
  gMtftp6ServiceBindingEntsProtocolInterface->ClientHandle      = ClientHandle;
  gMtftp6ServiceBindingEntsProtocolInterface->ClientInterface   = NULL;
  gMtftp6ServiceBindingEntsProtocolInterface->EntsInterfaceList = gMtftp6ServiceBindingEntsInterfaceList;
  gMtftp6ServiceBindingEntsProtocolInterface->RuntimeInfo       = gMtftp6ServiceBindingRuntimeInfo;
  gMtftp6ServiceBindingEntsProtocolInterface->RuntimeInfoSize   = gMtftp6ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gMtftp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gMtftp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Mtftp6ServiceBindingENTSTestUnload (
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
                  gMtftp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gMtftp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}
