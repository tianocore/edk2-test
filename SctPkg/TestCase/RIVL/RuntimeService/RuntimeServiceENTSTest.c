/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  RuntimeServiceENTSTest.c

Abstract:

--*/

#include "SctLib.h"
#include "SctLib.h"
#include "VariableService/VariableENTSTestCase.h"
#include "TimeService/TimeENTSTestCase.h"
#include "MiscellaneousRuntimeService/MiscellaneousRuntimeENTSTestCase.h"

static CHAR16     gRuntimeServiceName[] = L"RT";

CHAR16            *gRuntimeServiceRuntimeInfo;
UINTN             gRuntimeServiceRuntimeInfoSize;

ENTS_INTERFACE    gRuntimeServiceEntsInterfaceList[] = {
  {
    L"GetVariable",
    RT_GetVariable_EntsTest,
    tRTGetVariableArgField
  },
  {
    L"GetNextVariableName",
    RT_GetNextVariableName_EntsTest,
    tRTGetNextVariableNameArgField
  },
  {
    L"SetVariable",
    RT_SetVariable_EntsTest,
    tRTSetVariableArgField
  },
  {
    L"GetTime",
    RT_GetTime_EntsTest,
    tRTGetTimeArgField
  },
  {
    L"SetTime",
    RT_SetTime_EntsTest,
    tRTSetTimeArgField
  },
  {
    L"GetWakeupTime",
    RT_GetWakeupTime_EntsTest,
    tRTGetWakeupTimeArgField
  },
  {
    L"SetWakeupTime",
    RT_SetWakeupTime_EntsTest,
    tRTSetWakeupTimeArgField
  },
  {
    L"ResetSystem",
    RT_ResetSystem_EntsTest,
    tRTResetSystemArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gRuntimeServiceEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
RuntimeServiceENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
RuntimeServiceENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Runtime Service ENTS Test.

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
        &gEfiLoadedImageProtocolGuid,
        (VOID *) &LoadedImage
        );

  LoadedImage->Unload = RuntimeServiceENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gRuntimeServiceEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gRuntimeServiceEntsProtocolInterface->ClientName        = gRuntimeServiceName;
  gRuntimeServiceEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_RUNTIME_SERVICE;
  gRuntimeServiceEntsProtocolInterface->ClientGuid        = NULL;
  gRuntimeServiceEntsProtocolInterface->ClientHandle      = NULL;
  gRuntimeServiceEntsProtocolInterface->ClientInterface   = NULL;
  gRuntimeServiceEntsProtocolInterface->EntsInterfaceList = gRuntimeServiceEntsInterfaceList;
  gRuntimeServiceEntsProtocolInterface->RuntimeInfo       = gRuntimeServiceRuntimeInfo;
  gRuntimeServiceEntsProtocolInterface->RuntimeInfoSize   = gRuntimeServiceRuntimeInfoSize;

  return tBS->InstallMultipleProtocolInterfaces (
                &ImageHandle,
                &gEfiEntsProtocolGuid,
                gRuntimeServiceEntsProtocolInterface,
                NULL
                );
}

EFI_STATUS
EFIAPI
RuntimeServiceENTSTestUnload (
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
                  gRuntimeServiceEntsProtocolInterface,
                  NULL
                  );

  if (gRuntimeServiceEntsProtocolInterface != NULL) {
    tBS->FreePool (gRuntimeServiceEntsProtocolInterface);
  }

  return Status;
}
