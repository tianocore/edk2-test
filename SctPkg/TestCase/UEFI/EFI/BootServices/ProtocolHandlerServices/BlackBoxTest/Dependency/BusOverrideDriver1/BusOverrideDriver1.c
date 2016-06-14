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

  BusOverrideDriver1.c

Abstract:

  for Protocol Handler Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "Misc.h"
#include "../Inc/TestDriver.h"
//
// BusOverrideDriver1:
//
//

//
// data definition here
//
typedef struct {
  EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL   BusOverride;
  EFI_DRIVER_BINDING_PROTOCOL                 DriverBinding;
  EFI_HANDLE                                  ChildHandle;
  INTERFACE_FUNCTION_TEST_PROTOCOL_1          InterfaceFunctionTestProtocol1;
  EFI_HANDLE                                  DriverImageHandle[2];
  UINTN                                       Index;
} BUS_OVERRIDE_PRIVATE_DATA;

#define BUS_OVERRIDE_PRIVATE_DATA_FROM_DRIVER_BINDING(a) \
  BASE_CR(a, BUS_OVERRIDE_PRIVATE_DATA, DriverBinding)

#define BUS_OVERRIDE_PRIVATE_DATA_FROM_THIS(a) \
  BASE_CR(a, BUS_OVERRIDE_PRIVATE_DATA, BusOverride)

BUS_OVERRIDE_PRIVATE_DATA          *mPrivateData;

EFI_STATUS
InitializeBusOverrideDriver1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BusOverrideDriver1BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
BusOverrideDriver1BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
BusOverrideDriver1BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );

void
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  );

EFI_STATUS
BusOverrideDriver1GetDriver (
  IN     EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN OUT EFI_HANDLE                                 *DriverImageHandle
  );

STATIC
EFI_STATUS
LoadAndStartImage (
  EFI_HANDLE                          CurrentImageHandle,
  CHAR16                              *FileName,
  EFI_HANDLE                          *StartImage
  );

EFI_STATUS
BusOverrideDriver1Unload (
  IN EFI_HANDLE       ImageHandle
  );

//
// global variable for this test driver's image handle
//

EFI_STATUS
InitializeBusOverrideDriver1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImageInfoPtr;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //
  SctInitializeLib (ImageHandle, SystemTable);

  //
  // allocate memory for PrivateData
  //
  Status = gtBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof (BUS_OVERRIDE_PRIVATE_DATA),
                        (VOID**)&mPrivateData
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  gtBS->SetMem (mPrivateData,sizeof (BUS_OVERRIDE_PRIVATE_DATA),0);
  mPrivateData->Index = 0xffffffff;

  LoadAndStartImage (
              ImageHandle,
              DEVICE_DRIVER_110_NAME,
              &mPrivateData->DriverImageHandle[0]
              );
  LoadAndStartImage (
              ImageHandle,
              DEVICE_DRIVER_111_NAME,
              &mPrivateData->DriverImageHandle[1]
              );

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

  LoadedImageInfoPtr->Unload = BusOverrideDriver1Unload;

  return EFI_SUCCESS;

}

