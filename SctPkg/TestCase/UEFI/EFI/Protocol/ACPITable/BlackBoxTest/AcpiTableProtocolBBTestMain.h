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

  AcpiTableBBTestMain.h

Abstract:

  Test Driver of Acpi Table Protocol header file

--*/

#ifndef _ACPI_TABLE_PROTOCOL_BB_TEST_MAIN_H
#define _ACPI_TABLE_PROTOCOL_BB_TEST_MAIN_H


#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/AcpiTable.h>
#include "Guid.h"



#define EFI_ACPI_TABLE_PROTOCOL_TEST_REVISION    0x00010000

//
// One private signature
//
#define UEFI_SCTT_TABLE_SIGNATURE    EFI_SIGNATURE_32 ('S', 'C', 'T', 'T')

//
// Entry GUIDs for Func Test
//

//
// Entry GUIDs for Conf Test
//
#define EFI_ACPI_TABLE_PROTOCOL_TEST_ENTRY_GUID0201 \
{0x9689be8f, 0x13e4, 0x4705, { 0xbd, 0xb8, 0xe1, 0x92, 0x94, 0x3b, 0xbf, 0x92 } }

#define EFI_ACPI_TABLE_PROTOCOL_TEST_ENTRY_GUID0202 \
{0x67a7dbd, 0xdb96, 0x426b, { 0x9f, 0x16, 0xed, 0xdf, 0x0, 0xa3, 0xb4, 0x75 } }

#define EFI_ACPI_TABLE_PROTOCOL_TEST_ENTRY_GUID0101 \
{0x9c0b1a63, 0x33b8, 0x4a79, { 0xa8, 0xf6, 0x73, 0x4f, 0xaf, 0xe4, 0x25, 0x33 } }


#define EFI_ACPI_TABLE_PROTOCOL_TEST_ENTRY_GUID0102 \
{0x10f71445, 0xeba2, 0x4421, { 0x8d, 0xf2, 0x90, 0xc4, 0x2f, 0x6d, 0xc8, 0x23 } }


EFI_STATUS
InitializeBBTestAcpiTableProtocol (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
UnloadBBTestAcpiTableProtocol (
  IN EFI_HANDLE                   ImageHandle
  );

UINT8
EFIAPI
TestCalculateCheckSum8 (
  IN      CONST UINT8                *Buffer,
  IN      UINTN                      Length
  );

//
// Prototypes: Test Cases
//

EFI_STATUS
BBTestInstallAcpiTableConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
  
EFI_STATUS
BBTestUninstallAcpiTableConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  ); 
  
  
EFI_STATUS
BBTestInstallAcpiTableFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
  
EFI_STATUS
BBTestUninstallAcpiTableFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  ); 

  
EFI_STATUS
BBTestInstallAcpiTableConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );
  

EFI_STATUS
BBTestInstallAcpiTableConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );


EFI_STATUS
BBTestInstallAcpiTableConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );


EFI_STATUS
BBTestUninstallAcpiTableConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );
  
  
EFI_STATUS
BBTestInstallAcpiTableFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );
  
  
EFI_STATUS
BBTestUninstallAcpiTableFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );
  
  
#endif
