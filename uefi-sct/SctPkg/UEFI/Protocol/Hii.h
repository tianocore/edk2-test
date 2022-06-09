/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>
  (C) Copyright 2017 Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

/*++

Module Name:

  HiiProtocol.h

Abstract:

  Hii protocol definitions, including HIIDatabase, HIIString, HIIFont, HIIImage protocol

Revision History

--*/
#ifndef _HII_PROTOCOL_DEF_H_
#define _HII_PROTOCOL_DEF_H_

#define EFI_HII_DATABASE_PROTOCOL_GUID \
  { \
    0xef9fc172, 0xa1b2, 0x4693, 0xb3, 0x27, 0x6d, 0x32, 0xfc, 0x41, 0x60, 0x42 \
  }

#define EFI_HII_STRING_PROTOCOL_GUID \
  { 0xfd96974, 0x23aa, 0x4cdc, { 0xb9, 0xcb, 0x98, 0xd1, 0x77, 0x50, 0x32, 0x2a } }

#define EFI_HII_IMAGE_PROTOCOL_GUID \
  { 0x31a6406a, 0x6bdf, 0x4e46, { 0xb2, 0xa2, 0xeb, 0xaa, 0x89, 0xc4, 0x9, 0x20 } }

#define EFI_HII_FONT_PROTOCOL_GUID \
  { 0xe9ca4775, 0x8657, 0x47fc, { 0x97, 0xe7, 0x7e, 0xd6, 0x5a, 0x8, 0x43, 0x24 } }

#define EFI_HII_IMAGE_EX_PROTOCOL_GUID \
  { 0x1a1241e6, 0x8f19, 0x41a9, { 0xbc, 0xe, 0xe8, 0xef,0x39, 0xe0, 0x65, 0x46 } }

#define EFI_HII_FONT_EX_PROTOCOL_GUID \
  { 0x849e6875, 0xdb35, 0x4df8, { 0xb4, 0x1e, 0xc8, 0xf3, 0x37, 0x18, 0x7, 0x3f } }


#include "HiiDef.h"
//
// The definition for HIIFont protocol
//
typedef struct _EFI_HII_FONT_PROTOCOL EFI_HII_FONT_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_HII_STRING_TO_IMAGE) (
  IN CONST EFI_HII_FONT_PROTOCOL    *This,
  IN EFI_HII_OUT_FLAGS              Flags,
  IN CONST EFI_STRING               String,
  IN CONST EFI_FONT_DISPLAY_INFO    *StringInfo,
  IN OUT EFI_IMAGE_OUTPUT           **Blt,
  IN UINTN                          BltX,
  IN UINTN                          BltY,
  OUT EFI_HII_ROW_INFO              **RowInfoArray OPTIONAL,
  OUT UINTN                         *RowInfoArraySize OPTIONAL,
  OUT UINTN                         *ColumnInfoArray OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_STRING_ID_TO_IMAGE) (
  IN CONST EFI_HII_FONT_PROTOCOL    *This,
  IN EFI_HII_OUT_FLAGS              Flags,
  IN EFI_HII_HANDLE                 PackageList,
  IN EFI_STRING_ID                  StringId,
  IN CONST CHAR8                    *Language,
  IN CONST EFI_FONT_DISPLAY_INFO    *StringInfo OPTIONAL,
  IN OUT EFI_IMAGE_OUTPUT           **Blt,
  IN UINTN                          BltX,
  IN UINTN                          BltY,
  OUT EFI_HII_ROW_INFO              **RowInfoArray OPTIONAL,
  OUT UINTN                         *RowInfoArraySize OPTIONAL,
  OUT UINTN                         *ColumnInfoArray OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_GLYPH) (
  IN CONST EFI_HII_FONT_PROTOCOL    *This,
  IN CHAR16                         Char,
  IN CONST EFI_FONT_DISPLAY_INFO    *StringInfo,
  OUT EFI_IMAGE_OUTPUT              **Blt,
  OUT UINTN                         *Baseline OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_FONT_INFO) (
  IN CONST EFI_HII_FONT_PROTOCOL    *This,
  IN OUT EFI_FONT_HANDLE            *FontHandle,
  IN CONST EFI_FONT_DISPLAY_INFO    *StringInfoIn,
  OUT EFI_FONT_DISPLAY_INFO         **StringInfoOut,
  IN CONST EFI_STRING               String OPTIONAL
);

