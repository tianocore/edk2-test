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

  BlockIo2BBTestFunction.c

Abstract:

  Interface Function Test Cases of Block I/O 2 Protocol

--*/


#include "SctLib.h"
#include "BlockIo2BBTestMain.h"

#define BIO2ENTITY_SIGNATURE         EFI_SIGNATURE_32('b','i','o','2')


//
// record every Block IO 2 Async call status
//
typedef struct {
  UINTN                             Signature;
  EFI_BLOCK_IO2_TOKEN               BlockIo2Token;
  UINT32                            MediaId;
  EFI_LBA                           LBA;
  UINTN                             BufferSize;
  VOID                              *Buffer;
  SCT_LIST_ENTRY                    ListEntry;     
  EFI_STATUS                        StatusAsync;
  BOOLEAN                           MemCompared;
  UINTN                             ComparedVal;
  EFI_TEST_ASSERTION                AssertionType;
} BlockIO2_Task;

typedef struct {
  EFI_BLOCK_IO2_PROTOCOL            *BlockIo2;
  SCT_LIST_ENTRY                    *TaskHeader; 
  SCT_LIST_ENTRY                    *CurrentTaskEntry;
  EFI_BLOCK_IO2_TOKEN               *Token;
} BlockIO2_Batch_Task_Context;

EFI_STATUS
EFIAPI
BBTestReadBlocksExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

EFI_STATUS
EFIAPI
BBTestReadBlocksExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

EFI_STATUS
EFIAPI
BBTestReadBlocksExFunctionAutoTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

EFI_STATUS
EFIAPI
BBTestReadBlocksExFunctionAutoTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

EFI_STATUS
EFIAPI
BBTestWriteBlocksExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

EFI_STATUS
EFIAPI
BBTestWriteBlocksExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

EFI_STATUS
EFIAPI
BBTestWriteBlocksExFunctionAutoTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

EFI_STATUS
EFIAPI
BBTestWriteBlocksExFunctionAutoTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );


EFI_STATUS
EFIAPI
BBTestFushBlocksExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );


EFI_STATUS
EFIAPI
BBTestFushBlocksExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  );

#define EFI_INITIALIZE_LOCK_VARIABLE(Tpl) {Tpl,0,0}


#define ASYNC_WRITE_TEST_PATTERN            0x1C
#define SYNC_WRITE_TEST_PATTERN             0xAB

//
// Async Read Queue
//
SCT_LIST_ENTRY  ReadFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(ReadFinishListHead);
SCT_LIST_ENTRY  ReadExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(ReadExecuteListHead);
SCT_LIST_ENTRY  ReadFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(ReadFailListHead);
//
// Async Read lock
//
SCT_LOCK gReadQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);


//
// Mixed Async Read Queue
//
SCT_LIST_ENTRY  MixedReadFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedReadFinishListHead);
SCT_LIST_ENTRY  MixedReadExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedReadExecuteListHead);
SCT_LIST_ENTRY  MixedReadFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedReadFailListHead);
//
// Mixed Sync Read Queue
//
SCT_LIST_ENTRY  MixedSyncReadListHead     = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedSyncReadListHead);
SCT_LIST_ENTRY  MixedSyncReadFailListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedSyncReadFailListHead);


//
// Mixed Sync & Async Read lock
//
SCT_LOCK gMixedReadQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);


//
// Async Write Queue
//
SCT_LIST_ENTRY  WriteFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(WriteFinishListHead);
SCT_LIST_ENTRY  WriteExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(WriteExecuteListHead);
SCT_LIST_ENTRY  WriteFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(WriteFailListHead);
//
// Sync Read Data Queue for Async Write
//
SCT_LIST_ENTRY  SyncReadDataListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(SyncReadDataListHead);

//
// Async Write lock
//
SCT_LOCK gWriteQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);

//
// Mixed Async Write Queue
//
SCT_LIST_ENTRY  MixedWriteFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedWriteFinishListHead);
SCT_LIST_ENTRY  MixedWriteExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedWriteExecuteListHead);
SCT_LIST_ENTRY  MixedWriteFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedWriteFailListHead);
//
// Mixed Sync Write Queue
//
SCT_LIST_ENTRY  MixedSyncWriteListHead     = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedSyncWriteListHead);
SCT_LIST_ENTRY  MixedSyncWriteFailListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(MixedSyncWriteFailListHead);

//
// Mixed Sync & Async Write lock
//
SCT_LOCK gMixedWriteQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);

//
// Async signal
//
UINTN       AsyncReadFinished  = 0;
UINTN       AsyncWriteFinished = 0;
UINTN       AsyncFlushFinished[4] = {0, 0, 0, 0};


VOID
EFIAPI BlockIo2ReadNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  BlockIO2_Task *BlockIo2Entity;
  
  BlockIo2Entity = (BlockIO2_Task *)Context;

  //
  // Remove entity from ReadExecuteListHead &  add entity to ReadFinishListHead
  // All BlockIo2 Notify function run at Call Back level only once, So no locks required
  //
  SctRemoveEntryList (&BlockIo2Entity->ListEntry);
  SctInsertTailList (&ReadFinishListHead, &BlockIo2Entity->ListEntry);
}


/**
 *   Provide EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx() function abstraction interface
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @param MediaId Read media ID.
 *  @param LBA Read Logic Block Address.
 *  @param BufferSize write databuffer size.
 *  @param Buffer a pointer to read data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

STATIC
EFI_STATUS
BlockIo2AsyncReadData (
  IN EFI_BLOCK_IO2_PROTOCOL            *BlockIo2,
  IN UINT32                            MediaId,
  IN EFI_LBA                           LBA,
  IN UINTN                             BufferSize,
  OUT VOID                             *Buffer
)
{
  
  EFI_STATUS                         Status;
  BlockIO2_Task                      *BlockIo2Entity = NULL;

  ASSERT(BlockIo2 != NULL);
  
  //
  // Allocate memory for one BlockIo2Entity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(BlockIO2_Task), 
                   (VOID **) &BlockIo2Entity);
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  //
  // BlockIo2Token initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) BlockIo2ReadNotifyFunc,
                   BlockIo2Entity,
                   &BlockIo2Entity->BlockIo2Token.Event
                   );
  if (Status != EFI_SUCCESS) {
    gtBS->FreePool(BlockIo2Entity);
    return Status;
  }
  
  BlockIo2Entity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;

  //
  // Acquire lock to add entity to Execution ListHead
  //
  SctAcquireLock (&gReadQueueLock);
  SctInsertTailList (&ReadExecuteListHead, &BlockIo2Entity->ListEntry);
  SctReleaseLock (&gReadQueueLock);
  
  BlockIo2Entity->Buffer = Buffer;
  //
  // Async ReadBlockEx Call
  //
  Status = BlockIo2->ReadBlocksEx (
                       BlockIo2,
                       MediaId,
                       LBA,
                       &BlockIo2Entity->BlockIo2Token,
                       BufferSize,
                       Buffer
                       );
  
  if (EFI_ERROR (Status)) {
    gtBS->CloseEvent(BlockIo2Entity->BlockIo2Token.Event);
    //
    // Failed Status Event should never be signaled, so remove this entity from the list
    //
    SctAcquireLock (&gReadQueueLock);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
    SctReleaseLock (&gReadQueueLock);
    
    // 
    // Put failure execution into fail List
    //
    SctInsertTailList (&ReadFailListHead, &BlockIo2Entity->ListEntry);
    BlockIo2Entity->Buffer = NULL;
  }

  //
  // Record execution Info to Block IO 2 entity 
  //
  BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
  BlockIo2Entity->MediaId = MediaId;
  BlockIo2Entity->LBA = LBA;
  BlockIo2Entity->BufferSize = BufferSize;
  BlockIo2Entity->StatusAsync = Status;
  //
  // memory uncompared with BlockIO interface
  //
  BlockIo2Entity->MemCompared = FALSE;               
  
  return Status;
}


VOID
EFIAPI BlockIo2MixedReadNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  BlockIO2_Task *BlockIo2Entity;
  
  BlockIo2Entity = (BlockIO2_Task *)Context;

  //
  // Remove entity from MixedReadFinishListHead &  add entity to MixedReadFinishListHead
  // All BlockIo2 Notify function run at Call Back level only once, So no locks required
  //
  SctRemoveEntryList (&BlockIo2Entity->ListEntry);
  SctInsertTailList (&MixedReadFinishListHead, &BlockIo2Entity->ListEntry);
}


/**
 *   Provide EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx() function abstraction interface
 *  Mix Block Io2 ReadBlocksEx Async Read & Sync Read
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @param MediaId Read media ID.
 *  @param LBA Read Logic Block Address.
 *  @param BufferSize write databuffer size.
 *  @param Buffer a pointer to read data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

STATIC
EFI_STATUS
BlockIo2MixedSyncAsyncReadData (
  IN EFI_BLOCK_IO2_PROTOCOL            *BlockIo2,
  IN UINT32                            MediaId,
  IN EFI_LBA                           LBA,
  IN UINTN                             BufferSize,
  IN UINT32                            IoAlign,
  OUT VOID                             *Buffer
)
{
  
  EFI_STATUS                         Status;
  BlockIO2_Task                      *BlockIo2Entity = NULL;
  UINT8                              *BufferSync = NULL;

  ASSERT(BlockIo2 != NULL);
  
  //
  // Allocate memory for one BlockIo2Entity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(BlockIO2_Task), 
                   (VOID **) &BlockIo2Entity);
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  //
  // BlockIo2Token initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) BlockIo2MixedReadNotifyFunc,
                   BlockIo2Entity,
                   &BlockIo2Entity->BlockIo2Token.Event
                   );
  if (Status != EFI_SUCCESS) {
    gtBS->FreePool(BlockIo2Entity);
    FreeAlignedPool(Buffer);
    return Status;
  }
  
  BlockIo2Entity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;

  //
  // Acquire lock to add entity to Execution ListHead
  //
  SctAcquireLock (&gMixedReadQueueLock);
  SctInsertTailList (&MixedReadExecuteListHead, &BlockIo2Entity->ListEntry);
  SctReleaseLock (&gMixedReadQueueLock);
  
  //
  // Async ReadBlockEx Call
  //
  Status = BlockIo2->ReadBlocksEx (
                       BlockIo2,
                       MediaId,
                       LBA,
                       &BlockIo2Entity->BlockIo2Token,
                       BufferSize,
                       Buffer
                       );
  
  if (EFI_ERROR (Status)) {
    gtBS->CloseEvent(BlockIo2Entity->BlockIo2Token.Event);
    //
    // Failed Status Event should never be signaled, so remove this entity from the list
    //
    SctAcquireLock (&gMixedReadQueueLock);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
    SctReleaseLock (&gMixedReadQueueLock);
    
    // 
    // Put failure execution into fail List
    //
    SctInsertTailList (&MixedReadFailListHead, &BlockIo2Entity->ListEntry);
  }

  //
  // Record execution Info to Block IO 2 entity 
  //
  BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
  BlockIo2Entity->MediaId = MediaId;
  BlockIo2Entity->LBA = LBA;
  BlockIo2Entity->BufferSize = BufferSize;
  BlockIo2Entity->Buffer = Buffer;
  BlockIo2Entity->StatusAsync = Status;
  //
  // memory uncompared with BlockIO interface
  //
  BlockIo2Entity->MemCompared = FALSE;               

  //
  // Sync Call comes after a successful Async Read 
  //
  if (!EFI_ERROR (Status)) {
    BufferSync = AllocateAlignedPool(
                   EfiBootServicesData, 
                   BufferSize, 
                   IoAlign
                   );
    if (BufferSync == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
  
    //
    // Allocate memory for one BlockIo2Entity
    //
    Status = gtBS->AllocatePool(
                     EfiBootServicesData, 
                     sizeof(BlockIO2_Task), 
                     (VOID **) &BlockIo2Entity);
    if (Status != EFI_SUCCESS) {
      FreeAlignedPool(BufferSync);
      return Status;
    }

    //
    // Record  Sync execution Info to Block IO 2 entity 
    //
    BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
    BlockIo2Entity->MediaId = MediaId;
    BlockIo2Entity->LBA = LBA;
    BlockIo2Entity->BufferSize = BufferSize;
    BlockIo2Entity->Buffer = BufferSync;
    BlockIo2Entity->BlockIo2Token.Event = NULL;
    //
    // memory uncompared with BlockIO 2 Async interface
    //
    BlockIo2Entity->MemCompared = FALSE;
    BlockIo2Entity->ComparedVal = 1;

    Status = BlockIo2->ReadBlocksEx (
                         BlockIo2,
                         BlockIo2Entity->MediaId,
                         BlockIo2Entity->LBA,
                         &BlockIo2Entity->BlockIo2Token,
                         BlockIo2Entity->BufferSize,
                         BlockIo2Entity->Buffer
                         );
    if (!EFI_ERROR(Status)) {
      // 
      // Put success execution into Sync read List
      //
      SctInsertTailList (&MixedSyncReadListHead, &BlockIo2Entity->ListEntry);
    } else {
      // 
      // Put failure execution into fail List
      //
      SctInsertTailList (&MixedSyncReadFailListHead, &BlockIo2Entity->ListEntry);
    }
         
  }
  
  return Status;
}

VOID
EFIAPI BlockIo2WriteNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  BlockIO2_Task *BlockIo2Entity;
  
  BlockIo2Entity = (BlockIO2_Task *)Context;

  //
  // Remove entity from WriteExecuteListHead &  add entity to WriteFinishListHead
  // All BlockIo2 Notify function run at Call Back level only once, So no locks required
  //
  SctRemoveEntryList (&BlockIo2Entity->ListEntry);
  SctInsertTailList (&WriteFinishListHead, &BlockIo2Entity->ListEntry);
}


VOID
EFIAPI BlockIo2FinishNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  UINTN * flag = (UINTN *)Context;
  *flag = 1;
}


/**
 *   Provide EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx() function abstraction interface
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @param MediaId Write media ID.
 *  @param LBA Write Logic Block Address.
 *  @param BufferSize write databuffer size.
 *  @param Buffer a pointer to write data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

STATIC
EFI_STATUS
BlockIo2AsyncWriteData (
  IN EFI_BLOCK_IO2_PROTOCOL            *BlockIo2,
  IN UINT32                            MediaId,
  IN EFI_LBA                           LBA,
  IN UINTN                             BufferSize,
  OUT VOID                             *Buffer
)
{
  
  EFI_STATUS                         Status;
  BlockIO2_Task                      *BlockIo2Entity = NULL;

  ASSERT(BlockIo2 != NULL);
  
  //
  // Allocate memory for one BlockIo2Entity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(BlockIO2_Task), 
                   (VOID **) &BlockIo2Entity
                   );
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  //
  // BlockIo2Token initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) BlockIo2WriteNotifyFunc,
                   BlockIo2Entity,
                   &BlockIo2Entity->BlockIo2Token.Event
                   );
  if (Status != EFI_SUCCESS) {
    gtBS->FreePool(BlockIo2Entity);
    return Status;
  }
  
  BlockIo2Entity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;

  //
  // Acquire lock to add entity to Write Execution ListHead
  //
  SctAcquireLock (&gWriteQueueLock);
  SctInsertTailList (&WriteExecuteListHead, &BlockIo2Entity->ListEntry);
  SctReleaseLock (&gWriteQueueLock);
  
  BlockIo2Entity->Buffer = Buffer;
  //
  // Async WriteBlockEx Call
  //
  Status = BlockIo2->WriteBlocksEx (
                       BlockIo2,
                       MediaId,
                       LBA,
                       &BlockIo2Entity->BlockIo2Token,
                       BufferSize,
                       Buffer
                       );
  
  if (EFI_ERROR (Status)) {
    gtBS->CloseEvent(BlockIo2Entity->BlockIo2Token.Event);
    //
    // Failed Status Event should never be signaled, so remove this entity from the list
    //
    SctAcquireLock (&gWriteQueueLock);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
    SctReleaseLock (&gWriteQueueLock);
    
    // 
    // Put failure execution into fail List
    //
    SctInsertTailList (&WriteFailListHead, &BlockIo2Entity->ListEntry);
    
    BlockIo2Entity->Buffer = NULL;
    
  }

  //
  // Record execution Info to Block IO 2 entity 
  //
  BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
  BlockIo2Entity->MediaId = MediaId;
  BlockIo2Entity->LBA = LBA;
  BlockIo2Entity->BufferSize = BufferSize;
  BlockIo2Entity->StatusAsync = Status;
  BlockIo2Entity->MemCompared = FALSE;      

  return Status;
}


VOID
EFIAPI BlockIo2MixedWriteNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  BlockIO2_Task *BlockIo2Entity;
  
  BlockIo2Entity = (BlockIO2_Task *)Context;

  //
  // Remove entity from MixedWriteExecuteListHead &  add entity to WriteFinishListHead
  // All BlockIo2 Notify function run at Call Back level only once, So no locks required
  //
  SctRemoveEntryList (&BlockIo2Entity->ListEntry);
  SctInsertTailList (&MixedWriteFinishListHead, &BlockIo2Entity->ListEntry);
}


/**
 *   Provide EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx() function abstraction interface
 *  Mix Block Io2 WriteBlocksEx Async Read & Sync Read
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @param MediaId Write media ID.
 *  @param LBA Write Logic Block Address.
 *  @param BufferSize write databuffer size.
 *  @param Buffer a pointer to write data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

STATIC
EFI_STATUS
BlockIo2MixedSyncAsyncWriteData (
  IN EFI_BLOCK_IO2_PROTOCOL            *BlockIo2,
  IN UINT32                            MediaId,
  IN EFI_LBA                           LBA,
  IN UINTN                             BufferSize,
  IN UINT32                            IoAlign,
  OUT VOID                             *Buffer
)
{
  
  EFI_STATUS                         Status;
  BlockIO2_Task                      *BlockIo2Entity = NULL;
  UINT8                              *BufferSync = NULL;

  ASSERT(BlockIo2 != NULL);
  
  //
  // Allocate memory for one BlockIo2Entity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(BlockIO2_Task), 
                   (VOID **) &BlockIo2Entity
                   );
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  //
  // BlockIo2Token initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) BlockIo2MixedWriteNotifyFunc,
                   BlockIo2Entity,
                   &BlockIo2Entity->BlockIo2Token.Event
                   );
  if (Status != EFI_SUCCESS) {
    gtBS->FreePool(BlockIo2Entity);
    FreeAlignedPool(Buffer);
    return Status;
  }
  
  BlockIo2Entity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;

  //
  // Acquire lock to add entity to MixedWrite Execution ListHead
  //
  SctAcquireLock (&gMixedWriteQueueLock);
  SctInsertTailList (&MixedWriteExecuteListHead, &BlockIo2Entity->ListEntry);
  SctReleaseLock (&gMixedWriteQueueLock);
  
  //
  // Async WriteBlockEx Call
  //
  Status = BlockIo2->WriteBlocksEx (
                       BlockIo2,
                       MediaId,
                       LBA,
                       &BlockIo2Entity->BlockIo2Token,
                       BufferSize,
                       Buffer
                       );
  
  if (EFI_ERROR (Status)) {
    gtBS->CloseEvent(BlockIo2Entity->BlockIo2Token.Event);
    //
    // Failed Status Event should never be signaled, so remove this entity from the list
    //
    SctAcquireLock (&gMixedWriteQueueLock);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
    SctReleaseLock (&gMixedWriteQueueLock);
    
    // 
    // Put failure execution into fail List
    //
    SctInsertTailList (&MixedWriteFailListHead, &BlockIo2Entity->ListEntry);
  }

  //
  // Record execution Info to Block IO 2 entity 
  //
  BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
  BlockIo2Entity->MediaId = MediaId;
  BlockIo2Entity->LBA = LBA;
  BlockIo2Entity->BufferSize = BufferSize;
  BlockIo2Entity->Buffer = Buffer;
  BlockIo2Entity->StatusAsync = Status;
  BlockIo2Entity->MemCompared = FALSE;       

  //
  // Sync Call comes after a successful Async Write 
  //
  if (!EFI_ERROR (Status)) {
    BufferSync = AllocateAlignedPool(
                   EfiBootServicesData, 
                   BufferSize, 
                   IoAlign
                   );
    if (BufferSync == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    
    //
    // Allocate memory for one BlockIo2Entity
    //
    Status = gtBS->AllocatePool(
                     EfiBootServicesData, 
                     sizeof(BlockIO2_Task), 
                     (VOID **) &BlockIo2Entity);
    if (Status != EFI_SUCCESS) {
      FreeAlignedPool(BufferSync);
      return Status;
    }
    SctSetMem (BufferSync, BufferSize, SYNC_WRITE_TEST_PATTERN);

    //
    // Record  Sync execution Info to Block IO 2 entity 
    //
    BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
    BlockIo2Entity->MediaId = MediaId;
    BlockIo2Entity->LBA = LBA;
    BlockIo2Entity->BufferSize = BufferSize;
    BlockIo2Entity->Buffer = BufferSync;
    BlockIo2Entity->BlockIo2Token.Event = NULL;
    //
    // memory uncompared with BlockIO 2 Async interface
    //
    BlockIo2Entity->MemCompared = FALSE;
    BlockIo2Entity->ComparedVal = 1;

    Status = BlockIo2->WriteBlocksEx (
                         BlockIo2,
                         BlockIo2Entity->MediaId,
                         BlockIo2Entity->LBA,
                         &BlockIo2Entity->BlockIo2Token,
                         BlockIo2Entity->BufferSize,
                         BlockIo2Entity->Buffer
                         );
    if (!EFI_ERROR(Status)) {
      // 
      // Put success execution into Sync Write List
      //
      SctInsertTailList (&MixedSyncWriteListHead, &BlockIo2Entity->ListEntry);
    } else {
      // 
      // Put failure execution into fail List
      //
      SctInsertTailList (&MixedSyncWriteFailListHead, &BlockIo2Entity->ListEntry);
    }
         
  }
  

  return Status;
}


VOID
EFIAPI BlockIo2ReadBatchNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  
  BlockIO2_Batch_Task_Context         *TaskContext;
  BlockIO2_Task                       *BlockIo2Entity = NULL;
  SCT_LIST_ENTRY                      *CurrentTaskEntry = NULL;
  EFI_BLOCK_IO2_PROTOCOL              *BlockIo2 = NULL;
  EFI_STATUS                          Status;

  
  TaskContext = (BlockIO2_Batch_Task_Context *) Context;
  CurrentTaskEntry = TaskContext->CurrentTaskEntry;
  BlockIo2 = TaskContext->BlockIo2;

  if (!SctIsNodeAtEnd(TaskContext->TaskHeader, CurrentTaskEntry) ){
    BlockIo2Entity = CR(CurrentTaskEntry->ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);

    BlockIo2Entity->BlockIo2Token.Event = NULL;
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) BlockIo2ReadBatchNotifyFunc,
                     TaskContext,
                     &BlockIo2Entity->BlockIo2Token.Event
                     );
    if (Status != EFI_SUCCESS) {
      goto END;
    }
    //
    // Current Task Entry move forward
    //
    TaskContext->CurrentTaskEntry = CurrentTaskEntry->ForwardLink;

    Status = BlockIo2->ReadBlocksEx (
                         BlockIo2,
                         BlockIo2Entity->MediaId,
                         BlockIo2Entity->LBA,
                         &BlockIo2Entity->BlockIo2Token,
                         BlockIo2Entity->BufferSize,
                         BlockIo2Entity->Buffer
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
    BlockIo2Entity = CR(CurrentTaskEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    if (BlockIo2Entity->BlockIo2Token.Event != NULL) {
      gtBS->CloseEvent (BlockIo2Entity->BlockIo2Token.Event);
    }

    gtBS->FreePool (TaskContext);

    return;
  }

END:
  //
  // Close current Event
  //
  BlockIo2Entity = CR(CurrentTaskEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
  if (BlockIo2Entity->BlockIo2Token.Event != NULL) {
    gtBS->CloseEvent (BlockIo2Entity->BlockIo2Token.Event);
  }
  
  return;
}


/**
 *   Provide Batch task for EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx() function 
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @param TaskList point to batch task list.
 *  @param Token task list token.
 *  @return EFI_SUCCESS Finish the test successfully.
 */


