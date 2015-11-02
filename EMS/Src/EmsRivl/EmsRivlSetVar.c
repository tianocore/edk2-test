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
  
    EmsRivlSetVar.c
    
Abstract:

    Implementation of RIVL TCL command SetVar

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "stdlib.h"
#include "EmsRivlUtil.h"
#include "EmsRivlType.h"
#include "EmsRpcMain.h"

BOOLEAN
GetNameRemainFromStr (
  INT8        *VarStr,
  INT8        *Name,
  INT8        *Remain
  );

BOOLEAN
GetIndexMemberFromStr (
  INT8           *Remain,
  UINT32         *Pos,
  BOOLEAN        *IsIndexDefined,
  INT8           *MemberName,
  UINT32         *Index
  );

BOOLEAN
VerifyMemberValue (
  INT8                     *ErrorBuff,
  RIVL_MEMBER              *Member,
  INT8                     *MemberValue,
  BOOLEAN                  IsRefer,
  BOOLEAN                  IsPtr,
  INT8                     *Value
  );

BOOLEAN
RivlSetVarVerifyValue (
  IN  INT8             *ErrorBuff,
  IN  INT8             *ValStr,
  IN  INT8             *TypeName,
  IN  BOOLEAN          IsArray,
  IN  BOOLEAN          IsRefer,
  IN  BOOLEAN          IsPtr,
  IN  UINT32           ValNum,
  OUT INT8             *Value
  );

BOOLEAN
SetInternalTypeVar (
  INT8               *ErrorBuff,
  INT8               *ValStr,
  INTERNAL_TYPE      *IType,
  BOOLEAN            IsRefer,
  BOOLEAN            IsPtr,
  INT8               *Value
  );

BOOLEAN
SetInternalTypeArray (
  INT8               *ErrorBuff,
  INT8               *VarStr,
  INTERNAL_TYPE      *IType,
  BOOLEAN            IsRefer,
  BOOLEAN            IsPtr,
  UINT32             ValNum,
  INT8               *Value
  );

BOOLEAN
SetExternalTypeVarRef (
  INT8               *ErrorBuff,
  INT8               *VarStr,
  RIVL_TYPE          *EType,
  INT8               *Value,
  BOOLEAN            IsRefer,
  BOOLEAN            IsPtr
  );

BOOLEAN
SetExternalTypeArray (
  INT8               *ErrorBuff,
  INT8               *VarStr,
  RIVL_TYPE          *EType,
  UINT32             ValNum,
  INT8               *Value,
  BOOLEAN            IsRefer,
  BOOLEAN            IsPtr
  );

BOOLEAN
SetExternalTypeVarMember (
  INT8                 *ErrorBuff,
  INT8                 *ValStr,
  RIVL_TYPE            *EType,
  INT8                 *Value,
  BOOLEAN              IsRefer,
  BOOLEAN              IsPtr
  );

