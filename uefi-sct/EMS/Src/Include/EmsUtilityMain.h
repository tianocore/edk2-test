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
  
    EmsUtilityMain.h
    
Abstract:

    Incude header files for utility functions

--*/

#ifndef _EMS_UTILITY_H_
#define _EMS_UTILITY_H_

#include "EmsMain.h"
#include "EmsTypes.h"
#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsLogCommand.h"

#ifndef MAX_DIR_LEN
#define MAX_DIR_LEN 1024
#endif

extern Tcl_CmdProc  TclStall;
extern Tcl_CmdProc  TclInclude;
extern Tcl_CmdProc  TclSetCaseRoot;

VOID_P
UtilityTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Utility related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

#endif
