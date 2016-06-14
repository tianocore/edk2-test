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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  RivlVariable.c

Abstract:

  Remote Interface Validation Language Variable implementation

--*/

#include "SctLib.h"
#include "Rivl.h"
#include "RivlVariable.h"
#include "RivlType.h"

#define MULTIPLIER  4

RIVL_VARIABLE *gRivlVariableList;

//
// Internal functions
//
UINT32
GetSizeFromTypeList (
  IN CHAR16                    *Type
  );

CHAR16        *
my_strtok_line (
  CHAR16       *s,
  const CHAR16 *ct
  );

CHAR16        *
my_strtok_field (
  CHAR16       *s,
  const CHAR16 *ct
  );

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
{
  EFI_STATUS  Status;
  CHAR16      *Name;
  CHAR16      *Type;
  CHAR16      *TotalSizeStr;
  UINTN       TotalSize;
  CHAR16      *ArrayNumberStr;
  UINTN       ArrayNumber;
  UINT32      Attribute;
  INTN        Index;

  //
  // Conformance check
  //
  if (VarBuf == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Seperate the VarBuf
  //
  Name            = strtok_line (VarBuf, RIVL_SEP_SIG);
  Type            = strtok_line (NULL, RIVL_SEP_SIG);
  TotalSizeStr    = strtok_line (NULL, RIVL_SEP_SIG);
  ArrayNumberStr  = strtok_line (NULL, RIVL_SEP_SIG);

  //
  // Conformance check
  //
  if ((Name == NULL) || (Type == NULL) || (TotalSizeStr == NULL) || (ArrayNumberStr == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Convert string to number
  //
  Index = EntsStrToUINTN (TotalSizeStr, &TotalSize);
  if (Index == -1) {
    return EFI_INVALID_PARAMETER;
  }

  Index = EntsStrToUINTN (ArrayNumberStr, &ArrayNumber);
  if (Index == -1) {
    return EFI_INVALID_PARAMETER;
  }

  switch (Name[0]) {
  case RIVL_ADD_SIG:
    Name++;
    Attribute = RIVL_VAR_ATTRIB_REFERENCE;
    break;

  case RIVL_PTR_SIG:
    Name++;
    Attribute = RIVL_VAR_ATTRIB_POINTER;
    break;

  default:
    Attribute = RIVL_VAR_ATTRIB_VARIABLE;
    break;
  }
  //
  // Add Rivl Variable
  //
  Status = AddRivlVariable (
            Name,
            Type,
            (UINT32) TotalSize,
            (UINT32) ArrayNumber,
            Attribute
            );

  return Status;
}

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
{
  CHAR16      *Name;

  //
  // If buf is NULL, delete all variable
  //
  if (VarBuf == NULL) {
    DelRivlAllVariable ();
    return EFI_SUCCESS;
  }
  //
  // Del Rivl Variable
  //
  Name = strtok_line (VarBuf, RIVL_SEP_SIG);
  if (Name != NULL) {
    DelRivlVariable (Name);
  }

  while (Name != NULL) {
    Name = strtok_line (NULL, RIVL_SEP_SIG);
    if (Name != NULL) {
      DelRivlVariable (Name);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
AddRivlVariable (
  IN CHAR16                    *Name,
  IN CHAR16                    *Type,
  IN UINT32                    TotalSize,
  IN UINT32                    ArrayNumber,
  IN UINT32                    Attribute
  )
/*++

Routine Description:

  This func is to add RivlVariable to gRivlVariableList.

Arguments:

  Name        - Type of RivlVariable.
  Type        - Type of RivlVariable.
  TotalSize   - TotalSize of RivlVariable.
  ArrayNumber - ArrayNumber of RivlVariable.
  Attribute   - Attribute of RivlVariable.

Returns:

  EFI_ALREADY_STARTED   - Rivil type already existed.
  EFI_OUT_OF_RESOURCES  - Memory allocation failed.
  EFI_INVALID_PARAMETER - Invalide parameter.
  EFI_SUCCESS           - Operation succeeded.
  
--*/
{
  RIVL_VARIABLE *NewRivlVariable;
  RIVL_VARIABLE *OldRivlVariable;

  //
  // Create node
  //
  NewRivlVariable = EntsAllocatePool (sizeof (RIVL_VARIABLE));
  if (NewRivlVariable == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SctZeroMem (NewRivlVariable, sizeof (RIVL_VARIABLE));

  //
  // Fill Name
  //
  SctStrCpy (NewRivlVariable->Name, Name);

  //
  // Fill Type
  //
  SctStrCpy (NewRivlVariable->Type, Type);

  //
  // Fill ArrayNumber
  //
  NewRivlVariable->ArrayNumber = ArrayNumber;

  //
  // Fill TypeSize
  //
  NewRivlVariable->TypeSize = GetSizeFromTypeList (Type);
  if ((NewRivlVariable->TypeSize == 0) || (TotalSize != NewRivlVariable->TypeSize * ArrayNumber)) {
    EntsFreePool (NewRivlVariable);
    return EFI_INVALID_PARAMETER;
  }
  //
  // Fill Attribute
  //
  NewRivlVariable->Attribute = Attribute;

  //
  // Fill Address
  //
  switch (Attribute) {
  case RIVL_VAR_ATTRIB_VARIABLE:
    NewRivlVariable->Address = EntsAllocatePool (TotalSize);
    if (NewRivlVariable->Address == NULL) {
      EntsFreePool (NewRivlVariable);
      return EFI_OUT_OF_RESOURCES;
    }

    SctZeroMem (NewRivlVariable->Address, TotalSize);
    break;

  case RIVL_VAR_ATTRIB_REFERENCE:
    NewRivlVariable->Address = NULL;
    break;

  case RIVL_VAR_ATTRIB_POINTER:
    NewRivlVariable->Address = EntsAllocatePool (sizeof (VOID *));
    if (NewRivlVariable->Address == NULL) {
      EntsFreePool (NewRivlVariable);
      return EFI_OUT_OF_RESOURCES;
    }

    SctZeroMem (NewRivlVariable->Address, sizeof (VOID *));
    break;

  default:
    break;
  }
  //
  // Duplicate check
  //
  OldRivlVariable = SearchRivlVariable (Name);
  if (OldRivlVariable != NULL) {
    RIVL_DEBUG ((L"Duplicated Variable - %s\n", Name));
    EntsFreePool (NewRivlVariable->Address);
    EntsFreePool (NewRivlVariable);
    return EFI_ALREADY_STARTED;
  }
  //
  // Add to Variable List
  //
  OldRivlVariable       = gRivlVariableList;
  gRivlVariableList     = NewRivlVariable;
  NewRivlVariable->Next = OldRivlVariable;
  if (OldRivlVariable != NULL) {
    OldRivlVariable->Prev = NewRivlVariable;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
DelRivlVariable (
  IN CHAR16                    *Name
  )
/*++

Routine Description:

  This func is to delete RivlVariable from gRivlVariableList.

Arguments:

  Name  - Type of RivlVariable.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_NOT_FOUND         - The specified type cannot be found.
  EFI_SUCCESS           - Operation succeeded.

--*/
{
  RIVL_VARIABLE *OldRivlVariable;

  if (Name == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Search the node
  //
  OldRivlVariable = SearchRivlVariable (Name);
  if (OldRivlVariable == NULL) {
    return EFI_NOT_FOUND;
  }

  if (OldRivlVariable->Prev != NULL) {
    OldRivlVariable->Prev->Next = OldRivlVariable->Next;
  }

  if (OldRivlVariable->Next != NULL) {
    OldRivlVariable->Next->Prev = OldRivlVariable->Prev;
  }

  if (gRivlVariableList == OldRivlVariable) {
    gRivlVariableList = OldRivlVariable->Next;
  }
  //
  // Free the node
  //
  switch (OldRivlVariable->Attribute) {
  case RIVL_VAR_ATTRIB_VARIABLE:
  case RIVL_VAR_ATTRIB_POINTER:
    if (OldRivlVariable->Address != NULL) {
      EntsFreePool (OldRivlVariable->Address);
    }
    break;

  case RIVL_VAR_ATTRIB_REFERENCE:
    OldRivlVariable->Address = NULL;
    break;

  default:
    break;
  }

  EntsFreePool (OldRivlVariable);

  return EFI_SUCCESS;
}

EFI_STATUS
DelRivlAllVariable (
  VOID
  )
/*++

Routine Description:

  This func is to delete all RivlVariable from gRivlVariableList.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  RIVL_VARIABLE *OldRivlVariable;

  OldRivlVariable = gRivlVariableList;
  while (OldRivlVariable != NULL) {
    gRivlVariableList = gRivlVariableList->Next;

    //
    // Free node
    //
    switch (OldRivlVariable->Attribute) {
    case RIVL_VAR_ATTRIB_VARIABLE:
    case RIVL_VAR_ATTRIB_POINTER:
      if (OldRivlVariable->Address != NULL) {
        EntsFreePool (OldRivlVariable->Address);
      }
      break;

    case RIVL_VAR_ATTRIB_REFERENCE:
      OldRivlVariable->Address = NULL;
      break;

    default:
      break;
    }

    EntsFreePool (OldRivlVariable);

    OldRivlVariable = gRivlVariableList;
  }

  return EFI_SUCCESS;
}

RIVL_VARIABLE *
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
{
  RIVL_VARIABLE *RivlVariable;

  if (Name == NULL) {
    return NULL;
  }

  RivlVariable = gRivlVariableList;
  while (RivlVariable != NULL) {
    if (SctStrCmp (RivlVariable->Name, Name) == 0) {
      //
      // Find it
      //
      return RivlVariable;
    }

    RivlVariable = RivlVariable->Next;
  }

  return NULL;
}

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
{
  CHAR16              *VarName;
  RIVL_VARIABLE       *RivlVariable;
  UINT32              Offset;
  UINT32              Length;
  UINT32              ArrayNumber;
  VOID                *Type;
  UINT32              Feature;
  CHAR16              *NameBuffer;
  CHAR16              *ValueBuffer;
  UINT32              VarIndex;
  EFI_STATUS          Status;
  CHAR16              *TmpBuf;
  UINT32              TypeSize;
  RIVL_VARIABLE       *RivlBufferVariable;
  UINT32              BufferOffset;
  UINT32              BufferLength;
  UINT32              BufferArrayNumber;
  VOID                *BufferType;
  UINT32              BufferFeature;
  RIVL_INTERNAL_TYPE  *RivlInternalType;
  RIVL_TYPE           *RivlType;
  RIVL_MEMBER         *RivlMember;
  INTN                Result;
  UINT8               **VarBaseAddress;
  UINT8               **BufferVarBaseAddress;

  //
  // Conformance check
  //
  if (VarBuf == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  TmpBuf = EntsStrDuplicate (VarBuf);
  if (TmpBuf == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  VarName = strtok_line (VarBuf, RIVL_SEP_SIG);

  //
  // Advanced Search the Variable
  //
  Status = AdvancedSearchRivlVariable (
            VarName,
            &RivlVariable,
            &Offset,
            &Length,
            &ArrayNumber,
            &Type,
            &Feature
            );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  if ((Feature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
    VarBaseAddress = (UINT8 **) &RivlVariable->Address;
  } else {
    VarBaseAddress = RivlVariable->Address;
  }
  //
  // It is address
  //
  if ((Feature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
    //
    // Get the Value
    //
    ValueBuffer = strtok_line (NULL, RIVL_SEP_SIG);
    if (ValueBuffer == NULL) {
      Status = EFI_INVALID_PARAMETER;
      goto Done;
    }

    if ((ValueBuffer[0] != RIVL_ADD_SIG) && (ValueBuffer[0] != RIVL_PTR_SIG) && (ValueBuffer[0] != RIVL_VAL_SIG)) {
      //
      // Raw data
      //
      StringToMem (
        ValueBuffer,
        VarBaseAddress,
        sizeof (VOID *)
        );
      goto Done;
    }
    //
    // Advanced Search the Variable
    //
    Status = AdvancedSearchRivlVariable (
              ValueBuffer,
              &RivlBufferVariable,
              &BufferOffset,
              &BufferLength,
              &BufferArrayNumber,
              &BufferType,
              &BufferFeature
              );
    if (EFI_ERROR (Status)) {
      goto Done;
    }

    if ((BufferFeature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
      BufferVarBaseAddress = (UINT8 **)&(RivlBufferVariable->Address);
    } else {
      BufferVarBaseAddress = RivlBufferVariable->Address;
    }
    //
    // Check the Value
    //
    if ((BufferFeature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
      Result = (INTN) (*BufferVarBaseAddress + BufferOffset);
      SctCopyMem (
        VarBaseAddress,
        &Result,
        sizeof (VOID *)
        );
    } else {
      SctCopyMem (
        VarBaseAddress,
        *BufferVarBaseAddress + BufferOffset,
        sizeof (VOID *)
        );
    }

    goto Done;
  }
  //
  // It is value
  //
  //
  // It is Rivl Internal Type
  //
  if ((Feature & RIVL_VAR_FEATURE_INTERNAL) == RIVL_VAR_FEATURE_INTERNAL) {
    if (ArrayNumber > 1) {
      //
      // It is an array
      //
      if (Type == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Done;
      }

      RivlInternalType = (RIVL_INTERNAL_TYPE *) Type;
      for (VarIndex = 0; VarIndex < ArrayNumber; VarIndex++) {
        //
        // Get the Value
        //
        ValueBuffer = strtok_line (NULL, RIVL_SEP_SIG);
        if (ValueBuffer == NULL) {
          break;
        }

        if ((ValueBuffer[0] != RIVL_ADD_SIG) && (ValueBuffer[0] != RIVL_PTR_SIG) && (ValueBuffer[0] != RIVL_VAL_SIG)) {
          //
          // Raw data
          //
          StringToMem (
            ValueBuffer,
            *VarBaseAddress + Offset + RivlInternalType->Size * VarIndex,
            Length
            );
          continue;
        }
        //
        // Advanced Search the Variable
        //
        Status = AdvancedSearchRivlVariable (
                  ValueBuffer,
                  &RivlBufferVariable,
                  &BufferOffset,
                  &BufferLength,
                  &BufferArrayNumber,
                  &BufferType,
                  &BufferFeature
                  );
        if (EFI_ERROR (Status)) {
          goto Done;
        }

        if ((BufferFeature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
          BufferVarBaseAddress = (UINT8 **)&(RivlBufferVariable->Address);
        } else {
          BufferVarBaseAddress = RivlBufferVariable->Address;
        }
        //
        // Check the Value
        //
        if ((BufferFeature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
          Result = (INTN) (*BufferVarBaseAddress + BufferOffset);
          SctCopyMem (
            *VarBaseAddress + Offset + RivlInternalType->Size * VarIndex,
            &Result,
            sizeof (INTN)
            );
        } else {
          SctCopyMem (
            *VarBaseAddress + Offset + RivlInternalType->Size * VarIndex,
            *BufferVarBaseAddress + BufferOffset,
            BufferLength
            );
        }
      }
    } else {
      //
      // It is a single value
      //
      //
      // Get the Value
      //
      ValueBuffer = strtok_line (NULL, RIVL_SEP_SIG);
      if (ValueBuffer == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Done;
      }

      if ((ValueBuffer[0] != RIVL_ADD_SIG) && (ValueBuffer[0] != RIVL_PTR_SIG) && (ValueBuffer[0] != RIVL_VAL_SIG)) {
        //
        // Raw data
        //
        StringToMem (
          ValueBuffer,
          *VarBaseAddress + Offset,
          Length
          );
        goto Done;
      }
      //
      // Advanced Search the Variable
      //
      Status = AdvancedSearchRivlVariable (
                ValueBuffer,
                &RivlBufferVariable,
                &BufferOffset,
                &BufferLength,
                &BufferArrayNumber,
                &BufferType,
                &BufferFeature
                );
      if (EFI_ERROR (Status)) {
        goto Done;
      }

      if ((BufferFeature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
        BufferVarBaseAddress = (UINT8 **)&(RivlBufferVariable->Address);
      } else {
        BufferVarBaseAddress = RivlBufferVariable->Address;
      }
      //
      // Check the Value
      //
      if ((BufferFeature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
        Result = (INTN) (*BufferVarBaseAddress + BufferOffset);
        SctCopyMem (
          *VarBaseAddress + Offset,
          &Result,
          sizeof (INTN)
          );
      } else {
        SctCopyMem (
          *VarBaseAddress + Offset,
          *BufferVarBaseAddress + BufferOffset,
          BufferLength
          );
      }
    }

    goto Done;
  }
  //
  // It is Rivl Type
  //
  if ((Feature & RIVL_VAR_FEATURE_EXTERNAL) == RIVL_VAR_FEATURE_EXTERNAL) {
    if (ArrayNumber > 1) {
      //
      // It is an array
      //
      for (VarIndex = 0; VarIndex < ArrayNumber; VarIndex++) {
        //
        // Get the Value
        //
        ValueBuffer = strtok_line (NULL, RIVL_SEP_SIG);
        if (ValueBuffer == NULL) {
          break;
        }

        if ((ValueBuffer[0] != RIVL_ADD_SIG) && (ValueBuffer[0] != RIVL_PTR_SIG) && (ValueBuffer[0] != RIVL_VAL_SIG)) {
          //
          // Raw data
          //
          Status = EFI_INVALID_PARAMETER;
          goto Done;
        }
        //
        // Advanced Search the Variable
        //
        Status = AdvancedSearchRivlVariable (
                  ValueBuffer,
                  &RivlBufferVariable,
                  &BufferOffset,
                  &BufferLength,
                  &BufferArrayNumber,
                  &BufferType,
                  &BufferFeature
                  );
        if (EFI_ERROR (Status)) {
          goto Done;
        }

        if ((BufferFeature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
          BufferVarBaseAddress = (UINT8 **)&(RivlBufferVariable->Address);
        } else {
          BufferVarBaseAddress = RivlBufferVariable->Address;
        }
        //
        // Check the Value
        //
        if ((BufferFeature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
          Status = EFI_INVALID_PARAMETER;
          goto Done;
        } else {
          TypeSize = Length / ArrayNumber;
          SctCopyMem (
            *VarBaseAddress + Offset + TypeSize * VarIndex,
            *BufferVarBaseAddress + BufferOffset,
            BufferLength
            );
        }
      }

      goto Done;
    } else {
      //
      // It is a sigle struct
      //
      if (Type == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Done;
      }

      RivlType = (RIVL_TYPE *) Type;
      for (VarIndex = 0; VarIndex < RivlType->MemberNumber; VarIndex++) {
        //
        // Get the Name and Value
        //
        NameBuffer  = strtok_line (NULL, RIVL_SEP_SIG);
        ValueBuffer = strtok_line (NULL, RIVL_SEP_SIG);

        if ((VarIndex == 0) && (NameBuffer == NULL) && (ValueBuffer == NULL)) {
          Status = EFI_INVALID_PARAMETER;
          goto Done;
        }
        //
        // Only one whole item
        //
        if ((VarIndex == 0) && (NameBuffer != NULL) && (ValueBuffer == NULL)) {
          ValueBuffer = NameBuffer;

          if ((ValueBuffer[0] != RIVL_ADD_SIG) && (ValueBuffer[0] != RIVL_PTR_SIG) && (ValueBuffer[0] != RIVL_VAL_SIG)) {
            //
            // Raw data
            //
            Status = EFI_INVALID_PARAMETER;
            goto Done;
          }
          //
          // Advanced Search the Variable
          //
          Status = AdvancedSearchRivlVariable (
                    ValueBuffer,
                    &RivlBufferVariable,
                    &BufferOffset,
                    &BufferLength,
                    &BufferArrayNumber,
                    &BufferType,
                    &BufferFeature
                    );
          if (EFI_ERROR (Status)) {
            goto Done;
          }

          if ((BufferFeature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
            BufferVarBaseAddress = (UINT8 **)&(RivlBufferVariable->Address);
          } else {
            BufferVarBaseAddress = RivlBufferVariable->Address;
          }
          //
          // Check the Value
          //
          if ((BufferFeature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
            Status = EFI_INVALID_PARAMETER;
          } else {
            SctCopyMem (
              *VarBaseAddress + Offset,
              *BufferVarBaseAddress + BufferOffset,
              BufferLength
              );
          }

          goto Done;
        }
        //
        // member,value pair
        //
        if ((VarIndex != 0) && ((NameBuffer == NULL) || (ValueBuffer == NULL))) {
          break;
        }

        RivlMember = SearchRivlMember (RivlType, NameBuffer);
        if (RivlMember == NULL) {
          return EFI_INVALID_PARAMETER;
        }

        if ((ValueBuffer[0] != RIVL_ADD_SIG) && (ValueBuffer[0] != RIVL_PTR_SIG) && (ValueBuffer[0] != RIVL_VAL_SIG)) {
          //
          // Raw data
          //
          StringToMem (
            ValueBuffer,
            *VarBaseAddress + Offset + RivlMember->Offset,
            RivlMember->TypeSize
            );
          continue;
        }
        //
        // Advanced Search the Variable
        //
        Status = AdvancedSearchRivlVariable (
                  ValueBuffer,
                  &RivlBufferVariable,
                  &BufferOffset,
                  &BufferLength,
                  &BufferArrayNumber,
                  &BufferType,
                  &BufferFeature
                  );
        if (EFI_ERROR (Status)) {
          goto Done;
        }

        if ((BufferFeature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
          BufferVarBaseAddress = (UINT8 **)&(RivlBufferVariable->Address);
        } else {
          BufferVarBaseAddress = RivlBufferVariable->Address;
        }

        if ((BufferFeature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
          Result = (INTN) (*BufferVarBaseAddress + BufferOffset);
          SctCopyMem (
            *VarBaseAddress + Offset,
            &Result,
            sizeof (INTN)
            );
        } else {
          SctCopyMem (
            *VarBaseAddress + Offset + RivlMember->Offset,
            *BufferVarBaseAddress + BufferOffset,
            BufferLength
            );
        }
      }
    }
  }

Done:
  SctStrCpy (VarBuf, TmpBuf);
  EntsFreePool (TmpBuf);

  return Status;
}

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
{
  CHAR16        *VarName;
  RIVL_VARIABLE *RivlVariable;
  UINT32        Offset;
  UINT32        Length;
  UINT32        ArrayNumber;
  VOID          *Type;
  UINT32        Feature;
  EFI_STATUS    Status;
  CHAR16        *TmpBuf;
  INTN          Result;
  UINT8         **VarBaseAddress;

  //
  // Conformance check
  //
  if (VarBuf == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  TmpBuf = EntsStrDuplicate (VarBuf);
  if (TmpBuf == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  VarName = strtok_line (VarBuf, RIVL_SEP_SIG);

  //
  // Advanced Search the var by name
  //
  Status = AdvancedSearchRivlVariable (
            VarName,
            &RivlVariable,
            &Offset,
            &Length,
            &ArrayNumber,
            &Type,
            &Feature
            );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  if ((Feature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
    VarBaseAddress = (UINT8 **)&(RivlVariable->Address);
  } else {
    VarBaseAddress = RivlVariable->Address;
  }

  if ((Feature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
    //
    // It is reference
    //
    Length = sizeof (VOID *);
    if (*BufferSize < Length * MULTIPLIER + 2) {
      *BufferSize = Length * MULTIPLIER + 2;
      Status      = EFI_BUFFER_TOO_SMALL;
      goto Done;
    }

    Result = (INTN) (*VarBaseAddress + Offset);
    MemToString (
      &Result,
      Buffer,
      Length
      );
    *BufferSize = Length * MULTIPLIER + 2;
  } else {
    //
    // It is value
    //
    if (*BufferSize < Length * MULTIPLIER + 2) {
      *BufferSize = Length * MULTIPLIER + 2;
      Status      = EFI_BUFFER_TOO_SMALL;
      goto Done;
    }

    MemToString (
      *VarBaseAddress + Offset,
      Buffer,
      Length
      );
    *BufferSize = Length * MULTIPLIER + 2;
  }

Done:
  SctStrCpy (VarBuf, TmpBuf);
  EntsFreePool (TmpBuf);

  return Status;
}

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
{
  RIVL_VARIABLE       *RivlVariable;
  RIVL_TYPE           *RivlType;
  RIVL_INTERNAL_TYPE  *RivlInternalType;
  RIVL_MEMBER         *RivlMember;
  CHAR16              *UnitName;
  CHAR16              *IndexName;
  BOOLEAN             HasIndex;
  UINTN               IndexValue;
  INTN                Result;

  //
  // Conformance check
  //
  if ((Name == NULL) ||
      (Variable == NULL) ||
      (Offset == NULL) ||
      (Length == NULL) ||
      (ArrayNumber == NULL) ||
      (Type == NULL) ||
      (Feature == NULL)
      ) {
    return EFI_INVALID_PARAMETER;
  }

  UnitName      = NULL;
  IndexName     = NULL;
  HasIndex      = FALSE;
  IndexValue    = 0;

  *Offset       = 0;
  *Length       = 0;
  *ArrayNumber  = 1;
  *Feature      = 0;

  //
  // Get the variable name
  //
  UnitName = my_strtok_line (Name, L".");

  if (UnitName == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  switch (UnitName[0]) {
  //
  // Check Address signature
  //
  case RIVL_ADD_SIG:
    *Feature |= RIVL_VAR_FEATURE_ADDRESS;
    UnitName += 1;
    switch (UnitName[0]) {
    case RIVL_PTR_SIG:
      *Feature |= RIVL_VAR_FEATURE_POINTER;
      UnitName += 1;
      switch (UnitName[0]) {
      case RIVL_VAL_SIG:
        *Feature |= RIVL_VAR_FEATURE_VARIABLE;
        UnitName += 1;
        break;

      default:
        return EFI_INVALID_PARAMETER;
      }
      break;

    case RIVL_VAL_SIG:
      *Feature |= RIVL_VAR_FEATURE_VARIABLE;
      UnitName += 1;
      break;

    default:
      return EFI_INVALID_PARAMETER;
    }
    break;

  //
  // Check Pointer signature
  //
  case RIVL_PTR_SIG:
    *Feature |= RIVL_VAR_FEATURE_POINTER;
    UnitName += 1;
    switch (UnitName[0]) {
    case RIVL_VAL_SIG:
      *Feature |= RIVL_VAR_FEATURE_VARIABLE;
      UnitName += 1;
      break;

    default:
      return EFI_INVALID_PARAMETER;
    }
    break;

  //
  // Check Value signature
  //
  case RIVL_VAL_SIG:
    *Feature |= RIVL_VAR_FEATURE_VARIABLE;
    UnitName += 1;
    break;

  default:
    return EFI_INVALID_PARAMETER;
  }

  my_strtok_field (UnitName, L"(");
  IndexName = my_strtok_field (NULL, L")");

  if (IndexName == NULL) {
    //
    // No index
    //
    HasIndex = FALSE;
  } else {
    //
    // Get index value
    //
    Result = EntsStrToUINTN (IndexName, &IndexValue);
    if (Result == -1) {
      return EFI_INVALID_PARAMETER;
    }

    HasIndex = TRUE;
  }
  //
  // Search the variable
  //
  RivlVariable = SearchRivlVariable (UnitName);
  if (RivlVariable == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Check the correctness (for pointer)
  //
  if ((*Feature & RIVL_VAR_FEATURE_POINTER) == RIVL_VAR_FEATURE_POINTER) {
    if (RivlVariable->Attribute != RIVL_VAR_ATTRIB_POINTER) {
      return EFI_INVALID_PARAMETER;
    }
  }
  //
  // Check the correctness (for index)
  //
  if (HasIndex) {
    if (RivlVariable->Attribute == RIVL_VAR_ATTRIB_POINTER) {
      if ((*Feature & RIVL_VAR_FEATURE_POINTER) == RIVL_VAR_FEATURE_POINTER) {
        return EFI_INVALID_PARAMETER;
      }
      //
      // adjust the feature (for index)
      //
      *Feature |= RIVL_VAR_FEATURE_POINTER;
    }
  }
  //
  // Get ArrayNumber
  //
  if (!HasIndex) {
    *ArrayNumber = RivlVariable->ArrayNumber;
  } else {
    *ArrayNumber = 1;
  }

  if (HasIndex && ((RivlVariable->ArrayNumber == 1) || (IndexValue >= RivlVariable->ArrayNumber))) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Get the address, length and offset
  //
  *Variable = RivlVariable;
  *Length   = RivlVariable->TypeSize * (HasIndex ? 1 : RivlVariable->ArrayNumber);
  *Offset   = (HasIndex ? (RivlVariable->TypeSize * (UINT32) IndexValue) : 0);

  //
  // Get the Sub-member
  //
  UnitName = my_strtok_line (NULL, L".");

  //
  // Check the correctness (for sub-member)
  //
  if (UnitName != NULL) {
    if (RivlVariable->Attribute == RIVL_VAR_ATTRIB_POINTER) {
      if ((*Feature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
        return EFI_INVALID_PARAMETER;
      }
    }
  }
  //
  // adjust the feature (for pointer)
  //
  if (RivlVariable->Attribute == RIVL_VAR_ATTRIB_POINTER) {
    if (!HasIndex && (UnitName == NULL)) {
      if (((*Feature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) &&
          ((*Feature & RIVL_VAR_FEATURE_ADDRESS) != RIVL_VAR_FEATURE_ADDRESS)
          ) {
        *Feature |= RIVL_VAR_FEATURE_POINTER;
        *Feature |= RIVL_VAR_FEATURE_ADDRESS;
      }
    }
  }
  //
  // Get the variable type
  //
  RivlInternalType  = SearchRivlInternalType (RivlVariable->Type);
  RivlType          = SearchRivlType (RivlVariable->Type);
  if ((RivlInternalType == NULL) && (RivlType == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((RivlType == NULL) && (UnitName != NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Recursive search the member name
  //
  while (UnitName != NULL) {
    my_strtok_field (UnitName, L"(");
    IndexName = my_strtok_field (NULL, L")");

    if (IndexName == NULL) {
      //
      // No index
      //
      HasIndex = FALSE;
    } else {
      //
      // Get index value
      //
      Result = EntsStrToUINTN (IndexName, &IndexValue);
      if (Result == -1) {
        return EFI_INVALID_PARAMETER;
      }

      HasIndex = TRUE;
    }
    //
    // Search the member
    //
    RivlMember = SearchRivlMember (RivlType, UnitName);
    if (RivlMember == NULL) {
      return EFI_INVALID_PARAMETER;
    }
    //
    // Get ArrayNumber
    //
    if (!HasIndex) {
      *ArrayNumber = RivlMember->ArrayNumber;
    } else {
      *ArrayNumber = 1;
    }

    //if (HasIndex && ((RivlMember->ArrayNumber == 1) || (IndexValue >= RivlMember->ArrayNumber))) {
    //  return EFI_INVALID_PARAMETER;
    //}
    //
    // Recalculate the length and offset
    //
    *Length = RivlMember->TypeSize * (HasIndex ? 1 : RivlMember->ArrayNumber);
    *Offset += RivlMember->Offset + (HasIndex ? (RivlMember->TypeSize * (UINT32) IndexValue) : 0);

    //
    // Get the Sub-variable
    //
    UnitName = my_strtok_line (NULL, L".");
    if (RivlType == NULL) {
      return EFI_INVALID_PARAMETER;
    }
    //
    // Get the member type
    //
    RivlInternalType  = SearchRivlInternalType (RivlMember->Type);
    RivlType          = SearchRivlType (RivlMember->Type);
    if ((RivlInternalType == NULL) && (RivlType == NULL)) {
      return EFI_INVALID_PARAMETER;
    }

    if ((RivlType == NULL) && (UnitName != NULL)) {
      return EFI_INVALID_PARAMETER;
    }
  }
  //
  // Get the Type
  //
  if ((RivlInternalType != NULL) && (RivlType == NULL)) {
    *Type = RivlInternalType;
    *Feature |= RIVL_VAR_FEATURE_INTERNAL;
  } else if ((RivlInternalType == NULL) && (RivlType != NULL)) {
    *Type = RivlType;
    *Feature |= RIVL_VAR_FEATURE_EXTERNAL;
  } else {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

UINT32
GetSizeFromTypeList (
  IN CHAR16                    *Type
  )
/*++

Routine Description:

  This func is to get the Size of Type form gRivlInternalTypeArray or gRivlTypeList.

Arguments:

  Type  - Type to be searched.

Returns:

  The Size of Type, 0 means not found.

--*/
{
  RIVL_TYPE           *RivlType;
  RIVL_INTERNAL_TYPE  *RivlInternalType;

  RivlInternalType = SearchRivlInternalType (Type);
  if (RivlInternalType != NULL) {
    return RivlInternalType->Size;
  }

  RivlType = SearchRivlType (Type);
  if (RivlType != NULL) {
    return RivlType->Size;
  }

  return 0;
}

CHAR16  *___my_strtok_line  = NULL;
CHAR16  *___my_strtok_field = NULL;

CHAR16 *
my_strtok_line (
  CHAR16       *s,
  const CHAR16 *ct
  )
/*++

Routine Description:

  Find the next token in a string.

--*/
{
  CHAR16  *sbegin;

  CHAR16  *send;

  sbegin = s ? s : ___my_strtok_line;
  if (!sbegin) {
    return NULL;
  }

  sbegin += strspn (sbegin, ct);
  if (*sbegin == '\0') {
    ___my_strtok_line = NULL;
    return NULL;
  }

  send = strpbrk (sbegin, ct);
  if (send && (*send != '\0')) {
    *send++ = '\0';
  }

  ___my_strtok_line = send;
  return sbegin;
}

CHAR16 *
my_strtok_field (
  CHAR16       *s,
  const CHAR16 *ct
  )
/*++

Routine Description:

  Find the next token in a string.

--*/
{
  CHAR16  *sbegin;

  CHAR16  *send;

  sbegin = s ? s : ___my_strtok_field;
  if (!sbegin) {
    return NULL;
  }
  //
  // sbegin += strspn (sbegin, ct);
  // Different with my_strtok_line()
  // do not find the first substring, just use this char as sbegin
  //
  if (*sbegin == '\0') {
    ___my_strtok_field = NULL;
    return NULL;
  }

  send = strpbrk (sbegin, ct);
  if (send && (*send != '\0')) {
    *send++ = '\0';
  }

  ___my_strtok_field = send;
  return sbegin;
}
