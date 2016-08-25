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

  SbbrBootServicesBBTestMain.c

Abstract:

  Test driver for SbbrBootServices tests.

--*/

#include "SctLib.h"
#include "SbbrBootServicesBBTestMain.h"
#include "SbbrBootServicesBBTestFunction.h"

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SBBRBOOTSERVICES_TEST_REVISION,
  SBBRBOOTSERVICES_TEST_GUID,
  L"SbbrBootServices Tests",
  L"Tests SBBR boot services requirements."
};

EFI_GUID gSupportProtocolGuid[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    SBBRBOOTSERVICES_MEMORYMAP_GUID,
    L"MemoryMap",
    L"Checks memory map provided by UEFI.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestMemoryMapTest
  },
  {
    SBBRBOOTSERVICES_SMBIOSTABLE_GUID,
    L"SmbiosTable",
    L"Checks that SMBIOS3 table is provided by UEFI.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSmbiosTableTest
  },
  {
    SBBRBOOTSERVICES_ACPITABLE_GUID,
    L"AcpiTable",
    L"Checks that ACPI table is provided by UEFI.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestAcpiTableTest
  },
  EFI_NULL_GUID
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

/**
 *  The driver's Unload function
 *  @param  ImageHandle The test driver image handle
 *  @return EFI_SUCCESS Indicates the interface was Uninstalled
*/
EFI_STATUS
BBTestSbbrBootServicesUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

/**
 *  Creates/installs the BlackBox Interface and eminating Entry Point
 *  node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 */
EFI_STATUS
InitializeBBTestSbbrBootServices (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{

  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestSbbrBootServicesUnload,
           &gBBTestProtocolInterface
           );
}
