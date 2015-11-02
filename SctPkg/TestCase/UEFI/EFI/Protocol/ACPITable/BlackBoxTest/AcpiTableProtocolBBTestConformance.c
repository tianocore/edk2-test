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
    AcpiTableProtocolBBTestConformance.c

Abstract:
    for EFI Driver Acpi Table Protocol's Conformance Test

--*/
#include "SctLib.h"
#include "AcpiTableProtocolBBTestMain.h"


EFI_STATUS
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
                   &StandardLib
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
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BBTestUninstallAcpiTableConformanceTestCheckpoint1 (StandardLib, AcpiTable);
  
  return EFI_SUCCESS;
}


EFI_STATUS
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
