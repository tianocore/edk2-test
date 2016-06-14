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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/**
 *  This file is a test image for the Image Boot Services Test
 */
/*++

Module Name:
    RuntimeServicesDriver3.c

Abstract:       
    for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include <Library/EfiTestLib.h>

//
// data definition here
//
typedef struct {
  EFI_HANDLE      Handle;
  EFI_HANDLE      OpenHandle;
} RUNTIME_SERVICES_DRIVER_3_PRIVATE_DATA;

RUNTIME_SERVICES_DRIVER_3_PRIVATE_DATA   mPrivateData;

EFI_STATUS
InitializeRuntimeServicesDriver3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
RuntimeServicesDriver3Unload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
InitializeRuntimeServicesDriver3 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;  
  EFI_HANDLE                            *HandleBuffer;
  UINTN                                 NoHandles;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImageInfoPtr;
  
  mPrivateData.Handle = NULL;
  mPrivateData.OpenHandle = NULL;
  HandleBuffer = NULL;
  
  EfiInitializeTestLib (ImageHandle, SystemTable);
  
  //
  // UnLoad Function Handler
  //  
  gtBS->HandleProtocol (
        ImageHandle, 
        &gEfiLoadedImageProtocolGuid, 
        (VOID*)&LoadedImageInfoPtr
        ); 
        
  LoadedImageInfoPtr->Unload = RuntimeServicesDriver3Unload;
  
  gtBS->InstallProtocolInterface (
                      &mPrivateData.Handle,
                      &mImageTestNoInterfaceProtocol1Guid,
                      EFI_NATIVE_INTERFACE,
                      NULL
                      );
                      
  Status = gtBS->LocateHandleBuffer (
                  ByProtocol,
                  &mImageTestNoInterfaceProtocol2Guid,
                  NULL,
                  &NoHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status)) {
    return EFI_SUCCESS;
  }
  
  mPrivateData.OpenHandle = HandleBuffer[0];
  gtBS->OpenProtocol (
                mPrivateData.OpenHandle,
                &mImageTestNoInterfaceProtocol2Guid,
                NULL,
                ImageHandle,
                NULL,
                EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                );
  
  gtBS->FreePool (HandleBuffer);
                
  return EFI_SUCCESS;
}

EFI_STATUS
RuntimeServicesDriver3Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
              mPrivateData.Handle,
              &mImageTestNoInterfaceProtocol1Guid,
              NULL
              );
   
  return EFI_UNSUPPORTED;
}