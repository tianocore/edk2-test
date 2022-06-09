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

  Ip6ENTSTest.c

Abstract:

--*/

#include "Ip6ENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gIp6ProtocolName[] = L"Ip6";

CHAR16            *gIp6RuntimeInfo;
UINTN             gIp6RuntimeInfoSize;

ENTS_INTERFACE    gIp6EntsInterfaceList[] = {
  {
    L"GetModeData",
    Ip6GetModeData_EntsTest,
    gIp6GetModeDataArgField
  },
  {
    L"Configure",
    Ip6Configure_EntsTest,
    gIp6ConfigureArgField
  },
  {
    L"Groups",
    Ip6Groups_EntsTest,
    gIp6GroupsArgField
  },
  {
    L"Routes",
    Ip6Routes_EntsTest,
    gIp6RoutesArgField
  },
  {
    L"Neighbors",
    Ip6Neighbors_EntsTest,
    gIp6NeighborsArgField
  },
  {
    L"Transmit",
    Ip6Transmit_EntsTest,
    gIp6TransmitArgField
  },
  {
    L"Receive",
    Ip6Receive_EntsTest,
    gIp6ReceiveArgField
  },
  {
    L"Cancel",
    Ip6Cancel_EntsTest,
    gIp6CancelArgField
  },
  {
    L"Poll",
    Ip6Poll_EntsTest,
    gIp6PollArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gIp6EntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Ip6ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Ip6ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Ip6 protocol ENTS Test.

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

  LoadedImage->Unload = Ip6ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gIp6EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gIp6EntsProtocolInterface->ClientName         = gIp6ProtocolName;
  gIp6EntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gIp6EntsProtocolInterface->ClientGuid         = &gBlackBoxEfiIp6ProtocolGuid;
  gIp6EntsProtocolInterface->ClientHandle       = NULL;
  gIp6EntsProtocolInterface->ClientInterface    = NULL;
  gIp6EntsProtocolInterface->EntsInterfaceList  = gIp6EntsInterfaceList;
  gIp6EntsProtocolInterface->RuntimeInfo        = gIp6RuntimeInfo;
  gIp6EntsProtocolInterface->RuntimeInfoSize    = gIp6RuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gIp6EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gIp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gIp6EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Ip6ENTSTestUnload (
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
                  gIp6EntsProtocolInterface,
                  NULL
                  );

  if (gIp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gIp6EntsProtocolInterface);
  }

  return Status;
}
