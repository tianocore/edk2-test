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
    HIIFontBBTestFunction.c

Abstract:
    for EFI Driver HII Font Protocol's function Test

--*/

#include "HIIFontBBTestMain.h"

extern UINT8 mPackageList1[];
extern UINT8 mPackageListTestFont[];

UINTN
StrLen (
    IN CHAR16   *s1
    );

UINTN
StrSize (
    IN CHAR16   *s1
    );

VOID
StrCpy (
    IN CHAR16   *Dest,
    IN CHAR16   *Src
    );

EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  );

EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  );

EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  );

EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  );

EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  );

EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  );

EFI_STATUS
EFIAPI
BBTestStringIdToImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  );

EFI_STATUS
EFIAPI
BBTestStringIdToImageFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  );

EFI_STATUS
EFIAPI
BBTestGetGlyphFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  );

EFI_STATUS
EFIAPI
BBTestGetFontInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  );

EFI_STATUS
EFIAPI
BBTestGetFontInfoFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  );

EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_FONT_PROTOCOL                 *HIIFont;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase = NULL;


  //
  // init
  //
  HIIFont = (EFI_HII_FONT_PROTOCOL*)ClientInterface;

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
  
  Status = GetHIIDatabaseInterface( &HIIDatabase );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  Status = GetGraphicsOutputInterface ( &GraphicsOutput );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  //Call check points
  //
  BBTestStringToImageFunctionTestCheckpoint1 (StandardLib, HIIFont);

  BBTestStringToImageFunctionTestCheckpoint2 (StandardLib, HIIFont, GraphicsOutput);

  //
  // check point 3 check system font glyph
  //
  BBTestStringToImageFunctionTestCheckpoint3 (StandardLib, HIIFont, GraphicsOutput);

  // check point 4 check customized test font glyph
  BBTestStringToImageFunctionTestCheckpoint4 (StandardLib, HIIDatabase, HIIFont, GraphicsOutput);


  //
  // Now R9 code base HII font interface fails in check point 5, 6. And still not fixed yet
  // So temperally remove these two checkpoints
  //
  
  //
  // check point 5 test RowInfoArray / RowInfoArraySize / ColumnInfoArray with sysinfo == NULL
  //
  BBTestStringToImageFunctionTestCheckpoint5 (StandardLib, HIIFont, GraphicsOutput);

  
  // check point 6 test RowInfoArray / RowInfoArraySize / ColumnInfoArray with sysinfo != NULL
  BBTestStringToImageFunctionTestCheckpoint6 (StandardLib, HIIDatabase, HIIFont, GraphicsOutput);

  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestStringIdToImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_FONT_PROTOCOL                 *HIIFont;
  EFI_HII_STRING_PROTOCOL               *HIIString;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;

  //
  // init
  //
  HIIFont = (EFI_HII_FONT_PROTOCOL*)ClientInterface;

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
  
  Status = GetHIIDatabaseInterface( &HIIDatabase );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  Status = GetHIIStringInterface ( &HIIString );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  Status = GetGraphicsOutputInterface ( &GraphicsOutput );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  //Call check points
  //
  BBTestStringIdToImageFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIString, HIIFont);

  BBTestStringIdToImageFunctionTestCheckpoint2 (StandardLib, HIIDatabase, HIIString, HIIFont, GraphicsOutput);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetGlyphFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_FONT_PROTOCOL                 *HIIFont;

  //
  // init
  //
  HIIFont = (EFI_HII_FONT_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //

  BBTestGetGlyphFunctionTestCheckpoint1 (StandardLib, HIIFont);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetFontInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_FONT_PROTOCOL                 *HIIFont;

  //
  // init
  //
  HIIFont = (EFI_HII_FONT_PROTOCOL*)ClientInterface;

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

  //
  //Call check points
  //
  BBTestGetFontInfoFunctionTestCheckpoint1 (StandardLib, HIIFont);

  BBTestGetFontInfoFunctionTestCheckpoint2 (StandardLib, HIIFont);
  
  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_STRING               TestString;
  EFI_FONT_DISPLAY_INFO    *StringInfo;
  EFI_IMAGE_OUTPUT         *Blt;
  UINTN                    BltX;
  UINTN                    BltY;
  EFI_HII_ROW_INFO         **RowInfoArray = NULL;
  UINTN                    *RowInfoArraySize = NULL;
  UINTN                    *ColumnInfoArray = NULL;
  UINTN                    Index = 0;
  
  //
  // Init the Flags, String, StringInfo, Blt
  //
  EFI_HII_OUT_FLAGS ValidFlags[] = {
    EFI_HII_OUT_FLAG_CLIP, 
    EFI_HII_OUT_FLAG_WRAP,
    EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_OUT_FLAG_CLIP,
    EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_OUT_FLAG_CLIP,
    EFI_HII_OUT_FLAG_TRANSPARENT,
    EFI_HII_IGNORE_IF_NO_GLYPH,
    EFI_HII_IGNORE_LINE_BREAK,
    0
  };
  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if ( Blt == NULL ){
    return  EFI_UNSUPPORTED;
  }

  Blt->Width = 50;
  Blt->Height = 40;
  
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (Blt->Width * Blt->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Blt->Image.Bitmap == NULL ){
  	gtBS->FreePool (Blt);
    return  EFI_UNSUPPORTED;
  }
  
  TestString = L"TestString";
  StringInfo = NULL;
  BltX = 0;
  BltY = 0;

  //
  // Call HIIFont->StringToImage with valid parameters
  //
  for ( Index = 0; ValidFlags[Index] != 0; Index++ ){
    Status = HIIFont->StringToImage (
                        HIIFont,
                        ValidFlags[Index],
                        TestString,
                        StringInfo,
                        &Blt,
                        BltX,
                        BltY,
                        RowInfoArray,
                        RowInfoArraySize,
                        ColumnInfoArray
                        );
                            

    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIFontBBTestFunctionAssertionGuid001,
                   L"HII_FONT_PROTOCOL.StringToImage - StringToImage() returns EFI_SUCCESS with valid parameters.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

	if ( RowInfoArray != NULL )
		gtBS->FreePool (RowInfoArray);
  }

  gtBS->FreePool (Blt->Image.Bitmap);
  gtBS->FreePool (Blt);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_STRING               TestString;
  EFI_FONT_DISPLAY_INFO    *StringInfo;
  EFI_IMAGE_OUTPUT         *Blt;
  UINTN                    BltX;
  UINTN                    BltY;
  EFI_HII_ROW_INFO         **RowInfoArray = NULL;
  UINTN                    *RowInfoArraySize = NULL;
  UINTN                    *ColumnInfoArray = NULL;
  UINTN                    Index = 0;

  
  UINT32                   HorizontalResolution;
  UINT32                   VerticalResolution;
  
  //
  // Init the Flags, String, StringInfo, Blt
  //
  EFI_HII_OUT_FLAGS ValidFlags[] = {
    EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN, 
    EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_IGNORE_LINE_BREAK | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_DIRECT_TO_SCREEN,
    0
  };

  if ( GraphicsOutput != NULL ) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if ( Blt == NULL ){
    return  EFI_UNSUPPORTED;
  }
  
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput;
  TestString = L"TestString";
  StringInfo = NULL;
  BltX = 0;
  BltY = 0;

  //
  // Call HIIFont->StringToImage with valid parameters
  //
  for ( Index = 0; ValidFlags[Index] != 0; Index++ ){
    Status = HIIFont->StringToImage (
                        HIIFont,
                        ValidFlags[Index],
                        TestString,
                        StringInfo,
                        &Blt,
                        BltX,
                        BltY,
                        RowInfoArray,
                        RowInfoArraySize,
                        ColumnInfoArray
                        );
                            

    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIFontBBTestFunctionAssertionGuid002,
                   L"HII_FONT_PROTOCOL.StringToImage - StringToImage() returns EFI_SUCCESS with valid parameters.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

	if ( RowInfoArray != NULL )
		gtBS->FreePool (RowInfoArray);
  }

  gtBS->FreePool (Blt);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  )
{
  EFI_STATUS               Status;
  EFI_TEST_ASSERTION       AssertionType;
  CHAR16                   TestString[2];
  EFI_FONT_DISPLAY_INFO    *StringInfo = NULL;
  EFI_IMAGE_OUTPUT         *Blt;
  EFI_IMAGE_OUTPUT         *FontGlyphBlt = NULL;
  UINTN                    BltX;
  UINTN                    BltY;
  EFI_HII_ROW_INFO         **RowInfoArray = NULL;
  UINTN                    *RowInfoArraySize = NULL;
  UINTN                    *ColumnInfoArray = NULL;
  UINT32                   HorizontalResolution;
  UINT32                   VerticalResolution;
  UINTN                    BaseLine;
  BOOLEAN                  GlyPhMismatch = FALSE;
  
  if ( GraphicsOutput != NULL ) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if ( Blt == NULL ){
  	 StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateZeroPool fail",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return  EFI_UNSUPPORTED;
  }
 
  TestString[1] = L'\0';
  
  //
  // test ASCII letter glyph from ' ' to '~'
  // 
  for (TestString[0] = L' '; TestString[0] <= L'~'; TestString[0]++) {
    do {
      //
      // get charater sysetem default Glyph Image Buffer 
      //
      FontGlyphBlt = NULL;
      
      Status = HIIFont->GetGlyph (
                          HIIFont,
                          TestString[0],
                          NULL,
                          &FontGlyphBlt,
                          &BaseLine
                          );              
      if (Status != EFI_SUCCESS) { 
        StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GetGlyph fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
        break;
      }
  
      //
      // Print charater system default Glyph to image buffer
      //
      Blt->Width = FontGlyphBlt->Width;
      Blt->Height = FontGlyphBlt->Height;
      Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Blt->Width * Blt->Height);
      StringInfo = NULL;
      BltX = 0;
      BltY = 0;
  
      if (Blt->Image.Bitmap == NULL) {
        StandardLib->RecordAssertion (
                      StandardLib,
                      EFI_TEST_ASSERTION_FAILED,
                      gTestGenericFailureGuid,
                      L"GetFontInfo fail",
                      L"%a:%d: Status - %r",
                      __FILE__,
                      (UINTN)__LINE__,
                      Status
                      );
        break;
      }
      
      Status = HIIFont->StringToImage (
                          HIIFont,
                          EFI_HII_DRAW_FLAG_DEFAULT,
                          TestString,
                          StringInfo,
                          &Blt,
                          BltX,
                          BltY,
                          RowInfoArray,
                          RowInfoArraySize,
                          ColumnInfoArray
                          );

      //
      // Compare with the image buffer from GetGlyph & StringToImage
      //
      if (SctCompareMem (
      	     FontGlyphBlt->Image.Bitmap, 
      	     Blt->Image.Bitmap, 
      	     sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Blt->Width * Blt->Height)) {
        GlyPhMismatch = TRUE;
      }
    }while (0);
    
    if (FontGlyphBlt->Image.Bitmap != NULL) {
      SctFreePool (FontGlyphBlt->Image.Bitmap);
      FontGlyphBlt->Image.Bitmap = NULL;
    }
    
    if (FontGlyphBlt != NULL) {
      SctFreePool (FontGlyphBlt);
      FontGlyphBlt = NULL;
    }   

    if ( RowInfoArray != NULL ) {
      SctFreePool (RowInfoArray);
      RowInfoArray = NULL;
    }
     
    if (Blt->Image.Bitmap != NULL) {
      SctFreePool (Blt->Image.Bitmap);
      Blt->Image.Bitmap = NULL;
    }
    
    if (GlyPhMismatch == TRUE) {
      break;
    }
  }

  if (GlyPhMismatch == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIFontBBTestFunctionAssertionGuid008,
                   L"HII_FONT_PROTOCOL.StringToImage - StringToImage() returns EFI_SUCCESS with valid parameters.",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );

  if (Blt != NULL) {
    SctFreePool (Blt);
  }
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  )
{
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  CHAR16                                TestString[2];
  EFI_FONT_DISPLAY_INFO                 *StringInfo = NULL;
  UINTN                                 InfoSize;
  EFI_IMAGE_OUTPUT                      *Blt = NULL;
  EFI_IMAGE_OUTPUT                      *FontGlyphBlt = NULL;
  UINTN                                 BltX;
  UINTN                                 BltY;
  EFI_HII_ROW_INFO                      **RowInfoArray = NULL;
  UINTN                                 *RowInfoArraySize = NULL;
  UINTN                                 *ColumnInfoArray = NULL;
  UINT32                                HorizontalResolution;
  UINT32                                VerticalResolution;
  UINTN                                 BaseLine;
  EFI_HII_PACKAGE_LIST_HEADER           *PackageList = NULL;
  EFI_HII_HANDLE                        HiiHandle = NULL;
  BOOLEAN                               GlyPhMismatch = FALSE;
  
  
  if ( GraphicsOutput != NULL ) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  //
  // Add the PackageList to the HII database to get a EFI_HII_HANDLE
  //
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageListTestFont;

  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &HiiHandle
                          );
  if ( EFI_ERROR(Status) ) {
  	 StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Test font packetlist add fail",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_LOAD_ERROR;
  }

  InfoSize = sizeof (EFI_FONT_DISPLAY_INFO) - sizeof (CHAR16) + SctStrSize (L"testfont");
  StringInfo = (EFI_FONT_DISPLAY_INFO *) SctAllocateZeroPool (InfoSize);
  if (StringInfo == NULL) {
  	 StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateZeroPool fail",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    goto EXIT;  	  
  }
  
  StringInfo->BackgroundColor.Blue = 0xFF;
  StringInfo->BackgroundColor.Red  = 0x00;
  StringInfo->BackgroundColor.Green= 0x00;
  
  StringInfo->ForegroundColor.Blue = 0x00;
  StringInfo->ForegroundColor.Red  = 0x00;
  StringInfo->ForegroundColor.Green= 0xFF;
  
  StringInfo->FontInfoMask = EFI_FONT_INFO_ANY_STYLE;

  StringInfo->FontInfo.FontSize = 19;
  StringInfo->FontInfo.FontStyle = 0;  
  SctStrCpy (StringInfo->FontInfo.FontName, L"testfont");
  
  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if ( Blt == NULL ){
  	 StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateZeroPool fail",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    goto EXIT;  	  
  }
 
  TestString[1] = L'\0';
  
  //
  // test ASCII letter glyph from ' ' to '~'
  // 
  for (TestString[0] = L' '; TestString[0] <= L'~'; TestString[0]++) {
    do {
      //
      // get charater sysetem default Glyph Image Buffer 
      //
      
      Status = HIIFont->GetGlyph (
                          HIIFont,
                          TestString[0],
                          StringInfo,
                          &FontGlyphBlt,
                          &BaseLine
                          );              
      if (Status != EFI_SUCCESS) { 
        StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GetGlyph fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
        break;
      }
  
      //
      // Print charater system default Glyph to image buffer
      //
      Blt->Width = FontGlyphBlt->Width;
      Blt->Height = FontGlyphBlt->Height;
      Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Blt->Width * Blt->Height);
      BltX = 0;
      BltY = 0;
  
      if (Blt->Image.Bitmap == NULL) {
        StandardLib->RecordAssertion (
                      StandardLib,
                      EFI_TEST_ASSERTION_FAILED,
                      gTestGenericFailureGuid,
                      L"GetFontInfo fail",
                      L"%a:%d: Status - %r",
                      __FILE__,
                      (UINTN)__LINE__,
                      Status
                      );
        break;
      }
      
      Status = HIIFont->StringToImage (
                          HIIFont,
                          EFI_HII_DRAW_FLAG_DEFAULT,
                          TestString,
                          StringInfo,
                          &Blt,
                          BltX,
                          BltY,
                          RowInfoArray,
                          RowInfoArraySize,
                          ColumnInfoArray
                          );

      //
      // Compare with the image buffer from GetGlyph & StringToImage
      //
      if (SctCompareMem (
            FontGlyphBlt->Image.Bitmap, 
            Blt->Image.Bitmap, 
            sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Blt->Width * Blt->Height)) {
        GlyPhMismatch = TRUE;
      }
    }while (0);

    if (FontGlyphBlt->Image.Bitmap != NULL) {
      SctFreePool (FontGlyphBlt->Image.Bitmap);
      FontGlyphBlt->Image.Bitmap = NULL;
    }
    
    if (FontGlyphBlt != NULL) {
      SctFreePool (FontGlyphBlt);
      FontGlyphBlt = NULL;
    }   

    if ( RowInfoArray != NULL ) {
      SctFreePool (RowInfoArray);
      RowInfoArray = NULL;
    }
     
    if (Blt->Image.Bitmap != NULL) {
      SctFreePool (Blt->Image.Bitmap);
      Blt->Image.Bitmap = NULL;
    }
    
    if (GlyPhMismatch == TRUE) {
      break;
    }
  }

  if (GlyPhMismatch == TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIFontBBTestFunctionAssertionGuid023,
                   L"HII_FONT_PROTOCOL.StringToImage - StringToImage() returns EFI_SUCCESS with valid parameters.",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );

