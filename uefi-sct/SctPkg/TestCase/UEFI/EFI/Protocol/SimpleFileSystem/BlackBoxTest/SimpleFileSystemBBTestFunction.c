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
    SimpleFileSystemBasicTest.c

Abstract:
    for EFI Simple File System Protocol and EFI_FILE Protocol's Basic Test

--*/

#include "SimpleFileSystemBBTest.h"

#define VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE    8   // zero-based
#define ALL_ATTRIBUTES_COUNT_FOR_CREATE                16

#define MAX_NUMBER_OF_FILE_NAME   1000

CHAR16 ValidFileBaseName[][30] = {
                              L"u",
                              L"h_jsf77",
                              L"sf_h+8~a",
                              L"was09=$iw",
                              L"a2~isudfoi01f98w7r7%01'-f@a",
                              L"!123",
                              L"wx#12`A;--0B",
                              L"[abc123]][()]"
                              };
CHAR16 ValidExtensionName[][15]={L"", L"1", L"u2", L"sf_", L"0404", L"g_=fs+lkd11", L"Aa [b"};

UINT64 ValidAttributesForCreate[] = {
  0,
  EFI_FILE_HIDDEN,
  EFI_FILE_SYSTEM,
  EFI_FILE_ARCHIVE,
  EFI_FILE_HIDDEN | EFI_FILE_SYSTEM,
  EFI_FILE_HIDDEN | EFI_FILE_ARCHIVE,
  EFI_FILE_SYSTEM | EFI_FILE_ARCHIVE,
  EFI_FILE_HIDDEN | EFI_FILE_SYSTEM | EFI_FILE_ARCHIVE,
  //
  // below are for directory
  //
  EFI_FILE_DIRECTORY,
  EFI_FILE_DIRECTORY | EFI_FILE_HIDDEN,
  EFI_FILE_DIRECTORY | EFI_FILE_SYSTEM,
  EFI_FILE_DIRECTORY | EFI_FILE_ARCHIVE,
  EFI_FILE_DIRECTORY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM,
  EFI_FILE_DIRECTORY | EFI_FILE_HIDDEN | EFI_FILE_ARCHIVE,
  EFI_FILE_DIRECTORY | EFI_FILE_SYSTEM | EFI_FILE_ARCHIVE,
  EFI_FILE_DIRECTORY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM | EFI_FILE_ARCHIVE
  };

//
// some private functions declaration
//
EFI_STATUS
ComposeFileNameArray (
  CHAR16        **PureFileNameArray,
  UINT32        *NameCount
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test5 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test5 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  );

VOID
InvertFileAttributes (
  EFI_FILE_INFO   *FileInfo
  );


/**
 *  @brief For OpenVolume() basic test
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.1
//
EFI_STATUS
EFIAPI
BBTestOpenVolumeBasicTest (
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
  // 5.1.1.2.1  OpenVolume() Basic Functionality
  //
  BBTestOpenVolumeBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Open() basic test
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.2
//
EFI_STATUS
EFIAPI
BBTestOpenBasicTest (
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
  // 5.1.2.2.1  Call Open() to create new files(directories)
  // with valid file names and valid attributes.
  //
  BBTestOpenBasicTestCheckpoint1 (StandardLib, SimpleFileSystem, FALSE);

  //
  // 5.1.2.2.2  Call Open() to Open existing files with all valid OpenMode.
  //
  BBTestOpenBasicTestCheckpoint2 (StandardLib, SimpleFileSystem, FALSE);

  return EFI_SUCCESS;
}

/**
 *  @brief For Close() basic test
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.3
//
EFI_STATUS
EFIAPI
BBTestCloseBasicTest (
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
  // 5.1.3.2.1  Close() Basic Functionality
  //
  BBTestCloseBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Delete() basic test
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.4
//
EFI_STATUS
EFIAPI
BBTestDeleteBasicTest (
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
  // 5.1.4.2.1  Call Delete() to delete a normal file.
  //
  BBTestDeleteBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.1.4.2.2  Call Delete() to delete empty directory.
  //
  BBTestDeleteBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);

  //
  // 5.1.4.2.3  Call Delete() to delete nonempty directory.
  //
  BBTestDeleteBasicTestCheckpoint3 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Read() basic test
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.5
//
EFI_STATUS
EFIAPI
BBTestReadBasicTest (
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
  // 5.1.5.2.1  Call Read() to read data from a file.
  //
  BBTestReadBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.1.5.2.2  Call Read() to read data from a directory.
  //
  BBTestReadBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Write() basic test
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.6
//
EFI_STATUS
EFIAPI
BBTestWriteBasicTest (
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
  // 5.1.6.2.1  Call Write() to write data into a normal file.
  //
  BBTestWriteBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For Flush() basic test
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.7
//
EFI_STATUS
EFIAPI
BBTestFlushBasicTest (
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
  // 5.1.7.2.1  Flush() a normal file.
  //
  BBTestFlushBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.1.7.2.2  Flush() a directory.
  //
  BBTestFlushBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For SetPosition() basic test
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.8
//
EFI_STATUS
EFIAPI
BBTestSetPositionBasicTest (
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
  // 5.1.8.2.1  SetPosition() to a file.
  //
  BBTestSetPositionBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  //
  // 5.1.8.2.2  Call SetPosition() to set zero position to a directory.
  //
  BBTestSetPositionBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For GetPosition() basic test
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.9
//
EFI_STATUS
EFIAPI
BBTestGetPositionBasicTest (
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
  // 5.1.9.2.1  Get current position of a file
  //
  BBTestGetPositionBasicTestCheckpoint1 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}


/**
 *  @brief For GetInfo() basic test
 *         4 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.10
//
EFI_STATUS
EFIAPI
BBTestGetInfoBasicTest (
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
  // 5.1.10.2.1  Call GetInfo() to retrieve EFI_FILE_INFO
  // from a file/directory.
  //
  BBTestGetInfoBasicTestCheckpoint1 (StandardLib, SimpleFileSystem, FALSE);

  //
  // 5.1.10.2.2  Call GetInfo() to retrieve EFI_FILE_INFO
  // from the root directory.
  //
  BBTestGetInfoBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);

  //
  // 5.1.10.2.3  Call GetInfo() to retrieve EFI_FILE_SYSTEM_INFO
  // from the root directory.
  //
  BBTestGetInfoBasicTestCheckpoint3 (StandardLib, SimpleFileSystem);

  //
  // 5.1.10.2.4  Call GetInfo() to retrieve EFI_FILE_SYSTEM_VOLUME_LABEL
  // from the root directory.
  //
  BBTestGetInfoBasicTestCheckpoint4 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

/**
 *  @brief For SetInfo() basic test
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 5.1.11
//
EFI_STATUS
EFIAPI
BBTestSetInfoBasicTest (
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
  // 5.1.11.2.1 Call SetInfo() to set valid EFI_FILE_INFO for a file/directory.
  //
  BBTestSetInfoBasicTestCheckpoint1 (StandardLib, SimpleFileSystem, FALSE);

  //
  // 5.1.11.2.2 Call SetInfo() to set valid EFI_FILE_SYSTEM_INFO
  // for the root directory.
  //
  BBTestSetInfoBasicTestCheckpoint2 (StandardLib, SimpleFileSystem);

  //
  // 5.1.11.2.3 Call SetInfo() to set EFI_FILE_SYSTEM_VOLUME_LABEL
  // for the root directory.
  //
  BBTestSetInfoBasicTestCheckpoint3 (StandardLib, SimpleFileSystem);

  return EFI_SUCCESS;
}

VOID
ReadOnlyDirCheck (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root, 
  CHAR16                                *DirName,
  EFI_FILE_INFO                         *DirInfo
  )
{
  EFI_TEST_ASSERTION    AssertionType;
  EFI_STATUS            Status, Status1, Status2;
  EFI_FILE              *DirHandle;
  EFI_FILE_INFO         Info;
  UINTN                 InfoSize;
  UINT8                 *Buffer;

  EFI_GUID              UnsupportedInfoType =
                              {0x986dcfe, 0x90b8, 0x46bb, {0xb1, 0xbf, 0x1e, 0xfe, 0x9d, 0xd, 0xa2, 0x6b}};

  Status1 = Root->Open (
                    Root,
                    &DirHandle,
                    DirName,
                    EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                    0
                    );
 
  Status2 = Root->Open (
                    Root,
                    &DirHandle,
                    DirName,
                    EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                    0
                    );
  if (Status1 == EFI_WRITE_PROTECTED && Status2 == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid008,
                   L"ReadOnly System - Open Dir with invalid mode",
                   L"%a:%d: ReadOnly System: Open Dir should be failed, Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                  );


  Status = Root->Open (
                   Root,
                   &DirHandle,
                   L"InvalidName",
                   EFI_FILE_MODE_READ,
                   0
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid009,
                   L"ReadOnly System - Open Dir with InvalidName",
                   L"%a:%d: ReadOnly System: Open Dir should be failed, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );

  
  Status = Root->Open (
                   Root,
                   &DirHandle,
                   DirName,
                   EFI_FILE_MODE_READ,
                   0
                   );

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid010,
                   L"ReadOnly System - Open File with read mode",
                   L"%a:%d: ReadOnly System: Open File should be success, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    return;
  }  

  //
  // retrieve unsupported info type for the file
  //
  InfoSize = sizeof (UINT8);
  Status = DirHandle->GetInfo (DirHandle, &UnsupportedInfoType, &InfoSize, &Info);
  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid011,
                 L"ReadOnly System - GetInfo with unsupported GUID",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  InfoSize = sizeof (UINT8);
  Status = DirHandle->GetInfo (DirHandle, &gBlackBoxEfiFileInfoGuid, &InfoSize, &Info);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid012,
                 L"ReadOnly System - GetInfo with small buffer size",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 ); 
  
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    return;
  }

  Buffer = NULL;
  Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     InfoSize,
                     (VOID**)&Buffer
                     );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Allocate Pool fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return;
  }

  Status = DirHandle->GetInfo (DirHandle, &gBlackBoxEfiFileInfoGuid, &InfoSize, (VOID*)Buffer);
  if (Status == EFI_SUCCESS && InfoSize == DirInfo->Size) {
    if (SctCompareMem (Buffer, DirInfo, InfoSize) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid013,
                 L"ReadOnly System - GetInfo with correct paremeters, the outputs should be correct",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 ); 
  
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    return;
  }

  Status1 = DirHandle->SetInfo (DirHandle, &gBlackBoxEfiFileInfoGuid, InfoSize, (VOID*)Buffer);
  Status2 = DirHandle->SetInfo (DirHandle, &UnsupportedInfoType, InfoSize, (VOID*)Buffer);

  if (Status1 == EFI_WRITE_PROTECTED && Status2 == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid014,
                 L"ReadOnly System - SetInfo, the returned status should be EFI_WRITE_PROTECTED and EFI_UNSUPPORTED",
                 L"%a:%d: Status1 - %r, Status2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status1,
                 Status2
                 ); 
  
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    return;
  }  

  Status = DirHandle->Delete (DirHandle);
  if (Status == EFI_WARN_DELETE_FAILURE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } 

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid019,
                 L"ReadOnly System - Delete, the returned status should be EFI_WARN_DELETE_FAILURE",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    return;
  }  


  Status1 = Root->Open (
                   Root,
                   &DirHandle,
                   DirName,
                   EFI_FILE_MODE_READ,
                   0
                   );

  Status2 = DirHandle->Close (DirHandle);
  if (Status1 == EFI_SUCCESS && Status2 == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid020,
                 L"ReadOnly System - Close, the returned status should be EFI_SUCCESS",
                 L"%a:%d: Status2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status2
                 );  

  SctFreePool(Buffer);

  return;
}


VOID
ReadOnlyFileCheck (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root, 
  CHAR16                                *FileName,
  EFI_FILE_INFO                         *FileInfo
  )
{
  EFI_TEST_ASSERTION    AssertionType;
  EFI_STATUS            Status, Status1, Status2, Status3;
  EFI_FILE              *FileHandle;
  EFI_FILE_INFO         Info;
  UINTN                 InfoSize;
  UINT8                 *Buffer;
  UINT8                 *FileBuf;
  UINTN                 FileBufSize;
  UINT64                Position;
  UINT8                 Buf[10];
  UINTN                 Size;
  UINT8                 Index;

  EFI_GUID              UnsupportedInfoType =
                              {0x986dcfe, 0x90b8, 0x46bb, {0xb1, 0xbf, 0x1e, 0xfe, 0x9d, 0xd, 0xa2, 0x6b }};

  Status1 = Root->Open (
                    Root,
                    &FileHandle,
                    FileName,
                    EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE,
                    0
                    );
 
  Status2 = Root->Open (
                    Root,
                    &FileHandle,
                    FileName,
                    EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                    0
                    );
  if (Status1 == EFI_WRITE_PROTECTED && Status2 == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid008,
                   L"ReadOnly System - Open File with invalid mode",
                   L"%a:%d: ReadOnly System: Open File should be failed, Status1 - %r, Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                  );


  Status = Root->Open (
                   Root,
                   &FileHandle,
                   L"InvalidName",
                   EFI_FILE_MODE_READ,
                   0
                   );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid009,
                   L"ReadOnly System - Open File with InvalidName",
                   L"%a:%d: ReadOnly System: Open File should be failed, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );

  
  Status = Root->Open (
                   Root,
                   &FileHandle,
                   FileName,
                   EFI_FILE_MODE_READ,
                   0
                   );

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid010,
                   L"ReadOnly System - Open File with read mode",
                   L"%a:%d: ReadOnly System: Open File should be success, Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                  );
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    return;
  }  

  //
  // retrieve unsupported info type for the file
  //
  InfoSize = sizeof (UINT8);
  Status = FileHandle->GetInfo (FileHandle, &UnsupportedInfoType, &InfoSize, &Info);
  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid011,
                 L"ReadOnly System - GetInfo with unsupported GUID",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );  

  InfoSize = sizeof (UINT8);
  Status = FileHandle->GetInfo (FileHandle, &gBlackBoxEfiFileInfoGuid, &InfoSize, &Info);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid012,
                 L"ReadOnly System - GetInfo with small buffer size",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 ); 
  
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    return;
  }

  Buffer = NULL;
  Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     InfoSize,
                     (VOID**)&Buffer
                     );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Allocate Pool fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return;
  }

  Status = FileHandle->GetInfo (FileHandle, &gBlackBoxEfiFileInfoGuid, &InfoSize, (VOID*)Buffer);
  if (Status == EFI_SUCCESS && InfoSize == FileInfo->Size) {
    if (SctCompareMem (Buffer, FileInfo, InfoSize) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid013,
                 L"ReadOnly System - GetInfo with correct paremeters, the outputs should be correct",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 ); 
  
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    return;
  }

  Status1 = FileHandle->SetInfo (FileHandle, &gBlackBoxEfiFileInfoGuid, InfoSize, (VOID*)Buffer);
  Status2 = FileHandle->SetInfo (FileHandle, &UnsupportedInfoType, InfoSize, (VOID*)Buffer);

  if (Status1 == EFI_WRITE_PROTECTED && Status2 == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid014,
                 L"ReadOnly System - SetInfo, the returned status should be EFI_WRITE_PROTECTED and EFI_UNSUPPORTED",
                 L"%a:%d: Status1 - %r, Status2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status1,
                 Status2
                 ); 
  
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    return;
  }  

  Status = FileHandle->GetPosition (FileHandle, &Position);
  if (Status == EFI_SUCCESS && Position >= 0 && Position <= FileInfo->FileSize) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid015,
                 L"ReadOnly System - GetPosition, the returned status should be EFI_SUCCESS and Position is one reasonable value",
                 L"%a:%d: Status - %r, Position - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Position
                 );   
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    return;
  }

  Status = FileHandle->Write (FileHandle, &InfoSize, (VOID*)Buffer);
  if (Status == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid016,
                 L"ReadOnly System - Write, the returned status should be EFI_WRITE_PROTECTED",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    return;
  }


  Status = FileHandle->Flush (FileHandle);
  if (Status == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid017,
                 L"ReadOnly System - Flush, the returned status should be EFI_WRITE_PROTECTED",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    return;
  }  

  FileBufSize = (UINTN)FileInfo->FileSize;

  Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     FileBufSize,
                     (VOID**)&FileBuf
                     );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Allocate Pool fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    SctFreePool(Buffer);
    return;
  }  
  
  Status1 = FileHandle->SetPosition (FileHandle, 0);
  Status2 = FileHandle->Read (FileHandle, &FileBufSize, FileBuf);
  Status3 = FileHandle->GetPosition (FileHandle, &Position);

  if (Status1 == EFI_SUCCESS && Status2 == EFI_SUCCESS && Status3 == EFI_SUCCESS && 
    FileBufSize == FileInfo->FileSize && Position == FileBufSize) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (FileBufSize > 20) {
      Size = 10;
      FileHandle->SetPosition (FileHandle, 0);
      FileHandle->Read (FileHandle, &Size, Buf);
      for (Index = 0; Index < 10 ; Index++) {
        if (Buf[Index] != FileBuf[Index])
          break;
      }
      if (Index != 10) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      FileHandle->Read (FileHandle, &Size, Buf);
      for (Index = 0; Index < 10 ; Index++) {
        if (Buf[Index] != FileBuf[Index + 10])
          break;
      }
      if (Index != 10) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      FileHandle->SetPosition (FileHandle, Position - 10);
      FileHandle->Read (FileHandle, &Size, Buf);
      for (Index = 0; Index < 10 ; Index++) {

        if (Buf[Index] != *(FileBuf + Position - 10 + Index))
          break;
      }
      if (Index != 10) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid018,
                 L"ReadOnly System - Read/SetPosition, the operation should be correct",
                 L"%a:%d: ",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    SctFreePool(FileBuf);
    return;
  }  

  Status = FileHandle->Delete (FileHandle);
  if (Status == EFI_WARN_DELETE_FAILURE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } 

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid019,
                 L"ReadOnly System - Delete, the returned status should be EFI_WARN_DELETE_FAILURE",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    SctFreePool(Buffer);
    SctFreePool(FileBuf);
    return;
  }  


  Status1 = Root->Open (
                   Root,
                   &FileHandle,
                   FileName,
                   EFI_FILE_MODE_READ,
                   0
                   );

  Status2 = FileHandle->Close (FileHandle);
  if (Status1 == EFI_SUCCESS && Status2 == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid020,
                 L"ReadOnly System - Close, the returned status should be EFI_SUCCESS",
                 L"%a:%d: Status2 - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status2
                 );  

  SctFreePool(Buffer);
  SctFreePool(FileBuf);

  return;
}



VOID
BBTestReadOnlyTestCheckPoints (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib, 
  EFI_FILE                              *Root, 
  EFI_FILE_SYSTEM_INFO                  *SystemInfo,
  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO     *VolumeInfo,
  EFI_FILE_INFO                         *FileInfo
  )
{
  EFI_TEST_ASSERTION    AssertionType;
  UINTN                 BufSize;
  EFI_FILE_INFO         *Info;
  EFI_STATUS            Status, Status1, Status2;
  BOOLEAN               File;
  BOOLEAN               Dir;
  CHAR16                *FileName;
  CHAR16                *DirName;
  UINT64                Position;
/*
  if (SystemInfo->ReadOnly && (FileInfo->Attribute & EFI_FILE_READ_ONLY) != 0 ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid001,
                   L"ReadOnly System - checkpoint1",
                   L"%a:%d: ReadOnly System: ReadOnly attribute should be aligned in SystemInfo and FileInfo. ReadOnly - %d, Attribute - 0x%x",
                   __FILE__,
                   (UINTN)__LINE__,
                   SystemInfo->ReadOnly,
                   FileInfo->Attribute
                  );
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    return;
  }
*/
  Status = Root->SetPosition (Root, 1);
  if (Status != EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }	
  
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid002,
                   L"ReadOnly System: Dir SetPosition 1 fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  if (Status != EFI_UNSUPPORTED) {
    return;
  }


  Status = Root->SetPosition (Root, 0);
  if (Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid003,
                   L"ReadOnly System: Dir SetPosition 0 Success",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  if (Status != EFI_SUCCESS) {
    return;
  }

  Status = Root->GetPosition (Root, &Position);
  if (Status != EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid004,
                   L"ReadOnly System: Dir GetPosition should be unsupported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  if (Status != EFI_UNSUPPORTED) {
    return;
  }
  

  Status1 = Root->SetInfo (Root, &gBlackBoxEfiFileSystemInfoGuid, (UINTN)(SystemInfo->Size), (VOID*)SystemInfo);
  Status2 = Root->SetInfo (Root, &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid, SctStrLen(VolumeInfo->VolumeLabel), (VOID*)VolumeInfo);
  if (Status1 == EFI_WRITE_PROTECTED && Status2 == EFI_WRITE_PROTECTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }


  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid005,
                   L"ReadOnly System: Dir SetInfo should return EFI_WRITE_PROTECTED",
                   L"%a:%d: Status1 - %r Status2 - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2
                   );

  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    return;
  }


  //To find one file in system.

  BufSize = SIZE_OF_EFI_FILE_INFO + 1024;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   BufSize,
                   (VOID**)&Info
                   );
  if (Status != EFI_SUCCESS ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"Allocate Pool fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return;    
  }
 

  Status = Root->Write (Root, &BufSize, (VOID*)Info);
  if (Status == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gReadOnlyFileSystemBBTestAssertionGuid006,
                   L"ReadOnly System: Dir Write should be unsupported",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  if (Status != EFI_UNSUPPORTED) {
    SctFreePool(Info);
    return;
  }


  BufSize = SIZE_OF_EFI_FILE_INFO;
  Status  = Root->Read (Root, &BufSize, Info);
  if (Status == EFI_BUFFER_TOO_SMALL || (Status == EFI_SUCCESS && BufSize == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gReadOnlyFileSystemBBTestAssertionGuid007,
                 L"ReadOnly System: Dir Read should be EFI_BUFFER_TOO_SMALL with the limited buffer size or EFI_SUCCESS when no dirs and files",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (Status != EFI_BUFFER_TOO_SMALL) {
    SctFreePool(Info);
    return;
  }
  

  File = FALSE;
  Dir  = FALSE;

  do {
    BufSize = SIZE_OF_EFI_FILE_INFO + 1024;
    Status  = Root->Read (Root, &BufSize, Info);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Read fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      break;  
    }

    if (Info->Attribute & EFI_FILE_DIRECTORY) {
      DirName = Info->FileName;
      if (Dir == FALSE)
        ReadOnlyDirCheck(StandardLib, Root, DirName, Info);
      Dir = TRUE;
    } else {
      FileName = Info->FileName;
      if (File == FALSE)
        ReadOnlyFileCheck(StandardLib, Root, FileName, Info);
      File = TRUE;
    }

    if (BufSize == 0)
      break;

  } while (File == FALSE || Dir == FALSE);
 
  SctFreePool (Info);
  return;
}

EFI_STATUS
EFIAPI
BBTestOpenVolumeBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  UINTN                     BufferSize;
  EFI_FILE_INFO             *FileInfo;
  EFI_FILE_SYSTEM_INFO      *SystemInfo;
  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO   *VolumeLabel;
  EFI_STATUS                Status1, Status2;
  EFI_GUID                  TplGuid;

  EFI_GUID                   *InfoType[] = {
                                &gBlackBoxEfiFileInfoGuid,
                                &gBlackBoxEfiFileSystemInfoGuid,
                                &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid
                              };

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Init
    //
    FileInfo = NULL;
    SystemInfo = NULL;
    VolumeLabel = NULL;

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      if (EFI_NO_MEDIA == Status || EFI_MEDIA_CHANGED == Status || EFI_UNSUPPORTED == Status || EFI_ACCESS_DENIED == Status) {
        AssertionType = EFI_TEST_ASSERTION_WARNING;
      }
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid001;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid002;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"OpenVolume() Basic Test - checkpoint1",
                   L"%a:%d: OpenVolume Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                  );
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //
    // retrieve EFI_FILE_INFO
    //
    Status = InternalGetInfo (Root, (VOID **) &FileInfo, &BufferSize, InfoType[0]);
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid003;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid004;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"OpenVolume() Basic Test - checkpoint1",
                   L"%a:%d: GetInfo (Fileinfo) Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                  );
    if (!EFI_ERROR (Status)) {

      //
      // check EFI_FILE_INFO.Attribute & EFI_FILE_DIRECTORY != 0
      //
      if ((FileInfo->Attribute & EFI_FILE_DIRECTORY) != 0) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid005;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid006;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"OpenVolume() Basic Test - checkpoint1",
                     L"%a:%d: Root's Attribute - 0x%lx, TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     FileInfo->Attribute,
                     TplArray[Index]
                    );
    }

    //
    // retrieve EFI_FILE_SYSTEM_INFO
    //

    Status1 = InternalGetInfo (Root, (VOID **) &SystemInfo, &BufferSize, InfoType[1]);
    if (EFI_SUCCESS == Status1) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid007;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid008;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"OpenVolume() Basic Test - checkpoint1",
                   L"%a:%d: GetInfo (SystemInfo) Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   TplArray[Index]
                  );


    //
    // retrieve EFI_FILE_SYSTEM_VOLUME_LABEL
    //
    Status2 = InternalGetInfo (Root, (VOID **) &VolumeLabel, &BufferSize, InfoType[2]);
    if (EFI_SUCCESS == Status2) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid009;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid010;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"OpenVolume() Basic Test - checkpoint1",
                   L"%a:%d: GetInfo (VolumeLabel) Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status2,
                   TplArray[Index]
                  );

    //
    // VolumeLable equals with EFI_FILE_SYSTEM_INFO.VolumeLabel
    //
    if (!EFI_ERROR (Status1) && !EFI_ERROR (Status2)) {
      if (!SctStrCmp (SystemInfo->VolumeLabel, VolumeLabel->VolumeLabel)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid011;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid012;
    }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"OpenVolume() Basic Test - checkpoint1",
                     L"%a:%d: Compare (VolumeLabel), TPL - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     TplArray[Index]
                    );
    }

    //
    // insert the checkpoints for read-only system
	//
    if (SystemInfo->ReadOnly) {
      BBTestReadOnlyTestCheckPoints (StandardLib, Root, SystemInfo, VolumeLabel, FileInfo);
	}    


    //
    // could not delete root directory
    //
    Status = Root->Delete (Root);
    if (EFI_WARN_DELETE_FAILURE == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid013;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid014;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"OpenVolume() Basic Test - checkpoint1",
                   L"%a:%d: Delete Root Status- %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   TplArray[Index]
                  );

    //
    // free resources
    //

    if (FileInfo != NULL) {
      gtBS->FreePool (FileInfo);
    }

    if (SystemInfo != NULL) {
      gtBS->FreePool (SystemInfo);
    }

    if (VolumeLabel != NULL) {
      gtBS->FreePool (VolumeLabel);
    }
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  CHAR16                    *PureFileNameArray;
  UINT32                    Count;

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

  Status = ComposeFileNameArray (&PureFileNameArray, &Count);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ComposeFileNameArray fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                 );
    return Status;
  }

  //
  // Test 1: one directory level
  // Source: Root
  // FileName: pure file name (no other nodes)
  //
  Status = BBTestOpenBasicTestCheckpoint1_Test1 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Test 2: 2 directory levels
  // Source: Root
  // FileName: file name with directory node (subdir\filename)
  //
  Status = BBTestOpenBasicTestCheckpoint1_Test2 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  //
  // Test 3: 2 directory levels
  // Source: Sub directory
  // FileName: pure file name
  //
  Status = BBTestOpenBasicTestCheckpoint1_Test3 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  //
  // Test 4: 3 directory levels (subdir1\subdir2\filename)
  // Source: level 1 directory (subdir1)
  // FileName: file name with directory node (subdir2\filename)
  //
  Status = BBTestOpenBasicTestCheckpoint1_Test4 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  //
  // Test 5: 3 directory levels
  // Source: level 2 directory (subdir2)
  // FileName: file name with directory node (\subdir1\subdir2\filename)
  //
  Status = BBTestOpenBasicTestCheckpoint1_Test5 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );

