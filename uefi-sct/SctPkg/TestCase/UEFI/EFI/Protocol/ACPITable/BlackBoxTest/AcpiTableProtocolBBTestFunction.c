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
    AcpiTableProtocolBBTestFunction.c

Abstract:
    for EFI Driver Acpi Table Protocol's function Test

--*/
#include "SctLib.h"
#include "AcpiTableProtocolBBTestMain.h"

#define EFI_ACPI_TABLE_GUID \
  { 0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 }}

#define ACPI_10_TABLE_GUID \
  { 0xeb9d2d30, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d }}

EFI_GUID gAcpiTableGuid = EFI_ACPI_TABLE_GUID;

EFI_GUID gAcpi10TableGuid = ACPI_10_TABLE_GUID;

typedef struct {
  UINT64  Signature;
  UINT8   Checksum;
  UINT8   OemId[6];
  UINT8   Revision;
  UINT32  RSDTAddress;
  UINT32  Length;
  UINT64  XSDTAddress;
  UINT8   ExtChecksum;
  UINT8   Reserve[3];
} EFI_ACPI_RSDP;

EFI_STATUS
EFIAPI
BBTestInstallAcpiTableFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ACPI_TABLE_PROTOCOL               *AcpiTable;

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

  BBTestInstallAcpiTableFunctionTestCheckpoint1 (StandardLib, AcpiTable);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestUninstallAcpiTableFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ACPI_TABLE_PROTOCOL               *AcpiTable;

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

  BBTestUninstallAcpiTableFunctionTestCheckpoint1 (StandardLib, AcpiTable);
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestInstallAcpiTableFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL               *AcpiTable
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  VOID                                        *AcpiTableBuffer = NULL;
  UINTN                                       AcpiTableBufferSize;
  UINTN                                       TableKey;
  UINT8                                       AcpiCheckSum;
  UINT8                                       CheckSum;
  BOOLEAN                                     RSDTTable;

  EFI_CONFIGURATION_TABLE                     *ConfigurationTable = NULL;
  UINTN                                       NumberOfTableEntries;
  UINTN                                       Index;
  EFI_ACPI_RSDP                               *RSDP;
  EFI_ACPI_DESCRIPTION_HEADER                 *RSDT;
  EFI_ACPI_DESCRIPTION_HEADER                 *XSDT;
  UINT64                                      Address;
  EFI_ACPI_DESCRIPTION_HEADER                 *LinkedTable = NULL;

  UINT8 AcpiCheckSum1;
  
  //
  // with correct AcpiTable data.
  //
  AcpiTableBufferSize = 128;
  AcpiTableBuffer = (CHAR8 *) SctAllocateZeroPool (AcpiTableBufferSize);
  if( !AcpiTableBuffer )
    return EFI_OUT_OF_RESOURCES;

  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Signature = UEFI_SCTT_TABLE_SIGNATURE;
  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Length    = (UINT32) AcpiTableBufferSize;

  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Checksum = TestCalculateCheckSum8((UINT8 *)AcpiTableBuffer, AcpiTableBufferSize);
  
  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        AcpiTableBuffer,
                        AcpiTableBufferSize,
                        &TableKey
                        );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gInstallAcpiTableBBTestFunctionAssertionGuid001,
                 L"ACPI_TABLE_PROTOCOL.InstallAcpiTable - InstallAcpiTable() returns EFI_SUCCESS with valid parameters.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_SUCCESS == Status) {
    Status = AcpiTable->UninstallAcpiTable (
                          AcpiTable,
                          TableKey
                          );
    if(EFI_ERROR(Status))
      goto EXIT;
  }

  //
  // call InstallAcpiTable with AcpiTable with wrong checksum
  //
  AcpiCheckSum = ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Checksum;

  ((EFI_ACPI_DESCRIPTION_HEADER *) AcpiTableBuffer)->Checksum++;

  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        AcpiTableBuffer,
                        AcpiTableBufferSize,
                        &TableKey
                        );
  
  if (EFI_SUCCESS == Status) { 
    ConfigurationTable   = gtST->ConfigurationTable;
    NumberOfTableEntries = gtST->NumberOfTableEntries;

    for (Index = 0; Index < NumberOfTableEntries; Index++) {
      if (SctCompareGuid (&(ConfigurationTable->VendorGuid), &gAcpiTableGuid) == 0) {
        break;
      }
      ConfigurationTable++;
    }

    if (Index == NumberOfTableEntries) {
      for (Index = 0; Index < NumberOfTableEntries; Index++) {
        if (SctCompareGuid (&(ConfigurationTable->VendorGuid), &gAcpi10TableGuid) == 0) {
          break;
        }
        ConfigurationTable++;
      }
    }
    
    if (Index == NumberOfTableEntries) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      RSDP = (EFI_ACPI_RSDP *)ConfigurationTable->VendorTable;

      RSDTTable = FALSE;

      RSDT = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)(RSDP->RSDTAddress);
      if (RSDT != NULL) {	  
        NumberOfTableEntries = (RSDT->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER))/sizeof(UINT32);

        for (Index = 0; Index < NumberOfTableEntries; Index++) {
          LinkedTable = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)*(UINT32 *)((UINTN)RSDT + sizeof(EFI_ACPI_DESCRIPTION_HEADER) + Index * sizeof(UINT32));
          if (((EFI_ACPI_DESCRIPTION_HEADER *) LinkedTable)->Signature == UEFI_SCTT_TABLE_SIGNATURE) {
            RSDTTable = TRUE;
            break;
          }  
          LinkedTable = NULL;
        }
      }
      if (LinkedTable == NULL) {
        XSDT = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)(RSDP->XSDTAddress);

        if (XSDT != NULL) {		
          NumberOfTableEntries = (XSDT->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER))/sizeof(UINT64);

          for (Index = 0; Index < NumberOfTableEntries; Index++) {
            SctCopyMem (&Address, (UINT64 *)((UINTN)XSDT + sizeof(EFI_ACPI_DESCRIPTION_HEADER) + Index * sizeof(UINT64)), sizeof(UINT64));
            LinkedTable = (EFI_ACPI_DESCRIPTION_HEADER*)(UINTN)Address;
            if (((EFI_ACPI_DESCRIPTION_HEADER *) LinkedTable)->Signature == UEFI_SCTT_TABLE_SIGNATURE)
              break;
            LinkedTable = NULL;
          }
        }
      }

      if (LinkedTable != NULL) {
        AcpiCheckSum = ((EFI_ACPI_DESCRIPTION_HEADER *) LinkedTable)->Checksum;
        ((EFI_ACPI_DESCRIPTION_HEADER *) LinkedTable)->Checksum = 0;
        AcpiCheckSum1 = TestCalculateCheckSum8((UINT8 *) LinkedTable, ((EFI_ACPI_DESCRIPTION_HEADER *) LinkedTable)->Length);
        ((EFI_ACPI_DESCRIPTION_HEADER *) LinkedTable)->Checksum = AcpiCheckSum;

        if (((EFI_ACPI_DESCRIPTION_HEADER *) LinkedTable)->Checksum == AcpiCheckSum1) {
          if (RSDTTable == TRUE) {
            CheckSum       = RSDT->Checksum;
            RSDT->Checksum = 0;
            if (CheckSum == TestCalculateCheckSum8((UINT8 *)RSDT, RSDT->Length)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            RSDT->Checksum = CheckSum;
          } else {
            XSDT           = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)(RSDP->XSDTAddress);
            CheckSum       = XSDT->Checksum;
            XSDT->Checksum = 0;
            if (CheckSum == TestCalculateCheckSum8((UINT8 *)XSDT, XSDT->Length)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
            XSDT->Checksum = CheckSum;
          }
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gInstallAcpiTableBBTestFunctionAssertionGuid002,
                 L"ACPI_TABLE_PROTOCOL.InstallAcpiTable - InstallAcpiTable() returns EFI_SUCCESS & automatically correct AcpiTable checksum.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_SUCCESS == Status) {
    Status = AcpiTable->UninstallAcpiTable (
                          AcpiTable,
                          TableKey
                          );
    if(EFI_ERROR(Status))
      goto EXIT;
  }
  
EXIT:

  gtBS->FreePool (AcpiTableBuffer);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestUninstallAcpiTableFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ACPI_TABLE_PROTOCOL               *AcpiTable
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
  //with TableKey refer to a table entry
  //
  Status = AcpiTable->UninstallAcpiTable (
                        AcpiTable,
                        TableKey
                        );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUninstallAcpiTableBBTestFunctionAssertionGuid001,
                 L"ACPI_TABLE_PROTOCOL.UninstallAcpiTable - UninstallAcpiTable() returns EFI_SUCCESS with TableKey refer to a table entry.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
 
  gtBS->FreePool (AcpiTableBuffer);

  return EFI_SUCCESS;
}
