/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Dell Inc. All rights reserved.<BR>
  Copyright (c) 2021, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    FirmwareManagementBBTestConformance.c

Abstract:
    Firmware Management Protocol's conformance tests.

--*/

#define DEBUG_ALL                                0
#define DEBUG_GET_IMAGE_INFO                     0
#define DEBUG_GET_IMAGE                          0
#define DEBUG_SET_IMAGE                          0
#define DEBUG_CHECK_IMAGE                        0
#define DEBUG_SET_PACKAGE_INFO                   0

#include "SctLib.h"
#include "FirmwareManagementBBTestMain.h"

// ****************************************************************************
//   Support Routines
// ****************************************************************************

EFI_STATUS
CheckForSupportGetImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
CheckForSupportSetImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );


EFI_STATUS
CheckForSupportCheckImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
CheckForSupportSetPackageInfo (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

// ****************************************************************************
//   Check Points
// ****************************************************************************

EFI_STATUS
EFIAPI
BBTestGetImageInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestGetImageInfoConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestCheckImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestCheckImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestSetPackageInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestSetPackageInfoConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestSetPackageInfoConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestSetPackageInfoConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

// ****************************************************************************
//   Support Routines
// 
// 
// ****************************************************************************

// ****************************************************************************
//   Support Routine: Progress
// ****************************************************************************

EFI_STATUS
EFIAPI
Progress (
  IN UINTN                                       Completion
)
{
  return EFI_SUCCESS;
}

// ****************************************************************************
//   Support Routine: CheckForSupportGetImage
// ****************************************************************************

EFI_STATUS
CheckForSupportGetImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
)
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  UINT8                                          ImageIndex;
  VOID                                           *Image;
  UINTN                                          ImageSize;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceSupportGuid001;
  ResultMessageLabel = L"GetImage, function support check";

  ImageIndex = 1;
  Image = NULL;
  ImageSize = 0;

  //
  // Check if function is supported
  //

  Status = FirmwareManagement->GetImage ( 
                                 FirmwareManagement,
                                 ImageIndex,
                                 Image,
                                 &ImageSize
                                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (Status == EFI_UNSUPPORTED) {
    ResultMessageData = L"function is NOT supported";
  } else {
    ResultMessageData = L"function is supported.";
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Image != NULL) {
    gtBS->FreePool (Image);
  }

  if (Status == EFI_UNSUPPORTED) {
    return EFI_UNSUPPORTED;
  } else {
    return EFI_SUCCESS;
  }
}

// ****************************************************************************
//   Support Routine: CheckForSupportSetImage
// ****************************************************************************

EFI_STATUS
CheckForSupportSetImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
)
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  UINT8                                          ImageIndex;
  VOID                                           *Image;
  UINTN                                          ImageSize;
  CHAR16                                         *AbortReason;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceSupportGuid002;
  ResultMessageLabel = L"SetImage, function support check";

  ImageIndex = 1;
  Image = NULL;
  ImageSize = 0;
  AbortReason = NULL;

  //
  // Check if function is supported
  //

  Status = FirmwareManagement->SetImage ( 
                                 FirmwareManagement,
                                 ImageIndex,
                                 Image,
                                 ImageSize,
                                 NULL,  // VendorCode
                                 Progress,
                                 &AbortReason
                                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (Status == EFI_UNSUPPORTED) {
    ResultMessageData = L"function is NOT supported";
  } else {
    ResultMessageData = L"function is supported.";
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (AbortReason != NULL) {
    gtBS->FreePool (AbortReason);
  }

  if (Status == EFI_UNSUPPORTED) {
    return EFI_UNSUPPORTED;
  } else {
    return EFI_SUCCESS;
  }
}

// ****************************************************************************
//   Support Routine: CheckForSupportCheckImage
// ****************************************************************************

EFI_STATUS
CheckForSupportCheckImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
)
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  UINT8                                          ImageIndex;
  VOID                                           *Image;
  UINTN                                          ImageSize;
  UINT32                                         ImageUpdatable;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceSupportGuid003;
  ResultMessageLabel = L"CheckImage, function support check";

  ImageIndex = 1;
  Image = NULL;
  ImageSize = 0;

  //
  // Check if function is supported
  //

  Status = FirmwareManagement->CheckImage ( 
                                 FirmwareManagement,
                                 ImageIndex,
                                 Image,
                                 ImageSize,
                                 &ImageUpdatable
                                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (Status == EFI_UNSUPPORTED) {
    ResultMessageData = L"function is NOT supported";
  } else {
    ResultMessageData = L"function is supported.";
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Status == EFI_UNSUPPORTED) {
    return EFI_UNSUPPORTED;
  } else {
    return EFI_SUCCESS;
  }
}

// ****************************************************************************
//   Support Routine: CheckForSupportSetPackageInfo
// ****************************************************************************

EFI_STATUS
CheckForSupportSetPackageInfo (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
)
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  VOID                                           *Image;
  UINTN                                          ImageSize;
  VOID                                           *VendorCode;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceSupportGuid004;
  ResultMessageLabel = L"SetPackageInfo, function support check";

  Image = NULL;
  ImageSize = 0;
  VendorCode = NULL;
  PackageVersion = 0;
  PackageVersionName = NULL;

  //
  // Check if function is supported
  //

  Status = FirmwareManagement->SetPackageInfo (
                                 FirmwareManagement,
                                 Image,  
                                 ImageSize,
                                 VendorCode,
                                 PackageVersion,
                                 PackageVersionName
                                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (Status == EFI_UNSUPPORTED) {
    ResultMessageData = L"function is NOT supported";
  } else {
    ResultMessageData = L"function is supported.";
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Status == EFI_UNSUPPORTED) {
    return EFI_UNSUPPORTED;
  } else {
    return EFI_SUCCESS;
  }
}

