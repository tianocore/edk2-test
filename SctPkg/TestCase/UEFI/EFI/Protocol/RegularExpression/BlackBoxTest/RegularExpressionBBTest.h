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
    RegularExpressionBBTest.h

Abstract:
    head file of test driver of EFI REGULAR EXPRESSION Protocol Test

--*/

#ifndef _REGULAR_EXPRESSION_TEST_H
#define _REGULAR_EXPRESSION_TEST_H


#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/RegularExpression.h>
#include "Guid.h"

#define EFI_REGULAR_EXPRESSION_TEST_REVISION 0x00010000

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Function Test
//
#define EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0x9531a0ea, 0x7955, 0x4cc1, {0xb1, 0x12, 0xb8, 0x95, 0xd9, 0xd3, 0xb, 0x86} }

#define EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0x7ef858ab, 0x54a8, 0x481d, {0x95, 0x9d, 0xc4, 0x5, 0xb5, 0xd7, 0x20, 0x87} }

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0201 \
 {0xdf61e05b, 0x25b4, 0x4e05, {0xa5, 0x16, 0x8d, 0xa3, 0x6a, 0xae, 0xce, 0xa9} }

#define EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0202 \
 {0x6f7ecf1, 0x6b72, 0x4816, {0x8f, 0x67, 0xf7, 0x42, 0x1e, 0x73, 0x3e, 0xb0} }

 
typedef struct {
  CHAR16             *Pattern;
  CHAR16             *String;
  BOOLEAN            Result;
  UINTN              CapturesCount;
} MATCHSTRING_TEST_DATA_FIELD;

//
// functions declaration
//
EFI_STATUS
InitializeBBTestRegularExpression (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestRegularExpressionUnload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
BBTestRegExGetInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestMatchStringFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestRegExGetInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
BBTestMatchStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
BBTestMatchStringFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
BBTestGetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestMatchStringConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestGetInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
BBTestMatchStringConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
BBTestMatchStringConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


#endif
