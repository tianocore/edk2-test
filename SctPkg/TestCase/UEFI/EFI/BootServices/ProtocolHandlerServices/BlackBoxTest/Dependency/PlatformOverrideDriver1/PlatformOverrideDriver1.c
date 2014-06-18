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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  PlatformOverrideDriver1.c

Abstract:

  for Protocol Handler Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "Misc.h"
#include "../Inc/TestDriver.h"

//
// PlatformOverrideDriver1:
//
//

//
// data definition here
//
typedef struct {
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL     PlatformOverride;
  EFI_DRIVER_BINDING_PROTOCOL               DriverBinding;
  UINTN                                     PathIndex;
  UINTN                                     ImageIndex;
  EFI_DEVICE_PATH_PROTOCOL                  *DriverImagePath[2];
  EFI_HANDLE                                DriverImageHandle[2];

  //
  // It is used to save the original platform driver override protocol
  //
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL     *OrigPlatformOverride;
} PLATFORM_OVERRIDE_PRIVATE_DATA;

#define PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_DRIVER_BINDING(a) \
 BASE_CR(a, PLATFORM_OVERRIDE_PRIVATE_DATA, DriverBinding)

 #define PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_THIS(a) \
 BASE_CR(a, PLATFORM_OVERRIDE_PRIVATE_DATA, PlatformOverride)

PLATFORM_OVERRIDE_PRIVATE_DATA          *mPrivateData;

