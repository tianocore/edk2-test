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
    SimpleFileSystemExTestFunction_ReadEx.c

Abstract:
    For EFI Simple File System Protocol and EFI_FILE Protocol's Function Test

--*/


#define EFI_FILE_HANDLE_REVISION 0x00020000

#include "SimpleFileSystemBBTest.h"

//
//checkpoint 
//
EFI_STATUS
EFIAPI
BBTestReadExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
EFIAPI
BBTestReadExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
EFIAPI
BBTestReadExBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );


EFI_STATUS
EFIAPI
BBTestReadExBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );




//
// Async Read File Queue
//
SCT_LIST_ENTRY  AsyncReadExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncReadExecuteListHead);
SCT_LIST_ENTRY  AsyncReadFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncReadFinishListHead);
SCT_LIST_ENTRY  AsyncReadFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncReadFailListHead);

//
// Async Read File lock
//
SCT_LOCK  gAsyncReadQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);


//
// Async Read Directory Queue
//
SCT_LIST_ENTRY  AsyncReadDirExecuteListHead = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncReadDirExecuteListHead);
SCT_LIST_ENTRY  AsyncReadDirFinishListHead  = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncReadDirFinishListHead);
SCT_LIST_ENTRY  AsyncReadDirFailListHead    = INITIALIZE_SCT_LIST_HEAD_VARIABLE(AsyncReadDirFailListHead);

//
// Async Read Directory lock
//
SCT_LOCK  gAsyncReadDirQueueLock = SCT_INITIALIZE_LOCK_VARIABLE (TPL_CALLBACK);


//
//Async Read NotifyFunc
//
VOID
EFIAPI FileIoReadNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  FileIo_Task    *FileIoEntity;
  
  FileIoEntity = (FileIo_Task *)Context;

  //
  // Remove entity from ReadExecuteListHead &  add entity to ReadFinishListHead
  // All FileIo Notify function run at Call Back level only once, So no locks required
  //
  SctAcquireLock (&gAsyncReadQueueLock);
  SctRemoveEntryList(&FileIoEntity->ListEntry);
  SctInsertTailList(&AsyncReadFinishListHead, &FileIoEntity->ListEntry);

  FileIoEntity->FileIo->GetPosition (FileIoEntity->FileIo, &FileIoEntity->PositionAfterRead);
  
  SctReleaseLock (&gAsyncReadQueueLock);
}

/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.ReadEx() function abstraction interface
 *  @param FileIo  a pointer to File Io to be tested.
 *  @param Tpl the Tpl level
 *  @param SetPosition the Starting Position to read from.
 *  @param ReadLength the read length.
 *  @param Buffer a pointer to read data buffer.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncReadData (
  IN EFI_FILE                          *FileIo,
  IN EFI_TPL                           Tpl,
  IN UINT64                            SetPosition,
  IN UINTN                             ReadLength,
  IN UINTN                             BufferSize,
  OUT UINT8                            *Buffer
)
{

  EFI_STATUS                         Status;
  FileIo_Task                        *FileIoEntity = NULL;
  EFI_TPL                            OldTpl;

  ASSERT(FileIo != NULL);
  
  //
  // Allocate memory for one FileIoEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIo_Task), 
                   (VOID **) &FileIoEntity);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  //
  // FileIoToken initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   (EFI_EVENT_NOTIFY) FileIoReadNotifyFunc,
                   FileIoEntity,
                   &FileIoEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(FileIoEntity);
    return Status;
  }

  FileIoEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoEntity->FileIo                 = FileIo;
  FileIoEntity->FileIoToken.Status     = EFI_NOT_READY;
  FileIoEntity->FileIoToken.Buffer     = (UINT8 *)Buffer;
  FileIoEntity->FileIoToken.BufferSize = ReadLength;
  FileIoEntity->Tpl                    = Tpl;  
  FileIoEntity->SetPosition            = SetPosition;
  FileIoEntity->ReadLength             = BufferSize;
  FileIoEntity->PositionAfterRead      = 0;
  

  SctAcquireLock (&gAsyncReadQueueLock);
  SctInsertTailList(&AsyncReadExecuteListHead, &FileIoEntity->ListEntry);
  SctReleaseLock (&gAsyncReadQueueLock);
  
  //
  // Async ReadEx Call
  //
  OldTpl = gtBS->RaiseTPL (FileIoEntity->Tpl);
  Status = FileIo->ReadEx (
                     FileIoEntity->FileIo,
                     &FileIoEntity->FileIoToken
                     );
  gtBS->RestoreTPL (OldTpl);
  
  if (EFI_ERROR (Status)) {
    SctAcquireLock (&gAsyncReadQueueLock);
    SctRemoveEntryList(&FileIoEntity->ListEntry);
    SctInsertTailList(&AsyncReadFailListHead, &FileIoEntity->ListEntry);    
    SctReleaseLock (&gAsyncReadQueueLock);

    FileIoEntity->FileIoToken.Buffer = NULL;
  }

  //
  // Record execution Info to File IO  entity 
  //
  FileIoEntity->StatusAsync = Status;

  return Status;
}