Done:
  if (PureFileNameArray != NULL) {
    gtBS->FreePool (PureFileNameArray);
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *FileHandle;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  EFI_STATUS                Status;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  CHAR16                    *PureStrPointer;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex; NameIndex++, PureStrPointer += MAX_STRING_LENGTH) {

      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {

        FileHandle = NULL;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);

        Status = Root->Open (
                         Root,
                         &FileHandle,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[AttributesIndex]
                         );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else if ((EFI_MEDIA_CHANGED == Status)
                  || (EFI_WRITE_PROTECTED == Status)
                  || (EFI_VOLUME_FULL == Status)) {

          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid015;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid016;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Open() Basic Test - checkpoint1",
                       L"%a:%d: Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                      );

        if (FileHandle != NULL) {
          FileHandle->Delete (FileHandle);
        }
      }
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *DirHandle;
  UINT32                    DirAttributesIndex;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  CHAR16                    *FileNameArray, *StrPointer, *PureStrPointer;
  EFI_STATUS                Status;
  UINTN                     ArraySize;
  UINTN                     Index;
  UINTN                     FileNameLength;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // prepare file name "subdir" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  gtBS->SetMem (FileNameArray, ArraySize * sizeof (CHAR16), 0);

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  for (Loop = 0; Loop < FixedNameCount; Loop++) {
    SctStrCpy (StrPointer, PureStrPointer);
    FileNameLength = SctStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    SctStrCat (StrPointer, PureStrPointer);

    PureStrPointer += MAX_STRING_LENGTH;
    StrPointer += MAX_STRING_LENGTH;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    StrPointer = FileNameArray;
    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
         StrPointer += MAX_STRING_LENGTH, PureStrPointer += MAX_STRING_LENGTH, NameIndex++) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
            DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {

        DirHandle = NULL;

        //
        // create sub directory first
        //
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);

        Status = Root->Open (
                         Root,
                         &DirHandle,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[DirAttributesIndex]
                         );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else if ((EFI_MEDIA_CHANGED == Status)
                  || (EFI_WRITE_PROTECTED == Status)
                  || (EFI_VOLUME_FULL == Status)) {

          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid017;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid018;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Open() Basic Test - checkpoint1",
                       L"%a:%d: create directory Status - %r, dir name - %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       PureStrPointer
                      );

        if (EFI_ERROR (Status)) {
          goto Done;
        }

        for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex;
              AttributesIndex++) {

          //
          // create file under the created directory
          //
          FileHandle = NULL;

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = Root->Open (
                           Root,
                           &FileHandle,
                           StrPointer,
                           EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                           ValidAttributesForCreate[AttributesIndex]
                           );
          gtBS->RestoreTPL (OldTpl);

          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;

          } else if ((EFI_MEDIA_CHANGED == Status)
                    || (EFI_WRITE_PROTECTED == Status)
                    || (EFI_VOLUME_FULL == Status)) {

            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid019;
          } else {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid020;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"Open() Basic Test - checkpoint1",
                         L"%a:%d: create file Status - %r, FileName - %s",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         StrPointer
                        );

          if (EFI_SUCCESS == Status) {
            FileHandle->Delete (FileHandle);
          } else {
            goto DirClean;
          }
        }
DirClean:
        if (DirHandle != NULL) {
          Status = DirHandle->Delete (DirHandle);
          DirHandle = NULL;
        }
        if (EFI_ERROR (Status)) {
          goto Done;
        }
      }
    }
  }

Done:

  gtBS->FreePool (FileNameArray);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *DirHandle;
  UINT32                    DirAttributesIndex;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  EFI_STATUS                Status;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  CHAR16                    *PureStrPointer;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
        NameIndex++, PureStrPointer += MAX_STRING_LENGTH) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
            DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {

        DirHandle = NULL;

        //
        // create sub directory first
        //
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = Root->Open (
                         Root,
                         &DirHandle,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[DirAttributesIndex]
                         );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else if ((EFI_MEDIA_CHANGED == Status)
                  || (EFI_WRITE_PROTECTED == Status)
                  || (EFI_VOLUME_FULL == Status)) {

          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid021;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid022;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Open() Basic Test - checkpoint1",
                       L"%a:%d: create directory Status - %r, dir name - %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       PureStrPointer
                      );

        if (EFI_ERROR (Status)) {
          return Status;
        }

        for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex;
              AttributesIndex++) {

          //
          // create file under the created directory
          // source is DirHandle
          //
          FileHandle = NULL;

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = DirHandle->Open (
                                DirHandle,
                                &FileHandle,
                                PureStrPointer,
                                EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                ValidAttributesForCreate[AttributesIndex]
                                );
          gtBS->RestoreTPL (OldTpl);

          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;

          } else if ((EFI_MEDIA_CHANGED == Status)
                    || (EFI_WRITE_PROTECTED == Status)
                    || (EFI_VOLUME_FULL == Status)) {

            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid023;
          } else {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid024;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"Open() Basic Test - checkpoint1",
                         L"%a:%d: create file Status - %r, FileName - %s",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         PureStrPointer
                        );

          if (EFI_SUCCESS == Status) {
            FileHandle->Delete (FileHandle);
          } else {
            goto DirClean;
          }
        }
DirClean:
        if (DirHandle != NULL) {
          Status = DirHandle->Delete (DirHandle);
        }
        if (EFI_ERROR (Status)) {
          return Status;
        }
      }
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *DirHandle1;
  EFI_FILE                  *DirHandle2;
  UINT32                    DirAttributesIndex;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  CHAR16                    *FileNameArray;
  EFI_STATUS                Status;
  UINTN                     ArraySize;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     FileNameLength;
  CHAR16                    *StrPointer, *PureStrPointer;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  for (Loop = 0; Loop < FixedNameCount; Loop++) {
    SctStrCpy (StrPointer, PureStrPointer);
    FileNameLength = SctStrLen (PureStrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    SctStrCat (StrPointer, PureStrPointer);

    StrPointer += MAX_STRING_LENGTH;
    PureStrPointer += MAX_STRING_LENGTH;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    StrPointer = FileNameArray;
    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
    StrPointer += MAX_STRING_LENGTH, PureStrPointer += MAX_STRING_LENGTH, NameIndex++) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
            DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {

        DirHandle1 = NULL;
        DirHandle2 = NULL;

        //
        // create sub directory 1 first
        //
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = Root->Open (
                         Root,
                         &DirHandle1,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[DirAttributesIndex]
                         );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else if ((EFI_MEDIA_CHANGED == Status)
                  || (EFI_WRITE_PROTECTED == Status)
                  || (EFI_VOLUME_FULL == Status)) {

          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid025;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid026;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Open() Basic Test - checkpoint1",
                       L"%a:%d: create directory 1 Status - %r, dir name - %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       PureStrPointer
                      );

        if (EFI_ERROR (Status)) {
          goto Done;
        }

        //
        // create sub directory 2
        //
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = DirHandle1->Open (
                               DirHandle1,
                               &DirHandle2,
                               PureStrPointer,
                               EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                               ValidAttributesForCreate[DirAttributesIndex]
                               );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else if ((EFI_MEDIA_CHANGED == Status)
                  || (EFI_WRITE_PROTECTED == Status)
                  || (EFI_VOLUME_FULL == Status)) {

          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid027;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid028;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Open() Basic Test - checkpoint1",
                       L"%a:%d: create directory 2 Status - %r, dirname - %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       PureStrPointer
                      );
        if (EFI_ERROR (Status)) {
          goto Dir1Clean;
        }

        for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex;
              AttributesIndex++) {

          //
          // create file under the created directory
          //
          FileHandle = NULL;

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = DirHandle1->Open (
                                 DirHandle1,
                                 &FileHandle,
                                 StrPointer,
                                 EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                 ValidAttributesForCreate[AttributesIndex]
                                 );
          gtBS->RestoreTPL (OldTpl);

          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;

          } else if ((EFI_MEDIA_CHANGED == Status)
                    || (EFI_WRITE_PROTECTED == Status)
                    || (EFI_VOLUME_FULL == Status)) {

            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid029;
          } else {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid030;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"Open() Basic Test - checkpoint1",
                         L"%a:%d: create file Status - %r, FileName - %s",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         StrPointer
                        );

          if (EFI_SUCCESS == Status) {
            FileHandle->Delete (FileHandle);
          } else {
            goto Dir2Clean;
          }
        }

