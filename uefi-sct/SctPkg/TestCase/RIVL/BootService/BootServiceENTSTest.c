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
  BootServiceENTSTest.c

Abstract:

--*/

#include "SctLib.h"
#include "EventTimerAndTaskPriorityService/EventTimerAndTaskPriorityENTSTestCase.h"
#include "MemoryAllocationService/MemoryAllocationENTSTestCase.h"
#include "MiscellaneousBootService/MiscellaneousBootENTSTestCase.h"

static CHAR16     gBootServiceName[] = L"BS";

CHAR16            *gBootServiceRuntimeInfo;
UINTN             gBootServiceRuntimeInfoSize;

ENTS_INTERFACE    gBootServiceEntsInterfaceList[] = {
  {
    L"CreateEvent",
    BS_CreateEvent_EntsTest,
    BSCreateEventArgField
  },
  {
    L"CloseEvent",
    BS_CloseEvent_EntsTest,
    BSCloseEventArgField
  },
  {
    L"SignalEvent",
    BS_SignalEvent_EntsTest,
    BSSignalEventArgField
  },
  {
    L"WaitForEvent",
    BS_WaitForEvent_EntsTest,
    BSWaitForEventArgField
  },
  {
    L"CheckEvent",
    BS_CheckEvent_EntsTest,
    BSCheckEventArgField
  },
  {
    L"SetTimer",
    BS_SetTimer_EntsTest,
    BSSetTimerArgField
  },
  {
    L"AllocatePages",
    BS_AllocatePages_EntsTest,
    BSAllocatePagesArgField
  },
  {
    L"FreePages",
    BS_FreePages_EntsTest,
    BSFreePagesArgField
  },
  {
    L"AllocatePool",
    BS_AllocatePool_EntsTest,
    BSAllocatePoolArgField
  },
  {
    L"FreePool",
    BS_FreePool_EntsTest,
    BSFreePoolArgField
  },
  {
    L"SetWatchdogTimer",
    BS_SetWatchdogTimer_EntsTest,
    BSSetWatchdogTimerArgField
  },
  {
    L"Stall",
    BS_Stall_EntsTest,
    BSStallArgField
  },
  {
    L"CopyMem",
    BS_CopyMem_EntsTest,
    BSCopyMemArgField
  },
  {
    L"SetMem",
    BS_SetMem_EntsTest,
    BSSetMemArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gBootServiceEntsProtocolInterface = NULL;

EFI_STATUS
EFIAPI
BootServiceENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
EFIAPI
BootServiceENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Boot Service ENTS Test.

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

  LoadedImage->Unload = BootServiceENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **) &gBootServiceEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gBootServiceEntsProtocolInterface->ClientName         = gBootServiceName;
  gBootServiceEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_BOOT_SERVICE;
  gBootServiceEntsProtocolInterface->ClientGuid         = NULL;
  gBootServiceEntsProtocolInterface->ClientHandle       = NULL;
  gBootServiceEntsProtocolInterface->ClientInterface    = NULL;
  gBootServiceEntsProtocolInterface->EntsInterfaceList  = gBootServiceEntsInterfaceList;
  gBootServiceEntsProtocolInterface->RuntimeInfo        = gBootServiceRuntimeInfo;
  gBootServiceEntsProtocolInterface->RuntimeInfoSize    = gBootServiceRuntimeInfoSize;

  return tBS->InstallMultipleProtocolInterfaces (
                &ImageHandle,
                &gEfiEntsProtocolGuid,
                gBootServiceEntsProtocolInterface,
                NULL
                );
}

EFI_STATUS
EFIAPI
BootServiceENTSTestUnload (
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
                  gBootServiceEntsProtocolInterface,
                  NULL
                  );

  if (gBootServiceEntsProtocolInterface != NULL) {
    tBS->FreePool (gBootServiceEntsProtocolInterface);
  }

  return Status;
}
