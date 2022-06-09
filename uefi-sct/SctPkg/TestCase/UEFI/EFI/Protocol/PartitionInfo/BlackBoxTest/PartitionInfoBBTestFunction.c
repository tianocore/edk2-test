/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

    PartitionInfoBBTestFunction.c

Abstract:

    for EFI Driver Partition Info Protocol's Function Test

--*/

#include "PartitionInfoBBTestMain.h"

EFI_GUID gPartitionInfoEFIUnusedEntryGuid                  = EFI_UNUSED_ENTRY_GUID;
EFI_GUID gPartitionInfoEFISystemPartitionGuid              = EFI_SYSTEM_PARTITION_GUID;
EFI_GUID gPartitionInfoEFIPartitionContainingLegacyMBRGuid = EFI_PARTITION_CONTAINING_LEGACY_MBR_GUID;

EFI_STATUS
EFIAPI
BBTestPartitionInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_PARTITION_INFO_PROTOCOL           *PartitionInfo;
  EFI_TEST_ASSERTION                    AssertionType;
  
  PartitionInfo = (EFI_PARTITION_INFO_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  
  if ((PartitionInfo->Revision != EFI_PARTITION_INFO_PROTOCOL_REVISION) || 
    ((PartitionInfo->Type != PARTITION_TYPE_OTHER) && (PartitionInfo->Type != PARTITION_TYPE_MBR) && (PartitionInfo->Type != PARTITION_TYPE_GPT)) ||
    ((PartitionInfo->System != 0) && (PartitionInfo->System != 1))) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPartitionInfoBBTestFunctionAssertionGuid001,
                   L"PartitionInfo - Revision, Type, System test",
                   L"%a:%d:Revision - 0x%08x, Info - %d, System - %d\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   PartitionInfo->Revision,
                   PartitionInfo->Type,
                   PartitionInfo->System
                   );
  
  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    if (PartitionInfo->Type == PARTITION_TYPE_MBR) {
      if (PartitionInfo->Info.Mbr.OSIndicator == 0xEF) {
        if ((PartitionInfo->System != 1))
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        else
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gPartitionInfoBBTestFunctionAssertionGuid003,
                         L"PartitionInfo - Mbr.OSIndicator should be aligned with PartitionInfo->System",
                         L"%a:%d:Mbr.OSIndicator - %d, System - %d\n",
                         __FILE__,
                         (UINTN)__LINE__,
                         PartitionInfo->Info.Mbr.OSIndicator,
                         PartitionInfo->System
                         );
      }
    }
    if (PartitionInfo->Type == PARTITION_TYPE_GPT) {
      if (!GuidCmp(PartitionInfo->Info.Gpt.PartitionTypeGUID, gPartitionInfoEFISystemPartitionGuid)) {
        if ((PartitionInfo->System != 1))
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        else
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gPartitionInfoBBTestFunctionAssertionGuid002,
                         L"PartitionInfo - Gpt.PartitionTypeGUID should be aligned with PartitionInfo->System",
                         L"%a:%d:Gpt.PartitionTypeGUID - %g, System - %d\n",
                         __FILE__,
                         (UINTN)__LINE__,
                         &PartitionInfo->Info.Gpt.PartitionTypeGUID,
                         PartitionInfo->System
                         );
      }

    }
     
  }
  
   return EFI_SUCCESS;
}

