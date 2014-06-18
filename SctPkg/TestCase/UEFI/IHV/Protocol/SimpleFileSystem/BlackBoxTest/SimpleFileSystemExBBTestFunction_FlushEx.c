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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    SimpleFileSystemExTestFunction_FlushEx.c

Abstract:
    for EFI Simple File System Protocol and EFI_FILE Protocol's Function Test

--*/


#include "SimpleFileSystemBBTest.h"

//
//
//
typedef struct {
  UINTN                 Signature;
  EFI_FILE_PROTOCOL     *FileIo;
  EFI_FILE_IO_TOKEN     FileIoToken;
  EFI_TPL               Tpl;
  EFI_LIST_ENTRY        ListEntry;     
  EFI_STATUS            StatusAsync;
  EFI_TEST_ASSERTION    AssertionType;
} FileIoFlush_Task;

//
//CheckPoints
//
EFI_STATUS
BBTestFlushExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
BBTestFlushExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
BBTestFlushExBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
BBTestFlushExBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
InternalGetInfoFileIo2 (
  EFI_FILE_PROTOCOL    *FileHandle,
  VOID                 **InfoBuffer,
  UINTN                *BufferSize,
  EFI_GUID             *InfoId
  );

EFI_STATUS
InternalSetFileSizeFileIo2 (
  EFI_FILE_PROTOCOL    *FileHandle,
  UINT64               FileSize
  );

//
// Async Flush File Queue
//
EFI_LIST_ENTRY  AsyncFlushFileExecuteListHead = INITIALIZE_LIST_HEAD_VARIABLE(AsyncFlushFileExecuteListHead);
EFI_LIST_ENTRY  AsyncFlushFileFinishListHead  = INITIALIZE_LIST_HEAD_VARIABLE(AsyncFlushFileFinishListHead);
EFI_LIST_ENTRY  AsyncFlushFileFailListHead    = INITIALIZE_LIST_HEAD_VARIABLE(AsyncFlushFileFailListHead);

//
// Async Flush File lock
//
FLOCK  gAsyncFlushFileQueueLock = EFI_INITIALIZE_LOCK_VARIABLE (EFI_TPL_CALLBACK);


//
// Async Flush Dir Queue
//
EFI_LIST_ENTRY  AsyncFlushDirExecuteListHead = INITIALIZE_LIST_HEAD_VARIABLE(AsyncFlushDirExecuteListHead);
EFI_LIST_ENTRY  AsyncFlushDirFinishListHead  = INITIALIZE_LIST_HEAD_VARIABLE(AsyncFlushDirFinishListHead);
EFI_LIST_ENTRY  AsyncFlushDirFailListHead    = INITIALIZE_LIST_HEAD_VARIABLE(AsyncFlushDirFailListHead);

//
// Async Flush Dir lock
//
FLOCK  gAsyncFlushDirQueueLock = EFI_INITIALIZE_LOCK_VARIABLE (EFI_TPL_CALLBACK);



//
//Async Flush File NotifyFunc
//
VOID
EFIAPI FileIoFlushFileNotifyFunc (
  IN  EFI_EVENT    Event,
  IN  VOID         *Context
  )
{
  FileIoFlush_Task    *FileIoEntity;
  
  FileIoEntity = (FileIoFlush_Task *)Context;

  //
  // Remove entity from FlushFileExecuteListHead &  add entity to FlushFileFinishListHead
  // All FileIoFlushFile Notify function run at Call Back level only once, So no locks required
  //
  AcquireLock(&gAsyncFlushFileQueueLock);
  RemoveEntryList(&FileIoEntity->ListEntry);
  InsertTailList(&AsyncFlushFileFinishListHead, &FileIoEntity->ListEntry);
  ReleaseLock(&gAsyncFlushFileQueueLock);
}