INT32
TclSetVar (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "SetVar" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8    ErrorBuff[MAX_ERRBUFF_LEN];
  INT8    TypeName[MAX_TYPENAME_LEN];
  INT8    Message[MAX_MESSAGE_LEN];
  INT8    *VarName;
  BOOLEAN IsArrayTemp1;
  BOOLEAN IsRefer;
  BOOLEAN ShouldBePtr;
  BOOLEAN IsPtr;
  UINT32  ValNum;
  INT32   Length;

  IsRefer     = FALSE;
  ShouldBePtr = FALSE;
  //
  // The following description is supported
  //      1). SetVar Var_Name {value}
  //      2). SetVar Var_Name {value1 value2 valu3 ...} # Array
  //      3). SetVar Var_Name {
  //            member1 : value1
  //            member2 : value2
  //            member3 : value3
  //            ......
  //          }
  // The format of Var_Name can be any of the following
  //      var_name
  //      var_name(index)
  //      var_name.Member
  //      var_name(index).Member
  //      var_name.Member(index)
  //      any valid combination of (var_name, index, Member)
  //      .......
  //
  //
  // argument counts must be 3
  //
  //
  // verify argv[1], var_name
  // check if the var is reference variable
  // check if the var is valid, and get it's type and array_num
  //
  VarName = (INT8 *) Argv[1];
  if (VarName[0] == '&') {
    IsRefer = TRUE;
    VarName = &VarName[1];
  } else if (VarName[0] == '*') {
    ShouldBePtr = TRUE;
    VarName     = &VarName[1];
  }

  if (FALSE == RivlSetVarVerifyVarName (
                VarName,
                ShouldBePtr,
                TypeName,
                &IsArrayTemp1,
                &ValNum,
                &IsPtr
                )) {
    sprintf (ErrorBuff, "%s Variable %s invalid", Argv[0], Argv[1]);
    goto ErrorExit;
  }

  Message[0] = '\0';
  strcat (Message, "RIVL_SETVAR ");

  if (IsRefer) {
    strcat (Message, "&");
  }

  if (ShouldBePtr) {
    strcat (Message, "*");
  }

  strcat (Message, "@");
  strcat (Message, VarName);
  strcat (Message, " ");

  //
  // vefiry argv[2], value
  // check if the value is valid, and put into mesasge
  //
  if (!RivlSetVarVerifyValue (
        ErrorBuff,
        (INT8 *) Argv[2],
        TypeName,
        IsArrayTemp1,
        IsRefer,
        IsPtr,
        ValNum,
        Message + sizeof (INT32) + strlen (Message + sizeof (INT32))
        )) {
    goto ErrorExit;
  }

  Length = strlen (Message);
  RpcSendMessage (Length, Message);
  Message[0]  = 0;
  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);

  //
  // Request EFI to do Var setting, wait for response, check operation result
  //
  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

BOOLEAN
RivlSetVarVerifyVarName (
  IN  INT8            *VarStr,
  IN  BOOLEAN         ShouldBePtr,
  OUT INT8            *TypeName,
  OUT BOOLEAN         *IsArray,
  OUT UINT32          *ValNum,
  OUT BOOLEAN         *IsPtr
  )
