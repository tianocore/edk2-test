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
  
    EmsRivFuncDef.c
    
Abstract:

    Implementation of RIVL function declaration

--*/

#include "stdlib.h"
#include "EmsRivlType.h"
#include "EmsRivlFunc.h"
#include "EmsRivlUtil.h"
#include "EmsRivlMain.h"

#define MAX_MEMBER_NUM  100

INT32
TclFuncDef (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Func" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          *Name;
  INT8          ErrorBuff[MAX_ERRBUFF_LEN];
  UINT32        ArgNum;
  INT8          Type[MAX_STRING_LEN];
  UINT32        Index;
  UINT32        Len;
  UINT32        Pos;
  INT8          Line[MAX_STRING_LEN];

  RIVL_FUNCTION *TempFunction;

  TempFunction = NULL;
  LogCurrentCommand (Argc, Argv);

  //
  // Parse argument
  //
  if (Argc != 3) {
    sprintf (ErrorBuff, "%s: Syntax error.\n", Argv[0]);
    goto ErrorExit;
  }

  Name = (INT8 *) Argv[1];
  if (strlen (Name) >= MAX_FUNTIONNAME_LEN) {
    sprintf (ErrorBuff, "%s: Function Name is too long.\n", Argv[0]);
    goto ErrorExit;
  }
  //
  // Check if this type has existed. If yes, give a warning and return
  //
  if (FunctionExist (Name)) {
    sprintf (ErrorBuff, "%s: Function '%s' redefined.\n", Argv[0], Name);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    goto ErrorExit;
  }

  TempFunction = (RIVL_FUNCTION *) malloc (sizeof (RIVL_FUNCTION));

  strcpy (TempFunction->Name, Name);

  Len     = strlen (Argv[2]);
  Pos     = 0;
  ArgNum  = 0;
  while (Pos != Len) {
    Pos = GetNextLine ((INT8 *) Argv[2], Pos, Line);
    if ('\0' == *Line) {
      continue;
    }

    StripString (Line, Type);
    if (!((RivlInternalTypeFindByName (Type)) || (RivlTypeFindByName (Type)))) {
      sprintf (ErrorBuff, "%s: Type '%s' doesn't exist.\n", Argv[0], Type);
      Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
      goto ErrorExit;
    }

    TempFunction->arg_type[ArgNum] = _strdup (Type);
    ArgNum++;
    if (ArgNum == MAX_ARG_NUM) {
      sprintf (ErrorBuff, "%s: Function '%s' has too many argumems.\n", Argv[0], Name);
      Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
      goto ErrorExit;
    }
  }

  TempFunction->Argc = ArgNum;
  RivlFunctionAdd (TempFunction);

  Tcl_CreateCommand (
    TestCaseInterp,
    Name,
    TclFuncDeclare,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  return TCL_OK;

ErrorExit:
  if (TempFunction) {
    for (Index = 0; Index < ArgNum; Index++) {
      free (TempFunction->arg_type[Index]);
    }

    free (TempFunction);
  }

  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}
