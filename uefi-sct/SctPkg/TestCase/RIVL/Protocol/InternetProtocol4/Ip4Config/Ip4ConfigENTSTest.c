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

  Ip4ConfigENTSTest.c

Abstract:

--*/

#include "Ip4ConfigENTSTestCase.h"
//#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gIp4ConfigProtocolName[] = L"Ip4Config";

CHAR16            *gIp4ConfigRuntimeInfo;
UINTN             gIp4ConfigRuntimeInfoSize;

ENTS_INTERFACE    gIp4ConfigEntsInterfaceList[] = {
  {
    L"Start",
    Ip4ConfigStart_EntsTest,
    gIp4ConfigStartArgField
  },
  {
    L"Stop",
    Ip4ConfigStop_EntsTest,
    gIp4ConfigStopArgField
  },
  {
    L"GetData",
    Ip4ConfigGetData_EntsTest,
    gIp4ConfigGetDataArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gIp4ConfigEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Ip4ConfigENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Ip4ConfigENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Ip4Config protocol ENTS Test.

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

  LoadedImage->Unload = Ip4ConfigENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gIp4ConfigEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gIp4ConfigEntsProtocolInterface->ClientName         = gIp4ConfigProtocolName;
  gIp4ConfigEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gIp4ConfigEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiIp4ConfigProtocolGuid;
  gIp4ConfigEntsProtocolInterface->ClientHandle       = NULL;
  gIp4ConfigEntsProtocolInterface->ClientInterface    = NULL;
  gIp4ConfigEntsProtocolInterface->EntsInterfaceList  = gIp4ConfigEntsInterfaceList;
  gIp4ConfigEntsProtocolInterface->RuntimeInfo        = gIp4ConfigRuntimeInfo;
  gIp4ConfigEntsProtocolInterface->RuntimeInfoSize    = gIp4ConfigRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gIp4ConfigEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gIp4ConfigEntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4ConfigEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Ip4ConfigENTSTestUnload (
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
                  gIp4ConfigEntsProtocolInterface,
                  NULL
                  );

  if (gIp4ConfigEntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4ConfigEntsProtocolInterface);
  }

  return Status;
}
