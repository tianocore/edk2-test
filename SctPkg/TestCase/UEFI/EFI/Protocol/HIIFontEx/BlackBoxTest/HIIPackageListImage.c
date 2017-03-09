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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
  
  (C) Copyright 2017 Hewlett Packard Enterprise Development LP<BR>
  This software contains information confidential and proprietary to
  Hewlett Packard Enterprise. It shall not be reproduced in whole or in part,
  or transferred to other documents, or disclosed to third parties, or used
  for any purpose other than that for which it was obtained without the prior
  written consent of Hewlett Packard Enterprise.
--*/
/*++

Module Name:

    HIIPackageListImage.c
    
Abstract:

    Contain some package list images.

Revision History

--*/

#include "HIIFontExBBTestMain.h" 


UINT8 mPackageList1[] = {                                                                         
  //                                                                                             
  // EFI_HII_PACKAGE_LIST_HEADER.
  // SimpleFont; Font; GUID, Image, DevicePath, KeyboardLayout
  //                                                                                             
  0x89, 0xcd, 0xab, 0x03, 0xf4, 0x03, 0x44, 0x70, 0x81, 0xde, 0x99, 0xb1, 0x81, 0x20, 0xf7, 0x68,    //PackageListGuid
  0xb5, 0x01, 0x00, 0x00,    // PackageListLength 4
  
  //                                                                                             
  // Simple Font Package 1, length = 74. 
  // 
  //
  // EFI_HII_PACKAGE_HEADER
  //
  0x4A, 0x00, 0x00,    // Package Length 3
  EFI_HII_PACKAGE_SIMPLE_FONTS,    //Package Type 1                                                              
  1, 0,    // Num of Narrow Glyph 2 
  1, 0,    // Num of Wide Glyph 2
  0x55, 0x0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,  //EFI_NARROW_GLYPH (UnicodeWeight 2, Attribute 1, GlyphCol1[19])
  0x77, 0x0, 0x2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
  3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 0, 0, 0,  //EFI_WIDE_GLYPH(.UnicodeWeight 2, Attribute 1, GlyphCol1[19], GlyphCol1219], Pad[3]) 
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //
  // Font Package 1, length = 111.   
  //               
  0x6F, 0x00, 0x00,    // Package Length 3
  EFI_HII_PACKAGE_FONTS,    // Package Type 1
  0x5A, 0x00, 0x00, 0x00,    // header size 4 
  0x5A, 0x00, 0x00, 0x00,    // GlyphBlockOffset  4      
  0x08,0x00, 0x13,0x00, 0x00,0x00, 0x00,0x00, 0x08,0x00,    //EFI_HII_GLYPH_INFO (Width, Height, OffsetX, OffsetY, AdvanceX) 10
  0x01,0x00, 0x00, 0x00,    // EFI_HII_FONT_STYLE 4
  0x77,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x52,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x66,  //FontFamily The Null-terminated string with the name of the font family to which the font belongs. 64// BUGBUG
  //
  // Glyph block  1
  //
  // 
  //  EFI_HII_GLYPH_BLOCK
  //
  EFI_HII_GIBT_GLYPH_DEFAULT, // BlockType 1  
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x99, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22,//19, BitMapData
  EFI_HII_GIBT_END, //1
  
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //
  // Guid Package 1. Length = 20.    tested
  //
  0x14, 0x00, 0x00,    // PackageLength 3
  EFI_HII_PACKAGE_TYPE_GUID,   // Package Type  1
  0x5a, 0xc9, 0x87, 0x03, 0x3, 0xd7, 0x46, 0x23, 0xb2, 0xab, 0xd0, 0xc7, 0xdd, 0x90, 0x44, 0xf8, // EFI_GUID 16
      
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Image Package. Length = 16. 
  //
  0x10, 0x00, 0x00, // PackageLength 3
  EFI_HII_PACKAGE_IMAGES,    // Package Type  1
  0x0c, 0x00, 0x00, 0x00,    // image info offset 4. relatice to this header. If this is zero, then there are no palettes in the image package
  0x00, 0x00, 0x00, 0x00,    // palette info offset 4. relatice to this header. If this is zero, then there are no palettes in the image package
  //
  // Image block 1
  //
  EFI_HII_IIBT_DUPLICATE,    // BlockType 1
  0x01, 0x00,    // image id 2  ???
  EFI_HII_IIBT_END,    //1
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // EFI_HII_PACKAGE_DEVICE_PATH length = 8.
  //
//  0x08, 0x00, 0x00,    // PackageLength 3
//  EFI_HII_PACKAGE_DEVICE_PATH,    // Package Type  1
//  0x01, 0x23, 0x45, 0x66, // dummy device path protocol instance address 4 //BUGBUG

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Keyboard layout package. Length 
  0xc0, 0x00, 0x00,    // PackageLength 3
  EFI_HII_PACKAGE_KEYBOARD_LAYOUT,    // Package Type  1
  0x02, 0x00, //2, LayoutCount
  //
  // Layout 1
  //
  0x5d, 0x00, // layout length 2
  0x1f, 0x6a, 0xf5, 0xe0, 0x6b, 0xdf, 0x7e, 0x4a, 0xa3, 0x9a, 0xe7, 0xa5, 0x19, 0x15, 0x45, 0xd6, //16, GUID
  0x37, 0x00, 0x00, 0x00, //layout descriptor string offset 4
  0x02, // Descriptor count 1
  //
  // Descriptor 1, 16 bytes,
  //
  EfiKeyC1, 0x00, 0x00, 0x00, // 4 
  'a', 0x00,
  'A', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER,0x00,
  0x03, 0x00, // affected attributes
  //
  // Descriptor 2,  16 bytes
  //
  EfiKeyC2, 0x00, 0x00, 0x00,
  's', 0x00,
  'S', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER, 0x00,
  0x03, 0x00,
  //
  // EFI_DESCRIPTOR_STRING_BUNDLE
  //
  0x01, 0x00,                 // DescriptionCount 2
  'e', 0x0, 'n', 0x0, '-', 0x0, 'U', 0x0, 'S', 0x0,  // RFC3066 language code 10
  ' ', 0x0,                        // Space 2
  'S', 0x0, 'i', 0x0, 'm', 0x0, 'p', 0x0, 'l', 0x0, 'e', 0x0, '1', 0x0, 'o', 0x0, 'n', 0x0, 'l', 0x0, 'y', 0x0, '\0', 0x0, // DescriptionString  24
  
  //
  // Layout 2
  //  
  0x5d, 0x00, // layout length 2
  0xc9, 0x6a, 0xbe, 0x47, 0xcc, 0x54, 0xf9, 0x46, 0xa2, 0x62, 0xd5, 0x3b, 0x25, 0x6a, 0xc, 0x34, //16, GUID
  0x37, 0x00, 0x00, 0x00, //layout descriptor string offset 4
  0x02,  // Descriptor count 1
  //
  // Descriptor 1, 16 bytes,
  //
  EfiKeyC3, 0x0, 0x0, 0x0,
  'd', 0x00,
  'D', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER, 0x0,
  0x03, 0x00,
  //
  // Descriptor 2,  16 bytes
  //
  EfiKeyC4, 0x0, 0x0, 0x0,
  'e', 0x00,
  'E', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER,  0x0,
  0x03, 0x00,
  //
  // EFI_DESCRIPTOR_STRING_BUNDLE
  //
  0x01, 0x00,                 // DescriptionCount 2
  'e', 0x0, 'n', 0x0, '-', 0x0, 'U', 0x0, 'S', 0x0,  // RFC3066 language code 10
  ' ', 0x0,                        // Space 2
  'S', 0x0, 'i', 0x0, 'm', 0x0, 'p', 0x0, 'l', 0x0, 'e', 0x0, '2', 0x0, 'o', 0x0, 'n', 0x0, 'l', 0x0, 'y', 0x0, '\0', 0x0, // DescriptionString  24
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // End of package list, length = 4,
  //
  0x4, 0x00, 0x00,
  EFI_HII_PACKAGE_END                                                                                    
};

