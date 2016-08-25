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

  Copyright 2006 - 2016 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2016, ARM Ltd. All rights reserved.

--*/
/*++

Module Name:

  SbbrBootServicesBBTestFunction.c

Abstract:

  Test case function definitions for SbbrBootServices.

--*/

#include "Guid.h"
#include <IndustryStandard/Acpi20.h>
#include <IndustryStandard/SmBios.h>
#include "SbbrBootServicesBBTestMain.h"
#include "SbbrBootServicesBBTestFunction.h"
#include "SctLib.h"

/* Helper Functions */

STATIC
UINT8
SbbrBootServicesByteChecksum (
  IN VOID                 *Data,
  IN UINT32               Length
  )
{
  UINT32 i;
  UINT8 sum = 0;
  UINT8 *Bytes = (UINT8 *)Data;

  for (i = 0; i < Length; i++){
    sum = sum + Bytes[i];
  }

  return sum;
}

STATIC
UINT32
SbbrBootServicesIsRam (
  EFI_MEMORY_DESCRIPTOR *MemoryMapEntry
  )
{
  switch (MemoryMapEntry->Type)
  {
    case EfiLoaderCode:
    case EfiLoaderData:
    case EfiBootServicesCode:
    case EfiBootServicesData:
    case EfiRuntimeServicesCode:
    case EfiRuntimeServicesData:
    case EfiConventionalMemory:
      return TRUE;
    default:
      return FALSE;
  }
}

