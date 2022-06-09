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

  HttpENTSTest.c

Abstract:

--*/

#include "HttpENTSTestCase.h"

static CHAR16     gHttpProtocolName[]       = L"Http";
CHAR16            *gHttpEntsRuntimeInfo     = NULL;
UINTN             gHttpEntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gHttpEntsInterfaceList[] = {
  {
    L"GetModeData",
    HttpGetModeData_EntsTest,
    gHttpGetModeDataArgField
  },
  {
    L"Configure",
    HttpConfigure_EntsTest,
    gHttpConfigureArgField
  },
  {
    L"Request",
    HttpRequest_EntsTest,
    gHttpRequestArgField
  },
  {
    L"Cancel",
    HttpCancel_EntsTest,
    gHttpCancelArgField
  },
  {
    L"Response",
    HttpResponse_EntsTest,
    gHttpResponseArgField
  },
  {
    L"Poll",
    HttpPoll_EntsTest,
    gHttpPollArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gHttpEntsProtocolInterface = NULL;

EFI_STATUS
HttpENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
HttpENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Http protocol ENTS Test.

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

  SctInitializeDriver (ImageHandle, SystemTable);
  EfiInitializeEntsLib (ImageHandle, SystemTable);

  tBS->HandleProtocol (
        ImageHandle,
        &gBlackBoxEfiLoadedImageProtocolGuid,
        (VOID *) &LoadedImage
        );

  LoadedImage->Unload = HttpENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gHttpEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gHttpEntsProtocolInterface->ClientName        = gHttpProtocolName;
  gHttpEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gHttpEntsProtocolInterface->ClientGuid        = &gBlackBoxEfiHttpProtocolGuid;
  gHttpEntsProtocolInterface->ClientHandle      = NULL;
  gHttpEntsProtocolInterface->ClientInterface   = NULL;
  gHttpEntsProtocolInterface->EntsInterfaceList = gHttpEntsInterfaceList;
  gHttpEntsProtocolInterface->RuntimeInfo       = gHttpEntsRuntimeInfo;
  gHttpEntsProtocolInterface->RuntimeInfoSize   = gHttpEntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gHttpEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gHttpEntsProtocolInterface != NULL) {
    tBS->FreePool (gHttpEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
HttpENTSTestUnload (
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
                  gHttpEntsProtocolInterface,
                  NULL
                  );

  if (gHttpEntsProtocolInterface != NULL) {
    tBS->FreePool (gHttpEntsProtocolInterface);
  }

  return Status;
}
