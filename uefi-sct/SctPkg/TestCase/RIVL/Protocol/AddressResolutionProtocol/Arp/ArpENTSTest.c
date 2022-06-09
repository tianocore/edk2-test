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

  ArpENTSTest.c

Abstract:

--*/

#include "ArpENTSTestCase.h"

static CHAR16     gArpProtocolName[] = L"Arp";

CHAR16            *gArpRuntimeInfo;
UINTN             gArpRuntimeInfoSize;

ENTS_INTERFACE    gArpEntsInterfaceList[] = {
  {
    L"Configure",
    ArpConfig_EntsTest,
    gArpConfigArgField
  },
  {
    L"Add",
    ArpAdd_EntsTest,
    gArpAddArgField
  },
  {
    L"Find",
    ArpFind_EntsTest,
    gArpFindArgField
  },
  {
    L"Delete",
    ArpDelete_EntsTest,
    gArpDeleteArgField
  },
  {
    L"Flush",
    ArpFlush_EntsTest,
    gArpFlushArgField
  },
  {
    L"Request",
    ArpRequest_EntsTest,
    gArpRequestArgField
  },
  {
    L"Cancel",
    ArpCancel_EntsTest,
    gArpCancelArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gArpEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
ArpENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
ArpENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for ARP protocol ENTS Test.

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

  LoadedImage->Unload = ArpENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gArpEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gArpEntsProtocolInterface->ClientName         = gArpProtocolName;
  gArpEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gArpEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiArpProtocolGuid;
  gArpEntsProtocolInterface->ClientHandle       = NULL;
  gArpEntsProtocolInterface->ClientInterface    = NULL;
  gArpEntsProtocolInterface->EntsInterfaceList  = gArpEntsInterfaceList;
  gArpEntsProtocolInterface->RuntimeInfo        = gArpRuntimeInfo;
  gArpEntsProtocolInterface->RuntimeInfoSize    = gArpRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gArpEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gArpEntsProtocolInterface != NULL) {
    tBS->FreePool (gArpEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
ArpENTSTestUnload (
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
                  gArpEntsProtocolInterface,
                  NULL
                  );

  if (gArpEntsProtocolInterface != NULL) {
    tBS->FreePool (gArpEntsProtocolInterface);
  }

  return Status;
}