/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.FlushEx() function abstraction interface
 *  @param FileIo  a pointer to File Io to be tested.
 *  @param Tpl the Tpl level
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncFlushFileData (
  IN EFI_FILE_PROTOCOL    *FileIo,
  IN EFI_TPL              Tpl
)
{

  EFI_STATUS          Status;
  FileIoFlush_Task    *FileIoEntity;
  EFI_TPL             OldTpl;

  ASSERT(FileIo != NULL);

  FileIoEntity = NULL;
  
  //
  // Allocate memory for one FileIoFlushFileEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoFlush_Task), 
                   &FileIoEntity);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  // FileIoToken initialization
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   FileIoFlushFileNotifyFunc,
                   FileIoEntity,
                   &FileIoEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(FileIoEntity);
    return Status;
  }

  FileIoEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoEntity->FileIo                 = FileIo;
  FileIoEntity->Tpl                    = Tpl;
  FileIoEntity->FileIoToken.Status     = EFI_NOT_READY;

  AcquireLock(&gAsyncFlushFileQueueLock);
  InsertTailList(&AsyncFlushFileExecuteListHead, &FileIoEntity->ListEntry);
  ReleaseLock(&gAsyncFlushFileQueueLock);
  
  //
  // Async FlushEx Call
  //
  OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  Status = FileIo->FlushEx (
                     FileIoEntity->FileIo,
                     &FileIoEntity->FileIoToken
                     );
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    AcquireLock(&gAsyncFlushFileQueueLock);
    RemoveEntryList(&FileIoEntity->ListEntry);
    InsertTailList(&AsyncFlushFileFailListHead, &FileIoEntity->ListEntry);    
    ReleaseLock(&gAsyncFlushFileQueueLock);
  }

  //
  // Record execution Info to File IO  entity 
  //
  FileIoEntity->StatusAsync = Status;

  return Status;
}

//
//Async Flush Dir NotifyFunc
//
VOID
EFIAPI FileIoFlushDirNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  FileIoFlush_Task    *FileIoEntity;
  
  FileIoEntity = (FileIoFlush_Task *)Context;

  //
  // Remove entity from FlushDirExecuteListHead &  add entity to FlushDirFinishListHead
  // All FileIoFlushDir Notify function run at Call Back level only once, So no locks required
  //
  AcquireLock(&gAsyncFlushDirQueueLock);
  RemoveEntryList(&FileIoEntity->ListEntry);
  InsertTailList(&AsyncFlushDirFinishListHead, &FileIoEntity->ListEntry);
  ReleaseLock(&gAsyncFlushDirQueueLock);
}


/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.FlushEx() function abstraction interface
 *  @param FileIo  a pointer to File Io to be tested.
 *  @param Buffer a pointer to Write data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncFlushDirData (
  IN EFI_FILE_PROTOCOL                 *FileIo,
  IN EFI_TPL                           Tpl
)
{

  EFI_STATUS                         Status;
  FileIoFlush_Task                   *FileIoEntity = NULL;
  EFI_TPL                            OldTpl;

  ASSERT(FileIo != NULL);
  
  //
  // Allocate memory for one FileIoFlushDirEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoFlush_Task), 
                   &FileIoEntity);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  // FileIoToken initialization
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   FileIoFlushDirNotifyFunc,
                   FileIoEntity,
                   &FileIoEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(FileIoEntity);
    FileIoEntity = NULL;
    return Status;
  }

  FileIoEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoEntity->FileIo                 = FileIo;
  FileIoEntity->Tpl                    = Tpl;
  FileIoEntity->FileIoToken.Status     = EFI_NOT_READY;

  AcquireLock(&gAsyncFlushDirQueueLock);
  InsertTailList(&AsyncFlushDirExecuteListHead, &FileIoEntity->ListEntry);
  ReleaseLock(&gAsyncFlushDirQueueLock);
  
  //
  // Async FlushEx Call
  //
  OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  Status = FileIo->FlushEx (
                     FileIoEntity->FileIo,
                     &FileIoEntity->FileIoToken
                     );
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    AcquireLock(&gAsyncFlushDirQueueLock);
    RemoveEntryList(&FileIoEntity->ListEntry);
    InsertTailList(&AsyncFlushDirFailListHead, &FileIoEntity->ListEntry);    
    ReleaseLock(&gAsyncFlushDirQueueLock);
    FileIoEntity->StatusAsync        = Status;
    return Status;
  }

  //
  // Record execution Info to File IO  entity 
  //
  FileIoEntity->StatusAsync = Status;

  return Status;
}



