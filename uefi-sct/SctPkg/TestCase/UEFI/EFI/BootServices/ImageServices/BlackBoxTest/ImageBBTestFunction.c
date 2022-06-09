/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ImageBBTestFunction.c

Abstract:

  for Image Boot Services' Interface Function Test

--*/

#include "SctLib.h"
#include "Misc.h"

extern EFI_GUID gBlackBoxEfiHIIPackageListProtocolGuid;

//
// Useful Macros
//
#define     DEL_PTRS(ptr)   if(ptr) {gtBS->FreePool(ptr); ptr = NULL;} // Prevent to generate the unrefernced ptrs

//
// Global Variables
//
EFI_GUID                    NameGuid1 = APPLICATION_IMAGE_2_NAME_GUID;
EFI_GUID                    NameGuid2 = BOOT_SERVICES_DRIVER_IMAGE_2_NAME_GUID;
EFI_GUID                    NameGuid3 = RUNTIME_SERVICES_DRIVER_IMAGE_2_NAME_GUID;


/**
 *  @brief internal function to Unload the BS or RT driver, give the driver a
 *  UnLoad function so the driver can be unloaded from the memory correctly.
 *  @param ImageHandle the HANDLE of Image to be unloaded.uired
 *  @return EFI_SUCCESS
 */
EFI_STATUS
EFIAPI
ImageTestDriversUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->LoadImage() Interface Function
           Test. 7 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestLoadImageInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.1.2.1  Call LoadImage to load image from disk device that support Simple File System Protocol.
  //
  BBTestLoadImageInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.1.2.2  Call LoadImage to load image from firmware volume
  //
  // Firmware Volume is not belong to EFI1.10 Spec, so remove it.
  //

  //
  // Checkpoint 3:
  // 4.1.2.3  Call LoadImage to load image from memory
  //
  BBTestLoadImageInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.1.2.4  If calling LoadImage with non-NULL SourceBuffer,
  // parameter FilePath should be ignored.
  //
  BBTestLoadImageInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.1.2.5  Call LoadImage to try to load some images
  // whose format were corrupt or not understood
  //
  BBTestLoadImageInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.1.2.6  Call LoadImage to try to load a very large image
  //
  // Remove this checkpoint since NOTE 1 & NOTE 2
  //

  //
  // NOTE 1: not run this on IPF platform, because the image size
  // can not be large enough to exceed the 4G memory.
  //

  //
  // NOTE 2: On IA32 platform, the accessable memory size may also
  // larger than 4G after EM64T enabled.
  //

  // BBTestLoadImageInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.1.2.7  Call LoadImage to load image via LOAD_FILE protocol
  //
  BBTestLoadImageInterfaceTestCheckPoint7 (StandardLib);

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
  //
  //Checkpoint 8:
  //4.1.2.8  Call LoadImage to load image for HII protocol
  //
  BBTestLoadImageInterfaceTestCheckPoint8(StandardLib);

  BBTestLoadImageInterfaceTestCheckPoint9(StandardLib);
#endif  
  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->StartImage() Interface Function
 *         Test. 5 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestStartImageInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.2.2.1  Call StartImage to start an EFI application
  //
  BBTestStartImageInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.2.2.2  Call StartImage to start a Boot Services Driver
  // whose entry point return success
  //
  BBTestStartImageInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.2.2.3  Call StartImage to start a Boot Services Driver
  // whose entry point return eror
  //
  BBTestStartImageInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.2.2.4  Call StartImage to start a Runtime Services Driver
  // whose entry point return success
  //
  BBTestStartImageInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.2.2.5  Call StartImage to start a Runtime Services Driver
  // whose entry point return eror
  //
  BBTestStartImageInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.2.2.5  Calling StartImage twice with the same image handle
  // should not succeed in the second times
  //
  BBTestStartImageInterfaceTestCheckPoint6 (StandardLib);

  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->UnloadImage() Interface Function
 *         Test.10 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.3.2.1  Unload an EFI application before image is started
  //
  BBTestUnloadImageInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.3.2.2  Unload a Boot Services Driver before image is started
  //
  BBTestUnloadImageInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.3.2.3  Unload a Runtime Services Driver before image is started
  //
  BBTestUnloadImageInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.3.2.4  Unload an EFI application after image is started
  //
  BBTestUnloadImageInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.3.2.5  After image start, Unload a Boot Services Driver
  // which has Unload function and the Unload function returns success
  //
  BBTestUnloadImageInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.3.2.6  After image start, Unload a Boot Services Driver
  // which has Unload function and the Unload function returns error
  //
  BBTestUnloadImageInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.3.2.7  After image start, Unload a Boot Services Driver
  // which does not own a Unload function
  //
  BBTestUnloadImageInterfaceTestCheckPoint7 (StandardLib);

  //
  // Checkpoint 8:
  // 4.3.2.8  After image start, Unload a Runtime Services Driver
  // which has Unload function and the Unload function returns success
  //
  BBTestUnloadImageInterfaceTestCheckPoint8 (StandardLib);

  //
  // Checkpoint 9:
  // 4.3.2.9  After image start, Unload a Runtime Services Driver
  // which has Unload function and the Unload function returns error
  //
  BBTestUnloadImageInterfaceTestCheckPoint9 (StandardLib);

  //
  // Checkpoint 10:
  // 4.3.2.10 After image start, Unload a Runtime Services Driver
  // which does not own a Unload function
  //
  BBTestUnloadImageInterfaceTestCheckPoint10 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->Exit() Interface Function Test.
 *         10 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.4
//
EFI_STATUS
EFIAPI
BBTestExitInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.4.2.1  Exit an EFI application before image is started
  //
  BBTestExitInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.4.2.2  Exit a Boot Services Driver before image is started
  //
  BBTestExitInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.4.2.3  Exit a Runtime Services Driver before image is started
  //
  BBTestExitInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.4.2.4  Exit a already started image by the test case
  //
  BBTestExitInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.4.2.5  Exit an EFI application within its entry point
  // with success exit code
  //
  BBTestExitInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.4.2.6  Exit an EFI application within its entry point
  // with error exit code
  //
  BBTestExitInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.4.2.7  Exit a Boot Services Driver within its entry point
  // with success exit code
  //
  BBTestExitInterfaceTestCheckPoint7 (StandardLib);

  //
  // Checkpoint 8:
  // 4.4.2.8  Exit a Boot Services Driver within its entry point
  // with error exit code
  //
  BBTestExitInterfaceTestCheckPoint8 (StandardLib);

  //
  // Checkpoint 9:
  // 4.4.2.9  Exit a Runtime Services Driver within its entry point
  // with success exit code
  //
  BBTestExitInterfaceTestCheckPoint9 (StandardLib);

  //
  // Checkpoint 10:
  // 4.4.2.10 Exit a Runtime Services Driver within its entry point
  // with error exit code
  //
  BBTestExitInterfaceTestCheckPoint10 (StandardLib);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestLoadImageInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath[3];
  BOOLEAN                     BootPolicy[2];
  UINTN                       BootIndex;
  UINTN                       FileIndex;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  CHAR16                      *FileName;
  EFI_STATUS                  Status1, Status2, Status3;
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  gtBS->SetMem (FilePath, 3 * sizeof (EFI_DEVICE_PATH_PROTOCOL*), 0);
  BootPolicy[0] = FALSE;
  BootPolicy[1] = TRUE;

  FileName = APPLICATION_IMAGE_1_NAME;
  Status1 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              FileName,
              &FilePath[0]
              );

  FileName = BOOT_SERVICES_DRIVER_IMAGE_1_NAME;
  Status2 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              FileName,
              &FilePath[1]
              );

  FileName = RUNTIME_SERVICES_DRIVER_IMAGE_1_NAME;
  Status3 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              FileName,
              &FilePath[2]
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    for (Index = 0; Index < 3; Index++) {
      gtBS->FreePool (FilePath[Index]);
    }
    return EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    for (BootIndex = 0; BootIndex < 2; BootIndex++) {

      for (FileIndex = 0; FileIndex < 3; FileIndex++) {

        //
        // Init
        //
        ImageHandle = NULL;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);

        Status = gtBS->LoadImage (
                         BootPolicy[BootIndex],
                         mImageHandle,
                         FilePath[FileIndex],
                         NULL,
                         0,
                         &ImageHandle
                         );
        gtBS->RestoreTPL (OldTpl);

        //
        // Step 1: check return status
        //
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid001,
                       L"BS.LoadImage - InterfaceTestCheckpoint1",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
          continue;
        }

        //
        // Step 2: check whether returned ImageHandle has Loaded Image Protocol
        // installed.
        //
        Status = gtBS->HandleProtocol (
                         ImageHandle,
                         &gEfiLoadedImageProtocolGuid,
                         (VOID **) &LoadedImage
                         );
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid002,
                       L"BS.LoadImage - InterfaceTestCheckpoint1",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
          gtBS->UnloadImage (ImageHandle);
          continue;
        }

        //
        // Step 3: check the ImageCodeType and ImageDataType.
        //
        switch (FileIndex) {
          case 0: // application image
            if ((LoadedImage->ImageCodeType == EfiLoaderCode)
                && (LoadedImage->ImageDataType == EfiLoaderData)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            break;

          case 1: // boot services driver image
            if ((LoadedImage->ImageCodeType == EfiBootServicesCode)
                && (LoadedImage->ImageDataType == EfiBootServicesData)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            break;

          case 2: // runtime services driver image
            if ((LoadedImage->ImageCodeType == EfiRuntimeServicesCode)
                && (LoadedImage->ImageDataType == EfiRuntimeServicesData)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            break;

          default:
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid003,
                       L"BS.LoadImage - InterfaceTestCheckpoint1",
                       L"%a:%d:CodeType - %d, DataType - %d, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       LoadedImage->ImageCodeType,
                       LoadedImage->ImageDataType,
                       TplArray[Index]
                       );

        //
        // restore environment
        //
        if (ImageHandle != NULL) {
          gtBS->UnloadImage (ImageHandle);
        }
      }
    }
  }

  //
  // free resources
  //
  for (Index = 0; Index < 3; Index++) {
    gtBS->FreePool (FilePath[Index]);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}


