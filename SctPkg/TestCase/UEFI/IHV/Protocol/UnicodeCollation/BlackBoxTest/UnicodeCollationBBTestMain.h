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

  UnicodeCollationBBTestMain.h

Abstract:

  BB test header file of Unicode Collation Protocol

--*/


#ifndef _UNICODE_COLLATION_BBTEST_H_
#define _UNICODE_COLLATION_BBTEST_H_


#include "Efi.h"
#include "Guid.h"
#include <UEFI/Protocol/UnicodeCollation.h>
#include <Library/EfiTestLib.h>

#define  UNICODE_COLLATION_PROTOCOL_TEST_REVISION    0x00010000

#define  IHV_UNICODE_COLLATION_PROTOCOL_GUID         \
  { 0xc26b6274, 0x90cb, 0x45f9, { 0x93, 0xac, 0xb8, 0x16, 0x93, 0xab, 0xd0, 0x5b } }

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
InitializeBBTestUnicodeCollation (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestUnicodeCollationProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
BBTestStriCollFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestMetaiMatchFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestStrLwrFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestStrUprFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFatToStrFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestStrToFatFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
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

#define UNICODE_COLLATION_PROTOCOL_STRICOLL_FUNCTION_AUTO_GUID \
  { 0x62be0688, 0x3ec4, 0x41e3, { 0x9d, 0x78, 0xa8, 0xf7, 0xaa, 0x11, 0xa7, 0x3a } }

#define UNICODE_COLLATION_PROTOCOL_METAIMATCH_FUNCTION_AUTO_GUID \
  { 0x5ef6dd78, 0x6ede, 0x42f4, { 0xa5, 0x68, 0xbb, 0x44, 0xfe, 0xcf, 0x47, 0x99 } }

#define UNICODE_COLLATION_PROTOCOL_STRLWR_FUNCTION_AUTO_GUID \
  { 0x1fc4b451, 0xad82, 0x4861, { 0x88, 0xed, 0x7a, 0x7d, 0xb3, 0x27, 0xd2, 0xf6 } }

#define UNICODE_COLLATION_PROTOCOL_STRUPR_FUNCTION_AUTO_GUID \
  { 0x85fbc62c, 0x2aeb, 0x45e9, { 0xa7, 0x1, 0xbc, 0xba, 0x69, 0x55, 0xd2, 0x16 } }

#define UNICODE_COLLATION_PROTOCOL_FATTOSTR_FUNCTION_AUTO_GUID \
  { 0xb4f11d20, 0x7a0a, 0x42a0, { 0xb8, 0x53, 0xe9, 0xb7, 0xbf, 0x2e, 0x57, 0x8e } }

#define UNICODE_COLLATION_PROTOCOL_STRTOFAT_FUNCTION_AUTO_GUID \
  { 0xe5992185, 0xf29c, 0x497b, { 0x82, 0xdb, 0xff, 0xe5, 0xaf, 0xf3, 0x95, 0x11 } }

#define UNICODE_COLLATION_PROTOCOL_STRESS_AUTO_GUID \
  { 0x7c627cbe, 0x7c9e, 0x4634, { 0x8e, 0x3, 0x2, 0x10, 0x5e, 0x76, 0x24, 0x25 } }

#endif

