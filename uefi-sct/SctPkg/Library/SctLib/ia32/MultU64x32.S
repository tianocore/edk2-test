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
#   MultU64x32.S
#
# Abstract:
#
#   Calculate the product of a 64-bit integer and a 32-bit integer
#
#------------------------------------------------------------------------------


    .code:

ASM_GLOBAL ASM_PFX(SctMultU64x32)

#------------------------------------------------------------------------------
# UINT64
# EFIAPI
# SctMultU64x32 (
#   IN      UINT64                    Multiplicand,
#   IN      UINT32                    Multiplier
#   );
#------------------------------------------------------------------------------
ASM_PFX(SctMultU64x32):
  push   %ebp
  mov    %esp,%ebp
  mov    0x8(%ebp),%eax
  mull   0x10(%ebp)
  push   %eax
  push   %edx
  mov    0xc(%ebp),%eax
  mull   0x10(%ebp)
  pop    %edx
  add    %eax,%edx
  pop    %eax
  pop    %ebp
  ret   