Dir2Clean:
        if (DirHandle2 != NULL) {
          Status = DirHandle2->Delete (DirHandle2);
        }

Dir1Clean:
        if (DirHandle1 != NULL) {
          Status = DirHandle1->Delete (DirHandle1);
        }

        if (EFI_ERROR (Status)) {
          goto Done;
        }
      }
    }
  }

Done:

  gtBS->FreePool (FileNameArray);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1_Test5 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *DirHandle1;
  EFI_FILE                  *DirHandle2;
  UINT32                    DirAttributesIndex;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINT32                    Loop;
  CHAR16                    *FileNameArray;
  EFI_STATUS                Status;
  UINTN                     ArraySize;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     FileNameLength;
  CHAR16                    *StrPointer, *PureStrPointer;
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }

  //
  // prepare file name "\" + subdir1 + "\" + subdir2 + "\" + filename
  //
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  for (Loop = 0; Loop < FixedNameCount; Loop++) {

    //
    // "\"
    //
    StrPointer[0] = '\\';
    StrPointer[1] = 0;

    //
    // "\" + subdir1
    //
    SctStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\"
    //
    FileNameLength = SctStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2
    //
    SctStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\" + subdir2 + "\"
    //
    FileNameLength = SctStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2 + "\" + filename
    //
    SctStrCat (StrPointer, PureStrPointer);

    StrPointer += MAX_STRING_LENGTH;
    PureStrPointer += MAX_STRING_LENGTH;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    StrPointer = FileNameArray;
    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
        StrPointer += MAX_STRING_LENGTH, PureStrPointer += MAX_STRING_LENGTH, NameIndex++) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
            DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {

        DirHandle1 = NULL;
        DirHandle2 = NULL;

        //
        // create sub directory 1 first
        //
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = Root->Open (
                         Root,
                         &DirHandle1,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[DirAttributesIndex]
                         );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else if ((EFI_MEDIA_CHANGED == Status)
                  || (EFI_WRITE_PROTECTED == Status)
                  || (EFI_VOLUME_FULL == Status)) {

          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid031;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid032;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Open() Basic Test - checkpoint1",
                       L"%a:%d: create directory 1 Status - %r, DirName - %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       PureStrPointer
                       );

        if (EFI_ERROR (Status)) {
          goto Done;
        }

        //
        // create sub directory 2
        //
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = DirHandle1->Open (
                               DirHandle1,
                               &DirHandle2,
                               PureStrPointer,
                               EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                               ValidAttributesForCreate[DirAttributesIndex]
                               );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else if ((EFI_MEDIA_CHANGED == Status)
                  || (EFI_WRITE_PROTECTED == Status)
                  || (EFI_VOLUME_FULL == Status)) {

          AssertionType = EFI_TEST_ASSERTION_WARNING;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid033;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid034;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Open() Basic Test - checkpoint1",
                       L"%a:%d: create directory 2 Status - %r, DirName - %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       PureStrPointer
                       );
        if (EFI_ERROR (Status)) {
          goto Dir1Clean;
        }

        for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex;
              AttributesIndex++) {

          //
          // create file under the created directory
          //
          FileHandle = NULL;

          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = DirHandle2->Open (
                                 DirHandle2,
                                 &FileHandle,
                                 StrPointer,
                                 EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                 ValidAttributesForCreate[AttributesIndex]
                                 );
          gtBS->RestoreTPL (OldTpl);

          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;

          } else if ((EFI_MEDIA_CHANGED == Status)
                    || (EFI_WRITE_PROTECTED == Status)
                    || (EFI_VOLUME_FULL == Status)) {

            AssertionType = EFI_TEST_ASSERTION_WARNING;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }

          if (Index == 0) {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid035;
          } else {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid036;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"Open() Basic Test - checkpoint1",
                         L"%a:%d: create file Status - %r, FileName - %s",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         StrPointer
                         );

          if (EFI_SUCCESS == Status) {
            FileHandle->Delete (FileHandle);
          } else {
            goto Dir2Clean;
          }
        }

Dir2Clean:
        if (DirHandle2 != NULL) {
          Status = DirHandle2->Delete (DirHandle2);
        }

Dir1Clean:
        if (DirHandle1 != NULL) {
          Status = DirHandle1->Delete (DirHandle1);
        }

        if (EFI_ERROR (Status)) {
          goto Done;
        }
      }
    }
  }

Done:

  gtBS->FreePool (FileNameArray);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  CHAR16                    *PureFileNameArray;
  UINT32                    Count;

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
  // compose pure file name array
  //
  Status = ComposeFileNameArray (&PureFileNameArray, &Count);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ComposeFileNameArray fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Test 1: one directory level
  // Source: Root
  // FileName: pure file name (no other nodes)
  //
  Status = BBTestOpenBasicTestCheckpoint2_Test1 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Test 2: 2 directory levels
  // Source: Root
  // FileName: file name with directory node (subdir\filename)
  //
  Status = BBTestOpenBasicTestCheckpoint2_Test2 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  //
  // Test 3: 2 directory levels
  // Source: Sub directory
  // FileName: pure file name
  //
  Status = BBTestOpenBasicTestCheckpoint2_Test3 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  //
  // Test 4: 3 directory levels (subdir1\subdir2\filename)
  // Source: level 1 directory (subdir1)
  // FileName: file name with directory node (subdir2\filename)
  //
  Status = BBTestOpenBasicTestCheckpoint2_Test4 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }
  //
  // Test 5: 3 directory levels
  // Source: level 2 directory (subdir2)
  // FileName: file name with directory node (\subdir1\subdir2\filename)
  //
  Status = BBTestOpenBasicTestCheckpoint2_Test5 (
             StandardLib,
             Root,
             PureFileNameArray,
             Count,
             IsStress
             );

Done:
  if (PureFileNameArray != NULL) {
    gtBS->FreePool (PureFileNameArray);
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *CreateFileHandle;
  EFI_FILE                  *OpenFileHandle;
  UINT32                    AttributesIndex;
  UINT32                    NameIndex;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
          NameIndex++, PureStrPointer += MAX_STRING_LENGTH) {

      //
      // create file only (do not create directory)
      //
      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {

        for (OpenIndex = 0; OpenIndex < 3; OpenIndex++) {

          CreateFileHandle = NULL;
          OpenFileHandle = NULL;
          FileInfo = NULL;

          //
          // create file
          //

          Status = Root->Open (
                           Root,
                           &CreateFileHandle,
                           PureStrPointer,
                           EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                           ValidAttributesForCreate[AttributesIndex]
                           );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"create file fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            return Status;
          }

          //
          // enlarge file size
          //

          Status = InternalGetInfo (
                     CreateFileHandle,
                     (VOID **) &FileInfo,
                     &InfoBufferSize,
                     &gBlackBoxEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            goto FileClean;
          }

          FileInfo->FileSize = 1;

          Status = CreateFileHandle->SetInfo (
                                       CreateFileHandle,
                                       &gBlackBoxEfiFileInfoGuid,
                                       InfoBufferSize,
                                       FileInfo
                                       );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"set file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            goto FileClean;
          }

          gtBS->FreePool (FileInfo);
          FileInfo = NULL;
          if (CreateFileHandle != NULL) {
            CreateFileHandle->Close (CreateFileHandle);
            CreateFileHandle = NULL;
          }
          //
          // open the  file
          //
          OldTpl = gtBS->RaiseTPL (TplArray[Index]);
          Status = Root->Open (
                           Root,
                           &OpenFileHandle,
                           PureStrPointer,
                           OpenMode[OpenIndex],
                           ValidAttributesForCreate[AttributesIndex]
                           );
          gtBS->RestoreTPL (OldTpl);

          if (EFI_SUCCESS == Status) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;

          } else {
            if (((OpenMode[OpenIndex] & EFI_FILE_MODE_WRITE) == 0)
              && ((ValidAttributesForCreate[AttributesIndex] & EFI_FILE_READ_ONLY) != 0)) {

              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {

              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
          }

          if (Index == 0) {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid037;
          } else {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid038;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"Open() Basic Test - checkpoint2_Test1",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (EFI_ERROR (Status)) {
            goto FileClean;
          }

          //
          // Retrieve file info again
          //
          Status = InternalGetInfo (
                     OpenFileHandle,
                     (VOID **) &FileInfo,
                     &InfoBufferSize,
                     &gBlackBoxEfiFileInfoGuid
                     );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"get file info fail",
                           L"%a:%d: Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            goto FileClean;
          }

          //
          // OpenMode is Create/Read/Write:
          // Create for an existing file will open the existing file
          //
          //if (OpenMode[OpenIndex] & CREATE_FILE_MODE) {
            if (FileInfo->FileSize == 1) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }

            if (Index == 0) {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid039;
            } else {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid040;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"Open() Basic Test - checkpoint2_Test1",
                           L"%a:%d: create an existing file",
                           __FILE__,
                           (UINTN)__LINE__
                           );
          // goto FileClean;
          //}

          //
          // Write / SetInfo to the file
          //
          Temp = 0;
          TempSize = sizeof (UINT8);

          WriteStatus = OpenFileHandle->Write (
                                          OpenFileHandle,
                                          &TempSize,
                                          &Temp
                                          );

          Status = OpenFileHandle->SetInfo (
                                     OpenFileHandle,
                                     &gBlackBoxEfiFileInfoGuid,
                                     InfoBufferSize,
                                     FileInfo
                                     );
          //
          // OpenMode is Read
          //
          if (OpenMode[OpenIndex] == EFI_FILE_MODE_READ) {
            if ((EFI_ACCESS_DENIED == WriteStatus)
                && (EFI_SUCCESS == Status)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
          } else {
            if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;
            } else {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
            }
          }

          if (Index == 0) {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid041;
          } else {
            TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid042;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         TplGuid,
                         L"Open() Basic Test - checkpoint2_Test1",
                         L"%a:%d: OpenMode-0x%lx,WriteStatus-%r, SetInfoStatus-%r",
                         __FILE__,
                         (UINTN)__LINE__,
                         OpenMode[OpenIndex],
                         WriteStatus,
                         Status
                         );
FileClean:
          if (FileInfo != NULL) {
            gtBS->FreePool (FileInfo);
          }

          if (OpenFileHandle != NULL) {
            OpenFileHandle->Delete (OpenFileHandle);
          }
          if (CreateFileHandle != NULL) {
            CreateFileHandle->Close (CreateFileHandle);
          }
        }
      }
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *CreateFileHandle;
  EFI_FILE                  *OpenFileHandle;
  EFI_FILE                  *DirHandle;
  UINT32                    AttributesIndex;
  UINT32                    DirAttributesIndex;
  UINT32                    NameIndex;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  UINT32                    Loop;
  CHAR16                    *FileNameArray;
  UINTN                     ArraySize;
  UINTN                     FileNameLength;
  CHAR16                    *PureStrPointer, *StrPointer;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // prepare file name "subdir" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  gtBS->SetMem (FileNameArray, ArraySize * sizeof (CHAR16), 0);

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  for (Loop = 0; Loop < FixedNameCount; Loop++) {

    SctStrCpy (StrPointer, PureStrPointer);
    FileNameLength = SctStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;
    SctStrCat (StrPointer, PureStrPointer);

    StrPointer += MAX_STRING_LENGTH;
    PureStrPointer += MAX_STRING_LENGTH;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    StrPointer = FileNameArray;
    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
        StrPointer += MAX_STRING_LENGTH, PureStrPointer += MAX_STRING_LENGTH, NameIndex++) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
           DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {

        DirHandle = NULL;

        //
        // create sub directory first
        //

        Status = Root->Open (
                         Root,
                         &DirHandle,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[DirAttributesIndex]
                         );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"create directory fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          goto Done;
        }

        for (AttributesIndex = 0;
             AttributesIndex < MaxAttributesIndex;
             AttributesIndex++) {

          for (OpenIndex = 0; OpenIndex < 3; OpenIndex++) {

            CreateFileHandle = NULL;
            OpenFileHandle = NULL;
            FileInfo = NULL;

            //
            // create file
            //
            Status = Root->Open (
                             Root,
                             &CreateFileHandle,
                             StrPointer,
                             EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                             ValidAttributesForCreate[AttributesIndex]
                             );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"create file fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto DirClean;
            }

            //
            // enlarge file size
            //

            Status = InternalGetInfo (
                       CreateFileHandle,
                       (VOID **) &FileInfo,
                       &InfoBufferSize,
                       &gBlackBoxEfiFileInfoGuid
                       );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"get file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            FileInfo->FileSize = 1;

            Status = CreateFileHandle->SetInfo (
                                         CreateFileHandle,
                                         &gBlackBoxEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"set file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            gtBS->FreePool (FileInfo);
            FileInfo = NULL;
            if (CreateFileHandle != NULL) {
              CreateFileHandle->Close (CreateFileHandle);
              CreateFileHandle = NULL;
            }
            //
            // open the  file
            //
            OldTpl = gtBS->RaiseTPL (TplArray[Index]);
            Status = Root->Open (
                             Root,
                             &OpenFileHandle,
                             StrPointer,
                             OpenMode[OpenIndex],
                             ValidAttributesForCreate[AttributesIndex]
                             );
            gtBS->RestoreTPL (OldTpl);

            if (EFI_SUCCESS == Status) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;

            } else {
              if (((OpenMode[OpenIndex] & EFI_FILE_MODE_WRITE) == 0)
                && ((ValidAttributesForCreate[AttributesIndex] & EFI_FILE_READ_ONLY) != 0)) {

                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {

                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            }

            if (Index == 0) {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid043;
            } else {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid044;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"Open() Basic Test - checkpoint2_Test2",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (EFI_ERROR (Status)) {
              goto FileClean;
            }

            //
            // Retrieve file info again
            //
            Status = InternalGetInfo (
                       OpenFileHandle,
                       (VOID **) &FileInfo,
                       &InfoBufferSize,
                       &gBlackBoxEfiFileInfoGuid
                       );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"get file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            //
            // OpenMode is Create/Read/Write:
            // Create for an existing file will open the existing file.
            //
            //if (OpenMode[OpenIndex] & CREATE_FILE_MODE) {
              if (FileInfo->FileSize == 1) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }

              if (Index == 0) {
                TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid045;
              } else {
                TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid046;
              }
              StandardLib->RecordAssertion (
                             StandardLib,
                             AssertionType,
                             TplGuid,
                             L"Open() Basic Test - checkpoint2_Test2",
                             L"%a:%d: create an existing file",
                             __FILE__,
                             (UINTN)__LINE__
                             );
              //goto FileClean;
            //}

            //
            // Write / SetInfo to the file
            //
            Temp = 0;
            TempSize = sizeof (UINT8);
            WriteStatus = OpenFileHandle->Write (
                                            OpenFileHandle,
                                            &TempSize,
                                            &Temp
                                            );

            Status = OpenFileHandle->SetInfo (
                                       OpenFileHandle,
                                       &gBlackBoxEfiFileInfoGuid,
                                       InfoBufferSize,
                                       FileInfo
                                       );
            //
            // OpenMode is Read
            //
            if (OpenMode[OpenIndex] == EFI_FILE_MODE_READ) {
              if ((EFI_ACCESS_DENIED == WriteStatus)
                  && (EFI_SUCCESS == Status)) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            }

            if (Index == 0) {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid047;
            } else {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid048;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"Open() Basic Test - checkpoint2_Test2",
                           L"%a:%d: Open Mode- 0x%lx, WriteStatus-%r, SetInfoStatus- %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           OpenMode[OpenIndex],
                           WriteStatus,
                           Status
                           );
FileClean:
            if (FileInfo != NULL) {
              gtBS->FreePool (FileInfo);
            }

            if (OpenFileHandle != NULL) {
              OpenFileHandle->Delete (OpenFileHandle);
            }

            if (CreateFileHandle != NULL) {
              CreateFileHandle->Delete (CreateFileHandle);
            }

            if (EFI_ERROR (Status)) {
              goto DirClean;
            }

          }
        }
DirClean:
        if (DirHandle != NULL) {
          DirHandle->Delete (DirHandle);
        }

        if (EFI_ERROR (Status)) {
          goto Done;
        }
      }
    }
  }

