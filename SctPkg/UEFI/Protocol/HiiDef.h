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
   
--*/
/*++

Module Name:

  HiiDef.h

Abstract:

  Hii relative definitions, such as Hii package, IFR OpCode etc

Revision History

--*/
#ifndef _HII_DEFINITION_H_
#define _HII_DEFINITION_H_

#include <UEFI/Protocol/GraphicsOutput.h>

typedef VOID    *EFI_HII_HANDLE;
typedef CHAR16  *EFI_STRING;
typedef UINT16  EFI_IMAGE_ID;
typedef UINT16  EFI_STRING_ID;
typedef UINT16  EFI_FORM_ID;
typedef UINT16  EFI_DEFAULT_ID;
typedef UINT32  EFI_HII_FONT_STYLE;
typedef VOID    *EFI_FONT_HANDLE;

//
// HII package list
//
typedef struct {
  EFI_GUID               PackageListGuid;
  UINT32                 PackageLength;
} EFI_HII_PACKAGE_LIST_HEADER;

typedef struct {
  UINT32                 Length:24;
  UINT32                 Type:8;
} EFI_HII_PACKAGE_HEADER;

#define EFI_HII_PACKAGE_TYPE_ALL             0x00
#define EFI_HII_PACKAGE_TYPE_GUID            0x01
#define EFI_HII_PACKAGE_FORM                 0x02
//#define EFI_HII_PACKAGE_KEYBOARD_LAYOUT      0x03
#define EFI_HII_PACKAGE_STRINGS              0x04
#define EFI_HII_PACKAGE_FONTS                0x05
#define EFI_HII_PACKAGE_IMAGES               0x06
#define EFI_HII_PACKAGE_SIMPLE_FONTS         0x07
#define EFI_HII_PACKAGE_DEVICE_PATH          0x08
#define EFI_HII_PACKAGE_KEYBOARD_LAYOUT      0x09
#define EFI_HII_PACKAGE_END                  0xDF
#define EFI_HII_PACKAGE_TYPE_SYSTEM_BEGIN    0xE0
#define EFI_HII_PACKAGE_TYPE_SYSTEM_END      0xFF

//
// Simplified Font Package
//

#define EFI_GLYPH_HEIGHT                     19
#define EFI_GLYPH_WIDTH                      8
//
// Contents of EFI_NARROW_GLYPH.Attributes
//
#define EFI_GLYPH_NON_SPACING                0x01
#define EFI_GLYPH_WIDE                       0x02


typedef struct {
  CHAR16                 UnicodeWeight;
  UINT8                  Attributes;
  UINT8                  GlyphCol1[EFI_GLYPH_HEIGHT];
} EFI_NARROW_GLYPH;

typedef struct {
  CHAR16                 UnicodeWeight;
  UINT8                  Attributes;
  UINT8                  GlyphCol1[EFI_GLYPH_HEIGHT];
  UINT8                  GlyphCol2[EFI_GLYPH_HEIGHT];
  UINT8                  Pad[3];
} EFI_WIDE_GLYPH;

typedef struct _EFI_HII_SIMPLE_FONT_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER Header;
  UINT16                 NumberOfNarrowGlyphs;
  UINT16                 NumberOfWideGlyphs;
  EFI_NARROW_GLYPH       *NarrowGlyphs;
  EFI_WIDE_GLYPH         *WideGlyphs;
} EFI_HII_SIMPLE_FONT_PACKAGE_HDR;

//
// Font Package
//

#define EFI_HII_FONT_STYLE_BOLD              0x00000001
#define EFI_HII_FONT_STYLE_ITALIC            0x00000002
#define EFI_HII_FONT_STYLE_EMBOSS            0x00010000
#define EFI_HII_FONT_STYLE_OUTLINE           0x00020000
#define EFI_HII_FONT_STYLE_SHADOW            0x00040000
#define EFI_HII_FONT_STYLE_UNDERLINE         0x00080000
#define EFI_HII_FONT_STYLE_DBL_UNDER         0x00100000

typedef UINT32        EFI_HII_OUT_FLAGS;
#define EFI_HII_OUT_FLAG_CLIP           0x00000001
#define EFI_HII_OUT_FLAG_WRAP           0x00000002
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_Y   0x00000004
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_X   0x00000008
#define EFI_HII_OUT_FLAG_TRANSPARENT    0x00000010
#define EFI_HII_IGNORE_IF_NO_GLYPH      0x00000020
#define EFI_HII_IGNORE_LINE_BREAK       0x00000040
#define EFI_HII_DIRECT_TO_SCREEN        0x00000080

