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
  
    EmsTest.h
    
Abstract:

  Incude header files for EMS Test functions

--*/

#ifndef __EMS_TEST_H__
#define __EMS_TEST_H__

#include "tcl.h"
#include "EmsTypes.h"

typedef struct _TESTCASE_LIST_ENTRY {
  struct _TESTCASE_LIST_ENTRY *Next;
  UINT8                       CasePath[256];
  UINT8                       CaseName[64];
} TESTCASE_LIST_ENTRY;

typedef struct _TESTCASE_LIST_HEAD {
  TESTCASE_LIST_ENTRY *Head;
  TESTCASE_LIST_ENTRY *Tail;
  UINT32              EntryNum;
} TESTCASE_LIST_HEAD;

STATIC Tcl_CmdProc  EmsTestInit;
STATIC Tcl_CmdProc  EmsTestCaseScriptEval;
STATIC Tcl_CmdProc  EmsRemoteValidationTestStart;
STATIC Tcl_CmdProc  EmsRemoteValidationTestStop;
STATIC Tcl_CmdProc  EmsRemoteValidationTestContinue;
STATIC Tcl_CmdProc  EmsTestIsRunning;
STATIC Tcl_CmdProc  EmsThreadCmd;
STATIC Tcl_CmdProc  RemoteValidationTestCaseAllPost;

INT32
EmsTestInit (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsTestInit" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
;

INT32
EmsThreadCmd (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsThreadCmd" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
;

INT32
EmsTestCaseScriptEval (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsTestCaseScriptEval" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
;

INT32
EmsRemoteValidationTestStop (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsRemoteValidationTestStop" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK

--*/
;

INT32
EmsRemoteValidationTestStart (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsRemoteValidationTestStart" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK

--*/
;

INT32
EmsTestIsRunning (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsTestIsRunning" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK

--*/
;

VOID
EmsTestTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS test related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

#endif