Done:

  gtBS->FreePool (FileNameArray);

  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *CreateFileHandle;
  EFI_FILE                  *OpenFileHandle;
  EFI_FILE                  *DirHandle;
  UINT32                    AttributesIndex;
  UINT32                    DirAttributesIndex;
  UINT32                    NameIndex;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  CHAR16                    *PureStrPointer;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };
  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
         NameIndex++, PureStrPointer += MAX_STRING_LENGTH) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
           DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {

        DirHandle = NULL;

        //
        // create sub directory first
        //
        Status = Root->Open (
                         Root,
                         &DirHandle,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[DirAttributesIndex]
                         );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"create directory fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          return Status;
        }

        for (AttributesIndex = 0;
             AttributesIndex < MaxAttributesIndex;
             AttributesIndex++) {

          for (OpenIndex = 0; OpenIndex < 3; OpenIndex++) {

            CreateFileHandle = NULL;
            OpenFileHandle = NULL;
            FileInfo = NULL;

            //
            // create file
            //
            Status = DirHandle->Open (
                                  DirHandle,
                                  &CreateFileHandle,
                                  PureStrPointer,
                                  EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                  ValidAttributesForCreate[AttributesIndex]
                                  );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"create file fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto DirClean;
            }

            //
            // enlarge file size
            //

            Status = InternalGetInfo (
                       CreateFileHandle,
                       (VOID **) &FileInfo,
                       &InfoBufferSize,
                       &gBlackBoxEfiFileInfoGuid
                       );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"get file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            FileInfo->FileSize = 1;

            Status = CreateFileHandle->SetInfo (
                                         CreateFileHandle,
                                         &gBlackBoxEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"set file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            gtBS->FreePool (FileInfo);
            FileInfo = NULL;
            if (CreateFileHandle != NULL) {
              CreateFileHandle->Close (CreateFileHandle);
              CreateFileHandle = NULL;
            }
            //
            // open the  file
            //
            OldTpl = gtBS->RaiseTPL (TplArray[Index]);
            Status = DirHandle->Open (
                                  DirHandle,
                                  &OpenFileHandle,
                                  PureStrPointer,
                                  OpenMode[OpenIndex],
                                  ValidAttributesForCreate[AttributesIndex]
                                  );
            gtBS->RestoreTPL (OldTpl);

            if (EFI_SUCCESS == Status) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;

            } else {
              if (((OpenMode[OpenIndex] & EFI_FILE_MODE_WRITE) == 0)
                && ((ValidAttributesForCreate[AttributesIndex] & EFI_FILE_READ_ONLY) != 0)) {

                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {

                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            }

            if (Index == 0) {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid049;
            } else {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid050;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"Open() Basic Test - checkpoint2_Test3",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (EFI_ERROR (Status)) {
              goto FileClean;
            }

            //
            // Retrieve file info again
            //
            Status = InternalGetInfo (
                       OpenFileHandle,
                       (VOID **) &FileInfo,
                       &InfoBufferSize,
                       &gBlackBoxEfiFileInfoGuid
                       );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"get file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            //
            // OpenMode is Create/Read/Write:
            // Create for an existing file will delete this file and open it again.
            //
            //if (OpenMode[OpenIndex] & CREATE_FILE_MODE) {
              if (FileInfo->FileSize == 1) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }

              if (Index == 0) {
                TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid051;
              } else {
                TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid052;
              }
              StandardLib->RecordAssertion (
                             StandardLib,
                             AssertionType,
                             TplGuid,
                             L"Open() Basic Test - checkpoint2_Test3",
                             L"%a:%d: create an existing file",
                             __FILE__,
                             (UINTN)__LINE__
                             );
              //goto FileClean;
            //}

            //
            // Write / SetInfo to the file
            //
            Temp = 0;
            TempSize = sizeof (UINT8);
            WriteStatus = OpenFileHandle->Write (
                                            OpenFileHandle,
                                            &TempSize,
                                            &Temp
                                            );

            Status = OpenFileHandle->SetInfo (
                                       OpenFileHandle,
                                       &gBlackBoxEfiFileInfoGuid,
                                       InfoBufferSize,
                                       FileInfo
                                       );
            //
            // OpenMode is Read
            //
            if (OpenMode[OpenIndex] == EFI_FILE_MODE_READ) {
              if ((EFI_ACCESS_DENIED == WriteStatus)
                  && (EFI_SUCCESS == Status)) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            }

            if (Index == 0) {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid053;
            } else {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid054;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"Open() Basic Test - checkpoint2_Test3",
                           L"%a:%d: Open Mode- 0x%lx, WriteStatus-%r, SetInfoStatus- %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           OpenMode[OpenIndex],
                           WriteStatus,
                           Status
                           );
FileClean:
            if (FileInfo != NULL) {
              gtBS->FreePool (FileInfo);
            }

            if (OpenFileHandle != NULL) {
              OpenFileHandle->Delete (OpenFileHandle);
            }

            if (CreateFileHandle != NULL) {
              CreateFileHandle->Delete (CreateFileHandle);
            }

            if (EFI_ERROR (Status)) {
              goto DirClean;
            }

          }
        }
DirClean:
        if (DirHandle != NULL) {
          DirHandle->Delete (DirHandle);
        }

        if (EFI_ERROR (Status)) {
          return Status;
        }
      }
    }
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *CreateFileHandle;
  EFI_FILE                  *OpenFileHandle;
  EFI_FILE                  *DirHandle1;
  EFI_FILE                  *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    DirAttributesIndex;
  UINT32                    NameIndex;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  UINT32                    Loop;
  CHAR16                    *FileNameArray;
  CHAR16                    *StrPointer, *PureStrPointer;
  UINTN                     ArraySize;
  UINTN                     FileNameLength;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  gtBS->SetMem (FileNameArray, ArraySize * sizeof (CHAR16), 0);

  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  for (Loop = 0; Loop < FixedNameCount; Loop++) {

    SctStrCpy (StrPointer, PureStrPointer);
    FileNameLength = SctStrLen (StrPointer);

    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    SctStrCat (StrPointer, PureStrPointer);

    StrPointer += MAX_STRING_LENGTH;
    PureStrPointer += MAX_STRING_LENGTH;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    StrPointer = FileNameArray;
    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
        StrPointer += MAX_STRING_LENGTH, PureStrPointer += MAX_STRING_LENGTH, NameIndex++) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
            DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {

        DirHandle1 = NULL;
        DirHandle2 = NULL;

        //
        // create sub directory 1
        //
        Status = Root->Open (
                         Root,
                         &DirHandle1,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[DirAttributesIndex]
                         );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"create directory fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          goto Done;
        }

        //
        // create sub directory 2
        //
        Status = DirHandle1->Open (
                               DirHandle1,
                               &DirHandle2,
                               PureStrPointer,
                               EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                               ValidAttributesForCreate[DirAttributesIndex]
                               );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"create directory fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          DirHandle1->Delete (DirHandle1);
          goto Done;
        }

        for (AttributesIndex = 0;
             AttributesIndex < MaxAttributesIndex;
             AttributesIndex++) {

          for (OpenIndex = 0; OpenIndex < 3; OpenIndex++) {

            CreateFileHandle = NULL;
            OpenFileHandle = NULL;
            FileInfo = NULL;

            //
            // create file
            //
            Status = DirHandle1->Open (
                                   DirHandle1,
                                   &CreateFileHandle,
                                   StrPointer,
                                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                   ValidAttributesForCreate[AttributesIndex]
                                   );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"create file fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto DirClean;
            }

            //
            // enlarge file size
            //

            Status = InternalGetInfo (
                       CreateFileHandle,
                       (VOID **) &FileInfo,
                       &InfoBufferSize,
                       &gBlackBoxEfiFileInfoGuid
                       );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"get file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            FileInfo->FileSize = 1;

            Status = CreateFileHandle->SetInfo (
                                         CreateFileHandle,
                                         &gBlackBoxEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"set file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            gtBS->FreePool (FileInfo);
            FileInfo = NULL;
            if (CreateFileHandle != NULL) {
              CreateFileHandle->Close (CreateFileHandle);
              CreateFileHandle = NULL;
            }
            //
            // open the  file
            //
            OldTpl = gtBS->RaiseTPL (TplArray[Index]);
            Status = DirHandle1->Open (
                                   DirHandle1,
                                   &OpenFileHandle,
                                   StrPointer,
                                   OpenMode[OpenIndex],
                                   ValidAttributesForCreate[AttributesIndex]
                                   );
            gtBS->RestoreTPL (OldTpl);

            if (EFI_SUCCESS == Status) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;

            } else {
              if (((OpenMode[OpenIndex] & EFI_FILE_MODE_WRITE) == 0)
                && ((ValidAttributesForCreate[AttributesIndex] & EFI_FILE_READ_ONLY) != 0)) {

                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {

                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            }

            if (Index == 0) {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid055;
            } else {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid056;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"Open() Basic Test - checkpoint2_Test4",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (EFI_ERROR (Status)) {
              goto FileClean;
            }

            //
            // Retrieve file info again
            //
            Status = InternalGetInfo (
                       OpenFileHandle,
                       (VOID **) &FileInfo,
                       &InfoBufferSize,
                       &gBlackBoxEfiFileInfoGuid
                       );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"get file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            //
            // OpenMode is Create/Read/Write:
            // Create for an existing file will open the existing file.
            //
            //if (OpenMode[OpenIndex] & CREATE_FILE_MODE) {
              if (FileInfo->FileSize == 1) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }

              if (Index == 0) {
                TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid057;
              } else {
                TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid058;
              }
              StandardLib->RecordAssertion (
                             StandardLib,
                             AssertionType,
                             TplGuid,
                             L"Open() Basic Test - checkpoint2_Test4",
                             L"%a:%d: create an existing file",
                             __FILE__,
                             (UINTN)__LINE__
                             );
            //  goto FileClean;
            //}

            //
            // Write / SetInfo to the file
            //
            Temp = 0;
            TempSize = sizeof (UINT8);
            WriteStatus = OpenFileHandle->Write (
                                            OpenFileHandle,
                                            &TempSize,
                                            &Temp
                                            );

              Status = OpenFileHandle->SetInfo (
                                         OpenFileHandle,
                                         &gBlackBoxEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
            //
            // OpenMode is Read
            //
            if (OpenMode[OpenIndex] == EFI_FILE_MODE_READ) {
              if ((EFI_ACCESS_DENIED == WriteStatus)
                  && (EFI_SUCCESS == Status)) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            }

            if (Index == 0) {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid059;
            } else {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid060;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"Open() Basic Test - checkpoint2_Test4",
                           L"%a:%d: Open Mode- 0x%lx, WriteStatus- %r, SetInfoStatus- %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           OpenMode[OpenIndex],
                           WriteStatus,
                           Status
                           );
FileClean:
            if (FileInfo != NULL) {
              gtBS->FreePool (FileInfo);
            }

            if (OpenFileHandle != NULL) {
              OpenFileHandle->Delete (OpenFileHandle);
            }

            if (CreateFileHandle != NULL) {
              CreateFileHandle->Delete (CreateFileHandle);
            }

            if (EFI_ERROR (Status)) {
              goto DirClean;
            }

          }
        }
DirClean:
        if (DirHandle2 != NULL) {
          DirHandle2->Delete (DirHandle2);
        }

        if (DirHandle1 != NULL) {
          DirHandle1->Delete (DirHandle1);
        }

        if (EFI_ERROR (Status)) {
          goto Done;
        }
      }
    }
  }

Done:

  if (FileNameArray != NULL) {
    gtBS->FreePool (FileNameArray);
  }

  return Status;
}

EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2_Test5 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_FILE                              *Root,
  CHAR16                                *PureFileNameArray,
  UINT32                                FixedNameCount,
  BOOLEAN                               IsStress
  )
{
  EFI_FILE                  *CreateFileHandle;
  EFI_FILE                  *OpenFileHandle;
  EFI_FILE                  *DirHandle1;
  EFI_FILE                  *DirHandle2;
  UINT32                    AttributesIndex;
  UINT32                    DirAttributesIndex;
  UINT32                    NameIndex;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT8                     Temp;
  UINTN                     TempSize;
  EFI_STATUS                WriteStatus;
  EFI_STATUS                Status;
  UINT32                    Loop;
  CHAR16                    *FileNameArray;
  CHAR16                    *StrPointer, *PureStrPointer;
  UINTN                     FileNameLength;
  UINTN                     ArraySize;
  UINTN                     OpenIndex;
  UINT64                    OpenMode[3] = {
                 EFI_FILE_MODE_READ,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                 EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE
                 };

  UINT32                    MaxDirAttributesIndex;
  UINT32                    MaxAttributesIndex;
  UINT32                    MaxNameIndex;
  EFI_GUID                  TplGuid;

  if (IsStress) {
    MaxDirAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
    MaxNameIndex = FixedNameCount;
  } else {
    MaxDirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE + 1;
    MaxAttributesIndex = 1;
    MaxNameIndex = 1;
  }

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // prepare file name "subdir2" + "\" + "filename"
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNameArray
                   );
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
    return Status;
  }
  gtBS->SetMem (FileNameArray, ArraySize * sizeof (CHAR16), 0);

  //
  // prepare file name "\" + subdir1 + "\" + subdir2 + "\" + filename
  //
  StrPointer = FileNameArray;
  PureStrPointer = PureFileNameArray;
  for (Loop = 0; Loop < FixedNameCount; Loop++) {

    //
    // "\"
    //
    StrPointer[0] = '\\';
    StrPointer[1] = 0;

    //
    // "\" + subdir1
    //
    SctStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\"
    //
    FileNameLength = SctStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2
    //
    SctStrCat (StrPointer, PureStrPointer);

    //
    // "\" + subdir1 + "\" + subdir2 + "\"
    //
    FileNameLength = SctStrLen (StrPointer);
    StrPointer[FileNameLength] = '\\';
    StrPointer[FileNameLength + 1] = 0;

    //
    // "\" + subdir1 + "\" + subdir2 + "\" + filename
    //
    SctStrCat (StrPointer, PureStrPointer);

    StrPointer += MAX_STRING_LENGTH;
    PureStrPointer += MAX_STRING_LENGTH;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    StrPointer = FileNameArray;
    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
        NameIndex++, StrPointer += MAX_STRING_LENGTH, PureStrPointer += MAX_STRING_LENGTH) {

      for (DirAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
            DirAttributesIndex < MaxDirAttributesIndex; DirAttributesIndex++) {

        DirHandle1 = NULL;
        DirHandle2 = NULL;

        //
        // create sub directory 1
        //
        Status = Root->Open (
                         Root,
                         &DirHandle1,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[DirAttributesIndex]
                         );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"create sub directory 1 fail",
                         L"%a:%d: Status - %r, dir name - %s",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         PureStrPointer
                         );
          goto Done;
        }

        //
        // create sub directory 2
        //
        Status = DirHandle1->Open (
                               DirHandle1,
                               &DirHandle2,
                               PureStrPointer,
                               EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                               ValidAttributesForCreate[DirAttributesIndex]
                               );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"create sub directory 2 fail",
                         L"%a:%d: Status - %r, dir name - %s",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         PureStrPointer
                         );
          DirHandle1->Delete (DirHandle1);
          goto Done;
        }

        for (AttributesIndex = 0;
             AttributesIndex < MaxAttributesIndex;
             AttributesIndex++) {

          for (OpenIndex = 0; OpenIndex < 3; OpenIndex++) {

            CreateFileHandle = NULL;
            OpenFileHandle = NULL;
            FileInfo = NULL;

            //
            // create file
            //
            Status = DirHandle2->Open (
                                   DirHandle2,
                                   &CreateFileHandle,
                                   StrPointer,
                                   EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                                   ValidAttributesForCreate[AttributesIndex]
                                   );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"create file fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto DirClean;
            }

            //
            // enlarge file size
            //

            Status = InternalGetInfo (
                       CreateFileHandle,
                       (VOID **) &FileInfo,
                       &InfoBufferSize,
                       &gBlackBoxEfiFileInfoGuid
                       );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"get file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            FileInfo->FileSize = 1;

            Status = CreateFileHandle->SetInfo (
                                         CreateFileHandle,
                                         &gBlackBoxEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"set file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            gtBS->FreePool (FileInfo);
            FileInfo = NULL;
            if (CreateFileHandle != NULL) {
              CreateFileHandle->Close (CreateFileHandle);
              CreateFileHandle = NULL;
            }
            //
            // open the  file
            //
            OldTpl = gtBS->RaiseTPL (TplArray[Index]);
            Status = DirHandle2->Open (
                                   DirHandle2,
                                   &OpenFileHandle,
                                   StrPointer,
                                   OpenMode[OpenIndex],
                                   ValidAttributesForCreate[AttributesIndex]
                                   );
            gtBS->RestoreTPL (OldTpl);

            if (EFI_SUCCESS == Status) {
              AssertionType = EFI_TEST_ASSERTION_PASSED;

            } else {
              if (((OpenMode[OpenIndex] & EFI_FILE_MODE_WRITE) == 0)
                && ((ValidAttributesForCreate[AttributesIndex] & EFI_FILE_READ_ONLY) != 0)) {

                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {

                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            }

            if (Index == 0) {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid061;
            } else {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid062;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"Open() Basic Test - checkpoint2_Test5",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (EFI_ERROR (Status)) {
              goto FileClean;
            }

            //
            // Retrieve file info again
            //
            Status = InternalGetInfo (
                       OpenFileHandle,
                       (VOID **) &FileInfo,
                       &InfoBufferSize,
                       &gBlackBoxEfiFileInfoGuid
                       );
            if (EFI_ERROR (Status)) {
              StandardLib->RecordAssertion (
                             StandardLib,
                             EFI_TEST_ASSERTION_FAILED,
                             gTestGenericFailureGuid,
                             L"get file info fail",
                             L"%a:%d: Status - %r",
                             __FILE__,
                             (UINTN)__LINE__,
                             Status
                             );
              goto FileClean;
            }

            //
            // OpenMode is Create/Read/Write:
            // Create for an existing file will open the existing file.
            //
            //if (OpenMode[OpenIndex] & CREATE_FILE_MODE) {
              if (FileInfo->FileSize == 1) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }

              if (Index == 0) {
                TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid063;
              } else {
                TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid064;
              }
              StandardLib->RecordAssertion (
                             StandardLib,
                             AssertionType,
                             TplGuid,
                             L"Open() Basic Test - checkpoint2_Test5",
                             L"%a:%d: create an existing file",
                             __FILE__,
                             (UINTN)__LINE__
                             );
            //  goto FileClean;
            //}

            //
            // Write / SetInfo to the file
            //
            Temp = 0;
            TempSize = sizeof (UINT8);
            WriteStatus = OpenFileHandle->Write (
                                            OpenFileHandle,
                                            &TempSize,
                                            &Temp
                                            );

              Status = OpenFileHandle->SetInfo (
                                         OpenFileHandle,
                                         &gBlackBoxEfiFileInfoGuid,
                                         InfoBufferSize,
                                         FileInfo
                                         );
            //
            // OpenMode is Read
            //
            if (OpenMode[OpenIndex] == EFI_FILE_MODE_READ) {
              if ((EFI_ACCESS_DENIED == WriteStatus)
                  && (EFI_SUCCESS == Status)) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            } else {
              if ((EFI_SUCCESS == WriteStatus) && (EFI_SUCCESS == Status)) {
                AssertionType = EFI_TEST_ASSERTION_PASSED;
              } else {
                AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
            }

            if (Index == 0) {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid065;
            } else {
              TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid066;
            }
            StandardLib->RecordAssertion (
                           StandardLib,
                           AssertionType,
                           TplGuid,
                           L"Open() Basic Test - checkpoint2_Test5",
                           L"%a:%d: Open Mode- 0x%lx, WriteStatus- %r, SetInfoStatus- %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           OpenMode[OpenIndex],
                           WriteStatus,
                           Status
                           );
FileClean:
            if (FileInfo != NULL) {
              gtBS->FreePool (FileInfo);
            }

            if (OpenFileHandle != NULL) {
              OpenFileHandle->Delete (OpenFileHandle);
            }

            if (CreateFileHandle != NULL) {
              CreateFileHandle->Delete (CreateFileHandle);
            }

            if (EFI_ERROR (Status)) {
              goto DirClean;
            }

          }
        }
DirClean:
        if (DirHandle2 != NULL) {
          DirHandle2->Delete (DirHandle2);
        }

        if (DirHandle1 != NULL) {
          DirHandle1->Delete (DirHandle1);
        }

        if (EFI_ERROR (Status)) {
          goto Done;
        }
      }
    }
  }

