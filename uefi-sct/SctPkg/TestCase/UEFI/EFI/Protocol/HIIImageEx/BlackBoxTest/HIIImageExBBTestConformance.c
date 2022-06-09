/** @file

  Copyright 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2017, Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    HIIImageExBBTestConformance.c

Abstract:
    for EFI Driver HII ImageEx Protocol's conformance Test

--*/

#include "HIIImageExBBTestMain.h"

extern UINT8 mPackageList1[];

extern UINT8 mImage[];

#define mImage1 ((EFI_IMAGE_INPUT*)(mImage)) 

EFI_STATUS
EFIAPI
BBTestNewImageExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestGetImageExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );
  
EFI_STATUS
EFIAPI
BBTestGetImageExConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestGetImageExConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );
  
EFI_STATUS
EFIAPI
BBTestSetImageExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );
  
EFI_STATUS
EFIAPI
BBTestSetImageExConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestSetImageExConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );
  
EFI_STATUS
EFIAPI
BBTestDrawImageExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestDrawImageExConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestDrawImageExConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestDrawImageExConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestDrawImageExConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdExConformanceTestCheckpoint1(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDataBase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdExConformanceTestCheckpoint2(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDataBase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdExConformanceTestCheckpoint3(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDataBase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdExConformanceTestCheckpoint4(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDataBase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
EFIAPI
BBTestGetImageInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );


//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestNewImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_EX_PROTOCOL             *HIIImageEx;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;
  
  //
  // init
  //
  HIIImageEx = (EFI_HII_IMAGE_EX_PROTOCOL*) ClientInterface;

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
  BBTestNewImageExConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_EX_PROTOCOL             *HIIImageEx;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImageEx = (EFI_HII_IMAGE_EX_PROTOCOL*) ClientInterface;

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
  BBTestGetImageExConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);
  
  BBTestGetImageExConformanceTestCheckpoint2 (StandardLib, HIIDatabase, HIIImageEx);

  BBTestGetImageExConformanceTestCheckpoint3 (StandardLib, HIIDatabase, HIIImageEx);
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
EFIAPI
BBTestSetImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_EX_PROTOCOL             *HIIImageEx;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImageEx = (EFI_HII_IMAGE_EX_PROTOCOL*) ClientInterface;

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
  BBTestSetImageExConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);
  
  BBTestSetImageExConformanceTestCheckpoint2 (StandardLib, HIIDatabase, HIIImageEx);

  BBTestSetImageExConformanceTestCheckpoint3 (StandardLib, HIIDatabase, HIIImageEx);
  
  return EFI_SUCCESS;
}
  
