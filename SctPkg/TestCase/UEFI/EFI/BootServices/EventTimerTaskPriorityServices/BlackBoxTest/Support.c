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

  Support.c

Abstract:

  Test Driver of Event and Timer and Task Priority Services

--*/

#include "EventTimerTaskPriorityServicesBBTestMain.h"


VOID
NotifyFunction (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  UINTN     *Buffer;

  if (Context != NULL) {
    Buffer = Context;

    Buffer[1]++;
    if (Buffer[1] <= Buffer[0]) {
      Buffer[1 + Buffer[1]] = (UINTN) Event;
    }
  }

  return;
}

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
VOID
NotifyFunctionTplEx(
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  UINTN     *Buffer;
  EFI_TPL   OldTpl;
  UINTN     EventIndex;
  UINTN     Index;
  
  if (Context != NULL) {
    Buffer = Context;

    EventIndex = Buffer[0];

    Index = 3-EventIndex;

    while (1) {     
      if (Buffer[Index] == (UINTN)(-1)) {
        break;
      } else {
        Index += 2;
      }
    }
    
    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);

    Buffer[Index] = EventIndex;
    Buffer[Index+1] = OldTpl;
  }

  return;
}
#endif

VOID
NotifyFunctionTpl (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  UINTN     *Buffer;
  EFI_TPL   OldTpl;

  if (Context != NULL) {
    Buffer = Context;

    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);

    Buffer[1]++;
    if (Buffer[1] <= Buffer[0]) {
      Buffer[1 + Buffer[1]] = (UINTN) OldTpl;
    }
  }

  return;
}


VOID
NotifyFunctionSignal (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  gtBS->SignalEvent (Event);
  return;
}

VOID
NotifyFunctionNoSignal (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  return;
}
