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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    AcpiTableProtocolBBTestFunction.c

Abstract:
    for EFI Driver Acpi Table Protocol's function Test

--*/
#include "SctLib.h"
#include "AcpiTableProtocolBBTestMain.h"

#define EFI_ACPI_TABLE_GUID \
  { 0x8868e871, 0xe4f1, 0x11d3, 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 }

#define ACPI_10_TABLE_GUID \
  { 0xeb9d2d30, 0x2d88, 0x11d3, 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d }

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
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BBTestInstallAcpiTableFunctionTestCheckpoint1 (StandardLib, AcpiTable);
  
  return EFI_SUCCESS;
}


EFI_STATUS
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
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BBTestUninstallAcpiTableFunctionTestCheckpoint1 (StandardLib, AcpiTable);
  
  return EFI_SUCCESS;
}


EFI_STATUS
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

      RSDT = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)(RSDP->RSDTAddress);
      NumberOfTableEntries = (RSDT->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER))/sizeof(UINT32);

      RSDTTable = FALSE;

      for (Index = 0; Index < NumberOfTableEntries; Index++) {
        LinkedTable = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)*(UINT32 *)((UINTN)RSDT + sizeof(EFI_ACPI_DESCRIPTION_HEADER) + Index * sizeof(UINT32));
        if (((EFI_ACPI_DESCRIPTION_HEADER *) LinkedTable)->Signature == UEFI_SCTT_TABLE_SIGNATURE) {
          RSDTTable = TRUE;
          break;
        }  
        LinkedTable = NULL;
      }

      if (LinkedTable == NULL) {
        XSDT = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN)(RSDP->XSDTAddress);
        NumberOfTableEntries = (XSDT->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER))/sizeof(UINT64);

        for (Index = 0; Index < NumberOfTableEntries; Index++) {
          SctCopyMem (&Address, (UINT64 *)((UINTN)XSDT + sizeof(EFI_ACPI_DESCRIPTION_HEADER) + Index * sizeof(UINT64)), sizeof(UINT64));
          LinkedTable = (EFI_ACPI_DESCRIPTION_HEADER*)(UINTN)Address;
          if (((EFI_ACPI_DESCRIPTION_HEADER *) LinkedTable)->Signature == UEFI_SCTT_TABLE_SIGNATURE)
            break;
          LinkedTable = NULL;
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
