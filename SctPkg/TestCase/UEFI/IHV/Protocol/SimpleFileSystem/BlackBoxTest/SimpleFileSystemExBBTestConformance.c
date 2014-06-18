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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2013 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    SimpleFileSystemExConformanceTest.c

Abstract:
    for EFI Simple File System Protocol and EFI_FILE Protocol's Conformance Test

--*/


#include "SimpleFileSystemBBTest.h"

STATIC BOOLEAN                         FileIoFinished;

STATIC
VOID
NotifyFunc (
  EFI_EVENT    Event,
  BOOLEAN      *Finished
  )
{
  *Finished = TRUE;
  return ;
}

//
// some private functions declaration
//
VOID
CreateRandomValueFileIo2 (
  UINT32    *RandomValue
  );

// TDS 5.2.9.2.1

EFI_STATUS
BBTestOpenExConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );
// TDS 5.2.9.2.2

EFI_STATUS
BBTestOpenExConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );
// TDS 5.2.9.2.3

EFI_STATUS
BBTestOpenExConformanceTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

// TDS 5.2.10.2.1

EFI_STATUS
BBTestWriteExConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

// TDS 5.2.10.2.2

EFI_STATUS
BBTestWriteExConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

// TDS 5.2.11.2.1

EFI_STATUS
BBTestWriteExConformanceTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.11.2.1
//
EFI_STATUS
BBTestFlushExConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.12.2.1
//
EFI_STATUS
BBTestReadExConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.12.2.2
//
EFI_STATUS
BBTestReadExConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );


