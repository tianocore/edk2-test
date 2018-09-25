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

  LibConfig.h

Abstract:

  This file defines the configuration data structures for the test support
  libraries.

--*/

#ifndef _EFI_LIB_CONFIG_H_
#define _EFI_LIB_CONFIG_H_

//
// Includes
//
#include EFI_TEST_PROTOCOL_DEFINITION(StandardTestLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestOutputLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TslInit)

//
// Type definitions
//

//
// Structure for one output file's configuration
//
typedef struct {
  BOOLEAN                             EnableScreenOutput;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  CHAR16                              *FileName;
  BOOLEAN                             OverwriteFile;
} EFI_LIB_CONFIG_FILE_DATA;

//
// Structure for all logging configuration
//
typedef struct {
  //
  // Test Output Library Protocol
  //
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL    *OutputProtocol;

  //
  // Log files' configuration
  //
  EFI_LIB_CONFIG_FILE_DATA            SystemLogFile;
  EFI_LIB_CONFIG_FILE_DATA            SystemKeyFile;
  EFI_LIB_CONFIG_FILE_DATA            CaseLogFile;
  EFI_LIB_CONFIG_FILE_DATA            CaseKeyFile;

  //
  // Test platform's configuration
  //
  CHAR16                              *BiosId;
  UINT32                              PlatformNumber;
  UINT32                              ConfigurationNumber;
  CHAR16                              *ScenarioString;

  //
  // Test case's configuration
  //
  UINT64                              TestRevision;
  CHAR16                              *TestName;
  EFI_GUID                            *EntryId;
  CHAR16                              *EntryName;
  CHAR16                              *EntryDescription;
  EFI_GUID                            *SupportProtocols;

  //
  // Test output level
  //
  EFI_VERBOSE_LEVEL                   VerboseLevel;

  //
  // Test status
  //
  BOOLEAN                             IsRecovery;
  UINT32                              PassCount;
  UINT32                              WarningCount;
  UINT32                              FailCount;

  //
  // Additional info to be recorded in the log files
  //
  CHAR16                              *TestCategory;
  CHAR16                              *DevicePath;
} EFI_LIB_CONFIG_DATA;

#endif
