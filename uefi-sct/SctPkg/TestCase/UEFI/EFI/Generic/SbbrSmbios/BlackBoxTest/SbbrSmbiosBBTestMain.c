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

  SbbrSmbiosBBTestMain.c

Abstract:

  Test driver for SbbrSmbios tests.

--*/

#include "SctLib.h"
#include "SbbrSmbiosBBTestMain.h"
#include "SbbrSmbiosBBTestFunction.h"

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SBBRSMBIOS_TEST_REVISION,
  SBBRSMBIOS_TEST_GUID,
  L"SbbrSmbios Tests",
  L"Checks that SMBIOS on UEFI is implemented correctly."
};

EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    SBBRSMBIOS_UEFISMBIOS_GUID,
    L"UefiSmbios",
    L"Checks that the SMBIOS3 table is accessible though its GUID and that it has the correct memory region settings.",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestUefiSmbiosTest
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
BBTestSbbrSmbiosUnload (
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
InitializeBBTestSbbrSmbios (
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
              BBTestSbbrSmbiosUnload,
              &gBBTestProtocolInterface
              );
}

/**
 * SbbrGetMemoryMap function used by test cases.
 */
EFI_STATUS
SbbrAllocAndGetMemoryMap (
  UINTN                               *MemoryMapSize,
  VOID                                **MemoryMap,
  UINTN                               *MapKey,
  UINTN                               *DescriptorSize,
  UINT32                              *DescriptorVersion
  )
{
  EFI_STATUS                          Status;

  //
  // Getting memory map
  //
  do {
    *MemoryMapSize = 0;
    // First call with a size of 0 so we can find out how big the memory map is.
    Status = gtBS->GetMemoryMap (
                MemoryMapSize,
                *MemoryMap,
                MapKey,
                DescriptorSize,
                DescriptorVersion
                );
    if (Status != EFI_BUFFER_TOO_SMALL){
      return EFI_NOT_FOUND;
    }
    *MemoryMap = SctAllocatePool(*MemoryMapSize);
    if (*MemoryMap == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    // Second call with our newly allocated buffer should work properly.
    Status = gtBS->GetMemoryMap (
                MemoryMapSize,
                *MemoryMap,
                MapKey,
                DescriptorSize,
                DescriptorVersion
                );
    if (EFI_ERROR (Status)) {
      SctFreePool(*MemoryMap);
    }
  } while (EFI_ERROR (Status));

  return EFI_SUCCESS;
}
