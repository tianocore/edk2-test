/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  (C) Copyright 2016 - 2017 Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    RegularExpressionBBTest.h

Abstract:
    head file of test driver of EFI REGULAR EXPRESSION Protocol Test

--*/

#ifndef _REGULAR_EXPRESSION_TEST_H
#define _REGULAR_EXPRESSION_TEST_H


#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/RegularExpression.h>
#include "Guid.h"

#define EFI_REGULAR_EXPRESSION_TEST_REVISION 0x00010000

extern EFI_HANDLE   mImageHandle;

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Function Test
//
#define EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0x9531a0ea, 0x7955, 0x4cc1, {0xb1, 0x12, 0xb8, 0x95, 0xd9, 0xd3, 0xb, 0x86} }

#define EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0x7ef858ab, 0x54a8, 0x481d, {0x95, 0x9d, 0xc4, 0x5, 0xb5, 0xd7, 0x20, 0x87} }

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0201 \
 {0xdf61e05b, 0x25b4, 0x4e05, {0xa5, 0x16, 0x8d, 0xa3, 0x6a, 0xae, 0xce, 0xa9} }

#define EFI_REGULAR_EXPRESSION_PROTOCOL_TEST_ENTRY_GUID0202 \
 {0x6f7ecf1, 0x6b72, 0x4816, {0x8f, 0x67, 0xf7, 0x42, 0x1e, 0x73, 0x3e, 0xb0} }

 
typedef struct {
  CHAR16             *Pattern;
  CHAR16             *String;
  BOOLEAN            Result;
  UINTN              CapturesCount;
} MATCHSTRING_TEST_DATA_FIELD;

//
// functions declaration
//
EFI_STATUS
EFIAPI
InitializeBBTestRegularExpression (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestRegularExpressionUnload (
  IN EFI_HANDLE       ImageHandle
  );


EFI_STATUS
EFIAPI
BBTestRegExGetInfoFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestMatchStringFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestRegExGetInfoFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
EFIAPI
BBTestMatchStringFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
EFIAPI
BBTestMatchStringFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
EFIAPI
BBTestGetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestMatchStringConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


EFI_STATUS
EFIAPI
BBTestGetInfoConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
EFIAPI
BBTestMatchStringConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


EFI_STATUS
EFIAPI
BBTestMatchStringConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_REGULAR_EXPRESSION_PROTOCOL       *RegularExpression
  );


#endif
