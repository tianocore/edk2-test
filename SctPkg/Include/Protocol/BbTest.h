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

  BbTest.h

Abstract:

  This file defines the EFI Black-Box Test Protocol.

--*/

#ifndef _EFI_BB_TEST_H_
#define _EFI_BB_TEST_H_

//
// Includes
//

//
// EFI Black-Box Test Protocol Definitions
//

#define EFI_BB_TEST_GUID                \
  { 0x8C41CE3E, 0xB255, 0x4966, {0xB5, 0x3C, 0x39, 0x76, 0x5A, 0xE1, 0x11, 0xD0 }}

#define EFI_BB_TEST_REVISION            0x00010000

#define EFI_IHV_BB_TEST_GUID           \
  { 0x27e36cde, 0xa7e7, 0x4a4a, {0x9b, 0x5f, 0xa3, 0x9a, 0x56, 0x75, 0xcb, 0x80 }}

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_BB_TEST_ENTRY EFI_BB_TEST_ENTRY;
typedef struct _EFI_BB_TEST_PROTOCOL EFI_BB_TEST_PROTOCOL;

//
// EFI Black-Box Test Entry Point
//

typedef
EFI_STATUS
(EFIAPI *EFI_BB_ENTRY_POINT) (
  IN  EFI_BB_TEST_PROTOCOL              *This,
  IN  VOID                              *ClientInterface,
  IN  EFI_TEST_LEVEL                    TestLevel,
  IN  EFI_HANDLE                        SupportHandle
  );

//
// EFI Black-Box Test Entry
//

struct _EFI_BB_TEST_ENTRY {
  EFI_BB_TEST_ENTRY                     *Next;
  EFI_GUID                              EntryId;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TEST_LEVEL                        TestLevelSupportMap;
  EFI_GUID                              *SupportProtocols;
  EFI_TEST_ATTRIBUTE                    CaseAttribute;
  EFI_BB_ENTRY_POINT                    EntryPoint;
};

//
// EFI Black-Box Test Protocol
//

struct _EFI_BB_TEST_PROTOCOL {
  UINT64                                TestRevision;
  EFI_GUID                              CategoryGuid;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_BB_TEST_ENTRY                     *EntryList;
};

//
// Global ID for EFI Black-Box Test Protocol
//

extern EFI_GUID gEfiBbTestGuid;
extern EFI_GUID gEfiIHVBbTestGuid;

#endif