// ****************************************************************************
//   Test Cases
// 
// 
// ****************************************************************************

/*
EFI_STATUS
EFIAPI
BBTestUnitTest (
  IN EFI_BB_TEST_PROTOCOL                        *This,
  IN VOID                                        *ClientInterface,
  IN EFI_TEST_LEVEL                              TestLevel,
  IN EFI_HANDLE                                  SupportHandle
  )
{
  return EFI_SUCCESS;
}
*/

// ****************************************************************************
//   Test Case: GetImageInfo
// ****************************************************************************
 
EFI_STATUS
EFIAPI
BBTestGetImageInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL                        *This,
  IN VOID                                        *ClientInterface,
  IN EFI_TEST_LEVEL                              TestLevel,
  IN EFI_HANDLE                                  SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL             *StandardLib;
  EFI_STATUS                                     Status;
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL               *FirmwareManagement;

  // 
  // Init
  //

  FirmwareManagement = (EFI_FIRMWARE_MANAGEMENT_PROTOCOL*)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Call check point(s)
  //

  BBTestGetImageInfoConformanceTestCheckpoint1 (StandardLib, FirmwareManagement);
  BBTestGetImageInfoConformanceTestCheckpoint2 (StandardLib, FirmwareManagement);

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Test Case: GetImage
// ****************************************************************************

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL                        *This,
  IN VOID                                        *ClientInterface,
  IN EFI_TEST_LEVEL                              TestLevel,
  IN EFI_HANDLE                                  SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL             *StandardLib;
  EFI_STATUS                                     Status;
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL               *FirmwareManagement;

  // 
  // Init
  //

  FirmwareManagement = (EFI_FIRMWARE_MANAGEMENT_PROTOCOL*)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Check if function is supported
  // 

  Status = CheckForSupportGetImage (StandardLib, FirmwareManagement);
  if (Status == EFI_UNSUPPORTED) {
    return Status;
  }

  //
  // Call check point(s)
  //

  BBTestGetImageConformanceTestCheckpoint1 (StandardLib, FirmwareManagement);
  BBTestGetImageConformanceTestCheckpoint2 (StandardLib, FirmwareManagement);
  BBTestGetImageConformanceTestCheckpoint3 (StandardLib, FirmwareManagement);
  BBTestGetImageConformanceTestCheckpoint4 (StandardLib, FirmwareManagement);
  
  return EFI_SUCCESS;
}

// ****************************************************************************
//   Test Case: SetImage
// ****************************************************************************

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL                        *This,
  IN VOID                                        *ClientInterface,
  IN EFI_TEST_LEVEL                              TestLevel,
  IN EFI_HANDLE                                  SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL             *StandardLib;
  EFI_STATUS                                     Status;
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL               *FirmwareManagement;

  // 
  // Init
  //

  FirmwareManagement = (EFI_FIRMWARE_MANAGEMENT_PROTOCOL*)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Check if function is supported
  // 

  Status = CheckForSupportSetImage (StandardLib, FirmwareManagement);
  if (Status == EFI_UNSUPPORTED) {
    return Status;
  }

  //
  // Call check point(s)
  //

  BBTestSetImageConformanceTestCheckpoint1 (StandardLib, FirmwareManagement);
  //BBTestSetImageConformanceTestCheckpoint2 (StandardLib, FirmwareManagement);
  BBTestSetImageConformanceTestCheckpoint3 (StandardLib, FirmwareManagement);
  BBTestSetImageConformanceTestCheckpoint4 (StandardLib, FirmwareManagement);
  
  return Status;
}

// ****************************************************************************
//   Test Case: CheckImage
// ****************************************************************************

EFI_STATUS
EFIAPI
BBTestCheckImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL                        *This,
  IN VOID                                        *ClientInterface,
  IN EFI_TEST_LEVEL                              TestLevel,
  IN EFI_HANDLE                                  SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL             *StandardLib;
  EFI_STATUS                                     Status;
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL               *FirmwareManagement;

  // 
  // Init
  //

  FirmwareManagement = (EFI_FIRMWARE_MANAGEMENT_PROTOCOL*)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Check if function is supported
  // 

  Status = CheckForSupportCheckImage (StandardLib, FirmwareManagement);
  if (Status == EFI_UNSUPPORTED) {
    return Status;
  }

  //
  // Call check point(s)
  //

  BBTestCheckImageConformanceTestCheckpoint1 (StandardLib, FirmwareManagement);
  BBTestCheckImageConformanceTestCheckpoint2 (StandardLib, FirmwareManagement);
  
  return Status;
}

// ****************************************************************************
//   Test Case: SetPackageInfo
// ****************************************************************************
 
