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

  DBindingDriver4.c

Abstract:

  for Protocol Handler Boot Services Black Box Test

--*/

#include "ProtocolDefinition.h"
#include "../Inc/TestDriver.h"

//
// DriverBindingDriver4:
// Open InterfaceTestProtocol1 EXCLUSIVE;
// Open InterfaceTestProtocol2 EXCLUSIVE;
// Open InterfaceTestProtocol3 EXCLUSIVE
// Open InterfaceTestProtocol4 EXCLUSIVE
// Export EXTERNAL_DRIVER_PROTOCOL_1 protocol
//

//
// data definition here
//
#define DBINDING_DRIVER_4_PRIVATE_DATA_FROM_THIS(a) \
 BASE_CR(a, DBINDING_DRIVER_PRIVATE_DATA, ExProt1)

#define DBINDING_DRIVER_4_PRIVATE_DATA_FROM_DRIVER_BINDING(a) \
 BASE_CR(a, DBINDING_DRIVER_PRIVATE_DATA, DriverBinding)

DBINDING_DRIVER_PRIVATE_DATA          *mPrivateData;

EFI_STATUS
EFIAPI
InitializeDBindingDriver4 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
DBindingDriver4BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
DBindingDriver4BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
DBindingDriver4BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );

VOID
EFIAPI
DBindingDriver4GetNextStatusReport (
  IN EXTERNAL_DRIVER_PROTOCOL_1   *This,
  IN EFI_STATUS                   *NextStatus
  );

VOID
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  );

EFI_STATUS
EFIAPI
DBindingDriver4Unload (
  IN EFI_HANDLE       ImageHandle
  );

//
// global variable for this test driver's image handle
//

