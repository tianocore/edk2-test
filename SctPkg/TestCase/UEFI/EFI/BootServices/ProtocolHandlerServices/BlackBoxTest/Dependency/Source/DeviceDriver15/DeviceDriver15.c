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
/**
 *  This file is a test image for the Protocol Handler Boot Services Test
 */
/*++

Module Name:

    DeviceDriver15.c

Abstract:       

    for Protocol Handler Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "../Inc/TestDriver.h"

//
// TestDeviceDriver15:
// Consume InterfaceTestProtocol2 BY_DRIVER, InterfaceTestProtocol3 BY_DRIVER;
// Produce InterfaceTestProtocol8 on the same handle
//

//
// data definition here
//
typedef struct {
  INTERFACE_FUNCTION_TEST_PROTOCOL_8    InterfaceFunctionTestProtocol8;
  EFI_DRIVER_BINDING_PROTOCOL           DriverBinding;
} DEVICE_DRIVER_15_PRIVATE_DATA;

#define DEVICE_DRIVER_15_PRIVATE_DATA_FROM_DRIVER_BINDING(a) \
 BASE_CR(a, DEVICE_DRIVER_15_PRIVATE_DATA, DriverBinding)
 
DEVICE_DRIVER_15_PRIVATE_DATA          *mPrivateData;

EFI_STATUS
InitializeDeviceDriver15 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );
  
EFI_STATUS
DeviceDriver15BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
DeviceDriver15BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
DeviceDriver15BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );

void
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  );

VOID
Protocol8ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_8   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol8 (
  INTERFACE_FUNCTION_TEST_PROTOCOL_8     *InterfaceFunctionTestProtocol8
  );

EFI_STATUS
DeviceDriver15Unload (
  IN EFI_HANDLE       ImageHandle
  );

//
// global variable for this test driver's image handle
//

EFI_STATUS
InitializeDeviceDriver15 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;  
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImageInfoPtr;
  
  EfiInitializeTestLib (ImageHandle, SystemTable);
  
  //
  // allocate memory for PrivateData
  //
  Status = gtBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof (DEVICE_DRIVER_15_PRIVATE_DATA),
                        (VOID**)&mPrivateData
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  gtBS->SetMem (mPrivateData,sizeof (DEVICE_DRIVER_15_PRIVATE_DATA),0);
  
  InitializeDriverBinding (&mPrivateData->DriverBinding);
  
  Status = gtBS->InstallProtocolInterface (
            &ImageHandle,
            &gEfiDriverBindingProtocolGuid,
            EFI_NATIVE_INTERFACE,
            &mPrivateData->DriverBinding
            );
  mPrivateData->DriverBinding.ImageHandle = ImageHandle;
  mPrivateData->DriverBinding.DriverBindingHandle = ImageHandle;
  //
  // UnLoad Function Handler
  //  
  gtBS->HandleProtocol (
        ImageHandle, 
        &gEfiLoadedImageProtocolGuid, 
        (VOID*)&LoadedImageInfoPtr
        ); 
        
  LoadedImageInfoPtr->Unload = DeviceDriver15Unload;
  
  return EFI_SUCCESS;
  
}

EFI_STATUS
DeviceDriver15BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )  
{
  EFI_STATUS        Status1,Status2;
  
  Status1 = gtBS->OpenProtocol (
                      Controller,
                      &mInterfaceFunctionTestProtocol2Guid,
                      NULL,
                      This->DriverBindingHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  Status2 = gtBS->OpenProtocol (
                      Controller,
                      &mInterfaceFunctionTestProtocol3Guid,
                      NULL,
                      This->DriverBindingHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  if (EFI_ERROR(Status1) && EFI_ERROR(Status2)) {
    return EFI_UNSUPPORTED;
  }
  
  return EFI_SUCCESS;  
}

EFI_STATUS
DeviceDriver15BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  EFI_STATUS                            Status1, Status2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2    *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3    *IFTestProt3;
  DEVICE_DRIVER_15_PRIVATE_DATA         *PrivateData;
  
  PrivateData = DEVICE_DRIVER_15_PRIVATE_DATA_FROM_DRIVER_BINDING (This);
  
  Status1 = gtBS->OpenProtocol (
                     Controller,
                     &mInterfaceFunctionTestProtocol2Guid,
                     &IFTestProt2,
                     This->DriverBindingHandle,
                     Controller,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
  Status2 = gtBS->OpenProtocol (
                     Controller,
                     &mInterfaceFunctionTestProtocol3Guid,
                     &IFTestProt3,
                     This->DriverBindingHandle,
                     Controller,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
  if (EFI_ERROR(Status1) && EFI_ERROR(Status2)) {
    Status = EFI_DEVICE_ERROR;
    goto ErrorExit;
  }
  
  InitializeInterfaceFunctionTestProtocol8 (&PrivateData->InterfaceFunctionTestProtocol8);
  
  Status = gtBS->InstallProtocolInterface (
                  Controller,
                  &mInterfaceFunctionTestProtocol8Guid,
                  EFI_NATIVE_INTERFACE,
                  &PrivateData->InterfaceFunctionTestProtocol8
                  );
  if (!EFI_ERROR(Status)) {
    return EFI_SUCCESS;
  }

ErrorExit:
  gtBS->CloseProtocol (
            Controller,
            &mInterfaceFunctionTestProtocol2Guid,
            This->DriverBindingHandle,
            Controller
            );
  gtBS->CloseProtocol (
            Controller,
            &mInterfaceFunctionTestProtocol3Guid,
            This->DriverBindingHandle,
            Controller
            );
  return Status;
}

EFI_STATUS
DeviceDriver15BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  DEVICE_DRIVER_15_PRIVATE_DATA          *PrivateData;
  
  PrivateData = DEVICE_DRIVER_15_PRIVATE_DATA_FROM_DRIVER_BINDING (This);
  
  gtBS->UninstallProtocolInterface (
            Controller,
            &mInterfaceFunctionTestProtocol8Guid,
            &PrivateData->InterfaceFunctionTestProtocol8
            );
  
  gtBS->CloseProtocol (
            Controller,
            &mInterfaceFunctionTestProtocol2Guid,
            This->DriverBindingHandle,
            Controller
            );
  gtBS->CloseProtocol (
            Controller,
            &mInterfaceFunctionTestProtocol3Guid,
            This->DriverBindingHandle,
            Controller
            );
  return EFI_SUCCESS;
}

void
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  )
{
  DriverBinding->Supported            = DeviceDriver15BindingSupported;
  DriverBinding->Start                = DeviceDriver15BindingStart;
  DriverBinding->Stop                 = DeviceDriver15BindingStop;
  DriverBinding->Version              = 0x10;
  DriverBinding->ImageHandle          = NULL;
  DriverBinding->DriverBindingHandle  = NULL;
}

VOID
Protocol8ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_8   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  )
{
  *ProtocolAttributes = This->ProtocolAttributes;
}

VOID
InitializeInterfaceFunctionTestProtocol8 (
  INTERFACE_FUNCTION_TEST_PROTOCOL_8     *InterfaceFunctionTestProtocol8
  )
{
  InterfaceFunctionTestProtocol8->ReportProtocolAttributes = Protocol8ReportProtocolAttributes;
  InterfaceFunctionTestProtocol8->ProtocolAttributes.ProtocolId = InterfaceFunctionTestProtocol8Id;
  InterfaceFunctionTestProtocol8->ProtocolAttributes.ReinstallField = 0;
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
DeviceDriver15Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
              mPrivateData->DriverBinding.DriverBindingHandle,
              &gEfiDriverBindingProtocolGuid,
              &mPrivateData->DriverBinding
              );
  gtBS->FreePool (mPrivateData);
  
  return EFI_SUCCESS;
}