EFI_STATUS
EFIAPI
BBTestLoadImageInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  BOOLEAN                     BootPolicy[2];
  UINTN                       BootIndex;
  UINTN                       FileIndex;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  CHAR16                      *FileName;
  EFI_STATUS                  Status1, Status2, Status3;
  UINT8                       *SourceBufferArray[3];
  UINTN                       SourceBufferSizeArray[3];
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  gtBS->SetMem (SourceBufferArray, 3 * sizeof (UINT8*), 0);
  gtBS->SetMem (SourceBufferSizeArray, 3 * sizeof (UINT8), 0);

  BootPolicy[0] = FALSE;
  BootPolicy[1] = TRUE;

  FileName = APPLICATION_IMAGE_3_NAME;
  Status1 = ImageTestCopySimpleFileToMemory (
              StandardLib,
              mImageHandle,
              FileName,
              &SourceBufferArray[0],
              &SourceBufferSizeArray[0]
              );
  FileName = BOOT_SERVICES_DRIVER_IMAGE_3_NAME;
  Status2 = ImageTestCopySimpleFileToMemory (
              StandardLib,
              mImageHandle,
              FileName,
              &SourceBufferArray[1],
              &SourceBufferSizeArray[1]
              );
  FileName = RUNTIME_SERVICES_DRIVER_IMAGE_3_NAME;
  Status3 = ImageTestCopySimpleFileToMemory (
              StandardLib,
              mImageHandle,
              FileName,
              &SourceBufferArray[2],
              &SourceBufferSizeArray[2]
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestCopySimpleFileToMemory - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    for (Index = 0; Index < 3; Index++) {
      gtBS->FreePool (SourceBufferArray[Index]);
    }
    return EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    for (BootIndex = 0; BootIndex < 2; BootIndex++) {

      for (FileIndex = 0; FileIndex < 3; FileIndex++) {

        //
        // Init
        //
        ImageHandle = NULL;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);

        Status = gtBS->LoadImage (
                         BootPolicy[BootIndex],
                         mImageHandle,
                         NULL,
                         SourceBufferArray[FileIndex],
                         SourceBufferSizeArray[FileIndex],
                         &ImageHandle
                         );
        gtBS->RestoreTPL (OldTpl);

        //
        // Step 1: check return status
        //
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid007,
                       L"BS.LoadImage - InterfaceTestCheckpoint3",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
          continue;
        }

        //
        // Step 2: check whether returned ImageHandle has Loaded Image Protocol
        // installed.
        //
        Status = gtBS->HandleProtocol (
                         ImageHandle,
                         &gEfiLoadedImageProtocolGuid,
                         (VOID **) &LoadedImage
                         );
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid008,
                       L"BS.LoadImage - InterfaceTestCheckpoint3",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
          gtBS->UnloadImage (ImageHandle);
          continue;
        }

        //
        // Step 3: check the ImageCodeType and ImageDataType.
        //
        switch (FileIndex) {
          case 0: // application image
            if ((LoadedImage->ImageCodeType == EfiLoaderCode)
                && (LoadedImage->ImageDataType == EfiLoaderData)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            break;

          case 1: // boot services driver image
            if ((LoadedImage->ImageCodeType == EfiBootServicesCode)
                && (LoadedImage->ImageDataType == EfiBootServicesData)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            break;

          case 2: // runtime services driver image
            if ((LoadedImage->ImageCodeType == EfiRuntimeServicesCode)
                && (LoadedImage->ImageDataType == EfiRuntimeServicesData)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            break;

          default:
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid009,
                       L"BS.LoadImage - InterfaceTestCheckpoint3",
                       L"%a:%d:CodeType - %d, DataType - %d, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       LoadedImage->ImageCodeType,
                       LoadedImage->ImageDataType,
                       TplArray[Index]
                       );

        //
        // restore environment
        //
        if (ImageHandle != NULL) {
          gtBS->UnloadImage (ImageHandle);
        }
      }
    }
  }

  //
  // free resources
  //
  for (Index = 0; Index < 3; Index++) {
    gtBS->FreePool (SourceBufferArray[Index]);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestLoadImageInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  BOOLEAN                     BootPolicy[2];
  UINTN                       BootIndex;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  EFI_STATUS                  Status1, Status2;
  UINT8                       *SourceBuffer;
  UINTN                       SourceBufferSize;
  EFI_HANDLE                  ImageHandle;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  SourceBuffer = NULL;
  FilePath = NULL;

  BootPolicy[0] = FALSE;
  BootPolicy[1] = TRUE;

  Status1 = ImageTestCopySimpleFileToMemory (
              StandardLib,
              mImageHandle,
              APPLICATION_IMAGE_3_NAME,
              &SourceBuffer,
              &SourceBufferSize
              );

  Status2 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              BOOT_SERVICES_DRIVER_IMAGE_1_NAME,
              &FilePath
              );

  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestCopySimpleFileToMemory & ImageTestComposeSimpleFilePath",
                   L"%a:%d:Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    gtBS->FreePool (SourceBuffer);
    gtBS->FreePool (FilePath);
    return EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    for (BootIndex = 0; BootIndex < 2; BootIndex++) {

      //
      // Init
      //
      ImageHandle = NULL;

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);

      Status = gtBS->LoadImage (
                       BootPolicy[BootIndex],
                       mImageHandle,
                       FilePath,
                       SourceBuffer,
                       SourceBufferSize,
                       &ImageHandle
                       );
      gtBS->RestoreTPL (OldTpl);

      //
      // Step 1: check return status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gImageBBTestFunctionAssertionGuid010,
                     L"BS.LoadImage - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
        continue;
      }

      //
      // Step 2: check whether returned ImageHandle has Loaded Image Protocol
      // installed.
      //
      Status = gtBS->HandleProtocol (
                       ImageHandle,
                       &gEfiLoadedImageProtocolGuid,
                       (VOID **) &LoadedImage
                       );
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gImageBBTestFunctionAssertionGuid011,
                     L"BS.LoadImage - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
        gtBS->UnloadImage (ImageHandle);
        continue;
      }

      //
      // Step 3: check the ImageCodeType and ImageDataType.
      //
      if ((LoadedImage->ImageCodeType == EfiLoaderCode)
           && (LoadedImage->ImageDataType == EfiLoaderData)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gImageBBTestFunctionAssertionGuid012,
                     L"BS.LoadImage - InterfaceTestCheckpoint4",
                     L"%a:%d:CodeType - %d, DataType - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     LoadedImage->ImageCodeType,
                     LoadedImage->ImageDataType,
                     TplArray[Index]
                     );

      //
      // restore environment
      //
      if (ImageHandle != NULL) {
        gtBS->UnloadImage (ImageHandle);
      }
    }

  }

  //
  // free resources
  //
  gtBS->FreePool (SourceBuffer);

  gtBS->FreePool (FilePath);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestLoadImageInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath[7];
  UINTN                       FileIndex;
  EFI_STATUS                  Status1, Status2, Status3, Status4, Status5, Status6, Status7;
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  gtBS->SetMem (FilePath, 7 * sizeof (EFI_DEVICE_PATH_PROTOCOL*), 0);

  Status1 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              INVALID_IMAGE_1_NAME,
              &FilePath[0]
              );

  Status2 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              INVALID_IMAGE_2_NAME,
              &FilePath[1]
              );

  Status3 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              INVALID_IMAGE_3_NAME,
              &FilePath[2]
              );

  Status4 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              INVALID_IMAGE_4_NAME,
              &FilePath[3]
              );

  Status5 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              INVALID_IMAGE_5_NAME,
              &FilePath[4]
              );

  Status6 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              INVALID_IMAGE_6_NAME,
              &FilePath[5]
              );

  Status7 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              INVALID_IMAGE_7_NAME,
              &FilePath[6]
              );

  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)
      || EFI_ERROR(Status4) || EFI_ERROR(Status5) || EFI_ERROR(Status6)
      || EFI_ERROR(Status7)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Statuses - %r,%r,%r,%r,%r,%r,%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3,
                   Status4,
                   Status5,
                   Status6,
                   Status7
                   );
    for (Index = 0; Index < 7; Index++) {
      gtBS->FreePool (FilePath[Index]);
    }
    return EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    for (FileIndex = 0; FileIndex < 7; FileIndex++) {

      //
      // Init
      //
      ImageHandle = NULL;

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);

      Status = gtBS->LoadImage (
                       FALSE,
                       mImageHandle,
                       FilePath[FileIndex],
                       NULL,
                       0,
                       &ImageHandle
                       );
      gtBS->RestoreTPL (OldTpl);

      //
      // Step 1: check return status
      //
      if (EFI_SUCCESS != Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gImageBBTestFunctionAssertionGuid013,
                     L"BS.LoadImage - InterfaceTestCheckpoint5",
                     L"%a:%d:FileIndex - %d, Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIndex,
                     Status,
                     TplArray[Index]
                     );
      //
      // restore environment
      //
      if (ImageHandle != NULL) {
        gtBS->UnloadImage (ImageHandle);
      }
    }
  }

  //
  // free resources
  //
  for (Index = 0; Index < 7; Index++) {
    gtBS->FreePool (FilePath[Index]);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestLoadImageInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;

  //
  // NOTE: not run this on IPF platform, because the image size
  // can not be large enough to exceed the 4G memory.
  //
  if (sizeof (UINTN) == sizeof (UINT64)) {
    return EFI_SUCCESS;
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             VERY_LARGE_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_OUT_OF_RESOURCES == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid014,
                   L"BS.LoadImage - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }
  }

  //
  // free resources
  //
  gtBS->FreePool (FilePath);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestLoadImageInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath[3];
  BOOLEAN                     BootPolicy[2];
  UINTN                       BootIndex;
  UINTN                       FileIndex;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  EFI_STATUS                  Status1, Status2, Status3;
  EFI_HANDLE                  ImageHandle;
  EFI_HANDLE                  DriverImageHandle;
  EFI_LOAD_FILE_PROTOCOL      *LoadFile;

  UINTN                       Numbers;

  //
  // Skip this checkpoint if LOAD_FILE protocol already exists
  //
  Status = gtBS->LocateProtocol (
                   &gEfiLoadFileProtocolGuid,
                   NULL,
                   (VOID **) &LoadFile
                   );
  if (!EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  gtBS->SetMem (FilePath, 3 * sizeof (EFI_DEVICE_PATH_PROTOCOL*), 0);
  BootPolicy[0] = FALSE;
  BootPolicy[1] = TRUE;
  DriverImageHandle = NULL;

  //
  // Load & Connect  a test driver that implement a LOAD_FILE protocol
  //
  Status = StartLoadFileTestDriver (&DriverImageHandle);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"StartLoadFileTestDriver - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status1 = ImageTestComposeLoadFilePath (&FilePath[0], TypeApplication);

  Status2 = ImageTestComposeLoadFilePath (&FilePath[1], TypeBootDriver);

  Status3 = ImageTestComposeLoadFilePath (&FilePath[2], TypeRuntimeDriver);
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeLoadFilePath - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    for (Index = 0; Index < 3; Index++) {
      gtBS->FreePool (FilePath[Index]);
    }

    StopLoadFileTestDriver (DriverImageHandle);
    return EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    for (BootIndex = 0; BootIndex < 2; BootIndex++) {

      for (FileIndex = 0; FileIndex < 3; FileIndex++) {

        //
        // Init
        //
        ImageHandle = NULL;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);

        Status = gtBS->LoadImage (
                         BootPolicy[BootIndex],
                         mImageHandle,
                         FilePath[FileIndex],
                         NULL,
                         0,
                         &ImageHandle
                         );
        gtBS->RestoreTPL (OldTpl);

        //
        // Step 1: check return status
        //
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid015,
                       L"BS.LoadImage - InterfaceTestCheckpoint7",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
          continue;
        }

        //
        // Step 2: check whether returned ImageHandle has Loaded Image Protocol
        // installed.
        //
        Status = gtBS->HandleProtocol (
                         ImageHandle,
                         &gEfiLoadedImageProtocolGuid,
                         (VOID **) &LoadedImage
                         );
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid016,
                       L"BS.LoadImage - InterfaceTestCheckpoint7",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
          gtBS->UnloadImage (ImageHandle);
          continue;
        }

        //
        // Step 3: check the ImageCodeType and ImageDataType.
        //
        switch (FileIndex) {
          case 0: // application image
            if ((LoadedImage->ImageCodeType == EfiLoaderCode)
                && (LoadedImage->ImageDataType == EfiLoaderData)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            break;

          case 1: // boot services driver image
            if ((LoadedImage->ImageCodeType == EfiBootServicesCode)
                && (LoadedImage->ImageDataType == EfiBootServicesData)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            break;

          case 2: // runtime services driver image
            if ((LoadedImage->ImageCodeType == EfiRuntimeServicesCode)
                && (LoadedImage->ImageDataType == EfiRuntimeServicesData)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            break;

          default:
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid017,
                       L"BS.LoadImage - InterfaceTestCheckpoint7",
                       L"%a:%d:CodeType - %d, DataType - %d, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       LoadedImage->ImageCodeType,
                       LoadedImage->ImageDataType,
                       TplArray[Index]
                     );

        //
        // restore environment
        //
        if (ImageHandle != NULL) {
          gtBS->UnloadImage (ImageHandle);
        }
      }
    }
  }

  //
  // free resources
  //
  StopLoadFileTestDriver (DriverImageHandle);

  for (Index = 0; Index < 3; Index++) {
    gtBS->FreePool (FilePath[Index]);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)


EFI_STATUS
EFIAPI
BBTestLoadImageInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{

  EFI_STATUS                        Status;
  EFI_TEST_ASSERTION                AssertionType;
  EFI_DEVICE_PATH_PROTOCOL          *FilePath;
  EFI_HANDLE                        ImageHandle;
  EFI_HII_PACKAGE_LIST_PROTOCOL     *HiiPackageList;
  BOOLEAN                           BootPolicy[2];
  UINTN                             Numbers;
  UINTN                             Index;
  UINTN                             PolicyIndex;
  EFI_TPL                           OldTpl;


  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }
  
  //
  // Constant Prepare
  //
  BootPolicy[0] = TRUE;
  BootPolicy[1] = FALSE;
  
  //
  //  Init - Load a valid HII image
  //
  FilePath = NULL;
  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             VALID_HII_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto    Done;
  }

  for(Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {
    for(PolicyIndex = 0; PolicyIndex < 2; PolicyIndex++) {
      ImageHandle = NULL;    
      OldTpl = gtBS->RaiseTPL(TplArray[Index]);
      Status = gtBS->LoadImage (
                       BootPolicy[PolicyIndex],
                       mImageHandle,
                       FilePath,
                       NULL,
                       0,
                       &ImageHandle
                       );
      gtBS->RestoreTPL(OldTpl);

      //
      // Step 1: Check the return status of the LoadImage
      //      
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gImageBBTestFunctionAssertionGuid145,
                     L"BS.LoadImage - InterfaceTestCheckpoint8",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_ERROR(Status)) {
        continue;
      }
      
      //
      // Step 2: Check to see if the EFI_HII_PACKAGE_LIST_PROTOCOL is installed on the ImageHandle
      //
      Status = gtBS->HandleProtocol(
                   ImageHandle, 
                   &gBlackBoxEfiHIIPackageListProtocolGuid,
                   (VOID **)&HiiPackageList
                   );
      if(EFI_ERROR(Status)) {
         AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
         AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
              
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gImageBBTestFunctionAssertionGuid146,
                     L"BS.LoadImage - InterfaceTestCheckpoint8",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      gtBS->UnloadImage(ImageHandle);               
    }
  } 

Done:
   
  DEL_PTRS(FilePath);

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }
        
  return   Status;
                  
}


