/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  BlockIoBBTestFunction.c

Abstract:

  Interface Function Test Cases of Block I/O Protocol

--*/


#include "SctLib.h"
#include "BlockIoBBTestMain.h"

/**
 *  Entrypoint for EFI_BLOCK_IO_PROTOCOL.Reset() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS or EFI_DEVICE_ERROR Finish the test successfully.
 */
//
// TDS 5.1
//
EFI_STATUS
EFIAPI
BBTestResetFunctionAutoTest (
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
  // Assertion Point 5.1.2.1
  // Reset block device hardware with extended verification
  //
  Status = BlockIo->Reset (BlockIo, TRUE);
  if (Status != EFI_DEVICE_ERROR && Status != EFI_SUCCESS) {
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
                 gBlockIoFunctionTestAssertionGuid001,
                 L"EFI_BLOCK_IO_PROTOCOL.Reset - Reset the block device with extended verification",
                 L"%a:%d:Status=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Assertion Point 5.1.2.2
  // Reset the block device hardware without extended verification
  //
  Status = BlockIo->Reset (BlockIo, FALSE);
  if (Status != EFI_DEVICE_ERROR && Status != EFI_SUCCESS) {
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
                 gBlockIoFunctionTestAssertionGuid002,
                 L"EFI_BLOCK_IO_PROTOCOL.Reset - Reset the block device without extended verification",
                 L"%a:%d:Status=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_BLOCK_IO_PROTOCOL.ReadBlocks() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.2
//
EFI_STATUS
EFIAPI
BBTestReadBlocksFunctionAutoTest (
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
  UINT8                                *Buffer = NULL;

  UINT32                               BlockNumber;

  UINTN                                IndexI, IndexJ;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;

  UINTN                                Remainder;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;

  CHAR16                               *DevicePathStr;


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
    BufferSize = BlockSize;
  }

  //
  // allocate aligned buffer
  //
  Buffer = AllocateAlignedPool(
             EfiBootServicesData, 
             BufferSize, 
             IoAlign
             );
  if (Buffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateAlignedPool - Allocate aligned buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_OUT_OF_RESOURCES
                   );
    return EFI_OUT_OF_RESOURCES;
  }


  //
  // Assertion Point 5.2.2.1
  // ReadBlocks must succeed to read proper data from device with valid parameter
  //
  if (MediaPresent == TRUE) {
    for (IndexI = 0; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_DIFFERENT_BUFFERSIZE_FOR_TEST*BlockSize
      //
      NewBufferSize = IndexI * BlockSize;

      //
      //parameter verification on NewBufferSize
      //
      if (NewBufferSize > BufferSize) {
        break;
      }

      for (IndexJ = 0; IndexJ < 3 * MAX_DIFFERENT_LBA_FOR_TEST; IndexJ++) {
        //
        // prepare test data
        //
        if (IndexJ < MAX_DIFFERENT_LBA_FOR_TEST) {
          // from 1 to MAX_DIFFERENT_LBA_FOR_TEST
          NewLba = IndexJ;
        } else if (IndexJ < 2 * MAX_DIFFERENT_LBA_FOR_TEST) {
          // from (LastBlock - MAX_DIFFERENT_LBA_FOR_TEST - MAX_DIFFERENT_BUFFERSIZE_FOR_TEST)  to (LastBlock - MAX_DIFFERENT_BUFFERSIZE_FOR_TEST)
          if (LastBlock < MAX_DIFFERENT_LBA_FOR_TEST + MAX_DIFFERENT_BUFFERSIZE_FOR_TEST)
            continue;
          NewLba = IndexJ + LastBlock - 2 * MAX_DIFFERENT_LBA_FOR_TEST - MAX_DIFFERENT_BUFFERSIZE_FOR_TEST;
        } else {
          // from (LastBlock/2 - MAX_DIFFERENT_LBA_FOR_TEST/2) to (LastBlock/2 + MAX_DIFFERENT_LBA_FOR_TEST/2)
          if (LastBlock < MAX_DIFFERENT_LBA_FOR_TEST)
            continue;
          NewLba = IndexJ - 2 * MAX_DIFFERENT_LBA_FOR_TEST + (SctDivU64x32 (LastBlock, 2, &Remainder) - MAX_DIFFERENT_LBA_FOR_TEST / 2);
        }

        //
        //parameter verification on NewLba
        //
        if (NewLba + NewBufferSize / BlockSize > LastBlock + 1) {
          continue;
        }

        //
        // Call ReadBlocks with the specified LBA and BufferSize
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
                       gBlockIoFunctionTestAssertionGuid003,
                       L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Read Block with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Lba=0x%lx, Status=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       NewLba,
                       Status
                       );
        if (EFI_ERROR(Status)) {
          continue;
        }
      }//end of loop of Lba - IndexJ
    }//end of loop of BufferSize - IndexI
  }


  //
  // Free aligned buffer
  //
  Status = FreeAlignedPool (Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"FreeAlignedPool - Free aligned buffer for testing",
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
 *  Entrypoint for EFI_BLOCK_IO_PROTOCOL.WriteBlocks() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.3
//
EFI_STATUS
EFIAPI
BBTestWriteBlocksFunctionAutoTest (
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
  UINT8                                *Buffer  = NULL;
  UINT8                                *Buffer2 = NULL;
  UINT8                                *Buffer3 = NULL;

  UINT32                               BlockNumber;

  UINTN                                IndexI, IndexJ;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;

  UINTN                                Remainder;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  EFI_TEST_ASSERTION                   AssertionTypeRead1;
  EFI_TEST_ASSERTION                   AssertionTypeRead2;
  EFI_TEST_ASSERTION                   AssertionTypeRead3;
  EFI_TEST_ASSERTION                   AssertionTypeWrite1;
  EFI_TEST_ASSERTION                   AssertionTypeWrite2;
  EFI_TEST_ASSERTION                   AssertionTypeComp1;
  EFI_TEST_ASSERTION                   AssertionTypeComp2;

  EFI_STATUS                           StatusRead1;
  EFI_STATUS                           StatusRead2;
  EFI_STATUS                           StatusRead3;
  EFI_STATUS                           StatusWrite1;
  EFI_STATUS                           StatusWrite2;

  UINTN                                CountComp1;
  UINTN                                CountComp2;


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
    BufferSize = BlockSize;
  }

  //
  // allocate aligned buffer
  //
  Buffer = AllocateAlignedPool(
             EfiBootServicesData, 
             BufferSize, 
             IoAlign
             );
  if (Buffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateAlignedPool - Allocate aligned buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_OUT_OF_RESOURCES
                   );
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // allocate aligned buffer
  //
  Buffer2 = AllocateAlignedPool(
              EfiBootServicesData, 
              BufferSize, 
              IoAlign
              );
  if (Buffer2 == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateAlignedPool - Allocate aligned buffer2 for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_OUT_OF_RESOURCES
                   );
    FreeAlignedPool (Buffer);
    return EFI_OUT_OF_RESOURCES;
  }
  
  //
  // allocate aligned buffer
  //
  Buffer3 = AllocateAlignedPool(
              EfiBootServicesData, 
              BufferSize, 
              IoAlign
              );
  if (Buffer3 == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateAlignedPool - Allocate aligned buffer3 for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_OUT_OF_RESOURCES
                   );
    FreeAlignedPool (Buffer);
    FreeAlignedPool (Buffer2);
    return EFI_OUT_OF_RESOURCES;
  }
  
  //
  // Assertion Point 5.3.2.1
  // ReadBlocks must succeed to read proper data from device with valid parameter
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (LastBlock != 0)) {
    for (IndexI = 0; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_DIFFERENT_BUFFERSIZE_FOR_TEST*BlockSize
      //
      NewBufferSize = IndexI * BlockSize;

      //
      //parameter verification on NewBufferSize
      //
      if (NewBufferSize > BufferSize) {
        break;
      }

      for (IndexJ = 0; IndexJ < 3 * MAX_DIFFERENT_LBA_FOR_TEST; IndexJ++) {
        //
        // prepare test data
        //
        if (IndexJ < MAX_DIFFERENT_LBA_FOR_TEST) {
          // from 1 to MAX_DIFFERENT_LBA_FOR_TEST
          NewLba = IndexJ;
        } else if (IndexJ < 2 * MAX_DIFFERENT_LBA_FOR_TEST) {
          // from (LastBlock - MAX_DIFFERENT_LBA_FOR_TEST - MAX_DIFFERENT_BUFFERSIZE_FOR_TEST)  to (LastBlock - MAX_DIFFERENT_BUFFERSIZE_FOR_TEST)
          NewLba = IndexJ + LastBlock - 2 * MAX_DIFFERENT_LBA_FOR_TEST - MAX_DIFFERENT_BUFFERSIZE_FOR_TEST;
        } else {
          // from (LastBlock/2 - MAX_DIFFERENT_LBA_FOR_TEST/2) to (LastBlock/2 + MAX_DIFFERENT_LBA_FOR_TEST/2)
          NewLba = IndexJ - 2 * MAX_DIFFERENT_LBA_FOR_TEST + (SctDivU64x32 (LastBlock, 2, &Remainder) - MAX_DIFFERENT_LBA_FOR_TEST / 2);
        }

        //
        //parameter verification on NewLba
        //
        if (NewLba + NewBufferSize / BlockSize > LastBlock + 1) {
          continue;
        }

        //
        // To avoid the LOG information is destroied, the LOG information will
        // be recorded after the original data is written again.
        //

        //
        // Call ReadBlocks with the specified LBA and BufferSize
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
        } else {
          AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
        }

        //
        // Write specified buffer2 differ from buffer to the device
        //
        StatusWrite1 = BlockIo->WriteBlocks (
                                  BlockIo,
                                  MediaId,
                                  NewLba,
                                  NewBufferSize,
                                  (VOID*)Buffer2
                                  );
        if (EFI_ERROR(StatusWrite1)) {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
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
        // Read Block with same LBA and BufferSize again and save data into Buffer3
        //
        StatusRead2 = BlockIo->ReadBlocks (
                                 BlockIo,
                                 MediaId,
                                 NewLba,
                                 NewBufferSize,
                                 (VOID*)Buffer3
                                 );
        if (EFI_ERROR(StatusRead2)) {
          AssertionTypeRead2 = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeRead2 = EFI_TEST_ASSERTION_PASSED;
        }

        //
        // verification on Write and Read blocks on valid media
        //
        CountComp1 = VerifyBuffer (Buffer2, Buffer3, NewBufferSize);
        if (CountComp1 > 0) {
          AssertionTypeComp1 = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeComp1 = EFI_TEST_ASSERTION_PASSED;
        }

        //
        // Write buffer read in the first call of ReadBlocks back to the device
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
                                 NewLba,
                                 NewBufferSize,
                                 (VOID*)Buffer3
                                 );
        if (EFI_ERROR(StatusRead3)) {
          AssertionTypeRead3 = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeRead3 = EFI_TEST_ASSERTION_PASSED;
        }

        //
        // verification on first and last call of ReadBlocks
        //
        CountComp2 = VerifyBuffer (Buffer, Buffer3, NewBufferSize);
        if (CountComp2 > 0) {
          AssertionTypeComp2 = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeComp2 = EFI_TEST_ASSERTION_PASSED;
        }

        //
        // Record test results
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead1,
                       gTestGenericFailureGuid,
                       L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Read Block with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Lba=0x%lx, Status=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       NewLba,
                       StatusRead1
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeWrite1,
                       gBlockIoFunctionTestAssertionGuid009,
                       L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Write Block with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Lba=0x%lx, Status=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       NewLba,
                       StatusWrite1
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead2,
                       gTestGenericFailureGuid,
                       L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Read Block with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Lba=0x%lx, Status=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       NewLba,
                       StatusRead2
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeComp1,
                       gBlockIoFunctionTestAssertionGuid012,
                       L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Verification on Write and Read blocks on valid media",
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
                       gBlockIoFunctionTestAssertionGuid013,
                       L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Write Block with proper parameter back to valid media ",
                       L"%a:%d:BufferSize=%d, Lba=0x%lx, Status=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       NewLba,
                       StatusWrite2
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead3,
                       gTestGenericFailureGuid,
                       L"EFI_BLOCK_IO_PROTOCOL.ReadBlocks - Read Block with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Lba=0x%lx, Status=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       NewLba,
                       StatusRead3
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeComp2,
                       gBlockIoFunctionTestAssertionGuid016,
                       L"EFI_BLOCK_IO_PROTOCOL.WriteBlocks - Verification on Write and Read blocks on valid media",
                       L"%a:%d:BufferSize=%d, Lba=0x%lx,  DiffCount=%d",
                      __FILE__,
                      (UINTN)__LINE__,
                      NewBufferSize,
                      NewLba,
                      CountComp2
                      );
      }//end of loop of Lba - IndexJ
    }//end of loop of BufferSize - IndexI
  }

  //
  // Free resources
  //
  Status = FreeAlignedPool (Buffer);
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
  }

  Status = FreeAlignedPool (Buffer2);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free buffer2 for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  Status = FreeAlignedPool (Buffer3);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.FreePool - Free buffer3 for testing",
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
 *  Entrypoint for EFI_BLOCK_IO_PROTOCOL.FlushBlocks() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.4