typedef UINT32        EFI_FONT_INFO_MASK;
#define EFI_FONT_INFO_SYS_FONT          0x00000001
#define EFI_FONT_INFO_SYS_SIZE          0x00000002
#define EFI_FONT_INFO_SYS_STYLE         0x00000004
#define EFI_FONT_INFO_SYS_FORE_COLOR    0x00000010
#define EFI_FONT_INFO_SYS_BACK_COLOR    0x00000020
#define EFI_FONT_INFO_RESIZE            0x00001000
#define EFI_FONT_INFO_RESTYLE           0x00002000
#define EFI_FONT_INFO_ANY_FONT          0x00010000
#define EFI_FONT_INFO_ANY_SIZE          0x00020000
#define EFI_FONT_INFO_ANY_STYLE         0x00040000

typedef struct {
  EFI_HII_FONT_STYLE    FontStyle;
  UINT16                FontSize; // character cell size in pixels
  CHAR16                FontName[1];
} EFI_FONT_INFO;

typedef struct _EFI_FONT_DISPLAY_INFO {
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL     ForegroundColor;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL     BackgroundColor;
  EFI_FONT_INFO_MASK                FontInfoMask;
  EFI_FONT_INFO                     FontInfo;
} EFI_FONT_DISPLAY_INFO;

typedef struct _EFI_HII_GLYPH_INFO {
  UINT16                 Width;
  UINT16                 Height;
  INT16                  OffsetX;
  INT16                  OffsetY;
  INT16                  AdvanceX;
} EFI_HII_GLYPH_INFO;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL EFI_GRAPHICS_OUTPUT_PROTOCOL;;

typedef struct _EFI_IMAGE_OUTPUT {
  UINT16 Width;
  UINT16 Height;
  union {
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL    *Bitmap;
    EFI_GRAPHICS_OUTPUT_PROTOCOL     *Screen;
  } Image;
} EFI_IMAGE_OUTPUT;

typedef struct _EFI_HII_ROW_INFO {
  UINTN                        StartIndex;
  UINTN                        EndIndex;
  UINTN                        LineHeight;
  UINTN                        LineWidth;
  UINTN                        BaselineOffset;
} EFI_HII_ROW_INFO;

typedef struct _EFI_HII_FONT_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER Header;
  UINT32                 HdrSize;
  UINT32                 GlyphBlockOffset;
  EFI_HII_GLYPH_INFO     Cell;
  EFI_HII_FONT_STYLE     FontStyle;
  CHAR16                 FontFamily[1];
} EFI_HII_FONT_PACKAGE_HDR;

#define EFI_HII_GIBT_END                  0x00
#define EFI_HII_GIBT_GLYPH                0x10
#define EFI_HII_GIBT_GLYPHS               0x11
#define EFI_HII_GIBT_GLYPH_DEFAULT        0x12
#define EFI_HII_GIBT_GLYPHS_DEFAULT       0x13
#define EFI_HII_GIBT_DUPLICATE            0x20
#define EFI_HII_GIBT_SKIP2                0x21
#define EFI_HII_GIBT_SKIP1                0x22
#define EFI_HII_GIBT_DEFAULTS             0x23
#define EFI_HII_GIBT_EXT1                 0x30
#define EFI_HII_GIBT_EXT2                 0x31
#define EFI_HII_GIBT_EXT4                 0x32

//
// Device Path Package
//
typedef struct _EFI_HII_DEVICE_PATH_PACKAGE {
  EFI_HII_PACKAGE_HEADER   Header;
  EFI_DEVICE_PATH_PROTOCOL *DevicePath;
} EFI_HII_DEVICE_PATH_PACKAGE;

//
// GUID Package
//
typedef struct _EFI_HII_GUID_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER   Header;
  EFI_GUID                 Guid;
} EFI_HII_GUID_PACKAGE_HDR;

//
// String Package
//

#define UEFI_CONFIG_LANG       L"x-UEFI"
#define UEFI_CONFIG_LANG2      L"x-i-UEFI"     // BUGBUG, spec need to be updated.

