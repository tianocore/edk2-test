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
  
    EmsRivlGetVar.c
    
Abstract:

    Implementation of RIVL TCL command GetVar

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "stdlib.h"
#include "EmsRivlUtil.h"
#include "EmsRivlType.h"
#include "EmsRpcMain.h"
#include "EmsRivlTclVar.h"

BOOLEAN
RivlTypeFindByVariableName (
  INT8              *Name,
  BOOLEAN           ShouldBePtr,
  INTERNAL_TYPE     **IType,
  RIVL_TYPE         **EType,
  BOOLEAN           *Array,
  BOOLEAN           *Index,
  UINT32            *Num,
  BOOLEAN           *IsPtr
  );

BOOLEAN
ParseBufferStringByIType (
  IN   Tcl_Interp        *Interp,
  IN   INT8              *String,
  IN   INTERNAL_TYPE     *IType,
  IN   BOOLEAN           IsArray,
  IN   BOOLEAN           Index,
  IN   UINT32            Num,
  IN   INT8              *Name,
  IN   INT8              *OrigName,
  IN   INT8              ArrayIndex
  );

BOOLEAN
ParseBufferStringByEType (
  IN   Tcl_Interp        *Interp,
  IN   INT8              *String,
  IN   RIVL_TYPE         *EType,
  IN   BOOLEAN           IsArray,
  IN   BOOLEAN           Index,
  IN   UINT32            Num,
  IN   INT8              *Name,
  IN   INT8              *OrigName,
  IN   INT8              ArrayIndex
  );

BOOLEAN
RivlGetVariableName (
  INT8                   *Name,
  INT8                   *VarName,
  BOOLEAN                *GetAddr,
  BOOLEAN                *ShouldBePtr,
  BOOLEAN                *ContainIndex,
  INT8                   *ArrayIndex
  );

BOOLEAN
ParseBufferStringAddr (
  Tcl_Interp         *Interp,
  INT8               *String,
  BOOLEAN            ShouldBePtr,
  INT8               *VarName,
  INT8               *OrigName
  );

INT32
TclGetVar (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GetVar" implementation routine  

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
  UINT8         VarName[MAX_VARNAME_LEN];
  INT8          Message[MAX_MESSAGE_LEN];
  INT8          *TypeName;
  INT8          *Name;
  INTERNAL_TYPE *TempIType;
  RIVL_TYPE     *TempEType;
  UINT32        Num;
  INT8          ArrayIndex;
  BOOLEAN       ContainIndex;
  BOOLEAN       IsArray;
  BOOLEAN       GetAddr;
  BOOLEAN       ShouldBePtr;
  BOOLEAN       IsPtr;
  INT32         Length;
  BOOLEAN       Pass;
  INT8          *Out;
  INT8          *Log;

  TempIType   = NULL;
  TempEType   = NULL;
  GetAddr     = FALSE;
  ShouldBePtr = FALSE;

  if (Argc != 2) {
    sprintf (ErrorBuff, "%s : Syntax error!", Argv[0]);
    goto ErrorExit;
  }

  Name = (INT8 *) Argv[1];

  if (FALSE == RivlGetVariableName (
                Name,
                VarName,
                &GetAddr,
                &ShouldBePtr,
                &ContainIndex,
                &ArrayIndex
                )) {
    goto ErrorExit;
  }

  if (Name[0] == '&') {
    Name++;
  }

  if (Name[0] == '*') {
    Name++;
  }

  IsArray = FALSE;
  if (FALSE == RivlTypeFindByVariableName (
                Name,
                ShouldBePtr,
                &TempIType,
                &TempEType,
                &IsArray,
                &ContainIndex,
                &Num,
                &IsPtr
                )) {
    sprintf (ErrorBuff, "%s : No varialbe %s exist!", Argv[0], Name);
    goto ErrorExit;
  }

  if (TempIType) {
    TypeName = TempIType->Name;
  } else {
    TypeName = TempEType ? TempEType->Name : NULL;
  }

  if (ShouldBePtr != IsPtr) {
    goto ErrorExit;
  }
  //
  // 1). Build message  2). sent Out 3). recv response
  //
  Message[0] = 0;
  strcpy (Message, "RIVL_GETVAR  ");
  if (GetAddr) {
    strcat (Message, "&");
  }

  if (ShouldBePtr) {
    strcat (Message, "*");
  }

  strcat (Message, "@");
  strcat (Message, Name);

  Length = strlen (Message);
  RpcSendMessage (Length, Message);
  Message[sizeof (INT32)] = 0;
  Length                  = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);

  if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) || (FALSE == Pass)) {
    sprintf (ErrorBuff, "EAS: GetVar %s failed!", Name);
    goto ErrorExit;
  }

  if (!RivlAddTclVarsByName (VarName)) {
    sprintf (ErrorBuff, "%s : RivlAddTclVarsByName %s failed!", Argv[0], VarName);
    printf ("here\n");
	goto ErrorExit;
  }

  if (GetAddr && Out) {
    ParseBufferStringAddr (Interp, Out, ShouldBePtr, VarName, VarName);
  } else {

    if (TempIType && Out) {
      ParseBufferStringByIType (
        Interp,
        Out,
        TempIType,
        IsArray,
        ContainIndex,
        Num,
        Name,
        VarName,
        ArrayIndex
        );
    }

    if (TempEType && Out) {
      if (VarName[0] == '*') {
        Name--;
      }

      ParseBufferStringByEType (
        Interp,
        Out,
        TempEType,
        IsArray,
        ContainIndex,
        Num,
        Name,
        VarName,
        ArrayIndex
        );
    }
  }
  //
  //  Tcl_AppendResult(interp, message, (char *) NULL);
  //
  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;

}