EFI_STATUS
EFIAPI
BBTestLoadImageInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  BOOLEAN                     BootPolicy[2];
  UINTN                       BootIndex;
  UINTN                       FileIndex;
  EFI_HII_PACKAGE_LIST_PROTOCOL       HiiPackageList;
  CHAR16                      *FileName;
  EFI_STATUS                  Status1, Status2, Status3;
  UINT8                       *SourceBufferArray[3];
  UINTN                       SourceBufferSizeArray[3];
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  gtBS->SetMem (SourceBufferArray, 3 * sizeof (UINT8*), 0);
  gtBS->SetMem (SourceBufferSizeArray, 3 * sizeof (UINT8), 0);

  BootPolicy[0] = FALSE;
  BootPolicy[1] = TRUE;

  FileName = APPLICATION_IMAGE_3_NAME;
  Status1 = ImageTestCopySimpleFileToMemory (
              StandardLib,
              mImageHandle,
              FileName,
              &SourceBufferArray[0],
              &SourceBufferSizeArray[0]
              );
  FileName = BOOT_SERVICES_DRIVER_IMAGE_3_NAME;
  Status2 = ImageTestCopySimpleFileToMemory (
              StandardLib,
              mImageHandle,
              FileName,
              &SourceBufferArray[1],
              &SourceBufferSizeArray[1]
              );
  FileName = RUNTIME_SERVICES_DRIVER_IMAGE_3_NAME;
  Status3 = ImageTestCopySimpleFileToMemory (
              StandardLib,
              mImageHandle,
              FileName,
              &SourceBufferArray[2],
              &SourceBufferSizeArray[2]
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestCopySimpleFileToMemory - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    for (Index = 0; Index < 3; Index++) {
      gtBS->FreePool (SourceBufferArray[Index]);
    }
    return EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    for (BootIndex = 0; BootIndex < 2; BootIndex++) {

      for (FileIndex = 0; FileIndex < 3; FileIndex++) {

        //
        // Init
        //
        ImageHandle = NULL;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);

        Status = gtBS->LoadImage (
                         BootPolicy[BootIndex],
                         mImageHandle,
                         NULL,
                         SourceBufferArray[FileIndex],
                         SourceBufferSizeArray[FileIndex],
                         &ImageHandle
                         );
        gtBS->RestoreTPL (OldTpl);

        //
        // Step 1: check return status
        //
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid147,
                       L"BS.LoadImage - InterfaceTestCheckpoint9",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
          continue;
        }

       //
       // Step 2: check whether returned ImageHandle has Loaded EFI_HII_PACKAGE_LIST_PROTOCOL
       // installed.
       //
        Status = gtBS->HandleProtocol (
                         ImageHandle,
                         &gBlackBoxEfiHIIPackageListProtocolGuid,
                         (VOID **) &HiiPackageList
                         );
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid148,
                       L"BS.LoadImage - InterfaceTestCheckpoint9",
                       L"%a:%d:Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
          gtBS->UnloadImage (ImageHandle);
          continue ;
        }
		
        //
        // restore environment
        //
        if (ImageHandle != NULL) {
          gtBS->UnloadImage (ImageHandle);
        }
      }
    }
  }

  //
  // free resources
  //
  for (Index = 0; Index < 3; Index++) {
    gtBS->FreePool (SourceBufferArray[Index]);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

#endif

EFI_STATUS
EFIAPI
BBTestStartImageInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  VOID                        *Registration;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;
  EFI_EVENT                   Event;
  UINTN                       NotifyTimes;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             APPLICATION_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The application image will open
  // protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    Event = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;
    NotifyTimes = 0;

    //
    // load the boot services driver image
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // Create an event
    //
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     ImageTestNotifyFunction,
                     &NotifyTimes,
                     &Event
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // register the event for protocol1 installation.
    // the application image will install protocol1 in its entry point function.
    //
    Status = gtBS->RegisterProtocolNotify (
                     &mImageTestNoInterfaceProtocol1Guid,
                     Event,
                     &Registration
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.RegisterProtocolNotify - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // start the image
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check the return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid018,
                   L"BS.StartImage - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // stall some time to wait for the notification
    //
    gtBS->Stall (STALL_1_SECOND);

    //
    // Step 2: check whether the protocol1's notify function is invoked once
    //
    if (1 == NotifyTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid019,
                   L"BS.StartImage - InterfaceTestCheckpoint1",
                   L"%a:%d:NotifyTimes - %d, Expected is 1, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   NotifyTimes,
                   TplArray[Index]
                   );

    //
    // Step 3: check the protocol2 is not opened.
    //
    Status = gtBS->OpenProtocolInformation (
                        Handle,
                        &mImageTestNoInterfaceProtocol2Guid,
                        &EntryBuffer,
                        &EntryCount
                        );
    if ((EFI_NOT_FOUND == Status)
        || ((EFI_SUCCESS == Status) && (0 == EntryCount))) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid020,
                   L"BS.StartImage - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

NextLoop:
    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (Event != NULL) {
      gtBS->CloseEvent (Event);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestStartImageInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  VOID                        *Registration;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;
  EFI_EVENT                   Event;
  UINTN                       NotifyTimes;
  UINTN                       NoHandles;
  EFI_HANDLE                  *HandleBuffer;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             BOOT_SERVICES_DRIVER_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The boot services driver image
  // will open protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    Event = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;
    NotifyTimes = 0;
    NoHandles = 0;
    HandleBuffer = NULL;

    //
    // load the boot services driver image 1
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // Create an event
    //
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     ImageTestNotifyFunction,
                     &NotifyTimes,
                     &Event
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // register the event for protocol1 installation.
    // the application image will install protocol1 in its entry point function.
    //
    Status = gtBS->RegisterProtocolNotify (
                     &mImageTestNoInterfaceProtocol1Guid,
                     Event,
                     &Registration
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.RegisterProtocolNotify - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // start the image
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check the return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid021,
                   L"BS.StartImage - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // stall some time to wait for the notification
    //
    gtBS->Stall (STALL_1_SECOND);

    //
    // Step 2: check whether the protocol1's notify function is invoked once
    //
    if (1 == NotifyTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid022,
                   L"BS.StartImage - InterfaceTestCheckpoint2",
                   L"%a:%d:NotifyTimes - %d, Expected is 1, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   NotifyTimes,
                   TplArray[Index]
                   );

    //
    // Step 3: check whether the protocol1 could be located in the system.
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mImageTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) && (1 == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid023,
                   L"BS.StartImage - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );

    //
    // Step 4: check the protocol2 is still opened.
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol2Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_SUCCESS == Status) && (1 == EntryCount)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid024,
                   L"BS.StartImage - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

NextLoop:
    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (Event != NULL) {
      gtBS->CloseEvent (Event);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestStartImageInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  UINTN                       RepeatIndex;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib, mImageHandle,
             BOOT_SERVICES_DRIVER_IMAGE_2_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The boot services driver image 2
  // will open protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (RepeatIndex = 0; RepeatIndex < 2; RepeatIndex++ ) {

    for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

      //
      // Init
      //
      ImageHandle = NULL;
      ExitData = NULL;
      EntryBuffer = NULL;
      EntryCount = 0;

      //
      // load the boot services driver image 2
      //
      Status = gtBS->LoadImage (
                       FALSE,
                       mImageHandle,
                       FilePath,
                       NULL,
                       0,
                       &ImageHandle
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.LoadImage - build environemnt",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        continue;
      }

      //
      // start the image
      //
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);

      if (RepeatIndex == 0) {
        Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
      } else {
        ExitDataSize = 0;
        Status = gtBS->StartImage (ImageHandle, &ExitDataSize, NULL);
      }

      gtBS->RestoreTPL (OldTpl);

      //
      // Step 1: check the return status
      // boot services driver image 2 will Exit with error code 'EFI_DEVICE_ERROR'
      //
      if (EFI_DEVICE_ERROR == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gImageBBTestFunctionAssertionGuid025,
                     L"BS.StartImage - InterfaceTestCheckpoint3",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );

      //
      // Step 2: check the protocol2 is not opened.
      //
      Status = gtBS->OpenProtocolInformation (
                       Handle,
                       &mImageTestNoInterfaceProtocol2Guid,
                       &EntryBuffer,
                       &EntryCount
                       );
      if ((EFI_NOT_FOUND == Status)
          || ((EFI_SUCCESS == Status) && (0 == EntryCount))) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gImageBBTestFunctionAssertionGuid026,
                     L"BS.StartImage - InterfaceTestCheckpoint3",
                     L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EntryCount,
                     TplArray[Index]
                     );
      //
      // Step 3: check whether the ExitData is not NULL or ExitDataSize remain
      // Unchanged
      //
      if (RepeatIndex == 0) {
        if (NULL != ExitData) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid027,
                       L"BS.StartImage - InterfaceTestCheckpoint3",
                       L"%a:%d:ExitData - 0x%x, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       ExitData,
                       TplArray[Index]
                       );

      } else {
        if (ExitDataSize == 0) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gImageBBTestFunctionAssertionGuid144,
                       L"BS.StartImage - InterfaceTestCheckpoint3",
                       L"%a:%d:ExitDataSize - 0x%x, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       ExitDataSize,
                       TplArray[Index]
                       );
      }
      //
      // restore environment
      //
      if (ImageHandle != NULL) {
        gtBS->UnloadImage (ImageHandle);
        ImageHandle = NULL;
      }

      if (EntryBuffer != NULL) {
        gtBS->FreePool (EntryBuffer);
        EntryBuffer = NULL;
      }

      if (ExitData != NULL) {
        gtBS->FreePool (ExitData);
        ExitData = NULL;
      }

    }
  }
Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestStartImageInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  VOID                        *Registration;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;
  EFI_EVENT                   Event;
  UINTN                       NotifyTimes;
  UINTN                       NoHandles;
  EFI_HANDLE                  *HandleBuffer;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib, mImageHandle,
             RUNTIME_SERVICES_DRIVER_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The runtime services driver image
  // will open protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    Event = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;
    NotifyTimes = 0;
    NoHandles = 0;
    HandleBuffer = NULL;

    //
    // load the runtime services driver image 1
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // Create an event
    //
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     ImageTestNotifyFunction,
                     &NotifyTimes,
                     &Event
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // register the event for protocol1 installation.
    // the application image will install protocol1 in its entry point function.
    //
    Status = gtBS->RegisterProtocolNotify (
                     &mImageTestNoInterfaceProtocol1Guid,
                     Event,
                     &Registration
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.RegisterProtocolNotify - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // start the image
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check the return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid028,
                   L"BS.StartImage - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    if (EFI_TEST_ASSERTION_FAILED == AssertionType) {
      goto NextLoop;
    }

    //
    // stall some time to wait for the notification
    //
    gtBS->Stall (STALL_1_SECOND);

    //
    // Step 2: check whether the protocol1's notify function is invoked once
    //
    if (1 == NotifyTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid029,
                   L"BS.StartImage - InterfaceTestCheckpoint4",
                   L"%a:%d:NotifyTimes - %d, Expected is 1, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   NotifyTimes,
                   TplArray[Index]
                   );

    //
    // Step 3: check whether the protocol1 could be located in the system.
    //
    Status = gtBS->LocateHandleBuffer (
                    ByProtocol,
                    &mImageTestNoInterfaceProtocol1Guid,
                    NULL,
                    &NoHandles,
                    &HandleBuffer
                    );
    if ((EFI_SUCCESS == Status) && (1 == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid030,
                   L"BS.StartImage - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );

    //
    // Step 4: check the protocol2 is still opened.
    //
    Status = gtBS->OpenProtocolInformation (
                        Handle,
                        &mImageTestNoInterfaceProtocol2Guid,
                        &EntryBuffer,
                        &EntryCount
                        );
    if ((EFI_SUCCESS == Status) && (1 == EntryCount)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid031,
                   L"BS.StartImage - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

NextLoop:
    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (Event != NULL) {
      gtBS->CloseEvent (Event);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestStartImageInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib, mImageHandle,
             RUNTIME_SERVICES_DRIVER_IMAGE_2_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The runtime services driver image 2
  // will open protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;

    //
    // load the runtime services driver image 2
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // start the image
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check the return status
    // runtime services driver image 2 will Exit with error code 'EFI_NOT_FOUND'
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid032,
                   L"BS.StartImage - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // Step 2: check the protocol2 is not opened.
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol2Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_NOT_FOUND == Status)
        || ((EFI_SUCCESS == Status) && (0 == EntryCount))) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid033,
                   L"BS.StartImage - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    //
    // Step 3: check whether the ExitData is not NULL
    //
    if (NULL != ExitData) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gImageBBTestFunctionAssertionGuid034,
                   L"BS.StartImage - InterfaceTestCheckpoint5",
                   L"%a:%d:ExitData - 0x%x, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ExitData,
                   TplArray[Index]
                   );

    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }

  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}