//
EFI_STATUS
EFIAPI
BBTestFlushBlocksFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  //
  // Current not support!
  //

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_BLOCK_IO_PROTOCOL.MediaInfo Integrity Check Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.4
//
EFI_STATUS
EFIAPI
BBTestMediaInfoCheckAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  //
  // Current not support!
  //
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
#ifndef EFIARM
  EFI_BLOCK_IO_PROTOCOL                *BlockIo;
  EFI_TEST_ASSERTION                   AssertionType;
#endif

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
#ifndef EFIARM
  BlockIo = (EFI_BLOCK_IO_PROTOCOL *)ClientInterface;

  if (BlockIo->Revision >= EFI_BLOCK_IO_PROTOCOL_REVISION2 && BlockIo->Media->LogicalPartition) {
    if (BlockIo->Media->LogicalBlocksPerPhysicalBlock == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBlockIoFunctionTestAssertionGuid021,
                 L"EFI_BLOCK_IO_PROTOCOL.Media - LogicalBlocksPerPhysicalBlock should be 0 when LogicalPartition is TRUE ",
                 L"%a:%d Media->LogicalBlocksPerPhysicalBlock %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 BlockIo->Media->LogicalBlocksPerPhysicalBlock
                 );
  } 

  if (BlockIo->Revision >= EFI_BLOCK_IO_PROTOCOL_REVISION3 && BlockIo->Media->LogicalPartition) {
    if (BlockIo->Media->OptimalTransferLengthGranularity == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBlockIoFunctionTestAssertionGuid022,
                 L"EFI_BLOCK_IO_PROTOCOL.Media - OptimalTransferLengthGranularity should be 0 when LogicalPartition is TRUE ",
                 L"%a:%d Media->OptimalTransferLengthGranularity %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 BlockIo->Media->OptimalTransferLengthGranularity
                 );
  } 
