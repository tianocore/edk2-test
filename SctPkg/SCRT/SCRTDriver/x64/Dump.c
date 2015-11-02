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
  Printf("\n================Dump Runtime Table===============\n");
  Printf("Header Signature = 0x%x\n", VRT->Hdr.Signature);

  Printf("\n================GetTime Service==============\n");
  Printf("GetTime @ 0x%x\n", VRT->GetTime);

  Printf("\n================SetTime Service==============\n");
  Printf("SetTime @ 0x%x\n", VRT->SetTime);

  Printf("\n================GetWakeupTime Service==============\n");
  Printf("GetWakeupTime @ 0x%x\n", VRT->GetWakeupTime);

  Printf("\n================SetWakeupTime Service==============\n");
  Printf("SetWakeupTime @ 0x%x\n", VRT->SetWakeupTime);

  Printf("\n================GetVariable Service==============\n");
  Printf("GetVariable @ 0x%x\n", VRT->GetVariable);

  Printf("\n================GetNextVariableName Service==============\n");
  Printf("GetNextVariableName @ 0x%x\n", VRT->GetNextVariableName);

  Printf("\n================SetVariable Service==============\n");
  Printf("SetVariable @ 0x%x\n", VRT->SetVariable);

  Printf("\n================GetNextHighMonotonicCount Service==============\n");
  Printf("GetNextHighMonotonicCount @ 0x%x\n", VRT->GetNextHighMonotonicCount);

  Printf("\n================ResetSystem Service==============\n");
  Printf("ResetSystem @ 0x%x\n", VRT->ResetSystem);
#if 0
  Printf("\n================UpdateCapsule Service==============\n");
  Printf("UpdateCapsule @ 0x%x\n", VRT->UpdateCapsule);

  Printf("\n================QueryCapsuleCapabilities Service==============\n");
  Printf("QueryCapsuleCapabilities @ 0x%x\n", VRT->QueryCapsuleCapabilities);

  Printf("\n================QueryVariableInfo Service==============\n");
  Printf("QueryVariableInfo @ 0x%x\n", VRT->QueryVariableInfo);
#endif
}