/*++

Routine Description:

  check if the variable name is valid get the type of the variable, 
  IsArray, and how much value should be input

Arguments:

  VarStr       - The variable string
  ShouldBePtr  - Whether the result should be pointer
  TypeName     - Return the type name
  IsArray      - Return whether the result is array
  ValNum       - Return the count of member if the variable is an arrary
  IsPtr        - Return whether the result is pointer

Returns:

  TRUE or FALSE

--*/
{
  INT8          Name[MAX_VARNAME_LEN];
  INT8          VarName[MAX_VARNAME_LEN];
  INT8          Remain[MAX_VARNAME_LEN];
  INT8          MemberName[MAX_VARNAME_LEN];
  INT8          *TypeNamePointer;
  BOOLEAN       IsArrayTemp;
  BOOLEAN       IsIndexDefined;
  UINT32        ArrayNum;
  UINT32        TempIndex;
  UINT32        TempValNum;
  RIVL_VARIABLE *Variable;
  RIVL_MEMBER   *Member;
  UINT32        MaxNumber;
  UINT32        Stop;
  UINT32        VarStrLen;
  BOOLEAN       IsArrayTemp1;

  Variable    = NULL;

  *IsArray    = FALSE;
  *IsPtr      = FALSE;
  *ValNum     = 0;
  TypeName[0] = '\0';

  //
  // get variable name from the raw var_str
  // check if the variable has been defined
  //
  if (FALSE == GetNameRemainFromStr (VarStr, Name, Remain)) {
    return FALSE;
  }

  Variable = RivlVariableFindByName (Name);
  if (NULL == Variable) {
    return FALSE;
  }
  //
  // If no Remain string, just set type->name and val_num
  //
  if (!Remain[0]) {
    if (ShouldBePtr && !Variable->IsPtr) {
      return FALSE;
    }

    TypeNamePointer = Variable->Internal ? Variable->IType->Name : Variable->EType->Name;
    *IsArray        = Variable->IsArray;
    *ValNum         = Variable->IsArray ? Variable->ArrayNum : GetMemberCount (TypeNamePointer);
    *IsPtr          = Variable->IsPtr;
    strcat (TypeName, TypeNamePointer);
    return TRUE;
  }

  if (IsDefineArray (VarStr, &ArrayNum, VarName) && ShouldBePtr) {
    return FALSE;
  }
  //
  // check the remaining str of the var_str
  //
  MaxNumber       = Variable->ArrayNum - 1;
  Stop            = 0;
  VarStrLen       = strlen (Remain);
  IsArrayTemp     = Variable->IsArray;
  TempValNum      = Variable->ArrayNum;
  TypeNamePointer = Variable->Internal ? Variable->IType->Name : Variable->EType->Name;
  //
  // l_is_ptr    = variable->IsPtr;
  //
  IsArrayTemp1 = Variable->IsArray;

  while (Stop < VarStrLen) {
    //
    // check index
    //
    if (FALSE == GetIndexMemberFromStr (
                  Remain,
                  &Stop,
                  &IsIndexDefined,
                  MemberName,
                  &TempIndex
                  )) {
      return FALSE;
    }

    if ((IsArrayTemp1 && !IsIndexDefined) || (!IsArrayTemp1 && IsIndexDefined)) {
      return FALSE;
    }

    if (IsArrayTemp1 && IsIndexDefined) {
      if (TempIndex >= (MaxNumber)) {
        return FALSE;
      }

      IsArrayTemp = FALSE;
      //
      // l_is_ptr   =
      //
      TempValNum = GetMemberCount (TypeNamePointer);
    }
    //
    // It's error if neither index nor member_name are defined in Remain
    //
    if (!IsIndexDefined && !MemberName[0]) {
      return FALSE;
    }
    //
    // If member_name is defined in Remain,
    //
    if (MemberName[0]) {
      Member = GetMemberFromType (TypeNamePointer, MemberName);
      if (NULL == Member) {
        return FALSE;
      }

      IsArrayTemp1    = Member->IsArray;
      MaxNumber       = Member->ArrayNum;
      TypeNamePointer = Member->Type;
      IsArrayTemp     = Member->IsArray;
      //
      // l_is_ptr    = Member->IsPtr;
      //
      TempValNum = Member->IsArray ? Member->ArrayNum : GetMemberCount (TypeNamePointer);
    }
  }

  if (Stop == VarStrLen) {
    *IsArray  = IsArrayTemp;
    *ValNum   = TempValNum;
    //
    // *is_ptr   = l_is_ptr;
    //
    strcat (TypeName, TypeNamePointer);
  }

  return TRUE;
}

BOOLEAN
GetIndexMemberFromStr (
  INT8           *Remain,
  UINT32         *Pos,
  BOOLEAN        *IsIndexDefined,
  INT8           *MemberName,
  UINT32         *Index
  )
