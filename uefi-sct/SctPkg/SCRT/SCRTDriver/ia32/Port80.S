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


ASM_GLOBAL ASM_PFX(Port80)
#------------------------------------------------------------------------------
#  VOID
#  Port80 (
#    UINT8 Number
#    )
#------------------------------------------------------------------------------
ASM_PFX(Port80):
  push  %ebp
  mov   %esp,%ebp
  mov   0x8(%ebp),%al
  out   %al,$0x80
  leave
  ret
