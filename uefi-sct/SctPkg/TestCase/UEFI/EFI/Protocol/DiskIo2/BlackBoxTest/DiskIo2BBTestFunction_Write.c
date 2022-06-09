/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DiskIo2BBFunctionTest.c

Abstract:

  Interface Function Test Cases of Disk I/O2 Protocol

--*/


#include "DiskIo2BBTestMain.h"



EFI_STATUS
EFIAPI
BBTestWriteDiskExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );


EFI_STATUS
EFIAPI
BBTestWriteDiskExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );


EFI_STATUS
EFIAPI
BBTestWriteDiskExFunctionAutoTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );


#define EFI_INITIALIZE_LOCK_VARIABLE(Tpl) {Tpl,0,0}


#define ASYNC_WRITE_TEST_PATTERN            0x1C
#define SYNC_WRITE_TEST_PATTERN             0xAB

//
// Async Write Queue
//
SCT_LIST_ENTRY  AsyncWriteFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncWriteFinishListHead);
SCT_LIST_ENTRY  AsyncWriteExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncWriteExecuteListHead);
SCT_LIST_ENTRY  AsyncWriteFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncWriteFailListHead);


//
// Sync Read Data Queue for Async Write
//
SCT_LIST_ENTRY  SyncReadDataListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(SyncReadDataListHead);

//
// Async Write lock
//
SCT_LOCK gAsyncWriteQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);

//
//  Sync Write Queue
//
SCT_LIST_ENTRY  SyncWriteListHead     = INITIALIZE_SCT_LIST_HEAD_VARIABLE(SyncWriteListHead);
SCT_LIST_ENTRY  SyncWriteFailListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(SyncWriteFailListHead);



//
// Async signal
//
UINTN       AsyncBatchWriteFinished = 0;





VOID
EFIAPI DiskIo2WriteNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  DiskIO2_Task *DiskIo2Entity;
  
  DiskIo2Entity = (DiskIO2_Task *)Context;

  //
  // Remove entity from WriteExecuteListHead &  add entity to WriteFinishListHead
  // All DiskIo2 Notify function run at Call Back level only once, So no locks required
  //
  SctAcquireLock (&gAsyncWriteQueueLock);
  SctRemoveEntryList(&DiskIo2Entity->ListEntry);
  SctInsertTailList(&AsyncWriteFinishListHead, &DiskIo2Entity->ListEntry);
  SctReleaseLock (&gAsyncWriteQueueLock);
}






/**
 *   Provide EFI_DISK_IO2_PROTOCOL.WriteDiskEx() function abstraction interface
 *  @param DiskIo 2 a pointer to Disk IO2 to be tested.
 *  @param MediaId Write media ID.
 *  @param Offset the starting byte offset to read from.
 *  @param BufferSize write databuffer size.
 *  @param Buffer a pointer to write data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

STATIC
EFI_STATUS
DiskIo2AsyncWriteData (
  IN EFI_DISK_IO2_PROTOCOL    *DiskIo2,
  IN UINT32                   MediaId,
  IN UINT64                   Offset,
  IN UINTN                    BufferSize,
  OUT VOID                    *Buffer
  )
{
  EFI_STATUS      Status;
  DiskIO2_Task    *DiskIo2Entity = NULL;

  ASSERT(DiskIo2 != NULL);
 
  //
  // Allocate memory for one DiskIo2Entity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(DiskIO2_Task), 
                   (VOID **) &DiskIo2Entity
                   );
  
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  // DiskIo2Token initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) DiskIo2WriteNotifyFunc,
                   DiskIo2Entity,
                   &DiskIo2Entity->DiskIo2Token.Event
                   );
  
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(DiskIo2Entity);
    return Status;
  }

  DiskIo2Entity->DiskIo2Token.TransactionStatus = EFI_NOT_READY;

  //
  // Acquire lock to add entity to Write Execution ListHead
  //
  SctAcquireLock (&gAsyncWriteQueueLock);
  SctInsertTailList(&AsyncWriteExecuteListHead, &DiskIo2Entity->ListEntry);
  SctReleaseLock (&gAsyncWriteQueueLock);
  
  DiskIo2Entity->Buffer      = Buffer;
  DiskIo2Entity->Signature   = DISKIO2ENTITY_SIGNATURE;
  DiskIo2Entity->MediaId     = MediaId;
  DiskIo2Entity->Offset      = Offset;
  DiskIo2Entity->BufferSize  = BufferSize;
  DiskIo2Entity->MemCompared = FALSE;     

  //
  // Async WriteDiskEx Call
  //
  Status = DiskIo2->WriteDiskEx (
                      DiskIo2,
                      MediaId,
                      Offset,
                      &DiskIo2Entity->DiskIo2Token,
                      BufferSize,
                      Buffer
                      );

  DiskIo2Entity->StatusAsync = Status;

  if (EFI_ERROR (Status)) {
    gtBS->CloseEvent(DiskIo2Entity->DiskIo2Token.Event);
    //
    // Failed Status Event should never be signaled, so remove this entity from the list
    //
    SctAcquireLock (&gAsyncWriteQueueLock);
    SctRemoveEntryList(&DiskIo2Entity->ListEntry);
    
    // 
    // Put failure execution into fail List
    //
    SctInsertTailList(&AsyncWriteFailListHead, &DiskIo2Entity->ListEntry);
    SctReleaseLock (&gAsyncWriteQueueLock);

    DiskIo2Entity->Buffer = NULL;

    return Status;
  }

  return Status;
}



VOID
EFIAPI DiskIo2WriteBatchNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  
  DiskIO2_Batch_Task_Context    *TaskContext;
  DiskIO2_Task                  *DiskIo2Entity    = NULL;
  SCT_LIST_ENTRY                *CurrentTaskEntry = NULL;
  EFI_DISK_IO2_PROTOCOL         *DiskIo2          = NULL;
  EFI_STATUS                    Status;

  TaskContext      = (DiskIO2_Batch_Task_Context *) Context;
  CurrentTaskEntry = TaskContext->CurrentTaskEntry;
  DiskIo2          = TaskContext->DiskIo2;

  if (!SctIsNodeAtEnd(TaskContext->TaskHeader, CurrentTaskEntry) ){
    DiskIo2Entity = CR(CurrentTaskEntry->ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);

    DiskIo2Entity->DiskIo2Token.Event = NULL;
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) DiskIo2WriteBatchNotifyFunc,
                     TaskContext,
                     &DiskIo2Entity->DiskIo2Token.Event
                     );
    if (EFI_ERROR(Status) ) {
      goto END;
    }

    //
    // Current Task Entry move forward
    //
    TaskContext->CurrentTaskEntry = CurrentTaskEntry->ForwardLink;

    Status = DiskIo2->WriteDiskEx (
                        DiskIo2,
                        DiskIo2Entity->MediaId,
                        DiskIo2Entity->Offset,
                        &DiskIo2Entity->DiskIo2Token,
                        DiskIo2Entity->BufferSize,
                        DiskIo2Entity->Buffer
                        );
    if (Status != EFI_SUCCESS) {
      goto END;
    }
  } else {
      //
      // All Task has been handled, kick off notify event & clean Task context
      //
      gtBS->SignalEvent (TaskContext->Token->Event);
      //
      // Close current Event
      //
      DiskIo2Entity = CR(CurrentTaskEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);

      gtBS->FreePool (TaskContext);
    
      return;
  }

END:
  //
  // Close current Event
  //
  DiskIo2Entity = CR(CurrentTaskEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
  
  return;
}




/**
 *   Provide Batch task for EFI_DISK_IO2_PROTOCOL.WriteDiskEx() function 
 *  @param DiskIo 2 a pointer to Disk IO2 to be tested.
 *  @param TaskList point to batch task list.
 *  @param Token task list token.
 *  @return EFI_SUCCESS Finish the test successfully.
 */


