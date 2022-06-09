/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
#include "Guid.h"

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
EFIAPI
InitializeBBTestExeMode (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );
  
EFI_STATUS
EFIAPI
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
EFIAPI
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
EFIAPI
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