EFI_STATUS
EFIAPI
BBTestStartImageInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath[3];
  UINTN                       FileIndex;
  EFI_STATUS                  Status1, Status2, Status3;
  EFI_HANDLE                  ImageHandle;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;

  UINTN                       Numbers;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  gtBS->SetMem (FilePath, 3 * sizeof (EFI_DEVICE_PATH_PROTOCOL*), 0);

  Status1 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              APPLICATION_IMAGE_1_NAME,
              &FilePath[0]
              );

  Status2 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              BOOT_SERVICES_DRIVER_IMAGE_1_NAME,
              &FilePath[1]
              );

  Status3 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              RUNTIME_SERVICES_DRIVER_IMAGE_1_NAME,
              &FilePath[2]
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    for (Index = 0; Index < 3; Index++) {
      gtBS->FreePool (FilePath[Index]);
    }
    return EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    for (FileIndex = 0; FileIndex < 3; FileIndex++) {

      //
      // Init
      //
      ImageHandle = NULL;
      ExitData = NULL;

      Status = gtBS->LoadImage (
                       FALSE,
                       mImageHandle,
                       FilePath[FileIndex],
                       NULL,
                       0,
                       &ImageHandle
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.LoadImage - build environment",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        continue;
      }

      //
      // invoke StartImage twice
      //

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);

      gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);

      Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);

      gtBS->RestoreTPL (OldTpl);

      //
      // Step 1: check return status, expected status is EFI_INVALID_PARAMETER
      //
      if (EFI_INVALID_PARAMETER == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gImageBBTestFunctionAssertionGuid035,
                     L"BS.StartImage - InterfaceTestCheckpoint6",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      //
      // restore environment
      //
      if (ImageHandle != NULL) {
        gtBS->UnloadImage (ImageHandle);
      }

      if (ExitData != NULL) {
        gtBS->FreePool (ExitData);
      }
    }

  }

  //
  // free resources
  //
  for (Index = 0; Index < 3; Index++) {
    gtBS->FreePool (FilePath[Index]);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                     Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             APPLICATION_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid036;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid037;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }



  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             BOOT_SERVICES_DRIVER_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid039;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid040;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             RUNTIME_SERVICES_DRIVER_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid042;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid043;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  CHAR16                      *ExitData;
  UINTN                       ExitDataSize;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             APPLICATION_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    // EFI application will unload image automatically after StartImage
    //
    if (EFI_INVALID_PARAMETER == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid044;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid045;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint4",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  CHAR16                      *ExitData;
  UINTN                       ExitDataSize;
  UINTN                       EntryCount;
  UINTN                       NoHandles;
  EFI_HANDLE                  *HandleBuffer;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             BOOT_SERVICES_DRIVER_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The image will open
  // protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    HandleBuffer = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid046;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid047;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check whether protocol1 could be located.
    // (protocol1 should be uninstalled by the image's Unload function
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mImageTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid048;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid049;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );

    //
    // Step 3: check whether the protocol2 is closed or not
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol2Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_NOT_FOUND == Status)
        || ((EFI_SUCCESS == Status) && (0 == EntryCount))) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid050;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid051;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  CHAR16                      *ExitData;
  UINTN                       ExitDataSize;
  UINTN                       EntryCount;
  UINTN                       NoHandles;
  EFI_HANDLE                  *HandleBuffer;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImageInfoPtr;


  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             BOOT_SERVICES_DRIVER_IMAGE_3_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The image will open
  // protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    HandleBuffer = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    // the image's unload function returns EFI_DEVICE_ERROR.
    //
    if (EFI_DEVICE_ERROR == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid052;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid053;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check whether protocol1 could be located.
    // (protocol1 should be uninstalled by the image's Unload function
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mImageTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );

    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid054;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid055;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );

    //
    // Step 3: check whether the protocol2 is closed or not
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol2Guid,
                     &EntryBuffer,
                     &EntryCount
                     );

    if ((EFI_SUCCESS == Status) && (EntryCount == 1)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid056;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid057;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

    //
    //use the good UnLoad() function to unload this driver from memory.
    //

    gtBS->HandleProtocol (
            ImageHandle,
            &gEfiLoadedImageProtocolGuid,
            (VOID*)&LoadedImageInfoPtr
            );

    LoadedImageInfoPtr->Unload = ImageTestDriversUnload;

    gtBS->UnloadImage (ImageHandle);

    //
    //free unused resource.
    //

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle1;
  EFI_HANDLE                  Handle2;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  CHAR16                      *ExitData;
  UINTN                       ExitDataSize;
  UINTN                       EntryCount;
  UINTN                       NoHandles;
  EFI_HANDLE                  *HandleBuffer;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle1 = NULL;
  Handle2 = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib, mImageHandle,
             BOOT_SERVICES_DRIVER_IMAGE_4_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The image will open
  // protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle1,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol3 onto a new handle. The image will open
  // protocol3 BY_DRIVER in its DriverBinding.Start() function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle2,
                   &mImageTestNoInterfaceProtocol3Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    HandleBuffer = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    // the image has no Unload function at first.
    //
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid058;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid059;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check whether protocol1 could be located.
    // (protocol1 should be uninstalled by the image's Unload function
    //
    Status = gtBS->LocateHandleBuffer (
                    ByProtocol,
                    &mImageTestNoInterfaceProtocol1Guid,
                    NULL,
                    &NoHandles,
                    &HandleBuffer
                    );
    if ((EFI_SUCCESS == Status) && (1 == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid060;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid061;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );

    //
    // Step 3: check whether the protocol2 is closed or not
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle1,
                     &mImageTestNoInterfaceProtocol2Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_SUCCESS == Status) && (1 == EntryCount)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid062;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid063;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

    Status = gtBS->ConnectController (Handle2, NULL, NULL, TRUE);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.ConnectController - restore environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    gtBS->DisconnectController (Handle2, NULL, NULL);

    gtBS->UnloadImage (ImageHandle);

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle1 != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle1,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }
  if (Handle2 != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle2,
            &mImageTestNoInterfaceProtocol3Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  CHAR16                      *ExitData;
  UINTN                       ExitDataSize;
  UINTN                       EntryCount;
  UINTN                       NoHandles;
  EFI_HANDLE                  *HandleBuffer;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             RUNTIME_SERVICES_DRIVER_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The image will open
  // protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    HandleBuffer = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid064;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid065;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint8",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check whether protocol1 could be located.
    // (protocol1 should be uninstalled by the image's Unload function
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mImageTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_NOT_FOUND == Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid066;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid067;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint8",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );

    //
    // Step 3: check whether the protocol2 is closed or not
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol2Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_NOT_FOUND == Status)
        || ((EFI_SUCCESS == Status) && (0 == EntryCount))) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid068;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid069;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint8",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:

  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  CHAR16                      *ExitData;
  UINTN                       ExitDataSize;
  UINTN                       EntryCount;
  UINTN                       NoHandles;
  EFI_HANDLE                  *HandleBuffer;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImageInfoPtr;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             RUNTIME_SERVICES_DRIVER_IMAGE_3_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The image will open
  // protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    HandleBuffer = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    // the image's unload function returns EFI_UNSUPPORTED.
    //
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid070;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid071;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check whether protocol1 could be located.
    // (protocol1 should be uninstalled by the image's Unload function
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mImageTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_NOT_FOUND == Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid072;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid073;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );

    //
    // Step 3: check whether the protocol2 is still opened by the Image.
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol2Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_SUCCESS == Status) && (1 == EntryCount)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid074;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid075;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

    //
    //use the good UnLoad() function to unload this driver from memory.
    //

    gtBS->HandleProtocol (
            ImageHandle,
            &gEfiLoadedImageProtocolGuid,
            (VOID*)&LoadedImageInfoPtr
            );

    LoadedImageInfoPtr->Unload = ImageTestDriversUnload;

    gtBS->UnloadImage (ImageHandle);

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUnloadImageInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle1;
  EFI_HANDLE                  Handle2;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  CHAR16                      *ExitData;
  UINTN                       ExitDataSize;
  UINTN                       EntryCount;
  UINTN                       NoHandles;
  EFI_HANDLE                  *HandleBuffer;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle1 = NULL;
  Handle2 = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             RUNTIME_SERVICES_DRIVER_IMAGE_4_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol2 onto a new handle. The image will open
  // protocol2 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle1,
                   &mImageTestNoInterfaceProtocol2Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol3 onto a new handle. The image will open
  // protocol3 BY_DRIVER in its DriverBinding.Start() function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle2,
                   &mImageTestNoInterfaceProtocol3Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    HandleBuffer = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->UnloadImage (ImageHandle);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    // the image has no Unload function at first.
    //
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid076;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid077;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint10",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    //
    // Step 2: check whether protocol1 could be located.
    // (protocol1 should be uninstalled by the image's Unload function
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mImageTestNoInterfaceProtocol1Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) && (1 == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid078;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid079;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint10",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );

    //
    // Step 3: check whether the protocol2 is closed or not
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle1,
                     &mImageTestNoInterfaceProtocol2Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_SUCCESS == Status) && (1 == EntryCount)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid080;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid081;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.UnloadImage - InterfaceTestCheckpoint10",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

    Status = gtBS->ConnectController (Handle2, NULL, NULL, TRUE);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.ConnectController - restore environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    gtBS->DisconnectController (Handle2, NULL, NULL);

    gtBS->UnloadImage (ImageHandle);

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle1 != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle1,
            &mImageTestNoInterfaceProtocol2Guid,
            NULL
            );
  }

  if (Handle2 != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle2,
            &mImageTestNoInterfaceProtocol3Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}


EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             APPLICATION_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->Exit (ImageHandle, EFI_SUCCESS, 0, NULL);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid082;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid083;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint1",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             BOOT_SERVICES_DRIVER_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->Exit (ImageHandle, EFI_SUCCESS, 0, NULL);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid084;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid085;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint2",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             RUNTIME_SERVICES_DRIVER_IMAGE_1_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (FilePath);
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;

    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
     if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L" BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);

    Status = gtBS->Exit (ImageHandle, EFI_SUCCESS, 0, NULL);

    gtBS->RestoreTPL (OldTpl);

    //
    // Step 1: check return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid086;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid087;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint3",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
  }

  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_TPL                     OldTpl;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath[3];
  EFI_HANDLE                  ImageHandle;
  EFI_STATUS                  Status1, Status2, Status3;
  UINTN                       FileIndex;
  CHAR16                      *ExitData;
  UINTN                       ExitDataSize;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  gtBS->SetMem (FilePath, 3 * sizeof (EFI_DEVICE_PATH_PROTOCOL*), 0);

  Status1 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              APPLICATION_IMAGE_1_NAME,
              &FilePath[0]
              );
  Status2 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              BOOT_SERVICES_DRIVER_IMAGE_1_NAME,
              &FilePath[1]
              );
  Status3 = ImageTestComposeSimpleFilePath (
              StandardLib,
              mImageHandle,
              RUNTIME_SERVICES_DRIVER_IMAGE_1_NAME,
              &FilePath[2]
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2) || EFI_ERROR(Status3)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status1 - %r, Status2 - %r, Status3 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    for (Index = 0; Index < 3; Index++) {
      gtBS->FreePool (FilePath[Index]);
    }
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE; Index++) {

    for (FileIndex = 0; FileIndex < 3; FileIndex++) {
      //
      // Init
      //
      ImageHandle = NULL;
      ExitData = NULL;

      Status = gtBS->LoadImage (
                       FALSE,
                       mImageHandle,
                       FilePath[FileIndex],
                       NULL,
                       0,
                       &ImageHandle
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L" BS.LoadImage - build environment",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        continue;
      }

      Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L" BS.StartImage - build environment",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto NextLoop;
      }

      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = gtBS->Exit (ImageHandle, EFI_SUCCESS, 0, NULL);
      gtBS->RestoreTPL (OldTpl);

      //
      // Step 1: check return status
      //
      if (EFI_INVALID_PARAMETER == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
      TplGuid = gImageBBTestFunctionAssertionGuid088;
    } else {
      TplGuid = gImageBBTestFunctionAssertionGuid089;
    }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"BS.Exit - InterfaceTestCheckpoint4",
                     L"%a:%d:Status - %r, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
NextLoop:
      //
      // restore environment
      //
      gtBS->UnloadImage (ImageHandle);

      if (ExitData != NULL) {
        gtBS->FreePool (ExitData);
      }
    }
  }

  //
  // free resources
  //
  for (Index = 0; Index < 3; Index++) {
    if (FilePath[Index] != NULL) {
      gtBS->FreePool (FilePath[Index]);
    }
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}


EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  VOID                        *Registration;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;
  EFI_EVENT                   Event;
  UINTN                       NotifyTimes;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;
  UINTN                       DataSize;
  EFI_HANDLE                  VariableHandle;


  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             APPLICATION_IMAGE_3_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol4 onto a new handle. The application image will open
  // protocol4 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol4Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    Event = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;
    NotifyTimes = 0;

    //
    // load the image file
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // Create an event
    //
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     ImageTestNotifyFunction,
                     &NotifyTimes,
                     &Event
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // register the event for protocol3 installation.
    // the application image will install protocol3 in its entry point function.
    //
    Status = gtBS->RegisterProtocolNotify (
                     &mImageTestNoInterfaceProtocol3Guid,
                     Event,
                     &Registration
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.RegisterProtocolNotify - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // start the application image. This image's Exit() return EFI_SUCCESS.
    //

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);


    //
    // Step 1: check the return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid090;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // stall some time to wait for the notification
    //
    gtBS->Stall (STALL_1_SECOND);

    //
    // Step 2: check whether the protocol3's notify function is invoked once
    //
    if (1 == NotifyTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid092;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint5",
                   L"%a:%d:NotifyTimes - %d, Expected is 1, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   NotifyTimes,
                   TplArray[Index]
                   );

    //
    // Step 3: check the protocol4 is not opened.
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol4Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_NOT_FOUND == Status)
        || ((EFI_SUCCESS == Status) && (0 == EntryCount))) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid094;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint5",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

    //
    //step 4 check the Exit() directly return control to us and not call the
    //SetVariable function.
    //
    DataSize = sizeof (EFI_HANDLE);

    Status = gtRT->GetVariable (
                     IMAGE_APPLICATION3_CALLED_AFTER_EXIT,
                     &mImageTestVariableVendorGuid,
                     NULL,
                     &DataSize,
                     &VariableHandle
                     );

    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid132;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint5",
                   L"%a:%d:GetVariable() Name - %s, Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   IMAGE_APPLICATION3_CALLED_AFTER_EXIT,
                   Status,
                   TplArray[Index]
                   );


