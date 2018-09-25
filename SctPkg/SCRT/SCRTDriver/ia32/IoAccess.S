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


ASM_GLOBAL ASM_PFX(CpuIoRead8)
#------------------------------------------------------------------------------
#  UINT8
#  CpuIoRead8 (
#    IN UINT16 Port
#    )
#------------------------------------------------------------------------------
ASM_PFX(CpuIoRead8):
  push   %ebp
  mov    %esp,%ebp
  mov    0x8(%ebp),%dx
  in     (%dx),%al
  leave
  ret

ASM_GLOBAL ASM_PFX(CpuIoRead16)
#------------------------------------------------------------------------------
#  UINT16
#  CpuIoRead16 (
#    IN UINT16 Port
#    )
#------------------------------------------------------------------------------
ASM_PFX(CpuIoRead16):
  push   %ebp
  mov    %esp,%ebp
  mov    0x8(%ebp),%dx
  in     (%dx),%ax
  leave
  ret

ASM_GLOBAL ASM_PFX(CpuIoRead32)
#------------------------------------------------------------------------------
#  UINT32
#  CpuIoRead32 (
#    IN UINT16 Port
#    )
#------------------------------------------------------------------------------
ASM_PFX(CpuIoRead32):
  push   %ebp
  mov    %esp,%ebp
  mov    0x8(%ebp),%dx
  in     (%dx),%eax
  leave
  ret

ASM_GLOBAL ASM_PFX(CpuIoWrite8)
#------------------------------------------------------------------------------
#  VOID
#  CpuIoWrite8 (
#    IN UINT16 Port
#    IN UINT32 Data
#    )
#------------------------------------------------------------------------------
ASM_PFX(CpuIoWrite8):
  push   %ebp
  mov    %esp,%ebp
  mov    0xc(%ebp),%eax
  mov    0x8(%ebp),%dx
  out    %al,(%dx)
  leave  
  ret   

ASM_GLOBAL ASM_PFX(CpuIoWrite16)
#------------------------------------------------------------------------------
#  VOID
#  CpuIoWrite16 (
#    IN UINT16 Port
#    IN UINT32 Data
#    )
#------------------------------------------------------------------------------
ASM_PFX(CpuIoWrite16):
  push   %ebp
  mov    %esp,%ebp
  mov    0xc(%ebp),%eax
  mov    0x8(%ebp),%dx
  out    %ax,(%dx)
  leave  
  ret 

ASM_GLOBAL ASM_PFX(CpuIoWrite32)
#------------------------------------------------------------------------------
#  VOID
#  CpuIoWrite32 (
#    IN UINT16 Port
#    IN UINT32 Data
#    )
#------------------------------------------------------------------------------
ASM_PFX(CpuIoWrite32):
  push   %ebp
  mov    %esp,%ebp
  mov    0xc(%ebp),%eax
  mov    0x8(%ebp),%dx
  out    %eax,(%dx)
  leave  
  ret 



