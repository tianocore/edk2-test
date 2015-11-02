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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Misc.c

Abstract:

  Internal functions

--*/

#include "Misc.h"
#include "SctLib.h"

EFI_FILE_HANDLE                         RootFs;
EFI_DEVICE_PATH_PROTOCOL                *mLoadFileDevicePath = NULL;
CHAR16                                  *mFilePath;
EFI_HANDLE                              mImageHandle;

/**
 *  @brief This function create an invalid handle. To avoid memory leak,
 *         it is stronggly recommended to use with ReleaseInvalidHandle.
 *  @see ReleaseInvalidHandle.
 */
VOID
ImageTestCreateInvalidHandle (
  OUT EFI_HANDLE  *InvalidHandle
  )
{
  EFI_HANDLE                  Handle = NULL;
  EFI_STATUS                  Status;

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    *InvalidHandle = NULL;
  } else {
    //
    // "+ 8" is for the alignment on IPF platform.
    //
    // When restore the environment, the valid handle should be
    // (EFI_HANDLE)((UINT8*)InvalidHandle - 8)
    //
    *InvalidHandle = (EFI_HANDLE)((UINT8*)Handle + 8);
  }
}

VOID
ImageTestReleaseInvalidHandle (
  IN EFI_HANDLE    InvalidHandle
  )
{
  EFI_HANDLE              ValidHandle;

  if (InvalidHandle == NULL) {
    return;
  }

  ValidHandle = (EFI_HANDLE)((UINT8*)InvalidHandle - 8);

  gtBS->UninstallProtocolInterface (ValidHandle, &mImageTestNoInterfaceProtocol1Guid, NULL);
}

VOID
ImageTestCreateNewHandle (
  OUT EFI_HANDLE  *NewHandle
  )
{
  EFI_HANDLE                  Handle = NULL;
  EFI_STATUS                  Status;

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    NewHandle = NULL;
  } else {
    *NewHandle = Handle;
  }
}

VOID
ImageTestReleaseNewHandle (
  IN EFI_HANDLE    NewHandle
  )
{
  if (NewHandle == NULL) {
    return;
  }

  gtBS->UninstallProtocolInterface (NewHandle, &mImageTestNoInterfaceProtocol2Guid, NULL);
}

BOOLEAN
ImageTestImageLoadableDevicePath (
  IN OUT EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
/*++
  Two device paths are eligible for loading image:
    1) File Path Media Device Path
    2) Firmware Volume File Path Media Device Path

  Firmware Volume is not belong to EFI1.10 spec, so remove it.
--*/
{
  while (!SctIsDevicePathEnd (DevicePath)) {
    if (DevicePath->Type == MEDIA_DEVICE_PATH &&
        DevicePath->SubType == MEDIA_FILEPATH_DP) {
      return TRUE;
    }
    DevicePath = SctNextDevicePathNode (DevicePath);
  }

  return FALSE;
}

VOID
ImageTestLocateNonFilePath (
  OUT EFI_DEVICE_PATH_PROTOCOL **IrrelevantFilePath
  )
{
  UINTN                       NoHandles;
  EFI_HANDLE                  *HandleBuffer;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
  EFI_STATUS                  Status;
  UINTN                       Index;

  HandleBuffer = NULL;

  if (IrrelevantFilePath == NULL) {
    return;
  }

  *IrrelevantFilePath = NULL;

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gEfiDevicePathProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status)) {
    return;
  }

  for (Index = 0; Index < NoHandles; Index++) {
    gtBS->HandleProtocol (
            HandleBuffer[Index],
            &gEfiDevicePathProtocolGuid,
            (VOID **) &DevicePath
            );
  if (!ImageTestImageLoadableDevicePath (DevicePath)) {
    *IrrelevantFilePath = DevicePath;
    break;
  }
  }

  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }
  return;
}

VOID
ImageTestCreateNonExistentDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **NonExistentDevicePath
  )
{
  ImageTestCreateVendorDevicePath (
    NonExistentDevicePath,
    mImageTestVendorDevicePath1Guid
    );
}

VOID
ImageTestCreateCombinedNonExistentDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **CombinedNonExistentDevicePath
  )