STATIC
EFI_STATUS
DiskIo2AsyncBatchWrite (
  IN EFI_DISK_IO2_PROTOCOL           *DiskIo2,
  IN SCT_LIST_ENTRY                  *ListHeader,
  IN OUT EFI_DISK_IO2_TOKEN	         *Token
)
{
  DiskIO2_Batch_Task_Context    *TaskContext   = NULL; 
  DiskIO2_Task                  *DiskIo2Entity = NULL;
  EFI_STATUS                    Status         = EFI_SUCCESS;
  
  ASSERT(Token != NULL && Token->Event != NULL);

  if (!SctIsListEmpty(ListHeader)) {
    //
    // Task Context will be freed in DiskIo2WriteBatchNotifyFunc when all task finished
    //
    Status = gtBS->AllocatePool (
                     EfiBootServicesData, 
                     sizeof(DiskIO2_Batch_Task_Context), 
                     (VOID **) &TaskContext
                     );
    if (TaskContext == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Init BatchTask structure
    // 
    TaskContext->TaskHeader       = ListHeader;
    TaskContext->CurrentTaskEntry = ListHeader->ForwardLink;
    TaskContext->Token            = Token;
    TaskContext->DiskIo2          = DiskIo2;

    DiskIo2Entity = CR(ListHeader->ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);

    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) DiskIo2WriteBatchNotifyFunc,
                     TaskContext,
                     &DiskIo2Entity->DiskIo2Token.Event
                     );
    if (EFI_ERROR(Status) ) {
      return Status;
    }
    
    Status = DiskIo2->WriteDiskEx (
                        DiskIo2,
                        DiskIo2Entity->MediaId,
                        DiskIo2Entity->Offset,
                        &DiskIo2Entity->DiskIo2Token,
                        DiskIo2Entity->BufferSize,
                        DiskIo2Entity->Buffer
                        );
    }

    return Status;
}



 
/**
*  Entrypoint for EFI_DISK_IO2_PROTOCOL.WriteDiskEx() Function Test.
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
BBTestWriteDiskExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL      *This,
  IN VOID                      *ClientInterface,
  IN EFI_TEST_LEVEL            TestLevel,
  IN EFI_HANDLE                SupportHandle
  )
{
  EFI_STATUS                               Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL       *StandardLib    = NULL;
  EFI_DISK_IO_PROTOCOL                     *DiskIo         = NULL;
  EFI_BLOCK_IO2_PROTOCOL                   *BlockIo2       = NULL;
  EFI_DISK_IO2_PROTOCOL                    *DiskIo2        = NULL;
  EFI_DISK_IO2_PROTOCOL                    *DiskIo2Temp    = NULL;
  EFI_DEVICE_PATH_PROTOCOL                 *DevicePath     = NULL;
  CHAR16                                   *DevicePathStr  = NULL;
  UINTN                                    Index;
  UINTN                                    NoHandles;
  EFI_HANDLE                               *HandleBuffer    = NULL;
 
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

  DiskIo2 = (EFI_DISK_IO2_PROTOCOL *)ClientInterface;

  Status = LocateBlockIo2FromDiskIo2 (DiskIo2, &BlockIo2, StandardLib);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }


  //
  // Locate Device path of the current DiskIo2 device
  // and save it into log for investigating
  //
  LocateDevicePathFromDiskIo2 (DiskIo2, &DevicePath, StandardLib);
  
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
  // Locate Disk IO protocol on same handler for test
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiDiskIo2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiDiskIo2ProtocolGuid,
                     (VOID **) &DiskIo2Temp
                     );

    if (Status == EFI_SUCCESS && DiskIo2Temp == DiskIo2) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gBlackBoxEfiDiskIoProtocolGuid,
                       (VOID **) &DiskIo
                       );
      if (Status != EFI_SUCCESS) {
        DiskIo = NULL;
      }
      break;
    }
  }
   
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }
  //
  // Async call to test Disk IO 2 WriteDiskEx
  // Using link list  to manage token pool
  //
  BBTestWriteDiskExFunctionAutoTestCheckpoint1 (StandardLib, DiskIo, DiskIo2,BlockIo2);
  
  //
  // Sync call to test Disk IO 2 WriteDiskEx
  //
  BBTestWriteDiskExFunctionAutoTestCheckpoint2 (StandardLib, DiskIo, DiskIo2,BlockIo2);	 
  //
  // Async call to test Disk IO 2 WriteDiskEx
  // Using Cascade Event Chain to manage token pool
  //
  BBTestWriteDiskExFunctionAutoTestCheckpoint3 (StandardLib, DiskIo, DiskIo2,BlockIo2);

  return Status;
  }
  
/**
*   EFI_DISK_IO2_PROTOCOL.WriteDiskEx() Function Test 1. Async mode test
*  @param StandardLib a point to standard test lib
*  @param DiskIo a pointer to Disk IO the interface.
*  @param DiskIo 2 a pointer to Disk IO2 to be tested.
*  @return EFI_SUCCESS Finish the test successfully.
*/
 