BOOLEAN
RivlTypeFindByVariableName (
  INT8              *Name,
  BOOLEAN           ShouldBePtr,
  INTERNAL_TYPE     **IType,
  RIVL_TYPE         **EType,
  BOOLEAN           *Array,
  BOOLEAN           *Index,
  UINT32            *Num,
  BOOLEAN           *IsPtr
  )
/*++

Routine Description:

  Find a Rivl type accroding to variable name

Arguments:

  Name          - The name of the variable
  ShouldBePtr   - whether the variable should be a poniter or not
  IType         - whether the variable is internal
  EType         - whether the variable is external
  Array         - return whether the members of variable is an array or not
  Index         - return whether the variable is an array or not
  Num           - return the array name
  IsPtr         - whether the variable is a pointer or not

Returns:

  TRUE or FALSE

--*/
{
  INT8          *PPointer;
  INT8          *HPointer;
  INTERNAL_TYPE *TempIType;
  RIVL_TYPE     *TempEType;
  RIVL_VARIABLE *Variable;
  UINT8         SubName[MAX_VARNAME_LEN];
  UINT8         VarName[MAX_VARNAME_LEN];
  RIVL_MEMBER   *member;
  BOOLEAN       ShouldStop;
  BOOLEAN       IsArray;
  UINT32        ArrayNum;

  *IsPtr    = FALSE;

  HPointer  = Name;
  PPointer  = Name;
  while (*PPointer && *PPointer != '.') {
    PPointer++;
  }

  strncpy (SubName, HPointer, (UINT32) (PPointer - HPointer));
  SubName[(UINT32) (PPointer - HPointer)] = '\0';

  IsArray = IsDefineArray (SubName, &ArrayNum, VarName);
  if (!IsArray && 0 == ArrayNum) {
    goto ErrorExit;
  }

  Variable = RivlVariableFindByName (VarName);
  if (Variable) {
    if (IsArray && (!Variable->IsArray)) {
      goto ErrorExit;
    }
    //
    // check *
    //
    if (ShouldBePtr && (!Variable->IsPtr || IsArray)) {
      return FALSE;
    }

    if (Variable->Internal) {
      *IType = Variable->IType;
    } else {
      *EType = Variable->EType;
    }

    *Num    = IsArray ? 1 : Variable->IsArray ? Variable->ArrayNum : 1;
    *Array  = Variable->IsArray;
    *IsPtr  = Variable->IsPtr;
    if (*PPointer && (!IsArray) && (Variable->IsArray)) {
      goto ErrorExit;
    }
  } else {
    return FALSE;
  }

  ShouldStop = FALSE;
  while (*PPointer) {
    PPointer++;
    HPointer = PPointer;

    if (ShouldStop) {
      goto ErrorExit;
    }

    while (*PPointer && (*PPointer != '.')) {
      PPointer++;
    }

    strncpy (SubName, HPointer, (UINT32) (PPointer - HPointer));
    SubName[(UINT32) (PPointer - HPointer)] = '\0';
    IsArray = IsDefineArray (SubName, &ArrayNum, VarName);
    if (0 == ArrayNum) {
      goto ErrorExit;
    }

    member = GetMemberFromName (*EType, VarName);
    if (NULL == member) {
      goto ErrorExit;
    }

    *Array = member->IsArray;

    if (IsArray && (!member->IsArray)) {
      goto ErrorExit;
    }

    TempIType = RivlInternalTypeFindByName (member->Type);
    if (TempIType) {
      *IType  = TempIType;
      *EType  = NULL;
    }

    TempEType = RivlTypeFindByName (member->Type);
    if (TempEType) {
      *EType  = TempEType;
      *IType  = NULL;
    }

    *Num = IsArray ? 1 : member->IsArray ? member->ArrayNum : 1;
    //
    // *is_ptr = *is_ptr?true:member->IsPtr;
    //
    if (*IType) {
      ShouldStop = TRUE;
    }

    if ((!IsArray) && (member->IsArray)) {
      ShouldStop = TRUE;
    }
  }

  *Index = IsArray;

  return TRUE;
ErrorExit:
  return FALSE;
}

