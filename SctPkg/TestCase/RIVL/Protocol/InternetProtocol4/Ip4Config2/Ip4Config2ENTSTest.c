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
                                                                
  Copyright 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Ip4Config2ENTSTest.c

Abstract:

--*/

#include "Ip4Config2ENTSTestCase.h"
//#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gIp4Config2ProtocolName[] = L"Ip4Config2";

CHAR16            *gIp4Config2RuntimeInfo;
UINTN             gIp4Config2RuntimeInfoSize;

ENTS_INTERFACE    gIp4Config2EntsInterfaceList[] = {
  {
    L"SetData",
    Ip4Config2SetData_EntsTest,
    gIp4Config2SetDataArgField
  },
  {
    L"GetData",
    Ip4Config2GetData_EntsTest,
    gIp4Config2GetDataArgField
  },  
  {
    L"RegisterDataNotify",
    Ip4Config2RegisterDataNotify_EntsTest,
    gIp4Config2RegisterDataNotifyArgField
  },
  {
    L"UnregisterDataNotify",
    Ip4Config2UnregisterDataNotify_EntsTest,
    gIp4Config2UnregisterDataNotifyArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gIp4Config2EntsProtocolInterface = NULL;

EFI_STATUS
Ip4Config2ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
Ip4Config2ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Ip4Config2 protocol ENTS Test.

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

  LoadedImage->Unload = Ip4Config2ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gIp4Config2EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gIp4Config2EntsProtocolInterface->ClientName         = gIp4Config2ProtocolName;
  gIp4Config2EntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gIp4Config2EntsProtocolInterface->ClientGuid         = &gBlackBoxEfiIp4Config2ProtocolGuid;
  gIp4Config2EntsProtocolInterface->ClientHandle       = NULL;
  gIp4Config2EntsProtocolInterface->ClientInterface    = NULL;
  gIp4Config2EntsProtocolInterface->EntsInterfaceList  = gIp4Config2EntsInterfaceList;
  gIp4Config2EntsProtocolInterface->RuntimeInfo        = gIp4Config2RuntimeInfo;
  gIp4Config2EntsProtocolInterface->RuntimeInfoSize    = gIp4Config2RuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gIp4Config2EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gIp4Config2EntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4Config2EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Ip4Config2ENTSTestUnload (
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
                  gIp4Config2EntsProtocolInterface,
                  NULL
                  );

  if (gIp4Config2EntsProtocolInterface != NULL) {
    tBS->FreePool (gIp4Config2EntsProtocolInterface);
  }

  return Status;
}
