/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  (C) Copyright 2016 Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

/*++

Module Name:

  RegularExpressionProtocol.h

Abstract:

  EFI Regular Expression Protocol

--*/

#ifndef _REGEX_PROTOCOL_H_
#define _REGEX_PROTOCOL_H_

//
// Global ID for the Regular Expression Protocol
//
#define EFI_REGULAR_EXPRESSION_PROTOCOL_GUID    \
  { 0xB3F79D9A, 0x436C, 0xDC11, {0xB0, 0x52, 0xCD, 0x85,0xDF, 0x52, 0x4C, 0xE6 }}


typedef struct _EFI_REGULAR_EXPRESSION_PROTOCOL EFI_REGULAR_EXPRESSION_PROTOCOL;;

typedef EFI_GUID EFI_REGEX_SYNTAX_TYPE;

typedef struct {
 CONST CHAR16 *CapturePtr;
 UINTN Length;
} EFI_REGEX_CAPTURE;

typedef
EFI_STATUS
(EFIAPI *EFI_REGULAR_EXPRESSION_GET_INFO) (
  IN     EFI_REGULAR_EXPRESSION_PROTOCOL *This,
  IN OUT UINTN                           *RegExSyntaxTypeListSize,
  OUT    EFI_REGEX_SYNTAX_TYPE           *RegExSyntaxTypeList
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REGULAR_EXPRESSION_MATCH) (
  IN  EFI_REGULAR_EXPRESSION_PROTOCOL *This,
  IN  CHAR16                          *String,
  IN  CHAR16                          *Pattern,
  IN  EFI_REGEX_SYNTAX_TYPE           *RegExSyntaxTypeList, OPTIONAL
  OUT BOOLEAN                         *Result,
  OUT EFI_REGEX_CAPTURE               **Captures, OPTIONAL
  OUT UINTN                           *CapturesCount
  );

//
// Interface structure for the Regular Expression Protocol
//
struct _EFI_REGULAR_EXPRESSION_PROTOCOL {
  EFI_REGULAR_EXPRESSION_MATCH     MatchString;
  EFI_REGULAR_EXPRESSION_GET_INFO  GetInfo;
} ;

extern EFI_GUID gBlackBoxEfiRegularExpressionProtocolGuid;

#endif
