## @file
#
#  Copyright 2010 - 2010 Unified EFI, Inc.<BR>
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
##

ASM_GLOBAL ASM_PFX(EnablePageTable)
#------------------------------------------------------------------------------
#  UINT8
#  EnablePageTable (
#    IN  UINTN  HighAddress,
#    IN  UINTN  PageTables,
#    IN  UINTN  FuncPointer,
#    IN  UNITN  ConfigInfo
#    )
#------------------------------------------------------------------------------
ASM_PFX(EnablePageTable):
  push   %ebp
  mov    %esp,%ebp
  mov    0x8(%ebp),%bl
  mov    0xc(%ebp),%edx
  mov    0x10(%ebp),%esi
  mov    0x14(%ebp),%edi
  mov    %edx,%cr3
  mov    %cr4,%eax
  bts    $0x4,%eax
  mov    %eax,%cr4
  mov    %cr0,%eax
  bts    $0x1f,%eax
  mov    %eax,%cr0
  mov    $new_address,%eax
  mov    $0x80000000,%ecx
  cmp    $0x0,%bl
  jne    Above2G
  add    %ecx,%eax
  jmp    Next

Above2G:
  sub    %ecx,%eax

Next:
  jmp    *%eax

#ASM_GLOBAL ASM_PFX(new_address)
new_address:
  cmp    $0x0,%bl
  jne    Bigger
  mov    $0x80000000,%eax
  add    %eax,%edx
  mov    $0x0,%ecx
  add    $0x83,%eax

again0:
  mov    %eax,(%ecx,%edx,1)
  add    $0x400000,%eax
  add    $0x4,%ecx
  cmp    $0x800,%ecx
  jne    again0
  jmp    SwitchEsp

Bigger:
  mov    $0x80000000,%eax
  sub    %eax,%edx
  mov    $0x0,%eax
  mov    $0x0,%ecx
  add    $0x83,%eax

again1:
  mov    %eax,0x800(%ecx,%edx,1)
  add    $0x400000,%eax
  add    $0x4,%ecx
  cmp    $0x800,%ecx
  jne    again1

SwitchEsp:
  cmp    $0x80000000,%esp
  jae    SubEsp
  add    $0x80000000,%esp
  add    $0x80000000,%ebp
  push   %edi
  push   %edi
  jmp    CallTestFunction

SubEsp:
  sub    $0x80000000,%esp
  sub    $0x80000000,%ebp
  push   %edi
  push   %edi
  jmp    CallTestFunction

CallTestFunction:
  jmp    *%esi
  leave  
  ret  