/*++

Routine Description:

  Get the member from string

Arguments:

  Remain            - The string
  Pos               - The start position as input and end position as output
  IsIndexDefined    - Return whether the variable has member
  MemberName        - Return the member's name
  Index             - Return the Index of the member start

Returns:

  TRUE or FALSE

--*/
{
  INT8    IndexStr[10];
  //
  // max array number is 100000000
  //
  UINT32  VarLen;
  UINT32  LStart;
  UINT32  LStop;
  INT8    *PacketPointer;

  VarLen          = strlen (Remain);
  LStart          = *Pos;
  LStop           = LStart;

  *IsIndexDefined = FALSE;
  MemberName[0]   = '\0';
  *Index          = 0;

  if (LStart >= strlen (Remain)) {
    return FALSE;
  }
  //
  // the first character must be '.' or '('
  //
  if (Remain[LStart] != '.' && Remain[LStart] != '(') {
    return FALSE;
  }

  if (Remain[LStart] == '(') {
    //
    // get index
    //
    LStart++;
    LStop         = LStart;
    PacketPointer = Remain + LStop;
    while (LStop < (VarLen - 1) && Remain[LStop] >= 0x30 && Remain[LStop] <= 0x39) {
      LStop++;
    }

    if (LStop >= (VarLen) || Remain[LStop] != ')') {
      return FALSE;
    }
    //
    // get index
    //
    *IsIndexDefined = TRUE;
    strncpy (IndexStr, &Remain[LStart], (LStop - LStart));
    IndexStr[LStop - LStart - 1]  = '\0';
    *Index                        = atoi (IndexStr);

    if (LStop == (VarLen - 1)) {
      //
      // reach the end of the string
      //
      LStop++;
      *Pos = LStop;
      return TRUE;
    }

    LStop++;
  }
  //
  // not reach the end of string
  //
  LStart = LStop;
  if (Remain[LStart] != '.') {
    return FALSE;
  }
  //
  // get Member
  //
  LStop++;
  LStart = LStop;
  while (LStop < (VarLen) && Remain[LStop] != '(' && Remain[LStop] != '.') {
    LStop++;
  }

  strncpy (MemberName, Remain + LStart, LStop - LStart);
  MemberName[LStop - LStart]  = '\0';
  *Pos                        = LStop;

  return TRUE;
}

BOOLEAN
GetNameRemainFromStr (
  INT8        *VarStr,
  INT8        *Name,
  INT8        *Remain
  )
/*++

Routine Description:

  Get the name from remain string

Arguments:

  VarStr  - The string
  Name    - Return the got name
  Remain  - Return the remain string

Returns:

  TRUE or FALSE

--*/
{
  UINT32  Length;
  UINT32  Stop;

  Stop = 0;

  if (!VarStr) {
    return FALSE;
  }

  Length = strlen (VarStr);
  while (Stop < Length && VarStr[Stop] != 0 && VarStr[Stop] != '.' && VarStr[Stop] != '(') {
    Stop++;
  }

  strncpy (Name, VarStr, Stop);
  Name[Stop] = '\0';

  strncpy (Remain, VarStr + Stop, Length - Stop);
  Remain[Length - Stop] = '\0';

  return TRUE;
}

BOOLEAN
RivlSetVarVerifyValue (
  IN  INT8             *ErrorBuff,
  IN  INT8             *ValStr,
  IN  INT8             *TypeName,
  IN  BOOLEAN          IsArray,
  IN  BOOLEAN          IsRefer,
  IN  BOOLEAN          IsPtr,
  IN  UINT32           ValNum,
  OUT INT8             *Value
  )
/*++

Routine Description:

  Set a Rivl variable

Arguments:

  ErrorBuff - The buffer for error message
  ValStr    - The value string
  TypeName  - The type
  IsArray   - Whether to set an array variable
  IsRefer   - Whether to set a variable which pointer referenced
  IsPtr     - Whether to set a pointer variable
  ValNum    - The number of variable member if it is array
  Value     - Output the value

Returns:

  TRUE or FALSE

--*/
{
  INTERNAL_TYPE *IType;
  RIVL_TYPE     *EType;

  IType = RivlInternalTypeFindByName (TypeName);
  EType = RivlTypeFindByName (TypeName);

  if (IsArray) {
    if (IType) {
      //
      // Internal type array
      //
      return SetInternalTypeArray (ErrorBuff, ValStr, IType, IsRefer, IsPtr, ValNum, Value);
    } else if (EType) {
      //
      return SetExternalTypeArray (ErrorBuff, ValStr, EType, ValNum, Value, IsRefer, IsPtr);
    } else {
      return FALSE;
    }
  } else {
    if (IType) {
      return SetInternalTypeVar (ErrorBuff, ValStr, IType, IsRefer, IsPtr, Value);
    } else if (EType) {
      if (strstr (ValStr, ":")) {
        return SetExternalTypeVarMember (ErrorBuff, ValStr, EType, Value, IsRefer, IsPtr);
      } else {
        return SetExternalTypeVarRef (ErrorBuff, ValStr, EType, Value, IsRefer, IsPtr);
      }
    }
  }

  return TRUE;
}

