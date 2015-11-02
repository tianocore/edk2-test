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
  
    EmsRivlUtil.c
    
Abstract:

    Implementation of RIVL utility functions

--*/

#include "EmsRivlMain.h"
#include "stdlib.h"
#include "EmsRivlVar.h"
#include "EmsRivlType.h"

BOOLEAN
IsDefineArray (
  INT8      *Str,
  UINT32    *ArrayNum,
  INT8      *Name
  )
/*++

Routine Description:

  whether define an array

Arguments:

  Str       - The 
  ArrayNum  - IN OUT : array num, if it is an array
              1, if it is not an array
              0, if any format error
  Name      - OUT: Array name, if it is an array

Returns:

  TRUE or FALSE

--*/
{
  UINT32  Index;
  UINT32  Len;

  Len = strlen (Str);

  if (')' == Str[Len - 1]) {
    //
    // Maybe it defines a Array
    //
    for (Index = 0; (Str[Index] != '(') && (Str[Index] != '\0'); Index++)
      ;
    if (0 == Index || Len == Index) {
      goto ErrorExit;
    }

    if ((Len - Index - 2) != AsciiStringToUint32 (&Str[Index + 1], ArrayNum)) {
      goto ErrorExit;
    }

    strncpy (Name, Str, Index);
    Name[Index] = '\0';
    return TRUE;
  }

  strcpy (Name, Str);
  *ArrayNum = 1;
  return FALSE;

ErrorExit:
  *Name     = '\0';
  *ArrayNum = 0;
  return FALSE;

}

UINT32
GetNextSubStr (
  IN   INT8   *Str,
  IN   UINT32 Pos,
  OUT  INT8   *SubStr
  )
/*++

Routine Description:

  Get sub-string from a string. The list separators 
  include ';', ' ', '\n', '\r', '\b', ','

Arguments:

  Str     - source string
  Pos     - Start position
  SubStr - sub string extracted

Returns:

  The stop position of the sub string in the source string

--*/
{
  UINT32  End;
  UINT32  Start;
  UINT32  Len;
  if ('\0' == Str[Pos]) {
    *SubStr = '\0';
    return Pos;
  }

  Start = Pos;
  for (Start = Pos; Str[Start]; Start++) {
    if (!
          (
          (Str[Start] == ' ') ||
        (Str[Start] == '\b') ||
        (Str[Start] == '\n') ||
        (Str[Start] == '\r') ||
        (Str[Start] == '\0') ||
        (Str[Start] == ';') ||
        (Str[Start] == ',') ||
        (Str[Start] == ':')
      )
          ) {
      break;
    }
  }

  for (End = Start; Str[End]; End++) {
    if ((Str[End] == ' ') ||
        (Str[End] == '\b') ||
        (Str[End] == '\n') ||
        (Str[End] == '\r') ||
        (Str[End] == '\0') ||
        (Str[End] == ';') ||
        (Str[End] == ',') ||
        (Str[Start] == ':')
        ) {
      break;
    }
  }

  Len = End - Start;
  if (0 == Len) {
    SubStr[0] = '\0';
    return End;
  }

  strncpy (SubStr, &(Str[Start]), Len);
  SubStr[Len] = '\0';
  return End;
}

UINT32
GetNextLine (
  IN   INT8   *Str,
  IN   UINT32 Pos,
  OUT  INT8   *Line
  )
/*++

Routine Description:

  Get a line form a string. 

Arguments:

  Str   - source string
  Pos   - Start position
  Line  - line extracted

Returns:

  The stop position of the sub string in the source string

--*/
{
  UINT32  End;
  UINT32  Start;
  UINT32  Len;
  if ('\0' == Str[Pos]) {
    *Line = '\0';
    return Pos;
  }

  Start = Pos;
  for (Start = Pos; Str[Start]; Start++) {
    if (!
          (
          (Str[Start] == ' ') ||
        (Str[Start] == '\b') ||
        (Str[Start] == '\n') ||
        (Str[Start] == '\r') ||
        (Str[Start] == '\0')
      )
          ) {
      break;
    }
  }

  for (End = Start; Str[End]; End++) {
    if ((Str[End] == '\n') || (Str[End] == '\r') || (Str[End] == '\0')) {
      break;
    }
  }

  Len = End - Start;
  if (0 == Len) {
    *Line = '\0';
    return End;
  }

  strncpy (Line, &(Str[Start]), Len);
  Line[Len] = '\0';
  return End;
}

