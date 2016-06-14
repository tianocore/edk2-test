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
  
    EmsRivlTclVar.c
    
Abstract:

    Implementation of RIVL TCL variables related functions
    Because some RIVL commands just like GetVar will create some TCL variables
    to store the value, all the TCL variables should be recorded and deleted 
    when they are unuseful any longer. Generally, they will be deleted when the 
    RIVL command "EndScope" or "DelVar" is called.
    
--*/

#include <stdlib.h>
#include "EmsRivlMain.h"
#include "EmsRivlTclVar.h"
#include "tcl.h"

STATIC RIVL_TCL_VARIABLES *TclVars = NULL;

RIVL_TCL_VARIABLES *
RivlTclVarsFindByName (
  INT8                    *Name
  )
/*++

Routine Description:

  Find one group of Rivl TCL variables accroding to name

Arguments:

  Name  - The name of the group

Returns:

  return the pointer to the group of Rivl variables found

--*/
{
  RIVL_TCL_VARIABLES  *VPointer;
  VPointer = TclVars;
  while (VPointer) {
    if (0 == strcmp (Name, VPointer->Name)) {
      break;
    }

    VPointer = VPointer->Next;
  }

  return VPointer;
}

RIVL_TCL_VARIABLE *
RivlTclVarFindByName (
  RIVL_TCL_VARIABLES    *Vars,
  INT8                  *Name
  )
/*++

Routine Description:

  Find a Rivl TCL variable accroding to name

Arguments:

  Name  - The name of the variable

Returns:

  return the pointer to the Rivl variable found

--*/
{
  RIVL_TCL_VARIABLE *VPointer;

  if (!Vars) {
    return NULL;
  }

  VPointer = Vars->Head;

  while (VPointer) {
    if (0 == strcmp (Name, VPointer->Name)) {
      break;
    }

    VPointer = VPointer->Next;
  }

  return VPointer;
}

BOOLEAN
TclVarsExist (
  INT8                    *Name
  )
/*++

Routine Description:

  Check whether the group of TCL variable exists

Arguments:

  Name  - The name of the group

Returns:

  TRUE or FALSE

--*/
{
  return RivlTclVarsFindByName (Name) ? TRUE : FALSE;
}

BOOLEAN
TclVarExist (
  RIVL_TCL_VARIABLES     *Vars,
  INT8                   *Name
  )
/*++

Routine Description:

  Check whether the TCL variable exists

Arguments:

  Name  - The name of the variable

Returns:

  TRUE or FALSE

--*/
{
  return RivlTclVarFindByName (Vars, Name) ? TRUE : FALSE;
}

BOOLEAN
RivlAddTclVarsByName (
  INT8  *Name
  )
/*++

Routine Description:

  Add TCL variable by RIVL variable name

Arguments:

  Name  - The RIVL variable name

Returns:

  TRUE or FALSE

--*/
{
  RIVL_TCL_VARIABLES  *VPointer;
  RIVL_TCL_VARIABLES  *Vars;

  if (TclVarsExist (Name)) {
    //
    // if already exist, ==> do nothing
    //
    return TRUE;
  }

  Vars = malloc (sizeof (*Vars));
  if (!Vars) {
    return FALSE;
  }
  //
  // initialze this node
  //
  Vars->Name[0] = '\0';
  strcat (Vars->Name, Name);
  Vars->Head  = NULL;
  Vars->Next  = NULL;

  if (!TclVars) {
    //
    // insert to the head
    //
    TclVars = Vars;
    return TRUE;
  }
  //
  // append to the tail of the list
  //
  VPointer = TclVars;
  while (VPointer->Next) {
    VPointer = VPointer->Next;
  }

  VPointer->Next = Vars;
  return TRUE;
}

BOOLEAN
RivlAddTclVarByName (
  INT8  *VarName,
  INT8  *TclVarName
  )
