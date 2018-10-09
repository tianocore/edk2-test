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
  
    EmsPktValidate.h
    
Abstract:

    Incude header files for packet validate

--*/

#ifndef __EMS_VALIDATE_H__
#define __EMS_VALIDATE_H__

#include "EmsTclInit.h"

#define EXPR_MAX_LEN  256

#define HIGHP         1
#define LOWP          2
#define ERRP          3
#define EQUAP         0

#define IsDigit(c)    (c >= '0' && c <= '9')

typedef struct _OPERATOR_T {
  INT8  *Name;
} OPERATOR_T;

VOID_P
ValidateTclInit (
  Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet validation related TCL command initialization routine

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

#endif
