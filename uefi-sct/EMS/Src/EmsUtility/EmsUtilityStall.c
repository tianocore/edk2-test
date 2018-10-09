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
  
    EmsUtilityStall.c
    
Abstract:

    Implementation of Ents command "Stall"

--*/

#include "tcl.h"
#include "EmsUtilityMain.h"
#include "stdlib.h"

INT32
TclStall (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Stall" implementation routine  

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
  INT32 Timeout;

  //
  // get time interval of sleep
  // the format of this command is: Stall timeout
  // The unit of 'timeout' is second
  //
  if (Argc != 2) {
    sprintf (ErrorBuff, "Syntax of Stall - Stall Timeout\n");
    goto ErrorExit;
  }

  Timeout = atoi (Argv[1]);
  Tcl_Sleep (Timeout * 1000);
  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}