EXIT:
	 //
  // remove test font package
  //
  if (HiiHandle != NULL) {
    HIIDatabase->RemovePackageList (
                   HIIDatabase,
                   HiiHandle
                   );
  }

  if (StringInfo != NULL) {
    SctFreePool (StringInfo);
  }
    
  if (Blt != NULL) {
    SctFreePool (Blt);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  )
{
  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  EFI_STRING                     TestString = NULL;
  EFI_FONT_DISPLAY_INFO          *StringInfo = NULL;
  EFI_IMAGE_OUTPUT               *Blt = NULL;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_HII_ROW_INFO               *RowInfoArray = NULL;
  UINTN                          RowInfoArraySize;
  UINTN                          *ColumnInfoArray = NULL;
  UINT32                         HorizontalResolution;
  UINT32                         VerticalResolution;
  UINT32                         Index;
  UINT16                         TestFontHeight, TestFontWidth;
  UINT32                         StrLen;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  BltPixel;


  if ( GraphicsOutput != NULL ) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  BltPixel.Blue = 0;
  BltPixel.Red = 0;
  BltPixel.Green = 0;

  //
  // UEFI describes a standard font, which is required for all systems which support
  // text display on bitmapped output devices. The standard font (named 'system') 
  // is a fixed pitch font, where all characters are either narrow (8x19) or wide (16x19).
  //
  //
  //Points to the string output information, including the color and font. If NULL, then the
  //string will be output in the default system font and color.
  // 
  // Get Character 'T'  default system font as test character  
  //
  Status = HIIFont->GetGlyph (
  	                   HIIFont,
                      L'T',
                      NULL,
                      &Blt,
                      NULL
  	                   );
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"GetGlyph fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  TestFontHeight = Blt->Height;
  TestFontWidth  = Blt->Width;
  SctFreePool (Blt);
  Blt = NULL;

  //
  // Construct test string dynamically according to screen size  ( 4~5 charaters longer than screen width)
  // 
  TestString = (EFI_STRING)SctAllocateZeroPool (sizeof(L'T') * (HorizontalResolution / TestFontWidth + 5));
  if (TestString == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateZeroPool fail",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    goto EXIT;
  }
  
  StrLen = HorizontalResolution / TestFontWidth + 4;
  for (Index = 0; Index < StrLen; Index++) {
    TestString[Index] = L'T';
  }

  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if ( Blt == NULL ){
    goto EXIT;
  }

  //
  // 1. Check EFI_HII_DIRECT_TO_SCREEN only case
  // If Blt is not NULL, then EFI_HII_OUT_FLAG_CLIP is implied  
  // String is designed to displayed with one full line
  //
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  StringInfo = NULL;

  BltX = 0;
  BltY = VerticalResolution - 3 * TestFontHeight;
  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_DIRECT_TO_SCREEN,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  
  //
  // For the final row, the RowInfoArray.LineHeight and RowInfoArray.BaseLine may describe pixels
  // which are outside the limit specified by Blt. Height (unless EFI_HII_OUT_FLAG_CLIP_CLEAN_Y 
  // is specified) even though those pixels were not drawn.
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1    
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0 
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == Blt->Width
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid009,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage() EFI_HII_DIRECT_TO_SCREEN returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  if (RowInfoArray != NULL) {
    SctFreePool (RowInfoArray);
    RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
  
  //
  // 2. Check EFI_HII_OUT_FLAG_CLIP  
  //  
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  StringInfo = NULL;
  //
  // String is designed to displayed at screen bottom with 2 pixel lines cutted
  //
  BltX = 0;
  BltY = VerticalResolution - TestFontHeight + 2;
  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  
  //
  // For the final row, the RowInfoArray.LineHeight and RowInfoArray.BaseLine 'May' describe pixels
  // which are outside the limit specified by Blt. Height (unless EFI_HII_OUT_FLAG_CLIP_CLEAN_Y 
  // is specified) even though those pixels were not drawn.
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1  
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0 
   && (RowInfoArray[0].LineHeight == BltY + TestFontHeight - Blt->Height 
    || RowInfoArray[0].LineHeight == (UINTN)(TestFontHeight - 2))
   && RowInfoArray[0].LineWidth == Blt->Width
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid010,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"    \
                 L"EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  if (RowInfoArray != NULL) {
    SctFreePool (RowInfoArray);
    RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
    
  //
  // 3. Check EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X
  //
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  StringInfo = NULL;
  //
  // String is designed to displayed at screen bottom & cover all screen columns, 
  // Charaters ouside screen width are not displayed 
  //
  BltX = 0;
  BltY = VerticalResolution - 2 * TestFontHeight;

  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_DIRECT_TO_SCREEN ,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  //
  // if a character's right-most on pixel cannot fit, then it will not be drawn at all. 
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1  
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0 
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == (UINTN)(Blt->Width / TestFontWidth) * TestFontWidth
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid011,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"   \
                 L"EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_DIRECT_TO_SCREEN returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  if (RowInfoArray != NULL) {
  	 SctFreePool (RowInfoArray);
  	 RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
  
  //
  // 4. Check EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y
  //
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  StringInfo = NULL;
  //
  // String is designed not to display at all since EFI_HII_OUT_FLAG_CLIP_CLEAN_Y is set
  //
  BltX = 0;
  BltY = VerticalResolution - TestFontHeight + 3;
  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  //
  // This flag requires that EFI_HII_OUT_FLAG_CLIP be set.
  //
  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_DIRECT_TO_SCREEN ,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  //
  // if a row's bottom-most pixel exceed screen Height, then it will not be drawn at all.
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 0
   && RowInfoArray == NULL
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid012,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"   \
                 L"EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_DIRECT_TO_SCREEN returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  if (RowInfoArray != NULL) {
     SctFreePool (RowInfoArray);
     RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }
  
  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );

  //
  // 5. Check EFI_HII_OUT_FLAG_WRAP with line break opportunity 
  // 
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  StringInfo = NULL;
  //
  // String is designed to show 20 characters before line break opportunity 
  // and new line starts at the next row
  //
  BltX = 0;
  BltY = VerticalResolution - 6*TestFontHeight;  
  //
  // SPACE is a line break opportunity 
  // system default font package supports ASCII characters, so here use none other break opportunity than 0x0020  
  //
  TestString[20] = (CHAR16)0x0020;    
  TestString[30] = (CHAR16)0x2013;
  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN ,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );

  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 2
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == (UINTN) 30 * TestFontWidth
   && RowInfoArray[1].BaselineOffset == 0
   && RowInfoArray[1].LineHeight == TestFontHeight
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid013,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"   \
                 L"EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN"   \
                 L"and String with line break opportunity returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  if (RowInfoArray != NULL) {
     SctFreePool (RowInfoArray);
     RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );

  //
  // 6. Check EFI_HII_OUT_FLAG_WRAP without line break opportunity 
  //
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  StringInfo = NULL;
  //
  // String without  line break opportunity  
  //
  for (Index = 0; Index < StrLen; Index++) {
    TestString[Index] = L'T';
  }
  TestString[StrLen] = L'\0';
  
  BltX = 0;
  BltY = VerticalResolution - 4*TestFontHeight;
  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  //
  //  String is designed to display as if EFI_HII_OUT_FLAG_CLIP_CLEAN_X is set
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1  
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0 
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == (UINTN)(Blt->Width / TestFontWidth) * TestFontWidth
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid014,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"   \
                 L"EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN and String without line break opportunity "    \
                 L"returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  if (RowInfoArray != NULL) {
     SctFreePool (RowInfoArray);
     RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
    
  //
  // 7. Check  EFI_HII_IGNORE_LINE_BREAK
  //
  
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  StringInfo = NULL;
  //
  // String is designed to display 
  //
  for (Index = 0; Index < StrLen; Index++) {
    TestString[Index] = L'T';
  }
  TestString[StrLen] = L'\0';
  //
  // The following characters force a line-break : 000C FORM FEED
  //
  TestString[20] = (CHAR16) 0x000C;

  BltX = 0;
  BltY = VerticalResolution - 4 * TestFontHeight;
  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_IGNORE_LINE_BREAK | EFI_HII_DIRECT_TO_SCREEN,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  //
  // if a row's bottom-most pixel cannot fit, then it will not be drawn at all.
  // This flag requires that EFI_HII_OUT_FLAG_CLIP be set.
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1
   && RowInfoArray != NULL
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == Blt->Width
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid015,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"   \
                 L"EFI_HII_IGNORE_LINE_BREAK | EFI_HII_DIRECT_TO_SCREEN returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  
  if (RowInfoArray != NULL) {
     SctFreePool (RowInfoArray);
     RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }
   
EXIT:

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );

  if (Blt != NULL) {
    SctFreePool (Blt);
  }
  
  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
  }
  
  if (TestString != NULL) {
    SctFreePool (TestString);
  }
  
  return EFI_SUCCESS;
  
}


EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTestCheckpoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  )
{
  EFI_STATUS                          Status;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_STRING                          TestString = NULL;
  UINTN                               InfoSize;
  EFI_FONT_DISPLAY_INFO               *StringInfo = NULL;
  EFI_IMAGE_OUTPUT                    *Blt = NULL;
  UINTN                               BltX;
  UINTN                               BltY;
  EFI_HII_ROW_INFO                    *RowInfoArray = NULL;
  UINTN                               RowInfoArraySize;
  UINTN                               *ColumnInfoArray = NULL;
  UINT32                              HorizontalResolution;
  UINT32                              VerticalResolution;
  UINT32                              Index;
  UINT16                              TestFontHeight, TestFontWidth;
  UINT32                              StrLen;
  EFI_HII_PACKAGE_LIST_HEADER         *PackageList = NULL;
  EFI_HII_HANDLE                      HiiHandle = NULL;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       BltPixel;
  EFI_IMAGE_OUTPUT                    *FontGlyphBlt = NULL;
  UINTN                               BaseLine;

  
  if ( GraphicsOutput != NULL ) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  BltPixel.Blue = 0;
  BltPixel.Red = 0;
  BltPixel.Green = 0;
  
  //
  // Add the PackageList to the HII database to get a EFI_HII_HANDLE
  //
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageListTestFont;

  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &HiiHandle
                          );
  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Test font packetlist add fail",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return EFI_LOAD_ERROR;
  }

  InfoSize = sizeof (EFI_FONT_DISPLAY_INFO) - sizeof (CHAR16) + SctStrSize (L"testfont");
  StringInfo = (EFI_FONT_DISPLAY_INFO *) SctAllocateZeroPool (InfoSize);
  if (StringInfo == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateZeroPool fail",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    goto EXIT;  	  
  }
  

  StringInfo->BackgroundColor.Blue = 0x00;
  StringInfo->BackgroundColor.Red  = 0xFF;
  StringInfo->BackgroundColor.Green= 0x00;
  
  StringInfo->ForegroundColor.Blue = 0x00;
  StringInfo->ForegroundColor.Red  = 0x00;
  StringInfo->ForegroundColor.Green= 0xFF;
  
  StringInfo->FontInfoMask = EFI_FONT_INFO_ANY_STYLE;

  StringInfo->FontInfo.FontSize = 19;
  StringInfo->FontInfo.FontStyle = 0;  
  SctStrCpy (StringInfo->FontInfo.FontName, L"testfont");
  
  // 
  // Get Character 'T'  default system font as test character  
  //
  Status = HIIFont->GetGlyph (
                      HIIFont,
                      L'T',
                      StringInfo,
                      &Blt,
                      NULL
                      );
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"GetGlyph fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto EXIT;
  }

  TestFontHeight = Blt->Height;
  TestFontWidth  = Blt->Width;
  SctFreePool (Blt);
  Blt = NULL;

  // 
  // Configure String Info 
  //

  //
  // Construct test string dynamically according to screen size  ( 4~5 charaters longer than screen width)
  // 
  TestString = (EFI_STRING)SctAllocateZeroPool (sizeof(L'T') * (HorizontalResolution / TestFontWidth + 5));
  if (TestString == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateZeroPool fail",
                   L"%a:%d: ",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    goto EXIT;
  }
  
  StrLen = HorizontalResolution / TestFontWidth + 4;
  for (Index = 0; Index < StrLen; Index++) {
    TestString[Index] = L'T';
  }

  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if ( Blt == NULL ){
    goto EXIT;
  }

  //
  // 1. Check EFI_HII_DIRECT_TO_SCREEN only case
  // If Blt is not NULL, then EFI_HII_OUT_FLAG_CLIP is implied  
  // String is designed to displayed with one full line
  //
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 

  BltX = 0;
  BltY = VerticalResolution - 3 * TestFontHeight;

  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_DIRECT_TO_SCREEN,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  
  //
  // For the final row, the RowInfoArray.LineHeight and RowInfoArray.BaseLine may describe pixels
  // which are outside the limit specified by Blt. Height (unless EFI_HII_OUT_FLAG_CLIP_CLEAN_Y 
  // is specified) even though those pixels were not drawn.
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1 	
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0 
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == Blt->Width
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid016,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage() EFI_HII_DIRECT_TO_SCREEN returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  if (RowInfoArray != NULL) {
    SctFreePool (RowInfoArray);
    RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
  

  //
  // 2. Check EFI_HII_OUT_FLAG_CLIP  
  //  
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  //
  // String is designed to displayed at screen bottom with 2 pixel line cutted
  //
  BltX = 0;
  BltY = VerticalResolution - TestFontHeight + 2;

  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  
  //
  // For the final row, the RowInfoArray.LineHeight and RowInfoArray.BaseLine may describe pixels
  // which are outside the limit specified by Blt. Height (unless EFI_HII_OUT_FLAG_CLIP_CLEAN_Y 
  // is specified) even though those pixels were not drawn.
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1  
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0 
   && (RowInfoArray[0].LineHeight == BltY + TestFontHeight - Blt->Height
    || RowInfoArray[0].LineHeight == (UINTN)(TestFontHeight - 2))
   && RowInfoArray[0].LineWidth == Blt->Width
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid017,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage() EFI_HII_OUT_FLAG_CLIP returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  if (RowInfoArray != NULL) {
    SctFreePool (RowInfoArray);
    RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
  

  //
  // 3. Check EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X
  //
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  //
  // String is designed to displayed at screen bottom & cover all screen columns, 
  // Charaters ouside screen width are not displayed 
  //
  BltX = 0;
  BltY = VerticalResolution - 2 * TestFontHeight;

  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_DIRECT_TO_SCREEN ,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  //
  // if a character's right-most on pixel cannot fit, then it will not be drawn at all. 
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1  
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0 
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == (UINTN)(Blt->Width / TestFontWidth) * TestFontWidth
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid018,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"    \
                 L"EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_DIRECT_TO_SCREEN returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  if (RowInfoArray != NULL) {
    SctFreePool (RowInfoArray);
    RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }
  
  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
  
  //
  // 4. Check EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y
  //
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  //
  // String is designed not to display at all since EFI_HII_OUT_FLAG_CLIP_CLEAN_Y is set
  //
  BltX = 0;
  BltY = VerticalResolution - TestFontHeight + 3;
  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }
  
  //
  // This flag requires that EFI_HII_OUT_FLAG_CLIP be set.
  //
  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_DIRECT_TO_SCREEN ,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  //
  // if a row's bottom-most pixel exceed screen Height, then it will not be drawn at all.
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 0
   && RowInfoArray == NULL
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid019,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"    \
                 L"EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_DIRECT_TO_SCREEN returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  if (RowInfoArray != NULL) {
    SctFreePool (RowInfoArray);
    RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }
  
  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
  
  //
  // 5. Check EFI_HII_OUT_FLAG_WRAP with line break opportunity 
  // 
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  //
  // String is designed to show 20 characters before line break opportunity 
  // and new line starts at the next row
  //
  BltX = 0;
  BltY = VerticalResolution - 6 * TestFontHeight;  
  //
  // SPACE is a line-break opportunity
  // system default font package supports ASCII characters, so here use none other break opportunity than 0x0020  
  //
  TestString[20] = (CHAR16)0x0020; 
  TestString[30] = (CHAR16)0x2013;

  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN ,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );

  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 2
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == (UINTN) 30 * TestFontWidth
   && RowInfoArray[1].BaselineOffset == 0
   && RowInfoArray[1].LineHeight == TestFontHeight
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid020,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"    \
                 L"EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN"   \
                 L"and String with line break opportunity returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  if (RowInfoArray != NULL) {
     SctFreePool (RowInfoArray);
     RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
  

  //
  // 6. Check EFI_HII_OUT_FLAG_WRAP without line break opportunity 
  //
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  //
  // String without  line break opportunity  
  //
  for (Index = 0; Index < StrLen; Index++) {
    TestString[Index] = L'T';
  }
  TestString[StrLen] = L'\0';
    
  BltX = 0;
  BltY = VerticalResolution - 4*TestFontHeight;

  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  //
  //  String is designed to display as if EFI_HII_OUT_FLAG_CLIP_CLEAN_X is set
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1  
   && RowInfoArray != NULL
   && RowInfoArray[0].BaselineOffset == 0 
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == (UINTN)(Blt->Width / TestFontWidth) * TestFontWidth
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid021,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"    \
                 L"EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN and String without line break opportunity "    \
                 L"returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  if (RowInfoArray != NULL) {
     SctFreePool (RowInfoArray);
     RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }
  
  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
  
  //
  // 7. Check  EFI_HII_IGNORE_LINE_BREAK
  //
  
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput; 
  //
  // String is designed to display 
  //
  for (Index = 0; Index < StrLen; Index++) {
    TestString[Index] = L'T';
  }
  TestString[StrLen] = L'\0';
  
  //
  // The following characters force a line-break : 000C FORM FEED
  //
  TestString[20] = (CHAR16) 0x000C;

  BltX = 0;
  BltY = VerticalResolution - 4 * TestFontHeight;
  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_IGNORE_LINE_BREAK | EFI_HII_DIRECT_TO_SCREEN,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  //
  // if a row's bottom-most pixel cannot fit, then it will not be drawn at all.
  // This flag requires that EFI_HII_OUT_FLAG_CLIP be set.
  //
  if (EFI_SUCCESS == Status 
   && RowInfoArraySize == 1
   && RowInfoArray != NULL
   && RowInfoArray[0].LineHeight == TestFontHeight
   && RowInfoArray[0].LineWidth == Blt->Width
   ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid022,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"    \
                 L"EFI_HII_IGNORE_LINE_BREAK | EFI_HII_DIRECT_TO_SCREEN returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  
  if (RowInfoArray != NULL) {
     SctFreePool (RowInfoArray);
     RowInfoArray = NULL;
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );

  //
  // 8. Check  EFI_HII_OUT_FLAG_TRANSPARENT
  //

  TestString[0] = L'T';
  TestString[1] = L'\0';
  
  //
  // Get font glyphs
  //
  StringInfo->BackgroundColor.Blue = 0x00;
  StringInfo->BackgroundColor.Red  = 0x00;
  StringInfo->BackgroundColor.Green= 0x00;
  
  StringInfo->ForegroundColor.Blue = 0x00;
  StringInfo->ForegroundColor.Red  = 0x00;
  StringInfo->ForegroundColor.Green= 0xFF;

  
  Status = HIIFont->GetGlyph (
                      HIIFont,
                      TestString[0],
                      StringInfo,
                      &FontGlyphBlt,
                      &BaseLine
                      );              
  if (Status != EFI_SUCCESS) { 
    StandardLib->RecordAssertion (
                 StandardLib,
                 EFI_TEST_ASSERTION_FAILED,
                 gTestGenericFailureGuid,
                 L"GetGlyph fail",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
    goto EXIT;
  }

  //
  // Change Background Blue & ForeGround green
  //
  StringInfo->BackgroundColor.Blue = 0xFF;
  StringInfo->BackgroundColor.Red  = 0x00;
  StringInfo->BackgroundColor.Green= 0x00;
  
  StringInfo->ForegroundColor.Blue = 0x00;
  StringInfo->ForegroundColor.Red  = 0x00;
  StringInfo->ForegroundColor.Green= 0xFF;

  BltX = 0;
  BltY = 0;

  //
  // Setup an one charater image buffer
  //
  Blt->Width = FontGlyphBlt->Width;
  Blt->Height = FontGlyphBlt->Height;
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Blt->Width * Blt->Height); 
  
  ColumnInfoArray =(UINTN *) SctAllocateZeroPool (sizeof(UINTN) * StrLen);
  if ( ColumnInfoArray == NULL ){
    goto EXIT;
  }

  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_TRANSPARENT,
                      TestString,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      &RowInfoArray,
                      &RowInfoArraySize,
                      ColumnInfoArray
                      );
  //
  // check output buffer StringInfo background should be ignored according to EFI spec
  //
  if (EFI_SUCCESS == Status
    && !SctCompareMem (
          FontGlyphBlt->Image.Bitmap, 
          Blt->Image.Bitmap, 
          sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Blt->Width * Blt->Height)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid024,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage()"    \
                 L"EFI_HII_OUT_FLAG_TRANSPARENT returns EFI_SUCCESS.",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  if (FontGlyphBlt->Image.Bitmap != NULL) {
    SctFreePool (FontGlyphBlt->Image.Bitmap);
    FontGlyphBlt->Image.Bitmap = NULL;
  }
    
  if (FontGlyphBlt != NULL) {
    SctFreePool (FontGlyphBlt);
    FontGlyphBlt = NULL;
  }   

  if (Blt->Image.Bitmap != NULL) {
    SctFreePool (Blt->Image.Bitmap);
    Blt->Image.Bitmap = NULL;
  }
  
  if (RowInfoArray != NULL) {
    SctFreePool (RowInfoArray);
    RowInfoArray = NULL;
  }
   
  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
    ColumnInfoArray = NULL;
  }

  