typedef struct _EFI_HII_STRING_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER  Header;
  UINT32                  HdrSize;
  UINT32                  StringInfoOffset;
  CHAR16                  LanguageWindow[16];
  EFI_STRING_ID           LanguageName;
  CHAR8                   Language[1];
} EFI_HII_STRING_PACKAGE_HDR;

typedef struct {
  UINT8                   BlockType;
  //UINT8                 BlockBody[];
} EFI_HII_STRING_BLOCK;

#define EFI_HII_SIBT_END                     0x00
#define EFI_HII_SIBT_STRING_SCSU             0x10
#define EFI_HII_SIBT_STRING_SCSU_FONT        0x11
#define EFI_HII_SIBT_STRINGS_SCSU            0x12
#define EFI_HII_SIBT_STRINGS_SCSU_FONT       0x13
#define EFI_HII_SIBT_STRING_UCS2             0x14
#define EFI_HII_SIBT_STRING_UCS2_FONT        0x15
#define EFI_HII_SIBT_STRINGS_UCS2            0x16
#define EFI_HII_SIBT_STRINGS_UCS2_FONT       0x17
#define EFI_HII_SIBT_DUPLICATE               0x20
#define EFI_HII_SIBT_SKIP2                   0x21
#define EFI_HII_SIBT_SKIP1                   0x22
#define EFI_HII_SIBT_EXT1                    0x30
#define EFI_HII_SIBT_EXT2                    0x31
#define EFI_HII_SIBT_EXT4                    0x32
#define EFI_HII_SIBT_FONT                    0x40

//
// Image Packages
//

typedef struct _EFI_HII_IMAGE_PACKAGE_HDR {
  EFI_HII_PACKAGE_HEADER       Header;
  UINT32                       ImageInfoOffset;
  UINT32                       PaletteInfoOffset;
} EFI_HII_IMAGE_PACKAGE_HDR;

typedef struct _EFI_HII_IMAGE_BLOCK {
  UINT8                        BlockType;
} EFI_HII_IMAGE_BLOCK;

#define EFI_IMAGE_TRANSPARENT          0x00000001

typedef struct _EFI_IMAGE_INPUT {
  UINT32                           Flags;
  UINT16                           Width;
  UINT16                           Height;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL    *Bitmap;
} EFI_IMAGE_INPUT;

typedef UINT32    EFI_HII_DRAW_FLAGS;
#define EFI_HII_DRAW_FLAG_CLIP             0x00000001
#define EFI_HII_DRAW_FLAG_TRANSPARENT      0x00000030
#define EFI_HII_DRAW_FLAG_DEFAULT          0x00000000
#define EFI_HII_DRAW_FLAG_FORCE_TRANS      0x00000010
#define EFI_HII_DRAW_FLAG_FORCE_OPAQUE     0x00000020
#define EFI_HII_DIRECT_TO_SCREEN           0x00000080

#define EFI_HII_IIBT_END               0x00
#define EFI_HII_IIBT_IMAGE_1BIT        0x10
#define EFI_HII_IIBT_IMAGE_1BIT_TRANS  0x11
#define EFI_HII_IIBT_IMAGE_4BIT        0x12
#define EFI_HII_IIBT_IMAGE_4BIT_TRANS  0x13
#define EFI_HII_IIBT_IMAGE_8BIT        0x14
#define EFI_HII_IIBT_IMAGE_8BIT_TRANS  0x15
#define EFI_HII_IIBT_IMAGE_24BIT       0x16
#define EFI_HII_IIBT_IMAGE_24BIT_TRANS 0x17
#define EFI_HII_IIBT_IMAGE_JPEG        0x18
#define EFI_HII_IIBT_DUPLICATE         0x20
#define EFI_HII_IIBT_SKIP2             0x21
#define EFI_HII_IIBT_SKIP1             0x22
#define EFI_HII_IIBT_EXT1              0x30
#define EFI_HII_IIBT_EXT2              0x31
#define EFI_HII_IIBT_EXT4              0x32

//
// Forms Package
//

typedef struct {
  UINT8 Hour;
  UINT8 Minute;
  UINT8 Second;
} EFI_HII_TIME;

typedef struct {
  UINT16 Year;
  UINT8  Month;
  UINT8  Day;
} EFI_HII_DATE;

