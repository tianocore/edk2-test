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

  Dhcp6ENTSTest.c

Abstract:

--*/

#include "Dhcp6ENTSTestCase.h"
#include "EfiTest.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gDhcp6ProtocolName[] = L"Dhcp6";

CHAR16            *gDhcp6RuntimeInfo;
UINTN             gDhcp6RuntimeInfoSize;

ENTS_INTERFACE    gDhcp6EntsInterfaceList[] = {
  {
    L"GetModeData",
    Dhcp6GetModeData_EntsTest,
    gDhcp6GetModeDataArgField
  },
  {
    L"Configure",
    Dhcp6Config_EntsTest,
    gDhcp6ConfigArgField
  },
  {
    L"Start",
    Dhcp6Start_EntsTest,
    gDhcp6StartArgField
  },
  {
    L"InfoRequest",
    Dhcp6InfoRequest_EntsTest,
    gDhcp6InfoRequestArgField
  },
  {
    L"RenewRebind",
    Dhcp6RenewRebind_EntsTest,
    gDhcp6RenewRebindArgField
  },
  {
    L"Decline",
    Dhcp6Decline_EntsTest,
    gDhcp6DeclineArgField
  },
  {
    L"Release",
    Dhcp6Release_EntsTest,
    gDhcp6ReleaseArgField
  },
  {
    L"Stop",
    Dhcp6Stop_EntsTest,
    gDhcp6StopArgField
  },
  {
    L"Parse",
    Dhcp6Parse_EntsTest,
    gDhcp6ParseArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gDhcp6EntsProtocolInterface = NULL;

EFI_STATUS
Dhcp6ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
Dhcp6ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Dhcp6 protocol ENTS Test.

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

  LoadedImage->Unload = Dhcp6ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gDhcp6EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gDhcp6EntsProtocolInterface->ClientName         = gDhcp6ProtocolName;
  gDhcp6EntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gDhcp6EntsProtocolInterface->ClientHandle       = NULL;
  gDhcp6EntsProtocolInterface->ClientGuid         = &gBlackBoxEfiDhcp6ProtocolGuid;
  gDhcp6EntsProtocolInterface->ClientInterface    = NULL;
  gDhcp6EntsProtocolInterface->EntsInterfaceList  = gDhcp6EntsInterfaceList;
  gDhcp6EntsProtocolInterface->RuntimeInfo        = gDhcp6RuntimeInfo;
  gDhcp6EntsProtocolInterface->RuntimeInfoSize    = gDhcp6RuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gDhcp6EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gDhcp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp6EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Dhcp6ENTSTestUnload (
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
  tBS->UninstallMultipleProtocolInterfaces (
        ImageHandle,
        &gEfiEntsProtocolGuid,
        gDhcp6EntsProtocolInterface,
        NULL
        );
  if (gDhcp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp6EntsProtocolInterface);
  }

  return EFI_SUCCESS;
}
