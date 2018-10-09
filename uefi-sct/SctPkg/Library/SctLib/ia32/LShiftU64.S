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
#   LShiftU64.S
#
# Abstract:
#
#   64-bit left shift function for IA-32
#
#------------------------------------------------------------------------------

ASM_GLOBAL ASM_PFX(SctLShiftU64)

#------------------------------------------------------------------------------
# UINT64
# EFIAPI
# SctLShiftU64 (
#   IN      UINT64                    Operand,
#   IN      UINTN                     Count
#   );
#------------------------------------------------------------------------------
ASM_PFX(SctLShiftU64):
  push   %ebp
  mov    %esp,%ebp
  mov    0x8(%ebp),%eax
  mov    0xc(%ebp),%edx
  mov    0x10(%ebp),%ecx
  and    $0x3f,%ecx
  shld   %cl,%eax,%edx
  shl    %cl,%eax
  cmp    $0x20,%ecx
  jb     LShiftU64_Done
  mov    %eax,%edx
  xor    %eax,%eax

LShiftU64_Done:
  pop    %ebp
  ret   
