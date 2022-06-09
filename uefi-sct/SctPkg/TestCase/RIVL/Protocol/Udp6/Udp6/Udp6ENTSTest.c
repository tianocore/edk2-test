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

  Udp6ENTSTest.c

Abstract:

--*/

#include "Udp6ENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gUdp6ProtocolName[]       = L"Udp6";
CHAR16            *gUdp6EntsRuntimeInfo     = NULL;
UINTN             gUdp6EntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gUdp6EntsInterfaceList[] = {
  {
    L"GetModeData",
    Udp6GetModeData_EntsTest,
    gUdp6GetModeDataArgField
  },
  {
    L"Configure",
    Udp6Configure_EntsTest,
    gUdp6ConfigureArgField
  },
  {
    L"Groups",
    Udp6Groups_EntsTest,
    gUdp6GroupsArgField
  },
  {
    L"Poll",
    Udp6Poll_EntsTest,
    gUdp6PollArgField
  },
  {
    L"Receive",
    Udp6Receive_EntsTest,
    gUdp6ReceiveArgField
  },
  {
    L"Transmit",
    Udp6Transmit_EntsTest,
    gUdp6TransmitArgField
  },
  {
    L"Cancel",
    Udp6Cancel_EntsTest,
    gUdp6CancelArgField
  },
  {
    L"SignalRecycleEvent",
    Udp6SignalRecycleEvent_EntsTest,
    gUdp6SignalRecycleEventArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gUdp6EntsProtocolInterface = NULL;

EFI_STATUS
Udp6ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Udp6ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Udp6 protocol ENTS Test.

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

  LoadedImage->Unload = Udp6ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gUdp6EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gUdp6EntsProtocolInterface->ClientName        = gUdp6ProtocolName;
  gUdp6EntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gUdp6EntsProtocolInterface->ClientGuid        = &gBlackBoxEfiUdp6ProtocolGuid;
  gUdp6EntsProtocolInterface->ClientHandle      = NULL;
  gUdp6EntsProtocolInterface->ClientInterface   = NULL;
  gUdp6EntsProtocolInterface->EntsInterfaceList = gUdp6EntsInterfaceList;
  gUdp6EntsProtocolInterface->RuntimeInfo       = gUdp6EntsRuntimeInfo;
  gUdp6EntsProtocolInterface->RuntimeInfoSize   = gUdp6EntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gUdp6EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gUdp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gUdp6EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Udp6ENTSTestUnload (
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
                  gUdp6EntsProtocolInterface,
                  NULL
                  );

  if (gUdp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gUdp6EntsProtocolInterface);
  }

  return Status;
}