EFI_STATUS
EFIAPI
BBTestSetPackageInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL                        *This,
  IN VOID                                        *ClientInterface,
  IN EFI_TEST_LEVEL                              TestLevel,
  IN EFI_HANDLE                                  SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL             *StandardLib;
  EFI_STATUS                                     Status;
  EFI_FIRMWARE_MANAGEMENT_PROTOCOL               *FirmwareManagement;

  // 
  // Init
  //

  FirmwareManagement = (EFI_FIRMWARE_MANAGEMENT_PROTOCOL*)ClientInterface;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Check if function is supported
  // 

  Status = CheckForSupportSetPackageInfo (StandardLib, FirmwareManagement);
  if (Status == EFI_UNSUPPORTED) {
    return Status;
  }

  //
  // Call check point(s)
  //

  BBTestSetPackageInfoConformanceTestCheckpoint1 (StandardLib, FirmwareManagement);
  BBTestSetPackageInfoConformanceTestCheckpoint2 (StandardLib, FirmwareManagement);
  BBTestSetPackageInfoConformanceTestCheckpoint3 (StandardLib, FirmwareManagement);
  BBTestSetPackageInfoConformanceTestCheckpoint4 (StandardLib, FirmwareManagement);
  
  return Status;
}

// ****************************************************************************
//   Check Points
// 
// 
// ****************************************************************************

// ****************************************************************************
//   Checkpoint: GetImageInfo, 1
// ****************************************************************************

/**
  This routine:
    - Calls function with valid parameters, except ImageInfoSize = 1.
      The function should return EFI_BUFFER_TOO_SMALL and ImageInfoSize > 1.
**/

EFI_STATUS
EFIAPI
BBTestGetImageInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid001;
  ResultMessageLabel = L"GetImageInfo, conformance checkpoint #1";
  ResultMessageData = L"correctly returned EFI_BUFFER_TOO_SMALL.";

  ImageInfo = NULL;
  PackageVersionName = NULL;

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }
  ImageInfoSize = 1;

  //
  // Check the data returned by the function
  //

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );

  if (Status != EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"failed to return EFI_BUFFER_TOO_SMALL.";
    goto Exit;
  }
  if (ImageInfoSize <= 1) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"failed to update *ImageInfoSize.";
  }

  //
  // Report the checkpoint result
  // 
 
Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (ImageInfo != NULL) {
    gtBS->FreePool (ImageInfo);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: GetImageInfo, 2
// ****************************************************************************

/**
  This routine:
    - Calls function with valid parameters, except &ImageInfoSize = NULL.
      The function should return EFI_INVALID_PARAMETER.
**/

EFI_STATUS
EFIAPI
BBTestGetImageInfoConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid002;
  ResultMessageLabel = L"GetImageInfo, conformance checkpoint #2";
  ResultMessageData = L"correctly returned EFI_INVALID_PARAMETER.";

  ImageInfo = NULL;
  PackageVersionName = NULL;

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  //
  // Check the data returned by the function
  //

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 NULL, // &ImageInfoSize
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );

  if (Status != EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"failed to return EFI_INVALID_PARAMETER.";
  }

  //
  // Report the checkpoint result
  // 
 
Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (ImageInfo != NULL) {
    gtBS->FreePool (ImageInfo);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: GetImage, 1
// ****************************************************************************

/**
  This routine:
    - Calls function with valid parameters, except ImageSize = 1.
      The function should return EFI_BUFFER_TOO_SMALL and ImageSize > 1.
**/

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;
  VOID                                           *BufferImage;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  VOID                                           *Image;
  UINTN                                          ImageSize;

  UINTN                                          i;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *p;
  UINTN                                          FunctionTested;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid003;
  ResultMessageLabel = L"GetImage, conformance checkpoint #1";

  BufferImageInfo = NULL;
  BufferImage = NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;
  FunctionTested = 0;

  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));

    if (((p->AttributesSupported & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) == 
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) &&
        ((p->AttributesSetting & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) ==
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED)) {
      continue;
    }
    if (p->Size == 0) {
      continue;
    }
    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }

    ImageSize = p->Size;
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageSize,
                     (VOID **) &Image
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit; 
    }
    BufferImage = Image;

    ImageSize = 1;
    FunctionTested++;
    Status = FirmwareManagement->GetImage ( 
                                   FirmwareManagement,
                                   p->ImageIndex,
                                   Image,
                                   &ImageSize
                                   );
    gtBS->FreePool (BufferImage);
    BufferImage = NULL;
    Image = NULL;

    //
    // Report the checkpoint result
    //

    if (Status != EFI_BUFFER_TOO_SMALL) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to return EFI_BUFFER_TOO_SMALL.";
      goto Exit; 
    }
    if (ImageInfoSize <= 1) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to update *ImageSize.";
      goto Exit;
    }
  }

  if (FunctionTested == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"test skipped - test case does not apply.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_BUFFER_TOO_SMALL.";
  }

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }
  if (BufferImage != NULL) {
      gtBS->FreePool (BufferImage);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: GetImage, 2
// ****************************************************************************

/**
  This routine:
    - Calls function with valid parameters, except Image = NULL.
      The function should return EFI_INVALID_PARAMETER.
**/

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  VOID                                           *Image;
  UINTN                                          ImageSize;

  UINTN                                          i;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *p;
  UINTN                                          FunctionTested;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid004;
  ResultMessageLabel = L"GetImage, conformance checkpoint #2";

  BufferImageInfo = NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;
  FunctionTested = 0;

  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));

    if (((p->AttributesSupported & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) == 
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) &&
        ((p->AttributesSetting & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) ==
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED)) {
      continue;
    }
    if (p->Size == 0) {
      continue;
    }
    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }

    // Use a sufficiently large buffer size to avoid EFI_BUFFER_TOO_SMALL.
    ImageSize = p->Size * 2;
    Image = NULL;
    FunctionTested++;
    Status = FirmwareManagement->GetImage ( 
                                   FirmwareManagement,
                                   p->ImageIndex,
                                   Image,
                                   &ImageSize
                                   );

    //
    // Report the checkpoint result
    //

    if (Status != EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to return EFI_INVALID_PARAMETER.";
      goto Exit; 
    }
  }

  if (FunctionTested == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"test skipped - test case does not apply.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_INVALID_PARAMETER.";
  }

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: GetImage, 3
// ****************************************************************************

