/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  GraphicsOutputBBTest.h

Abstract:
  
  BB test header file of Graphics Output Protocol
  
References:

  UEFI 2.0 Specification
  Graphics Output Protocol Test Design Specification
  UEFI/Tiano DXE Test Case Writer's Guide

--*/
#ifndef __GRAPHICS_OUTPUT_BBTEST_H__
#define __GRAPHICS_OUTPUT_BBTEST_H__

#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/GraphicsOutput.h>

#define EFI_GRAPHICS_OUTPUT_BB_TEST_REVISION  0x00010000

#define STEP_WIDTH                            50
#define STEP_WIDTH_BUFFER                     100
//
// These defines are for stress test
//
#define DEMO_SOURCE_POSITION_ENUM       3
#define DEMO_DESTINATION_POSITION_ENUM  3
#define DEMO_DELTA_ENUM                 4
#define DEMO_WIDTH_HEIGHT_ENUM          2
//
//  EFI Graphics Output Black-Box Function Test Category GUID
//
#define EFI_GRAPHICS_OUTPUT_BB_TEST_CATEGORY_GUID \
  { \
    0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a } \
  }

//
//  EFI Graphics Output Black-Box Function Test Assertions
//
#define EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERYMODE_BB_TEST_FUNCTION_ASSERTION_GUID \
  { \
    0xd1824539, 0x92cd, 0x434c, {0x81, 0x65, 0x87, 0x2c, 0xc2, 0x1a, 0x5f, 0x9e } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_SETMODE_BB_TEST_FUNCTION_ASSERTION_GUID \
  { \
    0xb3a4939b, 0xd00a, 0x4da7, {0xaf, 0x6d, 0xf3, 0xee, 0xcb, 0xf9, 0x99, 0x0c } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOFILL_BB_TEST_FUNCTION_ASSERTION_GUID_001 \
  { \
    0x95a44702, 0xcea0, 0x480f, {0x9f, 0x84, 0xe2, 0x4c, 0x17, 0xbf, 0x47, 0x79 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOFILL_BB_TEST_FUNCTION_ASSERTION_GUID_002 \
  { \
    0x699c30b0, 0xab3f, 0x45d9, {0xbd, 0x69, 0x6b, 0x93, 0x96, 0xb7, 0x7e, 0x66 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_BB_TEST_FUNCTION_ASSERTION_GUID_001 \
  { \
    0xc34c3fa4, 0xa61e, 0x4598, {0x9f, 0x80, 0x2d, 0xee, 0x8e, 0x2c, 0x9b, 0x57 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_BB_TEST_FUNCTION_ASSERTION_GUID_002 \
  { \
    0x33a341ea, 0xc6a2, 0x4037, {0x8a, 0x2d, 0x19, 0xea, 0x1f, 0xe2, 0xf2, 0xa6 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_BB_TEST_FUNCTION_ASSERTION_GUID_003 \
  { \
    0x13f113dc, 0xafd0, 0x4658, {0xb7, 0xfb, 0x83, 0xd5, 0xae, 0x6f, 0x10, 0x58 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_BB_TEST_FUNCTION_ASSERTION_GUID_004 \
  { \
    0x5ca291cc, 0x84a0, 0x489d, {0x9b, 0x2a, 0x0f, 0x2f, 0xcc, 0xc6, 0x0b, 0x29 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOTOVIDEO_BB_TEST_FUNCTION_ASSERTION_GUID_001 \
  { \
    0x6c2632c0, 0xe3de, 0x4afc, {0xb3, 0xa1, 0xbe, 0x50, 0x75, 0xab, 0x2d, 0x7a } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOTOVIDEO_BB_TEST_FUNCTION_ASSERTION_GUID_002 \
  { \
    0x07d1d0c1, 0x3884, 0x4310, {0x97, 0xbc, 0x16, 0xd6, 0xaa, 0x1a, 0x21, 0x80 } \
  }

//
//  EFI Graphics Output Black-Box Conformance Test Assertions
//
#define EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_001 \
  { \
    0x82dfd41e, 0x49db, 0x4c86, {0x99, 0xbb, 0xc5, 0x74, 0x33, 0x4b, 0xa0, 0xc3 } \
  }

extern EFI_GUID gGraphicsOutputQueryModeConformanceTestAssertionGuid001;

#define EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_002 \
  { \
    0x8ebcd9ab, 0x69a9, 0x48a2, {0x9b, 0xbc, 0x8c, 0x47, 0x9e, 0x68, 0x91, 0x56 } \
  }

extern EFI_GUID gGraphicsOutputQueryModeConformanceTestAssertionGuid002;

#define EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_003 \
  { \
    0x394e306b, 0x652a, 0x403a, {0xbd, 0x15, 0xdb, 0x9b, 0x46, 0xc3, 0x44, 0x3b } \
  }

extern EFI_GUID gGraphicsOutputQueryModeConformanceTestAssertionGuid003;

#define EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_004 \
  { \
    0xe7782dc5, 0x2b78, 0x460f, {0xb1, 0x02, 0x88, 0xd5, 0x12, 0x06, 0x45, 0x1f } \
  }

extern EFI_GUID gGraphicsOutputQueryModeConformanceTestAssertionGuid004;

#define EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_005 \
  { \
    0x486360f1, 0x6b8e, 0x48b5, {0x8b, 0xa8, 0xae, 0x40, 0xeb, 0x3b, 0x07, 0xa2 } \
  }

extern EFI_GUID gGraphicsOutputQueryModeConformanceTestAssertionGuid005;

#define EFI_TEST_GRAPHICSOUTPUT_QUERYMODE_CONFORMANCETEST_ASSERTION_GUID_006 \
  { \
    0xdc19ab69, 0x764e, 0x429b, {0xa5, 0x3f, 0xb8, 0x1e, 0xd6, 0x3c, 0xd6, 0xc0 } \
  }

extern EFI_GUID gGraphicsOutputQueryModeConformanceTestAssertionGuid006;

#define EFI_TEST_GRAPHICSOUTPUT_SETMODE_CONFORMANCETEST_ASSERTION_GUID_001 \
  { \
    0x128e953b, 0xe6ec, 0x4f93, {0xa8, 0xec, 0x72, 0xc5, 0x9b, 0x8a, 0x40, 0x43 } \
  }

extern EFI_GUID gGraphicsOutputSetModeConformanceTestAssertionGuid001;

#define EFI_TEST_GRAPHICSOUTPUT_SETMODE_CONFORMANCETEST_ASSERTION_GUID_002 \
  { \
    0x4f13e7ba, 0xb35a, 0x4bf7, {0xb1, 0xc0, 0xfe, 0x39, 0x9c, 0x49, 0x97, 0xfe } \
  }

extern EFI_GUID gGraphicsOutputSetModeConformanceTestAssertionGuid002;

#define EFI_TEST_GRAPHICSOUTPUT_SETMODE_CONFORMANCETEST_ASSERTION_GUID_003 \
  { \
    0x8776b9dc, 0x711e, 0x4e36, {0x99, 0x21, 0x7e, 0xa7, 0xc4, 0xc7, 0xee, 0x6d } \
  }

extern EFI_GUID gGraphicsOutputSetModeConformanceTestAssertionGuid003;

#define EFI_TEST_GRAPHICSOUTPUT_BLT_CONFORMANCETEST_ASSERTION_GUID_001 \
  { \
    0x11af616a, 0xbef5, 0x4590, {0xbe, 0x85, 0x19, 0x52, 0xa0, 0x0d, 0xe1, 0xaf } \
  }

extern EFI_GUID gGraphicsOutputBltConformanceTestAssertionGuid001;

//
//  EFI Graphics Output Black-Box Stress Test Assertions
//
#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILL_STRESS_AUTO_TEST_ASSERTION_GUID_001 \
  { \
    0xe967bdc7, 0xa0ea, 0x4fd7, {0xab, 0xba, 0x52, 0xf3, 0xef, 0x53, 0x22, 0x3e } \
  }

extern EFI_GUID gGraphicsOutputBltVideoFillStressAutoTestAssertionGuid001;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILL_STRESS_AUTO_TEST_ASSERTION_GUID_002 \
  { \
    0x1fc521b0, 0x63c1, 0x4f42, {0xb8, 0x14, 0x06, 0x8a, 0x6c, 0x9c, 0x3e, 0x29 } \
  }

extern EFI_GUID gGraphicsOutputBltVideoFillStressAutoTestAssertionGuid002;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILL_STRESS_AUTO_TEST_ASSERTION_GUID_003 \
  { \
    0x04fd0571, 0xf3eb, 0x4d69, {0xb2, 0xd2, 0x5c, 0x4f, 0xfb, 0x10, 0x5a, 0xc3 } \
  }

extern EFI_GUID gGraphicsOutputBltVideoFillStressAutoTestAssertionGuid003;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_001 \
  { \
    0x5bee154c, 0xe519, 0x4be4, {0xaf, 0x8c, 0xb4, 0x18, 0x8e, 0x79, 0xb4, 0xbf } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid001;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_002 \
  { \
    0xf9e726c1, 0x1346, 0x419e, {0x90, 0x8a, 0x66, 0xc4, 0x49, 0x8c, 0xfd, 0x71 } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid002;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_003 \
  { \
    0x00f74a1b, 0x4599, 0x45b7, {0xb6, 0xf7, 0x13, 0xf2, 0xcb, 0xd8, 0x6c, 0xe6 } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid003;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_004 \
  { \
    0x26da6582, 0x8b82, 0x4bd2, {0xac, 0x3a, 0x6e, 0x37, 0x85, 0x4f, 0xd8, 0x21 } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid004;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOBLTBUFFER_STRESS_AUTO_TEST_ASSERTION_GUID_005 \
  { \
    0x0aaf7f4e, 0x1794, 0x403c, {0xb3, 0xb0, 0x18, 0xf5, 0xe4, 0xd3, 0xc4, 0xea } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid005;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_001 \
  { \
    0x2a79335b, 0xafc3, 0x4ccf, {0x9b, 0xa4, 0x91, 0x9b, 0xe4, 0xb8, 0xbe, 0xfc } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid001;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_002 \
  { \
    0x3f4c2c88, 0xa1f8, 0x46f5, {0x9e, 0x5e, 0x67, 0x50, 0xb4, 0xae, 0x2b, 0x6f } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid002;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_003 \
  { \
    0xa11dd47e, 0xf144, 0x460c, {0x9e, 0x18, 0x7e, 0xb7, 0xed, 0xda, 0xc0, 0x18 } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid003;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_004 \
  { \
    0xbe3e3046, 0x5aea, 0x48d0, {0x91, 0xc4, 0x62, 0xce, 0xff, 0x61, 0x3c, 0xec } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid004;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOVIDEO_STRESS_AUTO_TEST_ASSERTION_GUID_005 \
  { \
    0xed4e402a, 0x403c, 0x4071, {0x86, 0x93, 0x9d, 0x8d, 0x28, 0xf7, 0x83, 0xd9 } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid005;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_001 \
  { \
    0x3b54894e, 0x6383, 0x4dd5, {0x9e, 0x53, 0xbe, 0x6b, 0xc1, 0x1b, 0xd8, 0x94 } \
  }

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid001;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_002 \
  { \
    0xd0869ac8, 0x1d16, 0x4657, {0xae, 0xf2, 0x6, 0xc3, 0x49, 0x82, 0x1d, 0x55 } \
  };

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid002;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_003 \
  { \
    0x1f026b26, 0x36fd, 0x4f1c, {0x95, 0x4c, 0x16, 0xf, 0x9f, 0x98, 0x49, 0xd1 } \
  };

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid003;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_004 \
  { \
    0xd0bfb3c3, 0x54df, 0x4c07, {0x8e, 0x5c, 0x7a, 0x19, 0xa3, 0x5b, 0x5c, 0xc } \
  };

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid004;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_005 \
  { \
    0xfde7edd9, 0x1486, 0x45e9, {0xae, 0x06, 0x31, 0xe8, 0xcb, 0x3f, 0xf3, 0x46 } \
  };

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid005;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_006 \
  { \
    0x538471f3, 0x8828, 0x4d1b, {0x8c, 0x2b, 0x1, 0x37, 0xe9, 0x4f, 0xae, 0xc9 } \
  };

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid006;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_007 \
  { \
    0x30ef55c6, 0x62a2, 0x4f90, {0xb3, 0xf8, 0xf4, 0xf9, 0x1b, 0x94, 0xbf, 0x91 } \
  };

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid007;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_008 \
  { \
    0x2bb7feeb, 0x9b15, 0x4b27, {0x92, 0x61, 0xff, 0xa6, 0x9e, 0xcf, 0xa, 0x0 } \
  };

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid008;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLBUFFERTOVIDEO_MANUAL_ASSERTION_GUID_009 \
  { \
    0x3bb9ebcc, 0x370a, 0x4c02, {0xb2, 0xd, 0x1f, 0x86, 0x5a, 0x98, 0xaa, 0x15 } \
  };

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid009;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_001 \
  { \
    0xb904f2be, 0x720e, 0x4d9b, {0x86, 0x72, 0xd7, 0x84, 0x6b, 0xbc, 0x53, 0xea } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid001;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_002 \
  { \
    0x53748ffc, 0xaff8, 0x4cc9, {0x83, 0xab, 0xc7, 0x09, 0xe1, 0x59, 0x1c, 0xed } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid002;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_003 \
  { \
    0x4acd2d08, 0x01dd, 0x411f, {0xa6, 0xe2, 0xf3, 0x6f, 0x9f, 0x4b, 0x03, 0xb0 } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid003;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_004 \
  { \
    0xb11e8ade, 0x0c54, 0x4963, {0x89, 0x66, 0xa0, 0x4a, 0x50, 0x40, 0x1c, 0x7b } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid004;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_005 \
  { \
    0xfa43d810, 0x7501, 0x481f, {0xbd, 0xcd, 0xc1, 0x06, 0x57, 0x94, 0x84, 0x9a } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid005;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_006 \
  { \
    0x94989a37, 0x3941, 0x4cd8, {0x97, 0x0b, 0x14, 0xfa, 0x46, 0xb6, 0x07, 0x16 } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid006;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_007 \
  { \
    0x4dde309d, 0xaf32, 0x4a35, {0x91, 0x5a, 0x41, 0xcb, 0xb0, 0x18, 0x7c, 0x29 } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid007;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_008 \
  { \
    0xaa6b7386, 0x0537, 0x4762, {0xa1, 0x43, 0xca, 0xde, 0xb7, 0x55, 0x15, 0xc7 } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid008;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_009 \
  { \
    0xb751208f, 0x10eb, 0x47eb, {0x9c, 0x73, 0x15, 0x08, 0xb8, 0xc9, 0xcd, 0xbe } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid009;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOFILLVIDEOTOVIDEO_MANUAL_ASSERTION_GUID_010 \
  { \
    0x57b7debf, 0xb831, 0x40d1, {0x8b, 0xa0, 0xa6, 0x57, 0x7b, 0x92, 0xe2, 0x53 } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid010;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOBUFFER_EXTENSIVE_ASSERTION_GUID_001 \
  { \
    0x8971c5fe, 0x02c6, 0x4ada, {0xab, 0x30, 0x36, 0xc5, 0xa7, 0xd9, 0xdc, 0x01 } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoToBufferBBTestExtensiveAssertionGuid001;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOBUFFER_EXTENSIVE_ASSERTION_GUID_002 \
  { \
    0x03093b96, 0x2b15, 0x4008, {0xb7, 0xbf, 0x9f, 0x8c, 0x17, 0x41, 0x2d, 0xb3 } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoToBufferBBTestExtensiveAssertionGuid002;

#define EFI_TEST_GRAPHICSOUTPUT_BLTVIDEOTOBUFFER_EXTENSIVE_ASSERTION_GUID_003 \
  { \
    0x1ef36d93, 0x8591, 0x4172, {0x94, 0xfd, 0x93, 0x08, 0x54, 0x6e, 0x73, 0x11 } \
  };
extern EFI_GUID gEfiGraphicsOutputBltVideoToBufferBBTestExtensiveAssertionGuid003;

//
//  EFI Graphics Output Black-Box Functions Test Entries GUIDs define
//
#define EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERYMODE_FUNCTION_AUTO_GUID \
  { \
    0x97a6f, 0xf44a, 0x45e0, {0xa2, 0x50, 0xce, 0x43, 0x80, 0x5c, 0x8c, 0x6e } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_SETMODE_FUNCTION_AUTO_GUID \
  { \
    0x431549c4, 0xec39, 0x4995, {0xbf, 0xb7, 0x6c, 0xcb, 0x7, 0x5b, 0xf1, 0xbe } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOFILL_FUNCTION_AUTO_GUID \
  { \
    0x442b902b, 0x44a8, 0x4c1e, {0xbf, 0x2c, 0x50, 0xec, 0x4f, 0xa4, 0x36, 0x7b } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOBLTBUFFER_FUNCTION_AUTO_GUID \
  { \
    0xb504931b, 0xbc55, 0x4e84, {0x82, 0x29, 0xf8, 0x31, 0x62, 0x37, 0x85, 0xfb } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLTVIDEOTOVIDEO_FUNCTION_AUTO_GUID \
  { \
    0x734f7f92, 0xaa5e, 0x407b, {0xab, 0xb5, 0x8, 0xf7, 0x3a, 0xab, 0xdd, 0xdd } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERYMODE_CONFORMANCE_AUTO_GUID \
  { \
    0x9fcaaf30, 0xba66, 0x44bd, {0xbc, 0x4f, 0x56, 0x5b, 0x8e, 0x2, 0xe8, 0x98 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_SETMODE_CONFORMANCE_AUTO_GUID \
  { \
    0x8b191407, 0x7aec, 0x4826, {0xa6, 0xa8, 0x27, 0xfd, 0xdb, 0x67, 0xf1, 0x35 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT_CONFORMANCE_AUTO_GUID \
  { \
    0x2ce3ab58, 0xa0ea, 0x427c, {0x9e, 0xe6, 0xa, 0x5f, 0x52, 0x55, 0x7e, 0x5d } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_VIDEOFILL_BUFFERTOVIDEO_EXTENSIVE_MANUAL_GUID \
  { \
    0xed4e402a, 0x403c, 0x4071, {0x86, 0x93, 0x9d, 0x8d, 0x28, 0xf7, 0x83, 0xd9 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_VIDEOFILL_VIDEOTOVIDEO_EXTENSIVE_MANUAL_GUID \
  { \
    0xfb8bc698, 0x14e2, 0x4784, {0xb6, 0xd4, 0x7b, 0xe3, 0xe3, 0x4, 0x72, 0xbe } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_VIDEOTOBLTBUFFER_EXTENSIVE_AUTO_GUID \
  { \
    0xc4106369, 0x811b, 0x4375, {0x91, 0x6, 0xf1, 0xb6, 0x3d, 0xdc, 0x2c, 0x4b } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_EFIBLTVIDEOFILL_STRESS_AUTO_GUID \
  { \
    0x874f145c, 0xbb6a, 0x4add, {0x88, 0xaa, 0xaa, 0x9e, 0x3c, 0xc1, 0x89, 0x3d } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_EFIBLTVIDEOBLTBUFFER_STRESS_AUTO_GUID \
  { \
    0xd8a84ba8, 0x32fe, 0x4268, {0x8a, 0xd5, 0xaf, 0xe7, 0x26, 0x1b, 0x9, 0x93 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_EFIBLTVIDEOTOVIDEO_STRESS_AUTO_GUID \
  { \
    0x33e45463, 0xa730, 0x4573, {0xb1, 0xcd, 0x8f, 0xf0, 0x95, 0xd0, 0xba, 0xb4 } \
  }

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_SPECIAL_TEST_GUID \
  { \
    0x1a666d10, 0x4f18, 0x42c3, {0x96, 0xf4, 0x51, 0xeb, 0x7d, 0xa7, 0x3a, 0x38 } \
  }

extern EFI_GUID gEfiGraphicsOutputQueryModeBBTestFunctionAssertionGuid;

extern EFI_GUID gEfiGraphicsOutputSetModeBBTestFunctionAssertionGuid;

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBBTestFunctionAssertionGuid001;

extern EFI_GUID gEfiGraphicsOutputBltVideoFillBBTestFunctionAssertionGuid002;

extern EFI_GUID gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid001;

extern EFI_GUID gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid002;

extern EFI_GUID gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid003;

extern EFI_GUID gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid004;

extern EFI_GUID gEfiGraphicsOutputBltVideoVideoBBTestFunctionAssertionGuid001;

extern EFI_GUID gEfiGraphicsOutputBltVideoVideoBBTestFunctionAssertionGuid002;

//
//  Function GUIDs referenced in Functions
//
extern EFI_GUID gBlackBoxEfiGraphicsOutputQueryModeBBTestFunctionAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputSetModeFunctionAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputBltVideoFillFunctionAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputBltVideoBltBufferFunctionAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputBltVideoToVideoFunctionAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputQueryModeConformanceAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputSetModeConformanceAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputBltConformanceAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputBltVideoFillStressAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputBltVideoBltBufferStressAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputBltVideoToVideoStressAutoGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputVideoFillBufferToVideoExtensiveManualGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputVideoFillVideoToVideoExtensiveManualGuid;

extern EFI_GUID gBlackBoxEfiGraphicsOutputVideoToBufferExtensiveGuid;

//
// Test Case Define
//   An individual test composed of 1 to more test cases,
//   which in turn may contain sereral test assertions.
//   Individual test cases are specified by the Test Entry Field.
//
EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputSpecialFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()- BltVideoFill operation special function Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputQueryModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode() function Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputSetModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode() function Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputBltVideoFillFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()- BltVideoFill operation function Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputBltVideoBltBufferFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt() - BltVideoToBltBuffer & BltBufferToVideo function Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputBltVideoToVideoFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt() - BltVideoToVideo function Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

//
// confomance functions
//
EFI_STATUS
EFIAPI
BBTestQueryModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode() Conformance Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestBltConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt() Conformance Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestSetModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode() Conformance Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

//
// stress test
//
EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputBltVideoFillStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoFill/VideoToBuffer Extensive Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputBltVideoBltBufferStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoToBuffer/BltBufferToVideo Extensive Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

 --*/
;

EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputBltVideoToVideoStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoToVideo Extensive Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestVideoFillBufferToVideoManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoFill& BltBufferToVideo Manual Stress Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestVideoFillVideoToVideoManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoToVideo Manual Stress Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;

EFI_STATUS
EFIAPI
BBTestVideoToBltBufferExtensiveAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoToBltBuffer Extensive Auto Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
;
//
// EFI GraphicsOutput Protocol Test Entry Points
//
EFI_STATUS
EFIAPI
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
;

//
// EFI GraphicsOutput Protocol Test Exit Points
//
EFI_STATUS
EFIAPI
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
;

//
//  Test Support funcitons define
//

EFI_STATUS
InitTestEnv (
  IN EFI_HANDLE                         SupportHandle,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL **StandardLib,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL       *GraphicsOutput

  )
/*++

Routine Description:

  find the Standard Test Libray Interface from SupportHandle,
  locate the DevicePath Protocol bound to GraphicsOutput Protocol,
  output the device path string


Arguments:

  SupportHandle     - The handle to find the S.T.L. Interface
  GraphicsOutput    - The protocol to find its corresponse device path
  StandardLib       - The S.T.L. interface instance found with S.T.L. GUID

Returns:

  EFI_SUCCESS      - No error occurs
  EFI_DEVICE_ERROR - Something wrong.

--*/
;


EFI_STATUS
GraphicsOutputClearScreen (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL      *GraphicsOutput,
  IN  UINTN                             HorizontalResolution,
  IN  UINTN                             VerticalResolution
  )
/*++

Routine Description:

  Clear the whole screen

Arguments:

  GraphicsOutput        - GraphicsOutPut protocol interface
  HorizontalResolution  - Horizontal resolution of the screen
  VerticalResolution    - Vertical resolution of the screen

Returns:

  EFI_SUCCESS - No error occurs
  
--*/
;


//
// Prepare more test data.
//
VOID
GetTestData (
  IN  UINTN        Index,
  IN  UINTN        *Width,
  IN  UINTN        *Height,
  IN  UINTN        *SourceX,
  IN  UINTN        *SourceY,
  IN  UINTN        *DestinationX,
  IN  UINTN        *DestinationY,
  IN  UINTN        *Delta,
  IN  UINTN        HorizontalResolution,
  IN  UINTN        VerticalResolution
  )
/*++

Routine Description:

  Assistant function for preparing test data

Arguments:

  Index                 - Index of the current test count
  Width                 - Test data for Width to be returned
  Height                - Test data for Height to be returned
  SourceX               - Test data for SourceX to be returned
  SourceY               - Test data for SourceY to be returned
  DestinationX          - Test data for DestinationX to be returned
  DestinationY          - Test data for DestinationY to be returned
  Delta                 - Test data for Delta to be returned
  HorizontalResolution  - Test data for HorizontalResolution to be returned
  VerticalResolution    - Test data for VerticalResolution to be returned

Returns:

  No return status.

--*/
;
//
// Set a bitmap in the BltBuffer
//
EFI_STATUS
LoadBmp (
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL  **BltBuffer,
  IN UINTN                          *Width,
  IN UINTN                          *Height
  )
/*++

Routine Description:

  Assistant function for loading a bmp file

Arguments:

  BltBuffer - Buffer for loading a bmp file
  Width     - Width of the bmp file
  Height    - Height of the bmp file

Returns:

  EFI_SUCCESS - No error returns

--*/
;
BOOLEAN
AutoJudgeGop (
  IN  UINTN         X,
  IN  UINTN         Y,
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  )
/*++

Routine Description:

  Assistant function to auto judge the user's choice, correct or uncorrect?

Arguments:

  X       - The coordination of X
  Y       - The coordination of Y
  Seconds - The time to wait the user for judging
  Default - Default value(True/False) for auto judge(Yes/No) 
  Message - The message printed on the screen to remind the user

Returns:

  TRUE/FALSE standing for correct/uncorrect choice respectively

--*/
;
#endif
