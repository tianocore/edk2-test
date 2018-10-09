/** @file
 
  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsRivlInterType.c
    
Abstract:

    Implementation of RIVL internal type 

--*/

#include "EmsRivlMain.h"
#include "EmsRivlVar.h"
#include "stdlib.h"
#include "EmsRivlEndian.h"
#include "EmsRivlUtil.h"
#include "EmsRpcMain.h"

VALIDATE_VALUE_T  ValidateBOOL;
VALIDATE_VALUE_T  ValidateINT8;
VALIDATE_VALUE_T  ValidateINT16;
VALIDATE_VALUE_T  ValidateINT32;
VALIDATE_VALUE_T  ValidateINT64;
VALIDATE_VALUE_T  ValidateCHAR8;
VALIDATE_VALUE_T  ValidateCHAR16;
VALIDATE_VALUE_T  ValidateVOID;
VALIDATE_VALUE_T  ValidateINTN;
VALIDATE_VALUE_T  ValidateUINTN;
VALIDATE_VALUE_T  ValidatePOINTER;
CONVERT_VALUE_T   ConvertBOOL;
CONVERT_VALUE_T   ConvertINT8;
CONVERT_VALUE_T   ConvertINT16;
CONVERT_VALUE_T   ConvertINT32;
CONVERT_VALUE_T   ConvertINT64;
CONVERT_VALUE_T   ConvertCHAR8;
CONVERT_VALUE_T   ConvertCHAR16;
CONVERT_VALUE_T   ConvertINTN;
CONVERT_VALUE_T   ConvertUINTN;
CONVERT_VALUE_T   ConvertPOINTER;

extern
BOOLEAN
RivlBuildvariable (
  INT8          *,
  RIVL_VARIABLE *
  );

BOOLEAN
RivlBuildSetVar (
  INT8         *,
  RIVL_VARIABLE*
  );

INTERNAL_TYPE     *
RivlInternalTypeFindByName (
  INT8 *Name
  );

STATIC UINT32     TargetBits = 32;

INTERNAL_TYPE     InternalTypes[] = {
  {
    "BOOLEAN",
    ValidateBOOL,
    ConvertBOOL,
    1 /*sizeof(bool)*/
  },
  {
    "INTN",
    ValidateINTN,
    ConvertINTN,
    sizeof (INT32)
  },
  {
    "UINTN",
    ValidateUINTN,
    ConvertUINTN,
    sizeof (INT32)
  },
  {
    "INT8",
    ValidateINT8,
    ConvertINT8,
    sizeof (INT8)
  },
  {
    "UINT8",
    ValidateINT8,
    ConvertINT8,
    sizeof (INT8)
  },
  {
    "INT16",
    ValidateINT16,
    ConvertINT16,
    sizeof (INT16)
  },
  {
    "UINT16",
    ValidateINT16,
    ConvertINT16,
    sizeof (INT16)
  },
  {
    "INT32",
    ValidateINT32,
    ConvertINT32,
    sizeof (INT32)
  },
  {
    "UINT32",
    ValidateINT32,
    ConvertINT32,
    sizeof (INT32)
  },
  {
    "INT64",
    ValidateINT64,
    ConvertINT64,
    sizeof (INT64)
  },
  {
    "UINT64",
    ValidateINT64,
    ConvertINT64,
    sizeof (INT64)
  },
  {
    "CHAR8",
    ValidateCHAR8,
    ConvertCHAR8,
    sizeof (INT8)
  },
  {
    "CHAR16",
    ValidateCHAR16,
    ConvertCHAR16,
    sizeof (INT16)
  },
  {
    "POINTER",
    ValidateVOID,
    ConvertPOINTER,
    sizeof (INT32)
  },
  {
    NULL
  }
};

extern
BOOLEAN
IsDefineArray (
  INT8      *Str,
  UINT32    *ArrayNum,
  INT8      *Name
  );