NextLoop:
    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (Event != NULL) {
      gtBS->CloseEvent (Event);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol4Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  VOID                        *Registration;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;
  EFI_EVENT                   Event;
  UINTN                       NotifyTimes;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;
  UINTN                       DataSize;
  EFI_HANDLE                  VariableHandle;


  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             APPLICATION_IMAGE_4_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol4 onto a new handle. The application image will open
  // protocol4 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol4Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    Event = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;
    NotifyTimes = 0;

    //
    // load the image file
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                    );
      continue;
    }

    //
    // Create an event
    //
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     ImageTestNotifyFunction,
                     &NotifyTimes,
                     &Event
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // register the event for protocol3 installation.
    // the application image will install protocol3 in its entry point function.
    //
    Status = gtBS->RegisterProtocolNotify (
                        &mImageTestNoInterfaceProtocol3Guid,
                        Event,
                        &Registration
                        );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.RegisterProtocolNotify - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // start the application image. This image's Exit() return EFI_DEVICE_ERROR
    // and the ExitData returns "Application 4's Error Code is EFI_DEVICE_ERROR".
    //

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);


    //
    // Step 1: check the return status
    //
    if (EFI_DEVICE_ERROR == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid096;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // stall some time to wait for the notification
    //
    gtBS->Stall (STALL_1_SECOND);

    //
    // Step 2: check whether the protocol3's notify function is invoked once
    //
    if (1 == NotifyTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid098;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint6",
                   L"%a:%d:NotifyTimes - %d, Expected is 1, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   NotifyTimes,
                   TplArray[Index]
                   );

    //
    // Step 3: check the protocol4 is not opened.
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol4Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_NOT_FOUND == Status)
        || ((EFI_SUCCESS == Status) && (0 == EntryCount))) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid100;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint6",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    //
    // Step 4: check the returned Exit Data
    //
    if (!SctStrCmp (ExitData, ERROR_MESSAGE_FOR_APPLICATION_4)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid102;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint6",
                   L"%a:%d:Expected: %s, Received: %s,TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ERROR_MESSAGE_FOR_APPLICATION_4,
                   ExitData,
                   TplArray[Index]
                   );

    //
    //step 5 verify the Exit() return control to StartImage directly and the
    //variable should not be set.
    //

    DataSize = sizeof(EFI_HANDLE);

    Status = gtRT->GetVariable (
                     IMAGE_APPLICATION4_CALLED_AFTER_EXIT,
                     &mImageTestVariableVendorGuid,
                     NULL,
                     &DataSize,
                     &VariableHandle
                     );

    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid134;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint6",
                   L"%a:%d:GetVariable() Name - %s, Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   IMAGE_APPLICATION4_CALLED_AFTER_EXIT,
                   Status,
                   TplArray[Index]
                   );

NextLoop:
    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (Event != NULL) {
      gtBS->CloseEvent (Event);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol4Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;
  EFI_HANDLE                  *HandleBuffer;
  UINTN                       NoHandles;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;
  UINTN                       DataSize;
  EFI_HANDLE                  VariableHandle;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             BOOT_SERVICES_DRIVER_IMAGE_5_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol4 onto a new handle. The application image will open
  // protocol4 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol4Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;
    HandleBuffer = NULL;
    NoHandles = 0;


    //
    // load the image file
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // start the boot services driver image. This image's Exit() return EFI_SUCCESS.
    //

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);

    //
    // Step 1: check the return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid104;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // Step 2: locate for the Protocol3
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mImageTestNoInterfaceProtocol3Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) && (1 == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid106;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );
    //
    // Step 3: check the protocol4 is still opened.
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol4Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_SUCCESS == Status) && (1 == EntryCount)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid108;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint7",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );

    //
    //step 4 verify the Exit() return control to StartImage directly and the
    //variable should not be set.
    //

    DataSize = sizeof(EFI_HANDLE);

    Status = gtRT->GetVariable (
                     IMAGE_BOOTSERVICESDRIVER5_CALLED_AFTER_EXIT,
                     &mImageTestVariableVendorGuid,
                     NULL,
                     &DataSize,
                     &VariableHandle
                     );

    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid136;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint7",
                   L"%a:%d:GetVariable() Name - %s, Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   IMAGE_BOOTSERVICESDRIVER5_CALLED_AFTER_EXIT,
                   Status,
                   TplArray[Index]
                   );

    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol4Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  VOID                        *Registration;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;
  EFI_EVENT                   Event;
  UINTN                       NotifyTimes;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;
  UINTN                       DataSize;
  EFI_HANDLE                  VariableHandle;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             BOOT_SERVICES_DRIVER_IMAGE_6_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol4 onto a new handle. The boot services driver image will
  // open protocol4 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol4Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    Event = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;
    NotifyTimes = 0;

    //
    // load the image file
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // Create an event
    //
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     ImageTestNotifyFunction,
                     &NotifyTimes,
                     &Event
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // register the event for protocol3 installation.
    // the boot services driver image will install protocol3
    // in its entry point function.
    //
    Status = gtBS->RegisterProtocolNotify (
                     &mImageTestNoInterfaceProtocol3Guid,
                     Event,
                     &Registration
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.RegisterProtocolNotify - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // start the boot services driver image. This image's Exit()
    // return EFI_NOT_FOUND and the ExitData returns
    // " Boot Services Driver Image 6 return EFI_NOT_FOUND"
    //

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);


    //
    // Step 1: check the return status
    //
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid110;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint8",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // stall some time to wait for the notification
    //
    gtBS->Stall (STALL_1_SECOND);

    //
    // Step 2: check whether the protocol3's notify function is invoked once
    //
    if (1 == NotifyTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid112;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint8",
                   L"%a:%d:NotifyTimes - %d, Expected is 1, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   NotifyTimes,
                   TplArray[Index]
                   );

    //
    // Step 3: check the protocol4 is not opened.
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol4Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_NOT_FOUND == Status)
        || ((EFI_SUCCESS == Status) && (0 == EntryCount))) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid114;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint8",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    //
    // Step 4: check the returned Exit Data
    //
    if (!SctStrCmp (ExitData, ERROR_MESSAGE_FOR_BOOT_SERVICES_DRIVER_6)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid116;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint8",
                   L"%a:%d:Expected - %s, Received - %s, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ERROR_MESSAGE_FOR_BOOT_SERVICES_DRIVER_6,
                   ExitData,
                   TplArray[Index]
                   );

    //
    //step 5 verify the Exit() return control to StartImage directly and the
    //variable should not be set.
    //

    DataSize = sizeof(EFI_HANDLE);

    Status = gtRT->GetVariable (
                     IMAGE_BOOTSERVICESDRIVER6_CALLED_AFTER_EXIT,
                     &mImageTestVariableVendorGuid,
                     NULL,
                     &DataSize,
                     &VariableHandle
                     );

    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid138;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint8",
                   L"%a:%d:GetVariable() Name - %s, Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   IMAGE_BOOTSERVICESDRIVER6_CALLED_AFTER_EXIT,
                   Status,
                   TplArray[Index]
                   );