EFI_STATUS
BusOverrideDriver1BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS        Status;

  Status = gtBS->OpenProtocol (
                      Controller,
                      &mTestNoInterfaceProtocol2Guid,
                      NULL,
                      This->DriverBindingHandle,
                      Controller,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  if (EFI_ERROR(Status)) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BusOverrideDriver1BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  BUS_OVERRIDE_PRIVATE_DATA             *PrivateData;
  VOID                                  *ProtInstance;

  PrivateData = BUS_OVERRIDE_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mTestNoInterfaceProtocol2Guid,
                     &ProtInstance,
                     This->DriverBindingHandle,
                     Controller,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeInterfaceFunctionTestProtocol1 (&PrivateData->InterfaceFunctionTestProtocol1);

  PrivateData->BusOverride.GetDriver = BusOverrideDriver1GetDriver;

  PrivateData->ChildHandle = NULL;
  Status = gtBS->InstallMultipleProtocolInterfaces (
                  &PrivateData->ChildHandle,
                  &mInterfaceFunctionTestProtocol1Guid,
                  &PrivateData->InterfaceFunctionTestProtocol1,
                  &gEfiBusSpecificDriverOverrideProtocolGuid,
                  &PrivateData->BusOverride,
                  NULL
                  );
  if (EFI_ERROR(Status)) {
    gtBS->CloseProtocol (
            Controller,
            &mTestNoInterfaceProtocol2Guid,
            This->DriverBindingHandle,
            Controller
            );
    return Status;
  }

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mTestNoInterfaceProtocol2Guid,
                     &ProtInstance,
                     This->DriverBindingHandle,
                     PrivateData->ChildHandle,
                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                     );
  if (EFI_ERROR(Status)) {
    gtBS->UninstallMultipleProtocolInterfaces (
                  PrivateData->ChildHandle,
                  &mInterfaceFunctionTestProtocol1Guid,
                  &PrivateData->InterfaceFunctionTestProtocol1,
                  &gEfiBusSpecificDriverOverrideProtocolGuid,
                  &PrivateData->BusOverride,
                  NULL
                  );
    gtBS->CloseProtocol (
            Controller,
            &mTestNoInterfaceProtocol2Guid,
            This->DriverBindingHandle,
            Controller
            );
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BusOverrideDriver1BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  BUS_OVERRIDE_PRIVATE_DATA           *PrivateData;
  UINTN                               Index;
  EFI_STATUS                          Status;
  BOOLEAN                             AllChildrenStopped;

  PrivateData = BUS_OVERRIDE_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  if (NumberOfChildren == 0) {

    gtBS->CloseProtocol (
            Controller,
            &mTestNoInterfaceProtocol2Guid,
            This->DriverBindingHandle,
            Controller
            );
    return EFI_SUCCESS;
  }

  AllChildrenStopped = TRUE;

  for (Index = 0; Index < NumberOfChildren; Index++) {

    gtBS->CloseProtocol (
            Controller,
            &mTestNoInterfaceProtocol2Guid,
            This->DriverBindingHandle,
            ChildHandleBuffer[Index]
            );
    Status = gtBS->UninstallMultipleProtocolInterfaces (
                  ChildHandleBuffer[Index],
                  &mInterfaceFunctionTestProtocol1Guid,
                  &PrivateData->InterfaceFunctionTestProtocol1,
                  &gEfiBusSpecificDriverOverrideProtocolGuid,
                  &PrivateData->BusOverride,
                  NULL
                  );
    if (EFI_ERROR (Status)) {
      AllChildrenStopped = FALSE;
    }
  }

  if (!AllChildrenStopped) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

void
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  )
{
  DriverBinding->Supported            = BusOverrideDriver1BindingSupported;
  DriverBinding->Start                = BusOverrideDriver1BindingStart;
  DriverBinding->Stop                 = BusOverrideDriver1BindingStop;
  DriverBinding->Version              = 0x10;
  DriverBinding->ImageHandle          = NULL;
  DriverBinding->DriverBindingHandle  = NULL;
}

EFI_STATUS
BusOverrideDriver1GetDriver (
  IN     EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN OUT EFI_HANDLE                                 *DriverImageHandle
  )
{
  BUS_OVERRIDE_PRIVATE_DATA           *PrivateData;

  PrivateData = BUS_OVERRIDE_PRIVATE_DATA_FROM_THIS (This);

  if (*DriverImageHandle == NULL) {
    PrivateData->Index = 0;
  }

  if (PrivateData->Index >= 2) {
    return EFI_NOT_FOUND;
  }

  *DriverImageHandle = PrivateData->DriverImageHandle[PrivateData->Index];

  PrivateData->Index ++;

  return EFI_SUCCESS;
}

EFI_STATUS
LoadAndStartImage (
  EFI_HANDLE                          CurrentImageHandle,
  CHAR16                              *FileName,
  EFI_HANDLE                          *StartImage
  )
{
  EFI_STATUS                          Status;
  EFI_LOADED_IMAGE_PROTOCOL           *LoadImage;
  EFI_DEVICE_PATH_PROTOCOL            *FileDevPath;
  CHAR16                              *EntireFileName;
  CHAR16                              *FilePath;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib;

  Status = gtBS->HandleProtocol (
                      CurrentImageHandle,
                      &gEfiLoadedImageProtocolGuid,
                      &LoadImage
                      );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Use profile lib at here just for less effect on the current system. It is
  // dependent on the implementation of test framework. So need to be updated
  // later.
  //
  Status = gtBS->LocateProtocol (
                   &gEfiTestProfileLibraryGuid,
                   NULL,
                   &ProfileLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                          ProfileLib,
                          &DevicePath,
                          &FilePath
                          );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  EntireFileName = SctPoolPrint (L"%s\\%s\\%s", FilePath, DEPENDENCY_DIR_NAME, FileName);

  SctFreePool (FilePath);
  SctFreePool (DevicePath);

  FileDevPath = SctFileDevicePath (LoadImage->DeviceHandle, EntireFileName);

  SctFreePool (EntireFileName);

  if (FileDevPath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gtBS->LoadImage (
                FALSE,
                CurrentImageHandle,
                FileDevPath,
                NULL,
                0,
                StartImage
                );

  gtBS->FreePool (FileDevPath);

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gtBS->StartImage (*StartImage,0,NULL);

  return Status;
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
BusOverrideDriver1Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  UINTN     Index;
  //
  // free resources
  //
  for (Index = 0; Index < 2; Index ++) {
    if (mPrivateData->DriverImageHandle[Index] != NULL) {
      gtBS->UnloadImage (mPrivateData->DriverImageHandle[Index]);
    }
  }

  if (mPrivateData->DriverBinding.DriverBindingHandle != NULL) {
    gtBS->UninstallProtocolInterface (
                mPrivateData->DriverBinding.DriverBindingHandle,
                &gEfiDriverBindingProtocolGuid,
                &mPrivateData->DriverBinding
                );
  }
  gtBS->FreePool (mPrivateData);

  return EFI_SUCCESS;
}
