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
