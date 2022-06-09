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

  DiskIoBBFunctionTest.c

Abstract:

  Interface Function Test Cases of Disk I/O Protocol

--*/


#include "SctLib.h"
#include "DiskIoBBTestMain.h"


/**
 *  Entrypoint for EFI_DISK_IO_PROTOCOL.ReadDisk() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 5.1
//
EFI_STATUS
EFIAPI
BBTestReadDiskFunctionAutoTest (
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
  UINTN                                IndexI, IndexJ;
  UINTN                                NewBufferSize;
  UINT64                               Offset;
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

  Buffer = NULL;

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_PASSED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // If the floppy is ejected without "map -r", after first readdisk() or writedisk()
  // the DiskIo will be changed because of reinstall and the original DiskIo will be
  // invalid. Doing operation after this will hang the system. So add check error
  // status after that and once this condition happen return immediately.
  //

  //
  // Assertion Point 5.1.2.1
  // ReadDisk must succeed to read proper data from disk with valid parameter
  //
  if ((MediaPresent == TRUE) && (LastBlock != 0)) {
    for (IndexI = 0; IndexI < 9; IndexI++) {
      //
      // prepare test data
      //
      switch (IndexI) {
        case 0:
          NewBufferSize = BlockSize;
          break;
        case 1:
          NewBufferSize = BufferSize;
          break;
        case 2:
          NewBufferSize = BlockSize + 1;
          break;
        case 3:
          NewBufferSize = BlockSize - 1;
          break;
        case 4:
          NewBufferSize = BufferSize - 10;
          break;
        case 5:
          NewBufferSize = 2*BlockSize;
          break;
        case 6:
          NewBufferSize = 2*BlockSize + 1;
          break;
        case 7:
          NewBufferSize = 2*BlockSize - 1;
          break;
        default:
          NewBufferSize = 0;
          break;
      }

      //
      //parameter verification on NewBufferSize
      //
      if (NewBufferSize > BufferSize) {
        continue;
      }

      for (IndexJ = 0; IndexJ < 30; IndexJ++) {
        //
        // Prepare test data of Offset
        // Following Offset value covers:
        //    Offset at the front part of the disk
        //    Offset at the end   part of the disk
        //    Offset at the middle part of the disk
        //    Offset right at the boundary of the block of the disk
        //    Offset not at the boundary of the block of the disk
        //
        switch (IndexJ) {
          case 0:
            Offset = 0;
            break;
          case 1:
            Offset = BlockSize;
            break;
          case 2:
            Offset = 2 * BlockSize;
            break;
          case 3:
            Offset = SctMultU64x32 (LastBlock , BlockSize);
            break;
          case 4:
            Offset = SctMultU64x32 (LastBlock-1 , BlockSize);
            break;
          case 5:
            Offset = SctMultU64x32 (SctDivU64x32 (LastBlock, 2, &Remainder) , BlockSize);
            break;
          case 6:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize);
            break;
          case 7:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize);
            break;

          case 10:
            Offset = BlockSize + 1;
            break;
          case 11:
            Offset = 2 * BlockSize + 1;
            break;
          case 12:
            Offset = SctMultU64x32 (LastBlock , BlockSize) + 1;
            break;
          case 13:
            Offset = SctMultU64x32 (LastBlock-1 , BlockSize) + 1;
            break;
          case 14:
            Offset = SctMultU64x32 (SctDivU64x32 (LastBlock, 2, &Remainder) , BlockSize) + 1;
            break;
          case 15:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) + 1;
            break;
          case 16:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) + 1;
            break;

          case 20:
            Offset = BlockSize - 1;
            break;
          case 21:
            Offset = 2 * BlockSize - 1;
            break;
          case 22:
            Offset = SctMultU64x32 (LastBlock , BlockSize) - 1;
            break;
          case 23:
            Offset = SctMultU64x32 (LastBlock-1 , BlockSize) - 1;
            break;
          case 24:
            Offset = SctMultU64x32 (SctDivU64x32 (LastBlock, 2, &Remainder) , BlockSize) - 1;
            break;
          case 25:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) - 1;
            break;
          case 26:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) - 1;
            break;

          default:
            Offset = LastOffset + 1;
        }

        // 
        // Check that the Offset value is still valid.
        // 
        // When LastBlock==2 (or 3) in case 25 above the final arithmetic becomes
        // Offset = 0 - 1; 
        // which results in Offset underflowing to become 0xFFFFFFFFFFFFFFFF.
        // This is not covered by any other checks. For example,
        // adding (Offset + NewbufferSize) is (0xFFFFFFFFFFFFFFFF + NewBufferSize),
        // which overflows to the equivalent value (NewBufferSize - 1);
        //
        if ( Offset > LastOffset ) {
          continue;
        }

        //
        // parameter verification on Offset;
        // It's recommended not to touch the last two blocks of the media in test because 
        // some old PATA CD/DVDROM's last two blocks can not be read.
        //
        if ( Offset + NewBufferSize > LastOffset - 2 * BlockSize ) {
          continue;
        }

        //
        // Call ReadDisk with the specified Offset and BufferSize
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
                       gDiskIoFunctionTestAssertionGuid001,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Disk with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       Status
                       );
        if (EFI_ERROR(Status)) {
          gtBS->FreePool (Buffer);
          return Status;
        }
      }//end of loop of Offset - IndexJ
    }//end of loop of BufferSize - IndexI
  }

  gtBS->FreePool (Buffer);

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_DISK_IO_PROTOCOL.WriteDisk() Function Test.
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
BBTestWriteDiskFunctionAutoTest (
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
  UINTN                                IndexI, IndexJ;
  UINTN                                NewBufferSize;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;
  UINT64                               Offset;
  UINTN                                Remainder;

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

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer);
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

  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer2);
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

  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer3);
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

  //
  // If the floppy is ejected without "map -r", after first readdisk() or writedisk()
  // the DiskIo will be changed because of reinstall and the original DiskIo will be
  // invalid. Doing operation after this will hang the system. So add check error
  // status after that and once this condition happen return immediately.
  //

  //
  // Assertion Point 5.2.2.1
  // WriteDisk must succeed to read proper data from disk with valid parameter
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    for (IndexI = 0; IndexI < 9; IndexI++) {
      //
      // prepare test data
      //
      switch (IndexI) {
        case 0:
          NewBufferSize = BlockSize;
          break;
        case 1:
          NewBufferSize = BufferSize;
          break;
        case 2:
          NewBufferSize = BlockSize + 1;
          break;
        case 3:
          NewBufferSize = BlockSize - 1;
          break;
        case 4:
          NewBufferSize = BufferSize - 10;
          break;
        case 5:
          NewBufferSize = 2*BlockSize;
          break;
        case 6:
          NewBufferSize = 2*BlockSize + 1;
          break;
        case 7:
          NewBufferSize = 2*BlockSize - 1;
          break;
        default:
          NewBufferSize = 0;
          break;
      }

      //
      //parameter verification on NewBufferSize
      //
      if (NewBufferSize > BufferSize) {
        continue;
      }

      for (IndexJ = 0; IndexJ < 30; IndexJ++) {
        //
        // Prepare test data of Offset
        // Following Offset value covers:
        //    Offset at the front part of the disk
        //    Offset at the end   part of the disk
        //    Offset at the middle part of the disk
        //    Offset right at the boundary of the block of the disk
        //    Offset not at the boundary of the block of the disk
        //
        switch (IndexJ) {
          case 0:
            Offset = 0;
            break;
          case 1:
            Offset = BlockSize;
            break;
          case 2:
            Offset = 2 * BlockSize;
            break;
          case 3:
            Offset = SctMultU64x32 (LastBlock , BlockSize);
            break;
          case 4:
            Offset = SctMultU64x32 (LastBlock-1 , BlockSize);
            break;
          case 5:
            Offset = SctMultU64x32 (SctDivU64x32 (LastBlock, 2, &Remainder) , BlockSize);
            break;
          case 6:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize);
            break;
          case 7:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize);
            break;

          case 10:
            Offset = BlockSize + 1;
            break;
          case 11:
            Offset = 2 * BlockSize + 1;
            break;
          case 12:
            Offset = SctMultU64x32 (LastBlock , BlockSize) + 1;
            break;
          case 13:
            Offset = SctMultU64x32 (LastBlock-1 , BlockSize) + 1;
            break;
          case 14:
            Offset = SctMultU64x32 (SctDivU64x32 (LastBlock, 2, &Remainder) , BlockSize) + 1;
            break;
          case 15:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) + 1;
            break;
          case 16:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) + 1;
            break;

          case 20:
            Offset = BlockSize - 1;
            break;
          case 21:
            Offset = 2 * BlockSize - 1;
            break;
          case 22:
            Offset = SctMultU64x32 (LastBlock , BlockSize) - 1;
            break;
          case 23:
            Offset = SctMultU64x32 (LastBlock-1 , BlockSize) - 1;
            break;
          case 24:
            Offset = SctMultU64x32 (SctDivU64x32 (LastBlock, 2, &Remainder) , BlockSize) - 1;
            break;
          case 25:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) - 1;
            break;
          case 26:
            Offset = SctMultU64x32 ((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) - 1;
            break;

          default:
            Offset = LastOffset + 1;
        }

        //
        //parameter verification on Offset
        //
        if (Offset + NewBufferSize > LastOffset) {
          continue;
        }

        //
        // Call ReadDisk with the specified Offset and BufferSize
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
                         L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Disk with proper parameter from valid media",
                         L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         StatusRead1
                         );
          gtBS->FreePool (Buffer3);
          gtBS->FreePool (Buffer2);
          gtBS->FreePool (Buffer);
          return StatusRead1;
        }

        //
        // Write Disk with same Offset and BufferSize to write the specified buffer2 to the disk
        // Here Buffer2 is not the same with Buffer
        //
        StatusWrite1 = DiskIo->WriteDisk (
                                 DiskIo,
                                 MediaId,
                                 Offset,
                                 NewBufferSize,
                                 (VOID*)Buffer2
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
                         gDiskIoFunctionTestAssertionGuid003,
                         L"EFI_DISK_IO_PROTOCOL.WriteDisk - Write Disk with proper parameter from valid media",
                         L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         StatusWrite1
                         );
          gtBS->FreePool (Buffer3);
          gtBS->FreePool (Buffer2);
          gtBS->FreePool (Buffer);
          return StatusWrite1;
        }

        //
        // Read Disk with same Offset and BufferSize again and save data into Buffer3
        //
        StatusRead2 = DiskIo->ReadDisk (
                                DiskIo,
                                MediaId,
                                Offset,
                                NewBufferSize,
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
                         L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         StatusRead2
                         );
          gtBS->FreePool (Buffer3);
          gtBS->FreePool (Buffer2);
          gtBS->FreePool (Buffer);
          return StatusRead2;
        }

        //
        // verification on the buffer read in the two steps of ReadDisk call
        //
        CountComp1 = VerifyBuffer (Buffer2, Buffer3, NewBufferSize);
        if (CountComp1 > 0) {
          AssertionTypeComp1 = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeComp1 = EFI_TEST_ASSERTION_PASSED;
        }

        //
        // Write Disk with same Offset and BufferSize to write the buffer read from the first call of ReadDisk
        // to restore the original device
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
                         gDiskIoFunctionTestAssertionGuid005,
                         L"EFI_DISK_IO_PROTOCOL.WriteDisk - Write Disk with proper parameter from valid media",
                         L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         StatusWrite2
                         );
          gtBS->FreePool (Buffer3);
          gtBS->FreePool (Buffer2);
          gtBS->FreePool (Buffer);
          return StatusWrite2;
        }

        //
        // Read Disk with same Offset and BufferSize again and save data into Buffer3
        //
        StatusRead3 = DiskIo->ReadDisk (
                                DiskIo,
                                MediaId,
                                Offset,
                                NewBufferSize,
                                (VOID*)Buffer3
                                );
        if (EFI_ERROR(StatusRead3)) {
          AssertionTypeRead3 = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeRead3 = EFI_TEST_ASSERTION_PASSED;
        }
        if (EFI_ERROR(StatusRead3)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionTypeRead3,
                         gTestGenericFailureGuid,
                         L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Disk with proper parameter from valid media",
                         L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         StatusRead3
                         );
          gtBS->FreePool (Buffer3);
          gtBS->FreePool (Buffer2);
          gtBS->FreePool (Buffer);
          return StatusRead3;
        }

        //
        // verification on the buffer read in the two steps of ReadDisk call
        //
        CountComp2 = VerifyBuffer (Buffer, Buffer3, NewBufferSize);
        if (CountComp2 > 0) {
          AssertionTypeComp2 = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionTypeComp2 = EFI_TEST_ASSERTION_PASSED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead1,
                       gTestGenericFailureGuid,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Disk with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       StatusRead1
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeWrite1,
                       gDiskIoFunctionTestAssertionGuid003,
                       L"EFI_DISK_IO_PROTOCOL.WriteDisk - Write Disk with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       StatusWrite1
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead2,
                       gTestGenericFailureGuid,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Disk with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       StatusRead2
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeComp1,
                       gDiskIoFunctionTestAssertionGuid004,
                       L"EFI_DISK_IO_PROTOCOL.WriteDisk - Verification on two times of reading block with proper parameter from valid media after writting",
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
                       gDiskIoFunctionTestAssertionGuid005,
                       L"EFI_DISK_IO_PROTOCOL.WriteDisk - Write Disk with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       StatusWrite2
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeRead3,
                       gTestGenericFailureGuid,
                       L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read Disk with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, Status = %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       StatusRead3
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionTypeComp2,
                       gDiskIoFunctionTestAssertionGuid006,
                       L"EFI_DISK_IO_PROTOCOL.WriteDisk - Verification on original block after writting",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, Different Buffer Count=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       NewBufferSize,
                       Offset,
                       CountComp2
                       );

      }//end of loop of Offset - IndexJ
    }//end of loop of BufferSize - IndexI
  }

  gtBS->FreePool (Buffer3);
  gtBS->FreePool (Buffer2);
  gtBS->FreePool (Buffer);

  return EFI_SUCCESS;
}