Done:

  if (FileNameArray != NULL) {
    gtBS->FreePool (FileNameArray);
  }

  return Status;
}


EFI_STATUS
EFIAPI
BBTestCloseBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
/*
  The directory structure set up in this checkpoint is illustrated as below:

           Root
          ======
          | | |
         /  |  \
        /   |   \
       /    |    \
    ===    ===    ===
     D1    D2      F1
    ===    ===    ===
    / \    / \
   =   =  =   =
   F2  F3 F4  F5

  The test operation steps are:

    * Close() Root, D1, F2 and F5.
    * Read/Write/GetInfo/SetInfo/GetPosition/SetPosition to F1, F3 and F4.
    * Open/GetInfo to D2.
    * Close() all opened handles
*/
{
  EFI_STATUS                Status;
  EFI_STATUS                Status1, Status2, Status3, Status4, Status5, Status6;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  UINT8                     Temp;
  UINTN                     TempSize;
  UINTN                     InfoBufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINT64                    Position;
  EFI_FILE                  *FileHandle[5];
  EFI_FILE                  *DirHandle[2];
  EFI_FILE                  *OpenFileHandle[5];
  EFI_FILE                  *OpenDirHandle[2];
  CHAR16                    FileName[5][100];
  CHAR16                    DirName[2][100];
  EFI_GUID                  TplGuid;

  SctStrCpy (FileName[0], L"File1");
  SctStrCpy (FileName[1], L"File2");
  SctStrCpy (FileName[2], L"File3");
  SctStrCpy (FileName[3], L"File4");
  SctStrCpy (FileName[4], L"File5");

  SctStrCpy (DirName[0], L"Dir1");
  SctStrCpy (DirName[1], L"Dir2");

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    //
    // Init
    //
    gtBS->SetMem (DirHandle, 2 * sizeof (EFI_FILE*), 0);
    gtBS->SetMem (FileHandle, 5 * sizeof (EFI_FILE*), 0);
    gtBS->SetMem (OpenDirHandle, 2 * sizeof (EFI_FILE*), 0);
    gtBS->SetMem (OpenFileHandle, 5 * sizeof (EFI_FILE*), 0);
    Root = NULL;

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
    // create D1 and D2
    //
    for (Index = 0; Index < 2; Index++) {
      DirHandle[Index] = NULL;
    }
    for (Index = 0; Index < 5; Index++) {
      FileHandle[Index] = NULL;
    }
    for (Index = 0; Index < 2; Index++) {

      Status = Root->Open (
                       Root,
                       &DirHandle[Index],
                       DirName[Index],
                       CREATE_FILE_MODE,
                       EFI_FILE_DIRECTORY
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Create Directory fail",
                       L"%a:%d: Status - %r, Index - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index
                       );
        for (Index = 0; Index < 2; Index++) {
          if (DirHandle[Index] != NULL) {
            DirHandle[Index]->Delete (DirHandle[Index]);
          }
        }
        return Status;
      }
    }

    //
    // create F2 and F3 (under D1)
    //
    for (Index = 1; Index < 3; Index++) {

      Status = DirHandle[0]->Open (
                               DirHandle[0],
                               &FileHandle[Index],
                               FileName[Index],
                               CREATE_FILE_MODE,
                               0
                               );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Create File fail",
                       L"%a:%d: Status - %r, Index - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index + 1
                       );
        for (Index = 0; Index < 5; Index++) {
          if (FileHandle[Index] != NULL) {
            FileHandle[Index]->Delete (FileHandle[Index]);
          }
        }

        for (Index = 0; Index < 2; Index++) {
          if (DirHandle[Index] != NULL) {
            DirHandle[Index]->Delete (DirHandle[Index]);
          }
        }
        return Status;
      }
    }

    //
    // create F4 and F5 (under D2)
    //
    for (Index = 3; Index < 5; Index++) {

      Status = DirHandle[1]->Open (
                               DirHandle[1],
                               &FileHandle[Index],
                               FileName[Index],
                               CREATE_FILE_MODE,
                               0
                               );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Create File fail",
                       L"%a:%d: Status - %r, Index - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index + 1
                       );
        for (Index = 0; Index < 5; Index++) {
          if (FileHandle[Index] != NULL) {
            FileHandle[Index]->Delete (FileHandle[Index]);
          }
        }

        for (Index = 0; Index < 2; Index++) {
          if (DirHandle[Index] != NULL) {
            DirHandle[Index]->Delete (DirHandle[Index]);
          }
        }

        return Status;
      }
    }

    //
    // create F1
    //
    Status = Root->Open (
                     Root,
                     &FileHandle[0],
                     FileName[0],
                     CREATE_FILE_MODE,
                     0
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Create File fail",
                     L"%a:%d: Status - %r, Index - 0",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      for (Index = 0; Index < 5; Index++) {
        if (FileHandle[Index] != NULL) {
          FileHandle[Index]->Delete (FileHandle[Index]);
        }
      }

      for (Index = 0; Index < 2; Index++) {
        if (DirHandle[Index] != NULL) {
          DirHandle[Index]->Delete (DirHandle[Index]);
        }
      }
      return Status;
    }

    //
    // * Close() Root, D1, F2 and F5.
    //
    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);

    Status1 = Root->Close (Root);
    Status2 = DirHandle[0]->Close (DirHandle[0]);
    Status3 = FileHandle[1]->Close (FileHandle[1]);
    Status4 = FileHandle[4]->Close (FileHandle[4]);

    gtBS->RestoreTPL (OldTpl);

    if ((EFI_SUCCESS == Status1) && (EFI_SUCCESS == Status2)
        && (EFI_SUCCESS == Status3) && (EFI_SUCCESS == Status4)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid067;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid068;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Close() Basic Test - checkpoint1",
                   L"%a:%d: Status1- %r,Status2- %r,Status3- %r,Status4:%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3,
                   Status4
                   );
    //
    // NULL those handles
    //
    Root = NULL;
    DirHandle[0] = NULL;
    FileHandle[1] = NULL;
    FileHandle[4] = NULL;

    //
    // Read/Write/GetInfo/SetInfo/GetPosition/SetPosition to F1, F3 and F4.
    //
    for (Index = 0; Index < 4; Index++) {

      if (Index == 1) {
        continue;
      }

      Temp = 0;
      TempSize = sizeof (UINT8);
      FileInfo = NULL;

      Status1 = FileHandle[Index]->Write (FileHandle[Index], &TempSize, &Temp);

      Status2 = FileHandle[Index]->Read (FileHandle[Index], &TempSize, &Temp);

      Status3 = InternalGetInfo (
                  FileHandle[Index],
                  (VOID **) &FileInfo,
                  &InfoBufferSize,
                  &gBlackBoxEfiFileInfoGuid
                  );
      if (!EFI_ERROR (Status3)) {
        Status4 = FileHandle[Index]->SetInfo (
                                       FileHandle[Index],
                                       &gBlackBoxEfiFileInfoGuid,
                                       InfoBufferSize,
                                       FileInfo
                                       );
      }
      if (FileInfo != NULL) {
        gtBS->FreePool (FileInfo);
      }

      Status5 = FileHandle[Index]->GetPosition (FileHandle[Index], &Position);

      Status6 = FileHandle[Index]->SetPosition (FileHandle[Index], Position);

      if ((EFI_SUCCESS == Status1) && (EFI_SUCCESS == Status2)
        && (EFI_SUCCESS == Status3) && (EFI_SUCCESS == Status4)
        && (EFI_SUCCESS == Status5) && (EFI_SUCCESS == Status6)) {

        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid069;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid070;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Close() Basic Test - checkpoint1",
                     L"%a:%d: Write Status- %r,Read Status- %r,GetInfo Status- %r,SetInfo Status- %r,GetPosition Status- %r,SetPosition Status- %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1,
                     Status2,
                     Status3,
                     Status4,
                     Status5,
                     Status6
                     );
    }

    //
    // * Open/GetInfo/SetInfo to D2.
    //
    FileInfo = NULL;
    Status1 = DirHandle[1]->Open (
                              DirHandle[1],
                              &OpenFileHandle[4],
                              FileName[4],      // open F5
                              OPEN_R_W_MODE,
                              0
                              );

    Status2 = InternalGetInfo (
                DirHandle[1],
                (VOID **) &FileInfo,
                &InfoBufferSize,
                &gBlackBoxEfiFileInfoGuid
                );
    if (!EFI_ERROR (Status2)) {
      Status3 = DirHandle[1]->SetInfo (
                                DirHandle[1],
                                &gBlackBoxEfiFileInfoGuid,
                                InfoBufferSize,
                                FileInfo
                                );
    }

    if ((EFI_SUCCESS == Status1) && (EFI_SUCCESS == Status2)
      && (EFI_SUCCESS == Status3)) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid071;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid072;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Close() Basic Test - checkpoint1",
                   L"%a:%d: Open Status- %r,GetInfo Status- %r,SetInfo Status- %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   Status2,
                   Status3
                   );
    if (FileInfo != NULL) {
      gtBS->FreePool (FileInfo);
    }

    if (OpenFileHandle[4] != NULL) {
      OpenFileHandle[4]->Close (OpenFileHandle[4]);
    }

    //
    // clean resources for the next loop
    //

    if (Root != NULL) {
      Root->Close (Root);
    }

    for (Index = 0; Index < 5; Index++) {
      if (FileHandle[Index] != NULL) {
        FileHandle[Index]->Close (FileHandle[Index]);
      }
    }

    for (Index = 0; Index < 2; Index++) {
      if (DirHandle[Index] != NULL) {
        DirHandle[Index]->Close (DirHandle[Index]);
      }
    }

    //
    // open all those files and delete them
    //

    //
    // open root
    //
    Status = SimpleFileSystem->OpenVolume (SimpleFileSystem, &Root);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"open Root fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    //
    // open D1 and D2
    //
    for (Index = 0; Index < 2; Index++) {

      Status = Root->Open (
                       Root,
                       &OpenDirHandle[Index],
                       DirName[Index],
                       OPEN_R_W_MODE,
                       EFI_FILE_DIRECTORY
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"open directory fail",
                       L"%a:%d: Status - %r, Index - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index + 1
                       );
      }
    }

    //
    // open F2 and F3 (under D1)
    //
    for (Index = 1; Index < 3; Index++) {

      if (OpenDirHandle[0] != NULL) {
        Status = OpenDirHandle[0]->Open (
                                     OpenDirHandle[0],
                                     &OpenFileHandle[Index],
                                     FileName[Index],
                                     CREATE_FILE_MODE,
                                     0
                                     );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"open File fail",
                         L"%a:%d: Status - %r, Index - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         Index + 1
                         );
        }
      }
    }

    //
    // open F4 and F5 (under D2)
    //
    for (Index = 3; Index < 5; Index++) {

      if (OpenDirHandle[1] != NULL) {
        Status = OpenDirHandle[1]->Open (
                                     OpenDirHandle[1],
                                     &OpenFileHandle[Index],
                                     FileName[Index],
                                     CREATE_FILE_MODE,
                                     0
                                     );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"open File fail",
                         L"%a:%d: Status - %r, Index - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         Index + 1
                         );
        }
      }
    }

    //
    // open F1
    //
    Status = Root->Open (
                     Root,
                     &OpenFileHandle[0],
                     FileName[0],
                     CREATE_FILE_MODE,
                     0
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Create File fail",
                     L"%a:%d: Status - %r, Index - 0",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

Done:
    for (Index = 0; Index < 5; Index++) {
      if (OpenFileHandle[Index] != NULL) {
        OpenFileHandle[Index]->Delete (OpenFileHandle[Index]);
      }
    }

    for (Index = 0; Index < 2; Index++) {
      if (OpenDirHandle[Index] != NULL) {
        OpenDirHandle[Index]->Delete (OpenDirHandle[Index]);
      }
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDeleteBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *OpenHandle;
  EFI_GUID                  TplGuid;

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

  SctStrCpy (FileName, L"BBTestDeleteBasicTestCheckpoint1_File1");

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    //
    // create the file
    //
    FileHandle = NULL;
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
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = FileHandle->Delete (FileHandle);
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid073;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid074;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Delete() Basic Test - checkpoint1",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    // try to open this file again
    //
    OpenHandle = NULL;
    Status = Root->Open (Root, &OpenHandle, FileName, OPEN_R_W_MODE, 0);
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid075;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid076;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Delete() Basic Test - checkpoint1",
                   L"%a:%d: open Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (OpenHandle != NULL) {
      OpenHandle->Close (OpenHandle);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDeleteBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  CHAR16                    DirName[100];
  EFI_FILE                  *DirHandle;
  EFI_FILE                  *OpenHandle;
  EFI_GUID                  TplGuid;

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

  SctStrCpy (DirName, L"BBTestDeleteBasicTestCheckpoint2_Dir1");

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    //
    // create the directory
    //
    DirHandle = NULL;
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
      return Status;
    }

    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = DirHandle->Delete (DirHandle);
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid077;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid078;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Delete() Basic Test - checkpoint2",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    // try to open this directory again
    //
    OpenHandle = NULL;
    Status = Root->Open (Root, &OpenHandle, DirName, OPEN_R_W_MODE, 0);
    if (EFI_NOT_FOUND == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid079;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid080;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Delete() Basic Test - checkpoint2",
                   L"%a:%d: open Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (OpenHandle != NULL) {
      OpenHandle->Close (OpenHandle);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestDeleteBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  CHAR16                    DirName[100];
  CHAR16                    FileName[100];
  EFI_FILE                  *DirHandle;
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *OpenDirHandle;
  EFI_GUID                  TplGuid;

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

  SctStrCpy (DirName, L"BBTestDeleteBasicTestCheckpoint3_Dir1");
  SctStrCpy (FileName, L"BBTestDeleteBasicTestCheckpoint3_File1");

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    //
    // create the directory
    //
    DirHandle = NULL;
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
      return Status;
    }

    //
    // create file under the directory
    //
    FileHandle = NULL;
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
      return Status;
    }

    //
    // try to delete the nonempty directory
    //
    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = DirHandle->Delete (DirHandle);
    gtBS->RestoreTPL (OldTpl);

    if (EFI_WARN_DELETE_FAILURE == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid081;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid082;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Delete() Basic Test - checkpoint3",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    // try to open this directory again
    //
    OpenDirHandle = NULL;
    Status = Root->Open (Root, &OpenDirHandle, DirName, OPEN_R_W_MODE, 0);
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid083;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid084;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Delete() Basic Test - checkpoint3",
                   L"%a:%d: open Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    //
    // clean resources
    //
    if (FileHandle != NULL) {
      FileHandle->Delete (FileHandle);
    }

    if (OpenDirHandle != NULL) {
      OpenDirHandle->Delete (OpenDirHandle);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestReadBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  UINT64                    FileSize = 200;
  UINT8                     *Buffer;
  UINTN                     BufferSize;
  UINT64                    FilePosition;
  UINT64                    SetPosition[9] = {0, 0, 0, 100, 100, 100, 200, 200, 300};
  UINTN                     ReadLength[9] = {50, 200, 250, 50, 100, 200, 0, 100, 1};
  UINTN                     PositionIndex;
  UINTN                     Index;
  EFI_GUID                  TplGuid;

  //
  // init
  //
  Buffer = NULL;
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

  SctStrCpy (FileName, L"BBTestReadBasicTestCheckpoint1_File");

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
    goto Done;
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
    goto Done;
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
      BufferSize = ReadLength[PositionIndex];

      OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
      Status = FileHandle->Read (FileHandle, &BufferSize, Buffer);
      gtBS->RestoreTPL (OldTpl);
      if (SetPosition[PositionIndex] > FileSize) {
        if (EFI_DEVICE_ERROR == Status) {
           AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
           AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }
      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid085;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid086;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Read() Basic Test - checkpoint1",
                     L"%a:%d: Index - %d, Status - %r, setpostion - %ld, ReadLength - %d, ReturnedBufferSize - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     PositionIndex,
                     Status,
                     SetPosition[PositionIndex],
                     ReadLength[PositionIndex],
                     BufferSize
                     );
      if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
        continue;
      }
      Status = FileHandle->GetPosition (FileHandle, &FilePosition);
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid087;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid088;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Read() Basic Test - checkpoint1",
                     L"%a:%d: GetPosition Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      if (ReadLength[PositionIndex] + SetPosition[PositionIndex] > FileSize) {

        //
        // returned BufferSize is truncated
        // IF FileSize > SetPosition[PositionIndex] THEN
        //   BufferSize = FileSize - SetPosition[PositionIndex]
        // ELSE
        //   BufferSize = 0
        //
        if (FileSize > SetPosition[PositionIndex]) {
          if (BufferSize == (FileSize - SetPosition[PositionIndex])) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
        //  if (BufferSize == 0) {
        //    AssertionType = EFI_TEST_ASSERTION_PASSED;
        //  } else {
        //    AssertionType = EFI_TEST_ASSERTION_FAILED;
        //  }
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid089;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid090;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Read() Basic Test - checkpoint1",
                       L"%a:%d: position before read - %d, position after read - %d, RequestedReadLeng - %d, Current BufferSize - %d",
                      __FILE__,
                       (UINTN)__LINE__,
                       (UINTN)SetPosition[PositionIndex],
                       (UINTN)FilePosition,
                       ReadLength[PositionIndex],
                       BufferSize
                       );

        //
        // file position unchanged if SetPosition > FileSize
        //
        if (SetPosition[PositionIndex] >= FileSize) {
          if ((FilePosition == SetPosition[PositionIndex])
              || (FilePosition == FileSize)) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          //
          // file position updated to the end of the file
          //
          if (FilePosition == FileSize) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid091;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid092;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Read() Basic Test - checkpoint1",
                       L"%a:%d: position before read - %d, position after read - %d, RequestedReadLeng - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       (UINTN)SetPosition[PositionIndex],
                       (UINTN)FilePosition,
                       ReadLength[PositionIndex]
                       );
      } else {

        //
        // returned BufferSize equals ReadLength[PositionIndex]
        //
        if (BufferSize == ReadLength[PositionIndex]) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid093;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid094;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Read() Basic Test - checkpoint1",
                       L"%a:%d: BufferSize - %d, Expected - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       BufferSize,
                       ReadLength[PositionIndex]
                       );
        //
        // file position is updated
        //
        if (FilePosition == (SetPosition[PositionIndex] + ReadLength[PositionIndex])) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid095;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid096;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Read() Basic Test - checkpoint1",
                       L"%a:%d: position before read - %d, position after read - %d, RequestedReadLeng - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       (UINTN)SetPosition[PositionIndex],
                       (UINTN)FilePosition,
                       ReadLength[PositionIndex]
                       );
      }

      //
      // check read content
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      for (Index = 0; Index < BufferSize; Index++) {
        if (Buffer[Index] != 0x33) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid097;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid098;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Read() Basic Test - checkpoint1",
                     L"%a:%d: BufferSize - %d, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     PositionIndex
                     );
    }
  }

