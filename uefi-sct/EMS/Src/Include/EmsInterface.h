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
  
    EmsInterface.h
    
Abstract:

    Data definition for interface related functions

--*/

#ifndef __EMS_INTERFACE_H__
#define __EMS_INTERFACE_H__

#include "EmsTypes.h"
#include "EmsTclInit.h"

extern
VOID_P
InterfaceTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS Interface related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

VOID
VifDownAll(
  VOID
  )
/*++

Routine Description:

  Shutdown all the virtual interface

Arguments:

  None

Returns:

  None

--*/
;

extern Tcl_CmdProc  TclVifUp;
extern Tcl_CmdProc  TclVifDown;
extern Tcl_CmdProc  TclGetMac;
extern Tcl_CmdProc  TclShowIf;
extern Tcl_CmdProc  TclSetIf;

#endif // __EMS_INTERFACE_H__
