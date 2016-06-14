/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
