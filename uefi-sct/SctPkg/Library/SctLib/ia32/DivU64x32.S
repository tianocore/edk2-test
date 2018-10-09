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
#   DivU64x32.S
#
# Abstract:
#
#   Calculate the quotient of a 64-bit integer by a 32-bit integer
#
#------------------------------------------------------------------------------

ASM_GLOBAL ASM_PFX(SctDivU64x32)

#------------------------------------------------------------------------------
# UINT64
# EFIAPI
# SctDivU64x32 (
#   IN      UINT64                    Dividend,
#   IN      UINT32                    Divisor
#   );
#------------------------------------------------------------------------------
ASM_PFX(SctDivU64x32):
  push   %ebp
  mov    %esp,%ebp
  xor    %edx,%edx
  mov    0xc(%ebp),%eax
  mov    0x10(%ebp),%ecx
  div    %ecx
  push   %eax
  mov    0x8(%ebp),%eax
  div    %ecx
  mov    0x14(%ebp),%ecx
  jecxz  Label1
  mov    %edx,(%ecx)

Label1:
  pop    %edx
  pop    %ebp
  ret   
