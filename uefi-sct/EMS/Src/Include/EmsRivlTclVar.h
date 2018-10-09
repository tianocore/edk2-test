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
  
    EmsRivlTclVar.h
    
Abstract:

    Incude header files for RIVL tcl variable related functions

--*/

#ifndef __EMS_RIVL_TCL_VAR_H__
#define __EMS_RIVL_TCL_VAR_H__
#include "EmsRivlMain.h"

RIVL_TCL_VARIABLES  *
RivlTclVarsFindByName (
  INT8                    *Name
  )
/*++

Routine Description:

  Find one group of Rivl TCL variables accroding to name

Arguments:

  Name  - The name of the group

Returns:

  return the pointer to the group of Rivl variables found

--*/
;

BOOLEAN
TclVarsExist (
  INT8                    *Name
  )
/*++

Routine Description:

  Check whether the group of TCL variable exists

Arguments:

  Name  - The name of the group

Returns:

  TRUE or FALSE

--*/
;

RIVL_TCL_VARIABLE   *
RivlTclVarFindByName (
  RIVL_TCL_VARIABLES    *Vars,
  INT8                  *Name
  )
/*++

Routine Description:

  Find a Rivl TCL variable accroding to name

Arguments:

  Name  - The name of the variable

Returns:

  return the pointer to the Rivl variable found

--*/
;

BOOLEAN
TclVarExist (
  RIVL_TCL_VARIABLES     *Vars,
  INT8                   *Name
  )
/*++

Routine Description:

  Check whether the TCL variable exists

Arguments:

  Name  - The name of the variable

Returns:

  TRUE or FALSE

--*/
;

BOOLEAN
RivlAddTclVarsByName (
  INT8  *Name
  )
/*++

Routine Description:

  Add TCL variable by RIVL variable name

Arguments:

  Name  - The RIVL variable name

Returns:

  TRUE or FALSE

--*/
;

BOOLEAN
RivlAddTclVarByName (
  INT8  *VarName,
  INT8  *TclVarName
  )
/*++

Routine Description:

  Add TCL variable by RIVL variable name and TCL variable name

Arguments:

  VarName      - The RIVL variable name
  TclVarName   - The TCL variable name

Returns:

  TRUE or FALSE

--*/
;

VOID_P
RivlRemoveTclVarsAll (
  Tcl_Interp        *Interp
  )
/*++

Routine Description:

  Remove all the TCL variables

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

VOID_P
RivlRemoveTclVarsByName (
  Tcl_Interp        *Interp,
  INT8              *Name
  )
/*++

Routine Description:

  Remove a TCL variable accroding to name

Arguments:

  Interp      - TCL intepreter.
  Name    - The variable name

Returns:

  None

--*/
;

BOOLEAN
RivlRemoveTclVars (
  Tcl_Interp          *Interp,
  RIVL_TCL_VARIABLES  *Vars
  )
/*++

Routine Description:

  Remove all the TCL variables

Arguments:

  Interp      - TCL intepreter.
  Vars    - The RIVL variables

Returns:

  TRUE

--*/
;

#endif
