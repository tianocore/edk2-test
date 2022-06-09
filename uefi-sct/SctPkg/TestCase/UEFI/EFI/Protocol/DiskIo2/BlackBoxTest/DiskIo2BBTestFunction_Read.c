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
BBTestReadDiskExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

EFI_STATUS
EFIAPI
BBTestReadDiskExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );


EFI_STATUS
EFIAPI
BBTestReadDiskExFunctionAutoTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );


EFI_STATUS
EFIAPI
BBTestReadDiskExFunctionAutoTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

#define EFI_INITIALIZE_LOCK_VARIABLE(Tpl) {Tpl,0,0}

//
// Async Read Queue
//
SCT_LIST_ENTRY  AsyncReadExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncReadExecuteListHead);
SCT_LIST_ENTRY  AsyncReadFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncReadFinishListHead);
SCT_LIST_ENTRY  AsyncReadFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncReadFailListHead);

//
// Async Read lock
//
SCT_LOCK  gAsyncReadQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);

//
// Mixed Async Read Queue
//
SCT_LIST_ENTRY  MixedReadExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedReadExecuteListHead);
SCT_LIST_ENTRY  MixedReadFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedReadFinishListHead);
SCT_LIST_ENTRY  MixedReadFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedReadFailListHead);

//
// Sync Read Queue
//
SCT_LIST_ENTRY  SyncReadListHead     = INITIALIZE_SCT_LIST_HEAD_VARIABLE(SyncReadListHead);
SCT_LIST_ENTRY  SyncReadFailListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(SyncReadFailListHead);

//
// Mixed Sync & Async Read lock
//
SCT_LOCK  gMixedReadQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);

//
// Async signal
//
UINTN  AsyncBatchReadFinished = 0;


VOID
EFIAPI DiskIo2ReadNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  DiskIO2_Task *DiskIo2Entity;
  
  DiskIo2Entity = (DiskIO2_Task *)Context;

  //
  // Remove entity from ReadExecuteListHead &  add entity to ReadFinishListHead
  // All DiskIo2 Notify function run at Call Back level only once, So no locks required
  //
  SctAcquireLock (&gAsyncReadQueueLock);
  SctRemoveEntryList(&DiskIo2Entity->ListEntry);
  SctInsertTailList(&AsyncReadFinishListHead, &DiskIo2Entity->ListEntry);
  SctReleaseLock (&gAsyncReadQueueLock);
}


