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

  Mtftp6ENTSTestCase.h

Abstract:

--*/

#ifndef _MTFTP6_ENTS_TESTCASE_H_
#define _MTFTP6_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION(EntsProtocol)
#include "Eas.h"
#include <Library/EntsLib.h>
#include <UEFI/Protocol/Mtftp6.h>

EFI_STATUS
EFIAPI
Mtftp6GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp6Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp6GetInfo_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6 GetInfo Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp6ParseOptions_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6 ParseOptions Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp6ReadFile_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6 ReadFile Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp6WriteFile_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6 WriteFile Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp6ReadDirectory_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6 ReadDirectory Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp6Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp6 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gMtftp6EntsRuntimeInfo;
extern UINTN          gMtftp6EntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gMtftp6GetModeDataArgField[];
extern ENTS_ARG_FIELD gMtftp6ConfigureArgField[];
extern ENTS_ARG_FIELD gMtftp6GetInfoArgField[];
extern ENTS_ARG_FIELD gMtftp6ParseOptionsArgField[];
extern ENTS_ARG_FIELD gMtftp6ReadFileArgField[];
extern ENTS_ARG_FIELD gMtftp6WriteFileArgField[];
extern ENTS_ARG_FIELD gMtftp6ReadDirectoryArgField[];
extern ENTS_ARG_FIELD gMtftp6PollArgField[];

#endif // _MTFTP6_ENTS_TESTCASE_H_
