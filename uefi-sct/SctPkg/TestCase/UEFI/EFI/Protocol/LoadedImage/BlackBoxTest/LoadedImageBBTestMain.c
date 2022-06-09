/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  LoadedImageBBTestMain.c

Abstract:

  for Loaded Image Protocol Black Box Test

--*/
#include "LoadedImageBBTest.h"

//
// global variable for this test driver's image handle
//
EFI_HANDLE      mImageHandle;


EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  LOADED_IMAGE_PROTOCOL_TEST_REVISION,
  EFI_LOADED_IMAGE_PROTOCOL_GUID,
  L"Testing For Loaded Image Protocol",
  L"Total # test cases for the Loaded Image Protocol"
};

EFI_GUID gSupportProtocolGuid1[3] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_PROFILE_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    LOADED_IMAGE_PROTOCOL_TEST_ENTRY_GUID0101,
    L"LoadedImageProtocolTest1",
    L"Test on new created Loaded Image Protocol instance",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLoadedImageTest1
  },
  {
    LOADED_IMAGE_PROTOCOL_TEST_ENTRY_GUID0102,
    L"LoadedImageProtocolTest2",
    L"Test on all Loaded Image Protocols",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestLoadedImageTest2
  },
  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

/**
 *  Creates/installs the BlackBox Interface and eminating Entry Point
 *  node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 */
EFI_STATUS
EFIAPI
InitializeBBTestLoadedImageProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //
  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestLoadedImageProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
EFIAPI
BBTestLoadedImageProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