BOOLEAN
ValidateBOOL (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the boolean varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  INT8    Item[MAX_STRING_LEN];
  UINT32  Pos;
  UINT32  ItemNum;
  UINT32  Len;

  Pos         = 0;
  ItemNum     = 0;
  Len         = strlen (Value);

  *StripValue = '\0';

  while (Pos != Len) {
    Pos = GetNextSubStr (
            Value,
            Pos,
            Item
            );
    if (*Item) {
      ItemNum++;
    } else {
      continue;
    }

    if (0 == strcmp_i ("true", Item)) {
      strcat (StripValue, "01");
    } else if (0 == strcmp_i ("false", Item)) {
      strcat (StripValue, "00");
    } else {
      sprintf (
        ErrBuff,
        "\"%s\" is not a valid vaue",
        Item
        );
      return FALSE;
    }
  }

  if (ItemNum > *Num) {
    sprintf (
      ErrBuff,
      "Exceed Array range[0..%d]",
      *Num - 1
      );
    return FALSE;
  }

  return TRUE;
}

BOOLEAN
ValidateINT8 (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the INT8 varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  INT8    Item[MAX_STRING_LEN];
  UINT32  Pos;
  UINT32  ItemNum;
  UINT32  Len;
  UINT32  TempValue;
  INT8    TempStr[10];

  Pos         = 0;
  ItemNum     = 0;
  Len         = strlen (Value);

  *StripValue = '\0';

  while (Pos != Len) {
    Pos = GetNextSubStr (
            Value,
            Pos,
            Item
            );
    if (*Item) {
      ItemNum++;
    } else {
      continue;
    }

    if ((strlen (Item) != AsciiStringToUint32 (Item, &TempValue)) || (TempValue > 0xff)) {
      sprintf (
        ErrBuff,
        "\"%s\" is not a valid Value",
        Item
        );
      return FALSE;
    }

    sprintf (TempStr, "%02x", TempValue);
    strcat (StripValue, TempStr);
  }

  if (ItemNum > *Num) {
    sprintf (
      ErrBuff,
      "Exceed Array range[0..%d]",
      *Num - 1
      );
    return FALSE;
  }

  return TRUE;
}

BOOLEAN
ValidateINT16 (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the INT16 varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  INT8    Item[MAX_STRING_LEN];
  UINT32  Pos;
  UINT32  ItemNum;
  UINT32  Len;
  UINT32  TempValue;
  INT8    TempStr[10];

  Pos         = 0;
  ItemNum     = 0;
  Len         = strlen (Value);

  *StripValue = '\0';
  while (Pos != Len) {
    Pos = GetNextSubStr (
            Value,
            Pos,
            Item
            );
    if (*Item) {
      ItemNum++;
    } else {
      continue;
    }

    if ((strlen (Item) != AsciiStringToUint32 (Item, &TempValue)) || (TempValue > 0xffff)) {
      sprintf (
        ErrBuff,
        "\"%s\" is not a valid Value",
        Item
        );
      return FALSE;
    }

    sprintf (TempStr, "%04x", RivlSwap16 (TempValue));
    strcat (StripValue, TempStr);
  }

  if (ItemNum > *Num) {
    sprintf (
      ErrBuff,
      "Exceed Array range[0..%d]",
      *Num - 1
      );
    return FALSE;
  }

  return TRUE;
}

BOOLEAN
ValidateINT32 (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the INT32 varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  INT8    Item[MAX_STRING_LEN];
  UINT32  Pos;
  UINT32  ItemNum;
  UINT32  Len;
  UINT32  TempValue;
  INT8    TempStr[10];

  Pos     = 0;
  ItemNum = 0;
  Len     = strlen (Value);

  memset (TempStr, 0, 10);
  *StripValue = '\0';
  while (Pos != Len) {
    Pos = GetNextSubStr (
            Value,
            Pos,
            Item
            );
    if (*Item) {
      ItemNum++;
    } else {
      continue;
    }

    if (strlen (Item) != AsciiStringToUint32 (Item, &TempValue)) {
      sprintf (
        ErrBuff,
        "\"%s\" is not a valid Value",
        Item
        );
      return FALSE;
    }

    sprintf (TempStr, "%08x", RivlSwap32 (TempValue));
    strcat (StripValue, TempStr);
  }

  if (ItemNum > *Num) {
    sprintf (
      ErrBuff,
      "Exceed Array range[0..%d]",
      *Num - 1
      );
    return FALSE;
  }

  return TRUE;
}

