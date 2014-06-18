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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    SimpleFileSystemConformanceTest.c

Abstract:
    for EFI Simple File System Protocol and EFI_FILE Protocol's Conformance Test

--*/

#include "SimpleFileSystemBBTest.h"

//
// some private functions declaration
//
VOID
CreateRandomValue (
  UINT32    *RandomValue
  );

/**
 *  @brief Entrypoint for Open() Conformance Test.
 *         6 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.1
//
EFI_STATUS
BBTestOpenConformanceTest (
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
  // 5.2.1.2.1  Call Open() to open non-existent file.
  //
  BBTestOpenConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.2.1.2.2  Call Open() to create a file under non-existent directory.
  //
  BBTestOpenConformanceTestCheckpoint2 (StandardLib, SimpleFileSystem);
  //
  // 5.2.1.2.3  Call Open() with invalid OpenMode.
  //
  BBTestOpenConformanceTestCheckpoint3 (StandardLib, SimpleFileSystem);

  //
  // 5.2.1.2.4  Call Open() with Unacceptable FileName.
  //
  // Remove from SCT, because this case is not stated in EFI spec 1.1
  //
  // BBTestOpenConformanceTestCheckpoint4 (StandardLib, SimpleFileSystem);

  //
  // 5.2.1.2.5  Call Open() to try to create file under a file
  // (not a directory).
  //
  //Remove from SCT, because this case is not stated in EFI spec 1.1
  //
  //BBTestOpenConformanceTestCheckpoint5 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Delete() Conformance test
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.2
//
EFI_STATUS
BBTestDeleteConformanceTest (
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
  // 5.2.2.2.1  Call Delete() to try to delete the root directory.
  //
  BBTestDeleteConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Write() Conformance test
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.3
//
EFI_STATUS
BBTestWriteConformanceTest (
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
  // 5.2.3.2.1  Call Write() to try to write data to a directory.
  //
  BBTestWriteConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.2.3.2.2  Call Write() to try to write data to a file
  // which has read-only attributes.
  //

  //
  // Following line is commented for developer's note.
  // Refer to Tracker#2332
  //

  //BBTestWriteConformanceTestCheckpoint2 (StandardLib, SimpleFileSystem);

  //
  // 5.2.3.2.3  Call Write() to try to write data to a file
  // which was opened read-only.
  //
  BBTestWriteConformanceTestCheckpoint3 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Flush() Conformance test
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.4
//
EFI_STATUS
BBTestFlushConformanceTest (
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
  // 5.2.4.2.1  Call Flush() to try to flush data to a file
  // which has read-only attributes.
  //

  //
  // Following line is commented for developer's note.
  // Refer to Tracker#2333
  //

  //BBTestFlushConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.2.4.2.2  Call Flush() to try to flush data to a file
  // which was opened read-only.
  //
  BBTestFlushConformanceTestCheckpoint2 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For SetPosition() Conformance test
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.5
//
EFI_STATUS
BBTestSetPositionConformanceTest (
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
  // 5.2.5.2.1  Call SetPosition() to try to set non-zero value to a directory.
  //
  BBTestSetPositionConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For GetPosition() Conformance test
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.6
//
EFI_STATUS
BBTestGetPositionConformanceTest (
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
  // 5.2.6.2.1  Call GetPosition() to try to get file position from a directory.
  //
  BBTestGetPositionConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For GetInfo() Conformance test
 *         4 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.7
//
EFI_STATUS
BBTestGetInfoConformanceTest (
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
  // 5.2.7.2.1  Call GetInfo() with unsupported InformationType.
  //
  BBTestGetInfoConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.2.7.2.2  Call GetInfo() with small buffer size.
  //
  BBTestGetInfoConformanceTestCheckpoint2 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For SetInfo() Conformance test
 *         5 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.2.8
//
EFI_STATUS
BBTestSetInfoConformanceTest (
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
  // 5.2.8.2.1  Call SetInfo() with unsupported InformationType.
  //
  BBTestSetInfoConformanceTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.2.8.2.2  Call SetInfo() to try to set EFI_FILE_INFO for a file
  // which is read-only Opened.
  //

  //
  // Commented out following check point according to spec changed
  //
  BBTestSetInfoConformanceTestCheckpoint2 (StandardLib, SimpleFileSystem);

  //
  // 5.2.8.2.3  Call SetInfo() with smaller buffer size.
  //
  BBTestSetInfoConformanceTestCheckpoint3 (StandardLib, SimpleFileSystem);

  //
  // 5.2.8.2.4  Call SetInfo() to try to set invalid EFI_FILE_INFO content
  // to a file.
  //
  BBTestSetInfoConformanceTestCheckpoint4 (StandardLib, SimpleFileSystem);

  //
  // 5.2.8.2.5  Call SetInfo() to try to change the fields of
  // EFI_FILE_SYSTEM_INFO other than VolumeLabel.
  //
  BBTestSetInfoConformanceTestCheckpoint5 (StandardLib, SimpleFileSystem);

  // 5.2.8.2.5  Call SetInfo()to check its behavior on a read_only opened file
  BBTestSetInfoConformanceTestCheckpoint6 (StandardLib, SimpleFileSystem);

  // 5.2.8.2.7 Call SetInfo() to check  SetInfo() attempt to change the name of file to a file that is already present
  BBTestSetInfoConformanceTestCheckpoint7 (StandardLib, SimpleFileSystem);

  // 5.2.8.2.8 Call SetInfo() to check  when firmware media is read-only
  BBTestSetInfoConformanceTestCheckpoint8 (StandardLib, SimpleFileSystem);
	
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestOpenConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINT32                    RandomValue = 0;
  UINT32                    FileIndex;
  CHAR16                    RandomChars[10];
  CHAR16                    *BaseFileName = L"Non-existence_";
  CHAR16                    NewFileName[100];
  EFI_FILE                  *FileHandle;

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

  //
  // open 100 file & directory with the random name
  //
  for (FileIndex = 0; FileIndex < 2; FileIndex++) {
    //for (FileIndex = 0; FileIndex < 100 ; FileIndex++) {

    //
    // init
    //
    FileHandle = NULL;

    //
    // Create random file name
    //
    CreateRandomValue (&RandomValue);
    SctValueToHexStr (RandomChars, RandomValue, PREFIX_ZERO, sizeof (UINT32));
    SctStrCpy (NewFileName, BaseFileName);
    SctStrCat (NewFileName, RandomChars);

    //
    // open file
    //
    Status = Root->Open(
                     Root,
                     &FileHandle,
                     NewFileName,
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                     0
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if ((EFI_MEDIA_CHANGED == Status)
              || (EFI_WRITE_PROTECTED == Status)
              || (EFI_VOLUME_FULL == Status)) {

      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid001,
                   L"Open() Conformance Test - checkpoint1",
                   L"%a:%d: Status - %r, FileName - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NewFileName
                   );
    if (FileHandle != NULL) {
      FileHandle->Delete (FileHandle);
    }
  }
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestOpenConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINT32                    RandomValue;
  CHAR16                    RandomChars[100];
  CHAR16                    BaseDirName[100];
  CHAR16                    NewDirName[100];
  CHAR16                    FileName[100];
  CHAR16                    OpenFileName[MAX_STRING_LENGTH];
  EFI_FILE                  *FileHandle;
  UINTN                     FileNameLength;
  UINTN                     FileIndex;

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

  SctStrCpy (FileName, L"BBTestOpenConformanceTestCheckpoint2_File");
  SctStrCpy (BaseDirName, L"BBTestOpenConformanceTestCheckpoint2_");

  //
  // create 100 directory name with the random name
  //
  //for (FileIndex = 0; FileIndex < 100; FileIndex++) {
  for (FileIndex = 0; FileIndex < 2 ; FileIndex++) {

    //
    // init
    //
    FileHandle = NULL;

    //
    // Create random dir name
    //
    CreateRandomValue (&RandomValue);
    SctValueToHexStr (RandomChars, RandomValue, PREFIX_ZERO, sizeof (UINT32));
    SctStrCpy (NewDirName, BaseDirName);
    SctStrCat (NewDirName, RandomChars);

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
    SctStrCat (OpenFileName, NewDirName);

    //
    // "\" + DirName + "\"
    //
    FileNameLength = SctStrLen (OpenFileName);
    OpenFileName[FileNameLength] = '\\';
    OpenFileName[FileNameLength + 1] = 0;

    //
    // "\" + DirName + "\" + FileName
    //
    SctStrCat (OpenFileName, FileName);

    //
    // create file
    //
    Status = Root->Open (
                     Root,
                     &FileHandle,
                     OpenFileName,
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                     0
                     );
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if ((EFI_MEDIA_CHANGED == Status)
              || (EFI_WRITE_PROTECTED == Status)
              || (EFI_VOLUME_FULL == Status)) {

      AssertionType = EFI_TEST_ASSERTION_WARNING;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid002,
                   L"Open() Conformance Test - checkpoint2",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (FileHandle != NULL) {
      FileHandle->Delete (FileHandle);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestOpenConformanceTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *OpenHandle;
  UINTN                     ModeIndex;
  UINT64                    InvalidMode[] = {
                                  EFI_FILE_MODE_WRITE,
                                  EFI_FILE_MODE_CREATE,
                                  EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ,
                                  EFI_FILE_MODE_CREATE | EFI_FILE_MODE_WRITE,
                                  0,
                                  0xFFFFFFFFFFFFFF
                                };

  SctStrCpy (FileName, L"BBTestOpenConformanceTestCheckpoint3_File");

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
    return Status;
  }

  for (ModeIndex = 0; ModeIndex < sizeof (InvalidMode) / sizeof (UINT64); ModeIndex++) {

    //
    // init
    //
    OpenHandle = NULL;

    //
    // open file with invalid mode
    //
    Status = Root->Open (
                     Root,
                     &OpenHandle,
                     FileName,
                     InvalidMode[ModeIndex],
                     0
                     );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid003,
                   L"Open() Conformance Test - checkpoint3",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (OpenHandle != NULL) {
      OpenHandle->Close (OpenHandle);
    }
  }

  if (FileHandle != NULL) {
    FileHandle->Delete (FileHandle);
  }

  return EFI_SUCCESS;
}

CHAR16            UnacceptableFileName[][100] = {
                                {0},
                                {0x01, 0x41, 0},
                                {0x41, 0x01, 0},
                                {0x02, 0x42, 0},
                                {0x42, 0x02, 0},
                                {0x03, 0x43, 0},
                                {0x43, 0x03, 0},
                                {0x44, 0x04, 0},
                                {0x05, 0x45, 0},
                                {0x45, 0x05, 0},
                                {0x06, 0x46, 0},
                                {0x46, 0x06, 0},
                                {0x07, 0x47, 0},
                                {0x47, 0x07, 0},
                                {0x08, 0x48, 0},
                                {0x48, 0x08, 0},
                                {0x09, 0x49, 0},
                                {0x49, 0x09, 0},
                                {0x0A, 0x4A, 0},
                                {0x4A, 0x0A, 0},
                                {0x0B, 0x4B, 0},
                                {0x4B, 0x0B, 0},
                                {0x0C, 0x4C, 0},
                                {0x4C, 0x0C, 0},
                                {0x0D, 0x4D, 0},
                                {0x4D, 0x0D, 0},
                                {0x0E, 0x4E, 0},
                                {0x4E, 0x0E, 0},
                                {0x0F, 0x4F, 0},
                                {0x4F, 0x0F, 0},
                                {0x10, 0x50, 0},
                                {0x50, 0x10, 0},
                                {0x11, 0x51, 0},
                                {0x51, 0x11, 0},
                                {0x12, 0x52, 0},
                                {0x52, 0x12, 0},
                                {0x13, 0x53, 0},
                                {0x53, 0x13, 0},
                                {0x14, 0x54, 0},
                                {0x54, 0x14, 0},
                                {0x15, 0x55, 0},
                                {0x55, 0x15, 0},
                                {0x16, 0x56, 0},
                                {0x56, 0x16, 0},
                                {0x17, 0x57, 0},
                                {0x57, 0x17, 0},
                                {0x18, 0x58, 0},
                                {0x58, 0x18, 0},
                                {0x19, 0x59, 0},
                                {0x59, 0x19, 0},
                                {0x1A, 0x5A, 0},
                                {0x5A, 0x1A, 0},
                                {0x1B, 0x5B, 0},
                                {0x5B, 0x1B, 0},
                                {0x1C, 0x60, 0},
                                {0x60, 0x1C, 0},
                                {0x1D, 0x5D, 0},
                                {0x5D, 0x1D, 0},
                                {0x1E, 0x5E, 0},
                                {0x5E, 0x1E, 0},
                                {0x1F, 0x5F, 0},
                                {0x5F, 0x1F, 0},
                                L"\"a",
                                L"a\"",
                                L"*b",
                                L"b*",
                                L"/e",
                                L"e/",
                                L":f",
                                L"f:",
                                L"<g",
                                L"g<",
                                L">i",
                                L"i>",
                                L"?j",
                                L"j?",
                                L"|n",
                                L"n|"
                              };

EFI_STATUS
BBTestOpenConformanceTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *OpenHandle;
  UINTN                     FileIndex;
  UINTN                     FileNumber;

  FileNumber = sizeof (UnacceptableFileName) / sizeof (*UnacceptableFileName);

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

  for (FileIndex = 0; FileIndex < FileNumber; FileIndex++) {


    //
    // init
    //
    OpenHandle = NULL;
    FileHandle = NULL;

    //
    // create file with invalid file name
    //
    Status = Root->Open (
                     Root,
                     &FileHandle,
                     UnacceptableFileName[FileIndex],
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                     0
                     );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid004,
                   L"Open () Conformance Test - checkpoint4",
                   L"%a:%d: FileIndex- %d, FileName- %s, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIndex,
                   UnacceptableFileName[FileIndex],
                   Status
                   );
    if ((EFI_MEDIA_CHANGED == Status)
              || (EFI_WRITE_PROTECTED == Status)
              || (EFI_VOLUME_FULL == Status)) {

      AssertionType = EFI_TEST_ASSERTION_WARNING;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"Open() Conformance Test - checkpoint4",
                     L"%a:%d: open failure, Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
       return Status;
    }
    //
    // open file with invalid file name
    //
    Status = Root->Open (
                     Root,
                     &OpenHandle,
                     UnacceptableFileName[FileIndex],
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                     0
                     );
    if ((Status == EFI_NOT_FOUND) || (Status == EFI_INVALID_PARAMETER)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid005,
                   L"Open() Conformance Test - checkpoint4",
                   L"%a:%d: FileIndex - %d, FileName- %s, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileIndex,
                   UnacceptableFileName[FileIndex],
                   Status
                   );

    if (OpenHandle != NULL) {
      OpenHandle->Close (OpenHandle);
    }

    if (FileHandle != NULL) {
      FileHandle->Delete (FileHandle);
    }

  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestOpenConformanceTestCheckpoint5 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *PseudoDirHandle;
  CHAR16                    FileName[100];
  CHAR16                    PseudoDirName[100];

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

  //
  // init
  //
  PseudoDirHandle = NULL;
  FileHandle = NULL;
  SctStrCpy (FileName, L"BBTestOpenConformanceTestCheckpoint5_File");
  SctStrCpy (PseudoDirName, L"BBTestOpenConformanceTestCheckpoint5_Dir");

  //
  // create pseudo dir which actually is a file.
  //
  Status = Root->Open (
                   Root,
                   &PseudoDirHandle,
                   PseudoDirName,
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
    return Status;
  }

  //
  // create file under the pseudo directory (actually is a file)
  //
  Status = PseudoDirHandle->Open (
                              PseudoDirHandle,
                              &FileHandle,
                              FileName,
                              EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                              0
                              );
  if (Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid006,
                 L"Open() Conformance Test - checkpoint5",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (FileHandle != NULL) {
    FileHandle->Delete (FileHandle);
  }

  if (PseudoDirHandle != NULL) {
    PseudoDirHandle->Delete (PseudoDirHandle);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestDeleteConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;

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

  //
  // delete the Root Directory
  //

  Status = Root->Delete (Root);
  if (Status == EFI_WARN_DELETE_FAILURE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid007,
                 L"Delete() Conformance Test - checkpoint1",
                 L"%a:%d: Delete Root Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid008,
                 L"Delete() Conformance Test - checkpoint1",
                 L"%a:%d: Open Root Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestWriteConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *DirHandle;
  CHAR16                    DirName[100];
  UINT8                     Temp;
  UINTN                     TempSize;

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

  SctStrCpy (DirName, L"BBTestWriteConformanceTestCheckpoint1_Dir");

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
    return Status;
  }

  //
  // try to write to the directory
  //
  TempSize = sizeof (UINT8);
  Status = DirHandle->Write (DirHandle, &TempSize, &Temp);

  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid009,
                 L"Write() Conformance Test - checkpoint1",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  DirHandle->Delete (DirHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestWriteConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle;
  CHAR16                    FileName[100];
  UINT8                     Temp;
  UINTN                     TempSize;

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

  SctStrCpy (FileName, L"BBTestWriteConformanceTestCheckpoint2_File");

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
    return Status;
  }

  //
  // set the file attribute to EFI_FILE_READ_ONLY
  //
  Status = InternalSetFileAttribute (FileHandle, EFI_FILE_READ_ONLY);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalSetFileAttribute fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    FileHandle->Delete (FileHandle);
    return Status;
  }

  //
  // try to write to the Read-only file
  //
  TempSize = sizeof (UINT8);
  Status = FileHandle->Write (FileHandle, &TempSize, &Temp);

  if (Status == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid010,
                 L"Write() Conformance Test - checkpoint2",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  FileHandle->Delete (FileHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestWriteConformanceTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *OpenHandle;
  CHAR16                    FileName[100];
  UINT8                     Temp;
  UINTN                     TempSize;

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

  SctStrCpy (FileName, L"BBTestWriteConformanceTestCheckpoint3_File");

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
    FileHandle->Delete (FileHandle);
    return Status;
  }

  //
  // try to write to the Read-only opened file
  //
  TempSize = sizeof (UINT8);
  Status = OpenHandle->Write (OpenHandle, &TempSize, &Temp);

  if (Status == EFI_ACCESS_DENIED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid011,
                 L"Write() Conformance Test - checkpoint3",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  OpenHandle->Delete (OpenHandle);
  FileHandle->Delete (FileHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestFlushConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle;
  CHAR16                    FileName[100];

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

  SctStrCpy (FileName, L"BBTestFlushConformanceTestCheckpoint1_File");

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
    return Status;
  }

  //
  // set the file attribute to EFI_FILE_READ_ONLY
  //
  Status = InternalSetFileAttribute (FileHandle, EFI_FILE_READ_ONLY);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalSetFileAttribute fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    FileHandle->Delete (FileHandle);
    return Status;
  }

  //
  // try to flush to the Read-only file
  //
  Status = FileHandle->Flush (FileHandle);

  if (Status == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid012,
                 L"Flush() Conformance Test - checkpoint1",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  FileHandle->Delete (FileHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestFlushConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *OpenHandle;
  CHAR16                    FileName[100];

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

  SctStrCpy (FileName, L"BBTestFlushConformanceTestCheckpoint2_File");

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
    FileHandle->Delete (FileHandle);
    return Status;
  }

  //
  // try to flush to the Read-only opened file
  //
  Status = OpenHandle->Flush (OpenHandle);

  if (Status == EFI_ACCESS_DENIED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid013,
                 L"Flush() Conformance Test - checkpoint2",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  OpenHandle->Delete (OpenHandle);
  FileHandle->Delete (FileHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetPositionConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *DirHandle;
  CHAR16                    DirName[100];

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

  SctStrCpy (DirName, L"BBTestSetPositionConformanceTestCheckpoint1_Dir");

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
                   L"Create dir fail",
                   L"%a:%d: DirName - %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   DirName,
                   Status
                   );
    return Status;
  }

  //
  // Set non-zero position to the directory
  //
  Status = DirHandle->SetPosition (DirHandle, 0xFFFFFFFFFFFFFFFF);
  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid014,
                 L"SetPosition() Conformance Test - checkpoint1",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  DirHandle->Delete (DirHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetPositionConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *DirHandle;
  CHAR16                    DirName[100];
  UINT64                    Position;

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

  SctStrCpy (DirName, L"BBTestGetPositionConformanceTestCheckpoint1_Dir");

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
                   L"Create dir fail",
                   L"%a:%d: DirName - %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   DirName,
                   Status
                   );
    return Status;
  }

  //
  // Get position from a directory
  //
  Status = DirHandle->GetPosition (DirHandle, &Position);
  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid015,
                 L"GetPosition() Conformance Test - checkpoint1",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  DirHandle->Delete (DirHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetInfoConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle;
  CHAR16                    FileName[100];
  EFI_GUID                  UnsupportedInfoType =
                              {0x986dcfe, 0x90b8, 0x46bb, 0xb1, 0xbf, 0x1e, 0xfe, 0x9d, 0xd, 0xa2, 0x6b};
  UINT8                     TempInfo;
  UINTN                     TempSize;

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
  
  SctStrCpy (FileName, L"BBTestGetInfoConformanceTestCheckpoint1_File");

  //
  // create the file
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
    return Status;
  }

  //
  // retrieve unsupported info type for the file
  //
  TempSize = sizeof (UINT8);
  Status = FileHandle->GetInfo (FileHandle, &UnsupportedInfoType, &TempSize, &TempInfo);
  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid016,
                 L"GetInfo() Conformance Test - checkpoint1",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  FileHandle->Delete (FileHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetInfoConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle[2];
  CHAR16                    FileName[2][100];
  UINTN                     BufferSize;
  UINTN                     Index;
  UINT64                    Attribute[2] = {0, EFI_FILE_DIRECTORY};
  UINT8                     Temp;

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

  SctStrCpy (FileName[0], L"BBTestGetInfoConformanceTestCheckpoint2_File");
  SctStrCpy (FileName[1], L"BBTestGetInfoConformanceTestCheckpoint2_Dir");

  //
  // init
  //
  gtBS->SetMem (FileHandle, 2 * sizeof (EFI_FILE*), 0);

  for (Index = 0; Index < 2; Index++) {

    //
    // create the file (directory)
    //
    Status = Root->Open (
                     Root,
                     &FileHandle[Index],
                     FileName[Index],
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                     Attribute[Index]
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
                     FileName[Index],
                     Status
                     );
      goto Done;
    }
  }

  //
  // retrieve EFI_FILE_INFO with small buffer
  //
  for (Index = 0; Index < 2; Index++) {

    BufferSize = sizeof (UINT8);

    Status = FileHandle[Index]->GetInfo (
                                  FileHandle[Index],
                                  &gBlackBoxEfiFileInfoGuid,
                                  &BufferSize,
                                  &Temp
                                  );

    if (Status == EFI_BUFFER_TOO_SMALL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid017,
                   L"GetInfo() Conformance Test - checkpoint2",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // retrieve EFI_FILE_SYSTEM_INFO with small buffer
  //
  BufferSize = sizeof (UINT8);
  Status = Root->GetInfo (Root, &gBlackBoxEfiFileSystemInfoGuid, &BufferSize, &Temp);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid018,
                 L"GetInfo() Conformance Test - checkpoint2",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // retrieve EFI_FILE_SYSTEM_VOLUME_LABEL with small buffer
  //
  BufferSize = sizeof (UINT8);
  Status = Root->GetInfo (Root, &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid, &BufferSize, &Temp);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid019,
                 L"GetInfo() Conformance Test - checkpoint2",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
Done:

  for (Index = 0; Index < 2; Index++) {
    if (FileHandle[Index] != NULL) {
      FileHandle[Index]->Delete (FileHandle[Index]);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle;
  CHAR16                    FileName[100];
  EFI_GUID                  UnsupportedInfoType =
                              {0x986dcfe, 0x90b8, 0x46bb, 0xb1, 0xbf, 0x1e, 0xfe, 0x9d, 0xd, 0xa2, 0x6b};
  UINT8                     TempInfo;
  UINTN                     TempSize;
  UINTN                     BufferSize;
  EFI_FILE_SYSTEM_INFO      *FileSystemInfo = NULL;

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
  
  Status = InternalGetInfo (Root, &FileSystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //  Read-only media, Bypass checkpoint 1
  // 
  if (FileSystemInfo->ReadOnly == TRUE) {
    gtBS->FreePool (FileSystemInfo);
    return EFI_SUCCESS;
  } else {
    gtBS->FreePool (FileSystemInfo);
    FileSystemInfo = NULL;
  }
  
  
  SctStrCpy (FileName, L"BBTestSetInfoConformanceTestCheckpoint1_File");

  //
  // create the file
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
    return Status;
  }

  //
  // set unsupported info type for the file
  //
  TempSize = sizeof (UINT8);
  Status = FileHandle->SetInfo (FileHandle, &UnsupportedInfoType, TempSize, &TempInfo);
  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid020,
                 L"SetInfo() Conformance Test - checkpoint1",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  FileHandle->Delete (FileHandle);

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle[2];
  EFI_FILE                  *OpenHandle[2];
  CHAR16                    FileName[2][100];
  CHAR16                    ChangeFileName[100];
  UINTN                     BufferSize;
  UINTN                     Index;
  UINT64                    Attribute[2] = {0, EFI_FILE_DIRECTORY};
  EFI_FILE_INFO             *FileInfo;
  EFI_FILE_SYSTEM_INFO      *FileSystemInfo = NULL;

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

  Status = InternalGetInfo (Root, &FileSystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //  Read-only media, Bypass checkpoint 2
  // 
  if (FileSystemInfo->ReadOnly == TRUE) {
    gtBS->FreePool (FileSystemInfo);
    return EFI_SUCCESS;
  } else {
    gtBS->FreePool (FileSystemInfo);
    FileSystemInfo = NULL;
  }
  
  //
  // init
  //
  gtBS->SetMem (FileHandle, 2 * sizeof (EFI_FILE*), 0);
  gtBS->SetMem (OpenHandle, 2 * sizeof (EFI_FILE*), 0);
  SctStrCpy (FileName[0], L"BBTestSetInfoConformanceTestCheckpoint2_File");
  SctStrCpy (FileName[1], L"BBTestSetInfoConformanceTestCheckpoint2_Dir");

  for (Index = 0; Index < 2; Index++) {

    FileInfo = NULL;

    //
    // create the file (directory)
    //
    Status = Root->Open (
                     Root,
                     &FileHandle[Index],
                     FileName[Index],
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                     Attribute[Index]
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
                     FileName[Index],
                     Status
                     );
      goto NextLoop;
    }

    Status = InternalGetInfo (FileHandle[Index], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"InternalGetInfo fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }
    if (FileHandle[Index] != NULL) {
      FileHandle[Index]->Close (FileHandle[Index]);
    }
    //
    // open file for Read
    //
    Status = Root->Open (
                     Root,
                     &OpenHandle[Index],
                     FileName[Index],
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
                     FileName[Index],
                     Status
                     );
      goto NextLoop;
    }

    //
    // set info with the read-only opened file handle
    //

    FileInfo->FileSize = 0x100;

    Status = OpenHandle[Index]->SetInfo (
                                  OpenHandle[Index],
                                  &gBlackBoxEfiFileInfoGuid,
                                  BufferSize,
                                  FileInfo
                                  );

    if (Status == EFI_ACCESS_DENIED || Status == EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid021,
                   L"SetInfo() Conformance Test - checkpoint2 - change file size on read-only opened file or dir",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (OpenHandle[Index] != NULL) {
      OpenHandle[Index]->Close (OpenHandle[Index]);
      OpenHandle[Index] = NULL;
    }
    //
    // open file for Read again
    //
    Status = Root->Open (
                     Root,
                     &OpenHandle[Index],
                     FileName[Index],
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
                     FileName[Index],
                     Status
                     );
      goto NextLoop;
    }

    //
    // set info with the read-only opened file handle
    // change file name
    //

    SctStrCpy (ChangeFileName, L"BBTestSetInfoConfTestCheckpoint2_File_New");
    SctStrCpy (FileInfo->FileName, ChangeFileName);

    FileHandle[Index] = NULL;
    Status = Root->Open (
                     Root,
                     &FileHandle[Index],
                     ChangeFileName,
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                     Attribute[Index]
                     );

    if (FileHandle[Index] != NULL) {
      FileHandle[Index]->Delete (FileHandle[Index]);
    }

    Status = OpenHandle[Index]->SetInfo (
                                  OpenHandle[Index],
                                  &gBlackBoxEfiFileInfoGuid,
                                  BufferSize,
                                  FileInfo
                                  );

    if (Status == EFI_ACCESS_DENIED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid034,
                   L"SetInfo() Conformance Test - checkpoint2 - change file name on read-only opened file or dir",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

NextLoop:
    if (FileInfo != NULL) {
      gtBS->FreePool (FileInfo);
    }
    if (OpenHandle[Index] != NULL) {
      OpenHandle[Index] -> Close (OpenHandle[Index]);
      OpenHandle[Index] = NULL;
      Status = Root->Open (
                       Root,
                       &OpenHandle[Index],
                       FileName[Index],
                       EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                       Attribute[Index]
                       );
    }
    if (OpenHandle[Index] != NULL) {
      OpenHandle[Index]->Delete (OpenHandle[Index]);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle[2];
  CHAR16                    FileName[2][100];
  UINTN                     BufferSize;
  UINTN                     Index;
  UINT64                    Attribute[2] = {0, EFI_FILE_DIRECTORY};
  EFI_FILE_INFO             *FileInfo = NULL;
  EFI_FILE_SYSTEM_INFO      *SystemInfo = NULL;
  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO   *VolumeLabel = NULL;

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

  Status = InternalGetInfo (Root, &SystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //  Read-only media, Bypass checkpoint 3
  // 
  if (SystemInfo->ReadOnly == TRUE) {
    gtBS->FreePool (SystemInfo);
    return EFI_SUCCESS;
  } else {
    gtBS->FreePool (SystemInfo);
    SystemInfo = NULL;
  }

  //
  // init
  //
  gtBS->SetMem (FileHandle, 2 * sizeof (EFI_FILE*), 0);
  SctStrCpy (FileName[0], L"BBTestSetInfoConformanceTestCheckpoint3_File");
  SctStrCpy (FileName[1], L"BBTestSetInfoConformanceTestCheckpoint3_Dir");

  for (Index = 0; Index < 2; Index++) {

    //
    // create the file (directory)
    //
    Status = Root->Open (
                     Root,
                     &FileHandle[Index],
                     FileName[Index],
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                     Attribute[Index]
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
                     FileName[Index],
                     Status
                     );
      goto Done;
    }
  }

  //
  // Set EFI_FILE_INFO with small buffer
  //
  BufferSize = sizeof (UINT8);
  for (Index = 0; Index < 2; Index++) {

    FileInfo = NULL;

    //
    // get info first
    //
    Status = InternalGetInfo (FileHandle[Index], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"InternalGetInfo fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    BufferSize = SIZE_OF_EFI_FILE_INFO - 1;
    Status = FileHandle[Index]->SetInfo (
                                  FileHandle[Index],
                                  &gBlackBoxEfiFileInfoGuid,
                                  BufferSize,
                                  FileInfo
                                  );

    if (Status == EFI_BAD_BUFFER_SIZE) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid022,
                   L"SetInfo() Conformance Test - checkpoint3",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
NextLoop:
    if (FileInfo != NULL) {
      gtBS->FreePool (FileInfo);
    }
  }

  //
  // set EFI_FILE_SYSTEM_INFO with small buffer
  //

  // retrieve system info first
  Status = InternalGetInfo (Root, &SystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  BufferSize = SIZE_OF_EFI_FILE_SYSTEM_INFO - 1;
  Status = Root->SetInfo (Root, &gBlackBoxEfiFileSystemInfoGuid, BufferSize, SystemInfo);
  if (Status == EFI_BAD_BUFFER_SIZE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid023,
                 L"SetInfo() Conformance Test - checkpoint3",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Set EFI_FILE_SYSTEM_VOLUME_LABEL with small buffer
  //

  // retrieve volume label first
  Status = InternalGetInfo (Root, &VolumeLabel, &BufferSize, &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  BufferSize = 1;
  Status = Root->SetInfo (Root, &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid, BufferSize, VolumeLabel);
  if (Status == EFI_BAD_BUFFER_SIZE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid024,
                 L"SetInfo() Conformance Test - checkpoint3",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
Done:

  for (Index = 0; Index < 2; Index++) {
    if (FileHandle[Index] != NULL) {
      FileHandle[Index]->Delete (FileHandle[Index]);
    }
  }

  if (SystemInfo != NULL) {
    gtBS->FreePool (SystemInfo);
  }

  if (VolumeLabel != NULL) {
    gtBS->FreePool (VolumeLabel);
  }
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle[2];
  CHAR16                    FileName[2][100];
  UINTN                     BufferSize;
  UINTN                     Index;
  UINT64                    Attribute[2];
  UINT64                    FileInvalidAttribute[2];
  UINT64                    DirInvalidAttribute[2];
  EFI_FILE_INFO             *FileInfo = NULL;
  UINTN                     FileNumber;
  UINT64                    SavedSize;
  UINT64                    SavedPhysicalSize;
  UINT64                    SavedAttribute;
  EFI_FILE_SYSTEM_INFO      *FileSystemInfo = NULL;

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

  Status = InternalGetInfo (Root, &FileSystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //  Read-only media, Bypass checkpoint 4
  // 
  if (FileSystemInfo->ReadOnly == TRUE) {
    gtBS->FreePool (FileSystemInfo);
    return EFI_SUCCESS;
  } else {
    gtBS->FreePool (FileSystemInfo);
    FileSystemInfo = NULL;
  }
  
  //
  // init
  //
  gtBS->SetMem (FileHandle, 2 * sizeof (EFI_FILE*), 0);

  FileNumber = sizeof (UnacceptableFileName) / sizeof (*UnacceptableFileName);

  SctStrCpy (FileName[0], L"BBTestSetInfoConformanceTestCheckpoint4_File");
  SctStrCpy (FileName[1], L"BBTestSetInfoConformanceTestCheckpoint4_Dir");

  Attribute[0] = 0;
  Attribute[1] = EFI_FILE_DIRECTORY;

  DirInvalidAttribute[0] = 0;
  DirInvalidAttribute[1] = (UINT64)(~EFI_FILE_VALID_ATTR);

  FileInvalidAttribute[0] = EFI_FILE_DIRECTORY;
  FileInvalidAttribute[1] = DirInvalidAttribute[1];

  for (Index = 0; Index < 2; Index++) {

    FileInfo = NULL;

    //
    // create the file (directory)
    //
    Status = Root->Open (
                     Root,
                     &FileHandle[Index],
                     FileName[Index],
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                     Attribute[Index]
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
                     FileName[Index],
                     Status
                     );
      goto Done;
    }
  }

  //
  // set file size for the file
  //
  Status = InternalSetFileSize (FileHandle[0], 100);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalSetFileSize fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName[0],
                   Status
                   );
    goto Done;
  }

  Status = InternalGetInfo (FileHandle[0], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName[0],
                   Status
                   );
    goto Done;
  }

  //
  // save the original FileInfo
  //
  SavedSize = FileInfo->Size;
  SavedPhysicalSize = FileInfo->PhysicalSize;
  SavedAttribute = FileInfo->Attribute;

  //
  // set file info for the file
  //
  //
  // EFI_FILE_INFO.Size < sizeof (EFI_FILE_INFO)
  // EFI_FILE_INFO.PhysicalSize < EFI_FILE_INFO.Size.
  // Invalid Attributes
  //
  for (Index = 0; Index < 2; Index++) {

    FileInfo->Size = SIZE_OF_EFI_FILE_INFO - 1;
    FileInfo->PhysicalSize = FileInfo->FileSize - 1;
    FileInfo->Attribute= FileInvalidAttribute[Index];

    Status = FileHandle[0]->SetInfo (FileHandle[0], &gBlackBoxEfiFileInfoGuid, BufferSize, FileInfo);

    //
    // free FileInfo
    //
    gtBS->FreePool (FileInfo);
    FileInfo = NULL;

    //
    // check the FileInfo is not updated
    //
    Status = InternalGetInfo (FileHandle[0], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);

    if ((SavedSize == FileInfo->Size)
        && (SavedPhysicalSize == FileInfo->PhysicalSize)
        && (SavedAttribute == FileInfo->Attribute)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid025,
                   L"SetInfo() Conformance Test - checkpoint4",
                   L"%a:%d: FileName- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName[0]
                   );
  }

  if (FileInfo != NULL) {
    gtBS->FreePool (FileInfo);
    FileInfo = NULL;
  }

  Status = InternalGetInfo (FileHandle[0], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName[0],
                   Status
                   );
    goto Done;
  }


  //
  // set file info for the file
  //
  //  Invalid File Name as Appendix D list.
  //  (since the length of those invalid file names are shorter than
  //   the original file name, so there is no need to re-allocate the FileInfo)
  //
  for (Index = 0; Index < FileNumber; Index++) {

    SctStrCpy (FileInfo->FileName, UnacceptableFileName[Index]);

    Status = FileHandle[0]->SetInfo (FileHandle[0], &gBlackBoxEfiFileInfoGuid, BufferSize, FileInfo);

    //
    // free FileInfo
    //
    gtBS->FreePool (FileInfo);
    FileInfo = NULL;

    //
    // check the FileInfo is not updated
    //
    Status = InternalGetInfo (FileHandle[0], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);

    //
    // should not match
    //
    if (SctStrCmp (FileInfo->FileName, UnacceptableFileName[Index])) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid026,
                   L"SetInfo() Conformance Test - checkpoint4",
                   L"%a:%d: FileName- %s,InvalidFileName- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileInfo->FileName,
                   UnacceptableFileName[Index]
                   );
  }

  if (FileInfo != NULL) {
    gtBS->FreePool (FileInfo);
    FileInfo = NULL;
  }

  //
  // for the directory
  //

  Status = InternalGetInfo (FileHandle[1], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName[1],
                   Status
                   );
    goto Done;
  }

  //
  // save the original FileInfo
  //
  SavedSize = FileInfo->Size;
  SavedPhysicalSize = FileInfo->PhysicalSize;
  SavedAttribute = FileInfo->Attribute;

  //
  // set file info for the file
  //
  //
  // EFI_FILE_INFO.Size < sizeof (EFI_FILE_INFO)
  // EFI_FILE_INFO.PhysicalSize < EFI_FILE_INFO.Size.
  // Invalid Attributes
  //
  for (Index = 0; Index < 2; Index++) {

    FileInfo->Size = SIZE_OF_EFI_FILE_INFO - 1;
    FileInfo->PhysicalSize = FileInfo->FileSize - 1;
    FileInfo->Attribute= DirInvalidAttribute[Index];

    Status = FileHandle[1]->SetInfo (FileHandle[1], &gBlackBoxEfiFileInfoGuid, BufferSize, FileInfo);

    //
    // free FileInfo
    //
    gtBS->FreePool (FileInfo);
    FileInfo = NULL;

    //
    // check the FileInfo is not updated
    //
    Status = InternalGetInfo (FileHandle[1], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);

    if ((SavedSize == FileInfo->Size)
        && (SavedPhysicalSize == FileInfo->PhysicalSize)
        && (SavedAttribute == FileInfo->Attribute)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid027,
                   L"SetInfo() Conformance Test - checkpoint4",
                   L"%a:%d: FileName- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName[1]
                   );
  }

  if (FileInfo != NULL) {
    gtBS->FreePool (FileInfo);
    FileInfo = NULL;
  }

  Status = InternalGetInfo (FileHandle[1], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName[1],
                   Status
                   );
    goto Done;
  }


  //
  // set file info for the directory
  //
  //  Invalid File Name as Appendix D list.
  //  (since the length of those invalid file names are shorter than
  //   the original file name, so there is no need to re-allocate the FileInfo)
  //
  for (Index = 0; Index < FileNumber; Index++) {

    SctStrCpy (FileInfo->FileName, UnacceptableFileName[Index]);

    Status = FileHandle[1]->SetInfo (FileHandle[1], &gBlackBoxEfiFileInfoGuid, BufferSize, FileInfo);

    //
    // free FileInfo
    //
    gtBS->FreePool (FileInfo);
    FileInfo = NULL;

    //
    // check the FileInfo is not updated
    //
    Status = InternalGetInfo (FileHandle[1], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);

    //
    // should not match
    //
    if (SctStrCmp (FileInfo->FileName, UnacceptableFileName[Index])) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gSimpleFileSystemConformanceTestAssertionGuid028,
                   L"SetInfo() Conformance Test - checkpoint4",
                   L"%a:%d: FileName- %s,InvalidFileName- %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileInfo->FileName,
                   UnacceptableFileName[Index]
                   );
  }

Done:

  for (Index = 0; Index < 2; Index++) {
    if (FileHandle[Index] != NULL) {
      FileHandle[Index]->Delete (FileHandle[Index]);
    }
  }

  if (FileInfo != NULL) {
    gtBS->FreePool (FileInfo);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint5 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     BufferSize;
  EFI_FILE_SYSTEM_INFO      *SystemInfo = NULL;
  EFI_FILE_SYSTEM_INFO      SavedSystemInfo;

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

  Status = InternalGetInfo (Root, &SystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //  Read-only media, Bypass checkpoint 5
  // 
  if (SystemInfo->ReadOnly == TRUE) {
    gtBS->FreePool (SystemInfo);
    return EFI_SUCCESS;
  } else {
    gtBS->FreePool (SystemInfo);
    SystemInfo = NULL;
  }
  
  //
  // init
  //
  SystemInfo = NULL;

  Status = InternalGetInfo (Root, &SystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // save the system info
  //
  SavedSystemInfo = *SystemInfo;

  //
  // modify the System Info
  //
  SystemInfo->Size -= 1;
  SystemInfo->ReadOnly = (BOOLEAN)(!(SystemInfo->ReadOnly));
  SystemInfo->VolumeSize -= 100;
  SystemInfo->FreeSpace += 1000;
  SystemInfo->BlockSize += 29;

  Status = Root->SetInfo (Root, &gBlackBoxEfiFileSystemInfoGuid, BufferSize, SystemInfo);

  gtBS->FreePool (SystemInfo);
  SystemInfo = NULL;

  Status = InternalGetInfo (Root, &SystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  if ((SystemInfo->Size == SavedSystemInfo.Size)
      && (SystemInfo->ReadOnly == SavedSystemInfo.ReadOnly)
      && (SystemInfo->VolumeSize == SavedSystemInfo.VolumeSize)
      && (SystemInfo->FreeSpace == SavedSystemInfo.FreeSpace)
      && (SystemInfo->BlockSize == SavedSystemInfo.BlockSize)) {

    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid029,
                 L"SetInfo() Conformance Test - checkpoint5",
                 L"%a:%d: System should not be changed",
                 __FILE__,
                 (UINTN)__LINE__
                 );
Done:

  if (SystemInfo != NULL) {
    gtBS->FreePool (SystemInfo);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint6 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle;
  CHAR16                    FileName[100];

  UINTN                     BufferSize;
//  UINTN                     Index;
 // UINT64                    Attribute = EFI_FILE_READ_ONLY;
  EFI_FILE_INFO             *FileInfo = NULL;
  EFI_FILE_SYSTEM_INFO      *SystemInfo = NULL;
  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO   *VolumeLabel = NULL;

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
  
  Status = InternalGetInfo (Root, &SystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //  Read-only media, Bypass checkpoint 6
  // 
  if (SystemInfo->ReadOnly == TRUE) {
    gtBS->FreePool (SystemInfo);
    return EFI_SUCCESS;
  } 
  
  //
  // init
  //

  SctStrCpy (FileName, L"BBTestSetInfoConformanceTestCheckpoint6_File");

  //
  // create the read-only file
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
    return Status;
  }


  BufferSize = sizeof (UINT8);

  FileInfo = NULL;

  //
  // get info first
  //
  Status = InternalGetInfo (FileHandle, &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto NextLoop;
  }
  //
  // Set read-only file attribute
  //
  FileInfo->Attribute = EFI_FILE_READ_ONLY;
  BufferSize = SIZE_OF_EFI_FILE_INFO;

  Status = FileHandle->SetInfo (
                         FileHandle,
                         &gBlackBoxEfiFileInfoGuid,
                         (UINTN)(BufferSize + 0x1000),
                         FileInfo
                         );

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid030,
                 L"SetInfo() Conformance Test - checkpoint6 - Set EFI_FILE_INFO",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = FileHandle->Close (FileHandle);

  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Close filehandle fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto NextLoop;
  }
  FileHandle = NULL;

  Status = Root->Open (
                   Root,
                   &FileHandle,
                   FileName,
                   EFI_FILE_MODE_READ,
                   0
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Open read_only file fail",
                   L"%a:%d: FileName- %s,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileName,
                   Status
                   );
    goto NextLoop;
  }


  //
  // Set EFI_FILE_INFO with small buffer
  //
  BufferSize = sizeof (UINT8);

  FileInfo = NULL;

  //
  // get info first
  //
  Status = InternalGetInfo (FileHandle, &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto NextLoop;
  }
  if (FileInfo->Attribute != EFI_FILE_READ_ONLY)
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemConformanceTestAssertionGuid031,
                   L"InternalGetInfo fail,FileInfo->Attribute should be EFI_FILE_READONLY ",
                   L"%a:%d: Status - %r, Attribute- 0x%lx",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   FileInfo->Attribute
                   );
    goto NextLoop;
  }

  FileInfo->Attribute = 0;
  BufferSize = SIZE_OF_EFI_FILE_INFO;

  Status = FileHandle->SetInfo (
                         FileHandle,
                         &gBlackBoxEfiFileInfoGuid,
                         (UINTN)(BufferSize + 0x1000),
                         FileInfo
                         );

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid032,
                 L"SetInfo() Conformance Test - checkpoint6 - Set EFI_FILE_INFO, Change Attribute to 0",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  Status = InternalGetInfo (FileHandle, &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto NextLoop;
  }
  if (FileInfo->Attribute != 0)
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gSimpleFileSystemConformanceTestAssertionGuid033,
                   L"InternalGetInfo fail,FileInfo->Attribute should be 0 ",
                   L"%a:%d: Status - %r , File Attribute - 0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   FileInfo->Attribute
                   );
    goto NextLoop;
  }
NextLoop:
  if (FileInfo != NULL) {
    gtBS->FreePool (FileInfo);
  }
  if (FileHandle != NULL) {
    FileHandle -> Close (FileHandle);
    FileHandle = NULL;
    Status = Root->Open (
                     Root,
                     &FileHandle,
                     FileName,
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                     0
                     );
  }
  if (FileHandle != NULL) {
    Status = FileHandle->Delete (FileHandle);
  }
  if (SystemInfo != NULL) {
    gtBS->FreePool (SystemInfo);
  }

  if (VolumeLabel != NULL) {
    gtBS->FreePool (VolumeLabel);
  }
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint7 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  EFI_FILE                  *FileHandle[2];
  CHAR16                    FileName[2][100];
  UINTN                     BufferSize;
  UINTN                     Index;
  UINT64                    Attribute[2];
  EFI_FILE_INFO             *FileInfo = NULL;
  EFI_FILE_SYSTEM_INFO      *FileSystemInfo = NULL;

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
 
  Status = InternalGetInfo (Root, &FileSystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  //  Read-only media, Bypass checkpoint 7
  // 
  if (FileSystemInfo->ReadOnly == TRUE) {
    gtBS->FreePool (FileSystemInfo);
    return EFI_SUCCESS;
  } else {
    gtBS->FreePool (FileSystemInfo);
    FileSystemInfo = NULL;
  }
  

  //
  // init
  //
  gtBS->SetMem (FileHandle, 2 * sizeof (EFI_FILE*), 0);


  SctStrCpy (FileName[0], L"BBTestSetInfoConformanceTestCheckpoint7_File_One");
  SctStrCpy (FileName[1], L"BBTestSetInfoConformanceTestCheckpoint7_File_Two");
	

  Attribute[0] = 0;
  Attribute[1] = 0;


  for (Index = 0; Index < 2; Index++) {

    FileInfo = NULL;

    //
    // create the file (directory)
    //
    Status = Root->Open (
                     Root,
                     &FileHandle[Index],
                     FileName[Index],
                     EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                     Attribute[Index]
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
                     FileName[Index],
                     Status
                     );
      goto Done;
    }
  }

	//
  // get info first
  //
  Status = InternalGetInfo (FileHandle[0], &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }
	
	// change one file to a file name already exists 
	// !! be carefull new file name should be same as or smaller than original file name 
	// otherwise we should reallocate pool & change FileInfo->Size 
	SctStrCpy (FileInfo->FileName, L"BBTestSetInfoConformanceTestCheckpoint7_File_Two");

	Status = FileHandle[0]->SetInfo (
                            FileHandle[0],
                            &gBlackBoxEfiFileInfoGuid,
                            BufferSize,
                            FileInfo
                            );

	// according to UEFI 2.3 spec, interface must return EFI_ACCESS_DENIED
  if (Status == EFI_ACCESS_DENIED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid035,
                 L"SetInfo() Conformance Test - checkpoint7 - change file name to an existing file or dir",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
	

Done:
  if (FileInfo != NULL) {
    gtBS->FreePool (FileInfo);
  }
 
  for (Index = 0; Index < 2; Index++) {
    if (FileHandle[Index] != NULL) {
      FileHandle[Index]->Delete (FileHandle[Index]);
    }
  }

  return EFI_SUCCESS;

}

EFI_STATUS
BBTestSetInfoConformanceTestCheckpoint8 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     BufferSize;
  EFI_FILE_INFO             *FileInfo = NULL;
  EFI_FILE_SYSTEM_INFO      *FileSystemInfo = NULL;
  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO      *FileSystemLabel = NULL;

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

  // 1. ===================== test system volume info ========================
  //
  // get system volume info  from Root directory
  //
  Status = InternalGetInfo (Root, &FileSystemInfo, &BufferSize, &gBlackBoxEfiFileSystemInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }
  
  // if file media is not read-only, skip test
  if (FileSystemInfo->ReadOnly == FALSE) {
    goto Done;
  }

  // change file system info volume label & test it on a read-only media
  *(FileSystemInfo->VolumeLabel) += 1;
  Status = Root->SetInfo (
                   Root,
                   &gBlackBoxEfiFileSystemInfoGuid,
                   BufferSize,
                   FileSystemInfo
                   );
	 
  // according to UEFI 2.3 spec, interface must return EFI_WRITE_PROTECTED
  if (Status == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid036,
                 L"SetInfo() Conformance Test - checkpoint8 - change file system info on a read only media",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // 2. ===================== test system volume label ========================
  //
  // get system volume label from Root directory
  //
  Status = InternalGetInfo (Root, &FileSystemLabel, &BufferSize, &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  // change file system info volume label first letter & test it on a read-only media
  *(FileSystemLabel->VolumeLabel) += 2;
  Status = Root->SetInfo (
                   Root,
                   &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid,
                   BufferSize,
                   FileSystemLabel
                   );
  
  // according to UEFI 2.3 spec, interface must return EFI_WRITE_PROTECTED
  if (Status == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid037,
                 L"SetInfo() Conformance Test - checkpoint8 - change file system label on a read only media",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
 
  // 3. ======================= test file info ==========================
  //
  // get root directory file info  
  //
  Status = InternalGetInfo (Root, &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"InternalGetInfo fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }
  
  // change file info to read-only for test
  FileInfo->Attribute |= EFI_FILE_READ_ONLY;
  Status = Root->SetInfo (
                   Root,
                   &gBlackBoxEfiFileInfoGuid,
                   BufferSize,
                   FileInfo
                   );
  
  // according to UEFI 2.3 spec, interface must return EFI_WRITE_PROTECTED
  if (Status == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gSimpleFileSystemConformanceTestAssertionGuid038,
                 L"SetInfo() Conformance Test - checkpoint8 - change root directory attribute on a read only media",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
 
		
Done:
  if (FileInfo != NULL) {
    gtBS->FreePool (FileInfo);
  }
 
  if (FileSystemInfo != NULL) {
    gtBS->FreePool (FileSystemInfo);
  }
 
  if (FileSystemLabel != NULL) {
    gtBS->FreePool (FileSystemLabel);
  }

  return EFI_SUCCESS;

}


VOID
CreateRandomValue (
  UINT32    *RandomValue
  )
{
  *RandomValue = (((*RandomValue) * 1103515245 + 98765432) >> 16) % 9999;
}
