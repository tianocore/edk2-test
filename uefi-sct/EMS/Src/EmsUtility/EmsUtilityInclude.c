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
  
    EmsUtilityInclude.c
    
Abstract:

    Implementation of Ents TCL commands  "SetCaseRoot" and "Include"

--*/

#include "tcl.h"
#include "EmsUtilityMain.h"

#define MAX_JOIN_PATH 10

STATIC INT8 EmsRootDir[1024] = {0,};

INT32
TclSetCaseRoot (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "SetCaseRoot" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];
  if (Argc != 2) {
    sprintf (ErrorBuff, "Syntax of SetCaseRoot failed\n");
    goto ErrorExit;
  }

  strcpy(EmsRootDir, Argv[1]);
  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclInclude (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Include" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8        ErrorBuff[MAX_ERRBUFF_LEN];
  Tcl_DString Directory;
  INT32       ArgcJoin;
  INT8        *ArgvJoin[MAX_JOIN_PATH];
  INT32       Index;

  if (Argc > MAX_JOIN_PATH) {
    sprintf (ErrorBuff, "Syntax of Include failed\n");
    goto ErrorExit;
  }

  ArgcJoin    = Argc;
  ArgvJoin[0] = EmsRootDir;
  for (Index = 1; Index < Argc; Index++) {
    ArgvJoin[Index] = (INT8 *) Argv[Index];
  }

  Tcl_DStringInit (&Directory);
  Tcl_JoinPath (ArgcJoin, (CONST84 INT8 **) ArgvJoin, &Directory);
  Tcl_EvalFile (Interp, Tcl_DStringValue (&Directory));
  Tcl_DStringFree (&Directory);

  Tcl_AppendResult (Interp, (INT8 *) NULL);
  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}
