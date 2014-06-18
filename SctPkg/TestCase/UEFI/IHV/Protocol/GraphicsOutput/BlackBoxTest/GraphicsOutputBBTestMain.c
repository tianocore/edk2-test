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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  GraphicsOutputBBTestMain.c

Abstract:

  Test Driver Entry Point of Graphics Output Protocol
  
References:

  UEFI Specification
  Graphics Output Protocol Test Design Specification
  UEFI/Tiano DXE Test Case Writer's Guide

--*/
#include "SctLib.h"
#include "GraphicsOutputBBTest.h"

#define IHV_GRAPHICS_OUTPUT_BB_TEST_CATEGORY_GUID	\
  { 0x112c7fbd, 0xfcb3, 0x4bd8, { 0xb7, 0x2, 0x42, 0x17, 0xc1, 0xac, 0x2b, 0xac } }

//
//  Assertion GUIDs referenced in Funcitons
//
EFI_GUID gEfiGraphicsOutputQueryModeBBTestFunctionAssertionGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERYMODE_BB_TEST_FUNCTION_ASSERTION_GUID;

EFI_GUID                    gEfiGraphicsOutputSetModeBBTestFunctionAssertionGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_SETMODE_BB_TEST_FUNCTION_ASSERTION_GUID;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBBTestFunctionAssertionGuid001 =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOFILL_BB_TEST_FUNCTION_ASSERTION_GUID_001;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBBTestFunctionAssertionGuid002 =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOFILL_BB_TEST_FUNCTION_ASSERTION_GUID_002;

EFI_GUID                    gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid001 =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_BB_TEST_FUNCTION_ASSERTION_GUID_001;

EFI_GUID                    gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid002 =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_BB_TEST_FUNCTION_ASSERTION_GUID_002;

EFI_GUID                    gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid003 =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_BB_TEST_FUNCTION_ASSERTION_GUID_003;

EFI_GUID                    gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid004 =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_BB_TEST_FUNCTION_ASSERTION_GUID_004;

EFI_GUID                    gEfiGraphicsOutputBltVideoVideoBBTestFunctionAssertionGuid001 =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOTOVIDEO_BB_TEST_FUNCTION_ASSERTION_GUID_001;

EFI_GUID                    gEfiGraphicsOutputBltVideoVideoBBTestFunctionAssertionGuid002 =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOTOVIDEO_BB_TEST_FUNCTION_ASSERTION_GUID_002;

EFI_GUID                    gGraphicsOutputQueryModeConformanceTestAssertionGuid001 =
  EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_001;

EFI_GUID                    gGraphicsOutputQueryModeConformanceTestAssertionGuid002 =
  EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_002;

EFI_GUID                    gGraphicsOutputQueryModeConformanceTestAssertionGuid003 =
  EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_003;

EFI_GUID                    gGraphicsOutputQueryModeConformanceTestAssertionGuid004 =
  EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_004;

EFI_GUID                    gGraphicsOutputQueryModeConformanceTestAssertionGuid005 =
  EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_005;

EFI_GUID                    gGraphicsOutputQueryModeConformanceTestAssertionGuid006 =
  EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_006;

EFI_GUID                    gGraphicsOutputSetModeConformanceTestAssertionGuid001 =
  EFI_TEST_GRAPHICSOUTPUT_SETMODE_CONFORMANCETEST_ASSERTION_GUID_001;

EFI_GUID                    gGraphicsOutputSetModeConformanceTestAssertionGuid002 =
  EFI_TEST_GRAPHICSOUTPUT_SETMODE_CONFORMANCETEST_ASSERTION_GUID_002;

EFI_GUID                    gGraphicsOutputSetModeConformanceTestAssertionGuid003 =
  EFI_TEST_GRAPHICSOUTPUT_SETMODE_CONFORMANCETEST_ASSERTION_GUID_003;

EFI_GUID                    gGraphicsOutputBltConformanceTestAssertionGuid001 =
  EFI_TEST_GRAPHICSOUTPUT_BLT_CONFORMANCETEST_ASSERTION_GUID_001;

//
// Stress assertion id
//
// BltVideoFill stress
//
EFI_GUID                    gGraphicsOutputBltVideoFillStressAutoTestAssertionGuid001 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILL_STRESS_AUTO_TEST_ASSERTION_GUID_001;

EFI_GUID                    gGraphicsOutputBltVideoFillStressAutoTestAssertionGuid002 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILL_STRESS_AUTO_TEST_ASSERTION_GUID_002;

EFI_GUID                    gGraphicsOutputBltVideoFillStressAutoTestAssertionGuid003 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILL_STRESS_AUTO_TEST_ASSERTION_GUID_003;

//
// BltVideoBltBuffer stress
//
EFI_GUID                    gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid001 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_001;

EFI_GUID                    gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid002 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_002;

EFI_GUID                    gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid003 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_003;

EFI_GUID                    gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid004 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_004;

EFI_GUID                    gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid005 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_005;

