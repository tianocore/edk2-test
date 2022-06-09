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

  BlockIoBBTestStress.c

Abstract:

  Combination Test Cases of Block I/O Protocol

--*/


#include "SctLib.h"
#include "BlockIoBBTestMain.h"




/**
 *  Entrypoint for EFI_BLOCK_IO_PROTOCOL.Reset() Stress Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 6.1
//
EFI_STATUS
EFIAPI
BBTestResetStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_BLOCK_IO_PROTOCOL                *BlockIo;
  EFI_TEST_ASSERTION                   AssertionType;

  UINTN                                Index;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  BlockIo = (EFI_BLOCK_IO_PROTOCOL *)ClientInterface;

  //
  // Assertion Points 6.1.2.1
  // Stress test for Reset with extended verification
  //
  for (Index = 0; Index < MAX_REPEAT_OF_STRESS_TEST; Index++) {
    Status = BlockIo->Reset (BlockIo, TRUE);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Sometimes the file system will be destroied from this point. Just add a
    // stall to avoid it. (Need investigation, I don't know it is useful or not!)
    //
    SctPrint (L"Wait 5 seconds for the block device resetting...");
    gtBS->Stall (5000000);

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIoCombinationTestAssertionGuid001,
                   L"EFI_BLOCK_IO_PROTOCOL.Reset - Stress Reset the block device with extended verification",
                   L"%a:%d:Index=%d, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index,
                   Status
                   );
  }

  //
  // Assertion Points 6.1.2.2
  // Stress test for Reset without extended verification
  //
  for (Index = 0; Index < MAX_REPEAT_OF_STRESS_TEST; Index++) {
    Status = BlockIo->Reset (BlockIo, FALSE);
    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Sometimes the file system will be destroied from this point. Just add a
    // stall to avoid it. (Need investigation, I don't know it is useful or not!)
    //
    SctPrint (L"Wait 5 seconds for the block device resetting...");
    gtBS->Stall (5000000);

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIoCombinationTestAssertionGuid002,
                   L"EFI_BLOCK_IO_PROTOCOL.Reset - Stress Reset the block device without extended verification",
                   L"%a:%d,Index=%d, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index,
                   Status
                   );
  }

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_BLOCK_IO_PROTOCOL.ReadBlocks() Stress Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 6.2
//
EFI_STATUS
EFIAPI
BBTestReadBlocksStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_BLOCK_IO_PROTOCOL                *BlockIo;
  EFI_TEST_ASSERTION                   AssertionType;

  UINT32                               MediaId;
  BOOLEAN                              RemovableMedia;
  BOOLEAN                              MediaPresent;
  BOOLEAN                              LogicalPartition;
  BOOLEAN                              ReadOnly;
  BOOLEAN                              WriteCaching;
  UINT32                               BlockSize;
  UINT32                               IoAlign;
  EFI_LBA                              LastBlock;

  UINTN                                BufferSize;
  UINT8                                *Buffer;
  UINT8                                *Buffer2;

  UINT32                               BlockNumber;

  UINTN                                IndexI, IndexJ;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;

  UINTN                                Remainder;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;

  CHAR16                               *DevicePathStr;

  EFI_TEST_ASSERTION                   AssertionTypeRead1;
  EFI_TEST_ASSERTION                   AssertionTypeComp1;

  EFI_STATUS                           StatusRead1;

  UINTN                                CountComp1;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  BlockIo = (EFI_BLOCK_IO_PROTOCOL *)ClientInterface;

  LocateDevicePathFromBlockIo (BlockIo, &DevicePath, StandardLib);

  DevicePathStr = SctDevicePathToStr (DevicePath);
  if (DevicePathStr != NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Current Device: %s",
                   DevicePathStr
                   );

    Status = gtBS->FreePool (DevicePathStr);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.FreePool - Free device path string",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }

    DevicePathStr = NULL;
  }


  //
  // Initialize variable
  //
  MediaId           = BlockIo->Media->MediaId;
  RemovableMedia    = BlockIo->Media->RemovableMedia;
  MediaPresent      = BlockIo->Media->MediaPresent;
  LogicalPartition  = BlockIo->Media->LogicalPartition;
  ReadOnly          = BlockIo->Media->ReadOnly;
  WriteCaching      = BlockIo->Media->WriteCaching;
  BlockSize         = BlockIo->Media->BlockSize;
  IoAlign           = BlockIo->Media->IoAlign;
  LastBlock         = BlockIo->Media->LastBlock;

  BlockNumber       = (UINT32) MINIMUM(LastBlock, MAX_NUMBER_OF_READ_BLOCK_BUFFER);
  BufferSize        = BlockNumber * BlockSize;

  if (BufferSize == 0) {
    BufferSize = 512;
  }

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **)&Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **)&Buffer2);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // Assertion Point 6.2.2.1
  // ReadBlocks must succeed to read proper data from device with valid parameter
  //
  if (MediaPresent == TRUE) {
    for (IndexI = 0; IndexI < 2; IndexI++) {
      //
      // initialize test data
      //
      switch (IndexI) {
      case 0:
        NewLba = 1;
        NewBufferSize = BufferSize;
        break;
      case 1:
        NewLba = LastBlock - BufferSize/BlockSize;
        NewBufferSize = BufferSize;
        break;
      default:
        NewLba        = LastBlock + 1;
        NewBufferSize = BufferSize + 10;
      }

      //
      // Verify test data
      //
      if ((NewLba + NewBufferSize / BlockSize > LastBlock + 1) || (NewBufferSize > BufferSize)) {
        continue;
      }

      //
      // Initialized
      //
      AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
      AssertionTypeComp1 = EFI_TEST_ASSERTION_PASSED;
      StatusRead1 = EFI_SUCCESS;
      CountComp1 = 0;

      //
      // stress test on ReadBlock
      //
      for (IndexJ = 0; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        if (IndexJ == 0) {
          StatusRead1 = BlockIo->ReadBlocks (
                                   BlockIo,
                                   MediaId,
                                   NewLba,
                                   NewBufferSize,
                                   (VOID*)Buffer
                                   );
        } else {
          StatusRead1 = BlockIo->ReadBlocks (
                                   BlockIo,
                                   MediaId,
                                   NewLba,
                                   NewBufferSize,
                                   (VOID*)Buffer2
                                   );
        }

        if (EFI_ERROR(Status)) {
          AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
          break;
        } else {
          AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
        }

        if (IndexJ > 0) {
          //
          // Verification on the buffer read by ReadBlocks
          //
          CountComp1 = VerifyBuffer (Buffer, Buffer2, NewBufferSize);
          if (CountComp1 > 0) {
            AssertionTypeComp1 = EFI_TEST_ASSERTION_FAILED;
            break;
          } else {
            AssertionTypeComp1 = EFI_TEST_ASSERTION_PASSED;
          }
        }
      }

      //
      // Record the test results
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead1,
                     gBlockIoCombinationTestAssertionGuid003,
                     L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Stress test for ReadBlocks with same BufferSize and LBA",
                     L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Index=%d, Status=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     NewLba,
                     LastBlock,
                     IndexJ,
                     StatusRead1
                     );

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeComp1,
                     gBlockIoCombinationTestAssertionGuid004,
                     L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Stress test for ReadBlocks with same BufferSize and LBA and Verification on the buffer",
                     L"%a:%d:BufferSize=%d, Lba=0x%lx, Index=%d, DiffCount=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     NewLba,
                     IndexJ,
                     CountComp1
                     );
    }
  }

  //
  // Assertion Point 6.2.2.2
  // Stress test for ReadBlocks with same LBA and different BufferSize
  //
  if (MediaPresent == TRUE) {
    for (IndexI = 1; IndexI < MAX_REPEAT_OF_STRESS_TEST; IndexI++) {
      NewBufferSize = IndexI * BlockSize;

      //
      // Make sure that the repetition will not exceed
      //
      if (NewBufferSize > BufferSize) {
        break;
      }

      Status = BlockIo->ReadBlocks (
                          BlockIo,
                          MediaId,
                          0,
                          NewBufferSize,
                          (VOID*)Buffer
                          );
      if (EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIoCombinationTestAssertionGuid005,
                     L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Stress test for ReadBlocks with same LBA and different BufferSize",
                     L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Index=%d, Status=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     LastBlock,
                     IndexI,
                     Status
                     );
    }
  }

  //
  // Assertion Point 6.2.2.3
  // Stress test for ReadBlocks with same BufferSize and different LBA
  //

  if (MediaPresent == TRUE) {
    for (IndexI = 1; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      NewBufferSize = IndexI * BlockSize;

      //
      // Parameter verification on BufferSize
      //
      if (NewBufferSize > BufferSize) {
        continue;
      }

      for (IndexJ = 0; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        NewLba = IndexJ;
        //
        // Parameter verification on Lba
        //
        if (NewLba + NewBufferSize/BlockSize > LastBlock + 1) {
          continue;
        }

        Status = BlockIo->ReadBlocks (
                            BlockIo,
                            MediaId,
                            NewLba,
                            NewBufferSize,
                            (VOID*)Buffer
                            );
        if (EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gBlockIoCombinationTestAssertionGuid006,
                       L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Stress test for ReadBlocks with same BufferSize and different LBA",
                       L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Index=%d, Status=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       NewLba,
                       LastBlock,
                       IndexJ,
                       Status
                       );
      }
    }
  }

  //
  // Assertion point 6.2.2.4
  // Stress test for ReadBlocks on bouncing LBA value
  //
  if (MediaPresent == TRUE) {
    for (IndexI = 1; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      //
      // For different BufferSize;
      //
      NewBufferSize = IndexI * BlockSize;

      if (NewBufferSize > BufferSize) {
        break;
      }

      IndexJ = 0;
      while (1) {
        if ((IndexJ > SctDivU64x32 (LastBlock, 2, &Remainder)) || (IndexJ > MAX_REPEAT_OF_STRESS_TEST)) {
          break;
        }

        NewLba = IndexJ;

        if (NewLba + NewBufferSize/BlockSize > LastBlock + 1) {
          IndexJ++;
          continue;
        }

        //
        // Call ReadBlocks with specified BufferSize and Lba being some value start from first block of device
        //
        Status = BlockIo->ReadBlocks (
                            BlockIo,
                            MediaId,
                            NewLba,
                            NewBufferSize,
                            (VOID*)Buffer
                            );
        if (EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gBlockIoCombinationTestAssertionGuid007,
                       L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Stress test for ReadBlocks with bouncing LBA value",
                       L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Index=%d, Status=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       NewLba,
                       LastBlock,
                       IndexJ,
                       Status
                       );

        NewLba = LastBlock - IndexJ - NewBufferSize/BlockSize;
        if (NewLba + NewBufferSize/BlockSize > LastBlock + 1 || NewLba < 0) {
          IndexJ++;
          continue;
        }

        //
        // Call ReadBlocks with specified BufferSize and Lba being some value start back from last block of device
        //
        Status = BlockIo->ReadBlocks (
                            BlockIo,
                            MediaId,
                            NewLba,
                            NewBufferSize,
                            (VOID*)Buffer
                            );
        if (EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gBlockIoCombinationTestAssertionGuid008,
                       L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Stress test for ReadBlocks with bouncing LBA value",
                       L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Index=%d, Status=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       NewLba,
                       LastBlock,
                       IndexJ,
                       Status
                       );
        IndexJ++;
      }
    }
  }


  //
  // Free resources
  //
  Status = gtBS->FreePool (Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->FreePool (Buffer2);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_BLOCK_IO_PROTOCOL.WriteBlocks() Stress Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 6.3
//
EFI_STATUS
EFIAPI
BBTestWriteBlocksStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_BLOCK_IO_PROTOCOL                *BlockIo;

  UINT32                               MediaId;
  BOOLEAN                              RemovableMedia;
  BOOLEAN                              MediaPresent;
  BOOLEAN                              LogicalPartition;
  BOOLEAN                              ReadOnly;
  BOOLEAN                              WriteCaching;
  UINT32                               BlockSize;
  UINT32                               IoAlign;
  EFI_LBA                              LastBlock;

  UINTN                                BufferSize;
  UINT8                                *Buffer;
  UINT8                                *Buffer2;
  UINT8                                *Buffer3;
  UINT8                                *Buffer4;

  UINT32                               BlockNumber;

  UINTN                                IndexI = 0;
  UINTN                                IndexJ = 0;
  UINTN                                NewBufferSize = 0;
  EFI_LBA                              NewLba = 0;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_TEST_ASSERTION                   AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeRead2 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeRead3 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeRead4 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeWrite2 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeWrite3 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeWrite4 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeComp1 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeComp2 = EFI_TEST_ASSERTION_FAILED;

  EFI_STATUS                           StatusRead1 = EFI_SUCCESS;
  EFI_STATUS                           StatusRead2 = EFI_SUCCESS;
  EFI_STATUS                           StatusRead3 = EFI_SUCCESS;
  EFI_STATUS                           StatusRead4 = EFI_SUCCESS;
  EFI_STATUS                           StatusWrite1 = EFI_SUCCESS;
  EFI_STATUS                           StatusWrite2 = EFI_SUCCESS;
  EFI_STATUS                           StatusWrite3 = EFI_SUCCESS;
  EFI_STATUS                           StatusWrite4 = EFI_SUCCESS;

  UINTN                                CountComp1 = 0;
  UINTN                                CountComp2 = 0;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  BlockIo = (EFI_BLOCK_IO_PROTOCOL *)ClientInterface;

  //
  // Locate & record DevicePath for further investigation
  //
  LocateDevicePathFromBlockIo (BlockIo, &DevicePath, StandardLib);

  DevicePathStr = SctDevicePathToStr (DevicePath);
  if (DevicePathStr != NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Current Device: %s",
                   DevicePathStr
                   );

    Status = gtBS->FreePool (DevicePathStr);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.FreePool - Free device path string",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }

    DevicePathStr = NULL;
  }


  //
  // Initialize variable
  //
  MediaId           = BlockIo->Media->MediaId;
  RemovableMedia    = BlockIo->Media->RemovableMedia;
  MediaPresent      = BlockIo->Media->MediaPresent;
  LogicalPartition  = BlockIo->Media->LogicalPartition;
  ReadOnly          = BlockIo->Media->ReadOnly;
  WriteCaching      = BlockIo->Media->WriteCaching;
  BlockSize         = BlockIo->Media->BlockSize;
  IoAlign           = BlockIo->Media->IoAlign;
  LastBlock         = BlockIo->Media->LastBlock;

  BlockNumber       = (UINT32) MINIMUM(LastBlock, MAX_NUMBER_OF_READ_BLOCK_BUFFER);
  BufferSize        = BlockNumber * BlockSize;

  if (BufferSize == 0) {
    BufferSize = 512;
  }

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **)&Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **)&Buffer2);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (Buffer);
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **)&Buffer3);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (Buffer);
    gtBS->FreePool (Buffer2);
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **)&Buffer4);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (Buffer);
    gtBS->FreePool (Buffer2);
    gtBS->FreePool (Buffer3);
    return Status;
  }


  //
  // Assertion Point 6.3.2.1
  // WriteBlocks must succeed to write proper data to device with valid parameter
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    for (IndexI = 0; IndexI < 2; IndexI++) {
      //
      // initialize test data
      //
      switch (IndexI) {
      case 0:
        NewLba = 1;
        NewBufferSize = BufferSize;
        break;
      case 1:
        NewLba = LastBlock - BufferSize/BlockSize;
        NewBufferSize = BufferSize;
        break;
      default:
        //
        // This will be invalid for the test data
        //
        NewLba=LastBlock + 10;
        NewBufferSize = BufferSize+10;;
      }

      //
      // Verify test data
      //
      if ((NewLba + NewBufferSize / BlockSize > LastBlock + 1) || (NewBufferSize > BufferSize)) {
        continue;
      }

      //
      // To avoid the LOG information is destroied, the LOG information will
      // be recorded after the original data is written again.
      //

      //
      // Call ReadBlocks with specified LBA and BufferSize
      //
      StatusRead1 = BlockIo->ReadBlocks (
                               BlockIo,
                               MediaId,
                               NewLba,
                               NewBufferSize,
                               (VOID*)Buffer
                               );
      if (EFI_ERROR(StatusRead1)) {
        AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
        break;
      } else {
        AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
      }

      //
      // stress test on WriteBlock
      //
      for (IndexJ = 0; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        //
        // Write Buffer to device
        //
        if (IndexJ == 0) {
          StatusWrite1 = BlockIo->WriteBlocks (
                                    BlockIo,
                                    MediaId,
                                    NewLba,
                                    NewBufferSize,
                                    (VOID*)Buffer
                                    );
        } else {
          StatusWrite1 = BlockIo->WriteBlocks (
                                    BlockIo,
                                    MediaId,
                                    NewLba,
                                    NewBufferSize,
                                    (VOID*)Buffer2
                                    );
        }

        if (EFI_ERROR(StatusWrite1)) {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
          break;
        } else {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_PASSED;
        }

        //
        // if write-cached, then flush the data to physical device
        //
        if (WriteCaching) {
          BlockIo->FlushBlocks (BlockIo);
        }

        //
        // Read Block with same parameter and save data into buffer2
        //
        StatusRead2 = BlockIo->ReadBlocks (
                                 BlockIo,
                                 MediaId,
                                 NewLba,
                                 NewBufferSize,
                                 (VOID*)Buffer2
                                 );
        if (EFI_ERROR(StatusRead2)) {
          AssertionTypeRead2 = EFI_TEST_ASSERTION_FAILED;
          break;
        } else {
          AssertionTypeRead2 = EFI_TEST_ASSERTION_PASSED;
        }
      }

      //
      // Verification on the buffer read of first and last call of ReadBlocks
      //
      CountComp1 = VerifyBuffer (Buffer, Buffer2, NewBufferSize);
      if (CountComp1 > 0) {
        AssertionTypeComp1 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeComp1 = EFI_TEST_ASSERTION_PASSED;
      }

      //
      // Restore data
      //
      StatusWrite2 = BlockIo->WriteBlocks (
                                BlockIo,
                                MediaId,
                                NewLba,
                                NewBufferSize,
                                (VOID*)Buffer
                                );
      if (EFI_ERROR(StatusWrite2)) {
        AssertionTypeWrite2 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeWrite2 = EFI_TEST_ASSERTION_PASSED;
      }

      //
      // Record test results
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead1,
                     gBlockIoCombinationTestAssertionGuid009,
                     L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - ReadBlocks with valid BufferSize and LBA",
                     L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Status=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     NewLba,
                     LastBlock,
                     StatusRead1
                     );

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeWrite1,
                     gBlockIoCombinationTestAssertionGuid010,
                     L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Stress test for WriteBlocks with same BufferSize and LBA",
                     L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Index=%d, Status=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     NewLba,
                     LastBlock,
                     IndexJ,
                     StatusWrite1
                     );

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead2,
                     gBlockIoCombinationTestAssertionGuid012,
                     L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - ReadBlocks with valid BufferSize and LBA",
                     L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Index=%d, Status=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     NewLba,
                     LastBlock,
                     IndexJ,
                     StatusRead2
                     );

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeComp1,
                     gBlockIoCombinationTestAssertionGuid013,
                     L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Stress test for WriteBlocks with same BufferSize and LBA and Verification on the buffer",
                     L"%a:%d:BufferSize=%d, Lba=0x%lx, DiffCount=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     NewLba,
                     CountComp1
                     );

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeWrite2,
                     gBlockIoCombinationTestAssertionGuid014,
                     L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - WriteBlocks with valid BufferSize and LBA",
                     L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Status=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     NewLba,
                     LastBlock,
                     StatusWrite2
                     );
    }
  }

  //
  // Assertion Point 6.3.2.2
  // Stress test for WriteBlocks with same LBA and different BufferSize
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {

    //
    // To avoid the LOG information is destroied, the LOG information will
    // be recorded after the original data is written again.
    //

    //
    // Call ReadBlocks with Lba being zero and valid BufferSize
    // For backup data
    //
    StatusRead1 = BlockIo->ReadBlocks (
                             BlockIo,
                             MediaId,
                             0,
                             BufferSize,
                             (VOID*)Buffer
                             );
    if (EFI_ERROR(StatusRead1)) {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
      goto FreeBuffer;
    } else {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Stress test on WriteBlocks
    //
    for (IndexI = MAX_REPEAT_OF_STRESS_TEST - 1; IndexI > 0; IndexI--) {
      NewBufferSize = IndexI * BlockSize;

      //
      // Make sure that the repetition will not exceed 100 times
      //
      if (NewBufferSize > BufferSize) {
        continue;
      }

      StatusWrite1 = BlockIo->WriteBlocks (
                                BlockIo,
                                MediaId,
                                0,
                                NewBufferSize,
                                (VOID*)Buffer
                                );
      if (EFI_ERROR(StatusWrite1)) {
        AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
        break;
      } else {
        AssertionTypeWrite1 = EFI_TEST_ASSERTION_PASSED;
      }
    }

    //
    // if write-cached, then flush the data to physical device
    //
    if (WriteCaching) {
      BlockIo->FlushBlocks (BlockIo);
    }

    //
    // Call ReadBlocks with Lba being zero and valid BufferSize again
    // For verification
    //
    StatusRead2 = BlockIo->ReadBlocks (
                             BlockIo,
                             MediaId,
                             0,
                             BufferSize,
                             (VOID*)Buffer2
                             );
    if (EFI_ERROR(StatusRead2)) {
      AssertionTypeRead2 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeRead2 = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Verification on the buffer read of first and last call of ReadBlocks
    //
    CountComp1 = VerifyBuffer (Buffer, Buffer2, BufferSize);
    if (CountComp1 > 0) {
      AssertionTypeComp1 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeComp1 = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Restore data
    //
    StatusWrite2 = BlockIo->WriteBlocks (
                              BlockIo,
                              MediaId,
                              0,
                              BufferSize,
                              (VOID*)Buffer
                              );
    if (EFI_ERROR(StatusWrite2)) {
      AssertionTypeWrite2 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeWrite2 = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Record the test results
    //

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead1,
                   gBlockIoCombinationTestAssertionGuid015,
                   L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - ReadBlocks with Lba being zero and valid BufferSize",
                   L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastBlock,
                   StatusRead1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite1,
                   gBlockIoCombinationTestAssertionGuid016,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Stress test for WriteBlocks with same LBA and different BufferSize",
                   L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Index=%d, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   NewBufferSize,
                   LastBlock,
                   IndexI,
                   StatusWrite1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead2,
                   gBlockIoCombinationTestAssertionGuid018,
                   L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - ReadBlocks with same LBA being zero and valid BufferSize",
                   L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastBlock,
                   StatusRead2
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeComp1,
                   gBlockIoCombinationTestAssertionGuid019,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Stress test for WriteBlocks with different BufferSize and same LBA and Verification on the buffer",
                   L"%a:%d:BufferSize=%d, Lba=0, DiffCount=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   CountComp1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite2,
                   gBlockIoCombinationTestAssertionGuid020,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - WriteBlocks with valid BufferSize and LBA",
                   L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastBlock,
                   StatusWrite2
                   );
  }

  //
  // Assertion Point 6.3.2.3
  // Stress test for WriteBlocks with same BufferSize and different LBA
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {

    //
    // To avoid the LOG information is destroied, the LOG information will
    // be recorded after the original data is written again.
    //

    //
    // Call ReadBlocks with Lba being zero and valid BufferSize
    // For backup data
    //
    StatusRead1 = BlockIo->ReadBlocks (
                             BlockIo,
                             MediaId,
                             0,
                             BufferSize,
                             (VOID*)Buffer
                             );
    if (EFI_ERROR(StatusRead1)) {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
      goto FreeBuffer;
    } else {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Stress test on WriteBlocks
    //
    for (IndexI = 1; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      NewBufferSize = IndexI * BlockSize;

      //
      // Parameter verification on BufferSize
      //
      if (NewBufferSize > BufferSize) {
        continue;
      }

      for (IndexJ = 0; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        NewLba = IndexJ;

        //
        // Parameter verification on Lba
        //
        if (SctMultU64x32 (NewLba, BlockSize) + NewBufferSize > BufferSize) {
          break;
        }

        StatusWrite1 = BlockIo->WriteBlocks (
                                  BlockIo,
                                  MediaId,
                                  NewLba,
                                  NewBufferSize,
                                  (VOID*)(Buffer + SctMultU64x32 (NewLba, BlockSize))
                                  );
        if (EFI_ERROR(StatusWrite1)) {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
          break;
        } else {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_PASSED;
        }
      }
    }

    //
    // if write-cached, then flush the data to physical device
    //
    if (WriteCaching) {
      BlockIo->FlushBlocks (BlockIo);
    }

    //
    // Call ReadBlocks with Lba being zero and valid BufferSize again
    // For verification
    //
    StatusRead2 = BlockIo->ReadBlocks (
                             BlockIo,
                             MediaId,
                             0,
                             BufferSize,
                             (VOID*)Buffer2
                             );
    if (EFI_ERROR(StatusRead2)) {
      AssertionTypeRead2 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeRead2 = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Verification on the buffer read of first and last call of ReadBlocks
    //
    CountComp1 = VerifyBuffer (Buffer, Buffer2, BufferSize);
    if (CountComp1 > 0) {
      AssertionTypeComp1 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeComp1 = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Restore data
    //
    StatusWrite2 = BlockIo->WriteBlocks (
                              BlockIo,
                              MediaId,
                              0,
                              BufferSize,
                              (VOID*)Buffer
                              );
    if (EFI_ERROR(StatusWrite2)) {
      AssertionTypeWrite2 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeWrite2 = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Record test results
    //

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead1,
                   gBlockIoCombinationTestAssertionGuid021,
                   L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - ReadBlocks with same valid parameter",
                   L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastBlock,
                   StatusRead1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite1,
                   gBlockIoCombinationTestAssertionGuid022,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Stress test for WriteBlocks with same BufferSize and different LBA",
                   L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Index=%d, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   NewBufferSize,
                   NewLba,
                   LastBlock,
                   IndexJ,
                   StatusWrite1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead2,
                   gBlockIoCombinationTestAssertionGuid024,
                   L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - ReadBlocks with Lba being zero and valid BufferSize",
                   L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastBlock,
                   StatusRead2
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeComp1,
                   gBlockIoCombinationTestAssertionGuid025,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Stress test for WriteBlocks with same BufferSize and different LBA and Verification on the buffer",
                   L"%a:%d:BufferSize=%d, Lba=0, DiffCount=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   CountComp1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite2,
                   gBlockIoCombinationTestAssertionGuid026,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - WriteBlocks with valid BufferSize and LBA",
                   L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastBlock,
                   StatusWrite2
                   );
  }

  //
  // Assertion point 6.3.2.4
  // Stress test for WriteBlocks on bouncing LBA value
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {

    //
    // To avoid the LOG information is destroied, the LOG information will
    // be recorded after the original data is written again.
    //

    //
    // backup start and last BufferSize of block on device and save them into Buffer & Buffer2
    //
    StatusRead1 = BlockIo->ReadBlocks (
                             BlockIo,
                             MediaId,
                             0,
                             BufferSize,
                             (VOID*)Buffer
                             );
    if (EFI_ERROR(StatusRead1)) {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
      goto FreeBuffer;
    } else {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
    }

    NewLba = LastBlock + 1 - BufferSize/BlockSize;
    StatusRead2 = BlockIo->ReadBlocks (
                             BlockIo,
                             MediaId,
                             NewLba,
                             BufferSize,
                             (VOID*)Buffer2
                             );
    if (EFI_ERROR(StatusRead2)) {
      AssertionTypeRead2 = EFI_TEST_ASSERTION_FAILED;
      goto FreeBuffer;
    } else {
      AssertionTypeRead2 = EFI_TEST_ASSERTION_PASSED;
    }

    for (IndexI = 1; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      //
      // For different BufferSize;
      //
      NewBufferSize = IndexI * BlockSize;
      if (NewBufferSize > BufferSize) {
        break;
      }

      for (IndexJ = 0; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        NewLba = IndexJ;

        //
        // Parameter verification on Lba
        //
        if (SctMultU64x32 (NewLba, BlockSize) + NewBufferSize > BufferSize) {
          break;
        }

        //
        // Call WriteBlocks with specified BufferSize and Lba being some value start from first block of device
        //
        StatusWrite1 = BlockIo->WriteBlocks (
                                  BlockIo,
                                  MediaId,
                                  NewLba,
                                  NewBufferSize,
                                  (VOID*)(Buffer + SctMultU64x32 (NewLba, BlockSize))
                                  );
        if (EFI_ERROR(StatusWrite1)) {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
          break;
        } else {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_PASSED;
        }

        NewLba = LastBlock + 1 - IndexJ - NewBufferSize/BlockSize;

        //
        // Parameter verification on Lba
        //
        if (BlockSize * IndexJ + NewBufferSize > BufferSize) {
          break;
        }

        //
        // Call WriteBlocks with specified BufferSize and Lba being some value start back from last block of device
        //
        StatusWrite2 = BlockIo->WriteBlocks (
                                  BlockIo,
                                  MediaId,
                                  NewLba,
                                  NewBufferSize,
                                  (VOID*)(Buffer2 + BufferSize - BlockSize * IndexJ - NewBufferSize)
                                  );
        if (EFI_ERROR(StatusWrite2)) {
          AssertionTypeWrite2 = EFI_TEST_ASSERTION_FAILED;
          break;
        } else {
          AssertionTypeWrite2 = EFI_TEST_ASSERTION_PASSED;
        }
      }

      //
      // if write-cached, then flush the data to physical device
      //
      if (WriteCaching) {
        BlockIo->FlushBlocks (BlockIo);
      }

      //
      // Read Block with same LBA and BufferSize again and save data into Buffer3
      //
      StatusRead3 = BlockIo->ReadBlocks (
                               BlockIo,
                               MediaId,
                               0,
                               BufferSize,
                               (VOID*)Buffer3
                               );
      if (EFI_ERROR(StatusRead3)) {
        AssertionTypeRead3 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeRead3 = EFI_TEST_ASSERTION_PASSED;
      }

      //
      // verification on the buffer read in the two steps of ReadBlocks call
      //
      CountComp1 = VerifyBuffer (Buffer, Buffer3, BufferSize);
      if (CountComp1 > 0) {
        AssertionTypeComp1 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeComp1 = EFI_TEST_ASSERTION_PASSED;
      }

      //
      // Read Block with same LBA and BufferSize again and save data into Buffer4
      //
      NewLba = LastBlock + 1 - BufferSize/BlockSize;
      StatusRead4 = BlockIo->ReadBlocks (
                               BlockIo,
                               MediaId,
                               NewLba,
                               BufferSize,
                               (VOID*)Buffer4
                               );
      if (EFI_ERROR(StatusRead4)) {
        AssertionTypeRead4 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeRead4 = EFI_TEST_ASSERTION_PASSED;
      }

      //
      // verification on the buffer read in the two steps of ReadBlocks call
      //
      CountComp2 = VerifyBuffer (Buffer2, Buffer4, BufferSize);
      if (CountComp2 > 0) {
        AssertionTypeComp2 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeComp2 = EFI_TEST_ASSERTION_PASSED;
      }
    }

    //
    // Rewrite buffer back to block device
    //
    StatusWrite3 = BlockIo->WriteBlocks (
                              BlockIo,
                              MediaId,
                              0,
                              BufferSize,
                              (VOID*)Buffer
                              );
    if (EFI_ERROR(StatusWrite3)) {
      AssertionTypeWrite3 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeWrite3 = EFI_TEST_ASSERTION_PASSED;
    }

    NewLba = LastBlock + 1 - BufferSize/BlockSize;
    StatusWrite4 = BlockIo->WriteBlocks (
                              BlockIo,
                              MediaId,
                              NewLba,
                              BufferSize,
                              (VOID*)Buffer2
                              );
    if (EFI_ERROR(StatusWrite4)) {
      AssertionTypeWrite4 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeWrite4 = EFI_TEST_ASSERTION_PASSED;
    }

    //
    // Read test results
    //

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead1,
                   gBlockIoCombinationTestAssertionGuid027,
                   L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - ReadBlocks with specified value",
                   L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastBlock,
                   StatusRead1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead2,
                   gBlockIoCombinationTestAssertionGuid028,
                   L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - ReadBlocks with specified value",
                   L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   NewLba,
                   LastBlock,
                   StatusRead2
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite1,
                   gBlockIoCombinationTestAssertionGuid029,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Stress test for WriteBlocks with bouncing LBA value",
                   L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Index=%d, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   NewBufferSize,
                   NewLba,
                   LastBlock,
                   IndexJ,
                   StatusWrite1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite2,
                   gBlockIoCombinationTestAssertionGuid030,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Stress test for WriteBlocks with bouncing LBA value",
                   L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Index=%d, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   NewBufferSize,
                   NewLba,
                   LastBlock,
                   IndexJ,
                   StatusWrite2
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead3,
                   gBlockIoCombinationTestAssertionGuid032,
                   L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Read Block with proper parameter from valid media",
                   L"%a:%d:BufferSize=%d, Lba=0, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   StatusRead3
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeComp1,
                   gBlockIoCombinationTestAssertionGuid033,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Verification on two times of reading block after writing on bouncing LBA value",
                   L"%a:%d:BufferSize=%d, Lba=0, DiffCount=%d",
                  __FILE__,
                  (UINTN)__LINE__,
                  BufferSize,
                  CountComp1
                  );

    StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionTypeRead4,
                  gBlockIoCombinationTestAssertionGuid034,
                  L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Read Block with proper parameter from valid media",
                  L"%a:%d:BufferSize=%d, Lba=0x%lx, Status=%r",
                  __FILE__,
                  (UINTN)__LINE__,
                  BufferSize,
                  NewLba,
                  StatusRead4
                  );

    StandardLib->RecordAssertion (
                  StandardLib,
                  AssertionTypeComp2,
                  gBlockIoCombinationTestAssertionGuid035,
                  L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Verification on two times of reading block after writing on bouncing LBA value",
                  L"%a:%d:BufferSize=%d, Lba=0x%lx, DiffCount=%d",
                  __FILE__,
                  (UINTN)__LINE__,
                  BufferSize,
                  NewLba,
                  CountComp2
                  );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite3,
                   gBlockIoCombinationTestAssertionGuid036,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - WriteBlocks with specified value",
                   L"%a:%d:BufferSize=%d, LBA=0, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastBlock,
                   StatusWrite3
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite4,
                   gBlockIoCombinationTestAssertionGuid037,
                   L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - WriteBlocks with specified value",
                   L"%a:%d:BufferSize=%d, LBA=0x%lx, LastBlock=0x%lx, Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   NewLba,
                   LastBlock,
                   StatusWrite4
                   );
  }

FreeBuffer:
  //
  // Free resources
  //
  Status = gtBS->FreePool (Buffer4);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->FreePool (Buffer3);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->FreePool (Buffer2);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = gtBS->FreePool (Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  return EFI_SUCCESS;
}