struct _EFI_HII_FONT_PROTOCOL {
  EFI_HII_STRING_TO_IMAGE           StringToImage;
  EFI_HII_STRING_ID_TO_IMAGE        StringIdToImage;
  EFI_HII_GET_GLYPH                 GetGlyph;
  EFI_HII_GET_FONT_INFO             GetFontInfo;
};

//
// The definition for HIIFontEx protocol
//
typedef struct _EFI_HII_FONT_EX_PROTOCOL EFI_HII_FONT_EX_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_HII_STRING_TO_IMAGE_EX) (
  IN CONST EFI_HII_FONT_EX_PROTOCOL *This,
  IN EFI_HII_OUT_FLAGS              Flags,
  IN CONST EFI_STRING               String,
  IN CONST EFI_FONT_DISPLAY_INFO    *StringInfo,
  IN OUT EFI_IMAGE_OUTPUT           **Blt,
  IN UINTN                          BltX,
  IN UINTN                          BltY,
  OUT EFI_HII_ROW_INFO              **RowInfoArray OPTIONAL,
  OUT UINTN                         *RowInfoArraySize OPTIONAL,
  OUT UINTN                         *ColumnInfoArray OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_STRING_ID_TO_IMAGE_EX) (
  IN CONST EFI_HII_FONT_EX_PROTOCOL *This,
  IN EFI_HII_OUT_FLAGS              Flags,
  IN EFI_HII_HANDLE                 PackageList,
  IN EFI_STRING_ID                  StringId,
  IN CONST CHAR8                    *Language,
  IN CONST EFI_FONT_DISPLAY_INFO    *StringInfo OPTIONAL,
  IN OUT EFI_IMAGE_OUTPUT           **Blt,
  IN UINTN                          BltX,
  IN UINTN                          BltY,
  OUT EFI_HII_ROW_INFO              **RowInfoArray OPTIONAL,
  OUT UINTN                         *RowInfoArraySize OPTIONAL,
  OUT UINTN                         *ColumnInfoArray OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_GLYPH_EX) (
  IN CONST EFI_HII_FONT_EX_PROTOCOL *This,
  IN CHAR16                         Char,
  IN CONST EFI_FONT_DISPLAY_INFO    *StringInfo,
  OUT EFI_IMAGE_OUTPUT              **Blt,
  OUT UINTN                         *Baseline OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_FONT_INFO_EX) (
  IN CONST EFI_HII_FONT_EX_PROTOCOL *This,
  IN OUT EFI_FONT_HANDLE            *FontHandle,
  IN CONST EFI_FONT_DISPLAY_INFO    *StringInfoIn,
  OUT EFI_FONT_DISPLAY_INFO         **StringInfoOut,
  IN CONST EFI_STRING               String OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_GLYPH_INFO) (
  IN CONST EFI_HII_FONT_EX_PROTOCOL *This,
  IN CHAR16                         Char,
  IN CONST EFI_FONT_DISPLAY_INFO    *FontDisplayInfo,
  OUT EFI_HII_GLYPH_INFO            *GlyphInfo
);

struct _EFI_HII_FONT_EX_PROTOCOL {
  EFI_HII_STRING_TO_IMAGE_EX           StringToImageEx;
  EFI_HII_STRING_ID_TO_IMAGE_EX        StringIdToImageEx;
  EFI_HII_GET_GLYPH_EX                 GetGlyphEx;
  EFI_HII_GET_FONT_INFO_EX             GetFontInfoEx;
  EFI_HII_GET_GLYPH_INFO               GetGlyphInfo;
};