NextLoop:
    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (Event != NULL) {
      gtBS->CloseEvent (Event);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol4Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;
  EFI_HANDLE                  *HandleBuffer;
  UINTN                       NoHandles;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;
  UINTN                       DataSize;
  EFI_HANDLE                  VariableHandle;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             RUNTIME_SERVICES_DRIVER_IMAGE_5_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol4 onto a new handle. The application image will open
  // protocol4 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol4Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;
    HandleBuffer = NULL;
    NoHandles = 0;


    //
    // load the image file
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // start the runtime services driver image. This image's Exit() return EFI_SUCCESS.
    //

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);

    //
    // Step 1: check the return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid118;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // Step 2: locate for the Protocol3
    //
    Status = gtBS->LocateHandleBuffer (
                     ByProtocol,
                     &mImageTestNoInterfaceProtocol3Guid,
                     NULL,
                     &NoHandles,
                     &HandleBuffer
                     );
    if ((EFI_SUCCESS == Status) && (1 == NoHandles)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid120;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, NoHandles - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles,
                   TplArray[Index]
                   );
    //
    // Step 3: check the protocol4 is still opened.
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol4Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_SUCCESS == Status) && (1 == EntryCount)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid122;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint9",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    //
    //step 4 verify the Exit() return control to StartImage directly and the
    //variable should not be set.
    //

    DataSize = sizeof(EFI_HANDLE);

    Status = gtRT->GetVariable (
                     IMAGE_RUNTIMESERVICESDRIVER5_CALLED_AFTER_EXIT,
                     &mImageTestVariableVendorGuid,
                     NULL,
                     &DataSize,
                     &VariableHandle
                     );

    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    TplGuid = gImageBBTestFunctionAssertionGuid140;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint9",
                   L"%a:%d:GetVariable() Name - %s, Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   IMAGE_RUNTIMESERVICESDRIVER5_CALLED_AFTER_EXIT,
                   Status,
                   TplArray[Index]
                   );


    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol4Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestExitInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_HANDLE                  Handle;
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINTN                       Index;
  EFI_DEVICE_PATH_PROTOCOL    *FilePath;
  EFI_HANDLE                  ImageHandle;
  VOID                        *Registration;
  UINTN                       ExitDataSize;
  CHAR16                      *ExitData;
  UINTN                       EntryCount;
  EFI_EVENT                   Event;
  UINTN                       NotifyTimes;

  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *EntryBuffer;

  UINTN                       Numbers;
  EFI_GUID                    TplGuid;
  UINTN                       DataSize;
  EFI_HANDLE                  VariableHandle;

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" ImageTestCheckForCleanEnvironment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
    return Status;
  }

  //
  // init
  //
  FilePath = NULL;
  Handle = NULL;

  Status = ImageTestComposeSimpleFilePath (
             StandardLib,
             mImageHandle,
             RUNTIME_SERVICES_DRIVER_IMAGE_6_NAME,
             &FilePath
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ImageTestComposeSimpleFilePath - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // install protocol4 onto a new handle. The boot services driver image will
  // open protocol4 in its entry point function.
  //
  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mImageTestNoInterfaceProtocol4Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.InstallProtocolInterface - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE; Index++) {

    //
    // Init
    //
    ImageHandle = NULL;
    Event = NULL;
    ExitData = NULL;
    EntryBuffer = NULL;
    EntryCount = 0;
    NotifyTimes = 0;

    //
    // load the image file
    //
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // Create an event
    //
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     ImageTestNotifyFunction,
                     &NotifyTimes,
                     &Event
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // register the event for protocol3 installation.
    // the runtime services driver image will install protocol3
    // in its entry point function.
    //
    Status = gtBS->RegisterProtocolNotify (
                     &mImageTestNoInterfaceProtocol3Guid,
                     Event,
                     &Registration
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.RegisterProtocolNotify - build environemnt",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // start the runtime services driver image. This image's Exit()
    // return EFI_UNSUPPORTED and the ExitData returns
    // "Runtime Services Driver Image 6 return EFI_UNSUPPORTED"
    //

    Status = gtBS->StartImage (ImageHandle, &ExitDataSize, &ExitData);


    //
    // Step 1: check the return status
    //
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid124;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint10",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );

    //
    // stall some time to wait for the notification
    //
    gtBS->Stall (STALL_1_SECOND);

    //
    // Step 2: check whether the protocol3's notify function is invoked once
    //
    if (1 == NotifyTimes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid126;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint10",
                   L"%a:%d:NotifyTimes - %d, Expected is 1, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   NotifyTimes,
                   TplArray[Index]
                   );

    //
    // Step 3: check the protocol4 is not opened.
    //
    Status = gtBS->OpenProtocolInformation (
                     Handle,
                     &mImageTestNoInterfaceProtocol4Guid,
                     &EntryBuffer,
                     &EntryCount
                     );
    if ((EFI_NOT_FOUND == Status)
        || ((EFI_SUCCESS == Status) && (0 == EntryCount))) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid128;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint10",
                   L"%a:%d:Status - %r, EntryCount - %d, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EntryCount,
                   TplArray[Index]
                   );
    //
    // Step 4: check the returned Exit Data
    //
    if (!SctStrCmp (ExitData, ERROR_MESSAGE_FOR_RUNTIME_SERVICES_DRIVER_6)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid130;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint10",
                   L"%a:%d:Expected: %s, Received: %s,TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   ERROR_MESSAGE_FOR_RUNTIME_SERVICES_DRIVER_6,
                   ExitData,
                   TplArray[Index]
                   );

    //
    //step 4 verify the Exit() return control to StartImage directly and the
    //variable should not be set.
    //

    DataSize = sizeof(EFI_HANDLE);

    Status = gtRT->GetVariable (
                     IMAGE_RUNTIMESERVICESDRIVER6_CALLED_AFTER_EXIT,
                     &mImageTestVariableVendorGuid,
                     NULL,
                     &DataSize,
                     &VariableHandle
                     );

    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }


    TplGuid = gImageBBTestFunctionAssertionGuid142;

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"BS.Exit - InterfaceTestCheckpoint10",
                   L"%a:%d:GetVariable() Name - %s, Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   IMAGE_RUNTIMESERVICESDRIVER6_CALLED_AFTER_EXIT,
                   Status,
                   TplArray[Index]
                   );



NextLoop:
    //
    // restore environment
    //
    if (ImageHandle != NULL) {
      gtBS->UnloadImage (ImageHandle);
    }

    if (Event != NULL) {
      gtBS->CloseEvent (Event);
    }

    if (EntryBuffer != NULL) {
      gtBS->FreePool (EntryBuffer);
    }

    if (ExitData != NULL) {
      gtBS->FreePool (ExitData);
    }
  }

Done:
  //
  // free resources
  //
  if (FilePath != NULL) {
    gtBS->FreePool (FilePath);
  }

  if (Handle != NULL) {
    gtBS->UninstallProtocolInterface (
            Handle,
            &mImageTestNoInterfaceProtocol4Guid,
            NULL
            );
  }

  Status = ImageTestCheckForCleanEnvironment (&Numbers);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L" CheckForCleanEnvironment - restore environment",
                   L"%a:%d:Status - %r, Number - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Numbers
                   );
  }

  return Status;
}
