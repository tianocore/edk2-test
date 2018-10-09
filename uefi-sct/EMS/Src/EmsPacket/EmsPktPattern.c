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
  
    EmsPktPattern.c
    
Abstract:

    Implementation for packet validation validation

--*/

#include "EmsPktValidate.h"
#include "EmsTypes.h"
#include "EmsPktMain.h"
#include "EmsProtocols.h"
#include "EmsUtilityString.h"

STATIC INT8     Expression[EXPR_MAX_LEN];
STATIC BOOLEAN  Operands[EXPR_MAX_LEN];
STATIC INT8     Operators[EXPR_MAX_LEN];
STATIC BOOLEAN  *OperandTop;
STATIC INT8     *OperatorTop;

//
// operators in packet validate expression  :
//   AND  OR  NOT  (  )
//
OPERATOR_T      OperatorList[] = {
#define OP_AND  0
  {
    "AND"
  },
#define OP_OR 1
  {
    "OR"
  },
#define OP_NOT  2
  {
    "NOT"
  },
#define OP_LPA  3
  {
    "("
  },
#define OP_RPA  4
  {
    ")"
  },
#define OP_CRS  5
  {
    "#"
  },
  {
    NULL
  }
};

/* The priority relationhip between every two operator */

/* AND   OR    NOT   (     )     #  */
UINT32          Priority[6][6] = {
  {
    HIGHP,
    HIGHP,
    LOWP,
    LOWP,
    HIGHP,
    HIGHP
  },

  /* AND */
  {
    HIGHP,
    HIGHP,
    LOWP,
    LOWP,
    HIGHP,
    HIGHP
  },

  /* OR */
  {
    HIGHP,
    HIGHP,
    HIGHP,
    LOWP,
    HIGHP,
    HIGHP
  },

  /* NOT */
  {
    LOWP,
    LOWP,
    LOWP,
    LOWP,
    EQUAP,
    ERRP
  },

  /* ( */
  {
    HIGHP,
    HIGHP,
    HIGHP,
    ERRP,
    HIGHP,
    HIGHP
  },

  /* ) */
  {
    LOWP,
    LOWP,
    LOWP,
    LOWP,
    ERRP,
    EQUAP
  }
};  /* # */

STATIC
VOID_P
InitOperandStack (
  VOID_P
  )
/*++

Routine Description:

  Initialize the Stack of Operand

Arguments:

  VOID_P - None

Returns:

  None

--*/
{
  BOOLEAN *PacketPointer;
  UINT32  Index;
  PacketPointer = Operands;
  for (Index = 0; Index < EXPR_MAX_LEN; Index++) {
    PacketPointer[Index] = TRUE;
  }
}

STATIC
VOID_P
PushOperandStack (
  IN BOOLEAN Value
  )
/*++

Routine Description:

  Push an Operand into Stack.

Arguments:

  Value - The Operand to push.

Returns:

  None

--*/
{
  *OperandTop = Value;
  OperandTop += 1;
}

STATIC
BOOLEAN
PopOperandStack (
  VOID_P
  )
/*++

Routine Description:

  Pop an Operand from Stack.

Arguments:

  None

Returns:

  The Operand on top of stack.

--*/
{
  OperandTop -= 1;
  return *OperandTop;
}

STATIC
BOOLEAN
GetTopOperandStack (
  VOID_P
  )
/*++

Routine Description:

  Just get the top Operand from Stack, without any change to stack pointer.

Arguments:

  None

Returns:

  The Operand on top of stack.

--*/
{
  return *(OperandTop - 1);
}

STATIC
VOID_P
InitOperatorStack (
  VOID_P
  )
/*++

Routine Description:

  Initialize the Operator Stack.

Arguments:

  None

Returns:

  None

--*/
{
  INT8    *PacketPointer;
  UINT32  Index;
  PacketPointer = Operators;

  for (Index = 0; Index < EXPR_MAX_LEN; Index++) {
    PacketPointer[Index] = -1;
  }
}

/*++

Routine Description:
   Push an Operator into Stack.
Argumems:
   The Operator to push.
Returns:
--*/
STATIC
VOID_P
PushOperatorStack (
  IN INT8 Value
  )
/*++

Routine Description:

  Push an Operator into Stack.

Arguments:

  Value - The Operator to push.

Returns:

  None

--*/
{
  *OperatorTop = Value;
  OperatorTop += 1;
}

STATIC
INT8
PopOperatorStack (
  VOID_P
  )
