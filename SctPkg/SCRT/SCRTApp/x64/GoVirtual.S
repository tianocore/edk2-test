#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
#
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