BOOLEAN
ValidateINT64 (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the INT64 varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  INT8    Item[MAX_STRING_LEN];
  UINT32  Pos;
  UINT32  ItemNum;
  UINT32  Len;
  UINT64  TempValue;
  INT8    TempStr[20];

  Pos         = 0;
  ItemNum     = 0;
  Len         = strlen (Value);

  *StripValue = '\0';
  while (Pos != Len) {
    Pos = GetNextSubStr (
            Value,
            Pos,
            Item
            );
    if (*Item) {
      ItemNum++;
    } else {
      continue;
    }

    if (strlen (Item) != AsciiStringToUint64 (Item, &TempValue)) {
      sprintf (
        ErrBuff,
        "\"%s\" is not a valid Value",
        Item
        );
      return FALSE;
    }

    sprintf (TempStr, "%08x", (UINT32) (RivlSwap64 (TempValue) >> 32));
    strcat (StripValue, TempStr);
    sprintf (TempStr, "%08x", (UINT32) RivlSwap64 (TempValue));
    strcat (StripValue, TempStr);
  }

  if (ItemNum > *Num) {
    sprintf (
      ErrBuff,
      "Exceed Array range[0..%d]",
      *Num - 1
      );
    return FALSE;
  }

  return TRUE;
}

BOOLEAN
ValidateINTN (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the INTN varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  if (TargetBits == 32) {
    return ValidateINT32 (Value, Num, ErrBuff, StripValue);
  } else {
    return ValidateINT64 (Value, Num, ErrBuff, StripValue);
  }
}

BOOLEAN
ValidateUINTN (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the UINTN varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  return ValidateINTN (Value, Num, ErrBuff, StripValue);
}

BOOLEAN
ValidateCHAR8 (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the CHAR8 varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  UINT32  Len;
  UINT32  Index;
  INT8    TempStr[8];

  Len = strlen (Value);
  if (Len > *Num) {
    sprintf (
      ErrBuff,
      "\"%s\" is too long.",
      Value
      );
  }

  *StripValue = '\0';
  for (Index = 0; Index < Len; Index++) {
    sprintf (TempStr, "%02x", (UINT8) Value[Index]);
    strcat (StripValue, TempStr);
  }

  strcat (StripValue, "00");
  return TRUE;
}

BOOLEAN
ValidateCHAR16 (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the CHAR16 varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  UINT32  Len;
  UINT32  Index;
  INT8    TempStr[8];

  Len = strlen (Value);
  if (Len > *Num) {
    sprintf (
      ErrBuff,
      "\"%s\" is too long.",
      Value
      );
  }

  *StripValue = '\0';
  for (Index = 0; Index < Len; Index++) {
    sprintf (TempStr, "%02x", (UINT8) Value[Index]);
    strcat (StripValue, TempStr);
    strcat (StripValue, "00");
  }

  strcat (StripValue, "0000");
  return TRUE;
}

