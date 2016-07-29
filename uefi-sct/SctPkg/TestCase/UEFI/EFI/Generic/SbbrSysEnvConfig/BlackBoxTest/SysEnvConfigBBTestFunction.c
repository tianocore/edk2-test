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

  Copyright (c) 2006, ARM. All rights reserved.<BR>

--*/
/*++

Module Name:

  SysEnvConfigBBTestFunction.c

Abstract:

  Test case definitions for SysEnvConfig tests.

--*/

#include <Chipset/AArch64.h>
#include "Guid.h"
#include <Library/ArmLib.h>
#include "SctLib.h"
#include "SysEnvConfigBBTestFunction.h"
#include "SysEnvConfigBBTestMain.h"
#include <UEFI/Protocol/BlockIo.h>
#include <Uefi/UefiGpt.h>
#include <Uefi/UefiMultiPhase.h>

/**
 *  Entrypoint for Boot Exception Level Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

//
// SBBR 3.3.1
//

EFI_STATUS
BBTestBootExcLevelTest (
  IN EFI_BB_TEST_PROTOCOL               *This,
  IN VOID                               *ClientInterface,
  IN EFI_TEST_LEVEL                     TestLevel,
  IN EFI_HANDLE                         SupportHandle
  )
{

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 CurrentEL;

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
  // Reading CurrentEL register into ExceptionLevel register variable and checking its value.
  //
  CurrentEL = ArmReadCurrentEL();

  switch(CurrentEL){
    case AARCH64_EL1:
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      break;
    case AARCH64_EL2:
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      break;
    case AARCH64_EL3:
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      break;
    default:
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"Unrecognized CurrentEL Value",
                  L"%a:%d:CurrentEL=0x%X",
                  __FILE__,
                  (UINTN)__LINE__,
                  CurrentEL
                  );
      return EFI_UNSUPPORTED;
  }

  StandardLib->RecordAssertion (
              StandardLib,
              AssertionType,
              gSysEnvConfigAssertion001Guid,
              L"TestBootExcLevel",
              L"%a:%d:CurrentEL=0x%X",
              __FILE__,
              __LINE__,
              CurrentEL
              );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Memory Address Alignment Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

//
// SBBR 3.3.2
//

EFI_STATUS
BBTestMemAddrAlignmentTest (
  IN EFI_BB_TEST_PROTOCOL               *This,
  IN VOID                               *ClientInterface,
  IN EFI_TEST_LEVEL                     TestLevel,
  IN EFI_HANDLE                         SupportHandle
  )
{

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT32                                Sctlr;

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
  // Reading SCTLR for current exception level
  //
  Sctlr = ArmReadSctlr();

  if (Sctlr & SCTLR_A_MASK)
  {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  else
  {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
              StandardLib,
              AssertionType,
              gSysEnvConfigAssertion002Guid,
              L"TestMemAddrAlignment",
              L"%a:%d:SCTLR.A=%d",
              __FILE__,
              __LINE__,
              (Sctlr & SCTLR_A_MASK) >> SCTLR_A_SHIFT
              );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Operating System Boot Disk Partition Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

//
// SBBR 3.3.3
//

EFI_STATUS
BBTestOsDiskFormatTest (
  IN EFI_BB_TEST_PROTOCOL               *This,
  IN VOID                               *ClientInterface,
  IN EFI_TEST_LEVEL                     TestLevel,
  IN EFI_HANDLE                         SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  INTN                                  iStatus;
  UINTN                                 NumberOfHandles;
  EFI_HANDLE                            *HandleBuffer;
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo;
  UINT8                                 *BlockBuffer;
  EFI_GUID                              PartitionTypeGuid;
  UINT32                                GptPartitionsInThisLbaCount;
  EFI_LBA                               PartitionEntryLba;
  UINT32                                NumberOfPartitionEntries;
  UINT32                                SizeOfPartitionEntry;
  UINT32                                PartitionEntriesPerLba;
  UINT32                                HandleCount;
  UINT32                                GptPartitionEntryCount;
  EFI_PARTITION_TABLE_HEADER            *GptTableHeader;
  EFI_PARTITION_ENTRY                   *GptPartitionEntry;
  UINT8                                 GptSignature[] = GPT_SIGNATURE;
  EFI_GUID                              GptEfiPartitionGuid = GPT_EFI_PARTITION_GUID;

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
  // Get list of all handles that support BlockIO.
  //
  Status = gBS->LocateHandleBuffer (
              ByProtocol,
              &gBlackBoxEfiBlockIoProtocolGuid,
              NULL,
              &NumberOfHandles,
              &HandleBuffer
              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Checking each disk device to see if it is bootable
  //
  HandleCount = 0;
  while (HandleCount < NumberOfHandles) {

    //
    // Creating BlockIo device for one of the handles we found.
    //
    Status = gBS->OpenProtocol (
                HandleBuffer[HandleCount],
                &gBlackBoxEfiBlockIoProtocolGuid,
                (void *)&BlockIo,
                gImageHandle,
                NULL,
                EFI_OPEN_PROTOCOL_GET_PROTOCOL
                );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    // Allocating memory to read data into
    //
    Status = gBS->AllocatePool (
                EfiBootServicesData,
                BlockIo->Media->BlockSize,
                (void **)&BlockBuffer
                );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    // Reading block that should contain GPT header.
    //
    Status = BlockIo->ReadBlocks (
                BlockIo,
                BlockIo->Media->MediaId,
                GPT_HEADER_LBA,
                BlockIo->Media->BlockSize,
                (VOID*)BlockBuffer
                );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    // Checking if block is a GPT header.
    //
    GptTableHeader = (EFI_PARTITION_TABLE_HEADER *)BlockBuffer;
    iStatus = SctCompareMem (
                (void *)&GptTableHeader->Header.Signature,
                (void *)GptSignature,
                GPT_SIGNATURE_SIZE
                );
    if (iStatus == 0) {

      //
      // Block contains a GPT header, so now we need to find an EFI partition.
      //
      PartitionEntryLba = GptTableHeader->PartitionEntryLBA;
      NumberOfPartitionEntries = GptTableHeader->NumberOfPartitionEntries;
      SizeOfPartitionEntry = GptTableHeader->SizeOfPartitionEntry;

      //
      // Loops through LBAs until all partition entries have been searched.
      //
      GptPartitionEntryCount = 0;
      PartitionEntriesPerLba = BlockIo->Media->BlockSize / SizeOfPartitionEntry;
      while (GptPartitionEntryCount < NumberOfPartitionEntries) {

        //
        // Reading LBA of partition entry.
        //
        Status = BlockIo->ReadBlocks (
                    BlockIo,
                    BlockIo->Media->MediaId,
                    PartitionEntryLba,
                    BlockIo->Media->BlockSize,
                    (VOID *)BlockBuffer
                    );
        if (EFI_ERROR (Status)) {
          return Status;
        }

        //
        // Loops through partition entries in a single LBA
        //
        GptPartitionsInThisLbaCount = 0;
        while ( (GptPartitionsInThisLbaCount < PartitionEntriesPerLba) \
                && (GptPartitionEntryCount < NumberOfPartitionEntries) \
                ) {

          GptPartitionEntry = (EFI_PARTITION_ENTRY *)&BlockBuffer[(GptPartitionEntryCount % PartitionEntriesPerLba) * SizeOfPartitionEntry];

          //
          // Checking partition type GUID against EFI partition type GUID.
          //
          CopyGuid (
                      &PartitionTypeGuid,
                      &GptPartitionEntry->PartitionTypeGUID
                      );

          iStatus = SctCompareGuid (
                      (void *)&PartitionTypeGuid,
                      (void *)&GptEfiPartitionGuid
                      );
          if (iStatus == 0) {
            StandardLib->RecordAssertion (
                        StandardLib,
                        EFI_TEST_ASSERTION_PASSED,
                        gSysEnvConfigAssertion003Guid,
                        L"TestOsDiskFormat",
                        L"%a:%d:Valid Boot Disk Found",
                        __FILE__,
                        (UINTN)__LINE__
                        );
            gBS->FreePool ((void *)BlockBuffer);
            Status = gBS->CloseProtocol (
                        HandleBuffer[HandleCount],
                        &gBlackBoxEfiBlockIoProtocolGuid,
                        gImageHandle,
                        NULL
                        );
            return EFI_SUCCESS;
          }

          GptPartitionEntryCount++;
          GptPartitionsInThisLbaCount++;
        }

        PartitionEntryLba++;
      }
    }

    gBS->FreePool ((void *)BlockBuffer);

    //
    // Closing the protocol
    //
    Status = gBS->CloseProtocol (
                HandleBuffer[HandleCount],
                &gBlackBoxEfiBlockIoProtocolGuid,
                gImageHandle,
                NULL
                );

    HandleCount++;
  }

  StandardLib->RecordAssertion (
              StandardLib,
              EFI_TEST_ASSERTION_FAILED,
              gSysEnvConfigAssertion003Guid,
              L"TestOsDiskFormat",
              L"%a:%d:No Valid Boot Disk Found",
              __FILE__,
              (UINTN)__LINE__
              );

  return EFI_SUCCESS;
}
