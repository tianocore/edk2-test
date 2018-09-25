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

  EasType.h

Abstract:

  ENTS Typ edefinitions.

--*/
#ifndef _EAS_TYPE_H_
#define _EAS_TYPE_H_

//
// EFI_NETWORK_TEST_FILE
//
#define EFI_NETWORK_TEST_FILE_SIGNATURE   EFI_SIGNATURE_32 ('n', 't', 'f', 'l')
#define EFI_NETWORK_TEST_FILE_VERSION     0x10

#define EFI_NETWORK_TEST_FILE_UNKNOWN     0x00
#define EFI_NETWORK_TEST_FILE_DRIVER      0x01
#define EFI_NETWORK_TEST_FILE_APPLICATION 0x02
#define EFI_NETWORK_TEST_FILE_SCRIPT      0x03
#define EFI_NETWORK_TEST_FILE_PY_SCRIPT   0x04
#define EFI_NETWORK_TEST_FILE_SUPPORT     0x05

typedef struct _EFI_NETWORK_TEST_FILE {
  UINT32                    Signature;
  UINTN                     Version;

  SCT_LIST_ENTRY            Link;

  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  CHAR16                    *FileName;
  CHAR16                    *CmdName;
  EFI_HANDLE                ImageHandle;

  UINTN                     Type;
  VOID                      *Context;
} EFI_NETWORK_TEST_FILE;

//
// ENTS_MONITOR_COMMAND
//
typedef enum {
  ELET_CMD          = 1,
  RIVL_DEFTYPE,
  RIVL_CRTVAR,
  RIVL_SETVAR,
  RIVL_GETVAR,
  RIVL_DELTYPE,
  RIVL_DELVAR,
  ABORT,
  EXECUTE,
  RUNTIME_INFO_REQ,
  RUNTIME_INFO_CLEAR,
  GET_FILE,
  PUT_FILE,
} ENTS_CMD_TYPE;

typedef enum _ENTS_CMD_RESULT
{
  PASS,
  FAIL,
} ENTS_CMD_RESULT;

#define EFI_MONITOR_COMMAND_SIGNATURE EFI_SIGNATURE_32 ('n', 's', 'c', 'd')
#define EFI_MONITOR_COMMAND_VERSION   0x10

typedef struct _EFI_MONITOR_COMMAND {
  UINT32                Signature;
  UINTN                 Version;

  CHAR16                *ComdName;
  CHAR16                *ComdArg;

  CHAR16                *ComdRuntimeInfo;
  UINTN                 ComdRuntimeInfoSize;

  CHAR16                *ComdOutput;
  UINTN                 ComdOutputSize;

  ENTS_CMD_RESULT       ComdResult;
  ENTS_CMD_TYPE         CmdType;

  EFI_NETWORK_TEST_FILE *TestFile;
  CHAR16                *ComdInterface;
} EFI_MONITOR_COMMAND;

//
// EFI_SCT_FRAMEWORK_TABLE
//
#define EFI_NETWORK_TEST_FRAMEWORK_TABLE_SIGNATURE  EFI_SIGNATURE_32 ('n', 'f', 'w', 't')
#define EFI_NETWORK_TEST_FRAMEWORK_TABLE_VERSION    0x10

typedef struct _EFI_NETWORK_TEST_FRAMEWORK_TABLE {
  UINT32                    Signature;
  UINTN                     Version;

  //
  // Image data
  //
  EFI_HANDLE                ImageHandle;
  EFI_SYSTEM_TABLE          *SystemTable;

  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  CHAR16                    *FilePath;

  //
  // Test data
  //
  SCT_LIST_ENTRY            TestAppList;

  //
  // Test support list
  //
  SCT_LIST_ENTRY            SupportList;

  //
  // Test support data
  //
  VOID                      *Monitor;
  EFI_MONITOR_COMMAND       *Cmd;
} EFI_NETWORK_TEST_FRAMEWORK_TABLE;

//
// Data type
//
#define OCTET1  0x11
#define OCTET2  0x12
#define OCTET4  0x13
#define OCTET8  0x14
#define OCTETN  0x15
#define BOOL    0x16
#define POINTER 0x17

#endif