BOOLEAN
ValidateVOID (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the VOID varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  INT8          Item[MAX_STRING_LEN];
  UINT32        Pos;
  UINT32        ItemNum;
  UINT32        Len;
  UINT32        TempValue32;
  UINT64        TempValue64;
  INT8          TempStr[20];
  RIVL_VARIABLE *Variable;

  Pos     = 0;
  ItemNum = 0;
  Len     = strlen (Value);

  while (Pos != Len) {
    Pos = GetNextSubStr (
            Value,
            Pos,
            Item
            );
    if (*Item) {
      ItemNum++;
    } else {
      continue;
    }
    //
    // The value of 'NULL' is a valid VOID
    //
    if (0 == strcmp_i (Item, "NULL")) {
      strcat (StripValue, Item);
      continue;
    }
    //
    // The format of VOID can be: &varname, @varname or 0xXXXX
    //
    if (Item[0] == '@') {
      //
      // varname after '@' should be existed and be type VOID
      //
      Variable = RivlVariableFindByName (Item + 1);
      if (NULL == Variable) {
        return FALSE;
      } else {
        if ((FALSE == Variable->Internal) || (strcmp (Variable->IType->Name, "VOID_P"))) {
          return FALSE;
        }

        strcat (StripValue, Item);
      }
    } else if (Item[0] == '&') {
      //
      // varname after '&' should be existed
      //
      Variable = RivlVariableFindByName (Item + 1);
      if (NULL == Variable) {
        return FALSE;
      }
    } else {
      switch (TargetBits) {
      case 32:
        if (strlen (Item) != AsciiStringToUint32 (Item, &TempValue32)) {
          sprintf (
            ErrBuff,
            "\"%s\" is not a valid Value",
            Item
            );
          return FALSE;
        }

        sprintf (TempStr, "%08x", RivlSwap32 (TempValue32));
        strcat (StripValue, TempStr);
        break;

      case 64:
        if (strlen (Item) != AsciiStringToUint64 (Item, &TempValue64)) {
          sprintf (
            ErrBuff,
            "\"%s\" is not a valid Value",
            Item
            );
          return FALSE;
        }

        sprintf (TempStr, "%08x", (UINT32) (RivlSwap64 (TempValue64) >> 32));
        strcat (StripValue, TempStr);
        sprintf (TempStr, "%08x", (UINT32) RivlSwap64 (TempValue64));
        strcat (StripValue, TempStr);
        break;
      }
    }
  }

  if (ItemNum > *Num) {
    sprintf (ErrBuff, "Exceed Array range[0..%d]", *Num - 1);
    return FALSE;
  }

  return TRUE;
}

BOOLEAN
ValidatePOINTER (
  IN     INT8          *Value,      // value to Validate
  IN OUT UINT32        *Num,
  OUT    INT8          *ErrBuff,    // error message
  OUT    INT8          *StripValue  // striped string
  )
/*++

Routine Description:

  Validate the pointer varibale 

Arguments:

  Value             - The value to validate
  Num               - The Array range
  ErrBuff           - The error message buffer
  StripValue        - The striped string

Returns:

  TRUE or FALSE

--*/
{
  if (Value[0] != '&') {
    return FALSE;
  }

  strcpy (StripValue, Value);
  return TRUE;
}

INTERNAL_TYPE *
RivlInternalTypeFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find a Rivl internal type accroding name

Arguments:

  Name  - The name of type

Returns:

  NULL if not found otherwise return the internal type found

--*/
{
  UINT32  Index;
  for (Index = 0; InternalTypes[Index].Name; Index++) {
    if (0 == strcmp (Name, InternalTypes[Index].Name)) {
      return &InternalTypes[Index];
    }
  }

  return NULL;
}

BOOLEAN
IsInternalType (
  INT8 *Name
  )
/*++

Routine Description:

  Check the variable type is Rivl internal type

Arguments:

  Name  - The type name

Returns:

  TRUE or FALSE

--*/
{
  return RivlInternalTypeFindByName (Name) ? TRUE : FALSE;
}

