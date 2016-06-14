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

    HIIPackageListImage.c
    
Abstract:

    Contain some package list images.

Revision History

--*/

#include "HIIDatabaseBBTestMain.h"

UINT8 mPackageList1[] = {                                                                         
  //                                                                                             
  // EFI_HII_PACKAGE_LIST_HEADER, total length = 452-110 =342.
  // SimpleFont; Font; GUID, Form, String, Image, DevicePath, KeyboardLayout
  //                                                                                             
  0x89, 0xcd, 0xab, 0x03, 0xf4, 0x03, 0x44, 0x70, 0x81, 0xde, 0x99, 0xb1, 0x81, 0x20, 0xf7, 0x68,    //16
  0xcf, 0x01, 0x00, 0x00,     // 4    
  //                                                                                             
  // Simple Font Package 1, length = 74.            tested                                                         
  //                                                                                             
  0x4A, 0x00, 0x00,                
  EFI_HII_PACKAGE_SIMPLE_FONTS,                                                                  
  1, 0,                                                                                             
  1, 0,
  0x55, 0x0, 0x1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
  0x77, 0x0, 0x2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
  3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 0, 0, 0,
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Font Package 1, length=110                   tested
  //               
  /*
  0x6e, 0x00, 0x00,                 //3
  EFI_HII_PACKAGE_FONTS,  //1
  0x5c, 0x00, 0x00, 0x00,                    // 4 size of header
  0x5c, 0x00, 0x00, 0x00,  //offset  4      
  0xf1,0x00, 0xf2,0x00, 0xf3,0x00, 0xf4,0x00, 0xf5,0x00, 0xec, 0xec, // 10,, but we need pad 2 bytes here...
  0xff,0x33, 0xff, 0x44,// font style 4
  0x77,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x52,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x66,  //64
  //
  // Glyph block  1
  //
  EFI_HII_GIBT_GLYPH_DEFAULT, // 1  
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x99, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, //16, BitMapData
  
  EFI_HII_GIBT_END, //1
  */
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //
  // Guid Package 1
  //
  
  0x14, 0x00, 0x00,  //3                                    tested
  EFI_HII_PACKAGE_TYPE_GUID, //1
  0x5a, 0xc9, 0x87, 0x03, 0x3, 0xd7, 0x46, 0x23, 0xb2, 0xab, 0xd0, 0xc7, 0xdd, 0x90, 0x44, 0xf8, //16, EFI_GUID
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //
  // EFI_HII_PACKAGE_FORM
  //
  0x08, 0x00, 0x00, // 3                tested
  EFI_HII_PACKAGE_FORM,
  
  //
  // Opcode 1
  //
  EFI_IFR_AND_OP,
  0x82,
  
  EFI_IFR_END_OP,
  0x02,
  
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //
  // EFI_HII_PACKAGE_STRINGS
  //
  0x4e, 0x00, 0x00, //3                                       tested
  EFI_HII_PACKAGE_STRINGS, //1
  
  0x3c, 0x00, 0x00, 0x00, //4
  0x3c, 0x00, 0x00, 0x00, //offset 4
  0x00, 0x00, 0x11, 0x22, 0x44, 0x55, 0x77, 0x89, // language windows    32
  0x11, 0x00, 0x11, 0x22, 0x44, 0x55, 0x87, 0x89, 
  0x22, 0x00, 0x11, 0x22, 0x44, 0x55, 0x77, 0x89, 
  0x33, 0x00, 0x11, 0x22, 0x44, 0x55, 0x77, 0x89, 
  0x01, 0x00,    // language name, 2
  0x65, 0x6e, 0x2d, 0x55, 0x53, 0x3b, 0x7a, 0x68,  // language 14, en-US;zh-Hant
  0x2d, 0x48, 0x61, 0x6e, 0x74, 0x00, 
  
  EFI_HII_SIBT_STRING_UCS2, // 1
  0x45,  0x00,  0x6E,  0x00,  0x67,  0x00,  0x6C,  0x00,  0x69,  0x00,  0x73,  0x00,  0x68,  0x00,  0x00,  
  0x00, //16
  
  EFI_HII_SIBT_END, // 1
  
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // EFI_HII_PACKAGE_IMAGES
  //
  0x43, 0x00, 0x00, //3                              tested
  EFI_HII_PACKAGE_IMAGES,
  0x0c, 0x00, 0x00, 0x00, // image info offset 4
  0x39, 0x00, 0x00, 0x00, // palette info offset 4
  
  EFI_HII_IIBT_IMAGE_1BIT, //1
  0x01, 
  0x0b, 0x00, 
  0x13, 0x00,
  0x80, 0x00,
  0xc0, 0x00,
  0xe0, 0x00,
  0xf0, 0x00,
  0xf8, 0x00,
  0xfc, 0x00,
  0xfe, 0x00,
  0xff, 0x00,
  0xff, 0x80,
  0xff, 0xc0,
  0xff, 0xe0,
  0xfe, 0x00,
  0xef, 0x00,
  0xcf, 0x00,
  0x87, 0x80,
  0x07, 0x80,
  0x03, 0xc0,
  0x03, 0xc0,
  0x01, 0x80,
  
  EFI_HII_IIBT_END, //1

  0x01, 0x00,
  0x06, 0x00,
  0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF,
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // EFI_HII_PACKAGE_DEVICE_PATH
  //
//  0x08, 0x00, 0x00, //3                             tested
//  EFI_HII_PACKAGE_DEVICE_PATH, //1
  
//  0x01, 0x23, 0x45, 0x66, // dummy device path protocol instance address 4

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Keyboard layout package 1
  0xc0, 0x00, 0x00, //3
  EFI_HII_PACKAGE_KEYBOARD_LAYOUT, //1

  0x02, 0x00, //2, LayoutCount 
  
  //
  // Layout 1
  //
  
  0x5d, 0x00, //2, layout length
  0x95, 0xe4, 0x40, 0x8d, 0xaa, 0xe2, 0x6f, 0x4c, 0x89, 0x70, 0x68, 0x85, 0x09, 0xee, 0xc7, 0xd2, //16, GUID
  0x37, 0x00, 0x00, 0x00, //layout descriptor string offset 4
  0x02, // 1 Descriptor count
  //
  // Descriptor 1, 16 bytes,
  //
  EfiKeyD1, 0x00, 0x00, 0x00, // 4 
  'q', 0x00,
  'Q', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER,0x00,
  0x03, 0x00, // affected attributes
  //
  // Descriptor 2,  16 bytes
  //
  EfiKeyD2, 0x00, 0x00, 0x00,
  'w', 0x00,
  'W', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER, 0x00,
  0x3, 0x0,

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
  
  0x5d, 0x00, //2//layout length
  0x3e, 0x0b, 0xe6, 0x2a, 0xd6, 0xb9, 0xd8, 0x49, 0x9a, 0x16, 0xc2, 0x48, 0xf1, 0xeb, 0xa8, 0xdb, //16 GUID
  0x37, 0x00, 0x00, 0x00, //layout descriptor string offset 4
  0x02,  // 1 Descriptor count
  //
  // Descriptor 1, 16 bytes,
  //
  EfiKeyD3, 0x0, 0x0, 0x0,
  'e', 0x00,
  'E', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER, 0x0,
  0x3, 0x0,
  //
  // Descriptor 2,  16 bytes
  //
  EfiKeyD4, 0x0, 0x0, 0x0,
  'r', 0x00,
  'R', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER,  0x0,
  0x3, 0x0,

  //
  // EFI_DESCRIPTOR_STRING_BUNDLE
  //
  0x01, 0x00,                 // DescriptionCount 2
  'e', 0x0, 'n', 0x0, '-', 0x0, 'U', 0x0, 'S', 0x0,  // RFC3066 language code 10
  ' ', 0x0,                        // Space 2
  'S', 0x0, 'i', 0x0, 'm', 0x0, 'p', 0x0, 'l', 0x0, 'e', 0x0, '2', 0x0, 'o', 0x0, 'n', 0x0, 'l', 0x0, 'y', 0x0, '\0', 0x0, // DescriptionString  24  

  
  //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // End of package list, length=4,
  //
  0x4, 0x00, 0x00,                                                    // tested
  EFI_HII_PACKAGE_END                                                                                    
};

