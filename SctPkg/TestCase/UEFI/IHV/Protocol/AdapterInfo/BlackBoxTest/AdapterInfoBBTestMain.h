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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  AdapterInfoBBTestMain.h

Abstract:

  Test Driver of Adapter Information Protocol header file

--*/

#ifndef _ADAPTER_INFORMATION_BB_TEST_MAIN
#define _ADAPTER_INFORMATION_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/AdapterInfo.h>
#include "guid.h"


#define IHV_ADAPTER_INFORMATION_PROTOCOL_TEST_REVISION    0x00010000

#define IHV_ADAPTER_INFORMATION_PROTOCOL_GUID \
{0x369eaa20, 0xefe7, 0x4b56, 0x8b, 0xb6, 0xd8, 0xc2, 0x96, 0x4b, 0x2b, 0xde} 



//
// Entry GUIDs for Func Test
//
#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xfeb5d3b9, 0x23ef, 0x4cfb, { 0xb9, 0x1a, 0x43, 0xd2, 0xf, 0x4b, 0x8b, 0x3 } }

#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x69891f7e, 0xdb2c, 0x4d00, { 0x92, 0xd3, 0x58, 0x84, 0x22, 0x86, 0xb, 0x2d } }

#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0xd8fe3070, 0xc23e, 0x46c9, { 0xb7, 0x1b, 0x6c, 0x8c, 0xb6, 0xb4, 0x26, 0xd } }


//
// Entry GUIDs for Conf Test
//
#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x72555bc1, 0x8da6, 0x4814, { 0xb1, 0xd9, 0x98, 0xb4, 0xab, 0xda, 0x90, 0xde } }

#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0xad52c0e, 0x9b39, 0x41dc, { 0xae, 0xf8, 0x12, 0x30, 0x48, 0x33, 0x67, 0x13 } }

#define EFI_ADAPTER_INFORMATION_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0xd1f31918, 0xf989, 0x4874, { 0xaa, 0xa4, 0x4b, 0x48, 0x63, 0x2a, 0x29, 0x2a } }
                           
                                
//
//GuidCmp
//

INTN 
GuidCmp(
  EFI_GUID                      GuidGiven,
  EFI_GUID                      GuidNeedToCmp
  );
//
//InfoTypeAndBlockSizeCmp
//
BOOLEAN
InfoTypeAndBlockSizeCmp( 
  EFI_GUID                      InformationType,
  UINTN                         InformationBlockSize
  );





//
//
//
EFI_STATUS
InitializeAdapterInfoBBTest (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );
  
EFI_STATUS
UnloadAdapterInfoBBTest (
  IN EFI_HANDLE                 ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
BBTestGetInformationConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestSetInformationConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetSupportedTypesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

  
EFI_STATUS
BBTestGetInformationFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetInformationFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestGetSupportedTypesFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


VOID
SctInitializeLib (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );


#endif
