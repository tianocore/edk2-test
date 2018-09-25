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

  TestOutputLibrary.h

Abstract:

  This file defines the EFI Test Output Library Protocol.

  This protocol will be invoked by the standard test library protocol, the test
  logging library protocol, or the other user-defined library protocols.
  Generally a test case should only invoke the standard test library protocol
  or the test logging library protocol to record the output message. It can not
  touch this test output library protocol directly.

--*/

#ifndef _EFI_TEST_OUTPUT_LIBRARY_H_
#define _EFI_TEST_OUTPUT_LIBRARY_H_

//
// Includes
//

#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)

//
// EFI Test Output Library Protocol Definitions
//

#define EFI_TEST_OUTPUT_LIBRARY_GUID        \
  { 0x8bfeab85, 0x83cf, 0x4c7b, {0x9e, 0xcd, 0xcf, 0x14, 0x28, 0x87, 0xe7, 0x12 }}

#define EFI_TEST_OUTPUT_LIBRARY_REVISION    0x00010000

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_TEST_OUTPUT_LIBRARY_PROTOCOL EFI_TEST_OUTPUT_LIBRARY_PROTOCOL;

//
// EFI Test Output Library Protocol API - Open
//
typedef
EFI_STATUS
(EFIAPI *EFI_TOL_OPEN) (
  IN  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          *This,
  IN  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN  CHAR16                                    *FileName,
  IN  BOOLEAN                                   Overwrite,
  OUT EFI_FILE                                  **FileHandle
  )
/*++

Routine Description:

  Open an output file.

Arguments:

  This          - Test output library protocol instance.

  DevicePath    - Device path of the output file.

  FileName      - File name of the output file.

  Overwrite     - Control write operations. TRUE stands for overwrite the old
                  file, FALSE for append it.

  FileHandle    - Handle for the opened file.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Output Library Protocol API - Close
//
typedef
EFI_STATUS
(EFIAPI *EFI_TOL_CLOSE) (
  IN  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          *This,
  IN  EFI_FILE                                  *FileHandle
  )
/*++

Routine Description:

  Close an output file.

Arguments:

  This          - Test output library protocol instance.

  FileHandle    - File handle to be closed.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Output Library Protocol API - Write
//
typedef
EFI_STATUS
(EFIAPI *EFI_TOL_WRITE) (
  IN  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          *This,
  IN  EFI_FILE                                  *FileHandle,
  IN  CHAR16                                    *String
  )
/*++

Routine Description:

  Write a string to the output file.

Arguments:

  This          - Test output library protocol instance.

  FileHandle    - Handle for the opened file.

  String        - Null terminated Unicode string to be written.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Output Library Protocol
//

struct _EFI_TEST_OUTPUT_LIBRARY_PROTOCOL {
  UINT64                                LibraryRevision;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TOL_OPEN                          Open;
  EFI_TOL_CLOSE                         Close;
  EFI_TOL_WRITE                         Write;
};

//
// Global ID for EFI Test Output Library Protocol
//

extern EFI_GUID gEfiTestOutputLibraryGuid;

#endif