BOOLEAN
SetInternalTypeVar (
  INT8               *ErrorBuff,
  INT8               *ValStr,
  INTERNAL_TYPE      *IType,
  BOOLEAN            IsRefer,
  BOOLEAN            IsPtr,
  INT8               *Value
  )
/*++

Routine Description:

  Set an internal type's variable

Arguments:

  ErrorBuff - The buffer for error message
  ValStr    - The string
  IType     - Whether to set an internal type's variable
  IsRefer   - Whether to set the variable which a pointer referenced
  IsPtr     - Whether to set a pointer type's variable
  Value     - The value to set

Returns:

  TRUE or FALSE

--*/
{
  INT8    TypeName[MAX_TYPENAME_LEN];
  INT8    *PacketPointer;
  BOOLEAN ValAddress;
  BOOLEAN ValBevariable;
  BOOLEAN ValShouldBePtr;
  BOOLEAN ValIsArray;
  INT32   ValNumber;
  BOOLEAN ValIsPtr;

  ValAddress      = FALSE;
  ValBevariable   = FALSE;
  ValShouldBePtr  = FALSE;
  ValNumber       = 1;

  if ((ValStr[0] == '@')) {
    PacketPointer   = &ValStr[1];
    ValShouldBePtr  = FALSE;
    ValBevariable   = TRUE;
  } else if (ValStr[0] == '&' && ValStr[1] == '@') {
    PacketPointer   = &ValStr[2];
    ValShouldBePtr  = FALSE;
    ValBevariable   = TRUE;
    ValAddress      = TRUE;
  } else if (ValStr[0] == '*' && ValStr[1] == '@') {
    PacketPointer   = &ValStr[2];
    ValShouldBePtr  = TRUE;
    ValBevariable   = TRUE;
  }

  if (ValBevariable) {
    if (!RivlSetVarVerifyVarName (
          PacketPointer,
          ValShouldBePtr,
          TypeName,
          &ValIsArray,
          &ValNumber,
          &ValIsPtr
          )) {
      sprintf (ErrorBuff, "Value: %s invalid", ValStr);
      return FALSE;
    }
    //
    // check type
    //
    if ((IsPtr && !(ValIsPtr ^ ValAddress)) || (strcmp (IType->Name, TypeName) && (strcmp (IType->Name, "POINTER")))) {
      return FALSE;
    }

    strcpy (Value, ValStr);
    return TRUE;
  } else {
    if (IsRefer) {
      if (InternalTypes[UINT32_TYPE].Validate (ValStr, &ValNumber, ErrorBuff, Value)) {
        return FALSE;
      }

      return TRUE;
    }

    if (!IType->Validate (ValStr, &ValNumber, ErrorBuff, Value)) {
      return FALSE;
    }
  }

  return TRUE;
}

BOOLEAN
SetInternalTypeArray (
  INT8               *ErrorBuff,
  INT8               *VarStr,
  INTERNAL_TYPE      *IType,
  BOOLEAN            IsRefer,
  BOOLEAN            IsPtr,
  UINT32             ValNum,
  INT8               *Value
  )
/*++

Routine Description:

  Set an array type's variable

Arguments:

  ErrorBuff - The buffer for error message
  ValStr    - The string
  IType     - Whether to set an internal type's variable
  IsRefer   - Whether to set the variable which a pointer referenced
  IsPtr     - Whether to set a pointer type's variable
  ValNum    - The number of array's member
  Value     - The value to set

Returns:

  TRUE or FALSE

--*/
{
  INT8    Item[MAX_STRING_LEN];
  UINT32  Pos;
  UINT32  ItemNum;
  UINT32  Len;

  Pos     = 0;
  ItemNum = 0;
  Len     = strlen (VarStr);

  while (Pos != Len) {
    Pos = GetNextSubStr (VarStr, Pos, Item);
    if (*Item) {
      ItemNum++;
      if (ItemNum > ValNum) {
        return FALSE;
      }
    } else {
      return TRUE;
    }

    if (!SetInternalTypeVar (ErrorBuff, Item, IType, IsRefer, IsPtr, Value + strlen (Value))) {
      return FALSE;
    }

    strcat (Value, " ");
  }

  return TRUE;
}

