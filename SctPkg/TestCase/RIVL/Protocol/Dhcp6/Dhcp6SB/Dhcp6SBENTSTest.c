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

  Dhcp6SBENTSTest.c

Abstract:

--*/

#include "Dhcp6SBENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gDhcp6ServiceBindingProtocolName[] = L"Dhcp6ServiceBinding";

CHAR16            *gDhcp6ServiceBindingRuntimeInfo;
UINTN             gDhcp6ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gDhcp6ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Dhcp6CreateChild_EntsTest,
    gDhcp6CreateChildArgField
  },
  {
    L"DestroyChild",
    Dhcp6DestroyChild_EntsTest,
    gDhcp6DestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gDhcp6ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
Dhcp6SBENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
Dhcp6SBENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Dhcp6 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Dhcp6SBENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gDhcp6ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiDhcp6ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gDhcp6ServiceBindingEntsProtocolInterface->ClientName         = gDhcp6ServiceBindingProtocolName;
  gDhcp6ServiceBindingEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gDhcp6ServiceBindingEntsProtocolInterface->ClientHandle       = ClientHandle;
  gDhcp6ServiceBindingEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiDhcp6ServiceBindingProtocolGuid;
  gDhcp6ServiceBindingEntsProtocolInterface->ClientInterface    = NULL;
  gDhcp6ServiceBindingEntsProtocolInterface->EntsInterfaceList  = gDhcp6ServiceBindingEntsInterfaceList;
  gDhcp6ServiceBindingEntsProtocolInterface->RuntimeInfo        = gDhcp6ServiceBindingRuntimeInfo;
  gDhcp6ServiceBindingEntsProtocolInterface->RuntimeInfoSize    = gDhcp6ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gDhcp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gDhcp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Dhcp6SBENTSTestUnload (
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
        gDhcp6ServiceBindingEntsProtocolInterface,
        NULL
        );
  if (gDhcp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp6ServiceBindingEntsProtocolInterface);
  }

  return EFI_SUCCESS;
}
