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

  HIIImageExBBTestMain.h

Abstract:

  Test Driver of HII ImageEx Protocol header file

--*/

#ifndef _HII_IMAGE_EX_BB_TEST_MAIN
#define _HII_IMAGE_EX_BB_TEST_MAIN

#define __UEFI_INTERNAL_FORMREPRESENTATION_H__
#include <Base.h>
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/Hii.h>
#include "Guid.h"
#include <UEFI/Protocol/GraphicsOutput.h>



#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xe5f6885a, 0x5673, 0x4a27, { 0x88, 0x6, 0x97, 0x5, 0x94, 0x8a, 0x9c, 0xa0 } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x9e0c6d74, 0x269e, 0x4204, { 0x9b, 0xc0, 0x5d, 0xfd, 0xdb, 0x23, 0x5, 0x7d } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0xef75ba0, 0xc815, 0x4299, { 0xb9, 0xdb, 0x27, 0xa2, 0xe8, 0xc7, 0xf3, 0xee } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0x3f5bf0a2, 0x8ef1, 0x43be, { 0x83, 0x39, 0xf9, 0xd5, 0x9d, 0x5c, 0x7f, 0x3c } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0x8470dbe4, 0xea97, 0x4768, { 0x84, 0x85, 0xe7, 0xeb, 0x8, 0x74, 0x6b, 0x32 } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0106 \
{ 0x8a8c4085, 0xabdc, 0x4bd8, { 0xa8, 0x47, 0xad, 0x8c, 0xcd, 0x89, 0x47, 0xe7 } }

//
// Entry GUIDs for Conf Test
//
#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x2e160adc, 0xd828, 0x4ed2, { 0xbd, 0xe2, 0xfd, 0xf7, 0xe5, 0x6b, 0xc4, 0xf7 } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x84ee13d3, 0xb67e, 0x4299, { 0xb2, 0x61, 0xc, 0x8b, 0x10, 0x2e, 0x8, 0xaf } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x554fe68d, 0xbce3, 0x4801, { 0x89, 0x53, 0x1, 0xa8, 0xb5, 0xb0, 0x27, 0xcf } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0x98bb5fb5, 0x32a0, 0x4bc2, { 0xb9, 0xa2, 0xb8, 0x89, 0x9a, 0xc2, 0xa2, 0x40 } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0x82dd330c, 0x34f7, 0x4e4f, { 0x89, 0x42, 0xe6, 0xe6, 0x2c, 0x2d, 0x51, 0xa1 } }

#define EFI_HII_IMAGE_EX_PROTOCOL_TEST_ENTRY_GUID0206 \
{ 0xf172e387, 0x35f4, 0x4439, { 0x93, 0xc3, 0x85, 0xf9, 0x53, 0x35, 0x17, 0xa } }

//
//
//
EFI_STATUS
EFIAPI
InitializeHIIImageExBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
  
EFI_STATUS
EFIAPI
UnloadHIIImageExBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestNewImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestSetImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestDrawImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestDrawImageIdExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetImageInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestNewImageExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestGetImageExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestSetImageExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestDrawImageExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestDrawImageIdExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestGetImageInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
//
//
//
EFI_STATUS
GetGraphicsOutputInterface (
  OUT EFI_GRAPHICS_OUTPUT_PROTOCOL    **GraphicsOutput
  );


EFI_STATUS
GetHIIDatabaseInterface (
  OUT EFI_HII_DATABASE_PROTOCOL    **HIIDatabase
  );

#endif