/*++

Routine Description:

  Add TCL variable by RIVL variable name and TCL variable name

Arguments:

  VarName      - The RIVL variable name
  TclVarName   - The TCL variable name

Returns:

  TRUE or FALSE

--*/
{
  RIVL_TCL_VARIABLES  *Vars;
  RIVL_TCL_VARIABLE   *var;
  RIVL_TCL_VARIABLE   *VPointer;

  Vars = RivlTclVarsFindByName (VarName);
  if (Vars == NULL) {
    return FALSE;
  }

  if (TclVarExist (Vars, TclVarName)) {
    //
    // already exist
    //
    return TRUE;
  }
  //
  // alloc resource for this node
  //
  var = malloc (sizeof (*var));
  if (!var) {
    return TRUE;
  }
  //
  // initialize this node
  //
  var->Name[0] = '\0';
  strcat (var->Name, TclVarName);
  var->Next = NULL;

  if (!Vars->Head) {
    //
    // inset at the head of the list
    //
    Vars->Head = var;
    return TRUE;
  }
  //
  // append to the tail of the list
  //
  VPointer = Vars->Head;
  while (VPointer->Next) {
    VPointer = VPointer->Next;
  }

  VPointer->Next = var;

  return TRUE;
}

VOID_P
RivlRemoveTclVarsAll (
  Tcl_Interp        *Interp
  )
/*++

Routine Description:

  Remove all the TCL variables

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  RIVL_TCL_VARIABLES  *VPointer;

  VPointer = TclVars;

  while (VPointer) {
    TclVars = VPointer->Next;
    RivlRemoveTclVars (Interp, VPointer);
    VPointer = TclVars;
  }
}

VOID_P
RivlRemoveTclVarsByName (
  Tcl_Interp        *Interp,
  INT8              *Name
  )
/*++

Routine Description:

  Remove a TCL variable accroding to name

Arguments:

  Interp      - TCL intepreter.
  Name    - The variable name

Returns:

  None

--*/
{
  RIVL_TCL_VARIABLES  *VPointer;
  RIVL_TCL_VARIABLES  *Prev;

  VPointer  = TclVars;
  Prev      = NULL;
  //
  // sanity check
  //
  if (!VPointer) {
    return ;
  }

  if (!strcmp (VPointer->Name, Name)) {
    //
    // header is the TclVars to be removed ==>
    //      a). update link info
    //      b). free the header struct
    //
    TclVars = VPointer->Next;
    RivlRemoveTclVars (Interp, VPointer);
    return ;
  }

  Prev      = TclVars;
  VPointer  = VPointer->Next;
  while (VPointer) {
    if (0 == strcmp (Name, VPointer->Name)) {
      //
      // other node except for the header is the TclVars to be removed
      //    a). update link info
      //    b). free this node
      //
      Prev->Next = VPointer->Next;
      RivlRemoveTclVars (Interp, VPointer);
      VPointer = Prev->Next;
    } else {
      //
      // if not equal
      //
      Prev      = Prev->Next;
      VPointer  = VPointer->Next;
    }
  }
}

BOOLEAN
RivlRemoveTclVars (
  Tcl_Interp          *Interp,
  RIVL_TCL_VARIABLES  *Vars
  )
/*++

Routine Description:

  Remove all the TCL variables

Arguments:

  Interp      - TCL intepreter.
  Vars    - The RIVL variables

Returns:

  TRUE

--*/
{
  RIVL_TCL_VARIABLE *VPointer;
  INT32             Index;
  INT8              *TempName;
  VPointer = Vars->Head;

  while (VPointer) {
    Vars->Head = VPointer->Next;
    //
    // unlink the TCL Variable and free value
    // Consider if the Varaible is an array
    //
    TempName = _strdup ((INT8 *) VPointer->Name);
    for (Index = 0; (TempName[Index] != '(') && (TempName[Index] != '\0'); Index++)
      ;
    TempName[Index] = '\0';
    Tcl_UnsetVar (Interp, TempName, TCL_GLOBAL_ONLY);
    free (TempName);

    free (VPointer);
    VPointer = Vars->Head;
  }

  return TRUE;
}
