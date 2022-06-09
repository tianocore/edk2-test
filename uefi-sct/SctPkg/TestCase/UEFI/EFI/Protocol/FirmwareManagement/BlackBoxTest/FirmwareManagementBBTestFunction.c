/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Dell Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    FirmwareManagementBBTestFunction.c

Abstract:
    Firmware Management Protocol's function tests.

--*/

#define DEBUG_ALL                                0
#define DEBUG_GET_IMAGE_INFO                     1
#define DEBUG_GET_IMAGE                          0
#define DEBUG_GET_PACKAGE_INFO                   1


#include "SctLib.h"
#include "FirmwareManagementBBTestMain.h"

// ****************************************************************************
//   Check Points
// ****************************************************************************

EFI_STATUS
EFIAPI
BBTestGetImageInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestGetImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

EFI_STATUS
EFIAPI
BBTestGetPackageInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL          *StandardLib,
  IN EFI_FIRMWARE_MANAGEMENT_PROTOCOL            *FirmwareManagement
  );

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
BBTestGetImageInfoFunctionTest (
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

  BBTestGetImageInfoFunctionTestCheckpoint1 (StandardLib, FirmwareManagement);
  
  return EFI_SUCCESS;
}

// ****************************************************************************
// Test Case: GetImage
// ****************************************************************************

EFI_STATUS
EFIAPI
BBTestGetImageFunctionTest (
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

  BBTestGetImageFunctionTestCheckpoint1 (StandardLib, FirmwareManagement);
  
  return EFI_SUCCESS;
}

// ****************************************************************************
//   Test Case: GetPackageInfo
// ****************************************************************************
 
EFI_STATUS
EFIAPI
BBTestGetPackageInfoFunctionTest (
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

  BBTestGetPackageInfoFunctionTestCheckpoint1 (StandardLib, FirmwareManagement);
  
  return EFI_SUCCESS;
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
    - Calls function with all valid parameters.
      The function should return EFI_SUCCESS.
    - Checks DescriptorSize is 0.
    - Checks (DescriptorCount * DescriptorSize) is <= ImageInfoSize. 
    - Checks DescriptorVersion is == 1.
    - Checks ImageIndex is between 1 and DescriptorCount.
    - Checks AttributesSupported has no bits set beyond bit3.
    - Checks AttribtuesSetting has no bits set beyond bit3.
    - Checks Compatibilities bit1 thru bit15 are 0s.
**/

EFI_STATUS
EFIAPI
BBTestGetImageInfoFunctionTestCheckpoint1 (
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

  CHAR16*                                        Attribute[4];

  UINTN                                          i;
  EFI_FIRMWARE_IMAGE_DESCRIPTOR                  *p;

#if (DEBUG_ALL || DEBUG_GET_IMAGE_INFO)

  CHAR16                                         *BitField;
  CHAR16                                         *BitSetting;

  UINT64                                         j;
  UINTN                                          k;

#endif

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestFunctionAssertionGuid001;
  ResultMessageLabel = L"GetImageInfo, function checkpoint #1";

  BufferImageInfo = NULL;
  ImageInfo = NULL;
  PackageVersionName = NULL;

  Attribute[0] = L"Image Updatable";
  Attribute[1] = L"Reset Required";
  Attribute[2] = L"Authentication Required";
  Attribute[3] = L"In Use";

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
  }

  //
  // Check the data returned by the function
  //

  BufferImageInfo = ImageInfo;

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_SUCCESS.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"failed to return EFI_SUCCESS.";
    goto Exit;
  }

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

  if (DescriptorVersion != 1) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
    ResultMessageData = L"*DescriptorVersion != 1.";
    goto Exit;
  }

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));

    if (p->ImageIndex > DescriptorCount) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
      ResultMessageData = L"ImageIndex is beyond DescriptorCount.";
      goto Exit; 
    }
 
    if ((p->AttributesSupported & 0xFFFFFFFFFFFFFFF0) != 0) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
      ResultMessageData = L"AttributesSupported has bit(s) set beyond bit3.";
      goto Exit; 
    }

    if ((p->AttributesSetting & 0xFFFFFFFFFFFFFFF0) != 0) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
      ResultMessageData = L"AttributesSetting has bit(s) set beyond bit3.";
      goto Exit; 
    }

    if ((p->Compatibilities & 0x000000000000FFFE) !=0) {
      AssertionType = EFI_TEST_ASSERTION_WARNING;
      ResultMessageData = L"Compatibilities have bit(s) set between bit1 and bit15.";
      goto Exit; 
    }
  }

