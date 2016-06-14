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

  DiskIoBBTestMain.h

Abstract:

  BB test header file of Disk I/O Protocol

--*/


#ifndef _DISK_IO_BBTEST_H_
#define _DISK_IO_BBTEST_H_


#include "Efi.h"
#include <UEFI/Protocol/BlockIo.h>
#include <UEFI/Protocol/DiskIo.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define  DISK_IO_PROTOCOL_TEST_REVISION    0x00010000

#define  MAX_NUMBER_OF_READ_DISK_BUFFER    65536
#define  MAX_DIFFERENT_BUFFERSIZE_FOR_TEST 4
#define  MAX_DIFFERENT_LBA_FOR_TEST        4
#define  MAX_DIFFERENT_IOALIGN_FOR_TEST    4
#define  MAX_REPEAT_OF_STRESS_TEST         20

extern   EFI_EVENT                         TimerEvent;

EFI_STATUS
InitializeBBTestDiskIo (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestDiskIoProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
BBTestReadDiskConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestWriteDiskConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Function Interface test declaration section
//

EFI_STATUS
BBTestReadDiskFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteDiskFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Combination test declaration section
//

EFI_STATUS
BBTestReadDiskStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteDiskStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Other function declaration section
//
UINTN
VerifyBuffer(
  IN UINT8           *Buffer1,
  IN UINT8           *Buffer2,
  IN UINTN           BufferSize
  );

BOOLEAN
AutoJudge(
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

EFI_STATUS
LocateBlockIoFromDiskIo(
  IN EFI_DISK_IO_PROTOCOL                 *DiskIo,
  IN EFI_BLOCK_IO_PROTOCOL                **BlockIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
LocateDevicePathFromDiskIo(
  IN EFI_DISK_IO_PROTOCOL                 *DiskIo,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Entry GUIDs
//

//
// Comformance
//

#define DISK_IO_PROTOCOL_READDISK_CONFORMANCE_AUTO_GUID \
  { 0x75dfba09, 0x44f, 0x4a18, { 0x81, 0x38, 0xa5, 0x3a, 0x7a, 0x88, 0x4c, 0xda } }

#define DISK_IO_PROTOCOL_WRITEDISK_CONFORMANCE_AUTO_GUID \
  { 0xbbf7473a, 0xa8af, 0x4948, { 0xa7, 0xf3, 0x91, 0x51, 0xa1, 0x34, 0x56, 0xd6 } }

//
// Function
//

#define DISK_IO_PROTOCOL_READDISK_FUNCTION_AUTO_GUID \
  { 0x7e06642e, 0x36c1, 0x436e, { 0x9d, 0x27, 0xfb, 0x11, 0x9c, 0x96, 0xd2, 0x1f } }

#define DISK_IO_PROTOCOL_WRITEDISK_FUNCTION_AUTO_GUID \
  { 0x6006c77f, 0xa521, 0x4aac, { 0x97, 0xf6, 0xf0, 0x68, 0x67, 0xd8, 0x86, 0x6d } }

//
// Combination
//
#define DISK_IO_PROTOCOL_READDISK_STRESS_AUTO_GUID \
  { 0xb9f35106, 0xb49a, 0x4e35, { 0xb4, 0x44, 0x3a, 0x42, 0x72, 0xe6, 0x40, 0x7f } }

#define DISK_IO_PROTOCOL_WRITEDISK_STRESS_AUTO_GUID \
  { 0xccd054bd, 0x6a62, 0x49f5, { 0xa5, 0xf8, 0xaa, 0xc8, 0x6f, 0x1e, 0x3d, 0x1c } }


#endif

