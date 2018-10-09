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
#/*++
#
#Module Name:
#
#  GoVirtual.asm
#
#--*/
    .text

#define HIGHBASE  0x800000000

# VOID
# LoadNewPageTable (
#   VOID                  *FuncPointer
#   UINTN                 ConfigInfo
# )
    .global LoadNewPageTable
    .type LoadNewPageTable, function
LoadNewPageTable:
    #
    # set the entries for virtual address above 4GB
    #
    movq %cr3, %rax
    movq (%rax), %rax
    andw $0xf000, %ax
    movq %rax, %r8

    #
    # Create mapping entry for 32G-64G
    # 0-32G & 32G-64G have identical phycial address mapping
    #
    push %rcx
    push %rdx
    mov  $32, %rcx			# get 32GB (1GB per entry)
again:  
    movq (%rax), %rbx
    and  $0xffdf, %bx			# Clear access flag
    movq %rbx, 0x100(%rax)
    add  $8, %rax			# point to next entry
    dec  %rcx
    jnz  again

    #
    # Change ConfigInfo to rcx to pass it to callee
    #
    pop  %rcx  
    pop  %rdx

    #
    # jmp to the virtual address above 4GB 
    #
    leaq  new_address(%rip), %rax
    movq  $HIGHBASE, %rbx
    add   %rbx, %rax
    jmp   *%rax

new_address:
    mov   $HIGHBASE, %rbx
    add   %rbx, %rsp

    #
    # It is safe time to destroy 0-32G virtual mapping
    #
    movq  $0, %r10
    movq  $32, %r9			# get 32B (1GB per entry)
Kill:  
    movq  %r10, (%r8)
    add   $8, %r8			# point to next entry
    dec   %r9
    jnz   Kill

    push  %rdx
    ret