/**
  This routine:
    - Calls function with valid parameters, except ImageIndex = 0 or
      ImageIndex = DescriptorCount + 1.
      The function should return EFI_INVALID_PARAMETER or EFI_NOT_FOUND.
**/

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;
  VOID                                           *BufferImage;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  VOID                                           *Image;
  UINTN                                          ImageSize;
  UINT8                                          ImageIndex;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid005;
  ResultMessageLabel = L"GetImage, conformance checkpoint #3";

  BufferImageInfo = NULL;
  BufferImage = NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;

  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  // Dummy image so as to fail on Image = NULL
  // Any size since the function should check for index before size
  ImageSize = 64;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageSize,
                   (VOID **) &Image
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit; 
  }
  BufferImage = Image;

  AssertionType = EFI_TEST_ASSERTION_FAILED;
  ResultMessageData = L"failed to return EFI_INVALID_PARAMETER or EFI_NOT_FOUND.";

  ImageIndex = 0;
  Status = FirmwareManagement->GetImage ( 
                                 FirmwareManagement,
                                 ImageIndex,
                                 Image,
                                 &ImageSize
                                 );
  if ((Status != EFI_INVALID_PARAMETER) && (Status != EFI_NOT_FOUND)) {
    goto Exit; 
  }

  if ((DescriptorCount + 1) != 0) {
    ImageIndex = DescriptorCount + 1;
    Status = FirmwareManagement->GetImage ( 
                                   FirmwareManagement,
                                   ImageIndex, 
                                   Image,
                                   &ImageSize
                                   );
    if ((Status != EFI_INVALID_PARAMETER) && (Status != EFI_NOT_FOUND)) {
      goto Exit; 
    }
  }

  //
  // Report the checkpoint result
  //

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  ResultMessageData = L"correctly returned EFI_INVALID_PARAMETER or EFI_NOT_FOUND.";

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }
   if (BufferImage != NULL) {
      gtBS->FreePool (BufferImage);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: GetImage, 4
// ****************************************************************************

/**
  This routine:
    - The function requires authentication.
    - Calls function with valid parameters, except Image has dummy 
      authentication data.     
      The function should return EFI_SECURITY_VIOLATION.
**/

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;
  VOID                                           *BufferImage;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  VOID                                           *Image;
  UINTN                                          ImageSize;
 
  UINTN                                          i;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *p;
  UINTN                                          FunctionTested;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid006;
  ResultMessageLabel = L"GetImage, conformance checkpoint #4";

  BufferImageInfo = NULL;
  BufferImage = NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;
  FunctionTested = 0;
  
  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));

    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
      continue;
    }
    if (p->Size == 0) {
      continue;
    }
    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }

    // Use a sufficiently large buffer size to avoid EFI_BUFFER_TOO_SMALL.
    ImageSize = p->Size * 2;
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageSize,
                     (VOID **) &Image
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit; 
    }
    BufferImage = Image;

    FunctionTested++;

    Status = FirmwareManagement->GetImage ( 
                                   FirmwareManagement,
                                   p->ImageIndex,
                                   Image,
                                   &ImageSize
                                   );
    gtBS->FreePool (BufferImage);
    BufferImage = NULL;
    Image = NULL;   

    //
    // Report the checkpoint result
    //

    if (Status != EFI_SECURITY_VIOLATION) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to return EFI_SECURITY_VIOLATION.";
      goto Exit;  
    }
  }

  if (FunctionTested == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"test skipped - test case does not apply.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_SECURITY_VIOLATION";
  }

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }
  if (BufferImage != NULL) {
    gtBS->FreePool (BufferImage);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: SetImage, 1
// ****************************************************************************

/**
  This routine:
    - Calls function with valid parameters, except Image = NULL.
      The function should return EFI_INVALID_PARAMETER.
**/

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  CHAR16                                         *AbortReason;

  VOID                                           *Image;
  UINTN                                          ImageSize;

  UINTN                                          i;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *p;
  UINTN                                          FunctionTested;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid007;
  ResultMessageLabel = L"SetImage, conformance checkpoint #1";

  BufferImageInfo = NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;
  AbortReason = NULL;
  FunctionTested = 0;

  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));

    if (((p->AttributesSupported & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) == 
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) &&
        ((p->AttributesSetting & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) ==
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED)) {
      continue;
    }
    if (p->Size == 0) {
      continue;
    }
    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }

    ImageSize = p->Size;
    Image = NULL;
    FunctionTested++;
    Status = FirmwareManagement->SetImage ( 
                                   FirmwareManagement,
                                   p->ImageIndex,
                                   Image,
                                   ImageSize,
                                   NULL,  // VendorCode
                                   Progress,
                                   &AbortReason
                                   );

    //
    // Report the checkpoint result
    //

    if (Status != EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to return EFI_INVALID_PARAMETER.";
      goto Exit; 
    }
  }

  if (FunctionTested == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"test skipped - test case does not apply.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_INVALID_PARAMETER.";
  }

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }
  if (AbortReason != NULL) {
    gtBS->FreePool (AbortReason);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: SetImage, 2
// ****************************************************************************

/**
  This routine:
    - Calls function with valid parameters, except Image is a dummy image.
      The function should return EFI_INVALID_PARAMETER or EFI_ABORTED.
**/

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;
  VOID                                           *BufferImage;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  CHAR16                                         *AbortReason;

  VOID                                           *Image;
  UINTN                                          ImageSize;

  UINTN                                          i;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *p;
  UINTN                                          FunctionTested;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid008;
  ResultMessageLabel = L"SetImage, conformance checkpoint #2";

  BufferImageInfo = NULL;
  BufferImage = NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;
  AbortReason = NULL;
  FunctionTested = 0;

  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));

    if (((p->AttributesSupported & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) == 
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) &&
        ((p->AttributesSetting & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) ==
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED)) {
      continue;
    }
    if (p->Size == 0) {
      continue;
    }
    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }

    ImageSize = p->Size;
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageSize,
                     (VOID **) &Image
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    BufferImage = Image;
    FunctionTested++;
    Status = FirmwareManagement->SetImage ( 
                                   FirmwareManagement,
                                   p->ImageIndex,
                                   Image,
                                   ImageSize,
                                   NULL,  // VendorCode
                                   Progress,
                                   &AbortReason
                                   );
    gtBS->FreePool (BufferImage);
    BufferImage = NULL;
    Image = NULL;

    //
    // Report the checkpoint result
    //

    if ((Status != EFI_INVALID_PARAMETER) && (Status != EFI_ABORTED)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to return EFI_INVALID_PARAMETER or EFI_ABORTED.";
      goto Exit; 
    }
  }

  if (FunctionTested == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"test skipped - test case does not apply.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_INVALID_PARAMETER or EFI_ABORTED.";
  }

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }
  if (BufferImage != NULL) {
    gtBS->FreePool (BufferImage);
  }
  if (AbortReason != NULL) {
    gtBS->FreePool (AbortReason);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: SetImage, 3
// ****************************************************************************

/**
  This routine:
    - Calls function with valid parameters, except ImageIndex = 0 or
      ImageIndex = DescriptorCount + 1.
      The function should return EFI_INVALID_PARAMETER or EFI_ABORTED.
**/

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;
  VOID                                           *BufferImage;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  CHAR16                                         *AbortReason;

  VOID                                           *Image;
  UINTN                                          ImageSize;
  UINT8                                          ImageIndex;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid009;
  ResultMessageLabel = L"SetImage, conformance checkpoint #3";

  BufferImageInfo = NULL;
  BufferImage=NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;
  AbortReason = NULL;

  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  // Dummy image so as to fail on Image = NULL
  // Any size since the function should check for index before size
  ImageSize = 64;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageSize,
                   (VOID **) &Image
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit; 
  }
  BufferImage = Image;

  AssertionType = EFI_TEST_ASSERTION_FAILED;
  ResultMessageData = L"failed to return EFI_INVALID_PARAMETER or EFI_ABORTED.";

  ImageIndex = 0;
  Status = FirmwareManagement->SetImage ( 
                                 FirmwareManagement,
                                 ImageIndex,
                                 Image,
                                 ImageSize,
                                 NULL,  // VendorCode
                                 Progress,
                                 &AbortReason
                                 );
  if ((Status != EFI_INVALID_PARAMETER) && (Status != EFI_ABORTED)) {
    goto Exit; 
  }

  if ((DescriptorCount + 1) != 0) {
    ImageIndex = DescriptorCount + 1;
    Status = FirmwareManagement->SetImage ( 
                                   FirmwareManagement,
                                   ImageIndex, 
                                   Image,
                                   ImageSize,
                                   NULL,  // Vendorcode
                                   Progress,
                                   &AbortReason
                                   );
    if ((Status != EFI_INVALID_PARAMETER) && (Status != EFI_ABORTED)) {
      goto Exit; 
    }
  }

  //
  // Report the checkpoint result
  //

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  ResultMessageData = L"correctly returned EFI_INVALID_PARAMETER or EFI_ABORTED.";

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }
  if (BufferImage != NULL) {
      gtBS->FreePool (BufferImage);
  }
  if (AbortReason != NULL) {
    gtBS->FreePool (AbortReason);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: SetImage, 4
// ****************************************************************************

/**
  This routine:
    - The function requires authentication.
    - Calls function with valid parameters, except Image has dummy 
      authentication data.     
      The function should return EFI_SECURITY_VIOLATION.
**/

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;
  VOID                                           *BufferImage;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  CHAR16                                         *AbortReason;

  VOID                                           *Image;
  UINTN                                          ImageSize;
 
  UINTN                                          i;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *p;
  UINTN                                          FunctionTested;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid010;
  ResultMessageLabel = L"SetImage, conformance checkpoint #4";

  BufferImageInfo = NULL;
  BufferImage = NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;
  AbortReason = NULL;
  FunctionTested = 0;
  
  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));

    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
      continue;
    }
    if (p->Size == 0) {
      continue;
    }
    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }

    ImageSize = p->Size;
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageSize,
                     (VOID **) &Image
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    BufferImage = Image;
    FunctionTested++;
    Status = FirmwareManagement->SetImage ( 
                                   FirmwareManagement,
                                   p->ImageIndex,
                                   Image,
                                   ImageSize,
                                   NULL,  // VendorCode
                                   Progress,
                                   &AbortReason
                                   );
    gtBS->FreePool (BufferImage);
    BufferImage = NULL;
    Image = NULL;

    //
    // Report the checkpoint result
    //

    if (Status != EFI_SECURITY_VIOLATION) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to return EFI_SECURITY_VIOLATION.";
      goto Exit;  
    }
  }

  if (FunctionTested == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"test skipped - test case does not apply.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_SECURITY_VIOLATION";
  }

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }
  if (BufferImage != NULL) {
    gtBS->FreePool (BufferImage);
  }
  if (AbortReason != NULL) {
    gtBS->FreePool (AbortReason);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: CheckImage, 1
// ****************************************************************************

/**
  This routine:
    - Calls function with valid parameters, except Image = NULL.
      The function should return EFI_INVALID_PARAMETER.
**/

EFI_STATUS
EFIAPI
BBTestCheckImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  UINT32                                         ImageUpdatable;

  VOID                                           *Image;
  UINTN                                          ImageSize;

  UINTN                                          i;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *p;
  UINTN                                          FunctionTested;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid011;
  ResultMessageLabel = L"CheckImage, conformance checkpoint #1";

  BufferImageInfo = NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;
  FunctionTested = 0;

  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));

    if (((p->AttributesSupported & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) == 
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) &&
        ((p->AttributesSetting & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) ==
          IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED)) {
      continue;
    }
    if (p->Size == 0) {
      continue;
    }
    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }

    ImageSize = p->Size;
    Image = NULL;
    FunctionTested++;
    Status = FirmwareManagement->CheckImage ( 
                                   FirmwareManagement,
                                   p->ImageIndex,
                                   Image,
                                   ImageSize,
                                   &ImageUpdatable
                                   );

    //
    // Report the checkpoint result
    //

    if (Status != EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to return EFI_INVALID_PARAMETER.";
      goto Exit; 
    }
  }

  if (FunctionTested == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"test skipped - test case does not apply.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_INVALID_PARAMETER.";
  }

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: CheckImage, 2
// ****************************************************************************