EFI_STATUS
EFIAPI
BBTestWriteDiskExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS            Status;
  UINT32                MediaId;
  BOOLEAN               RemovableMedia;
  BOOLEAN               MediaPresent;
  BOOLEAN               LogicalPartition;
  BOOLEAN               ReadOnly;
  BOOLEAN               WriteCaching;
  BOOLEAN               ReadCompleted;
  UINT32                BlockSize;
  UINT32                IoAlign;
  EFI_LBA               LastBlock;
  UINTN                 BufferSize;
  UINT64                Offset;
  UINT64                LastOffset;   
  UINT8                 *ReadBuffer  = NULL;
  VOID                  *WriteBuffer = NULL;
  
  UINTN                 IndexI,IndexJ;
  UINTN                 NewBufferSize;
  UINTN                 Remainder;
  EFI_STATUS            StatusWrite;
  DiskIO2_Task          *DiskIo2EntityWrite = NULL;
  DiskIO2_Task          *DiskIo2EntityRead  = NULL;
  SCT_LIST_ENTRY        *ListEntry          = NULL;
  
  UINTN                 WaitIndex;
  EFI_DISK_IO2_TOKEN    DiskIo2TokenSync;
   
  //
  // Initialize variable
  //
  MediaId          = BlockIo2->Media->MediaId;
  RemovableMedia   = BlockIo2->Media->RemovableMedia;
  MediaPresent     = BlockIo2->Media->MediaPresent;
  LogicalPartition = BlockIo2->Media->LogicalPartition;
  ReadOnly         = BlockIo2->Media->ReadOnly;
  WriteCaching     = BlockIo2->Media->WriteCaching;
  BlockSize        = BlockIo2->Media->BlockSize;
  IoAlign          = BlockIo2->Media->IoAlign;
  LastBlock        = BlockIo2->Media->LastBlock;
  
  ReadCompleted    = FALSE;
  
  BufferSize = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset = SctMultU64x32 (LastBlock + 1, BlockSize);
  
  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }   
  //
  // Sync Token Init
  //
  DiskIo2TokenSync.Event             = NULL;
  DiskIo2TokenSync.TransactionStatus = EFI_NOT_READY;

  SctPrint (L"Read Record Data.\n");
  //
  // Record all write disk data for recovery first
  //
  
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    SctPrint (L" =================== Record Disk Info =================== \n\n");
    for (IndexI = 0; IndexI < 8; IndexI++) {
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
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize);
            break;
          case 7:
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize);
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
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) + 1;
            break;
          case 16:
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) + 1;
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
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) - 1;
            break;
          case 26:
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) - 1;
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
        // Allocate memory for one DiskIo2Entity
        //
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         sizeof(DiskIO2_Task), 
                         (VOID **) &DiskIo2EntityRead
                         );
        if (EFI_ERROR(Status)) {
          goto END;
        } 
  
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList(&SyncReadDataListHead, &DiskIo2EntityRead->ListEntry);
  
        DiskIo2EntityRead->Buffer = NULL;
        DiskIo2EntityRead->DiskIo2Token.Event = NULL;
        DiskIo2EntityRead->DiskIo2Token.TransactionStatus = EFI_NOT_READY;
        DiskIo2EntityRead->Signature = DISKIO2ENTITY_SIGNATURE;
        DiskIo2EntityRead->BufferSize = NewBufferSize;
        DiskIo2EntityRead->Offset = Offset;
        DiskIo2EntityRead->MediaId = MediaId;
     
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         NewBufferSize, 
                         (VOID **) &DiskIo2EntityRead->Buffer
                         );
        if (EFI_ERROR(Status)){
          goto END;
        }

        //
        // Sync Call ReadDiskEx with the specified Offset and BufferSize
        //
        Status = DiskIo2->ReadDiskEx (
                            DiskIo2,
                            DiskIo2EntityRead->MediaId,
                            DiskIo2EntityRead->Offset,
                            &DiskIo2EntityRead->DiskIo2Token,
                            DiskIo2EntityRead->BufferSize,
                            DiskIo2EntityRead->Buffer
                            );
        if (EFI_ERROR(Status)) {
          goto END;
        }
      }
    }
  
    ReadCompleted = TRUE;
  
  
    SctPrint (L" ================ Start to do Async WriteDiskEx call ================ \n\n");
    // 
    // do Asyn write call basing on read data result 
    //
    if (!SctIsListEmpty(&SyncReadDataListHead)) {
      for(ListEntry = SctGetFirstNode(&SyncReadDataListHead); ; ListEntry = SctGetNextNode(&SyncReadDataListHead, ListEntry)) {
  
        DiskIo2EntityRead = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
   
        WriteBuffer = NULL;

        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         DiskIo2EntityRead->BufferSize, 
                         (VOID **) &WriteBuffer
                         );
    
        if ( EFI_ERROR(Status)) {
          goto END_WAIT;
        }

        //
        // Set test data pattern into Write Buffer  
        //
        SctSetMem (WriteBuffer, DiskIo2EntityRead->BufferSize, ASYNC_WRITE_TEST_PATTERN);
        //
        // Write specified buffer2 differ from buffer to the device
        // write info comes from previous read info list
        //
        StatusWrite = DiskIo2AsyncWriteData(
                        DiskIo2,
                        DiskIo2EntityRead->MediaId,
                        DiskIo2EntityRead->Offset,
                        DiskIo2EntityRead->BufferSize,
                        WriteBuffer
                        );
  
        if (EFI_ERROR(StatusWrite)) {
          gtBS->FreePool(WriteBuffer);
        }
  
        //
        // Last list node handled
        //
        if (SctIsNodeAtEnd(&SyncReadDataListHead,ListEntry)) {
          break;
        }
      }
  
      SctPrint (L" ================== Async WriteDiskEx call finshed ================== \n\n"); 

