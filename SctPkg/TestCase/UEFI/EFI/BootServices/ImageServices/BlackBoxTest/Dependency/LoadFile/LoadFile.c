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

  LoadFile.c

Abstract:

  A test driver that implements LOAD_FILE protocol.

--*/

#include "ProtocolDefinition.h"
#include "EfiTest.h"
#include "SctLib.h"
#include <Library/EfiTestLib.h>

#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (LoadFile)
#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

#define MAX_STRING_LEN      250

EFI_HANDLE        mDriverImageHandle;

EFI_STATUS
InitializeLoadFileDriver (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
LoadFileDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
LoadFileDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
LoadFileDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );


EFI_STATUS
LoadFileDriverUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
EFIAPI
ImageTestLoadFile (
  IN EFI_LOAD_FILE_PROTOCOL           *This,
  IN EFI_DEVICE_PATH_PROTOCOL         *FilePath,
  IN BOOLEAN                          BootPolicy,
  IN OUT UINTN                        *BufferSize,
  IN VOID                             *Buffer OPTIONAL
  );

EFI_DRIVER_BINDING_PROTOCOL mLoadFileDriverBinding = {
    LoadFileDriverBindingSupported,
    LoadFileDriverBindingStart,
    LoadFileDriverBindingStop,
    0x10,
    NULL,
    NULL
  };

EFI_LOAD_FILE_PROTOCOL    mLoadFileProtocol = {
    ImageTestLoadFile
  };

EFI_DEVICE_PATH_PROTOCOL    *mLoadFileDriverDevicePath;

//
// global variable for this test driver's image handle
//

