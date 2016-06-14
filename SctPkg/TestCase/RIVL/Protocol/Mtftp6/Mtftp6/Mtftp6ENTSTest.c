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

  Mtftp6ENTSTest.c

Abstract:

--*/

#include "Mtftp6ENTSTestCase.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

static CHAR16     gMtftp6ProtocolName[]       = L"Mtftp6";
CHAR16            *gMtftp6EntsRuntimeInfo     = NULL;
UINTN             gMtftp6EntsRuntimeInfoSize  = 16;

ENTS_INTERFACE    gMtftp6EntsInterfaceList[] = {
  {
    L"GetModeData",
    Mtftp6GetModeData_EntsTest,
    gMtftp6GetModeDataArgField
  },
  {
    L"Configure",
    Mtftp6Configure_EntsTest,
    gMtftp6ConfigureArgField
  },
  {
    L"GetInfo",
    Mtftp6GetInfo_EntsTest,
    gMtftp6GetInfoArgField
  },
  {
    L"ParseOptions",
    Mtftp6ParseOptions_EntsTest,
    gMtftp6ParseOptionsArgField
  },
  {
    L"ReadFile",
    Mtftp6ReadFile_EntsTest,
    gMtftp6ReadFileArgField
  },
  {
    L"WriteFile",
    Mtftp6WriteFile_EntsTest,
    gMtftp6WriteFileArgField
  },
  {
    L"ReadDirectory",
    Mtftp6ReadDirectory_EntsTest,
    gMtftp6ReadDirectoryArgField
  },
  {
    L"Poll",
    Mtftp6Poll_EntsTest,
    gMtftp6PollArgField
  },
  NULL
};

EFI_ENTS_PROTOCOL *gMtftp6EntsProtocolInterface = NULL;

EFI_STATUS
Mtftp6ENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
Mtftp6ENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for Mtftp6 protocol ENTS Test.

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
        (VOID *) &LoadedImage
        );

  LoadedImage->Unload = Mtftp6ENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gMtftp6EntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gMtftp6EntsProtocolInterface->ClientName        = gMtftp6ProtocolName;
  gMtftp6EntsProtocolInterface->ClientAttribute   = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL_SERVICE_BINDING_RELATED;
  gMtftp6EntsProtocolInterface->ClientGuid        = &gBlackBoxEfiMtftp6ProtocolGuid;
  gMtftp6EntsProtocolInterface->ClientHandle      = NULL;
  gMtftp6EntsProtocolInterface->ClientInterface   = NULL;
  gMtftp6EntsProtocolInterface->EntsInterfaceList = gMtftp6EntsInterfaceList;
  gMtftp6EntsProtocolInterface->RuntimeInfo       = gMtftp6EntsRuntimeInfo;
  gMtftp6EntsProtocolInterface->RuntimeInfoSize   = gMtftp6EntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gMtftp6EntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gMtftp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp6EntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
Mtftp6ENTSTestUnload (
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
                  gMtftp6EntsProtocolInterface,
                  NULL
                  );

  if (gMtftp6EntsProtocolInterface != NULL) {
    tBS->FreePool (gMtftp6EntsProtocolInterface);
  }

  return Status;
}
