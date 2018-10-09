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

#------------------------------------------------------------------------------
#*   Module Name:
#*    #Io.asm
#*  
#*   Abstract:
#*    #Supports x64 CPU IO operation
#*
#------------------------------------------------------------------------------
#
#   
# 
# Abstract:
# 
#   
#------------------------------------------------------------------------------

.text

#------------------------------------------------------------------------------
#  UINT8
#  CpuIoRead8 (
#    #UINT16  Port   // rcx
#    #)
#------------------------------------------------------------------------------
    .global CpuIoRead8
CpuIoRead8:
    xor   %eax, %eax
    mov   %cx, %dx
    inb   %dx, %al
    ret

#------------------------------------------------------------------------------
#  VOID
#  CpuIoWrite8 (
#    #UINT16  Port,    // rcx
#    #UINT32  Data     // rdx
#    #)
#------------------------------------------------------------------------------
    .global CpuIoWrite8
CpuIoWrite8:
    mov   %edx, %eax
    mov   %cx, %dx
    outb  %al, %dx
    ret

#------------------------------------------------------------------------------
#  UINT16
#  CpuIoRead16 (
#    #UINT16  Port   // rcx
#    #)
#------------------------------------------------------------------------------
    .global CpuIoRead16
CpuIoRead16:
    xor   %eax, %eax
    mov   %cx, %dx
    inw   %dx, %ax
    ret

#------------------------------------------------------------------------------
#  VOID
#  CpuIoWrite16 (
#    #UINT16  Port,    // rcx
#    #UINT32  Data     // rdx
#    #)
#------------------------------------------------------------------------------
    .global CpuIoWrite16
CpuIoWrite16:
    mov    %edx, %eax
    mov    %cx, %dx
    outw   %ax, %dx
    ret

#------------------------------------------------------------------------------
#  UINT32
#  CpuIoRead32 (
#    #UINT16  Port   // rcx
#    #)
#------------------------------------------------------------------------------
    .global CpuIoRead32
CpuIoRead32:
    mov    %cx, %dx
    inl    %dx, %eax
    ret

#------------------------------------------------------------------------------
#  VOID
#  CpuIoWrite32 (
#    #UINT16  Port,    // rcx
#    #UINT32  Data     // rdx
#    #)
#------------------------------------------------------------------------------
    .global CpuIoWrite32
CpuIoWrite32:
    mov    %edx, %eax
    mov    %cx, %dx
    outl   %eax, %dx
    ret
