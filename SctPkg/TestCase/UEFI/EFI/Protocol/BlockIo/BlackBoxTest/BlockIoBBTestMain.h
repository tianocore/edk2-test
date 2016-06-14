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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  BlockIoBBTestMain.h

Abstract:

  BB test header file of Block I/O Protocol

--*/


#ifndef _BLOCK_IO_BBTEST_H_
#define _BLOCK_IO_BBTEST_H_

//
// Includes
//

#include "Efi.h"
#include <UEFI/Protocol/BlockIo.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>


//
// Definitions
//

#define BLOCK_IO_PROTOCOL_TEST_REVISION     0x00010000

#define MAX_NUMBER_OF_READ_BLOCK_BUFFER     20
#define MAX_DIFFERENT_BUFFERSIZE_FOR_TEST   4
#define MAX_DIFFERENT_LBA_FOR_TEST          4
#define MAX_DIFFERENT_IOALIGN_FOR_TEST      4
#define MAX_REPEAT_OF_STRESS_TEST           20

#define MAXIMUM(a,b)                        ((a)>(b)?(a):(b))
#define MINIMUM(a,b)                        ((a)<(b)?(a):(b))

//
// Entry GUIDs
//

//
// Conformance
//
#define BLOCK_IO_PROTOCOL_READBLOCKS_CONFORMANCE_AUTO_GUID \
  { 0x826159d3, 0x4a5, 0x4cce, { 0x84, 0x31, 0x34, 0x47, 0x7, 0xa8, 0xb5, 0x7a } }

#define BLOCK_IO_PROTOCOL_READBLOCKS_CONFORMANCE_MANUAL_GUID \
  { 0xd743e08, 0xe3fd, 0x401b, { 0x95, 0xc4, 0x98, 0x61, 0x1f, 0x65, 0xf2, 0xee } }

#define BLOCK_IO_PROTOCOL_WRITEBLOCKS_CONFORMANCE_AUTO_GUID \
  { 0x75961463, 0x882b, 0x4afd, { 0x87, 0xcc, 0x7a, 0xfb, 0xd4, 0xd8, 0xff, 0x32 } }

#define BLOCK_IO_PROTOCOL_WRITEBLOCKS_CONFORMANCE_MANUAL_GUID \
  { 0x8b983f70, 0x7478, 0x4f59, { 0xbe, 0xad, 0x16, 0xd1, 0x89, 0x0, 0xa3, 0xd9 } }

#define BLOCK_IO_PROTOCOL_FLUSHBLOCKS_CONFORMANCE_AUTO_GUID \
  { 0x759c5229, 0x272a, 0x45aa, { 0xa6, 0x16, 0xb5, 0x62, 0x26, 0x19, 0xeb, 0x6 } }

#define BLOCK_IO_PROTOCOL_FLUSHBLOCKS_CONFORMANCE_MANUAL_GUID \
  { 0x5c484ad1, 0xa3bc, 0x495a, { 0xa8, 0x82, 0xd6, 0xd8, 0x9d, 0x76, 0xf2, 0xa } }

//
// Function
//
#define BLOCK_IO_PROTOCOL_RESET_FUNCTION_AUTO_GUID \
  { 0xb0501c52, 0x1564, 0x4945, { 0xb5, 0x7b, 0x1f, 0xd2, 0xc8, 0x82, 0xff, 0x91 } }

#define BLOCK_IO_PROTOCOL_READBLOCKS_FUNCTION_AUTO_GUID \
  { 0xa4284ae9, 0xc988, 0x4230, { 0x97, 0x3a, 0x5c, 0x19, 0x39, 0x8c, 0x82, 0x54 } }

#define BLOCK_IO_PROTOCOL_WRITEBLOCKS_FUNCTION_AUTO_GUID \
  { 0xb7e32978, 0x4a8, 0x414d, { 0x99, 0x7b, 0x59, 0x62, 0x8d, 0x73, 0xbf, 0x0 } }

#define BLOCK_IO_PROTOCOL_MEDIA_INTEGRITY_MANUAL_GUID \
  { 0x616fdaf9, 0x413f, 0x4a8c, { 0xac, 0xd5, 0xa5, 0xac, 0x72, 0x71, 0x2c, 0xf2 } }

#define BLOCK_IO_PROTOCOL_FLUSHBLOCKS_FUNCTION_AUTO_GUID \
  { 0x7c947313, 0xc8a3, 0x4abd, { 0xa1, 0xf2, 0x86, 0x70, 0xee, 0x57, 0x4b, 0xe5 } }

#define BLOCK_IO_PROTOCOL_MEDIAINFO_INTEGRITY_AUTO_GUID \
  { 0xeabbfa97, 0x314d, 0x49d2, { 0x90, 0x19, 0xd, 0xff, 0x52, 0x12, 0x6, 0x2f } }

//
// Combination
//
#define BLOCK_IO_PROTOCOL_RESET_STRESS_AUTO_GUID \
  { 0xc29d4482, 0x3341, 0x4bbb, { 0x8c, 0xa3, 0x82, 0xf2, 0x77, 0x2d, 0x98, 0x80 } }

#define BLOCK_IO_PROTOCOL_READBLOCKS_STRESS_AUTO_GUID \
  { 0x4fdea1da, 0x643d, 0x4e71, { 0x82, 0xd7, 0xad, 0xd1, 0xc6, 0x4d, 0x70, 0x9c } }

#define BLOCK_IO_PROTOCOL_WRITEBLOCKS_STRESS_AUTO_GUID \
  { 0x8619522b, 0xc0bb, 0x48ea, { 0xb9, 0xa2, 0x23, 0x0, 0x69, 0xfd, 0x4, 0xa9 } }

//
// Global variables
//

extern   EFI_EVENT                         TimerEvent;

//
// Prototypes
//

EFI_STATUS
InitializeBBTestBlockIo (
  IN EFI_HANDLE                 ImageHandle,
  IN EFI_SYSTEM_TABLE           *SystemTable
  );

EFI_STATUS
BBTestBlockIoProtocolUnload (
  IN EFI_HANDLE                 ImageHandle
  );

//
// Conformance test case prototypes
//

EFI_STATUS
BBTestReadBlocksConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestReadBlocksConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteBlocksConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteBlocksConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFlushBlocksConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestFlushBlocksConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Function test case prototypes
//

EFI_STATUS
BBTestResetFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestReadBlocksFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteBlocksFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFlushBlocksFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestMediaInfoCheckAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestMediaIntegrityManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Stress test case prototypes
//

EFI_STATUS
BBTestResetStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestReadBlocksStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestWriteBlocksStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Internal support function prototypes
//

UINTN
VerifyBuffer(
  IN UINT8                      *Buffer1,
  IN UINT8                      *Buffer2,
  IN UINTN                      BufferSize
  );

BOOLEAN
AutoJudge(
  IN  UINTN                     Seconds,
  IN  BOOLEAN                   Default,
  IN  CHAR16                    *Message
  );

EFI_STATUS
LocateDevicePathFromBlockIo(
  IN EFI_BLOCK_IO_PROTOCOL                *BlockIo,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
LocateBlockIoFromDevicePath(
  IN EFI_BLOCK_IO_PROTOCOL                **BlockIo,
  IN EFI_DEVICE_PATH_PROTOCOL             *DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

VOID *
AllocateAlignedPool (
  IN EFI_MEMORY_TYPE  PoolType,
  IN UINTN            AllocationSize,
  IN UINTN            Alignment
  );

EFI_STATUS
FreeAlignedPool (
  IN VOID   *Buffer
  );

#endif

