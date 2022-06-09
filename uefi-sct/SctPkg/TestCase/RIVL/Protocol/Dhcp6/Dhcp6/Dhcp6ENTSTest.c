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

  Dhcp6ENTSTest.c

Abstract:

--*/

#include "Dhcp6ENTSTestCase.h"
#include "EfiTest.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gDhcp6ProtocolName[] = L"Dhcp6";

CHAR16            *gDhcp6RuntimeInfo;
UINTN             gDhcp6RuntimeInfoSize;

ENTS_INTERFACE    gDhcp6EntsInterfaceList[] = {
  {
    L"GetModeData",
    Dhcp6GetModeData_EntsTest,
    gDhcp6GetModeDataArgField
  },
  {
    L"Configure",
    Dhcp6Config_EntsTest,
    gDhcp6ConfigArgField
  },
  {
    L"Start",
    Dhcp6Start_EntsTest,
    gDhcp6StartArgField
  },
  {
    L"InfoRequest",
    Dhcp6InfoRequest_EntsTest,
    gDhcp6InfoRequestArgField
  },
  {
    L"RenewRebind",
    Dhcp6RenewRebind_EntsTest,
    gDhcp6RenewRebindArgField
  },
  {
    L"Decline",
    Dhcp6Decline_EntsTest,
    gDhcp6DeclineArgField
  },
  {
    L"Release",
    Dhcp6Release_EntsTest,
    gDhcp6ReleaseArgField
  },
  {
    L"Stop",
    Dhcp6Stop_EntsTest,
    gDhcp6StopArgField
  },
  {
    L"Parse",
    Dhcp6Parse_EntsTest,
    gDhcp6ParseArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gDhcp6EntsProtocolInterface = NULL;

EFI_STATUS
Dhcp6ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Dhcp6ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Dhcp6 protocol ENTS Test.

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

  LoadedImage->Unload = Dhcp6ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gDhcp6EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gDhcp6EntsProtocolInterface->ClientName         = gDhcp6ProtocolName;
  gDhcp6EntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gDhcp6EntsProtocolInterface->ClientHandle       = NULL;
  gDhcp6EntsProtocolInterface->ClientGuid         = &gBlackBoxEfiDhcp6ProtocolGuid;
  gDhcp6EntsProtocolInterface->ClientInterface    = NULL;
  gDhcp6EntsProtocolInterface->EntsInterfaceList  = gDhcp6EntsInterfaceList;
  gDhcp6EntsProtocolInterface->RuntimeInfo        = gDhcp6RuntimeInfo;
  gDhcp6EntsProtocolInterface->RuntimeInfoSize    = gDhcp6RuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gDhcp6EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gDhcp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp6EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Dhcp6ENTSTestUnload (
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
        gDhcp6EntsProtocolInterface,
        NULL
        );
  if (gDhcp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp6EntsProtocolInterface);
  }

  return EFI_SUCCESS;
}
