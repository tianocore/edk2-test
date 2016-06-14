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
  
    EmsRivlRemoteDel.c
    
Abstract:

    Implementation of RIVL type/func/variable delete 

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "stdlib.h"
#include "EmsRivlUtil.h"
#include "EmsRivlType.h"
#include "EmsRpcMain.h"
#include "EmsRivlTclVar.h"
#include "EmsRivlFunc.h"

INT32
TclRemoteDelType (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DelType" implementation routine  

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
  INT8  Message[MAX_MESSAGE_LEN];
  INT8  *Name;
  INT32 Length;

  Name = NULL;
  //
  // Check argument count, should be 1
  //
  if ((Argc != 1) && (Argc != 2)) {
    sprintf (ErrorBuff, "EMS_DELTYPE : Syntax Error!");
    goto ErrorExit;
  }
  //
  // Check if the type exist?
  //
  if (Argc == 2) {
    Name = (INT8 *) Argv[1];
    if (NULL == RivlTypeFindByName (Name)) {
      sprintf (
        ErrorBuff,
        "EMS_DELTYPE : Type %s not defined!",
        Name
        );
      goto ErrorExit;
    }
  }
  //
  // Build Message and Send it to EAS
  //
  memset (Message, 0, MAX_MESSAGE_LEN);
  Message[0] = '\0';
  strcat (Message, "RIVL_DELTYPE");
  if (Name) {
    strcat (Message, " ");
    strcat (Message, Argv[1]);
  }

  Length = strlen (Message);
  RpcSendMessage (Length, Message);
  Message[0]  = 0;
  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);

  //
  // Local Delete Type
  //
  if (Name) {
    RivlTypeRemoveByName (Name);
  } else {
    RivlTypeDestroyAll ();
  }

  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclRemoteDelVar (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DelVar" implementation routine  

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
  INT8  Message[MAX_MESSAGE_LEN];
  INT8  *Name;
  INT32 Length;

  Name = NULL;
  //
  // Check argument count, should be 1
  //
  if ((Argc != 1) && (Argc != 2)) {
    sprintf (ErrorBuff, "EMS_DELTYPE : Syntax Error!");
    goto ErrorExit;
  }
  //
  // Check if the variable exist?
  //
  if (Argc == 2) {
    Name = (INT8 *) Argv[1];
    if (NULL == RivlVariableFindByName (Name)) {
      sprintf (ErrorBuff, "EMS_DELVAR : Variable %s not defined!", Name);
      goto ErrorExit;
    }
  }
  //
  // Build Message and Send it to EAS
  //
  Message[0] = '\0';
  strcat (Message, "RIVL_DELVAR");
  if (Argc == 2) {
    strcat (Message, " ");
    strcat (Message, Argv[1]);
  }

  Length = strlen (Message);
  RpcSendMessage (Length, Message);
  Message[0]  = '\0';
  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);
  //
  // rivl_msg_send;
  //
  // Local Delete variable and its relative TCL variable
  //
  if (Name) {
    RivlVariableRemoveByName (Name);
    RivlRemoveTclVarsByName (Interp, (INT8 *) Name);
  } else {
    RivlVariableDestroyAll ();
    RivlRemoveTclVarsAll (Interp);
  }

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclRemoteDelFunc (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DelFunc" implementation routine  

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
  INT8  *Name;

  Name = NULL;
  //
  // Check argument count, should be 1
  //
  if ((Argc != 1) && (Argc != 2)) {
    sprintf (ErrorBuff, "EMS_DELTYPE : Syntax Error!");
    goto ErrorExit;
  }
  //
  // Check if the variable exist?
  //
  if (Argc == 2) {
    Name = (INT8 *) Argv[1];
    if (NULL == RivlFunctionFindByName (Name)) {
      sprintf (ErrorBuff, "EMS_DELTYPE : Variable %s not defined!", Name);
      goto ErrorExit;
    }
  }
  //
  // Local Delete variable and its relative TCL variable
  //
  if (Name) {
    RivlFunctionRemoveByName (Name);
  } else {
    RivlFunctionRemoveAll ();
  }

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}
