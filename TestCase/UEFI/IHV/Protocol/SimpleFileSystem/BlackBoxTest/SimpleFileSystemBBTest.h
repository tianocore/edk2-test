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
    SimpleFileSystemTest.h

Abstract:
    head file of test driver of EFI Simple File System Protocol
    and EFI_FILE Protocol Test

--*/

#ifndef _SIMPLE_FILE_SYSTEM_TEST_H
#define _SIMPLE_FILE_SYSTEM_TEST_H


#include "Efi.h"
#include "EfiCommonLib.h"
#include "EfiTestUtilityLib.h"
#include "EfiTestLib.h"
#include "guid.h"

//----------------------------------//
//
//  This macro is used for a sub-set test (to save time)
//
#define FILE_SYSTEM_SIMPLE_TEST 1
//
//---------------------------------//



#define SIMPLE_FILE_SYSTEM_TEST_REVISION      0x00010000

#define IHV_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID  \
  { 0x2cce80e2, 0x4f3b, 0x42c1, 0xa0, 0x00, 0xfc, 0x17, 0xf7, 0x0b, 0x3d, 0x4e }


#define MAX_STRING_LENGTH         266

#define OPEN_R_W_MODE       (EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE)
#define CREATE_FILE_MODE    (OPEN_R_W_MODE | EFI_FILE_MODE_CREATE)

#define TPL_ARRAY_SIZE 2

