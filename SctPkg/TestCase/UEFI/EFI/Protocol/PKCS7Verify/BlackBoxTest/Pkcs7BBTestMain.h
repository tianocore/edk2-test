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
                                                                
  Copyright 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Pkcs7BBTestMain.h

Abstract:

  Test Driver of Pkcs7 Verify Protocol header file

--*/

#ifndef _PKCS7_BB_TEST_MAIN
#define _PKCS7_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/Pkcs7Verify.h>
#include "Guid.h"


#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x5c6a8139, 0xad48, 0x4d52, {0x86, 0x37, 0x6, 0x9d, 0xf6, 0xad, 0x81, 0x5e }}

#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x413c4823, 0x263a, 0x417d, {0xa3, 0xd7, 0x14, 0x79, 0xf9, 0x2b, 0xf1, 0xb4 }}


//
// Entry GUIDs for Conf Test
//
#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x562af518, 0xd04e, 0x435e, {0xa8, 0x9f, 0x79, 0xbb, 0x6f, 0x48, 0x16, 0x9a }}

#define EFI_PKCS7_VERIFY_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xaf5e33d1, 0x3e08, 0x451a, {0xb1, 0x92, 0xe7, 0xb9, 0x91, 0x67, 0x83, 0xae }}




extern UINT8 TestBin[64];
extern UINT8 TestBinHash[32];
extern UINT8 TestSubCert[755];
extern UINT8 TestRootCert[756];
extern UINT8 P7Embedded[3330];
extern UINT8 P7Detached[1138];
extern UINT8 TSRootCert[1177];
extern UINT8 TBSCert[479];
extern UINT8 TestSubHash[32];

//
//
//
EFI_STATUS
InitializePkcs7VerifyBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
UnloadPkcs7VerifyBBTest (
  IN EFI_HANDLE                   ImageHandle
  ); 
  
//
//Test Cases
//
EFI_STATUS
BBTestVerifyBufferConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestHashConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  

  
EFI_STATUS
BBTestVerifyBufferFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestVerifySignatureFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
#endif

