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
                                                                
  Copyright 2017 Unified EFI, Inc. All Rights Reserved, subject 
  to all existing rights in all matters included within this 
  Test Suite, to which United EFI, Inc. makes no claim of right.
  
  (C) Copyright 2017 Hewlett Packard Enterprise Development LP<BR>
--*/
/*++

Module Name:

  HIIFontExBBTestMain.h

Abstract:

  Test Driver of HII FontEx Protocol header file

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


#define EFI_HII_FONT_EX_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x3e5ae5bd, 0x3222, 0x4274, {0x91, 0x3b, 0x9a, 0x2e, 0x6c, 0x5d, 0xf6, 0x51 }}

#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x71722f2a, 0x4ee0, 0x4685, {0xa9, 0x4c, 0xc8, 0xf7, 0xb4, 0x50, 0x86, 0x6e }}


#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x96093f78, 0xa87f, 0x4cef, {0xae, 0x18, 0x4c, 0x18, 0x3a, 0xbe, 0xc4, 0x1f }}


#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0xf22da2d8, 0x5616, 0x4301, {0xab, 0x1d, 0x67, 0x5f, 0x87, 0xb8, 0x1d, 0x92 }}

#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0x881020c7, 0x4006, 0x4780, {0xb9, 0x77, 0xb6, 0x5e, 0x4a, 0xa7, 0x66, 0x36 }}

//
// Entry GUIDs for Conf Test
//
#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xef1cc390, 0x2ccf, 0x480a, {0x8a, 0x5c, 0x2f, 0xc6, 0xad, 0x29, 0x3e, 0xb3 }}


#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xb7d801c5, 0xb629, 0x4c7d, {0xa5, 0xdc, 0x0, 0xe5, 0x2c, 0x58, 0x23, 0x2d }}

#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x2a310d2d, 0x142d, 0x4334, {0xb8, 0x67, 0x77, 0x6a, 0xfd, 0xd0, 0xdf, 0xb1 }}

#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0x4b9a0e29, 0x1aab, 0x4ae6, {0xae, 0xcd, 0x68, 0x79, 0x80, 0x82, 0x9b, 0x7c }}

#define EFI_HII_FONT_EX_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0xc2bd052e, 0x4eb7, 0x4daf, {0xb9, 0xfc, 0x77, 0x6c, 0xf7, 0x6c, 0xfc, 0x58 }}


#define FONT_TEST_GLYPH(Index)      EFI_HII_GIBT_GLYPH_DEFAULT, (Index), 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x99, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22 

#define EMPTY_TEST_GLYPH            EFI_HII_GIBT_GLYPH_DEFAULT, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 

//
//
//
EFI_STATUS
InitializeHIIFontExBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
  
EFI_STATUS
UnloadHIIFontExBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
BBTestStringToImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestStringIdToImageExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetGlyphExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetFontInfoExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetGlyphInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestStringToImageExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestStringIdToImageExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetGlyphExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetFontInfoExFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetGlyphInfoFunctionTest (
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
