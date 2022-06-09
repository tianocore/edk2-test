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

  Dhcp4ENTSTest.c

Abstract:

--*/

#include "Dhcp4ENTSTestCase.h"

static CHAR16     gDhcp4ProtocolName[] = L"Dhcp4";

CHAR16            *gDhcp4RuntimeInfo;
UINTN             gDhcp4RuntimeInfoSize;

ENTS_INTERFACE    gDhcp4EntsInterfaceList[] = {
  {
    L"GetModeData",
    Dhcp4GetModeData_EntsTest,
    gDhcp4GetModeDataArgField
  },
  {
    L"Configure",
    Dhcp4Config_EntsTest,
    gDhcp4ConfigArgField
  },
  {
    L"Start",
    Dhcp4Start_EntsTest,
    gDhcp4StartArgField
  },
  {
    L"RenewRebind",
    Dhcp4RenewRebind_EntsTest,
    gDhcp4RenewRebindArgField
  },
  {
    L"Release",
    Dhcp4Release_EntsTest,
    gDhcp4ReleaseArgField
  },
  {
    L"Stop",
    Dhcp4Stop_EntsTest,
    gDhcp4StopArgField
  },
  {
    L"Build",
    Dhcp4Build_EntsTest,
    gDhcp4BuildArgField
  },
  {
    L"TransmitReceive",
    Dhcp4TransmitReceive_EntsTest,
    gDhcp4TransmitReceiveArgField
  },
  {
    L"Parse",
    Dhcp4Parse_EntsTest,
    gDhcp4ParseArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gDhcp4EntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Dhcp4ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Dhcp4ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Dhcp4 protocol ENTS Test.

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

  LoadedImage->Unload = Dhcp4ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gDhcp4EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gDhcp4EntsProtocolInterface->ClientName         = gDhcp4ProtocolName;
  gDhcp4EntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gDhcp4EntsProtocolInterface->ClientHandle       = NULL;
  gDhcp4EntsProtocolInterface->ClientGuid         = &gBlackBoxEfiDhcp4ProtocolGuid;
  gDhcp4EntsProtocolInterface->ClientInterface    = NULL;
  gDhcp4EntsProtocolInterface->EntsInterfaceList  = gDhcp4EntsInterfaceList;
  gDhcp4EntsProtocolInterface->RuntimeInfo        = gDhcp4RuntimeInfo;
  gDhcp4EntsProtocolInterface->RuntimeInfoSize    = gDhcp4RuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gDhcp4EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gDhcp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp4EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Dhcp4ENTSTestUnload (
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
        gDhcp4EntsProtocolInterface,
        NULL
        );
  if (gDhcp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp4EntsProtocolInterface);
  }

  return EFI_SUCCESS;
}
