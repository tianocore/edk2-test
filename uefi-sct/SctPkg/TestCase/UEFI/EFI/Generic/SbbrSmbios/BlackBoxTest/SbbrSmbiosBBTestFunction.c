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

  Copyright (c) 2016, ARM LTD. All rights reserved.

--*/
/*++

Module Name:

  SbbrSmbiosBBTestFunction.c

Abstract:

  Test case function definitions for SbbrSmbios.

--*/

#include "SbbrSmbiosBBTestMain.h"
#include "SbbrSmbiosBBTestFunction.h"
#include "SctLib.h"
#include "Guid.h"
#include <IndustryStandard/SmBios.h>
#include <Library/EfiTestLib.h>

/**
 *  Entrypoint for UefiSmbios Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
BBTestUefiSmbiosTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  SMBIOS_TABLE_3_0_ENTRY_POINT        *SmbiosTable;
  UINTN                               MemoryMapSize;
  VOID                                *MemoryMap;
  EFI_MEMORY_DESCRIPTOR               *MemoryMapDescriptor;
  UINTN                               MapKey;
  UINTN                               DescriptorSize;
  UINT32                              DescriptorVersion;
  UINT32                              i;
  UINT64                              EndAddress;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Looking for SMBIOS table
  //
  Status = SctGetSystemConfigurationTable (
              &gEfiSmbios3TableGuid,
              (VOID **)&SmbiosTable
              );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrSmbiosAssertion001Guid,
                L"UefiSmbios",
                L"%a:%d - SMBIOS30 Table Not Found",
                __FILE__,
                __LINE__
                );
    return EFI_SUCCESS;
  }

  //
  // Checking SMBIOS table version
  //
  if (SmbiosTable->MajorVersion != SBBRSMBIOS_MAJOR_VERSION) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gSbbrSmbiosAssertion001Guid,
                L"UefiSmbios",
                L"%a:%d - SMBIOS30 table invalid version. %d",
                __FILE__,
                __LINE__,
                SmbiosTable->MajorVersion
                );
    return EFI_SUCCESS;
  }

  //
  // Getting Memory Map
  //
  Status = SbbrAllocAndGetMemoryMap (
              &MemoryMapSize,
              &MemoryMap,
              &MapKey,
              &DescriptorSize,
              &DescriptorVersion
              );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                StandardLib,
                EFI_TEST_ASSERTION_FAILED,
                gTestGenericFailureGuid,
                L"MemoryMap",
                L"%a:%d - Could not retrieve memory map. 0x%X",
                __FILE__,
                __LINE__,
                Status
                );
    return EFI_NOT_FOUND;
  }

  //
  // Looping through memory map descriptors to find the one containing SMBIOS table
  //
  for (i = 0; i < MemoryMapSize / DescriptorSize; i++) {
    MemoryMapDescriptor = (EFI_MEMORY_DESCRIPTOR *)(MemoryMap + (i * DescriptorSize));
    EndAddress = MemoryMapDescriptor->PhysicalStart + (MemoryMapDescriptor->NumberOfPages * EFI_PAGE_SIZE);
    if ( (SmbiosTable->TableAddress >= MemoryMapDescriptor->PhysicalStart) &&
         ((SmbiosTable->TableAddress + SmbiosTable->TableMaximumSize) < EndAddress))
    {
      //
      // Memory region containing SMBIOS table found
      //
      if (MemoryMapDescriptor->Type != EfiRuntimeServicesData) {
        StandardLib->RecordAssertion (
                    StandardLib,
                    EFI_TEST_ASSERTION_FAILED,
                    gSbbrSmbiosAssertion001Guid,
                    L"UefiSmbios",
                    L"%a:%d - Wrong SMBIOS30 Memory Type. 0x%X",
                    __FILE__,
                    __LINE__,
                    MemoryMapDescriptor->Type
                    );
      } else {
        StandardLib->RecordAssertion (
                    StandardLib,
                    EFI_TEST_ASSERTION_PASSED,
                    gSbbrSmbiosAssertion001Guid,
                    L"UefiSmbios",
                    L"%a:%d",
                    __FILE__,
                    __LINE__
                    );
      }

      SctFreePool(MemoryMap);
      return EFI_SUCCESS;
    }

  }

  //
  // Memory region not found.
  //
  StandardLib->RecordAssertion (
              StandardLib,
              EFI_TEST_ASSERTION_FAILED,
              gSbbrSmbiosAssertion001Guid,
              L"UefiSmbios",
              L"%a:%d - Memory region not found in map.",
              __FILE__,
              __LINE__
              );
  SctFreePool(MemoryMap);
  return EFI_SUCCESS;
}