END_WAIT:   
     
      //
      // Busy waiting 120s on all the execute entity being moved to finished queue
      //  
      SctPrint (L"Wait maximumly 120s for all Async Write events signaled\n\n");
      Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
      IndexI = 0;
      IndexI = 0;
    
      SctAcquireLock (&gAsyncWriteQueueLock);
      while (!SctIsListEmpty(&AsyncWriteExecuteListHead) && IndexI < 120) {
        SctReleaseLock (&gAsyncWriteQueueLock);
 
        gtBS->WaitForEvent (
                1,
                &TimerEvent,
                &WaitIndex
                );
        IndexI++;
        SctPrint (L".");
        SctAcquireLock (&gAsyncWriteQueueLock);
      }
      SctReleaseLock (&gAsyncWriteQueueLock);
   
      Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
      SctPrint (L"\n");
    }
  }
  
  //
  // clear all Disk IO2 events from gWriteFinishQueue 
  // gWriteFinishQueue is handled first since we use Disk IO write to do write buffer validation 
  // Here no logs should be wrote to this disk device to keep data intact
  //
  SctAcquireLock (&gAsyncWriteQueueLock);
  if (!SctIsListEmpty(&AsyncWriteFinishListHead)) {
    for(ListEntry = SctGetFirstNode(&AsyncWriteFinishListHead); ; ListEntry = SctGetNextNode(&AsyncWriteFinishListHead, ListEntry)) {
      DiskIo2EntityWrite = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncWriteQueueLock);
     
      //
      // Check written data of each successful Disk IO2 execution 
      //
      if (DiskIo2EntityWrite->DiskIo2Token.TransactionStatus == EFI_SUCCESS) {
  
        DiskIo2EntityWrite->AssertionType = EFI_TEST_ASSERTION_PASSED;
  
        Status= gtBS->AllocatePool(
                        EfiBootServicesData, 
                        DiskIo2EntityWrite->BufferSize, 
                        (VOID **) &ReadBuffer
                        );

        if (!EFI_ERROR(Status)) {
          Status = DiskIo2->ReadDiskEx(
                              DiskIo2,
                              DiskIo2EntityWrite->MediaId,
                              DiskIo2EntityWrite->Offset,
                              &DiskIo2TokenSync,
                              DiskIo2EntityWrite->BufferSize,
                              (VOID *)ReadBuffer
                              );
          //
          // Compare with write test pattern
          //
          if (Status == EFI_SUCCESS) {
            DiskIo2EntityWrite->ComparedVal = 0;
            DiskIo2EntityWrite->MemCompared = TRUE;
            for (IndexI = 0; IndexI < DiskIo2EntityWrite->BufferSize; IndexI++) {
              if (ReadBuffer[IndexI] != ASYNC_WRITE_TEST_PATTERN) {
                DiskIo2EntityWrite->AssertionType = EFI_TEST_ASSERTION_FAILED;
                DiskIo2EntityWrite->ComparedVal = 1;
                break;
              }
            }
          }

          gtBS->FreePool(ReadBuffer);
          ReadBuffer = NULL;
        }
      } else {
        DiskIo2EntityWrite->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      SctAcquireLock (&gAsyncWriteQueueLock);
      if (SctIsNodeAtEnd(&AsyncWriteFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  SctReleaseLock (&gAsyncWriteQueueLock);
  
END:
  //
  // Clean up & free all record resources
  //
  SctPrint (L"============ Restore All written disk ============= \n");
  while (!SctIsListEmpty(&SyncReadDataListHead)) {
    DiskIo2EntityRead = CR(SyncReadDataListHead.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2EntityRead->ListEntry);
  
    if (DiskIo2EntityRead->Buffer != NULL && ReadCompleted == TRUE) {
      //
      // restore all read informations
      //
      Status = DiskIo2->WriteDiskEx (
                          DiskIo2,
                          DiskIo2EntityRead->MediaId,
                          DiskIo2EntityRead->Offset,
                          &DiskIo2EntityRead->DiskIo2Token,
                          DiskIo2EntityRead->BufferSize,
                          DiskIo2EntityRead->Buffer
                          );
  
      if (EFI_ERROR(Status) ) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Restore blocks fail",
                       L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx",
                       __FILE__,
                       (UINTN)__LINE__,
                       DiskIo2EntityRead->MediaId,
                       DiskIo2EntityRead->Offset,
                       DiskIo2EntityRead->BufferSize
                       );
      }
  
    }
  
    if (DiskIo2EntityRead->Buffer != NULL) {
      Status = gtBS->FreePool (DiskIo2EntityRead->Buffer);
    }
  
    gtBS->FreePool(DiskIo2EntityRead);
  }
     
  SctPrint (L"============ Record All written disk finshed ============ \n");

  //
  // Record All write finshed test logs
  //  
  SctAcquireLock (&gAsyncWriteQueueLock);
  while (!SctIsListEmpty(&AsyncWriteFinishListHead)) {
    DiskIo2EntityWrite = CR(AsyncWriteFinishListHead.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    
    SctRemoveEntryList(&DiskIo2EntityWrite->ListEntry);
    SctReleaseLock (&gAsyncWriteQueueLock);
    
     
    if (DiskIo2EntityWrite->MemCompared == TRUE) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     DiskIo2EntityWrite->AssertionType,
                     gDiskIo2FunctionTestAssertionGuid012,
                     L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Async Write Disk with proper parameter to valid media "    \
                     L"ASYNC_WRITE_TEST_PATTERN 0x1C",
                     L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx ReadDiskEx Buffer CompareStatus=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     DiskIo2EntityWrite->MediaId,
                     DiskIo2EntityWrite->Offset,
                     DiskIo2EntityWrite->BufferSize,
                     DiskIo2EntityWrite->Buffer,
                     DiskIo2EntityWrite->ComparedVal
                     );
    } else {
      StandardLib->RecordAssertion (
                     StandardLib,
                     DiskIo2EntityWrite->AssertionType,
                     gDiskIo2FunctionTestAssertionGuid012,
                     L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Async Write Disk with proper parameter to valid media "    \
                     L"ASYNC_WRITE_TEST_PATTERN 0x1C",
                     L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                     __FILE__,
                     (UINTN)__LINE__,
                     DiskIo2EntityWrite->MediaId,
                     DiskIo2EntityWrite->Offset,
                     DiskIo2EntityWrite->BufferSize,
                     DiskIo2EntityWrite->Buffer
                     );
    }
    
    gtBS->CloseEvent(DiskIo2EntityWrite->DiskIo2Token.Event);
    
    //
    // Free  Buffer
    //
    if (DiskIo2EntityWrite->Buffer != NULL) {
      gtBS->FreePool (DiskIo2EntityWrite->Buffer);
    }
    gtBS->FreePool(DiskIo2EntityWrite);
    
    SctAcquireLock (&gAsyncWriteQueueLock);
  }  
  SctReleaseLock (&gAsyncWriteQueueLock);
   
  //
  // If WriteFailListHead is not empty, which means some Async Calls are wrong 
  // 
  while(!SctIsListEmpty(&AsyncWriteFailListHead)) {
    DiskIo2EntityWrite = CR(AsyncWriteFailListHead.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2EntityWrite->ListEntry);
  
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gDiskIo2FunctionTestAssertionGuid013,
                   L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Async Write Disk with proper parameter to valid media "	 \
                   L"Write Failed ",
                   L"%a:%d:BufferSize=%d, Offset=0x%lx, StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   DiskIo2EntityWrite->BufferSize,
                   DiskIo2EntityWrite->Offset,
                   DiskIo2EntityWrite->StatusAsync
                   );
  
    gtBS->FreePool(DiskIo2EntityWrite);
  }
  
  //
  // If WriteExecuteList is not empty, which means some token events havn't been signaled yet
  //
  //
  // Be careful, All the entities in Execution list should NOT be freed here! 
  //
  SctAcquireLock (&gAsyncWriteQueueLock);
  if (!SctIsListEmpty(&AsyncWriteExecuteListHead)) {
    for(ListEntry = SctGetFirstNode(&AsyncWriteExecuteListHead); ; ListEntry = SctGetNextNode(&AsyncWriteExecuteListHead, ListEntry)) {
      DiskIo2EntityWrite = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncWriteQueueLock);
  
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gDiskIo2FunctionTestAssertionGuid014,
                     L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Async Write Disk with proper parameter to valid media "    \
                     L"Async write event has not been signaled",
                     L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx Buffer=0x%lx ",
                     __FILE__,
                     (UINTN)__LINE__,
                     DiskIo2EntityWrite->MediaId,
                     DiskIo2EntityWrite->Offset,
                     DiskIo2EntityWrite->BufferSize,
                     DiskIo2EntityWrite->Buffer
                     );
  
      SctAcquireLock (&gAsyncWriteQueueLock);
      if (SctIsNodeAtEnd(&AsyncWriteExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  
  SctReleaseLock (&gAsyncWriteQueueLock);
  
  return EFI_SUCCESS;
}
 

/**
*   EFI_DISK_IO2_PROTOCOL.WriteDiskEx() Function Test 2. Sync mode test
*  @param StandardLib a point to standard test lib
*  @param DiskIo a pointer to Disk IO the interface.
*  @param DiskIo 2 a pointer to Disk IO2 to be tested.
*  @return EFI_SUCCESS Finish the test successfully.
*/
 
EFI_STATUS
EFIAPI
BBTestWriteDiskExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS            Status;
  UINT32                MediaId;
  BOOLEAN               RemovableMedia;
  BOOLEAN               MediaPresent;
  BOOLEAN               LogicalPartition;
  BOOLEAN               ReadOnly;
  BOOLEAN               WriteCaching;
  UINT32                BlockSize;
  UINT32                IoAlign;
  EFI_LBA               LastBlock;
  UINTN                 BufferSize;
  UINT64                Offset;
  UINT64                LastOffset;
  UINTN                 Remainder;
  UINT8                 *ReadBuffer  = NULL;
  UINT8                 *WriteBuffer = NULL;
  UINTN                 IndexI,IndexJ;
  UINTN                 NewBufferSize;
  EFI_STATUS            StatusWrite;
  DiskIO2_Task          *DiskIo2EntityRead = NULL;
  SCT_LIST_ENTRY        *ListEntry         = NULL;
  EFI_DISK_IO2_TOKEN    DiskIo2TokenSync;

  //
  // Initialize variable
  //
  MediaId          = BlockIo2->Media->MediaId;
  RemovableMedia   = BlockIo2->Media->RemovableMedia;
  MediaPresent     = BlockIo2->Media->MediaPresent;
  LogicalPartition = BlockIo2->Media->LogicalPartition;
  ReadOnly         = BlockIo2->Media->ReadOnly;
  WriteCaching     = BlockIo2->Media->WriteCaching;
  BlockSize        = BlockIo2->Media->BlockSize;
  IoAlign          = BlockIo2->Media->IoAlign;
  LastBlock        = BlockIo2->Media->LastBlock;
   
  BufferSize = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? \
                 MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset = SctMultU64x32 (LastBlock+1, BlockSize);
  
  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }
     
  //
  // Sync Token Init
  //
  DiskIo2TokenSync.Event = NULL;
  DiskIo2TokenSync.TransactionStatus = EFI_NOT_READY;
   
  SctPrint (L"Read Record Data.\n");
  //
  // Record all write disk data for recovery first
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
  
    SctPrint (L" =================== Record Disk Info =================== \n\n");
   
    for (IndexI = 0; IndexI < 8; IndexI++) {
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
      // parameter verification on NewBufferSize
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
          Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize);
          break;
        case 7:
          Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize);
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
          Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) + 1;
          break;
        case 16:
          Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) + 1;
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
          Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) - 1;
          break;
        case 26:
          Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) - 1;
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
      // Allocate memory for one DiskIo2Entity
      //
      Status = gtBS->AllocatePool(
                       EfiBootServicesData, 
                       sizeof(DiskIO2_Task), 
                       (VOID **) &DiskIo2EntityRead
                       );
      if (EFI_ERROR(Status)) {
        goto END;
      } 
      
      //
      // Add Read info to SyncReadDataList
      //
      SctInsertTailList(&SyncReadDataListHead, &DiskIo2EntityRead->ListEntry);
      
      DiskIo2EntityRead->Buffer     = NULL;
      DiskIo2EntityRead->Signature  = DISKIO2ENTITY_SIGNATURE;
      DiskIo2EntityRead->BufferSize = NewBufferSize;
      DiskIo2EntityRead->Offset     = Offset;
      DiskIo2EntityRead->MediaId    = MediaId;

      DiskIo2EntityRead->DiskIo2Token.Event             = NULL;
      DiskIo2EntityRead->DiskIo2Token.TransactionStatus = EFI_NOT_READY;
    
      Status=gtBS->AllocatePool(
                     EfiBootServicesData, 
                     NewBufferSize, 
                     (VOID **) &DiskIo2EntityRead->Buffer
                     );
      
      if (EFI_ERROR(Status) ){
        goto END;
      }
      
      //
      // Sync Call ReadDiskEx with the specified Offset and BufferSize to record disk data
      //
      Status = DiskIo2->ReadDiskEx (
                          DiskIo2,
                          DiskIo2EntityRead->MediaId,
                          DiskIo2EntityRead->Offset,
                          &DiskIo2EntityRead->DiskIo2Token,
                          DiskIo2EntityRead->BufferSize,
                          (VOID*)DiskIo2EntityRead->Buffer
                          );
      if (EFI_ERROR(Status)) {
        goto END;
      }
      }
    }
 
    SctPrint (L" ================ Start to do Sync WriteDiskEx call ================ \n\n");
    // 
    // do Asyn write call basing on read data result 
    //
    if (!SctIsListEmpty(&SyncReadDataListHead)) {
      for(ListEntry = SctGetFirstNode(&SyncReadDataListHead); ; ListEntry = SctGetNextNode(&SyncReadDataListHead, ListEntry)) {
        DiskIo2EntityRead = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);

        WriteBuffer = NULL;
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         DiskIo2EntityRead->BufferSize, 
                         (VOID **) &WriteBuffer
                         );
        if (EFI_ERROR(Status)) {
          goto END;
        }
    
        ReadBuffer = NULL;
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         DiskIo2EntityRead->BufferSize, 
                         (VOID **) &ReadBuffer
                         );
        if (EFI_ERROR(Status) ) {
          gtBS->FreePool(WriteBuffer);
          goto END;
        }
    
        //
        // Set test data pattern into Write Buffer  
        //
        SctSetMem (WriteBuffer, DiskIo2EntityRead->BufferSize, SYNC_WRITE_TEST_PATTERN);
        //
        // Write specified buffer2 differ from buffer to the device
        // write info comes from previous read info list
        //
        StatusWrite = DiskIo2->WriteDiskEx(
                                 DiskIo2,
                                 DiskIo2EntityRead->MediaId,
                                 DiskIo2EntityRead->Offset,
                                 &DiskIo2TokenSync,
                                 DiskIo2EntityRead->BufferSize,
                                 (VOID*)WriteBuffer
                                 );

        DiskIo2EntityRead->MemCompared = FALSE;
        DiskIo2EntityRead->ComparedVal = 0;

        if (EFI_ERROR(StatusWrite)) {
          DiskIo2EntityRead->AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          DiskIo2EntityRead->AssertionType = EFI_TEST_ASSERTION_PASSED;

          Status = DiskIo2->ReadDiskEx(
                              DiskIo2,
                              DiskIo2EntityRead->MediaId,
                              DiskIo2EntityRead->Offset,
                              &DiskIo2TokenSync,
                              DiskIo2EntityRead->BufferSize,
                              ReadBuffer
                              );

          if (!EFI_ERROR(Status)) {
            DiskIo2EntityRead->MemCompared = TRUE;
            for (IndexI = 0; IndexI < DiskIo2EntityRead->BufferSize; IndexI++) {
              if (ReadBuffer[IndexI] != SYNC_WRITE_TEST_PATTERN) {
                DiskIo2EntityRead->AssertionType = EFI_TEST_ASSERTION_FAILED;
                DiskIo2EntityRead->ComparedVal   = 1;
                break;
              }
            } 
          }
        }

        gtBS->FreePool(WriteBuffer);
        gtBS->FreePool(ReadBuffer);
    
        //
        // Last list node handled
        //
        if (SctIsNodeAtEnd(&SyncReadDataListHead, ListEntry)) {
          break;
        }
      }
    }
  }