//
//Async Read Dir NotifyFunc
//
VOID
EFIAPI FileIoReadDirNotifyFunc (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  FileIoDir_Task    *FileIoReadDirEntity;
  
  FileIoReadDirEntity = (FileIoDir_Task *)Context;

  //
  // Remove entity from ReadDirExecuteListHead &  add entity to ReadDirFinishListHead
  // All FileIoReadDir Notify function run at Call Back level only once, So no locks required
  //
  SctAcquireLock (&gAsyncReadDirQueueLock);
  SctRemoveEntryList(&FileIoReadDirEntity->ListEntry);
  SctInsertTailList(&AsyncReadDirFinishListHead, &FileIoReadDirEntity->ListEntry);
  SctReleaseLock (&gAsyncReadDirQueueLock);
}

/**
 *  Provide EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.ReadEx() function abstraction interface
 *  @param FileIo  a pointer to File Io to be tested.
 *  @param Tpl the Tpl level
 *  @param Index Related To The Setposition.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
STATIC
EFI_STATUS
FileIoAsyncReadDir (
  IN EFI_FILE                          *FileIo,
  IN EFI_TPL                           Tpl,
  IN UINTN                             ReadLength,
  IN UINTN                             Index
)
{

  EFI_STATUS                         Status;
  FileIoDir_Task                     *FileIoReadDirEntity;
  EFI_TPL                            OldTpl;
  UINTN                              BufferSize;
  UINTN                              Loop;
  ASSERT(FileIo != NULL);

  BufferSize          = 0x1000;
  FileIoReadDirEntity = NULL;
  
  //
  // Allocate memory for one FileIoReadDirEntity
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   sizeof(FileIoDir_Task), 
                   (VOID **) &FileIoReadDirEntity);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Allocate memory for Read Buffer
  //
  Status = gtBS->AllocatePool(
                   EfiBootServicesData, 
                   BufferSize, 
                   (VOID **) &FileIoReadDirEntity->FileIoToken.Buffer
                   );
  if (EFI_ERROR (Status)) {
    gtBS->FreePool(FileIoReadDirEntity);
    return Status;
  }
  //
  // FileIoToken initialization
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   FileIoReadDirNotifyFunc,
                   FileIoReadDirEntity,
                   &FileIoReadDirEntity->FileIoToken.Event
                   );
  if (EFI_ERROR (Status)) {
  	gtBS->FreePool(FileIoReadDirEntity->FileIoToken.Buffer);
    gtBS->FreePool(FileIoReadDirEntity);
    return Status;
  }

  FileIoReadDirEntity->Signature              = FILEIOENTITY_SIGNATURE;
  FileIoReadDirEntity->FileIo                 = FileIo;
  FileIoReadDirEntity->FileIoToken.Status     = EFI_NOT_READY;
  FileIoReadDirEntity->FileIoToken.BufferSize = ReadLength;  
  FileIoReadDirEntity->Tpl                    = Tpl;
  FileIoReadDirEntity->Index                  = Index;
  
  if (Index > 4){
    //
    // read until end of the file
    //
    BufferSize = SIZE_OF_EFI_FILE_INFO;
    for (Loop = 0; Loop < 100; Loop++) {
      FileIoReadDirEntity->FileIo->Read (
                                     FileIoReadDirEntity->FileIo, 
                                     &BufferSize,
                                     FileIoReadDirEntity->FileIoToken.Buffer
                                     );
    }
  }

  SctAcquireLock (&gAsyncReadDirQueueLock);
  SctInsertTailList(&AsyncReadDirExecuteListHead, &FileIoReadDirEntity->ListEntry);
  SctReleaseLock (&gAsyncReadDirQueueLock);
  
  //
  // Async Directory ReadEx Call
  //
  OldTpl = gtBS->RaiseTPL (FileIoReadDirEntity->Tpl);
  Status = FileIo->ReadEx (
                     FileIoReadDirEntity->FileIo,
                     &FileIoReadDirEntity->FileIoToken
                     );
  gtBS->RestoreTPL (OldTpl);

  if (Status != EFI_SUCCESS) {
    SctAcquireLock (&gAsyncReadDirQueueLock);
    SctRemoveEntryList(&FileIoReadDirEntity->ListEntry);
    SctInsertTailList(&AsyncReadDirFailListHead, &FileIoReadDirEntity->ListEntry);    
    SctReleaseLock (&gAsyncReadDirQueueLock);
  }

  //
  // Record execution Info to File Io ReadDir entity 
  //
  FileIoReadDirEntity->StatusAsync = Status;

  return Status;
}




/**
 *  @brief For ReadEx() basic test
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.13
//
EFI_STATUS
EFIAPI
BBTestReadExBasicTest (
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
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // 5.1.12.2.1 Async Call ReadEx() to read data from a file.
  //
  BBTestReadExBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.1.12.2.2  Sync Call ReadEx() to read data from a file.
  //
  BBTestReadExBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);

  //
  // 5.1.12.2.3  Async Call ReadEx() to read data from a directory.
  //
  BBTestReadExBasicTestCheckpoint3 (StandardLib, SimpleFileSystem);

  //
  // 5.1.12.2.4 Sync  Call ReadEx() to read data from a directory.
  //
  BBTestReadExBasicTestCheckpoint4 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestReadExBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  UINTN                     TplIndex;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  UINTN                     FileSize;
  UINT8                     *Buffer;
  UINTN                     BufferSize;
  UINTN                     PositionIndex;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  SCT_LIST_ENTRY            *ListEntry;
  FileIo_Task               *FileIoEntity;
  UINT8                     *BufferRead;
  UINTN                     SetPosition[9] = {0, 0, 0, 100, 100, 100, 200, 200, 300};
  UINTN                     ReadLength[9] = {50, 200, 250, 50, 100, 200, 0, 100, 1};

  Root         = NULL;
  ListEntry    = NULL;
  FileIoEntity = NULL;
  Buffer       = NULL;
  FileHandle   = NULL;
  FileSize     = 200;
  
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

  SctStrCpy (FileName, L"BBTestReadExBasicTestCheckpoint1_File");

  //
  // allocate buffer for read
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, (UINTN)FileSize, (VOID**)&Buffer);
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
    
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
      Buffer = NULL;
    }
    
    Root->Close(Root);
    return Status;
  }

  //
  // write file with the Buffer (all are 0x33)
  //
  BufferSize = (UINTN)FileSize;
  gtBS->SetMem (Buffer, BufferSize, 0x33);
  
  Status = FileHandle->Write (FileHandle, &BufferSize, Buffer);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"write file fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
      Buffer = NULL;
     } 
          
    if (FileHandle != NULL) {
      FileHandle->Delete (FileHandle);
      FileHandle = NULL;
    }
    
    Root->Close(Root);

    return Status;
  }

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    for (PositionIndex = 0; PositionIndex < 9; PositionIndex++) {

      Status = FileHandle->SetPosition (FileHandle, SetPosition[PositionIndex]);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"set file position fail",
                       L"%a:%d: Status - %r, setpostion - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       SetPosition[PositionIndex]
                       );
        continue;
      }

      //
      // read data from the file
      //
      if (SetPosition[PositionIndex] > FileSize) {
        continue;
	  } else {
        if (SetPosition[PositionIndex] + ReadLength[PositionIndex] > FileSize) {
          BufferSize = FileSize - SetPosition[PositionIndex];
        } else {
          BufferSize = ReadLength[PositionIndex];
        }
	  }

      Status = FileIoAsyncReadData(
                 FileHandle,
                 TplArray[TplIndex],
                 SetPosition[PositionIndex],
                 ReadLength[PositionIndex],
                 BufferSize,
                 Buffer
                 );
      }
    }
  
    SctPrint (L" ================== Async ReadEx call finshed ================== \n\n");
  

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
 
    //
    // clear all File IO events from gReadFinishQueue 
    // gReadFinshQueue is handled first since we use File IO read to do read buffer validation 
    // Here no logs should be wrote to this file device to keep data intact
    //
    SctAcquireLock (&gAsyncReadQueueLock);
    if (!SctIsListEmpty(&AsyncReadFinishListHead)) {
      for(ListEntry = SctGetFirstNode(&AsyncReadFinishListHead); ; ListEntry = SctGetNextNode(&AsyncReadFinishListHead, ListEntry)) {
        FileIoEntity = CR(ListEntry, FileIo_Task, ListEntry, FILEIOENTITY_SIGNATURE);
        SctReleaseLock (&gAsyncReadQueueLock);

        FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
        //
        // Check & record every File Io execution entity status 
        //
        if (FileIoEntity->FileIoToken.Status == EFI_SUCCESS) {
       
          //
          // returned BufferSize equals ReadLength
          //
          if (FileIoEntity->ReadLength == FileIoEntity->FileIoToken.BufferSize) {
            //
            // file position is updated
            //
            if (FileIoEntity->PositionAfterRead == (FileIoEntity->SetPosition + FileIoEntity->ReadLength)) {
              FileIoEntity->AssertionType = EFI_TEST_ASSERTION_PASSED; 
                
              BufferRead = (UINT8 *)FileIoEntity->FileIoToken.Buffer;
                
              for (Index = 0; Index < FileIoEntity->ReadLength; Index++) {
                if (*BufferRead != 0x33) {
                  FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
				  break;
                }
                BufferRead++;
              }
            } else {
              FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            FileIoEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
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
      FileIoEntity = CR(AsyncReadFinishListHead.ForwardLink, FileIo_Task, ListEntry, FILEIOENTITY_SIGNATURE);   
      SctRemoveEntryList(&FileIoEntity->ListEntry);
      SctReleaseLock (&gAsyncReadQueueLock);
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     FileIoEntity->AssertionType,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid001,
                     L"ReadEx() Basic Test - checkpoint1----Async",
                     L"%a:%d: BufferSize - %d, Expected - %d, position before read - %d, position after read - %d, Tpl - %d, StatusAsync=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->FileIoToken.BufferSize,
                     FileIoEntity->ReadLength,
                     (UINTN)FileIoEntity->SetPosition,
                     (UINTN)FileIoEntity->PositionAfterRead,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync
                     );

      gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
      gtBS->FreePool(FileIoEntity);
      SctAcquireLock (&gAsyncReadQueueLock);
    }
    SctReleaseLock (&gAsyncReadQueueLock);


    //
    // If ReadFailListHead is not empty, which means some Async Calls are wrong 
    //
    SctAcquireLock (&gAsyncReadQueueLock);
    while(!SctIsListEmpty(&AsyncReadFailListHead)) {
      FileIoEntity = CR(AsyncReadFailListHead.ForwardLink, FileIo_Task, ListEntry, FILEIOENTITY_SIGNATURE);
      SctRemoveEntryList(&FileIoEntity->ListEntry);
      SctReleaseLock (&gAsyncReadQueueLock);
        
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid002,
                     L"ReadEx() Basic Test - checkpoint1---Async",
                     L"%a:%d: BufferSize - %d, Expected - %d, position before read - %d, position after read - %d, Tpl - %d,StatusAsync=%r",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoEntity->FileIoToken.BufferSize,
                     FileIoEntity->ReadLength,
                     (UINTN)FileIoEntity->SetPosition,
                     (UINTN)FileIoEntity->PositionAfterRead,
                     FileIoEntity->Tpl,
                     FileIoEntity->StatusAsync
                     );

       gtBS->CloseEvent(FileIoEntity->FileIoToken.Event);
       gtBS->FreePool(FileIoEntity);
         
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
        FileIoEntity = CR(ListEntry, FileIo_Task, ListEntry, FILEIOENTITY_SIGNATURE);
        SctReleaseLock (&gAsyncReadQueueLock);
      
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gSimpleFileSystemExBBTestFunctionAssertionGuid003,
                       L"ReadEx() Basic Test - checkpoint1----Async",
                       L"%a:%d: BufferSize - %d, Expected - %d, position before read - %d, position after read - %d, Tpl - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       FileIoEntity->FileIoToken.BufferSize,
                       FileIoEntity->ReadLength,
                       (UINTN)FileIoEntity->SetPosition,
                       (UINTN)FileIoEntity->PositionAfterRead,
                       FileIoEntity->Tpl
                       );

        SctAcquireLock (&gAsyncReadQueueLock);
        if (SctIsNodeAtEnd(&AsyncReadExecuteListHead, ListEntry)) {
          break;
        }
      }
    }
    
    SctReleaseLock (&gAsyncReadQueueLock);
	
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
    }

    FileHandle->Delete(FileHandle);
    Root->Close(Root);
    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestReadExBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  UINTN                     TplIndex;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  UINTN                     FileSize;
  UINT8                     *Buffer;
  UINTN                     BufferSize;
  UINT64                    PositionAfterRead;
  UINTN                     PositionIndex;
  UINTN                     Index;
  UINT8                     *BufferRead;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     SetPosition[9] = {0, 0, 0, 100, 100, 100, 200, 200, 300};
  UINTN                     ReadLength[9] = {50, 200, 250, 50, 100, 200, 0, 100, 1};

  Root       = NULL;
  Buffer     = NULL;
  FileHandle = NULL;
  FileSize   = 200;
  
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
  SctStrCpy (FileName, L"BBTestReadExBasicTestCheckpoint2_File");
 
  //
  // allocate buffer for read
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, (UINTN)FileSize, (VOID**)&Buffer);
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
     
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
    }

    Root->Close(Root);
    return Status;
  }
 
  //
  // write file with the Buffer (all are 0x33)
  //
  BufferSize = (UINTN)FileSize;
  gtBS->SetMem (Buffer, BufferSize, 0x33);

  Status = FileHandle->Write (FileHandle, &BufferSize, Buffer);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"write file fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
    } 
           
    if (FileHandle != NULL) {
      FileHandle->Delete (FileHandle);
    }
    Root->Close(Root);
    return Status;
  }
 
  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
 
    for (PositionIndex = 0; PositionIndex < 9; PositionIndex++) {
 
      Status = FileHandle->SetPosition (FileHandle, SetPosition[PositionIndex]);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"set file position fail",
                       L"%a:%d: Status - %r, setpostion - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       SetPosition[PositionIndex]
                       );
        continue;
      }

      //
      // Sync Token Init
      //
      FileIoTokenSync.Event      = NULL;
      FileIoTokenSync.Status     = EFI_NOT_READY;
      FileIoTokenSync.BufferSize = ReadLength[PositionIndex];
      FileIoTokenSync.Buffer     = Buffer;

      if (SetPosition[PositionIndex] > FileSize) {
        continue;
      } else {
        if (SetPosition[PositionIndex] + ReadLength[PositionIndex] > FileSize) {
          BufferSize = FileSize - SetPosition[PositionIndex];;
		} else {
          BufferSize = ReadLength[PositionIndex];
        }
      }
       
      OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
       
      Status = FileHandle->ReadEx (
                 FileHandle,
                 &FileIoTokenSync
                 );
       
      gtBS->RestoreTPL (OldTpl);

      if (EFI_ERROR(Status) ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
	  
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleFileSystemExBBTestFunctionAssertionGuid004,
                       L"ReadEx() Basic Test - checkpoint2---Sync",
                       L"%a:%d: Status - %d, Tpl - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[TplIndex]
                       );		
	  } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        //
        // Check & record  
        // 
        Status = FileHandle->GetPosition (FileHandle, &PositionAfterRead);

        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"get file position fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          continue;
        }  else {
          //
          // file position is updated
          //
          if (PositionAfterRead == (SetPosition[PositionIndex]+ BufferSize)) {
            BufferRead = (UINT8 *)FileIoTokenSync.Buffer;
            for (Index = 0; Index < BufferSize; Index++) {
              if (*BufferRead != 0x33) {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }
              BufferRead++;
            }
          } else {
             AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        }
	  
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gSimpleFileSystemExBBTestFunctionAssertionGuid004,
                       L"ReadEx() Basic Test - checkpoint2---Sync",
                       L"%a:%d: BufferSize - %d, Expected - %d, position before read - %d, position after read - %d, Tpl - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       FileIoTokenSync.BufferSize,
                       BufferSize,
                       SetPosition[PositionIndex],
                       (UINTN)PositionAfterRead,
                       TplArray[TplIndex]
                       );
      }
    }
  }

  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
    Buffer = NULL;
  } 
          
  if (FileHandle != NULL) {
    FileHandle->Delete (FileHandle);
    FileHandle = NULL;
  }

  Root->Close(Root);

  return Status;
}
   


EFI_STATUS
EFIAPI
BBTestReadExBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
/*
  the directory has three directory entry:
    "."
    ".."
    "BBTestReadExBasicTestCheckpoint3_File"
*/

