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

    HIIPackageListImage.c
    
Abstract:

    Contain some package list images.

Revision History

--*/

#include "HIIImageExBBTestMain.h"

UINT8 mPackageList1[] = {                                                                         
  //                                                                                             
  // EFI_HII_PACKAGE_LIST_HEADER, total length = 452-110 =342.
  // SimpleFont; Font; GUID, Form, String, Image, DevicePath, KeyboardLayout
  //                                                                                             
  0x89, 0xcd, 0xab, 0x03, 0xf4, 0x03, 0x44, 0x70, 0x81, 0xde, 0x99, 0xb1, 0x81, 0x20, 0xf7, 0x68,    //16
  0x8e, 0x01, 0x00, 0x00,     // 4    
  //                                                                                             
  // Simple Font Package 1, length = 74.            tested                                                         
  //                                                                                             
  0x4A, 0x00, 0x00,                
  EFI_HII_PACKAGE_SIMPLE_FONTS,                                                                  
  1, 0,                                                                                             
  1, 0,
  0x55, 0x0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
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
  0x40, 0x00, 0x00, //3                                       tested
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
  
  EFI_HII_SIBT_DUPLICATE, // 1
  0x02, 0x00, //2
  
  EFI_HII_SIBT_END, // 1
  
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // EFI_HII_PACKAGE_IMAGES
  //
  0x10, 0x00, 0x00, //3                              tested
  EFI_HII_PACKAGE_IMAGES,
  0x0c, 0x00, 0x00, 0x00, // image info offset 4
  0x00, 0x00, 0x00, 0x00, // palette info offset 4
  
  EFI_HII_IIBT_DUPLICATE, //1
  0x01, 0x00, //2  image id
  EFI_HII_IIBT_END, //1
  
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
  0x03, 0x00,
  //
  // EFI_DESCRIPTOR_STRING_BUNDLE
  //
  0x01, 0x00,                 // DescriptionCount 2
  'e', 0x0, 'n', 0x0, '-', 0x0, 'U', 0x0, 'S', 0x0,  // RFC3066 language code 10
  ' ', 0x0,                        // Space 2
  'S', 0x0, 'i', 0x0, 'm', 0x0, 'p', 0x0, 'l', 0x0, 'e', 0x0, '2', 0x0, 'o', 0x0, 'n', 0x0, 'l', 0x0, 'y', 0x0, '\0', 0x0, // DescriptionString  24
  
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
  EfiKeyD3, 0x0, 0x0, 0x0,
  'e', 0x00,
  'E', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER, 0x0,
  0x03, 0x00,
  //
  // Descriptor 2,  16 bytes
  //
  EfiKeyD4, 0x0, 0x0, 0x0,
  'r', 0x00,
  'R', 0x00,
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

  
  //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // End of package list, length=4,
  //
  0x4, 0x00, 0x00,                                                    // tested
  EFI_HII_PACKAGE_END                                                                                    
};

CHAR8 mImage[] = {
  0x00
};

CHAR8 mSetNewImage[] = {
  0x00
};