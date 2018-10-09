/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ApTest.h

Abstract:

  This file defines a protocol interface for Application Test.

--*/

#ifndef _EFI_AP_TEST_H_
#define _EFI_AP_TEST_H_

//
// Includes
//

//
// EFI Application Test Interface definitions
//

#define EFI_AP_TEST_REVISION            0x00010000

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_AP_TEST_ENTRY EFI_AP_TEST_ENTRY;

//
// EFI Application Test Entry Point
//

struct _EFI_AP_TEST_ENTRY {
  EFI_AP_TEST_ENTRY     *Next;
  EFI_GUID              EntryId;
  CHAR16                *Name;
  CHAR16                *Description;
  UINT32                TestLevelSupportMap;
  EFI_GUID              *SupportProtocols;
  UINT32                CaseAttribute;
  CHAR16                *Parameters;
};

//
// EFI Application Test Interface
//

typedef struct {
  UINT64                TestRevision;
  EFI_GUID              CategoryGuid;
  CHAR16                *Name;
  CHAR16                *Description;
  EFI_AP_TEST_ENTRY     *EntryList;
} EFI_AP_TEST_INTERFACE;

#endif
