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

  ExeModeBBTest.h

Abstract:

  BB test header file for UEFI processor execution mode

--*/

#ifndef _EXE_MODE_BBTEST_H
#define _EXE_MODE_BBTEST_H


#include "Efi.h"
#include "EfiTest.h"
#include <Library/EfiTestLib.h>
#include "guid.h"

#define EXE_MODE_TEST_REVISION 0x00010000

#define FPU_CONTROL_WORD_VALUE_IA32 0x027F
#define FPU_CONTROL_WORD_VALUE_X64  0x037F
#define MX_CSR_VALUE  0x1F80

// {F736C316-1327-4ea5-AD40-029EEA4B06E3}
#define EFI_EXE_MODE_TEST_GUID \
{ 0xf736c316, 0x1327, 0x4ea5, { 0xad, 0x40, 0x2, 0x9e, 0xea, 0x4b, 0x6, 0xe3 } }


//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Basic Test
//
#define EXE_MODE_TEST_ENTRY_GUID0101 \
 {0x8bdf3c09, 0xdd56, 0x493a, {0x88, 0x37, 0xb5, 0xba, 0xb, 0x8, 0x90, 0xc8} }

#define EXE_MODE_TEST_ENTRY_GUID0102 \
 {0xA593c98e, 0x3eb5, 0x491b, {0x9f, 0xd6, 0x6, 0x63, 0x97, 0x2d, 0xfa, 0x18} }



//
// functions
//

EFI_STATUS
InitializeBBTestExeMode (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );
  
EFI_STATUS
BBTestExeModeUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Basic test functions
//

//
// TDS 3.1
//
EFI_STATUS
BBTestFpuControlWordTest (
    IN EFI_BB_TEST_PROTOCOL       *This, 
    IN VOID                       *ClientInterface,    
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );
  
//
// TDS 3.2
//
EFI_STATUS
BBTestMxCsrTest (
    IN EFI_BB_TEST_PROTOCOL       *This, 
    IN VOID                       *ClientInterface,    
    IN EFI_TEST_LEVEL             TestLevel,
    IN EFI_HANDLE                 SupportHandle
  );


//
// Some internal functions
//

EFI_STATUS
GetFpuControlWord (
  OUT  UINT16  *Reg              
  );

EFI_STATUS
GetMxCsr (
  OUT  UINT32  *Reg              
  );

#endif
