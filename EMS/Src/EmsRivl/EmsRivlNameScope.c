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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsRivlNameScope.c
    
Abstract:

    Implementation of RIVL Name Space

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "stdlib.h"
#include "EmsRivlEndian.h"
#include "EmsRivlUtil.h"
#include "EmsRpcMain.h"
#include "EmsRivlTclVar.h"
#include "EmsThread.h"

RIVL_SCOPE  *RivlScopes[SCOPE_STACK_DEPTH];
UINT32      ScopeDepth = 0;

INT32
TclBeginScope (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "BeginScope" implementation routine 

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];

  LogCurrentCommand (Argc, Argv);

  if (Argc != 2) {
    sprintf (ErrorBuff, "%s", "BeginScope: BeginScope scopename");
    goto ErrorExit;
  };

  if (strlen (Argv[1]) >= MAX_SCOPENAME_LEN) {
    sprintf (ErrorBuff, "BeginScope: scopename \"%s\" is too long", Argv[1]);
    goto ErrorExit;
  }

  ScopeDepth++;

  RivlScopes[ScopeDepth] = (RIVL_SCOPE *) calloc (1, sizeof (RIVL_SCOPE));
  strcpy (RivlScopes[ScopeDepth]->Name, Argv[1]);

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (
    Interp,
    ErrorBuff,
    (INT8 *) NULL
    );
  return TCL_ERROR;
}

INT32
TclEndScope (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EndScope" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          ErrorBuff[MAX_ERRBUFF_LEN];
  INT8          Message[MAX_MESSAGE_LEN];
  INT8          *Name;
  RIVL_VARIABLE *Header;
  RIVL_VARIABLE *Var;
  INT32         Length;

  LogCurrentCommand (Argc, Argv);

  if (Argc != 2) {
    sprintf (ErrorBuff, "%s", "EndScope: EndScope scopename");
    goto ErrorExit;
  };

  if (ScopeDepth == 0) {
    sprintf (ErrorBuff, "EndScope: None scopename \"%s\" defined", Argv[1]);
    goto ErrorExit;
  }

  if (strcmp (Argv[1], RivlScopes[ScopeDepth]->Name)) {
    sprintf (
      ErrorBuff,
      "EndScope: scopename \"%s\" does not match current scopename \"%s\"",
      Argv[1],
      RivlScopes[ScopeDepth - 1]->Name
      );
    goto ErrorExit;
  }

  Header = RivlVariableGetByScope (RivlScopes[ScopeDepth]);

  for (Var = Header; Var; Var = Var->NextByScope) {
    //
    // Build Message and Send it to EAS
    //
    Message[0] = '\0';
    strcat (Message, "RIVL_DELVAR");
    if (Argc == 2) {
      strcat (Message, " ");
      strcat (Message, Var->Name);
    }

    Length = strlen (Message);
    RpcSendMessage (Length, Message);
    memset (Message, 0, MAX_MESSAGE_LEN);
    Length = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);
  }

  for (Var = Header; Var;) {
    Name  = _strdup (Var->Name);
    Var   = Var->NextByScope;
    //
    // Local Delete variable and its relative TCL variable
    //
    RivlVariableRemoveByName (Name);
    RivlRemoveTclVarsByName (Interp, Name);
    free (Name);

  }

  free (RivlScopes[ScopeDepth]);
  RivlScopes[ScopeDepth] = NULL;
  ScopeDepth--;
  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (
    Interp,
    ErrorBuff,
    (INT8 *) NULL
    );
  return TCL_ERROR;
}

VOID
EmsClearLocalScope(
  VOID
  )
/*++

Routine Description:

  Clear all local scope

Arguments:

  None

Returns:

  None

--*/
{
  while(ScopeDepth > 0)
  {
    free (RivlScopes[ScopeDepth]);
    RivlScopes[ScopeDepth] = NULL;
    ScopeDepth--;
  }
}
