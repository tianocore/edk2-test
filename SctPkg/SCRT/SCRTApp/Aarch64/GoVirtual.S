## @file
#
#  Copyright 2010 - 2012 Unified EFI, Inc.<BR>
#  Copyright (c) 2012, ARM Ltd. All rights reserved.<BR>
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
#
#/*++
#
# Module Name:
#
#  GoVirtual.S
#
#--*/
#start of the code section
.text
/* FIXME: Should alignment be different on Aarch64? */
.align 3

.global JumpToTestFunc
.type JumpToTestFunc, %function

#------------------------------------------------------------------------------
# VOID
# JumpToTestFunc (
#   IN  UINTN  FuncPointer,
#   IN  UNITN  ConfigInfo
#   )
#
JumpToTestFunc:
	mov x2, x0
	mov x0, x1

	// Jump to Virtual function
	blr x2
