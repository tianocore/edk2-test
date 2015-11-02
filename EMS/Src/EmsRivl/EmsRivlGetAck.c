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
  
    EmsRivlGetAck.c
    
Abstract:

    Implementation of RIVL GetAck(TCL command)

--*/

#include <stdlib.h>
#include "EmsRivlType.h"
#include "EmsRivlMain.h"
#include "EmsRpcMain.h"

INT32
TclGetAck (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GetAck" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8    Message[MAX_MESSAGE_LEN];
  INT8    ErrorBuff[MAX_ERRBUFF_LEN];
  INT8    TempStr[10];
  INT32   Timeout;
  INT32   Length;
  BOOLEAN Pass;
  INT8    *Out;
  INT8    *Log;

  if (Argc > 1) {
    Timeout = atoi (Argv[1]);
  } else {
    Timeout = -1;
  }

  Timeout = -1;

  //
  // memset  (message, 0, MAX_MESSAGE_LEN);
  //
  Message[0]  = 0;
  Length      = RpcRecvMessage (Timeout, MAX_MESSAGE_LEN, Message);
  if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) /*||
      (false == Pass)*/ ) {
    sprintf (ErrorBuff, "GetAck failed!");
    goto ErrorExit;
  }
  //
  // Format of GetAck should be
  //      GetAck [timeout [Pass [Out [log]]]]
  //
  switch (Argc) {
  case 5:
    Tcl_SetVar (Interp, Argv[4], Log, TCL_GLOBAL_ONLY);

  case 4:
    Tcl_SetVar (Interp, Argv[3], Out, TCL_GLOBAL_ONLY);

  case 3:
    if (Pass == TRUE) {
      strcpy (TempStr, "true");
      Tcl_SetVar (Interp, Argv[2], TempStr, TCL_GLOBAL_ONLY);
    } else {
      strcpy (TempStr, "false");
      Tcl_SetVar (Interp, Argv[2], TempStr, TCL_GLOBAL_ONLY);
    }
    break;

  case 2:
    break;

  case 1:
    break;

  default:
    sprintf (ErrorBuff, "Contax of GetAck error");
    goto ErrorExit;
  }

  if (Pass != TRUE) {
    sprintf (ErrorBuff, "GetAck failed!");
    goto ErrorExit;
  }

  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);

  return TCL_ERROR;
}
