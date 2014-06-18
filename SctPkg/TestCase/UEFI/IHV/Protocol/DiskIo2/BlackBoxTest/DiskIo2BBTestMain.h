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

  DiskIo2BBTestMain.h

Abstract:

  BB test header file of Disk I/O2 Protocol

--*/


#ifndef _DISK_IO2_BBTEST_H_
#define _DISK_IO2_BBTEST_H_


#include "SctLib.h"
#include <UEFI/Protocol/DiskIo2.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/BlockIo2.h>


#define  IHV_DISK_IO2_PROTOCOL_TEST_REVISION    0x00020000

#define  IHV_DISK_IO2_PROTOCOL_GUID         \
  {0x7bbdca06, 0x99c5, 0x4d0a, { 0xb5, 0x7a, 0xa5, 0x26, 0xd5, 0x25, 0xb2, 0xcc }}




#define  MAX_NUMBER_OF_READ_DISK_BUFFER     65536
#define  MAX_DIFFERENT_BUFFERSIZE_FOR_TEST  4
#define  MAX_DIFFERENT_LBA_FOR_TEST         4
#define  MAX_DIFFERENT_IOALIGN_FOR_TEST     4
#define  MAX_REPEAT_OF_STRESS_TEST          20
#define DISKIO2ENTITY_SIGNATURE             EFI_SIGNATURE_32('d','i','o','2')



extern   EFI_EVENT                          TimerEvent;

EFI_STATUS
InitializeBBTestDiskIo2 (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDiskIo2ProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
BBTestReadDiskExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFlushDiskExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteDiskExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Function Interface test declaration section
//
EFI_STATUS
BBTestCancelFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestReadDiskExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFlushDiskExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteDiskExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

VOID
EFIAPI DiskIo2FinishNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  );




EFI_STATUS
LocateDevicePathFromDiskIo2(
  IN EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  IN EFI_DEVICE_PATH_PROTOCOL              **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib
  );

EFI_STATUS
LocateBlockIo2FromDiskIo2(
  IN EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  IN EFI_BLOCK_IO2_PROTOCOL                **BlockIo2,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib
  );


//
// record every Disk IO 2 Async call status
//
typedef struct {
  UINTN                             Signature;
  EFI_DISK_IO2_TOKEN               	DiskIo2Token;
  UINT32                            MediaId;
  UINT64                            Offset;
  UINTN                             BufferSize;
  VOID                              *Buffer;
  SCT_LIST_ENTRY                    ListEntry;     
  EFI_STATUS                        StatusAsync;
  BOOLEAN                           MemCompared;
  UINTN                             ComparedVal;
  EFI_TEST_ASSERTION                AssertionType;
} DiskIO2_Task;


typedef struct {
  EFI_DISK_IO2_PROTOCOL             *DiskIo2;
  SCT_LIST_ENTRY                    *TaskHeader; 
  SCT_LIST_ENTRY                    *CurrentTaskEntry;
  EFI_DISK_IO2_TOKEN                *Token;
} DiskIO2_Batch_Task_Context;


//
// Entry GUIDs
//

//
// Comformance
//

#define DISK_IO2_PROTOCOL_READDISKEX_CONFORMANCE_AUTO_GUID \
  { 0x38c754d4, 0x8aff, 0x4cdd, { 0x9e, 0x20, 0x34, 0xea, 0x56, 0x1c, 0xeb, 0xe1 } }


#define DISK_IO2_PROTOCOL_FLUSHDISKEX_CONFORMANCE_AUTO_GUID \
  { 0xa91bc372, 0x10ff, 0x4e23, { 0xbe, 0xbd, 0x81, 0x3, 0x1d, 0x92, 0xcc, 0x94 } }
  

#define DISK_IO2_PROTOCOL_WRITEDISKEX_CONFORMANCE_AUTO_GUID \
  { 0x67eb768b, 0xf303, 0x420b, { 0x9f, 0xd9, 0x1f, 0x3f, 0x6d, 0x43, 0xe4, 0x99 } }
  

//
// Function
//
#define DISK_IO2_PROTOCOL_CANCEL_FUNCTION_AUTO_GUID \
  {0x5bdac136, 0x9a4e, 0x4087, { 0x8d, 0x59, 0xe1, 0x13, 0x47, 0x8a, 0x54, 0x44 } }
  

#define DISK_IO2_PROTOCOL_READDISKEX_FUNCTION_AUTO_GUID \
  { 0xb32c8adb, 0xc6f6, 0x4a41, { 0x98, 0xe7, 0x96, 0x18, 0x96, 0x5b, 0x1e, 0x21 } }
  
#define DISK_IO2_PROTOCOL_FLUSHDISKEX_FUNCTION_AUTO_GUID \
  { 0x73449201, 0xf501, 0x467e, { 0x8b, 0x18, 0x24, 0xce, 0x43, 0xf, 0xb6, 0x35 } }
  

#define DISK_IO2_PROTOCOL_WRITEDISKEX_FUNCTION_AUTO_GUID \
  {0xfb7b94af, 0x368, 0x4a66, { 0xaf, 0x52, 0x31, 0x0, 0x8a, 0xf1, 0xd5, 0xc7 } }

#endif

