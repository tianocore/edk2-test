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
  GenericServiceENTSTestCase.h

Abstract:

--*/

#ifndef _GENERIC_SERVICE_ENTS_TESTCASE_H_
#define _GENERIC_SERVICE_ENTS_TESTCASE_H_

#include "SctLib.h"
#include "Eas.h"

EFI_STATUS
EFIAPI
GS_MemCmp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  MemCmp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gGenericServiceRuntimeInfo;
extern UINTN          gGenericServiceRuntimeInfoSize;

extern ENTS_ARG_FIELD gGSMemCmpArgField[];

#endif