EXIT:
  //
  // Clear Screen for next output
  //
  GraphicsOutput->Blt (
                    GraphicsOutput,
                    &BltPixel,
                    EfiBltVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
  
  //
  // remove test font package
  //
  if (HiiHandle != NULL) {
    HIIDatabase->RemovePackageList (
                   HIIDatabase,
                   HiiHandle
                   );
  }

  if (StringInfo != NULL) {
    SctFreePool (StringInfo);
  }

  if (ColumnInfoArray != NULL) {
    SctFreePool (ColumnInfoArray);
  }

  if (Blt != NULL) {
    SctFreePool (Blt);
  }

  if (TestString != NULL) {
    SctFreePool (TestString);
  }
  
  return EFI_SUCCESS;
  
}



EFI_STATUS
EFIAPI
BBTestStringIdToImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  UINTN                          Index;
  
  EFI_STRING_ID            StringId;
  CHAR8                    *Language;
  CHAR16                   *LanguageName;
  EFI_FONT_DISPLAY_INFO    *StringInfo;
  EFI_IMAGE_OUTPUT         *Blt;
  UINTN                    BltX;
  UINTN                    BltY;

  EFI_STRING               TestString;
  EFI_HII_ROW_INFO         **RowInfoArray = NULL;
  UINTN                    *RowInfoArraySize = NULL;
  UINTN                    *ColumnInfoArray = NULL;

  EFI_HII_OUT_FLAGS ValidFlags[] = {
    EFI_HII_OUT_FLAG_CLIP, 
    EFI_HII_OUT_FLAG_WRAP,
    EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_OUT_FLAG_CLIP,
    EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_OUT_FLAG_CLIP,
    EFI_HII_OUT_FLAG_TRANSPARENT,
    EFI_HII_IGNORE_IF_NO_GLYPH,
    EFI_HII_IGNORE_LINE_BREAK,
    0
  };
  
  //
  // Allocate Memory
  //
  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if ( Blt == NULL ){
    return  EFI_UNSUPPORTED;
  }

  Blt->Width = 50;
  Blt->Height = 40;
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)SctAllocateZeroPool (Blt->Width *Blt->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Blt->Image.Bitmap == NULL ){
  	gtBS->FreePool (Blt);
    return  EFI_UNSUPPORTED;
  } 

  //
  // Add the PackageList to the HII database to get a EFI_HII_HANDLE
  //
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;

  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Add a String to the PackageList to get a StringId
  //
  Language = "en-US";
  TestString = L"TestString";
  LanguageName = L"English(United States)";
  Status = HIIString->NewString(
                        HIIString,
                        Handle,
                        &StringId,
                        Language,
                        LanguageName,
                        TestString,
                        NULL);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  StringInfo = NULL;
  BltX = 0;
  BltY = 0;
  
  //
  // Call HIIFont->StringIdToImage with valid parameters
  //
  for ( Index = 0; ValidFlags[Index] != 0; Index++ ){
    Status = HIIFont->StringIdToImage (
                        HIIFont,
                        ValidFlags[Index],
                        Handle,
                        StringId,
                        Language,
                        StringInfo,
                        &Blt,
                        BltX,
                        BltY,
                        RowInfoArray,
                        RowInfoArraySize,
                        ColumnInfoArray
                        );
                            

    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIFontBBTestFunctionAssertionGuid003,
                   L"HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage() returns EFI_SUCCESS with valid parameters.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

	if (RowInfoArray != NULL)
		gtBS->FreePool (RowInfoArray);
  }

  gtBS->FreePool (Blt->Image.Bitmap);
  gtBS->FreePool (Blt);

  //
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestStringIdToImageFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  UINTN                          Index;
  
  EFI_STRING_ID            StringId;
  CHAR8                    *Language;
  CHAR16                   *LanguageName;
  EFI_FONT_DISPLAY_INFO    *StringInfo;
  EFI_IMAGE_OUTPUT         *Blt;
  UINTN                    BltX;
  UINTN                    BltY;

  EFI_STRING               TestString;
  EFI_HII_ROW_INFO         **RowInfoArray = NULL;
  UINTN                    *RowInfoArraySize = NULL;
  UINTN                    *ColumnInfoArray = NULL;
  
  UINT32                   HorizontalResolution;
  UINT32                   VerticalResolution;
  

  EFI_HII_OUT_FLAGS ValidFlags[] = {
    EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN, 
    EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_IGNORE_LINE_BREAK | EFI_HII_DIRECT_TO_SCREEN,
    EFI_HII_DIRECT_TO_SCREEN,
    0
  };

  if ( GraphicsOutput != NULL ) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  //
  // Add the PackageList to the HII database to get a EFI_HII_HANDLE
  //
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*)mPackageList1;

  Status = HIIDatabase->NewPackageList(
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Add a String to the PackageList to get a StringId
  //
  Language = "en-US";
  TestString = L"TestString";
  LanguageName = L"English(United States)";
  Status = HIIString->NewString(
                        HIIString,
                        Handle,
                        &StringId,
                        Language,
                        LanguageName,
                        TestString,
                        NULL);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Allocate Memory
  //
  Blt = (EFI_IMAGE_OUTPUT *) SctAllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if ( Blt == NULL ){
    return  EFI_UNSUPPORTED;
  }
  
  
  StringInfo = NULL;
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput;
  BltX = 0;
  BltY = 0;
  
  //
  // Call HIIFont->StringIdToImage with valid parameters
  //
  for ( Index = 0; ValidFlags[Index] != 0; Index++ ){
    Status = HIIFont->StringIdToImage (
                        HIIFont,
                        ValidFlags[Index],
                        Handle,
                        StringId,
                        Language,
                        StringInfo,
                        &Blt,
                        BltX,
                        BltY,
                        RowInfoArray,
                        RowInfoArraySize,
                        ColumnInfoArray
                        );
                            

    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIFontBBTestFunctionAssertionGuid004,
                   L"HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage() returns EFI_SUCCESS with valid parameters.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

	if ( RowInfoArray != NULL )
		gtBS->FreePool (RowInfoArray);
  }

  gtBS->FreePool (Blt);

  //
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetGlyphFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  CHAR16                   Char = L'A';
  EFI_FONT_DISPLAY_INFO    *StringInfo = NULL;
  EFI_IMAGE_OUTPUT         *Blt = NULL;
  UINTN                    Baseline = 0;
  
  //
  // Call GetGlyph with valid parameters
  //
  Status = HIIFont->GetGlyph (
                      HIIFont,
                      Char,
                      StringInfo,
                      &Blt,
                      &Baseline
                      );

  if ( EFI_SUCCESS == Status ){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }else if ( EFI_WARN_UNKNOWN_GLYPH == Status ){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }else if ( EFI_OUT_OF_RESOURCES == Status ) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;

  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid005,
                 L"HII_FONT_PROTOCOL.GetGlyph - GetGlyph() returns EFI_SUCCESS with valid parameters.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  if ( EFI_SUCCESS == Status ){
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetFontInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  )
{

  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_FONT_DISPLAY_INFO    *StringInfoIn;
  EFI_FONT_DISPLAY_INFO    *StringInfoOut;
  EFI_STRING               String = L"TestString";
  EFI_FONT_HANDLE          FontHandle = NULL;

  StringInfoOut = NULL;
  //
  // Init 
  StringInfoIn = (EFI_FONT_DISPLAY_INFO *) SctAllocateZeroPool (sizeof(EFI_FONT_DISPLAY_INFO));
  if ( StringInfoIn == NULL ){
    return  EFI_UNSUPPORTED;
  }
  
  StringInfoIn->FontInfo.FontStyle = EFI_FONT_INFO_SYS_FONT;
  StringInfoIn->FontInfo.FontSize = 20;
  StringInfoIn->ForegroundColor.Blue= 0;
  StringInfoIn->ForegroundColor.Green = 0;
  StringInfoIn->ForegroundColor.Red = 0;
  StringInfoIn->BackgroundColor.Blue = 150;
  StringInfoIn->BackgroundColor.Green = 150;
  StringInfoIn->BackgroundColor.Red = 150;
  StringInfoIn->FontInfoMask = EFI_FONT_INFO_SYS_FONT | EFI_FONT_INFO_SYS_SIZE | EFI_FONT_INFO_SYS_STYLE | \
                               EFI_FONT_INFO_SYS_FORE_COLOR | EFI_FONT_INFO_SYS_BACK_COLOR;

  Status = EFI_SUCCESS;

  while( !EFI_ERROR(Status) ){

    Status = HIIFont->GetFontInfo (
                        HIIFont,
                        &FontHandle,
                        StringInfoIn,
                        &StringInfoOut,
                        String
                        );
	
    if ( StringInfoOut != NULL ) {
      gtBS->FreePool (StringInfoOut);
      StringInfoOut = NULL;
    }
  }	
  
  if ( (EFI_NOT_FOUND == Status && NULL == FontHandle) || EFI_OUT_OF_RESOURCES == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid006,
                 L"HII_FONT_PROTOCOL.GetFont - GetFont() returns EFI_SUCCESS with valid parameters.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool (StringInfoIn);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetFontInfoFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  )
{

  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_FONT_DISPLAY_INFO    *StringInfoIn;
  EFI_FONT_DISPLAY_INFO    *StringInfoOut;
  EFI_STRING               String = L"TestString";
  EFI_FONT_HANDLE          FontHandle = NULL;


  //When StringInfoIn is NULL, the default system font and color should be returned.
  StringInfoIn = NULL;
  StringInfoOut = NULL;

  Status = EFI_SUCCESS;

  while( !EFI_ERROR(Status) ){

    Status = HIIFont->GetFontInfo (
                        HIIFont,
                        &FontHandle,
                        StringInfoIn,
                        &StringInfoOut,
                        String
                        );
	
    if ( StringInfoOut != NULL ) {
      gtBS->FreePool (StringInfoOut);
      StringInfoOut = NULL;	  
    }
  }	

  
  if ( (EFI_NOT_FOUND == Status && NULL == FontHandle) || EFI_OUT_OF_RESOURCES == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestFunctionAssertionGuid007,
                 L"HII_FONT_PROTOCOL.GetFont - GetFont() returns EFI_SUCCESS with valid parameters.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

