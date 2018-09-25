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
if {[info exist ENTS_EFI_RT_INC] == 1} {
  return
}
set ENTS_EFI_RT_INC 1

set EFI_RESET_CODE          0
set EFI_RESET_WARM          1
set EFI_RESET_SHUTDOWN      2

Func RT->GetVariable {
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func RT->GetNextVariableName {
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func RT->SetVariable {
  POINTER
  POINTER
  UINT32
  UINTN
  POINTER
  POINTER
  }

Func RT->GetTime {
  POINTER
  POINTER
  POINTER
  }

Func RT->SetTime {
  POINTER
  POINTER
  }

Func RT->GetWakeupTime {
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func RT->SetWakeupTime {
  BOOLEAN
  POINTER
  POINTER
  }

Func RT->ResetSystem {
  UINTN
  UINTN
  UINTN
  POINTER
  }

