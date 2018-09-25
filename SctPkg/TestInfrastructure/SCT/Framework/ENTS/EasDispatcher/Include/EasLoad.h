/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EasLoad.h

Abstract:

  ENTS extended data services declarations.

--*/

#ifndef _EFI_LOAD_H_
#define _EFI_LOAD_H_

//
// External functions declarations
//
EFI_STATUS
EntsLoadSupportFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN BOOLEAN                      Recursive
  )
/*++

Routine Description:

  Load all support files.

Arguments:

  DevicePath  - Device path of the test files.
  FilePath    - Path of the test files.
  Recursive   - Resursively.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
EntsUnloadSupportFiles (
  IN SCT_LIST_ENTRY               *TestAppList
  )
/*++

Routine Description:

  Unload all support files.

Arguments:

  TestAppList - Pointer to the test file list.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
EntsLoadTestFiles (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath,
  IN BOOLEAN                      Recursive
  )
/*++

Routine Description:

  Load all application files.

Arguments:

  DevicePath  - Device path of the test files.
  FilePath    - Path of the test files.
  Recursive   - Resursively.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Invalid parameter.
  Others                - Operation failed.

--*/
;

EFI_STATUS
EntsUnloadTestFiles (
  IN SCT_LIST_ENTRY               *TestAppList
  )
/*++

Routine Description:

  Unload all test files.

Arguments:

  TestAppList - Pointer to the test file list.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Operation failed.

--*/
;

EFI_STATUS
EntsFindTestFileByName (
  IN CHAR16                       *CmdName,
  IN OUT EFI_NETWORK_TEST_FILE    **TestFile
  )
/*++

Routine Description:

  Find a test file by a name.

Arguments:

  CmdName   - Command name.
  TestFile  - Pointer to the testFile structure.
  
Returns:

  EFI_SUCCESS - Operation succeeded.
  Others - Operation failed.

--*/
;

#endif
