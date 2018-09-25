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
