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
  
    EmsRivlFuncDecl.c
    
Abstract:

    Implementation of RIVL function declaration

--*/

#include <stdlib.h>

#include "EmsRivlMain.h"
#include "EmsRivlFunc.h"
#include "EmsRivlType.h"
#include "EmsRivlUtil.h"
#include "EmsRivlVar.h"
#include "EmsRpcMain.h"

BOOLEAN
RivlCheckOneArgument (
  INT8            *ErrorBuff,
  INT8            *Arg,
  INT8            *TypeName,
  INT8            *Value
  );

INT32
TclFuncDeclare (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  The implementation routine for Declaring TCL function

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          ErrorBuff[MAX_ERRBUFF_LEN];
  INT8          Message[MAX_MESSAGE_LEN];
  INT8          Item[MAX_STRING_LEN];
  INT8          StripValue[MAX_STRING_LEN];
  //
  // int8_t         *varname;
  //
  RIVL_FUNCTION *Func;
  UINT32        Pos;
  UINT32        ItemCnt;
  INT32         Length;
  Func = NULL;
  if (Argc != 2) {
    sprintf (
      ErrorBuff,
      "Format of Funccall invalid - FunName {Argument1 Argument2 ...}\n"
      );
    goto ErrorExit;
  }
  //
  // Check function name
  //
  if (NULL == (Func = RivlFunctionFindByName ((INT8 *) Argv[0]))) {
    sprintf (
      ErrorBuff,
      "Func %s not defined\n",
      Argv[0]
      );
    goto ErrorExit;
  }
  //
  // build message header
  //
  Message[0] = 0;
  strcat (Message, Argv[0]);
  strcat (Message, " ");

  //
  // Check argument and Append parameter to message
  // All the parameters are braced by a pair of {}, and different
  // The funcation call should be in the following format:
  //    FuncName {Argument1 Argument2 Argument3 ......}
  //    The different argumems are separated by space, or comma,
  //
  Length  = strlen (Argv[1]);
  Pos     = 0;
  ItemCnt = 0;
  while (Pos != Length) {
    Pos = GetNextSubStr ((INT8 *) Argv[1], Pos, Item);
    if (*Item) {
      ItemCnt++;
      //
      // printf ("Item[%d]=%s\n", item_cnt, Item);
      //
      if (ItemCnt > Func->Argc) {
        //
        // Check argument count
        //
        sprintf (
          ErrorBuff,
          "Func %s: Argument too much, Arg Num (In: %d, Exp:%d\n",
          Argv[0],
          ItemCnt,
          Func->Argc
          );
        goto ErrorExit;
      } else {
        StripValue[0] = 0;
        if (FALSE == RivlCheckOneArgument (
                      ErrorBuff,
                      Item,
                      Func->arg_type[ItemCnt - 1],
                      StripValue
                      )) {
          //
          // Check argument type
          //
          sprintf (
            ErrorBuff,
            "Func %s: Argument %s is invalid Type",
            Argv[0],
            Item
            );
          goto ErrorExit;
        } else {
          //
          //  printf ("message: %s\n", message+sizeof(int));
          //
          strcat (Message, StripValue);
          strcat (Message, " ");
          continue;
        }
      }
    }
  }

  Length = strlen (Message);
  RpcSendMessage (Length, Message);

  LogCurrentCommand (Argc, Argv);
  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

BOOLEAN
RivlCheckOneArgument (
  INT8            *ErrorBuff,
  INT8            *Arg,
  INT8            *TypeName,
  INT8            *Value
  )
/*++

Routine Description:

  Check Rivl function's argument

Arguments:

  ErrorBuff - Return the Error message when checking
  Arg       - The argument
  TypeName  - The type of the variable
  Value     - The value of the variable

Returns:

  TURE or FALSE

--*/
{
  INT8          *VarName;
  INT8          TargetName[MAX_VARNAME_LEN];
  BOOLEAN       IsArray;
  BOOLEAN       IsRefer;
  BOOLEAN       ShouldBePtr;
  BOOLEAN       IsPtr;
  UINT32        ValNum;
  INTERNAL_TYPE *InternalType;
  //
  // rivl_type       *e_type;
  // rivl_variable   *variable;
  //
  UINT32        ArrayNum;

  IsRefer     = FALSE;
  ShouldBePtr = FALSE;

  if (Arg[0] == '@' || Arg[0] == '&' || Arg[0] == '*') {
    //
    // all vraible begin with @&* should be considered as followed by var_name
    //
    VarName = Arg;
    if (VarName[0] == '&') {
      IsRefer = TRUE;
      VarName++;
    } else if (VarName[0] == '*') {
      ShouldBePtr = TRUE;
      VarName++;
    } else if (VarName[0] != '@') {
      sprintf (ErrorBuff, "Variable %s invalid", Arg);
      return FALSE;
    }

    VarName++;

    //
    // all variable begin with
    //
    if (FALSE == RivlSetVarVerifyVarName (
                  VarName,
                  ShouldBePtr,
                  TargetName,
                  &IsArray,
                  &ValNum,
                  &IsPtr
                  )) {
      sprintf (ErrorBuff, "Variable %s not defined", Arg);
      return FALSE;
    } else {
      //
      // check if the TargetName matched?
      //
      if ((IsRefer && strcmp (TypeName, "POINTER")) || ((!IsRefer) && strcmp (TargetName, TypeName))) {
        sprintf (ErrorBuff, "Variable %s: %s", VarName, TypeName);
        return FALSE;
      }

      strcat (Value, Arg);
      return TRUE;
    }
  } else {
    //
    // Only Internal_type can transfer value directly
    //
    InternalType = RivlInternalTypeFindByName (TypeName);
    if (NULL == InternalType) {
      sprintf (ErrorBuff, "external Type can't trasfer Value directly");
      return FALSE;
    } else {
      //
      // get value
      //
      ArrayNum = 1;
      if (!(InternalType->Validate (Arg, &ArrayNum, ErrorBuff, Value))) {
        sprintf (ErrorBuff, "Validate fail");
        return FALSE;
      } else {
        //
        // *value = '\0';
        // strcat (value, arg);
        //
        return TRUE;
      }
    }
  }
}
