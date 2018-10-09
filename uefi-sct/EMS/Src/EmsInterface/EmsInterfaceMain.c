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
  
    EmsInterfaceMain.c
    
Abstract:

    Implementation for interface related TCL commands

--*/

#include "EmsInterface.h"

STATIC TCL_CMD_TBL  TclCmd[] = {
  {
    "VifUp",
    TclVifUp
  },
  {
    "ShowIf",
    TclShowIf
  },
  {
    "Interface",
    TclSetIf
  },
  {
    "VifDown",
    TclVifDown
  },
  {
    "GetMac",
    TclGetMac
  },
  {
    "GetHostMac",
    TclGetMac
  },
  {
    NULL,
    NULL
  }
};

VOID_P
InterfaceTclInit (
  Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS Interface related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  UINT32  Index;
  //
  // Create internal TCL commands
  //
  for (Index = 0; TclCmd[Index].Cmd; Index++) {
    Tcl_CreateCommand (
      Interp,
      TclCmd[Index].Cmd,
      TclCmd[Index].Proc,
      (ClientData) NULL,
      (Tcl_CmdDeleteProc *) NULL
      );
  }

  return ;
}
