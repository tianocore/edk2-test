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
  
    EmsTclInit.h
    
Abstract:

    Incude header files for TCL related functions

--*/

#ifndef __EMS_TCL_H__
#define __EMS_TCL_H__

#include <tcl.h>
#include "EmsTypes.h"
#ifdef WITH_GUI
#include <tk.h>
#endif
//
// Structure definition for command table
//
typedef struct _TCL_CMD_TBL {
  INT8        *Cmd;
  Tcl_CmdProc *Proc;
} TCL_CMD_TBL;

INT32
EmsGuiInterpInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  The EMS GUI intepreter's initialization

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

VOID_P
RpcTclInit (
  Tcl_Interp *Interp
  )
/*++

Routine Description:

  Initialize the EMS RPC

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

INT32
EmsTestInterpInit (
  Tcl_Interp  *Interp
  )
/*++

Routine Description:

  The EMS test intepreter's initialization

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

extern Tcl_Interp *TestCaseInterp;
extern Tcl_Interp *GuiInterp;

#endif
