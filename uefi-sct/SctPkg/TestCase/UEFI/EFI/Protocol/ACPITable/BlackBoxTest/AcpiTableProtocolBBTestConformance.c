/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    AcpiTableProtocolBBTestConformance.c

Abstract:
    for EFI Driver Acpi Table Protocol's Conformance Test

--*/
#include "SctLib.h"
#include "AcpiTableProtocolBBTestMain.h"


EFI_STATUS
EFIAPI
BBTestInstallAcpiTableConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ACPI_TABLE_PROTOCOL          		*AcpiTable;

  //
  // init
  //
  AcpiTable = (EFI_ACPI_TABLE_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BBTestInstallAcpiTableConformanceTestCheckpoint1 (StandardLib, AcpiTable);

  BBTestInstallAcpiTableConformanceTestCheckpoint2 (StandardLib, AcpiTable);

  BBTestInstallAcpiTableConformanceTestCheckpoint3 (StandardLib, AcpiTable);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestUninstallAcpiTableConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ACPI_TABLE_PROTOCOL          		*AcpiTable;

  //
  // init
  //
  AcpiTable = (EFI_ACPI_TABLE_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BBTestUninstallAcpiTableConformanceTestCheckpoint1 (StandardLib, AcpiTable);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestInstallAcpiTableConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL               *AcpiTable
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  UINTN                                       AcpiTableBufferSize;
  UINTN                                       TableKey;

  //
  // with AcpiTableBuffer being NULL.
  //
  AcpiTableBufferSize = 128;
  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        NULL,
                        AcpiTableBufferSize,
                        &TableKey
                        );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gInstallAcpiTableBBTestConformanceAssertionGuid001,
                 L"ACPI_TABLE_PROTOCOL.InstallAcpiTable - InstallAcpiTable() returns EFI_INVALID_PARAMETER with NULL AcpiTableBuffer.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestInstallAcpiTableConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  VOID                                        *AcpiTableBuffer;
  UINTN                                       AcpiTableBufferSize;

  //
  // with TableKey being NULL.
  //
  AcpiTableBufferSize = 128;
  AcpiTableBuffer = (CHAR8 *) SctAllocateZeroPool (AcpiTableBufferSize);
  if( !AcpiTableBuffer )
	return EFI_OUT_OF_RESOURCES;

  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Length = (UINT32) AcpiTableBufferSize;

  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Checksum = TestCalculateCheckSum8((UINT8 *)AcpiTableBuffer, AcpiTableBufferSize);
  
  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        AcpiTableBuffer,
                        AcpiTableBufferSize,
                        NULL
                        );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gInstallAcpiTableBBTestConformanceAssertionGuid002,
                 L"ACPI_TABLE_PROTOCOL.InstallAcpiTable - InstallAcpiTable() returns EFI_INVALID_PARAMETER with NULL TableKey.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
 
  gtBS->FreePool (AcpiTableBuffer);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestInstallAcpiTableConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  VOID                                        *AcpiTableBuffer;
  UINTN                                       AcpiTableBufferSize;
  UINTN                                       TableKey;
  //
  // with AcpiTableBufferSize if different with the size field in AcpiTableBuffer.
  //
  AcpiTableBufferSize = 128;
  AcpiTableBuffer = (CHAR8 *) SctAllocateZeroPool (AcpiTableBufferSize-1);
  if( !AcpiTableBuffer )
	return EFI_OUT_OF_RESOURCES;
 
  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Length = (UINT32) (AcpiTableBufferSize-1);

  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Checksum = TestCalculateCheckSum8((UINT8 *)AcpiTableBuffer, AcpiTableBufferSize);
  
  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        AcpiTableBuffer,
                        AcpiTableBufferSize,
                        &TableKey
                        );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gInstallAcpiTableBBTestConformanceAssertionGuid003,
                 L"ACPI_TABLE_PROTOCOL.InstallAcpiTable - InstallAcpiTable() returns EFI_INVALID_PARAMETER with  AcpiTableBufferSize is different with the size field in AcpiTableBuffer.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (AcpiTableBuffer);
 
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUninstallAcpiTableConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL          *AcpiTable
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  VOID                                        *AcpiTableBuffer;
  UINTN                                       AcpiTableBufferSize;
  UINTN                                       TableKey;

  //
  // with TableKey not refer to a table entry.
  //
  AcpiTableBufferSize = 128;
  AcpiTableBuffer = (CHAR8 *) SctAllocateZeroPool (AcpiTableBufferSize);
  if( !AcpiTableBuffer )
	return EFI_OUT_OF_RESOURCES;

  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Length = (UINT32) AcpiTableBufferSize;

  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Checksum = TestCalculateCheckSum8((UINT8 *)AcpiTableBuffer, AcpiTableBufferSize);

  //
  //Install a Acpi table, to get a valid TableKey
  //
  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        AcpiTableBuffer,
                        AcpiTableBufferSize,
                        &TableKey
                        );
  if( EFI_ERROR(Status) ) {
	gtBS->FreePool (AcpiTableBuffer);
	return Status;
  }

  //
  //Uninstall the Acpi table, to make the TableKey invalid ( not refer to any table entry )
  //
  Status = AcpiTable->UninstallAcpiTable (
                        AcpiTable,
                        TableKey
                        );
  if( EFI_ERROR(Status) ) {
    gtBS->FreePool (AcpiTableBuffer);
	return Status;
  }  
  
  //
  //with TableKey not refer to any table entry
  //
  Status = AcpiTable->UninstallAcpiTable (
                        AcpiTable,
                        TableKey
                        );
  
  if (EFI_NOT_FOUND == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gInstallAcpiTableBBTestConformanceAssertionGuid004,
                 L"ACPI_TABLE_PROTOCOL.UninstallAcpiTable - UninstallAcpiTable() returns EFI_NOT_FOUND with TableKey not refer to a table entry.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
 
  gtBS->FreePool (AcpiTableBuffer);

  return EFI_SUCCESS;
}