EFI_STATUS
InitializeLoadFileDriver (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_LOADED_IMAGE_PROTOCOL             *LoadedImageInfoPtr;

  EfiInitializeTestLib (ImageHandle, SystemTable);

  SctInitializeLib (ImageHandle, SystemTable);

  mDriverImageHandle = ImageHandle;
  mLoadFileDriverDevicePath = NULL;

  Status = gtBS->InstallProtocolInterface (
                   &ImageHandle,
                   &gEfiDriverBindingProtocolGuid,
                   EFI_NATIVE_INTERFACE,
                   &mLoadFileDriverBinding
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  mLoadFileDriverBinding.ImageHandle = ImageHandle;
  mLoadFileDriverBinding.DriverBindingHandle = ImageHandle;

  //
  // UnLoad Function Handler
  //
  gtBS->HandleProtocol (
          ImageHandle,
          &gEfiLoadedImageProtocolGuid,
          (VOID*)&LoadedImageInfoPtr
          );

  LoadedImageInfoPtr->Unload = LoadFileDriverUnload;

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
LoadFileDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS        Status;
  VOID              *TestProtInstance;

  Status = gtBS->OpenProtocol (
                   Controller,
                   &mImageTestForLoadFileProtocol1Guid,
                   &TestProtInstance,
                   This->DriverBindingHandle,
                   Controller,
                   EFI_OPEN_PROTOCOL_BY_DRIVER
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  gtBS->CloseProtocol (
          Controller,
          &mImageTestForLoadFileProtocol1Guid,
          This->DriverBindingHandle,
          Controller
          );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
LoadFileDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  VOID                                  *TestProtInstance;

  Status = gtBS->OpenProtocol (
                   Controller,
                   &mImageTestForLoadFileProtocol1Guid,
                   &TestProtInstance,
                   This->DriverBindingHandle,
                   Controller,
                   EFI_OPEN_PROTOCOL_BY_DRIVER
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // in EFI1.1 test, if do not add the Print statement,
  // the efforts to connect the LoadFile driver will fail.
  // Don't know the reason.
  //
  SctPrint (L"\n");

  mLoadFileDriverDevicePath = SctDuplicateDevicePath (RemainingDevicePath);

  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Controller,
                   &gEfiLoadFileProtocolGuid,
                   &mLoadFileProtocol,
                   &gEfiDevicePathProtocolGuid,
                   mLoadFileDriverDevicePath,
                   NULL
                   );
  return Status;
}

EFI_STATUS
EFIAPI
LoadFileDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  EFI_STATUS        Status;

  Status = gtBS->OpenProtocol (
                   Controller,
                   &mImageTestForLoadFileProtocol1Guid,
                   NULL,
                   This->DriverBindingHandle,
                   Controller,
                   EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  gtBS->UninstallMultipleProtocolInterfaces (
          Controller,
          &gEfiLoadFileProtocolGuid,
          &mLoadFileProtocol,
          &gEfiDevicePathProtocolGuid,
          mLoadFileDriverDevicePath,
          NULL
          );

  gtBS->FreePool (mLoadFileDriverDevicePath);
  mLoadFileDriverDevicePath = NULL;

  gtBS->CloseProtocol (
          Controller,
          &mImageTestForLoadFileProtocol1Guid,
          This->DriverBindingHandle,
          Controller
          );

  return EFI_SUCCESS;
}

EFI_STATUS
CopySimpleFileToMemory (
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT UINT8                               **SourceBuffer,
  OUT UINTN                               *SourceBufferSize
  )
{
  EFI_STATUS                        Status;
  EFI_LOADED_IMAGE_PROTOCOL         *LoadImage;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Volume;
  EFI_FILE_HANDLE                   FileHandle;
  EFI_FILE_HANDLE                   Root;
  UINT8                             Temp;
  UINTN                             InfoSize;
  EFI_FILE_INFO                     *InfoBuffer;
  CHAR16                            *EntireFileName, *FilePath;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL *ProfileLib;

  //
  // init
  //
  InfoBuffer = NULL;
  *SourceBufferSize = 0;
  *SourceBuffer = NULL;
  EntireFileName = NULL;
  DevicePath = NULL;

  Status = gtBS->HandleProtocol (
                   CurrentImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   &LoadImage
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // locate simple file system on the LoadImage->DeviceHandle
  //
  Status = gtBS->HandleProtocol (
                   LoadImage->DeviceHandle,
                   &gEfiSimpleFileSystemProtocolGuid,
                   &Volume
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  EntireFileName = NULL;

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

  Root = NULL;
  FileHandle = NULL;
  Status = Volume->OpenVolume (Volume, &Root);
  if (!EFI_ERROR(Status)) {
    Status = Root->Open (
                     Root,
                     &FileHandle,
                     EntireFileName,
                     EFI_FILE_MODE_READ,
                     0
                     );
  }

  if (EFI_ERROR(Status)) {
    goto Done;
  }

  InfoSize = 1;
  Status = FileHandle->GetInfo (
                         FileHandle,
                         &gEfiFileInfoGuid,
                         &InfoSize,
                         &Temp
                         );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    Status = gtBS->AllocatePool (EfiBootServicesData, InfoSize, (VOID**)&InfoBuffer);

    if (!EFI_ERROR(Status)) {

      Status = FileHandle->GetInfo (
                             FileHandle,
                             &gEfiFileInfoGuid,
                             &InfoSize,
                             (VOID*)InfoBuffer
                             );
    }
  }

  if (EFI_ERROR(Status)) {
    goto Done;
  }

  *SourceBufferSize = (UINTN)InfoBuffer->FileSize;

  Status = gtBS->AllocatePool (EfiBootServicesData, *SourceBufferSize, (VOID**)SourceBuffer);
  if (EFI_ERROR(Status)) {
    goto Done;
  }

  //
  // roll the file to the start position
  //
  FileHandle->SetPosition (FileHandle, 0);

  Status = FileHandle->Read (FileHandle, SourceBufferSize, *SourceBuffer);

Done:
  //
  // release resource
  //
  if (EntireFileName != NULL) {
    SctFreePool (EntireFileName);
  }

  if (DevicePath != NULL) {
    SctFreePool (DevicePath);
  }

  if (FileHandle != NULL) {
    FileHandle->Close (FileHandle);
  }

  if (Root != NULL) {
    Root->Close (Root);
  }

  if (InfoBuffer != NULL) {
    gtBS->FreePool (InfoBuffer);
  }

  return Status;
}


EFI_STATUS
EFIAPI
ImageTestLoadFile (
  IN EFI_LOAD_FILE_PROTOCOL           *This,
  IN EFI_DEVICE_PATH_PROTOCOL         *FilePath,
  IN BOOLEAN                          BootPolicy,
  IN OUT UINTN                        *BufferSize,
  IN VOID                             *Buffer OPTIONAL
  )
{

  EFI_STATUS                  Status;
  VENDOR_DEVICE_PATH          *VendorDevicePathNode;
  UINT8                       *SourceBuffer;
  UINTN                       SourceBufferSize;

  SourceBuffer = NULL;
  SourceBufferSize = 0;
  Status = EFI_SUCCESS;

  if ((FilePath == NULL) || (BufferSize == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (SctDevicePathNodeLength (FilePath) != sizeof (VENDOR_DEVICE_PATH)
      || (FilePath->Type != HARDWARE_DEVICE_PATH)
      || (FilePath->SubType != HW_VENDOR_DP)) {
    //return EFI_NO_SUCH_MEDIA;
    return EFI_NOT_FOUND;
  }

  VendorDevicePathNode = (VENDOR_DEVICE_PATH*)FilePath;

  if (SctCompareGuid (&VendorDevicePathNode->Guid, &mImageTestLoadFileApplicationPathGuid) == 0) {

    CopySimpleFileToMemory (
      mDriverImageHandle,
      APPLICATION_IMAGE_1_NAME,
      &SourceBuffer,
      &SourceBufferSize
      );
  } else if (SctCompareGuid (&VendorDevicePathNode->Guid, &mImageTestLoadFileBootPathGuid) == 0) {

    CopySimpleFileToMemory (
      mDriverImageHandle,
      BOOT_SERVICES_DRIVER_IMAGE_1_NAME,
      &SourceBuffer,
      &SourceBufferSize
      );
  } else if (SctCompareGuid (&VendorDevicePathNode->Guid, &mImageTestLoadFileRuntimePathGuid) == 0) {

    CopySimpleFileToMemory (
      mDriverImageHandle,
      RUNTIME_SERVICES_DRIVER_IMAGE_1_NAME,
      &SourceBuffer,
      &SourceBufferSize
      );
  }

  if (SourceBufferSize == 0) {
    //Status = EFI_NO_SUCH_MEDIA;
    Status = EFI_NOT_FOUND;
    goto Done;
  }

  if (Buffer == NULL) {
    Status = EFI_BUFFER_TOO_SMALL;
    *BufferSize = SourceBufferSize;
    goto Done;
  } else if (*BufferSize < SourceBufferSize) {
    Status = EFI_BUFFER_TOO_SMALL;
    *BufferSize = SourceBufferSize;
    goto Done;
  }

  *BufferSize = SourceBufferSize;

  gtBS->CopyMem (Buffer, SourceBuffer, SourceBufferSize);

Done:

  if (SourceBuffer != NULL) {
    gtBS->FreePool (SourceBuffer);
  }

  return Status;
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
LoadFileDriverUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  //
  // free resources
  //
  gtBS->UninstallProtocolInterface (
          mLoadFileDriverBinding.DriverBindingHandle,
          &gEfiDriverBindingProtocolGuid,
          &mLoadFileDriverBinding
          );
  return EFI_SUCCESS;
}
