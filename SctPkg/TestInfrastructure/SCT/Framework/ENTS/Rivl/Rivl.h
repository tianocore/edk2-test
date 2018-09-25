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

  Rivl.h

Abstract:

  Remote Interface Validation Language definitions

--*/

#ifndef __RIVL_H__
#define __RIVL_H__

#include <Library/EntsLib.h>

#define RIVL_MAX_VARNAME_LEN      64
#define RIVL_MAX_TYPENAME_LEN     64

#define RIVL_VAR_ATTRIB_VARIABLE  1
#define RIVL_VAR_ATTRIB_REFERENCE 2
#define RIVL_VAR_ATTRIB_POINTER   3

#define RIVL_VAL_SIG              L'@'
#define RIVL_ADD_SIG              L'&'
#define RIVL_PTR_SIG              L'*'
#define RIVL_SEP_SIG              L" \t"

#define RIVL_VAR_FEATURE_INTERNAL 0x1
#define RIVL_VAR_FEATURE_EXTERNAL 0x2
#define RIVL_VAR_FEATURE_VARIABLE 0x10
#define RIVL_VAR_FEATURE_ADDRESS  0x20
#define RIVL_VAR_FEATURE_POINTER  0x40

#define RIVL_DEBUG_PRINT

#ifdef RIVL_DEBUG_PRINT
#define RIVL_DEBUG(a) SctPrint a
#else
#define RIVL_DEBUG(a)
#endif

typedef struct _RIVL_INTERNAL_TYPE {
  CHAR16  Type[RIVL_MAX_TYPENAME_LEN];
  UINT32  Size;
} RIVL_INTERNAL_TYPE;

typedef struct _RIVL_MEMBER {
  CHAR16  Name[RIVL_MAX_VARNAME_LEN];
  CHAR16  Type[RIVL_MAX_TYPENAME_LEN];
  UINT32  TypeSize;
  UINT32  ArrayNumber;
  UINT32  Offset;
} RIVL_MEMBER;

typedef struct _RIVL_TYPE {
  struct _RIVL_TYPE *Next;
  struct _RIVL_TYPE *Prev;
  CHAR16            Type[RIVL_MAX_TYPENAME_LEN];
  UINT32            Size;
  UINT32            MemberNumber;
  RIVL_MEMBER       *Member;
} RIVL_TYPE;

typedef struct _RIVL_VARIABLE {
  struct _RIVL_VARIABLE *Next;
  struct _RIVL_VARIABLE *Prev;
  CHAR16                Name[RIVL_MAX_VARNAME_LEN];
  CHAR16                Type[RIVL_MAX_TYPENAME_LEN];
  UINT32                TypeSize;
  UINT32                ArrayNumber;
  UINT32                Attribute;
  VOID                  *Address;
} RIVL_VARIABLE;

extern RIVL_INTERNAL_TYPE gRivlInternalTypeArray[];
extern RIVL_TYPE          *gRivlTypeList;
extern RIVL_VARIABLE      *gRivlVariableList;

//
// External function definition
//
EFI_STATUS
RivlAddRivlType (
  IN CHAR16                    *TypeBuf
  )
/*++

Routine Description:

  This func is attend to add RivlType to gRivlTypeList
  The format of the type buffer is :
  <TypeName> <TypeSize> <TypeMemberNumber> 
    (<MemberName> <MemberType> <MemberSize> <MemberOffset>) ...

Arguments:

  TypeBuf -  The buffer string of Type

Returns:

  EFI_INVALID_PARAMETER - Invalide parameter.
  EFI_OUT_OF_RESOURCES  - Memory allocation failed.
  EFI_SUCCESS           - Operation succeeded.

--*/
;

EFI_STATUS
RivlDelRivlType (
  IN CHAR16                    *TypeBuf
  )
/*++

Routine Description:

  This func is attend to delete RivlType from gRivlTypeList.

Arguments:

  TypeBuf     - The buffer string of Type, NULL means delete all.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

RIVL_TYPE                 *
SearchRivlType (
  IN CHAR16                    *Type
  )
/*++

Routine Description:

  This func is to search RivlType from gRivlTypeList.

Arguments:

  Type  - Type of RivlType.

Returns:

  The pointer of RivlType found successfully, NULL means not found

--*/
;

RIVL_INTERNAL_TYPE        *
SearchRivlInternalType (
  IN CHAR16                    *Type
  )
