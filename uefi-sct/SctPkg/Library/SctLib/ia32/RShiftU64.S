## @file
#
#  Copyright 2010 - 2016 Unified EFI, Inc.<BR>
#  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
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
#
# Module Name:
#
#   RShiftU64.S
#
# Abstract:
#
#   64-bit logical right shift function for IA-32
#
#------------------------------------------------------------------------------


    .code:

ASM_GLOBAL ASM_PFX(SctRShiftU64)

#------------------------------------------------------------------------------
# UINT64
# EFIAPI
# SctRShiftU64 (
#   IN      UINT64                    Operand,
#   IN      UINTN                     Count
#   );
#------------------------------------------------------------------------------
ASM_PFX(SctRShiftU64):
  push   %ebp
  mov    %esp,%ebp
  mov    0x8(%ebp),%eax
  mov    0xc(%ebp),%edx
  mov    0x10(%ebp),%ecx
  and    $0x3f,%ecx
  shrd   %cl,%edx,%eax
  shr    %cl,%edx
  cmp    $0x20,%ecx
  jb     RShiftU64_Done
  mov    %edx,%eax
  xor    %edx,%edx

RShiftU64_Done:
  pop    %ebp
  ret  