BOOLEAN
GetNameValueFromLine (
  IN    INT8   *Line,
  OUT   INT8   *Name,
  OUT   INT8   *Value
  )
/*++

Routine Description:

  Get the name&value pair for a line string.

Arguments:

  Line  - source string
  Name  - member name extracted
  Value - member value extracted

Returns:

  TRUE or FALSE

--*/
{
  UINT32  End;
  UINT32  Start;
  UINT32  Len;

  Start = 0;
  for (Start = 0; Line[Start]; Start++) {
    if (!((Line[Start] == ' ') || (Line[Start] == '\b') || (Line[Start] == '\0'))) {
      break;
    }
  }

  for (End = Start; Line[End]; End++) {
    if ((Line[End] == ' ') || (Line[End] == '\b') || (Line[End] == ':')) {
      break;
    }
  }

  Len = End - Start;
  if (0 == Len) {
    *Name   = '\0';
    *Value  = '\0';
    return FALSE;
  }

  strncpy (Name, &(Line[Start]), Len);
  Name[Len] = '\0';

  for (Start = End; Line[Start]; Start++) {
    if (!((Line[Start] == ' ') || (Line[Start] == '\b') || (Line[Start] == '\0') || (Line[Start] == ':'))) {
      break;
    }
  }

  for (End = Start; Line[End]; End++) {
    if ((Line[End] == ' ') || (Line[End] == '\b') || (Line[End] == '\0')) {
      break;
    }
  }

  Len = End - Start;
  if (0 == Len) {
    *Name   = '\0';
    *Value  = '\0';
    return FALSE;
  }

  strncpy (Value, &(Line[Start]), Len);
  Value[Len] = '\0';
  return TRUE;
}

BOOLEAN
GetNameOptValueFromLine (
  IN    INT8        *Line,
  OUT   INT8        **Name,
  OUT   BOOLEAN     *IsValueDefined,
  OUT   INT8        **Value
  )
/*++

Routine Description:

  Get the name&option value pair for a line string.

Arguments:

  Line              - source string
  Name              - member name extracted
  IsValueDefined    - whether the value is defined
  Value             - member value extracted

Returns:

  TRUE or FALSE

--*/
{
  UINT32  End;
  UINT32  Start;
  UINT32  Len;

  Start = 0;
  for (Start = 0; Line[Start]; Start++) {
    if (!((Line[Start] == ' ') || (Line[Start] == '\b') || (Line[Start] == '\0'))) {
      break;
    }
  }

  for (End = Start; Line[End]; End++) {
    if ((Line[End] == ' ') || (Line[End] == '\b') || (Line[End] == ':')) {
      break;
    }
  }

  Len = End - Start;
  if (0 == Len) {
    *Name   = NULL;
    *Value  = '\0';
    return FALSE;
  }

  *Name     = &Line[Start];
  Line[End] = '\0';

  for (Start = End + 1; Line[Start]; Start++) {
    if (!((Line[Start] == ' ') || (Line[Start] == '\b') || (Line[Start] == '\0') || (Line[Start] == ':'))) {
      break;
    }
  }

  for (End = Start; Line[End]; End++) {
    if ((Line[End] == ' ') || (Line[End] == '\b') || (Line[End] == '\0')) {
      break;
    }
  }

  Len = End - Start;
  if (0 == Len) {
    *IsValueDefined = FALSE;
    return TRUE;;
  }

  *IsValueDefined = TRUE;
  *Value          = &Line[Start];
  Line[End]       = '\0';
  return TRUE;
}

VOID_P
StripString (
  IN    INT8   *Src,
  OUT   INT8   *Dst
  )