BOOLEAN
SetExternalTypeVarRef (
  INT8               *ErrorBuff,
  INT8               *ValStr,
  RIVL_TYPE          *EType,
  INT8               *Value,
  BOOLEAN            IsRefer,
  BOOLEAN            IsPtr
  )
/*++

Routine Description:

  Set an external type's variable which be referenced by pointer

Arguments:

  ErrorBuff - The buffer for error message
  ValStr    - The string
  EType     - Whether to set an external type's variable
  Value     - The value to set
  IsRefer   - Whether to set the variable which a pointer referenced
  IsPtr     - Whether to set a pointer type's variable

Returns:

  TRUE or FALSE

--*/
{
  INT8    TypeName[MAX_TYPENAME_LEN];
  INT8    *PacketPointer;
  BOOLEAN ValAddress;
  BOOLEAN ValBevariable;
  BOOLEAN ValShouldBePtr;
  BOOLEAN ValIsArray;
  INT32   ValNumber;
  BOOLEAN ValIsPtr;

  ValAddress      = FALSE;
  ValBevariable   = FALSE;
  ValShouldBePtr  = FALSE;

  if ((ValStr[0] == '@')) {
    PacketPointer   = &ValStr[1];
    ValShouldBePtr  = FALSE;
    ValBevariable   = TRUE;
  } else if (ValStr[0] == '&' && ValStr[1] == '@') {
    PacketPointer   = &ValStr[2];
    ValShouldBePtr  = FALSE;
    ValBevariable   = TRUE;
    ValAddress      = TRUE;
  } else if (ValStr[0] == '*' && ValStr[1] == '@') {
    PacketPointer   = &ValStr[2];
    ValShouldBePtr  = TRUE;
    ValBevariable   = TRUE;
  }

  if (ValBevariable) {
    if (!RivlSetVarVerifyVarName (
          PacketPointer,
          ValShouldBePtr,
          TypeName,
          &ValIsArray,
          &ValNumber,
          &ValIsPtr
          )) {
      sprintf (ErrorBuff, "Value: %s invalid", ValStr);
      return FALSE;
    }
    //
    // check type
    //
    if ((IsPtr && !(ValIsPtr ^ ValAddress)) || (strcmp (EType->Name, TypeName))) {
      sprintf (
        ErrorBuff,
        "%d ? %d ^ %d\n, %s ? t%s",
        IsPtr,
        ValIsPtr,
        ValAddress,
        EType->Name,
        TypeName
        );
      return FALSE;
    }

    strcpy (Value, ValStr);
    return TRUE;
  } else if (IsPtr) {
    INTERNAL_TYPE *IType;
    IType = RivlInternalTypeFindByName ("POINTER");
    if (!IType->Validate (ValStr, &ValNumber, ErrorBuff, Value)) {
      return FALSE;
    }

    return TRUE;
  }

  return TRUE;
}

BOOLEAN
SetExternalTypeArray (
  INT8               *ErrorBuff,
  INT8               *VarStr,
  RIVL_TYPE          *EType,
  UINT32             ValNum,
  INT8               *Value,
  BOOLEAN            IsRefer,
  BOOLEAN            IsPtr
  )
/*++

Routine Description:

  Set an external type's array

Arguments:

  ErrorBuff - The buffer for error message
  ValStr    - The string
  EType     - Whether to set an external type's variable
  ValNum    - The number of array's member
  Value     - The value to set
  IsRefer   - Whether to set the variable which a pointer referenced
  IsPtr     - Whether to set a pointer type's variable

Returns:

  TRUE or FALSE

--*/
{
  INT8    Item[MAX_STRING_LEN];
  UINT32  Pos;
  UINT32  ItemNum;
  UINT32  Len;

  Pos     = 0;
  ItemNum = 0;
  Len     = strlen (VarStr);

  while (Pos != Len) {
    Pos = GetNextSubStr (VarStr, Pos, Item);
    if (*Item) {
      ItemNum++;
      if (ItemNum > ValNum) {
        return FALSE;
      }
    } else {
      if (ItemNum == ValNum) {
        return TRUE;
      } else {
        return FALSE;
      }
      //
      // continue;
      //
    }

    if (!SetExternalTypeVarRef (ErrorBuff, Item, EType, Value + strlen (Value), IsRefer, IsPtr)) {
      return FALSE;
    }

    strcat (Value, " ");
  }

  return TRUE;
}