STATIC
EFI_STATUS
BlockIo2AsyncBatchRead (
  IN EFI_BLOCK_IO2_PROTOCOL          *BlockIo2,
  IN SCT_LIST_ENTRY                  *ListHeader,
  IN OUT EFI_BLOCK_IO2_TOKEN	     *Token
)
{
  BlockIO2_Batch_Task_Context        *TaskContext = NULL;
  BlockIO2_Task                      *BlockIo2Entity = NULL;
  EFI_STATUS                         Status = EFI_SUCCESS;
  
  ASSERT(Token != NULL && Token->Event != NULL);
  
  if (!SctIsListEmpty (ListHeader)) {  
    //
    // Task Context will be freed in BlockIo2ReadBatchNotifyFunc when all task finished
    //
    Status = gtBS->AllocatePool (
                     EfiBootServicesData, 
                     sizeof(BlockIO2_Batch_Task_Context), 
                     (VOID **) &TaskContext
                     );
    if (TaskContext == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    // 
    // Init BatchTask structure
    // 
    TaskContext->TaskHeader = ListHeader;
    TaskContext->CurrentTaskEntry = ListHeader->ForwardLink;
    TaskContext->Token = Token;
    TaskContext->BlockIo2 = BlockIo2;

    BlockIo2Entity = CR(ListHeader->ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
 
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) BlockIo2ReadBatchNotifyFunc,
                     TaskContext,
                     &BlockIo2Entity->BlockIo2Token.Event
                     );
    if (Status != EFI_SUCCESS) {
      return Status;
    }
    
    Status = BlockIo2->ReadBlocksEx (
                         BlockIo2,
                         BlockIo2Entity->MediaId,
                         BlockIo2Entity->LBA,
                         &BlockIo2Entity->BlockIo2Token,
                         BlockIo2Entity->BufferSize,
                         BlockIo2Entity->Buffer
                         );
  }

  return Status;
}


