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

  HIIImageBBTestMain.h

Abstract:

  Test Driver of HII Image Protocol header file

--*/

#ifndef _HII_IMAGE_BB_TEST_MAIN
#define _HII_IMAGE_BB_TEST_MAIN

#define __UEFI_INTERNAL_FORMREPRESENTATION_H__
#include <Base.h>
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/Hii.h>
#include "Guid.h"
#include <UEFI/Protocol/GraphicsOutput.h>



#define EFI_HII_IMAGE_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x4ba02e97, 0xcdc4, 0x466d, { 0x9f, 0x13, 0xa3, 0xf, 0xad, 0x30, 0x1a, 0xf0 } }

#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0xbf2de3b1, 0x4e2f, 0x4820, { 0xb9, 0x2b, 0x2, 0x2, 0x86, 0xcd, 0x4a, 0x53 } }

#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0xfb6f0077, 0x9601, 0x4fe1, { 0x95, 0xef, 0xcf, 0xbc, 0x75, 0x44, 0x4d, 0x88 } }

#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0x1633e130, 0x78a3, 0x4615, { 0x8a, 0x7e, 0x41, 0xd0, 0xdb, 0x60, 0x89, 0xfb } }

#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0xf6340606, 0xec05, 0x4238, { 0xaa, 0xe4, 0x96, 0x67, 0x8d, 0xa1, 0x8a, 0x90 } }

//
// Entry GUIDs for Conf Test
//
#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x9dc66432, 0xa4af, 0x408b, { 0xad, 0x2e, 0xe5, 0x7, 0xcf, 0xea, 0x29, 0x4e } }

#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x5f2ea1b0, 0xd8a8, 0x4045, { 0x96, 0xf3, 0x1, 0x48, 0x0, 0x6, 0x3b, 0x91 } }

#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x9e79efa2, 0x8159, 0x4c89, { 0x85, 0x68, 0xe2, 0x4a, 0xd5, 0xe5, 0x75, 0x66 } }

#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0xff1e44fb, 0xd242, 0x41e9, { 0xa7, 0xa, 0x40, 0xfd, 0x5e, 0x3f, 0x71, 0x4d } }

#define EFI_HII_IMAGE_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0x6bd79a9c, 0x98ee, 0x45e5, { 0x90, 0xed, 0x1d, 0xa2, 0xec, 0x7, 0x86, 0x6f } }

//
//
//
EFI_STATUS
InitializeHIIImageBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
  
EFI_STATUS
UnloadHIIImageBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
BBTestNewImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestSetImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestDrawImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestDrawImageIdConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestNewImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestSetImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestDrawImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestDrawImageIdFunctionTest (
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