/*++

Routine Description:

  Strip the spaces at the head and tail of the string

Arguments:

  Src - source string
  Dst - destination string

Returns:

  None

--*/
{
  UINT32  End;
  UINT32  Start;
  UINT32  Len;

  Start = 0;
  for (Start = 0; Src[Start]; Start++) {
    if (!((Src[Start] == ' ') || (Src[Start] == '\b') || (Src[Start] == '\0'))) {
      break;
    }
  }

  Len = strlen (Src);
  for (End = Len; End > 0; End--) {
    if (!((Src[End - 1] == ' ') || (Src[End - 1] == '\b'))) {
      break;
    }
  }

  Len = End - Start;
  if (0 == Len) {
    *Dst = '\0';
    return ;
  }

  strncpy (Dst, &(Src[Start]), Len);
  Dst[Len] = '\0';
  return ;
}

RIVL_MEMBER *
GetMemberFromName (
  IN RIVL_TYPE *EType,
  IN INT8      *Name
  )
/*++

Routine Description:

  Get the pointer to member structure using member's name

Arguments:

  EType   - The user defined type 
  Name    - the member's name

Returns:

  The pointer to the corresponding member

--*/
{
  UINT32      Index;
  UINT32      MemberNum;
  RIVL_MEMBER *member;

  MemberNum = EType->MemberNum;
  for (Index = 0; Index < MemberNum; Index++) {
    member = &(EType->Members[Index]);
    if (0 == strcmp (Name, member->Name)) {
      return member;
    }
  }

  return NULL;
}

BOOLEAN
AddMemberValue (
  IN   RIVL_VARIABLE *Variable,
  IN   INT8          *Name,
  IN   INT8          *Value
  )
/*++

Routine Description:

  Add a name/value pairs into 

Arguments:

  Variable  - the pointer to variable
  Name      - the member's name
  Value     - its value

Returns:

  false, any error occurs

--*/
{
  UINT32              Index;
  UINT32              MemberNum;
  RIVL_VARIABLE_VALUE *member_value;

  member_value = NULL;
  if (NULL == Variable->EType) {
    return FALSE;
  }

  MemberNum = Variable->IsArray ? Variable->ArrayNum : Variable->EType->MemberNum;

  for (Index = 0; Index < MemberNum; Index++) {
    member_value = &(Variable->Value[Index]);
    if (0 == strcmp (Name, member_value->Name)) {
      break;
    }
  }

  if (Index == MemberNum) {
    return FALSE;
  }

  if (member_value->Value) {
    free (member_value->Value);
  }

  member_value->Value = _strdup (Value);
  return TRUE;
}

BOOLEAN
CheckVariableAttribute (
  IN   RIVL_VARIABLE    *Variable,
  IN   BOOLEAN          Internal,
  IN   INTERNAL_TYPE    *IType,
  IN   RIVL_TYPE        *EType,
  IN   BOOLEAN          IsArray,
  IN   BOOLEAN          ArrayNum
  )
/*++

Routine Description:

  Check the variable's attribute

Arguments:

  Variable  - The variable to be checked
  Internal  - Point out that whether the variable is internal type
  IType     - Used to Check internal type
  EType     - Used to Check external type
  IsArray   - Used to Check array type
  ArrayNum  - Used to Check the number of array's member

Returns:

  TRUE or FALSE

--*/
{
  if (Variable->Internal != Internal) {
    return FALSE;
  }

  if (Internal) {
    if (IType != Variable->IType) {
      return FALSE;
    }
  } else {
    if (EType != Variable->EType) {
      return FALSE;
    }
  }

  if (Variable->IsArray != IsArray) {
    return FALSE;
  }

  if (Variable->ArrayNum != ArrayNum) {
    return FALSE;
  }

  return TRUE;
}

BOOLEAN
IsVariableMatchType (
  INT8          *VarName,
  UINT32        VarNum,
  INT8          *TypeName
  )
/*++

Routine Description:

  Check the variable's type is correct

Arguments:

  VarName  - The variable name
  VarNum   - The variable number
  TypeName - The type name

Returns:

  TRUE or FALSE

--*/
{
  RIVL_VARIABLE *Variable;
  INT8          *t_name;

  Variable = RivlVariableFindByName (VarName);
  if (NULL == Variable) {
    return FALSE;
  } else {
    t_name = Variable->Internal ? Variable->IType->Name : Variable->EType->Name;
    return Variable->ArrayNum == VarNum || 0 == strcmp (t_name, TypeName);
  }

  return TRUE;
}

