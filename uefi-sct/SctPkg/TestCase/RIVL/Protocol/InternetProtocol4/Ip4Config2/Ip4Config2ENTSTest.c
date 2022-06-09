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

  Ip4Config2ENTSTest.c

Abstract:

--*/

#include "Ip4Config2ENTSTestCase.h"
//#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gIp4Config2ProtocolName[] = L"Ip4Config2";

CHAR16            *gIp4Config2RuntimeInfo;
UINTN             gIp4Config2RuntimeInfoSize;

ENTS_INTERFACE    gIp4Config2EntsInterfaceList[] = {
  {
    L"SetData",
    Ip4Config2SetData_EntsTest,
    gIp4Config2SetDataArgField
  },
  {
    L"GetData",
    Ip4Config2GetData_EntsTest,
    gIp4Config2GetDataArgField
  },  
  {
    L"RegisterDataNotify",
    Ip4Config2RegisterDataNotify_EntsTest,
    gIp4Config2RegisterDataNotifyArgField
  },
  {
    L"UnregisterDataNotify",
    Ip4Config2UnregisterDataNotify_EntsTest,
    gIp4Config2UnregisterDataNotifyArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gIp4Config2EntsProtocolInterface = NULL;

EFI_STATUS
Ip4Config2ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Ip4Config2ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Ip4Config2 protocol ENTS Test.

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

  LoadedImage->Unload = Ip4Config2ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gIp4Config2EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gIp4Config2EntsProtocolInterface->ClientName         = gIp4Config2ProtocolName;
  gIp4Config2EntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gIp4Config2EntsProtocolInterface->ClientGuid         = &gBlackBoxEfiIp4Config2ProtocolGuid;
  gIp4Config2EntsProtocolInterface->ClientHandle       = NULL;
  gIp4Config2EntsProtocolInterface->ClientInterface    = NULL;
  gIp4Config2EntsProtocolInterface->EntsInterfaceList  = gIp4Config2EntsInterfaceList;
  gIp4Config2EntsProtocolInterface->RuntimeInfo        = gIp4Config2RuntimeInfo;
  gIp4Config2EntsProtocolInterface->RuntimeInfoSize    = gIp4Config2RuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gIp4Config2EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gIp4Config2EntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4Config2EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Ip4Config2ENTSTestUnload (
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
                  gIp4Config2EntsProtocolInterface,
                  NULL
                  );

  if (gIp4Config2EntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4Config2EntsProtocolInterface);
  }

  return Status;
}
