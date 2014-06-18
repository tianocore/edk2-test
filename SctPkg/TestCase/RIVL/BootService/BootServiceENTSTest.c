/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  BootServiceENTSTest.c

Abstract:

--*/

#include "SctLib.h"
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
BootServiceENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
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
                  &gBootServiceEntsProtocolInterface
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