Done:

  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
  }

  if (FileHandle != NULL) {
    FileHandle->Delete (FileHandle);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestReadBasicTestCheckpoint2 (
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
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  CHAR16                    FileName[100];
  CHAR16                    DirName[100];
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *DirHandle;
  UINT8                     *Buffer;
  UINTN                     ReadLength[5];
  UINTN                     BufferSize;
  UINTN                     Index;
  UINTN                     Loop;
  EFI_GUID                  TplGuid;

  //
  // init
  //
  Buffer = NULL;
  FileHandle = NULL;
  DirHandle = NULL;
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
    goto Done;
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
    goto Done;
  }

  //
  // init ReadLength[]
  // it is used for L"." entry
  // The exact Length for a read is SIZE_OF_EFI_FILE_INFO + SctStrLen (L".")
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
        goto Done;
      }

      //
      // read
      //
      BufferSize = ReadLength[Index];
      OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
      Status = DirHandle->Read (DirHandle, &BufferSize, Buffer);
      gtBS->RestoreTPL (OldTpl);
      if (Index < 2) {
        if ((EFI_BUFFER_TOO_SMALL == Status)
            && (BufferSize == (SIZE_OF_EFI_FILE_INFO + 4))) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid099;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid100;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Read() Basic Test - checkpoint2",
                       L"%a:%d:Status - %r, BufferSize - %d, Expected - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       BufferSize,
                       SIZE_OF_EFI_FILE_INFO + 4
                       );
      } else {
        if ((EFI_SUCCESS == Status)
            && (BufferSize == (SIZE_OF_EFI_FILE_INFO + 4))) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid101;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid102;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"Read() Basic Test - checkpoint2",
                       L"%a:%d:Status - %r, BufferSize - %d, Expected - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       BufferSize,
                       SIZE_OF_EFI_FILE_INFO + 4
                       );
      }
    }
  }

  //
  // second: before read,file position is at the end of the directory file
  //
  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    for (Index = 0; Index < 5; Index++) {

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
        goto Done;
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
      OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
      Status = DirHandle->Read (DirHandle, &BufferSize, Buffer);
      gtBS->RestoreTPL (OldTpl);
      if ((EFI_SUCCESS == Status) && (BufferSize == 0)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid103;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid104;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Read() Basic Test - checkpoint2",
                     L"%a:%d:Status - %r, BufferSize - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     BufferSize
                     );
    }
  }

Done:

  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
  }

  if (FileHandle != NULL) {
    FileHandle->Delete (FileHandle);
  }

  if (DirHandle != NULL) {
    DirHandle->Delete (DirHandle);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestWriteBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  UINT64                    FileSize = 200;
  UINT8                     *Buffer;
  UINTN                     BufferSize;
  UINT64                    FilePosition;
  UINT64                    SetPosition[9] = {0, 0, 0, 100, 100, 100, 200, 200, 300};
  UINTN                     WriteLength[9] = {50, 200, 250, 50, 100, 200, 0, 100, 1};
  UINTN                     PositionIndex;
  UINTN                     Index;
  EFI_FILE_INFO             *FileInfo;
  UINTN                     InfoSize;
  EFI_GUID                  TplGuid;

  //
  // init
  //
  Buffer = NULL;
  FileHandle = NULL;
  SctStrCpy (FileName, L"BBTestWriteBasicTestCheckpoint1_File");

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
  // allocate buffer for write
  //
  BufferSize = 300;
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
    goto Done;
  }

  //
  // enlarge file by setting file size
  //
  Status = InternalSetFileSize (FileHandle, FileSize);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"set file size fail",
                   L"%a:%d: Status - %r, filesize - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   (UINTN)FileSize
                   );
    goto Done;
  }

  //
  // set the Buffer content with 0x31
  //
  gtBS->SetMem (Buffer, BufferSize, 0x31);

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    for (PositionIndex = 0; PositionIndex < 9; PositionIndex++) {

      //
      // reset file size
      //
      Status = InternalSetFileSize (FileHandle, FileSize);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"set file position fail",
                       L"%a:%d: Status - %r, filesize - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINTN)FileSize
                       );
        continue;
      }

      Status = FileHandle->SetPosition (FileHandle, SetPosition[PositionIndex]);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"set file position fail",
                       L"%a:%d: Status - %r, postion - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINTN)SetPosition[PositionIndex]
                       );
        continue;
      }

      //
      // write data to the file
      //
      BufferSize = WriteLength[PositionIndex];

      OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
      Status = FileHandle->Write (FileHandle, &BufferSize, Buffer);
      gtBS->RestoreTPL (OldTpl);

      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid105;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid106;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Write() Basic Test - checkpoint1",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      Status = FileHandle->GetPosition (FileHandle, &FilePosition);
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid107;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid108;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Write() Basic Test - checkpoint1",
                     L"%a:%d: GetPosition Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      //
      // returned BufferSize is updated,
      // it equals WriteLength[PositionIndex]
      //
      if (BufferSize == WriteLength[PositionIndex]) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid109;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid110;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Write() Basic Test - checkpoint1",
                     L"%a:%d: BufferSize - %d, WriteLenght - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     WriteLength[PositionIndex]
                     );
      //
      // file position is updated
      //
      if (FilePosition == (SetPosition[PositionIndex] + WriteLength[PositionIndex])) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid111;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid112;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Read() Basic Test - checkpoint1",
                     L"%a:%d: position before write - %d, position after write - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     (UINTN)SetPosition[PositionIndex],
                     (UINTN)FilePosition
                     );

      //
      // file size grows
      //
      FileInfo = NULL;
      Status = InternalGetInfo (FileHandle, (VOID **) &FileInfo, &InfoSize, &gBlackBoxEfiFileInfoGuid);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"set file position fail",
                       L"%a:%d: Status - %r, postion - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINTN)SetPosition[PositionIndex]
                       );
        continue;
      }

      //
      // exceed original file size
      //
      if ((SetPosition[PositionIndex] + WriteLength[PositionIndex]) >= FileSize) {
        if (FileInfo->FileSize == FilePosition) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        if (FileInfo->FileSize == FileSize) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid113;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid114;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Write() Basic Test - checkpoint1",
                     L"%a:%d: NewFileSize - %d, NewFilePos - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     (UINTN)FileInfo->FileSize,
                     (UINTN)FilePosition
                     );
      gtBS->FreePool (FileInfo);

      //
      // check read content
      //

      Status = FileHandle->SetPosition (FileHandle, SetPosition[PositionIndex]);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"set file position fail",
                       L"%a:%d: Status - %r, postion - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINTN)SetPosition[PositionIndex]
                       );
        continue;
      }

      Status = FileHandle->Read (FileHandle, &BufferSize, Buffer);
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid115;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid116;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Write() Basic Test - checkpoint1",
                     L"%a:%d: Read Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      AssertionType = EFI_TEST_ASSERTION_PASSED;
      for (Index = 0; Index < BufferSize; Index++) {
        if (Buffer[Index] != 0x31) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }

      if (TplIndex == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid117;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid118;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"Write() Basic Test - checkpoint1",
                     L"%a:%d: BufferSize - %d, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     Index
                     );
    }
  }

Done:

  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
  }

  if (FileHandle != NULL) {
    FileHandle->Delete (FileHandle);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFlushBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  UINT64                    FileSize = 200;
  UINT8                     *Buffer;
  UINTN                     BufferSize;
  EFI_GUID                  TplGuid;

  //
  // init
  //
  Buffer = NULL;
  FileHandle = NULL;
  SctStrCpy (FileName, L"BBTestFlushBasicTestCheckpoint1_File");

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
  // allocate buffer for write
  //
  BufferSize = (UINTN)FileSize;
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
    goto Done;
  }

  //
  // set the Buffer content with 0x31
  //
  gtBS->SetMem (Buffer, BufferSize, 0x31);

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    //
    // reset file size
    //
    Status = InternalSetFileSize (FileHandle, 0);
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

    //
    // flush data to the file
    //
    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = FileHandle->Flush (FileHandle);
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid119;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid120;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Flush() Basic Test - checkpoint1",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

Done:

  if (Buffer != NULL) {
    gtBS->FreePool (Buffer);
  }

  if (FileHandle != NULL) {
    FileHandle->Delete (FileHandle);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestFlushBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  CHAR16                    DirName[100];
  CHAR16                    FileName[100];
  EFI_FILE                  *FileHandle;
  EFI_FILE                  *DirHandle;
  EFI_GUID                  TplGuid;

  //
  // init
  //
  DirHandle = NULL;

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

  SctStrCpy (DirName, L"BBTestFlushBasicTestCheckpoint2_Dir");
  SctStrCpy (FileName, L"BBTestFlushBasicTestCheckpoint2_File");

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
    goto Done;
  }

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    FileHandle = NULL;

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
      goto Done;
    }

    //
    // flush data to the dir
    //
    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = DirHandle->Flush (DirHandle);
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid121;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid122;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"Flush() Basic Test - checkpoint2",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (FileHandle != NULL) {
      FileHandle->Delete (FileHandle);
    }
  }

Done:

  if (DirHandle != NULL) {
    DirHandle->Delete (DirHandle);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetPositionBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  CHAR16                    FileName[3][100];
//  EFI_FILE                  *FileHandle[3];
  EFI_FILE                  *OpenFileHandle[3];
  UINTN                     PositionIndex;
  UINT64                    FileSize = 200;
  UINT64                    Position[6] = {0, 0xFFFFFFFFFFFFFFFF, 1, 120, 200, 250};
  UINT64                    OpenMode[3] = {
                                  OPEN_R_W_MODE,
                                  EFI_FILE_MODE_READ,
                                  EFI_FILE_MODE_READ,
                                  };
  UINT64                    Attributes[3] = {0, 0, EFI_FILE_READ_ONLY};
  UINT64                    GetPosition;
  EFI_STATUS                Status1, Status2;
  EFI_GUID                  TplGuid;

  //
  // init
  //

  gtBS->SetMem (OpenFileHandle, 3 * sizeof (EFI_FILE*), 0);

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

  SctStrCpy (FileName[0], L"BBTestSetPositionBasicTestCheckpoint1_File");
  SctStrCpy (FileName[1], L"BBTestSetPositionBasicTestCheckpoint1_ReadOnlyOpenFile");
  SctStrCpy (FileName[2], L"BBTestSetPositionBasicTestCheckpoint1_ReadOnlyFile");


  //
  // create the files
  //
  for (Index = 0; Index < 3; Index++) {
    OpenFileHandle[Index] = NULL;
  }

  for (Index = 0; Index < 3; Index++) {
    Status = Root->Open (
                     Root,
                     &OpenFileHandle[Index],
                     FileName[Index],
                     CREATE_FILE_MODE,
                     0
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Create file fail",
                     L"%a:%d: Status - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      goto NextLoop;
    }

    //
    // set file size and attributes
    //

    Status1 = InternalSetFileSize (OpenFileHandle[Index], FileSize);
    if (EFI_ERROR (Status1)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"Set File  Size fail",
                     L"%a:%d: Status1 - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1,
                     Index
                     );
      goto NextLoop;
    }

    Status2 = InternalSetFileAttribute (OpenFileHandle[Index], Attributes[Index]);

    if (EFI_ERROR (Status2)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"Set File Attribute fail",
                     L"%a:%d:  Status2 - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status2,
                     Index
                     );
      goto NextLoop;
    }

    //
    // open the files
    //
    if (OpenFileHandle[Index] != NULL) {
      OpenFileHandle[Index] -> Close (OpenFileHandle[Index]);
      OpenFileHandle[Index] = NULL;
    }
    Status = Root->Open (
                     Root,
                     &OpenFileHandle[Index],
                     FileName[Index],
                     OpenMode[Index],
                     0
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"open file fail",
                     L"%a:%d: Status - %r, Index - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index
                     );
      goto NextLoop;
    }


    for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

      for (PositionIndex = 0; PositionIndex < 6; PositionIndex++) {

        //
        // set file position
        //
        OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
        Status = OpenFileHandle[Index]->SetPosition (
                                          OpenFileHandle[Index],
                                          Position[PositionIndex]
                                          );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid123;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid124;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"SetPosition() Basic Test - checkpoint1",
                       L"%a:%d: SetStatus - %r, Index - %d,Position - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index,
                       Position[PositionIndex]
                       );
        //
        // get file position
        //
        Status = OpenFileHandle[Index]->GetPosition (
                                          OpenFileHandle[Index],
                                          &GetPosition
                                          );
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid125;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid126;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"SetPosition() Basic Test - checkpoint1",
                       L"%a:%d: GetStatus - %r, Index - %d,Position - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index,
                       (UINTN)GetPosition
                       );
        //
        // compare the retrieved one with the set one
        //
        if (Position[PositionIndex] == (UINT64)-1) {
          if (GetPosition == FileSize) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          if (GetPosition == Position[PositionIndex]) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid127;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid128;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"SetPosition() Basic Test - checkpoint1",
                       L"%a:%d: Index - %d,GetPosition - %d,SetPosition - %d ",
                       __FILE__,
                       (UINTN)__LINE__,
                       Index,
                       (UINTN)GetPosition,
                       (UINTN)Position[PositionIndex]
                       );
      }
    }
