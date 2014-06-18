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

  MemoryAllocationServicesBBTestMain.h

Abstract:

  BB test header file of Memory Allocation Boot Services

--*/


#ifndef _MEMORY_ALLOCATION_SERVICES
#define _MEMORY_ALLOCATION_SERVICES

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>


#define MEMORY_ALLOCATION_SERVICES_TEST_REVISION    0x00010000

#define MEMORY_ALLOCATION_SERVICES_TEST_GUID        \
  { 0xCC129459, 0xA197, 0x4c8f, 0x94, 0x22, 0x24, 0x41, 0xE8, 0x8C, 0x55, 0x9A }

#define TPL_ARRAY_SIZE 3

extern EFI_TPL TplArray[TPL_ARRAY_SIZE];

//
// Prototypes of Consistency Test
//

//
// TDS 3.1
//
EFI_STATUS
BBTestGetMemoryMapConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
BBTestAllocatePagesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.3
//
EFI_STATUS
BBTestFreePagesConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.4
//
EFI_STATUS
BBTestAllocatePoolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.5
//
EFI_STATUS
BBTestFreePoolConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1
//
EFI_STATUS
BBTestGetMemoryMapInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
BBTestAllocatePagesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
BBTestFreePagesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.4
//
EFI_STATUS
BBTestAllocatePoolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.5
//
EFI_STATUS
BBTestFreePoolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1
//
EFI_STATUS
BBTestGetMemoryMapStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
BBTestPagesStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3
//
EFI_STATUS
BBTestPoolStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Internal Functions
//

extern UINT8                                *MemoryMap;
extern UINTN                                MemoryMapSizeNeeded;

EFI_STATUS
InitMemoryMap (
  );

EFI_STATUS
FreeMemoryMap (
  );

EFI_STATUS
GetMaxFreeMemoryDescriptor (
  OUT EFI_MEMORY_DESCRIPTOR       *MemoryDescriptor
  );

EFI_STATUS
GetMaxAddressMemoryDescriptor (
  OUT EFI_MEMORY_DESCRIPTOR       *MemoryDescriptor
  );

EFI_STATUS
GetAllocatedMemoryDescriptor (
  OUT EFI_MEMORY_DESCRIPTOR       *MemoryDescriptor
  );

EFI_STATUS
GetSecondMaxFreeMemoryDescriptor (
  OUT EFI_MEMORY_DESCRIPTOR       *MemoryDescriptor
  );

//
// Entry GUIDs
//

#define MEMORY_ALLOCATION_SERVICES_GETMEMORYMAP_CONSISTENCY_GUID \
  { 0x2c437186, 0xd178, 0x40cf, 0xa7, 0xb1, 0xa2, 0xe8, 0x6a, 0xf0, 0x6d, 0x86 }

#define MEMORY_ALLOCATION_SERVICES_ALLOCATEPAGES_CONSISTENCY_GUID \
  { 0x4e87315f, 0xbad6, 0x4b90, 0x88, 0xc3, 0x29, 0x72, 0xb1, 0xf9, 0xac, 0xbe }

#define MEMORY_ALLOCATION_SERVICES_FREEPAGES_CONSISTENCY_GUID \
  { 0xf30940b6, 0xde0d, 0x47b2, 0xbe, 0xbe, 0xe1, 0xc2, 0xc, 0x92, 0x13, 0xe9 }

#define MEMORY_ALLOCATION_SERVICES_ALLOCATEPOOL_CONSISTENCY_GUID \
  { 0x90023546, 0x6c92, 0x430a, 0xb2, 0x53, 0x70, 0x11, 0xd, 0x9e, 0xfd, 0xff }

#define MEMORY_ALLOCATION_SERVICES_FREEPOOL_CONSISTENCY_GUID \
  { 0x49709f9f, 0xa4d8, 0x42d6, 0xa6, 0x84, 0x49, 0x75, 0xee, 0x0, 0x99, 0xdb }

#define MEMORY_ALLOCATION_SERVICES_GETMEMORYMAP_INTERFACE_GUID \
  { 0xcde8be7, 0x85dc, 0x4e7c, 0xa5, 0x84, 0x56, 0x6a, 0x64, 0x3a, 0x35, 0x62 }

#define MEMORY_ALLOCATION_SERVICES_ALLOCATEPAGES_INTERFACE_GUID \
  { 0x21338335, 0x67ba, 0x4392, 0x8d, 0x5e, 0x71, 0x84, 0xc6, 0xd6, 0x1, 0xa6 }

#define MEMORY_ALLOCATION_SERVICES_FREEPAGES_INTERFACE_GUID \
  { 0x2cf12f16, 0x962e, 0x439d, 0xa1, 0xbf, 0x4e, 0x91, 0x51, 0x84, 0xeb, 0xae }

#define MEMORY_ALLOCATION_SERVICES_ALLOCATEPOOL_INTERFACE_GUID \
  { 0x4d5b638, 0xe15a, 0x4839, 0x9e, 0x7a, 0x6f, 0x1f, 0x6a, 0x3c, 0x58, 0x88 }

#define MEMORY_ALLOCATION_SERVICES_FREEPOOL_INTERFACE_GUID \
  { 0xd9980a61, 0x670b, 0x4078, 0x90, 0x49, 0x13, 0x9, 0xfc, 0xec, 0x71, 0x6 }

#define MEMORY_ALLOCATION_SERVICES_GETMEMORYMAP_STRESS_TEST_GUID \
  { 0x33c006dc, 0x57a6, 0x4a80, 0x97, 0x21, 0x92, 0xdc, 0x39, 0x3e, 0xb7, 0xf1 }

#define MEMORY_ALLOCATION_SERVICES_PAGES_STRESS_TEST_GUID \
  { 0xc48baf05, 0xf5cc, 0x4e38, 0xba, 0xf6, 0xf3, 0xee, 0xa5, 0x84, 0xcc, 0x5 }

#define MEMORY_ALLOCATION_SERVICES_POOL_STRESS_TEST_GUID \
  { 0x76b79925, 0x5353, 0x472d, 0x9d, 0x58, 0xfc, 0x53, 0x9, 0xcc, 0xcd, 0x7 }

#endif