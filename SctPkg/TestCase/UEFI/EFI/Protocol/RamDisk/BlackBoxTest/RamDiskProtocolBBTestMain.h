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
                                                                
  Copyright 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  RamDiskProtocolBBTestMain.h

Abstract:

  Test Driver of RamDisk Protocol header file

--*/

#ifndef _RAM_DISK_PROTOCOL_BB_TEST_MAIN_H
#define _RAM_DISK_PROTOCOL_BB_TEST_MAIN_H

#include <Efi.h>
#include <Library/EfiTestLib.h>
#include <SctLib.h>
#include "Guid.h"
#include <UEFI/Protocol/RamDisk.h>

#define EFI_RAM_DISK_PROTOCOL_TEST_REVISION    0x00010000

//
// Entry GUIDs for Func and Conf Test
//
#define EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x7a825f36, 0x6042, 0x423e, { 0xa4, 0x66, 0x62, 0xd1, 0xf9, 0x10, 0xe4, 0x59 } }

#define EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0xba0988ad, 0x6dcc, 0x49a5, { 0xb3, 0x1b, 0xe1, 0xf2, 0xb6, 0x6a, 0xc8, 0xdd } }

#define EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xdd819f83, 0xe040, 0x4ff7, { 0xab, 0x84, 0x62, 0xa, 0xad, 0x70, 0x3f, 0x48 } }

#define EFI_RAM_DISK_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x60505491, 0xc8a6, 0x4194, { 0xab, 0xb5, 0x31, 0xa1, 0xf7, 0xd3, 0x4e, 0xad } }


EFI_STATUS
InitializeBBTestRamDiskProtocol (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
UnloadBBTestRamDiskProtocol (
  IN EFI_HANDLE                   ImageHandle
  );

//
// Prototypes: Test Cases
//
EFI_STATUS
BBTestRegisterRamDiskFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
  
EFI_STATUS
BBTestUnregisterRamDiskFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
BBTestRegisterRamDiskConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
  
EFI_STATUS
BBTestUnregisterRamDiskConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  ); 

#endif
