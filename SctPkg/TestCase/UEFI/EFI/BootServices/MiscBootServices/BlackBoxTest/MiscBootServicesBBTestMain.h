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

  MiscBootServicesBBTestMain.h

Abstract:

  BB test header file of Miscellaneous Boot Services

--*/


#ifndef _MISCELLANEOUS_BOOT_SERVICES
#define _MISCELLANEOUS_BOOT_SERVICES

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

typedef struct _RESET_DATA {
  UINTN           Step;
  UINTN           TplIndex;
  UINT64          Count;
} RESET_DATA;

#include EFI_TEST_PROTOCOL_DEFINITION (TestRecoveryLibrary)

#define MISCELLANEOUS_BOOT_SERVICES_TEST_REVISION   0x00010001

#define MISCELLANEOUS_BOOT_SERVICES_TEST_GUID       \
  {0xA6033499, 0xE4AF, 0x44f5, 0x9D, 0x16, 0x30, 0x78, 0xD8, 0x61, 0x32, 0x28 }

#define TPL_ARRAY_SIZE 3
#define MAX_SECOND_MARGIN 2

//
// Change size from TPL_ARRAY_SIZE to TPL_ARRAY_SIZE + 1
// for Stall test in TPL_HIGH_LEVEL
//
extern EFI_TPL TplArray[TPL_ARRAY_SIZE + 1];

#define isleap(y) (((((y) % 4) == 0) && (((y) % 100) != 0)) || (((y) % 400) == 0))

