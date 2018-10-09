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

  TestProfile.h

Abstract:

  Driver to publish the Test Profile Library Protocol.

--*/

#ifndef _EFI_TEST_PROFILE_H_
#define _EFI_TEST_PROFILE_H_

//
// Includes
//

#include "LibPrivate.h"
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

//
// Private Data definition for TestProfileLibrary protocol
//
#define TEST_PROFILE_PRIVATE_DATA_SIGNATURE   EFI_SIGNATURE_32('A','D','V','L')

typedef struct {
  UINT32                                    Signature;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         TestProfile;
  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath;
  CHAR16                                    *FilePath;
} TEST_PROFILE_PRIVATE_DATA;

#define TEST_PROFILE_PRIVATE_DATA_FROM_THIS(a)  \
  CR(a, TEST_PROFILE_PRIVATE_DATA, TestProfile, TEST_PROFILE_PRIVATE_DATA_SIGNATURE)

//
// Private Data definition for EFI_INI_FILE interface
//
#define EFI_INI_FILE_PRIVATE_DATA_SIGNATURE   EFI_SIGNATURE_32('I','N','I','F')

#define MAX_STRING_LEN      100
#define MAX_LINE_LEN        512

//
// Forward reference for pure ANSI compatibility
//

typedef struct _INI INI;
typedef struct _COMMENTLINE COMMENTLINE;

struct _INI {
  UINT32                          commentNo;
  CHAR8                           ptrSection[MAX_STRING_LEN + 1];
  CHAR8                           ptrEntry[MAX_STRING_LEN + 1];
  CHAR8                           ptrValue[MAX_STRING_LEN + 1];
  INI                             *ptrNext;
};


struct _COMMENTLINE {
  UINT32                          commentNo;
  CHAR8                           ptrComment[MAX_LINE_LEN];
  COMMENTLINE                     *ptrNext;
};

typedef struct {
  UINT32                          Signature;
  EFI_INI_FILE                    Handle;
  EFI_DEVICE_PATH_PROTOCOL        *DevPath;
  CHAR16                          *FileName;
  INI                             *Head;
  INI                             *Tail;
  COMMENTLINE                     *CommentLineHead;
  BOOLEAN                         isUnicode;
  BOOLEAN                         Modified;
} EFI_INI_FILE_PRIVATE_DATA;

#define EFI_INI_FILE_PRIVATE_DATA_FROM_THIS(a)  \
  CR(a, EFI_INI_FILE_PRIVATE_DATA, Handle, EFI_INI_FILE_PRIVATE_DATA_SIGNATURE)

#endif
