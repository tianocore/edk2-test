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

  VariableENTSTestCase.h

Abstract:

--*/

#ifndef _VARIABLE_ENTS_TESTCASE_H_
#define _VARIABLE_ENTS_TESTCASE_H_

#include "SctLib.h"
#include "Eas.h"

EFI_STATUS
EFIAPI
RT_GetVariable_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  RT GetVariable Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
RT_GetNextVariableName_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  GetNextVariableName Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
RT_SetVariable_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SetVariable Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gRuntimeServiceRuntimeInfo;
extern UINTN          gRuntimeServiceRuntimeInfoSize;

extern ENTS_ARG_FIELD tRTGetVariableArgField[];
extern ENTS_ARG_FIELD tRTGetNextVariableNameArgField[];
extern ENTS_ARG_FIELD tRTSetVariableArgField[];

#endif