INT32
TclVarDeclareInternal (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  The implementation routine for declare internal TCL variable

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
  INT8          Name[MAX_VARNAME_LEN];
  INT8          Message[MAX_MESSAGE_LEN];
  INT8          StripValue[MAX_STRING_LEN];
  INT8          *VarName;
  INT8          *Value;
  BOOLEAN       IsArray;
  BOOLEAN       IsValueDefined;
  UINT32        ArrayNum;
  RIVL_VARIABLE *Variable;
  INTERNAL_TYPE *Type;
  INT32         Length;
  BOOLEAN       IsRefer;
  BOOLEAN       IsPtr;
  BOOLEAN       Pass;
  INT8          *Out;
  INT8          *Log;
  INT32         Index;

  IsRefer = FALSE;
  IsPtr   = FALSE;

  Type    = RivlInternalTypeFindByName ((INT8 *) Argv[0]);
  if (Argc < 2) {
    sprintf (ErrorBuff, "Lack of Variable Name for Type \"%s\"", (INT8 *) Argv[0]);
    goto ErrorExit;
  }
  //
  // You can define multiple variables in one command
  // Each variable is in this format
  //    Type [VarName : Value] ... Value can be embraced by {}
  //    e.g. UINT32 "Var2" "Var1 : 1" "Var3(3) : {1 2 3}"
  //                "Var4 : @temp" "Var5(3) : {@temp 2 3}"
  //
  Index = 1;
  while (Index < Argc) {
    IsValueDefined  = FALSE;
    VarName         = (INT8 *) Argv[Index];
    Index++;
    if ((Index < Argc) && (0 == strcmp ((INT8 *) Argv[Index], "="))) {
      Index++;
      if (Index < Argc) {
        IsValueDefined  = TRUE;
        Value           = (INT8 *) Argv[Index];
        Index++;
      }
    }

    /*
    // Get varName and value
    //
    is_value_defined = false;
    if (false == get_name_optvalue_from_line(argv[i], &varname, &is_value_defined, &value)) {
      sprintf (ErrorBuff, "Variable %s in error format", argv[i]);
      goto wrong;
    }
    */

    //
    // check if this variable is reference variable?
    //
    if (VarName[0] == '&') {
      IsRefer = TRUE;
      VarName = &VarName[1];
      //
      // printf ("inter_type: to define a reference variable - %s.\n", varname);
      //
    } else if (VarName[0] == '*') {
      IsPtr   = TRUE;
      VarName = &VarName[1];
    }
    //
    // printf ("varname:%s, value:%s, is_value_defined:%s\n", varname, value,
    //        is_value_defined?"true":"false");
    // Check varName length
    //
    if (strlen (VarName) > MAX_VARNAME_LEN) {
      sprintf (ErrorBuff, "Variable Name \"%s\" is too long.", VarName);
      goto ErrorExit;
    }
    //
    // Check if define array
    //
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
    Variable->Internal      = TRUE;
    Variable->IType         = Type;
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

    RivlVariableAdd (Variable);

    //
    //  sprintf(ErrorBuff, "Name: %s Array: %s  array_num %d", name,
    //          is_array? "true" : "false", array_num );
    //
    // 1). Build message  2). sent Out 3). recv response
    //
    Message[0] = 0;
    if (FALSE == RivlBuildvariable (Message, Variable)) {
      sprintf (ErrorBuff, "Something ErrorExit!");
      goto ErrorExit;
    }

    Length = strlen (Message);
    RpcSendMessage (Length, Message);
    Message[0]  = 0;
    Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);
    if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) || (FALSE == Pass)) {
      sprintf (ErrorBuff, "EAS: InterType %s failed!", Name);
      goto ErrorExit;
    }

    if (IsValueDefined) {
      //
      // set value to this variable
      // of course, this is Internal Type value
      //
      if (!(Variable->IType->Validate (Value, &ArrayNum, ErrorBuff, StripValue))) {
        goto ErrorExit;
      }

      Variable->InternalValue = _strdup (StripValue);

      //
      // build message and receive message from
      //
      if (FALSE == RivlBuildSetVar (Message, Variable)) {
        sprintf (ErrorBuff, "Something ErrorExit!");
        goto ErrorExit;
      }

      Length = strlen (Message);
      RpcSendMessage (Length, Message);
      Message[0]  = 0;
      Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);
      if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) || (FALSE == Pass)) {
        sprintf (ErrorBuff, "EAS: InterType %s failed!", Name);
        goto ErrorExit;
      }
    }
  }

  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