//
// BltVideoToVideo stress
//
EFI_GUID                    gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid001 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_001;

EFI_GUID                    gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid002 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_002;

EFI_GUID                    gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid003 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_003;

EFI_GUID                    gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid004 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_004;

EFI_GUID                    gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid005 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_005;
//
// BltVideoFill&BufferToVideo manul
//
EFI_GUID                    gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid001 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_001;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid002 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_002;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid003 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_003;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid004 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_004;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid005 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_005;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid006 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_006;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid007 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_007;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid008 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_008;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid009 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_009;
//
// BltVideoFill&VideoToVideo manul
//
EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid001 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_001;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid002 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_002;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid003 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_003;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid004 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_004;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid005 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_005;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid006 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_006;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid007 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_007;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid008 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_008;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid009 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_009;

EFI_GUID                    gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid010 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_010;
//
// BltBufferToVideo extensive
//
EFI_GUID                    gEfiGraphicsOutputBltVideoToBufferBBTestExtensiveAssertionGuid001 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOBUFFER_EXTENSIVE_ASSERTION_GUID_001;

EFI_GUID                    gEfiGraphicsOutputBltVideoToBufferBBTestExtensiveAssertionGuid002 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOBUFFER_EXTENSIVE_ASSERTION_GUID_002;

EFI_GUID                    gEfiGraphicsOutputBltVideoToBufferBBTestExtensiveAssertionGuid003 =
  EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOBUFFER_EXTENSIVE_ASSERTION_GUID_003;

//
//  Function GUIDs referenced in Functions
//
EFI_GUID                    gBlackBoxEfiGraphicsOutputQueryModeBBTestFunctionAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERYMODE_FUNCTION_AUTO_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputSetModeFunctionAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_SETMODE_FUNCTION_AUTO_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputBltVideoFillFunctionAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOFILL_FUNCTION_AUTO_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputBltVideoBltBufferFunctionAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_FUNCTION_AUTO_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputBltVideoToVideoFunctionAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOTOVIDEO_FUNCTION_AUTO_GUID;

//
// Conformance GUIDs referenced in Conformances
//
EFI_GUID                    gBlackBoxEfiGraphicsOutputQueryModeConformanceAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERYMODE_CONFORMANCE_AUTO_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputSetModeConformanceAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_SETMODE_CONFORMANCE_AUTO_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputBltConformanceAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT_CONFORMANCE_AUTO_GUID;

//
// Entry GUIDs for extensive test
//
EFI_GUID                    gBlackBoxEfiGraphicsOutputBltVideoFillStressAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_EFIBLTVIDEOFILL_STRESS_AUTO_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputBltVideoBltBufferStressAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_EFIBLTVIDEOBLTBUFFER_STRESS_AUTO_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputBltVideoToVideoStressAutoGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_EFIBLTVIDEOTOVIDEO_STRESS_AUTO_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputVideoFillBufferToVideoExtensiveManualGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_VIDEOFILL_BUFFERTOVIDEO_EXTENSIVE_MANUAL_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputVideoFillVideoToVideoExtensiveManualGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_VIDEOFILL_VIDEOTOVIDEO_EXTENSIVE_MANUAL_GUID;

EFI_GUID                    gBlackBoxEfiGraphicsOutputVideoToBufferExtensiveGuid =
  EFI_GRAPHICS_OUTPUT_PROTOCOL_VIDEOTOBLTBUFFER_EXTENSIVE_AUTO_GUID;

//
//  Individual Test define by EFI Black-Box Test Protocol Structure
//  This structure contains meta-data regarding the test, include
//  revision, category, and human-readable text descriptions
//
//
//
//  EFI Black-Box Test Protocol Field
//
EFI_BB_TEST_PROTOCOL_FIELD  gBBTestProtocolField = {
  EFI_GRAPHICS_OUTPUT_BB_TEST_REVISION,
  IHV_GRAPHICS_OUTPUT_BB_TEST_CATEGORY_GUID,
  L"UEFI GraphicsOutput Protocol Black-Box Test",
  L"UEFI GraphicsOutput Protocol Black-Box Test - QueryMode, SetMode, Blt Operation Function Test"
};

//
// Each test is required to have a GUID.
// The GUID is included in the test protocol field as a structure as bellow
//
EFI_GUID                    gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

