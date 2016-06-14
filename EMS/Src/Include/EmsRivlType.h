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
  
    EmsRivlType.h
    
Abstract:

    Incude header files for RIVL type functions

--*/

#ifndef _RIVL_TYPE_H_
#define _RIVL_TYPE_H_

#include "EmsRivlMain.h"

#define BOOLEAN_TYPE  0
#define INTN_TYPE     1
#define UINTN_TYPE    2
#define INT8_TYPE     3
#define UINT8_TYPE    4
#define INT16_TYPE    5
#define UINT16_TYPE   6
#define INT32_TYPE    7
#define UINT32_TYPE   8
#define INT64_TYPE    9
#define CHAR8_TYPE    10
#define CHAR16_TYPE   11
#define VOID_TYPE     12

RIVL_TYPE     *
RivlTypeFindByName (
  INT8 *Name
  )
/*++

Routine Description:

  Find RIVL variable's type accroding to name

Arguments:

  Name  - The type name

Returns:

  return the RIVL type found

--*/
;

VOID_P
RivlTypeRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove RIVL type accroding to name

Arguments:

  Name  - The type name

Returns:

  None

--*/
;

VOID_P
RivlTypeAdd (
  RIVL_TYPE *Type
  )
/*++

Routine Description:

  Add a new RIVL type

Arguments:

  Type  - The RIVL type to be added

Returns:

  None

--*/
;

VOID_P
RivlTypeDestroy (
  RIVL_TYPE *Type
  )
/*++

Routine Description:

  Destroy a RIVL type

Arguments:

  Type  - The RIVL type to be destroied

Returns:

  None

--*/
;

VOID_P
RivlTypeDestroyAll (
  VOID_P
  )
/*++

Routine Description:

  Destroy all the RIVL types

Arguments:

  None

Returns:

  None

--*/
;

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
;

#endif
