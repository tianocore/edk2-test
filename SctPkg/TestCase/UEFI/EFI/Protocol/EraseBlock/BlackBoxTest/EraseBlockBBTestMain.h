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
                                                                
  Copyright 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  EraseBlockBBTestMain.h

Abstract:

  Test Driver of Erase Block Protocol header file

--*/

#ifndef _ERASE_BLOCK_BB_TEST_MAIN
#define _ERASE_BLOCK_BB_TEST_MAIN

#include <Efi.h>
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include <UEFI/Protocol/EraseBlock.h>
#include <UEFI/Protocol/BlockIo.h>
#include <UEFI/Protocol/BlockIo2.h>
#include "Guid.h"


#define EFI_ERASE_BLOCK_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func Test
//
#define EFI_ERASE_BLOCK_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x2e54c9ba, 0xf0e0, 0x4cef, { 0x8c, 0xe6, 0x18, 0x15, 0x79, 0xfe, 0x5f, 0xc }}

//
// Entry GUIDs for Conf Test
//
#define EFI_ERASE_BLOCK_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xd0a834d6, 0xad31, 0x43d2, { 0xa7, 0x6a, 0x9f, 0x1a, 0xd6, 0x9e, 0x6f, 0x15 }}


#define MINIMUM(a,b)                        ((a)<(b)?(a):(b))
#define MAX_NUMBER_OF_READ_BLOCK_BUFFER     20

//
//
//
EFI_STATUS
EFIAPI
InitializeEraseBlockBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadEraseBlockBBTest (
  IN EFI_HANDLE                   ImageHandle
  ); 
  
//
//Test Cases
//
EFI_STATUS
BBTestEraseBlocksConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

  
EFI_STATUS
BBTestEraseBlocksFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
LocateBlockIoFromEraseBlock (
  IN EFI_ERASE_BLOCK_PROTOCOL              *EraseBlock,
  IN OUT EFI_BLOCK_IO_PROTOCOL             **BlockIo,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib
  );

EFI_STATUS
LocateBlockIo2FromEraseBlock (
  IN EFI_ERASE_BLOCK_PROTOCOL              *EraseBlock,
  IN OUT EFI_BLOCK_IO2_PROTOCOL            **BlockIo2,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib
  );

VOID
NotifyFunction (
  EFI_EVENT    Event,
  VOID         *Context
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