BOOLEAN
SetExternalTypeVarMember (
  INT8                 *ErrorBuff,
  INT8                 *ValStr,
  RIVL_TYPE            *EType,
  INT8                 *Value,
  BOOLEAN              IsRefer,
  BOOLEAN              IsPtr
  )
/*++

Routine Description:

  Set an internal type's array member

Arguments:

  ErrorBuff - The buffer for error message
  ValStr    - The string
  EType     - Whether to set an external type's variable
  Value     - The value to set
  IsRefer   - Whether to set the variable which a pointer referenced
  IsPtr     - Whether to set a pointer type's variable

Returns:

  TRUE or FALSE

--*/
{
  INT8        Line[MAX_STRING_LEN];
  INT8        MemberName[MAX_VARNAME_LEN];
  INT8        MemberValue[MAX_VARNAME_LEN];
  RIVL_MEMBER *Member;
  UINT32      Len;
  UINT32      Pos;

  Len = strlen (ValStr);
  Pos = 0;

  while (Pos != Len) {
    Pos = GetNextLine (ValStr, Pos, Line);
    if ('\0' == *Line) {
      continue;
    }
    //
    // Check format error of line, it should be
    //    membername: MemberValue
    //
    if (FALSE == GetNameValueFromLine (Line, MemberName, MemberValue)) {
      sprintf (ErrorBuff, "Format error in Line \"%s\"", Line);
      return FALSE;
    }
    //
    // Check if this Member exist in the type
    //
    Member = GetMemberFromName (EType, MemberName);
    if (NULL == Member) {
      sprintf (
        ErrorBuff,
        "No Member named \"%s\" in Type \"%s\"",
        MemberName,
        EType->Name
        );
      return FALSE;
    }
    //
    // Verify if the MemberValue is valid
    //
    strcat (Value, MemberName);
    strcat (Value, " ");

    if (FALSE == VerifyMemberValue (ErrorBuff, Member, MemberValue, IsRefer, IsPtr, Value + strlen (Value))) {
      sprintf (
        ErrorBuff,
        "Value %s for Member %s is invalid",
        MemberName,
        Member->Name
        );
    }

    strcat (Value, " ");

  }

  return TRUE;
}

BOOLEAN
VerifyMemberValue (
  INT8                     *ErrorBuff,
  RIVL_MEMBER              *Member,
  INT8                     *MemberValue,
  BOOLEAN                  IsRefer,
  BOOLEAN                  IsPtr,
  INT8                     *Value
  )
/*++

Routine Description:

  Verify the value of array's member

Arguments:

  ErrorBuff - The buffer for error message
  ValStr    - The member of array
  IsRefer   - Whether to set the variable which a pointer referenced
  IsPtr     - Whether to set a pointer type's variable
  Value     - The value to be verified

Returns:

  TRUE or FALSE

--*/
{
  INTERNAL_TYPE *IType;
  RIVL_TYPE     *EType;

  IType = RivlInternalTypeFindByName (Member->Type);

  if (IType) {
    return SetInternalTypeVar (
            ErrorBuff,
            MemberValue,
            IType,
            IsRefer,
            IsPtr,
            Value
            );
  } else {
    EType = RivlTypeFindByName (Member->Type);
    if (!EType) {
      return FALSE;
    }

    return SetExternalTypeVarRef (
            ErrorBuff,
            MemberValue,
            EType,
            Value,
            IsRefer,
            IsPtr
            );
  }

  return FALSE;
}
