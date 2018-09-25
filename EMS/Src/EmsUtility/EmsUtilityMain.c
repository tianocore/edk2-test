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
  
    EmsUtilityMain.c
    
Abstract:

    Implementation of Ents utility commands  

--*/

#include "EmsTypes.h"
#include "EmsUtilityMain.h"
#include "tcl.h"

STATIC TCL_CMD_TBL  TclUtilityCmd[] = {
  {
    "Stall",
    TclStall
  },
  {
    "Include",
    TclInclude
  },
  {
    "SetCaseRoot",
    TclSetCaseRoot
  },
  {
    NULL,
    NULL
  }
};

VOID_P
UtilityTclInit (
  Tcl_Interp        *Interp
  )
/*++

Routine Description:

  Packet capture related TCL initialization.

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
  for (Index = 0; TclUtilityCmd[Index].Cmd; Index++) {
    Tcl_CreateCommand (
      Interp,
      TclUtilityCmd[Index].Cmd,
      TclUtilityCmd[Index].Proc,
      (ClientData) NULL,
      (Tcl_CmdDeleteProc *) NULL
      );
  }

  return ;
}
