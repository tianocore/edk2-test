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

  MiscellaneousBootENTSTestCase.h

Abstract:

--*/

#ifndef _MISCELLANEOUS_BOOT_ENTS_TESTCASE_H_
#define _MISCELLANEOUS_BOOT_ENTS_TESTCASE_H_

#include "SctLib.h"
#include "Eas.h"

EFI_STATUS
EFIAPI
BS_SetWatchdogTimer_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 SetWatchdogTimer Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
BS_Stall_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 Stall Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
BS_CopyMem_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 CopyMem Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EFIAPI
BS_SetMem_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

 SetMem Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gRuntimeServiceRuntimeInfo;
extern UINTN          gRuntimeServiceRuntimeInfoSize;

extern ENTS_ARG_FIELD BSSetWatchdogTimerArgField[];
extern ENTS_ARG_FIELD BSStallArgField[];
extern ENTS_ARG_FIELD BSCopyMemArgField[];
extern ENTS_ARG_FIELD BSSetMemArgField[];

#endif
