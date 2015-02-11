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
  
    EmsRivlFunc.c
    
Abstract:

    Implementation of RIVL function related Functions

--*/

#include "EmsRivlMain.h"
#include "EmsRivlFunc.h"
#include "stdlib.h"

STATIC RIVL_FUNCTION  *Functions = NULL;

RIVL_FUNCTION *
RivlFunctionFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find a Rivl function type's variable accroding to name

Arguments:

  Name  - 

Returns:

  return the found variable

--*/
{
  RIVL_FUNCTION *FPointer;
  FPointer = Functions;
  while (FPointer) {
    if (0 == strcmp (Name, FPointer->Name)) {
      break;
    }

    FPointer = FPointer->Next;
  }

  return FPointer;
}

BOOLEAN
FunctionExist (
  INT8 *Name
  )
/*++

Routine Description:

  Check whether the Rivl function type's variable is exist

Arguments:

  Name  - The name of the Rivl function

Returns:

  TRUE or FALSE

--*/
{
  return RivlFunctionFindByName (Name) ? TRUE : FALSE;
}

VOID_P
RivlFunctionRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove a Rivl function type's variable accroding to name

Arguments:

  Name  - The name of the function

Returns:

  None

--*/
{
  RIVL_FUNCTION *FPointer;

  if (Functions == NULL) {
    return ;
  }

  if (strcmp (Name, Functions->Name)) {
    Functions = Functions->Next;
    return ;
  }

  for (FPointer = Functions; FPointer && FPointer->Next; FPointer = FPointer->Next) {
    if (0 == strcmp (Name, FPointer->Next->Name)) {
      FPointer->Next = FPointer->Next->Next;
      return ;
    }
  }
}

VOID_P
RivlFunctionDestroy (
  RIVL_FUNCTION *Func
  )
/*++

Routine Description:

  Destroy a Rivl function

Arguments:

  Func  - The pointer to a Rivl function

Returns:

  None

--*/
{
  if (Func) {
    free (Func);
  }
}

VOID_P
RivlFunctionAdd (
  RIVL_FUNCTION *Func
  )
/*++

Routine Description:

  Add a new Rivl function

Arguments:

  Func  - The pointer to a Rivl function

Returns:

  None

--*/
{
  RIVL_FUNCTION *FPointer;
  if (Func == NULL) {
    return ;
  }

  if (Functions == NULL) {
    Functions   = Func;
    Func->Next  = NULL;
    return ;
  }

  for (FPointer = Functions; FPointer->Next; FPointer = FPointer->Next)
    ;
  FPointer->Next  = Func;
  Func->Next      = NULL;
  return ;
}

VOID_P
RivlFunctionRemoveAll (
  VOID_P
  )
/*++

Routine Description:

  Remove all the Rivl functions

Arguments:

  None

Returns:

  None

--*/
{
  RIVL_FUNCTION *FPointer;

  //
  // remove header of the list
  //
  while (FPointer = Functions) {
    Functions = FPointer->Next;
    RivlFunctionDestroy (FPointer);
  }
}
