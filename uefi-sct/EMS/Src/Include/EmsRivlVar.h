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
  
    EmsRivlVar.h
    
Abstract:

    Incude header files for RIVL variable related functions

--*/

#ifndef _EMS_RIVL_VAR_H_
#define _EMS_RIVL_VAR_H_

#include "EmsRivlMain.h"

RIVL_VARIABLE *
RivlVariableFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find RIVL variable accroding to name

Arguments:

  Name  - the name of variable

Returns:

  Return the pointer to RIVL variable

--*/
;

VOID_P
RivlVariableRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove RIVL variable accroding to name

Arguments:

  Name  - The name of variable

Returns:

  None

--*/
;

VOID_P
RivlVariableDestroy (
  RIVL_VARIABLE *VPointer
  )
/*++

Routine Description:

  Destroy a RIVL variable

Arguments:

  VPointer - The pointer to the RIVL variable

Returns:

  None

--*/
;

VOID_P
RivlVariableAdd (
  RIVL_VARIABLE *Var
  )
/*++

Routine Description:

  Add a new RIVL variable

Arguments:

  Var - The new RIVL variable to be added

Returns:

  None

--*/
;

VOID_P
RivlVariableDestroyAll (
  VOID_P
  )
/*++

Routine Description:

  Destroy all the RIVL variables

Arguments:

  None

Returns:

  None

--*/
;

RIVL_VARIABLE *
RivlVariableGetByScope (
  RIVL_SCOPE   *Scope
  )
/*++

Routine Description:

  Get RIVL variables accroding to scope

Arguments:

  Scope - Used to find RIVL variables

Returns:

  return the Pointer to RIVL variables

--*/
;

#endif
