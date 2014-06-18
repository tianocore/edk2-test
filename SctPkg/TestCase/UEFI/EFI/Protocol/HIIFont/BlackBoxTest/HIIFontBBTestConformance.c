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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 -2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    HIIFontBBTestConformance.c

Abstract:
    for EFI Driver HII Font Protocol's conformance Test

--*/

#include "HIIFontBBTestMain.h"

extern UINT8 mPackageList1[];

EFI_STATUS
BBTestStringToImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  );

EFI_STATUS
BBTestStringIdToImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_STRING_PROTOCOL                    *HIIString, 
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  );

EFI_STATUS
BBTestGetGlyphConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  );


EFI_STATUS
BBTestGetFontInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  );

//
//Test Cases
//
EFI_STATUS
BBTestStringToImageConformanceTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestStringToImageConformanceTestCheckpoint1 (StandardLib, HIIFont);
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestStringIdToImageConformanceTest (
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
                   &StandardLib
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

  //
  //Call check points
  //
  BBTestStringIdToImageConformanceTestCheckpoint1 (StandardLib, HIIDatabase, HIIString, HIIFont);
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetGlyphConformanceTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetGlyphConformanceTestCheckpoint1 ( StandardLib, HIIFont );
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetFontInfoConformanceTest (
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
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetFontInfoConformanceTestCheckpoint1 ( StandardLib, HIIFont);
  
  return EFI_SUCCESS;
}

//
//Check Points: 
//
EFI_STATUS
BBTestStringToImageConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_HII_OUT_FLAGS        Flags;
  EFI_STRING               String;
  EFI_FONT_DISPLAY_INFO    *StringInfo;
  EFI_IMAGE_OUTPUT         *Blt;
  UINTN                    BltX;
  UINTN                    BltY;
  
  //
  // Allocate Memory
  //
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
  
  //
  // Call StringToImage with String being NULL, EFI_INVALID_PARAMETER should be returned.
  //
  Flags = EFI_HII_OUT_FLAG_CLIP;
  StringInfo = NULL;
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringToImage (
                      HIIFont,
                      Flags,
                      NULL,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      NULL,
                      NULL,
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
                 gHIIFontBBTestConformanceAssertionGuid001,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage() returns EFI_INVALID_PARAMETER with String been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call StringToImage with Blt being NULL, EFI_INVALID_PARAMETER should be returned.
  //
  String = L"TestString";
  Flags = EFI_HII_OUT_FLAG_CLIP;
  StringInfo = NULL;
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringToImage (
                      HIIFont,
                      Flags,
                      String,
                      StringInfo,
                      NULL,
                      BltX,
                      BltY,
                      NULL,
                      NULL,
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
                 gHIIFontBBTestConformanceAssertionGuid002,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage() returns EFI_INVALID_PARAMETER with Blt been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call StringToImage with Flag being EFI_HII_OUT_FLAG_CLIP_CLEAN_X/EFI_HII_OUT_FLAG_CLIP_CLEAN_X, 
  // with EFI_HII_OUT_FLAG_WRAP, EFI_INVALID_PARAMETER should be returned.
  String = L"TestString";
  StringInfo = NULL;
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP_CLEAN_X|EFI_HII_OUT_FLAG_WRAP,
                      String,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      NULL,
                      NULL,
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
                 gHIIFontBBTestConformanceAssertionGuid003,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage() returns EFI_INVALID_PARAMETER with invalid Flags combination.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Call StringToImage with Flag being EFI_HII_OUT_FLAG_CLIP_CLEAN_X/EFI_HII_OUT_FLAG_CLIP_CLEAN_X, 
  // without EFI_HII_OUT_FLAG_CLIP, EFI_INVALID_PARAMETER should be returned.
  String = L"TestString";
  StringInfo = NULL;
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP_CLEAN_X,
                      String,
                      StringInfo,
                      &Blt,
                      BltX,
                      BltY,
                      NULL,
                      NULL,
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
                 gHIIFontBBTestConformanceAssertionGuid004,
                 L"HII_FONT_PROTOCOL.StringToImage - StringToImage() returns EFI_INVALID_PARAMETER with invalid Flags combination.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  

  //
  // Free Memory
  //
  gtBS->FreePool (Blt->Image.Bitmap);
  gtBS->FreePool (Blt);
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestStringIdToImageConformanceTestCheckpoint1 (
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
  
  EFI_HII_OUT_FLAGS        Flags;
  EFI_STRING_ID            StringId;
  CHAR8                    *Language;
  CHAR16                   *LanguageName;
  EFI_FONT_DISPLAY_INFO    *StringInfo;
  EFI_IMAGE_OUTPUT         *Blt;
  UINTN                    BltX;
  UINTN                    BltY;

  EFI_STRING               TestString;
 
  //
  // Allocate Memory
  //

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

  //
  // Call StringIdToImage with Blt being NULL, EFI_INVALID_PARAMETER should be returned.
  //

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
                        NULL
                        );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Flags = EFI_HII_OUT_FLAG_CLIP;
  StringInfo = NULL;
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringIdToImage (
                      HIIFont,
                      Flags,
                      Handle,
                      StringId,
                      Language,
                      NULL,     //StringInfo Optional 
                      NULL,     //Blt
                      BltX,
                      BltY,
                      NULL,     //RowInfoArray Optional
                      NULL,     //RowInfoArraySize Optional
                      NULL      //ColumnInfoArray Optional
                      );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestConformanceAssertionGuid005,
                 L"HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage() returns EFI_INVALID_PARAMETER with Blt been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  //
  // Call StringIdToImage with PackageList being NULL, EFI_INVALID_PARAMETER should be returned.
  //
  Flags = EFI_HII_OUT_FLAG_CLIP;
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringIdToImage (
                      HIIFont,
                      Flags,
                      NULL,
                      StringId,
                      Language,
                      NULL,     //StringInfo Optional 
                      &Blt,
                      BltX,
                      BltY,
                      NULL,     //RowInfoArray Optional
                      NULL,     //RowInfoArraySize Optional
                      NULL      //ColumnInfoArray Optional
                      );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestConformanceAssertionGuid006,
                 L"HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage() returns EFI_INVALID_PARAMETER with PackageList been NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // Call StringIdToImage with PackageList not in Database, EFI_NOT_FOUND should be returned.
  //
  Flags = EFI_HII_OUT_FLAG_CLIP;
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringIdToImage (
                      HIIFont,
                      Flags,
                      (EFI_HANDLE)((UINT8*)(Handle) + 8),
                      StringId,
                      Language,
                      NULL,     //StringInfo Optional 
                      &Blt,
                      BltX,
                      BltY,
                      NULL,     //RowInfoArray Optional
                      NULL,     //RowInfoArraySize Optional
                      NULL      //ColumnInfoArray Optional
                      );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestConformanceAssertionGuid013,     //DSA modify it and replace it in the case spec and guidfile.txt
                 L"HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage() returns EFI_NOT_FOUND with PackageList not in Database.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  //
  // Call StringIdToImage with StringId not in PackageList, EFI_NOT_FOUND should be returned.
  //
  Flags = EFI_HII_OUT_FLAG_CLIP;
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringIdToImage (
                      HIIFont,
                      Flags,
                      Handle,
                      StringId+1,
                      Language,
                      NULL,     //StringInfo Optional 
                      &Blt,
                      BltX,
                      BltY,
                      NULL,     //RowInfoArray Optional
                      NULL,     //RowInfoArraySize Optional
                      NULL      //ColumnInfoArray Optional
                      );
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestConformanceAssertionGuid007,
                 L"HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage() returns EFI_NOT_FOUND with StringId not in PackageList.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Call StringIdToImage with Flag being EFI_HII_OUT_FLAG_CLIP_CLEAN_X/EFI_HII_OUT_FLAG_CLIP_CLEAN_Y, 
  // with EFI_HII_OUT_FLAG_WRAP, EFI_INVALID_PARAMETER should be returned.
  //
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringIdToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP_CLEAN_X|EFI_HII_OUT_FLAG_WRAP,
                      Handle,
                      StringId,
                      Language,
                      NULL,     //StringInfo Optional 
                      &Blt,
                      BltX,
                      BltY,
                      NULL,     //RowInfoArray Optional
                      NULL,     //RowInfoArraySize Optional
                      NULL      //ColumnInfoArray Optional
                      );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestConformanceAssertionGuid008,
                 L"HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage() returns EFI_INVALID_PARAMETER with invalid Flags combination.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // Call StringIdToImage with Flag being EFI_HII_OUT_FLAG_CLIP_CLEAN_X/EFI_HII_OUT_FLAG_CLIP_CLEAN_Y, 
  // without EFI_HII_OUT_FLAG_CLIP, EFI_INVALID_PARAMETER should be returned.
  //
  BltX = 0;
  BltY = 0;
  
  Status = HIIFont->StringIdToImage (
                      HIIFont,
                      EFI_HII_OUT_FLAG_CLIP_CLEAN_X,
                      Handle,
                      StringId,
                      Language,
                      NULL,     //StringInfo Optional 
                      &Blt,
                      BltX,
                      BltY,
                      NULL,     //RowInfoArray Optional
                      NULL,     //RowInfoArraySize Optional
                      NULL      //ColumnInfoArray Optional
                      );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestConformanceAssertionGuid009,
                 L"HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage() returns EFI_INVALID_PARAMETER with invalid Flags combination.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  //
  // Free Memory
  //
  gtBS->FreePool (Blt->Image.Bitmap);
  gtBS->FreePool (Blt);

  return EFI_SUCCESS;
}



EFI_STATUS
BBTestGetGlyphConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  CHAR16                   Char;
  EFI_FONT_DISPLAY_INFO    *StringInfo;
  EFI_IMAGE_OUTPUT         *Blt;
  UINTN                    *BaseLine = NULL;

  
  //
  // Init the char, StringInfo(unknow glyph)
  //
  StringInfo = NULL;
  Char = L'A';
  

  //
  // Call GetGlyph with Blt being NULL, EFI_INVALID_PARAMETER should be returned.
  //
  Status = HIIFont->GetGlyph (
                      HIIFont,
                      Char,
                      StringInfo,
                      NULL,
                      BaseLine
                      );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestConformanceAssertionGuid010,
                 L"HII_FONT_PROTOCOL.GetGlyph - GetGlyph() returns EFI_INVALID_PARAMETER with Blt being NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

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
  
  //
  // Call GetGlyph with *Blt being non NULL, EFI_INVALID_PARAMETER should be returned.
  //
  Status = HIIFont->GetGlyph (
                      HIIFont,
                      Char,
                      StringInfo,
                      &Blt,
                      BaseLine
                      );
  
  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIFontBBTestConformanceAssertionGuid014,
                 L"HII_FONT_PROTOCOL.GetGlyph - GetGlyph() returns EFI_INVALID_PARAMETER with *Blt being non NULL.",
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
BBTestGetFontInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_FONT_PROTOCOL                      *HIIFont
  ){

  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  EFI_FONT_HANDLE          FontHandle;
  EFI_FONT_DISPLAY_INFO    *StringInfoIn;
  EFI_FONT_DISPLAY_INFO    *StringInfoOut;
  EFI_STRING               String;
  
  UINTN                    Index;

  //
  //Invalid Combination
  //
  EFI_FONT_INFO_MASK InValidFlags[] = {
    EFI_FONT_INFO_SYS_FONT | EFI_FONT_INFO_ANY_FONT, 
    EFI_FONT_INFO_SYS_SIZE | EFI_FONT_INFO_ANY_SIZE,
    EFI_FONT_INFO_SYS_STYLE | EFI_FONT_INFO_ANY_STYLE,
    EFI_FONT_INFO_RESIZE | EFI_FONT_INFO_ANY_SIZE,
    EFI_FONT_INFO_RESTYLE | EFI_FONT_INFO_ANY_STYLE,
    0
  };


  FontHandle = NULL;
  StringInfoIn = NULL;
  StringInfoOut = NULL;
  String = NULL;

// remove this check point, please refer UEFI2.1 ECR Update 6
/*
  //
  // Call GetFontInfo with StringInfoIn being NULL, EFI_INVALID_PARAMETER should be returned.
  //

  Status = HIIFont->GetFontInfo (
                      HIIFont,
                      FontHandle,
                      StringInfoIn,
                      &StringInfoOut,
                      String
                      );

  if ( EFI_INVALID_PARAMETER != Status ){
  	AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

   StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionType,
                  gHIIFontBBTestConformanceAssertionGuid011,
                  L"HII_FONT_PROTOCOL.GetFontInfo - GetFontInfo() returns EFI_INVALID_PARAMETER with StringInfoIn points to an NULL pointer.",
                  L"%a:%d: Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
  */ 

  //
  // Call GetFontInfo with invalid Flags combination, EFI_INVALID_PARAMETER should be returned.
  //
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
  StringInfoIn->FontInfoMask = EFI_FONT_INFO_SYS_FONT | EFI_FONT_INFO_SYS_SIZE | EFI_FONT_INFO_SYS_STYLE;

  for ( Index = 0; InValidFlags[Index] != 0; Index++ ){
    StringInfoIn->FontInfoMask = InValidFlags[Index];
    FontHandle = NULL;
    String = NULL;
    Status = HIIFont->GetFontInfo (
                        HIIFont,
                        FontHandle,
                        StringInfoIn,
                        &StringInfoOut,
                        String
                        );
    if ( NULL != StringInfoOut ) {
      gtBS->FreePool (StringInfoOut);
    }

    if ( EFI_INVALID_PARAMETER != Status ){
  	  AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIFontBBTestConformanceAssertionGuid012,
                   L"HII_FONT_PROTOCOL.GetFontInfo - GetFontInfo() returns EFI_INVALID_PARAMETER with invalid EFI_FONT_INFO_MASK Combination.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  }

  gtBS->FreePool (StringInfoIn);

  return EFI_SUCCESS;
  
}
