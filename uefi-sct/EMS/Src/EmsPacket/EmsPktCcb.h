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
  
    EmsPktCcb.h
    
Abstract:

    

--*/

#ifndef _EMS_CCB_TCL_H_
#define _EMS_CCB_TCL_H_
#include "EmsVtcpTcb.h"
#include "EmsTypes.h"
#include "EmsPktCapture.h"

typedef struct _CCB_FIELD {
  INT8    *Name;
  UINT32  Offset;
} CCB_FIELD;

STATIC CCB_FIELD  CcbFields[] = {
  {
    "received",
    _OFFSET(CCB, Received)
  },
  {
    "receiveLen",
    _OFFSET(CCB, ReceiveLen)
  },
  {
    NULL,
    0
  }
};

VOID_P
EmsCcbCreateTcls (
  Tcl_Interp *Interp,
  IN CONST INT8       *Name,
  CCB        *Ccb
  )
/*++

Routine Description:

  Create corresponding TCL variables accroding to CCB

Arguments:

  Interp      - TCL intepreter.
  Name    - The name of variable
  Ccb     - CCB context.

Returns:

  None

--*/
;

VOID_P
EmsCcbDestroyTcls (
  Tcl_Interp       *Interp,
  CONST INT8       *Name
  )
/*++

Routine Description:

  Destroy the corresponding TCL variables accroding to CCB

Arguments:

  Interp      - TCL intepreter.
  Name    - The name of variable

Returns:

  None

--*/
;

#endif