static const UINTN  mon_lengths[2][12] = {
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

#define MINSPERHOUR  60
#define HOURSPERDAY  24
#define SECSPERMIN  60
#define SECSPERHOUR  (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY  ((long) SECSPERHOUR * HOURSPERDAY)
#define DAYSPERNYEAR  365
#define DAYSPERLYEAR  366

//
// Prototypes of Consistency Test
//

//
// TDS 3.1
//
EFI_STATUS
BBTestSetWatchdogTimerConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
BBTestGetNextMonotonicCountConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.3
//
EFI_STATUS
BBTestInstallConfigurationTableConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.4
//
EFI_STATUS
BBTestCalculateCrc32ConsistencyTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.1
//
EFI_STATUS
BBTestSetWatchdogTimerInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
BBTestStallInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
BBTestCopyMemInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.4
//
EFI_STATUS
BBTestSetMemInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.5
//
EFI_STATUS
BBTestGetNextMonotonicCountInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.6
//
EFI_STATUS
BBTestInstallConfigurationTableInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.7
//
EFI_STATUS
BBTestCalculateCrc32InterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1
//
EFI_STATUS
BBTestSetWatchdogTimerStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
BBTestStallStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3
//
EFI_STATUS
BBTestCopyMemStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.4
//
EFI_STATUS
BBTestSetMemStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.5
//
EFI_STATUS
BBTestGetNextMonotonicCountStressTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Internal Functions
//
UINT32
SecondsElapsedFromBaseYear (
  IN UINT16      BaseYear,
  IN UINT16      Year,
  IN UINT8       Month,
  IN UINT8       Day,
  IN UINT8       Hour,
  IN UINT8       Minute,
  IN UINT8       Second
  ) ;

UINT32
GetSecondsElapsed (
  IN EFI_TIME       *StartTime,
  IN EFI_TIME       *EndTime
  );

VOID
SetTestMem (
  IN UINT8 *Buffer,
  IN UINTN Size,
  IN UINT8 Value
  );

EFI_STATUS
CheckTestMem (
  IN UINT8 *Buffer,
  IN UINTN Size,
  IN UINT8 Value
  );

EFI_STATUS
CheckMemoryType (
  IN EFI_PHYSICAL_ADDRESS        Memory,
  IN UINTN                       Size,
  IN UINT32                      Type
  );

//
// Entry GUIDs
//

#define MISC_BOOT_SERVICES_SETWATCHDOGTIMER_CONSISTENCY_GUID \
  { 0xff388ae5, 0x4c51, 0x45c6, 0x9d, 0x37, 0x6d, 0xe0, 0x4b, 0xf9, 0x21, 0x9a }

#define MISC_BOOT_SERVICES_GETNEXTMONOTONICCOUNT_CONSISTENCY_GUID \
  { 0xe9544e95, 0x2792, 0x494c, 0xac, 0x39, 0xcc, 0x33, 0x68, 0x8f, 0x95, 0x13 }

#define MISC_BOOT_SERVICES_INSTALLCONFIGURATIONTABLE_CONSISTENCY_GUID \
  { 0xe00a6879, 0xaf7e, 0x4238, 0xaa, 0xd1, 0xb, 0x89, 0x1e, 0x71, 0xd7, 0x21 }

#define MISC_BOOT_SERVICES_CALCULATECRC32_CONSISTENCY_GUID \
  { 0x718165e6, 0xc904, 0x43f1, 0x9a, 0x93, 0xdd, 0xe3, 0x46, 0x7e, 0xed, 0xc2 }

#define MISC_BOOT_SERVICES_SETWATCHDOGTIMER_INTERFACE_GUID \
  { 0xf17b25a1, 0x866b, 0x4791, 0xbc, 0x9c, 0xbb, 0x3d, 0x19, 0xe4, 0xb3, 0xf8 }

#define MISC_BOOT_SERVICES_STALL_INTERFACE_GUID \
  { 0x539675b8, 0xd9b3, 0x4dc7, 0xa8, 0xd0, 0xff, 0x19, 0xbb, 0xa1, 0x3b, 0x86 }

#define MISC_BOOT_SERVICES_COPYMEM_INTERFACE_GUID \
  { 0x4397a610, 0x8d5d, 0x441b, 0x8e, 0x7d, 0xc2, 0x33, 0x77, 0xf3, 0xeb, 0x67 }

#define MISC_BOOT_SERVICES_SETMEM_INTERFACE_GUID \
  { 0x315be343, 0xa32d, 0x461d, 0xa3, 0xcc, 0x5e, 0x68, 0x95, 0xcc, 0x2c, 0xba }

#define MISC_BOOT_SERVICES_GETNEXTMONOTONICCOUNT_INTERFACE_GUID \
  { 0xd35aaef2, 0x55fb, 0x4377, 0xa0, 0x7b, 0x29, 0xdc, 0xa3, 0x20, 0x1f, 0x19 }

#define MISC_BOOT_SERVICES_INSTALLCONFIGURATIONTABLE_INTERFACE_GUID \
  { 0x911fb78b, 0x1a6d, 0x46c4, 0x9f, 0x68, 0x50, 0x9c, 0xfb, 0x59, 0x3d, 0x98 }

#define MISC_BOOT_SERVICES_CALCULATECRC32_INTERFACE_GUID \
  { 0xb510f99f, 0xfee9, 0x4af6, 0xbb, 0xf, 0x3c, 0x95, 0x8e, 0xf7, 0xf1, 0x66 }

#define MISC_BOOT_SERVICES_SETWATCHDOGTIMER_STRESS_TEST_GUID \
  { 0xd30a3a18, 0x4058, 0x4c68, 0x98, 0xee, 0xaf, 0x8d, 0xe6, 0x11, 0x25, 0xa4 }

#define MISC_BOOT_SERVICES_STALL_STRESS_TEST_GUID \
  { 0xd7506892, 0xe4af, 0x45c5, 0x96, 0x78, 0xad, 0x65, 0xeb, 0xb4, 0xdc, 0xe7 }

#define MISC_BOOT_SERVICES_COPYMEM_STRESS_TEST_GUID \
  { 0x435d51a6, 0xe3c9, 0x4079, 0xbf, 0xf9, 0xfd, 0x75, 0x83, 0x37, 0x81, 0xab }

#define MISC_BOOT_SERVICES_SETMEM_STRESS_TEST_GUID \
  { 0x3858b70e, 0x34f6, 0x4704, 0xa7, 0xd2, 0xe1, 0x52, 0x22, 0x65, 0xc7, 0xa5 }

#define MISC_BOOT_SERVICES_GETNEXTMONOTONICCOUNT_STRESS_TEST_GUID \
  { 0xeaecbb1d, 0xedc4, 0x4749, 0xa3, 0xe2, 0xcc, 0x48, 0x49, 0x1d, 0x76, 0xf }

#define MISC_BOOT_SERVICES_TEST_TABLE_GUID \
  { 0x1ba91874, 0x2bc4, 0x4b8b, 0xb6, 0xb, 0x2d, 0xf, 0xe4, 0x1d, 0xb3, 0x33 }

extern EFI_GUID gMiscBootServicesTestTableGuid;

#endif
