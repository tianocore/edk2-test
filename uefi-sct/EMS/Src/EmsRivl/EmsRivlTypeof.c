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
  
    EmsRivlTypeof.c
    
Abstract:

    Implementation of RIVL TCL command Typeof

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"

INT32
TclTypeof (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Typeof" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          Buff[MAX_ERRBUFF_LEN];
  RIVL_VARIABLE *Variable;
  INT8          *Type;

  //
  // Check argument count, should be 1
  //
  if ((Argc != 2)) {
    sprintf (Buff, "Typeof : Syntax Error!");
    goto ErrorExit;
  }

  Variable = RivlVariableFindByName ((INT8 *) Argv[1]);
  if (!Variable) {
    sprintf (Buff, "Typeof : Variable %s not defined", Argv[1]);
    goto ErrorExit;
  }

  Type = Variable->Internal ? Variable->IType->Name : Variable->EType->Name;
  sprintf (Buff, "%s", Type);

  Tcl_AppendResult (Interp, Buff, (INT8 *) NULL);
  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, Buff, (INT8 *) NULL);
  return TCL_ERROR;
}