EFI_STATUS
EFIAPI
InitializeDBindingDriver4 (
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
                        sizeof (DBINDING_DRIVER_PRIVATE_DATA),
                        (VOID**)&mPrivateData
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  gtBS->SetMem (mPrivateData,sizeof (DBINDING_DRIVER_PRIVATE_DATA),0);

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

  LoadedImageInfoPtr->Unload = DBindingDriver4Unload;

  mPrivateData->ArrayCount = 4;
  Status = gtBS->AllocatePool (
                        EfiBootServicesData,
                        mPrivateData->ArrayCount * sizeof (EFI_STATUS),
                        (VOID**)&(mPrivateData->StatusArray)
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  //
  // init StatusArray with invalid data
  //
  gtBS->SetMem (
        mPrivateData->StatusArray,
        mPrivateData->ArrayCount * sizeof (EFI_STATUS),
        0xff
        );

  Status = gtBS->AllocatePool (
                        EfiBootServicesData,
                        mPrivateData->ArrayCount * sizeof (EFI_HANDLE),
                        (VOID**)&(mPrivateData->HandleArray)
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  gtBS->SetMem (
        mPrivateData->HandleArray,
        mPrivateData->ArrayCount * sizeof (EFI_HANDLE),
        0
        );

  Status = gtBS->AllocatePool (
                        EfiBootServicesData,
                        mPrivateData->ArrayCount * sizeof (EFI_GUID),
                        (VOID**)&(mPrivateData->ProtGuidArray)
                        );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  mPrivateData->ProtGuidArray[0] = mInterfaceFunctionTestProtocol1Guid;
  mPrivateData->ProtGuidArray[1] = mInterfaceFunctionTestProtocol2Guid;
  mPrivateData->ProtGuidArray[2] = mInterfaceFunctionTestProtocol3Guid;
  mPrivateData->ProtGuidArray[3] = mInterfaceFunctionTestProtocol4Guid;

  Status = gtBS->InstallProtocolInterface (
                  &mPrivateData->ChildHandle,
                  &mTestNoInterfaceProtocol1Guid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
DBindingDriver4BindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS        Status1,Status2,Status3,Status4;


  Status1 = gtBS->OpenProtocol (
                      Controller,
                      &mInterfaceFunctionTestProtocol1Guid,
                      (VOID **) NULL,
                      This->DriverBindingHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  Status2 = gtBS->OpenProtocol (
                      Controller,
                      &mInterfaceFunctionTestProtocol2Guid,
                      (VOID **) NULL,
                      This->DriverBindingHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  Status3 = gtBS->OpenProtocol (
                      Controller,
                      &mInterfaceFunctionTestProtocol3Guid,
                      (VOID **) NULL,
                      This->DriverBindingHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  Status4 = gtBS->OpenProtocol (
                      Controller,
                      &mInterfaceFunctionTestProtocol4Guid,
                      (VOID **) NULL,
                      This->DriverBindingHandle,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                      );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)
      || EFI_ERROR(Status3) || EFI_ERROR(Status4)) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DBindingDriver4BindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  INTERFACE_FUNCTION_TEST_PROTOCOL_1    *IFTestProt1;
  INTERFACE_FUNCTION_TEST_PROTOCOL_2    *IFTestProt2;
  INTERFACE_FUNCTION_TEST_PROTOCOL_3    *IFTestProt3;
  INTERFACE_FUNCTION_TEST_PROTOCOL_4    *IFTestProt4;
  DBINDING_DRIVER_PRIVATE_DATA          *PrivateData;

  PrivateData = DBINDING_DRIVER_4_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  PrivateData->HandleArray[0] = Controller;
  PrivateData->StatusArray[0] = gtBS->OpenProtocol (
                                  Controller,
                                  &mInterfaceFunctionTestProtocol1Guid,
                                  (VOID **) &IFTestProt1,
                                  This->DriverBindingHandle,
                                  PrivateData->ChildHandle,
                                  EFI_OPEN_PROTOCOL_EXCLUSIVE
                                  );

  PrivateData->HandleArray[1] = Controller;
  PrivateData->StatusArray[1] = gtBS->OpenProtocol (
                                  Controller,
                                  &mInterfaceFunctionTestProtocol2Guid,
                                  (VOID **) &IFTestProt2,
                                  This->DriverBindingHandle,
                                  PrivateData->ChildHandle,
                                  EFI_OPEN_PROTOCOL_EXCLUSIVE
                                  );

  PrivateData->HandleArray[2] = Controller;
  PrivateData->StatusArray[2] = gtBS->OpenProtocol (
                                  Controller,
                                  &mInterfaceFunctionTestProtocol3Guid,
                                  (VOID **) &IFTestProt3,
                                  This->DriverBindingHandle,
                                  PrivateData->ChildHandle,
                                  EFI_OPEN_PROTOCOL_EXCLUSIVE
                                  );

  PrivateData->HandleArray[3] = Controller;
  PrivateData->StatusArray[3] = gtBS->OpenProtocol (
                                  Controller,
                                  &mInterfaceFunctionTestProtocol4Guid,
                                  (VOID **) &IFTestProt4,
                                  This->DriverBindingHandle,
                                  PrivateData->ChildHandle,
                                  EFI_OPEN_PROTOCOL_EXCLUSIVE
                                  );

  if (PrivateData->Handle == NULL) {
    PrivateData->ExProt1.GetNextStatusReport = DBindingDriver4GetNextStatusReport;
    gtBS->InstallProtocolInterface (
                    &PrivateData->Handle,
                    &mExternalDriverProtocol1Guid,
                    EFI_NATIVE_INTERFACE,
                    &PrivateData->ExProt1
                    );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DBindingDriver4BindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  DBINDING_DRIVER_PRIVATE_DATA          *PrivateData;
  UINTN                                 Index;

  PrivateData = DBINDING_DRIVER_4_PRIVATE_DATA_FROM_DRIVER_BINDING (This);

  if (PrivateData->HandleArray != NULL && PrivateData->ProtGuidArray != NULL) {
    for (Index = 0; Index < PrivateData->ArrayCount; Index ++) {
      if (PrivateData->HandleArray[Index] != NULL) {
        gtBS->CloseProtocol (
              PrivateData->HandleArray[Index],
              &PrivateData->ProtGuidArray[Index],
              PrivateData->DriverBinding.DriverBindingHandle,
              PrivateData->ChildHandle
              );
      }
    }
  }

  return EFI_SUCCESS;
}

VOID
EFIAPI
DBindingDriver4GetNextStatusReport (
  IN EXTERNAL_DRIVER_PROTOCOL_1   *This,
  IN EFI_STATUS                   *NextStatus
  )
{
  DBINDING_DRIVER_PRIVATE_DATA            *PrivateData;

  PrivateData = DBINDING_DRIVER_4_PRIVATE_DATA_FROM_THIS (This);

  if (*NextStatus == 0xffffffff) {
    PrivateData->Count = 0;
  } else {
    PrivateData->Count ++;
  }

  if (PrivateData->Count >= PrivateData->ArrayCount) {
    *NextStatus = 0xffffffff;
  } else {
    *NextStatus = PrivateData->StatusArray[PrivateData->Count];
  }

  return;
}

VOID
InitializeDriverBinding (
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding
  )
{
  DriverBinding->Supported            = DBindingDriver4BindingSupported;
  DriverBinding->Start                = DBindingDriver4BindingStart;
  DriverBinding->Stop                 = DBindingDriver4BindingStop;
  DriverBinding->Version              = 0x10;
  DriverBinding->ImageHandle          = NULL;
  DriverBinding->DriverBindingHandle  = NULL;
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
EFIAPI
DBindingDriver4Unload (
  IN EFI_HANDLE       ImageHandle
  )
{
  UINTN                                   Index;

  //
  // close protocols
  //
  if (mPrivateData->HandleArray != NULL && mPrivateData->ProtGuidArray != NULL) {
    for (Index = 0; Index < mPrivateData->ArrayCount; Index ++) {
      if (mPrivateData->HandleArray[Index] != NULL) {
        gtBS->CloseProtocol (
              mPrivateData->HandleArray[Index],
              &mPrivateData->ProtGuidArray[Index],
              mPrivateData->DriverBinding.DriverBindingHandle,
              mPrivateData->ChildHandle
              );
      }
    }
  }

  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
            ImageHandle,
            &gEfiDriverBindingProtocolGuid,
            &mPrivateData->DriverBinding
            );

  if (mPrivateData->Handle != NULL) {
    gtBS->UninstallProtocolInterface (
                    mPrivateData->Handle,
                    &mExternalDriverProtocol1Guid,
                    &mPrivateData->ExProt1
                    );
  }

  if (mPrivateData->HandleArray != NULL) {
    gtBS->FreePool (mPrivateData->HandleArray);
  }

  if (mPrivateData->ProtGuidArray != NULL) {
    gtBS->FreePool (mPrivateData->ProtGuidArray);
  }

  if (mPrivateData->StatusArray != NULL) {
    gtBS->FreePool (mPrivateData->StatusArray);
  }

  if (mPrivateData->ChildHandle != NULL) {
    gtBS->UninstallProtocolInterface (
              mPrivateData->ChildHandle,
              &mTestNoInterfaceProtocol1Guid,
              NULL
              );
  }
  gtBS->FreePool (mPrivateData);

  return EFI_SUCCESS;
}
