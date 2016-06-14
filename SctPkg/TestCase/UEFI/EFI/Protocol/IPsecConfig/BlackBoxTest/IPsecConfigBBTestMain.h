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

  IPsecConfigBBTestMain.h

Abstract:

  Test Driver of IPsec Config Protocol header file

--*/

#ifndef _IPSEC_CONFIG_BB_TEST_MAIN
#define _IPSEC_CONFIG_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/IPsecConfig.h>
#include "Guid.h"


#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_REVISION    0x00010000


//
// Entry GUIDs for Func Test
//
#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xd69baaa6, 0xa7a6, 0x4e15, { 0x9d, 0x3e, 0xa5, 0x77, 0xb8, 0x3b, 0xc2, 0x48 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x1944aae7, 0x4325, 0x45cf, { 0x82, 0x54, 0x5b, 0xb6, 0xd5, 0xa7, 0xa2, 0x6f } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x6e1a3e05, 0xd689, 0x465b, { 0xbb, 0x20, 0xb6, 0x67, 0x99, 0x25, 0x3f, 0x7a } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0xfe966b77, 0x5eb2, 0x4f97, { 0xa0, 0x64, 0xec, 0xf9, 0xc6, 0xd8, 0x6e, 0x3d } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0x44187ec6, 0x3b4a, 0x4909, { 0x81, 0x7b, 0xe7, 0xe8, 0xbc, 0x86, 0xe2, 0xde } }

//
// Entry GUIDs for Conf Test
//
#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xd44836ca, 0x4bc9, 0x4a37, { 0x97, 0x49, 0x70, 0xe8, 0x07, 0x8d, 0x84, 0xf7 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xacbf8376, 0xbea7, 0x4ad4, { 0x88, 0xb1, 0xb5, 0x44, 0xee, 0x29, 0xfb, 0xa7 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0xf8c735ac, 0xa588, 0x44a3, { 0xab, 0x7d, 0x36, 0x2c, 0xc0, 0xe7, 0xfa, 0x50 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0xb3342367, 0x9cf2, 0x4f32, { 0xbe, 0x58, 0x59, 0x8b, 0x4f, 0xc3, 0xcd, 0x80 } }

#define EFI_IPSEC_CONFIG_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0x27b9dc40, 0x84ef, 0x43ad, { 0xbc, 0xcd, 0x3e, 0xa4, 0x61, 0x2c, 0xe3, 0x86 } }

//
//
//
EFI_STATUS
InitializeIPsecConfigBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
UnloadIPsecConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
BBTestSetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetNextSelectorConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestRegisterDataNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestUnregisterDataNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestSetDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetDataFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetNextSelectorFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestRegisterDataNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestUnregisterDataNotifyFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

VOID
EventNotifyFunc (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );


#endif
