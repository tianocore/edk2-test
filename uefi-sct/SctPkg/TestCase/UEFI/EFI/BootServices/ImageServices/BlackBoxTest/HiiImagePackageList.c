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

    HIIImagePackageList.c
    
Abstract:

    Contain some package list images.

Revision History

--*/

#include "ImageBBTest.h"


UINT8 mPackageList[] = {
  //                                                                                             
  // EFI_HII_PACKAGE_LIST_HEADER, total length = 60.
  // Image,
  // 
  0x3f,0xe3,0x59,0xe0,0xf1,0x7c,0x6e,0x42,0x9e,0x60, 0x7b, 0xbf, 0x72, 0x75, 0xde, 0x2a,  //16 EFI_GUID
  0x3c,0x00,0x00,0x00,       //4
   
  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Guid Package 1
  //
  0x14, 0x00, 0x00,  //3                                    tested
  EFI_HII_PACKAGE_TYPE_GUID, //1
  0x2b,0xc3,0xae,0xcd,0x3a,0x72,0x67,0x41,0xb5, 0x9, 0x3, 0x67, 0x68, 0x4f, 0x7e, 0xdb,   //16 EFI_GUID
  
  ////////////////////////////////////////////////////////////////////////////////////////////
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
  // End of package list, length=4,
  //
  0x4, 0x00, 0x00,                                                    // tested
  EFI_HII_PACKAGE_END                                                         
};


UINT8 mPackageList1[] = {                                                                         
  //                                                                                             
  // EFI_HII_PACKAGE_LIST_HEADER, total length = 452-110 =342.
  // SimpleFont; Font; GUID, Form, String, Image, DevicePath, KeyboardLayout
  //                                                                                             
  0x3f,0xe3,0x59,0xe0,0xf1,0x7c,0x6e,0x42,0x9e,0x60, 0x7b, 0xbf, 0x72, 0x75, 0xde, 0x2a,  //16 EFI_GUID
  0x48,0x01,0x00,0x00,       //4
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
  0x2b,0xc3,0xae,0xcd,0x3a,0x72,0x67,0x41,0xb5, 0x9, 0x3, 0x67, 0x68, 0x4f, 0x7e, 0xdb,   //16 EFI_GUID
  
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
  0x7a, 0x00, 0x00, //3
  EFI_HII_PACKAGE_KEYBOARD_LAYOUT, //1

  0x02, 0x00, //0xec, 0xec, //2, LayoutCount + 2 pads
  
  //
  // Layout 1
  //
  
  0x3a, 0x00, //0xec, 0xec, //2, layout length + 2 pads
  0x95, 0xe4, 0x40, 0x8d, 0xaa, 0xe2, 0x6f, 0x4c, 0x89, 0x70, 0x68, 0x85, 0x09, 0xee, 0xc7, 0xd2, //16, GUID
  0xff, 0xf1, 0xf2, 0x3f, //layout descriptor string offset 4
  0x02, 0x00, 0x00, 0x00, // 1 Descriptor count +3 pads
  //
  // Descriptor 1, 16 bytes,
  //
  EfiKeyD1, 0x00, 0x00, 0x00, // 4 
  'q', 0x00,
  'Q', 0x00,
  0x11, 0x00,
  0x22, 0x00,
  EFI_NULL_MODIFIER,0x00,
  0x33, 0x00, // affected attributes
  //
  // Descriptor 2,  16 bytes
  //
  EfiKeyD2, 0x00, 0x00, 0x00,
  'w', 0x00,
  'W', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER, 0x00,
  0x0, 0x0,
  
  //
  // Layout 2
  //
  
  0x3a, 0x00, //0xec, 0xec, //2, layout length + 2 pads
  0x3e, 0x0b, 0xe6, 0x2a, 0xd6, 0xb9, 0xd8, 0x49, 0x9a, 0x16, 0xc2, 0x48, 0xf1, 0xeb, 0xa8, 0xdb, //16 GUID
  0xf4, 0xf0, 0xe2, 0xff, //layout descriptor string offset 4
  0x02, 0x00, 0x00, 0x00, // 1 Descriptor count + 3pads
  //
  // Descriptor 1, 16 bytes,
  //
  EfiKeyD3, 0x0, 0x0, 0x0,
  'e', 0x00,
  'E', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER, 0x0,
  0x0, 0x0,
  //
  // Descriptor 2,  16 bytes
  //
  EfiKeyD4, 0x0, 0x0, 0x0,
  'r', 0x00,
  'R', 0x00,
  0x00, 0x00,
  0x00, 0x00,
  EFI_NULL_MODIFIER,  0x0,
  0x0, 0x0,
  

  
  //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // End of package list, length=4,
  //
  0x4, 0x00, 0x00,                                                    // tested
  EFI_HII_PACKAGE_END                                                                                    
};


EFI_GUID mPackageListGuid = {
  0xe059e33f, 0x7cf1, 0x426e, {0x9e, 0x60, 0x7b, 0xbf, 0x72, 0x75, 0xde, 0x2a 
}};

EFI_GUID mPackageGuid = {
  0xcdaec32b, 0x723a, 0x4167, {0xb5, 0x9, 0x3, 0x67, 0x68, 0x4f, 0x7e, 0xdb
}};
