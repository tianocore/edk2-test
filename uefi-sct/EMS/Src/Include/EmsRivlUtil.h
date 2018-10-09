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
  
    EmsRivlUtil.h
    
Abstract:

    Incude header files for RIVL utility functions

--*/

#ifndef _EMS_RIVL_UTIL_H_
#define _EMS_RIVL_UTIL_H_

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

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
;

#endif
