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

  PXEBaseCodeENTSTest.c

Abstract:

--*/

#include "PXEBaseCodeENTSTestCase.h"

static CHAR16     gPXEBaseCodeProtocolName[]      = L"PXEBaseCode";
CHAR16            *gPXEBaseCodeEntsRuntimeInfo    = NULL;
UINTN             gPXEBaseCodeEntsRuntimeInfoSize = 16;

ENTS_INTERFACE    gPXEBaseCodeEntsInterfaceList[] = {
  {
    L"Start",
    PXEBaseCodeStart_EntsTest,
    gPXEBaseCodeStartArgField
  },
  {
    L"Stop",
    PXEBaseCodeStop_EntsTest,
    gPXEBaseCodeStopArgField
  },
  {
    L"Dhcp",
    PXEBaseCodeDhcp_EntsTest,
    gPXEBaseCodeDhcpArgField
  },
  {
    L"Discover",
    PXEBaseCodeDiscover_EntsTest,
    gPXEBaseCodeDiscoverArgField
  },
  {
    L"Mtftp",
    PXEBaseCodeMtftp_EntsTest,
    gPXEBaseCodeMtftpArgField
  },
  {
    L"UdpWrite",
    PXEBaseCodeUdpWrite_EntsTest,
    gPXEBaseCodeUdpWriteArgField
  },
  {
    L"UdpRead",
    PXEBaseCodeUdpRead_EntsTest,
    gPXEBaseCodeUdpReadArgField
  },
  {
    L"SetIpFilter",
    PXEBaseCodeSetIpFilter_EntsTest,
    gPXEBaseCodeSetIpFilterArgField
  },
  {
    L"Arp",
    PXEBaseCodeArp_EntsTest,
    gPXEBaseCodeArpArgField
  },
  {
    L"SetParameters",
    PXEBaseCodeSetParameters_EntsTest,
    gPXEBaseCodeSetParametersArgField
  },
  {
    L"SetStationIp",
    PXEBaseCodeSetStationIp_EntsTest,
    gPXEBaseCodeSetStationIpArgField
  },
  {
    L"SetPackets",
    PXEBaseCodeSetPackets_EntsTest,
    gPXEBaseCodeSetPacketsArgField
  },
  {
    L"Mode",
    PXEBaseCodeMode_EntsTest,
    gPXEBaseCodeModeArgField
  },
  {
    L"UdpWritePattern1",
    PXEBaseCodeUdpWritePattern1_EntsTest,
    gPXEBaseCodeUdpWritePattern1ArgField
  },
  {
    L"UdpReadPattern1",
    PXEBaseCodeUdpReadPattern1_EntsTest,
    gPXEBaseCodeUdpReadPattern1ArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gPXEBaseCodeEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
PXEBaseCodeENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
PXEBaseCodeENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for PXEBaseCode protocol ENTS Test.

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

  LoadedImage->Unload = PXEBaseCodeENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gPXEBaseCodeEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gPXEBaseCodeEntsProtocolInterface->ClientName         = gPXEBaseCodeProtocolName;
  gPXEBaseCodeEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gPXEBaseCodeEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiPxeBaseCodeProtocolGuid;
  gPXEBaseCodeEntsProtocolInterface->ClientHandle       = NULL;
  gPXEBaseCodeEntsProtocolInterface->ClientInterface    = NULL;
  gPXEBaseCodeEntsProtocolInterface->EntsInterfaceList  = gPXEBaseCodeEntsInterfaceList;
  gPXEBaseCodeEntsProtocolInterface->RuntimeInfo        = gPXEBaseCodeEntsRuntimeInfo;
  gPXEBaseCodeEntsProtocolInterface->RuntimeInfoSize    = gPXEBaseCodeEntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gPXEBaseCodeEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gPXEBaseCodeEntsProtocolInterface != NULL) {
    tBS->FreePool (gPXEBaseCodeEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
PXEBaseCodeENTSTestUnload (
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
                  gPXEBaseCodeEntsProtocolInterface,
                  NULL
                  );

  if (gPXEBaseCodeEntsProtocolInterface != NULL) {
    tBS->FreePool (gPXEBaseCodeEntsProtocolInterface);
  }

  return Status;
}
