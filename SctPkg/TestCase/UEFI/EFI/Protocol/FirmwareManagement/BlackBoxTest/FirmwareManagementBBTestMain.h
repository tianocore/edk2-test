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
                                                                
  Copyright (c) 2010, Dell Inc.  All rights reserved.   
   
--*/

/*++

Module Name:

  FirmwareManagementBBTestMain.h

Abstract:

  Header file for Firmware Management Protocol test driver.

--*/

#ifndef _FIRMWARE_MANAGEMENT_BB_TEST_MAIN
#define _FIRMWARE_MANAGEMENT_BB_TEST_MAIN

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

#include <UEFI/Protocol/FirmwareManagement.h>

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_REVISION    0x00010000

// ****************************************************************************
//   Entry GUIDs for Function Test
// ****************************************************************************

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x7ddddd57, 0x68ff, 0x460e, { 0x90, 0xad, 0xa9, 0xd5, 0xf1, 0xf0, 0xa0, 0x87 } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x5b4c24b2, 0x852d, 0x418a, { 0x82, 0x34, 0xc2, 0xc8, 0x63, 0x5e, 0x9a, 0x2a } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0x84062e44, 0xdaee, 0x41a5, { 0x94, 0xf8, 0x6d, 0xe0, 0x72, 0x9b, 0xfa, 0xb4 } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0104 \
{ 0xdeb26021, 0xca4e, 0x4876, { 0x90, 0x99, 0xca, 0x7d, 0x77, 0x2c, 0x90, 0x1d } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0105 \
{ 0xaa160ecc, 0xfc2f, 0x4f05, { 0xac, 0x20, 0x4c, 0xed, 0x45, 0xde, 0xda, 0xab } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0106 \
{ 0x7a9a2714, 0xf32b, 0x4083, { 0x90, 0xf2, 0x12, 0x51, 0x1a, 0x87, 0x48, 0x1a } }

// ****************************************************************************
//   Entry GUIDs for Conformance Test
// ****************************************************************************

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x54ee347c, 0x10a3, 0x4311, { 0x94, 0x27, 0xa8, 0x97, 0xbf, 0xdc, 0x98, 0x8 } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x68aba93c, 0x1d0c, 0x412f, { 0xb1, 0xe, 0xe3, 0xa4, 0x6, 0xbc, 0x42, 0xcf } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x12834a23, 0x6cef, 0x478e, { 0xaf, 0x48, 0x44, 0xe5, 0x93, 0x40, 0xab, 0xe8 } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0204 \
{ 0xc6dc94b1, 0xb81b, 0x4b85, { 0x8b, 0x7d, 0x8f, 0xbf, 0xa6, 0x8e, 0xf3, 0xe5 } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0205 \
{ 0x3d13f23d, 0x8306, 0x49d4, { 0xa0, 0xe0, 0x9a, 0x9b, 0xf6, 0x89, 0x40, 0x3c } }

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_TEST_ENTRY_GUID0206 \
{ 0x24cf9ac2, 0x9abc, 0x4f5c, { 0x9c, 0x7a, 0xbc, 0x22, 0x29, 0xc3, 0x2, 0x7f } }

// ****************************************************************************
//   Initializaiton and Unload functions
// ****************************************************************************

EFI_STATUS
InitializeFirmwareManagementBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
UnloadFirmwareManagementBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
//
// Test Cases - Unit Test
//

/*
EFI_STATUS
BBTestUnitTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
*/

//
// Test Cases - Function
//

EFI_STATUS
BBTestGetImageInfoFunctionTest (
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
BBTestCheckImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetPackageInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetPackageInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Test Cases - Conformance
//

EFI_STATUS
BBTestGetImageInfoConformanceTest (
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
BBTestCheckImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetPackageInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSetPackageInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

// ****************************************************************************
//   Support functions
// ****************************************************************************

#endif
