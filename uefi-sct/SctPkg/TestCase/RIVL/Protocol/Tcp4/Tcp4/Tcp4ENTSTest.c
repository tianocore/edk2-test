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

  Tcp4ENTSTest.c

Abstract:

--*/

#include "Tcp4ENTSTestCase.h"

static CHAR16     gTcp4ProtocolName[]       = L"Tcp4";
CHAR16            *gTcp4EntsRuntimeInfo     = NULL;
UINTN             gTcp4EntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gTcp4EntsInterfaceList[] = {
  {
    L"GetModeData",
    Tcp4GetModeData_EntsTest,
    gTcp4GetModeDataArgField
  },
  {
    L"Configure",
    Tcp4Configure_EntsTest,
    gTcp4ConfigureArgField
  },
  {
    L"Routes",
    Tcp4Routes_EntsTest,
    gTcp4RoutesArgField
  },
  {
    L"Connect",
    Tcp4Connect_EntsTest,
    gTcp4ConnectArgField
  },
  {
    L"Accept",
    Tcp4Accept_EntsTest,
    gTcp4AcceptArgField
  },
  {
    L"Transmit",
    Tcp4Transmit_EntsTest,
    gTcp4TransmitArgField
  },
  {
    L"Receive",
    Tcp4Receive_EntsTest,
    gTcp4ReceiveArgField
  },
  {
    L"Close",
    Tcp4Close_EntsTest,
    gTcp4CloseArgField
  },
  {
    L"Cancel",
    Tcp4Cancel_EntsTest,
    gTcp4CancelArgField
  },
  {
    L"Poll",
    Tcp4Poll_EntsTest,
    gTcp4PollArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gTcp4EntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Tcp4ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Tcp4ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Tcp4 protocol ENTS Test.

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

  LoadedImage->Unload = Tcp4ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gTcp4EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gTcp4EntsProtocolInterface->ClientName        = gTcp4ProtocolName;
  gTcp4EntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gTcp4EntsProtocolInterface->ClientGuid        = &gBlackBoxEfiTcp4ProtocolGuid;
  gTcp4EntsProtocolInterface->ClientHandle      = NULL;
  gTcp4EntsProtocolInterface->ClientInterface   = NULL;
  gTcp4EntsProtocolInterface->EntsInterfaceList = gTcp4EntsInterfaceList;
  gTcp4EntsProtocolInterface->RuntimeInfo       = gTcp4EntsRuntimeInfo;
  gTcp4EntsProtocolInterface->RuntimeInfoSize   = gTcp4EntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gTcp4EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gTcp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp4EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Tcp4ENTSTestUnload (
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
                  gTcp4EntsProtocolInterface,
                  NULL
                  );

  if (gTcp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp4EntsProtocolInterface);
  }

  return Status;
}