/**
 *  Provide EFI_DISK_IO2_PROTOCOL.ReadDiskEx() function abstraction interface
 *  @param DiskIo 2 a pointer to Disk IO2 to be tested.
 *  @param MediaId Read media ID.
 *  @param Offset the starting byte offset to read from.
 *  @param BufferSize write databuffer size.
 *  @param Buffer a pointer to read data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
DiskIo2AsyncReadData (
  IN EFI_DISK_IO2_PROTOCOL            *DiskIo2,
  IN UINT32                            MediaId,
  IN UINT64                            Offset,
  IN UINTN                             BufferSize,
  OUT VOID                             *Buffer
)
{

  EFI_STATUS                         Status;
  DiskIO2_Task                       *DiskIo2Entity = NULL;

  ASSERT(DiskIo2 != NULL);
  
  //
  // Allocate memory for one DiskIo2Entity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(DiskIO2_Task), 
                   (VOID **) &DiskIo2Entity);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  // DiskIo2Token initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) DiskIo2ReadNotifyFunc,
                   DiskIo2Entity,
                   &DiskIo2Entity->DiskIo2Token.Event
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(DiskIo2Entity);
    return Status;
  }

  DiskIo2Entity->DiskIo2Token.TransactionStatus = EFI_NOT_READY;
  DiskIo2Entity->Buffer                         = Buffer;

  SctAcquireLock (&gAsyncReadQueueLock);
  SctInsertTailList(&AsyncReadExecuteListHead, &DiskIo2Entity->ListEntry);
  SctReleaseLock (&gAsyncReadQueueLock);
  
  //
  // Async ReadDiskEx Call
  //
  Status = DiskIo2->ReadDiskEx (
                      DiskIo2,
                      MediaId,
                      Offset,
                      &DiskIo2Entity->DiskIo2Token,
                      BufferSize,
                      Buffer
                      );
  
  if (EFI_ERROR (Status)) {
    SctAcquireLock (&gAsyncReadQueueLock);
    SctRemoveEntryList(&DiskIo2Entity->ListEntry);
    SctInsertTailList(&AsyncReadFailListHead, &DiskIo2Entity->ListEntry);    
    SctReleaseLock (&gAsyncReadQueueLock);

    DiskIo2Entity->Buffer = NULL;

    return Status;
  }

  //
  // Record execution Info to Disk IO 2 entity 
  //
  DiskIo2Entity->Signature   = DISKIO2ENTITY_SIGNATURE;
  DiskIo2Entity->MediaId     = MediaId;
  DiskIo2Entity->Offset      = Offset;
  DiskIo2Entity->BufferSize  = BufferSize;
  DiskIo2Entity->StatusAsync = Status;
  //
  // memory uncompared with DiskIO interface
  //
  DiskIo2Entity->MemCompared = FALSE;
  
  return Status;
}




VOID
EFIAPI DiskIo2AsyncReadBatchNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  
  DiskIO2_Batch_Task_Context          *TaskContext;
  DiskIO2_Task                        *DiskIo2Entity    = NULL;
  SCT_LIST_ENTRY                      *CurrentTaskEntry = NULL;
  EFI_DISK_IO2_PROTOCOL               *DiskIo2          = NULL;
  EFI_STATUS                          Status;

  
  TaskContext      = (DiskIO2_Batch_Task_Context *) Context;
  CurrentTaskEntry = TaskContext->CurrentTaskEntry;
  DiskIo2          = TaskContext->DiskIo2;

  if (!SctIsNodeAtEnd(TaskContext->TaskHeader, CurrentTaskEntry) ){
    DiskIo2Entity = CR(CurrentTaskEntry->ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);

    DiskIo2Entity->DiskIo2Token.Event = NULL;
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) DiskIo2AsyncReadBatchNotifyFunc,
                     TaskContext,
                     &DiskIo2Entity->DiskIo2Token.Event
                     );
    if (Status != EFI_SUCCESS) {
      return;
    }

    //
    // Current Task Entry move forward
    //
    TaskContext->CurrentTaskEntry = CurrentTaskEntry->ForwardLink;

    Status = DiskIo2->ReadDiskEx (
                        DiskIo2,
                        DiskIo2Entity->MediaId,
                        DiskIo2Entity->Offset,
                        &DiskIo2Entity->DiskIo2Token,
                        DiskIo2Entity->BufferSize,
                        DiskIo2Entity->Buffer
                        );
    if (Status != EFI_SUCCESS) {
      return;
    }
  } else {
      //
      // All Task has been handled, kick off notify event & clean Task context
      //
      gtBS->SignalEvent (TaskContext->Token->Event);

      gtBS->FreePool (TaskContext);

      return;
    }
}


/**
 *  Provide Async Batch Read Task for EFI_DISK_IO2_PROTOCOL.ReadDiskEx() function 
 *  @param DiskIo 2 a pointer to Disk IO2 to be tested.
 *  @param TaskList point to batch task list.
 *  @param Token task list token.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
DiskIo2AsyncBatchRead (
  IN EFI_DISK_IO2_PROTOCOL           *DiskIo2,
  IN SCT_LIST_ENTRY                  *ListHeader,
  IN OUT EFI_DISK_IO2_TOKEN	         *Token
)
{
  DiskIO2_Batch_Task_Context         *TaskContext = NULL;
  DiskIO2_Task                       *DiskIo2Entity = NULL;
  EFI_STATUS                         Status = EFI_SUCCESS;
  
  ASSERT(Token != NULL && Token->Event != NULL);
  
  if (!SctIsListEmpty(ListHeader)) {  
    //
    // Task Context will be freed in DiskIo2ReadBatchNotifyFunc when all task finished
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
                     (EFI_EVENT_NOTIFY) DiskIo2AsyncReadBatchNotifyFunc,
                     TaskContext,
                     &DiskIo2Entity->DiskIo2Token.Event
                     );
    if (Status != EFI_SUCCESS) {
      return Status;
    }
    
    Status = DiskIo2->ReadDiskEx (
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


VOID
EFIAPI DiskIo2MixedReadNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  DiskIO2_Task *DiskIo2Entity=NULL;
  
  DiskIo2Entity = (DiskIO2_Task *)Context;

  //
  // Remove entity from MixedReadExecuteListHead &  add entity to MixedReadFinishListHead
  // All DiskIo2 Notify function run at Call Back level only once, So no locks required
  //
  SctRemoveEntryList(&DiskIo2Entity->ListEntry);
  SctInsertTailList(&MixedReadFinishListHead, &DiskIo2Entity->ListEntry);
}


/**
 *   Provide EFI_DISK_IO2_PROTOCOL.ReadDiskEx() function abstraction interface
 *  Mix Disk Io2 ReadDiskEx Async Read & Sync Read
 *  @param DiskIo 2 a pointer to Disk IO2 to be tested.
 *  @param MediaId Read media ID.
 *  @param Offset the starting byte offset to read from.
 *  @param BufferSize write databuffer size.
 *  @param Buffer a pointer to read data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

STATIC
EFI_STATUS
DiskIo2MixedReadData (
  IN EFI_DISK_IO2_PROTOCOL             *DiskIo2,
  IN UINT32                            MediaId,
  IN UINT64                            Offset,
  IN UINTN                             BufferSize,
  OUT VOID                             *Buffer
)
{
  
  EFI_STATUS                           Status;
  DiskIO2_Task                         *DiskIo2Entity     = NULL;
  DiskIO2_Task                         *DiskIo2EntitySync = NULL;
  VOID                                 *BufferSync        = NULL;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib       = NULL;
  
  ASSERT(DiskIo2 != NULL);
  
  //
  // Allocate memory for one DiskIo2Entity
  //
  Status = gtBS->AllocatePool(EfiBootServicesData, sizeof(DiskIO2_Task), (VOID **) &DiskIo2Entity);
  
  if (Status != EFI_SUCCESS) {
    gtBS->FreePool(Buffer);
    return Status;
  }
  
  //
  // DiskIo2Token initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) DiskIo2MixedReadNotifyFunc,
                   DiskIo2Entity,
                   &DiskIo2Entity->DiskIo2Token.Event
                   );
  
  if (Status != EFI_SUCCESS) {
    gtBS->FreePool(DiskIo2Entity);
    gtBS->FreePool(Buffer);
    return Status;
  }
  
  DiskIo2Entity->DiskIo2Token.TransactionStatus = EFI_NOT_READY;
  DiskIo2Entity->Signature                      = DISKIO2ENTITY_SIGNATURE;
  DiskIo2Entity->MediaId                        = MediaId;
  DiskIo2Entity->Offset                         = Offset;
  DiskIo2Entity->BufferSize                     = BufferSize;
  DiskIo2Entity->Buffer                         = Buffer;
  
  DiskIo2Entity->MemCompared                    = FALSE;  
  DiskIo2Entity->ComparedVal                    = 1;

  //
  // Acquire lock to add entity to Execution ListHead
  //
  SctAcquireLock (&gMixedReadQueueLock);
  SctInsertTailList(&MixedReadExecuteListHead, &DiskIo2Entity->ListEntry);
  SctReleaseLock (&gMixedReadQueueLock);
  
  //
  // Async ReadDiskEx Call
  //
  Status = DiskIo2->ReadDiskEx (
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
    // Put failure execution into fail List
    //
    SctAcquireLock (&gMixedReadQueueLock);
    SctRemoveEntryList(&DiskIo2Entity->ListEntry);
    SctInsertTailList(&MixedReadFailListHead, &DiskIo2Entity->ListEntry);
    SctReleaseLock (&gMixedReadQueueLock);

    gtBS->FreePool(Buffer);

    return Status;
  }

  //
  // Sync Call comes after a successful Async Read 
  //

  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &BufferSync);

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
    
  //
  // Allocate memory for one DiskIo2Entity
  //
  Status = gtBS->AllocatePool(EfiBootServicesData, sizeof(DiskIO2_Task), (VOID **) &DiskIo2EntitySync);

  if (Status != EFI_SUCCESS) {
    gtBS->FreePool(BufferSync);
    return Status;
  }

//
// Record  Sync execution Info to Disk IO 2 entity 
//
  DiskIo2EntitySync->Signature          = DISKIO2ENTITY_SIGNATURE;
  DiskIo2EntitySync->MediaId            = MediaId;
  DiskIo2EntitySync->Offset             = Offset;
  DiskIo2EntitySync->BufferSize         = BufferSize;
  DiskIo2EntitySync->Buffer             = BufferSync;
  DiskIo2EntitySync->DiskIo2Token.Event = NULL;

//
// memory uncompared with DISKIO 2 Async interface
//
  DiskIo2EntitySync->MemCompared = FALSE;
  DiskIo2EntitySync->ComparedVal = 1;

  Status = DiskIo2->ReadDiskEx (
                      DiskIo2,
                      DiskIo2EntitySync->MediaId,
                      DiskIo2EntitySync->Offset,
                      &DiskIo2EntitySync->DiskIo2Token,
                      DiskIo2EntitySync->BufferSize,
                      DiskIo2EntitySync->Buffer
                      );
  if (!EFI_ERROR(Status)) {
    SctInsertTailList(&SyncReadListHead, &DiskIo2EntitySync->ListEntry);
  } else {
    SctInsertTailList(&SyncReadFailListHead, &DiskIo2EntitySync->ListEntry);
  }

  return Status;
}


VOID
EFIAPI DiskIo2FinishNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{


  UINTN * flag = (UINTN *)Context;
  *flag        = 1;
}

/**
 *  Entrypoint for EFI_DISK_IO2_PROTOCOL.Cancel() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS or EFI_DEVICE_ERROR Finish the test successfully.
 */