/**
 *  @brief Entrypoint for Open() Conformance Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.9
//
EFI_STATUS
BBTestOpenExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL        *This,
  IN VOID                        *ClientInterface,
  IN EFI_TEST_LEVEL              TestLevel,
  IN EFI_HANDLE                  SupportHandle
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
  // 5.2.9.2.1  Call OpenEx() to open non-existent file.
  //
  BBTestOpenExConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.2.9.2.2  Call OpenEx() to create a file under non-existent directory.
  //
  BBTestOpenExConformanceTestCheckpoint2 (StandardLib, SimpleFileSystem);
  
  //
  // 5.2.9.2.3  Call OpenEx() with invalid OpenMode.
  //
  BBTestOpenExConformanceTestCheckpoint3 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Write() Conformance test
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.10
//
EFI_STATUS
BBTestWriteExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL        *This,
  IN VOID                        *ClientInterface,
  IN EFI_TEST_LEVEL              TestLevel,
  IN EFI_HANDLE                  SupportHandle
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
  // 5.2.10.2.1  Call WriteEx() to try to write data to a directory.
  //
  BBTestWriteExConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.2.10.2.2  Call WriteEx() to try to write data to a file
  // which was opened read-only.
  //
  BBTestWriteExConformanceTestCheckpoint2 (StandardLib, SimpleFileSystem);

  //
  // 5.2.10.2.2  Call WriteEx() to try to write data to a file
  // which has been deleted.
  //
  BBTestWriteExConformanceTestCheckpoint3 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Flush() Conformance test
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.11
//
EFI_STATUS
BBTestFlushExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL        *This,
  IN VOID                        *ClientInterface,
  IN EFI_TEST_LEVEL              TestLevel,
  IN EFI_HANDLE                  SupportHandle
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
  // 5.2.11.2.2  Call FlushEx() to try to flush data to a file
  // which was opened read-only.
  //
  BBTestFlushExConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For ReadEx() Conformance test
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
 
//
// TDS 5.2.12
//
EFI_STATUS
BBTestReadExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL        *This,
  IN VOID                        *ClientInterface,
  IN EFI_TEST_LEVEL              TestLevel,
  IN EFI_HANDLE                  SupportHandle
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
  // 5.2.12.2.1  Call ReadEx() to try to read data from a file with the fileposition beyond the end of the file.
  //
  BBTestReadExConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);
  //
  // 5.2.12.2.2  Call ReadEx() to try to read data to a file which has been deleted.
  //
  BBTestReadExConformanceTestCheckpoint2 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                StatusSync;
  EFI_STATUS                StatusAsync;
  EFI_FILE_PROTOCOL         *Root;
  EFI_TEST_ASSERTION        AssertionType;

  UINT32                    RandomValue;
  UINT32                    FileIndex;
  CHAR16                    RandomChars[10];
  CHAR16                    *BaseFileName;
  CHAR16                    NewFileName[100];
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_IO_TOKEN         FileIoTokenAsync;
  EFI_TPL                   OldTpl;
  UINTN                     Index;

  RandomValue  = 0;
  BaseFileName = L"Non-existence_";

  //
  // Check if Async File IO is supported
  //
  Root   = NULL;
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
  // Initialize File IO OpenEx token event
  //
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event  = NULL;
  FileIoTokenSync.Status = EFI_NOT_READY;

  //
  // Async Token Init
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   NotifyFunc,
                   &FileIoFinished,
                   &FileIoTokenAsync.Event
                   );
  
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat OpenEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
    return Status;
  }
  
  FileIoTokenAsync.Status = EFI_NOT_READY;

  //
  // open file & directory with the random name
  //
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    for (FileIndex = 0; FileIndex < 2; FileIndex++) {
    
      //
      // init
      //
      FileHandle = NULL;
    
      //
      // Create random file name
      //
      CreateRandomValueFileIo2 (&RandomValue);
      EfiValueToHexStr (RandomChars, RandomValue, PREFIX_ZERO, sizeof (UINT32));
      EfiStrCpy (NewFileName, BaseFileName);
      EfiStrCat (NewFileName, RandomChars);
    
      //
      // Sync Call OpenEx 
      //
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      StatusSync = Root->OpenEx(
                           Root,
                           &FileHandle,
                           NewFileName,
                           EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                           0,
                           &FileIoTokenSync
                           );
      gtBS->RestoreTPL (OldTpl);
      //
      // Async Call OpenEx 
      //
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      StatusAsync = Root->OpenEx(
                            Root,
                            &FileHandle,
                            NewFileName,
                            EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                            0,
                            &FileIoTokenAsync
                            );
      gtBS->RestoreTPL (OldTpl);
      
      if (EFI_NOT_FOUND == StatusSync && EFI_NOT_FOUND == StatusAsync) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      if ((EFI_MEDIA_CHANGED == StatusSync)
        || (EFI_WRITE_PROTECTED == StatusSync)
        || (EFI_VOLUME_FULL == StatusSync)
        || (EFI_MEDIA_CHANGED == StatusAsync)
        || (EFI_WRITE_PROTECTED == StatusAsync)
        || (EFI_VOLUME_FULL == StatusAsync)) {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      }
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleFileSystemExConformanceTestAssertionGuid001,
                     L"OpenEx() Conformance Test - checkpoint1",
                     L"%a:%d: Status - %r, FileName - %s, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     NewFileName,
                     TplArray[Index]
                     );
      if (FileHandle != NULL) {
        FileHandle->Delete (FileHandle);
      }
    }
  }
  
  gtBS->CloseEvent (FileIoTokenAsync.Event);
  Root->Close(Root);
  
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestOpenExConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                StatusSync;
  EFI_STATUS                StatusAsync;
  EFI_FILE_PROTOCOL         *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINT32                    RandomValue;
  CHAR16                    RandomChars[100];
  CHAR16                    BaseDirName[100];
  CHAR16                    NewDirName[100];
  CHAR16                    FileName[100];
  CHAR16                    OpenFileName[MAX_STRING_LENGTH];
  EFI_FILE_PROTOCOL         *FileHandle;
  UINTN                     FileNameLength;
  UINTN                     FileIndex;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_IO_TOKEN         FileIoTokenAsync;
  EFI_TPL                   OldTpl;
  UINTN                     Index;

  //
  // Check if Async File IO is supported
  //
  Root   = NULL;
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
  // Initialize File IO OpenEx token event
  //
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event = NULL;
  FileIoTokenSync.Status = EFI_NOT_READY;

  //
  // Async Token Init
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   NotifyFunc,
                   &FileIoFinished,
                   &FileIoTokenAsync.Event
                   );
  
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat OpenEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
    return Status;
  }
  
  FileIoTokenAsync.Status = EFI_NOT_READY;

  EfiStrCpy (FileName, L"BBTestOpenConformanceTestCheckpoint2_File");
  EfiStrCpy (BaseDirName, L"BBTestOpenConformanceTestCheckpoint2_");

  //
  // create directory name with the random name
  //
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    for (FileIndex = 0; FileIndex < 2 ; FileIndex++) {
    
      //
      // init
      //
      FileHandle = NULL;
    
      //
      // Create random dir name
      //
      CreateRandomValueFileIo2 (&RandomValue);
      EfiValueToHexStr (RandomChars, RandomValue, PREFIX_ZERO, sizeof (UINT32));
      EfiStrCpy (NewDirName, BaseDirName);
      EfiStrCat (NewDirName, RandomChars);
    
      //
      // create file name: "\" + DirName + "\" + FileName
      //
    
      //
      // "\"
      //
      OpenFileName[0] = '\\';
      OpenFileName[1] = 0;
    
      //
      // "\" + DirName
      //
      EfiStrCat (OpenFileName, NewDirName);
    
      //
      // "\" + DirName + "\"
      //
      FileNameLength = EfiStrLen (OpenFileName);
      OpenFileName[FileNameLength] = '\\';
      OpenFileName[FileNameLength + 1] = 0;
    
      //
      // "\" + DirName + "\" + FileName
      //
      EfiStrCat (OpenFileName, FileName);
    
      //
      // Sync create file 
      //
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      StatusSync = Root->OpenEx (
                           Root,
                           &FileHandle,
                           OpenFileName,
                           EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                           0,
                           &FileIoTokenSync
                           );
      gtBS->RestoreTPL (OldTpl);
      //
      // Async create file 
      //
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      StatusAsync = Root->OpenEx (
                           Root,
                           &FileHandle,
                           OpenFileName,
                           EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                           0,
                           &FileIoTokenAsync
                           );
      gtBS->RestoreTPL (OldTpl);
    
      
      if (EFI_NOT_FOUND == StatusSync && EFI_NOT_FOUND == StatusAsync) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      if ((EFI_MEDIA_CHANGED == StatusSync)
        || (EFI_WRITE_PROTECTED == StatusSync)
        || (EFI_VOLUME_FULL == StatusSync)
        || (EFI_MEDIA_CHANGED == StatusAsync)
        || (EFI_WRITE_PROTECTED == StatusAsync)
        || (EFI_VOLUME_FULL == StatusAsync)) {
    
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleFileSystemExConformanceTestAssertionGuid002,
                     L"OpenEx() Conformance Test - checkpoint2",
                     L"%a:%d: Status - %r, Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
	
      if (FileHandle != NULL) {
        FileHandle->Delete (FileHandle);
      }
    }
  }
  
  gtBS->CloseEvent (FileIoTokenAsync.Event);
  Root->Close(Root);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestOpenExConformanceTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                StatusSync;
  EFI_STATUS                StatusAsync;
  EFI_FILE_PROTOCOL         *Root;
  EFI_TEST_ASSERTION        AssertionType;
  CHAR16                    FileName[100];
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_FILE_PROTOCOL         *OpenHandle;
  UINTN                     ModeIndex;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  
  UINT64                    InvalidMode[] = {
                                  EFI_FILE_MODE_WRITE,
                                  EFI_FILE_MODE_CREATE,
                                  EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ,
                                  EFI_FILE_MODE_CREATE | EFI_FILE_MODE_WRITE,
                                  0,
                                  0xFFFFFFFFFFFFFF
                                };
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_IO_TOKEN         FileIoTokenAsync;

  //
  // Check if Async File IO is supported
  //
  Root   = NULL;
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

  EfiStrCpy (FileName, L"BBTestOpenConformanceTestCheckpoint3_File");
  
  //
  // Initialize File IO OpenEx token event
  //
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event  = NULL;
  FileIoTokenSync.Status = EFI_NOT_READY;
  
  //
  // Async Token Init
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   NotifyFunc,
                   &FileIoFinished,
                   &FileIoTokenAsync.Event
                   );
    
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat OpenEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);  
    return Status;
  }
    
  FileIoTokenAsync.Status = EFI_NOT_READY;

  //
  // create file
  //
  FileHandle = NULL;
  Status = Root->Open (
                   Root,
                   &FileHandle,
                   FileName,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   0
                   );
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
	
    gtBS->CloseEvent(FileIoTokenAsync.Event);
    Root->Close(Root);
    return Status;
  }
  
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    for (ModeIndex = 0; ModeIndex < sizeof (InvalidMode) / sizeof (UINT64); ModeIndex++) {
    
      //
      // init
      //
      OpenHandle = NULL;
    
      //
      //Sync open file with invalid mode
      //      
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      StatusSync = Root->OpenEx (
                           Root,
                           &OpenHandle,
                           FileName,
                           InvalidMode[ModeIndex],
                           0,
                           &FileIoTokenSync
                           );
      gtBS->RestoreTPL (OldTpl);
      //
      //Async open file with invalid mode
      //
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      StatusAsync = Root->OpenEx (
                            Root,
                            &OpenHandle,
                            FileName,
                            InvalidMode[ModeIndex],
                            0,
                            &FileIoTokenAsync
                            );
      gtBS->RestoreTPL (OldTpl);
	  
      if (EFI_INVALID_PARAMETER == StatusSync && EFI_INVALID_PARAMETER == StatusAsync) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gSimpleFileSystemExConformanceTestAssertionGuid003,
                     L"OpenEx() Conformance Test - checkpoint3",
                     L"%a:%d: Status - %r, Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (OpenHandle != NULL) {
        OpenHandle->Close (OpenHandle);
      }
    }
  }

  if (FileHandle != NULL) {
    Status = FileHandle->Delete (FileHandle);	
  }
  
  gtBS->CloseEvent(FileIoTokenAsync.Event);
  Root->Close(Root);
  return EFI_SUCCESS;
}




EFI_STATUS
BBTestWriteExConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                StatusSync;
  EFI_STATUS                StatusAsync;
  EFI_FILE_PROTOCOL         *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE_PROTOCOL         *DirHandle;
  CHAR16                    DirName[100];
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_IO_TOKEN         FileIoTokenAsync;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  
  //
  // Check if Async File IO is supported
  //
  Root   = NULL;
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
  // Initialize File IO OpenEx token event
  //
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event  = NULL;
  FileIoTokenSync.Status = EFI_NOT_READY;

 

  //
  // Async Token Init
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   NotifyFunc,
                   &FileIoFinished,
                   &FileIoTokenAsync.Event
                   );
  
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat OpenEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  	Root->Close(Root);
    return Status;
  }
  
  FileIoTokenAsync.Status = EFI_NOT_READY;

  EfiStrCpy (DirName, L"BBTestWriteExConformanceTestCheckpoint1_Dir");

  //
  // create the Dir
  //
  Status = Root->Open (
                   Root,
                   &DirHandle,
                   DirName,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   EFI_FILE_DIRECTORY
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create Dir fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->CloseEvent(FileIoTokenAsync.Event);
  	Root->Close(Root);
    return Status;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // try to sync write to the directory
    //
    TempSize = sizeof (UINT8);
    FileIoTokenSync.Buffer = &Temp;
    FileIoTokenSync.BufferSize = TempSize;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    StatusSync = DirHandle->WriteEx (DirHandle, &FileIoTokenSync);
    gtBS->RestoreTPL (OldTpl);
    
    //
    // try to async write to the directory
    //
    TempSize = sizeof (UINT8);
    FileIoTokenAsync.Buffer = &Temp;
    FileIoTokenAsync.BufferSize = TempSize;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    StatusAsync = DirHandle->WriteEx (DirHandle, &FileIoTokenAsync);
    gtBS->RestoreTPL (OldTpl);
    
    if (EFI_UNSUPPORTED == StatusSync && EFI_UNSUPPORTED == StatusAsync ) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemExConformanceTestAssertionGuid004,
                   L"WriteEx() Conformance Test - checkpoint1",
                   L"%a:%d: Status - %r, Tpl - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                   );
    
  }
  DirHandle->Delete (DirHandle); 
  gtBS->CloseEvent (FileIoTokenAsync.Event);
  Root->Close(Root);
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestWriteExConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                StatusSync;
  EFI_STATUS                StatusAsync;
  
  EFI_FILE_PROTOCOL         *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_FILE_PROTOCOL         *OpenHandle;
  CHAR16                    FileName[100];
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_IO_TOKEN         FileIoTokenAsync;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  
  //
  // Check if Async File IO is supported
  //
  Root   = NULL;
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
 // Initialize File IO OpenEx token event
 //
 //
 // Sync Token Init
 //
 FileIoTokenSync.Event = NULL;
 FileIoTokenSync.Status = EFI_NOT_READY;
 
 //
 // Async Token Init
 //
 Status = gtBS->CreateEvent (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  EFI_TPL_CALLBACK,
                  NotifyFunc,
                  &FileIoFinished,
                  &FileIoTokenAsync.Event
                  );
   
 if (EFI_ERROR (Status)) {
   StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"BS.CreateEvent - Creat OpenEx Event",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
 
   return Status;
 }
   
  FileIoTokenAsync.Status = EFI_NOT_READY;


  EfiStrCpy (FileName, L"BBTestWriteExConformanceTestCheckpoint2_File");

  //
  // create the File
  //
  Status = Root->Open (
                   Root,
                   &FileHandle,
                   FileName,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   0
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );
    gtBS->CloseEvent(FileIoTokenAsync.Event);
  	Root->Close(Root);
    return Status;
  }

  //
  // Open the file with Mode Read
  //
  Status = Root->Open (
                   Root,
                   &OpenHandle,
                   FileName,
                   EFI_FILE_MODE_READ,
                   0
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Open file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );

    gtBS->CloseEvent(FileIoTokenAsync.Event);
	FileHandle->Delete (FileHandle);
    Root->Close(Root);
	
    return Status;
  }

  FileHandle->Close (FileHandle);
  
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // try to sync write to the Read-only opened file
    //
    TempSize = sizeof (UINT8);
    FileIoTokenSync.Buffer = &Temp;
    FileIoTokenSync.BufferSize = TempSize;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    StatusSync = OpenHandle->WriteEx (OpenHandle, &FileIoTokenSync);
    gtBS->RestoreTPL (OldTpl);
    
    //
    // try to Async write to the Read-only opened file
    //
    TempSize = sizeof (UINT8);
    FileIoTokenAsync.Buffer = &Temp;
    FileIoTokenAsync.BufferSize = TempSize;
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    StatusAsync = OpenHandle->WriteEx (OpenHandle, &FileIoTokenAsync);
    gtBS->RestoreTPL (OldTpl);
    
    if (EFI_ACCESS_DENIED == StatusSync && EFI_ACCESS_DENIED == StatusAsync) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemExConformanceTestAssertionGuid005,
                   L"WriteEx() Conformance Test - checkpoint2",
                   L"%a:%d: StatusSync - %r, StatusAsync - %r, Tpl - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   StatusSync,
                   StatusAsync,
                   TplArray[Index]
                   );
  }
  
  OpenHandle->Close (OpenHandle);

  Root->Open (
          Root,
          &FileHandle,
          FileName,
          EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
          0
          );
  FileHandle->Delete (FileHandle);
  
  gtBS->CloseEvent(FileIoTokenAsync.Event);
  Root->Close(Root);

  return EFI_SUCCESS;
}



EFI_STATUS
BBTestWriteExConformanceTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                StatusSync;
  EFI_STATUS                StatusAsync;
  
  EFI_FILE_PROTOCOL         *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE_PROTOCOL         *FileHandle1;
  EFI_FILE_PROTOCOL         *FileHandle2;
  CHAR16                    FileName[100];
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_IO_TOKEN         FileIoTokenAsync;

  Root        = NULL;
  FileHandle1 = NULL;
  FileHandle2 = NULL;

  //
  // Check if Async File IO is supported
  //
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
 // Initialize File IO WriteEx token event
 //
 //
 // Sync Token Init
 //
 FileIoTokenSync.Event = NULL;
 FileIoTokenSync.Status = EFI_NOT_READY;
 
 //
 // Async Token Init
 //
 Status = gtBS->CreateEvent (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  EFI_TPL_CALLBACK,
                  NotifyFunc,
                  &FileIoFinished,
                  &FileIoTokenAsync.Event
                  );
   
 if (EFI_ERROR (Status)) {
   StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"BS.CreateEvent - Creat OpenEx Event",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

   Root->Close(Root);
   return Status;
 }
   
  FileIoTokenAsync.Status = EFI_NOT_READY;

  EfiStrCpy (FileName, L"BBTestWriteExConformanceTestCheckpoint3_File");

  //
  // create the File
  //
  Status = Root->Open (
                   Root,
                   &FileHandle1,
                   FileName,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   0
                   );
  
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );
    
    gtBS->CloseEvent(FileIoTokenAsync.Event);
  	Root->Close(Root);
    return Status;
  }

  //
  // open the File
  //
  Status = Root->Open (
                   Root,
                   &FileHandle2,
                   FileName,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                   0
                   );
  
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );
    FileHandle1->Delete(FileHandle1);
    gtBS->CloseEvent(FileIoTokenAsync.Event);
  	Root->Close(Root);
    return Status;
  }  

  FileHandle1->Delete(FileHandle1);
 
  //
  // try to sync write to the deleted file
  //
  TempSize = sizeof (UINT8);
  FileIoTokenSync.Buffer = &Temp;
  FileIoTokenSync.BufferSize = TempSize;
  StatusSync = FileHandle2->WriteEx (FileHandle2, &FileIoTokenSync);
    
  //
  // try to Async write to the deleted file
  //
  TempSize = sizeof (UINT8);
  FileIoTokenAsync.Buffer = &Temp;
  FileIoTokenAsync.BufferSize = TempSize;

  StatusAsync = FileHandle2->WriteEx (FileHandle2, &FileIoTokenAsync);

    
  if (EFI_DEVICE_ERROR == StatusSync && EFI_DEVICE_ERROR == StatusAsync) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemExConformanceTestAssertionGuid006,
                 L"WriteEx() Conformance Test - checkpoint3",
                 L"%a:%d: StatusSync - %r, StatusAsync - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusSync,
                 StatusAsync
                 );
  
  FileHandle2->Close(FileHandle2);
  gtBS->CloseEvent(FileIoTokenAsync.Event);
  Root->Close(Root);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestFlushExConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                StatusSync;
  EFI_STATUS                StatusAsync;
  
  EFI_FILE_PROTOCOL         *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE_PROTOCOL         *FileHandle;
  EFI_FILE_PROTOCOL         *OpenHandle;
  CHAR16                    FileName[100];
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_IO_TOKEN         FileIoTokenAsync;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  
  //
  // Check if Async File IO is supported
  //
  Root       = NULL;
  FileHandle = NULL;
  OpenHandle = NULL;
  
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
  // Initialize File IO OpenEx token event
  //
  //
  // Sync Token Init
  //
  FileIoTokenSync.Event  = NULL;
  FileIoTokenSync.Status = EFI_NOT_READY;
   
   
  //
  // Async Token Init
  //
  Status = gtBS->CreateEvent (
                   EFI_EVENT_NOTIFY_SIGNAL,
                   EFI_TPL_CALLBACK,
                   NotifyFunc,
                   &FileIoFinished,
                   &FileIoTokenAsync.Event
                   );
    
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.CreateEvent - Creat FlushEx Event",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    Root->Close(Root);
    return Status;
  }
    
  FileIoTokenAsync.Status = EFI_NOT_READY;

  EfiStrCpy (FileName, L"BBTestFlushExConformanceTestCheckpoint1_File");

  //
  // create the File
  //
  Status = Root->Open (
                   Root,
                   &FileHandle,
                   FileName,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   0
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );

    gtBS->CloseEvent(FileIoTokenAsync.Event);
    FileIoTokenAsync.Event = NULL;
  	Root->Close(Root);

    return Status;
  }

  //
  // Open the file with Mode Read
  //
  Status = Root->Open (
                   Root,
                   &OpenHandle,
                   FileName,
                   EFI_FILE_MODE_READ,
                   0
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Open file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );

    gtBS->CloseEvent(FileIoTokenAsync.Event);
	FileHandle->Delete (FileHandle);
  	Root->Close(Root);

    return Status;
  }

  FileHandle->Close (FileHandle);
  
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    //
    // try to sync flush to the Read-only opened file
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    StatusSync = OpenHandle->FlushEx (OpenHandle,&FileIoTokenSync);
    gtBS->RestoreTPL (OldTpl);
    
    //
    // try to Async flush to the Read-only opened file
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    StatusAsync = OpenHandle->FlushEx (OpenHandle,&FileIoTokenAsync);
    gtBS->RestoreTPL (OldTpl);
    
    if (EFI_ACCESS_DENIED == StatusSync && EFI_ACCESS_DENIED == StatusAsync) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemExConformanceTestAssertionGuid007,
                   L"FlushEx() Conformance Test - checkpoint1",
                   L"%a:%d: StatusSync - %r, StatusAsync - %r, Tpl - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   StatusSync,
                   StatusAsync,
                   TplArray[Index]
                   );
  }

  OpenHandle->Close (OpenHandle);

  Root->Open (
          Root,
          &FileHandle,
          FileName,
          EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
          0
          );
  FileHandle->Delete (FileHandle);

  
  gtBS->CloseEvent(FileIoTokenAsync.Event);
  Root->Close(Root);

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestReadExConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                StatusSync;
  EFI_STATUS                StatusAsync;
  
  EFI_FILE_PROTOCOL         *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE_PROTOCOL         *FileHandle;
  CHAR16                    FileName[100];
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_IO_TOKEN         FileIoTokenAsync;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  UINT8                     Buffer[200];
  UINTN                     BufferSize;
  
  BufferSize  = 200;
  Root        = NULL;
  FileHandle  = NULL;
  
  //
  // Check if Async File Io is supported
  //
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
 // Initialize File IO ReadEx token event
 //
 //
 // Sync Token Init
 //
 FileIoTokenSync.Event = NULL;
 FileIoTokenSync.Status = EFI_NOT_READY;
  
 //
 // Async Token Init
 //
 Status = gtBS->CreateEvent (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  EFI_TPL_CALLBACK,
                  NotifyFunc,
                  &FileIoFinished,
                  &FileIoTokenAsync.Event
                  );
   
 if (EFI_ERROR (Status)) {
   StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"BS.CreateEvent - Creat OpenEx Event",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );
   Root->Close(Root);
   return Status;
 }
   
  FileIoTokenAsync.Status = EFI_NOT_READY;

  EfiStrCpy (FileName, L"BBTestReadExConformanceTestCheckpoint1_File");

  //
  // create the File
  //
  Status = Root->Open (
                   Root,
                   &FileHandle,
                   FileName,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   0
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );
    gtBS->CloseEvent(FileIoTokenAsync.Event);
  	Root->Close(Root);
    return Status;
  }

  //
  // write file with the Buffer (all are 0x33)
  //
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
    gtBS->CloseEvent(FileIoTokenAsync.Event);
    FileHandle->Delete(FileHandle);
  	Root->Close(Root);
    return Status;
  }
  
  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {
    
    Status = FileHandle->SetPosition (FileHandle, 0xff);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"set file position fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
       continue;
    }

    //
    // try to sync read the file
    //
    TempSize = sizeof (UINT8);
    FileIoTokenSync.Buffer = &Temp;
    FileIoTokenSync.BufferSize = TempSize;
    
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    StatusSync = FileHandle->ReadEx(FileHandle,&FileIoTokenSync);
    gtBS->RestoreTPL (OldTpl);

    
    //
    // try to Async read the file
    //
    TempSize = sizeof (UINT8);
    FileIoTokenAsync.Buffer = &Temp;
    FileIoTokenAsync.BufferSize = TempSize;
    
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    StatusAsync = FileHandle->ReadEx (FileHandle, &FileIoTokenAsync);
    gtBS->RestoreTPL (OldTpl);
    
    if (EFI_DEVICE_ERROR == StatusSync && EFI_DEVICE_ERROR == StatusAsync) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemExConformanceTestAssertionGuid008,
                   L"ReadEx() Conformance Test - checkpoint1",
                   L"%a:%d: StatusSync - %r, StatusAsync - %r, Tpl - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   StatusSync,
                   StatusAsync,
                   TplArray[Index]
                   );
  }

  FileHandle->Delete (FileHandle);
  
  gtBS->CloseEvent(FileIoTokenAsync.Event);
    
  Root->Close(Root);
  
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestReadExConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_STATUS                StatusSync;
  EFI_STATUS                StatusAsync;
  
  EFI_FILE_PROTOCOL         *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE_PROTOCOL         *FileHandle1;
  EFI_FILE_PROTOCOL         *FileHandle2;  
  CHAR16                    FileName[100];
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_FILE_IO_TOKEN         FileIoTokenSync;
  EFI_FILE_IO_TOKEN         FileIoTokenAsync;

  Root        = NULL;
  FileHandle1 = NULL;
  FileHandle2 = NULL;

  //
  // Check if Async File Io is supported
  //
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
 // Initialize File IO OpenEx token event
 //
 //
 // Sync Token Init
 //
 FileIoTokenSync.Event = NULL;
 FileIoTokenSync.Status = EFI_NOT_READY;
 
 //
 // Async Token Init
 //
 Status = gtBS->CreateEvent (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  EFI_TPL_CALLBACK,
                  NotifyFunc,
                  &FileIoFinished,
                  &FileIoTokenAsync.Event
                  );
   
 if (EFI_ERROR (Status)) {
   StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"BS.CreateEvent - Creat OpenEx Event",
                  L"%a:%d:Status - %r",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status
                  );

   Root->Close(Root);
   return Status;
 }
   
  FileIoTokenAsync.Status = EFI_NOT_READY;

  EfiStrCpy (FileName, L"BBTestReadExConformanceTestCheckpoint2_File");

  //
  // create the File
  //
  Status = Root->Open (
                   Root,
                   &FileHandle1,
                   FileName,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                   0
                   );
  
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );
    
    gtBS->CloseEvent(FileIoTokenAsync.Event);
  	Root->Close(Root);
    return Status;
  }

  //
  // open the File
  //
  Status = Root->Open (
                   Root,
                   &FileHandle2,
                   FileName,
                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                   0
                   ); 
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Create file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );
	
    FileHandle1->Delete(FileHandle1);    
    gtBS->CloseEvent(FileIoTokenAsync.Event);
  	Root->Close(Root);
    return Status;
  }

  FileHandle1->Delete(FileHandle1);

  //
  // try to sync read to the deleted file
  //
  TempSize = sizeof (UINT8);
  FileIoTokenSync.Buffer = &Temp;
  FileIoTokenSync.BufferSize = TempSize;

  StatusSync = FileHandle2->ReadEx (FileHandle2, &FileIoTokenSync);
 
  //
  // try to Async read to the deleted file
  //
  TempSize = sizeof (UINT8);
  FileIoTokenAsync.Buffer = &Temp;
  FileIoTokenAsync.BufferSize = TempSize;

  StatusAsync = FileHandle2->ReadEx (FileHandle2, &FileIoTokenAsync);
    
  if (EFI_DEVICE_ERROR == StatusSync && EFI_DEVICE_ERROR == StatusAsync) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemExConformanceTestAssertionGuid009,
                 L"ReadEx() Conformance Test - checkpoint2",
                 L"%a:%d: StatusSync - %r, StatusAsync - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusSync,
                 StatusAsync
                 );

  FileHandle2->Close(FileHandle2);
  gtBS->CloseEvent(FileIoTokenAsync.Event);
  Root->Close(Root);

  return EFI_SUCCESS;
}


VOID
CreateRandomValueFileIo2 (
  UINT32    *RandomValue
  )
{
  *RandomValue = (((*RandomValue) * 1103515245 + 98765432) >> 16) % 9999;
}