{
  EFI_STATUS                          Status;
  EFI_LOADED_IMAGE_PROTOCOL           *LoadImage;
  EFI_DEVICE_PATH_PROTOCOL            *VendorDevicePath;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;


  ImageTestCreateVendorDevicePath (
    &VendorDevicePath,
    mImageTestVendorDevicePath1Guid
    );


  Status = gtBS->HandleProtocol (
                   mImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **) &LoadImage
                   );

  if (EFI_ERROR(Status)) {
    return;
  }

  gtBS->HandleProtocol (
          LoadImage->DeviceHandle,
          &gEfiDevicePathProtocolGuid,
          (VOID **) &DevicePath
          );

  *CombinedNonExistentDevicePath = SctAppendDevicePath (
                                     DevicePath,
                                     VendorDevicePath
                                     );

  gtBS->FreePool (VendorDevicePath);

  return;
}


VOID
ImageTestCreateVendorDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  )
{
  UINTN                       Length;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL    *DevPointer;
  EFI_STATUS                  Status;

  //
  // init
  //
  *DevicePath = NULL;
  Length = sizeof (VENDOR_DEVICE_PATH) + sizeof (EFI_DEVICE_PATH_PROTOCOL);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Length,
                   (VOID**)DevicePath
                   );
  if (EFI_ERROR(Status)) {
    return;
  }

  DevicePathNode = NULL;
  ImageTestCreateVendorDevicePathNode (&DevicePathNode, Guid);

  DevPointer = *DevicePath;

  gtBS->CopyMem (DevPointer, DevicePathNode, sizeof (VENDOR_DEVICE_PATH));

  //
  // points to next node
  //
  DevPointer = (EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)DevPointer + sizeof (VENDOR_DEVICE_PATH));
  //
  // End Node
  //
  SctSetDevicePathEndNode (DevPointer);

  //
  // release resource
  //
  gtBS->FreePool (DevicePathNode);

  return;
}

VOID
ImageTestCreateVendorDevicePathNode (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  )
{
  UINTN                       Length;
  EFI_DEVICE_PATH_PROTOCOL    *DevPointer;
  EFI_STATUS                  Status;
  VENDOR_DEVICE_PATH          VendorDevicePathNode;

  if (DevicePath == NULL) {
    return;
  }

  //
  // init
  //
  *DevicePath = NULL;
  Length = sizeof (VENDOR_DEVICE_PATH);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Length,
                   (VOID**)DevicePath
                   );
  if (EFI_ERROR(Status)) {
    //
    // record FAIL assertion (generic)
    //
    return;
  }

  DevPointer = *DevicePath;

  //
  // Vendor device path node
  //
  VendorDevicePathNode.Header.Type = HARDWARE_DEVICE_PATH;
  VendorDevicePathNode.Header.SubType = HW_VENDOR_DP;
  VendorDevicePathNode.Header.Length[0] = sizeof (VENDOR_DEVICE_PATH);
  VendorDevicePathNode.Header.Length[1] = 0;
  gtBS->CopyMem (&VendorDevicePathNode.Guid, &Guid, sizeof (EFI_GUID));
  gtBS->CopyMem (DevPointer, &VendorDevicePathNode, sizeof (VENDOR_DEVICE_PATH));

  return;
}

EFI_STATUS
ImageTestRetrieveCurrentMapKey (
  OUT UINTN        *MapKey
  )
{
  UINTN                         MemoryMapSize;
  EFI_MEMORY_DESCRIPTOR         *MemoryMap;
  UINTN                         DescriptorSize;
  UINT32                        DescriptorVersion;
  EFI_STATUS                    Status;
  EFI_MEMORY_DESCRIPTOR         Temp;

  MemoryMapSize = 1;
  Status = gtBS->GetMemoryMap (
                    &MemoryMapSize,
                    &Temp,
                    MapKey,
                    &DescriptorSize,
                    &DescriptorVersion
                    );
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return Status;
  }

  MemoryMapSize *= 2;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   MemoryMapSize,
                   (VOID**)&MemoryMap
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gtBS->GetMemoryMap (
                    &MemoryMapSize,
                    MemoryMap,
                    MapKey,
                    &DescriptorSize,
                    &DescriptorVersion
                    );

  gtBS->FreePool (MemoryMap);

  return Status;
}

/**
 *  @brief This function is used to compose a device path of a file located at disk media.
 *  @see ReleaseInvalidHandle.
 */
