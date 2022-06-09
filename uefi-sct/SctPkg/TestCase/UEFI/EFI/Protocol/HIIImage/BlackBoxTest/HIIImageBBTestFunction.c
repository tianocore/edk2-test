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
    HIIImageBBTestFunction.c

Abstract:
    for EFI Driver HII Image Protocol's function Test

--*/

#include "HIIImageBBTestMain.h"

extern UINT8 mPackageList1[];

extern UINT8 mImage[];

extern UINT8 mSetNewImage[];

#define mImage1 ((EFI_IMAGE_INPUT*)(mImage))
#define mImage2 ((EFI_IMAGE_INPUT*)(mSetNewImage))
#define Image1Length 1
#define Image2Length 1

EFI_STATUS
EFIAPI
BBTestNewImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
  
EFI_STATUS
EFIAPI
BBTestGetImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
  
EFI_STATUS
EFIAPI
BBTestSetImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );


//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestNewImageFunctionTest (
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
  BBTestNewImageFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetImageFunctionTest (
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
  BBTestGetImageFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetImageFunctionTest (
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
  BBTestSetImageFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDrawImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;

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
  if (EFI_ERROR(Status)) {
    return Status;
  }
  
  Status = GetGraphicsOutputInterface (&GraphicsOutput);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestDrawImageFunctionTestCheckpoint1 (StandardLib, HIIImage);

  BBTestDrawImageFunctionTestCheckpoint2 (StandardLib, HIIImage);

//  BBTestDrawImageFunctionTestCheckpoint3 (StandardLib, GraphicsOutput, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDrawImageIdFunctionTest (
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
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;  

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

  Status = GetGraphicsOutputInterface (&GraphicsOutput);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  //Call check points
  //
  BBTestDrawImageIdFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);

  BBTestDrawImageIdFunctionTestCheckpoint2 (StandardLib, HIIDatabase, HIIImage);

//  BBTestDrawImageIdFunctionTestCheckpoint3 (StandardLib, HIIDatabase, GraphicsOutput, HIIImage);
  
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestNewImageFunctionTestCheckpoint1 (
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
  // Call NewImage with valid parameters
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid001,
                 L"HII_IMAGE_PROTOCOL.NewImage - NewImage() returns EFI_SUCCESS with valid parameters and result checked.",
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
BBTestGetImageFunctionTestCheckpoint1 (
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
    gtBS->FreePool ( Image );
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
  // Call GetImage to with valid parameters
  //
  Status = HIIImage->GetImage (
                       HIIImage,
                       Handle,
                       ImageId,
                       Image
                       );

//  if ( EFI_SUCCESS == Status && ImageSize == (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) + 8) ) {
  if ( EFI_SUCCESS == Status ) {	
	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid002,
                 L"HII_IMAGE_PROTOCOL.GetImage - GetImage() returns EFI_SUCCESS with valid parameters and the result checked.",
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
BBTestSetImageFunctionTestCheckpoint1 (
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
    if ( EFI_ERROR (Status) ) {
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
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image2->Bitmap = Bitmap2;

  
  //
  // Call SetImage with valid parameters
  //
  Status = HIIImage->SetImage(
                       HIIImage,
                       Handle,
                       ImageId,
                       Image2
                       );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid003,
                 L"HII_IMAGE_PROTOCOL.SetImage - SetImage() returns EFI_SUCCESS with valid parameters and result checked.",
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
BBTestDrawImageFunctionTestCheckpoint1 (
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
  Flag = EFI_HII_DRAW_FLAG_FORCE_OPAQUE;
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
  // Call DrawImage with with valid parameter
  //
  Status = HIIImage->DrawImage(
                       HIIImage,
                       Flag,
                       Image,
                       &Blt,
                       BltX,
                       BltY
                       );
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid004,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_SUCCESS with valid parameter.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  gtBS->FreePool (Blt);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestDrawImageFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
)
{
  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  UINT16                         Index;

  EFI_HII_DRAW_FLAGS             ValidFlags[] = {
                                   EFI_HII_DRAW_FLAG_CLIP,
                                   EFI_HII_DRAW_FLAG_DEFAULT,
                                   EFI_HII_DRAW_FLAG_FORCE_TRANS,
                                   EFI_HII_DRAW_FLAG_FORCE_OPAQUE,
                                   0xFFFFFFFF 
                                 };

  //
  // Init the Flag and Blt
  //
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
  if ( Image == NULL ) {
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
    gtBS->FreePool (Image);
    return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call DrawImage with with valid parameter
  //
  for (Index=0; ValidFlags[Index] != 0xFFFFFFFF; Index++) {
    Status = HIIImage->DrawImage(
                         HIIImage,
                         ValidFlags[Index],
                         Image,
                         &Blt,
                         BltX,
                         BltY
                         );
    if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIImageBBTestFunctionAssertionGuid005,
                   L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_SUCCESS with valid parameter.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  gtBS->FreePool (Blt);
  
  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
BBTestDrawImageFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput,
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
  UINT32                         HorizontalResolution;
  UINT32                         VerticalResolution;
  UINT32                         CurrentMode;
  
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DIRECT_TO_SCREEN;
  BltX = 0;
  BltY = 0;

  if (GraphicsOutput != NULL) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL)
    return  EFI_UNSUPPORTED;
  
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput;

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ){
	gtBS->FreePool (Blt);
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
	gtBS->FreePool (Blt);
    gtBS->FreePool (Image);
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  CurrentMode = GraphicsOutput->Mode->Mode;


  //
  // Call DrawImage with with valid parameter
  //
  Status = HIIImage->DrawImage(
                       HIIImage,
                       Flag,
                       Image,
                       &Blt,
                       BltX,
                       BltY
                       );

  Status = GraphicsOutput->SetMode (GraphicsOutput, CurrentMode);
  
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid006,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_SUCCESS with valid parameter.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool (Blt);
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestDrawImageIdFunctionTestCheckpoint1 (
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
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DRAW_FLAG_FORCE_OPAQUE;
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
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    return Status;
  }

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
  // Call DrawImageId with with valid parameter
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
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid007,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_SUCCESS with valid parameter.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  gtBS->FreePool (Blt);

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
BBTestDrawImageIdFunctionTestCheckpoint2 (
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
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_IMAGE_ID                   ImageId;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  UINT16                         Index;

  EFI_HII_DRAW_FLAGS             ValidFlags[] = {
                                   EFI_HII_DRAW_FLAG_CLIP,
                                   EFI_HII_DRAW_FLAG_DEFAULT,
                                   EFI_HII_DRAW_FLAG_FORCE_TRANS,
                                   EFI_HII_DRAW_FLAG_FORCE_OPAQUE,
                                   0xFFFFFFFF 
                                 };

  BltX = 0;
  BltY = 0;
  
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
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (Blt->Width *Blt->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
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
  // Call DrawImage with with valid parameter
  //
  for (Index=0; ValidFlags[Index] != 0xFFFFFFFF; Index++) {
    Status = HIIImage->DrawImageId(
                         HIIImage,
                         ValidFlags[Index],
                         Handle,
                         ImageId,
                         &Blt,
                         BltX,
                         BltY
                         );
    if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIImageBBTestFunctionAssertionGuid008,
                   L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_SUCCESS with valid parameter.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  gtBS->FreePool (Blt);

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
BBTestDrawImageIdFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput,
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
  UINT32                         HorizontalResolution;
  UINT32                         VerticalResolution;
  
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DIRECT_TO_SCREEN;
  BltX = 0;
  BltY = 0;

  if (GraphicsOutput != NULL) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL)
    return  EFI_UNSUPPORTED;
  
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput;


  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ){
	gtBS->FreePool (Blt);
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) SctAllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
	gtBS->FreePool (Blt);
    gtBS->FreePool (Image);
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

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
  	gtBS->FreePool (Blt);
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    return Status;
  }

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
  // Call DrawImageId with with valid parameter
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
  
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid009,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_SUCCESS with valid parameter.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
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
