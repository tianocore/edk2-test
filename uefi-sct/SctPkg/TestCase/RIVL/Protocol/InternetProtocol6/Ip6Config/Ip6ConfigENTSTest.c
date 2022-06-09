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

  Ip6ConfigENTSTest.c

Abstract:

--*/

#include "Ip6ConfigENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
static CHAR16     gIp6ConfigProtocolName[] = L"Ip6Config";

CHAR16            *gIp6ConfigRuntimeInfo;
UINTN             gIp6ConfigRuntimeInfoSize;

ENTS_INTERFACE    gIp6ConfigEntsInterfaceList[] = {
  {
    L"SetData",
    Ip6ConfigSetData_EntsTest,
    gIp6ConfigSetDataArgField
  },
  {
    L"GetData",
    Ip6ConfigGetData_EntsTest,
    gIp6ConfigGetDataArgField
  },
  {
    L"RegisterDataNotify",
    Ip6ConfigRegisterDataNotify_EntsTest,
    gIp6ConfigRegisterDataNotifyArgField
  },
  {
    L"UnregisterDataNotify",
	Ip6ConfigUnregisterDataNotify_EntsTest,
	gIp6ConfigUnregisterDataNotifyArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gIp6ConfigEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Ip6ConfigENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Ip6ConfigENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Ip6Config protocol ENTS Test.

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
  EFI_HANDLE                ClientHandle;

  SctInitializeDriver (ImageHandle, SystemTable);
  EfiInitializeEntsLib (ImageHandle, SystemTable);

  tBS->HandleProtocol (
        ImageHandle,
        &gBlackBoxEfiLoadedImageProtocolGuid,
        (VOID **) &LoadedImage
        );

  LoadedImage->Unload = Ip6ConfigENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gIp6ConfigEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiIp6ConfigProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gIp6ConfigEntsProtocolInterface->ClientName         = gIp6ConfigProtocolName;
  gIp6ConfigEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gIp6ConfigEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiIp6ConfigProtocolGuid;
  gIp6ConfigEntsProtocolInterface->ClientHandle       = ClientHandle;
  gIp6ConfigEntsProtocolInterface->ClientInterface    = NULL;
  gIp6ConfigEntsProtocolInterface->EntsInterfaceList  = gIp6ConfigEntsInterfaceList;
  gIp6ConfigEntsProtocolInterface->RuntimeInfo        = gIp6ConfigRuntimeInfo;
  gIp6ConfigEntsProtocolInterface->RuntimeInfoSize    = gIp6ConfigRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gIp6ConfigEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gIp6ConfigEntsProtocolInterface != NULL) {
    tBS->FreePool (gIp6ConfigEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Ip6ConfigENTSTestUnload (
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
                  gIp6ConfigEntsProtocolInterface,
                  NULL
                  );

  if (gIp6ConfigEntsProtocolInterface != NULL) {
    tBS->FreePool (gIp6ConfigEntsProtocolInterface);
  }

  return Status;
}
