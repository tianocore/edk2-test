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

  Ip4ENTSTest.c

Abstract:

--*/

#include "Ip4ENTSTestCase.h"

static CHAR16     gIp4ProtocolName[] = L"Ip4";

CHAR16            *gIp4RuntimeInfo;
UINTN             gIp4RuntimeInfoSize;

ENTS_INTERFACE    gIp4EntsInterfaceList[] = {
  {
    L"GetModeData",
    Ip4GetModeData_EntsTest,
    gIp4GetModeDataArgField
  },
  {
    L"Configure",
    Ip4Configure_EntsTest,
    gIp4ConfigureArgField
  },
  {
    L"Groups",
    Ip4Groups_EntsTest,
    gIp4GroupsArgField
  },
  {
    L"Routes",
    Ip4Routes_EntsTest,
    gIp4RoutesArgField
  },
  {
    L"Transmit",
    Ip4Transmit_EntsTest,
    gIp4TransmitArgField
  },
  {
    L"Receive",
    Ip4Receive_EntsTest,
    gIp4ReceiveArgField
  },
  {
    L"Cancel",
    Ip4Cancel_EntsTest,
    gIp4CancelArgField
  },
  {
    L"Poll",
    Ip4Poll_EntsTest,
    gIp4PollArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gIp4EntsProtocolInterface = NULL;

EFI_STATUS
Ip4ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Ip4ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Ip4 protocol ENTS Test.

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
        (VOID **) &LoadedImage
        );

  LoadedImage->Unload = Ip4ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gIp4EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gIp4EntsProtocolInterface->ClientName         = gIp4ProtocolName;
  gIp4EntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gIp4EntsProtocolInterface->ClientGuid         = &gBlackBoxEfiIp4ProtocolGuid;
  gIp4EntsProtocolInterface->ClientHandle       = NULL;
  gIp4EntsProtocolInterface->ClientInterface    = NULL;
  gIp4EntsProtocolInterface->EntsInterfaceList  = gIp4EntsInterfaceList;
  gIp4EntsProtocolInterface->RuntimeInfo        = gIp4RuntimeInfo;
  gIp4EntsProtocolInterface->RuntimeInfoSize    = gIp4RuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gIp4EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gIp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Ip4ENTSTestUnload (
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
                  gIp4EntsProtocolInterface,
                  NULL
                  );

  if (gIp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4EntsProtocolInterface);
  }

  return Status;
}
