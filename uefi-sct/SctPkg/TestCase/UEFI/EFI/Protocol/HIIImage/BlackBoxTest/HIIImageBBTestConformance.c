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
    HIIImageBBTestConformance.c

Abstract:
    for EFI Driver HII Image Protocol's conformance Test

--*/

#include "HIIImageBBTestMain.h"

extern UINT8 mPackageList1[];

extern UINT8 mImage[];

#define mImage1 ((EFI_IMAGE_INPUT*)(mImage)) 

EFI_STATUS
EFIAPI
BBTestNewImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
  
EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
  
EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
  
EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
  
EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
  
EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint1(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDataBase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint2(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDataBase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint3(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDataBase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint4(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDataBase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint5(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDataBase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestNewImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;
  
  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface (&HIIDatabase);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestNewImageConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface (&HIIDatabase);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetImageConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);
  
//  BBTestGetImageConformanceTestCheckpoint2 (StandardLib, HIIDatabase, HIIImage);
  
  BBTestGetImageConformanceTestCheckpoint3 (StandardLib, HIIDatabase, HIIImage);

//  BBTestGetImageConformanceTestCheckpoint4 (StandardLib, HIIDatabase, HIIImage);

  BBTestGetImageConformanceTestCheckpoint5 (StandardLib, HIIDatabase, HIIImage);
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
EFIAPI
BBTestSetImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface (&HIIDatabase);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestSetImageConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);
  
  BBTestSetImageConformanceTestCheckpoint2 (StandardLib, HIIDatabase, HIIImage);

  BBTestSetImageConformanceTestCheckpoint3 (StandardLib, HIIDatabase, HIIImage);
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface (&HIIDatabase);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestDrawImageConformanceTestCheckpoint1 (StandardLib, HIIImage);
  
  BBTestDrawImageConformanceTestCheckpoint2 (StandardLib, HIIImage);
  
  BBTestDrawImageConformanceTestCheckpoint3 (StandardLib, HIIImage);

  BBTestDrawImageConformanceTestCheckpoint4 (StandardLib, HIIImage);

  BBTestDrawImageConformanceTestCheckpoint5 (StandardLib, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface (&HIIDatabase);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestDrawImageIdConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);

  BBTestDrawImageIdConformanceTestCheckpoint2 (StandardLib, HIIDatabase, HIIImage);

//  BBTestDrawImageIdConformanceTestCheckpoint3 (StandardLib, HIIDatabase, HIIImage);

  BBTestDrawImageIdConformanceTestCheckpoint4 (StandardLib, HIIDatabase, HIIImage);

  BBTestDrawImageIdConformanceTestCheckpoint5 (StandardLib, HIIDatabase, HIIImage);
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestNewImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
  	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }  
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
  	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call NewImage with ImageId been NULL
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       NULL,
                       Image
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid001,
                 L"HII_IMAGE_PROTOCOL.NewImage - NewImage() returns EFI_INVALID_PARAMETER with ImageId been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call NewImage with Image been NULL
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       NULL
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid002,
                 L"HII_IMAGE_PROTOCOL.NewImage - NewImage() returns EFI_INVALID_PARAMETER with Image been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Call NewImage with PackageList been NULL
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       NULL,
                       &ImageId,
                       Image
                       );
  
  if ( EFI_NOT_FOUND!= Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid003,
                 L"HII_IMAGE_PROTOCOL.NewImage - NewImage() returns EFI_NOT_FOUND with PackageList been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool (Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
		return TempStatus;
    }
    return Status;
  }
  
  //
  // Call GetImage with ImageId been invalid
  //
  Status = HIIImage->GetImage (
                       HIIImage,
                       Handle,
                       ImageId+1,
                       Image
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid004,
                 L"HII_IMAGE_PROTOCOL.GetImage - GetImage() returns EFI_NOT_FOUND with ImageId been invalid.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
  	return Status;
  }

  return EFI_SUCCESS;
}


