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

  Mtftp6ENTSTest.c

Abstract:

--*/

#include "Mtftp6ENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gMtftp6ProtocolName[]       = L"Mtftp6";
CHAR16            *gMtftp6EntsRuntimeInfo     = NULL;
UINTN             gMtftp6EntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gMtftp6EntsInterfaceList[] = {
  {
    L"GetModeData",
    Mtftp6GetModeData_EntsTest,
    gMtftp6GetModeDataArgField
  },
  {
    L"Configure",
    Mtftp6Configure_EntsTest,
    gMtftp6ConfigureArgField
  },
  {
    L"GetInfo",
    Mtftp6GetInfo_EntsTest,
    gMtftp6GetInfoArgField
  },
  {
    L"ParseOptions",
    Mtftp6ParseOptions_EntsTest,
    gMtftp6ParseOptionsArgField
  },
  {
    L"ReadFile",
    Mtftp6ReadFile_EntsTest,
    gMtftp6ReadFileArgField
  },
  {
    L"WriteFile",
    Mtftp6WriteFile_EntsTest,
    gMtftp6WriteFileArgField
  },
  {
    L"ReadDirectory",
    Mtftp6ReadDirectory_EntsTest,
    gMtftp6ReadDirectoryArgField
  },
  {
    L"Poll",
    Mtftp6Poll_EntsTest,
    gMtftp6PollArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gMtftp6EntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
Mtftp6ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
Mtftp6ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Mtftp6 protocol ENTS Test.

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

  LoadedImage->Unload = Mtftp6ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gMtftp6EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gMtftp6EntsProtocolInterface->ClientName        = gMtftp6ProtocolName;
  gMtftp6EntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gMtftp6EntsProtocolInterface->ClientGuid        = &gBlackBoxEfiMtftp6ProtocolGuid;
  gMtftp6EntsProtocolInterface->ClientHandle      = NULL;
  gMtftp6EntsProtocolInterface->ClientInterface   = NULL;
  gMtftp6EntsProtocolInterface->EntsInterfaceList = gMtftp6EntsInterfaceList;
  gMtftp6EntsProtocolInterface->RuntimeInfo       = gMtftp6EntsRuntimeInfo;
  gMtftp6EntsProtocolInterface->RuntimeInfoSize   = gMtftp6EntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gMtftp6EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gMtftp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp6EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
Mtftp6ENTSTestUnload (
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
                  gMtftp6EntsProtocolInterface,
                  NULL
                  );

  if (gMtftp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp6EntsProtocolInterface);
  }

  return Status;
}
