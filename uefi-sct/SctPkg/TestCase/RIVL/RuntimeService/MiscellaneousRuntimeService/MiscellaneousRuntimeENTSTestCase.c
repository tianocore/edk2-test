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

  MiscellaneousRuntimeENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "MiscellaneousRuntimeENTSTestCase.h"

//
// RT.ResetSystem
//
static EFI_RESET_TYPE RTResetSystemResetType;
static EFI_STATUS     RTResetSystemResetStatus;
static UINTN          RTResetSystemDataSize;
static CHAR16         *RTResetSystemResetData;

ENTS_ARG_FIELD        tRTResetSystemArgField[] = {
  {
    OCTETN,
    &RTResetSystemResetType
  },
  {
    OCTETN,
    &RTResetSystemResetStatus
  },
  {
    OCTETN,
    &RTResetSystemDataSize
  },
  {
    POINTER,
    &RTResetSystemResetData
  },
  0
};

EFI_STATUS
EFIAPI
RT_ResetSystem_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  ResetSystem Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  RuntimeService->ResetSystem (
                    RTResetSystemResetType,
                    RTResetSystemResetStatus,
                    RTResetSystemDataSize,
                    RTResetSystemResetData
                    );
  return EFI_SUCCESS;
}