#if (DEBUG_ALL || DEBUG_GET_IMAGE_INFO)

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_QUIET,
                 L"Firmware Image Info Header: \n"
                 L"  - *ImageInfoSize = %x\n"
                 L"  - *DescriptorVersion = %x\n"
                 L"  - *DescriptorCount = %x\n"
                 L"  - *DescriptorSzie = %x\n"
                 L"  - *PackageVersion = %08x\n"
                 L"  - **PackageVersionName = %s\n",
                 ImageInfoSize,
                 DescriptorVersion,
                 DescriptorCount,
                 DescriptorSize,
                 PackageVersion,
                 PackageVersionName
                 );

  for (i = 0; i < DescriptorCount; i++) {
    p = (EFI_FIRMWARE_IMAGE_DESCRIPTOR *) (((UINT8 *) ImageInfo) + (i * DescriptorSize));
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_QUIET,
                   L"Descriptor Index = %x:\n"
                   L"  - ImageTypeId = %08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x",
                   p->ImageIndex,
                   p->ImageTypeId.Data1,
                   p->ImageTypeId.Data2,
                   p->ImageTypeId.Data3,
                   p->ImageTypeId.Data4[0],
                   p->ImageTypeId.Data4[1],
                   p->ImageTypeId.Data4[2],
                   p->ImageTypeId.Data4[3],
                   p->ImageTypeId.Data4[4],
                   p->ImageTypeId.Data4[5],
                   p->ImageTypeId.Data4[6],
                   p->ImageTypeId.Data4[7]
                   );
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_QUIET,
                   L"  - ImageId = %016X\n"
                   L"  - *ImageIdName = %s\n"
                   L"  - Version = %08x\n"
                   L"  - *VersionName = %s\n"
                   L"  - Size = %x",
                   p->ImageId,
                   p->ImageIdName,
                   p->Version,
                   p->VersionName,
                   p->Size
                   );
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_QUIET,
                   L"  - AttributesSupported = %016x\n"
                   L"  - AttributesSetting   = %016x",
                   p->AttributesSupported,
                   p->AttributesSetting
                   );
    for (j = 1, k = 0; j <= IMAGE_ATTRIBUTE_IN_USE; j = SctLShiftU64(j, 1), k++) {
      BitField = Attribute[k];
      if ((p->AttributesSupported & j) != j) {
        BitSetting = L"Not Supported";
      } else if ((p->AttributesSetting & j) == j) {
        BitSetting = L"Yes";
      } else {
        BitSetting = L"No";
      }
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_QUIET,
                     L"    - %s = %s",
                     BitField,
                     BitSetting
                     );
    }
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_QUIET,
                   L"  - Compatibilities = %016x\n",
                   p->Compatibilities
                   );
  }

#endif

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
  if (BufferImageInfo != NULL) {
    gtBS->FreePool (BufferImageInfo);
  }

  return EFI_SUCCESS;
} 

// ****************************************************************************
//   Checkpoint: GetImage, 1
// ****************************************************************************

/**
  This routine:
    - Calls function with all valid parameters.
      The function should return EFI_SUCCESS or EFI_UNSUPPORTED.
**/