UINT8 mPackageList2[] = {                                                                         
  //                                                                                             
  // EFI_HII_PACKAGE_LIST_HEADER, total length = 376-122 =254.
  //
  0xd3, 0xde, 0x85, 0x86, 0xce, 0x1b, 0xf3, 0x43, 0xa2, 0x0c, 0xa3, 0x06, 0xec, 0x69, 0x72, 0xdd,    //16 
  0x3E, 0x01, 0x00, 0x00,     // 4
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //                                                                                             
  // Simple Font Package 2, length = 74.            tested                                                                                                                                 
  //                                                                                             
  0x4A, 0x00, 0x00,                        // 3                                                                
  EFI_HII_PACKAGE_SIMPLE_FONTS,  // 1                                                                
  1, 0,                         // 2
  1, 0,                         // 2
  0x33, 0x0, 0, 1, 2, 3, 4, 5, 0, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,  //22
  0x44, 0x0, 0x2, 2, 3, 4, 5, 6, 0, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, // 22
  3, 4, 5, 6, 7, 8, 9, 10, 11, 9, 13, 14, 15, 16, 17, 18, 19, 20, 21, 0, 0, 0,  // 22
                                                                                                 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                 
  //
  // Font Package 2, length=122.                    tested
  //               
  /*
  0x7A, 0x00, 0x00,                 //3
  EFI_HII_PACKAGE_FONTS,  //1
  0x5C, 0x00, 0x00, 0x00,                     // 4 size of header
  0x5C, 0x00, 0x00, 0x00, //dummy offset  4      
  0xf1,0x00, 0xf2,0x00, 0xf3,0x00, 0xf4,0x00, 0xf5,0x00, 0xec, 0xec,// 10, but we need pad 2 bytes here..., 12
  0xff,0x11, 0xff, 0x22,// font style 4
  0x99,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x52,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 
  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x88,  //64
  
  //
  // Glyph block  1
  //
  EFI_HII_GIBT_GLYPH, // 1
  0xf1,0x00, 0xf2,0x00, 0xf3,0x00, 0xf4,0x00, 0xf5,0x00, // 10
  0xff,0x01, // 2
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, //16, BitMapData
  
  EFI_HII_GIBT_END, //1
  */
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //
  // Guid Package 1
  //
  
  0x14, 0x00, 0x00,  //3                                    tested
  EFI_HII_PACKAGE_TYPE_GUID, //1
  0x5a, 0xc9, 0x87, 0x03, 0x3, 0xd7, 0x46, 0x23, 0xb2, 0xab, 0xd0, 0xc7, 0xdd, 0x90, 0x44, 0xf8, //16, EFI_GUID
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Keyboard layout package 2
  0xc0, 0x00, 0x00, //3
  EFI_HII_PACKAGE_KEYBOARD_LAYOUT, //1

  0x02, 0x00, //0xec, 0xec, //2, LayoutCount + 2 pads
  
  //
  // Layout 1
  //
  
  0x5d, 0x00, //2, layout length 
  0x1f, 0x6a, 0xf5, 0xe0, 0x6b, 0xdf, 0x7e, 0x4a, 0xa3, 0x9a, 0xe7, 0xa5, 0x19, 0x15, 0x45, 0xd6, //16, GUID
  0x37, 0x00, 0x00, 0x00, //layout descriptor string offset 4
  0x02, // 1 Descriptor count 
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
  0x3, 0x0,
  //
  // EFI_DESCRIPTOR_STRING_BUNDLE
  //
  0x01, 0x00,                 // DescriptionCount 2
  'e', 0x0, 'n', 0x0, '-', 0x0, 'U', 0x0, 'S', 0x0,  // RFC3066 language code 10
  ' ', 0x0,                        // Space 2
  'S', 0x0, 'i', 0x0, 'm', 0x0, 'p', 0x0, 'l', 0x0, 'e', 0x0, '3', 0x0, 'o', 0x0, 'n', 0x0, 'l', 0x0, 'y', 0x0, '\0', 0x0, // DescriptionString  24

  //
  // Layout 2
  //
  
  0x5d, 0x00, //2, layout length
  0xc9, 0x6a, 0xbe, 0x47, 0xcc, 0x54, 0xf9, 0x46, 0xa2, 0x62, 0xd5, 0x3b, 0x25, 0x6a, 0xc, 0x34, //16, GUID
  0x37, 0x00, 0x00, 0x00, //layout descriptor string offset 4
  0x02, // 1 Descriptor count 
  //
  // Descriptor 1, 16 bytes,
  //
  EfiKeyC3, 0x0, 0x0, 0x0,
  'd', 0x00,
  'D', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER, 0x0,
  0x3, 0x0,
  //
  // Descriptor 2,  16 bytes
  //
  EfiKeyC4, 0x0, 0x0, 0x0,
  'e', 0x00,
  'E', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER,  0x0,
  0x3, 0x0,
  //
  // EFI_DESCRIPTOR_STRING_BUNDLE
  //
  0x01, 0x00,                 // DescriptionCount 2
  'e', 0x0, 'n', 0x0, '-', 0x0, 'U', 0x0, 'S', 0x0,  // RFC3066 language code 10
  ' ', 0x0,                        // Space 2
  'S', 0x0, 'i', 0x0, 'm', 0x0, 'p', 0x0, 'l', 0x0, 'e', 0x0, '4', 0x0, 'o', 0x0, 'n', 0x0, 'l', 0x0, 'y', 0x0, '\0', 0x0, // DescriptionString  24


  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //
  // EFI_HII_PACKAGE_FORM
  //
  0x08, 0x00, 0x00, // 3
  EFI_HII_PACKAGE_FORM,

  
  //
  // Opcode 1
  //
  EFI_IFR_BITWISE_AND_OP,
  0x02,
  
  EFI_IFR_END_OP,
  0x02,
  
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // End of package list, length=4,
  //
  0x4, 0x00, 0x00,                                                    // tested
  EFI_HII_PACKAGE_END                                                                                    
};