NextLoop:
    if (OpenMode[Index] == EFI_FILE_MODE_READ) {
      if (OpenFileHandle[Index] != NULL) {
        InternalSetFileAttribute (OpenFileHandle[Index], 0);
        OpenFileHandle[Index] -> Close (OpenFileHandle[Index]);
        OpenFileHandle[Index] = NULL;
        Status = Root->Open (
                         Root,
                         &OpenFileHandle[Index],
                         FileName[Index],
                         CREATE_FILE_MODE,
                         0
                         );
      }
    }
    if (OpenFileHandle[Index] != NULL) {
      OpenFileHandle[Index]->Delete (OpenFileHandle[Index]);
      OpenFileHandle[Index] = NULL;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetPositionBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  EFI_TPL                   OldTpl;
  CHAR16                    DirName[100];
  EFI_FILE                  *DirHandle;
  EFI_GUID                  TplGuid;

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

  SctStrCpy (DirName, L"BBTestSetPositionBasicTestCheckpoint2_Dir");

  //
  // create the dir
  //
  DirHandle = NULL;
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
    goto Done;
  }

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    //
    // set file position
    //
    OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
    Status = DirHandle->SetPosition (DirHandle, 0);
    gtBS->RestoreTPL (OldTpl);

    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (TplIndex == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid129;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid130;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"SetPosition() Basic Test - checkpoint2",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

Done:

  if (DirHandle != NULL) {
    DirHandle->Delete (DirHandle);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetPositionBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     TplIndex;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  CHAR16                    FileName[3][100];
  EFI_FILE                  *FileHandle[3];
//  EFI_FILE                  *OpenFileHandle[3];
  UINTN                     PositionIndex;
  UINT64                    FileSize = 200;
  UINT64                    Position[6] = {0, 0xFFFFFFFFFFFFFFFF, 1, 120, 200, 250};
  UINT64                    OpenMode[3] = {
                                  OPEN_R_W_MODE,
                                  OPEN_R_W_MODE,
                                  OPEN_R_W_MODE
                                  };
  UINT64                    Attributes[3] = {0, 0, EFI_FILE_READ_ONLY};
  UINT64                    GetPosition;
  EFI_STATUS                Status1, Status2;
  EFI_GUID                  TplGuid;

  //
  // init
  //
  gtBS->SetMem (FileHandle, 3 * sizeof (EFI_FILE*), 0);
//  gtBS->SetMem (OpenFileHandle, 3 * sizeof (EFI_FILE*), 0);

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

  SctStrCpy (FileName[0], L"BBTestGetPositionBasicTestCheckpoint1_File");
  SctStrCpy (FileName[1], L"BBTestGetPositionBasicTestCheckpoint1_File");
  SctStrCpy (FileName[2], L"BBTestGetPositionBasicTestCheckpoint1_ReadOnlyFile");

  //
  // create the files
  //

  for (TplIndex = 0; TplIndex < TPL_ARRAY_SIZE; TplIndex++) {

    for (Index = 0; Index < 3; Index++) {
      FileHandle[Index] = NULL;
      Status = Root->Open (
                       Root,
                       &FileHandle[Index],
                       FileName[Index],
                       CREATE_FILE_MODE,
                       0
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Create file fail",
                       L"%a:%d: Status - %r, Index - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index
                       );
        goto Done;
      }
      if (FileHandle[Index] != NULL) {
        FileHandle[Index]->Close(FileHandle[Index]);
        FileHandle[Index] = NULL;
      }

    //
    // open the files
    //

//      OpenFileHandle[Index] = NULL;
      Status = Root->Open (
                       Root,
                       &FileHandle[Index],
                       FileName[Index],
                       OpenMode[Index],
                       0
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"open file fail",
                       L"%a:%d: Status - %r, Index - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index
                       );
        goto Done;
      }


      //
      // set file size and attributes
      //

      Status1 = InternalSetFileSize (FileHandle[Index], FileSize);
      if (EFI_ERROR (Status1)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Set File  Size fail",
                       L"%a:%d: Status1 - %r, Index - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status1,
                       Index
                       );
        goto Done;
      }
      Status2 = InternalSetFileAttribute (FileHandle[Index], Attributes[Index]);

      if (EFI_ERROR (Status2)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"Set File Attribute fail",
                       L"%a:%d:  Status2 - %r, Index - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status2,
                       Index
                       );
        goto Done;
      }

      for (PositionIndex = 0; PositionIndex < 6; PositionIndex++) {

        //
        // set file position
        //
        Status = FileHandle[Index]->SetPosition (
                                      FileHandle[Index],
                                      Position[PositionIndex]
                                      );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"SetPosition failed",
                         L"%a:%d: SetStatus - %r, Index - %d,Position - %d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         Index,
                         Position[PositionIndex]
                         );
          continue;
        }

        //
        // get file position
        //
        OldTpl = gtBS->RaiseTPL (TplArray[TplIndex]);
        Status = FileHandle[Index]->GetPosition (
                                      FileHandle[Index],
                                      &GetPosition
                                      );
        gtBS->RestoreTPL (OldTpl);

        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid131;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid132;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"GetPosition() Basic Test - checkpoint1",
                       L"%a:%d: GetStatus - %r, Index - %d,Position - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Index,
                       (UINTN)GetPosition
                       );
        //
        // compare the retrieved one with the set one
        //
        if (Position[PositionIndex] == (UINT64)-1) {
          if (GetPosition == FileSize) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        } else {
          if (GetPosition == Position[PositionIndex]) {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
        }

        if (TplIndex == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid133;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid134;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"GetPosition() Basic Test - checkpoint1",
                       L"%a:%d: Index - %d,GetPosition - %d,SetPosition - %d ",
                       __FILE__,
                       (UINTN)__LINE__,
                       Index,
                       (UINTN)GetPosition,
                       (UINTN)Position[PositionIndex]
                       );
      }

Done:
      if (FileHandle[Index] != NULL) {
        FileHandle[Index]->Delete (FileHandle[Index]);
      }
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetInfoBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  CHAR16                    *PureFileNameArray;
  CHAR16                    *PureStrPointer;
  UINT32                    Count;
  EFI_FILE                  *FileHandle;
  UINTN                     BufferSize;
  EFI_FILE_INFO             *FileInfo;
  UINTN                     NameIndex;
  UINTN                     AttributesIndex;
  UINTN                     MaxNameIndex;
  UINTN                     MaxAttributesIndex;
  EFI_GUID                  TplGuid;

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
  // compose pure file name array
  //
  Status = ComposeFileNameArray (&PureFileNameArray, &Count);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ComposeFileNameArray fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  if (IsStress) {
    MaxNameIndex = Count;
    MaxAttributesIndex = ALL_ATTRIBUTES_COUNT_FOR_CREATE;
  } else {
    MaxNameIndex = 1;
    MaxAttributesIndex = 1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
         NameIndex++, PureStrPointer += MAX_STRING_LENGTH) {

      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {

        FileHandle = NULL;

        //
        // create a file
        //

        Status = Root->Open (
                         Root,
                         &FileHandle,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[AttributesIndex]
                         );
        if (EFI_ERROR (Status)) {
          continue;
        }

        //
        // get info
        //
        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = InternalGetInfo (FileHandle, (VOID **) &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
        gtBS->RestoreTPL (OldTpl);

        //
        // check 1: return status
        //
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid135;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid136;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"GetInfo() Basic Test - checkpoint1",
                       L"%a:%d: Status - %r, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       TplArray[Index]
                       );
        if (EFI_ERROR (Status)) {
          FileHandle->Delete (FileHandle);
          continue;
        }

        //
        // check 2: Size check
        //
        if (BufferSize == FileInfo->Size) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid137;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid138;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"GetInfo() Basic Test - checkpoint1",
                       L"%a:%d: FileInfo->Size - %d, BufferSize - %d, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       (UINTN)FileInfo->Size,
                       BufferSize,
                       TplArray[Index]
                       );
        //
        // check 3: Attribute check
        //
        if ((FileInfo->Attribute | EFI_FILE_ARCHIVE) ==
                     (ValidAttributesForCreate[AttributesIndex] | EFI_FILE_ARCHIVE)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid139;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid140;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"GetInfo() Basic Test - checkpoint1",
                       L"%a:%d: FileInfo->Attribute - %x, Attribute - %x, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       (UINTN)FileInfo->Attribute,
                       (UINTN)ValidAttributesForCreate[AttributesIndex],
                       TplArray[Index]
                       );
        //
        // check 4: file name check
        //
        if (!SctStrCmp (FileInfo->FileName, PureStrPointer)) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid141;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid142;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"GetInfo() Basic Test - checkpoint1",
                       L"%a:%d: FileInfo->FileName - %s, FileName - %s, TPL - %d",
                       __FILE__,
                       (UINTN)__LINE__,
                       FileInfo->FileName,
                       PureStrPointer,
                       TplArray[Index]
                       );

        FileHandle->Delete (FileHandle);
        gtBS->FreePool (FileInfo);
      }
    }
  }

  gtBS->FreePool (PureFileNameArray);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetInfoBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  UINTN                     BufferSize;
  EFI_FILE_INFO             *FileInfo;
  EFI_GUID                  TplGuid;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // get EFI_FILE info from the Root
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = InternalGetInfo (Root, (VOID **) &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
    gtBS->RestoreTPL (OldTpl);

    //
    // check 1: return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid143;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid144;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"GetInfo() Basic Test - checkpoint2",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // check 2: Size check
    //
    if (BufferSize == FileInfo->Size) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid145;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid146;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"GetInfo() Basic Test - checkpoint2",
                   L"%a:%d: FileInfo->Size - %d, BufferSize - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   FileInfo->Size,
                   BufferSize
                   );

    gtBS->FreePool (FileInfo);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetInfoBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  UINTN                     BufferSize[2];
  EFI_FILE_SYSTEM_INFO      *SystemInfo[2];
  UINTN                     InfoIndex;
  EFI_FILE                  *FileHandle[100];
  CHAR16                    BasicFileName[100];
  CHAR16                    *FileNamePool;
  CHAR16                    *FileName;
  UINTN                     FileIndex;
  UINTN                     ArraySize;
  BOOLEAN                   VolumeChanged = FALSE;
  EFI_GUID                  TplGuid;

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

  FileNamePool = NULL;
  ArraySize = MAX_STRING_LENGTH * 100;
  SctStrCpy (BasicFileName, L"BBTestGetInfoBasicTestCheckpoint3_File");

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&FileNamePool
                   );

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Init
    //
    gtBS->SetMem (SystemInfo, 2 * sizeof (EFI_FILE_SYSTEM_INFO*), 0);
    gtBS->SetMem (FileHandle, 100 * sizeof (EFI_FILE*), 0);

    for (InfoIndex = 0; InfoIndex < 2; InfoIndex++) {

      //
      // create some files in the root directory before retrieving
      // the second system information
      //
      if (InfoIndex == 1) {

        VolumeChanged = FALSE;

        FileName = FileNamePool;
        for (FileIndex = 0; FileIndex < 100; FileIndex++, FileName += MAX_STRING_LENGTH) {

          SctSPrint (FileName, MAX_STRING_LENGTH, L"%s_%d", BasicFileName, FileIndex);

          Status = Root->Open (
                    Root,
                    &FileHandle[FileIndex],
                    FileName,
                    EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                    0);
          if (EFI_ERROR (Status)) {
            continue;
          }

          //
          // Set each file size to 800
          //
          Status = InternalSetFileSize (FileHandle[FileIndex], 800);
          if (EFI_ERROR (Status)) {
            continue;
          }

          VolumeChanged = TRUE;
        }
      }

      //
      // get EFI_FILE_SYSTEM_INFO from the Root
      //
      OldTpl = gtBS->RaiseTPL (TplArray[Index]);
      Status = InternalGetInfo (
                 Root,
                 (VOID **) &SystemInfo[InfoIndex],
                 &BufferSize[InfoIndex],
                 &gBlackBoxEfiFileSystemInfoGuid
                 );
      gtBS->RestoreTPL (OldTpl);

      //
      // check 1: return status
      //
      if (EFI_SUCCESS == Status) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid147;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid148;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"GetInfo() Basic Test - checkpoint3",
                     L"%a:%d: Status - %r, Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     TplArray[Index]
                     );
      if (EFI_ERROR (Status)) {
        goto NextTpl;
      }

      //
      // check 2: Size check
      //
      if (BufferSize[InfoIndex] == SystemInfo[InfoIndex]->Size) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid149;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid150;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"GetInfo() Basic Test - checkpoint3",
                     L"%a:%d: SystemInfo->Size - %d, BufferSize - %d, Tpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     (UINTN)SystemInfo[InfoIndex]->Size,
                     BufferSize[InfoIndex],
                     TplArray[Index]
                     );
    }

    //
    // compare the two system info
    //

    if ((SystemInfo[0]->Size == SystemInfo[1]->Size)
        && (SystemInfo[0]->ReadOnly == SystemInfo[1]->ReadOnly)
        && (SystemInfo[0]->VolumeSize == SystemInfo[1]->VolumeSize)
        && (SystemInfo[0]->BlockSize == SystemInfo[1]->BlockSize)
        && (!SctStrCmp (SystemInfo[0]->VolumeLabel, SystemInfo[1]->VolumeLabel))) {

      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid151;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid152;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"GetInfo() Basic Test - checkpoint3",
                   L"%a:%d: compare System Info, Tpl - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   TplArray[Index]
                   );

    //
    // compare free space change if files are created successfully on the volume.
    //
    if (VolumeChanged) {
      if (SystemInfo[0]->FreeSpace > SystemInfo[1]->FreeSpace){
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (Index == 0) {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid153;
      } else {
        TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid154;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     TplGuid,
                     L"GetInfo() Basic Test - checkpoint3",
                     L"%a:%d: FreeSpace1: 0x%x, FreeSpace2: 0x%x",
                     __FILE__,
                     (UINTN)__LINE__,
                     (UINTN)SystemInfo[0]->FreeSpace,
                     (UINTN)SystemInfo[1]->FreeSpace
                     );
    }

NextTpl:

    for (InfoIndex = 0; InfoIndex < 2; InfoIndex++) {
      if (SystemInfo[InfoIndex] != NULL) {
        gtBS->FreePool (SystemInfo[InfoIndex]);
      }
    }

    for (FileIndex = 0; FileIndex < 100; FileIndex++) {
      if (FileHandle[FileIndex] != NULL) {
        FileHandle[FileIndex]->Delete (FileHandle[FileIndex]);
      }
    }

    if (EFI_ERROR (Status)) {
      break;
    }
  }

  if (FileNamePool != NULL) {
    gtBS->FreePool (FileNamePool);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetInfoBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  UINTN                     SystemInfoSize;
  UINTN                     VolumeLabelSize;
  EFI_FILE_SYSTEM_INFO      *SystemInfo;
  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO   *VolumeLabel;
  EFI_GUID                  TplGuid;

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Init
    //
    SystemInfo = NULL;
    VolumeLabel = NULL;

    //
    // get EFI_FILE_SYSTEM_VOLUME_LABEL_INFO from the Root
    //
    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = InternalGetInfo (
               Root,
               (VOID **) &VolumeLabel,
               &VolumeLabelSize,
               &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid
               );
    gtBS->RestoreTPL (OldTpl);

    //
    // check 1: return status
    //
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid155;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid156;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"GetInfo() Basic Test - checkpoint4",
                   L"%a:%d: get VolumeLabel Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // check 2: retrieve SystemInfo
    //
    Status = InternalGetInfo (
               Root,
               (VOID **) &SystemInfo,
               &SystemInfoSize,
               &gBlackBoxEfiFileSystemInfoGuid
               );
    if (EFI_SUCCESS == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid157;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid158;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"GetInfo() Basic Test - checkpoint4",
                   L"%a:%d: get SystemInfo Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (EFI_ERROR (Status)) {
      goto NextLoop;
    }

    //
    // check 3: compare VolumeLabel with SystemInfo
    //
    if (!SctStrCmp (VolumeLabel->VolumeLabel, SystemInfo->VolumeLabel)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid159;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid160;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"GetInfo() Basic Test - checkpoint4",
                   L"%a:%d: VolumeLabel->VolumeLabel - %s, SystemInfo->VolumeLabel - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   VolumeLabel->VolumeLabel,
                   SystemInfo->VolumeLabel
                   );

NextLoop:

    if (SystemInfo != NULL) {
      gtBS->FreePool (SystemInfo);
    }

    if (VolumeLabel != NULL) {
      gtBS->FreePool (VolumeLabel);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetInfoBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  CHAR16                    *PureFileNameArray;
  CHAR16                    *PureStrPointer;
  UINT32                    Count;
  EFI_FILE                  *FileHandle;
  UINTN                     BufferSize;
  EFI_FILE_INFO             *NewFileInfo;
  EFI_FILE_INFO             *FileInfo;
  UINTN                     NameIndex;
  UINTN                     AttributesIndex;
  CHAR16                    ChangeFileName[100];
  UINTN                     MaxNameIndex;
  UINTN                     MaxAttributesIndex;
  EFI_GUID                  TplGuid;

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

  SctStrCpy (ChangeFileName, L"BBTestSetInfoBasicTestCheckpoint1_File");

  //
  // compose pure file name array
  //
  Status = ComposeFileNameArray (&PureFileNameArray, &Count);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"ComposeFileNameArray fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  if (IsStress) {
    MaxNameIndex = Count;
    MaxAttributesIndex = VALID_DIRECTORY_ATTRIBUTES_INDEX_FOR_CREATE;
  } else {
    MaxNameIndex = 1;
    MaxAttributesIndex = 1;
  }

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    PureStrPointer = PureFileNameArray;
    for (NameIndex = 0; NameIndex < MaxNameIndex;
         NameIndex++, PureStrPointer += MAX_STRING_LENGTH) {

      for (AttributesIndex = 0; AttributesIndex < MaxAttributesIndex; AttributesIndex++) {

        FileHandle = NULL;
        FileInfo = NULL;
        NewFileInfo = NULL;

        //
        // create a file
        //

        Status = Root->Open (
                         Root,
                         &FileHandle,
                         PureStrPointer,
                         EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE|EFI_FILE_MODE_CREATE,
                         ValidAttributesForCreate[AttributesIndex]
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
          continue;
        }

        //
        // get info
        //
        Status = InternalGetInfo (FileHandle, (VOID **) &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"GetInfo fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          FileHandle->Delete (FileHandle);
          continue;
        }

        //
        // update all updateable fields
        //

        Status = gtBS->AllocatePool (
                         EfiBootServicesData,
                         (BufferSize + 0x1000),
                         (VOID**)&NewFileInfo
                         );
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
          goto NextLoop;
        }

        gtBS->CopyMem (NewFileInfo, FileInfo, BufferSize);

        //
        // free FileInfo AND reset the pointer
        //
        gtBS->FreePool (FileInfo);
        FileInfo = NULL;

        //
        // enlarge FileSize;
        // change file name;
        // invert Attribute (do not include EFI_FILE_DIRECTORY inversion)
        //
        NewFileInfo->FileSize = 0x100;
        SctStrCpy (NewFileInfo->FileName, ChangeFileName);
        InvertFileAttributes (NewFileInfo);

        //
        // update the Size
        //
        NewFileInfo->Size = SIZE_OF_EFI_FILE_INFO + SctStrSize (NewFileInfo->FileName);

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);

        Status = FileHandle->SetInfo (
                               FileHandle,
                               &gBlackBoxEfiFileInfoGuid,
                               (UINTN)(BufferSize + 0x1000),
                               NewFileInfo
                               );

        gtBS->RestoreTPL (OldTpl);

        //
        // check 1: return status
        //
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid161;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid162;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"SetInfo() Basic Test - checkpoint1",
                       L"%a:%d: Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        if (EFI_ERROR (Status)) {
          goto NextLoop;
        }

        //
        // check 2: get info and compare
        //


        Status = InternalGetInfo (FileHandle, (VOID **) &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"GetInfo fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          goto NextLoop;
        }


        //
        // the Attribute always add EFI_FILE_ARCHIVE. <-- is it a bug?
        //
        if ((NewFileInfo->FileSize == FileInfo->FileSize) && (NewFileInfo->Size == FileInfo->Size)
            && !SctStrCmp (NewFileInfo->FileName, (FileInfo->FileName))
            && ((NewFileInfo->Attribute | EFI_FILE_ARCHIVE) == (FileInfo->Attribute | EFI_FILE_ARCHIVE))) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid163;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid164;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"SetInfo() Basic Test - checkpoint1",
                       L"%a:%d: OldFileSize = 0x%lx, NewFileSize = 0x%lx, OldSize = 0x%lx, NewSize = 0x%lx, OldAttribute = 0x%lx, NewAttribute = 0x%lx",
                       __FILE__,
                       (UINTN)__LINE__,
                       FileInfo->FileSize,
                       NewFileInfo->FileSize,
                       FileInfo->Size,
                       NewFileInfo->Size,
                       FileInfo->Attribute,
                       NewFileInfo->Attribute
                       );
        //
        // free FileInfo AND reset the pointer
        //
        gtBS->FreePool (FileInfo);
        FileInfo = NULL;

        //
        // check 3:
        // reduce FileSize and set info again
        //
        NewFileInfo->FileSize -= 0x50;

        OldTpl = gtBS->RaiseTPL (TplArray[Index]);
        Status = FileHandle->SetInfo (
                               FileHandle,
                               &gBlackBoxEfiFileInfoGuid,
                               (UINTN)(BufferSize + 0x1000),
                               NewFileInfo
                               );
        gtBS->RestoreTPL (OldTpl);

        //
        // check return status
        //
        if (EFI_SUCCESS == Status) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid165;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid166;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"SetInfo() Basic Test - checkpoint1",
                       L"%a:%d: Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        if (EFI_ERROR (Status)) {
          goto NextLoop;
        }

        //
        // get info and compare
        //

        Status = InternalGetInfo (FileHandle, (VOID **) &FileInfo, &BufferSize, &gBlackBoxEfiFileInfoGuid);
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"GetInfo fail",
                         L"%a:%d: Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          goto NextLoop;
        }

        if ((NewFileInfo->FileSize == FileInfo->FileSize)
            && !SctStrCmp (NewFileInfo->FileName, (FileInfo->FileName))
            && ((NewFileInfo->Attribute | EFI_FILE_ARCHIVE) == (FileInfo->Attribute | EFI_FILE_ARCHIVE))) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        if (Index == 0) {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid167;
        } else {
          TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid168;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       TplGuid,
                       L"SetInfo() Basic Test - checkpoint1",
                       L"%a:%d: OldFileSize = 0x%lx, NewFileSize = 0x%lx, OldAttribute = 0x%lx, NewAttribute = 0x%lx",
                       __FILE__,
                       (UINTN)__LINE__,
                       FileInfo->FileSize,
                       NewFileInfo->FileSize,
                       FileInfo->Attribute,
                       NewFileInfo->Attribute
                       );
