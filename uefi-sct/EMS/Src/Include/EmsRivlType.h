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
  
    EmsRivlType.h
    
Abstract:

    Incude header files for RIVL type functions

--*/

#ifndef _RIVL_TYPE_H_
#define _RIVL_TYPE_H_

#include "EmsRivlMain.h"

#define BOOLEAN_TYPE  0
#define INTN_TYPE     1
#define UINTN_TYPE    2
#define INT8_TYPE     3
#define UINT8_TYPE    4
#define INT16_TYPE    5
#define UINT16_TYPE   6
#define INT32_TYPE    7
#define UINT32_TYPE   8
#define INT64_TYPE    9
#define CHAR8_TYPE    10
#define CHAR16_TYPE   11
#define VOID_TYPE     12

RIVL_TYPE     *
RivlTypeFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find RIVL variable's type accroding to name

Arguments:

  Name  - The type name

Returns:

  return the RIVL type found

--*/
;

VOID_P
RivlTypeRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove RIVL type accroding to name

Arguments:

  Name  - The type name

Returns:

  None

--*/
;

VOID_P
RivlTypeAdd (
  RIVL_TYPE *Type
  )
/*++

Routine Description:

  Add a new RIVL type

Arguments:

  Type  - The RIVL type to be added

Returns:

  None

--*/
;

VOID_P
RivlTypeDestroy (
  RIVL_TYPE *Type
  )
/*++

Routine Description:

  Destroy a RIVL type

Arguments:

  Type  - The RIVL type to be destroied

Returns:

  None

--*/
;

VOID_P
RivlTypeDestroyAll (
  VOID_P
  )
/*++

Routine Description:

  Destroy all the RIVL types

Arguments:

  None

Returns:

  None

--*/
;

INTERNAL_TYPE *
RivlInternalTypeFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find a Rivl internal type accroding name

Arguments:

  Name  - The name of type

Returns:

  NULL if not found otherwise return the internal type found

--*/
;

#endif
