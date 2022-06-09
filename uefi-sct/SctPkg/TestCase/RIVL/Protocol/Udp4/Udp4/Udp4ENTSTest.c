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

  Udp4ENTSTest.c

Abstract:

--*/

#include "Udp4ENTSTestCase.h"

static CHAR16     gUdp4ProtocolName[]       = L"Udp4";
CHAR16            *gUdp4EntsRuntimeInfo     = NULL;
UINTN             gUdp4EntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gUdp4EntsInterfaceList[] = {
  {
    L"GetModeData",
    Udp4GetModeData_EntsTest,
    gUdp4GetModeDataArgField
  },
  {
    L"Configure",
    Udp4Configure_EntsTest,
    gUdp4ConfigureArgField
  },
  {
    L"Groups",
    Udp4Groups_EntsTest,
    gUdp4GroupsArgField
  },
  {
    L"Routes",
    Udp4Routes_EntsTest,
    gUdp4RoutesArgField
  },
  {
    L"Poll",
    Udp4Poll_EntsTest,
    gUdp4PollArgField
  },
  {
    L"Receive",
    Udp4Receive_EntsTest,
    gUdp4ReceiveArgField
  },
  {
    L"Transmit",
    Udp4Transmit_EntsTest,
    gUdp4TransmitArgField
  },
  {
    L"Cancel",
    Udp4Cancel_EntsTest,
    gUdp4CancelArgField
  },
  {
    L"SignalRecycleEvent",
    Udp4SignalRecycleEvent_EntsTest,
    gUdp4SignalRecycleEventArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gUdp4EntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Udp4ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Udp4ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Udp4 protocol ENTS Test.

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

  LoadedImage->Unload = Udp4ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **) &gUdp4EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gUdp4EntsProtocolInterface->ClientName        = gUdp4ProtocolName;
  gUdp4EntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gUdp4EntsProtocolInterface->ClientGuid        = &gBlackBoxEfiUdp4ProtocolGuid;
  gUdp4EntsProtocolInterface->ClientHandle      = NULL;
  gUdp4EntsProtocolInterface->ClientInterface   = NULL;
  gUdp4EntsProtocolInterface->EntsInterfaceList = gUdp4EntsInterfaceList;
  gUdp4EntsProtocolInterface->RuntimeInfo       = gUdp4EntsRuntimeInfo;
  gUdp4EntsProtocolInterface->RuntimeInfoSize   = gUdp4EntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gUdp4EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gUdp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gUdp4EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Udp4ENTSTestUnload (
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
                  gUdp4EntsProtocolInterface,
                  NULL
                  );

  if (gUdp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gUdp4EntsProtocolInterface);
  }

  return Status;
}
