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
  
    EmsTclInit.c
    
Abstract:

  Implementation of EMS TCL Main Initialize function.

--*/

#include "EmsProtocols.h"
#include "EmsPktCapture.h"
#include "EmsPktCreate.h"
#include "EmsPktSend.h"
#include "EmsPktValidate.h"
#include "EmsPktParse.h"
#include "EmsPktPayload.h"
#include "EmsPktDump.h"
#include "EmsRpcMain.h"
#include "EmsInterface.h"
#include "EmsRivlMain.h"
#include "EmsUtilityMain.h"
#include "EmsLogCommand.h"
#include "EmsVtcpTcb.h"
#include "EmsPktRecvAssertion.h"

#include "EmsEftp.h"
#include "EmsTclCleanup.h"
#include "EmsUtilityString.h"
#include "EmsThread.h"
#include "EmsTest.h"

Tcl_Interp        *TestCaseInterp;
Tcl_Interp        *GuiInterp;
extern EmsThread  EmsGuiThreadCtl;

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
{
  UINT32  Index;

  TestCaseInterp = Interp;

  //
  // Invoke TCL initialization functions in other modules
  //
  CaptureTclInit (Interp);
  ValidateTclInit (Interp);
  CreateTclInit (Interp);
  SendTclInit (Interp);
  LogTclInit (Interp);
  ParseTclInit (Interp);
  PayloadTclInit (Interp);
  DumpTclInit (Interp);
  RivlTclInit (Interp);
  UtilityTclInit (Interp);
  InterfaceTclInit (Interp);
  VTcpTclInit (Interp);

  RpcTclCmdInit (Interp);

  //
  // Invoke TCL initialization functions in individual protocols
  //
  for (Index = 0; Protocols[Index]; Index++) {
    if (Protocols[Index]->TclInit) {
      Protocols[Index]->TclInit (Interp);
    }
  }

  return TCL_OK;
}

STATIC
INT32
GuiMainEventLoop (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GuiMainEventLoop" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  EmsEvent    *Event;
  Tcl_Interp  *ExecInterp;

  Event       = NULL;
  ExecInterp  = NULL;

  while (TRUE) {
    EmsEventQueueLock (&EmsThreadEventMng);
    if (FALSE == EmsEventListIsEmpty (&EmsThreadEventMng)) {
      EmsGetOneEvent (&Event, &EmsThreadEventMng);
      EmsEventQueueUnlock (&EmsThreadEventMng);

      ExecInterp = Event->ExecThread->Interp;
      Tcl_Preserve (ExecInterp);
      Tcl_EvalObj (ExecInterp, Event->Script);
      Event->Result = Tcl_GetObjResult (ExecInterp);
      Tcl_Release (ExecInterp);
      Tcl_DecrRefCount (Event->Script);

      if (EmsEventWait (Event)) {
        EmsThreadSignal (Event->SrcThread);
      } else {
        EmsFreeEventObj (Event, &EmsThreadEventMng);
      }

      continue;
    }

    EmsEventQueueUnlock (&EmsThreadEventMng);

    Tcl_DoOneEvent (TCL_ALL_EVENTS);
  }

  return TCL_OK;
}

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
{
  if (Tcl_Init (Interp) == TCL_ERROR) {
    return TCL_ERROR;
  }

#ifdef WITH_GUI
  if (Tk_Init (Interp) == TCL_ERROR) {
    return TCL_ERROR;
  }
#endif
  GuiInterp = Interp;

  LogTclInit (Interp);
  RivlTclInit (Interp);
  UtilityTclInit (Interp);
  InterfaceTclInit (Interp);
  RpcTclInit (Interp);
  VTcpTclInit (Interp);

  ResTclInit (Interp);

  if (EFI_SUCCESS != EmsThreadEnable (&EmsGuiThreadCtl, GuiInterp)) {
    printf ("EmsThreadEnable return Error\n");
    return TCL_ERROR;
  }

  EmsTestTclInit (Interp);
  RecvAssertionTclInit (Interp);

  EmsEftpModEnable ();
  EftpTclInit (Interp);

  StringUtilityInit (Interp);

  Tcl_CreateCommand (
    Interp,
    "GuiMainEventLoop",
    GuiMainEventLoop,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  return TCL_OK;
}