EFI_GUID mPackageListGuid1 = {
  0x03abcd89, 0x03f4, 0x7044, {0x81, 0xde, 0x99, 0xb1, 0x81, 0x20, 0xf7, 0x68 }
};

EFI_GUID mPackageListGuid2 = {
  0x8685ded3, 0x1bce, 0x43f3, {0xa2, 0x0c, 0xa3, 0x06, 0xec, 0x69, 0x72, 0xdd }
};

EFI_GUID mKBLayoutGuid11 = {
  0x8d40e495, 0xe2aa, 0x4c6f, {0x89, 0x70, 0x68, 0x85, 0x09, 0xee, 0xc7, 0xd2 }
};

EFI_GUID mKBLayoutGuid12 = {
  0x2ae60b3e, 0xb9d6, 0x49d8, {0x9a, 0x16, 0xc2, 0x48, 0xf1, 0xeb, 0xa8, 0xdb }
};

EFI_GUID mKBLayoutGuid21 = {
  0xe0f56a1f, 0xdf6b, 0x4a7e, {0xa3, 0x9a, 0xe7, 0xa5, 0x19, 0x15, 0x45, 0xd6 }
};

EFI_GUID mKBLayoutGuid22 = {
  0x47be6ac9, 0x54cc, 0x46f9, {0xa2, 0x62, 0xd5, 0x3b, 0x25, 0x6a, 0x0c, 0x34 }
};

EFI_GUID mPackageGuid = {
  0x0387c95a, 0xd703, 0x2346, {0xb2, 0xab, 0xd0, 0xc7, 0xdd, 0x90, 0x44, 0xf8 }
};