/*++

Routine Description:

  Pop an Operator from Stack.

Arguments:

  None

Returns:

  The Operator on top of stack.

--*/
{
  OperatorTop -= 1;
  return *OperatorTop;
}

STATIC
INT8
GetTopOperatorStack (
  VOID_P
  )
/*++

Routine Description:

  Just get the top Operator from Stack, without any change to stack pointer.

Arguments:

  None

Returns:

  The Operator on top of stack.

--*/
{
  return *(OperatorTop - 1);
}

STATIC
INT8
GetOperatorIndex (
  IN INT8 *OperatorName
  )
/*++

Routine Description:

  Get index of the Operator for convenience of comparing priority.

Arguments:

  OperatorName - The Operator per se.'+','-',etc..

Returns:

  The Operator's index.

--*/
{
  UINT32  Index;
  for (Index = 0; OperatorList[Index].Name; Index++) {
    if (strlen (OperatorList[Index].Name) > strlen (OperatorName)) {
      continue;
    }

    if (!(strncmp (OperatorList[Index].Name, OperatorName, strlen (OperatorList[Index].Name)))) {
      return Index;
    }
  }

  return -1;
}

STATIC
UINT8
ComparePriority (
  IN INT8 Operator1,
  IN INT8 Operator2
  )
/*++

Routine Description:

  Compare priorities between two operators.

Arguments:

  Operator1 - The operators.
  Operator2 - The operators.

Returns:

  HIGHP, LOWP, EQUAP or ERRP

--*/
{
  return Priority[Operator1][Operator2];
}

STATIC
BOOLEAN
OneStepCalculate (
  IN INT8        Operation,
  IN BOOLEAN     Operand1,
  IN BOOLEAN     Operand2
  )
/*++

Routine Description:

  Just execute a step of calculate

Arguments:

  Operation - The Operator,'AND' 'OR' 'NOT' '/'
  Operand1  - The 1st operand
  Operand2  - The 2nd operand

Returns:

  The calculated result.

--*/
{
  BOOLEAN Result;
  Result = TRUE;

  switch (Operation) {
  case OP_AND:
    Result = Operand1 ? Operand2 : FALSE;
    break;

  case OP_OR:
    Result = Operand1 ? TRUE : Operand2;
    break;

  case OP_NOT:
    Result = Operand2 ? FALSE : TRUE;
    break;

  default:
    break;
  }

  return Result;
}

STATIC
BOOLEAN
GetOperand (
  IN     INT8      *ExprP,
  IN     FIELD_T   *Unpack,
  IN OUT UINT32    *Offset
  )