BOOLEAN
ParseBufferStringByIType (
  IN   Tcl_Interp        *Interp,
  IN   INT8              *String,
  IN   INTERNAL_TYPE     *IType,
  IN   BOOLEAN           IsArray,
  IN   BOOLEAN           Index,
  IN   UINT32            Num,
  IN   INT8              *Name,
  IN   INT8              *OrigName,
  IN   INT8              ArrayIndex
  )
/*++

Routine Description:

  Parse buffer string use internal type

Arguments:

  Interp      - The TCL intepreter
  String      - The String should be parsed
  IType       - whether the result is internal
  IsArray     - whether the result is an array or not
  Index       - whether the variable is an array or not
  Num         - whether the variable is an array or not
  Name        - Return the name of variable
  OrigName    - The orignal name of variable
  ArrayIndex  - The index of array

Returns:

  TRUE

--*/
{
  INT8    *TempStr;
  INT8    *VarName;
  //
  // int8_t    *var_str;
  //
  UINT32  LoopIndex;

  TempStr = malloc (MAX_MESSAGE_LEN);
  VarName = malloc (2 * MAX_VARNAME_LEN);

  if ((!IsArray) || (IsArray && Index)) {
    IType->Convert (String, TempStr, 1);
    //
    //    printf  ("name: %s, val: %s\n", name, temp_str);
    //
    Tcl_SetVar (Interp, Name, TempStr, TCL_GLOBAL_ONLY);
    RivlAddTclVarByName (OrigName, Name);
    //
    //    printf  ("name1: %s, val: %s\n", name, temp_str);
    //
  } else {
    for (LoopIndex = 0; LoopIndex < Num; LoopIndex++) {
      sprintf (VarName, "%s(%d)", Name, LoopIndex);
      IType->Convert (&String[2 * LoopIndex * IType->Size], TempStr, 1);
      //
      //      printf ("name: %s, val: %s\n", var_name, temp_str);
      //
      Tcl_SetVar (Interp, VarName, TempStr, TCL_GLOBAL_ONLY);
      RivlAddTclVarByName (OrigName, VarName);
    }
  }

  free (TempStr);
  free (VarName);
  return TRUE;
}

BOOLEAN
ParseBufferStringByEType (
  IN   Tcl_Interp        *Interp,
  IN   INT8              *String,
  IN   RIVL_TYPE         *EType,
  IN   BOOLEAN           IsArray,
  IN   BOOLEAN           Index,
  IN   UINT32            Num,
  IN   INT8              *Name,
  IN   INT8              *OrigName,
  IN   INT8              ArrayIndex
  )
/*++

Routine Description:

  Parse buffer string use external type

Arguments:

  Interp      - The TCL intepreter
  String      - The String should be parsed
  IType       - whether the result is internal
  IsArray     - whether the result is an array or not
  Index       - whether the variable is an array or not
  Num         - whether the variable is an array or not
  Name        - Return the name of variable
  OrigName    - The orignal name of variable
  ArrayIndex  - The index of array

Returns:

  TRUE

--*/
{
  INT8          VarName[2 * MAX_VARNAME_LEN];
  UINT32        LoopIndex;
  INTERNAL_TYPE *TempIType;
  RIVL_TYPE     *TempEType;

  if ((!IsArray) || (IsArray && Index)) {
    for (LoopIndex = 0; LoopIndex < EType->MemberNum; LoopIndex++) {
      sprintf (VarName, "%s.%s", Name, EType->Members[LoopIndex].Name);
      TempIType = RivlInternalTypeFindByName (EType->Members[LoopIndex].Type);
      if (NULL != TempIType) {
        //
        // This member is Internal type
        //
        ParseBufferStringByIType (
          Interp,
          &String[2 * EType->Members[LoopIndex].Offset],
          TempIType,
          EType->Members[LoopIndex].IsArray,
          FALSE,
          EType->Members[LoopIndex].ArrayNum,
          VarName,
          OrigName,
          0
          );
      } else {
        TempEType = RivlTypeFindByName (EType->Members[LoopIndex].Type);
        if (NULL != TempEType) {
          //
          // printf ("External type member, %s.%s, %s array, index=%d\n",
          //    name, e_type->members[i].name,
          //    is_array?"is":"not", index);
          // This member is External type
          // sprintf(var_name, "%s.%s", name, e_type->members[i].name);
          //
          ParseBufferStringByEType (
            Interp,
            &String[2 * EType->Members[LoopIndex].Offset],
            TempEType,
            EType->Members[LoopIndex].IsArray,
            FALSE,
            EType->Members[LoopIndex].ArrayNum,
            VarName,
            OrigName,
            0
            );

        }
      }
    }
  } else {
    for (LoopIndex = 0; LoopIndex < Num; LoopIndex++) {
      sprintf (VarName, "%s(%d)", Name, LoopIndex);
      ParseBufferStringByEType (
        Interp,
        &String[2 * EType->Size * LoopIndex],
        EType,  //        e_type->members[i].IsArray,
        IsArray,
        TRUE,
        1,
        VarName,
        OrigName,
        0
        );
    }
  }

  return TRUE;
}