/**
 *  Entrypoint for MemoryMap Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
BBTestMemoryMapTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  UINTN                               MemoryMapSize;
  VOID                                *MemoryMap;
  EFI_MEMORY_DESCRIPTOR               *MemoryMapDescriptor;
  UINTN                               MapKey;
  UINTN                               DescriptorSize;
  UINT32                              DescriptorVersion;
  UINT32                              i;
  UINT32                              error;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
              SupportHandle,
              &gEfiStandardTestLibraryGuid,
              &StandardLib
              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Getting memory map
  //
  MemoryMapSize = 0;
  Status = gtBS->GetMemoryMap (
              &MemoryMapSize,
              MemoryMap,
              &MapKey,
              &DescriptorSize,
              &DescriptorVersion
              );
  if (Status != EFI_BUFFER_TOO_SMALL){
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion001Guid,
                L"MemoryMap",
                L"%a:%d - MemoryMap Not Found",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }
  MemoryMap = SctAllocatePool(MemoryMapSize);
  if (MemoryMap == 0) {
    return EFI_OUT_OF_RESOURCES;
  }
  Status = gtBS->GetMemoryMap (
              &MemoryMapSize,
              MemoryMap,
              &MapKey,
              &DescriptorSize,
              &DescriptorVersion
              );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion001Guid,
                L"MemoryMap",
                L"%a:%d - MemoryMap Not Found",
                __FILE__,
                __LINE__
                );
    SctFreePool(MemoryMap);
    return EFI_SUCCESS;
  }

  //
  // Looping through each descriptor
  //
  for (i = 0; i < MemoryMapSize / DescriptorSize; i++) {
    MemoryMapDescriptor = (EFI_MEMORY_DESCRIPTOR *)(MemoryMap + (i * DescriptorSize));
    error = FALSE;

    //
    // Checking for identity mapping
    //
    if (MemoryMapDescriptor->PhysicalStart != MemoryMapDescriptor->VirtualStart) {
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gSbbrBootServicesAssertion001Guid,
                  L"MemoryMap",
                  L"%a:%d - MemoryMap 0x%X Not Identity Mapped",
                  __FILE__,
                  __LINE__,
                  MemoryMapDescriptor
                  );
      error = TRUE;
    }

    //
    // Checking attribute
    //
    if (SbbrBootServicesIsRam(MemoryMapDescriptor) == TRUE && !(MemoryMapDescriptor->Attribute & EFI_MEMORY_WB)) {
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gSbbrBootServicesAssertion001Guid,
                  L"MemoryMap",
                  L"%a:%d - MemoryMap 0x%X Attribute Not Supported",
                  __FILE__,
                  __LINE__,
                  MemoryMapDescriptor
                  );
      error = TRUE;
    }

    //
    // Checking for 64KB alignment
    //
    if (MemoryMapDescriptor->PhysicalStart & (SIZE_64KB - 1)) {
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gSbbrBootServicesAssertion001Guid,
                  L"MemoryMap",
                  L"%a:%d - MemoryMap 0x%X Not Aligned to 64KB",
                  __FILE__,
                  __LINE__,
                  MemoryMapDescriptor
                  );
      error = TRUE;
    }

    //
    // No issues found
    //
    if (error == FALSE) {
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_PASSED,
                  gSbbrBootServicesAssertion001Guid,
                  L"MemoryMap 0x%X",
                  L"%a:%d",
                  __FILE__,
                  __LINE__,
                  MemoryMapDescriptor
                  );
    }
  }

  SctFreePool(MemoryMap);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for AcpiTable Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
BBTestAcpiTableTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  UINTN                               IStatus;
  EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER     *AcpiTable;
  UINT8                               Checksum;
  UINT32                              i;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
              SupportHandle,
              &gEfiStandardTestLibraryGuid,
              &StandardLib
              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Looking for ACPI table
  //
  Status = SctGetSystemConfigurationTable (
              &gEfiAcpi20TableGuid,
              &AcpiTable
              );
  if (EFI_ERROR (Status)){
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion002Guid,
                L"AcpiTable",
                L"%a:%d - ACPI Table Not Found",
                __FILE__,
                __LINE__
                );
  }

  //
  // Checking ACPI table signature
  //
  IStatus = SctCompareMem (
              &AcpiTable->Signature,
              RSDP_SIGNATURE_STRING,
              sizeof(RSDP_SIGNATURE_STRING) - 1
              );
  if (IStatus != 0) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion002Guid,
                L"AcpiTable",
                L"%a:%d - ACPI Table Invalid Signature",
                __FILE__,
                __LINE__
                );
  }

  //
  // Checking ACPI table checksum
  //
  Checksum = SbbrBootServicesByteChecksum (AcpiTable, ACPI_TABLE_CHECKSUM_LENGTH);
  if (Checksum != 0) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion002Guid,
                L"AcpiTable",
                L"%a:%d - ACPI Table Invalid Checksum",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }

  //
  // Checking ACPI table extended checksum
  //
  Checksum = SbbrBootServicesByteChecksum (AcpiTable, AcpiTable->Length);
  if (Checksum != 0) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion002Guid,
                L"AcpiTable",
                L"%a:%d - ACPI Table Invalid Extended Checksum",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }

  //
  // Checking ACPI table length
  //
  if (AcpiTable->Length != ACPI_TABLE_EXPECTED_LENGTH) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion002Guid,
                L"AcpiTable",
                L"%a:%d - ACPI Table Invalid Length",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }

  //
  // Checking ACPI table XSDT address
  //
  if (AcpiTable->XsdtAddress == 0) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion002Guid,
                L"AcpiTable",
                L"%a:%d - ACPI Table Invalid XSDT Pointer",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }

  StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_PASSED,
                gSbbrBootServicesAssertion002Guid,
                L"AcpiTable",
                L"%a:%d",
                __FILE__,
                __LINE__
                );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for SmbiosTable Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
BBTestSmbiosTableTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  INTN                                IStatus;
  SMBIOS_TABLE_3_0_ENTRY_POINT        *SmbiosTable;
  UINT8                               Checksum;
  UINT32                              i;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
              SupportHandle,
              &gEfiStandardTestLibraryGuid,
              &StandardLib
              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Looking for SMBIOS table
  //
  Status = SctGetSystemConfigurationTable (
              &gEfiSmbios3TableGuid,
              &SmbiosTable
              );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion003Guid,
                L"SmbiosTable",
                L"%a:%d - SMBIOS Table Not Found",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }

  //
  // Checking SMBIOS Anchor String
  //
  IStatus = SctCompareMem (
              SmbiosTable->AnchorString,
              SMBIOS30_ANCHOR_STRING,
              sizeof(SMBIOS30_ANCHOR_STRING) - 1
              );
  if (IStatus != 0) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion003Guid,
                L"SmbiosTable",
                L"%a:%d - SMBIOS Table Anchor String Not Found",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }

  //
  // Checking entry point revision
  //
  if (SmbiosTable->EntryPointRevision != 1) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion003Guid,
                L"SmbiosTable",
                L"%a:%d - SMBIOS Table Invalid Entry Point Revision",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }

  //
  // Checking entry point checksum
  //
  Checksum = SbbrBootServicesByteChecksum (SmbiosTable, SmbiosTable->EntryPointLength);
  if (Checksum != 0) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrBootServicesAssertion003Guid,
                L"SmbiosTable",
                L"%a:%d - SMBIOS Table Invalid Checksum",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }

  StandardLib->RecordAssertion (
              StandardLib,
              EFI_TEST_ASSERTION_PASSED,
              gSbbrBootServicesAssertion003Guid,
              L"SmbiosTable",
              L"%a:%d",
              __FILE__,
              __LINE__
              );

  return EFI_SUCCESS;
}
