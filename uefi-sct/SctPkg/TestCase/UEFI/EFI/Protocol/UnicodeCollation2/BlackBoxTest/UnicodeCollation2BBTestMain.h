/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  UnicodeCollationBBTestMain.h

Abstract:

  BB test header file of Unicode Collation Protocol

--*/


#ifndef _UNICODE_COLLATION2_BBTEST_H_
#define _UNICODE_COLLATION2_BBTEST_H_


#include "Efi.h"
#include "Guid.h"
#include <UEFI/Protocol/UnicodeCollation2.h>
#include <Library/EfiTestLib.h>

#define  UNICODE_COLLATION2_PROTOCOL_TEST_REVISION    0x00010000

#define  MAX_SIZE_OF_STRING                          255
#define  MAX_SIZE_OF_STRESS_STRING                   65535

extern   CHAR8                                       EngUpperMap[0x100];
extern   CHAR8                                       EngLowerMap[0x100];
extern   CHAR8                                       EngInfoMap[0x100];
extern   CHAR8                                       OtherChars[];


#define CHAR_FAT_VALID                               0x01

#define ToUpper(a)  (CHAR16)(a <= 0xFF ? EngUpperMap[a] : a)
#define ToLower(a)  (CHAR16)(a <= 0xFF ? EngLowerMap[a] : a)



typedef struct {
  CHAR16             *S1;
  CHAR16             *S2;
  INTN               Result;
} STRICOLL_TEST_DATA_FIELD;

#define  STRING_COMPARE_EQUAL     0
#define  STRING_COMPARE_LESS      -1
#define  STRING_COMPARE_MORE      1

typedef struct {
  CHAR16             *Pattern;
  CHAR16             *String;
  BOOLEAN            Result;
} METAIMATCH_TEST_DATA_FIELD;

EFI_STATUS
EFIAPI
InitializeBBTestUnicodeCollation (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestUnicodeCollationProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
EFIAPI
BBTestStriCollFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestMetaiMatchFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestStrLwrFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestStrUprFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestFatToStrFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestStrToFatFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

VOID
CopyUnicodeString (
  IN CHAR16                     *Destination,
  IN CHAR16                     *Source
  );

BOOLEAN
CheckStrLwr (
  IN CHAR16                     *Original,
  IN CHAR16                     *Result
  );

BOOLEAN
CheckStrUpr (
  IN CHAR16                     *Original,
  IN CHAR16                     *Result
  );

BOOLEAN
CheckStrEql (
  IN CHAR16                     *s1,
  IN CHAR16                     *s2
  );

UINTN
GetStrLen8(
  IN CHAR8                      *s
  );

UINTN
GetStrLen16(
  IN CHAR16                     *s
  );

BOOLEAN
CheckFatToStr (
  IN CHAR8                      *Fat,
  IN UINTN                      FatSize,
  IN CHAR16                     *Result
  );

BOOLEAN
CheckStrToFat (
  IN CHAR16                     *Source,
  IN UINTN                      FatSize,
  IN CHAR8                      *Fat,
  IN BOOLEAN                    IsLongFileName
  );

VOID
InitCharMapping();

BOOLEAN
CheckLongFileName(
  IN CHAR16                     *Source,
  IN UINTN                      FatSize
  ) ;

//
// Entry GUIDs
//

#define UNICODE_COLLATION2_PROTOCOL_STRICOLL_FUNCTION_AUTO_GUID \
  { 0xdad20219, 0x422f, 0x43da, { 0xa1, 0xfa, 0x85, 0xcb, 0xe2, 0xed, 0xd9, 0xc9 } }

#define UNICODE_COLLATION2_PROTOCOL_METAIMATCH_FUNCTION_AUTO_GUID \
  { 0x9e918792, 0x90da, 0x47b2, { 0xa6, 0x02, 0xa3, 0xfe, 0x79, 0x11, 0xa2, 0x7f } }

#define UNICODE_COLLATION2_PROTOCOL_STRLWR_FUNCTION_AUTO_GUID \
  { 0x81cd6598, 0x8530, 0x4765, { 0x86, 0x6c, 0xcd, 0x67, 0x49, 0x04, 0x64, 0x2a } }

#define UNICODE_COLLATION2_PROTOCOL_STRUPR_FUNCTION_AUTO_GUID \
  { 0x5a3a67b4, 0x812d, 0x4b1b, { 0xb3, 0x03, 0x3c, 0x3a, 0xc8, 0x7b, 0x97, 0x18 } }

#define UNICODE_COLLATION2_PROTOCOL_FATTOSTR_FUNCTION_AUTO_GUID \
  { 0x74a6e2ff, 0x9629, 0x4914, { 0xa0, 0x71, 0xc1, 0xbb, 0x1a, 0xdc, 0x86, 0x93 } }

#define UNICODE_COLLATION2_PROTOCOL_STRTOFAT_FUNCTION_AUTO_GUID \
  { 0x089376cc, 0x6530, 0x4653, { 0x80, 0x52, 0x60, 0x6b, 0x8d, 0x5f, 0x56, 0x4f } }

#define UNICODE_COLLATION2_PROTOCOL_STRESS_AUTO_GUID \
  { 0x7b8b1cb5, 0xa3b9, 0x410d, { 0x96, 0xf0, 0x3d, 0x88, 0x96, 0xe9, 0x03, 0x9a } }

#endif

