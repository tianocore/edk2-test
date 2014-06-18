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

  Dhcp4SBENTSTest.c

Abstract:

--*/

#include "Dhcp4SBENTSTestCase.h"

static CHAR16     gDhcp4ServiceBindingProtocolName[] = L"Dhcp4ServiceBinding";

CHAR16            *gDhcp4ServiceBindingRuntimeInfo;
UINTN             gDhcp4ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gDhcp4ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Dhcp4CreateChild_EntsTest,
    gDhcp4CreateChildArgField
  },
  {
    L"DestroyChild",
    Dhcp4DestroyChild_EntsTest,
    gDhcp4DestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gDhcp4ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
Dhcp4SBENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
Dhcp4SBENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Dhcp4 service binding protocol ENTS Test.

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

  LoadedImage->Unload = Dhcp4SBENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gDhcp4ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiDhcp4ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gDhcp4ServiceBindingEntsProtocolInterface->ClientName         = gDhcp4ServiceBindingProtocolName;
  gDhcp4ServiceBindingEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gDhcp4ServiceBindingEntsProtocolInterface->ClientHandle       = ClientHandle;
  gDhcp4ServiceBindingEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiDhcp4ServiceBindingProtocolGuid;
  gDhcp4ServiceBindingEntsProtocolInterface->ClientInterface    = NULL;
  gDhcp4ServiceBindingEntsProtocolInterface->EntsInterfaceList  = gDhcp4ServiceBindingEntsInterfaceList;
  gDhcp4ServiceBindingEntsProtocolInterface->RuntimeInfo        = gDhcp4ServiceBindingRuntimeInfo;
  gDhcp4ServiceBindingEntsProtocolInterface->RuntimeInfoSize    = gDhcp4ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gDhcp4ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gDhcp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp4ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Dhcp4SBENTSTestUnload (
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
        gDhcp4ServiceBindingEntsProtocolInterface,
        NULL
        );
  if (gDhcp4ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gDhcp4ServiceBindingEntsProtocolInterface);
  }

  return EFI_SUCCESS;
}