VOID
EFIAPI BlockIo2WriteBatchNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  
  BlockIO2_Batch_Task_Context         *TaskContext;
  BlockIO2_Task                       *BlockIo2Entity = NULL;
  SCT_LIST_ENTRY                      *CurrentTaskEntry = NULL;
  EFI_BLOCK_IO2_PROTOCOL              *BlockIo2 = NULL;
  EFI_STATUS                          Status;

  
  TaskContext = (BlockIO2_Batch_Task_Context *) Context;
  CurrentTaskEntry = TaskContext->CurrentTaskEntry;
  BlockIo2 = TaskContext->BlockIo2;

  if (!SctIsNodeAtEnd(TaskContext->TaskHeader, CurrentTaskEntry) ){

    BlockIo2Entity = CR(CurrentTaskEntry->ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);

    BlockIo2Entity->BlockIo2Token.Event = NULL;
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) BlockIo2WriteBatchNotifyFunc,
                     TaskContext,
                     &BlockIo2Entity->BlockIo2Token.Event
                     );
    if (Status != EFI_SUCCESS) {
      goto END;
    }
    //
    // Current Task Entry move forward
    //
    TaskContext->CurrentTaskEntry = CurrentTaskEntry->ForwardLink;

    Status = BlockIo2->WriteBlocksEx (
                         BlockIo2,
                         BlockIo2Entity->MediaId,
                         BlockIo2Entity->LBA,
                         &BlockIo2Entity->BlockIo2Token,
                         BlockIo2Entity->BufferSize,
                         BlockIo2Entity->Buffer
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
    BlockIo2Entity = CR(CurrentTaskEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    if (BlockIo2Entity->BlockIo2Token.Event != NULL) {
      gtBS->CloseEvent (BlockIo2Entity->BlockIo2Token.Event);
    }

    gtBS->FreePool (TaskContext);
    
    return;
  }

END:
  //
  // Close current Event
  //
  BlockIo2Entity = CR(CurrentTaskEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
  if (BlockIo2Entity->BlockIo2Token.Event != NULL) {
    gtBS->CloseEvent (BlockIo2Entity->BlockIo2Token.Event);
  }
  
  return;
}



/**
 *   Provide Batch task for EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx() function 
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @param TaskList point to batch task list.
 *  @param Token task list token.
 *  @return EFI_SUCCESS Finish the test successfully.
 */


STATIC
EFI_STATUS
BlockIo2AsyncBatchWrite (
  IN EFI_BLOCK_IO2_PROTOCOL          *BlockIo2,
  IN SCT_LIST_ENTRY                  *ListHeader,
  IN OUT EFI_BLOCK_IO2_TOKEN	     *Token
)
{
  BlockIO2_Batch_Task_Context        *TaskContext = NULL;
  BlockIO2_Task                      *BlockIo2Entity = NULL;
  EFI_STATUS                         Status = EFI_SUCCESS;
  
  ASSERT(Token != NULL && Token->Event != NULL);
  
  if (!SctIsListEmpty (ListHeader)) {
    //
    // Task Context will be freed in BlockIo2WriteBatchNotifyFunc when all task finished
    //
    Status = gtBS->AllocatePool (
                     EfiBootServicesData, 
                     sizeof(BlockIO2_Batch_Task_Context), 
                     (VOID **) &TaskContext
                     );
    if (TaskContext == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    // 
    // Init BatchTask structure
    // 
    TaskContext->TaskHeader = ListHeader;
    TaskContext->CurrentTaskEntry = ListHeader->ForwardLink;
    TaskContext->Token = Token;
    TaskContext->BlockIo2 = BlockIo2;

    BlockIo2Entity = CR(ListHeader->ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
 
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) BlockIo2WriteBatchNotifyFunc,
                     TaskContext,
                     &BlockIo2Entity->BlockIo2Token.Event
                     );
    if (Status != EFI_SUCCESS) {
      return Status;
    }
    
    Status = BlockIo2->WriteBlocksEx (
                         BlockIo2,
                         BlockIo2Entity->MediaId,
                         BlockIo2Entity->LBA,
                         &BlockIo2Entity->BlockIo2Token,
                         BlockIo2Entity->BufferSize,
                         BlockIo2Entity->Buffer
                         );
  }

  return Status;
}



/**
 *  Entrypoint for EFI_BLOCK_IO2_PROTOCOL.Reset() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS or EFI_DEVICE_ERROR Finish the test successfully.
 */


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
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2;
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

  BlockIo2 = (EFI_BLOCK_IO2_PROTOCOL *)ClientInterface;

  //
  // Assertion Point
  // Reset block device hardware with extended verification
  //
  Status = BlockIo2->Reset (BlockIo2, TRUE);
  if (Status != EFI_DEVICE_ERROR && Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  //
  // Sometimes the file system will be destroied from this point. Just add a
  // stall to avoid it. (Need investigation, I don't know it is useful or not!)
  //
  SctPrint (L"Wait 5 seconds for the block IO 2 device resetting...");
  gtBS->Stall (5000000);

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBlockIo2FunctionTestAssertionGuid017,
                 L"EFI_BLOCK_IO2_PROTOCOL.Reset - Reset the block IO 2 device with extended verification",
                 L"%a:%d:Status=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Assertion Point 5.1.2.2
  // Reset the block device hardware without extended verification
  //
  Status = BlockIo2->Reset (BlockIo2, FALSE);
  if (Status != EFI_DEVICE_ERROR && Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  //
  // Sometimes the file system will be destroied from this point. Just add a
  // stall to avoid it. (Need investigation, I don't know it is useful or not!)
  //
  SctPrint (L"Wait 5 seconds for the block IO 2 device resetting...");
  gtBS->Stall (5000000);

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBlockIo2FunctionTestAssertionGuid018,
                 L"EFI_BLOCK_IO2_PROTOCOL.Reset - Reset the block IO 2 device without extended verification",
                 L"%a:%d:Status=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx() Function Test.
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
BBTestReadBlocksExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                           Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib = NULL;
  EFI_BLOCK_IO_PROTOCOL                *BlockIo = NULL;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2 = NULL;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2Temp = NULL;
  EFI_DEVICE_PATH_PROTOCOL	           *DevicePath = NULL;
  CHAR16                               *DevicePathStr = NULL;
  UINTN                                Index;
  UINTN                                NoHandles;
  EFI_HANDLE                           *HandleBuffer = NULL;

  
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
  // Locate Block IO protocol on same handler for test
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiBlockIo2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  for (Index = 0; Index < NoHandles; Index++) {
     Status = gtBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gBlackBoxEfiBlockIo2ProtocolGuid,
                      (VOID **) &BlockIo2Temp
                      );
     if (Status == EFI_SUCCESS && BlockIo2Temp == BlockIo2) {
       Status = gtBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gBlackBoxEfiBlockIoProtocolGuid,
                        (VOID **) &BlockIo
                        );
       if (Status != EFI_SUCCESS) {
         BlockIo = NULL;
       }
       break;
    }
 
  }

  if (HandleBuffer != NULL) {
     gtBS->FreePool (HandleBuffer);
  }
  //
  // Async call 1 to test Block IO 2 ReadBlocksEx
  // Using Link list to manage token pool
  //
  BBTestReadBlocksExFunctionAutoTestCheckpoint1 (StandardLib, BlockIo, BlockIo2);
   
  //
  // Sync call to test Block IO 2 ReadBlocksEx
  //
  BBTestReadBlocksExFunctionAutoTestCheckpoint2 (StandardLib, BlockIo, BlockIo2);
  
  //
  // Async call 2 to test Block IO 2 ReadBlocksEx
  // Using Cascade Event Chain to manage token pool
  //
  BBTestReadBlocksExFunctionAutoTestCheckpoint3 (StandardLib, BlockIo, BlockIo2);

  //
  // Mixed Sync & Async Call to test Block IO 2 ReadBlocksEx
  //
  BBTestReadBlocksExFunctionAutoTestCheckpoint4 (StandardLib, BlockIo, BlockIo2);
  return Status;
}


