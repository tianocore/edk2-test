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
#  Port80.asm
#
#--*/

    .text

#
# VOID
# Port80 ( 
#  UINT8 Number
#  )
# Abstract: Print a Hex Number to I/O 80h
#
    .global Port80
Port80:
    mov    %cl, %al
    outb   %al, $0x80 
    ret