END:
  //
  // Clean up & free all record resources
  //
  SctPrint (L"Restore All written disk.\n");
  if (!SctIsListEmpty(&SyncReadDataListHead)) {
    for(ListEntry = SctGetFirstNode(&SyncReadDataListHead); ; ListEntry = SctGetNextNode(&SyncReadDataListHead, ListEntry)) {
      DiskIo2EntityRead = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
      
      if (DiskIo2EntityRead->Buffer != NULL) {
        //
        // restore all read informations
        //
        Status = DiskIo2->WriteDiskEx (
                            DiskIo2,
                            DiskIo2EntityRead->MediaId,
                            DiskIo2EntityRead->Offset,
                            &DiskIo2EntityRead->DiskIo2Token,
                            DiskIo2EntityRead->BufferSize,
                            (VOID*)DiskIo2EntityRead->Buffer
                            );

        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"Restore disk fail",
                         L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx",
                         __FILE__,
                        (UINTN)__LINE__,
                         DiskIo2EntityRead->MediaId,
                         DiskIo2EntityRead->Offset,
                         DiskIo2EntityRead->BufferSize
                         );
        }
      }
    
      if (SctIsNodeAtEnd(&SyncReadDataListHead, ListEntry)) {
        break;
      }
    }
  }
  
  //
  // Record all logs
  //
  while (!SctIsListEmpty(&SyncReadDataListHead)) {
    DiskIo2EntityRead = CR(SyncReadDataListHead.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2EntityRead->ListEntry);
    
    if (DiskIo2EntityRead->MemCompared == TRUE) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     DiskIo2EntityRead->AssertionType,
                     gDiskIo2FunctionTestAssertionGuid015,
                     L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Sync Write Disk with proper parameter to valid media "    \
                     L"ASYNC_WRITE_TEST_PATTERN 0x1C",
                     L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx ReadDiskEx Buffer CompareStatus=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     DiskIo2EntityRead->MediaId,
                     DiskIo2EntityRead->Offset,
                     DiskIo2EntityRead->BufferSize,
                     DiskIo2EntityRead->Buffer,
                     DiskIo2EntityRead->ComparedVal
                     );
    } else {
      StandardLib->RecordAssertion (
                     StandardLib,
                     DiskIo2EntityRead->AssertionType,
                     gDiskIo2FunctionTestAssertionGuid015,
                     L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Sync Write Disk with proper parameter to valid media "    \
                     L"ASYNC_WRITE_TEST_PATTERN 0x1C",
                     L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                     __FILE__,
                     (UINTN)__LINE__,
                     DiskIo2EntityRead->MediaId,
                     DiskIo2EntityRead->Offset,
                     DiskIo2EntityRead->BufferSize,
                     DiskIo2EntityRead->Buffer
                     );
    }
    //
    // Free All memory
    //
    gtBS->FreePool(DiskIo2EntityRead->Buffer);
    gtBS->FreePool(DiskIo2EntityRead);
  }

  return EFI_SUCCESS;
}