EFI_STATUS
EFIAPI
BBTestDrawImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_EX_PROTOCOL             *HIIImageEx;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImageEx = (EFI_HII_IMAGE_EX_PROTOCOL*) ClientInterface;

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
  BBTestDrawImageExConformanceTestCheckpoint1 (StandardLib, HIIImageEx);
  
  BBTestDrawImageExConformanceTestCheckpoint2 (StandardLib, HIIImageEx);
  
  BBTestDrawImageExConformanceTestCheckpoint3 (StandardLib, HIIImageEx);

  BBTestDrawImageExConformanceTestCheckpoint4 (StandardLib, HIIImageEx);

  BBTestDrawImageExConformanceTestCheckpoint5 (StandardLib, HIIImageEx);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDrawImageIdExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_EX_PROTOCOL             *HIIImageEx;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImageEx = (EFI_HII_IMAGE_EX_PROTOCOL*) ClientInterface;

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
  BBTestDrawImageIdExConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);

  BBTestDrawImageIdExConformanceTestCheckpoint2 (StandardLib, HIIDatabase, HIIImageEx);

  BBTestDrawImageIdExConformanceTestCheckpoint3 (StandardLib, HIIDatabase, HIIImageEx);

  BBTestDrawImageIdExConformanceTestCheckpoint4 (StandardLib, HIIDatabase, HIIImageEx);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetImageInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_EX_PROTOCOL             *HIIImageEx;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImageEx = (EFI_HII_IMAGE_EX_PROTOCOL*) ClientInterface;

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
  BBTestGetImageInfoConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestNewImageExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx with ImageId been NULL
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid001,
                 L"HII_IMAGE_EX_PROTOCOL.NewImageEx - NewImageEx() returns EFI_INVALID_PARAMETER with ImageId been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call NewImageEx with Image been NULL
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid002,
                 L"HII_IMAGE_EX_PROTOCOL.NewImageEx - NewImageEx() returns EFI_INVALID_PARAMETER with Image been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Call NewImageEx with PackageList been NULL
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid003,
                 L"HII_IMAGE_EX_PROTOCOL.NewImageEx - NewImageEx() returns EFI_NOT_FOUND with PackageList been NULL.",
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
BBTestGetImageExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to add a new image
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call GetImageEx with ImageId been invalid
  //
  Status = HIIImageEx->GetImageEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid004,
                 L"HII_IMAGE_EX_PROTOCOL.GetImageEx - GetImageEx() returns EFI_NOT_FOUND with ImageId been invalid.",
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
BBTestGetImageExConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to add a new image
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call GetImageEx with Image been NULL
  //
  Status = HIIImageEx->GetImageEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid005,
                 L"HII_IMAGE_EX_PROTOCOL.GetImageEx - GetImageEx() returns EFI_INVALID_PARAMETER with Image been NULL.",
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
BBTestGetImageExConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to add a new image
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call GetImageEx with PackageList is not in Database
  //
  Status = HIIImageEx->GetImageEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid006,
                 L"HII_IMAGE_EX_PROTOCOL.GetImageEx - GetImageEx() returns EFI_NOT_FOUND with PackageList is not in Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetImageEx with PackageList been NULL
  //
  Status = HIIImageEx->GetImageEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid007,
                 L"HII_IMAGE_EX_PROTOCOL.GetImageEx - GetImageEx() returns EFI_NOT_FOUND with PackageList been NULL.",
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
BBTestSetImageExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to add a new image
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call SetImageEx with ImageId been invalid
  //
  Status = HIIImageEx->SetImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid008,
                 L"HII_IMAGE_EX_PROTOCOL.SetImageEx - SetImageEx() returns EFI_NOT_FOUND with ImageId been invalid.",
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
BBTestSetImageExConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to add a new image
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call SetImageEx with Image been MULL
  //
  Status = HIIImageEx->SetImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid009,
                 L"HII_IMAGE_EX_PROTOCOL.SetImageEx - SetImageEx() returns EFI_INVALID_PARAMETER with Image been NULL.",
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
BBTestSetImageExConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to add a new image
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call SetImageEx with PackageList is not in Database
  //
  Status = HIIImageEx->SetImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid010,
                 L"HII_IMAGE_EX_PROTOCOL.SetImageEx - SetImageEx() returns EFI_NOT_FOUND with PackageList is not in Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Call SetImageEx with PackageList been MULL
  //
  Status = HIIImageEx->SetImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid011,
                 L"HII_IMAGE_EX_PROTOCOL.SetImageEx - SetImageEx() returns EFI_NOT_FOUND with PackageList been NULL.",
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
BBTestDrawImageExConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call DrawImageEx with Image been NULL
  //
  Status = HIIImageEx->DrawImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid012,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageEx - DrawImageEx() returns EFI_INVALID_PARAMETER with Image been NULL.",
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
BBTestDrawImageExConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call DrawImageEx with EFI_HII_DRAW_FLAG_TRANSPARENT and Blt been NULL
  //
  Status = HIIImageEx->DrawImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid013,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageEx - DrawImageEx() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_TRANSPARENT and Blt been NULL.",
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
BBTestDrawImageExConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call DrawImageEx with EFI_HII_DIRECT_TO_SCREEN and no screen
  //
  Status = HIIImageEx->DrawImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid014,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageEx - DrawImageEx() returns EFI_INVALID_PARAMETER with EFI_HII_DIRECT_TO_SCREEN and no screen.",
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
BBTestDrawImageExConformanceTestCheckpoint4(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call DrawImageEx with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL
  //
  Status = HIIImageEx->DrawImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid015,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageEx - DrawImageEx() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL.",
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
BBTestDrawImageExConformanceTestCheckpoint5(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call DrawImageEx with EFI_HII_DRAW_FLAG_DEFAULT, Blt points to NULL, and Image's Flags is EFI_IMAGE_TRANSPARENT.
  //
  Status = HIIImageEx->DrawImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid016,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageEx - DrawImageEx() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL.",
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
BBTestDrawImageIdExConformanceTestCheckpoint1(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to get the ImageId
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call DrawImageIdEx with PackageList is not in Database
  //
  Status = HIIImageEx->DrawImageIdEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid017,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageIdEx - DrawImageIdEx() returns EFI_NOT_FOUND with PackageList is not in Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call DrawImageIdEx with PackageList been NULL
  //
  Status = HIIImageEx->DrawImageIdEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid018,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageIdEx - DrawImageIdEx() returns EFI_NOT_FOUND with PackageList been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call DrawImageIdEx with invalid ImageId
  //
  Status = HIIImageEx->DrawImageIdEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid019,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageIdEx - DrawImageIdEx() returns EFI_NOT_FOUND with invalid ImageId.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call DrawImageIdEx with invalid PackageList
  //
  Status = HIIImageEx->DrawImageIdEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid020,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageIdEx - DrawImageIdEx() returns EFI_NOT_FOUND with invalid PackageList.",
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
BBTestDrawImageIdExConformanceTestCheckpoint2(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to get the ImageId
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call DrawImageIdEx with EFI_HII_DRAW_FLAG_TRANSPARENT and Blt been NULL
  //
  Status = HIIImageEx->DrawImageIdEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid021,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageIdEx - DrawImageIdEx() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_TRANSPARENT and Blt been NULL.",
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
BBTestDrawImageIdExConformanceTestCheckpoint3(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to get the ImageId
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call DrawImageIdEx with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL
  //
  Status = HIIImageEx->DrawImageIdEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid022,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageIdEx - DrawImageIdEx() returns EFI_INVALID_PARAMETER with EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL.",
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
BBTestDrawImageIdExConformanceTestCheckpoint4(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call NewImageEx to get the ImageId
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call DrawImageIdEx with EFI_HII_DRAW_FLAG_DEFAULT, Blt points to NULL, and Image's Flags is EFI_IMAGE_TRANSPARENT.
  //
  Status = HIIImageEx->DrawImageIdEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid023,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageIdEx - DrawImageIdEx() returns EFI_INVALID_PARAMETER with with EFI_HII_DRAW_FLAG_DEFAULT, Blt points to NULL, and Image's Flags is EFI_IMAGE_TRANSPARENT.",
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
BBTestGetImageInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  EFI_IMAGE_OUTPUT               Image3;
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
  // Call NewImageEx to add a new image
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
  // Call GetImageInfo with ImageId been invalid
  //
  Status = HIIImageEx->GetImageInfo(
                       HIIImageEx,
                       Handle,
                       ImageId+1,
                       &Image3
                       );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageExBBTestConformanceAssertionGuid024,
                 L"HII_IMAGE_EX_PROTOCOL.GetImageInfo - GetImageInfo() returns EFI_NOT_FOUND with ImageId been invalid.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetImageInfo with Image being NULL
  //
  Status = HIIImageEx->GetImageInfo(
                       HIIImageEx,
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
                 gHIIImageExBBTestConformanceAssertionGuid025,
                 L"HII_IMAGE_EX_PROTOCOL.GetImageInfo - GetImageInfo() returns EFI_INVALID_PARAMETER with Image been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call GetImageInfo with ImageId being 0
  //
  Status = HIIImageEx->GetImageInfo(
                       HIIImageEx,
                       Handle,
                       0,
                       &Image3
                       );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageExBBTestConformanceAssertionGuid026,
                 L"HII_IMAGE_EX_PROTOCOL.GetImageInfo - GetImageInfo() returns EFI_INVALID_PARAMETER with ImageId been 0.",
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

