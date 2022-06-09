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

  Mtftp4ENTSTestCase.h

Abstract:

--*/

#ifndef _MTFTP4_ENTS_TESTCASE_H_
#define _MTFTP4_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"
#include <UEFI/Protocol/Mtftp4.h>

EFI_STATUS
EFIAPI
Mtftp4GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp4Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp4GetInfo_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 GetInfo Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp4ParseOptions_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 ParseOptions Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp4ReadFile_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 ReadFile Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp4WriteFile_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 WriteFile Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp4ReadDirectory_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 ReadDirectory Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
Mtftp4Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gMtftp4EntsRuntimeInfo;
extern UINTN          gMtftp4EntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gMtftp4GetModeDataArgField[];
extern ENTS_ARG_FIELD gMtftp4ConfigureArgField[];
extern ENTS_ARG_FIELD gMtftp4GetInfoArgField[];
extern ENTS_ARG_FIELD gMtftp4ParseOptionsArgField[];
extern ENTS_ARG_FIELD gMtftp4ReadFileArgField[];
extern ENTS_ARG_FIELD gMtftp4WriteFileArgField[];
extern ENTS_ARG_FIELD gMtftp4ReadDirectoryArgField[];
extern ENTS_ARG_FIELD gMtftp4PollArgField[];

#endif // _MTFTP4_ENTS_TESTCASE_H_
