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
  
    EmsTclCleanup.c
    
Abstract:

  Implementation of EMS TCL cleanup function.

--*/

#include <windows.h>
#include "EmsTclCleanup.h"

STATIC EmsTclResMng *EmsTclResStack;
STATIC HANDLE       EmsTclResStackMutex;

VOID
EmsTclResStackPush (
  EmsTclResMng *Mng
  )
/*++

Routine Description:

  Push a EMS TCL resource into stack

Arguments:

  Mng - The structure for the EMS TCL resource management

Returns:

  None

--*/
{
  WaitForSingleObject (EmsTclResStackMutex, INFINITE);
  Mng->Next       = EmsTclResStack;
  EmsTclResStack  = Mng;
  ReleaseMutex (EmsTclResStackMutex);
}

VOID
EmsTclResStackPop (
  EmsTclResMng **Mng
  )
/*++

Routine Description:

  Pop a EMS TCL resource from stack

Arguments:

  Mng - The structure for the EMS TCL resource management

Returns:

  None

--*/
{
  *Mng            = EmsTclResStack;
  EmsTclResStack  = EmsTclResStack->Next;
  (*Mng)->Next    = NULL;
}

STATIC
BOOLEAN
EmsTclResStackIsEmpty (
  VOID
  )
/*++

Routine Description:

  Check whether the EMS TCL resouce stack is empty

Arguments:

  None

Returns:

  TRUE or FALSE

--*/
{
  BOOLEAN Result;
  Result = (EmsTclResStack == NULL) ? TRUE : FALSE;
  return Result;
}

STATIC
INT32
EmsTclResCleanup (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "EmsTclResCleanup" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  EmsTclResMng  *Temp;
  Temp = NULL;
  WaitForSingleObject (EmsTclResStackMutex, INFINITE);
  while (!EmsTclResStackIsEmpty ()) {
    EmsTclResStackPop (&Temp);
    ReleaseMutex (EmsTclResStackMutex);
    (Temp->CleanupFunc) (Temp->Res);
    WaitForSingleObject (EmsTclResStackMutex, INFINITE);
  }

  ReleaseMutex (EmsTclResStackMutex);
  return TCL_OK;
}

VOID_P
ResTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS cleanup related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  EmsTclResStack      = NULL;
  EmsTclResStackMutex = CreateMutex (NULL, FALSE, NULL);

  Tcl_CreateCommand (
    Interp,
    "EmsTclResCleanup",
    EmsTclResCleanup,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
}