/*++

Routine Description:

  This func is to search RivlInternalType from gRivlInternalTypeArray.

Arguments:

  Type  - Type of RivlInternalType.

Returns:

  The pointer of RivlInternalType found successfully, NULL means not found

--*/
;

RIVL_MEMBER               *
SearchRivlMember (
  IN RIVL_TYPE                 *RivlType,
  IN CHAR16                    *Name
  )
/*++

Routine Description:

  This func is to search RivlMember from RivlType.

Arguments:

  RivlType  - Which RivlType to be found in.
  Name      - Name of RivlMember.

Returns:

  The pointer of RivlMember found successfully, NULL means not found

--*/
;

EFI_STATUS
RivlAddRivlVariable (
  IN CHAR16                    *VarBuf
  )
/*++

Routine Description:

  This func is attend to add RivlVariable to gRivlVariableList
  The format of the variable buffer is :
  <VariableName> <VariableType> <VariableSize> <VariableArrayNumber>

Arguments:

  VarBuf  - The buffer string of Variable.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  Others                - Some failure happened.
  
--*/
;

EFI_STATUS
RivlDelRivlVariable (
  IN CHAR16                    *VarBuf
  )
/*++

Routine Description:

  This func is attend to delete RivlVariable from gRivlVariableList.

Arguments:

  VarBuf  - The buffer string of Variable, NULL means delete all.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
RivlSetRivlVariable (
  IN CHAR16                    *VarBuf
  )
/*++

Routine Description:

  This func is attend to set the value of RivlVariable
  The format of the variable buffer is :
  1) <VariableName> <VariableValue>
  2) <VariableName> (<VariableValue>) ...
  3) <VariableName> (<MemberName> <VariableValue>) ...

Arguments:

  VarBuf  - The buffer string of Variable

Returns:

  EFI_INVALID_PARAMETER - Invalide parameter.
  EFI_OUT_OF_RESOURCES  - Memory allocation failed.
  EFI_SUCCESS           - Operation succeeded.

--*/
;

EFI_STATUS
RivlGetRivlVariable (
  IN CHAR16                    *VarBuf,
  IN OUT UINT32                *BufferSize,
  IN OUT CHAR16                *Buffer
  )
/*++

Routine Description:

  This func is attend to get the value of RivlVariable.

Arguments:

  VarBuf      - The buffer string of Variable.
  BufferSize  - The size of buffer to hold the value.
  Buffer      - The buffer to hold the value.

Returns:

  EFI_INVALID_PARAMETER - Invalide parameter.
  EFI_OUT_OF_RESOURCES  - Memory allocation failed.
  EFI_SUCCESS           - Operation succeeded.

--*/
;

RIVL_VARIABLE             *
SearchRivlVariable (
  IN CHAR16                    *Name
  )
/*++

Routine Description:

  This func is to search RivlVariable from gRivlVariableList.

Arguments:

  Name  - Name of RivlVariable.

Returns:

  The pointer of RivlVariable found successfully, NULL means not found.

--*/
;

EFI_STATUS
AdvancedSearchRivlVariable (
  IN CHAR16                    *Name,
  IN OUT RIVL_VARIABLE         **Variable,
  IN OUT UINT32                *Offset,
  IN OUT UINT32                *Length,
  IN OUT UINT32                *ArrayNumber,
  IN OUT VOID                  **Type,
  IN OUT UINT32                *Feature
  )
/*++

Routine Description:

  This func is to do an advanced search from the variable name
  The format of the variable is [&]@VarName[(Index)][.SubName[(Index)][...]

Arguments:

  Name        - Name of variable to be searched.
  Variable    - The first RivlVariable.
  Offset      - Offset of the last variable.
  Length      - Length of the last variable.
  ArrayNumber - ArrayNumber of the last variable.
  Type        - Type of the last variable.
  Feature     - Feature of this variable.

Returns:

  EFI_INVALID_PARAMETER - Invalide parameter.
  EFI_SUCCESS           - Operation succeeded.

--*/
;

EFI_STATUS
RivlCallRivlFunc (
  IN CHAR16                    *FuncBuf,
  IN OUT EFI_STATUS            *FuncStatus
  )
/*++

Routine Description:

  This func is attend to add RivlType to gRivlTypeList
  The format of the type buffer is :
    <FuncName> <Arg1> <Arg2> ...

Arguments:

  FuncBuf     - The buffer string of Func
  FuncStatus  - The return value of Func

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS           - Operation succeeded.

--*/
;

#endif // __RIVL_H__
