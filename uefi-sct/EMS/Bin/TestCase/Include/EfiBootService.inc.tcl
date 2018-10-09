# 
#  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
if {[info exist ENTS_EFI_BS_INC] == 1} {
  return
}
set ENTS_EFI_BS_INC 1

set EVT_TIMER                           0x80000000
set EVT_RUNTIME                         0x40000000
set EVT_RUNTIME_CONTEXT                 0x20000000
set EVT_NOTIFY_WAIT                     0x00000100
set EVT_NOTIFY_SIGNAL                   0x00000200
set EVT_SIGNAL_EXIT_BOOT_SERVICES       0x00000201
set EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE   0x60000202

set EFI_TPL_APPLICATION                 4
set EFI_TPL_DRIVER                      6
set EFI_TPL_CALLBACK                    8
set EFI_TPL_NOTIFY                      16
set EFI_TPL_HIGH_LEVEL                  31

Func BS->CreateEvent {
  UINT32
  UINTN
  UINTN
  POINTER
  POINTER
  POINTER
  }

Func BS->CloseEvent {
  UINTN
  POINTER
  }

Func BS->SignalEvent {
  UINTN
  POINTER
  }

Func BS->WaitForEvent {
  UINTN
  POINTER
  POINTER
  POINTER
  }

Func BS->CheckEvent {
  UINTN
  POINTER
  }

Func BS->SetTimer {
  UINTN
  UINTN
  UINT64
  POINTER
  }

Func BS->AllocatePages {
  UINTN
  UINTN
  UINTN
  POINTER
  POINTER
  }

Func BS->FreePages {
  UINTN
  UINTN
  POINTER
  }

Func BS->AllocatePool {
  UINTN
  UINTN
  POINTER
  POINTER
  }

Func BS->FreePool {
  POINTER
  POINTER
  }

Func BS->SetWatchdogTimer {
  UINTN
  UINT64
  UINTN
  POINTER
  POINTER
  }

Func BS->Stall {
  UINTN
  POINTER
  }

Func BS->CopyMem {
  POINTER
  POINTER
  UINTN
  POINTER
  }

Func BS->SetMem {
  POINTER
  UINTN
  UINT8
  POINTER
  }

