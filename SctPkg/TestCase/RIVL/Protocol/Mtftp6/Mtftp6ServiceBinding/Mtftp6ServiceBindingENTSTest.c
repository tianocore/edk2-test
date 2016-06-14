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

  Mtftp6ServiceBindingENTSTest.c

Abstract:

--*/

#include "Mtftp6ServiceBindingENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gMtftp6ServiceBindingProtocolName[] = L"Mtftp6ServiceBinding";

CHAR16            *gMtftp6ServiceBindingRuntimeInfo;
UINTN             gMtftp6ServiceBindingRuntimeInfoSize;

ENTS_INTERFACE    gMtftp6ServiceBindingEntsInterfaceList[] = {
  {
    L"CreateChild",
    Mtftp6ServiceBindingCreateChild_EntsTest,
    gMtftp6ServiceBindingCreateChildArgField
  },
  {
    L"DestroyChild",
    Mtftp6ServiceBindingDestroyChild_EntsTest,
    gMtftp6ServiceBindingDestroyChildArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gMtftp6ServiceBindingEntsProtocolInterface = NULL;

EFI_STATUS
Mtftp6ServiceBindingENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
Mtftp6ServiceBindingENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Mtftp6 service binding protocol ENTS Test.

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
        (VOID *) &LoadedImage
        );

  LoadedImage->Unload = Mtftp6ServiceBindingENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gMtftp6ServiceBindingEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gBlackBoxEfiMtftp6ServiceBindingProtocolGuid,
             &ClientHandle
             );
  if (EFI_ERROR(Status)) {
  	goto Error;
  }

  gMtftp6ServiceBindingEntsProtocolInterface->ClientName        = gMtftp6ServiceBindingProtocolName;
  gMtftp6ServiceBindingEntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gMtftp6ServiceBindingEntsProtocolInterface->ClientGuid        = &gBlackBoxEfiMtftp6ServiceBindingProtocolGuid;
  gMtftp6ServiceBindingEntsProtocolInterface->ClientHandle      = ClientHandle;
  gMtftp6ServiceBindingEntsProtocolInterface->ClientInterface   = NULL;
  gMtftp6ServiceBindingEntsProtocolInterface->EntsInterfaceList = gMtftp6ServiceBindingEntsInterfaceList;
  gMtftp6ServiceBindingEntsProtocolInterface->RuntimeInfo       = gMtftp6ServiceBindingRuntimeInfo;
  gMtftp6ServiceBindingEntsProtocolInterface->RuntimeInfoSize   = gMtftp6ServiceBindingRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gMtftp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gMtftp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Mtftp6ServiceBindingENTSTestUnload (
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
                  gMtftp6ServiceBindingEntsProtocolInterface,
                  NULL
                  );

  if (gMtftp6ServiceBindingEntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp6ServiceBindingEntsProtocolInterface);
  }

  return Status;
}