BOOLEAN
RivlGetVariableName (
  INT8                   *Name,
  INT8                   *VarName,
  BOOLEAN                *GetAddr,
  BOOLEAN                *ShouldBePtr,
  BOOLEAN                *ContainIndex,
  INT8                   *ArrayIndex
  )
/*++

Routine Description:

  Get Rivl variable name from a name string

Arguments:

  Name          - The name string
  VarName       - Return the variable name
  GetAddr       - Return whether the result is an address
  ShouldBePtr   - whether the variable is pointer
  ContainIndex  - Return whether the variable's name contain '('
  ArrayIndex    - Return the index of "(" in variable's name

Returns:

  TRUE or FALSE

--*/
{
  INT8    *PPointer;
  INT8    *Start;
  INT8    Temp[10];
  UINT32  Index;

  PPointer      = Name;

  *GetAddr      = FALSE;
  *ShouldBePtr  = FALSE;

  if (PPointer[0] == '&') {
    *GetAddr = TRUE;
    PPointer++;
  }

  if (PPointer[0] == '*') {
    *ShouldBePtr = TRUE;
    PPointer++;
  }
  //
  // variable name may be followed by '.' and '('
  //
  while (*PPointer && *PPointer != '.' && *PPointer != '(') {
    PPointer++;
  }

  VarName[0] = '\0';
  strncpy (VarName, Name, PPointer - Name);
  VarName[PPointer - Name] = '\0';

  if (*PPointer == '(') {
    *ContainIndex = TRUE;
    Temp[0]       = 0;
    PPointer++;
    Start = PPointer;
    while (*PPointer != ')') {
      PPointer++;
    }

    memcpy (Temp, Start, PPointer - Start);
    Temp[PPointer - Start] = 0;
    AsciiStringToUint32 (Temp, &Index);
    *ArrayIndex = Index;
  } else {
    *ContainIndex = FALSE;
    *ArrayIndex   = 0;
  }

  return TRUE;
}

BOOLEAN
ParseBufferStringAddr (
  Tcl_Interp         *Interp,
  INT8               *String,
  BOOLEAN            ShouldBePtr,
  INT8               *VarName,
  INT8               *OrigName
  )
/*++

Routine Description:

  Parse buffer string for address

Arguments:

  Interp        - The TCL intepreter
  String        - The string to be parsed
  ShouldBePtr   - whether the variable should contain '*'
  VarName       - Return the name of variable
  OrigName      - The orignal name of variable

Returns:

  TRUE or FALSE

--*/
{
  INTERNAL_TYPE *TempIType;
  INT8          Name[MAX_TCL_VARNAME_LEN];
  INT8          TempStr[20];
  //
  // int8_t              *var_str;
  //
  TempIType = RivlInternalTypeFindByName ("UINT32");
  if (!TempIType) {
    return FALSE;
  }

  Name[0] = '\0';
  strcat (Name, "&");
  if (ShouldBePtr) {
    strcat (Name, "*");
  }

  strcat (Name, VarName);

  TempIType->Convert (String, TempStr, 1);
  //
  //  printf("set %s  %s\n", name, temp_str);
  //
  Tcl_SetVar (Interp, Name, TempStr, TCL_GLOBAL_ONLY);
  RivlAddTclVarByName (OrigName, Name);
  return TRUE;
}