//
// Remove Checkpoint2 to be compatible with Update7a
//
/*
EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image;
  UINTN                          ImageSize, ImageSizeSmall;
#if SWITCH_FLAG_EFI_IMAGE_INPUT
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
#else
  UINT16                         Width;
  UINT16                         Height;
#endif
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
#if SWITCH_FLAG_EFI_IMAGE_INPUT
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;
  ImageSize = Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) + 8;
  ImageSizeSmall = ImageSize - 1;
#else
  Width = 50;
  Height = 60;
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT)+ Width * Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) - sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Image == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = Width;
  Image->Height = Height;
  ImageSize = sizeof(EFI_IMAGE_INPUT)+ Width * Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) - sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
  ImageSizeSmall = ImageSize - 1;
#endif
  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
#if SWITCH_FLAG_EFI_IMAGE_INPUT  	
  	gtBS->FreePool (Bitmap);
#endif
  	gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}
    return Status;
  }
  
  //
  // Call GetImage with not enough ImageSize 
  //
  Status = HIIImage->GetImage (
                       HIIImage,
                       Handle,
                       ImageId,
                       Image,
                       &ImageSizeSmall
                       );
  
  if ( EFI_BUFFER_TOO_SMALL != Status && ImageSizeSmall != ImageSize ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid005,
                 L"HII_IMAGE_PROTOCOL.GetImage - GetImage() returns EFI_BUFFER_TOO_SMALL with ImageSize is small.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
#if SWITCH_FLAG_EFI_IMAGE_INPUT  
  gtBS->FreePool (Bitmap);
#endif
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;
}
*/

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;
  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Bitmap);
  	gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}
    return Status;
  }
  
  //
  // Call GetImage with Image been NULL
  //
  Status = HIIImage->GetImage (
                       HIIImage,
                       Handle,
                       ImageId,
                       NULL
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid006,
                 L"HII_IMAGE_PROTOCOL.GetImage - GetImage() returns EFI_INVALID_PARAMETER with Image been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;  
}

//
// Remove Checkpoint4 to be compatible with Update7a
//
/*
EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image;
  UINTN                          ImageSize;
#if SWITCH_FLAG_EFI_IMAGE_INPUT
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
#else
  UINT16                         Width;
  UINT16                         Height;
#endif
  
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
#if SWITCH_FLAG_EFI_IMAGE_INPUT
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
     Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }	
    return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;
  ImageSize = Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) + 8;
#else
  Width = 50;
  Height = 60;
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT)+ Width * Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) - sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Image == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = Width;
  Image->Height = Height;
  ImageSize = sizeof(EFI_IMAGE_INPUT)+ Width * Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) - sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
#endif
  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
#if SWITCH_FLAG_EFI_IMAGE_INPUT 
  	gtBS->FreePool (Bitmap);
#endif
  	gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}
    return Status;
  }

  //
  // Call GetImage with ImageSize been NULL
  //
  Status = HIIImage->GetImage (
                       HIIImage,
                       Handle,
                       ImageId,
                       Image,
                       NULL
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid007,
                 L"HII_IMAGE_PROTOCOL.GetImage - GetImage() returns EFI_INVALID_PARAMETER with ImageSize been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
#if SWITCH_FLAG_EFI_IMAGE_INPUT
  gtBS->FreePool (Bitmap);
#endif
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;  
}
*/

