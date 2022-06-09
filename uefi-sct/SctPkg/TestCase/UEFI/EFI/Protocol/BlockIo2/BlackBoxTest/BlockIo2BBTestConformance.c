/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2011 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  BlockIo2BBTestConformance.c

Abstract:

  Consistency Test Cases of Block I/O 2 Protocol

--*/


#include "SctLib.h"
#include "BlockIo2BBTestMain.h"

STATIC BOOLEAN                         BlkIO2Finished;

STATIC
VOID
NotifyFunc (
  EFI_EVENT               Event,
  BOOLEAN                 *Finished
  )
{
  *Finished = TRUE;
  return ;
}


/**
 *  Entrypoint for EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestReadBlocksExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib = NULL;
  EFI_STATUS                           Status, StatusSync, StatusAsync, FailedStatusSync, FailedStatusAsync;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2 = NULL;
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
  UINTN                                Index;
  UINT32                               NewMediaId;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  UINT32                               NewIoAlign;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath = NULL;
  CHAR16                               *DevicePathStr = NULL;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenSync;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenAsync;
  CHAR16                               *ErrorOutput = L"";


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

  BlockIo2 = (EFI_BLOCK_IO2_PROTOCOL *)ClientInterface;

  //
  // Locate & record DevicePath for further investigation
  //
  LocateDevicePathFromBlockIo2 (BlockIo2, &DevicePath, StandardLib);

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
  // Initialize Blk IO2 ReadEx token event
  //
  //
  // Sync Token Init
  //
  BlkIo2TokenSync.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  //
  // Async Token Init
  //
  BlkIO2Finished = FALSE;
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) NotifyFunc,
                   &BlkIO2Finished,
                   &BlkIo2TokenAsync.Event
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat Read BlockEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->CloseEvent (BlkIo2TokenAsync.Event);
    return Status;
  }
  BlkIo2TokenAsync.TransactionStatus = EFI_NOT_READY;

  
  //
  // Initialize variable
  //
  MediaId           = BlockIo2->Media->MediaId;
  RemovableMedia    = BlockIo2->Media->RemovableMedia;
  MediaPresent      = BlockIo2->Media->MediaPresent;
  LogicalPartition  = BlockIo2->Media->LogicalPartition;
  ReadOnly          = BlockIo2->Media->ReadOnly;
  WriteCaching      = BlockIo2->Media->WriteCaching;
  BlockSize         = BlockIo2->Media->BlockSize;
  IoAlign           = BlockIo2->Media->IoAlign;
  LastBlock         = BlockIo2->Media->LastBlock;

  BlockNumber       = (UINT32) MINIMUM(LastBlock + 1, MAX_NUMBER_OF_READ_BLOCK_BUFFER);
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
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }
  //
  // poisoned data buffer for debug
  //
  SctSetMem ((VOID *)Buffer, BufferSize, 0xAB);
  

  //
  // Assertion Points 4.1.2.1
  // ReadBlocksEx should not succeed to read from device
  // When MedialId is not the id for the current media in the device both in Sync & Async case
  //

  if (MediaPresent == TRUE) {
    for (Index = 0; Index < 5; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
      case 0:
        NewMediaId = MediaId + 5;
        break;
      case 1:
        NewMediaId = MediaId + 1;
        break;
      case 2:
        NewMediaId = MediaId - 1;
        break;
      case 3:
        NewMediaId = MediaId - 5;
        break;
      case 4:
        NewMediaId = 0;
        break;
      default:
        NewMediaId = MediaId;
      }

      //
      // Verify test data
      //
      if (NewMediaId == MediaId) {
        continue;
      }

      //
      // Sync Call ReadBlocksEx with false MediaID
      //
      StatusSync = BlockIo2->ReadBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               0,
                               &BlkIo2TokenSync,
                               BufferSize,
                               (VOID*)Buffer
                               );
      //
      // Async Call ReadBlocksEx with false MediaID
      //
      StatusAsync = BlockIo2->ReadBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BufferSize,
                                (VOID*)Buffer
                                );
      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      if (StatusSync == EFI_MEDIA_CHANGED 
       && StatusAsync == EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        ErrorOutput = L"False MediaID";
      }

      //
      // Sync Call ReadBlocksEx with false MediaID & invalid LBA
      //
      StatusSync = BlockIo2->ReadBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               LastBlock + 1,
                               &BlkIo2TokenSync,
                               BufferSize,
                               (VOID*)Buffer
                               );
      //
      // Async Call ReadBlocksEx with false MediaID  & invalid LBA
      //
      StatusAsync = BlockIo2->ReadBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                LastBlock + 1,
                                &BlkIo2TokenAsync,
                                BufferSize,
                                (VOID*)Buffer
                                );
  
      if (StatusSync != EFI_MEDIA_CHANGED 
       || StatusAsync != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"False MediaID & Invalid LBA";
      }
      
      //
      // Sync Call ReadBlocksEx with false MediaID & invalid BufferSize
      //
      StatusSync = BlockIo2->ReadBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               0,
                               &BlkIo2TokenSync,
                               BufferSize - 1,
                               (VOID*)Buffer
                               );
      //
      // Async Call ReadBlocksEx with false MediaID  & invalid BufferSize
      //
      StatusAsync = BlockIo2->ReadBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BufferSize - 1,
                                (VOID*)Buffer
                                );
     
      if (StatusSync != EFI_MEDIA_CHANGED 
       || StatusAsync != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"False MediaID & Invalid BufferSize";
      }

      //
      // Sync Call ReadBlocksEx with false MediaID & invalid 0 BufferSize
      //
      StatusSync = BlockIo2->ReadBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               0,
                               &BlkIo2TokenSync,
                               0,
                               (VOID*)Buffer
                               );
      //
      // Async Call ReadBlocksEx with false MediaID  &  invalid 0 BufferSize
      //
      StatusAsync = BlockIo2->ReadBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                0,
                                &BlkIo2TokenAsync,
                                0,
                                (VOID*)Buffer
                                );
      
      if (StatusSync != EFI_MEDIA_CHANGED 
       || StatusAsync != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"False MediaID & Invalid 0 BufferSize";
      }
      
      if (IoAlign > 1) {
        //
        // Sync Call ReadBlocksEx with false MediaID & wrong aligned Buffer
        //
        StatusSync = BlockIo2->ReadBlocksEx (
                                 BlockIo2,
                                 NewMediaId,
                                 0,
                                 &BlkIo2TokenSync,
                                 BufferSize - BlockSize,
                                 (VOID*)(Buffer + 1)
                                 );
        //
        // Async Call ReadBlocksEx with false MediaID  &  wrong aligned Buffer
        //
        StatusAsync = BlockIo2->ReadBlocksEx (
                                  BlockIo2,
                                  NewMediaId,
                                  0,
                                  &BlkIo2TokenAsync,
                                  BufferSize - BlockSize,
                                  (VOID*)(Buffer + 1)
                                  );

       if (StatusSync != EFI_MEDIA_CHANGED 
        || StatusAsync != EFI_MEDIA_CHANGED) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          FailedStatusSync = StatusSync;
          FailedStatusAsync = StatusAsync;
          ErrorOutput = L"False MediaID & Wrong aligned Buffer";
        }
      }

      //
      // Sync Call ReadBlocksEx with false MediaID & invalid 0 BufferSize
      //
      StatusSync = BlockIo2->ReadBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               0,
                               &BlkIo2TokenSync,
                               BufferSize,
                               NULL
                               );
      //
      // Async Call ReadBlocksEx with false MediaID  &  invalid 0 BufferSize
      //
      StatusAsync = BlockIo2->ReadBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BufferSize,
                                NULL
                                );
   
      if (StatusSync != EFI_MEDIA_CHANGED 
       || StatusAsync != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"False MediaID & Invalid NULL Buffer";
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIo2ConformanceTestAssertionGuid001,
                     L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Sync & Async Read block with MediaId not being the id for the current media in the device",
                     L"%a:%d: %s Actual MediaID=%d, MediaID=%d, StatusSync=%r, StatusAsync=%r, Expected=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     ErrorOutput,
                     MediaId,
                     NewMediaId,
                     FailedStatusSync,
                     FailedStatusAsync,
                     EFI_MEDIA_CHANGED
                     );
    }
  }

  //
  // Assertion point 4.1.2.2
  // ReadBlocksEx should not suceed to read from device when BufferSize is not
  // a multiple of the intrinsic block size of the device
  //
  if ((MediaPresent == TRUE) && (BlockSize != 1)) {
    for (Index = 0; Index < 4; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
      case 0:
        NewBufferSize = BlockSize + 1;
        break;
      case 1:
        NewBufferSize = 2 * BlockSize - 1;
        break;
      case 2:
        NewBufferSize = 2 * BlockSize + 1;
        break;
      case 3:
        NewBufferSize = 3 * BlockSize - 1;
        break;
      default:
        NewBufferSize = BufferSize;
        break;
      }

      //
      // Verify test data
      //
      if (((NewBufferSize % BlockSize) == 0) || (NewBufferSize > BufferSize)) {
        continue;
      }
      //
      // Sync Call ReadBlocksEx with false buffersize
      //
      StatusSync = BlockIo2->ReadBlocksEx (
                               BlockIo2,
                               MediaId,
                               0,
                               &BlkIo2TokenSync,
                               NewBufferSize,
                               (VOID*)Buffer
                               );
      //
      // Async Call ReadBlocksEx with false buffersize
      //
      StatusAsync = BlockIo2->ReadBlocksEx (
                                BlockIo2,
                                MediaId,
                                0,
                                &BlkIo2TokenAsync,
                                NewBufferSize,
                                (VOID*)Buffer
                                );
    
      if (StatusSync == EFI_BAD_BUFFER_SIZE
       && StatusAsync == EFI_BAD_BUFFER_SIZE) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIo2ConformanceTestAssertionGuid002,
                     L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Sync & Asnyc Read block with BufferSize not being a multiple of the intrinsic block size of the device",
                     L"%a:%d:BufferSize=%d, BlockSize=%d, StatusSync=%r, StatusAsync=%r, Expected=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     BlockSize,
                     StatusSync,
                     StatusAsync,
                     EFI_BAD_BUFFER_SIZE
                     );
    }
  }

  //
  // Assertion Point 4.1.2.3
  // ReadBlocksEx should not succeed to read from device with invalid LBA parameter
  //
  if (MediaPresent == TRUE) {
    for (Index = 0; Index < 6; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
      case 0:
        NewLba = LastBlock + 1;
        break;
      case 1:
        NewLba = LastBlock + 100;
        break;
      case 2:
        NewLba = LastBlock - BufferSize/BlockSize + 1;
        break;
      case 3:
        NewLba = LastBlock - BufferSize/BlockSize + 2;
        break;
      case 4:
        NewLba = LastBlock - BufferSize/BlockSize + 3;
        break;
      case 5:
        NewLba = LastBlock - BufferSize/BlockSize + 100;
        break;
      default:
        NewLba = 0;
        break;
      }

      //
      // Verify test data
      //
      if ((NewLba + BufferSize/BlockSize) <= (LastBlock + 1)) {
        continue;
      }

      //
      // Sync Call ReadBlocksEx with invalid LBA
      //
      StatusSync = BlockIo2->ReadBlocksEx (
                               BlockIo2,
                               MediaId,
                               NewLba,
                               &BlkIo2TokenSync,
                               BufferSize,
                               (VOID*)Buffer
                               );
      //
      // Async Call ReadBlocksEx with invalid LBA
      //
      StatusAsync = BlockIo2->ReadBlocksEx (
                                BlockIo2,
                                MediaId,
                                NewLba,
                                &BlkIo2TokenAsync,
                                BufferSize,
                                (VOID*)Buffer
                                );
    
      if (StatusSync == EFI_INVALID_PARAMETER
       && StatusAsync == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIo2ConformanceTestAssertionGuid003,
                     L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Sync & Async Read block with invalid LBA parameter",
                     L"%a:%d:BufferSize=%d, BlockSize=%d, LBA=0x%lx, LastBlock=0x%lx, StatusSync=%r, StatusAsync=%r, Expected=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     BlockSize,
                     NewLba,
                     LastBlock,
                     StatusSync,
                     StatusAsync,
                     EFI_INVALID_PARAMETER
                     );
    }
  }

  //
  // Assertion Point 
  // ReadBlocksEx should not suceed if datasize can be returned is smaller than buffersize passed in
  //
  if (MediaPresent == TRUE &&  LastBlock > 0) {
    //
    // Sync Call ReadBlocksEx with data buffer bigger than data availble for read
    //
    StatusSync = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             MediaId,
                             LastBlock - 1,
                             &BlkIo2TokenSync,
                             BufferSize,
                             (VOID*)Buffer
                             );
    //
    // Async Call ReadBlocksEx with data buffer bigger than data availble for read
    //
    StatusAsync = BlockIo2->ReadBlocksEx (
                              BlockIo2,
                              MediaId,
                              LastBlock - 1,
                              &BlkIo2TokenAsync,
                              BufferSize,
                              (VOID*)Buffer
                              );

    if (StatusSync == EFI_INVALID_PARAMETER
     && StatusAsync == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIo2ConformanceTestAssertionGuid004,
                   L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Sync & Async Read block returns data which are smaller than BufferSize passed in",
                   L"%a:%d:BufferSize=%d, StatusSync=%r, StatusAsync=%r, Expected=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   StatusSync,
                   StatusAsync,
                   EFI_INVALID_PARAMETER
                   );

  }
  

  //
  //
  //
  //
  // Assertion Point 4.1.2.5
  // ReadBlocksEx should not succed to read from device with Buffer is not on proper alignment
  //
  if ((MediaPresent == TRUE) && (IoAlign > 1)) {
    //
    // if IoAlign is large than 1, then it must be a power of 2
    //
    if ((IoAlign & (IoAlign - 1)) == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIo2ConformanceTestAssertionGuid005,
                   L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Sync & Async Read block alignment should be power of 2",
                   L"%a:%d:Aligment=0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   IoAlign
                   );
   
    for (NewIoAlign = (IoAlign >> 1); NewIoAlign > 0 ; NewIoAlign >>= 1) {
      //
      // Sync Call ReadBlocksEx with buffer of wrong aligment 
      //
      StatusSync = BlockIo2->ReadBlocksEx (
                               BlockIo2,
                               MediaId,
                               0,
                               &BlkIo2TokenSync,
                               BlockSize,
                               (VOID*)(Buffer + NewIoAlign)
                               );
      //
      // Async Call ReadBlocksEx with buffer of wrong aligment 
      //
      StatusAsync = BlockIo2->ReadBlocksEx (
                                BlockIo2,
                                MediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BlockSize,
                                (VOID*)(Buffer + NewIoAlign)
                                );
      if (StatusSync == EFI_INVALID_PARAMETER
       && StatusAsync == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIo2ConformanceTestAssertionGuid005,
                     L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Sync & Async Read block with unaligned data buffer",
                     L"%a:%d:Aligment=%d, StatusSync=%r, StatusAsync=%r, Expected=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewIoAlign,
                     StatusSync,
                     StatusAsync,
                     EFI_INVALID_PARAMETER
                     );
    }
  }

  //
  // Assertion Point 4.1.2.4
  // ReadBlocksEx should not succeed to read from device that with no media present in the device
  //
  if (MediaPresent == FALSE) {
    ErrorOutput = L"";

    //
    // Sync Call ReadBlocksEx with proper parameter
    //
    StatusSync = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             MediaId,
                             0,
                             &BlkIo2TokenSync,
                             BufferSize,
                             (VOID*)Buffer
                             );
    //
    // Async Call ReadBlocksEx with proper parameter
    //
    StatusAsync = BlockIo2->ReadBlocksEx (
                              BlockIo2,
                              MediaId,
                              0,
                              &BlkIo2TokenAsync,
                              BufferSize,
                              (VOID*)Buffer
                              );
    FailedStatusSync = StatusSync;
    FailedStatusAsync = StatusAsync;
    if (StatusSync == EFI_NO_MEDIA
     && StatusAsync == EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    

    //
    // Sync Call ReadBlocksEx with invalid LBA
    //
    StatusSync = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             MediaId,
                             LastBlock + 1,
                             &BlkIo2TokenSync,
                             BufferSize,
                             (VOID*)Buffer
                             );
    //
    // Async Call ReadBlocksEx with invalid LBA
    //
    StatusAsync = BlockIo2->ReadBlocksEx (
                              BlockIo2,
                              MediaId,
                              LastBlock + 1,
                              &BlkIo2TokenAsync,
                              BufferSize,
                              (VOID*)Buffer
                              ); 

    if (StatusSync != EFI_NO_MEDIA
     || StatusAsync != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      ErrorOutput = L"Invalid LBA";
    }

    //
    // Sync Call ReadBlocksEx with invalid BufferSize
    //
    StatusSync = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             MediaId,
                             0,
                             &BlkIo2TokenSync,
                             BufferSize - 1,
                             (VOID*)Buffer
                             );
    //
    // Async Call ReadBlocksEx with invalid BufferSize
    //
    StatusAsync = BlockIo2->ReadBlocksEx (
                              BlockIo2,
                              MediaId,
                              0,
                              &BlkIo2TokenAsync,
                              BufferSize - 1,
                              (VOID*)Buffer
                              ); 

    if (StatusSync != EFI_NO_MEDIA
     || StatusAsync != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      ErrorOutput = L"Invalid BufferSize";
    }

    //
    // Sync Call ReadBlocksEx with invalid 0 BufferSize
    //
    StatusSync = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             MediaId,
                             0,
                             &BlkIo2TokenSync,
                             0,
                             (VOID*)Buffer
                             );
    //
    // Async Call ReadBlocksEx with invalid 0 BufferSize
    //
    StatusAsync = BlockIo2->ReadBlocksEx (
                              BlockIo2,
                              MediaId,
                              0,
                              &BlkIo2TokenAsync,
                              0,
                              (VOID*)Buffer
                              ); 
    if (StatusSync != EFI_NO_MEDIA
     || StatusAsync != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      ErrorOutput = L"Zero BufferSize";
    }

    if (IoAlign > 1) {
      //
      // Sync Call ReadBlocksEx with unaligned Buffer
      //
      StatusSync = BlockIo2->ReadBlocksEx (
                               BlockIo2,
                               MediaId,
                               0,
                               &BlkIo2TokenSync,
                               BufferSize - BlockSize,
                               (VOID*)(Buffer + 1)
                               );
      //
      // Async Call ReadBlocksEx with unaligned Buffer
      //
      StatusAsync = BlockIo2->ReadBlocksEx (
                                BlockIo2,
                                MediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BufferSize - BlockSize,
                                (VOID*)(Buffer + 1)
                                ); 

      if (StatusSync != EFI_NO_MEDIA
       || StatusAsync != EFI_NO_MEDIA) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"Unaligned Buffer";
      }
    }

    //
    // Sync Call ReadBlocksEx with invalid NULL Buffer
    //
    StatusSync = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             MediaId,
                             0,
                             &BlkIo2TokenSync,
                             BufferSize,
                             NULL
                             );
    //
    // Async Call ReadBlocksEx with invalid NULL Buffer
    //
    StatusAsync = BlockIo2->ReadBlocksEx (
                              BlockIo2,
                              MediaId,
                              0,
                              &BlkIo2TokenAsync,
                              BufferSize ,
                              NULL
                              ); 
    if (StatusSync != EFI_NO_MEDIA
     || StatusAsync != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      ErrorOutput = L"NULL Buffer";
    }
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIo2ConformanceTestAssertionGuid006,
                   L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Sync & Async Read block from device without media present in the device",
                   L"%a:%d: %s BufferSize=%d, StatusSync=%r, StatusAsync=%r, Expected=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ErrorOutput,
                   BufferSize,
                   FailedStatusSync,
                   FailedStatusAsync,
                   EFI_NO_MEDIA
                   );
  }

  
  //
  // Close Block IO2 ReadEx block Event
  //
  gtBS->CloseEvent (BlkIo2TokenAsync.Event);

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
 *  Entrypoint for EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestWriteBlocksExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status, StatusSync, StatusAsync, FailedStatusSync, FailedStatusAsync;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2;
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
  UINT32                               NewMediaId;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  UINT32                               NewIoAlign;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenSync;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenAsync;
  CHAR16                               *ErrorOutput = L"";


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

  BlockIo2 = (EFI_BLOCK_IO2_PROTOCOL *)ClientInterface;

  //
  // Locate & record DevicePath for further investigation
  //
  LocateDevicePathFromBlockIo2 (BlockIo2, &DevicePath, StandardLib);

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
  // Initialize Blk IO2 WriteEx token event
  //
  //
  // Sync Token Init
  //
  BlkIo2TokenSync.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  //
  // Async Token Init
  //
  BlkIO2Finished = FALSE;
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) NotifyFunc,
                   &BlkIO2Finished,
                   &BlkIo2TokenAsync.Event
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat Read BlockEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->CloseEvent (BlkIo2TokenAsync.Event);
    return Status;
  }
  BlkIo2TokenAsync.TransactionStatus = EFI_NOT_READY;


  //
  // Initialize variable
  //
  MediaId           = BlockIo2->Media->MediaId;
  RemovableMedia    = BlockIo2->Media->RemovableMedia;
  MediaPresent      = BlockIo2->Media->MediaPresent;
  LogicalPartition  = BlockIo2->Media->LogicalPartition;
  ReadOnly          = BlockIo2->Media->ReadOnly;
  WriteCaching      = BlockIo2->Media->WriteCaching;
  BlockSize         = BlockIo2->Media->BlockSize;
  IoAlign           = BlockIo2->Media->IoAlign;
  LastBlock         = BlockIo2->Media->LastBlock;

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
                   L"AllocateAlignedPool - Allocate aligned buffer for write testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // poisoned data buffer for debug
  //
  SctSetMem ((VOID *)Buffer, BufferSize, 0xAB);
  
  //
  // Assertion Points 4.3.2.1
  // WriteBlocksEx should not succeed to write to device
  // When MedialId is not the id for the current media in the device
  //

  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    for (Index = 0; Index < 5; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
      case 0:
        NewMediaId = MediaId + 5;
        break;
      case 1:
        NewMediaId = MediaId + 1;
        break;
      case 2:
        NewMediaId = MediaId - 1;
        break;
      case 3:
        NewMediaId = MediaId - 5;
        break;
      case 4:
        NewMediaId = 0;
        break;
      default:
        NewMediaId = MediaId;
      }

      //
      // Verify test data
      //
      if (NewMediaId == MediaId) {
        continue;
      }

      //
      // Sync Call WriteBlocksEx with false MediaID
      //
      StatusSync = BlockIo2->WriteBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               0,
                               &BlkIo2TokenSync,
                               BufferSize,
                               (VOID*)Buffer
                               );
      //
      // Async Call WriteBlocksEx with false MediaID
      //
      StatusAsync = BlockIo2->WriteBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BufferSize,
                                (VOID*)Buffer
                                );

      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      if (StatusSync == EFI_MEDIA_CHANGED
       && StatusAsync == EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } 

      //
      // Sync Call WriteBlocksEx with false MediaID & invalid LBA
      //
      StatusSync = BlockIo2->WriteBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               LastBlock + 1,
                               &BlkIo2TokenSync,
                               BufferSize,
                               (VOID*)Buffer
                               );
      //
      // Async Call WriteBlocksEx with false MediaID & invalid LBA
      //
      StatusAsync = BlockIo2->WriteBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                LastBlock + 1,
                                &BlkIo2TokenAsync,
                                BufferSize,
                                (VOID*)Buffer
                                );
      if (StatusSync != EFI_MEDIA_CHANGED
       || StatusAsync != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"False MediaID & Invalid LBA";
      }

      //
      // Sync Call WriteBlocksEx with false MediaID & invalid BufferSize
      //
      StatusSync = BlockIo2->WriteBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               0,
                               &BlkIo2TokenSync,
                               BufferSize - 1,
                               (VOID*)Buffer
                               );
      //
      // Async Call WriteBlocksEx with false MediaID  & invalid BufferSize
      //
      StatusAsync = BlockIo2->WriteBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BufferSize - 1,
                                (VOID*)Buffer
                                );
      if (StatusSync != EFI_MEDIA_CHANGED
       || StatusAsync != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"False MediaID & Invalid BufferSize";
      }
      
      //
      // Sync Call WriteBlocksEx with false MediaID & invalid 0 BufferSize
      //  
      StatusSync = BlockIo2->WriteBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               0,
                               &BlkIo2TokenSync,
                               0,
                               (VOID*)Buffer
                               );
      //
      // Async Call WriteBlocksEx with false MediaID  & invalid 0 BufferSize
      //
      StatusAsync = BlockIo2->WriteBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                0,
                                &BlkIo2TokenAsync,
                                0,
                                (VOID*)Buffer
                                );

      if (StatusSync != EFI_MEDIA_CHANGED
       || StatusAsync != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED; 
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"False MediaID & Invalid 0 BufferSize";
      }
      
    
      if (IoAlign > 1) {
        //
        // Sync Call WriteBlocksEx with false MediaID & wrong aligned Buffer
        //
        StatusSync = BlockIo2->WriteBlocksEx (
                                 BlockIo2,
                                 NewMediaId,
                                 0,
                                 &BlkIo2TokenSync,
                                 BufferSize - BlockSize,
                                 (VOID*)(Buffer + 1)
                                 );
        //
        // Async Call WriteBlocksEx with false MediaID  & invalid 0 BufferSize
        //
        StatusAsync = BlockIo2->WriteBlocksEx (
                                  BlockIo2,
                                  NewMediaId,
                                  0,
                                  &BlkIo2TokenAsync,
                                  BufferSize - BlockSize,
                                  (VOID*)(Buffer + 1)
                                  );
        if (StatusSync != EFI_MEDIA_CHANGED
         || StatusAsync != EFI_MEDIA_CHANGED) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          FailedStatusSync = StatusSync;
          FailedStatusAsync = StatusAsync;
          ErrorOutput = L"False MediaID & Wrong aligned Buffer";
        }
      }

      //
      // Call WriteBlocks with false MediaID & invalid NULL Buffer
      //
      StatusSync = BlockIo2->WriteBlocksEx (
                               BlockIo2,
                               NewMediaId,
                               0,
                               &BlkIo2TokenSync,
                               BufferSize,
                               NULL
                               );
      //
      // Async Call WriteBlocksEx with false MediaID  & invalid NULL Buffer
      //
      StatusAsync = BlockIo2->WriteBlocksEx (
                                BlockIo2,
                                NewMediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BufferSize,
                                NULL
                                );
      if (StatusSync != EFI_MEDIA_CHANGED
       || StatusAsync != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"False MediaID & Invalid NULL Buffer";
      }
      

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIo2ConformanceTestAssertionGuid007,
                     L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Write block with MediaId not being the id for the current media in the device",
                     L"%a:%d: %s ActualMediaID=%d, MediaID=%d, StatusSync=%r, StatusAsync=%r, Expected=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     ErrorOutput,
                     MediaId,
                     NewMediaId,
                     FailedStatusSync,
                     FailedStatusAsync,
                     EFI_MEDIA_CHANGED
                     );
    }
  }

  //
  // Assertion point 4.3.2.2
  // WriteBlocksEx should not suceed to write to device when BufferSize is not
  // a multiple of the intrinsic block size of the device
  //
  if ((MediaPresent == TRUE) && (BlockSize != 1) && (ReadOnly == FALSE)) {
    for (Index = 0; Index < 4; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
      case 0:
        NewBufferSize = BlockSize + 1;
        break;
      case 1:
        NewBufferSize = 2 * BlockSize - 1;
        break;
      case 2:
        NewBufferSize = 2 * BlockSize + 1;
        break;
      case 3:
        NewBufferSize = 3 * BlockSize - 1;
        break;
      default:
        NewBufferSize = BufferSize;
        break;
      }
      //
      // Verify test data
      //
      if ((NewBufferSize % BlockSize == 0) || (NewBufferSize > BufferSize)) {
        continue;
      }

      //
      // Sync Call WriteBlocksEx with invalid BufferSize
      //
      StatusSync = BlockIo2->WriteBlocksEx (
                               BlockIo2,
                               MediaId,
                               0,
                               &BlkIo2TokenSync,
                               NewBufferSize,
                               (VOID*)Buffer
                               );
      //
      // Async Call WriteBlocksEx with invalid BufferSize
      //
      StatusAsync = BlockIo2->WriteBlocksEx (
                                BlockIo2,
                                MediaId,
                                0,
                                &BlkIo2TokenAsync,
                                NewBufferSize,
                                (VOID*)Buffer
                                );
     
      if (StatusSync == EFI_BAD_BUFFER_SIZE
       && StatusAsync == EFI_BAD_BUFFER_SIZE) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIo2ConformanceTestAssertionGuid008,
                     L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Write block with BufferSize not being a multiple of the intrinsic block size of the device",
                     L"%a:%d:BufferSize=%d, BlockSize=%d, StatusSync=%r, StatusAsync=%r, Expected=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewBufferSize,
                     BlockSize,
                     StatusSync,
                     StatusAsync,
                     EFI_BAD_BUFFER_SIZE
                     );
    }
  }

  //
  // Assertion Point 4.3.2.3
  // WriteBlocks should not succeed to write to device with invalid LBA parameter
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    for (Index = 0; Index < 6; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
      case 0:
        NewLba = LastBlock + 1;
        break;
      case 1:
        NewLba = LastBlock + 100;
        break;
      case 2:
        NewLba = LastBlock - BufferSize/BlockSize + 1;
        break;
      case 3:
        NewLba = LastBlock - BufferSize/BlockSize + 2;
        break;
      case 4:
        NewLba = LastBlock - BufferSize/BlockSize + 3;
        break;
      case 5:
        NewLba = LastBlock - BufferSize/BlockSize + 100;
        break;
      default:
        NewLba = 0;
        break;
      }

      //
      // Verify test data
      //
      if (NewLba + BufferSize/BlockSize <= LastBlock + 1) {
        continue;
      }

      //
      // Sync Call WriteBlocksEx with invalid BufferSize
      //
      StatusSync = BlockIo2->WriteBlocksEx (
                               BlockIo2,
                               MediaId,
                               NewLba,
                               &BlkIo2TokenSync,
                               BufferSize,
                               (VOID*)Buffer
                               );
      //
      // Async Call WriteBlocksEx with invalid BufferSize
      //
      StatusAsync = BlockIo2->WriteBlocksEx (
                                BlockIo2,
                                MediaId,
                                NewLba,
                                &BlkIo2TokenAsync,
                                BufferSize,
                                (VOID*)Buffer
                                );

      if (StatusSync == EFI_INVALID_PARAMETER
       && StatusAsync == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIo2ConformanceTestAssertionGuid009,
                     L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Write block with invalid LBA parameter",
                     L"%a:%d:BufferSize=%d, BlockSize=%d, LBA=0x%lx, LastBlock=0x%lx, StatusSync=%r, StatusAsync=%r, Expected=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     BlockSize,
                     NewLba,
                     LastBlock,
                     StatusSync,
                     StatusAsync,
                     EFI_INVALID_PARAMETER
                     );
    }
  }

  //
  //
  //
  //
  // Assertion Point 4.1.2.4
  // WriteBlocksEx should not succed to write to device with Buffer is not on proper alignment
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (IoAlign > 1)) {
    //
    // if IoAlign is large than 1, then it must be a power of 2
    //
    if ((IoAlign & (IoAlign - 1)) == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIo2ConformanceTestAssertionGuid010,
                   L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Sync & Async Write block aligment should be power of 2",
                   L"%a:%d:Aligment=0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   IoAlign
                   );

    for (NewIoAlign = (IoAlign >> 1); NewIoAlign > 0; NewIoAlign >>= 1) {
      //
      // Sync Call WriteBlocksEx with buffer of wrong aligment 
      //
      StatusSync = BlockIo2->WriteBlocksEx (
                               BlockIo2,
                               MediaId,
                               0,
                               &BlkIo2TokenSync,
                               BlockSize,
                               (VOID*)(Buffer + NewIoAlign)
                               );
      //
      // Async Call WriteBlocksEx with buffer of wrong aligment 
      //
      StatusAsync = BlockIo2->WriteBlocksEx (
                                BlockIo2,
                                MediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BlockSize,
                                (VOID*)(Buffer + NewIoAlign)
                                );
      if (StatusSync == EFI_INVALID_PARAMETER
       && StatusAsync == EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gBlockIo2ConformanceTestAssertionGuid011,
                     L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Sync & Async Write block with unaligned data buffer",
                     L"%a:%d:Aligment=%d, StatusSync=%r, StatusAsync=%r, Expected=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     NewIoAlign,
                     StatusSync,
                     StatusAsync,
                     EFI_INVALID_PARAMETER
                     );
    }
  }

  //
  // Assertion Point 4.3.2.7
  // WriteBlocksEx should not succeed to write to device that with no media present in the device
  //
  if (MediaPresent == FALSE) {
    ErrorOutput = L"";

    //
    // Sync Call WriteBlocksEx with proper parameter
    //
    StatusSync = BlockIo2->WriteBlocksEx (
                             BlockIo2,
                             MediaId,
                             0,
                             &BlkIo2TokenSync,
                             BufferSize,
                             (VOID*)Buffer
                             );
    //
    // Async Call WriteBlocksEx with proper parameter
    //
    StatusAsync = BlockIo2->WriteBlocksEx (
                              BlockIo2,
                              MediaId,
                              0,
                              &BlkIo2TokenAsync,
                              BufferSize,
                              (VOID*)Buffer
                              );

    FailedStatusSync = StatusSync;
    FailedStatusAsync = StatusAsync;
    if (StatusSync == EFI_NO_MEDIA 
     && StatusAsync == EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  
    //
    // Sync Call WriteBlocksEx with invalid LBA
    //
    StatusSync = BlockIo2->WriteBlocksEx (
                             BlockIo2,
                             MediaId,
                             LastBlock + 1,
                             &BlkIo2TokenSync,
                             BufferSize,
                             (VOID*)Buffer
                             );
    //
    // Async Call WriteBlocksEx with invalid LBA
    //
    StatusAsync = BlockIo2->WriteBlocksEx (
                              BlockIo2,
                              MediaId,
                              LastBlock + 1,
                              &BlkIo2TokenAsync,
                              BufferSize,
                              (VOID*)Buffer
                              );
   
    if (StatusSync != EFI_NO_MEDIA 
     || StatusAsync != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      ErrorOutput = L"Invalid LBA"; 
    }
    
    //
    // Sync Call ReadBlocksEx with invalid BufferSize
    //
    StatusSync = BlockIo2->WriteBlocksEx (
                             BlockIo2,
                             MediaId,
                             0,
                             &BlkIo2TokenSync,
                             BufferSize - 1,
                             (VOID*)Buffer
                             );
    //
    // Async Call WriteBlocksEx with invalid BufferSize
    //
    StatusAsync = BlockIo2->WriteBlocksEx (
                              BlockIo2,
                              MediaId,
                              0,
                              &BlkIo2TokenAsync,
                              BufferSize - 1,
                              (VOID*)Buffer
                              );
    
    if (StatusSync != EFI_NO_MEDIA 
     || StatusAsync != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;    
      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      ErrorOutput = L"Invalid BufferSize"; 
    }

    //
    // Sync Call WriteBlocksEx with invalid 0 BufferSize
    //
    StatusSync = BlockIo2->WriteBlocksEx (
                             BlockIo2,
                             MediaId,
                             0,
                             &BlkIo2TokenSync,
                             0,
                             (VOID*)Buffer
                             );
    //
    // Async Call WriteBlocksEx with invalid 0 BufferSize
    //
    StatusAsync = BlockIo2->WriteBlocksEx (
                              BlockIo2,
                              MediaId,
                              0,
                              &BlkIo2TokenAsync,
                              0,
                              (VOID*)Buffer
                              );
    
    if (StatusSync != EFI_NO_MEDIA 
     || StatusAsync != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED; 
      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      ErrorOutput = L"Zero BufferSize";
    }

    
    if (IoAlign > 1) {
      //
      // Sync Call WriteBlocksEx with Unaligned Buffer
      //
      StatusSync = BlockIo2->WriteBlocksEx (
                               BlockIo2,
                               MediaId,
                               0,
                               &BlkIo2TokenSync,
                               BufferSize - BlockSize,
                               (VOID*)(Buffer + 1)
                               );
      //
      // Async Call WriteBlocksEx with Unaligned Buffer
      //
      StatusAsync = BlockIo2->WriteBlocksEx (
                                BlockIo2,
                                MediaId,
                                0,
                                &BlkIo2TokenAsync,
                                BufferSize - BlockSize,
                                (VOID*)(Buffer + 1)
                                );

      if (StatusSync != EFI_NO_MEDIA 
       || StatusAsync != EFI_NO_MEDIA) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        FailedStatusSync = StatusSync;
        FailedStatusAsync = StatusAsync;
        ErrorOutput = L"Unaligned Buffer";
      }
    }

    //
    // Sync Call WriteBlocksEx with invalid NULL Buffer
    //
    StatusSync = BlockIo2->WriteBlocksEx (
                             BlockIo2,
                             MediaId,
                             0,
                             &BlkIo2TokenSync,
                             BufferSize,
                             NULL
                             );
    //
    // Async Call WriteBlocksEx with invalid NULL Buffer
    //
    StatusAsync = BlockIo2->WriteBlocksEx (
                              BlockIo2,
                              MediaId,
                              0,
                              &BlkIo2TokenAsync,
                              BufferSize,
                              NULL
                                );

    if (StatusSync != EFI_NO_MEDIA 
     || StatusAsync != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      FailedStatusSync = StatusSync;
      FailedStatusAsync = StatusAsync;
      ErrorOutput = L"Null Buffer";
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIo2ConformanceTestAssertionGuid012,
                   L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Write block from device with no media present in the device",
                   L"%a:%d: %s MediaID=%d, StatusSync=%r, StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ErrorOutput,
                   MediaId,
                   FailedStatusSync,
                   FailedStatusAsync
                   );
  }
   

  //
  // Assertion Point 4.3.2.6
  // WriteBlocksEx should not succeed to write to a write-protected device
  //
  if ((MediaPresent == TRUE) && (ReadOnly == TRUE)) {
    //
    // Sync Call WriteBlocksEx with proper parameter
    //
    StatusSync = BlockIo2->WriteBlocksEx (
                             BlockIo2,
                             MediaId,
                             0,
                             &BlkIo2TokenSync,
                             BufferSize,
                             (VOID*)Buffer
                             );
    //
    // Async Call WriteBlocksEx with proper parameter
    //
    StatusAsync = BlockIo2->WriteBlocksEx (
                              BlockIo2,
                              MediaId,
                              0,
                              &BlkIo2TokenAsync,
                              BufferSize,
                              (VOID*)Buffer
                              );
    if (StatusSync == EFI_WRITE_PROTECTED
     && StatusAsync == EFI_WRITE_PROTECTED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIo2ConformanceTestAssertionGuid013,
                   L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Write block to readonly device",
                   L"%a:%d:StatusSync=%r, StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   StatusSync,
                   StatusAsync
                   );
  }

  //
  // Close Block IO2 WriteEx block Event
  //
  gtBS->CloseEvent (BlkIo2TokenAsync.Event);

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
 *  Entrypoint for EFI_BLOCK_IO2_PROTOCOL.FlushBlocksEx() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.5
//
EFI_STATUS
EFIAPI
BBTestFlushBlocksExConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status, StatusSync, StatusAsync;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2;
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
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenSync;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenAsync;


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
  
  //
  // Initialize Blk IO2 FlushEx token  event
  //
  //
  // Sync Token Init
  //
  BlkIo2TokenSync.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  //
  // Async Token Init
  //
  BlkIO2Finished = FALSE;
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) NotifyFunc,
                   &BlkIO2Finished,
                   &BlkIo2TokenAsync.Event
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat Read BlockEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->CloseEvent (BlkIo2TokenAsync.Event);
    return Status;
  }
  BlkIo2TokenAsync.TransactionStatus = EFI_NOT_READY;


  BlockIo2 = (EFI_BLOCK_IO2_PROTOCOL *)ClientInterface;

  //
  // Initialize variable
  //
  MediaId           = BlockIo2->Media->MediaId;
  RemovableMedia    = BlockIo2->Media->RemovableMedia;
  MediaPresent      = BlockIo2->Media->MediaPresent;
  LogicalPartition  = BlockIo2->Media->LogicalPartition;
  ReadOnly          = BlockIo2->Media->ReadOnly;
  WriteCaching      = BlockIo2->Media->WriteCaching;
  BlockSize         = BlockIo2->Media->BlockSize;
  IoAlign           = BlockIo2->Media->IoAlign;
  LastBlock         = BlockIo2->Media->LastBlock;


  //
  // Assertion Point 4.5.2.1
  // FlushBlocksEx should not succeed to flush data to device that with no media present in the device
  //
  if ((MediaPresent == FALSE) && (WriteCaching == TRUE)) {
    //
    // Sync Call FlushBlocksEx for testing
    //
    StatusSync = BlockIo2->FlushBlocksEx (
                             BlockIo2,
                             &BlkIo2TokenSync
                             );
    //
    // Async Call FlushBlocksEx for testing
    //
    StatusAsync = BlockIo2->FlushBlocksEx (
                              BlockIo2,
                              &BlkIo2TokenAsync
                              );
    if (StatusSync == EFI_NO_MEDIA
     && StatusAsync == EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIo2ConformanceTestAssertionGuid014,
                   L"EFI_BLOCK_IO2_PROTOCOL.FlushBlocksEx - Sync & Async Flush blocks to device with no media present in the device",
                   L"%a:%d:StatusSync=%r, StatusAsync=%r, Expected=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   StatusSync,
                   StatusAsync,
                   EFI_NO_MEDIA
                   );
  }

  //
  // Assertion Point 4.5.2.1
  // FlushBlocksEx should not succeed to flush data to device that with read-only media
  //
  if ((MediaPresent == TRUE) && (ReadOnly == TRUE) && (WriteCaching == TRUE)) {
    //
    // Sync Call FlushBlocksEx to read-only media
    //
    StatusSync = BlockIo2->FlushBlocksEx (
                             BlockIo2,
                             &BlkIo2TokenSync
                             );
    //
    // Async Call FlushBlocksEx to read-only media
    //
    StatusAsync = BlockIo2->FlushBlocksEx (
                              BlockIo2,
                              &BlkIo2TokenAsync
                              );
    if (StatusSync == EFI_WRITE_PROTECTED
     && StatusAsync == EFI_WRITE_PROTECTED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIo2ConformanceTestAssertionGuid015,
                   L"EFI_BLOCK_IO2_PROTOCOL.FlushBlocksEx - Sync & Async Flush blocks to read-only device",
                   L"%a:%d:StatusSync=%r, StatusAsync=%r, Expected=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   StatusSync,
                   StatusAsync,
                   EFI_WRITE_PROTECTED
                   );
  }
  
  //
  // Close Block IO2 FlushEx block Event
  //
  if (BlkIo2TokenAsync.Event != NULL) {
    gtBS->CloseEvent (BlkIo2TokenAsync.Event);
  }
  
  return EFI_SUCCESS;
}