EFI_STATUS
ImageTestComposeSimpleFilePath (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib    OPTIONAL,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT EFI_DEVICE_PATH_PROTOCOL            **FilePath
  )
/*++
  The caller has the responsibility to free the FilePath
--*/
{
  EFI_STATUS                          Status;
  EFI_LOADED_IMAGE_PROTOCOL           *LoadImage;
  CHAR16                              *EntireFileName;
  CHAR16                              *FileNamePath;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib;

  Status = gtBS->HandleProtocol (
                   CurrentImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **) &LoadImage
                   );
  if (EFI_ERROR (Status)) {
    if (StandardLib != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
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
                         &FileNamePath
                         );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  EntireFileName = SctPoolPrint (L"%s\\%s\\%s", FileNamePath, DEPENDENCY_DIR_NAME, FileName);

  *FilePath = SctFileDevicePath (LoadImage->DeviceHandle, EntireFileName);

  gtBS->FreePool (EntireFileName);
  gtBS->FreePool (FileNamePath);
  gtBS->FreePool (DevicePath);

  if (*FilePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ImageTestCopySimpleFileToMemory (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib OPTIONAL,
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
  CHAR16                            *EntireFileName;

  //
  // init
  //
  InfoBuffer = NULL;
  *SourceBufferSize = 0;
  *SourceBuffer = NULL;
  EntireFileName = NULL;

  Status = gtBS->HandleProtocol (
                   CurrentImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **) &LoadImage
                   );
  if (EFI_ERROR (Status)) {
    if (StandardLib != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - for LoadedImage",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                   );
    }
    return Status;
  }

  //
  // locate simple file system on the LoadImage->DeviceHandle
  //
  Status = gtBS->HandleProtocol (
                   LoadImage->DeviceHandle,
                   &gEfiSimpleFileSystemProtocolGuid,
                   (VOID **) &Volume
                   );
  if (EFI_ERROR(Status)) {
    if (StandardLib != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.HandleProtocol - for SimpleFileSystem Protocol",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
    return Status;
  }

  EntireFileName = NULL;
  EntireFileName = SctPoolPrint (L"%s\\%s", mFilePath, FileName);

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
    if (StandardLib != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"OpenFile",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
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
    if (StandardLib != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GetFileInfo",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
    goto Done;
  }

  *SourceBufferSize = (UINTN)InfoBuffer->FileSize;

  Status = gtBS->AllocatePool (EfiBootServicesData, *SourceBufferSize, (VOID**)SourceBuffer);
  if (EFI_ERROR(Status)) {
    if (StandardLib != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.AllocatePool",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
    goto Done;
  }

  //
  // roll the file to the start position
  //
  FileHandle->SetPosition (FileHandle, 0);

  Status = FileHandle->Read (FileHandle, SourceBufferSize, *SourceBuffer);
  if (EFI_ERROR(Status)) {
    if (StandardLib != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"ReadFile",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
  }

Done:
  //
  // release resource
  //
  if (EntireFileName != NULL) {
    gtBS->FreePool (EntireFileName);
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


VOID
ImageTestNotifyFunction (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  )
{
  UINTN     *NotifyTimes;

  NotifyTimes = (UINTN*)Context;

  (*NotifyTimes)++;
}

VOID
ImageTestNotifyFunctionForCombinationTest1 (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  )
{
  IMAGE_TEST_NOTIFY_CONTEXT     *NotifyContextArray;
  UINTN                         NoHandles;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         Index;
  EFI_STATUS                    Status;

  NotifyContextArray = (IMAGE_TEST_NOTIFY_CONTEXT*)Context;

  for (Index = 0; Index < 10; Index++) {

    HandleBuffer = NULL;
    Status = gtBS->LocateHandleBuffer (
                     ByRegisterNotify,
                     NULL,
                     NotifyContextArray[Index].Registration,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if ((EFI_SUCCESS == Status) && (NoHandles == 1)) {
      break;
    }
  }

  if (Index < 10) {
    NotifyContextArray[Index].NotifyTimes++;
  }
}

STATIC
EFI_STATUS
ImageTestAliasLocateHandleBuffer (
  IN EFI_GUID  *Guid
  )
{
  EFI_HANDLE        *HandleBuffer;
  UINTN             NoHandles;
  EFI_STATUS        Status;

  NoHandles = 0;
  HandleBuffer = NULL;

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  return Status;
}


EFI_STATUS
ImageTestCheckForCleanEnvironment (
  OUT UINTN                               *Numbers
  )
{
  EFI_STATUS        Status;
  UINTN             Counts;

  //
  // init
  //
  Counts = 0;

  //
  // Probe mImageTestNoInterfaceProtocol1Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol1Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestNoInterfaceProtocol2Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol2Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestNoInterfaceProtocol3Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol3Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestNoInterfaceProtocol4Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol4Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestNoInterfaceProtocol5Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol5Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestNoInterfaceProtocol6Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol6Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestNoInterfaceProtocol7Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol7Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestNoInterfaceProtocol8Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol8Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestNoInterfaceProtocol9Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol9Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestNoInterfaceProtocol10Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestNoInterfaceProtocol10Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  //
  // Probe mImageTestForLoadFileProtocol1Guid
  //
  Status = ImageTestAliasLocateHandleBuffer (&mImageTestForLoadFileProtocol1Guid);
  if (!EFI_ERROR(Status))  {
    Counts++;
  }

  *Numbers = Counts;

  if (Counts != 0) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
 *  Get device path and file path from the image handle.
 *  @param IamgeHandle    The image handle.
 *  @param DevicePath     The device path of the image handle.
 *  @param FilePath       The file path of the image handle.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetImageDevicePath (
  IN     EFI_HANDLE                  ImageHandle,
     OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  IN OUT CHAR16                      **FilePath
  )
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *Image;
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL    *TempDeviceNode;
  CHAR16                      *TempFilePath;

  //
  // Get the image instance from the image handle
  //
  Status = gtBS->HandleProtocol (
                   ImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **) &Image
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the device instance from the device handle
  //
  Status = gtBS->HandleProtocol (
                   Image->DeviceHandle,
                   &gEfiDevicePathProtocolGuid,
                   (VOID **) &TempDevicePath
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  *DevicePath = SctDuplicateDevicePath (TempDevicePath);
  if (*DevicePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Get the file name from the image instance
  //
  TempDevicePath = SctUnpackDevicePath (Image->FilePath);

  TempFilePath = NULL;
  TempDeviceNode = TempDevicePath;
  while (!SctIsDevicePathEnd (TempDeviceNode)) {
    if ((SctDevicePathType (TempDeviceNode) == MEDIA_DEVICE_PATH) &&
        (SctDevicePathSubType (TempDeviceNode) == MEDIA_FILEPATH_DP)) {
      TempFilePath = SctStrDuplicate (((FILEPATH_DEVICE_PATH *)TempDeviceNode)->PathName);
      break;
    }
    TempDeviceNode = SctNextDevicePathNode (TempDeviceNode);
  }

  gtBS->FreePool (TempDevicePath);

  if (TempFilePath == NULL) {
    gtBS->FreePool (*DevicePath);
    return EFI_NOT_FOUND;
  }

  //
  // If the file path is only a root directory "\\", remove it
  //
  if ((TempFilePath[0] == L'\\') && (TempFilePath[1] == L'\0')) {
    TempFilePath[0] = L'\0';
  }

  *FilePath = TempFilePath;

  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;
}

/**
 *  @brief initialize those global datas for Image services test.
 *  @return EFI_SUCCESS
 */
EFI_STATUS
InitializeGlobalData (
  VOID
  )
{
  EFI_LOADED_IMAGE_PROTOCOL           *LoadedImage;
  EFI_STATUS                          Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL     *Vol;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib;

  EFI_GUID G1 = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
  EFI_GUID G2 = EFI_LOADED_IMAGE_PROTOCOL_GUID;

  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  CHAR16                              *FilePath;

  Status = gtBS -> HandleProtocol (mImageHandle, &G2, (VOID **) &LoadedImage);
  Status = gtBS -> HandleProtocol (LoadedImage->DeviceHandle, &G1, (VOID **) &Vol);

  Status = Vol -> OpenVolume (Vol, &RootFs);

  //
  // compose device path for the LOAD_FILE implementation driver
  //
  ImageTestCreateVendorDevicePath (
    &mLoadFileDevicePath,
    mImageTestLoadFileDriverPathGuid
    );

  mFilePath = NULL;
  DevicePath = NULL;
  FilePath = NULL;

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

  mFilePath = SctPoolPrint (L"%s\\%s", FilePath, DEPENDENCY_DIR_NAME);

  SctFreePool (FilePath);
  SctFreePool (DevicePath);

  return EFI_SUCCESS;
}

VOID
ReleaseGlobalData (
  VOID
  )
{
  if (mLoadFileDevicePath != NULL) {
    SctFreePool (mLoadFileDevicePath);
  }

  if (mFilePath != NULL) {
    SctFreePool (mFilePath);
  }
}

//
// support functions for LOAD_FILE
//

EFI_STATUS
StartLoadFileTestDriver (
  OUT EFI_HANDLE      *DriverImageHandle
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  CHAR16                      *FileName;
  EFI_HANDLE                  ImageHandle;
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_HANDLE                  HandleList[2];

  //
  // init
  //
  ImageHandle = NULL;
  Handle = NULL;
  FilePath = NULL;
  *DriverImageHandle = NULL;

  FileName = IMAGE_TEST_LOAD_FILE_DRIVER_NAME;
  Status = ImageTestComposeSimpleFilePath (
             NULL, mImageHandle,
             FileName,
             &FilePath
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Load the driver
  //
  Status = gtBS->LoadImage (
                   FALSE,
                   mImageHandle,
                   FilePath,
                   NULL,
                   0,
                   &ImageHandle
                   );
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = gtBS->StartImage (ImageHandle, NULL, NULL);
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  //
  // Create a handle that the driver support
  //
  Status = gtBS->InstallMultipleProtocolInterfaces (
                   &Handle,
                   &mImageTestForLoadFileProtocol1Guid,
                   NULL,
                   NULL
                   );
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  //
  // Start the driver
  //
  HandleList[0] = ImageHandle;
  HandleList[1] = 0;
  Status = gtBS->ConnectController (
                   Handle,
                   HandleList,
                   mLoadFileDevicePath,
                   FALSE
                   );
  if (!EFI_ERROR (Status)) {
    *DriverImageHandle = ImageHandle;
    return EFI_SUCCESS;
  }

ErrorExit:

  if (Handle != NULL) {
    gtBS->UninstallMultipleProtocolInterfaces (
            Handle,
            &mImageTestForLoadFileProtocol1Guid,
            NULL,
            NULL
            );
  }

  if (ImageHandle != NULL) {
    gtBS->UnloadImage (ImageHandle);
  }

  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  return Status;
}

VOID
StopLoadFileTestDriver (
  IN EFI_HANDLE        DriverImageHandle
  )
{
  EFI_STATUS            Status;
  EFI_HANDLE            *HandleBuffer;
  UINTN                 NoHandles;
  UINTN                 Index;

  //
  // init
  //
  HandleBuffer = NULL;

  //
  // locate the handle
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mImageTestForLoadFileProtocol1Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    return;
  }

  for (Index = 0; Index < NoHandles; Index++) {
    //
    // disconnect the handle from the LOAD_FILE driver
    //
    gtBS->DisconnectController (HandleBuffer[Index], NULL, NULL);

    gtBS->UninstallProtocolInterface (
            HandleBuffer[Index],
            &mImageTestForLoadFileProtocol1Guid,
            NULL
            );
  }

  //
  // unload image
  //
  gtBS->UnloadImage (DriverImageHandle);

  return;
}

EFI_STATUS
ImageTestComposeLoadFilePath (
  OUT EFI_DEVICE_PATH_PROTOCOL      **FilePath,
  IN  LOAD_FILE_TYPE                Type
  )
{
  EFI_DEVICE_PATH_PROTOCOL      *TailPath;

  TailPath = NULL;

  switch (Type) {
    case TypeApplication:
      ImageTestCreateVendorDevicePath (
        &TailPath,
        mImageTestLoadFileApplicationPathGuid
        );
      break;

    case TypeBootDriver:
      ImageTestCreateVendorDevicePath (
        &TailPath,
        mImageTestLoadFileBootPathGuid
        );
      break;

    case TypeRuntimeDriver:
      ImageTestCreateVendorDevicePath (
        &TailPath,
        mImageTestLoadFileRuntimePathGuid
        );
      break;
  }

  if (TailPath == NULL) {
    return EFI_NOT_FOUND;
  }

  *FilePath = SctAppendDevicePathNode (mLoadFileDevicePath, TailPath);

  SctFreePool (TailPath);

  if (*FilePath == NULL) {
    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}