EFI_STATUS
EFIAPI
BBTestLoadedImageTest1 (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_LOADED_IMAGE_PROTOCOL            *LoadedImage;
  EFI_DEVICE_PATH_PROTOCOL             *FilePath[6];
  EFI_STATUS                           Status;
  EFI_STATUS                           Status1;
  EFI_STATUS                           Status2;
  NOTIFY_CONTEXT                       ProtocolNotifyContext;
  EFI_EVENT                            EventArray[6];
  EFI_GUID                             *ProtocolGuid[6];
  UINTN                                Index;
  UINTN                                LoadOption;
  EFI_HANDLE                           ImageHandle;
  UINT32                               ImageRevision;
  EFI_PHYSICAL_ADDRESS                 Address1;
  EFI_PHYSICAL_ADDRESS                 Address2;
  EFI_PHYSICAL_ADDRESS                 Address3;

  //
  // init
  //
  gtBS->SetMem (FilePath, 6 * sizeof (EFI_DEVICE_PATH_PROTOCOL*), 0);
  gtBS->SetMem (&ProtocolNotifyContext, sizeof (NOTIFY_CONTEXT), 0);
  gtBS->SetMem (EventArray, 6 * sizeof (EFI_EVENT), 0);

  ProtocolGuid[0] = &mLoadedImageTestNoInterfaceProtocol1Guid;
  ProtocolGuid[1] = &mLoadedImageTestNoInterfaceProtocol2Guid;
  ProtocolGuid[2] = &mLoadedImageTestNoInterfaceProtocol3Guid;
  ProtocolGuid[3] = &mLoadedImageTestNoInterfaceProtocol4Guid;
  ProtocolGuid[4] = &mLoadedImageTestNoInterfaceProtocol5Guid;
  ProtocolGuid[5] = &mLoadedImageTestNoInterfaceProtocol6Guid;
  ImageRevision = EFI_LOADED_IMAGE_INFORMATION_REVISION;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the Profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status1 = LoadedImageTestComposeSimpleFilePath (
              StandardLib,
              ProfileLib,
              mImageHandle,
              EFI_APPLICATION_1_NAME,
              &FilePath[0]
              );
  Status2 = LoadedImageTestComposeSimpleFilePath (
              StandardLib,
              ProfileLib,
              mImageHandle,
              EFI_APPLICATION_2_NAME,
              &FilePath[1]
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"LoadedImageTestComposeSimpleFilePath - compose application files",
                   L"%a:%d:Status1:%r, Status2:%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  Status1 = LoadedImageTestComposeSimpleFilePath (
              StandardLib,
              ProfileLib,
              mImageHandle,
              BOOT_SERVICES_DRIVER_1_NAME,
              &FilePath[2]
              );
  Status2 = LoadedImageTestComposeSimpleFilePath (
              StandardLib,
              ProfileLib,
              mImageHandle,
              BOOT_SERVICES_DRIVER_2_NAME,
              &FilePath[3]
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"LoadedImageTestComposeSimpleFilePath - compose boot services drivers",
                   L"%a:%d:Status1:%r, Status2:%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  Status1 = LoadedImageTestComposeSimpleFilePath (
              StandardLib,
              ProfileLib,
              mImageHandle,
              RUNTIME_SERVICES_DRIVER_1_NAME,
              &FilePath[4]
              );
  Status2 = LoadedImageTestComposeSimpleFilePath (
              StandardLib,
              ProfileLib,
              mImageHandle,
              RUNTIME_SERVICES_DRIVER_2_NAME,
              &FilePath[5]
              );
  if (EFI_ERROR(Status1) || EFI_ERROR(Status2)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"LoadedImageTestComposeSimpleFilePath - compose runtime services drivers",
                   L"%a:%d:Status1:%r, Status2:%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );
    Status = EFI_DEVICE_ERROR;
    goto Done;
  }

  //
  // create 6 events for 6 protocol installation notify
  //
  for (Index = 0; Index < 6; Index++) {

    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) TestNotifyFunction,
                     &ProtocolNotifyContext,
                     &EventArray[Index]
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.CreateEvent()",
                     L"%a:%d:Status: %r, Index: %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      goto Done;
    }
  }

  //
  // register protocol notify
  //
  for (Index = 0; Index < 6; Index++) {
    Status = gtBS->RegisterProtocolNotify (
                     ProtocolGuid[Index],
                     EventArray[Index],
                     &(ProtocolNotifyContext.Registration[Index])
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.RegisterProtocolNotify()",
                     L"%a:%d:Status: %r, Index: %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      goto Done;
    }
  }

  LoadOption = 1;
  for (Index = 0; Index < 6; Index++) {

    ImageHandle = NULL;
    Status = gtBS->LoadImage (
                     FALSE,
                     mImageHandle,
                     FilePath[Index],
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage()",
                     L"%a:%d:Status :%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // handle the LoadedImage protocol on the image handle.
    //
    Status = gtBS->HandleProtocol (
                     ImageHandle,
                     &gBlackBoxEfiLoadedImageProtocolGuid,
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
                   gLoadedImageTestAssertionGuid001,
                   L"Loaded Image Protocol Test - test 1",
                   L"%a:%d: check HandleProtocol Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (EFI_ERROR (Status)) {
        goto NextLoop;
    }
    //
    // perform generic check on the LoadedImage protocol
    //
    if (LoadedImage->Revision == ImageRevision) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gLoadedImageTestAssertionGuid018,
                   L"Loaded Image Protocol Test - test 1",
                   L"%a:%d: Revision: 0x%x, expected: 0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   LoadedImage->Revision,
                   ImageRevision
                   );

    //
    // ParentHandle should equal the test driver's image handle.
    //
    if (LoadedImage->ParentHandle == mImageHandle) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gLoadedImageTestAssertionGuid002,
                   L"Loaded Image Protocol Test - test 1",
                   L"%a:%d: check ParentHandle",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // System Table is not NULL and points to valid position.
    //
    if (LoadedImage->SystemTable != NULL){
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gLoadedImageTestAssertionGuid003,
                   L"Loaded Image Protocol Test - test 1",
                   L"%a:%d: LoadedImage->SystemTable is 0x%x, gtST is 0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   LoadedImage->SystemTable,
                   gtST
                   );

    //
    // DeviceHandle is not NULL
    //
    if (LoadedImage->DeviceHandle != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gLoadedImageTestAssertionGuid004,
                   L"Loaded Image Protocol Test - test 1",
                   L"%a:%d: LoadedImage->DeviceHandle is 0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   LoadedImage->DeviceHandle
                   );

    //
    // ImageBase is not NULL and ImageSize is not 0.
    //
    if ((LoadedImage->ImageBase != NULL) && (LoadedImage->ImageSize != 0)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gLoadedImageTestAssertionGuid005,
                   L"Loaded Image Protocol Test - test 1",
                   L"%a:%d: LoadedImage->ImageBase is 0x%x, LoadedImage->ImageSize is 0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   LoadedImage->ImageBase,
                   (UINTN)LoadedImage->ImageSize
                   );

    //
    // special check for specific image file
    //

    //
    // check for ImageCodeType and ImageDataType
    //
    if (Index < 2) {
      if ((LoadedImage->ImageDataType == EfiLoaderData)
          && (LoadedImage->ImageCodeType == EfiLoaderCode)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gLoadedImageTestAssertionGuid006,
                     L"Loaded Image Protocol Test - test 1",
                     L"%a:%d: LoadedImage->ImageCodeType is %x, LoadedImage->ImageDataType is %x",
                     __FILE__,
                     (UINTN)__LINE__,
                     LoadedImage->ImageCodeType,
                     LoadedImage->ImageDataType
                     );
    } else if (Index < 4) {
      if ((LoadedImage->ImageDataType == EfiBootServicesData)
          && (LoadedImage->ImageCodeType == EfiBootServicesCode)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gLoadedImageTestAssertionGuid007,
                     L"Loaded Image Protocol Test - test 1",
                     L"%a:%d: LoadedImage->ImageCodeType is %x, LoadedImage->ImageDataType is %x",
                     __FILE__,
                     (UINTN)__LINE__,
                     LoadedImage->ImageCodeType,
                     LoadedImage->ImageDataType
                     );
    } else {
      if ((LoadedImage->ImageDataType == EfiRuntimeServicesData)
          && (LoadedImage->ImageCodeType == EfiRuntimeServicesCode)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gLoadedImageTestAssertionGuid008,
                     L"Loaded Image Protocol Test - test 1",
                     L"%a:%d: LoadedImage->ImageCodeType is %x, LoadedImage->ImageDataType is %x",
                     __FILE__,
                     (UINTN)__LINE__,
                     LoadedImage->ImageCodeType,
                     LoadedImage->ImageDataType
                     );
    }

    //
    // Application 1 ~ 2 have no Unload function
    //
    if (Index < 2) {
      if (LoadedImage->Unload == NULL) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gLoadedImageTestAssertionGuid009,
                     L"Loaded Image Protocol Test - test 1",
                     L"%a:%d: Unload is 0x%x, ImageBase is 0x%x, ImageSize is 0x%x",
                     __FILE__,
                     (UINTN)__LINE__,
                     LoadedImage->Unload,
                     LoadedImage->ImageBase,
                     (UINTN)LoadedImage->ImageSize
                     );
    }

    Status = gtBS->StartImage (ImageHandle, NULL, NULL);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.StartImage()",
                     L"%a:%d: Status: %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    if (Index > 1) {

      Address1 = (EFI_PHYSICAL_ADDRESS)((UINTN)LoadedImage->Unload);
      Address2 = (EFI_PHYSICAL_ADDRESS)((UINTN)LoadedImage->ImageBase);
      Address3 = (EFI_PHYSICAL_ADDRESS)(UINTN)((((UINTN)LoadedImage->ImageBase + (UINTN)LoadedImage->ImageSize) - 1));

      if ((LoadedImage->Unload != NULL)
          && (Address1 >= Address2)
          && (Address1 <= Address3)) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gLoadedImageTestAssertionGuid010,
                     L"Loaded Image Protocol Test - test 1",
                     L"%a:%d: Unload is 0x%x, ImageBase is 0x%x, ImageSize is 0x%x",
                     __FILE__,
                     (UINTN)__LINE__,
                     LoadedImage->Unload,
                     LoadedImage->ImageBase,
                     (UINTN)LoadedImage->ImageSize
                     );
    }

    //
    // check for LoadOption
    //

    //
    // Application 2, BootServicesDriver 2, RuntimeServicesDriver 2
    //
    if (Index == 1 || Index == 3 || Index == 5) {
      if (Index > 1) {
        gtBS->UnloadImage (ImageHandle);
      }
      Status = gtBS->LoadImage (
                       FALSE,
                       mImageHandle,
                       FilePath[Index],
                       NULL,
                       0,
                       &ImageHandle
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.LoadImage()",
                       L"%a:%d: Status: %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto NextLoop;
      }

      //
      // handle the LoadedImage protocol on the image handle.
      //
      Status = gtBS->HandleProtocol (
                       ImageHandle,
                       &gBlackBoxEfiLoadedImageProtocolGuid,
                       (VOID **) &LoadedImage
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.HandleProtocol()",
                       L"%a:%d: Status: %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto NextLoop;
      }

      LoadedImage->LoadOptions = &LoadOption;
      LoadedImage->LoadOptionsSize = sizeof (UINTN);

      Status = gtBS->StartImage (ImageHandle, NULL, NULL);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.StartImage()",
                       L"%a:%d: Status: %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto NextLoop;
      }

      //
      // check for protocol notify
      //
      if (ProtocolNotifyContext.ProtocolIndex == LoadOption) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gLoadedImageTestAssertionGuid011,
                     L"Loaded Image Protocol Test - test 1",
                     L"%a:%d: Protocol %d %s invoked",
                     __FILE__,
                     (UINTN)__LINE__,
                     LoadOption,
                     (AssertionType == EFI_TEST_ASSERTION_PASSED) ? L"is" : L"isn't"
                     );
      LoadOption++;
      if (Index > 1) {
        gtBS->UnloadImage (ImageHandle);
      }
      Status = gtBS->LoadImage (
                       FALSE,
                       mImageHandle,
                       FilePath[Index],
                       NULL,
                       0,
                       &ImageHandle
                       );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.LoadImage()",
                       L"%a:%d: Status: %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto NextLoop;
      }

      //
      // handle the LoadedImage protocol on the image handle.
      //
      Status = gtBS->HandleProtocol (
                       ImageHandle,
                       &gBlackBoxEfiLoadedImageProtocolGuid,
                       (VOID **) &LoadedImage
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.HandleProtocol()",
                       L"%a:%d: Status: %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto NextLoop;
      }

      //
      // change the LoadOption and then start image again.
      //
      LoadedImage->LoadOptions = &LoadOption;
      LoadedImage->LoadOptionsSize = sizeof (UINTN);

      Status = gtBS->StartImage (ImageHandle, NULL, NULL);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.StartImage()",
                       L"%a:%d: Status: %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto NextLoop;
      }

      //
      // check for protocol notify
      //
      if (ProtocolNotifyContext.ProtocolIndex == LoadOption) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gLoadedImageTestAssertionGuid012,
                     L"Loaded Image Protocol Test - test 1",
                     L"%a:%d: Protocol %d %s invoked",
                     __FILE__,
                     (UINTN)__LINE__,
                     LoadOption,
                     (AssertionType == EFI_TEST_ASSERTION_PASSED) ? L"is" : L"isn't"
                     );
      LoadOption++;

    }

