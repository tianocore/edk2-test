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

  libsalpal.h

Abstract:

  Function prototype definitions.

--*/

#ifndef _EFI_LIB_SAL_PAL_H_
#define _EFI_LIB_SAL_PAL_H_

#include "PalApi.h"
#include "SalApi.h"

typedef
PAL_RETURN_REGS
(EFIAPI *PAL_PROC) (
  IN  UINT64                      FunctionId,
  IN  UINT64                      Arg2,
  IN  UINT64                      Arg3,
  IN  UINT64                      Arg4
  );

EFI_STATUS
LibInitSalAndPalProc (
  VOID
    );

EFI_STATUS
LibGetSalVersionInfo (
  IN  OUT   UINT16  *SalSpecRev,
  IN  OUT   UINT16  *SalARev,
  IN  OUT   UINT16  *SalBRev
);

EFI_STATUS
LibGetSalIoPortMapping (
    OUT UINT64  *IoPortMapping
    );


EFI_STATUS
LibGetSalIpiBlock (
    OUT UINT64  *IpiBlock
    );

EFI_STATUS
LibGetSalWakeupVector (
    OUT UINT64  *WakeVector
    );

VOID *
LibSearchSalSystemTable (
    IN  UINT8   EntryType
    );

SAL_RETURN_REGS
LibSalProc (
    IN  UINT64    Arg1,
    IN  UINT64    Arg2,
    IN  UINT64    Arg3,
    IN  UINT64    Arg4,
    IN  UINT64    Arg5,
    IN  UINT64    Arg6,
    IN  UINT64    Arg7,
    IN  UINT64    Arg8
    );

#endif
