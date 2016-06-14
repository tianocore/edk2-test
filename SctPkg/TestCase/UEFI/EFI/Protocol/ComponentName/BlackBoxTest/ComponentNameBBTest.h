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
    ComponentNameBBTest.h

Abstract:
    head file of test driver of EFI Component Name Protocol Test

--*/

#ifndef _COMPONENT_NAME_TEST_H
#define _COMPONENT_NAME_TEST_H


#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/ComponentName.h>
#include "Guid.h"

#define EFI_COMPONENT_NAME_TEST_REVISION 0x00010000

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Basic Test
//
#define EFI_COMPONENT_NAME_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0x607330af, 0xc73c, 0x46a0, {0xb6, 0x9d, 0xd9, 0x5a, 0x1e, 0x3d, 0x84, 0xd7} }

#define EFI_COMPONENT_NAME_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0x76b77615, 0xdc9b, 0x4080, {0xb7, 0xf2, 0xdc, 0x1e, 0x9b, 0xef, 0xf0, 0x51} }

#define EFI_COMPONENT_NAME_PROTOCOL_TEST_ENTRY_GUID0103 \


//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define EFI_COMPONENT_NAME_PROTOCOL_TEST_ENTRY_GUID0201 \
 {0x7c2a00f3, 0xed82, 0x48c0, {0x81, 0x85, 0x6b, 0xcc, 0x1b, 0xa2, 0xef, 0xe5} }

#define EFI_COMPONENT_NAME_PROTOCOL_TEST_ENTRY_GUID0202 \
 {0xcea9e2d1, 0xcf17, 0x4cbe, {0x97, 0x2b, 0x3a, 0xf0, 0xd9, 0x11, 0x43, 0x49} }

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

//
// TestNoInterfaceProtocol1
//
#define TEST_NO_INTERFACE_PROTOCOL_1_GUID \
  {0x7362363, 0x3617, 0x4d92, 0xa1, 0xb1, 0x1d, 0x62, 0xa5, 0x78, 0x91, 0xa5 };

extern EFI_GUID mTestNoInterfaceProtocol1Guid;

//
// TestNoInterfaceProtocol2
//
#define TEST_NO_INTERFACE_PROTOCOL_2_GUID \
  {0x3fd2484, 0xa340, 0x41a7, 0xba, 0x13, 0xb4, 0x93, 0xb0, 0x67, 0xdb, 0x4c };

extern EFI_GUID mTestNoInterfaceProtocol2Guid;


//
// functions declaration
//

EFI_STATUS
InitializeBBTestComponentName (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestComponentNameUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Basic test functions
//

//
// TDS 9.2.1
//
EFI_STATUS
BBTestGetDriverNameBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 9.2.2
//
EFI_STATUS
BBTestGetControllerNameBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint functions for Basic tests
//

//
// TDS 9.2.1.2.1
//
EFI_STATUS
BBTestGetDriverNameBasicTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  );

//
// TDS 9.2.2.2.1
//
EFI_STATUS
BBTestGetControllerNameBasicTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  );

//
// TDS 9.2.2.2.2
//
EFI_STATUS
BBTestGetControllerNameBasicTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  );

//
// Conformance test functions
//

//
// TDS 9.3.1
//
EFI_STATUS
BBTestGetDriverNameConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 9.3.2
//
EFI_STATUS
BBTestGetControllerNameConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint functions for Conformance tests
//

//
// TDS 9.3.1.2.1
//
EFI_STATUS
BBTestGetDriverNameConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  );

//
// TDS 9.3.1.2.2
//
EFI_STATUS
BBTestGetDriverNameConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  );

//
// TDS 9.3.2.2.1
//
EFI_STATUS
BBTestGetControllerNameConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  );

//
// TDS 9.3.2.2.2
//
EFI_STATUS
BBTestGetControllerNameConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  );

//
// TDS 9.3.3.2.3
//
EFI_STATUS
BBTestGetControllerNameConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  );

EFI_STATUS
BBTestGetControllerNameConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_COMPONENT_NAME_PROTOCOL           *ComponentName
  );

#endif
