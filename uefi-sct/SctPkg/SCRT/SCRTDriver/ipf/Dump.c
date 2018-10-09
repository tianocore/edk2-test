/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
