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

  LibSalPal.h

Abstract:

  Function prototype definitions.

--*/

#ifndef _EFI_LIB_SAL_PAL_H_
#define _EFI_LIB_SAL_PAL_H_

#include "PalApi.h"
#include "SalApi.h"

typedef PAL_RETURN_REGS (EFIAPI *PAL_PROC) (IN UINT64 FunctionId, IN UINT64 Arg2, IN UINT64 Arg3, IN UINT64 Arg4);

EFI_STATUS
LibInitSalAndPalProc (
  VOID
  )
/*++

Routine Description:

  Initialize SAL and PAL procedure calling.

Arguments:

  None

Returns:

  EFI_SUCCESS - Always return success.

--*/
;

EFI_STATUS
LibGetSalVersionInfo (
  IN  OUT   UINT16  *SalSpecRev,
  IN  OUT   UINT16  *SalARev,
  IN  OUT   UINT16  *SalBRev
  )
/*++

Routine Description:

  Get SAL version infomation.

Arguments:

  SalSpecRev  - SAL Spec reversion.
  SalARev     - SAL A reversion.
  SalBRev     - SAL B reversion.

Returns:

  EFI_UNSUPPORTED - mSalSystemTable is NULL.
  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
LibGetSalIoPortMapping (
  OUT UINT64  *IoPortMapping
  )
/*++

Routine Description:

  Get the IO Port Map from the SAL System Table.

Arguments:

  IoPortMapping  - Pointer to receive IO port mapping address.

Returns:

  EFI_UNSUPPORTED - mSalSystemTable is NULL.
  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
LibGetSalIpiBlock (
  OUT UINT64  *IpiBlock
  )
/*++

Routine Description:

  Get the IPI block from the SAL system table

Arguments:

  IpiBlock  - Pointer to receive IPI block address.

Returns:

  EFI_UNSUPPORTED - SalMemDesc is NULL.
  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
LibGetSalWakeupVector (
  OUT UINT64  *WakeVector
  )
/*++

Routine Description:

  Get the wakeup vector from the SAL system table

Arguments:

  WakeVector  - Pointer to receive wakeup vector.

Returns:

  EFI_UNSUPPORTED - Cannot find wakeup decriptor.
  EFI_SUCCESS - Operation succeeded.

--*/
;

VOID  *
LibSearchSalSystemTable (
  IN  UINT8   EntryType
  )
/*++

Routine Description:

  Search SAL system table.

Arguments:

  EntryType - SAL entry type.

Returns:

  None.

--*/
;

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
  )
;

#endif