/*++

Routine Description:

  Calculate a Bool expression. 
  e.g. "ip_addr=192.168.88.1"

Arguments:

  ExprP   - The expression
  Unpack  - The Data
  Offset  - The offset the calculation end

Returns:

  Calculated result.

--*/
{
  BOOLEAN Result;
  INT32   Status;
  UINT32  Index;
  UINT32  AddrIndex;
  UINT32  Len;
  UINT32  Value;
  EMS_IPV6_ADDR IPv6Addr;
  UINT8   Eth[6];

  Result = FALSE;
  //
  // Find first '='
  //
  for (Len = 0; ExprP[Len]; Len++) {
    if (ExprP[Len] == '=') {
      break;
    }
  }

  if (ExprP[Len] == '\0') {
    return Result;

  }

  Len++;

  for (; ExprP[Len]; Len++) {
    if (ExprP[Len] != ' ') {
      break;
    }
  }

  *Offset = Len;

  for (Index = 0; Unpack[Index].Name; Index++) {
    if (0 == strncmp_i (Unpack[Index].Name, ExprP, strlen (Unpack[Index].Name))) {

      switch (Unpack[Index].Type) {
      case OCTET1:
        Status = AsciiStringToUint32 (ExprP + Len, &Value);
        if (Status <= 0) {
          return ERROR_WRONGFORMAT;
        }

        *Offset += Status;
        if ((UINT8) Value == * (UINT8 *) (Unpack[Index].Value)) {
          return TRUE;
        } else {
          return FALSE;
        }

      case OCTET2:
        Status = AsciiStringToUint32 (ExprP + Len, &Value);
        if (Status < 0) {
          return ERROR_WRONGFORMAT;
        }

        *Offset += Status;
        if ((UINT16) Value == * (UINT16 *) (Unpack[Index].Value)) {
          return TRUE;
        } else {
          return FALSE;
        }

      case OCTET4:
        Status = AsciiStringToUint32 (ExprP + Len, &Value);
        if (Status < 0) {
          return ERROR_WRONGFORMAT;
        }

        *Offset += Status;
        if (*(UINT32 *) (Unpack[Index].Value) == (UINT32) Value) {
          return TRUE;
        } else {
          return FALSE;
        }

      case IPADDR:
        Status = AsciiStringToIpv4 (ExprP + Len, &Value);
        if (Status < 0) {
          return ERROR_WRONGFORMAT;
        }

        *Offset += Status;
        if (*(UINT32 *) (Unpack[Index].Value) == (UINT32) Value) {
          return TRUE;
        } else {
          return FALSE;
        }
		
	  case IPV6ADDR:
        Status = AsciiStringToIpv6 (ExprP + Len, &IPv6Addr);
        if (Status <= 0) {
          return ERROR_WRONGFORMAT;
        }

        *Offset += Status;
		for (AddrIndex = 0; AddrIndex< 8 ; AddrIndex++){
          if (((EMS_IPV6_ADDR*)Unpack[Index].Value)->__u6_addr.__u6_addr16[AddrIndex] != 
		  	    IPv6Addr.__u6_addr.__u6_addr16[AddrIndex]){
            return FALSE;
		  }
		}
		return TRUE;

      case MACADDR:
        Status = AsciiStringToMac (ExprP + Len, Eth);
        if (Status < 0) {
          return ERROR_WRONGFORMAT;
        }

        *Offset += Status;
        if (0 == memcmp (Unpack[Index].Value, Eth, 6)) {
          return TRUE;
        } else {
          return FALSE;
        }

      case STRING:
        if (Len != strlen (*(INT8 **) Unpack[Index].Value)) {
          return FALSE;
        }

        if (0 == strncmp (*(INT8 **) Unpack[Index].Value, ExprP + Len, Len)) {
          return TRUE;
        } else {
          return FALSE;
        }

      case PAYLOAD:
      //
      // How to validata payload ???
      // Now case writer has to use "ParsePacket" to store the payload into
      // a packet then validate it.
      //
      default:
        return ERROR_INTERNAL;
      }
    }
  }

  return FALSE;
}

BOOLEAN
Validate (
  IN INT8      *Pattern,
  IN FIELD_T   *Unpack
  )
/*++

Routine Description:

  The main process of validate

Arguments:

  Pattern - The pattern validation
  Unpack  - The Data

Returns:

  Calculated result.

--*/
{

  INT8    *ExprP;
  INT8    CurrentOperator;
  INT8    TempOperator;
  BOOLEAN Operand1;
  BOOLEAN Operand2;
  BOOLEAN TempResult;
  UINT32  ExprLenth;
  UINT32  Offset;

  if (NULL == Unpack || NULL == Pattern) {
    return FALSE;
  }

  strcpy (Expression, Pattern);

  InitOperatorStack ();
  InitOperandStack ();
  Operators[0]          = OP_CRS;
  ExprLenth             = strlen (Expression);
  Expression[ExprLenth] = '#';
  ExprP                 = Expression;
  OperatorTop           = Operators + 1;
  OperandTop            = Operands;

  while (*ExprP) {
    if (('#' == *ExprP) && (OP_CRS == GetTopOperatorStack ())) {
      break;
    }

    TempOperator = GetOperatorIndex (ExprP);

    if (TempOperator >= 0) {
      switch (ComparePriority (GetTopOperatorStack (), TempOperator)) {
      case HIGHP:
        CurrentOperator = PopOperatorStack ();
        Operand2        = PopOperandStack ();
        Operand1        = PopOperandStack ();
        TempResult      = OneStepCalculate (CurrentOperator, Operand1, Operand2);
        PushOperandStack (TempResult);
        break;

      case LOWP:
        PushOperatorStack (TempOperator);
        if (TempOperator == OP_NOT) {
          PushOperandStack (TRUE);
        }

        ExprP += strlen (OperatorList[TempOperator].Name);
        break;

      case EQUAP:
        PopOperatorStack ();
        ExprP += 1;
        break;

      default:
        return -1;
        break;
      }
    } else if (' ' == *ExprP) {
      ExprP += 1;
    } else {
      TempResult = GetOperand (ExprP, Unpack, &Offset);
      ExprP += Offset;
      PushOperandStack (TempResult);
    }
  }

  return GetTopOperandStack ();
}
