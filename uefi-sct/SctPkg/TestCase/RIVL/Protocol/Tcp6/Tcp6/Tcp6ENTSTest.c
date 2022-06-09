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

  Tcp6ENTSTest.c

Abstract:

--*/

#include "Tcp6ENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gTcp6ProtocolName[]       = L"Tcp6";
CHAR16            *gTcp6EntsRuntimeInfo     = NULL;
UINTN             gTcp6EntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gTcp6EntsInterfaceList[] = {
  {
    L"GetModeData",
    Tcp6GetModeData_EntsTest,
    gTcp6GetModeDataArgField
  },
  {
    L"Configure",
    Tcp6Configure_EntsTest,
    gTcp6ConfigureArgField
  },
  {
    L"Connect",
    Tcp6Connect_EntsTest,
    gTcp6ConnectArgField
  },
  {
    L"Accept",
    Tcp6Accept_EntsTest,
    gTcp6AcceptArgField
  },
  {
    L"Transmit",
    Tcp6Transmit_EntsTest,
    gTcp6TransmitArgField
  },
  {
    L"Receive",
    Tcp6Receive_EntsTest,
    gTcp6ReceiveArgField
  },
  {
    L"Close",
    Tcp6Close_EntsTest,
    gTcp6CloseArgField
  },
  {
    L"Cancel",
    Tcp6Cancel_EntsTest,
    gTcp6CancelArgField
  },
  {
    L"Poll",
    Tcp6Poll_EntsTest,
    gTcp6PollArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gTcp6EntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Tcp6ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Tcp6ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Tcp6 protocol ENTS Test.

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

  LoadedImage->Unload = Tcp6ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gTcp6EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gTcp6EntsProtocolInterface->ClientName        = gTcp6ProtocolName;
  gTcp6EntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gTcp6EntsProtocolInterface->ClientGuid        = &gBlackBoxEfiTcp6ProtocolGuid;
  gTcp6EntsProtocolInterface->ClientHandle      = NULL;
  gTcp6EntsProtocolInterface->ClientInterface   = NULL;
  gTcp6EntsProtocolInterface->EntsInterfaceList = gTcp6EntsInterfaceList;
  gTcp6EntsProtocolInterface->RuntimeInfo       = gTcp6EntsRuntimeInfo;
  gTcp6EntsProtocolInterface->RuntimeInfoSize   = gTcp6EntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gTcp6EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gTcp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp6EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Tcp6ENTSTestUnload (
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
                  gTcp6EntsProtocolInterface,
                  NULL
                  );

  if (gTcp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp6EntsProtocolInterface);
  }

  return Status;
}