/**
*   EFI_DISK_IO2_PROTOCOL.WriteDiskEx() Function Test 3. Async mode test
*  @param StandardLib a point to standard test lib
*  @param DiskIo a pointer to Disk IO the interface.
*  @param DiskIo 2 a pointer to Disk IO2 to be tested.
*  @return EFI_SUCCESS Finish the test successfully.
*/
 
EFI_STATUS
EFIAPI
BBTestWriteDiskExFunctionAutoTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  ) 
{
  EFI_STATUS            Status = EFI_SUCCESS;
  UINT32                MediaId;
  BOOLEAN               RemovableMedia;
  BOOLEAN               MediaPresent;
  BOOLEAN               LogicalPartition;
  BOOLEAN               ReadOnly;
  BOOLEAN               WriteCaching;
  UINT32                BlockSize;
  UINT32                IoAlign;
  EFI_LBA               LastBlock;
  UINT64                Offset;
  UINT64                LastOffset;
  UINTN                 BufferSize;
  UINT8                 *ReadBufferSync = NULL;

  UINTN                 IndexI,IndexJ;
  UINTN                 NewBufferSize;
  UINTN                 Remainder;
  EFI_DISK_IO2_TOKEN    AsyncBatchWriteToken;
  EFI_DISK_IO2_TOKEN    DiskIo2TokenSync;
  
  SCT_LIST_ENTRY        ReadListHeader;
  SCT_LIST_ENTRY        WriteListHeader;
  SCT_LIST_ENTRY        *ListEntry = NULL;
  UINTN                 WaitIndex;
  DiskIO2_Task          *DiskIo2EntityRead  = NULL;
  DiskIO2_Task          *DiskIo2EntityWrite = NULL;
  BOOLEAN               MemoryAllocFail     = FALSE;

  //
  // Initialize variable
  //
  MediaId          = BlockIo2->Media->MediaId;
  RemovableMedia   = BlockIo2->Media->RemovableMedia;
  MediaPresent     = BlockIo2->Media->MediaPresent;
  LogicalPartition = BlockIo2->Media->LogicalPartition;
  ReadOnly         = BlockIo2->Media->ReadOnly;
  WriteCaching     = BlockIo2->Media->WriteCaching;
  BlockSize        = BlockIo2->Media->BlockSize;
  IoAlign          = BlockIo2->Media->IoAlign;
  LastBlock        = BlockIo2->Media->LastBlock;
  
  BufferSize = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset = SctMultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }
  
  //
  // Initialize batch task list header & Read data list header 
  //
  ReadListHeader.ForwardLink  = &(ReadListHeader);
  ReadListHeader.BackLink     = &(ReadListHeader);
  
  WriteListHeader.ForwardLink = &(WriteListHeader);
  WriteListHeader.BackLink    = &(WriteListHeader);
  
  //
  // Sync Token Init
  //
  DiskIo2TokenSync.Event             = NULL;
  DiskIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  
  // 
  // Batch Async Token Init
  //
  AsyncBatchWriteFinished                = 0;
  AsyncBatchWriteToken.Event             = NULL;
  AsyncBatchWriteToken.TransactionStatus = EFI_NOT_READY;
  
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) DiskIo2FinishNotifyFunc,
                   &AsyncBatchWriteFinished,
                   &AsyncBatchWriteToken.Event
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create Event Fail",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    goto END;
  }
  
  SctPrint (L"Create Batch Read Task List.\n\n");
  
  //
  // Create one Batch Read task list
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    SctPrint (L" =================== Record Disk Info =================== \n\n");
    for (IndexI = 0; IndexI < 8; IndexI++) {
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
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize);
            break;
          case 7:
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize);
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
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) + 1;
            break;
          case 16:
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) + 1;
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
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) - 1) , BlockSize) - 1;
            break;
          case 26:
            Offset = SctMultU64x32((SctDivU64x32 (LastBlock, 2, &Remainder) + 1) , BlockSize) - 1;
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
        // Allocate memory for one BlockIo2Entity
        //
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         sizeof(DiskIO2_Task), 
                         (VOID **) &DiskIo2EntityRead
                         );
        if (EFI_ERROR(Status)) {
          MemoryAllocFail = TRUE;
          goto END;
        } 
        
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList(&ReadListHeader, &DiskIo2EntityRead->ListEntry);
         
        DiskIo2EntityRead->Buffer                         = NULL;
        DiskIo2EntityRead->DiskIo2Token.Event             = NULL;
        DiskIo2EntityRead->DiskIo2Token.TransactionStatus = EFI_NOT_READY;
        DiskIo2EntityRead->Signature                      = DISKIO2ENTITY_SIGNATURE;
        DiskIo2EntityRead->BufferSize                     = NewBufferSize;
        DiskIo2EntityRead->Offset                         = Offset;
        DiskIo2EntityRead->MediaId                        = MediaId;
      
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         NewBufferSize, 
                         (VOID **) &DiskIo2EntityRead->Buffer
                         );
        
        if (EFI_ERROR(Status)){
          MemoryAllocFail = TRUE;
          goto END;
        }
        
        //
        // Sync Call ReadDiskEx with the specified Offset and BufferSize
        //
        Status = DiskIo2->ReadDiskEx (
                            DiskIo2,
                            DiskIo2EntityRead->MediaId,
                            DiskIo2EntityRead->Offset,
                            &DiskIo2EntityRead->DiskIo2Token,
                            DiskIo2EntityRead->BufferSize,
                            (VOID*)DiskIo2EntityRead->Buffer
                            );
        
        if (EFI_ERROR(Status)) {
          goto END;
        }
      }//end of loop of Offset - IndexJ
    }//end of loop of BufferSize - IndexI
     
     
    SctPrint (L" =================== Create Test Write Disk  =================== \n\n");
    if (!SctIsListEmpty(&ReadListHeader)) {
      for(ListEntry = SctGetFirstNode(&ReadListHeader); ; ListEntry = SctGetNextNode(&ReadListHeader, ListEntry)) {
        
        DiskIo2EntityRead = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
        //
        // To avoid the LOG information is destroied, the LOG information will
        // be recorded after the original data is written again.
        //
        //
        // Allocate memory for one DiskIo2Entity
        //
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         sizeof(DiskIO2_Task), 
                         (VOID **) &DiskIo2EntityWrite
                         );
        if (EFI_ERROR(Status)) {
          MemoryAllocFail = TRUE;
          goto END;
        } 
        
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList(&WriteListHeader, &DiskIo2EntityWrite->ListEntry);
        
        DiskIo2EntityWrite->Buffer                         = NULL;
        DiskIo2EntityWrite->DiskIo2Token.Event             = NULL;
        DiskIo2EntityWrite->DiskIo2Token.TransactionStatus = EFI_NOT_READY;
        DiskIo2EntityWrite->Signature                      = DISKIO2ENTITY_SIGNATURE;
        DiskIo2EntityWrite->BufferSize                     = DiskIo2EntityRead->BufferSize;
        DiskIo2EntityWrite->Offset                         = DiskIo2EntityRead->Offset;
        DiskIo2EntityWrite->MediaId                        = DiskIo2EntityRead->MediaId;
           
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         DiskIo2EntityWrite->BufferSize, 
                         (VOID **) &DiskIo2EntityWrite->Buffer
                         );
        if (EFI_ERROR(Status)){
          MemoryAllocFail = TRUE;
          goto END;
        }
        
        SctSetMem (DiskIo2EntityWrite->Buffer, DiskIo2EntityWrite->BufferSize, ASYNC_WRITE_TEST_PATTERN);
        
        //
        // Last list node handled
        //
        if (SctIsNodeAtEnd(&ReadListHeader, ListEntry)) {
          break;
        }
      }
    }

    SctPrint (L"Start to do Async Write.\n\n");
    Status = DiskIo2AsyncBatchWrite (
               DiskIo2,
               &WriteListHeader,
               &AsyncBatchWriteToken
               );
    if (EFI_ERROR(Status)) {
      goto END;
    }

    //
    // Busy Waiting BathWriteToken signal
    // Busy waiting 120s on all the execute entity being moved to finished queue
    //  
    SctPrint (L"Wait maximumly 120s for Async Batch Write events signaled\n\n");
    Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
     
    IndexI = 0;
    
    while (IndexI < 120 && AsyncBatchWriteFinished == 0) {
      WaitIndex = 0xFF;
      gtBS->WaitForEvent (  
              1,
              &TimerEvent,
              &WaitIndex
              );
      IndexI++;
      SctPrint (L".");
    }
    
    Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
    SctPrint (L"\n");
  }
  
  
  
