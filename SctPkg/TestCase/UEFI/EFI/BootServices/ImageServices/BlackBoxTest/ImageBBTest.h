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
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  ImageBBTest.h

Abstract:

  head file of test driver of Image Boot Services

--*/

#ifndef _IMAGE_BBTEST_H
#define _IMAGE_BBTEST_H


#include "Efi.h"
#include <Library/EfiTestLib.h>
#include "Guid.h"

#include EFI_PROTOCOL_DEFINITION (LoadFile)

#include EFI_TEST_PROTOCOL_DEFINITION (TestProfileLibrary)

#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)

extern     UINT8          mPackageList[];
extern     EFI_GUID     mPackageListGuid ;
extern     EFI_GUID     mPackageGuid ;

typedef    EFI_HII_PACKAGE_LIST_HEADER    *EFI_HII_PACKAGE_LIST_PROTOCOL;

#endif

#define IMAGE_BOOT_SERVICES_TEST_REVISION 0x00010001

#define IMAGE_BOOT_SERVICES_TEST_GUID     \
  { 0x883B957B, 0x25FF, 0x4b90, 0xA3, 0xA3, 0x0A, 0xA2, 0x60, 0x59, 0x98, 0x93 }

extern EFI_HANDLE   mImageHandle;
extern CHAR16       *mFilePath;

//
// EFI Package List Form
//
#define EFI_HII_PACKAGE_FORM                 0x02   

//
// LoadImage & StartImage TPL liminations: lower than TPL_CALLBACK
//
#define TPL_ARRAY_SIZE_FOR_LOAD_START_IMAGE  1

//
// Unload & Exit TPL liminations: lower than TPL_NOTIFY
//
#define TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE  2

extern EFI_TPL TplArray [TPL_ARRAY_SIZE_FOR_UNLOAD_EXIT_IMAGE];

#define STALL_1_SECOND    1000000 // in microsecond unit

#define MAX_STRING_LEN      250

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Consistency Test
//
#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0101 \
 {0x225239ad, 0xdcb8, 0x4367, {0x8f, 0xd8, 0x8e, 0x19, 0xe, 0x1a, 0x3, 0x8} }

#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0102 \
  {0x61995ef9, 0xd030, 0x44b1, {0x86, 0x4c, 0x55, 0xef, 0x7d, 0x7c, 0xbb, 0x74} }

#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0103 \
 { 0xb9afcac3, 0x198f, 0x4783, {0xa8, 0xca, 0x79, 0x59, 0x78, 0xdf, 0xcf, 0xba} }

#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0104 \
 {0xdd6e776a, 0x53a5, 0x4a72, {0x9e, 0xa6, 0xfb, 0x71, 0xa7, 0x9, 0x6e, 0xb5} }

#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0105 \
 {0x303abfab, 0xc865, 0x4255, {0x86, 0xe3, 0x6e, 0xef, 0x17, 0x5e, 0x30, 0xdd} }

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Interface Function Test
//
#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0200 \
 {0x2ff0431a, 0x8e07, 0x4cdb, {0xa2, 0x98, 0xd0, 0x4, 0x56, 0x6a, 0x74, 0xd4} }

#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0201 \
 {0xd407bc73, 0xbb7e, 0x443c, {0x9a, 0x61, 0x97, 0xc7, 0xb, 0x7a, 0x1d, 0x62} }

#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0202 \
 {0x4ac540da, 0xbb57, 0x4a8c, {0x82, 0x66, 0xff, 0x80, 0x9b, 0xc, 0x8f, 0xa2} }

#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0203 \
 {0x4ea3eea6, 0xf7c9, 0x4568, {0xb8, 0x1e, 0x10, 0xd3, 0xe0, 0xfe, 0xd6, 0xe7} }

#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0204 \
 {0x1491fd0d, 0xe7c0, 0x460f, {0x94, 0x6d, 0x2a, 0xf7, 0x85, 0x67, 0xd1, 0xaa} }

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Combination Test
//
#define IMAGE_BOOT_SERVICES_TEST_ENTRY_GUID0301 \
 {0xf18cfd06, 0x215e, 0x47f3, {0xa1, 0xd3, 0x87, 0x73, 0x22, 0xbc, 0x3f, 0xe0} }


//
// Functions for MainTest.c
//
EFI_STATUS
InitializeBBTestImageBootServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestImageBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  );


///////////////////////////////////////////////////////////////////////////////
//
// Functions for Consistency Test
//

//
// TDS 3.1
//
EFI_STATUS
BBTestLoadImageConsistencyTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
BBTestStartImageConsistencyTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.3
//
EFI_STATUS
BBTestUnloadImageConsistencyTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.4
//
EFI_STATUS
BBTestExitConsistencyTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.5
//
EFI_STATUS
BBTestExitBootServicesConsistencyTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1
//
EFI_STATUS
BBTestLoadImageInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
BBTestStartImageInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
BBTestUnloadImageInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.4
//
EFI_STATUS
BBTestExitInterfaceTest (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1
//
EFI_STATUS
BBTestImageServicesCombinationTest1 (
    IN EFI_BB_TEST_PROTOCOL       *This,
    IN VOID                       *ClientInterface,
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint functions for TDS 4.1
//
EFI_STATUS
BBTestLoadImageInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLoadImageInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLoadImageInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLoadImageInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLoadImageInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLoadImageInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLoadImageInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
EFI_STATUS
BBTestLoadImageInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestLoadImageInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );
#endif
//
// Checkpoint functions for TDS 4.2
//
EFI_STATUS
BBTestStartImageInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestStartImageInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestStartImageInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestStartImageInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestStartImageInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestStartImageInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint functions for TDS 4.3
//
EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestUnloadImageInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Checkpoint functions for TDS 4.4
//
EFI_STATUS
BBTestExitInterfaceTestCheckPoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestExitInterfaceTestCheckPoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestExitInterfaceTestCheckPoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestExitInterfaceTestCheckPoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestExitInterfaceTestCheckPoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestExitInterfaceTestCheckPoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestExitInterfaceTestCheckPoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestExitInterfaceTestCheckPoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestExitInterfaceTestCheckPoint9 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestExitInterfaceTestCheckPoint10 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );
#endif
