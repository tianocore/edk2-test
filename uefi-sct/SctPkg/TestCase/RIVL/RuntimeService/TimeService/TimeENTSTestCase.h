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

  TimeENTSTestCase.h

Abstract:

--*/

#ifndef _TIME_ENTS_TESTCASE_H_
#define _TIME_ENTS_TESTCASE_H_

#include "SctLib.h"
#include "Eas.h"

EFI_STATUS
EFIAPI
RT_GetTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  GetTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
RT_SetTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SetTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
RT_GetWakeupTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  GetWakeupTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
RT_SetWakeupTime_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SetWakeupTime Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gRuntimeServiceRuntimeInfo;
extern UINTN          gRuntimeServiceRuntimeInfoSize;

extern ENTS_ARG_FIELD tRTGetTimeArgField[];
extern ENTS_ARG_FIELD tRTSetTimeArgField[];
extern ENTS_ARG_FIELD tRTGetWakeupTimeArgField[];
extern ENTS_ARG_FIELD tRTSetWakeupTimeArgField[];

#endif