//
// The definition for HIIString protocol
//
typedef struct _EFI_HII_STRING_PROTOCOL EFI_HII_STRING_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_HII_NEW_STRING) (
  IN CONST EFI_HII_STRING_PROTOCOL         *This,
  IN EFI_HII_HANDLE                        PackageList,
  OUT EFI_STRING_ID                        *StringId,
  IN CONST CHAR8                           *Language,
  IN CONST CHAR16                          *LanguageName,
  IN CONST EFI_STRING                      String,
  IN CONST EFI_FONT_INFO                   *StringFontInfo
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_STRING) (
  IN CONST EFI_HII_STRING_PROTOCOL         *This,
  IN CONST CHAR8                           *Language,
  IN EFI_HII_HANDLE                        PackageList,
  IN EFI_STRING_ID                         StringId,
  OUT EFI_STRING                           String,
  IN OUT UINTN                             *StringSize,
  OUT EFI_FONT_INFO                        **StringFontInfo
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_SET_STRING) (
  IN CONST EFI_HII_STRING_PROTOCOL         *This,
  IN EFI_HII_HANDLE                        PackageList,
  IN EFI_STRING_ID                         StringId,
  IN CONST CHAR8                           *Language,
  IN CONST EFI_STRING                      String,
  IN CONST EFI_FONT_INFO                   *StringFontInfo
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_LANGUAGES) (
  IN CONST EFI_HII_STRING_PROTOCOL         *This,
  IN EFI_HII_HANDLE                        PackageList,
  IN OUT CHAR8                             *Languages,
  IN OUT UINTN                             *LanguagesSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_2ND_LANGUAGES) (
  IN CONST EFI_HII_STRING_PROTOCOL         *This,
  IN EFI_HII_HANDLE                        PackageList,
  IN CONST CHAR8                           *FirstLanguage,
  IN OUT CHAR8                             *SecondLanguages,
  IN OUT UINTN                             *SecondLanguagesSize
);

struct _EFI_HII_STRING_PROTOCOL {
  EFI_HII_NEW_STRING                    NewString;
  EFI_HII_GET_STRING                    GetString;
  EFI_HII_SET_STRING                    SetString;
  EFI_HII_GET_LANGUAGES                 GetLanguages;
  EFI_HII_GET_2ND_LANGUAGES             GetSecondaryLanguages;
};


//
// The definition for HIIImage protocol
//
typedef struct _EFI_HII_IMAGE_PROTOCOL EFI_HII_IMAGE_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_HII_NEW_IMAGE) (
  IN CONST EFI_HII_IMAGE_PROTOCOL    *This,
  IN EFI_HII_HANDLE                  PackageList,
  OUT EFI_IMAGE_ID                   *ImageId,
  IN CONST EFI_IMAGE_INPUT           *Image
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_IMAGE) (
  IN CONST EFI_HII_IMAGE_PROTOCOL    *This,
  IN EFI_HII_HANDLE                  PackageList,
  IN EFI_IMAGE_ID                    ImageId,
  OUT EFI_IMAGE_INPUT                *Image
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_SET_IMAGE) (
  IN CONST EFI_HII_IMAGE_PROTOCOL    *This,
  IN EFI_HII_HANDLE                  PackageList,
  IN EFI_IMAGE_ID                    ImageId,
  IN CONST EFI_IMAGE_INPUT           *Image
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DRAW_IMAGE) (
  IN CONST EFI_HII_IMAGE_PROTOCOL    *This,
  IN EFI_HII_DRAW_FLAGS              Flags,
  IN CONST EFI_IMAGE_INPUT           *Image,
  IN OUT EFI_IMAGE_OUTPUT            **Blt,
  IN UINTN                           BltX,
  IN UINTN                           BltY
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DRAW_IMAGE_ID) (
  IN CONST EFI_HII_IMAGE_PROTOCOL    *This,
  IN EFI_HII_DRAW_FLAGS              Flags,
  IN EFI_HII_HANDLE                  PackageList,
  IN EFI_IMAGE_ID                    ImageId,
  IN OUT EFI_IMAGE_OUTPUT            **Blt,
  IN UINTN                           BltX,
  IN UINTN                           BltY
);

