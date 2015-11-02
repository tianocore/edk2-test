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

  Mtftp4ENTSTest.c

Abstract:

--*/

#include "Mtftp4ENTSTestCase.h"

static CHAR16     gMtftp4ProtocolName[]       = L"Mtftp4";
CHAR16            *gMtftp4EntsRuntimeInfo     = NULL;
UINTN             gMtftp4EntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gMtftp4EntsInterfaceList[] = {
  {
    L"GetModeData",
    Mtftp4GetModeData_EntsTest,
    gMtftp4GetModeDataArgField
  },
  {
    L"Configure",
    Mtftp4Configure_EntsTest,
    gMtftp4ConfigureArgField
  },
  {
    L"GetInfo",
    Mtftp4GetInfo_EntsTest,
    gMtftp4GetInfoArgField
  },
  {
    L"ParseOptions",
    Mtftp4ParseOptions_EntsTest,
    gMtftp4ParseOptionsArgField
  },
  {
    L"ReadFile",
    Mtftp4ReadFile_EntsTest,
    gMtftp4ReadFileArgField
  },
  {
    L"WriteFile",
    Mtftp4WriteFile_EntsTest,
    gMtftp4WriteFileArgField
  },
  {
    L"ReadDirectory",
    Mtftp4ReadDirectory_EntsTest,
    gMtftp4ReadDirectoryArgField
  },
  {
    L"Poll",
    Mtftp4Poll_EntsTest,
    gMtftp4PollArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gMtftp4EntsProtocolInterface = NULL;

EFI_STATUS
Mtftp4ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
Mtftp4ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Mtftp4 protocol ENTS Test.

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

  LoadedImage->Unload = Mtftp4ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gMtftp4EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gMtftp4EntsProtocolInterface->ClientName        = gMtftp4ProtocolName;
  gMtftp4EntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gMtftp4EntsProtocolInterface->ClientGuid        = &gBlackBoxEfiMtftp4ProtocolGuid;
  gMtftp4EntsProtocolInterface->ClientHandle      = NULL;
  gMtftp4EntsProtocolInterface->ClientInterface   = NULL;
  gMtftp4EntsProtocolInterface->EntsInterfaceList = gMtftp4EntsInterfaceList;
  gMtftp4EntsProtocolInterface->RuntimeInfo       = gMtftp4EntsRuntimeInfo;
  gMtftp4EntsProtocolInterface->RuntimeInfoSize   = gMtftp4EntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gMtftp4EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gMtftp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp4EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Mtftp4ENTSTestUnload (
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
                  gMtftp4EntsProtocolInterface,
                  NULL
                  );

  if (gMtftp4EntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp4EntsProtocolInterface);
  }

  return Status;
}