NextLoop:

    if (ImageHandle != NULL) {
      if (Index > 1) {
        gtBS->UnloadImage (ImageHandle);
      }
    }

  }

Done:
  for (Index = 0; Index < 6; Index++) {
    gtBS->FreePool (FilePath[Index]);
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestLoadedImageTest2 (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_LOADED_IMAGE_PROTOCOL            *LoadedImage;
  UINT32                               ImageRevision;
  EFI_PHYSICAL_ADDRESS                 Address1;
  EFI_PHYSICAL_ADDRESS                 Address2;
  EFI_PHYSICAL_ADDRESS                 Address3;

  //
  // Init
  //
  LoadedImage = (EFI_LOADED_IMAGE_PROTOCOL*)ClientInterface;
  ImageRevision = EFI_LOADED_IMAGE_INFORMATION_REVISION;
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
  // verify the protocol members
  //
    if (LoadedImage->Revision == ImageRevision) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gLoadedImageTestAssertionGuid019,
                   L"Loaded Image Protocol Test - test 2",
                   L"%a:%d: Revision: 0x%x, expected: 0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   LoadedImage->Revision,
                   ImageRevision
                   );

  //
  // System Table is not NULL and points to valid position.
  //
  if (LoadedImage->SystemTable != NULL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gLoadedImageTestAssertionGuid013,
                 L"Loaded Image Protocol Test - test 2",
                 L"%a:%d: LoadedImage->SystemTable is 0x%x, gtST is 0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 LoadedImage->SystemTable,
                 gtST
                 );

  //
  // ImageBase is not NULL and ImageSize is not 0.
  //
  if ((LoadedImage->ImageBase != NULL) && (LoadedImage->ImageSize != 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gLoadedImageTestAssertionGuid015,
                 L"Loaded Image Protocol Test - test 2",
                 L"%a:%d: LoadedImage->ImageBase is 0x%x, LoadedImage->ImageSize is 0x%x",
                 __FILE__,
                 (UINTN)__LINE__,
                 LoadedImage->ImageBase,
                 LoadedImage->ImageSize
                 );

  //
  // ImageCodeType matches with the ImageDataType.
  //
  switch (LoadedImage->ImageCodeType) {
    case EfiLoaderCode:
      if (LoadedImage->ImageDataType == EfiLoaderData) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      break;

    case EfiBootServicesCode:
      if (LoadedImage->ImageDataType == EfiBootServicesData) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      break;

    case EfiRuntimeServicesCode:
      if (LoadedImage->ImageDataType == EfiRuntimeServicesData) {
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
                 gLoadedImageTestAssertionGuid016,
                 L"Loaded Image Protocol Test - test 2",
                 L"%a:%d: LoadedImage->ImageCodeType is %x, LoadedImage->ImageDataType is %x",
                 __FILE__,
                 (UINTN)__LINE__,
                 LoadedImage->ImageCodeType,
                 LoadedImage->ImageDataType
                 );

  //
  // If Unload() function is not NULL,
  // it should fall within the range of [ImageBase, ImageBase + ImageSize - 1]
  //
  if (LoadedImage->Unload != NULL) {

    Address1 = (EFI_PHYSICAL_ADDRESS)((UINTN)LoadedImage->Unload);
    Address2 = (EFI_PHYSICAL_ADDRESS)((UINTN)LoadedImage->ImageBase);
    Address3 = (EFI_PHYSICAL_ADDRESS)(UINTN)((((UINTN)LoadedImage->ImageBase + (UINTN)LoadedImage->ImageSize) - 1));

    if ((Address1 >= Address2)
        && (Address1 <= Address3)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gLoadedImageTestAssertionGuid017,
                   L"Loaded Image Protocol Test - test 2",
                   L"%a:%d: Unload is 0x%x, ImageBase is 0x%x, ImageSize is 0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   LoadedImage->Unload,
                   LoadedImage->ImageBase,
                   LoadedImage->ImageSize
                   );
  }


  return EFI_SUCCESS;
}

/**
 *  @brief This function is used to compose a device path of a file located at disk media.
 *  @see ReleaseInvalidHandle.
 */
EFI_STATUS
LoadedImageTestComposeSimpleFilePath (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib    OPTIONAL,
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL   *ProfileLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT EFI_DEVICE_PATH_PROTOCOL            **FilePath
  )
/*++
  The caller has the responsibility to free the FilePath
--*/
{
  EFI_STATUS                    Status;
  CHAR16                        *EntireFileName;
  CHAR16                        *FileNamePath;
  EFI_LOADED_IMAGE_PROTOCOL     *LoadImage;
  EFI_DEVICE_PATH_PROTOCOL      *DevicePath;

  Status = gtBS->HandleProtocol (
                   CurrentImageHandle,
                   &gBlackBoxEfiLoadedImageProtocolGuid,
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
  //Get system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &DevicePath,
                         &FileNamePath
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  EntireFileName = SctPoolPrint (L"%s\\%s\\%s", FileNamePath, DEPENDENCY_DIR_NAME, FileName);

  *FilePath = SctFileDevicePath (LoadImage->DeviceHandle, EntireFileName);

  SctFreePool (DevicePath);
  SctFreePool (FileNamePath);
  SctFreePool (EntireFileName);

  if (*FilePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}

VOID
TestNotifyFunction (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  )
{
  NOTIFY_CONTEXT    *ProtocolNotifyContext;
  UINTN             Index;
  EFI_STATUS        Status;
  UINTN             NoHandles;
  EFI_HANDLE        *HandleBuffer;

  ProtocolNotifyContext = (NOTIFY_CONTEXT*)Context;

  //
  // locate protocol according to the registration
  //
  for (Index = 0; Index < 6; Index++) {

    HandleBuffer = NULL;

    Status = gtBS->LocateHandleBuffer (
                     ByRegisterNotify,
                     NULL,
                     ProtocolNotifyContext->Registration[Index],
                     &NoHandles,
                     &HandleBuffer
                     );
    if (HandleBuffer != NULL) {
      gtBS->FreePool (HandleBuffer);
    }

    if (!EFI_ERROR (Status)) {
      ProtocolNotifyContext->ProtocolIndex = Index + 1;
      break;
    }
  }
}