struct _EFI_HII_IMAGE_PROTOCOL {
  EFI_HII_NEW_IMAGE                  NewImage;
  EFI_HII_GET_IMAGE                  GetImage;
  EFI_HII_SET_IMAGE                  SetImage;
  EFI_HII_DRAW_IMAGE                 DrawImage;
  EFI_HII_DRAW_IMAGE_ID              DrawImageId;
};

//
// The definition for HIIImageEx protocol
//
typedef struct _EFI_HII_IMAGE_EX_PROTOCOL EFI_HII_IMAGE_EX_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_HII_NEW_IMAGE_EX) (
  IN CONST EFI_HII_IMAGE_EX_PROTOCOL *This,
  IN EFI_HII_HANDLE                  PackageList,
  OUT EFI_IMAGE_ID                   *ImageId,
  IN CONST EFI_IMAGE_INPUT           *Image
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_IMAGE_EX) (
  IN CONST EFI_HII_IMAGE_EX_PROTOCOL *This,
  IN EFI_HII_HANDLE                  PackageList,
  IN EFI_IMAGE_ID                    ImageId,
  OUT EFI_IMAGE_INPUT                *Image
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_SET_IMAGE_EX) (
  IN CONST EFI_HII_IMAGE_EX_PROTOCOL *This,
  IN EFI_HII_HANDLE                  PackageList,
  IN EFI_IMAGE_ID                    ImageId,
  IN CONST EFI_IMAGE_INPUT           *Image
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DRAW_IMAGE_EX) (
  IN CONST EFI_HII_IMAGE_EX_PROTOCOL *This,
  IN EFI_HII_DRAW_FLAGS              Flags,
  IN CONST EFI_IMAGE_INPUT           *Image,
  IN OUT EFI_IMAGE_OUTPUT            **Blt,
  IN UINTN                           BltX,
  IN UINTN                           BltY
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DRAW_IMAGE_ID_EX) (
  IN CONST EFI_HII_IMAGE_EX_PROTOCOL *This,
  IN EFI_HII_DRAW_FLAGS              Flags,
  IN EFI_HII_HANDLE                  PackageList,
  IN EFI_IMAGE_ID                    ImageId,
  IN OUT EFI_IMAGE_OUTPUT            **Blt,
  IN UINTN                           BltX,
  IN UINTN                           BltY
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_IMAGE_INFO)(
  IN CONST  EFI_HII_IMAGE_EX_PROTOCOL       *This,
  IN        EFI_HII_HANDLE                  PackageList,
  IN        EFI_IMAGE_ID                    ImageId,
  OUT       EFI_IMAGE_OUTPUT                *Image
);


struct _EFI_HII_IMAGE_EX_PROTOCOL {
  EFI_HII_NEW_IMAGE_EX                  NewImageEx;
  EFI_HII_GET_IMAGE_EX                  GetImageEx;
  EFI_HII_SET_IMAGE_EX                  SetImageEx;
  EFI_HII_DRAW_IMAGE_EX                 DrawImageEx;
  EFI_HII_DRAW_IMAGE_ID_EX              DrawImageIdEx;
  EFI_HII_GET_IMAGE_INFO                GetImageInfo;
};