typedef union {
  UINT8           u8;
  UINT16          u16;
  UINT32          u32;
  UINT64          u64;
  BOOLEAN         b;
  EFI_HII_TIME    time;
  EFI_HII_DATE    date;
  EFI_STRING_ID   string;
} EFI_IFR_TYPE_VALUE;

#define EFI_IFR_FORM_OP                0x01
#define EFI_IFR_SUBTITLE_OP            0x02
#define EFI_IFR_TEXT_OP                0x03
#define EFI_IFR_IMAGE_OP               0x04
#define EFI_IFR_ONE_OF_OP              0x05
#define EFI_IFR_CHECKBOX_OP            0x06
#define EFI_IFR_NUMERIC_OP             0x07
#define EFI_IFR_PASSWORD_OP            0x08
#define EFI_IFR_ONE_OF_OPTION_OP       0x09
#define EFI_IFR_SUPPRESS_IF_OP         0x0A
#define EFI_IFR_LOCKED_OP              0x0B
#define EFI_IFR_ACTION_OP              0x0C
#define EFI_IFR_RESET_BUTTON_OP        0x0D
#define EFI_IFR_FORM_SET_OP            0x0E
#define EFI_IFR_REF_OP                 0x0F
#define EFI_IFR_NO_SUBMIT_IF_OP        0x10
#define EFI_IFR_INCONSISTENT_IF_OP     0x11
#define EFI_IFR_EQ_ID_VAL_OP           0x12
#define EFI_IFR_EQ_ID_ID_OP            0x13
#define EFI_IFR_EQ_ID_LIST_OP          0x14
#define EFI_IFR_AND_OP                 0x15
#define EFI_IFR_OR_OP                  0x16
#define EFI_IFR_NOT_OP                 0x17
#define EFI_IFR_RULE_OP                0x18
#define EFI_IFR_GRAY_OUT_IF_OP         0x19
#define EFI_IFR_DATE_OP                0x1A
#define EFI_IFR_TIME_OP                0x1B
#define EFI_IFR_STRING_OP              0x1C
#define EFI_IFR_REFRESH_OP             0x1D
#define EFI_IFR_DISABLE_IF_OP          0x1E
#define EFI_IFR_TO_LOWER_OP            0x20
#define EFI_IFR_TO_UPPER_OP            0x21
#define EFI_IFR_ORDERED_LIST_OP        0x23
#define EFI_IFR_VARSTORE_OP            0x24
#define EFI_IFR_VARSTORE_NAME_VALUE_OP 0x25
#define EFI_IFR_VARSTORE_EFI_OP        0x26
#define EFI_IFR_VARSTORE_DEVICE_OP     0x27
#define EFI_IFR_VERSION_OP             0x28
#define EFI_IFR_END_OP                 0x29
#define EFI_IFR_MATCH_OP               0x2A
#define EFI_IFR_EQUAL_OP               0x2F
#define EFI_IFR_NOT_EQUAL_OP           0x30
#define EFI_IFR_GREATER_THAN_OP        0x31
#define EFI_IFR_GREATER_EQUAL_OP       0x32
#define EFI_IFR_LESS_THAN_OP           0x33
#define EFI_IFR_LESS_EQUAL_OP          0x34
#define EFI_IFR_BITWISE_AND_OP         0x35
#define EFI_IFR_BITWISE_OR_OP          0x36
#define EFI_IFR_BITWISE_NOT_OP         0x37
#define EFI_IFR_SHIFT_LEFT_OP          0x38
#define EFI_IFR_SHIFT_RIGHT_OP         0x39
#define EFI_IFR_ADD_OP                 0x3A
#define EFI_IFR_SUBTRACT_OP            0x3B
#define EFI_IFR_MULTIPLY_OP            0x3C
#define EFI_IFR_DIVIDE_OP              0x3D
#define EFI_IFR_MODULO_OP              0x3E
#define EFI_IFR_RULE_REF_OP            0x3F
#define EFI_IFR_QUESTION_REF1_OP       0x40
#define EFI_IFR_QUESTION_REF2_OP       0x41
#define EFI_IFR_UINT8_OP               0x42
#define EFI_IFR_UINT16_OP              0x43
#define EFI_IFR_UINT32_OP              0x44
#define EFI_IFR_UINT64_OP              0x45
#define EFI_IFR_TRUE_OP                0x46
#define EFI_IFR_FALSE_OP               0x47
#define EFI_IFR_TO_UINT_OP             0x48
#define EFI_IFR_TO_STRING_OP           0x49
#define EFI_IFR_TO_BOOLEAN_OP          0x4A
#define EFI_IFR_MID_OP                 0x4B
#define EFI_IFR_FIND_OP                0x4C
#define EFI_IFR_TOKEN_OP               0x4D
#define EFI_IFR_STRING_REF1_OP         0x4E
#define EFI_IFR_STRING_REF2_OP         0x4F
#define EFI_IFR_CONDITIONAL_OP         0x50
#define EFI_IFR_QUESTION_REF3_OP       0x51
#define EFI_IFR_ZERO_OP                0x52
#define EFI_IFR_ONE_OP                 0x53
#define EFI_IFR_ONES_OP                0x54
#define EFI_IFR_UNDEFINED_OP           0x55
#define EFI_IFR_LENGTH_OP              0x56
#define EFI_IFR_DUP_OP                 0x57
#define EFI_IFR_THIS_OP                0x58
#define EFI_IFR_SPAN_OP                0x59
#define EFI_IFR_VALUE_OP               0x5A
#define EFI_IFR_DEFAULT_OP             0x5B
#define EFI_IFR_DEFAULTSTORE_OP        0x5C
#define EFI_IFR_CATENATE_OP            0x5E
#define EFI_IFR_GUID_OP                0x5F