/**
 *   EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx() Function Test 1. Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param BlockIo a pointer to Block IO the interface.
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestReadBlocksExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS                           Status = EFI_SUCCESS;
  EFI_STATUS                           StatusAsync = EFI_SUCCESS;
  EFI_STATUS                           StatusSync;
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
  UINT8                                *BufferAsync = NULL;
  UINT8                                *BufferSync = NULL;
  UINT32                               BlockNumber;
  UINTN                                IndexI;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  BlockIO2_Task                        *BlockIo2Entity = NULL;
  UINTN                                WaitIndex;
  SCT_LIST_ENTRY                       *ListEntry = NULL;
  
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

  BlockNumber       = (UINT32) MINIMUM(LastBlock, MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER);
  BufferSize        = BlockNumber * BlockSize;

  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }
  
  //
  // Assertion Point 5.2.2.1
  // ReadBlocksEx must succeed to read proper data from device with valid parameter
  //
  if (MediaPresent == TRUE) {
   
    SctPrint (L" ================ Start to do Async ReadBlocksEx call ================ \n\n");
 
    for (IndexI = BlockNumber; IndexI > 0; IndexI >>= 6) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER*BlockSize
      //
     
      NewBufferSize = IndexI * BlockSize;

      for (NewLba = LastBlock + 1 - BlockNumber; NewLba > 0; NewLba = SctRShiftU64(NewLba, 8)) {
        //
        // allocate aligned BufferSync
        //
        BufferAsync = NULL;
        BufferAsync = AllocateAlignedPool(
                        EfiBootServicesData, 
                        NewBufferSize, 
                        IoAlign
                        );
        if (BufferAsync == NULL) {
          goto END_WAIT;
        }

        //
        // Async Call ReadBlocksEx with the specified LBA and BufferSize
        //
        StatusAsync = BlockIo2AsyncReadData (
                        BlockIo2,
                        MediaId,
                        NewLba,
                        NewBufferSize,
                        BufferAsync
                        );

        if (EFI_ERROR(StatusAsync)) {
          FreeAlignedPool(BufferAsync);
        }
        
      }//end of loop of Lba - LBA
    }//end of loop of BufferSize - IndexI

    SctPrint (L" ================== Async ReadBlocksEx call finshed ================== \n\n");


END_WAIT:
    //
    // Busy waiting 120s on all the execute entity being moved to finished queue
    //  
    SctPrint (L"Wait maximumly 120s for all Async Read events signaled\n\n");
    Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
    IndexI = 0;
    
    SctAcquireLock (&gReadQueueLock);
    while (!SctIsListEmpty (&ReadExecuteListHead) && IndexI < 120) {
      SctReleaseLock (&gReadQueueLock);
    
      gtBS->WaitForEvent (                   
              1,
              &TimerEvent,
              &WaitIndex
              );
      IndexI++;
      SctPrint (L".");
      SctAcquireLock (&gReadQueueLock);
    }
    SctReleaseLock (&gReadQueueLock);

    Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
    SctPrint(L"\n");
  }
 


  //
  // clear all Block IO2 events from gReadFinishQueue 
  // gReadFinshQueue is handled first since we use BLock IO read to do read buffer validation 
  // Here no logs should be wrote to this block device to keep data intact
  //
  SctAcquireLock (&gReadQueueLock);
  if (!SctIsListEmpty (&ReadFinishListHead)) {
    for(ListEntry = SctGetFirstNode(&ReadFinishListHead); ; ListEntry = SctGetNextNode(&ReadFinishListHead, ListEntry)) {
      BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gReadQueueLock);

      //
      // Check & record every Block IO2 execution entity status 
      //
      //
      // Using Block IO Protocol to verify data buffer consistency
      //
      if (BlockIo != NULL && BlockIo2Entity->BlockIo2Token.TransactionStatus == EFI_SUCCESS) {
        BufferSync = AllocateAlignedPool(
                       EfiBootServicesData, 
                       BlockIo2Entity->BufferSize, 
                       IoAlign
                       );
        if (BufferSync != NULL) {
          StatusSync = BlockIo->ReadBlocks(
                                  BlockIo,
                                  BlockIo2Entity->MediaId,
                                  BlockIo2Entity->LBA,
                                  BlockIo2Entity->BufferSize,
                                  BufferSync
                                  );
     
          BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          if (StatusSync == EFI_SUCCESS) {
            BlockIo2Entity->ComparedVal = SctCompareMem (
                                            BlockIo2Entity->Buffer,
                                            BufferSync,
                                            BlockIo2Entity->BufferSize
                                            );
            //
            // Block IO Memory compare job done
            //
            BlockIo2Entity->MemCompared = TRUE;   
       
            if (BlockIo2Entity->ComparedVal == 0) {
              BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
            }
          }
     
          FreeAlignedPool(BufferSync);
          BufferSync = NULL;
        }
      } else if (BlockIo2Entity->BlockIo2Token.TransactionStatus == EFI_SUCCESS){
        BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      SctAcquireLock (&gReadQueueLock);
      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&ReadFinishListHead, ListEntry)) {
         break;
      }
    }
  }
 
  //
  // Record All Finished Read case results
  //
  while (!SctIsListEmpty (&ReadFinishListHead)) {
    BlockIo2Entity = CR(ReadFinishListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
       
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
    SctReleaseLock (&gReadQueueLock);
    
    
    if (BlockIo2Entity->MemCompared == TRUE) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     BlockIo2Entity->AssertionType,
                     gBlockIo2FunctionTestAssertionGuid001,
                     L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Async Read Block with proper parameter from valid media",
                     L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx Block IO Memory CompareStatus=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BlockIo2Entity->MediaId,
                     BlockIo2Entity->LBA,
                     BlockIo2Entity->BufferSize,
                     BlockIo2Entity->Buffer,
                     BlockIo2Entity->ComparedVal
                     );
    } else {
      StandardLib->RecordAssertion (
                     StandardLib,
                     BlockIo2Entity->AssertionType,
                     gBlockIo2FunctionTestAssertionGuid001,
                     L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Async Read Block with proper parameter from valid media",
                     L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                     __FILE__,
                     (UINTN)__LINE__,
                     BlockIo2Entity->MediaId,
                     BlockIo2Entity->LBA,
                     BlockIo2Entity->BufferSize,
                     BlockIo2Entity->Buffer
                     );
    }
    
    gtBS->CloseEvent(BlockIo2Entity->BlockIo2Token.Event);
    //
    // Free aligned Buffer
    //
    if (BlockIo2Entity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    }
    gtBS->FreePool(BlockIo2Entity);


    SctAcquireLock (&gReadQueueLock);
  }  
  SctReleaseLock (&gReadQueueLock);

  //
  // If ReadFailListHead is not empty, which means some Async Calls are wrong 
  // 
  while(!SctIsListEmpty (&ReadFailListHead)) {
    BlockIo2Entity = CR(ReadFailListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gBlockIo2FunctionTestAssertionGuid002,
                   L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Async Read Block with proper parameter from valid media "    \
                   L"Read Failed ",
                   L"%a:%d:BufferSize=%d, LBA=0x%lx, StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BlockIo2Entity->BufferSize,
                   BlockIo2Entity->LBA,
                   BlockIo2Entity->StatusAsync
                   );
     //
     // Free aligned Buffer
     //
     if (BlockIo2Entity->Buffer != NULL) {
       Status = FreeAlignedPool (BlockIo2Entity->Buffer);
     
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
       }
     }
 
     gtBS->FreePool(BlockIo2Entity);
  }
 

  //
  // If ReadExecuteList is not empty, which means some token events havn't been signaled yet
  //
  //
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  SctAcquireLock (&gReadQueueLock);
  if (!SctIsListEmpty (&ReadExecuteListHead)) {
    for(ListEntry = SctGetFirstNode(&ReadExecuteListHead); ; ListEntry = SctGetNextNode(&ReadExecuteListHead, ListEntry)) {
      BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gReadQueueLock);
  
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gBlockIo2FunctionTestAssertionGuid003,
                     L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Async Read Block with proper parameter from valid media "   \
                     L"Read event has not been signaled",
                      L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx Buffer=0x%lx ",
                     __FILE__,
                     (UINTN)__LINE__,
                     BlockIo2Entity->MediaId,
                     BlockIo2Entity->LBA,
                     BlockIo2Entity->BufferSize,
                     BlockIo2Entity->Buffer
                     );
  
      SctAcquireLock (&gReadQueueLock);
      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&ReadExecuteListHead, ListEntry)) {
         break;
      }
    }
  }

  SctReleaseLock (&gReadQueueLock);

  return EFI_SUCCESS;
}


/**
 *   EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx() Function Test 2. Sync mode test
 *  @param StandardLib a point to standard test lib
 *  @param BlockIo a pointer to Block IO the interface.
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestReadBlocksExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS                           Status = EFI_SUCCESS;
  EFI_STATUS                           StatusSync = EFI_SUCCESS;
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
  UINT8                                *BufferSync = NULL;
  UINT32                               BlockNumber;
  UINTN                                IndexI;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenSync;
  BOOLEAN                              MemCompared;
  UINTN                                CompareVal = 0;
  
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

  BlockNumber       = (UINT32) MINIMUM(LastBlock, MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER);
  BufferSize        = BlockNumber * BlockSize;

  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }

  //
  // Sync Token Init
  //
  BlkIo2TokenSync.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  
  //
  // allocate aligned Buffer if Block IO protocol is null then ignore this
  //
  if (BlockIo != NULL) {
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
                     L"AllocateAlignedPool - Allocate aligned Buffer for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     EFI_UNSUPPORTED
                     );
      goto END;
    }
  }
  //
  // allocate aligned BufferSync
  //
  BufferSync = AllocateAlignedPool(
                 EfiBootServicesData, 
                 BufferSize, 
                 IoAlign
                 );
  if (BufferSync == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocateAlignedPool - Allocate aligned BufferSync for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    goto END;
  }
  
  //
  // Assertion Point 5.2.2.1
  // ReadBlocksEx must succeed to read proper data from device with valid parameter
  //
  if (MediaPresent == TRUE) {
    for (IndexI = BlockNumber; IndexI > 0; IndexI >>= 6) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER*BlockSize
      //
      NewBufferSize = IndexI * BlockSize;

      for (NewLba = LastBlock + 1 - BlockNumber; NewLba > 0; NewLba = SctRShiftU64(NewLba, 8)) {
        //
        // Sync Call ReadBlocksEx with the specified LBA and BufferSize
        //
        StatusSync = BlockIo2->ReadBlocksEx (
                                 BlockIo2,
                                 MediaId,
                                 NewLba,
                                 &BlkIo2TokenSync,
                                 NewBufferSize,
                                 (VOID*)BufferSync
                                 );
        //
        // Sync Call Block IO ReadBlocks with specified LBA and BufferSize
        //
        MemCompared = FALSE;
        if (StatusSync == EFI_SUCCESS && BlockIo != NULL) {
          Status = BlockIo->ReadBlocks (
                              BlockIo,
                              MediaId,
                              NewLba,
                              NewBufferSize,
                              (VOID*)Buffer
                              );
          if (Status == EFI_SUCCESS) {
            CompareVal = SctCompareMem (BufferSync, Buffer, NewBufferSize);
            MemCompared = TRUE;
            if (CompareVal == 0) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        } else if (EFI_ERROR(StatusSync)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }

        if (MemCompared == TRUE) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gBlockIo2FunctionTestAssertionGuid004,
                         L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Sync Read Block with proper parameter from valid media",
                         L"%a:%d:BufferSize=0x%lx, Lba=0x%lx, StatusSync=%r Block IO Memory CompareStatus=%r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         NewLba,
                         StatusSync,
                         CompareVal
                         );
        } else {
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gBlockIo2FunctionTestAssertionGuid004,
                         L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Sync Read Block with proper parameter from valid media",
                         L"%a:%d:BufferSize=0x%lx, Lba=0x%lx, StatusSync=%r",
                         __FILE__,
                         (UINTN)__LINE__,
                         NewBufferSize,
                         NewLba,
                         StatusSync
                         );
        }

      }//end of loop of Lba - LBA
    }//end of loop of BufferSize - IndexI
  }


END:
  //
  // Free aligned buffer
  //
  if (Buffer != NULL) {
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
    }
  }

  //
  // Free aligned BufferSync
  //
  if (BufferSync != NULL) {
    StatusSync = FreeAlignedPool (BufferSync);
  
    if (EFI_ERROR(StatusSync)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"FreeAlignedPool - Free aligned buffer for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     StatusSync
                     );
      return StatusSync;
    }
  }

  return Status;
}

/**
 *   EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx() Function Test 3. Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param BlockIo a pointer to Block IO the interface.
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestReadBlocksExFunctionAutoTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS                           Status = EFI_SUCCESS;
  EFI_STATUS                           StatusSync;
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
  UINT8                                *BufferSync = NULL;
  UINT32                               BlockNumber;
  UINTN                                IndexI;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  SCT_LIST_ENTRY                       ListHeader;
  SCT_LIST_ENTRY                       *ListEntry = NULL;
  UINTN                                WaitIndex;
  BlockIO2_Task                        *BlockIo2Entity = NULL;
  EFI_BLOCK_IO2_TOKEN                  BatchReadToken;
  BOOLEAN                              MemoryAllocFail = FALSE;
  
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

  BlockNumber       = (UINT32) MINIMUM(LastBlock, MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER);
  BufferSize        = BlockNumber * BlockSize;

  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }

  //
  // Initialize batch task list header
  //
  ListHeader.ForwardLink = &(ListHeader);
  ListHeader.BackLink = &(ListHeader);

  //
  // Sync Token Init
  //
  AsyncReadFinished = 0;
  BatchReadToken.Event = NULL;
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) BlockIo2FinishNotifyFunc,
                   &AsyncReadFinished,
                   &BatchReadToken.Event
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
  BatchReadToken.TransactionStatus = EFI_NOT_READY;

  
  SctPrint (L"Create Batch Read Task List.\n\n");
  //
  // Create one Batch Read task list
  //
  if (MediaPresent == TRUE) {
    for (IndexI = BlockNumber; IndexI > 0; IndexI >>= 6) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER*BlockSize
      //
      NewBufferSize = IndexI * BlockSize;

      for (NewLba = LastBlock + 1 - BlockNumber; NewLba > 0; NewLba = SctRShiftU64(NewLba, 8)) {
        //
        // To avoid the LOG information is destroyed, the LOG information will
        // be recorded after the original data is written again.
        //
        //
        // Allocate memory for one BlockIo2Entity
        //
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         sizeof(BlockIO2_Task), 
                         (VOID **) &BlockIo2Entity
                         );
        if (Status != EFI_SUCCESS) {
          MemoryAllocFail = TRUE;
          goto END;
        } 
 
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList (&ListHeader, &BlockIo2Entity->ListEntry);
        
        BlockIo2Entity->Buffer = NULL;
        BlockIo2Entity->BlockIo2Token.Event = NULL;
        BlockIo2Entity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;
        BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
        BlockIo2Entity->BufferSize = NewBufferSize;
        BlockIo2Entity->LBA = NewLba;
        BlockIo2Entity->MediaId = MediaId;
          
        BlockIo2Entity->Buffer = AllocateAlignedPool(
                                   EfiBootServicesData, 
                                   NewBufferSize, 
                                   IoAlign
                                   );
        if (BlockIo2Entity->Buffer == NULL){
          MemoryAllocFail = TRUE;
          goto END;
        }
      }//end of loop of Lba - LBA
    }//end of loop of BufferSize - IndexI

    Status = BlockIo2AsyncBatchRead (
               BlockIo2,
               &ListHeader,
               &BatchReadToken
               );
    if (EFI_ERROR(Status)) {
      goto END;
    }
    
    //
    // Busy Waiting for BatchReadToken signal
    // Busy waiting 120s on all the execute entity being moved to finished queue
    //  
    SctPrint (L"Wait maximumly 120s for Async Batch Read events signaled\n\n");
    Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
    IndexI = 0;
    
    while (IndexI < 120 && AsyncReadFinished == 0) {
      Status =gtBS->WaitForEvent (                   
                      1,
                      &TimerEvent,
                      &WaitIndex
                      );
      IndexI++;
      SctPrint(L".");
    }

    Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
    SctPrint(L"\n");
  }
  
END:
  if (BatchReadToken.Event != NULL) {
    gtBS->CloseEvent (BatchReadToken.Event);
  } 
  
  //
  // Verify all Async Read Task Result 
  //
  if (!SctIsListEmpty (&ListHeader) && MemoryAllocFail == FALSE) {
    for(ListEntry = SctGetFirstNode(&ListHeader); ; ListEntry = SctGetNextNode(&ListHeader, ListEntry)) {
      BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);

      //
      // Check & record every Block IO2 execution entity status 
      //
      BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      //
      // Using Block IO Protocol to verify data buffer consistency
      //
      if (BlockIo != NULL && BlockIo2Entity->BlockIo2Token.TransactionStatus == EFI_SUCCESS) {
        BufferSync = AllocateAlignedPool(
                       EfiBootServicesData, 
                       BlockIo2Entity->BufferSize, 
                       IoAlign
                       );
        if (BufferSync != NULL) {
          StatusSync = BlockIo->ReadBlocks(
                                  BlockIo,
                                  BlockIo2Entity->MediaId,
                                  BlockIo2Entity->LBA,
                                  BlockIo2Entity->BufferSize,
                                  BufferSync
                                  );
     
          BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          if (StatusSync == EFI_SUCCESS) {
            BlockIo2Entity->ComparedVal = SctCompareMem (
                                            BlockIo2Entity->Buffer,
                                            BufferSync,
                                            BlockIo2Entity->BufferSize
                                            );
            //
            // Block IO Memory compare job done
            //
            BlockIo2Entity->MemCompared = TRUE;   
       
            if (BlockIo2Entity->ComparedVal == 0) {
              BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
            }
          }
     
          FreeAlignedPool(BufferSync);
          BufferSync = NULL;
        }
      } else if (BlockIo2Entity->BlockIo2Token.TransactionStatus == EFI_SUCCESS){
        BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
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
  while(!SctIsListEmpty (&ListHeader)) {
    BlockIo2Entity = CR(ListHeader.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);

    if ( MemoryAllocFail == FALSE) {
      if (BlockIo2Entity->MemCompared == TRUE) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       BlockIo2Entity->AssertionType,
                       gBlockIo2FunctionTestAssertionGuid005,
                       L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Batch Async Read Block with proper parameter from valid media",
                       L"%a:%d: MediaId=%d, BufferSize=0x%lx, LBA=0x%lx, BufferAddr=0x%lx, TransactionStatus=%r, Block IO Memory CompareStatus=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       BlockIo2Entity->MediaId,
                       BlockIo2Entity->BufferSize,
                       BlockIo2Entity->LBA,
                       BlockIo2Entity->Buffer,
                       BlockIo2Entity->BlockIo2Token.TransactionStatus,
                       BlockIo2Entity->ComparedVal
                       );
      } else {
        StandardLib->RecordAssertion (
                       StandardLib,
                       BlockIo2Entity->AssertionType,
                       gBlockIo2FunctionTestAssertionGuid005,
                       L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Batch Async Read Block with proper parameter from valid media",
                       L"%a:%d:MediaId=%d, BufferSize=0x%lx, LBA=0x%lx, BufferAddr=0x%lx, TransactionStatus=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       BlockIo2Entity->MediaId,
                       BlockIo2Entity->BufferSize,
                       BlockIo2Entity->LBA,
                       BlockIo2Entity->Buffer,
                       BlockIo2Entity->BlockIo2Token.TransactionStatus
                       );
      }
    }
    
    //
    // Free aligned Buffer
    //
    if (BlockIo2Entity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    
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
      }
    }
 
    gtBS->FreePool(BlockIo2Entity);
  }
  
  return Status;
}


/**
 *   EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx() Function Test 4. Mixed Sync & Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param BlockIo a pointer to Block IO the interface.
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestReadBlocksExFunctionAutoTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS                           Status = EFI_SUCCESS;
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
  UINT8                                *BufferAsync = NULL;
  UINT32                               BlockNumber;
  UINTN                                IndexI;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  BlockIO2_Task                        *BlockIo2Entity = NULL;
  BlockIO2_Task                        *BlockIo2EntitySync = NULL;
  UINTN                                WaitIndex;
  SCT_LIST_ENTRY                       *ListEntry = NULL;
  SCT_LIST_ENTRY                       *ListEntrySync = NULL;

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

  BlockNumber       = (UINT32) MINIMUM(LastBlock, MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER);
  BufferSize        = BlockNumber * BlockSize;

  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }

 
  
  //
  // Assertion Point 5.2.2.1
  // ReadBlocksEx must succeed to read proper data from device with valid parameter
  //
  if (MediaPresent == TRUE) {
   
    SctPrint (L" ============= Start to do Mixed Async & Sync ReadBlocksEx call ============= \n\n");
    for (IndexI = BlockNumber; IndexI > 0; IndexI >>= 6) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER*BlockSize
      //
     
      NewBufferSize = IndexI * BlockSize;

      for (NewLba = LastBlock + 1 - BlockNumber; NewLba > 0; NewLba = SctRShiftU64(NewLba, 8)) {
        //
        // allocate aligned BufferSync
        //
        BufferAsync = NULL;
        BufferAsync = AllocateAlignedPool(
                        EfiBootServicesData, 
                        NewBufferSize, 
                        IoAlign
                        );
        if (BufferAsync == NULL) {
          goto END_WAIT;
        }

        //
        // Async & Sync Call ReadBlocksEx with the specified LBA and BufferSize
        //
        Status = BlockIo2MixedSyncAsyncReadData (
                   BlockIo2,
                   MediaId,
                   NewLba,
                   NewBufferSize,
                   IoAlign,
                   BufferAsync
                   );
       }//end of loop of Lba - LBA
    }//end of loop of BufferSize - IndexI

    SctPrint (L" ================ Mixed Async & Sync ReadBlocksEx call finshed ================ \n\n");


END_WAIT:
  
    //
    // Busy waiting 120s on all the execute entity being moved to finished queue
    //  
    SctPrint (L"Wait maximumly 120s for all Async Read events signaled\n\n");
    Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
    IndexI = 0;
    
    SctAcquireLock (&gMixedReadQueueLock);
    while (!SctIsListEmpty (&MixedReadExecuteListHead) && IndexI < 120) {
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
    SctPrint(L"\n");

  }
 

  //
  // clear all Block IO2 events from gReadFinishQueue 
  // gReadFinshQueue is handled first since we use BLock IO read to do read buffer validation 
  // Here no logs should be wrote to this block device to keep data intact
  //
  SctAcquireLock (&gMixedReadQueueLock);
  if (!SctIsListEmpty (&MixedReadFinishListHead)) {
    for(ListEntry = SctGetFirstNode(&MixedReadFinishListHead); ; ListEntry = SctGetNextNode(&MixedReadFinishListHead, ListEntry)) {
      BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gMixedReadQueueLock);

      //
      // Check & record every Block IO2 execution entity status 
      //
      //
      // Using Block IO 2 Protocol Sync Read to verify data buffer consistency
      //
      if (BlockIo2Entity->BlockIo2Token.TransactionStatus == EFI_SUCCESS) {
        if (!SctIsListEmpty (&MixedSyncReadListHead)) {
          for(ListEntrySync = SctGetFirstNode(&MixedSyncReadListHead); ; ListEntrySync = SctGetNextNode(&MixedSyncReadListHead, ListEntrySync)) {

            BlockIo2EntitySync = CR(ListEntrySync, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
  
            if (BlockIo2Entity->MediaId == BlockIo2EntitySync->MediaId
             && BlockIo2Entity->LBA == BlockIo2EntitySync->LBA
             && BlockIo2Entity->BufferSize == BlockIo2EntitySync->BufferSize ) {
              BlockIo2EntitySync->ComparedVal = SctCompareMem (
                                                  BlockIo2Entity->Buffer,
                                                  BlockIo2EntitySync->Buffer,
                                                  BlockIo2Entity->BufferSize
                                                  );
   
              BlockIo2EntitySync->MemCompared = TRUE;
   
              if (BlockIo2EntitySync->ComparedVal == 0) {
                BlockIo2EntitySync->AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                BlockIo2EntitySync->AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
              
            }
  
            //
            // Last list node handled
            //
            if (SctIsNodeAtEnd(&MixedSyncReadListHead, ListEntrySync)) {
              break;
            }
          }
        }
      } else {
         BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
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
  
  //
  // Record All Finished Read case results
  //
  while (!SctIsListEmpty (&MixedReadFinishListHead)) {
    BlockIo2Entity = CR(MixedReadFinishListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
       
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
    SctReleaseLock (&gMixedReadQueueLock);
    
    
    gtBS->CloseEvent(BlockIo2Entity->BlockIo2Token.Event);
    //
    // Free aligned Buffer
    //
    if (BlockIo2Entity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    }
    gtBS->FreePool(BlockIo2Entity);
  
  
    SctAcquireLock (&gMixedReadQueueLock);
  }  
  SctReleaseLock (&gMixedReadQueueLock);

  
  //
  // Record All Failed Async Read case results
  //
  while (!SctIsListEmpty (&MixedReadFailListHead)) {
    BlockIo2Entity = CR(MixedReadFailListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
       
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gBlockIo2FunctionTestAssertionGuid011,
                   L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Mixed Sync & Async Read Block with proper parameter from valid media"    \
                   L"Async Read Call failed",
                   L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   BlockIo2Entity->MediaId,
                   BlockIo2Entity->LBA,
                   BlockIo2Entity->BufferSize,
                   BlockIo2Entity->Buffer
                   );
    
    //
    // Free aligned Buffer
    //
    if (BlockIo2Entity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    }
    gtBS->FreePool(BlockIo2Entity);
  
  }  

  //
  // Mixed Sync Async function test logs
  // 
  while (!SctIsListEmpty (&MixedSyncReadListHead)) {
    BlockIo2EntitySync = CR(MixedSyncReadListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2EntitySync->ListEntry);

    if (BlockIo2EntitySync->MemCompared == TRUE) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     BlockIo2EntitySync->AssertionType,
                     gBlockIo2FunctionTestAssertionGuid012,
                     L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Mixed Sync & Async Read Block with proper parameter from valid media",
                     L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx Block IO2 Sync Memory CompareStatus=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BlockIo2EntitySync->MediaId,
                     BlockIo2EntitySync->LBA,
                     BlockIo2EntitySync->BufferSize,
                     BlockIo2EntitySync->Buffer,
                     BlockIo2EntitySync->ComparedVal
                     );
    }
    if (BlockIo2EntitySync->Buffer != NULL) {
      FreeAlignedPool(BlockIo2EntitySync->Buffer);
    }

    gtBS->FreePool(BlockIo2EntitySync);
    
  }

  
  //
  // Mixed Sync Async function failed test logs
  // 
  while (!SctIsListEmpty (&MixedSyncReadFailListHead)) {
   BlockIo2EntitySync = CR(MixedSyncReadFailListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
   SctRemoveEntryList (&BlockIo2EntitySync->ListEntry);

   if (BlockIo2EntitySync->MemCompared == TRUE) {
     StandardLib->RecordAssertion (
                    StandardLib,
                    EFI_TEST_ASSERTION_FAILED,
                    gBlockIo2FunctionTestAssertionGuid013,
                    L"EFI_BLOCK_IO2_PROTOCOL.ReadBlocksEx - Mixed Sync & Async Read Block with proper parameter from valid media"     \
                    L"Sync Read failed",
                    L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx ",
                    __FILE__,
                    (UINTN)__LINE__,
                    BlockIo2EntitySync->MediaId,
                    BlockIo2EntitySync->LBA,
                    BlockIo2EntitySync->BufferSize,
                    BlockIo2EntitySync->Buffer
                    );
   }
   if (BlockIo2EntitySync->Buffer != NULL) {
     FreeAlignedPool(BlockIo2EntitySync->Buffer);
   }

   gtBS->FreePool(BlockIo2EntitySync);
    
  }

 
  return EFI_SUCCESS;
}



/**
 *  Entrypoint for EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx() Function Test.
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
BBTestWriteBlocksExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                                 Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib = NULL;
  EFI_BLOCK_IO_PROTOCOL                      *BlockIo = NULL;
  EFI_BLOCK_IO2_PROTOCOL                     *BlockIo2 = NULL;
  EFI_BLOCK_IO2_PROTOCOL                     *BlockIo2Temp = NULL;
  EFI_DEVICE_PATH_PROTOCOL                   *DevicePath = NULL;
  CHAR16                                     *DevicePathStr = NULL;
  UINTN                                      Index;
  UINTN                                      NoHandles;
  EFI_HANDLE                                 *HandleBuffer = NULL;


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
  // Locate Block IO protocol on same handler for test
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiBlockIo2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiBlockIo2ProtocolGuid,
                     (VOID **) &BlockIo2Temp
                     );
    if (Status == EFI_SUCCESS && BlockIo2Temp == BlockIo2) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gBlackBoxEfiBlockIoProtocolGuid,
                       (VOID **) &BlockIo
                       );
      if (Status != EFI_SUCCESS) {
        BlockIo = NULL;
      }
      break;
    }
  }
  
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }
  //
  // Async call to test Block IO 2 WriteBlocksEx
  // Using link list  to manage token pool
  //
  BBTestWriteBlocksExFunctionAutoTestCheckpoint1 (StandardLib, BlockIo, BlockIo2);
   
  //
  // Sync call to test Block IO 2 WriteBlocksEx
  //
  BBTestWriteBlocksExFunctionAutoTestCheckpoint2 (StandardLib, BlockIo, BlockIo2);

  //
  // Sync call to test Block IO 2 WriteBlocksEx
  // Using Cascade Event Chain to manage token pool
  //
  BBTestWriteBlocksExFunctionAutoTestCheckpoint3 (StandardLib, BlockIo, BlockIo2);
  //
  // Mixed Sync & Async Call to test Block IO 2 WriteBlocksEx
  //
  BBTestWriteBlocksExFunctionAutoTestCheckpoint4 (StandardLib, BlockIo, BlockIo2);

  return Status;

}


/**
 *   EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx() Function Test 1. Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param BlockIo a pointer to Block IO the interface.
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestWriteBlocksExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS                           Status;
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
  UINT8                                *ReadBuffer = NULL;
  UINT8                                *WriteBuffer = NULL;
  UINT32                               BlockNumber;
  UINTN                                IndexI;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  EFI_STATUS                           StatusWrite;
  BlockIO2_Task                        *BlockIo2Entity = NULL;
  SCT_LIST_ENTRY                       *ListEntry = NULL;
  UINTN                                WaitIndex;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenSync;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenFlush;

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
  // Sync & Flush Token Init
  //
  BlkIo2TokenSync.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  BlkIo2TokenFlush.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;

  SctPrint(L"Read Record Data.\n");
  //
  // Record all write blocks data for recovery first
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (LastBlock != 0)) {


    SctPrint (L" =================== Record Blocks Info =================== \n\n");
    for (IndexI = 1; IndexI < MAX_NUMBER_OF_WRITE_BLOCK_FUNC_BUFFER; IndexI++) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_DIFFERENT_BUFFERSIZE_FOR_TEST*BlockSize
      //
      NewBufferSize = IndexI * BlockSize;

      for (NewLba = SctRShiftU64(LastBlock, 1); NewLba < SctRShiftU64(LastBlock, 1) + MAX_DIFFERENT_LBA_FOR_TEST; NewLba++) {
        //
        // To avoid the LOG information being destroyed, the LOG information will
        // be recorded after the original data blocks are recovered.
        //
        //
        // Allocate memory for one BlockIo2Entity
        //
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         sizeof(BlockIO2_Task), 
                         (VOID **) &BlockIo2Entity
                         );
        if (Status != EFI_SUCCESS) {
          goto END;
        } 
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList (&SyncReadDataListHead, &BlockIo2Entity->ListEntry);
        
        BlockIo2Entity->Buffer = NULL;
        BlockIo2Entity->BlockIo2Token.Event = NULL;
        BlockIo2Entity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;
        BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
        BlockIo2Entity->BufferSize = NewBufferSize;
        BlockIo2Entity->LBA = NewLba;
        BlockIo2Entity->MediaId = MediaId;
          
        BlockIo2Entity->Buffer = AllocateAlignedPool(
                                   EfiBootServicesData, 
                                   NewBufferSize, 
                                   IoAlign
                                   );
        if (BlockIo2Entity->Buffer == NULL){
          goto END;
        }
      
        //
        // Sync Call ReadBlocksEx with the specified LBA and BufferSize
        //
        Status = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             BlockIo2Entity->MediaId,
                             BlockIo2Entity->LBA,
                             &BlockIo2Entity->BlockIo2Token,
                             BlockIo2Entity->BufferSize,
                             (VOID*)BlockIo2Entity->Buffer
                             );
        if (Status != EFI_SUCCESS) {
          goto END;
        }
      }
    }


    SctPrint (L" ================ Start to do Async WriteBlocksEx call ================ \n\n");
    // 
    // do Asyn write call basing on read data result 
    //
    if (!SctIsListEmpty (&SyncReadDataListHead)) {
      for(ListEntry = SctGetFirstNode(&SyncReadDataListHead); ; ListEntry = SctGetNextNode(&SyncReadDataListHead, ListEntry)) {
        BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
      
        WriteBuffer = NULL;
        WriteBuffer = AllocateAlignedPool(
                        EfiBootServicesData, 
                        BlockIo2Entity->BufferSize, 
                        IoAlign
                        );
        if (WriteBuffer == NULL) {
          goto END_WAIT;
        }
        //
        // Set test data pattern into Write Buffer  
        //
        SctSetMem (WriteBuffer, BlockIo2Entity->BufferSize, ASYNC_WRITE_TEST_PATTERN);
        //
        // Write specified buffer2 differ from buffer to the device
        // write info comes from previous read info list
        //
        StatusWrite = BlockIo2AsyncWriteData(
                        BlockIo2,
                        BlockIo2Entity->MediaId,
                        BlockIo2Entity->LBA,
                        BlockIo2Entity->BufferSize,
                        (VOID*)WriteBuffer
                        );

        if (EFI_ERROR(StatusWrite)) {
          FreeAlignedPool(WriteBuffer);
        }
        //
        // Last list node handled
        //
        if (SctIsNodeAtEnd(&SyncReadDataListHead, ListEntry)) {
          break;
        }
      }

    
      SctPrint (L" ================== Async WriteBlocksEx call finshed ================== \n\n");

END_WAIT:         
      //
      // if write-cached, then flush the data to physical device
      //
      if (WriteCaching) {
        BlockIo2->FlushBlocksEx (BlockIo2, &BlkIo2TokenSync);
      }
  
      
      //
      // Busy waiting 120s on all the execute entity being moved to finished queue
      //  
      SctPrint (L"Wait maximumly 120s for all Async Write events signaled\n\n");
      Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
      IndexI = 0;
      
      SctAcquireLock (&gWriteQueueLock);
      while (!SctIsListEmpty (&WriteExecuteListHead) && IndexI < 120) {
        SctReleaseLock (&gWriteQueueLock);
        
        gtBS->WaitForEvent (   
                1,
                &TimerEvent,
                &WaitIndex
                );
        IndexI++;
        SctPrint (L".");
        SctAcquireLock (&gWriteQueueLock);
      }
      SctReleaseLock (&gWriteQueueLock);

      Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
      SctPrint(L"\n");
    }
  }

END:
  //
  // Flush all data to physical device first
  //
  if (WriteCaching) {
    BlockIo2->FlushBlocksEx (BlockIo2, &BlkIo2TokenSync);
  }

  //
  // clear all Block IO2 events from gWriteFinishQueue 
  // gWriteFinishQueue is handled first since we use BLock IO write to do write buffer validation 
  // Here no logs should be wrote to this block device to keep data intact
  //
  SctAcquireLock (&gWriteQueueLock);
  if (!SctIsListEmpty (&WriteFinishListHead)) {
    for(ListEntry = SctGetFirstNode(&WriteFinishListHead); ; ListEntry = SctGetNextNode(&WriteFinishListHead, ListEntry)) {
      BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gWriteQueueLock);
  
      //
      // Check written data of each successful Block IO2 execution 
      //
      if (BlockIo2Entity->BlockIo2Token.TransactionStatus == EFI_SUCCESS) {

        BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;

        ReadBuffer = AllocateAlignedPool(
                       EfiBootServicesData, 
                       BlockIo2Entity->BufferSize, 
                       IoAlign
                       );
        if (ReadBuffer != NULL) {
          Status = BlockIo2->ReadBlocksEx(
                               BlockIo2,
                               BlockIo2Entity->MediaId,
                               BlockIo2Entity->LBA,
                               &BlkIo2TokenSync,
                               BlockIo2Entity->BufferSize,
                               ReadBuffer
                               );
          //
          // Compare with write test pattern
          //
          if (Status == EFI_SUCCESS) {
            BlockIo2Entity->ComparedVal = 0;
            for (IndexI = 0; IndexI < BlockIo2Entity->BufferSize; IndexI++) {
              if (ReadBuffer[IndexI] != ASYNC_WRITE_TEST_PATTERN) {
                BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                BlockIo2Entity->ComparedVal = 1;
                break;
              }
            }                              
          
            //
            // Block IO Memory compare job done
            //
            BlockIo2Entity->MemCompared = TRUE;   
          }
        
          FreeAlignedPool(ReadBuffer);
          ReadBuffer = NULL;
        }
      } else {
        BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      SctAcquireLock (&gWriteQueueLock);
      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&WriteFinishListHead, ListEntry)) {
        break;
      }
    }
  }
  SctReleaseLock (&gWriteQueueLock);

  //
  // Clean up & free all record resources
  //
  SctPrint (L"============ Restore All written blocks ============= \n");
  while (!SctIsListEmpty (&SyncReadDataListHead)) {
    BlockIo2Entity = CR(SyncReadDataListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);

    if (BlockIo2Entity->Buffer != NULL) {
      //
      // restore all read informations
      //
      Status = BlockIo2->WriteBlocksEx (
                           BlockIo2,
                           BlockIo2Entity->MediaId,
                           BlockIo2Entity->LBA,
                           &BlockIo2Entity->BlockIo2Token,
                           BlockIo2Entity->BufferSize,
                           (VOID*)BlockIo2Entity->Buffer
                           );
      if (Status != EFI_SUCCESS) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Restore blocks fail",
                       L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx",
                       __FILE__,
                       (UINTN)__LINE__,
                       BlockIo2Entity->MediaId,
                       BlockIo2Entity->LBA,
                       BlockIo2Entity->BufferSize
                       );
      }
      if (BlockIo2Entity->Buffer != NULL) {
        Status = FreeAlignedPool (BlockIo2Entity->Buffer);
      }
    }

    gtBS->FreePool(BlockIo2Entity);
  }
  
  //
  // Flush all data to physical device 
  //
  if (WriteCaching) {
    BlockIo2->FlushBlocksEx (BlockIo2, &BlkIo2TokenSync);
  }
  SctPrint (L"============ Restore All written blocks finshed ============ \n");

  //
  // Record All write finshed test logs
  //  
  SctAcquireLock (&gWriteQueueLock);
  while (!SctIsListEmpty (&WriteFinishListHead)) {
    BlockIo2Entity = CR(WriteFinishListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
   
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
    SctReleaseLock (&gWriteQueueLock);
   
    
    if (BlockIo2Entity->MemCompared == TRUE) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     BlockIo2Entity->AssertionType,
                     gBlockIo2FunctionTestAssertionGuid006,
                     L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Async Write Block with proper parameter to valid media "    \
                     L"ASYNC_WRITE_TEST_PATTERN 0x1C",
                     L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx ReadBlocksEx Buffer CompareStatus=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BlockIo2Entity->MediaId,
                     BlockIo2Entity->LBA,
                     BlockIo2Entity->BufferSize,
                     BlockIo2Entity->Buffer,
                     BlockIo2Entity->ComparedVal
                     );
    } else {
      StandardLib->RecordAssertion (
                     StandardLib,
                     BlockIo2Entity->AssertionType,
                     gBlockIo2FunctionTestAssertionGuid006,
                     L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Async Write Block with proper parameter to valid media "    \
                     L"ASYNC_WRITE_TEST_PATTERN 0x1C",
                     L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                     __FILE__,
                     (UINTN)__LINE__,
                     BlockIo2Entity->MediaId,
                     BlockIo2Entity->LBA,
                     BlockIo2Entity->BufferSize,
                     BlockIo2Entity->Buffer
                     );
    }
   
    gtBS->CloseEvent(BlockIo2Entity->BlockIo2Token.Event);
    //
    // Free aligned Buffer
    //
    if (BlockIo2Entity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    }
    gtBS->FreePool(BlockIo2Entity);
   
    
    SctAcquireLock (&gWriteQueueLock);
  }  
  SctReleaseLock (&gWriteQueueLock);

  //
  // If WriteFailListHead is not empty, which means some Async Calls are wrong 
  // 
  while(!SctIsListEmpty (&WriteFailListHead)) {
    BlockIo2Entity = CR(WriteFailListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gBlockIo2FunctionTestAssertionGuid007,
                   L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Async Write Block with proper parameter to valid media "    \
                   L"Write Failed ",
                   L"%a:%d:BufferSize=%d, LBA=0x%lx, StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BlockIo2Entity->BufferSize,
                   BlockIo2Entity->LBA,
                   BlockIo2Entity->StatusAsync
                   );
    //
    // Free aligned Buffer
    //
    if (BlockIo2Entity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    
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
      }
    }
 
    gtBS->FreePool(BlockIo2Entity);
  }
  

  //
  // If WriteExecuteList is not empty, which means some token events havn't been signaled yet
  //
  //
  // Be careful, All the entities in Execution list should NOT be freed here! 
  //
  SctAcquireLock (&gWriteQueueLock);
  if (!SctIsListEmpty (&WriteExecuteListHead)) {
    for(ListEntry = SctGetFirstNode(&WriteExecuteListHead); ; ListEntry = SctGetNextNode(&WriteExecuteListHead, ListEntry)) {
      BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
      SctReleaseLock (&gWriteQueueLock);
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gBlockIo2FunctionTestAssertionGuid008,
                     L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Async Write Block with proper parameter to valid media "    \
                     L"Async write event has not been signaled",
                     L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx Buffer=0x%lx ",
                     __FILE__,
                     (UINTN)__LINE__,
                     BlockIo2Entity->MediaId,
                     BlockIo2Entity->LBA,
                     BlockIo2Entity->BufferSize,
                     BlockIo2Entity->Buffer
                     );
     
      SctAcquireLock (&gWriteQueueLock);
      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&WriteExecuteListHead, ListEntry)) {
        break;
      }
    }
  }

  SctReleaseLock (&gWriteQueueLock);
  
  return EFI_SUCCESS;
}

/**
 *   EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx() Function Test 2. Sync mode test
 *  @param StandardLib a point to standard test lib
 *  @param BlockIo a pointer to Block IO the interface.
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestWriteBlocksExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_STATUS                           Status;
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
  UINT8                                *ReadBuffer = NULL;
  UINT8                                *WriteBuffer = NULL;
  UINT32                               BlockNumber;
  UINTN                                IndexI;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  EFI_STATUS                           StatusWrite;
  BlockIO2_Task                        *BlockIo2Entity = NULL;
  SCT_LIST_ENTRY                       *ListEntry = NULL;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenSync;

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
  // Sync Token Init
  //
  BlkIo2TokenSync.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;

  SctPrint(L"Read Record Data.\n");
  //
  // Record all write blocks data for recovery first
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (LastBlock != 0)) {

    SctPrint (L" =================== Record Blocks Info =================== \n\n");

    for (IndexI = 1; IndexI < MAX_NUMBER_OF_WRITE_BLOCK_FUNC_BUFFER; IndexI++) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_DIFFERENT_BUFFERSIZE_FOR_TEST*BlockSize
      //
      NewBufferSize = IndexI * BlockSize;

      for (NewLba = SctRShiftU64(LastBlock, 1); NewLba < SctRShiftU64(LastBlock, 1) + MAX_DIFFERENT_LBA_FOR_TEST; NewLba++) {
        //
        // To avoid the LOG information is destroied, the LOG information will
        // be recorded after the original data is written again.
        //
        //
        // Allocate memory for one BlockIo2Entity
        //
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         sizeof(BlockIO2_Task), 
                         (VOID **) &BlockIo2Entity
                         );
        if (Status != EFI_SUCCESS) {
          goto END;
        } 
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList (&SyncReadDataListHead, &BlockIo2Entity->ListEntry);

        BlockIo2Entity->Buffer = NULL;
        BlockIo2Entity->BlockIo2Token.Event = NULL;
        BlockIo2Entity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;
        BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
        BlockIo2Entity->BufferSize = NewBufferSize;
        BlockIo2Entity->LBA = NewLba;
        BlockIo2Entity->MediaId = MediaId;
        
        BlockIo2Entity->Buffer = AllocateAlignedPool(
                                    EfiBootServicesData, 
                                    NewBufferSize, 
                                    IoAlign
                                    );
        if (BlockIo2Entity->Buffer == NULL){
          goto END;
        }

        //
        // Sync Call ReadBlocksEx with the specified LBA and BufferSize to record block data
        //
        Status = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             BlockIo2Entity->MediaId,
                             BlockIo2Entity->LBA,
                             &BlockIo2Entity->BlockIo2Token,
                             BlockIo2Entity->BufferSize,
                             (VOID*)BlockIo2Entity->Buffer
                             );
        if (Status != EFI_SUCCESS) {
          goto END;
        }
      }
    }


    SctPrint (L" ================ Start to do Sync WriteBlocksEx call ================ \n\n");
    // 
    // do Asyn write call basing on read data result 
    //
    if (!SctIsListEmpty (&SyncReadDataListHead)) {
      for(ListEntry = SctGetFirstNode(&SyncReadDataListHead); ; ListEntry = SctGetNextNode(&SyncReadDataListHead, ListEntry)) {
        BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
        
        WriteBuffer = NULL;
        WriteBuffer = AllocateAlignedPool(
                        EfiBootServicesData, 
                        BlockIo2Entity->BufferSize, 
                        IoAlign
                        );
        if (WriteBuffer == NULL) {
          goto END;
        }
        ReadBuffer = NULL;
        ReadBuffer = AllocateAlignedPool(
                       EfiBootServicesData, 
                       BlockIo2Entity->BufferSize, 
                       IoAlign
                       );
        if (ReadBuffer == NULL) {
          FreeAlignedPool(WriteBuffer);
          goto END;
        }
        //
        // Set test data pattern into Write Buffer  
        //
        SctSetMem (WriteBuffer, BlockIo2Entity->BufferSize, SYNC_WRITE_TEST_PATTERN);
        //
        // Write specified buffer2 differ from buffer to the device
        // write info comes from previous read info list
        //
        StatusWrite = BlockIo2->WriteBlocksEx(
                                  BlockIo2,
                                  BlockIo2Entity->MediaId,
                                  BlockIo2Entity->LBA,
                                  &BlkIo2TokenSync,
                                  BlockIo2Entity->BufferSize,
                                  (VOID*)WriteBuffer
                                  );
        //
        // if write-cached, then flush the data to physical device
        //
        if (WriteCaching) {
          BlockIo2->FlushBlocksEx (BlockIo2, &BlkIo2TokenSync);
        }
        
        Status = BlockIo2->ReadBlocksEx(
                             BlockIo2,
                             BlockIo2Entity->MediaId,
                             BlockIo2Entity->LBA,
                             &BlkIo2TokenSync,
                             BlockIo2Entity->BufferSize,
                             ReadBuffer
                             );
        
        BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        BlockIo2Entity->ComparedVal = 0;
        for (IndexI = 0; IndexI < BlockIo2Entity->BufferSize; IndexI++) {
          if (ReadBuffer[IndexI] != SYNC_WRITE_TEST_PATTERN) {
            BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            BlockIo2Entity->ComparedVal = 1;
            break;
          }
        } 
        
        FreeAlignedPool(WriteBuffer);
        FreeAlignedPool(ReadBuffer);
        
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
  SctPrint (L"Restore All written blocks.\n");
  if (!SctIsListEmpty (&SyncReadDataListHead)) {
    for(ListEntry = SctGetFirstNode(&SyncReadDataListHead); ; ListEntry = SctGetNextNode(&SyncReadDataListHead, ListEntry)) {
      BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
     
      if (BlockIo2Entity->Buffer != NULL) {
        //
        // restore all read informations
        //
        Status = BlockIo2->WriteBlocksEx (
                             BlockIo2,
                             BlockIo2Entity->MediaId,
                             BlockIo2Entity->LBA,
                             &BlockIo2Entity->BlockIo2Token,
                             BlockIo2Entity->BufferSize,
                             (VOID*)BlockIo2Entity->Buffer
                             );
        if (Status != EFI_SUCCESS) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"Restore blocks fail",
                         L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx",
                         __FILE__,
                         (UINTN)__LINE__,
                         BlockIo2Entity->MediaId,
                         BlockIo2Entity->LBA,
                         BlockIo2Entity->BufferSize
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
  while (!SctIsListEmpty (&SyncReadDataListHead)) {
    BlockIo2Entity = CR(SyncReadDataListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);

    StandardLib->RecordAssertion (
                   StandardLib,
                   BlockIo2Entity->AssertionType,
                   gBlockIo2FunctionTestAssertionGuid009,
                   L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Sync Write Block with proper parameter to valid media "    \
                   L"SYNC_WRITE_TEST_PATTERN 0xAB",
                   L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx ReadBlocksEx Buffer CompareStatus=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BlockIo2Entity->MediaId,
                   BlockIo2Entity->LBA,
                   BlockIo2Entity->BufferSize,
                   BlockIo2Entity->ComparedVal
                   );
    //
    // Free All memory
    //
    Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    gtBS->FreePool(BlockIo2Entity);
  }
  
  return EFI_SUCCESS;
}

/**
 *   EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx() Function Test 3. Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param BlockIo a pointer to Block IO the interface.
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestWriteBlocksExFunctionAutoTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  ) 
{  
  EFI_STATUS                           Status = EFI_SUCCESS;
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
  UINT8                                *ReadBufferSync = NULL;
  UINT32                               BlockNumber;
  UINTN                                IndexI;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  EFI_BLOCK_IO2_TOKEN                  BatchWriteToken;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenSync;
  SCT_LIST_ENTRY                       RecordListHeader;
  SCT_LIST_ENTRY                       WriteListHeader;
  SCT_LIST_ENTRY                       *ListEntry = NULL;
  UINTN                                WaitIndex;
  BlockIO2_Task                        *BlockIo2RecordEntity = NULL;
  BlockIO2_Task                        *BlockIo2WriteEntity = NULL;
  BOOLEAN                              MemoryAllocFail = FALSE;

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

  BlockNumber       = (UINT32) MINIMUM(LastBlock, MAX_NUMBER_OF_READ_BLOCK_FUNC_BUFFER);
  BufferSize        = BlockNumber * BlockSize;

  if (BufferSize == 0) {
    BufferSize = BlockSize;
  }

  //
  // Initialize batch task list header & Read data list header 
  //
  RecordListHeader.ForwardLink = &(RecordListHeader);
  RecordListHeader.BackLink = &(RecordListHeader);
  WriteListHeader.ForwardLink = &(WriteListHeader);
  WriteListHeader.BackLink = &(WriteListHeader);
  //
  // Sync Token Init
  //
  BlkIo2TokenSync.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;

  // 
  // Batch Async Token Init
  //
  AsyncWriteFinished = 0;
  BatchWriteToken.Event = NULL;
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) BlockIo2FinishNotifyFunc,
                   &AsyncWriteFinished,
                   &BatchWriteToken.Event
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
  BatchWriteToken.TransactionStatus = EFI_NOT_READY;

  
  SctPrint (L"Create Batch Read Task List.\n\n");
  //
  // Create one Batch Read task list
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (LastBlock != 0)) {
    SctPrint (L" =================== Record Blocks Info =================== \n\n");

    for (IndexI = 1; IndexI < MAX_NUMBER_OF_WRITE_BLOCK_FUNC_BUFFER; IndexI++) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_DIFFERENT_BUFFERSIZE_FOR_TEST*BlockSize
      //
      NewBufferSize = IndexI * BlockSize;

      for (NewLba = SctRShiftU64(LastBlock, 1); NewLba < SctRShiftU64(LastBlock, 1) + MAX_DIFFERENT_LBA_FOR_TEST; NewLba++) {
        //
        // To avoid the LOG information is destroied, the LOG information will
        // be recorded after the original data is written again.
        //
        //
        // Allocate memory for one BlockIo2Entity
        //
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         sizeof(BlockIO2_Task), 
                         (VOID **) &BlockIo2RecordEntity
                         );
        if (Status != EFI_SUCCESS) {
          MemoryAllocFail = TRUE;
          goto END;
        } 
 
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList (&RecordListHeader, &BlockIo2RecordEntity->ListEntry);
        
        BlockIo2RecordEntity->Buffer = NULL;
        BlockIo2RecordEntity->BlockIo2Token.Event = NULL;
        BlockIo2RecordEntity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;
        BlockIo2RecordEntity->Signature = BIO2ENTITY_SIGNATURE;
        BlockIo2RecordEntity->BufferSize = NewBufferSize;
        BlockIo2RecordEntity->LBA = NewLba;
        BlockIo2RecordEntity->MediaId = MediaId;
          
        BlockIo2RecordEntity->Buffer = AllocateAlignedPool(
                                         EfiBootServicesData, 
                                         NewBufferSize, 
                                         IoAlign
                                         );
        if (BlockIo2RecordEntity->Buffer == NULL){
          MemoryAllocFail = TRUE;
          goto END;
        }
        //
        // Sync Call ReadBlocksEx with the specified LBA and BufferSize
        //
        Status = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             BlockIo2RecordEntity->MediaId,
                             BlockIo2RecordEntity->LBA,
                             &BlockIo2RecordEntity->BlockIo2Token,
                             BlockIo2RecordEntity->BufferSize,
                             (VOID*)BlockIo2RecordEntity->Buffer
                             );    
        if (Status != EFI_SUCCESS) {
          goto END;
        }
      }//end of loop of Lba - LBA
    }//end of loop of BufferSize - IndexI


    SctPrint (L" =================== Create Test Write Blocks  =================== \n\n");
    if (!SctIsListEmpty (&RecordListHeader)) {
      for(ListEntry = SctGetFirstNode(&RecordListHeader); ; ListEntry = SctGetNextNode(&RecordListHeader, ListEntry)) {

        BlockIo2RecordEntity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
        //
        // To avoid the LOG information is destroied, the LOG information will
        // be recorded after the original data is written again.
        //
        //
        // Allocate memory for one BlockIo2Entity
        //
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         sizeof(BlockIO2_Task), 
                         (VOID **) &BlockIo2WriteEntity
                         );
        if (Status != EFI_SUCCESS) {
          MemoryAllocFail = TRUE;
          goto END;
        } 
 
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList (&WriteListHeader, &BlockIo2WriteEntity->ListEntry);
        
        BlockIo2WriteEntity->Buffer = NULL;
        BlockIo2WriteEntity->BlockIo2Token.Event = NULL;
        BlockIo2WriteEntity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;
        BlockIo2WriteEntity->Signature = BIO2ENTITY_SIGNATURE;
        BlockIo2WriteEntity->BufferSize = BlockIo2RecordEntity->BufferSize;
        BlockIo2WriteEntity->LBA = BlockIo2RecordEntity->LBA;
        BlockIo2WriteEntity->MediaId = BlockIo2RecordEntity->MediaId;
          
        BlockIo2WriteEntity->Buffer = AllocateAlignedPool(
                                        EfiBootServicesData, 
                                        BlockIo2WriteEntity->BufferSize, 
                                        IoAlign
                                        );
        if (BlockIo2WriteEntity->Buffer == NULL){
          MemoryAllocFail = TRUE;
          goto END;
        }
        
        SctSetMem (BlockIo2WriteEntity->Buffer, BlockIo2WriteEntity->BufferSize, ASYNC_WRITE_TEST_PATTERN);

        //
        // Last list node handled
        //
        if (SctIsNodeAtEnd(&RecordListHeader, ListEntry)) {
          break;
        }
      }
    }

    
    SctPrint (L"Start to do Async Write.\n\n");
    Status = BlockIo2AsyncBatchWrite (
               BlockIo2,
               &WriteListHeader,
               &BatchWriteToken
               );

    //
    // Busy Waiting BathWriteToken signal
    // Busy waiting 120s on all the execute entity being moved to finished queue
    //  
    SctPrint (L"Wait maximumly 120s for Async Batch Write events signaled\n\n");
    Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
    
    IndexI = 0;
    
    while (IndexI < 120 && AsyncWriteFinished == 0) {
      WaitIndex = 0xFF;
      gtBS->WaitForEvent (                   
              1,
              &TimerEvent,
              &WaitIndex
              );
      IndexI++;
      SctPrint(L".");
    }
    
    Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
    SctPrint(L"\n");
  }
 

 
END:
  //
  // Flush all data to physical device first
  //
  if (WriteCaching) {
    BlockIo2->FlushBlocksEx (BlockIo2, &BlkIo2TokenSync);
  }
  
  if (BatchWriteToken.Event != NULL) {
    gtBS->CloseEvent (BatchWriteToken.Event);
  } 
  
  //
  // Verify Async Write Task List Result 
  //
  if (!SctIsListEmpty (&WriteListHeader) && MemoryAllocFail == FALSE) {
    for(ListEntry = SctGetFirstNode(&WriteListHeader); ; ListEntry = SctGetNextNode(&WriteListHeader, ListEntry)) {
      BlockIo2WriteEntity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);

      if (BlockIo2WriteEntity->BlockIo2Token.TransactionStatus == EFI_SUCCESS) {

        BlockIo2WriteEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;

        ReadBufferSync = AllocateAlignedPool(
                           EfiBootServicesData, 
                           BlockIo2WriteEntity->BufferSize, 
                           IoAlign
                           );
        if (ReadBufferSync != NULL) {
          Status = BlockIo2->ReadBlocksEx(
                               BlockIo2,
                               BlockIo2WriteEntity->MediaId,
                               BlockIo2WriteEntity->LBA,
                               &BlkIo2TokenSync,
                               BlockIo2WriteEntity->BufferSize,
                               ReadBufferSync
                               );
          //
          // Compare with write test pattern
          //
          if (Status == EFI_SUCCESS) {
            BlockIo2WriteEntity->ComparedVal = 0;
            for (IndexI = 0; IndexI < BlockIo2WriteEntity->BufferSize; IndexI++) {
              if (ReadBufferSync[IndexI] != ASYNC_WRITE_TEST_PATTERN) {
                BlockIo2WriteEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
                BlockIo2WriteEntity->MemCompared = 1;
                break;
              }
            }                              
          
            //
            // Block IO Memory compare job done
            //
            BlockIo2WriteEntity->MemCompared = TRUE;   
          }
        
          FreeAlignedPool(ReadBufferSync);
          ReadBufferSync = NULL;
        }
      } else {
        BlockIo2WriteEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
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
  // Restore written blocks data & Clean up record list 
  //
  while(!SctIsListEmpty (&RecordListHeader)) {
    BlockIo2RecordEntity = CR(RecordListHeader.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2RecordEntity->ListEntry); 

    if (BlockIo2RecordEntity->Buffer != NULL) {
      //
      // restore all read informations
      //
      Status = BlockIo2->WriteBlocksEx (
                           BlockIo2,
                           BlockIo2RecordEntity->MediaId,
                           BlockIo2RecordEntity->LBA,
                           &BlockIo2RecordEntity->BlockIo2Token,
                           BlockIo2RecordEntity->BufferSize,
                           (VOID*)BlockIo2RecordEntity->Buffer
                           );
      if (Status != EFI_SUCCESS) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Restore blocks fail",
                       L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx",
                       __FILE__,
                       (UINTN)__LINE__,
                       BlockIo2RecordEntity->MediaId,
                       BlockIo2RecordEntity->LBA,
                       BlockIo2RecordEntity->BufferSize
                       );
      }
      
      Status = FreeAlignedPool (BlockIo2RecordEntity->Buffer);
    }
 
    gtBS->FreePool(BlockIo2RecordEntity);
  }

  //
  // Flush all data to physical device first
  //
  if (WriteCaching) {
    BlockIo2->FlushBlocksEx (BlockIo2, &BlkIo2TokenSync);
  }
   
  //
  // Do logging & clean up Write list
  //
  while(!SctIsListEmpty (&WriteListHeader)) {
    BlockIo2WriteEntity = CR(WriteListHeader.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2WriteEntity->ListEntry);

    if (MemoryAllocFail == FALSE) {
      if (BlockIo2WriteEntity->MemCompared == TRUE) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       BlockIo2WriteEntity->AssertionType,
                       gBlockIo2FunctionTestAssertionGuid010,
                       L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Batch Async Write Block with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, LBA=0x%lx, BufferAddr=0x%lx, TransactionStatus=%r, ReadBlocksEx Buffer CompareStatus=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       BlockIo2WriteEntity->BufferSize,
                       BlockIo2WriteEntity->LBA,
                       BlockIo2WriteEntity->Buffer,
                       BlockIo2WriteEntity->BlockIo2Token.TransactionStatus,
                       BlockIo2WriteEntity->ComparedVal
                       );
      } else {
        StandardLib->RecordAssertion (
                       StandardLib,
                       BlockIo2WriteEntity->AssertionType,
                       gBlockIo2FunctionTestAssertionGuid010,
                       L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Batch Async Write Block with proper parameter from valid media",
                       L"%a:%d:BufferSize=%d, LBA=0x%lx, BufferAddr=0x%lx, TransactionStatus=%r",
                       __FILE__,
                       (UINTN)__LINE__,
                       BlockIo2WriteEntity->BufferSize,
                       BlockIo2WriteEntity->LBA,
                       BlockIo2WriteEntity->Buffer,
                       BlockIo2WriteEntity->BlockIo2Token.TransactionStatus
                       );
      }
    }

    //
    // Free aligned Buffer
    //
    if (BlockIo2WriteEntity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2WriteEntity->Buffer);
    
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
      }
    }
 
    gtBS->FreePool(BlockIo2WriteEntity);
  }
 
  return Status;
}


/**
 *   EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx() Function Test 4. Mixed Sync & Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param BlockIo a pointer to Block IO the interface.
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestWriteBlocksExFunctionAutoTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  ) 
{  

  EFI_STATUS                           Status;
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
  UINT8                                *ReadBuffer = NULL;
  UINT8                                *WriteBuffer = NULL;
  UINT32                               BlockNumber;
  UINTN                                IndexI;
  UINTN                                NewBufferSize;
  EFI_LBA                              NewLba;
  EFI_STATUS                           StatusWrite;
  BlockIO2_Task                        *BlockIo2Entity = NULL;
  SCT_LIST_ENTRY                       *ListEntry = NULL;
  UINTN                                WaitIndex;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenSync;
  EFI_BLOCK_IO2_TOKEN                  BlkIo2TokenFlush;

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
  // Sync & Flush Token Init
  //
  BlkIo2TokenSync.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;
  BlkIo2TokenFlush.Event = NULL;
  BlkIo2TokenSync.TransactionStatus = EFI_NOT_READY;

  //
  // Record all write blocks data for recovery first
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (LastBlock != 0)) {
  
  
    SctPrint (L" =================== Record Blocks Info =================== \n\n");
    for (IndexI = 1; IndexI < MAX_NUMBER_OF_WRITE_BLOCK_FUNC_BUFFER; IndexI++) {
      //
      // prepare test data
      // BufferSize will range from BlockSize to MAX_DIFFERENT_BUFFERSIZE_FOR_TEST*BlockSize
      //
      NewBufferSize = IndexI * BlockSize;
  
      for (NewLba = SctRShiftU64(LastBlock, 1); NewLba < SctRShiftU64(LastBlock, 1) + MAX_DIFFERENT_LBA_FOR_TEST; NewLba++) {
        //
        // To avoid the LOG information being destroyed, the LOG information will
        // be recorded after the original data blocks are recovered.
        //
        //
        // Allocate memory for one BlockIo2Entity
        //
        Status = gtBS->AllocatePool(
                         EfiBootServicesData, 
                         sizeof(BlockIO2_Task), 
                         (VOID **) &BlockIo2Entity
                         );
        if (Status != EFI_SUCCESS) {
          goto END;
        } 
        //
        // Add Read info to SyncReadDataList
        //
        SctInsertTailList (&SyncReadDataListHead, &BlockIo2Entity->ListEntry);
        
        BlockIo2Entity->Buffer = NULL;
        BlockIo2Entity->BlockIo2Token.Event = NULL;
        BlockIo2Entity->BlockIo2Token.TransactionStatus = EFI_NOT_READY;
        BlockIo2Entity->Signature = BIO2ENTITY_SIGNATURE;
        BlockIo2Entity->BufferSize = NewBufferSize;
        BlockIo2Entity->LBA = NewLba;
        BlockIo2Entity->MediaId = MediaId;
          
        BlockIo2Entity->Buffer = AllocateAlignedPool(
                                   EfiBootServicesData, 
                                   NewBufferSize, 
                                   IoAlign
                                   );
        if (BlockIo2Entity->Buffer == NULL){
          goto END;
        }
      
        //
        // Sync Call ReadBlocksEx with the specified LBA and BufferSize
        //
        Status = BlockIo2->ReadBlocksEx (
                             BlockIo2,
                             BlockIo2Entity->MediaId,
                             BlockIo2Entity->LBA,
                             &BlockIo2Entity->BlockIo2Token,
                             BlockIo2Entity->BufferSize,
                             (VOID*)BlockIo2Entity->Buffer
                             );
        if (Status != EFI_SUCCESS) {
          goto END;
        }
      }
    }

    if (!SctIsListEmpty (&SyncReadDataListHead)) {
      for(ListEntry = SctGetFirstNode(&SyncReadDataListHead); ; ListEntry = SctGetNextNode(&SyncReadDataListHead, ListEntry)) {
        BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    
        WriteBuffer = NULL;
        WriteBuffer = AllocateAlignedPool(
                        EfiBootServicesData, 
                        BlockIo2Entity->BufferSize, 
                        IoAlign
                        );
        if (WriteBuffer == NULL) {
          goto END_WAIT;
        }
        //
        // Set test data pattern into Write Buffer  
        //
        SctSetMem (WriteBuffer, BlockIo2Entity->BufferSize, ASYNC_WRITE_TEST_PATTERN);
        //
        // Async & Sync Write specified buffer2 differ from buffer to the device
        // write info comes from previous read info list
        //
        StatusWrite = BlockIo2MixedSyncAsyncWriteData(
                        BlockIo2,
                        BlockIo2Entity->MediaId,
                        BlockIo2Entity->LBA,
                        BlockIo2Entity->BufferSize,
                        IoAlign,
                        (VOID*)WriteBuffer
                        );
              
        //
        // Last list node handled
        //
        if (SctIsNodeAtEnd(&SyncReadDataListHead, ListEntry)) {
          break;
        }
      }

      SctPrint (L" ============== Mixed Sync & Async WriteBlocksEx call finshed ============== \n\n");
      
END_WAIT:      
      //
      // if write-cached, then flush the data to physical device
      //
      if (WriteCaching) {
        BlockIo2->FlushBlocksEx (BlockIo2, &BlkIo2TokenSync);
      }

      //
      // Busy waiting 120s on all the execute entity being moved to finished queue
      //  
      SctPrint (L"Wait maximumly 120s for all Async Write events signaled\n\n");
      Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
      IndexI = 0;
      
      SctAcquireLock (&gMixedWriteQueueLock);
      while (!SctIsListEmpty (&MixedWriteExecuteListHead) && IndexI < 120) {
        SctReleaseLock (&gMixedWriteQueueLock);
        
        gtBS->WaitForEvent (   
                1,
                &TimerEvent,
                &WaitIndex
                );
        IndexI++;
        SctPrint (L".");
        SctAcquireLock (&gMixedWriteQueueLock);
      }
      SctReleaseLock (&gMixedWriteQueueLock);
  
      Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
      SctPrint(L"\n");
    }
  }

END:
  //
  // Flush all data to physical device first
  //
  if (WriteCaching) {
    BlockIo2->FlushBlocksEx (BlockIo2, &BlkIo2TokenSync);
  }

  //
  // Compare all Sync Write results since Sync results always follows Async call
  //
  if (!SctIsListEmpty (&MixedSyncWriteListHead)) {
    for(ListEntry = SctGetFirstNode(&MixedSyncWriteListHead); ; ListEntry = SctGetNextNode(&MixedSyncWriteListHead, ListEntry)) {
      BlockIo2Entity = CR(ListEntry, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
  
      //
      // Check written data of each successful  Block IO2 Sync Write execution 
      //
      BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_PASSED;

      ReadBuffer = AllocateAlignedPool(
                     EfiBootServicesData, 
                     BlockIo2Entity->BufferSize, 
                     IoAlign
                     );
      if (ReadBuffer != NULL) {
        Status = BlockIo2->ReadBlocksEx(
                             BlockIo2,
                             BlockIo2Entity->MediaId,
                             BlockIo2Entity->LBA,
                             &BlkIo2TokenSync,
                             BlockIo2Entity->BufferSize,
                             ReadBuffer
                             );
        //
        // Compare with write test pattern
        //
        if (Status == EFI_SUCCESS) {
          BlockIo2Entity->ComparedVal = 0;
          for (IndexI = 0; IndexI < BlockIo2Entity->BufferSize; IndexI++) {
            if (ReadBuffer[IndexI] != SYNC_WRITE_TEST_PATTERN) {
              BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
              BlockIo2Entity->ComparedVal = 1;
              break;
            }
          }                              
        
          //
          // Block IO 2 Read Memory compare job done
          //
          BlockIo2Entity->MemCompared = TRUE;   
        }
      
        FreeAlignedPool(ReadBuffer);
        ReadBuffer = NULL;
      } else {
        BlockIo2Entity->AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      // Last list node handled
      //
      if (SctIsNodeAtEnd(&MixedSyncWriteListHead, ListEntry)) {
        break;
      }
    }
  }

  //
  // Clean up & free all record resources
  //
  SctPrint (L"============ Restore All written blocks ============ \n");
  while (!SctIsListEmpty (&SyncReadDataListHead)) {
    BlockIo2Entity = CR(SyncReadDataListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);

    if (BlockIo2Entity->Buffer != NULL) {
      //
      // restore all read informations
      //
      Status = BlockIo2->WriteBlocksEx (
                           BlockIo2,
                           BlockIo2Entity->MediaId,
                           BlockIo2Entity->LBA,
                           &BlockIo2Entity->BlockIo2Token,
                           BlockIo2Entity->BufferSize,
                           (VOID*)BlockIo2Entity->Buffer
                           );
      if (Status != EFI_SUCCESS) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Restore blocks fail",
                       L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx",
                       __FILE__,
                       (UINTN)__LINE__,
                       BlockIo2Entity->MediaId,
                       BlockIo2Entity->LBA,
                       BlockIo2Entity->BufferSize
                       );
      }
      if (BlockIo2Entity->Buffer != NULL) {
        Status = FreeAlignedPool (BlockIo2Entity->Buffer);
      }
    }

    gtBS->FreePool(BlockIo2Entity);
  }
  
  //
  // Flush all data to physical device 
  //
  if (WriteCaching) {
    BlockIo2->FlushBlocksEx (BlockIo2, &BlkIo2TokenSync);
  }
  SctPrint (L"============ Restore All written blocks finshed ============ \n");
    
  //
  // Record All Failed Async Write case results
  //
  while (!SctIsListEmpty (&MixedWriteFailListHead)) {
    BlockIo2Entity = CR(MixedWriteFailListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
       
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gBlockIo2FunctionTestAssertionGuid014,
                   L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Mixed Sync & Async Write Block with proper parameter from valid media"    \
                   L"Async Read Failed",
                   L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   BlockIo2Entity->MediaId,
                   BlockIo2Entity->LBA,
                   BlockIo2Entity->BufferSize,
                   BlockIo2Entity->Buffer
                   );
    
    //
    // Free aligned Buffer
    //
    if (BlockIo2Entity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    }
    gtBS->FreePool(BlockIo2Entity);
  
  }  
  
  //
  // Record All Mixed  Sync Async write finshed test logs
  //  
  while (!SctIsListEmpty (&MixedSyncWriteListHead)) {
    BlockIo2Entity = CR(MixedSyncWriteListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
   
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);
   
    
    if (BlockIo2Entity->MemCompared == TRUE) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     BlockIo2Entity->AssertionType,
                     gBlockIo2FunctionTestAssertionGuid015,
                     L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Mixed Sync & Async Write Block with proper parameter to valid media "    \
                     L"SYNC_WRITE_TEST_PATTERN 0xAB",
                     L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx ReadBlocksEx Buffer CompareStatus=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BlockIo2Entity->MediaId,
                     BlockIo2Entity->LBA,
                     BlockIo2Entity->BufferSize,
                     BlockIo2Entity->Buffer,
                     BlockIo2Entity->ComparedVal
                     );
    } else {
      StandardLib->RecordAssertion (
                     StandardLib,
                     BlockIo2Entity->AssertionType,
                     gBlockIo2FunctionTestAssertionGuid015,
                     L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Mixed Sync & Async Write Block with proper parameter to valid media "    \
                     L"SYNC_WRITE_TEST_PATTERN 0xAB",
                     L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx",
                     __FILE__,
                     (UINTN)__LINE__,
                     BlockIo2Entity->MediaId,
                     BlockIo2Entity->LBA,
                     BlockIo2Entity->BufferSize,
                     BlockIo2Entity->Buffer
                     );
    }
   
    //
    // Free aligned Buffer
    //
    if (BlockIo2Entity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    }
    gtBS->FreePool(BlockIo2Entity);
    
  }  

  //
  // Mixed Sync Async function failed test logs
  // 
  while (!SctIsListEmpty (&MixedSyncWriteFailListHead)) {
    BlockIo2Entity = CR(MixedSyncWriteFailListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);

     StandardLib->RecordAssertion (
                    StandardLib,
                    EFI_TEST_ASSERTION_FAILED,
                    gBlockIo2FunctionTestAssertionGuid016,
                    L"EFI_BLOCK_IO2_PROTOCOL.WriteBlocksEx - Mixed Sync & Async Write Block with proper parameter from valid media"     \
                    L"Sync Read Failed",
                    L"%a:%d: MediaId=%d LBA=0x%lx BufferSize=0x%lx BufferAddr=0x%lx ",
                    __FILE__,
                    (UINTN)__LINE__,
                    BlockIo2Entity->MediaId,
                    BlockIo2Entity->LBA,
                    BlockIo2Entity->BufferSize,
                    BlockIo2Entity->Buffer
                    );
    if (BlockIo2Entity->Buffer != NULL) {
      FreeAlignedPool(BlockIo2Entity->Buffer);
    }
 
    gtBS->FreePool(BlockIo2Entity);
  }
  
 
  //
  // Free All finished Async Write finshed test entity
  //  
  SctAcquireLock (&gMixedWriteQueueLock);
  while (!SctIsListEmpty (&MixedWriteFinishListHead)) {
    BlockIo2Entity = CR(MixedWriteFinishListHead.ForwardLink, BlockIO2_Task, ListEntry, BIO2ENTITY_SIGNATURE);
    SctRemoveEntryList (&BlockIo2Entity->ListEntry);

    SctReleaseLock (&gMixedWriteQueueLock);
   
    
    gtBS->CloseEvent(BlockIo2Entity->BlockIo2Token.Event);
    //
    // Free aligned Buffer
    //
    if (BlockIo2Entity->Buffer != NULL) {
      Status = FreeAlignedPool (BlockIo2Entity->Buffer);
    }
    gtBS->FreePool(BlockIo2Entity);
   
    
    SctAcquireLock (&gMixedWriteQueueLock);
  }  
  SctReleaseLock (&gMixedWriteQueueLock);
 
  
  return EFI_SUCCESS;
}
/**
 *  Entrypoint for EFI_BLOCK_IO2_PROTOCOL.FlushBlocksEx() Function Test.
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
BBTestFlushBlocksExFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                           Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib = NULL;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2 = NULL;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath = NULL;
  CHAR16                               *DevicePathStr = NULL;

  
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
  // Async call to test Block IO 2 FushBlocksEx
  //
  BBTestFushBlocksExFunctionAutoTestCheckpoint1 (StandardLib, BlockIo2);
   
  //
  // Sync call to test Block IO 2 FushBlocksEx
  //
  BBTestFushBlocksExFunctionAutoTestCheckpoint2 (StandardLib, BlockIo2);

  return EFI_SUCCESS;
}

/**
 *   EFI_BLOCK_IO2_PROTOCOL.FushBlocksEx() Function Test 1. Async mode test
 *  @param StandardLib a point to standard test lib
 *  @param BlockIo a pointer to Block IO the interface.
 *  @param BlockIo 2 a pointer to Block IO2 to be tested.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestFushBlocksExFunctionAutoTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_BLOCK_IO2_TOKEN                  BlockIo2TokenBuffer[4];
  BOOLEAN                              MediaPresent;
  BOOLEAN                              ReadOnly;
  BOOLEAN                              WriteCaching;
  EFI_STATUS                           Status;
  UINTN                                IndexI;
  UINTN                                WaitIndex;
  UINTN                                Time;
  
  
  MediaPresent   = BlockIo2->Media->MediaPresent;
  ReadOnly       = BlockIo2->Media->ReadOnly;
  WriteCaching   = BlockIo2->Media->WriteCaching;
  //
  // BlockIo2Token initialization
  //
  for (IndexI = 0; IndexI < 4; IndexI++) {
    AsyncFlushFinished[IndexI] = 0;
    BlockIo2TokenBuffer[IndexI].Event = NULL;
    BlockIo2TokenBuffer[IndexI].TransactionStatus = EFI_NOT_READY;
    Status = gtBS->CreateEvent (
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     (EFI_EVENT_NOTIFY) BlockIo2FinishNotifyFunc,
                     &AsyncFlushFinished[IndexI],
                     &BlockIo2TokenBuffer[IndexI].Event
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
  }

  if ((MediaPresent == TRUE) && (ReadOnly == FALSE) && (WriteCaching == TRUE)) {
    //
    // Perform Async Flush Ex
    //
    for (IndexI = 0; IndexI < 4; IndexI++){
      BlockIo2->FlushBlocksEx (BlockIo2, &BlockIo2TokenBuffer[IndexI]);
    }

    //
    // Busy waiting for all the flush blocks event signaled
    //
    SctPrint (L"Wait maximumly 60s for all Async Flush events signaled\n\n");
    
    Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
    Time = 0;

    while(Time < 60) {
      gtBS->WaitForEvent (   
              1,
              &TimerEvent,
              &WaitIndex
              );
      for (IndexI = 0; AsyncFlushFinished[IndexI] == 1 && IndexI < 4; IndexI++) {
        ;
      }
      if (IndexI == 4) {
        break;
      }

      Time++;
      SctPrint(L".");
    }
    SctPrint(L"\n");

    //
    // check all events have been siganaled & status been changed
    //
    if (IndexI == 4) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      for (IndexI = 0; IndexI < 4; IndexI++){
        if (BlockIo2TokenBuffer[IndexI].TransactionStatus != EFI_SUCCESS) {
           AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
    } else {
       AssertionType = EFI_TEST_ASSERTION_FAILED;
    } 
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gBlockIo2FunctionTestAssertionGuid019,
                   L"EFI_BLOCK_IO2_PROTOCOL.FushBlocksEx - Async Flush Block with proper parameter to valid media",
                   L"%a:%d: %d Events have been successfully signaled Status:=%r TransactionStatus:=%r returned",
                   __FILE__,
                   (UINTN)__LINE__,
                   4,
                   EFI_SUCCESS,
                   BlockIo2TokenBuffer[IndexI].TransactionStatus
                   );
    
    Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  }

  
END:
  for (IndexI = 0; IndexI < 4; IndexI++) {
    if (BlockIo2TokenBuffer[IndexI].Event != NULL) {
      gtBS->CloseEvent (BlockIo2TokenBuffer[IndexI].Event);
    }
  }
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFushBlocksExFunctionAutoTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_BLOCK_IO2_PROTOCOL                *BlockIo2
  )
{
  //
  // Currently Sync Flush Blocks Ex call do not need test
  //
  return EFI_SUCCESS;
}



/**
 *  Entrypoint for EFI_BLOCK_IO2_PROTOCOL.MediaInfo Integrity Check Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 
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
  EFI_STATUS                           Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib = NULL;
  EFI_BLOCK_IO_PROTOCOL                *BlockIo = NULL;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2 = NULL;
  EFI_BLOCK_IO2_PROTOCOL               *BlockIo2Temp = NULL;
  EFI_DEVICE_PATH_PROTOCOL	           *DevicePath = NULL;
  CHAR16                               *DevicePathStr = NULL;
  UINTN                                Index;
  UINTN                                NoHandles;
  EFI_HANDLE                           *HandleBuffer = NULL;
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
  // Locate Block IO protocol on same handler for test
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiBlockIo2ProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  for (Index = 0; Index < NoHandles; Index++) {
     Status = gtBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gBlackBoxEfiBlockIo2ProtocolGuid,
                      (VOID **) &BlockIo2Temp
                      );
     if (Status == EFI_SUCCESS && BlockIo2Temp == BlockIo2) {
       Status = gtBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gBlackBoxEfiBlockIoProtocolGuid,
                        (VOID **) &BlockIo
                        );
       if (Status != EFI_SUCCESS) {
         BlockIo = NULL;
       }
       break;
    }
 
  }

  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  if (BlockIo->Revision >= EFI_BLOCK_IO_PROTOCOL_REVISION2 && BlockIo2->Media->LogicalPartition) {
    if (BlockIo2->Media->LogicalBlocksPerPhysicalBlock == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBlockIo2FunctionTestAssertionGuid021,
                 L"EFI_BLOCK_IO2_PROTOCOL.Media - LogicalBlocksPerPhysicalBlock should be 0 when LogicalPartition is TRUE ",
                 L"%a:%d Media->LogicalBlocksPerPhysicalBlock %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 BlockIo2->Media->LogicalBlocksPerPhysicalBlock
                 );
  }

  if (BlockIo->Revision >= EFI_BLOCK_IO_PROTOCOL_REVISION3 && BlockIo2->Media->LogicalPartition) {
    if (BlockIo2->Media->OptimalTransferLengthGranularity == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gBlockIo2FunctionTestAssertionGuid022,
                 L"EFI_BLOCK_IO2_PROTOCOL.Media - OptimalTransferLengthGranularity should be 0 when LogicalPartition is TRUE ",
                 L"%a:%d Media->OptimalTransferLengthGranularity %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 BlockIo2->Media->OptimalTransferLengthGranularity
                 );
  } 
  
  return EFI_SUCCESS;
}

