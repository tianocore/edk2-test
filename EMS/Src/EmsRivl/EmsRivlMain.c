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
  
    EmsRivlMain.c
    
Abstract:

    Implementation of RIVL main 

--*/

#include "EmsTypes.h"
#include "EmsRivlMain.h"

STATIC TCL_CMD_TBL  TclCmd[] = {
  {
    "Struct",
    TclTypeDef
  },
  {
    "Union",
    TclTypeDef
  },
  {
    "ViewType",
    TclViewType
  },
  {
    "GetVar",
    TclGetVar
  },
  {
    "DumpVar",
    TclDumpVar
  },
  {
    "BeginScope",
    TclBeginScope
  },
  {
    "EndScope",
    TclEndScope
  },
  {
    "Func",
    TclFuncDef
  },
  {
    "Exit",
    TclTestAbort
  },
  {
    "GetAck",
    TclGetAck
  },
  {
    "DelType",
    TclRemoteDelType
  },
  {
    "DelVar",
    TclRemoteDelVar
  },
  {
    "Sizeof",
    TclSizeof
  },
  {
    "SetVar",
    TclSetVar
  },
  {
    "Typeof",
    TclTypeof
  },
  {
    "DelFunc",
    TclRemoteDelFunc
  },
  {
    "Pack",
    TclPack
  },
  {
    "DelTclVar",
    TclDelTclVar
  },
  {
    "Exec",
    TclExec
  },
  {
    "GetFile",
    TclGetFile
  },
  {
    "PutFile",
    TclPutFile
  },
  {
    "SetTargetBits",
    TclSetTargetBits
  },
  {
    "GetTargetBits",
    TclGetTargetBits
  },
  {
    NULL,
    NULL
  }
};

VOID_P
RivlTclInit (
  Tcl_Interp *Interp
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
  for (Index = 0; TclCmd[Index].Cmd; Index++) {
    Tcl_CreateCommand (
      Interp,
      TclCmd[Index].Cmd,
      TclCmd[Index].Proc,
      (ClientData) NULL,
      (Tcl_CmdDeleteProc *) NULL
      );
  }

  for (Index = 0; InternalTypes[Index].Name; Index++) {
    Tcl_CreateCommand (
      Interp,
      InternalTypes[Index].Name,
      TclVarDeclareInternal,
      (ClientData) NULL,
      (Tcl_CmdDeleteProc *) NULL
      );
  }

  return ;
}