//
// HII database
//
typedef UINTN         EFI_HII_DATABASE_NOTIFY_TYPE;
#define EFI_HII_DATABASE_NOTIFY_NEW_PACK        0x00000001
#define EFI_HII_DATABASE_NOTIFY_REMOVE_PACK     0x00000002
#define EFI_HII_DATABASE_NOTIFY_EXPORT_PACK     0x00000004
#define EFI_HII_DATABASE_NOTIFY_ADD_PACK        0x00000008

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_NOTIFY) (
  IN UINT8                           PackageType,
  IN CONST EFI_GUID                  *PackageGuid,
  IN CONST EFI_HII_PACKAGE_HEADER    *Package,
  IN EFI_HII_HANDLE                  Handle,
  IN EFI_HII_DATABASE_NOTIFY_TYPE    NotifyType
);

typedef enum {    
  EfiKeyLCtrl,    
  EfiKeyA0,       
  EfiKeyLAlt, 
  EfiKeySpaceBar,
  EfiKeyA2, 
  EfiKeyA3, 
  EfiKeyA4, 
  EfiKeyRCtrl, 
  EfiKeyLeftArrow,
  EfiKeyDownArrow, 
  EfiKeyRightArrow, 
  EfiKeyZero,
  EfiKeyPeriod, 
  EfiKeyEnter, 
  EfiKeyLShift, 
  EfiKeyB0,
  EfiKeyB1, 
  EfiKeyB2, 
  EfiKeyB3, 
  EfiKeyB4, 
  EfiKeyB5, 
  EfiKeyB6,
  EfiKeyB7, 
  EfiKeyB8, 
  EfiKeyB9, 
  EfiKeyB10, 
  EfiKeyRshift,
  EfiKeyUpArrow, 
  EfiKeyOne, 
  EfiKeyTwo, 
  EfiKeyThree,
  EfiKeyCapsLock, 
  EfiKeyC1, 
  EfiKeyC2, 
  EfiKeyC3, 
  EfiKeyC4,
  EfiKeyC5, 
  EfiKeyC6, 
  EfiKeyC7, 
  EfiKeyC8, 
  EfiKeyC9,
  EfiKeyC10, 
  EfiKeyC11, 
  EfiKeyC12, 
  EfiKeyFour, 
  EfiKeyFive,
  EfiKeySix, 
  EfiKeyPlus, 
  EfiKeyTab, 
  EfiKeyD1, 
  EfiKeyD2,
  EfiKeyD3, 
  EfiKeyD4, 
  EfiKeyD5, 
  EfiKeyD6, 
  EfiKeyD7, 
  EfiKeyD8,
  EfiKeyD9, 
  EfiKeyD10, 
  EfiKeyD11, 
  EfiKeyD12, 
  EfiKeyD13,
  EfiKeyDel, 
  EfiKeyEnd, 
  EfiKeyPgDn, 
  EfiKeySeven, 
  EfiKeyEight,
  EfiKeyNine, 
  EfiKeyE0, 
  EfiKeyE1, 
  EfiKeyE2,
  EfiKeyE3,
  EfiKeyE4, 
  EfiKeyE5, 
  EfiKeyE6, 
  EfiKeyE7, 
  EfiKeyE8, 
  EfiKeyE9,
  EfiKeyE10, 
  EfiKeyE11, 
  EfiKeyE12, 
  EfiKeyBackSpace,
  EfiKeyIns, 
  EfiKeyHome, 
  EfiKeyPgUp, 
  EfiKeyNLck, 
  EfiKeySlash,
  EfiKeyAsterisk, 
  EfiKeyMinus, 
  EfiKeyEsc, 
  EfiKeyF1, 
  EfiKeyF2,
  EfiKeyF3, 
  EfiKeyF4, 
  EfiKeyF5, 
  EfiKeyF6, 
  EfiKeyF7, 
  EfiKeyF8,
  EfiKeyF9, 
  EfiKeyF10, 
  EfiKeyF11, 
  EfiKeyF12, 
  EfiKeyPrint,
  EfiKeySLck, 
  EfiKeyPause
} EFI_KEY;