//
//  Individual test cases are specified by the Test Entry Field
//
EFI_BB_TEST_ENTRY_FIELD     gBBTestEntryField[] = {
  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERYMODE_FUNCTION_AUTO_GUID,
    L"QueryMode_Func",
    L"Efi GraphicsOutput Protocl QueryMode Function Test - QueryMode Function Test",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEfiGraphicsOutputQueryModeFunctionAutoTest
  },

  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERYMODE_CONFORMANCE_AUTO_GUID,
    L"QueryMode_Conf",
    L"Efi GraphicsOutput Protocol QueryMode Conformance Test - QueryMode Conformance Test",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestQueryModeConformanceAutoTest
  },

  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SETMODE_FUNCTION_AUTO_GUID,
    L"SetMode_Func",
    L"Efi GraphicsOutput Protocol SetMode Function Test - SetMode Function Test",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEfiGraphicsOutputSetModeFunctionAutoTest
  },

  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SETMODE_CONFORMANCE_AUTO_GUID,
    L"SetMode_Conf",
    L"Efi GraphicsOutput Protocol SetMode Conformance Test - SetMode Conformance Test",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetModeConformanceAutoTest
  },

  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT_CONFORMANCE_AUTO_GUID,
    L"Blt_Conf",
    L"Efi GraphicsOutput Protocol Blt Conformance Test - Blt Conformance Test",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestBltConformanceAutoTest
  },

  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOFILL_FUNCTION_AUTO_GUID,
    L"BltVideoFill_Func",
    L"Efi GraphicsOutput Protocol BltVideoFill Function Test - Blt VideoFill Operation Test",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEfiGraphicsOutputBltVideoFillFunctionAutoTest
  },

  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_FUNCTION_AUTO_GUID,
    L"BltVideoBltBuffer_Func ",
    L"Efi GraphicsOutput Protocol BltVideoBltBuffer Function Test - Blt VideotoBltBuffer Operation Test",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEfiGraphicsOutputBltVideoBltBufferFunctionAutoTest
  },

  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOTOVIDEO_FUNCTION_AUTO_GUID,
    L"BltVideoToVideo_Func",
    L"Efi GraphicsOutput Protocol BltVideoToVideo Function Test - Blt VideoToVideo Operation Test",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEfiGraphicsOutputBltVideoToVideoFunctionAutoTest
  },
  //
  // Extensive Function
  //
#ifdef EFI_TEST_EXHAUSTIVE
  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_EFIBLTVIDEOFILL_STRESS_AUTO_GUID,
    L"BltVideoFill_Stress",
    L"Efi GraphicsOutput Protocol BltVideoFill Stress Auto Test - BltVideoFill Stress Auto Test",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEfiGraphicsOutputBltVideoFillStressAutoTest
  },
  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_EFIBLTVIDEOBLTBUFFER_STRESS_AUTO_GUID,
    L"BltVideoBltBuffer_Stress",
    L"Efi GraphicsOutput Protocol BltVideoBltBuffer Stress Auto Test - BltVideoBltBuffer Stress Auto Test",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEfiGraphicsOutputBltVideoBltBufferStressAutoTest
  },
  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_EFIBLTVIDEOTOVIDEO_STRESS_AUTO_GUID,
    L"BltVideoToVideo_Stress",
    L"Efi GraphicsOutput Protocol BltVideoToVideo Stress Auto Test - BltVideoToVideo Stress Auto Test",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEfiGraphicsOutputBltVideoToVideoStressAutoTest
  },
  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_VIDEOFILL_BUFFERTOVIDEO_EXTENSIVE_MANUAL_GUID,
    L"BltVideoFill&BufferToVideo_Stress_Manual",
    L"Efi GraphicsOutput Protocol BltVideoFill&BufferToVideo Stress Manual Test - BltVideoFill&BufferToVideo Stress Manual Test",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    BBTestVideoFillBufferToVideoManualTest
  },
  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_VIDEOFILL_VIDEOTOVIDEO_EXTENSIVE_MANUAL_GUID,
    L"BltVideoFill&VideoToVideo_Stress_Manual",
    L"Efi GraphicsOutput Protocol BltVideoFill&VideoToVideo Stress Manual Test - BltVideoFill&VideoToVideo Stress Manual Test",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    BBTestVideoFillVideoToVideoManualTest
  },
  {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_VIDEOTOBLTBUFFER_EXTENSIVE_AUTO_GUID,
    L"BltVideoToBltBuffer_Extensive_Auto",
    L"Efi GraphicsOutput Protocol BltVideoToBltBuffer Extensive Auto Test - Perform auto extensive checkes on the BltVideoToBltBuffer",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestVideoToBltBufferExtensiveAutoTest
  },
#endif

  0
};

EFI_BB_TEST_PROTOCOL        *gBBTestProtocolInterface;

EFI_STATUS
UnloadEfiGraphicsOutputBBTest (
  IN EFI_HANDLE ImageHandle
  )
/*++

Routine Description:

  The driver's unload function

Arguments:

  ImageHandle - The driver image handle

Returns:

  EFI_SUCCESS - The driver is unloaded successfully.

--*/
{
  return EfiUninstallAndFreeIHVBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


EFI_STATUS
InitializeGraphicsOutputBBTest (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
  )
/*++

Routine Description:

   GraphicsOutput Protocol Test Driver Entry point.

Arguments:

  ImageHandle - The driver image handle
  SystemTable - The system table

Returns:

  EFI_SUCCESS - The driver is loaded successfully.
  
--*/
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);
  SctInitializeDriver (ImageHandle, SystemTable);

  return EfiInitAndInstallIHVBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadEfiGraphicsOutputBBTest,
           &gBBTestProtocolInterface
           );

}
