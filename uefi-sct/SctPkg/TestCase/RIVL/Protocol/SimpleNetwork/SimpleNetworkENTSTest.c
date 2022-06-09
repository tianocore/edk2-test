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

  SimpleNetworkENTSTest.c

Abstract:

--*/

#include "SimpleNetworkENTSTestCase.h"

static CHAR16     gSimpleNetworkProtocolName[]      = L"SimpleNetwork";
CHAR16            *gSimpleNetworkEntsRuntimeInfo    = NULL;
UINTN             gSimpleNetworkEntsRuntimeInfoSize = 16;

ENTS_INTERFACE    gSimpleNetworkEntsInterfaceList[] = {
  {
    L"Start",
    SimpleNetworkStart_EntsTest,
    gSimpleNetworkStartArgField
  },
  {
    L"Stop",
    SimpleNetworkStop_EntsTest,
    gSimpleNetworkStopArgField
  },
  {
    L"Initialize",
    SimpleNetworkInitialize_EntsTest,
    gSimpleNetworkInitializeArgField
  },
  {
    L"Reset",
    SimpleNetworkReset_EntsTest,
    gSimpleNetworkResetArgField
  },
  {
    L"Shutdown",
    SimpleNetworkShutdown_EntsTest,
    gSimpleNetworkShutdownArgField
  },
  {
    L"ReceiveFilters",
    SimpleNetworkReceiveFilters_EntsTest,
    gSimpleNetworkReceiveFiltersArgField
  },
  {
    L"StationAddress",
    SimpleNetworkStationAddress_EntsTest,
    gSimpleNetworkStationAddressArgField
  },
  {
    L"Statistics",
    SimpleNetworkStatistics_EntsTest,
    gSimpleNetworkStatisticsArgField
  },
  {
    L"MCastIpToMac",
    SimpleNetworkMCastIPToMAC_EntsTest,
    gSimpleNetworkMCastIPToMACArgField
  },
  {
    L"NvData",
    SimpleNetworkNvData_EntsTest,
    gSimpleNetworkNvDataArgField
  },
  {
    L"GetStatus",
    SimpleNetworkGetStatus_EntsTest,
    gSimpleNetworkGetStatusArgField
  },
  {
    L"Transmit",
    SimpleNetworkTransmit_EntsTest,
    gSimpleNetworkTransmitArgField
  },
  {
    L"Receive",
    SimpleNetworkReceive_EntsTest,
    gSimpleNetworkReceiveArgField
  },
  {
    L"Mode",
    SimpleNetworkMode_EntsTest,
    gSimpleNetworkModeArgField
  },
  {
    L"TransmitPattern1",
    SimpleNetworkTransmitPattern1_EntsTest,
    gSimpleNetworkTransmitPattern1ArgField
  },
  {
    L"TransmitPattern2",
    SimpleNetworkTransmitPattern2_EntsTest,
    gSimpleNetworkTransmitPattern2ArgField
  },
  {
    L"ReceivePattern1",
    SimpleNetworkReceivePattern1_EntsTest,
    gSimpleNetworkReceivePattern1ArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gSimpleNetworkEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
SimpleNetworkENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
SimpleNetworkENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for simple network protocol ENTS Test.

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

  LoadedImage->Unload = SimpleNetworkENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gSimpleNetworkEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gSimpleNetworkEntsProtocolInterface->ClientName         = gSimpleNetworkProtocolName;
  gSimpleNetworkEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gSimpleNetworkEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiSimpleNetworkProtocolGuid;
  gSimpleNetworkEntsProtocolInterface->ClientHandle       = NULL;
  gSimpleNetworkEntsProtocolInterface->ClientInterface    = NULL;
  gSimpleNetworkEntsProtocolInterface->EntsInterfaceList  = gSimpleNetworkEntsInterfaceList;
  gSimpleNetworkEntsProtocolInterface->RuntimeInfo        = gSimpleNetworkEntsRuntimeInfo;
  gSimpleNetworkEntsProtocolInterface->RuntimeInfoSize    = gSimpleNetworkEntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gSimpleNetworkEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gSimpleNetworkEntsProtocolInterface != NULL) {
    tBS->FreePool (gSimpleNetworkEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
SimpleNetworkENTSTestUnload (
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
                  gSimpleNetworkEntsProtocolInterface,
                  NULL
                  );

  if (gSimpleNetworkEntsProtocolInterface != NULL) {
    tBS->FreePool (gSimpleNetworkEntsProtocolInterface);
  }

  return Status;
}