UINT32
GetMemberCount (
  INT8        *TypeName
  )
/*++

Routine Description:

  Get the count of array's member

Arguments:

  TypeName - The name of type

Returns:

  1 if internal type
  0 if not define the type
  return the member's number

--*/
{
  RIVL_TYPE     *EType;
  INTERNAL_TYPE *IType;

  IType = RivlInternalTypeFindByName (TypeName);
  if (IType) {
    return 1;
  }

  EType = RivlTypeFindByName (TypeName);
  if (EType) {
    return EType->MemberNum;
  } else {
    return 0;
  }
}

RIVL_MEMBER *
GetMemberFromType (
  INT8        *TypeName,
  INT8        *MemberName
  )
/*++

Routine Description:

  Get member accroding to type

Arguments:

  TypeName   - The type's name
  MemberName - The member's name

Returns:

  The RIVL's member

--*/
{
  INTERNAL_TYPE *IType;
  RIVL_TYPE     *EType;

  IType = RivlInternalTypeFindByName (TypeName);
  if (IType) {
    return NULL;
  }

  EType = RivlTypeFindByName (TypeName);
  return GetMemberFromName (EType, MemberName);
}

BOOLEAN
CheckVariableType (
  INT8            *VarStr,
  INTERNAL_TYPE   *IType,
  RIVL_TYPE       *EType
  )
/*++

Routine Description:

  Check the variable's type

Arguments:

  VarStr - The source string
  IType  - Used to check internal type
  EType  - Used to check external type

Returns:

  TRUE or FALSE

--*/
{
  RIVL_VARIABLE *Variable;

  Variable = RivlVariableFindByName (VarStr);
  if (!Variable) {
    return FALSE;
  }

  if (Variable->Internal) {
    if (!IType || 0 != strcmp (Variable->IType->Name, IType->Name)) {
      return FALSE;
    }
  } else {
    if (!EType || 0 != strcmp (Variable->EType->Name, EType->Name)) {
      return FALSE;
    }
  }

  return TRUE;
}

BOOLEAN
CheckVariableTypeAttr (
  INT8               *VarStr,
  BOOLEAN            IsPtr,
  INTERNAL_TYPE      *IType,
  RIVL_TYPE          *EType
  )
/*++

Routine Description:

  Check the attribute of variable's type

Arguments:

  VarStr - The source string
  IsPtr  - Used to check pointer type
  IType  - Used to check internal type
  EType  - Used to check external type

Returns:

  TRUE or FALSE

--*/
{
  RIVL_VARIABLE *Variable;

  Variable = RivlVariableFindByName (VarStr);
  if (!Variable) {
    return FALSE;
  }
  //
  // printf ("check_variable_type_attr:%d ? %d\n", variable->IsPtr, is_ptr);
  // check attribute of is_ptr
  //
  if (Variable->IsPtr != IsPtr) {
    return FALSE;
  }

  if (Variable->Internal) {
    if (!IType || 0 != strcmp (Variable->IType->Name, IType->Name)) {
      return FALSE;
    }
  } else {
    if (!EType || 0 != strcmp (Variable->EType->Name, EType->Name)) {
      return FALSE;
    }
  }

  return TRUE;
}

BOOLEAN
CheckRefVariableAndType (
  INT8            *VarStr,
  INTERNAL_TYPE   *IType,
  RIVL_TYPE       *EType
  )
/*++

Routine Description:

  Check the variable and its type which be reference

Arguments:

  VarStr - The source string
  IType  - Used to check internal type
  EType  - Used to check external type

Returns:

  TRUE or FALSE

--*/
{
  RIVL_VARIABLE *Variable;

  Variable = RivlVariableFindByName (VarStr);
  if (!Variable) {
    return FALSE;
  }
  //
  // check if this variable is reference
  //
  if (!Variable->IsRefer) {
    return FALSE;
  }
  //
  // check type
  //
  if (Variable->Internal) {
    if (!IType || 0 != strcmp (Variable->IType->Name, IType->Name)) {
      return FALSE;
    }
  } else {
    if (!EType || 0 != strcmp (Variable->EType->Name, EType->Name)) {
      return FALSE;
    }
  }

  return TRUE;
}