/**
  This routine:
    - The function requires authentication.
    - Calls function with valid parameters, except Image has dummy 
      authentication data.     
      The function should return EFI_SECURITY_VIOLATION.
**/

EFI_STATUS
EFIAPI
BBTestCheckImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *BufferImageInfo;
  VOID                                           *BufferImage;

  UINTN                                          ImageInfoSize;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *ImageInfo;
  UINT32                                         DescriptorVersion;
  UINT8                                          DescriptorCount;
  UINTN                                          DescriptorSize;
  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;

  UINT32                                         ImageUpdatable;

  VOID                                           *Image;
  UINTN                                          ImageSize;

  UINTN                                          i;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *p;
  UINTN                                          FunctionTested;
  EFI_FIRMWARE_IMAGE_AUTHENTICATION              *EFIA;
  EFI_GUID                                       gEfiCertPkcs7Guid;
  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid012;
  gEfiCertPkcs7Guid = gFirmwareManagementBBTestConformanceSupportGuid005;
  ResultMessageLabel = L"CheckImage, conformance checkpoint #2";

  BufferImageInfo = NULL;
  BufferImage = NULL;
  ImageInfo = NULL;
  Image = NULL;
  PackageVersionName = NULL;
  FunctionTested = 0;

  // Use a sufficiently large buffer to obtain EFI_SUCCESS,
  // since some implementation does NOT correctly return EFI_BUFFER_TOO_SMALL.
  // Check for EFI_BUFFER_TOO_SMALL in another conformance test.

  ImageInfoSize = (sizeof (EFI_FIRMWARE_IMAGE_DESCRIPTOR)) * 20;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ImageInfoSize,
                   (VOID **) &ImageInfo
                   );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  Status = FirmwareManagement->GetImageInfo ( 
                                 FirmwareManagement,
                                 &ImageInfoSize,
                                 ImageInfo,
                                 &DescriptorVersion,
                                 &DescriptorCount,
                                 &DescriptorSize,
                                 &PackageVersion,
                                 &PackageVersionName
                                 );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    gtBS->FreePool (ImageInfo);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageInfoSize,
                     (VOID **) &ImageInfo
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }
    Status = FirmwareManagement->GetImageInfo ( 
                                   FirmwareManagement,
                                   &ImageInfoSize,
                                   ImageInfo,
                                   &DescriptorVersion,
                                   &DescriptorCount,
                                   &DescriptorSize,
                                   &PackageVersion,
                                   &PackageVersionName
                                   );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      BufferImageInfo = ImageInfo;
      goto Exit;
    }
  } 
  BufferImageInfo = ImageInfo;

  if (DescriptorSize == 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"*DescriptorSize is 0.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  
  if ((DescriptorCount * DescriptorSize) > ImageInfoSize) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"((*DescriptorCount) * (*DescriptorSize)) > *ImageInfoSize.";
    goto Exit;  // Note the Status = EFI_SUCCESS
  }  

  //
  // Check the data returned by the function
  //

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));

    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
      continue;
    }
    if (p->Size == 0) {
      continue;
    }
    if ((p->AttributesSupported & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }
    if ((p->AttributesSetting & IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) != IMAGE_ATTRIBUTE_IMAGE_UPDATABLE) {
      continue;
    }

    ImageSize = p->Size;
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     ImageSize,
                     (VOID **) &Image
                     );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"test case initialization failure.";
      goto Exit;
    }

    EFIA                                = Image;
    EFIA->AuthInfo.Hdr.dwLength         = sizeof(WIN_CERTIFICATE_UEFI_GUID)+0x10;
    EFIA->AuthInfo.Hdr.wRevision        = 0x0200;
    EFIA->AuthInfo.Hdr.wCertificateType = WIN_CERT_TYPE_EFI_GUID;
    for (i=0; i<sizeof(EFI_GUID); ((UINT8*)&EFIA->AuthInfo.CertType)[i]=((UINT8*)&gEfiCertPkcs7Guid)[i], i++);

    BufferImage = Image;
    FunctionTested++;
    Status = FirmwareManagement->CheckImage ( 
                                   FirmwareManagement,
                                   p->ImageIndex,
                                   Image,
                                   ImageSize,
                                   &ImageUpdatable
                                   );
    gtBS->FreePool (BufferImage);
    BufferImage = NULL;
    Image = NULL;

    //
    // Report the checkpoint result
    //

    if (Status != EFI_SECURITY_VIOLATION) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to return EFI_SECURITY_VIOLATION.";
      goto Exit;  
    }
  }

  if (FunctionTested == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"test skipped - test case does not apply.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_SECURITY_VIOLATION";
  }

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }
  if (BufferImage != NULL) {
    gtBS->FreePool (BufferImage);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: SetPackageInfo, 1
// ****************************************************************************

/**
  This routine:
    - Gets PackageVersionNameMaxLen.
    - Calls function with valid parameters, except PackageVersionName is longer
      than the value returned in PackageVersionNameLen.
      The function should return EFI_INVALID_PARAMETER.
**/

EFI_STATUS
EFIAPI
BBTestSetPackageInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;
  UINT32                                         PackageVersionNameMaxLen;
  UINT64                                         AttributesSupported;
  UINT64                                         AttributesSetting;

  CHAR16                                         *TestName;
  UINT32                                         TestNameLength;

  UINTN                                          i;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid013;
  ResultMessageLabel = L"SetPackageInfo, function checkpoint #1";

  PackageVersionName = NULL;
  TestName = NULL;

  //
  // Get PackageVersionNameMaxLen
  //

  Status = FirmwareManagement->GetPackageInfo (
                                 FirmwareManagement,
                                 &PackageVersion,
                                 &PackageVersionName,
                                 &PackageVersionNameMaxLen,
                                 &AttributesSupported,
                                 &AttributesSetting
                                 );
  if (Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  ResultMessageData = L"test skipped - test case does not apply.";
  if (PackageVersionNameMaxLen == 0) {
    goto Exit;
  }
  if (((AttributesSupported & PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) == 
        PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) &&
      ((AttributesSetting & PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) ==
        PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED)) {
    goto Exit;
  }
  if ((AttributesSupported & PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) != 
       PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) {
    goto Exit;
  }
  if ((AttributesSetting & PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) != 
       PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) {
    goto Exit;
  }

  //
  // Check the data returned by the function
  //

  gtBS->FreePool (PackageVersionName);
  PackageVersionName = NULL;
  TestNameLength = PackageVersionNameMaxLen + 1;
  Status = gtBS->AllocatePool (
                  EfiBootServicesData,
                  TestNameLength * 2,  // Unicode
                  (VOID **) &TestName
                  );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }
  for (i = 0; i < (TestNameLength - 1); i++) {
    TestName[i] = L' ';
  }
  TestName[i] = L'\0';
  Status = FirmwareManagement->SetPackageInfo (
                                 FirmwareManagement,
                                 NULL,  // Image
                                 0,  // ImageSize
                                 NULL,  // VendorCode
                                 0x01010101, // Dummy PackageVersion
                                 TestName
                                 );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_INVALID_PARAMETER.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"failed to return EFI_INVALID_PARAMETER.";
  }

  //
  // Report the checkpoint result
  // 
 
Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (TestName != NULL) {
    gtBS->FreePool (TestName);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: SetPackageInfo, 2
// ****************************************************************************

/**
  This routine:
    - The function requires authentication.
    - Calls function with valid parameters, except Image is NULL.
      The function should return EFI_SECURITY_VIOLATION.
**/

EFI_STATUS
EFIAPI
BBTestSetPackageInfoConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;
  UINT32                                         PackageVersionNameMaxLen;
  UINT64                                         AttributesSupported;
  UINT64                                         AttributesSetting;

  VOID                                           *Image;
  UINTN                                          ImageSize;
  
  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid014;
  ResultMessageLabel = L"SetPackageInfo, function checkpoint #2";

  PackageVersionName = NULL;

  //
  // Get PackageVersionNameMaxLen
  //

  Status = FirmwareManagement->GetPackageInfo (
                                 FirmwareManagement,
                                 &PackageVersion,
                                 &PackageVersionName,
                                 &PackageVersionNameMaxLen,
                                 &AttributesSupported,
                                 &AttributesSetting
                                 );
  if (Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  ResultMessageData = L"test skipped - test case does not apply.";
  if ((AttributesSupported & PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
    goto Exit;
  }
  if ((AttributesSetting & PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
    goto Exit;
  }
  if ((AttributesSupported & PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) != 
       PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) {
    goto Exit;
  }
  if ((AttributesSetting & PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) != 
       PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) {
    goto Exit;
  }

  //
  // Check the data returned by the function
  //

  Image = NULL;
  ImageSize = 64;  // Dummy
  Status = FirmwareManagement->SetPackageInfo (
                                 FirmwareManagement,
                                 Image,
                                 ImageSize,
                                 NULL,  // VendorCode
                                 PackageVersion,
                                 PackageVersionName
                                 );

  if (Status == EFI_SECURITY_VIOLATION) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_SECURITY_VIOLATION.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"failed to return EFI_SECURITY_VIOLATION.";
  }

  //
  // Report the checkpoint result
  // 

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: SetPackageInfo, 3
// ****************************************************************************

/**
  This routine:
    - The function requires authentication.
    - Calls function with valid parameters, except ImageSize is 0.
      The function should return EFI_SECURITY_VIOLATION.
**/

EFI_STATUS
EFIAPI
BBTestSetPackageInfoConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;
  UINT32                                         PackageVersionNameMaxLen;
  UINT64                                         AttributesSupported;
  UINT64                                         AttributesSetting;

  VOID                                           *Image;
  UINTN                                          ImageSize;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid015;
  ResultMessageLabel = L"SetPackageInfo, function checkpoint #3";

  PackageVersionName = NULL;
  Image = NULL;

  //
  // Get PackageVersionNameMaxLen
  //

  Status = FirmwareManagement->GetPackageInfo (
                                 FirmwareManagement,
                                 &PackageVersion,
                                 &PackageVersionName,
                                 &PackageVersionNameMaxLen,
                                 &AttributesSupported,
                                 &AttributesSetting
                                 );
  if (Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  ResultMessageData = L"test skipped - test case does not apply.";
  if ((AttributesSupported & PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
    goto Exit;
  }
  if ((AttributesSetting & PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
    goto Exit;
  }
  if ((AttributesSupported & PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) != 
       PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) {
    goto Exit;
  }
  if ((AttributesSetting & PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) != 
       PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) {
    goto Exit;
  }

  //
  // Check the data returned by the function
  //

  Status = gtBS->AllocatePool (
                EfiBootServicesData,
                64,  // Dummy
                (VOID **) &Image
                );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }
  ImageSize = 0;
  Status = FirmwareManagement->SetPackageInfo (
                                 FirmwareManagement,
                                 Image,  
                                 ImageSize,
                                 NULL,  // VendorCode
                                 PackageVersion,
                                 PackageVersionName
                                 );

  if (Status == EFI_SECURITY_VIOLATION) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_SECURITY_VIOLATION.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"failed to return EFI_SECURITY_VIOLATION.";
  }

  //
  // Report the checkpoint result
  // 

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (Image != NULL) {
    gtBS->FreePool (Image);
  }

  return EFI_SUCCESS;
}

// ****************************************************************************
//   Checkpoint: SetPackageInfo, 4
// ****************************************************************************

/**
  This routine:
    - The function requires authentication.
    - Calls function with valid parameters, except Image has a dummy 
      authentication data.
      The function should return EFI_SECURITY_VIOLATION.
**/

EFI_STATUS
EFIAPI
BBTestSetPackageInfoConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  )
{
  EFI_STATUS                                     Status;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_GUID                                       TestGuid;
  CHAR16                                         *ResultMessageLabel;
  CHAR16                                         *ResultMessageData;

  UINT32                                         PackageVersion;
  CHAR16                                         *PackageVersionName;
  UINT32                                         PackageVersionNameMaxLen;
  UINT64                                         AttributesSupported;
  UINT64                                         AttributesSetting;

  VOID                                           *Image;
  UINTN                                          ImageSize;

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestConformanceAssertionGuid016;
  ResultMessageLabel = L"SetPackageInfo, function checkpoint #4";

  PackageVersionName = NULL;
  Image = NULL;
  ImageSize = 64;

  //
  // Get PackageVersionNameMaxLen
  //

  Status = FirmwareManagement->GetPackageInfo (
                                 FirmwareManagement,
                                 &PackageVersion,
                                 &PackageVersionName,
                                 &PackageVersionNameMaxLen,
                                 &AttributesSupported,
                                 &AttributesSetting
                                 );
  if (Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  ResultMessageData = L"test skipped - test case does not apply.";
  if ((AttributesSupported & PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
    goto Exit;
  }
  if ((AttributesSetting & PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) != PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED) {
    goto Exit;
  }
  if ((AttributesSupported & PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) != 
       PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) {
    goto Exit;
  }
  if ((AttributesSetting & PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) != 
       PACKAGE_ATTRIBUTE_VERSION_UPDATABLE) {
    goto Exit;
  }

  //
  // Check the data returned by the function
  //

  Status = gtBS->AllocatePool (
                EfiBootServicesData,
                ImageSize,
                (VOID **) &Image
                );
  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"test case initialization failure.";
    goto Exit;
  }
  Status = FirmwareManagement->SetPackageInfo (
                                 FirmwareManagement,
                                 Image,  
                                 ImageSize,
                                 NULL,  // VendorCode
                                 PackageVersion,
                                 PackageVersionName
                                 );

  if (Status == EFI_SECURITY_VIOLATION) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_SECURITY_VIOLATION.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"failed to return EFI_SECURITY_VIOLATION.";
  }

  //
  // Report the checkpoint result
  // 

Exit:
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 TestGuid,
                 ResultMessageLabel,
                 L"Result - %s\n%a:%d: Status - %r",
                 ResultMessageData,
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (PackageVersionName != NULL) {
    gtBS->FreePool (PackageVersionName);
  }
  if (Image != NULL) {
    gtBS->FreePool (Image);
  }

  return EFI_SUCCESS;
}