EFI_STATUS
EFIAPI
BBTestGetImageFunctionTestCheckpoint1 (
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
  TestGuid = gFirmwareManagementBBTestFunctionAssertionGuid002;
  ResultMessageLabel = L"GetImage, function checkpoint #1";

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

    FunctionTested++;
    Status = FirmwareManagement->GetImage ( 
                                   FirmwareManagement,
                                   p->ImageIndex,
                                   Image,
                                   &ImageSize
                                   );

    if (Status == EFI_BUFFER_TOO_SMALL) {
      gtBS->FreePool (Image);
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
    }
    BufferImage = Image;

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

    if ((Status != EFI_SUCCESS) && (Status != EFI_UNSUPPORTED)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      ResultMessageData = L"failed to return EFI_SUCCESS or EFI_UNSUPPORTED.";
      goto Exit;  
    }
  }

  if (FunctionTested == 0) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"test skipped - test case does not apply.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_SUCCESS or EFI_UNSUPPORTED.";
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
//   Checkpoint: GetPackageInfo, 1
// ****************************************************************************

/**
  This routine:
    - Calls function with all valid parameters.
      The function should return EFI_SUCCESS or EFI_UNSUPPORTED.
    - Checks AttributesSupported has no bits set beyond bit2.
    - Checks AttributesSetting has no bits set beyond bit2.
**/

EFI_STATUS
EFIAPI
BBTestGetPackageInfoFunctionTestCheckpoint1 (
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
                                                                   
  CHAR16*                                        Attribute[3];

#if (DEBUG_ALL || DEBUG_GET_PACKAGE_INFO)

  CHAR16                                         *BitField;
  CHAR16                                         *BitSetting;

  UINT64                                         j;
  UINTN                                          k;

#endif

  //
  // Init
  //

  Status = EFI_SUCCESS;
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  TestGuid = gFirmwareManagementBBTestFunctionAssertionGuid003;
  ResultMessageLabel = L"GetPackageInfo, function checkpoint #1";

  PackageVersionName = NULL;

  Attribute[0] = L"Version Updatable";
  Attribute[1] = L"Reset Required";
  Attribute[2] = L"Authentication Required";

  //
  // Check the data returned by the function
  //

  Status = FirmwareManagement->GetPackageInfo (
                                 FirmwareManagement,
                                 &PackageVersion,
                                 &PackageVersionName,
                                 &PackageVersionNameMaxLen,
                                 &AttributesSupported,
                                 &AttributesSetting
                                 );

  if ((Status == EFI_SUCCESS) || (Status == EFI_UNSUPPORTED)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    ResultMessageData = L"correctly returned EFI_SUCCESS or EFI_UNSUPPORTED.";
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    ResultMessageData = L"failed to return EFI_SUCCESS or EFI_UNSUPPORTED.";
    goto Exit;
  }

#if (DEBUG_ALL || DEBUG_GET_PACKAGE_INFO)

  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_QUIET,
                 L"Firmware Package Info: \n"
                 L"  - *PackageVersion = %08x\n"
                 L"  - **PackageVersionName = %s\n"
                 L"  - *PackageVersionNameMaxLen = %08x",
                 PackageVersion,
                 PackageVersionName,
                 PackageVersionNameMaxLen
                );
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_QUIET,
                 L"  - *AttributesSupported = %016x\n"
                 L"  - *AttributesSetting   = %016x",
                 AttributesSupported,
                 AttributesSetting
                 );
  for (j = 1, k = 0; j <= PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED; j = SctLShiftU64(j, 1), k++) {
    BitField = Attribute[k];
    if ((AttributesSupported & j) != j) {
      BitSetting = L"Not Supported";
    } else if ((AttributesSetting & j) == j) {
      BitSetting = L"Yes";
    } else {
      BitSetting = L"No";
    }
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_QUIET,
                   L"    - %s = %s",
                   BitField,
                   BitSetting
                   );
  }

#endif

  if ((AttributesSupported & 0xFFFFFFFFFFFFFFF8) != 0) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
    ResultMessageData = L"*AttributesSupported has bit(s) set beyond bit2.";
    goto Exit; 
  }

  if ((AttributesSetting & 0xFFFFFFFFFFFFFFF8) != 0) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
    ResultMessageData = L"*AttributesSetting has bit(s) set beyond bit2.";
    goto Exit; 
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