NextLoop:

        FileHandle->Delete (FileHandle);

        if (FileInfo != NULL) {
          gtBS->FreePool (FileInfo);
        }

        if (NewFileInfo != NULL) {
          gtBS->FreePool (NewFileInfo);
        }
      }
    }
  }

  gtBS->FreePool (PureFileNameArray);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetInfoBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  UINTN                     BufferSize;
  EFI_FILE_SYSTEM_INFO      *NewSystemInfo;
  EFI_FILE_SYSTEM_INFO      *SavedSystemInfo;
  EFI_FILE_SYSTEM_INFO      *SystemInfo;
  CHAR16                    NewVolumeLabel[11];
  EFI_GUID                  TplGuid;

  SctStrCpy (NewVolumeLabel, L"123456");

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Init
    //
    NewSystemInfo = NULL;
    SavedSystemInfo = NULL;
    SystemInfo = NULL;

    //
    // get EFI_FILE_SYSTEM_INFO from the Root
    //
    Status = InternalGetInfo (
               Root,
               (VOID **) &SavedSystemInfo,
               &BufferSize,
               &gBlackBoxEfiFileSystemInfoGuid
               );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Get SystemInfo fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    // set new system info
    //
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     (BufferSize + 0x1000),
                     (VOID**)&NewSystemInfo
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Allocate Pool fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    //
    // copy the old content to the new first
    //
    gtBS->CopyMem (NewSystemInfo, SavedSystemInfo, BufferSize);

    SctStrCpy (NewSystemInfo->VolumeLabel, NewVolumeLabel);

    // update Size
    NewSystemInfo->Size = SIZE_OF_EFI_FILE_SYSTEM_INFO + SctStrSize (NewVolumeLabel);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = Root->SetInfo (
                     Root,
                     &gBlackBoxEfiFileSystemInfoGuid,
                     (UINTN)(BufferSize + 0x1000),
                     NewSystemInfo
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check 1: return status
    //
    if (EFI_SUCCESS == Status || EFI_WRITE_PROTECTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid169;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid170;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"SetInfo() Basic Test - checkpoint2",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (EFI_ERROR (Status)) {
      goto NextLoop;
    }

    //
    // check 2: content check
    //
    Status = InternalGetInfo (
               Root,
               (VOID**)&SystemInfo,
               &BufferSize,
               &gBlackBoxEfiFileSystemInfoGuid
               );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Get SystemInfo fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    if (!SctStrCmp (SystemInfo->VolumeLabel, NewVolumeLabel)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid171;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid172;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"SetInfo() Basic Test - checkpoint2",
                   L"%a:%d: SystemInfo->VolumeLabel - %s, NewVolumeLabel - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   SystemInfo->VolumeLabel,
                   NewVolumeLabel
                   );
NextLoop:

    //
    // restore Volume Label
    //
    if (SavedSystemInfo != NULL) {
      Root->SetInfo (Root, &gBlackBoxEfiFileSystemInfoGuid, (UINTN)(BufferSize + 0x1000), SavedSystemInfo);
      gtBS->FreePool (SavedSystemInfo);
    }

    if (NewSystemInfo != NULL) {
      gtBS->FreePool (NewSystemInfo);
    }

    if (SystemInfo != NULL) {
      gtBS->FreePool (SystemInfo);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetInfoBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  )
{
  EFI_STATUS                Status;
  EFI_FILE                  *Root;
  EFI_TEST_ASSERTION        AssertionType;
  UINTN                     Index;
  EFI_TPL                   OldTpl;
  UINTN                     BufferSize;
  UINTN                     SavedBufferSize;
  EFI_FILE_SYSTEM_INFO      *SystemInfo;
  CHAR16                    NewVolumeLabelString[11];

  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO   *SavedVolumeLabel;
  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO   *VolumeLabel;
  EFI_FILE_SYSTEM_VOLUME_LABEL_INFO   *NewVolumeLabel;

  EFI_GUID                  TplGuid;

  SctStrCpy (NewVolumeLabelString, L"123456789");

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

  for (Index = 0; Index < TPL_ARRAY_SIZE; Index++) {

    //
    // Init
    //
    NewVolumeLabel = NULL;
    SavedVolumeLabel = NULL;
    VolumeLabel = NULL;
    SystemInfo = NULL;

    //
    // get EFI_FILE_SYSTEM_VOLUME_LABEL from the Root
    //
    Status = InternalGetInfo (
               Root,
               (VOID**)&SavedVolumeLabel,
               &BufferSize,
               &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid
               );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Get SystemInfo fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    SavedBufferSize = BufferSize;

    //
    // set new volume label info
    //
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     (BufferSize + 0x1000),
                     (VOID**)&NewVolumeLabel
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Allocate Pool fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    SctStrCpy (NewVolumeLabel->VolumeLabel, NewVolumeLabelString);

    OldTpl = gtBS->RaiseTPL (TplArray[Index]);
    Status = Root->SetInfo (
                     Root,
                     &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid,
                     (UINTN)(BufferSize + 0x1000),
                     NewVolumeLabel
                     );
    gtBS->RestoreTPL (OldTpl);

    //
    // check 1: return status
    //
    if (EFI_SUCCESS == Status || EFI_WRITE_PROTECTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid173;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid174;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"SetInfo() Basic Test - checkpoint3",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (EFI_ERROR (Status)) {
      goto NextLoop;
    }

    //
    // check 2: content check
    //
    Status = InternalGetInfo (
               Root,
               (VOID**)&VolumeLabel,
               &BufferSize,
               &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid
               );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Get SystemVolumeLabel fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    if (!SctStrCmp (VolumeLabel->VolumeLabel, NewVolumeLabelString)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid175;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid176;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"SetInfo() Basic Test - checkpoint3",
                   L"%a:%d: VolumeLabel->VolumeLabel - %s, NewVolumeLabel - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   VolumeLabel->VolumeLabel,
                   NewVolumeLabelString
                   );
    //
    // check 3: content check with SystemInfo
    //
    Status = InternalGetInfo (
               Root,
               (VOID**)&SystemInfo,
               &BufferSize,
               &gBlackBoxEfiFileSystemInfoGuid
               );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Get SystemInfo fail",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto NextLoop;
    }

    if (!SctStrCmp (SystemInfo->VolumeLabel, NewVolumeLabelString)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Index == 0) {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid177;
    } else {
      TplGuid = gSimpleFileSystemBBTestFunctionAssertionGuid178;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   TplGuid,
                   L"SetInfo() Basic Test - checkpoint3",
                   L"%a:%d: SystemInfo->VolumeLabel - %s, NewVolumeLabel - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   SystemInfo->VolumeLabel,
                   NewVolumeLabelString
                   );
NextLoop:

    //
    // restore Volume Label
    //
    if (SavedVolumeLabel != NULL) {
      Root->SetInfo (
              Root,
              &gBlackBoxEfiFileSystemVolumeLabelInfoIdGuid,
              (UINTN)(SavedBufferSize + 0x1000),
              SavedVolumeLabel
              );
      gtBS->FreePool (SavedVolumeLabel);
    }

    if (NewVolumeLabel != NULL) {
      gtBS->FreePool (NewVolumeLabel);
    }

    if (VolumeLabel != NULL) {
      gtBS->FreePool (VolumeLabel);
    }

    if (SystemInfo != NULL) {
      gtBS->FreePool (SystemInfo);
    }
  }

  return EFI_SUCCESS;
}

VOID
InvertFileAttributes (
  EFI_FILE_INFO   *FileInfo
  )
{
  UINT64      Attribute;

  Attribute = FileInfo->Attribute;

  if (Attribute & EFI_FILE_READ_ONLY) {
    Attribute &= (UINT64)(~EFI_FILE_READ_ONLY);
  }

  if (Attribute & EFI_FILE_HIDDEN) {
    Attribute &= (UINT64)(~EFI_FILE_HIDDEN);
  }

  if (Attribute & EFI_FILE_SYSTEM) {
    Attribute &= (UINT64)(~EFI_FILE_SYSTEM);
  }

  if (Attribute & EFI_FILE_ARCHIVE) {
    Attribute &= (UINT64)(~EFI_FILE_ARCHIVE);
  }

  FileInfo->Attribute = Attribute;

}

EFI_STATUS
InternalGetInfo (
  EFI_FILE      *FileHandle,
  VOID          **InfoBuffer,
  UINTN         *BufferSize,
  EFI_GUID      *InfoId
  )
{
  UINT8         *Buffer = NULL;
  EFI_STATUS    Status = EFI_SUCCESS;

  *InfoBuffer = NULL;

  *BufferSize = 1;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   *BufferSize,
                   (VOID**)&Buffer
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = FileHandle->GetInfo (
                         FileHandle,
                         InfoId,
                         BufferSize,
                         (VOID*)Buffer
                         );
  if (EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL) {
    goto Done;
  }

  if (Status == EFI_BUFFER_TOO_SMALL) {

    gtBS->FreePool ((VOID*)Buffer);
    Buffer = NULL;
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     *BufferSize,
                     (VOID**)&Buffer
                     );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = FileHandle->GetInfo (
                           FileHandle,
                           InfoId,
                           BufferSize,
                           (VOID*)Buffer
                           );
  }

Done:
  if (EFI_ERROR(Status)) {
    if (Buffer != NULL) {
      gtBS->FreePool (Buffer);
      Buffer = NULL;
    }
  }

  *InfoBuffer = Buffer;
  return Status;
}

EFI_STATUS
InternalSetFileSize (
  EFI_FILE      *FileHandle,
  UINT64        FileSize
  )
{
  EFI_FILE_INFO *InfoBuffer;
  UINTN         BufferSize;
  EFI_STATUS    Status;

  Status = InternalGetInfo (FileHandle, (VOID**)&InfoBuffer, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  InfoBuffer->FileSize = FileSize;
  Status = FileHandle->SetInfo (FileHandle, &gBlackBoxEfiFileInfoGuid, BufferSize, InfoBuffer);

  gtBS->FreePool (InfoBuffer);

  return Status;
}

EFI_STATUS
InternalSetFileAttribute (
  EFI_FILE      *FileHandle,
  UINT64        Attribute
  )
{
  EFI_FILE_INFO *InfoBuffer;
  UINTN         BufferSize;
  EFI_STATUS    Status;

  Status = InternalGetInfo (FileHandle, (VOID**) &InfoBuffer, &BufferSize, &gBlackBoxEfiFileInfoGuid);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  InfoBuffer->Attribute = Attribute;
  Status = FileHandle->SetInfo (FileHandle, &gBlackBoxEfiFileInfoGuid, BufferSize, InfoBuffer);

  gtBS->FreePool (InfoBuffer);

  return Status;
}

EFI_STATUS
ComposeFileNameArray (
  CHAR16        **PureFileNameArray,
  UINT32        *NameCount
  )
{
  UINTN                     ArraySize;
  CHAR16                    *NameArray;
  CHAR16                    *StrPointer;
  UINT32                    Count;
  UINT8                     FileBaseNameLength;
  UINT8                     ExtensionNameLength;
  UINT8                     FileBaseNameNum;
  UINT8                     ExtensionNameNum;
  CHAR16                    TempChar;
  UINT8                     TempIndex;
  UINT8                     Loop;
  EFI_STATUS                Status;

  *PureFileNameArray = NULL;
  *NameCount = 0;

  ArraySize = MAX_STRING_LENGTH * MAX_NUMBER_OF_FILE_NAME;

  //
  // compose pure file name array
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   ArraySize * sizeof (CHAR16),
                   (VOID**)&NameArray
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gtBS->SetMem (NameArray, ArraySize * sizeof (CHAR16), 0);

  Count = 0;
  StrPointer = NameArray;
  for (FileBaseNameNum = sizeof (ValidFileBaseName) / sizeof (*ValidFileBaseName);
        FileBaseNameNum > 0;FileBaseNameNum --) {

    FileBaseNameLength = sizeof (ValidFileBaseName[FileBaseNameNum - 1]);

    for (ExtensionNameNum = sizeof (ValidExtensionName) / sizeof (*ValidExtensionName);
          ExtensionNameNum > 0; ExtensionNameNum --){

      ExtensionNameLength = sizeof (ValidExtensionName[ExtensionNameNum - 1]);
      TempIndex = 0;

      for (Loop = 0;Loop < FileBaseNameLength;Loop++){
        TempChar = ValidFileBaseName[FileBaseNameNum - 1][Loop];
        if (TempChar == 0){
          TempIndex = Loop;
          break;
        }
        StrPointer[Loop] = TempChar;
      }

      if (ExtensionNameNum != 1){
        StrPointer[TempIndex++] = (L'.');
      }

      for (Loop = 0;Loop < ExtensionNameLength;Loop++) {
        TempChar = ValidExtensionName[ExtensionNameNum - 1][Loop];
        if (TempChar == 0){
          break;
        }
        StrPointer[Loop + TempIndex] = TempChar;
      }

      StrPointer[Loop + TempIndex] = 0;

      Count++;

      if (Count > MAX_NUMBER_OF_FILE_NAME) {
        break;
      }

      StrPointer += MAX_STRING_LENGTH;
    }
  }

  *PureFileNameArray = NameArray;

#ifdef FILE_SYSTEM_SIMPLE_TEST
  *NameCount = 1;
#else
  *NameCount = Count;
#endif

  return EFI_SUCCESS;
}