#endif

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_BLOCK_IO_PROTOCOL.Media Integrity test
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.5
//
EFI_STATUS
EFIAPI
BBTestMediaIntegrityManualTest (
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

  UINT32                               BlockNumber;
  UINTN                                Index;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

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
    BufferSize = BlockSize;
  }

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &Buffer);
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

  //
  // Locate the Handle that the BlockIo interface is bound to
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
      goto FreeBuffer;
    }

    DevicePathStr = NULL;
  }

  //
  // Assertion Point 5.5.2.1
  // Media remove of insert of device must affect the MediaPresent field
  //
  if (RemovableMedia == TRUE) {

    //
    // Insert -> Remove -> Insert or Remove -> Insert -> Remove
    //
    for (Index = 0; Index < 2; Index++) {
      if (MediaPresent == TRUE) {
        SctPrint (L"Remove media in device ");
      } else {
        SctPrint (L"Insert media into device ");
      }

      DevicePathStr = SctDevicePathToStr (DevicePath);
      if (DevicePathStr != NULL) {
        SctPrint (DevicePathStr);

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
          goto FreeBuffer;
        }

        DevicePathStr = NULL;
      }

      if (AutoJudge (50, FALSE, L"\r\nReady?\r\n") != TRUE) {
        goto AssertionPoint2;
      }

      //
      // Call ReadBlocks to force re-install device
      //
      Status = BlockIo->ReadBlocks (
                          BlockIo,
                          MediaId,
                          0,
                          BlockSize,
                          (VOID*)Buffer
                          );
      if (EFI_ERROR(Status)) {
        //
        // No Status check here.
        //
      }

      //
      // Begin to re-locate the BlockIo interface according to the DevicePath
      //
      LocateBlockIoFromDevicePath (&BlockIo, DevicePath, StandardLib);

      if (MediaPresent == BlockIo->Media->MediaPresent) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIoFunctionTestAssertionGuid017,
                     L"EFI_BLOCK_IO_PROTOCOL.Media->MediaPresent,Media remove or insert of device must affect the MediaPresent field",
                     L"%a:%d:Previous MediaPresent=%d, After MediaPresent=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     MediaPresent,
                     BlockIo->Media->MediaPresent
                     );

      //
      // Restore the envionment
      //
      MediaPresent = BlockIo->Media->MediaPresent;
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
  }

  //
  // Assertion Point 5.5.2.2
  // Media change of device must affect the MediaId field and
  // may affect the BlockSize and ReadOnly and Logical Partition field.
  //
