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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
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
  Printf("\n================Dump Runtime Table===============\n");
  Printf("Header Signature = 0x%x\n", VRT->Hdr.Signature);

  Printf("\n================GetTime Service==============\n");
  Printf("GetTime @ 0x%x\n", VRT->GetTime);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetTime);
  Printf("GetTime Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("GetTime Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================SetTime Service==============\n");
  Printf("SetTime @ 0x%x\n", VRT->SetTime);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->SetTime);
  Printf("SetTime Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("SetTime Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================GetWakeupTime Service==============\n");
  Printf("GetWakeupTime @ 0x%x\n", VRT->GetWakeupTime);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetWakeupTime);
  Printf("GetWakeupTime Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("GetWakeupTime Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================SetWakeupTime Service==============\n");
  Printf("SetWakeupTime @ 0x%x\n", VRT->SetWakeupTime);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->SetWakeupTime);
  Printf("SetWakeupTime Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("SetWakeupTime Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================GetVariable Service==============\n");
  Printf("GetVariable @ 0x%x\n", VRT->GetVariable);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetVariable);
  Printf("GetVariable Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("GetVariable Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================GetNextVariableName Service==============\n");
  Printf("GetNextVariableName @ 0x%x\n", VRT->GetNextVariableName);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetNextVariableName);
  Printf("GetNextVariableName Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("GetNextVariableName Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================SetVariable Service==============\n");
  Printf("SetVariable @ 0x%x\n", VRT->SetVariable);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->SetVariable);
  Printf("SetVariable Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("SetVariable Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================GetNextHighMonotonicCount Service==============\n");
  Printf("GetNextHighMonotonicCount @ 0x%x\n", VRT->GetNextHighMonotonicCount);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->GetNextHighMonotonicCount);
  Printf("GetNextHighMonotonicCountPlabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("GetNextHighMonotonicCount Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================ResetSystem Service==============\n");
  Printf("ResetSystem @ 0x%x\n", VRT->ResetSystem);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->ResetSystem);
  Printf("ResetSystem Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("ResetSystem Plabel.GP @ 0x%x\n", Plabel->GP);
#if 0
  Printf("\n================UpdateCapsule Service==============\n");
  Printf("UpdateCapsule @ 0x%x\n", VRT->UpdateCapsule);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->UpdateCapsule);
  Printf("UpdateCapsule Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("UpdateCapsule Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================QueryCapsuleCapabilities Service==============\n");
  Printf("QueryCapsuleCapabilities @ 0x%x\n", VRT->QueryCapsuleCapabilities);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->QueryCapsuleCapabilities);
  Printf("QueryCapsuleCapabilities Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("QueryCapsuleCapabilities Plabel.GP @ 0x%x\n", Plabel->GP);

  Printf("\n================QueryVariableInfo Service==============\n");
  Printf("QueryVariableInfo @ 0x%x\n", VRT->QueryVariableInfo);
  Plabel = (EFI_PLABEL *)((VOID*)VRT->QueryVariableInfo);
  Printf("QueryVariableInfo Plabel.Entry @ 0x%x\n", Plabel->EntryPoint);
  Printf("QueryVariableInfo Plabel.GP @ 0x%x\n", Plabel->GP);
#endif
}
