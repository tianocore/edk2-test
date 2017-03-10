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
                                                                
  Copyright 2017 Unified EFI, Inc. All Rights Reserved, subject 
  to all existing rights in all matters included within this 
  Test Suite, to which United EFI, Inc. makes no claim of right.
  
  (C) Copyright 2017 Hewlett Packard Enterprise Development LP<BR>
--*/
/*++

Module Name:
    HIIImageExBBTestFunction.c

Abstract:
    for EFI Driver HII Image Ex Protocol's function Test

--*/

#include "HIIImageExBBTestMain.h"

extern UINT8 mPackageList1[];

extern UINT8 mImage[];

extern UINT8 mSetNewImage[];

#define mImage1 ((EFI_IMAGE_INPUT*)(mImage))
#define mImage2 ((EFI_IMAGE_INPUT*)(mSetNewImage))
#define Image1Length 1
#define Image2Length 1

EFI_STATUS
BBTestNewImageExFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );
  
EFI_STATUS
BBTestGetImageExFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );
  
EFI_STATUS
BBTestSetImageExFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
BBTestDrawImageExFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
BBTestDrawImageExFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );


EFI_STATUS
BBTestDrawImageIdExFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

EFI_STATUS
BBTestDrawImageIdExFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );


EFI_STATUS
BBTestGetImageInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
  );

//
//Test Cases
//
EFI_STATUS
BBTestNewImageExFunctionTest (
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
  BBTestNewImageExFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetImageExFunctionTest (
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
  BBTestGetImageExFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetImageExFunctionTest (
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
  BBTestSetImageExFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestDrawImageExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_EX_PROTOCOL             *HIIImageEx;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;

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
  BBTestDrawImageExFunctionTestCheckpoint1 (StandardLib, HIIImageEx);

  BBTestDrawImageExFunctionTestCheckpoint2 (StandardLib, HIIImageEx);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestDrawImageIdExFunctionTest (
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
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;  

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

  Status = GetGraphicsOutputInterface (&GraphicsOutput);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  //Call check points
  //
  BBTestDrawImageIdExFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);

  BBTestDrawImageIdExFunctionTestCheckpoint2 (StandardLib, HIIDatabase, HIIImageEx);

 
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetImageInfoFunctionTest (
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
  BBTestGetImageInfoFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImageEx);
  
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
BBTestNewImageExFunctionTestCheckpoint1 (
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
  // Call NewImageEx with valid parameters
  //
  Status = HIIImageEx->NewImageEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestFunctionAssertionGuid001,
                 L"HII_IMAGE_EX_PROTOCOL.NewImageEx - NewImageEx() returns EFI_SUCCESS with valid parameters and result checked.",
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
BBTestGetImageExFunctionTestCheckpoint1 (
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
  // Call GetImageEx to with valid parameters
  //
  Status = HIIImageEx->GetImageEx (
                       HIIImageEx,
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
                 gHIIImageExBBTestFunctionAssertionGuid002,
                 L"HII_IMAGE_EX_PROTOCOL.GetImageEx - GetImageEx() returns EFI_SUCCESS with valid parameters and the result checked.",
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
BBTestSetImageExFunctionTestCheckpoint1 (
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
  // Call SetImageEx with valid parameters
  //
  Status = HIIImageEx->SetImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestFunctionAssertionGuid003,
                 L"HII_IMAGE_EX_PROTOCOL.SetImageEx - SetImageEx() returns EFI_SUCCESS with valid parameters and result checked.",
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
BBTestDrawImageExFunctionTestCheckpoint1 (
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
  // Call DrawImageEx with with valid parameter
  //
  Status = HIIImageEx->DrawImageEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestFunctionAssertionGuid004,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageEx - DrawImageEx() returns EFI_SUCCESS with valid parameter.",
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
BBTestDrawImageExFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_EX_PROTOCOL                  *HIIImageEx
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
  // Call DrawImageEx with with valid parameter
  //
  for (Index=0; ValidFlags[Index] != 0xFFFFFFFF; Index++) {
    Status = HIIImageEx->DrawImageEx(
                         HIIImageEx,
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
                   gHIIImageExBBTestFunctionAssertionGuid005,
                   L"HII_IMAGE_EX_PROTOCOL.DrawImageEx - DrawImageEx() returns EFI_SUCCESS with valid parameter.",
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
BBTestDrawImageIdExFunctionTestCheckpoint1 (
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
  // Call DrawImageIdEx with with valid parameter
  //
  Status = HIIImageEx->DrawImageIdEx(
                       HIIImageEx,
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
                 gHIIImageExBBTestFunctionAssertionGuid006,
                 L"HII_IMAGE_EX_PROTOCOL.DrawImageIdEx - DrawImageIdEx() returns EFI_SUCCESS with valid parameter.",
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
BBTestDrawImageIdExFunctionTestCheckpoint2 (
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
  // Call DrawImageEx with with valid parameter
  //
  for (Index=0; ValidFlags[Index] != 0xFFFFFFFF; Index++) {
    Status = HIIImageEx->DrawImageIdEx(
                         HIIImageEx,
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
                   gHIIImageExBBTestFunctionAssertionGuid007,
                   L"HII_IMAGE_EX_PROTOCOL.DrawImageIdEx - DrawImageIdEx() returns EFI_SUCCESS with valid parameter.",
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
BBTestGetImageInfoFunctionTestCheckpoint1 (
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
  // Call GetImageInfo with valid parameters
  //
  Status = HIIImageEx->GetImageInfo(
                       HIIImageEx,
                       Handle,
                       ImageId,
                       &Image3
                       );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageExBBTestFunctionAssertionGuid008,
                 L"HII_IMAGE_EX_PROTOCOL.GetImageInfo - GetImageInfo() returns EFI_SUCCESS with valid parameters.",
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
