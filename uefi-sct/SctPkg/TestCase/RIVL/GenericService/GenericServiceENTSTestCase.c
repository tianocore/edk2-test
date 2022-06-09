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
  GenericServiceENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "GenericServiceENTSTestCase.h"

//
// MemCmp
//
static VOID     *GSMemCmpMemOne;
static VOID     *GSMemCmpMemTwo;
static UINTN    GSMemCmpLength;
static INTN     *GSMemCmpResult;

ENTS_ARG_FIELD  gGSMemCmpArgField[] = {
  {
    POINTER,
    &GSMemCmpMemOne
  },
  {
    POINTER,
    &GSMemCmpMemTwo
  },
  {
    OCTETN,
    &GSMemCmpLength
  },
  {
    POINTER,
    &GSMemCmpResult
  },
  0
};

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
{
  *GSMemCmpResult = 0;

  for (; GSMemCmpLength > 0; GSMemCmpLength--) {
    *GSMemCmpResult = (INTN) (*(INT8 *) GSMemCmpMemOne -*(INT8 *) GSMemCmpMemTwo);
    if (*GSMemCmpResult != 0) {
      return EFI_SUCCESS;
    }

    GSMemCmpMemOne  = (VOID *) ((UINTN) GSMemCmpMemOne + 1);
    GSMemCmpMemTwo  = (VOID *) ((UINTN) GSMemCmpMemTwo + 1);
  }

  return EFI_SUCCESS;
}
