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
  
    EmsRivlFunc.h
    
Abstract:

    Include file of RIVL function related functions

--*/

#ifndef _RIVL_FUNC_H_
#define _RIVL_FUNC_H_

#include "EmsRivlMain.h"

RIVL_FUNCTION *
RivlFunctionFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find a Rivl function type's variable accroding to name

Arguments:

  Name  - 

Returns:

  return the found variable

--*/
;

BOOLEAN
FunctionExist (
  INT8 *Name
  )
/*++

Routine Description:

  Check whether the Rivl function type's variable is exist

Arguments:

  Name  - The name of the Rivl function

Returns:

  TRUE or FALSE

--*/
;

VOID_P
RivlFunctionRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove a Rivl function type's variable accroding to name

Arguments:

  Name  - The name of the function

Returns:

  None

--*/
;

VOID_P
RivlFunctionDestroy (
  RIVL_FUNCTION *func
  )
/*++

Routine Description:

  Destroy a Rivl function

Arguments:

  Func  - The pointer to a Rivl function

Returns:

  None

--*/
;

VOID_P
RivlFunctionAdd (
  RIVL_FUNCTION *func
  )
/*++

Routine Description:

  Add a new Rivl function

Arguments:

  Func  - The pointer to a Rivl function

Returns:

  None

--*/
;

VOID_P
RivlFunctionRemoveAll (
  VOID_P
  )
/*++

Routine Description:

  Remove all the Rivl functions

Arguments:

  None

Returns:

  None

--*/
;

#endif