EFI_STATUS
InitializePlatformOverrideDriver1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
PlatformOverrideDriver1BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
PlatformOverrideDriver1BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
PlatformOverrideDriver1BindingStop (
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
PlatformOverrideDriver1GetDriver (
  IN     EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN     EFI_HANDLE                             ControllerHandle,
  IN OUT EFI_HANDLE                             *DriverImageHandle
  );

EFI_STATUS
PlatformOverrideDriver1GetDriverPath (
  IN     EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN     EFI_HANDLE                             ControllerHandle,
  IN OUT EFI_DEVICE_PATH_PROTOCOL               **DriverImagePath
  );

EFI_STATUS
PlatformOverrideDriver1DriverLoaded (
  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               *DriverImagePath,
  IN EFI_HANDLE                             DriverImageHandle
  );

EFI_STATUS
ComposeFilePath (
  EFI_HANDLE                          CurrentImageHandle,
  CHAR16                              *FileName,
  EFI_DEVICE_PATH_PROTOCOL            **FilePath
  );

EFI_STATUS
PlatformOverrideDriver1Unload (
  IN EFI_HANDLE       ImageHandle
  );

//
// global variable for this test driver's image handle
//

EFI_STATUS
InitializePlatformOverrideDriver1 (
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
                        sizeof (PLATFORM_OVERRIDE_PRIVATE_DATA),
                        (VOID**)&mPrivateData
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  gtBS->SetMem (mPrivateData,sizeof (PLATFORM_OVERRIDE_PRIVATE_DATA),0);
  mPrivateData->PathIndex = 0xffffffff;
  mPrivateData->ImageIndex = 0xffffffff;

  //
  // Set for DriverImagePath
  //
  ComposeFilePath (
              ImageHandle,
              DEVICE_DRIVER_18_NAME,
              &mPrivateData->DriverImagePath[0]
              );

  ComposeFilePath (
              ImageHandle,
              DEVICE_DRIVER_19_NAME,
              &mPrivateData->DriverImagePath[1]
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

  LoadedImageInfoPtr->Unload = PlatformOverrideDriver1Unload;

  return EFI_SUCCESS;

}

EFI_STATUS
PlatformOverrideDriver1BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS        Status;

  Status = gtBS->OpenProtocol (
                      Controller,
                      &mTestNoInterfaceProtocol1Guid,
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
PlatformOverrideDriver1BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  PLATFORM_OVERRIDE_PRIVATE_DATA        *PrivateData;
  VOID                                  *ProtInstance;
  UINTN                                 BufferSize;
  EFI_HANDLE                            Buffer;

  PrivateData = PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mTestNoInterfaceProtocol1Guid,
                     &ProtInstance,
                     This->DriverBindingHandle,
                     Controller,
                     EFI_OPEN_PROTOCOL_BY_DRIVER
                     );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  PrivateData->PlatformOverride.GetDriver = PlatformOverrideDriver1GetDriver;
  PrivateData->PlatformOverride.GetDriverPath = PlatformOverrideDriver1GetDriverPath;
  PrivateData->PlatformOverride.DriverLoaded = PlatformOverrideDriver1DriverLoaded;

  //
  // Install or reinstall the platform driver override protocol
  //
  BufferSize = sizeof (EFI_HANDLE);
  Buffer     = NULL;

  Status = gtBS->LocateHandle (
                  ByProtocol,
                  &gEfiPlatformDriverOverrideProtocolGuid,
                  NULL,
                  &BufferSize,
                  &Buffer
                  );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    //
    // Only one platform driver override protocol can exist on a platform. So
    // if the error status is not EFI_NOT_FOUND, return error.
    //
    return Status;
  }

  if (Status == EFI_SUCCESS) {
    //
    // The protocol exists, then reinstall it
    //
    Status = gtBS->HandleProtocol (
                    Controller,
                    &gEfiPlatformDriverOverrideProtocolGuid,
                    &PrivateData->OrigPlatformOverride
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = gtBS->ReinstallProtocolInterface (
                    Controller,
                    &gEfiPlatformDriverOverrideProtocolGuid,
                    PrivateData->OrigPlatformOverride,
                    &PrivateData->PlatformOverride
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else {
    //
    // The protocol does not exist, then install it
    //
    Status = gtBS->InstallProtocolInterface (
                    &Controller,
                    &gEfiPlatformDriverOverrideProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &PrivateData->PlatformOverride
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  //
  // Install the driver's protocol
  //
  Status = gtBS->InstallProtocolInterface (
                  &Controller,
                  &mPlatformOverrideDriver1Guid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );

  return Status;
}

EFI_STATUS
PlatformOverrideDriver1BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  PLATFORM_OVERRIDE_PRIVATE_DATA          *PrivateData;

  PrivateData = PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  //
  // Uninstall or reinstall the original platform driver override protocol
  //
  if (PrivateData->OrigPlatformOverride != NULL) {
    //
    // The original protocol exists, then reinstall it back
    //
    gtBS->ReinstallProtocolInterface (
            Controller,
            &gEfiPlatformDriverOverrideProtocolGuid,
            &PrivateData->PlatformOverride,
            PrivateData->OrigPlatformOverride
            );
  } else {
    //
    // The original protocol does not exist, then uninstall it
    //
    gtBS->UninstallProtocolInterface (
            Controller,
            &gEfiPlatformDriverOverrideProtocolGuid,
            &PrivateData->PlatformOverride
            );
  }

  gtBS->UninstallProtocolInterface (
            Controller,
            &mPlatformOverrideDriver1Guid,
            NULL
            );

  gtBS->CloseProtocol (
            Controller,
            &mTestNoInterfaceProtocol1Guid,
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
  DriverBinding->Supported            = PlatformOverrideDriver1BindingSupported;
  DriverBinding->Start                = PlatformOverrideDriver1BindingStart;
  DriverBinding->Stop                 = PlatformOverrideDriver1BindingStop;
  DriverBinding->Version              = 0x10;
  DriverBinding->ImageHandle          = NULL;
  DriverBinding->DriverBindingHandle  = NULL;
}

EFI_STATUS
PlatformOverrideDriver1GetDriver (
  IN     EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN     EFI_HANDLE                             ControllerHandle,
  IN OUT EFI_HANDLE                             *DriverImageHandle
  )
{
  EFI_STATUS                              Status;
  PLATFORM_OVERRIDE_PRIVATE_DATA          *PrivateData;

  PrivateData = PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_THIS (This);

  Status = gtBS->OpenProtocol (
                      ControllerHandle,
                      &mInterfaceFunctionTestProtocol1Guid,
                      NULL,
                      PrivateData->DriverBinding.DriverBindingHandle,
                      ControllerHandle,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  if (*DriverImageHandle == NULL) {
    PrivateData->ImageIndex = 0;
  }

  if (PrivateData->ImageIndex >= 2) {
    return EFI_NOT_FOUND;
  }

  *DriverImageHandle = PrivateData->DriverImageHandle[PrivateData->ImageIndex];

  PrivateData->ImageIndex ++;

  return EFI_SUCCESS;
}

EFI_STATUS
PlatformOverrideDriver1GetDriverPath (
  IN     EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN     EFI_HANDLE                             ControllerHandle,
  IN OUT EFI_DEVICE_PATH_PROTOCOL               **DriverImagePath
  )
{
  EFI_STATUS                              Status;
  PLATFORM_OVERRIDE_PRIVATE_DATA          *PrivateData;

  PrivateData = PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_THIS (This);

  Status = gtBS->OpenProtocol (
                      ControllerHandle,
                      &mInterfaceFunctionTestProtocol1Guid,
                      NULL,
                      PrivateData->DriverBinding.DriverBindingHandle,
                      ControllerHandle,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  if (*DriverImagePath == NULL) {
    PrivateData->PathIndex = 0;
  }

  if (PrivateData->PathIndex >= 2) {
    return EFI_NOT_FOUND;
  }


  *DriverImagePath = PrivateData->DriverImagePath[PrivateData->PathIndex];

  PrivateData->PathIndex ++;

  return EFI_SUCCESS;
}

EFI_STATUS
PlatformOverrideDriver1DriverLoaded (
  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               *DriverImagePath,
  IN EFI_HANDLE                             DriverImageHandle
  )
{
  EFI_STATUS                              Status;
  PLATFORM_OVERRIDE_PRIVATE_DATA          *PrivateData;
  UINTN                                   Index;

  PrivateData = PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_THIS (This);

  Status = gtBS->OpenProtocol (
                      ControllerHandle,
                      &mInterfaceFunctionTestProtocol1Guid,
                      NULL,
                      PrivateData->DriverBinding.DriverBindingHandle,
                      ControllerHandle,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < 2; Index ++) {

    if (DriverImagePath == PrivateData->DriverImagePath[Index]) {
      break;
    }
  }

  if (Index == 2) {
    return EFI_NOT_FOUND;
  }

  PrivateData->DriverImageHandle[Index] = DriverImageHandle;

  return EFI_SUCCESS;
}

EFI_STATUS
ComposeFilePath (
  EFI_HANDLE                          CurrentImageHandle,
  CHAR16                              *FileName,
  EFI_DEVICE_PATH_PROTOCOL            **FileDevPath
  )
{
  EFI_STATUS                          Status;
  CHAR16                              *EntireFileName;
  CHAR16                              *FilePath;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  EFI_LOADED_IMAGE_PROTOCOL           *LoadImage;
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

  *FileDevPath = SctFileDevicePath (LoadImage->DeviceHandle, EntireFileName);

  SctFreePool (EntireFileName);

  if (FileDevPath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
PlatformOverrideDriver1Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  UINTN           Index;
  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
              mPrivateData->DriverBinding.DriverBindingHandle,
              &gEfiDriverBindingProtocolGuid,
              &mPrivateData->DriverBinding
              );

  for (Index = 0; Index < 2; Index ++) {
    if (mPrivateData->DriverImagePath[Index] != NULL) {
      gtBS->FreePool (mPrivateData->DriverImagePath[Index]);
      mPrivateData->DriverImagePath[Index] = NULL;
    }
  }
  gtBS->FreePool (mPrivateData);

  return EFI_SUCCESS;
}
