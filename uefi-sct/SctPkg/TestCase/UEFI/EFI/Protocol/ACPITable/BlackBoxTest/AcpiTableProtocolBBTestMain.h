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
EFIAPI
InitializeBBTestAcpiTableProtocol (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
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
EFIAPI
BBTestInstallAcpiTableConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
  
EFI_STATUS
EFIAPI
BBTestUninstallAcpiTableConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  ); 
  
  
EFI_STATUS
EFIAPI
BBTestInstallAcpiTableFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
  
EFI_STATUS
EFIAPI
BBTestUninstallAcpiTableFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  ); 

  
EFI_STATUS
EFIAPI
BBTestInstallAcpiTableConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );
  

EFI_STATUS
EFIAPI
BBTestInstallAcpiTableConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );


EFI_STATUS
EFIAPI
BBTestInstallAcpiTableConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );


EFI_STATUS
EFIAPI
BBTestUninstallAcpiTableConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );
  
  
EFI_STATUS
EFIAPI
BBTestInstallAcpiTableFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );
  
  
EFI_STATUS
EFIAPI
BBTestUninstallAcpiTableFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  );
  
  
#endif
