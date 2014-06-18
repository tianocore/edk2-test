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
/*++

Module Name:

  BootServicesDriver2.c

Abstract:

  for Image Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "Misc.h"
#include <Library/EfiTestLib.h>

//
// data definition here
//

EFI_STATUS
InitializeBootServicesDriver2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );


EFI_STATUS
InitializeBootServicesDriver2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_HANDLE                            *HandleBuffer;
  UINTN                                 NoHandles;
  CHAR16                                *ExitData;
  CHAR16                                *ErrorMessage;
  UINTN                                 ExitSize;
  EFI_HANDLE                            Handle;

  Handle = NULL;
  HandleBuffer = NULL;
  ExitData = NULL;
  ExitSize = 0;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  Status = gtBS->LocateHandleBuffer (
                  ByProtocol,
                  &mImageTestNoInterfaceProtocol2Guid,
                  NULL,
                  &NoHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    return Status;
  }

  gtBS->OpenProtocol (
                HandleBuffer[0],
                &mImageTestNoInterfaceProtocol2Guid,
                NULL,
                ImageHandle,
                NULL,
                EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                );

  gtBS->InstallProtocolInterface (
                      &Handle,
                      &mImageTestNoInterfaceProtocol1Guid,
                      EFI_NATIVE_INTERFACE,
                      NULL
                      );
  //
  // clean resources before exit
  //
  gtBS->FreePool (HandleBuffer);

  gtBS->UninstallProtocolInterface (
                        Handle,
                        &mImageTestNoInterfaceProtocol1Guid,
                        NULL
                        );

  ErrorMessage = ERROR_MESSAGE_FOR_BOOT_SERVICES_DRIVER_2;

  ExitSize = SctStrSize (ErrorMessage);

  Status = gtBS->AllocatePool (
                        EfiBootServicesData,
                        ExitSize,
                        (VOID**)&ExitData
                        );
  if (!EFI_ERROR(Status)) {
    gtBS->CopyMem (ExitData, ErrorMessage, ExitSize);
  }

  gtBS->Exit (ImageHandle,EFI_DEVICE_ERROR,ExitSize,ExitData);

  //
  // actually should not arrive here. Just to pass compiling.
  //
  return EFI_SUCCESS;
}