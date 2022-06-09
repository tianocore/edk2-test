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

  Mtftp4ENTSTest.c

Abstract:

--*/

#include "Mtftp4ENTSTestCase.h"

static CHAR16     gMtftp4ProtocolName[]       = L"Mtftp4";
CHAR16            *gMtftp4EntsRuntimeInfo     = NULL;
UINTN             gMtftp4EntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gMtftp4EntsInterfaceList[] = {
  {
    L"GetModeData",
    Mtftp4GetModeData_EntsTest,
    gMtftp4GetModeDataArgField
  },
  {
    L"Configure",
    Mtftp4Configure_EntsTest,
    gMtftp4ConfigureArgField
  },
  {
    L"GetInfo",
    Mtftp4GetInfo_EntsTest,
    gMtftp4GetInfoArgField
  },
  {
    L"ParseOptions",
    Mtftp4ParseOptions_EntsTest,
    gMtftp4ParseOptionsArgField
  },
  {
    L"ReadFile",
    Mtftp4ReadFile_EntsTest,
    gMtftp4ReadFileArgField
  },
  {
    L"WriteFile",
    Mtftp4WriteFile_EntsTest,
    gMtftp4WriteFileArgField
  },
  {
    L"ReadDirectory",
    Mtftp4ReadDirectory_EntsTest,
    gMtftp4ReadDirectoryArgField
  },
  {
    L"Poll",
    Mtftp4Poll_EntsTest,
    gMtftp4PollArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gMtftp4EntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Mtftp4ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Mtftp4ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Mtftp4 protocol ENTS Test.

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

  LoadedImage->Unload = Mtftp4ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gMtftp4EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gMtftp4EntsProtocolInterface->ClientName        = gMtftp4ProtocolName;
  gMtftp4EntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gMtftp4EntsProtocolInterface->ClientGuid        = &gBlackBoxEfiMtftp4ProtocolGuid;
  gMtftp4EntsProtocolInterface->ClientHandle      = NULL;
  gMtftp4EntsProtocolInterface->ClientInterface   = NULL;
  gMtftp4EntsProtocolInterface->EntsInterfaceList = gMtftp4EntsInterfaceList;
  gMtftp4EntsProtocolInterface->RuntimeInfo       = gMtftp4EntsRuntimeInfo;
  gMtftp4EntsProtocolInterface->RuntimeInfoSize   = gMtftp4EntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gMtftp4EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gMtftp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp4EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Mtftp4ENTSTestUnload (
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
                  gMtftp4EntsProtocolInterface,
                  NULL
                  );

  if (gMtftp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp4EntsProtocolInterface);
  }

  return Status;
}
