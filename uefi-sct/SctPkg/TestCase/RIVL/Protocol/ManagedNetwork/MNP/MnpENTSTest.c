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

  MnpENTSTest.c

Abstract:

--*/

#include "MnpENTSTestCase.h"

static CHAR16     gMnpProtocolName[] = L"Mnp";

CHAR16            *gMnpRuntimeInfo;
UINTN             gMnpRuntimeInfoSize;

ENTS_INTERFACE    gMnpEntsInterfaceList[] = {
  {
    L"Configure",
    MnpConfig_EntsTest,
    gMnpConfigArgField
  },
  {
    L"GetModeData",
    MnpGetModeData_EntsTest,
    gMnpGetModeDataArgField
  },
  {
    L"MCastIpToMac",
    MnpMCastIpToMac_EntsTest,
    gMnpMCastIpToMacArgField
  },
  {
    L"Groups",
    MnpGroup_EntsTest,
    gMnpGroupArgField
  },
  {
    L"Transmit",
    MnpTransmit_EntsTest,
    gMnpTransmitArgField
  },
  {
    L"Receive",
    MnpReceive_EntsTest,
    gMnpReceiveArgField
  },
  {
    L"Poll",
    MnpPoll_EntsTest,
    gMnpPollArgField
  },
  {
    L"TransmitMultiPacket",
    MnpTransmitMultiPacket_EntsTest,
    gMnpTransmitMultiPacketArgField
  },
  {
    L"PollPattern1",
    MnpPollPattern1_EntsTest,
    gMnpPollPattern1ArgField
  },
  {
    L"ReceiveMultiPacket",
    MnpReceiveMultiPacket_EntsTest,
    gMnpReceiveMultiArgField
  },
  {
    L"Cancel",
    MnpCancel_EntsTest,
    gMnpCancelArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gMnpEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
MnpENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
MnpENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Mnp protocol ENTS Test.

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

  LoadedImage->Unload = MnpENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gMnpEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gMnpEntsProtocolInterface->ClientName         = gMnpProtocolName;
  gMnpEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gMnpEntsProtocolInterface->ClientHandle       = NULL;
  gMnpEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiManagedNetworkProtocolGuid;
  gMnpEntsProtocolInterface->ClientInterface    = NULL;
  gMnpEntsProtocolInterface->EntsInterfaceList  = gMnpEntsInterfaceList;
  gMnpEntsProtocolInterface->RuntimeInfo        = gMnpRuntimeInfo;
  gMnpEntsProtocolInterface->RuntimeInfoSize    = gMnpRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gMnpEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gMnpEntsProtocolInterface != NULL) {
    tBS->FreePool (gMnpEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
MnpENTSTestUnload (
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
        gMnpEntsProtocolInterface,
        NULL
        );
  if (gMnpEntsProtocolInterface != NULL) {
    tBS->FreePool (gMnpEntsProtocolInterface);
  }

  return EFI_SUCCESS;
}