AssertionPoint2:
  if (RemovableMedia == TRUE) {

    if (MediaPresent == TRUE) {
      SctPrint (L"Change media  in device ");
    } else {
      SctPrint (L"Insert media into device ");
    }

    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      SctPrint (DevicePathStr);

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
        goto FreeBuffer;
      }

      DevicePathStr = NULL;
    }

    if (AutoJudge (50, FALSE, L"\r\nReady?\r\n") != TRUE) {
      goto FreeBuffer;
    }

    //
    // Call ReadBlocks to force re-install device
    //
    Status = BlockIo->ReadBlocks (
                        BlockIo,
                        MediaId,
                        0,
                        BlockSize,
                        (VOID*)Buffer
                        );
    if (EFI_ERROR(Status)) {
      //
      // No Status check here.
      //
    }

    //
    // Begin to re-locate the BlockIo interface according to the DevicePath
    //
    LocateBlockIoFromDevicePath (&BlockIo, DevicePath, StandardLib);

    //
    // MediaID verificatoin
    //
    if (MediaId == BlockIo->Media->MediaId) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIoFunctionTestAssertionGuid019,
                   L"EFI_BLOCK_IO_PROTOCOL.Media->MediaId,Media remove or insert of device must affect the MediaId field",
                   L"%a:%d:Previous MediaId=%d, After MediaId=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   MediaId,
                   BlockIo->Media->MediaId
                   );

    //
    // User's view about the current attribute of the media
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

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Current Media data field:\n"
                   L"MediaId         =%d\n"
                   L"RemovableMedia  =%d\n"
                   L"MediaPresent    =%d\n"
                   L"LogicalPartition=%d\n"
                   L"ReadOnly        =%d\n"
                   L"WriteCaching    =%d\n"
                   L"BlockSize       =%d\n"
                   L"IoAlign         =%d\n"
                   L"LastBlock       =%lx\n",
                   MediaId,
                   RemovableMedia,
                   MediaPresent,
                   LogicalPartition,
                   ReadOnly,
                   WriteCaching,
                   BlockSize,
                   IoAlign,
                   LastBlock
                   );

    //
    // Output current media data structure
    //

    if (AutoJudge (99, TRUE, L"\r\nCorrect?\r\n") != TRUE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIoFunctionTestAssertionGuid020,
                   L"EFI_BLOCK_IO_PROTOCOL.Media,Media remove or insert of device must affect the MediaId field",
                   L"%a:%d:As user's select",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // Restore environment
    //
    if (MediaPresent == TRUE) {
      SctPrint (L"Change media back in device ");
    } else {
      SctPrint (L"Remove media from device ");
    }

    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      SctPrint (DevicePathStr);

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
        goto FreeBuffer;
      }

      DevicePathStr = NULL;
    }

    if (AutoJudge (50, FALSE, L"\r\nReady?\r\n") != TRUE) {
      goto FreeBuffer;
    }

    //
    // Call ReadBlocks to force re-install device
    //
    Status = BlockIo->ReadBlocks (
                        BlockIo,
                        MediaId,
                        0,
                        BlockSize,
                        (VOID*)Buffer
                        );
    if (EFI_ERROR(Status)) {
      //
      // No Status check here.
      //
    }
  }

FreeBuffer:
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

  return EFI_SUCCESS;
}