extern EFI_TPL TplArray [TPL_ARRAY_SIZE];

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Basic Test
//
#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0101 \
  { 0x0e6090f8, 0x5a70, 0x4ac1, { 0x80, 0x2b, 0x07, 0xc5, 0x76, 0x8b, 0xec, 0xc0 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0102 \
  { 0x7f6aecd1, 0x6088, 0x47be, { 0x80, 0xfe, 0xb7, 0xca, 0x52, 0x4c, 0xff, 0xe4 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0103 \
  { 0x8142067a, 0xe990, 0x45e4, { 0x93, 0x44, 0xf8, 0xa4, 0xfc, 0xba, 0x46, 0xdf } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0104 \
  { 0x20c04fa2, 0xaf9e, 0x47b0, { 0x87, 0x24, 0x9f, 0xce, 0x34, 0x17, 0xe9, 0x8a } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0105 \
  { 0xbc8cc21b, 0xb425, 0x43c0, { 0x88, 0x3a, 0x2f, 0xdc, 0x41, 0xc5, 0xb5, 0xbd } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0106 \
  { 0x1a2a79bc, 0x57d0, 0x4c80, { 0xb0, 0x6e, 0xd6, 0x9a, 0x15, 0x5f, 0xe5, 0x40 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0107 \
  { 0x3266ee24, 0xaa54, 0x4923, { 0xab, 0x30, 0xb6, 0x07, 0x69, 0xa5, 0x0d, 0xc8 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0108 \
  { 0x663e72f2, 0x4019, 0x486f, { 0x83, 0x7a, 0x03, 0x4d, 0xa3, 0x81, 0xdf, 0x20 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0109 \
  { 0x448a8625, 0x86e9, 0x470f, { 0xb3, 0x6e, 0xe9, 0x86, 0x9d, 0x76, 0x9f, 0xa8 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0110 \
  { 0x966b04ad, 0x5237, 0x416d, { 0xa1, 0xca, 0x54, 0x7b, 0xe5, 0x3c, 0x65, 0x22 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0111 \
  { 0xd1aec266, 0x1106, 0x4d3f, { 0x98, 0xb5, 0x38, 0x28, 0x07, 0x9d, 0xea, 0xee } }

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0201 \
  { 0x76b69481, 0xcfb0, 0x4683, { 0x85, 0x00, 0xdf, 0xa6, 0x70, 0x7c, 0xea, 0x52 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0202 \
  { 0xe57d2db1, 0x03b8, 0x4854, { 0x97, 0x24, 0xd1, 0x63, 0x28, 0xd1, 0x07, 0x5b } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0203 \
  { 0xce8e18f1, 0x11f7, 0x41c4, { 0xb9, 0x00, 0x6a, 0x9b, 0x0b, 0xa2, 0xa8, 0xe1 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0204 \
  { 0xcf12e749, 0xd77e, 0x4142, { 0xba, 0xbd, 0x18, 0xd0, 0x4f, 0x66, 0x72, 0x24 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0205 \
  { 0xc82d4a03, 0xa1d0, 0x4832, { 0x80, 0xd9, 0xc1, 0x2a, 0x2c, 0x55, 0x51, 0xfa } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0206 \
  { 0x48e6ff1b, 0x86a6, 0x4289, { 0xb5, 0x4f, 0x47, 0xe1, 0x88, 0x2e, 0xbf, 0xd7 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0207 \
  { 0x3ddff030, 0x36fc, 0x4ef0, { 0x80, 0x0d, 0x29, 0x6c, 0x34, 0x6f, 0xd4, 0x83 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0208 \
  { 0x1849e6cb, 0xd380, 0x48fe, { 0xa0, 0x8f, 0x51, 0x99, 0x45, 0x2e, 0x5a, 0x70 } }

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Automatic Extensive Test
//
#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0301 \
  { 0x3f0d5a08, 0x30a6, 0x481d, { 0xb5, 0x01, 0xfd, 0x7e, 0xba, 0x46, 0x39, 0x8d } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0302 \
  { 0x058c8717, 0x67cb, 0x4a90, { 0xbf, 0xf4, 0x3d, 0xe6, 0xae, 0xdd, 0x42, 0x4e } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0303 \
  { 0xa5214668, 0x7caf, 0x47b9, { 0xa2, 0x91, 0x92, 0xc5, 0x47, 0xd9, 0x45, 0xd1 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0304 \
  { 0xbd92b88d, 0x4fd4, 0x4969, { 0xa6, 0x94, 0xd7, 0xcc, 0xa2, 0xa6, 0x27, 0x85 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0305 \
  { 0x55fccf5b, 0xadac, 0x491c, { 0xb7, 0xcb, 0x57, 0xa2, 0xc9, 0xa2, 0x83, 0xa6 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0306 \
  { 0x178113ba, 0xcb67, 0x407a, { 0x93, 0x57, 0xb1, 0x00, 0xd8, 0xed, 0x2b, 0x5f } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0307 \
  { 0x77cfac95, 0xd099, 0x4d00, { 0x83, 0x84, 0x51, 0x9e, 0x4e, 0x88, 0xde, 0xad } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0308 \
  { 0x79cbf7b4, 0x9f89, 0x4e67, { 0x8d, 0xc5, 0xbe, 0x65, 0xfa, 0x97, 0x61, 0x7e } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0309 \
  { 0x596f8446, 0x915b, 0x4938, { 0xa9, 0x3a, 0x84, 0x91, 0xf9, 0x53, 0x9c, 0x3b } }

//////////////////////////////////////////////////////////////////////////////

//
// functions declaration
//

EFI_STATUS
InitializeBBTestSimpleFileSystem (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestSimpleFileSystemUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Basic test functions
//

//
// TDS 5.1.1
//
EFI_STATUS
BBTestOpenVolumeBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.2
//
EFI_STATUS
BBTestOpenBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.3
//
EFI_STATUS
BBTestCloseBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.4
//
EFI_STATUS
BBTestDeleteBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.5
//
EFI_STATUS
BBTestReadBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.6
//
EFI_STATUS
BBTestWriteBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.7
//
EFI_STATUS
BBTestFlushBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.8
//
EFI_STATUS
BBTestSetPositionBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.9
//
EFI_STATUS
BBTestGetPositionBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.10
//
EFI_STATUS
BBTestGetInfoBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.11
//
EFI_STATUS
BBTestSetInfoBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint functions for basic tests
//

//
// TDS 5.1.1.2.1
//
EFI_STATUS
BBTestOpenVolumeBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.2.2.1
//
EFI_STATUS
BBTestOpenBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );

//
// TDS 5.1.2.2.2
//
EFI_STATUS
BBTestOpenBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );

//
// TDS 5.1.3.2.1
//
EFI_STATUS
BBTestCloseBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.4.2.1
//
EFI_STATUS
BBTestDeleteBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.4.2.2
//
EFI_STATUS
BBTestDeleteBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.4.2.3
//
EFI_STATUS
BBTestDeleteBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.5.2.1
//
EFI_STATUS
BBTestReadBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.5.2.2
//
EFI_STATUS
BBTestReadBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.6.2.1
//
EFI_STATUS
BBTestWriteBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.7.2.1
//
EFI_STATUS
BBTestFlushBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.7.2.2
//
EFI_STATUS
BBTestFlushBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.8.2.1
//
EFI_STATUS
BBTestSetPositionBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *v
  );

//
// TDS 5.1.8.2.2
//
EFI_STATUS
BBTestSetPositionBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.9.2.1
//
EFI_STATUS
BBTestGetPositionBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *v
  );

//
// TDS 5.1.10.2.1
//
EFI_STATUS
BBTestGetInfoBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );

//
// TDS 5.1.10.2.2
//
EFI_STATUS
BBTestGetInfoBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );


//
// TDS 5.1.10.2.3
//
EFI_STATUS
BBTestGetInfoBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.10.2.4
//
EFI_STATUS
BBTestGetInfoBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.11.2.1
//
EFI_STATUS
BBTestSetInfoBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );

//
// TDS 5.1.11.2.2
//
EFI_STATUS
BBTestSetInfoBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.11.2.3
//
EFI_STATUS
BBTestSetInfoBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// Conformance test functions
//

//
// TDS 5.2.1
//
EFI_STATUS
BBTestOpenConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.2
//
EFI_STATUS
BBTestDeleteConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.3
//
EFI_STATUS
BBTestWriteConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.4
//
EFI_STATUS
BBTestFlushConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.5
//
EFI_STATUS
BBTestSetPositionConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.6
//
EFI_STATUS
BBTestGetPositionConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.7
//
EFI_STATUS
BBTestGetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.8
//
EFI_STATUS
BBTestSetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint functions for Conformance tests
//

//
// TDS 5.2.1.2.1
//
EFI_STATUS
BBTestOpenConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.2
//
EFI_STATUS
BBTestOpenConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.3
//
EFI_STATUS
BBTestOpenConformanceTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.4
//
EFI_STATUS
BBTestOpenConformanceTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.5
//
EFI_STATUS
BBTestOpenConformanceTestCheckpoint5(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.6
//
EFI_STATUS
BBTestOpenConformanceTestCheckpoint6(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.2.2.1
//
EFI_STATUS
BBTestDeleteConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.3.2.1
//
EFI_STATUS
BBTestWriteConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.3.2.2
//
EFI_STATUS
BBTestWriteConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.3.2.3
//
EFI_STATUS
BBTestWriteConformanceTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.4.2.1
//
EFI_STATUS
BBTestFlushConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.4.2.2
//
EFI_STATUS
BBTestFlushConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.5.2.1
//
EFI_STATUS
BBTestSetPositionConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.6.2.1
//
EFI_STATUS
BBTestGetPositionConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.7.2.1
//
EFI_STATUS
BBTestGetInfoConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.7.2.2
//
EFI_STATUS
BBTestGetInfoConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.1
//
EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.2
//
EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.3
//
EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.4
//
EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.5
//
EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint5(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint6(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

// TDS 5.2.8.2.7
EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint7(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

// TDS 5.2.8.2.8
EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint8 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// Automatic Extensive test functions
//

//
// TDS 5.3.1
//
EFI_STATUS
BBTestSimpleFileSytemExtensiveTest1 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.2
//
EFI_STATUS
BBTestSimpleFileSytemExtensiveTest2 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.3
//
EFI_STATUS
BBTestSimpleFileSytemExtensiveTest3 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.4
//
EFI_STATUS
BBTestSimpleFileSytemExtensiveTest4 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.5
//
EFI_STATUS
BBTestSimpleFileSytemExtensiveTest5 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.6
//
EFI_STATUS
BBTestSimpleFileSytemExtensiveTest6 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.7
//
EFI_STATUS
BBTestSimpleFileSytemOpenStress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.8
//
EFI_STATUS
BBTestSimpleFileSytemGetInfoStress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.9
//
EFI_STATUS
BBTestSimpleFileSytemSetInfoStress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// some internal functions
//
EFI_STATUS
InternalGetInfo (
  EFI_FILE      *FileHandle,
  VOID          **InfoBuffer,
  UINTN         *BufferSize,
  EFI_GUID      *InfoId
  );

EFI_STATUS
InternalSetFileSize (
  EFI_FILE      *FileHandle,
  UINT64        FileSize
  );

EFI_STATUS
InternalSetFileAttribute (
  EFI_FILE      *FileHandle,
  UINT64        Attribute
  );



#endif
