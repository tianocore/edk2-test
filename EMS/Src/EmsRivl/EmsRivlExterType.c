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
  
    EmsRivlExterType.c
    
Abstract:

    Implementation of RIVL external type declaration

--*/

#include "EmsRivlMain.h"
#include "EmsRivlType.h"
#include "EmsRivlUtil.h"
#include "EmsRivlVar.h"
#include "stdlib.h"
#include "EmsRivlNameScope.h"
#include "EmsRpcMain.h"

BOOLEAN
RivlBuildvariable (
  INT8           *Message,
  RIVL_VARIABLE  *Variable
  );

INT32
TclVarDeclareExternal (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  The implementation routine for Declare TCL variables

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          Message[MAX_MESSAGE_LEN];
  INT8          ErrorBuff[MAX_ERRBUFF_LEN];
  INT8          Name[MAX_VARNAME_LEN];
  BOOLEAN       IsArray;
  BOOLEAN       IsRefer;
  BOOLEAN       IsPtr;
  UINT32        ArrayNum;
  RIVL_VARIABLE *Variable;
  RIVL_TYPE     *Type;
  INT8          *VarName;
  INT32         Length;
  UINT32        Index;
  UINT32        Index2;
  BOOLEAN       Pass;
  INT8          *Out;
  INT8          *Log;

  IsRefer = FALSE;
  IsPtr   = FALSE;

  Type    = RivlTypeFindByName ((INT8 *) Argv[0]);
  if (NULL == Type) {
    sprintf (ErrorBuff, "Type %s not defined", (INT8 *) Argv[0]);
    goto ErrorExit;
  }

  if (Argc < 2) {
    sprintf (ErrorBuff, "Lack of Variable Name for Type \"%s\"", Argv[0]);
  }

  for (Index = 1; Index < (UINT32) Argc; Index++) {
    VarName = (INT8 *) Argv[Index];
    if (strlen (VarName) > MAX_VARNAME_LEN) {
      sprintf (ErrorBuff, "Variable Name \"%s\" is too long.", VarName);
      goto ErrorExit;
    }

    if (VarName[0] == '&') {
      IsRefer = TRUE;
      VarName = &VarName[1];
    } else if (VarName[0] == '*') {
      IsPtr   = TRUE;
      VarName = &VarName[1];
    }

    IsArray = IsDefineArray (VarName, &ArrayNum, Name);
    if (0 == ArrayNum) {
      sprintf (ErrorBuff, "Format error: \"%s\"", VarName);
      goto ErrorExit;
    }

    if (NULL != RivlVariableFindByName (Name)) {
      sprintf (ErrorBuff, "Variable \"%s\" is redefined", Name);
      goto ErrorExit;
    }

    Variable = (RIVL_VARIABLE *) malloc (sizeof (RIVL_VARIABLE));
    strcpy (Variable->Name, Name);
    Variable->Internal      = FALSE;
    Variable->EType         = Type;
    Variable->IType         = NULL;
    Variable->IsArray       = IsArray;
    Variable->ArrayNum      = ArrayNum;
    Variable->Value         = NULL;
    Variable->InternalValue = NULL;
    Variable->Address       = NULL;
    Variable->Next          = NULL;
    Variable->IsRefer       = IsRefer;
    Variable->IsPtr         = IsPtr;
    Variable->NextByScope   = NULL;
    Variable->Scope         = RivlScopes[ScopeDepth];

    if (IsArray) {
      Variable->Value = (RIVL_VARIABLE_VALUE *) malloc (sizeof (RIVL_VARIABLE_VALUE) * ArrayNum);
      for (Index2 = 0; Index2 < ArrayNum; Index2++) {
        sprintf (Variable->Value[Index2].Name, "%s(%d)", Name, Index2);
        Variable->Value[Index2].Value = NULL;
      }
    } else {
      Variable->Value = (RIVL_VARIABLE_VALUE *) malloc (sizeof (RIVL_VARIABLE_VALUE) * (Type->MemberNum));
      for (Index2 = 0; Index2 < Type->MemberNum; Index2++) {
        sprintf (Variable->Value[Index2].Name, "%s", Type->Members[Index2].Name);
        Variable->Value[Index2].Value = NULL;
      }
    }

    RivlVariableAdd (Variable);
  }
  //
  // 1). Build message  2). sent Out 3). recv response
  //
  if (FALSE == RivlBuildvariable (Message, Variable)) {
    sprintf (
      ErrorBuff,
      "Something ErrorExit!"
      );
    goto ErrorExit;
  }

  Length = strlen (Message);

  RpcSendMessage (Length, Message);

  Message[0]  = 0;
  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);
  if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) || (FALSE == Pass)) {
    sprintf (
      ErrorBuff,
      "EAS: Exter-Type %s failed!",
      Name
      );
    goto ErrorExit;
  }

  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;

}

BOOLEAN
RivlBuildvariable (
  INT8           *Message,
  RIVL_VARIABLE  *Variable
  )
/*++

Routine Description:

  Build a Rivl variable according to the message

Arguments:

  Message     - According to the message to build a new Rivl variable
  Variable    - Return the new Rivl variable

Returns:

  TRUE

--*/
{
  INT8    TempBuff[20];
  UINT32  TempSize;

  //
  // COMMANDNAME var_name type_name total_size array_number
  //
  sprintf (Message, "RIVL_CRTVAR ");
  if (Variable->IsRefer) {
    strcat (Message, "&");
  } else if (Variable->IsPtr) {
    strcat (Message, "*");
  }
  //
  // strcat  (message, "@");
  //
  strcat (Message, Variable->Name);
  strcat (Message, " ");
  if (Variable->Internal) {
    //
    // Internal Type
    //
    strcat (Message, Variable->IType->Name);
    strcat (Message, " ");
    memset (TempBuff, 0, 8);
    TempSize = (Variable->IsPtr ? SZ_PTR : (Variable->IType->Size)) * Variable->ArrayNum;
    sprintf (TempBuff, "%d ", TempSize);
    strcat (Message, TempBuff);
  } else {
    strcat (Message, Variable->EType->Name);
    strcat (Message, " ");
    memset (TempBuff, 0, 8);

    TempSize = Variable->EType->Size * Variable->ArrayNum;
    sprintf (TempBuff, "%d ", TempSize);
    strcat (Message, TempBuff);
  }

  memset (TempBuff, 0, 8);
  sprintf (TempBuff, "%d", Variable->ArrayNum);
  strcat (Message, TempBuff);
  return TRUE;
}
