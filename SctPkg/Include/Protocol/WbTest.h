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

  WbTest.h

Abstract:

  This file defines the EFI White-Box Test Protocol.

--*/

#ifndef _EFI_WB_TEST_H_
#define _EFI_WB_TEST_H_

//
// Includes
//

//
// EFI White-Box Test Protocol Definitions
//

#define EFI_WB_TEST_GUID                \
  { 0x0B486CED, 0x25EB, 0x448a, {0xB2, 0xB2, 0x22, 0x4E, 0x7A, 0x20, 0xCF, 0x57 }}
 
#define EFI_WB_TEST_REVISION            0x00010000

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_WB_TEST_ENTRY EFI_WB_TEST_ENTRY;
typedef struct _EFI_WB_TEST_PROTOCOL EFI_WB_TEST_PROTOCOL;

//
// EFI White-Box Test Entry Point
//

typedef
EFI_STATUS
(EFIAPI *EFI_WB_ENTRY_POINT) (
  IN  EFI_WB_TEST_PROTOCOL              *This,
  IN  EFI_TEST_LEVEL                    TestLevel,
  IN  EFI_HANDLE                        SupportHandle
  );

//
// EFI White-Box Test Entry
//

struct _EFI_WB_TEST_ENTRY {
  EFI_WB_TEST_ENTRY                     *Next;
  EFI_GUID                              EntryId;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TEST_LEVEL                        TestLevelSupportMap;
  EFI_GUID                              *SupportProtocols;
  EFI_TEST_ATTRIBUTE                    CaseAttribute;
  EFI_WB_ENTRY_POINT                    EntryPoint;
} ;

//
// EFI White-Box Test Protocol
//

struct _EFI_WB_TEST_PROTOCOL {
  UINT64                                TestRevision;
  EFI_GUID                              CategoryGuid;
  EFI_HANDLE                            ClientHandle;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_WB_TEST_ENTRY                     *EntryList;
};

//
// Global ID for EFI White-Box Test Protocol
//

extern EFI_GUID gEfiWbTestGuid;

#endif
