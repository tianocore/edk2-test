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

  UnicodeCollation2Protocol.h

Abstract:

  Unicode Collation2 Protocol (define according to the EFI Spec 2.1 )

--*/

#ifndef _EFI_UNICODE_COLLATION2_FOR_TEST_H_
#define _EFI_UNICODE_COLLATION2_FOR_TEST_H_

#define EFI_UNICODE_COLLATION2_PROTOCOL_GUID \
  { 0xa4c751fc, 0x23ae, 0x4c3e, {0x92, 0xe9, 0x49, 0x64, 0xcf, 0x63, 0xf3, 0x49 }}


typedef struct _EFI_UNICODE_COLLATION2_PROTOCOL EFI_UNICODE_COLLATION2_PROTOCOL;;


typedef
INTN
(EFIAPI *EFI_UNICODE_COLLATION_STRICOLL) (
  IN EFI_UNICODE_COLLATION2_PROTOCOL   *This,
  IN CHAR16                           *s1,
  IN CHAR16                           *s2
  );

typedef
BOOLEAN
(EFIAPI *EFI_UNICODE_COLLATION_METAIMATCH) (
  IN EFI_UNICODE_COLLATION2_PROTOCOL   *This,
  IN CHAR16                           *String,
  IN CHAR16                           *Pattern
  );

typedef
VOID
(EFIAPI *EFI_UNICODE_COLLATION_STRLWR) (
  IN EFI_UNICODE_COLLATION2_PROTOCOL   *This,
  IN OUT CHAR16                       *String
  );

typedef
VOID
(EFIAPI *EFI_UNICODE_COLLATION_STRUPR) (
  IN EFI_UNICODE_COLLATION2_PROTOCOL   *This,
  IN OUT CHAR16                       *String
  );

typedef
VOID
(EFIAPI *EFI_UNICODE_COLLATION_FATTOSTR) (
  IN EFI_UNICODE_COLLATION2_PROTOCOL   *This,
  IN UINTN                            FatSize,
  IN CHAR8                            *Fat,
  OUT CHAR16                          *String
  );

typedef
BOOLEAN
(EFIAPI *EFI_UNICODE_COLLATION_STRTOFAT) (
  IN EFI_UNICODE_COLLATION2_PROTOCOL   *This,
  IN CHAR16                           *String,
  IN UINTN                            FatSize,
  OUT CHAR8                           *Fat
  );

struct _EFI_UNICODE_COLLATION2_PROTOCOL {
  EFI_UNICODE_COLLATION_STRICOLL          StriColl;
  EFI_UNICODE_COLLATION_METAIMATCH        MetaiMatch;
  EFI_UNICODE_COLLATION_STRLWR            StrLwr;
  EFI_UNICODE_COLLATION_STRUPR            StrUpr;
  EFI_UNICODE_COLLATION_FATTOSTR          FatToStr;
  EFI_UNICODE_COLLATION_STRTOFAT          StrToFat;
  CHAR8                                   *SupportedLanguages;
};

extern EFI_GUID                           gBlackBoxEfiUnicodeCollation2ProtocolGuid;

#endif