BOOLEAN
ConvertBOOL (
  IN     INT8          *Src,  // value to Validate
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to boolean

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  INT32 Index;
  UINT8 Value;

  *Dst = '\0';

  for (Index = 0; Index < Num; Index++) {
    Value = (AsciiToUint32 (Src[2 * Index]) << 4) + (AsciiToUint32 (Src[2 * Index + 1]));
    if (Value) {
      strcat (Dst, "true");
    } else {
      strcat (Dst, "false");
    }
  }

  return TRUE;
}

BOOLEAN
ConvertINT8 (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to INT8

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  INT32 Index;
  UINT8 Value;
  UINT8 TempStr[5];

  *Dst = '\0';
  if (1 == Num) {
    Value = (AsciiToUint32 (Src[0]) << 4) + (AsciiToUint32 (Src[1]));
    sprintf (Dst, "%#x", Value);
    return TRUE;
  }

  for (Index = 0; Index < Num; Index++) {
    Value = (AsciiToUint32 (Src[2 * Index]) << 4) + (AsciiToUint32 (Src[2 * Index + 1]));
    if (0 == Value) {
      break;
    }

    sprintf (TempStr, "%c", Value);
    strcat (Dst, TempStr);
  }

  return TRUE;
}

BOOLEAN
ConvertINT16 (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to INT16

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  INT32   Index;
  UINT16  Value;

  *Dst = '\0';
  if (1 == Num) {
    Value = (AsciiToUint32 (Src[0]) << 12) + (AsciiToUint32 (Src[1]) << 8) + (AsciiToUint32 (Src[2]) << 4) + (AsciiToUint32 (Src[3]));
    sprintf (Dst, "%#x", RivlSwap16 (Value));
    return TRUE;
  }

  for (Index = 0; Index < Num; Index++) {
  }

  return TRUE;
}

BOOLEAN
ConvertUINTN (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to UINTN

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  return ConvertINTN (Src, Dst, Num);
}

BOOLEAN
ConvertINTN (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to INTN

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  if (TargetBits == 32) {
    return ConvertINT32 (Src, Dst, Num);
  } else {
    return ConvertINT64 (Src, Dst, Num);
  }
}

BOOLEAN
ConvertINT32 (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to INT32

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  INT32   Index;
  UINT32  Value;

  *Dst  = '\0';
  Value = 0;
  if (1 == Num) {
    for (Index = 0; Index < 4; Index++) {
      Value = (Value << 8) + (AsciiToUint32 (Src[2 * Index]) << 4) + (AsciiToUint32 (Src[2 * Index + 1]));
    }
    //
    //    sprintf(dst, "%#x", rivl_swap32(value));
    //
    sprintf (Dst, "0x%08x", RivlSwap32 (Value));
    return TRUE;
  }

  for (Index = 0; Index < Num; Index++) {
  }

  return TRUE;
}

BOOLEAN
ConvertINT64 (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to INT64

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  INT32   Index;
  UINT64  Value;
  UINT32  TempValue;
  UINT8   TempStr[20];

  *Dst  = '\0';
  Value = 0;
  if (1 == Num) {
    for (Index = 0; Index < 16; Index++) {
      Value = (Value << 4) + AsciiToUint32 (Src[Index]);
    }

    TempValue = (UINT32) (RivlSwap64 (Value) >> 32);
    if (TempValue != 0) {
      sprintf (TempStr, "%#x", TempValue);
      strcat (Dst, TempStr);
      sprintf (TempStr, "%08x", (UINT32) (RivlSwap64 (Value)));
    } else {
      sprintf (TempStr, "%#x", (UINT32) (RivlSwap64 (Value)));
    }

    strcat (Dst, TempStr);
    return TRUE;
  }

  for (Index = 0; Index < Num; Index++) {
  }

  return TRUE;
}

