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

  RivlVariable.h

Abstract:

  Remote Interface Validation Language Variable definitions

--*/

#ifndef __RIVL_VARIABLE_H__
#define __RIVL_VARIABLE_H__

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
;

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
;

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
;

#endif // __RIVL_VARIABLE_H__