//
// The definition for HIIDatabase protocol
//
typedef struct _EFI_HII_DATABASE_PROTOCOL EFI_HII_DATABASE_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_NEW_PACK) (
  IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
  IN CONST EFI_HII_PACKAGE_LIST_HEADER    *PackageList,
  IN CONST EFI_HANDLE                     DriverHandle,
  OUT EFI_HII_HANDLE                      *Handle
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_REMOVE_PACK) (
  IN CONST EFI_HII_DATABASE_PROTOCOL    *This,
  IN EFI_HII_HANDLE                     Handle
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_UPDATE_PACK) (
  IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
  IN EFI_HII_HANDLE                       Handle,
  IN CONST EFI_HII_PACKAGE_LIST_HEADER    *PackageList
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_LIST_PACKS) (
  IN CONST EFI_HII_DATABASE_PROTOCOL    *This,
  IN UINT8                              PackageType,
  IN CONST EFI_GUID                     *PackageGuid,
  IN OUT UINTN                          *HandleBufferLength,
  OUT EFI_HII_HANDLE                    *Handle
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_EXPORT_PACKS) (
  IN CONST EFI_HII_DATABASE_PROTOCOL    *This,
  IN EFI_HII_HANDLE                     Handle,
  IN OUT UINTN                          *BufferSize,
  OUT EFI_HII_PACKAGE_LIST_HEADER       *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_REGISTER_NOTIFY) (
  IN CONST EFI_HII_DATABASE_PROTOCOL    *This,
  IN UINT8                              PackageType,
  IN CONST EFI_GUID                     *PackageGuid,
  IN CONST EFI_HII_DATABASE_NOTIFY      PackageNotifyFn,
  IN EFI_HII_DATABASE_NOTIFY_TYPE       NotifyType,
  OUT EFI_HANDLE                        *NotifyHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_UNREGISTER_NOTIFY) (
  IN CONST EFI_HII_DATABASE_PROTOCOL    *This,
  IN EFI_HANDLE                         NotificationHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_FIND_KEYBOARD_LAYOUTS) (
  IN EFI_HII_DATABASE_PROTOCOL    *This,
  IN OUT UINT16                   *KeyGuidBufferLength,
  OUT EFI_GUID                    *KeyGuidBuffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_SET_KEYBOARD_LAYOUT) (
  IN EFI_HII_DATABASE_PROTOCOL             *This,
  IN EFI_GUID                              *KeyGuid
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_KEYBOARD_LAYOUT) (
  IN EFI_HII_DATABASE_PROTOCOL    *This,
  IN EFI_GUID                     *KeyGuid,
  IN OUT UINT16                   *KeyboardLayoutLength,
  OUT EFI_HII_KEYBOARD_LAYOUT     *KeyboardLayout
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_GET_PACK_HANDLE) (
  IN EFI_HII_DATABASE_PROTOCOL    *This,
  IN EFI_HII_HANDLE               PackageListHandle,
  OUT EFI_HANDLE                  *DriverHandle
);

struct _EFI_HII_DATABASE_PROTOCOL {
  EFI_HII_DATABASE_NEW_PACK            NewPackageList;
  EFI_HII_DATABASE_REMOVE_PACK         RemovePackageList;
  EFI_HII_DATABASE_UPDATE_PACK         UpdatePackageList;
  EFI_HII_DATABASE_LIST_PACKS          ListPackageLists;
  EFI_HII_DATABASE_EXPORT_PACKS        ExportPackageLists;
  EFI_HII_DATABASE_REGISTER_NOTIFY     RegisterPackageNotify;
  EFI_HII_DATABASE_UNREGISTER_NOTIFY   UnregisterPackageNotify;
  EFI_HII_FIND_KEYBOARD_LAYOUTS        FindKeyboardLayouts;
  EFI_HII_GET_KEYBOARD_LAYOUT          GetKeyboardLayout;
  EFI_HII_SET_KEYBOARD_LAYOUT          SetKeyboardLayout;
  EFI_HII_DATABASE_GET_PACK_HANDLE     GetPackageListHandle;
};

extern EFI_GUID gBlackBoxEfiHIIDatabaseProtocolGuid;
extern EFI_GUID gBlackBoxEfiHIIStringProtocolGuid;
extern EFI_GUID gBlackBoxEfiHIIPackageListProtocolGuid;
extern EFI_GUID gBlackBoxEfiHIIImageExProtocolGuid;
extern EFI_GUID gBlackBoxEfiHIIFontExProtocolGuid;

#endif
