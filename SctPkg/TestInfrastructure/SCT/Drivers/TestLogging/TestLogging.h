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

  TestLogging.h

Abstract:

  Driver to publish the Test Logging Library Protocol.

--*/

#ifndef _EFI_TEST_LOGGING_H_
#define _EFI_TEST_LOGGING_H_

//
// Includes
//

#include "LibPrivate.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

//
// Global definitions
//

#define EFI_MAX_PRINT_BUFFER                1024

//
// Private data structures
//

#define TEST_LOGGING_PRIVATE_DATA_SIGNATURE   EFI_SIGNATURE_32('T','L','L','P')

typedef struct {
  BOOLEAN                                   EnableScreenOutput;
  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath;
  CHAR16                                    *FileName;
  BOOLEAN                                   OverwriteFile;
  EFI_FILE_HANDLE                           FileHandle;
} EFI_LIB_CONFIG_FILE_HANDLE;

typedef struct {
  UINT32                                    Signature;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL         TestLogging;
  EFI_TLL_PRIVATE_INTERFACE                 PrivateInterface;
  EFI_TEST_OUTPUT_LIBRARY_PROTOCOL          *OutputProtocol;

  EFI_LIB_CONFIG_FILE_HANDLE                SystemLogFile;
  EFI_LIB_CONFIG_FILE_HANDLE                CaseLogFile;

  CHAR16                                    *BiosId;
  UINT32                                    PlatformNumber;
  UINT32                                    ConfigurationNumber;
  CHAR16                                    *ScenarioString;

  UINT64                                    TestRevision;
  CHAR16                                    *TestName;
  EFI_GUID                                  EntryId;
  CHAR16                                    *EntryName;
  CHAR16                                    *EntryDescription;
  EFI_GUID                                  *SupportProtocols;
  EFI_VERBOSE_LEVEL                         VerboseLevel;

  BOOLEAN                                   BeginLogging;
} TEST_LOGGING_PRIVATE_DATA;

#define TEST_LOGGING_PRIVATE_DATA_FROM_TLL(a) \
  CR(a, TEST_LOGGING_PRIVATE_DATA, TestLogging, TEST_LOGGING_PRIVATE_DATA_SIGNATURE)

#define TEST_LOGGING_PRIVATE_DATA_FROM_PI(a)  \
  CR(a, TEST_LOGGING_PRIVATE_DATA, PrivateInterface, TEST_LOGGING_PRIVATE_DATA_SIGNATURE)

#endif