BOOLEAN
ConvertCHAR8 (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to CHAR8

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  INT32 Index;
  UINT8 Value;
  UINT8 TempStr[5];

  *Dst = '\0';
  if (1 == Num) {
    Value = (AsciiToUint32 (Src[0]) << 4) + (AsciiToUint32 (Src[1]));
    sprintf (Dst, "%c", Value);
    return TRUE;
  }

  for (Index = 0; Index < Num; Index++) {
    Value = (AsciiToUint32 (Src[2 * Index]) << 4) + (AsciiToUint32 (Src[2 * Index + 1]));
    if (0 == Value) {
      break;
    }

    sprintf (TempStr, "%c", Value);
    strcat (Dst, TempStr);
  }

  return TRUE;
}

BOOLEAN
ConvertCHAR16 (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to CHAR16

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  INT32   Index;
  UINT16  Value;
  UINT8   TempStr[5];

  *Dst = '\0';
  if (1 == Num) {
    Value = (AsciiToUint32 (Src[0]) << 12) + (AsciiToUint32 (Src[1]) << 8) + (AsciiToUint32 (Src[2]) << 4) + (AsciiToUint32 (Src[3]));
    sprintf (Dst, "%c", RivlSwap16 (Value));
    return TRUE;
  }

  for (Index = 0; Index < Num; Index++) {
    Value = (AsciiToUint32 (Src[2 * Index + 0]) << 12) + (AsciiToUint32 (Src[2 * Index + 1]) << 8) + (AsciiToUint32 (Src[2 * Index + 2]) << 4) + (AsciiToUint32 (Src[2 * Index + 3]));
    if (0 == Value) {
      break;
    }

    sprintf (TempStr, "%c", RivlSwap16 (Value));
    strcat (Dst, TempStr);
  }

  return TRUE;
}

BOOLEAN
ConvertPOINTER32 (
  IN     INT8          *Src,
  OUT    INT8          *Dst
  )
/*++

Routine Description:

  Convert string to VOID

Arguments:

  Src - The source string
  Dst - The result string

Returns:

  TRUE

--*/
{
  INT32   Index;
  UINT32  Value;

  *Dst  = '\0';
  Value = 0;
  //
  // Beginning with '@'
  // Beginning with '&'
  // just number
  //
  if ((*Src != '@') || (*Src != '&') || (0 != strcmp_i (Src, "NULL"))) {
    for (Index = 0; Index < 4; Index++) {
      Value = (Value << 8) + (AsciiToUint32 (Src[2 * Index]) << 4) + (AsciiToUint32 (Src[2 * Index + 1]));
    }

    sprintf (Dst, "%#x", RivlSwap32 (Value));
    return TRUE;
  } else {
    sprintf (Dst, "%s", Src);
    return TRUE;
  }

  return TRUE;
}

BOOLEAN
ConvertPOINTER64 (
  IN     INT8          *Src,
  OUT    INT8          *Dst
  )
/*++

Routine Description:

  Convert string to VOID

Arguments:

  Src - The source string
  Dst - The result string

Returns:

  TRUE

--*/
{
  INT32   Index;
  UINT64  Value;
  UINT32  TempValue;
  UINT8   TempStr[20];

  *Dst  = '\0';
  Value = 0;
  //
  // Beginning with '@'
  // Beginning with '&'
  // just number
  //
  if ((*Src != '@') || (*Src != '&') || (0 != strcmp_i (Src, "NULL"))) {
    for (Index = 0; Index < 16; Index++) {
      Value = (Value << 4) + AsciiToUint32 (Src[Index]);
    }

    TempValue = (UINT32) (RivlSwap64 (Value) >> 32);
    if (TempValue != 0) {
      sprintf (TempStr, "%#x", TempValue);
      strcat (Dst, TempStr);
      sprintf (TempStr, "%08x", (UINT32) (RivlSwap64 (Value)));
    } else {
      sprintf (TempStr, "%#x", (UINT32) (RivlSwap64 (Value)));
    }

    strcat (Dst, TempStr);
  } else {
    sprintf (Dst, "%s", Src);
    return TRUE;
  }

  return TRUE;
}

