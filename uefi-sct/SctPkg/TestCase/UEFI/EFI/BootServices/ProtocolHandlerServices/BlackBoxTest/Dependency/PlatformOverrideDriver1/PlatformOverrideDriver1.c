/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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

  EFI_HANDLE                                OrigHandle;
  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL     *OrigPlatformOverride;
} PLATFORM_OVERRIDE_PRIVATE_DATA;

#define PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_DRIVER_BINDING(a) \
 BASE_CR(a, PLATFORM_OVERRIDE_PRIVATE_DATA, DriverBinding)

 #define PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_THIS(a) \
 BASE_CR(a, PLATFORM_OVERRIDE_PRIVATE_DATA, PlatformOverride)

PLATFORM_OVERRIDE_PRIVATE_DATA          *mPrivateData;

EFI_STATUS
EFIAPI
InitializePlatformOverrideDriver1 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
PlatformOverrideDriver1BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
PlatformOverrideDriver1BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
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
EFIAPI
PlatformOverrideDriver1GetDriver (
  IN     EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN     EFI_HANDLE                             ControllerHandle,
  IN OUT EFI_HANDLE                             *DriverImageHandle
  );

EFI_STATUS
EFIAPI
PlatformOverrideDriver1GetDriverPath (
  IN     EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
  IN     EFI_HANDLE                             ControllerHandle,
  IN OUT EFI_DEVICE_PATH_PROTOCOL               **DriverImagePath
  );

EFI_STATUS
EFIAPI
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
EFIAPI
PlatformOverrideDriver1Unload (
  IN EFI_HANDLE       ImageHandle
  );

//
// global variable for this test driver's image handle
//

EFI_STATUS
EFIAPI
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
EFIAPI
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
                      (VOID **) NULL,
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
EFIAPI
PlatformOverrideDriver1BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  PLATFORM_OVERRIDE_PRIVATE_DATA        *PrivateData;
  VOID                                  *ProtInstance;
  UINTN                                 HandleCount;
  EFI_HANDLE                            *HandleBuffer;

  PrivateData = PLATFORM_OVERRIDE_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  Status = gtBS->OpenProtocol (
                     Controller,
                     &mTestNoInterfaceProtocol1Guid,
                     (VOID **) &ProtInstance,
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
  //BufferSize = sizeof (EFI_HANDLE);
  //Buffer     = NULL;

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gEfiPlatformDriverOverrideProtocolGuid,
                   NULL,
                   &HandleCount,
                   &HandleBuffer
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
                     HandleBuffer[0],
                     &gEfiPlatformDriverOverrideProtocolGuid,
                     (VOID **) &PrivateData->OrigPlatformOverride
                     );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = gtBS->ReinstallProtocolInterface (
                     HandleBuffer[0],
                     &gEfiPlatformDriverOverrideProtocolGuid,
                     PrivateData->OrigPlatformOverride,
                     &PrivateData->PlatformOverride
                     );
    if (EFI_ERROR (Status)) {
      return Status;
    }

	PrivateData->OrigHandle = HandleBuffer[0];

    //
    // Install the driver's protocol
    //
    Status = gtBS->InstallProtocolInterface (
                     HandleBuffer,
                     &mPlatformOverrideDriver1Guid,
                     EFI_NATIVE_INTERFACE,
                     NULL
                     );

    gtBS->FreePool( HandleBuffer);

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

    //
    // Install the driver's protocol
    //
    Status = gtBS->InstallProtocolInterface (
                     &Controller,
                     &mPlatformOverrideDriver1Guid,
                     EFI_NATIVE_INTERFACE,
                     NULL
                     );


  }


  return Status;
}

EFI_STATUS
EFIAPI
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
            PrivateData->OrigHandle,
            &gEfiPlatformDriverOverrideProtocolGuid,
            &PrivateData->PlatformOverride,
            PrivateData->OrigPlatformOverride
            );

    gtBS->UninstallProtocolInterface (
            PrivateData->OrigHandle,
            &mPlatformOverrideDriver1Guid,
            NULL
            );

    gtBS->CloseProtocol (
            PrivateData->OrigHandle,
            &mTestNoInterfaceProtocol1Guid,
            This->DriverBindingHandle,
            Controller
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

  }

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
EFIAPI
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
                      (VOID **) NULL,
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
EFIAPI
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
                      (VOID **) NULL,
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
EFIAPI
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
                      (VOID **) NULL,
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
                      (VOID **) &LoadImage
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
                   (VOID **) &ProfileLib
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
EFIAPI
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
