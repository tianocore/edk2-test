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
    RandomNumberBBTest.h

Abstract:
    head file of test driver of EFI RANDOM NUMBER Protocol Test

--*/

#ifndef _RANDOM_NUMBER_TEST_H
#define _RANDOM_NUMBER_TEST_H


#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/RandomNumber.h>
#include "Guid.h"

#define EFI_RANDOM_NUMBER_TEST_REVISION 0x00010000

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Function Test
//
#define EFI_RANDOM_NUMBER_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0x39ff9c71, 0x4b41, 0x4e5b, {0xae, 0xd7, 0x87, 0xc7, 0x94, 0x18, 0x7d, 0x66} }

#define EFI_RANDOM_NUMBER_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0xdc5b2884, 0xedfb, 0x4078, {0xa2, 0x88, 0x4d, 0xfd, 0xa8, 0x49, 0xa0, 0x8d} }


//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define EFI_RANDOM_NUMBER_PROTOCOL_TEST_ENTRY_GUID0201 \
 {0x861f4a3b, 0x8125, 0x4a5a, {0x99, 0xcc, 0xda, 0x77, 0x79, 0xc2, 0xb0, 0x20} }

#define EFI_RANDOM_NUMBER_PROTOCOL_TEST_ENTRY_GUID0202 \
 {0xddbbe5ab, 0x206e, 0x4f35, {0x95, 0x56, 0x18, 0x6d, 0xa8, 0x7c, 0x2a, 0x86} }



//
// functions declaration
//
EFI_STATUS
InitializeBBTestRandomNumber (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestRandomNumberUnload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
BBTestGetInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestGetRNGFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestGetInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


EFI_STATUS
BBTestGetRNGFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


EFI_STATUS
BBTestGetRNGFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN  EFI_RNG_PROTOCOL                     *RandomNumber
  );


EFI_STATUS
BBTestGetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestGetRNGConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestGetInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


EFI_STATUS
BBTestGetRNGConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


EFI_STATUS
BBTestGetRNGConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RNG_PROTOCOL                      *RandomNumber
  );


#endif