{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  UINTN                     TplIndex;
  CHAR16                    FileName[100];
  CHAR16                    DirName[100];
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *DirHandle;
  UINTN                     ReadLength[10];
  UINTN                     BufferSize;
  UINTN                     Index;
  UINTN                     IndexI;
  UINTN                     WaitIndex;
  SCT_LIST_ENTRY            *ListEntry;
  FileIoDir_Task            *FileIoReadDirEntity;  

  Root                = NULL;
  FileHandle          = NULL;
  DirHandle           = NULL;
  ListEntry           = NULL;
  FileIoReadDirEntity = NULL;
  SctStrCpy (FileName, L"BBTestReadExBasicTestCheckpoint3_File");
  SctStrCpy (DirName, L"BBTestReadExBasicTestCheckpoint3_Dir");

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

  BufferSize = 0x1000;

  //
  // create the directory
  //
  Status = Root->Open (Root, &DirHandle, DirName, CREATE_FILE_MODE, EFI_FILE_DIRECTORY);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create directory fail",
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
  Status = DirHandle->Open (DirHandle, &FileHandle, FileName, CREATE_FILE_MODE, 0);
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

    if (DirHandle != NULL) {
      DirHandle->Delete (DirHandle);
    }
    Root->Close(Root);

    return EFI_SUCCESS;
  }

  //
  // init ReadLength[]
  // it is used for L"." entry
  // The exact Length for a read is SIZE_OF_EFI_FILE_INFO + StrLen (L".")
  //
  ReadLength[0] = 0;  // <
  ReadLength[1] = SIZE_OF_EFI_FILE_INFO - 1;  // <
  ReadLength[2] = SIZE_OF_EFI_FILE_INFO + 4;  // =
  ReadLength[3] = 2 * (SIZE_OF_EFI_FILE_INFO + 4);  // >
  ReadLength[4] = 2 * (SIZE_OF_EFI_FILE_INFO + 4) - 1;  // >
  ReadLength[5] = SIZE_OF_EFI_FILE_INFO + 4;
  ReadLength[6] = SIZE_OF_EFI_FILE_INFO + 4;
  ReadLength[7] = SIZE_OF_EFI_FILE_INFO + 4;
  ReadLength[8] = SIZE_OF_EFI_FILE_INFO + 4;
  ReadLength[9] = SIZE_OF_EFI_FILE_INFO + 4;
  //
  // first: before read, file position is at the beginning of the directory.
  //
  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    for (Index = 0; Index < 10; Index++) {
      
      Status = DirHandle->SetPosition (DirHandle, 0);

      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Set Position for a directory fail",
                       L"%a:%d: Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        if (FileHandle != NULL) {
          FileHandle->Delete (FileHandle);
          FileHandle = NULL;
        }

        if (DirHandle != NULL) {
          DirHandle->Delete (DirHandle);
          DirHandle = NULL;
        }
        Root->Close(Root);

        return Status;
      }

      //
      // read
      //      
      Status = FileIoAsyncReadDir(
                 DirHandle,
                 TplArray[TplIndex],
                 ReadLength[Index],
                 Index
                 );               
    }
  }
  
  
  SctPrint (L" ================== Async ReadEx call finshed ================== \n\n");
  
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

  //
  // clear all File IO events from gReadDirFinishQueue 
  // gReadDirFinshQueue is handled first since we use File IO read to do read buffer validation 
  // Here no logs should be wrote to this file device to keep data intact
  //
  SctAcquireLock (&gAsyncReadDirQueueLock);
    if (!SctIsListEmpty(&AsyncReadDirFinishListHead)) {
      for(ListEntry = SctGetFirstNode(&AsyncReadDirFinishListHead); ; ListEntry = SctGetNextNode(&AsyncReadDirFinishListHead, ListEntry)) {
        FileIoReadDirEntity = CR(ListEntry, FileIoDir_Task, ListEntry, FILEIOENTITY_SIGNATURE);
        SctReleaseLock (&gAsyncReadDirQueueLock);
      
        FileIoReadDirEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;

        //
        // Check & record every File Io Read Dir execution entity status 
        //
        if (FileIoReadDirEntity->Index < 2) {
          if ((EFI_BUFFER_TOO_SMALL == FileIoReadDirEntity->StatusAsync) && (FileIoReadDirEntity->FileIoToken.BufferSize == (SIZE_OF_EFI_FILE_INFO + 4))) {
            FileIoReadDirEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoReadDirEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        } else if (FileIoReadDirEntity->Index < 5){
          if ((EFI_SUCCESS == FileIoReadDirEntity->StatusAsync) && (FileIoReadDirEntity->FileIoToken.BufferSize == (SIZE_OF_EFI_FILE_INFO + 4))) {
            FileIoReadDirEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoReadDirEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          if ((EFI_SUCCESS == FileIoReadDirEntity->StatusAsync) && (FileIoReadDirEntity->FileIoToken.BufferSize == 0)) {
            FileIoReadDirEntity->AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            FileIoReadDirEntity->AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        }
          
        SctAcquireLock (&gAsyncReadDirQueueLock);
        //
        // Last list node handled
        //
        if (SctIsNodeAtEnd(&AsyncReadDirFinishListHead, ListEntry)) {
          break;
        }
      }
    }
  SctReleaseLock (&gAsyncReadQueueLock);    

  //
  // Record All Finished Read Dir case results
  //
  SctAcquireLock (&gAsyncReadDirQueueLock);
    while (!SctIsListEmpty(&AsyncReadDirFinishListHead)) {
      FileIoReadDirEntity = CR(AsyncReadDirFinishListHead.ForwardLink, FileIoDir_Task, ListEntry, FILEIOENTITY_SIGNATURE);   

      DirHandle = FileIoReadDirEntity->FileIo;

      SctRemoveEntryList(&FileIoReadDirEntity->ListEntry);
      SctReleaseLock (&gAsyncReadDirQueueLock);
            
      StandardLib->RecordAssertion (
                     StandardLib,
                     FileIoReadDirEntity->AssertionType,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid005,
                     L"ReadEx() Basic Test - checkpoint3----Async Read Dir",
                     L"%a:%d:Status - %r, BufferSize - %d, Expected - %d, Tpl - %d,Index = %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileIoReadDirEntity->StatusAsync,
                     FileIoReadDirEntity->FileIoToken.BufferSize,
                     (FileIoReadDirEntity->Index < 5) ? SIZE_OF_EFI_FILE_INFO + 4: 0,
                     FileIoReadDirEntity->Tpl,
                     FileIoReadDirEntity->Index
                     );
          
      if (FileIoReadDirEntity->FileIoToken.Buffer != NULL) {         
        Status = gtBS->FreePool (FileIoReadDirEntity->FileIoToken.Buffer);
        FileIoReadDirEntity->FileIoToken.Buffer = NULL;
      }

      gtBS->CloseEvent(FileIoReadDirEntity->FileIoToken.Event);

      gtBS->FreePool(FileIoReadDirEntity);

      SctAcquireLock (&gAsyncReadDirQueueLock);
    }
  SctReleaseLock (&gAsyncReadDirQueueLock);      

  //
  // If ReadFailDirListHead is not empty, which means some Async Read Dir Calls are wrong 
  //
  SctAcquireLock (&gAsyncReadDirQueueLock);
    while(!SctIsListEmpty(&AsyncReadDirFailListHead)) {

      FileIoReadDirEntity = CR(AsyncReadDirFailListHead.ForwardLink, FileIoDir_Task, ListEntry, FILEIOENTITY_SIGNATURE);

      DirHandle = FileIoReadDirEntity->FileIo;
        
      SctRemoveEntryList(&FileIoReadDirEntity->ListEntry);
      SctReleaseLock (&gAsyncReadDirQueueLock);
      if (FileIoReadDirEntity->StatusAsync == EFI_BUFFER_TOO_SMALL){
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_PASSED,
                       gSimpleFileSystemExBBTestFunctionAssertionGuid005,
                       L"ReadEx() Basic Test - checkpoint3----Async Read Dir EFI_BUFFER_TOO_SMALL",
                       L"%a:%d:Status - %r, BufferSize - %d, Expected - %d, Tpl - %d,Index = %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       FileIoReadDirEntity->StatusAsync,
                       FileIoReadDirEntity->FileIoToken.BufferSize,
                       SIZE_OF_EFI_FILE_INFO + 4,
                       FileIoReadDirEntity->Tpl,
                       FileIoReadDirEntity->Index
                       );
      } else {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gSimpleFileSystemExBBTestFunctionAssertionGuid006,
                       L"ReadEx() Basic Test - checkpoint3----Async Read Dir",
                       L"%a:%d:Status - %r, BufferSize - %d, Expected - %d, Tpl - %d,Index = %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       FileIoReadDirEntity->StatusAsync,
                       FileIoReadDirEntity->FileIoToken.BufferSize,
                       SIZE_OF_EFI_FILE_INFO + 4,
                       FileIoReadDirEntity->Tpl,
                       FileIoReadDirEntity->Index
                       );
      }
        

      //
      // Free  Buffer
      //
      if (FileIoReadDirEntity->FileIoToken.Buffer != NULL) {
        Status =gtBS->FreePool (FileIoReadDirEntity->FileIoToken.Buffer);
        FileIoReadDirEntity->FileIoToken.Buffer = NULL;
      }
      gtBS->CloseEvent(FileIoReadDirEntity->FileIoToken.Event);
      gtBS->FreePool(FileIoReadDirEntity);
             
      SctAcquireLock (&gAsyncReadDirQueueLock);
    }
  SctReleaseLock (&gAsyncReadDirQueueLock);        
         
  //
  // If ReadDirExecuteList is not empty, which means some token events havn't been signaled yet
  // Be careful, All the entities in Execution List should NOT be freed here!
  //
  SctAcquireLock (&gAsyncReadDirQueueLock);
    if (!SctIsListEmpty(&AsyncReadDirExecuteListHead)) {
      for(ListEntry = SctGetFirstNode(&AsyncReadDirExecuteListHead); ; ListEntry = SctGetNextNode(&AsyncReadDirExecuteListHead, ListEntry)) {
        FileIoReadDirEntity = CR(ListEntry, FileIoDir_Task, ListEntry, FILEIOENTITY_SIGNATURE);
        SctReleaseLock (&gAsyncReadDirQueueLock);
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gSimpleFileSystemExBBTestFunctionAssertionGuid007,
                       L"ReadEx() Basic Test - checkpoint3----Async Read Dir",
                       L"%a:%d:Status - %r, BufferSize - %d, Expected - %d, Tpl - %d,Index=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       FileIoReadDirEntity->StatusAsync,
                       FileIoReadDirEntity->FileIoToken.BufferSize,
                       SIZE_OF_EFI_FILE_INFO + 4,
                       FileIoReadDirEntity->Tpl,
                       FileIoReadDirEntity->Index
                       );
        
        SctAcquireLock (&gAsyncReadDirQueueLock);
        if (SctIsNodeAtEnd(&AsyncReadDirExecuteListHead, ListEntry)) {
          break;
        }
      }
    }
  SctReleaseLock (&gAsyncReadDirQueueLock);

  FileHandle->Delete(FileHandle);
  DirHandle->Delete(DirHandle);
  Root->Close(Root); 
  return EFI_SUCCESS;
}



  
EFI_STATUS
EFIAPI
BBTestReadExBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
    )
  /*
    the directory has three directory entry:
      "."
      ".."
      "BBTestReadBasicTestCheckpoint2_File"
  */
  
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  UINTN                     TplIndex;
  CHAR16                    FileName[100];
  CHAR16                    DirName[100];
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *DirHandle;
  UINT8                     *Buffer;
  UINTN                     ReadLength[5];
  UINTN                     BufferSize;
  UINTN                     Index;
  UINTN                     Loop;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  
  Root       = NULL;
  Buffer     = NULL;
  FileHandle = NULL;
  DirHandle  = NULL;
  SctStrCpy (FileName, L"BBTestReadBasicTestCheckpoint2_File");
  SctStrCpy (DirName, L"BBTestReadBasicTestCheckpoint2_Dir");
  
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
  // allocate a large enough buffer for directory reading
  //
  BufferSize = 0x1000;
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
  // create the directory
  //
  Status = Root->Open (Root, &DirHandle, DirName, CREATE_FILE_MODE, EFI_FILE_DIRECTORY);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create directory fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
    }
    Root->Close(Root);
    return EFI_SUCCESS;
  }
  
  //
  // create the file
  //
  Status = DirHandle->Open (DirHandle, &FileHandle, FileName, CREATE_FILE_MODE, 0);
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
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
    }
  
    if (DirHandle != NULL) {
      DirHandle->Delete (DirHandle);
    }
    Root->Close(Root);  
    return EFI_SUCCESS;
  }
  
  //
  // init ReadLength[]
  // it is used for L"." entry
  // The exact Length for a read is SIZE_OF_EFI_FILE_INFO + StrLen (L".")
  //
  ReadLength[0] = 0;  // <
  ReadLength[1] = SIZE_OF_EFI_FILE_INFO - 1;  // <
  ReadLength[2] = SIZE_OF_EFI_FILE_INFO + 4;  // =
  ReadLength[3] = 2 * (SIZE_OF_EFI_FILE_INFO + 4);  // >
  ReadLength[4] = 2 * (SIZE_OF_EFI_FILE_INFO + 4) - 1;  // >
  
  //
  // first: before read, file position is at the beginning of the directory.
  //
  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {
  
    for (Index = 0; Index < 5; Index++) {
      
      Status = DirHandle->SetPosition (DirHandle, 0);
  
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Set Position for a directory fail",
                       L"%a:%d: Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        if (Buffer != NULL) {
          gtBS->FreePool (Buffer);
        }
  
        if (FileHandle != NULL) {
          FileHandle->Delete (FileHandle);
        }
  
        if (DirHandle != NULL) {
          DirHandle->Delete (DirHandle);
        }
       Root->Close(Root);
        return EFI_SUCCESS;
      }
  
      //
      // read
      //
      BufferSize = ReadLength[Index];

      //
      // Sync Token Init
      //
      FileIoTokenSync.Event      = NULL;
      FileIoTokenSync.Status     = EFI_NOT_READY;
      FileIoTokenSync.BufferSize = BufferSize;
      FileIoTokenSync.Buffer     = Buffer;
      
      OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
            
      Status = FileHandle->ReadEx (
                 DirHandle,
                 &FileIoTokenSync
                 );
            
      gtBS->RestoreTPL (OldTpl);

      //
      // Check & record  
      //
      AssertionType = EFI_TEST_ASSERTION_FAILED; 

      if (Index < 2) {
        if ((EFI_BUFFER_TOO_SMALL == Status) && (FileIoTokenSync.BufferSize == (SIZE_OF_EFI_FILE_INFO + 4))) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }     
      } else {  
        if ((EFI_SUCCESS == Status) && (FileIoTokenSync.BufferSize == (SIZE_OF_EFI_FILE_INFO + 4))) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }              
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid008,
                     L"ReadEx() Basic Test - checkpoint4----Sync Read Dir",
                     L"%a:%d:Status - %r, BufferSize - %d, Expected - %d, Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     FileIoTokenSync.BufferSize,
                     SIZE_OF_EFI_FILE_INFO + 4,
                     TplArray[TplIndex]
                     );
    }
    
    //
    // second: before read,file position is at the end of the directory file
    //
    for (Index = 5; Index < 10; Index++) {
      Status = DirHandle->SetPosition (DirHandle, 0);
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
        if (Buffer != NULL) {
          gtBS->FreePool (Buffer);
        }
  
        if (FileHandle != NULL) {
          FileHandle->Delete (FileHandle);
        }
  
        if (DirHandle != NULL) {
          DirHandle->Delete (DirHandle);
        }
        Root->Close(Root);
        return EFI_SUCCESS;
      }
  
      //
      // read until end of the file
      //
      BufferSize = SIZE_OF_EFI_FILE_INFO;
      for (Loop = 0; Loop < 100; Loop++) {
        DirHandle->Read (DirHandle, &BufferSize, Buffer);
      }
  
      //
      // read
      //
      BufferSize = ReadLength[Index];
      //
      // Sync Token Init
      //
      FileIoTokenSync.Event      = NULL;
      FileIoTokenSync.Status     = EFI_NOT_READY;
      FileIoTokenSync.BufferSize = BufferSize;
      FileIoTokenSync.Buffer     = Buffer;
      
      OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
            
      Status = FileHandle->ReadEx (
                 DirHandle,
                 &FileIoTokenSync
                 );
            
      gtBS->RestoreTPL (OldTpl);
      //
      // Check & record  
      //
      AssertionType = EFI_TEST_ASSERTION_FAILED;           
      if ((EFI_SUCCESS == Status) && (FileIoTokenSync.BufferSize == 0)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleFileSystemExBBTestFunctionAssertionGuid008,
                     L"ReadEx() Basic Test - checkpoint4----Sync Read Dir",
                     L"%a:%d:Status - %r, BufferSize - %d, Expected - %d, Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     FileIoTokenSync.BufferSize,
                     0,
                     TplArray[TplIndex]
                     );

      }
    }
  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
  }
  if (FileHandle != NULL) {
    FileHandle->Delete (FileHandle);
  }
  if (DirHandle != NULL) {
    DirHandle->Delete (DirHandle);
  }
  Root->Close(Root);
  return EFI_SUCCESS;
  
}
   
