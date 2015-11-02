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

  Tcp6ENTSTest.c

Abstract:

--*/

#include "Tcp6ENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gTcp6ProtocolName[]       = L"Tcp6";
CHAR16            *gTcp6EntsRuntimeInfo     = NULL;
UINTN             gTcp6EntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gTcp6EntsInterfaceList[] = {
  {
    L"GetModeData",
    Tcp6GetModeData_EntsTest,
    gTcp6GetModeDataArgField
  },
  {
    L"Configure",
    Tcp6Configure_EntsTest,
    gTcp6ConfigureArgField
  },
  {
    L"Connect",
    Tcp6Connect_EntsTest,
    gTcp6ConnectArgField
  },
  {
    L"Accept",
    Tcp6Accept_EntsTest,
    gTcp6AcceptArgField
  },
  {
    L"Transmit",
    Tcp6Transmit_EntsTest,
    gTcp6TransmitArgField
  },
  {
    L"Receive",
    Tcp6Receive_EntsTest,
    gTcp6ReceiveArgField
  },
  {
    L"Close",
    Tcp6Close_EntsTest,
    gTcp6CloseArgField
  },
  {
    L"Cancel",
    Tcp6Cancel_EntsTest,
    gTcp6CancelArgField
  },
  {
    L"Poll",
    Tcp6Poll_EntsTest,
    gTcp6PollArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gTcp6EntsProtocolInterface = NULL;

EFI_STATUS
Tcp6ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
Tcp6ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Tcp6 protocol ENTS Test.

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

  LoadedImage->Unload = Tcp6ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gTcp6EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gTcp6EntsProtocolInterface->ClientName        = gTcp6ProtocolName;
  gTcp6EntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gTcp6EntsProtocolInterface->ClientGuid        = &gBlackBoxEfiTcp6ProtocolGuid;
  gTcp6EntsProtocolInterface->ClientHandle      = NULL;
  gTcp6EntsProtocolInterface->ClientInterface   = NULL;
  gTcp6EntsProtocolInterface->EntsInterfaceList = gTcp6EntsInterfaceList;
  gTcp6EntsProtocolInterface->RuntimeInfo       = gTcp6EntsRuntimeInfo;
  gTcp6EntsProtocolInterface->RuntimeInfoSize   = gTcp6EntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gTcp6EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gTcp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp6EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Tcp6ENTSTestUnload (
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
                  gTcp6EntsProtocolInterface,
                  NULL
                  );

  if (gTcp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gTcp6EntsProtocolInterface);
  }

  return Status;
}
