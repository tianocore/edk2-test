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

  DiskIoBBTestStress.c

Abstract:

  Stress Test Cases of Disk I/O Protocol

--*/


#include "SctLib.h"
#include "DiskIoBBTestMain.h"


/**
 *  Entrypoint for EFI_DISK_IO_PROTOCOL.ReadDisk() Stress Test.
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
BBTestReadDiskStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DISK_IO_PROTOCOL                 *DiskIo;
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
  UINT64                               LastOffset;
  UINTN                                BufferSize;
  UINT8                                *Buffer;
  UINT8                                *Buffer2;
  UINTN                                IndexI, IndexJ;
  UINTN                                NewBufferSize;
  UINT64                               Offset;
  UINTN                                Remainder;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;
  EFI_STATUS                           ReturnStatus;

  EFI_TEST_ASSERTION                   AssertionTypeRead1;
  EFI_TEST_ASSERTION                   AssertionTypeRead2Array[MAX_REPEAT_OF_STRESS_TEST];
  EFI_TEST_ASSERTION                   AssertionTypeComp1Array[MAX_REPEAT_OF_STRESS_TEST];
  EFI_STATUS                           StatusRead1;
  EFI_STATUS                           StatusRead2Array[MAX_REPEAT_OF_STRESS_TEST];
  UINTN                                CountComp1Array[MAX_REPEAT_OF_STRESS_TEST];

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

  DiskIo = (EFI_DISK_IO_PROTOCOL *)ClientInterface;

  Status = LocateBlockIoFromDiskIo (DiskIo, &BlockIo, StandardLib);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Locate Device path of the current DiskIo device
  // and save it into log for investigating
  //
  LocateDevicePathFromDiskIo (DiskIo, &DevicePath, StandardLib);

  DevicePathStr = SctDevicePathToStr (DevicePath);
  if (DevicePathStr != NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   DevicePathStr
                   );
    gtBS->FreePool (DevicePathStr);
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

  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? \
                                MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = SctMultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = 1;
  }

  Buffer  = NULL;
  Buffer2 = NULL;

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **)&Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
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
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // If the floppy is ejected without "map -r", after first readdisk() or writedisk()
  // the DiskIo will be changed because of reinstall and the original DiskIo will be
  // invalid. Doing operation after this will hang the system. So add check error
  // status after that and once this condition happen return immediately.
  //

  ReturnStatus = EFI_SUCCESS;

  //
  // Assertion Point 6.1.2.1
  // ReadDisk must succeed to read proper data from disk with valid parameter
  //
  if (MediaPresent == TRUE) {
    for (IndexI = 0; IndexI < 4; IndexI++) {
      //
      // initialize test data
      //
      switch (IndexI) {
        case 0:
          Offset = 0;
          NewBufferSize = BlockSize;
          break;
        case 1:
          NewBufferSize = BufferSize;
          Offset = LastOffset - NewBufferSize;
          break;
        case 2:
        case 3:
        default:
          Offset = LastOffset + 1;
          NewBufferSize = BufferSize+10;
      }
      //
      // Verify test data
      //
      if ((Offset + NewBufferSize > LastOffset) || (NewBufferSize > BufferSize)) {
        continue;
      }

      //
      // stress test on ReadBlock
      //

      //
      // For the first time, save the data into Buffer
      //
      StatusRead1 = DiskIo->ReadDisk (
                              DiskIo,
                              MediaId,
                              Offset,
                              NewBufferSize,
                              (VOID*)Buffer
                              );

      if (EFI_ERROR(StatusRead1)) {
        AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
      }
      if (EFI_ERROR(StatusRead1)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead1,
                       gDiskIoCombinationTestAssertionGuid001,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Stress test for ReadDisk with same BufferSize and Offset",
                       L"%a:%d:BufferSize = %d, LBA = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       LastOffset,
                       0,
                       StatusRead1
                       );
        ReturnStatus = StatusRead1;
        goto FreeBuffer;
      }

      for (IndexJ = 1; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        //
        // save the data into Buffer2
        //
        StatusRead2Array[IndexJ] = DiskIo->ReadDisk (
                                             DiskIo,
                                             MediaId,
                                             Offset,
                                             NewBufferSize,
                                             (VOID*)Buffer2
                                             );

        if (EFI_ERROR(StatusRead2Array[IndexJ])) {
          AssertionTypeRead2Array[IndexJ] = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeRead2Array[IndexJ] = EFI_TEST_ASSERTION_PASSED;
        }
        if (EFI_ERROR(StatusRead2Array[IndexJ])) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionTypeRead2Array[IndexJ],
                         gDiskIoCombinationTestAssertionGuid001,
                         L"EFI_DISK_IO_PROTOCOL.ReadDisk - Stress test for ReadDisk with same BufferSize and Offset",
                         L"%a:%d:BufferSize = %d, LBA = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         LastOffset,
                         IndexJ,
                         StatusRead2Array[IndexJ]
                         );
          ReturnStatus = StatusRead2Array[IndexJ];
          goto FreeBuffer;
        }

        //
        // Verification on the buffer read by ReadDisk
        // The data read in different times of call ReadDisk should be the same
        //
        CountComp1Array[IndexJ] = VerifyBuffer (Buffer, Buffer2, NewBufferSize);
        if (CountComp1Array[IndexJ] > 0) {
          AssertionTypeComp1Array[IndexJ] = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeComp1Array[IndexJ] = EFI_TEST_ASSERTION_PASSED;
        }
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead1,
                     gDiskIoCombinationTestAssertionGuid001,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - Stress test for ReadDisk with same BufferSize and Offset",
                     L"%a:%d:BufferSize = %d, LBA = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     Offset,
                     LastOffset,
                     0,
                     StatusRead1
                     );

      for (IndexJ = 1; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead2Array[IndexJ],
                       gDiskIoCombinationTestAssertionGuid001,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Stress test for ReadDisk with same BufferSize and Offset",
                       L"%a:%d:BufferSize = %d, LBA = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       LastOffset,
                       IndexJ,
                       StatusRead2Array[IndexJ]
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeComp1Array[IndexJ],
                       gDiskIoCombinationTestAssertionGuid002,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Stress test for ReadDisk with same BufferSize and Offset and Verification on the buffer",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, Index = %d, Different Buffer Count=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       IndexJ,
                       CountComp1Array[IndexJ]
                       );
      }
    }
  }

  //
  // Assertion Point 6.1.2.2
  // Stress test for ReadDisk with same Offset and different BufferSize
  //
  if (MediaPresent == TRUE) {
    NewBufferSize = 10;
    for (IndexI = 1; IndexI < MAX_REPEAT_OF_STRESS_TEST; IndexI++) {
      NewBufferSize += 100;
      //
      // Make sure that the repetition will not exceed 20 times
      //
      if (NewBufferSize > BufferSize) {
        break;
      }

      Status = DiskIo->ReadDisk (
                         DiskIo,
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
                     gDiskIoCombinationTestAssertionGuid003,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - Stress test for ReadDisk with same Offset and different BufferSize",
                     L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Index = %d, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     LastOffset,
                     IndexI,
                     Status
                     );
      if (EFI_ERROR(Status)) {
        ReturnStatus = Status;
        goto FreeBuffer;
      }
    }
  }

  //
  // Assertion Point 6.1.2.3
  // Stress test for ReadDisk with same BufferSize and different Offset
  //
  if (MediaPresent == TRUE) {
    NewBufferSize = 10;
    for (IndexI = 1; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      NewBufferSize += 100;
      //
      // Parameter verification on BufferSize
      //
      if (NewBufferSize > BufferSize) {
        break;
      }

      Offset = 0;
      for (IndexJ = 0; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        Offset += 100;
        //
        // Parameter verification on Offset
        //
        if (Offset + NewBufferSize > LastOffset) {
          break;
        }
        Status = DiskIo->ReadDisk (
                           DiskIo,
                           MediaId,
                           Offset,
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
                       gDiskIoCombinationTestAssertionGuid004,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Stress test for ReadDisk with same BufferSize and different Offset",
                       L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       LastOffset,
                       IndexJ,
                       Status
                       );
        if (EFI_ERROR(Status)) {
          ReturnStatus = Status;
          goto FreeBuffer;
        }
      }
    }
  }

  //
  // Assertion point 6.1.2.4
  // Stress test for ReadDisk on bouncing Offset value
  //
  if (MediaPresent == TRUE) {
    NewBufferSize = 10;
    for (IndexI = 1; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      //
      // For different BufferSize;
      //
      NewBufferSize += 100;
      if (NewBufferSize > BufferSize) {
        break;
      }

      IndexJ = 0;
      while (1) {
        if ((IndexJ > SctDivU64x32 (LastBlock, 2, &Remainder)) || (IndexJ > MAX_REPEAT_OF_STRESS_TEST)) {
          break;
        }

        Offset = IndexJ * 100;

        if (Offset + NewBufferSize > LastOffset) {
          IndexJ++;
          continue;
        }
        //
        // Call ReadDisk with specified BufferSize and Offset being some value start from first block of device
        //
        Status = DiskIo->ReadDisk (
                           DiskIo,
                           MediaId,
                           Offset,
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
                       gDiskIoCombinationTestAssertionGuid005,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Stress test for ReadDisk with bouncing Offset value",
                       L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       LastOffset,
                       IndexJ,
                       Status
                       );
        if (EFI_ERROR(Status)) {
          ReturnStatus = Status;
          goto FreeBuffer;
        }


        //
        // Call ReadDisk with specified BufferSize and Lba being some value start back from last block of device
        //
        Offset = LastOffset - IndexJ*100 - NewBufferSize;
        if (Offset + NewBufferSize > LastOffset) {
          IndexJ++;
          continue;
        }

        Status = DiskIo->ReadDisk (
                           DiskIo,
                           MediaId,
                           Offset,
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
                       gDiskIoCombinationTestAssertionGuid006,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Stress test for ReadDisk with bouncing Offset value",
                       L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       LastOffset,
                       IndexJ,
                       Status
                       );
        if (EFI_ERROR(Status)) {
          ReturnStatus = Status;
          goto FreeBuffer;
        }
        IndexJ++;
      }
    }
  }

FreeBuffer:
  gtBS->FreePool (Buffer2);
  gtBS->FreePool (Buffer);

  return ReturnStatus;
}

/**
 *  Entrypoint for EFI_DISK_IO_PROTOCOL.WriteDisk() Stress Test.
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
BBTestWriteDiskStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DISK_IO_PROTOCOL                 *DiskIo;
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
  UINT64                               LastOffset;
  UINTN                                BufferSize;
  UINT8                                *Buffer;
  UINT8                                *Buffer2;
  UINT8                                *Buffer3;
  UINT8                                *Buffer4;
  UINTN                                IndexI, IndexJ;
  UINTN                                NewBufferSize;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;
  UINT64                               Offset;
  UINTN                                Remainder;
  EFI_STATUS                           ReturnStatus;

  EFI_TEST_ASSERTION                   AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeRead2 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeWrite2 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeComp1 = EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeComp2 = EFI_TEST_ASSERTION_FAILED;
  EFI_STATUS                           StatusRead1 = EFI_SUCCESS;
  EFI_STATUS                           StatusRead2 = EFI_SUCCESS;
  EFI_STATUS                           StatusWrite1 = EFI_SUCCESS;
  EFI_STATUS                           StatusWrite2 = EFI_SUCCESS;
  UINTN                                CountComp1 = 0;
  UINTN                                CountComp2 = 0;

  EFI_TEST_ASSERTION                   AssertionTypeRead2Array[MAX_REPEAT_OF_STRESS_TEST];
  EFI_TEST_ASSERTION                   AssertionTypeWrite1Array[MAX_REPEAT_OF_STRESS_TEST];
  EFI_STATUS                           StatusRead2Array[MAX_REPEAT_OF_STRESS_TEST];
  EFI_STATUS                           StatusWrite1Array[MAX_REPEAT_OF_STRESS_TEST];

  EFI_TEST_ASSERTION                   AssertionTypeRead1Last= EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeRead2Last= EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeWrite1Last= EFI_TEST_ASSERTION_FAILED;
  EFI_TEST_ASSERTION                   AssertionTypeWrite2Last= EFI_TEST_ASSERTION_FAILED;
  EFI_STATUS                           StatusRead1Last= EFI_SUCCESS;
  EFI_STATUS                           StatusRead2Last= EFI_SUCCESS;
  EFI_STATUS                           StatusWrite1Last= EFI_SUCCESS;
  EFI_STATUS                           StatusWrite2Last= EFI_SUCCESS;

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

  DiskIo = (EFI_DISK_IO_PROTOCOL *)ClientInterface;

  Status = LocateBlockIoFromDiskIo (DiskIo, &BlockIo, StandardLib);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Locate Device path of the current DiskIo device
  // and save it into log for investigating
  //
  LocateDevicePathFromDiskIo (DiskIo, &DevicePath, StandardLib);

  DevicePathStr = SctDevicePathToStr (DevicePath);
  if (DevicePathStr != NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   DevicePathStr
                   );
    gtBS->FreePool (DevicePathStr);
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

  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? \
                                MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = SctMultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = 1;
  }

  Buffer  = NULL;
  Buffer2 = NULL;
  Buffer3 = NULL;
  Buffer4 = NULL;

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **)&Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
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
                   L"BS.AllocatePool - Allocate pool",
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
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (Buffer2);
    gtBS->FreePool (Buffer);
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **)&Buffer4);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (Buffer3);
    gtBS->FreePool (Buffer2);
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // If the floppy is ejected without "map -r", after first readdisk() or writedisk()
  // the DiskIo will be changed because of reinstall and the original DiskIo will be
  // invalid. Doing operation after this will hang the system. So add check error
  // status after that and once this condition happen return immediately.
  //

  ReturnStatus = EFI_SUCCESS;

  //
  // Assertion Point 6.2.2.1
  // WriteDisk must succeed to write proper data to disk with valid parameter
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    for (IndexI = 0; IndexI < 4; IndexI++) {
      //
      // initialize test data
      //
      switch (IndexI) {
        case 0:
          Offset = 0;
          NewBufferSize = BlockSize;
          break;
        case 1:
          NewBufferSize = BufferSize;
          Offset = LastOffset - NewBufferSize;
          break;
        case 2:
        case 3:
        default:
          Offset = LastOffset + 1;
          NewBufferSize = BufferSize+10;
      }
      //
      // Verify test data
      //
      if ((Offset + NewBufferSize > LastOffset) || (NewBufferSize>BufferSize)) {
        continue;
      }

      //
      // Call ReadDisk with specified Offset and BufferSize
      //
      StatusRead1 = DiskIo->ReadDisk (
                              DiskIo,
                              MediaId,
                              Offset,
                              NewBufferSize,
                              (VOID*)Buffer
                              );
      if (EFI_ERROR(StatusRead1)) {
        AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
      }
      if (EFI_ERROR(StatusRead1)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead1,
                       gTestGenericFailureGuid,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with valid BufferSize and Offset",
                       L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       LastOffset,
                       StatusRead1
                       );
        ReturnStatus = StatusRead1;
        goto FreeBuffer;
      }
      //
      // stress test on WriteBlock
      //
      for (IndexJ = 0; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        //
        // Write Buffer to disk
        //
        if (IndexJ == 0) {
           StatusWrite1Array[IndexJ] = DiskIo->WriteDisk (
                                                 DiskIo,
                                                 MediaId,
                                                 Offset,
                                                 NewBufferSize,
                                                 (VOID*)Buffer
                                                 );
        } else {
           StatusWrite1Array[IndexJ] = DiskIo->WriteDisk (
                                                 DiskIo,
                                                 MediaId,
                                                 Offset,
                                                 NewBufferSize,
                                                 (VOID*)Buffer2
                                                 );
        }

        if (EFI_ERROR(StatusWrite1Array[IndexJ])) {
          AssertionTypeWrite1Array[IndexJ] = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeWrite1Array[IndexJ] = EFI_TEST_ASSERTION_PASSED;
        }
        if (EFI_ERROR(StatusWrite1Array[IndexJ])) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionTypeWrite1Array[IndexJ],
                         gDiskIoCombinationTestAssertionGuid009,
                         L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with same BufferSize and Offset",
                         L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         LastOffset,
                         IndexJ,
                         StatusWrite1Array[IndexJ]
                         );
          ReturnStatus = StatusWrite1Array[IndexJ];
          goto FreeBuffer;
        }
        //
        // Read Disk with same parameter and save data into buffer2
        //
        StatusRead2Array[IndexJ] = DiskIo->ReadDisk (
                                             DiskIo,
                                             MediaId,
                                             Offset,
                                             NewBufferSize,
                                             (VOID*)Buffer2
                                             );
        if (EFI_ERROR(StatusRead2Array[IndexJ])) {
          AssertionTypeRead2Array[IndexJ] = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeRead2Array[IndexJ] = EFI_TEST_ASSERTION_PASSED;
        }
        if (EFI_ERROR(StatusRead2Array[IndexJ])) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionTypeRead2Array[IndexJ],
                         gTestGenericFailureGuid,
                         L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with valid BufferSize and Offset",
                         L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         LastOffset,
                         IndexJ,
                         StatusRead2Array[IndexJ]
                         );
          ReturnStatus = StatusRead2Array[IndexJ];
          goto FreeBuffer;
        }
      }

      //
      // Verification on the buffer read of first and last call of ReadDisk
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
      StatusWrite2 = DiskIo->WriteDisk (
                               DiskIo,
                               MediaId,
                               Offset,
                               NewBufferSize,
                               (VOID*)Buffer
                               );

      if (EFI_ERROR(StatusWrite2)) {
        AssertionTypeWrite2 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeWrite2 = EFI_TEST_ASSERTION_PASSED;
      }
      if (EFI_ERROR(StatusWrite2)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeWrite2,
                       gDiskIoCombinationTestAssertionGuid011,
                       L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with the same BufferSize and Offset",
                       L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       LastOffset,
                       StatusWrite2
                       );
          ReturnStatus = StatusWrite2;
          goto FreeBuffer;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead1,
                     gTestGenericFailureGuid,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with valid BufferSize and Offset",
                     L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     Offset,
                     LastOffset,
                     StatusRead1
                     );

      for (IndexJ = 0; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeWrite1Array[IndexJ],
                       gDiskIoCombinationTestAssertionGuid009,
                       L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with same BufferSize and Offset",
                       L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       LastOffset,
                       IndexJ,
                       StatusWrite1Array[IndexJ]
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead2Array[IndexJ],
                       gTestGenericFailureGuid,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with valid BufferSize and Offset",
                       L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       LastOffset,
                       IndexJ,
                       StatusRead2Array[IndexJ]
                       );
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeComp1,
                     gDiskIoCombinationTestAssertionGuid010,
                     L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with same BufferSize and Offset and Verification on the buffer",
                     L"%a:%d:BufferSize=%d, Offset=0x%lx, Different Buffer Count=%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     Offset,
                     CountComp1
                     );

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeWrite2,
                     gDiskIoCombinationTestAssertionGuid011,
                     L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with the same BufferSize and Offset",
                     L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     Offset,
                     LastOffset,
                     StatusWrite2
                     );
    }
  }

  //
  // Assertion Point 6.2.2.2
  // Stress test for WriteDisk with same Offset and different BufferSize
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    //
    // Call ReadDisk with Offset being zero and valid BufferSize
    // For backup data
    //
    StatusRead1 = DiskIo->ReadDisk (
                            DiskIo,
                            MediaId,
                            0,
                            BufferSize,
                            (VOID*)Buffer
                            );

    if (EFI_ERROR(StatusRead1)) {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
    }
    if (EFI_ERROR(StatusRead1)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead1,
                     gTestGenericFailureGuid,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with Offset being zero and valid BufferSize",
                     L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     LastOffset,
                     StatusRead1
                     );
      ReturnStatus = StatusRead1;
      goto FreeBuffer;
    }
    //
    // Stress test on WriteDisk
    //
    NewBufferSize = 10;
    IndexI        = 0;
    for (IndexI = 1; IndexI < MAX_REPEAT_OF_STRESS_TEST; IndexI++) {
      NewBufferSize += 100;
      //
      // Make sure that the repetition will not exceed 20 times
      //
      if (NewBufferSize > BufferSize) {
        break;
      }

      StatusWrite1 = DiskIo->WriteDisk (
                               DiskIo,
                               MediaId,
                               0,
                               NewBufferSize,
                               (VOID*)Buffer
                               );

      if (EFI_ERROR(StatusWrite1)) {
        AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeWrite1 = EFI_TEST_ASSERTION_PASSED;
      }
      if (EFI_ERROR(StatusWrite1)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeWrite1,
                       gDiskIoCombinationTestAssertionGuid012,
                       L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with same Offset and different BufferSize",
                       L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Index = %d, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       LastOffset,
                       IndexI,
                       StatusWrite1
                       );
        ReturnStatus = StatusWrite1;
        goto FreeBuffer;
      }
    }

    //
    // Call ReadDisk with Offset being zero and valid BufferSize again
    // For verification
    //
    StatusRead2 = DiskIo->ReadDisk (
                            DiskIo,
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
    if (EFI_ERROR(StatusRead2)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead2,
                     gTestGenericFailureGuid,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with same Offset being zero and valid BufferSize",
                     L"%a:%d:BufferSize = %d, LBA = 0, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     LastOffset,
                     StatusRead2
                     );
      ReturnStatus = StatusRead2;
      goto FreeBuffer;
    }

    //
    // Verification on the buffer read of first and last call of ReadDisk
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
    StatusWrite2 = DiskIo->WriteDisk (
                             DiskIo,
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
    if (EFI_ERROR(StatusWrite2)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeWrite2,
                     gDiskIoCombinationTestAssertionGuid014,
                     L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with Offset being zero and valid BufferSize",
                     L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     LastOffset,
                     StatusWrite2
                     );
      ReturnStatus = StatusWrite2;
      goto FreeBuffer;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead1,
                   gTestGenericFailureGuid,
                   L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with Offset being zero and valid BufferSize",
                   L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastOffset,
                   StatusRead1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite1,
                   gDiskIoCombinationTestAssertionGuid012,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with same Offset and different BufferSize",
                   L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Index = %d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   NewBufferSize,
                   LastOffset,
                   IndexI - 1,
                   StatusWrite1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead2,
                   gTestGenericFailureGuid,
                   L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with same Offset being zero and valid BufferSize",
                   L"%a:%d:BufferSize = %d, LBA = 0, LastOffset = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastOffset,
                   StatusRead2
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeComp1,
                   gDiskIoCombinationTestAssertionGuid013,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with same BufferSize and different Offset and Verification on the buffer",
                   L"%a:%d:BufferSize=%d, Lba=0, Different Buffer Count=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   CountComp1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite2,
                   gDiskIoCombinationTestAssertionGuid014,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with Offset being zero and valid BufferSize",
                   L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastOffset,
                   StatusWrite2
                   );
  }

  //
  // Assertion Point 6.2.2.3
  // Stress test for WriteDisk with same BufferSize and different Offset
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    //
    // Call ReadDisk with Offset being zero and valid BufferSize
    // For backup data
    //
    StatusRead1 = DiskIo->ReadDisk (
                            DiskIo,
                            MediaId,
                            0,
                            BufferSize,
                            (VOID*)Buffer
                            );

    if (EFI_ERROR(StatusRead1)) {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
    }
    if (EFI_ERROR(StatusRead1)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead1,
                     gTestGenericFailureGuid,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with same valid parameter",
                     L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     LastOffset,
                     StatusRead1
                     );
      ReturnStatus = StatusRead1;
      goto FreeBuffer;
    }
    //
    // Stress test on WriteDisk
    //
    NewBufferSize = 10;
    Offset        = 0;
    IndexJ        = 0;
    for (IndexI = 1; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      NewBufferSize += 100;
      //
      // Parameter verification on BufferSize
      //
      if (NewBufferSize > BufferSize) {
        break;
      }

      Offset = 0;
      for (IndexJ = 0; IndexJ < MAX_REPEAT_OF_STRESS_TEST; IndexJ++) {
        Offset += 100;
        //
        // Parameter verification on Lba
        //
        if ((Offset + NewBufferSize > LastOffset) || (Offset + NewBufferSize > BufferSize)) {
          break;
        }

        StatusWrite1 = DiskIo->WriteDisk (
                                 DiskIo,
                                 MediaId,
                                 Offset,
                                 NewBufferSize,
                                 (VOID*)(Buffer+Offset)
                                 );

        if (EFI_ERROR(StatusWrite1)) {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_PASSED;
        }
        if (EFI_ERROR(StatusWrite1)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionTypeWrite1,
                         gDiskIoCombinationTestAssertionGuid015,
                         L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with same BufferSize and different Offset",
                         L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         LastOffset,
                         IndexJ,
                         StatusWrite1
                         );
          ReturnStatus = StatusWrite1;
          goto FreeBuffer;
        }
      }
    }

    //
    // Call ReadDisk with Offset being zero and valid BufferSize again
    // For verification
    //
    StatusRead2 = DiskIo->ReadDisk (
                            DiskIo,
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
    if (EFI_ERROR(StatusRead2)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead2,
                     gTestGenericFailureGuid,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with Offset being zero and valid BufferSize",
                     L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     LastOffset,
                     StatusRead2
                     );
      ReturnStatus = StatusRead2;
      goto FreeBuffer;
    }

    //
    // Verification on the buffer read of first and last call of ReadDisk
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
    StatusWrite2 = DiskIo->WriteDisk (
                             DiskIo,
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
    if (EFI_ERROR(StatusWrite2)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeWrite2,
                     gDiskIoCombinationTestAssertionGuid017,
                     L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with Offset being zero and valid BufferSize",
                     L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     LastBlock,
                     StatusWrite2
                     );
      ReturnStatus = StatusWrite2;
      goto FreeBuffer;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead1,
                   gTestGenericFailureGuid,
                   L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with same valid parameter",
                   L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastOffset,
                   StatusRead1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite1,
                   gDiskIoCombinationTestAssertionGuid015,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with same BufferSize and different Offset",
                   L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   NewBufferSize,
                   Offset,
                   LastOffset,
                   IndexJ - 1,
                   StatusWrite1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead2,
                   gTestGenericFailureGuid,
                   L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with Offset being zero and valid BufferSize",
                   L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastOffset,
                   StatusRead2
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeComp1,
                   gDiskIoCombinationTestAssertionGuid016,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with different BufferSize and same LBA and Verification on the buffer",
                   L"%a:%d:BufferSize=%d, Lba=0, Different Buffer Count=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   CountComp1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite2,
                   gDiskIoCombinationTestAssertionGuid017,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with Offset being zero and valid BufferSize",
                   L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastBlock,
                   StatusWrite2
                   );
  }

  //
  // Assertion point 6.2.2.4
  // Stress test for WriteDisk on bouncing Offset value
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    //
    // backup start and last BufferSize of block on device and save them into Buffer & Buffer2
    //
    StatusRead1 = DiskIo->ReadDisk (
                            DiskIo,
                            MediaId,
                            0,
                            BufferSize,
                            (VOID*)Buffer
                            );

    if (EFI_ERROR(StatusRead1)) {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeRead1 = EFI_TEST_ASSERTION_PASSED;
    }
    if (EFI_ERROR(StatusRead1)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead1,
                     gTestGenericFailureGuid,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with specified value",
                     L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     LastOffset,
                     StatusRead1
                     );
      ReturnStatus = StatusRead1;
      goto FreeBuffer;
    }

    Offset = LastOffset - BufferSize;
    StatusRead1Last = DiskIo->ReadDisk (
                                DiskIo,
                                MediaId,
                                Offset,
                                BufferSize,
                                (VOID*)Buffer2
                                );

    if (EFI_ERROR(StatusRead1Last)) {
      AssertionTypeRead1Last = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeRead1Last = EFI_TEST_ASSERTION_PASSED;
    }
    if (EFI_ERROR(StatusRead1Last)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeRead1Last,
                     gTestGenericFailureGuid,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with specified value",
                     L"%a:%d:BufferSize = %d, Offset = 0,LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     LastOffset,
                     StatusRead1Last
                     );
      ReturnStatus = StatusRead1Last;
      goto FreeBuffer;
    }

    NewBufferSize = 10;
    Offset        = 0;
    IndexJ        = 0;
    for (IndexI = 1; IndexI < MAX_DIFFERENT_BUFFERSIZE_FOR_TEST; IndexI++) {
      //
      // For different BufferSize;
      //
      NewBufferSize += 100;
      if (NewBufferSize > BufferSize) {
        break;
      }

      IndexJ = 0;
      while (1) {
        if ((IndexJ > SctDivU64x32 (LastBlock, 2, &Remainder)) || (IndexJ > MAX_REPEAT_OF_STRESS_TEST)) {
          break;
        }

        Offset = IndexJ * 100;

        if (Offset + NewBufferSize > LastOffset) {
          IndexJ++;
          continue;
        }
        //
        // Call WriteDisk with specified BufferSize and Offset being some value start from first block of device
        //
        StatusWrite1 = DiskIo->WriteDisk (
                                 DiskIo,
                                 MediaId,
                                 Offset,
                                 NewBufferSize,
                                 (VOID*)(Buffer+Offset)
                                 );

        if (EFI_ERROR(StatusWrite1)) {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeWrite1 = EFI_TEST_ASSERTION_PASSED;
        }
        if (EFI_ERROR(StatusWrite1)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionTypeWrite1,
                         gDiskIoCombinationTestAssertionGuid018,
                         L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with bouncing LBA value",
                         L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         LastOffset,
                         IndexJ,
                         StatusWrite1
                         );
          ReturnStatus = StatusWrite1;
          goto FreeBuffer;
        }

        Offset = LastOffset - IndexJ*100 - NewBufferSize;
        if (Offset + NewBufferSize > LastOffset) {
          IndexJ++;
          continue;
        }
        //
        // Call WriteDisk with specified BufferSize and Offset being some value start back from last block of device
        //
        StatusWrite1Last = DiskIo->WriteDisk (
                                     DiskIo,
                                     MediaId,
                                     Offset,
                                     NewBufferSize,
                                     (VOID*)(Buffer2 - 100*IndexJ + BufferSize - NewBufferSize)
                                     );

        if (EFI_ERROR(StatusWrite1Last)) {
          AssertionTypeWrite1Last = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeWrite1Last = EFI_TEST_ASSERTION_PASSED;
        }
        if (EFI_ERROR(StatusWrite1Last)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionTypeWrite1Last,
                         gDiskIoCombinationTestAssertionGuid019,
                         L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with bouncing Offset value",
                         L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         LastOffset,
                         IndexJ,
                         StatusWrite1Last
                         );
          ReturnStatus = StatusWrite1Last;
          goto FreeBuffer;
        }
        IndexJ++;
      }

      //
      // Read Block with same Offset and BufferSize again and save data into Buffer3
      //
      StatusRead2 = DiskIo->ReadDisk (
                              DiskIo,
                              MediaId,
                              0,
                              BufferSize,
                              (VOID*)Buffer3
                              );
      if (EFI_ERROR(StatusRead2)) {
        AssertionTypeRead2 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeRead2 = EFI_TEST_ASSERTION_PASSED;
      }
      if (EFI_ERROR(StatusRead2)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead2,
                       gTestGenericFailureGuid,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Disk with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       BufferSize,
                       StatusRead2
                       );
        ReturnStatus = StatusRead2;
        goto FreeBuffer;
      }

      //
      // verification on the buffer read in the two steps of ReadDisk call
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
      Offset = LastOffset - BufferSize;
      StatusRead2Last = DiskIo->ReadDisk (
                                  DiskIo,
                                  MediaId,
                                  Offset,
                                  BufferSize,
                                  (VOID*)Buffer4
                                  );
      if (EFI_ERROR(StatusRead2Last)) {
        AssertionTypeRead2Last = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeRead2Last = EFI_TEST_ASSERTION_PASSED;
      }
      if (EFI_ERROR(StatusRead2Last)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead2Last,
                       gTestGenericFailureGuid,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Block with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       BufferSize,
                       Offset,
                       StatusRead2Last
                       );
        ReturnStatus = StatusRead2Last;
        goto FreeBuffer;
      }

      //
      // verification on the buffer read in the two steps of ReadDisk call
      //
      CountComp2 = VerifyBuffer (Buffer2, Buffer4, BufferSize);
      if (CountComp2 > 0) {
        AssertionTypeComp2 = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionTypeComp2 = EFI_TEST_ASSERTION_PASSED;
      }

      if (EFI_ERROR(StatusWrite1)          || EFI_ERROR(StatusWrite1Last)
             || EFI_ERROR(StatusRead2)     || (CountComp1 > 0)
             || EFI_ERROR(StatusRead2Last) || (CountComp2 > 0)) {
        break;
      }
      //
      // Next IndexI for another NewBufferSize
      //
    }

    //
    // Rewrite buffer back to block device
    //
    StatusWrite2 = DiskIo->WriteDisk (
                             DiskIo,
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
    if (EFI_ERROR(StatusWrite2)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeWrite2,
                     gDiskIoCombinationTestAssertionGuid022,
                     L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with specified value",
                     L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     LastOffset,
                     StatusWrite2
                     );
      ReturnStatus = StatusWrite2;
      goto FreeBuffer;
    }

    Offset = LastOffset - BufferSize;
    StatusWrite2Last = DiskIo->WriteDisk (
                                 DiskIo,
                                 MediaId,
                                 Offset,
                                 BufferSize,
                                 (VOID*)Buffer2
                                 );

    if (EFI_ERROR(StatusWrite2Last)) {
      AssertionTypeWrite2Last = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionTypeWrite2Last = EFI_TEST_ASSERTION_PASSED;
    }
    if (EFI_ERROR(StatusWrite2Last)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionTypeWrite2Last,
                     gDiskIoCombinationTestAssertionGuid023,
                     L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with specified value",
                     L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffest = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     Offset,
                     LastOffset,
                     StatusWrite2Last
                     );
      ReturnStatus = StatusWrite2Last;
      goto FreeBuffer;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead1,
                   gTestGenericFailureGuid,
                   L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with specified value",
                   L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastOffset,
                   StatusRead1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead1Last,
                   gTestGenericFailureGuid,
                   L"EFI_DISK_IO_PROTOCOL.ReadDisk - ReadDisk with specified value",
                   L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   Offset,
                   LastOffset,
                   StatusRead1Last
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite1,
                   gDiskIoCombinationTestAssertionGuid018,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with bouncing LBA value",
                   L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   NewBufferSize,
                   Offset,
                   LastOffset,
                   IndexJ - 1,
                   StatusWrite1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite1Last,
                   gDiskIoCombinationTestAssertionGuid019,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Stress test for WriteDisk with bouncing Offset value",
                   L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffset = 0x%lx, Index = %d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   NewBufferSize,
                   Offset,
                   LastOffset,
                   IndexJ - 1,
                   StatusWrite1Last
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead2,
                   gTestGenericFailureGuid,
                   L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Disk with proper parameter from valid media",
                   L"%a:%d:BufferSize=%d, Offset=0, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   StatusRead2
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeComp1,
                   gDiskIoCombinationTestAssertionGuid020,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Verification on two times of reading disk after writing on bouncing LBA value",
                   L"%a:%d:BufferSize=%d, Offset=0, Different Buffer Count=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   CountComp1
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeRead2Last,
                   gTestGenericFailureGuid,
                   L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Block with proper parameter from valid media",
                   L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   Offset,
                   StatusRead2Last
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeComp2,
                   gDiskIoCombinationTestAssertionGuid021,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Verification on two times of reading disk after writing on bouncing Offset value",
                   L"%a:%d:BufferSize=%d, Offset=0x%lx, Different Buffer Count=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   Offset,
                   CountComp2
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite2,
                   gDiskIoCombinationTestAssertionGuid022,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with specified value",
                   L"%a:%d:BufferSize = %d, Offset = 0, LastOffset = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   LastOffset,
                   StatusWrite2
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionTypeWrite2Last,
                   gDiskIoCombinationTestAssertionGuid023,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - WriteDisk with specified value",
                   L"%a:%d:BufferSize = %d, Offset = 0x%lx, LastOffest = 0x%lx, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   Offset,
                   LastOffset,
                   StatusWrite2Last
                   );
  }

FreeBuffer:
  gtBS->FreePool (Buffer4);
  gtBS->FreePool (Buffer3);
  gtBS->FreePool (Buffer2);
  gtBS->FreePool (Buffer);

  return ReturnStatus;
}