EFI_STATUS
EFIAPI
BBTestCancelFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DISK_IO2_PROTOCOL                *DiskIo2;
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

  DiskIo2 = (EFI_DISK_IO2_PROTOCOL *)ClientInterface;

  //
  // Assertion Point
  // 
  //
  Status = DiskIo2->Cancel (DiskIo2);
  
  if (Status != EFI_DEVICE_ERROR && Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }


  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDiskIo2FunctionTestAssertionGuid001,
                 L"EFI_DISK_IO2_PROTOCOL.Cancel - Cancel the Disk IO 2 device",
                 L"%a:%d:Status=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}



/**
 *  Entrypoint for EFI_DISK_IO2_PROTOCOL.ReadDiskEx() Function Test.
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
BBTestReadDiskExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                           Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib   = NULL;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2      = NULL;
  EFI_DISK_IO_PROTOCOL                 *DiskIo        = NULL;
  EFI_DISK_IO2_PROTOCOL                *DiskIo2       = NULL;
  EFI_DISK_IO2_PROTOCOL                *DiskIo2Temp   = NULL;
  
  EFI_DEVICE_PATH_PROTOCOL	           *DevicePath    = NULL;
  CHAR16                               *DevicePathStr = NULL;
  UINTN                                Index;
  UINTN                                NoHandles;
  EFI_HANDLE                           *HandleBuffer  = NULL;

  
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
  // Locate DISK IO protocol on same handler for test
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
  // Async call 1 to test Disk IO 2 ReadDiskEx
  // Using Link list to manage token pool
  //
  BBTestReadDiskExFunctionAutoTestCheckpoint1 (StandardLib, DiskIo, DiskIo2,BlockIo2);
  
  //
  // Sync call to test Disk IO 2 ReadDiskEx
  //
  BBTestReadDiskExFunctionAutoTestCheckpoint2 (StandardLib, DiskIo, DiskIo2,BlockIo2);
  
  //
  // Async call 2 to test Disk IO 2 ReadDiskEx
  // Using Cascade Event Chain to manage token pool
  //
  BBTestReadDiskExFunctionAutoTestCheckpoint3 (StandardLib, DiskIo, DiskIo2,BlockIo2);


  //
  // Mixed Sync & Async Call to test Disk IO 2 ReadDiskEx
  //
  BBTestReadDiskExFunctionAutoTestCheckpoint4 (StandardLib, DiskIo, DiskIo2,BlockIo2);

  return Status;
  
}


/**
 *   EFI_DISK_IO2_PROTOCOL.ReadDiskEx() Function Test 1. Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param DiskIo a pointer to Disk IO the interface.
 *  @param DiskIo 2 a pointer to Disk IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestReadDiskExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS        Status      = EFI_SUCCESS;
  EFI_STATUS        StatusAsync = EFI_SUCCESS;
  EFI_STATUS        StatusSync;
  
  UINT32            MediaId;
  BOOLEAN           RemovableMedia;
  BOOLEAN           MediaPresent;
  BOOLEAN           LogicalPartition;
  BOOLEAN           ReadOnly;
  BOOLEAN           WriteCaching;
  UINT32            BlockSize;
  UINT32            IoAlign;
  EFI_LBA           LastBlock;
  UINT64            LastOffset;
  UINTN             BufferSize;
  
  VOID              *BufferAsync = NULL;
  VOID              *BufferSync  = NULL;
  
  UINTN             IndexI,IndexJ;
  UINTN             NewBufferSize;

  UINT64            Offset;
  UINTN             Remainder;

  DiskIO2_Task      *DiskIo2Entity = NULL;
  UINTN             WaitIndex;
  SCT_LIST_ENTRY    *ListEntry     = NULL;
  
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
  
  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = SctMultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }
  
  //
  // Assertion Point 5.2.2.1
  // ReadDiskEx must succeed to read proper data from device with valid parameter
  //
  if ((MediaPresent == TRUE) && (LastBlock != 0)) {
   
    SctPrint (L" ================ Start to do Async ReadDiskEx call ================ \n\n");
 
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
          NewBufferSize = BufferSize + 1;
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
        // allocate bufferasync
        //
        Status = gtBS->AllocatePool (EfiBootServicesData, NewBufferSize, (VOID **) &BufferAsync);

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
          goto END_WAIT;
        }

        //
        // Async Call ReadDiskEx with the specified Offset and BufferSize
        //
        StatusAsync = DiskIo2AsyncReadData (
                        DiskIo2,
                        MediaId,
                        Offset,
                        NewBufferSize,
                        BufferAsync
                        );
        
      }//end of loop of Offset - IndecJ
    }//end of loop of BufferSize - IndexI

    SctPrint (L" ================== Async ReadDiskEx call finshed ================== \n\n");


END_WAIT:
    //
    // Busy waiting 120s on all the execute entity being moved to finished queue
    //  
    SctPrint (L"Wait maximumly 120s for all Async Read events signaled\n\n");
    Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
    IndexI = 0;
    
    SctAcquireLock (&gAsyncReadQueueLock);
    while (!SctIsListEmpty(&AsyncReadExecuteListHead) && IndexI < 120) {
      SctReleaseLock (&gAsyncReadQueueLock);
    
      gtBS->WaitForEvent (                   
              1,
              &TimerEvent,
              &WaitIndex
              );
      IndexI++;

      SctPrint (L".");
      SctAcquireLock (&gAsyncReadQueueLock);
    }
    SctReleaseLock (&gAsyncReadQueueLock);

    Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
    SctPrint (L"\n");
  }

  //
  // clear all Disk IO2 events from gReadFinishQueue 
  // gReadFinshQueue is handled first since we use Disk IO read to do read buffer validation 
  // Here no logs should be wrote to this disk device to keep data intact
  //
  SctAcquireLock (&gAsyncReadQueueLock);
  if (!SctIsListEmpty(&AsyncReadFinishListHead)) {
    for(ListEntry = SctGetFirstNode(&AsyncReadFinishListHead); ; ListEntry = SctGetNextNode(&AsyncReadFinishListHead, ListEntry)) {
      DiskIo2Entity = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncReadQueueLock);

      //
      // Check & record every Disk IO2 execution entity status 
      // Using Disk IO Protocol to verify data buffer consistency
      //
      if (DiskIo != NULL && DiskIo2Entity->DiskIo2Token.TransactionStatus == EFI_SUCCESS) {

        Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &BufferSync);

        if (BufferSync != NULL) {
          StatusSync = DiskIo->ReadDisk(
                                  DiskIo,
                                  DiskIo2Entity->MediaId,
                                  DiskIo2Entity->Offset,
                                  DiskIo2Entity->BufferSize,
                                  BufferSync
                                  );
     
          DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
 
          if (StatusSync == EFI_SUCCESS) {
            DiskIo2Entity->ComparedVal = SctCompareMem (
                                            DiskIo2Entity->Buffer,
                                            BufferSync,
                                            DiskIo2Entity->BufferSize
                                            );
            //
            // Disk IO Memory compare job done
            //
            DiskIo2Entity->MemCompared = TRUE;   

            if (DiskIo2Entity->ComparedVal == 0) {
              DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
            }
          } else {
              if (DiskIo2Entity->DiskIo2Token.TransactionStatus == EFI_SUCCESS){
                DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
              }   
            }
     
          gtBS->FreePool(BufferSync);
          BufferSync = NULL;
        }
      } else if (DiskIo2Entity->DiskIo2Token.TransactionStatus == EFI_SUCCESS){
          DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
          DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

      SctAcquireLock (&gAsyncReadQueueLock);
      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&AsyncReadFinishListHead, ListEntry)) {
         break;
      }
    }
  }
  SctReleaseLock (&gAsyncReadQueueLock);
 
  //
  // Record All Finished Read case results
  //
  SctAcquireLock (&gAsyncReadQueueLock);
  while (!SctIsListEmpty(&AsyncReadFinishListHead)) {
    DiskIo2Entity = CR(AsyncReadFinishListHead.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);   
    SctRemoveEntryList(&DiskIo2Entity->ListEntry);
    SctReleaseLock (&gAsyncReadQueueLock);
    
    if (DiskIo2Entity->MemCompared == TRUE) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     DiskIo2Entity->AssertionType,
                     gDiskIo2FunctionTestAssertionGuid002,
                     L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Async Read Disk with proper parameter from valid media",
                     L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx Disk IO Memory CompareStatus=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     DiskIo2Entity->MediaId,
                     DiskIo2Entity->Offset,
                     DiskIo2Entity->BufferSize,
                     DiskIo2Entity->Buffer,
                     DiskIo2Entity->ComparedVal
                     );
    } else {
      StandardLib->RecordAssertion (
                     StandardLib,
                     DiskIo2Entity->AssertionType,
                     gDiskIo2FunctionTestAssertionGuid002,
                     L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Async Read Disk with proper parameter from valid media",
                     L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                     __FILE__,
                     (UINTN)__LINE__,
                     DiskIo2Entity->MediaId,
                     DiskIo2Entity->Offset,
                     DiskIo2Entity->BufferSize,
                     DiskIo2Entity->Buffer
                     );
    }

    if (DiskIo2Entity->Buffer != NULL) {
      Status = gtBS->FreePool (DiskIo2Entity->Buffer);
    }
    gtBS->CloseEvent(DiskIo2Entity->DiskIo2Token.Event);
    gtBS->FreePool(DiskIo2Entity);

    SctAcquireLock (&gAsyncReadQueueLock);
  }  
  SctReleaseLock (&gAsyncReadQueueLock);


  //
  // If ReadFailListHead is not empty, which means some Async Calls are wrong 
  //
  SctAcquireLock (&gAsyncReadQueueLock);
  while(!SctIsListEmpty(&AsyncReadFailListHead)) {
    DiskIo2Entity = CR(AsyncReadFailListHead.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2Entity->ListEntry);
    SctReleaseLock (&gAsyncReadQueueLock);
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gDiskIo2FunctionTestAssertionGuid003,
                   L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Async Read Disk with proper parameter from valid media "    \
                   L"Read Failed ",
                   L"%a:%d:BufferSize=%d, Offset=0x%lx, StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   DiskIo2Entity->BufferSize,
                   DiskIo2Entity->Offset,
                   DiskIo2Entity->StatusAsync
                   );
     //
     // Free  Buffer
     //
     if (DiskIo2Entity->Buffer != NULL) {
       Status =gtBS->FreePool (DiskIo2Entity->Buffer);
     }
     gtBS->CloseEvent(DiskIo2Entity->DiskIo2Token.Event);
     gtBS->FreePool(DiskIo2Entity);
     
     SctAcquireLock (&gAsyncReadQueueLock);
  }
  SctReleaseLock (&gAsyncReadQueueLock);
  

  //
  // If ReadExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  SctAcquireLock (&gAsyncReadQueueLock);
  if (!SctIsListEmpty(&AsyncReadExecuteListHead)) {
    for(ListEntry = SctGetFirstNode(&AsyncReadExecuteListHead); ; ListEntry = SctGetNextNode(&AsyncReadExecuteListHead, ListEntry)) {
      DiskIo2Entity = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gAsyncReadQueueLock);
  
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gDiskIo2FunctionTestAssertionGuid004,
                     L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Async Read Disk with proper parameter from valid media "   \
                     L"Read event has not been signaled",
                      L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx Buffer=0x%lx ",
                     __FILE__,
                     (UINTN)__LINE__,
                     DiskIo2Entity->MediaId,
                     DiskIo2Entity->Offset,
                     DiskIo2Entity->BufferSize,
                     DiskIo2Entity->Buffer
                     );
  
      SctAcquireLock (&gAsyncReadQueueLock);
      if (SctIsNodeAtEnd(&AsyncReadExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  SctReleaseLock (&gAsyncReadQueueLock);

  return EFI_SUCCESS;
}


/**
 *   EFI_DISK_IO2_PROTOCOL.ReadDiskEx() Function Test 2. Sync mode test
 *  @param StandardLib a point to standard test lib
 *  @param DiskIo a pointer to Disk IO the interface.
 *  @param DiskIo 2 a pointer to Disk IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestReadDiskExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS            Status     = EFI_SUCCESS;
  EFI_STATUS            StatusSync = EFI_SUCCESS;
  EFI_TEST_ASSERTION    AssertionType;
  
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
  UINT64                LastOffset;
  
  VOID                  *DiskIoBuffer      = NULL;
  VOID                  *DiskIo2BufferSync = NULL;
  
  UINTN                 IndexI,IndexJ;
  UINTN                 NewBufferSize;

  UINT64                Offset;
  UINTN                 Remainder;
  
  EFI_DISK_IO2_TOKEN    DiskIo2TokenSync;
  BOOLEAN               MemCompared;
  UINTN                 CompareVal = 0;
  
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

  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = SctMultU64x32 (LastBlock+1, BlockSize);


  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }

  //
  // Sync Token Init
  //
  DiskIo2TokenSync.Event             = NULL;
  DiskIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  
  //
  // allocate DiskIoBuffer if Disk IO protocol is null then ignore this
  //
  if (DiskIo != NULL) {
    Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &DiskIoBuffer);
    if (Status != EFI_SUCCESS) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - Allocate DiskIoBuffer for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     EFI_OUT_OF_RESOURCES
                     );
      goto END;
    }
  }
  
  //
  // allocate  DiskIo2BufferSync
  //
  
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &DiskIo2BufferSync);
  
  if (DiskIo2BufferSync == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate DiskIo2BufferSync for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_OUT_OF_RESOURCES
                   );
    goto END;
  }
  
  //
  // Assertion Point 5.2.2.1
  // ReadDiskEx must succeed to read proper data from device with valid parameter
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
          NewBufferSize = BufferSize + 1;
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
        // Sync Call Disk IO2 ReadDiskEx with specified Offset and BufferSize
        //
        StatusSync = DiskIo2->ReadDiskEx (
                                DiskIo2,
                                MediaId,
                                Offset,
                                &DiskIo2TokenSync,
                                NewBufferSize,
                                DiskIo2BufferSync
                                );
        //
        // Sync Call Disk IO ReadDisk with specified Offset and BufferSize
        //
        MemCompared = FALSE;
        if (StatusSync == EFI_SUCCESS && DiskIo != NULL) {
          Status = DiskIo->ReadDisk (
                              DiskIo,
                              MediaId,
                              Offset,
                              NewBufferSize,
                              DiskIoBuffer
                              );
                              
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          
          if (Status == EFI_SUCCESS) {
            CompareVal = SctCompareMem (DiskIo2BufferSync, DiskIoBuffer, NewBufferSize);
            MemCompared = TRUE;
            if (CompareVal == 0) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            }
          }else {
              if (!EFI_ERROR(StatusSync)) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              }
            }
        }else if (EFI_ERROR(StatusSync)) {
           AssertionType = EFI_TEST_ASSERTION_FAILED;
        }else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }

        if (MemCompared == TRUE) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gDiskIo2FunctionTestAssertionGuid005,
                         L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Sync Read Disk with proper parameter from valid media",
                         L"%a:%d:BufferSize=0x%lx, Offset=0x%lx, StatusSync=%r Disk IO Memory CompareStatus=%r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         StatusSync,
                         CompareVal
                         );
        }else {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gDiskIo2FunctionTestAssertionGuid005,
                         L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Sync Read Disk with proper parameter from valid media",
                         L"%a:%d:BufferSize=0x%lx, Offset=0x%lx, StatusSync=%r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         Offset,
                         StatusSync
                         );
        }

      }//end of loop of Offset - IndexJ
    }//end of loop of BufferSize - IndexI
  }

END:

  if (DiskIoBuffer != NULL) {
    gtBS->FreePool (DiskIoBuffer);
  }

  if (DiskIo2BufferSync != NULL) {
    gtBS->FreePool (DiskIo2BufferSync);
  }

  return Status;
}


/**
 *   EFI_DISK_IO2_PROTOCOL.ReadDiskEx() Function Test 3. Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param DiskIo a pointer to Disk IO the interface.
 *  @param DiskIo 2 a pointer to Disk IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestReadDiskExFunctionAutoTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS            Status = EFI_SUCCESS;
  EFI_STATUS            DiskIoStatus;
  UINT32                MediaId;
  BOOLEAN               RemovableMedia;
  BOOLEAN               MediaPresent;
  BOOLEAN               LogicalPartition;
  BOOLEAN               ReadOnly;
  BOOLEAN               WriteCaching;
  UINT32                BlockSize;
  UINT32                IoAlign;
  EFI_LBA               LastBlock;

  UINT64                LastOffset;
  UINTN                 BufferSize; 
  VOID                  *DiskIoBuffer = NULL;

  UINTN                 IndexI,IndexJ;
  UINTN                 NewBufferSize;

  UINT64                Offset;
  UINTN                 Remainder;

  SCT_LIST_ENTRY        ListHeader;
  SCT_LIST_ENTRY        *ListEntry = NULL;
  UINTN                 WaitIndex;
  DiskIO2_Task          *DiskIo2Entity = NULL;
  EFI_DISK_IO2_TOKEN    AsyncBatchReadToken;
  BOOLEAN               MemoryAllocFail = FALSE;
  
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

  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = SctMultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }

  //
  // Initialize batch task list header
  //
  ListHeader.ForwardLink = &(ListHeader);
  ListHeader.BackLink = &(ListHeader);

  //
  // Async Batch Read Token Init
  // To identify all read are completed
  //
  AsyncBatchReadFinished = 0;
  AsyncBatchReadToken.Event = NULL;
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) DiskIo2FinishNotifyFunc,
                   &AsyncBatchReadFinished,
                   &AsyncBatchReadToken.Event
                   );
  if (Status != EFI_SUCCESS) {
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
  
  AsyncBatchReadToken.TransactionStatus = EFI_NOT_READY;

  SctPrint (L"Create Batch Read Task List.\n\n");
  //
  // Create one Batch Read task list
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
          NewBufferSize = BufferSize + 1;
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
                         (VOID **) &DiskIo2Entity
                         );
        if (Status != EFI_SUCCESS) {
          MemoryAllocFail = TRUE;
          goto END;
        }
 
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList(&ListHeader, &DiskIo2Entity->ListEntry);
        
        DiskIo2Entity->Buffer                         = NULL;
        DiskIo2Entity->DiskIo2Token.Event             = NULL;
        DiskIo2Entity->DiskIo2Token.TransactionStatus = EFI_NOT_READY;
        DiskIo2Entity->Signature                      = DISKIO2ENTITY_SIGNATURE;
        DiskIo2Entity->BufferSize                     = NewBufferSize;
        DiskIo2Entity->Offset                         = Offset;
        DiskIo2Entity->MediaId                        = MediaId;
          
        Status=gtBS->AllocatePool (EfiBootServicesData, NewBufferSize, (VOID **) &DiskIo2Entity->Buffer);

        if (Status != EFI_SUCCESS) {
          MemoryAllocFail = TRUE;
          goto END;
        }
      }//end of loop of Offset - IndexJ
    }//end of loop of BufferSize - IndexI

    Status = DiskIo2AsyncBatchRead (
               DiskIo2,
               &ListHeader,
               &AsyncBatchReadToken
               );
    if (EFI_ERROR(Status)) {
      goto END;
    }
    
    //
    // Busy Waiting for AsyncBatchReadToken signal
    // Busy waiting 120s on all the execute entity being moved to finished queue
    //  
    SctPrint (L"Wait maximumly 120s for Async Batch Read events signaled\n\n");
    Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
    IndexI = 0;
    
    while (IndexI < 120 && AsyncBatchReadFinished == 0) {
      Status =gtBS->WaitForEvent (                   
                      1,
                      &TimerEvent,
                      &WaitIndex
                      );
      IndexI++;
      SctPrint (L".");
    }
    SctPrint (L"AsyncBatchReadFinished is %d\n", AsyncBatchReadFinished);
    Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
    SctPrint (L"\n");
  }
  
END:
  
  //
  // Verify all Async Read Task Result 
  //
  if (!SctIsListEmpty(&ListHeader) && MemoryAllocFail == FALSE) {
    for(ListEntry = SctGetFirstNode(&ListHeader); ; ListEntry = SctGetNextNode(&ListHeader, ListEntry)) {
      DiskIo2Entity = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);

      //
      // Using Disk IO Protocol to verify data buffer consistency
      //
      if (DiskIo != NULL && DiskIo2Entity->DiskIo2Token.TransactionStatus == EFI_SUCCESS) {

        Status=gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &DiskIoBuffer);

        if (Status == EFI_SUCCESS) {
          DiskIoStatus = DiskIo->ReadDisk(
                                   DiskIo,
                                   DiskIo2Entity->MediaId,
                                   DiskIo2Entity->Offset,
                                   DiskIo2Entity->BufferSize,
                                   DiskIoBuffer
                                   );
     
          DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
  
          if (DiskIoStatus == EFI_SUCCESS) {
            DiskIo2Entity->ComparedVal = SctCompareMem (
                                           DiskIo2Entity->Buffer,
                                           DiskIoBuffer,
                                           DiskIo2Entity->BufferSize
                                           );

            DiskIo2Entity->MemCompared = TRUE;   
       
            if (DiskIo2Entity->ComparedVal == 0) {
              DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
            }
          } else {
              if (DiskIo2Entity->DiskIo2Token.TransactionStatus == EFI_SUCCESS) {
                DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
            }
          }
  
          gtBS->FreePool(DiskIoBuffer);
          DiskIoBuffer = NULL;  
        }
      } else if (DiskIo2Entity->DiskIo2Token.TransactionStatus == EFI_SUCCESS){
          DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&ListHeader, ListEntry)) {
         break;
      }
    }
  }

  //
  // Do logging & clean up 
  //
  while(!SctIsListEmpty(&ListHeader)) {
    DiskIo2Entity = CR(ListHeader.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2Entity->ListEntry);

    if ( MemoryAllocFail == FALSE) {

      if (DiskIo2Entity->MemCompared == TRUE) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       DiskIo2Entity->AssertionType,
                       gDiskIo2FunctionTestAssertionGuid006,
                       L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Batch Async Read Disk with proper parameter from valid media",
                       L"%a:%d: MediaId=%d, BufferSize=0x%lx, Offset=0x%lx, BufferAddr=0x%lx, TransactionStatus=%r, Disk IO Memory CompareStatus=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       DiskIo2Entity->MediaId,
                       DiskIo2Entity->BufferSize,
                       DiskIo2Entity->Offset,
                       DiskIo2Entity->Buffer,
                       DiskIo2Entity->DiskIo2Token.TransactionStatus,
                       DiskIo2Entity->ComparedVal
                       );
      } else {
        StandardLib->RecordAssertion (
                       StandardLib,
                       DiskIo2Entity->AssertionType,
                       gDiskIo2FunctionTestAssertionGuid006,
                       L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Batch Async Read Disk with proper parameter from valid media",
                       L"%a:%d:MediaId=%d, BufferSize=0x%lx, Offset=0x%lx, BufferAddr=0x%lx, TransactionStatus=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       DiskIo2Entity->MediaId,
                       DiskIo2Entity->BufferSize,
                       DiskIo2Entity->Offset,
                       DiskIo2Entity->Buffer,
                       DiskIo2Entity->DiskIo2Token.TransactionStatus
                       );
      }
    }

    if (DiskIo2Entity->DiskIo2Token.TransactionStatus == EFI_SUCCESS){
      gtBS->CloseEvent (DiskIo2Entity->DiskIo2Token.Event);
    }

    if (DiskIo2Entity->Buffer != NULL) {
      gtBS->FreePool (DiskIo2Entity->Buffer);
    }

    if (DiskIo2Entity != NULL) {
      gtBS->FreePool(DiskIo2Entity);
    }
  }

  if (AsyncBatchReadToken.Event != NULL) {
    gtBS->CloseEvent (AsyncBatchReadToken.Event);
  } 

  return Status;
}


/**
 *   EFI_DISK_IO2_PROTOCOL.ReadDiskEx() Function Test 4. Mixed Sync & Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param DiskIo a pointer to Disk IO the interface.
 *  @param DiskIo 2 a pointer to Disk IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestReadDiskExFunctionAutoTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_DISK_IO_PROTOCOL                  *DiskIo,
  EFI_DISK_IO2_PROTOCOL                 *DiskIo2,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS        Status = EFI_SUCCESS;
  UINT32            MediaId;
  BOOLEAN           RemovableMedia;
  BOOLEAN           MediaPresent;
  BOOLEAN           LogicalPartition;
  BOOLEAN           ReadOnly;
  BOOLEAN           WriteCaching;
  UINT32            BlockSize;
  UINT32            IoAlign;
  EFI_LBA           LastBlock;
  UINTN             BufferSize;
  UINT64            LastOffset;
 
  VOID              *BufferAsync = NULL;
  
  UINTN             IndexI,IndexJ;
  UINTN             NewBufferSize;

  UINT64            Offset;
  UINTN             Remainder;

  DiskIO2_Task      *DiskIo2Entity     = NULL;
  DiskIO2_Task      *DiskIo2EntitySync = NULL;
  UINTN              WaitIndex;
  SCT_LIST_ENTRY    *ListEntry     = NULL;
  SCT_LIST_ENTRY    *ListEntrySync = NULL;

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

  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = SctMultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }
  
  //
  // Assertion Point 5.2.2.1
  // ReadDiskEx must succeed to read proper data from device with valid parameter
  //
  if ((MediaPresent == TRUE) && (LastBlock != 0)) {
   
    SctPrint (L" ============= Start to do Mixed Async & Sync ReadDiskEx call ============= \n\n");
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
          NewBufferSize = BufferSize + 1 ;
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
        // allocate aligned BufferAsync
        //
        BufferAsync = NULL;
        Status = gtBS->AllocatePool (EfiBootServicesData, NewBufferSize, (VOID **) &BufferAsync);
        if (Status != EFI_SUCCESS) {
          goto END_WAIT;
        }

        //
        // Async & Sync Call ReadDiskEx with the specified Offset and BufferSize
        //
        DiskIo2MixedReadData (
          DiskIo2,
          MediaId,
          Offset,
          NewBufferSize,
          BufferAsync
          );

       }//end of loop of Offset - IndexJ
    }//end of loop of BufferSize - IndexI

    SctPrint (L" ================ Mixed Async & Sync ReadDiskEx call finshed ================ \n\n");

END_WAIT:
  
    //
    // Busy waiting 120s on all the execute entity being moved to finished queue
    //  
    SctPrint (L"Wait maximumly 120s for all Async Read events signaled\n\n");
    Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
    IndexI = 0;
    
    SctAcquireLock (&gMixedReadQueueLock);
    while (!SctIsListEmpty(&MixedReadExecuteListHead) && IndexI < 120) {
      SctReleaseLock (&gMixedReadQueueLock);
    
      gtBS->WaitForEvent (                   
              1,
              &TimerEvent,
              &WaitIndex
              );
      IndexI++;
      SctPrint (L".");
      SctAcquireLock (&gMixedReadQueueLock);
    }
    SctReleaseLock (&gMixedReadQueueLock);

    Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
    SctPrint (L"\n");
  }
 
  //
  // clear all Disk IO2 events from gReadFinishQueue 
  // gReadFinshQueue is handled first since we use Disk IO read to do read buffer validation 
  // Here no logs should be wrote to this disk device to keep data intact
  //
  SctAcquireLock (&gMixedReadQueueLock);
  if (!SctIsListEmpty(&MixedReadFinishListHead)) {
    for(ListEntry = SctGetFirstNode(&MixedReadFinishListHead); ; ListEntry = SctGetNextNode(&MixedReadFinishListHead, ListEntry)) {
      DiskIo2Entity = CR(ListEntry, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gMixedReadQueueLock);

      //
      // Check & record every Disk IO2 execution entity status 
      //
      //
      // Using Disk IO 2 Protocol Sync Read to verify data buffer consistency
      //
      if (DiskIo2Entity->DiskIo2Token.TransactionStatus == EFI_SUCCESS) {
        DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        if (!SctIsListEmpty(&SyncReadListHead)) {
          for(ListEntrySync = SctGetFirstNode(&SyncReadListHead); ; ListEntrySync = SctGetNextNode(&SyncReadListHead, ListEntrySync)) {

            DiskIo2EntitySync = CR(ListEntrySync, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
  
            if (DiskIo2Entity->MediaId == DiskIo2EntitySync->MediaId
              && DiskIo2Entity->Offset == DiskIo2EntitySync->Offset
              && DiskIo2Entity->BufferSize == DiskIo2EntitySync->BufferSize ) {

              DiskIo2Entity->MemCompared     = TRUE;
              DiskIo2EntitySync->MemCompared = TRUE;
  
              DiskIo2EntitySync->ComparedVal = SctCompareMem (
                                                  DiskIo2Entity->Buffer,
                                                  DiskIo2EntitySync->Buffer,
                                                  DiskIo2Entity->BufferSize
                                                  );
              DiskIo2Entity->ComparedVal = DiskIo2EntitySync->ComparedVal;

   
              if (DiskIo2EntitySync->ComparedVal == 0) {
                DiskIo2Entity->AssertionType     = EFI_TEST_ASSERTION_PASSED;
                DiskIo2EntitySync->AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                DiskIo2Entity->AssertionType     = EFI_TEST_ASSERTION_FAILED;
                DiskIo2EntitySync->AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
              
            }
  
            //
            // Last list node handled
            //
            if (SctIsNodeAtEnd(&SyncReadListHead, ListEntrySync)) {
              break;
            }
          }
        }
      } else {
         DiskIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

      SctAcquireLock (&gMixedReadQueueLock);
      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&MixedReadFinishListHead, ListEntry)) {
         break;
      }
    }
  }
  SctReleaseLock (&gMixedReadQueueLock);

  
  //
  // Record All Finished Read case results
  //
  SctAcquireLock (&gMixedReadQueueLock);
  while (!SctIsListEmpty(&MixedReadFinishListHead)) {
    DiskIo2Entity = CR(MixedReadFinishListHead.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2Entity->ListEntry);
    SctReleaseLock (&gMixedReadQueueLock);

    StandardLib->RecordAssertion (
                   StandardLib,
                   DiskIo2Entity->AssertionType,
                   gDiskIo2FunctionTestAssertionGuid007,
                   L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Mixed Sync & Async Read Disk with proper parameter from valid media"    \
                   L"Async Read Call Status",
                   L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   DiskIo2Entity->MediaId,
                   DiskIo2Entity->Offset,
                   DiskIo2Entity->BufferSize,
                   DiskIo2Entity->Buffer
                   );

    
    gtBS->CloseEvent(DiskIo2Entity->DiskIo2Token.Event);
    if (DiskIo2Entity->Buffer != NULL) {
      Status = gtBS->FreePool (DiskIo2Entity->Buffer);
    }
    gtBS->FreePool(DiskIo2Entity);
  
  
    SctAcquireLock (&gMixedReadQueueLock);
  }  
  SctReleaseLock (&gMixedReadQueueLock);

  
  //
  // Record All Failed Async Read case results
  //
  while (!SctIsListEmpty(&MixedReadFailListHead)) {
    DiskIo2Entity = CR(MixedReadFailListHead.ForwardLink, DiskIO2_Task, ListEntry,DISKIO2ENTITY_SIGNATURE);
       
    SctRemoveEntryList(&DiskIo2Entity->ListEntry);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gDiskIo2FunctionTestAssertionGuid008,
                   L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Mixed Sync & Async Read Disk with proper parameter from valid media"    \
                   L"Async Read Call failed",
                   L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   DiskIo2Entity->MediaId,
                   DiskIo2Entity->Offset,
                   DiskIo2Entity->BufferSize,
                   DiskIo2Entity->Buffer
                   );
    
    gtBS->FreePool(DiskIo2Entity);
  
  }  

  //
  // Record no finished Async read list
  //
  while (!SctIsListEmpty(&MixedReadExecuteListHead)) {
    DiskIo2Entity = CR(MixedReadExecuteListHead.ForwardLink, DiskIO2_Task, ListEntry,DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2Entity->ListEntry);

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gDiskIo2FunctionTestAssertionGuid009,
                   L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Mixed Sync & Async Read Disk with proper parameter from valid media"    \
                   L"Async Read Call failed",
                   L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   DiskIo2Entity->MediaId,
                   DiskIo2Entity->Offset,
                   DiskIo2Entity->BufferSize,
                   DiskIo2Entity->Buffer
                   );
    
    //
    // We should not free the resource of node in no finished Async read list
    //
  
  }  

  //
  // Record Sync Read function test logs
  // 
  while (!SctIsListEmpty(&SyncReadListHead)) {
    DiskIo2EntitySync = CR(SyncReadListHead.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2EntitySync->ListEntry);

    if (DiskIo2EntitySync->MemCompared == TRUE) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     DiskIo2EntitySync->AssertionType,
                     gDiskIo2FunctionTestAssertionGuid010,
                     L"EFI_DISK_IO2_PROTOCOL.ReadBlocksEx - Mixed Sync & Async Read Disk with proper parameter from valid media",
                     L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx Disk IO2 Sync Memory CompareStatus=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     DiskIo2EntitySync->MediaId,
                     DiskIo2EntitySync->Offset,
                     DiskIo2EntitySync->BufferSize,
                     DiskIo2EntitySync->Buffer,
                     DiskIo2EntitySync->ComparedVal
                     );
    }

    gtBS->FreePool(DiskIo2EntitySync->Buffer);
    gtBS->FreePool(DiskIo2EntitySync);
    
  }

  
  //
  // Record Sync function failed test logs
  // 
  while (!SctIsListEmpty(&SyncReadFailListHead)) {
    DiskIo2EntitySync = CR(SyncReadFailListHead.ForwardLink, DiskIO2_Task, ListEntry, DISKIO2ENTITY_SIGNATURE);
    SctRemoveEntryList(&DiskIo2EntitySync->ListEntry);

    StandardLib->RecordAssertion (
                    StandardLib,
                    EFI_TEST_ASSERTION_FAILED,
                    gDiskIo2FunctionTestAssertionGuid011,
                    L"EFI_DISK_IO2_PROTOCOL.ReadDiskEx - Mixed Sync & Async Read Disk with proper parameter from valid media"     \
                    L"Sync Read failed",
                    L"%a:%d: MediaId=%d Offset=0x%lx BufferSize=0x%lx BufferAddr=0x%lx ",
                    __FILE__,
                    (UINTN)__LINE__,
                    DiskIo2EntitySync->MediaId,
                    DiskIo2EntitySync->Offset,
                    DiskIo2EntitySync->BufferSize,
                    DiskIo2EntitySync->Buffer
                    );

    gtBS->FreePool(DiskIo2EntitySync->Buffer);
    gtBS->FreePool(DiskIo2EntitySync);
    
  }
 
  return EFI_SUCCESS;
}
         