/**
 *  @brief For FlushEx() basic test
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.15
//
EFI_STATUS
BBTestFlushExBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem;

  //
  // init
  //
  SimpleFileSystem = (EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 5.1.15.2.1  Async FlushEx() a normal file.
  //
  BBTestFlushExBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.1.15.2.2  Sync FlushEx() a normal file.
  //
  BBTestFlushExBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);
  


  //
  // 5.1.15.2.3  Async FlushEx() a directory.
  //
  BBTestFlushExBasicTestCheckpoint3 (StandardLib, SimpleFileSystem);

  //
  // 5.1.15.2.4  Sync FlushEx() a directory.
  //
  BBTestFlushExBasicTestCheckpoint4 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestFlushExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS           Status;
  EFI_FILE_PROTOCOL    *Root;
  UINTN                TplIndex;
  CHAR16               FileName[100];
  EFI_FILE_PROTOCOL    *FileHandle;
  UINT8                *Buffer;
  UINTN                BufferSize;
  UINTN                IndexI;
  UINTN                WaitIndex;
  EFI_LIST_ENTRY       *ListEntry;
  FileIoFlush_Task     *FileIoEntity;

  Root         = NULL;
  FileHandle   = NULL;
  Buffer       = NULL;
  ListEntry    = NULL;
  FileIoEntity = NULL;

  //
  // init
  //
  EfiStrCpy (FileName, L"BBTestFlushExBasicTestCheckpoint1_File");

  Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"OpenVolume fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  if (Root->Revision != EFI_FILE_PROTOCOL_REVISION2) {
    Root->Close(Root);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Async File IO is not supported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }

  //
  // allocate buffer for write
  //
  BufferSize = 200;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
    return Status;
  }

  //
  // create the file
  //
  Status = Root->Open (Root, &FileHandle, FileName, CREATE_FILE_MODE, 0);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool(Buffer);
    Root->Close(Root);    
    return Status;
  }

  //
  // set the Buffer content 
  //
  gtBS->SetMem (Buffer, BufferSize, 0x31);

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
 
    //
    // reset file size
    //
    Status = InternalSetFileSizeFileIo2 (FileHandle, 0);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"set file position fail",
                     L"%a:%d: Status - %r, filesize - 0",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
    //
    // write data to the file
    //
    BufferSize = 200;
    Status = FileHandle->Write (FileHandle, &BufferSize, Buffer);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Write to file fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
  
    Status = FileIoAsyncFlushFileData(
               FileHandle,
               TplArray[TplIndex]
               );
  }
    
  
  Print (L" ================== Async FlushEx call finshed ================== \n\n");
  
  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Write events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
    
  AcquireLock(&gAsyncFlushFileQueueLock);
  while (!IsListEmpty(&AsyncFlushFileExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncFlushFileQueueLock);
    
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
  
    Print (L".");
    AcquireLock(&gAsyncFlushFileQueueLock);
  }
  ReleaseLock(&gAsyncFlushFileQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");

  //
  // clear all File IO events from gFlushFileFinishQueue 
  // Here no logs should be wrote to this file device to keep data intact
  //
  AcquireLock(&gAsyncFlushFileQueueLock);
    if (!IsListEmpty(&AsyncFlushFileFinishListHead)) {
      for(ListEntry = GetFirstNode(&AsyncFlushFileFinishListHead); ; ListEntry = GetNextNode(&AsyncFlushFileFinishListHead, ListEntry)) {
        FileIoEntity = CR(ListEntry, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
        ReleaseLock(&gAsyncFlushFileQueueLock);

        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
        //
        // Check & record every File Io execution entity status 
        //
        if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
            && FileIoEntity->StatusAsync == EFI_SUCCESS) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        }
        AcquireLock(&gAsyncFlushFileQueueLock);
        //
        // Last list node handled
        //
        if (IsNodeAtEnd(&AsyncFlushFileFinishListHead, ListEntry)) {
           break;
        } 

      }
    }
  ReleaseLock(&gAsyncFlushFileQueueLock);
    
  //
  // Record All Finished Flush case results
  //
  AcquireLock(&gAsyncFlushFileQueueLock);
  while (!IsListEmpty(&AsyncFlushFileFinishListHead)) {
    FileIoEntity = CR(AsyncFlushFileFinishListHead.ForwardLink, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncFlushFileQueueLock);

    FileHandle = FileIoEntity->FileIo;

    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid017,
                   L"FlushEx() Basic Test - checkpoint1----Async",
                   L"%a:%d: Tpl - %d,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
      
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    gtBS->FreePool(FileIoEntity);
    AcquireLock(&gAsyncFlushFileQueueLock);
  }
  ReleaseLock(&gAsyncFlushFileQueueLock);

  //
  // If FlushFileFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncFlushFileQueueLock);
  while(!IsListEmpty(&AsyncFlushFileFailListHead)) {
    FileIoEntity = CR(AsyncFlushFileFailListHead.ForwardLink, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncFlushFileQueueLock);

    FileHandle = FileIoEntity->FileIo;

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid018,
                   L"FlushEx() Basic Test - checkpoint1---Async",
                   L"%a:%d:Tpl - %d,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);     

     gtBS->FreePool(FileIoEntity);
     AcquireLock(&gAsyncFlushFileQueueLock);
  }
  ReleaseLock(&gAsyncFlushFileQueueLock);
    
  //
  // If FlushFileExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncFlushFileQueueLock);
  if (!IsListEmpty(&AsyncFlushFileExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncFlushFileExecuteListHead); ; ListEntry = GetNextNode(&AsyncFlushFileExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncFlushFileQueueLock);


      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid019,
                     L"FlushEx() Basic Test - checkpoint1----Async",
                     L"%a:%d:Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl
                     );

      AcquireLock(&gAsyncFlushFileQueueLock);
      if (IsNodeAtEnd(&AsyncFlushFileExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncFlushFileQueueLock);

  FileHandle->Delete(FileHandle);
  FileHandle = NULL;
  gtBS->FreePool(Buffer);
  Root->Close(Root);  
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestFlushExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE_PROTOCOL         *Root;
  UINTN                     TplIndex;
  CHAR16                    FileName[100];
  EFI_FILE_PROTOCOL         *FileHandle;
  UINT8                     *Buffer;
  UINTN                     BufferSize;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;

  Root       = NULL;
  FileHandle = NULL;
  Buffer     = NULL;
  //
  // init
  //
  EfiStrCpy (FileName, L"BBTestFlushExBasicTestCheckpoint2_File");
  
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;
  
  Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"OpenVolume fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  if (Root->Revision != EFI_FILE_PROTOCOL_REVISION2) {
    Root->Close(Root);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Async File IO is not supported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }


  //
  // allocate buffer for write
  //
  BufferSize = 200;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID**)&Buffer);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
	return Status;
  }	

  //
  // set the Buffer content 
  //
  gtBS->SetMem (Buffer, BufferSize, 0x31);  

  //
  // create the file
  //
  Status = Root->Open (Root, &FileHandle, FileName, CREATE_FILE_MODE, 0);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (Buffer);
    Root->Close(Root);   
    return Status;
  }


  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
 
    //
    // reset file size
    //
    Status = InternalSetFileSizeFileIo2 (FileHandle, 0);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"set file position fail",
                     L"%a:%d: Status - %r, filesize - 0",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
    //
    // write data to the file
    //
    BufferSize = 200;
    Status = FileHandle->Write (FileHandle, &BufferSize, Buffer);

    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Write to file fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
    
    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = FileHandle->FlushEx(
               FileHandle,
               &FileIoTokenSync
               );
    gtBS->RestoreTPL (OldTpl);
    
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    //
    // Check & record every File Io execution entity status 
    //
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } 
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid020,
                   L"FlushEx() Basic Test - checkpoint2----Sync",
                   L"%a:%d: Tpl - %d,Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[TplIndex],
                   Status
                   );  
  }
  
  FileHandle->Delete(FileHandle);
  FileHandle = NULL;
  gtBS->FreePool(Buffer);
  Root->Close(Root); 

  return Status;
}
  
  
EFI_STATUS
BBTestFlushExBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE_PROTOCOL         *Root;
  UINTN                     TplIndex;
  CHAR16                    DirName[100];
  CHAR16                    FileName[TPL_ARRAY_SIZE][100];
  EFI_FILE_PROTOCOL         *DirHandle;
  EFI_FILE_PROTOCOL         *FileHandle[TPL_ARRAY_SIZE];
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  EFI_LIST_ENTRY            *ListEntry;
  FileIoFlush_Task          *FileIoEntity;

  Root          = NULL;
  DirHandle     = NULL;
  FileHandle[0] = NULL;
  FileHandle[1] = NULL;
  ListEntry     = NULL;
  FileIoEntity  = NULL;
  //
  // init
  //
  EfiStrCpy (DirName, L"BBTestFlushExBasicTestCheckpoint3_Dir");
  EfiStrCpy (FileName[0], L"BBTestFlushExBasicTestCheckpoint3_File_0");
  EfiStrCpy (FileName[1], L"BBTestFlushExBasicTestCheckpoint3_File_1");

  Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"OpenVolume fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

    
  if (Root->Revision != EFI_FILE_PROTOCOL_REVISION2) {
    Root->Close(Root);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Async File IO is not supported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }
  
  //
  // create the Dir
  //
  Status = Root->Open (Root, &DirHandle, DirName, CREATE_FILE_MODE, EFI_FILE_DIRECTORY);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create dir fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
    return Status;
  }

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
    //
    // create the file
    //
    Status = Root->Open (DirHandle, &FileHandle[TplIndex], FileName[TplIndex], CREATE_FILE_MODE, 0);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Create file fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }
   
    Status = FileIoAsyncFlushDirData(
               DirHandle,
               TplArray[TplIndex]
               );
    
  }
    
  Print (L" ================== Async FlushEx call finshed ================== \n\n");

  //
  // Busy waiting 120s on all the execute entity being moved to finished queue
  //  
  Print (L"Wait maximumly 120s for all Async Write events signaled\n\n");
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);
  IndexI = 0;
    
  AcquireLock(&gAsyncFlushDirQueueLock);
  while (!IsListEmpty(&AsyncFlushDirExecuteListHead) && IndexI < 120) {
    ReleaseLock(&gAsyncFlushDirQueueLock);
    
    gtBS->WaitForEvent (                   
            1,
            &TimerEvent,
            &WaitIndex
            );
    IndexI++;
  
    Print (L".");
    AcquireLock(&gAsyncFlushDirQueueLock);
  }
  ReleaseLock(&gAsyncFlushDirQueueLock);
  
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  Print(L"\n");
 
  //
  // clear all File IO events from gFlushDirFinishQueue 
  // Here no logs should be wrote to this file device to keep data intact
  //
  AcquireLock(&gAsyncFlushDirQueueLock);
    if (!IsListEmpty(&AsyncFlushDirFinishListHead)) {
      for(ListEntry = GetFirstNode(&AsyncFlushDirFinishListHead); ; ListEntry = GetNextNode(&AsyncFlushDirFinishListHead, ListEntry)) {
        FileIoEntity = CR(ListEntry, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
        ReleaseLock(&gAsyncFlushDirQueueLock);

        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
        //
        // Check & record every File Io execution entity status 
        //
        if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS
            && FileIoEntity->StatusAsync == EFI_SUCCESS) {
                FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
        }
        AcquireLock(&gAsyncFlushDirQueueLock);
        //
        // Last list node handled
        //
        if (IsNodeAtEnd(&AsyncFlushDirFinishListHead, ListEntry)) {
          break;
        } 
      }
    }
  ReleaseLock(&gAsyncFlushDirQueueLock);
    
  //
  // Record All Finished Flush case results
  //
  AcquireLock(&gAsyncFlushDirQueueLock);
  while (!IsListEmpty(&AsyncFlushDirFinishListHead)) {
    FileIoEntity = CR(AsyncFlushDirFinishListHead.ForwardLink, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncFlushDirQueueLock);
	
    StandardLib->RecordAssertion (
                   StandardLib,
                   FileIoEntity->AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid021,
                   L"FlushEx() Basic Test - checkpoint3----Async",
                   L"%a:%d: Tpl - %d,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
      
    gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
    
    gtBS->FreePool(FileIoEntity);
    AcquireLock(&gAsyncFlushDirQueueLock);
  }
  ReleaseLock(&gAsyncFlushDirQueueLock);
  

  //
  // If FlushDirFailListHead is not empty, which means some Async Calls are wrong 
  //
  AcquireLock(&gAsyncFlushDirQueueLock);
  while(!IsListEmpty(&AsyncFlushDirFailListHead)) {
    FileIoEntity = CR(AsyncFlushDirFailListHead.ForwardLink, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
    RemoveEntryList(&FileIoEntity->ListEntry);
    ReleaseLock(&gAsyncFlushDirQueueLock);

    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid022,
                   L"FlushEx() Basic Test - checkpoint3---Async",
                   L"%a:%d:Tpl - %d,StatusAsync=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIoEntity->Tpl,
                   FileIoEntity->StatusAsync
                   );
     gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
   
     gtBS->FreePool(FileIoEntity);
       
     AcquireLock(&gAsyncFlushDirQueueLock);
  }
  ReleaseLock(&gAsyncFlushDirQueueLock);
    
  //
  // If FlushDirExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  AcquireLock(&gAsyncFlushDirQueueLock);
  if (!IsListEmpty(&AsyncFlushDirExecuteListHead)) {
    for(ListEntry = GetFirstNode(&AsyncFlushDirExecuteListHead); ; ListEntry = GetNextNode(&AsyncFlushDirExecuteListHead, ListEntry)) {
      FileIoEntity = CR(ListEntry, FileIoFlush_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      ReleaseLock(&gAsyncFlushDirQueueLock);
    
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid023,
                     L"FlushEx() Basic Test - checkpoint3----Async",
                     L"%a:%d:Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->Tpl
                     );

      AcquireLock(&gAsyncFlushDirQueueLock);
      if (IsNodeAtEnd(&AsyncFlushDirExecuteListHead, ListEntry)) {
        break;
      }
    }
  }
  ReleaseLock(&gAsyncFlushDirQueueLock);

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
  	if (FileHandle[TplIndex] != NULL)
      FileHandle[TplIndex]->Delete(FileHandle[TplIndex]);
    FileHandle[TplIndex] = NULL;
  }
  
  if (DirHandle != NULL)
  	DirHandle->Delete(DirHandle);
  
  Root->Close(Root);    
  return EFI_SUCCESS;
}




EFI_STATUS
BBTestFlushExBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE_PROTOCOL         *Root;
  UINTN                     TplIndex;
  CHAR16                    DirName[100];
  CHAR16                    FileName[100];
  EFI_FILE_PROTOCOL         *DirHandle;
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;

  Root       = NULL;
  DirHandle  = NULL;
  FileHandle = NULL;
  
  Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"OpenVolume fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  if (Root->Revision != EFI_FILE_PROTOCOL_REVISION2) {
    Root->Close(Root);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Async File IO is not supported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EFI_UNSUPPORTED
                   );
    return EFI_UNSUPPORTED;
  }
  //
  // init
  //
  EfiStrCpy (DirName, L"BBTestFlushExBasicTestCheckpoint4_Dir");
  EfiStrCpy (FileName, L"BBTestFlushExBasicTestCheckpoint4_File");
  
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event      = NULL;
  FileIoTokenSync.Status     = EFI_NOT_READY;

  //
  // create the Dir
  //
  Status = Root->Open (Root, &DirHandle, DirName, CREATE_FILE_MODE, EFI_FILE_DIRECTORY);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create dir fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);

    return Status;
  }

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
    //
    // create the file
    //
    Status = Root->Open (Root, &FileHandle, FileName, CREATE_FILE_MODE, 0);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Create file fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      if (DirHandle != NULL){
         DirHandle->Delete(DirHandle);
         DirHandle = NULL;
      }
      
      Root->Close(Root);

      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = DirHandle->FlushEx(
               DirHandle,
               &FileIoTokenSync
               );
    gtBS->RestoreTPL (OldTpl);
    
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    //
    // Check & record every File Io execution entity status 
    //
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } 
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemExBBTestFunctionAssertionGuid024,
                   L"FlushEx() Basic Test - checkpoint4----Sync",
                   L"%a:%d: Tpl - %d,Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[TplIndex],
                   Status
                   ); 
  
    if (FileHandle != NULL){
      FileHandle->Delete(FileHandle);
      FileHandle = NULL;
    }   
  }
  
  if (DirHandle != NULL){
    DirHandle->Delete(DirHandle);
    DirHandle = NULL;
  }

  Root->Close(Root);

  return Status;
}


