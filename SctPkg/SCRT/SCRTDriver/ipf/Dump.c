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

  Dump.c

--*/

#include "SCRTDriver.h"


VOID
DumpRuntimeTable()
{
  EFI_PLABEL  *Plabel;
  SctAPrint ("\n================Dump Runtime Table===============\n");
  SctAPrint ("Header Signature = 0x%x\n", VRT->Hdr.Signature);

  SctAPrint ("\n================GetTime Service==============\n");
  SctAPrint ("GetTime @ 0x%x\n", VRT->GetTime);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetTime);
  SctAPrint ("GetTime Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("GetTime Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================SetTime Service==============\n");
  SctAPrint ("SetTime @ 0x%x\n", VRT->SetTime);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->SetTime);
  SctAPrint ("SetTime Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("SetTime Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================GetWakeupTime Service==============\n");
  SctAPrint ("GetWakeupTime @ 0x%x\n", VRT->GetWakeupTime);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetWakeupTime);
  SctAPrint ("GetWakeupTime Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("GetWakeupTime Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================SetWakeupTime Service==============\n");
  SctAPrint ("SetWakeupTime @ 0x%x\n", VRT->SetWakeupTime);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->SetWakeupTime);
  SctAPrint ("SetWakeupTime Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("SetWakeupTime Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================GetVariable Service==============\n");
  SctAPrint ("GetVariable @ 0x%x\n", VRT->GetVariable);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetVariable);
  SctAPrint ("GetVariable Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("GetVariable Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================GetNextVariableName Service==============\n");
  SctAPrint ("GetNextVariableName @ 0x%x\n", VRT->GetNextVariableName);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetNextVariableName);
  SctAPrint ("GetNextVariableName Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("GetNextVariableName Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================SetVariable Service==============\n");
  SctAPrint ("SetVariable @ 0x%x\n", VRT->SetVariable);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->SetVariable);
  SctAPrint ("SetVariable Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("SetVariable Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================GetNextHighMonotonicCount Service==============\n");
  SctAPrint ("GetNextHighMonotonicCount @ 0x%x\n", VRT->GetNextHighMonotonicCount);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetNextHighMonotonicCount);
  SctAPrint ("GetNextHighMonotonicCountPlabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("GetNextHighMonotonicCount Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================ResetSystem Service==============\n");
  SctAPrint ("ResetSystem @ 0x%x\n", VRT->ResetSystem);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->ResetSystem);
  SctAPrint ("ResetSystem Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("ResetSystem Plabel.GP @ 0x%x\n", Plabel->GP);
#if 0
  SctAPrint ("\n================UpdateCapsule Service==============\n");
  SctAPrint ("UpdateCapsule @ 0x%x\n", VRT->UpdateCapsule);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->UpdateCapsule);
  SctAPrint ("UpdateCapsule Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("UpdateCapsule Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================QueryCapsuleCapabilities Service==============\n");
  SctAPrint ("QueryCapsuleCapabilities @ 0x%x\n", VRT->QueryCapsuleCapabilities);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->QueryCapsuleCapabilities);
  SctAPrint ("QueryCapsuleCapabilities Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("QueryCapsuleCapabilities Plabel.GP @ 0x%x\n", Plabel->GP);

  SctAPrint ("\n================QueryVariableInfo Service==============\n");
  SctAPrint ("QueryVariableInfo @ 0x%x\n", VRT->QueryVariableInfo);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->QueryVariableInfo);
  SctAPrint ("QueryVariableInfo Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  SctAPrint ("QueryVariableInfo Plabel.GP @ 0x%x\n", Plabel->GP);
#endif
}