BOOLEAN
ConvertPOINTER (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  )
/*++

Routine Description:

  Convert string to pointer

Arguments:

  Src - The source string
  Dst - The result string
  Num - The number of character to convert

Returns:

  TRUE

--*/
{
  switch (TargetBits) {
  case 32:
    return ConvertPOINTER32 (Src, Dst);
  case 64:
    return ConvertPOINTER64 (Src, Dst);
  }
}

BOOLEAN
RivlBuildSetVar (
  INT8           *Message,
  RIVL_VARIABLE  *Variable
  )
/*++

Routine Description:

  Build Rivl "SetVar" rpc message command

Arguments:

  Message   - The message should be built
  Variable  - The variable which "SetVar" rpc message referance

Returns:

  TRUE or FALSE

--*/
{
  UINT32    MemberNum;
  UINT32    Index;
  RIVL_TYPE *EType;

  sprintf (Message, "RIVL_SETVAR ");
  if (Variable->Internal) {
    //
    // Internal type variable
    //
    if (Variable->InternalValue) {
      strcat (Message, Variable->Name);
      strcat (Message, " ");
      strcat (Message, Variable->InternalValue);
    } else {
      return FALSE;
    }
  } else if (FALSE == Variable->IsArray) {
    //
    // External type variable
    //
    EType = Variable->EType;
    strcat (Message, Variable->Name);
    strcat (Message, " ");
    MemberNum = Variable->IsArray ? Variable->ArrayNum : EType->MemberNum;

    for (Index = 0; Index < MemberNum; Index++) {

      if (NULL == Variable->Value[Index].Value) {
        continue;
      }

      strcat (Message, Variable->Value[Index].Name);
      strcat (Message, " ");
      strcat (Message, Variable->Value[Index].Value);
      strcat (Message, " ");
    }
  } else {
    //
    // External type variable
    //
    EType = Variable->EType;
    strcat (Message, Variable->Name);
    strcat (Message, " ");
    MemberNum = Variable->ArrayNum;

    for (Index = 0; Index < MemberNum; Index++) {

      if (NULL == Variable->Value[Index].Value) {
        continue;
      }
      //
      //      strcat(message, variable->value[i].name);
      //      strcat(message, " ");
      //
      strcat (Message, Variable->Value[Index].Value);
      strcat (Message, " ");
    }
  }

  return TRUE;
}

INT32
TclSetTargetBits (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "SetTargetBits" implementation routine  

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
  UINT32  Bits;
  UINT32  Index;

  if ((Argc != 2) || (AsciiStringToUint32 ((INT8 *) Argv[1], &Bits) <= 0)) {
    sprintf (ErrorBuff, "%s: %s 32/64", Argv[0], Argv[0]);
    goto ErrorExit;
  }

  if (32 != Bits && 64 != Bits) {
    sprintf (ErrorBuff, "%s: %s 32/64", Argv[0], Argv[0]);
    goto ErrorExit;
  }

  TargetBits = Bits;

  for (Index = 0; InternalTypes[Index].Name; Index++) {
    if ((0 == strcmp ("INTN", InternalTypes[Index].Name)) ||
        (0 == strcmp ("UINTN", InternalTypes[Index].Name)) ||
        (0 == strcmp ("POINTER", InternalTypes[Index].Name))
        ) {
      InternalTypes[Index].Size = Bits >> 3;
    }
  }

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclGetTargetBits (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GetTargetBits" implementation routine  

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

  sprintf (ErrorBuff, "%d", TargetBits);
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  
  return TCL_OK;
}