#define EFI_NULL_MODIFIER                  0x0000
#define EFI_LEFT_CONTROL_MODIFIER          0x0001
#define EFI_RIGHT_CONTROL_MODIFIER         0x0002
#define EFI_LEFT_ALT_MODIFIER              0x0003
#define EFI_RIGHT_ALT_MODIFIER             0x0004
#define EFI_ALT_GR_MODIFIER                0x0005
#define EFI_INSERT_MODIFIER                0x0006
#define EFI_DELETE_MODIFIER                0x0007
#define EFI_PAGE_DOWN_MODIFIER             0x0008
#define EFI_PAGE_UP_MODIFIER               0x0009
#define EFI_HOME_MODIFIER                  0x000A
#define EFI_END_MODIFIER                   0x000B
#define EFI_LEFT_SHIFT_MODIFIER            0x000C
#define EFI_RIGHT_SHIFT_MODIFIER           0x000D
#define EFI_CAPS_LOCK_MODIFIER             0x000E
#define EFI_NUM_LOCK _MODIFIER             0x000F
#define EFI_LEFT_ARROW_MODIFIER            0x0010
#define EFI_RIGHT_ARROW_MODIFIER           0x0011
#define EFI_DOWN_ARROW_MODIFIER            0x0012
#define EFI_UP_ARROW_MODIFIER              0X0013
#define EFI_NS_KEY_MODIFIER                0x0014
#define EFI_NS_KEY_DEPENDENCY_MODIFIER     0x0015
#define EFI_FUNCTION_KEY_ONE_MODIFIER      0x0016
#define EFI_FUNCTION_KEY_TWO_MODIFIER      0x0017
#define EFI_FUNCTION_KEY_THREE_MODIFIER    0x0018
#define EFI_FUNCTION_KEY_FOUR_MODIFIER     0x0019
#define EFI_FUNCTION_KEY_FIVE_MODIFIER     0x001A
#define EFI_FUNCTION_KEY_SIX_MODIFIER      0x001B
#define EFI_FUNCTION_KEY_SEVEN_MODIFIER    0x001C
#define EFI_FUNCTION_KEY_EIGHT_MODIFIER    0x001D
#define EFI_FUNCTION_KEY_NINE_MODIFIER     0x001E
#define EFI_FUNCTION_KEY_TEN_MODIFIER      0x001F
#define EFI_FUNCTION_KEY_ELEVEN_MODIFIER   0x0020
#define EFI_FUNCTION_KEY_TWELVE_MODIFIER   0x0021

typedef struct {
  EFI_KEY               Key;
  CHAR16                Unicode; 
  CHAR16                ShiftedUnicode;
  CHAR16                AltGrUnicode; 
  CHAR16                ShiftedAltGrUnicode; 
  UINT16                Modifier;
  UINT16                AffectedAttribute;
} EFI_KEY_DESCRIPTOR;

typedef struct {
  UINT16                  LayoutLength;
  EFI_GUID                Guid;
  UINT32                  LayoutDescriptorStringOffset;       
  UINT8                   DescriptorCount;
  EFI_KEY_DESCRIPTOR      Descriptors[1];
} EFI_HII_KEYBOARD_LAYOUT;

#endif