END:

  //
  // Verify Async Write Task List Result 
  //
  if (!SctIsListEmpty(&WriteListHeader) && MemoryAllocFail == FALSE) {
    for(ListEntry = SctGetFirstNode(&WriteListHeader); ; ListEntry = SctGetNextNode(&WriteListHeader, ListEntry)) {
      DiskIo2EntityWrite = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);

      DiskIo2EntityWrite->MemCompared = FALSE;
      DiskIo2EntityWrite->ComparedVal = 0;
      
      if (DiskIo2EntityWrite->DiskIo2Token.TransactionStatus == EFI_SUCCESS) {
      
        DiskIo2EntityWrite->AssertionType = EFI_TEST_ASSERTION_PASSED;
      
        gtBS->AllocatePool(
                EfiBootServicesData, 
                DiskIo2EntityWrite->BufferSize, 
                (VOID **) &ReadBufferSync
                );

        if (ReadBufferSync != NULL) {
          Status = DiskIo2->ReadDiskEx(
                              DiskIo2,
                              DiskIo2EntityWrite->MediaId,
                              DiskIo2EntityWrite->Offset,
                              &DiskIo2TokenSync,
                              DiskIo2EntityWrite->BufferSize,
                              ReadBufferSync
                              );
          //                    
          // Compare with write test pattern
          //
          if (Status == EFI_SUCCESS) {
            for (IndexI = 0; IndexI < DiskIo2EntityWrite->BufferSize; IndexI++) {
              if (ReadBufferSync[IndexI] != ASYNC_WRITE_TEST_PATTERN) {
                DiskIo2EntityWrite->AssertionType = EFI_TEST_ASSERTION_FAILED;
                DiskIo2EntityWrite->ComparedVal   = 1;
                break;
              }
            }
            DiskIo2EntityWrite->MemCompared = TRUE;
          }
     
          gtBS->FreePool(ReadBufferSync);
          ReadBufferSync = NULL;
        }
      } else {
          DiskIo2EntityWrite->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    
      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&WriteListHeader, ListEntry)) {
        break;
      }
    }
  }
   
  //
  // Restore written disk data & Clean up record list 
  //
  while(!SctIsListEmpty(&ReadListHeader)) {
    DiskIo2EntityRead = CR(ReadListHeader.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2EntityRead->ListEntry); 
    
    if (DiskIo2EntityRead->Buffer != NULL) {
      //
      // restore all read informations
      //
      Status = DiskIo2->WriteDiskEx (
                          DiskIo2,
                          DiskIo2EntityRead->MediaId,
                          DiskIo2EntityRead->Offset,
                          &DiskIo2EntityRead->DiskIo2Token,
                          DiskIo2EntityRead->BufferSize,
                          (VOID*)DiskIo2EntityRead->Buffer
                          );
    
      if (Status != EFI_SUCCESS) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Restore blocks fail",
                       L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx",
                       __FILE__,
                       (UINTN)__LINE__,
                       DiskIo2EntityRead->MediaId,
                       DiskIo2EntityRead->Offset,
                       DiskIo2EntityRead->BufferSize
                       );
      }
      if (DiskIo2EntityRead->Buffer != NULL) {
        gtBS->FreePool (DiskIo2EntityRead->Buffer);
      }
    }
    
    if (DiskIo2EntityRead != NULL) {
      gtBS->FreePool(DiskIo2EntityRead);
    }
  }
     


  //
  // Do logging & clean up Write list
  //
  while(!SctIsListEmpty(&WriteListHeader)) {
    DiskIo2EntityWrite = CR(WriteListHeader.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2EntityWrite->ListEntry);
    
    if (MemoryAllocFail == FALSE) {
      if (DiskIo2EntityWrite->MemCompared == TRUE) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       DiskIo2EntityWrite->AssertionType,
                       gDiskIo2FunctionTestAssertionGuid016,
                       L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Batch Async Write Disk with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, BufferAddr=0x%lx, TransactionStatus=%r, ReadDiskEx Buffer CompareStatus=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       DiskIo2EntityWrite->BufferSize,
                       DiskIo2EntityWrite->Offset,
                       DiskIo2EntityWrite->Buffer,
                       DiskIo2EntityWrite->DiskIo2Token.TransactionStatus,
                       DiskIo2EntityWrite->ComparedVal
                       );
      } else {
        StandardLib->RecordAssertion (
                       StandardLib,
                       DiskIo2EntityWrite->AssertionType,
                       gDiskIo2FunctionTestAssertionGuid016,
                       L"EFI_DISK_IO2_PROTOCOL.WriteDiskEx - Batch Async Write Disk with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, Offset=0x%lx, BufferAddr=0x%lx, TransactionStatus=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       DiskIo2EntityWrite->BufferSize,
                       DiskIo2EntityWrite->Offset,
                       DiskIo2EntityWrite->Buffer,
                       DiskIo2EntityWrite->DiskIo2Token.TransactionStatus
                       );
      }
    }
  
    if (DiskIo2EntityWrite->DiskIo2Token.TransactionStatus == EFI_SUCCESS){
      gtBS->CloseEvent (DiskIo2EntityWrite->DiskIo2Token.Event);
    }

    if (DiskIo2EntityWrite->Buffer != NULL) {
      gtBS->FreePool (DiskIo2EntityWrite->Buffer);
    }
    if (DiskIo2EntityWrite != NULL) {
      gtBS->FreePool(DiskIo2EntityWrite);
    }
  }

  if (AsyncBatchWriteToken.Event != NULL) {
    gtBS->CloseEvent (AsyncBatchWriteToken.Event);
  }

  return Status;
}

