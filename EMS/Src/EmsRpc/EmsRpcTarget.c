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
  
    EmsRpcTarget.c
    
Abstract:

    Implementation of RPC target related Functions

--*/

#include "EmsTypes.h"
#include "EmsMain.h"
#include "EmsUtilityString.h"
#include "EmsRpcTarget.h"

STATIC TARGET_T *Targets = NULL;

VOID_P
RpcTargetAddByMac (
  INT8      *Mac
  )
/*++

Routine Description:

  Add a target identified by MAC address

Arguments:

  Mac - The MAC address

Returns:

  None

--*/
{
  TARGET_T  *Node;
  TARGET_T  *TargetPointer;

  if (Mac == NULL) {
    return ;

  }

  Node = malloc (sizeof (TARGET_T));
  if (Node == NULL) {
    return ;
  }

  memcpy (Node->Mac, Mac, 6);

  if (Targets == NULL) {
    Targets     = Node;
    Node->Next  = NULL;
    return ;
  }

  for (TargetPointer = Targets; TargetPointer->Next; TargetPointer = TargetPointer->Next)
    ;

  TargetPointer->Next = Node;
  Node->Next          = NULL;
  return ;
}

TARGET_T *
RpcTargetFindByMac (
  INT8            *Mac
  )
/*++

Routine Description:

  Find the taget by MAC address

Arguments:

  Mac - MAC address

Returns:

  The target found

--*/
{
  TARGET_T  *TargetPointer;

  TargetPointer = Targets;
  while (TargetPointer) {
    if (0 == memcmp (Mac, TargetPointer->Mac, 6)) {
      break;
    }

    TargetPointer = TargetPointer->Next;
  }

  return TargetPointer;
}

VOID_P
RpcTargetRemoveAll (
  VOID_P
  )
/*++

Routine Description:

  Remove all the target

Arguments:

  None.

Returns:

  None

--*/
{
  TARGET_T  *TargetPointer;

  TARGET_T  *TargetPointer1;

  //
  // remove header of the list
  //
  TargetPointer = Targets;
  while (TargetPointer != NULL) {
    TargetPointer1 = TargetPointer->Next;
    free (TargetPointer);
    TargetPointer = TargetPointer1;
  }

  Targets = NULL;
}
//
// dump all Targets to buffer
//
VOID_P
RpcTargetDumpAll (
  INT8        *Buff
  )
/*++

Routine Description:

  Dump all the targets

Arguments:

  Buff  - The Buffer to contain targets

Returns:

  None

--*/
{
  TARGET_T  *TargetPointer;
  INT8      Str[18];

  TargetPointer = Targets;
  if (NULL == TargetPointer) {
    return ;
  }

  Buff[0] = '\0';
  while (TargetPointer) {
    MacToAsciiString (Str, TargetPointer->Mac);
    strcat (Buff, Str);
    TargetPointer = TargetPointer->Next;
  }
}