UINT8 mPackageListTestFont[] = {                                                                         
  //                                                                                             
  // EFI_HII_PACKAGE_LIST_HEADER. Length 20
  // SimpleFont; 
  //                                                                                             
  0xe7, 0xb5, 0xdb, 0x11, 0xfa, 0x5c, 0x47, 0x12, 0xa0, 0x6f, 0xc7, 0xa1, 0x10, 0x72, 0xc5, 0x6,   //PackageListGuid
  0x65, 0x0A, 0x00, 0x00,    // PackageListLength 4
  
  //                                                                                             
  // Simple Font Package , length = 30 
  // 
  //
  // EFI_HII_PACKAGE_HEADER
  //
  0x1E, 0x00, 0x00,    // Package Length 3
  EFI_HII_PACKAGE_SIMPLE_FONTS,    //Package Type 1                                                              
  1, 0,    // Num of Narrow Glyph 1  Length 2
  0, 0,    // Num of Wide Glyph 1 Length 2 

  0x54, 0x00,0x00, 0x00,0x00,0x00,0x10,0x30,0x30,0x30,0xFC,0x30,0x30,0x30,0x30,0x30,0x36,0x1C,0x00,0x00,0x00,0x00,  // Narrow Font Glyph Length 22
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //
  // Font Package 1, length = 2611.   
  //               
  0x33, 0x0A, 0x00,    // Package Length 3
  EFI_HII_PACKAGE_FONTS,    // Package Type 1
  0x5A, 0x00, 0x00, 0x00,    // header size 4 
  0x5A, 0x00, 0x00, 0x00,    // GlyphBlockOffset  4      
  0x08,0x00, 0x13,0x00, 0x00,0x00, 0x00,0x00, 0x08,0x00,    //EFI_HII_GLYPH_INFO (Width, Height, OffsetX, OffsetY, AdvanceX) 10
  0x01,0x00, 0x00, 0x00,    // EFI_HII_FONT_STYLE 4
  0x74,0x00, 0x65,0x00, 0x73,0x00, 0x74,0x00, 
  0x66,0x00, 0x6F,0x00, 0x6E,0x00, 0x74,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x52,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x66,  //FontFamily The Null-terminated string with the name of the font family to which the font belongs. 64// BUGBUG
  //
  // Glyph block  1
  //
  // 
  //  EFI_HII_GLYPH_BLOCK
  // Containing All ASCII visible letters
  // 
   EMPTY_TEST_GLYPH,              // 0x01
   EMPTY_TEST_GLYPH,              // 0x02
   EMPTY_TEST_GLYPH,              // 0x03
   EMPTY_TEST_GLYPH,              // 0x04
   EMPTY_TEST_GLYPH,              // 0x05
   EMPTY_TEST_GLYPH,              // 0x06
   EMPTY_TEST_GLYPH,              // 0x07
   EMPTY_TEST_GLYPH,              // 0x08
   EMPTY_TEST_GLYPH,              // 0x09
   EMPTY_TEST_GLYPH,              // 0x0A
   EMPTY_TEST_GLYPH,              // 0x0B
   EMPTY_TEST_GLYPH,              // 0x0C
   EMPTY_TEST_GLYPH,              // 0x0D
   EMPTY_TEST_GLYPH,              // 0x0E
   EMPTY_TEST_GLYPH,              // 0x0F
   EMPTY_TEST_GLYPH,              // 0x10
   EMPTY_TEST_GLYPH,              // 0x11
   EMPTY_TEST_GLYPH,              // 0x12
   EMPTY_TEST_GLYPH,              // 0x13
   EMPTY_TEST_GLYPH,              // 0x14
   EMPTY_TEST_GLYPH,              // 0x15
   EMPTY_TEST_GLYPH,              // 0x16
   EMPTY_TEST_GLYPH,              // 0x17
   EMPTY_TEST_GLYPH,              // 0x18
   EMPTY_TEST_GLYPH,              // 0x19
   EMPTY_TEST_GLYPH,              // 0x1A
   EMPTY_TEST_GLYPH,              // 0x1B
   EMPTY_TEST_GLYPH,              // 0x1C
   EMPTY_TEST_GLYPH,              // 0x1D
   EMPTY_TEST_GLYPH,              // 0x1E
   EMPTY_TEST_GLYPH,              // 0x1F
   FONT_TEST_GLYPH (0x20),        // 0x20   space
   FONT_TEST_GLYPH (0x21),        // 0x21   ! 
   FONT_TEST_GLYPH (0x22),        // 0x22   " 
   FONT_TEST_GLYPH (0x23),        // 0x23   # 
   FONT_TEST_GLYPH (0x24),        // 0x24   $ 
   FONT_TEST_GLYPH (0x25),        // 0x25   % 
   FONT_TEST_GLYPH (0x26),        // 0x26   & 
   FONT_TEST_GLYPH (0x27),        // 0x27    
   FONT_TEST_GLYPH (0x28),        // 0x28   ( 
   FONT_TEST_GLYPH (0x29),        // 0x29   ) 
   FONT_TEST_GLYPH (0x2A),        // 0x2A   * 
   FONT_TEST_GLYPH (0x2B),        // 0x2B   + 
   FONT_TEST_GLYPH (0x2C),        // 0x2C   , 
   FONT_TEST_GLYPH (0x2D),        // 0x2D  - 
   FONT_TEST_GLYPH (0x2E),        // 0x2E.  
   FONT_TEST_GLYPH (0x2F),        // 0x2F   / 
   FONT_TEST_GLYPH (0x30),        // 0x30   0 
   FONT_TEST_GLYPH (0x31),        // 0x31   1 
   FONT_TEST_GLYPH (0x32),        // 0x32   2 
   FONT_TEST_GLYPH (0x33),        // 0x33   3 
   FONT_TEST_GLYPH (0x34),        // 0x34   4 
   FONT_TEST_GLYPH (0x35),        // 0x35   5 
   FONT_TEST_GLYPH (0x36),        // 0x36   6 
   FONT_TEST_GLYPH (0x37),        // 0x37   7 
   FONT_TEST_GLYPH (0x38),        // 0x38   8 
   FONT_TEST_GLYPH (0x39),        // 0x39   9 
   FONT_TEST_GLYPH (0x3A),        // 0x3A   : 
   FONT_TEST_GLYPH (0x3B),        // 0x3B   ; 
   FONT_TEST_GLYPH (0x3C),        // 0x3C   < 
   FONT_TEST_GLYPH (0x3D),        // 0x3D  = 
   FONT_TEST_GLYPH (0x3E),        // 0x3E   >
   FONT_TEST_GLYPH (0x3F),        // 0x3F   ?
   FONT_TEST_GLYPH (0x40),        // 0x40   @
   FONT_TEST_GLYPH (0x41),        // 0x41   A
   FONT_TEST_GLYPH (0x42),        // 0x42   B
   FONT_TEST_GLYPH (0x43),        // 0x43   C
   FONT_TEST_GLYPH (0x44),        // 0x44   D
   FONT_TEST_GLYPH (0x45),        // 0x45   E
   FONT_TEST_GLYPH (0x46),        // 0x46   F
   FONT_TEST_GLYPH (0x47),        // 0x47   G
   FONT_TEST_GLYPH (0x48),        // 0x48   H
   FONT_TEST_GLYPH (0x49),        // 0x49   I
   FONT_TEST_GLYPH (0x4A),        // 0x4A   J
   FONT_TEST_GLYPH (0x4B),        // 0x4B   K
   FONT_TEST_GLYPH (0x4C),        // 0x4C   L
   FONT_TEST_GLYPH (0x4D),        // 0x4D  M
   FONT_TEST_GLYPH (0x4E),        // 0x4E   N
   FONT_TEST_GLYPH (0x4F),        // 0x4F   O
   FONT_TEST_GLYPH (0x50),        // 0x50   P
   FONT_TEST_GLYPH (0x51),        // 0x51   Q
   FONT_TEST_GLYPH (0x52),        // 0x52   R
   FONT_TEST_GLYPH (0x53),        // 0x53   S
   FONT_TEST_GLYPH (0x54),        // 0x54   T
   FONT_TEST_GLYPH (0x55),        // 0x55   U
   FONT_TEST_GLYPH (0x56),        // 0x56   V
   FONT_TEST_GLYPH (0x57),        // 0x57   W
   FONT_TEST_GLYPH (0x58),        // 0x58   X
   FONT_TEST_GLYPH (0x59),        // 0x59   Y
   FONT_TEST_GLYPH (0x5A),        // 0x5A   Z
   FONT_TEST_GLYPH (0x5B),        // 0x5B   [
   FONT_TEST_GLYPH (0x5C),        // 0x5C   '\'
   FONT_TEST_GLYPH (0x5D),        // 0x5D  [
   FONT_TEST_GLYPH (0x5E),        // 0x5E   ^
   FONT_TEST_GLYPH (0x5F),        // 0x5F   _
   FONT_TEST_GLYPH (0x60),        // 0x60   `
   FONT_TEST_GLYPH (0x61),        // 0x61   a
   FONT_TEST_GLYPH (0x62),        // 0x62   b
   FONT_TEST_GLYPH (0x63),        // 0x63   c
   FONT_TEST_GLYPH (0x64),        // 0x64   d
   FONT_TEST_GLYPH (0x65),        // 0x65   e
   FONT_TEST_GLYPH (0x66),        // 0x66   f
   FONT_TEST_GLYPH (0x67),        // 0x67   g
   FONT_TEST_GLYPH (0x68),        // 0x68   h
   FONT_TEST_GLYPH (0x69),        // 0x69   i
   FONT_TEST_GLYPH (0x6A),        // 0x6A   j
   FONT_TEST_GLYPH (0x6B),        // 0x6B   k
   FONT_TEST_GLYPH (0x6C),        // 0x6C   l
   FONT_TEST_GLYPH (0x6D),        // 0x6D  m
   FONT_TEST_GLYPH (0x6E),        // 0x6E   n
   FONT_TEST_GLYPH (0x6F),        // 0x6F   o
   FONT_TEST_GLYPH (0x70),        // 0x70   p
   FONT_TEST_GLYPH (0x71),        // 0x71   q
   FONT_TEST_GLYPH (0x72),        // 0x72   r
   FONT_TEST_GLYPH (0x73),        // 0x73   s
   FONT_TEST_GLYPH (0x74),        // 0x74   t
   FONT_TEST_GLYPH (0x75),        // 0x75   u
   FONT_TEST_GLYPH (0x76),        // 0x76   v
   FONT_TEST_GLYPH (0x77),        // 0x77   w
   FONT_TEST_GLYPH (0x78),        // 0x78   x
   FONT_TEST_GLYPH (0x79),        // 0x79   y
   FONT_TEST_GLYPH (0x7A),        // 0x7A   z
   FONT_TEST_GLYPH (0x7B),        // 0x7B   {
   FONT_TEST_GLYPH (0x7C),        // 0x7C   |
   FONT_TEST_GLYPH (0x7D),        // 0x7D  }
   FONT_TEST_GLYPH (0x7E),        // 0x7E   ~
  
 EFI_HII_GIBT_END, //1
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // End of package list, length = 4,
    //
    0x4, 0x00, 0x00,
    EFI_HII_PACKAGE_END                                                                                    
};  
