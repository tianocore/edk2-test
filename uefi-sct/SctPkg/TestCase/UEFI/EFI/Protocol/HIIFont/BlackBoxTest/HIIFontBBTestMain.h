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

  HIIFontBBTestMain.h

Abstract:

  Test Driver of HII Font Protocol header file

--*/

#ifndef _HII_FONT_BB_TEST_MAIN
#define _HII_FONT_BB_TEST_MAIN

#define __UEFI_INTERNAL_FORMREPRESENTATION_H__
#include <Base.h>
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/Hii.h>
#include "Guid.h"
#include <UEFI/Protocol/GraphicsOutput.h>


#define EFI_HII_FONT_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xc088cca1, 0xaf8b, 0x4a28, {0xa6, 0x52, 0xc9, 0x90, 0x5a, 0x83, 0x33, 0xb6 }}

#define EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x32e8b10d, 0x6755, 0x4111, {0xa6, 0xe5, 0xa4, 0x62, 0x40, 0x4a, 0x43, 0x12 }}

#define EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x8e288541, 0xcec7, 0x4362, {0xa8, 0xb4, 0xbd, 0xe3, 0xec, 0x34, 0xf7, 0x1a }}

#define EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0x95dfdde2, 0xd37f, 0x4cc4, {0x83, 0xb5, 0x63, 0x66, 0x87, 0x1e, 0x90, 0x26 }}

//
// Entry GUIDs for Conf Test
//
#define EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xdb08dd76, 0xd09f, 0x4a10, {0xa3, 0x1a, 0xa3, 0x48, 0x28, 0xfd, 0x4e, 0xa8 }}

#define EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x6815f00d, 0xfee1, 0x4f80, {0xa5, 0xe3, 0xf9, 0x7a, 0x4e, 0x6d, 0x69, 0xb6 }}

#define EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0xa1c299aa, 0x2d79, 0x47a6, {0xaa, 0x90, 0xf6, 0x56, 0x27, 0x4d, 0x70, 0xae }}

#define EFI_HII_FONT_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0xec3b496b, 0xe103, 0x4831, {0x85, 0xde, 0x8e, 0x3b, 0xed, 0xb4, 0x42, 0xfb }}

#define FONT_TEST_GLYPH(Index)      EFI_HII_GIBT_GLYPH_DEFAULT, (Index), 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x99, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22 

#define EMPTY_TEST_GLYPH            EFI_HII_GIBT_GLYPH_DEFAULT, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 

//
//
//
EFI_STATUS
EFIAPI
InitializeHIIFontBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
  
EFI_STATUS
EFIAPI
UnloadHIIFontBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestStringToImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestStringIdToImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetGlyphConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetFontInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestStringToImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestStringIdToImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetGlyphFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetFontInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
GetGraphicsOutputInterface (
  OUT EFI_GRAPHICS_OUTPUT_PROTOCOL    **GraphicsOutput
  );

EFI_STATUS
GetHIIDatabaseInterface (
  OUT EFI_HII_DATABASE_PROTOCOL    **HIIDatabase
  );

EFI_STATUS
GetHIIStringInterface (
  OUT EFI_HII_STRING_PROTOCOL    **HIIString
  );

#endif
