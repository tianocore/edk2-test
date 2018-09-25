/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2011 - 2012 ARM Ltd. All rights reserved.<BR>   

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
  SctAPrint ("\n================Dump Runtime Table===============\n");
  SctAPrint ("Header Signature = 0x%x\n", VRT->Hdr.Signature);

  SctAPrint ("\n================GetTime Service==============\n");
  SctAPrint ("GetTime @ 0x%x\n", VRT->GetTime);

  SctAPrint ("\n================SetTime Service==============\n");
  SctAPrint ("SetTime @ 0x%x\n", VRT->SetTime);

  SctAPrint ("\n================GetWakeupTime Service==============\n");
  SctAPrint ("GetWakeupTime @ 0x%x\n", VRT->GetWakeupTime);

  SctAPrint ("\n================SetWakeupTime Service==============\n");
  SctAPrint ("SetWakeupTime @ 0x%x\n", VRT->SetWakeupTime);

  SctAPrint ("\n================GetVariable Service==============\n");
  SctAPrint ("GetVariable @ 0x%x\n", VRT->GetVariable);

  SctAPrint ("\n================GetNextVariableName Service==============\n");
  SctAPrint ("GetNextVariableName @ 0x%x\n", VRT->GetNextVariableName);

  SctAPrint ("\n================SetVariable Service==============\n");
  SctAPrint ("SetVariable @ 0x%x\n", VRT->SetVariable);

  SctAPrint ("\n================GetNextHighMonotonicCount Service==============\n");
  SctAPrint ("GetNextHighMonotonicCount @ 0x%x\n", VRT->GetNextHighMonotonicCount);

  SctAPrint ("\n================ResetSystem Service==============\n");
  SctAPrint ("ResetSystem @ 0x%x\n", VRT->ResetSystem);
#if 0
  SctAPrint ("\n================UpdateCapsule Service==============\n");
  SctAPrint ("UpdateCapsule @ 0x%x\n", VRT->UpdateCapsule);

  SctAPrint ("\n================QueryCapsuleCapabilities Service==============\n");
  SctAPrint ("QueryCapsuleCapabilities @ 0x%x\n", VRT->QueryCapsuleCapabilities);

  SctAPrint ("\n================QueryVariableInfo Service==============\n");
  SctAPrint ("QueryVariableInfo @ 0x%x\n", VRT->QueryVariableInfo);
#endif
}