EFI_STATUS
EFIAPI
BBTestGetImageConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;
  
  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Bitmap);
  	gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}
	
    return Status;  
  }

  //
  // Call GetImage with PackageList is not in Database
  //
  Status = HIIImage->GetImage (
                       HIIImage,
                       (EFI_HANDLE)((UINT8*)(Handle) + 8),
                       ImageId,
                       Image
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid024,
                 L"HII_IMAGE_PROTOCOL.GetImage - GetImage() returns EFI_NOT_FOUND with PackageList is not in Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetImage with PackageList been NULL
  //
  Status = HIIImage->GetImage (
                       HIIImage,
                       NULL,
                       ImageId,
                       Image
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid008,
                 L"HII_IMAGE_PROTOCOL.GetImage - GetImage() returns EFI_NOT_FOUND with PackageList been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;  
}


EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image1;
  EFI_IMAGE_INPUT                *Image2;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap1; 
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap2;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image1
  //
  Image1 = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image1 == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image1->Flags = 0;
  Image1->Width = 50;
  Image1->Height = 60;
  Bitmap1 = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image1->Width * Image1->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap1 == NULL ) {
    gtBS->FreePool (Image1);
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image1->Bitmap = Bitmap1;
  
  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image1
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Bitmap1);
	gtBS->FreePool (Image1);
    TempStatus = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
    }
    return Status;
  }


  //
  // Init the Image2
  //
  Image2 = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image2 == NULL ) {
  	gtBS->FreePool (Bitmap1);
	gtBS->FreePool (Image1);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
	if ( EFI_ERROR(Status) ) {
      return Status;
    }
  	return EFI_UNSUPPORTED;
  }
  Image2->Flags = 0;
  Image2->Width = 30;
  Image2->Height = 40;
  Bitmap2= (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image2->Width * Image2->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap2 == NULL ) {
  	gtBS->FreePool (Bitmap1);
	gtBS->FreePool (Image1);
    gtBS->FreePool (Image2);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image2->Bitmap = Bitmap2;
  
  //
  // Call SetImage with ImageId been invalid
  //
  Status = HIIImage->SetImage(
                       HIIImage,
                       Handle,
                       ImageId+1,
                       Image2
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid009,
                 L"HII_IMAGE_PROTOCOL.SetImage - SetImage() returns EFI_NOT_FOUND with ImageId been invalid.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap1);
  gtBS->FreePool (Image1);
  gtBS->FreePool (Bitmap2);
  gtBS->FreePool (Image2);
  
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }	
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image1
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;
  
  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Bitmap);
	gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
    if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
    } 
    return Status;
  }
  
  //
  // Call SetImage with Image been MULL
  //
  Status = HIIImage->SetImage(
                       HIIImage,
                       Handle,
                       ImageId,
                       NULL
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid010,
                 L"HII_IMAGE_PROTOCOL.SetImage - SetImage() returns EFI_INVALID_PARAMETER with Image been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);
  
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  } 
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image1;
  EFI_IMAGE_INPUT                *Image2;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap1; 
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap2;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image1
  //
  Image1 = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image1 == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    } 
  	return EFI_UNSUPPORTED;
  }
  Image1->Flags = 0;
  Image1->Width = 50;
  Image1->Height = 60;
  Bitmap1 = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image1->Width * Image1->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap1 == NULL ) {
    gtBS->FreePool ( Image1 );
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    } 
    return EFI_UNSUPPORTED;
  }
  Image1->Bitmap = Bitmap1;
  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image1
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Bitmap1);
	gtBS->FreePool (Image1);
    TempStatus = HIIDatabase->RemovePackageList (
                    HIIDatabase,
                    Handle
                    );
    if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
    }
    return Status;
  }
  
  //
  // Init the Image2
  //
  Image2 = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image2 == NULL ) {
  	gtBS->FreePool (Bitmap1);
	gtBS->FreePool (Image1);
	Status = HIIDatabase->RemovePackageList (
                    HIIDatabase,
                    Handle
                    ); 
    if ( EFI_ERROR(Status) ) {
      return Status;
    } 
  	return EFI_UNSUPPORTED;
  }
  Image2->Flags = 0;
  Image2->Width = 30;
  Image2->Height = 40;
  Bitmap2= (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image2->Width * Image2->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap2 == NULL ) {
  	gtBS->FreePool (Bitmap1);
	gtBS->FreePool (Image1);
    gtBS->FreePool (Image2);
	Status = HIIDatabase->RemovePackageList (
                    HIIDatabase,
                    Handle
                    );
    if ( EFI_ERROR(Status) ) {
      return Status;
    } 
	return EFI_UNSUPPORTED;
  }
  Image2->Bitmap = Bitmap2;

  //
  // Call SetImage with PackageList is not in Database
  //
  Status = HIIImage->SetImage(
                       HIIImage,
                       (EFI_HANDLE)((UINT8*)(Handle) + 8),
                       ImageId,
                       Image2
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid025,
                 L"HII_IMAGE_PROTOCOL.SetImage - SetImage() returns EFI_NOT_FOUND with PackageList is not in Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Call SetImage with PackageList been MULL
  //
  Status = HIIImage->SetImage(
                       HIIImage,
                       NULL,
                       ImageId,
                       Image2
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid011,
                 L"HII_IMAGE_PROTOCOL.SetImage - SetImage() returns EFI_NOT_FOUND with PackageList been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap1);
  gtBS->FreePool (Image1);
  gtBS->FreePool (Bitmap2);
  gtBS->FreePool (Image2);
  
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }	
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_DRAW_FLAGS    Flag;
  EFI_IMAGE_OUTPUT      *Blt;
  UINTN                 BltX;
  UINTN                 BltY;
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DRAW_FLAG_CLIP;
  Blt = NULL;
  BltX = 0;
  BltY = 0;

  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL){
    return  EFI_UNSUPPORTED;
  }

  Blt->Width = 50;
  Blt->Height = 40;
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (Blt->Width *Blt->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if (Blt->Image.Bitmap == NULL){
  	gtBS->FreePool (Blt);
    return  EFI_UNSUPPORTED;
  }
  
  //
  // Call DrawImage with Image been NULL
  //
  Status = HIIImage->DrawImage(
                       HIIImage,
                       Flag,
                       NULL,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid012,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_INVALID_PARAMETER with Image been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Blt->Image.Bitmap);
  gtBS->FreePool (Blt);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_DRAW_FLAGS             Flag;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap; 

  Flag = EFI_HII_DRAW_FLAG_FORCE_TRANS;
  BltX = 0;
  BltY = 0;

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL )
  	return EFI_UNSUPPORTED;
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool ( Image );
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  
  //
  // Call DrawImage with EFI_HII_DRAW_FLAG_TRANSPARENT and Blt been NULL
  //
  Status = HIIImage->DrawImage(
                       HIIImage,
                       Flag,
                       Image,
                       NULL,
                       BltX,
                       BltY
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid013,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_TRANSPARENT and Blt been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);
  

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DIRECT_TO_SCREEN;
  BltX = 0;
  BltY = 0;

  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL){
    return  EFI_UNSUPPORTED;
  }

  Blt->Width = 50;
  Blt->Height = 40;
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (Blt->Width *Blt->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if (Blt->Image.Bitmap == NULL){
  	gtBS->FreePool (Blt);
    return  EFI_UNSUPPORTED;
  } 

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ){
  	gtBS->FreePool (Blt->Image.Bitmap);
	gtBS->FreePool (Blt);
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
	gtBS->FreePool (Blt);
    gtBS->FreePool ( Image );
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;
  
  //
  // Call DrawImage with EFI_HII_DIRECT_TO_SCREEN and no screen
  //
  Status = HIIImage->DrawImage(
                       HIIImage,
                       Flag,
                       Image,
                       NULL,
                       BltX,
                       BltY
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid014,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_INVALID_PARAMETER with EFI_HII_DIRECT_TO_SCREEN and no screen.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Blt->Image.Bitmap);
  gtBS->FreePool (Blt);
  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint4(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{

  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DRAW_FLAG_CLIP;
  Blt = NULL;
  BltX = 0;
  BltY = 0;

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL )
  	return EFI_UNSUPPORTED;
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool ( Image );
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  
  //
  // Call DrawImage with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL
  //
  Status = HIIImage->DrawImage(
                       HIIImage,
                       Flag,
                       Image,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid015,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDrawImageConformanceTestCheckpoint5(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{

  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DRAW_FLAG_DEFAULT;
  Blt = NULL;
  BltX = 0;
  BltY = 0;

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL )
  	return EFI_UNSUPPORTED;
  Image->Flags = EFI_IMAGE_TRANSPARENT;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool ( Image );
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  
  //
  // Call DrawImage with EFI_HII_DRAW_FLAG_DEFAULT, Blt points to NULL, and Image's Flags is EFI_IMAGE_TRANSPARENT.
  //
  Status = HIIImage->DrawImage(
                       HIIImage,
                       Flag,
                       Image,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid016,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint1(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;

  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;  
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_IMAGE_ID                   ImageId;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap; 

  BltX = 0;
  BltY = 0;
  Flag = EFI_HII_DRAW_FLAG_CLIP;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init Blt
  //
  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL){
  	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }             
    return  EFI_UNSUPPORTED;
  }

  Blt->Width = 50;
  Blt->Height = 40;
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (Blt->Width * Blt->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if (Blt->Image.Bitmap == NULL){
  	gtBS->FreePool (Blt);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }  
    return  EFI_UNSUPPORTED;
  }

  
  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags= 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);  	
    gtBS->FreePool (Image);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call NewImage to get the ImageId
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}                                
    return Status;
  }

  //
  // Call DrawImageId with PackageList is not in Database
  //
  Status = HIIImage->DrawImageId (
                       HIIImage,
                       Flag,
                       (EFI_HANDLE)((UINT8*)(Handle) + 8),
                       ImageId,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid026,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_NOT_FOUND with PackageList is not in Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call DrawImageId with PackageList been NULL
  //
  Status = HIIImage->DrawImageId (
                       HIIImage,
                       Flag,
                       NULL,
                       ImageId,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid017,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_NOT_FOUND with PackageList been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call DrawImageId with invalid ImageId
  //
  Status = HIIImage->DrawImageId (
                       HIIImage,
                       Flag,
                       Handle,
                       ImageId+1,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid018,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_NOT_FOUND with invalid ImageId.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call DrawImageId with invalid PackageList
  //
  Status = HIIImage->DrawImageId (
                       HIIImage,
                       Flag,
                       (EFI_HII_HANDLE)((UINT8*)Handle + 8),
                       ImageId,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid019,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_NOT_FOUND with invalid PackageList.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Blt->Image.Bitmap);
  gtBS->FreePool (Blt);
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  
  if ( EFI_ERROR(Status) ) {
    return Status;
  }                             

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint2(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;

  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;  
  EFI_HII_DRAW_FLAGS             Flag;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_IMAGE_ID                   ImageId;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap; 

  // 2007.12.18
  // Modify EFI_HII_DRAW_FLAG_TRANSPARENT to EFI_HII_DRAW_FLAG_FORCE_TRANS, Since EFI_HII_DRAW_FLAG_TRANSPARENT is a mask only
  //
  BltX = 0;
  BltY = 0;
  Flag = EFI_HII_DRAW_FLAG_FORCE_TRANS;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;
  //
  // Call NewImage to get the ImageId
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}                                
    return Status;
  }

  //
  // Call DrawImageId with EFI_HII_DRAW_FLAG_TRANSPARENT and Blt been NULL
  //
  Status = HIIImage->DrawImageId(
                       HIIImage,
                       Flag,
                       Handle,
                       ImageId,
                       NULL,
                       BltX,
                       BltY
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid020,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_TRANSPARENT and Blt been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint3(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;

  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;  
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_IMAGE_ID                   ImageId;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap; 

  BltX = 0;
  BltY = 0;
  Flag = EFI_HII_DIRECT_TO_SCREEN;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init Blt
  //
  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL){
  	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }             
    return  EFI_UNSUPPORTED;
  }

  Blt->Width = 50;
  Blt->Height = 40;
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (Blt->Width * Blt->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if (Blt->Image.Bitmap == NULL){
  	gtBS->FreePool (Blt);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }  
    return  EFI_UNSUPPORTED;
  }

  
  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);  	
    gtBS->FreePool (Image);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call NewImage to get the ImageId
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}                                
    return Status;
  }

  //
  // Call DrawImageId with EFI_HII_DIRECT_TO_SCREEN and no screen
  //
  Status = HIIImage->DrawImageId(
                       HIIImage,
                       Flag,
                       Handle,
                       ImageId,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid021,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_INVALID_PARAMETER with EFI_HII_DIRECT_TO_SCREEN and no screen.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Blt->Image.Bitmap);
  gtBS->FreePool (Blt);
  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint4(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;

  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;  
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_IMAGE_ID                   ImageId;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;

  Blt = NULL;
  BltX = 0;
  BltY = 0;
  Flag = EFI_HII_DRAW_FLAG_CLIP;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call NewImage to get the ImageId
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}                                
    return Status;
  }  

  
  //
  // Call DrawImageId with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL
  //
  Status = HIIImage->DrawImageId(
                       HIIImage,
                       Flag,
                       Handle,
                       ImageId,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid022,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }  

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDrawImageIdConformanceTestCheckpoint5(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{

  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;    
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_IMAGE_ID                   ImageId;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;

  Blt = NULL;
  BltX = 0;
  BltY = 0;
  Flag = EFI_HII_DRAW_FLAG_DEFAULT;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = EFI_IMAGE_TRANSPARENT;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call NewImage to get the ImageId
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}                                
    return Status;
  }  


  //
  // Call DrawImageId with EFI_HII_DRAW_FLAG_DEFAULT, Blt points to NULL, and Image's Flags is EFI_IMAGE_TRANSPARENT.
  //
  Status = HIIImage->DrawImageId(
                       HIIImage,
                       Flag,
                       Handle,
                       ImageId,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestConformanceAssertionGuid023,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_INVALID_PARAMETER with with EFI_HII_DRAW_FLAG_DEFAULT, Blt points to NULL, and Image's Flags is EFI_IMAGE_TRANSPARENT.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }  
  
  return EFI_SUCCESS;
}

