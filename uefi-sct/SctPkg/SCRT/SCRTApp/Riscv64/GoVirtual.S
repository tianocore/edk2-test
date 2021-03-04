## @file
#
#  Copyright 2010 - 2012 Unified EFI, Inc.<BR>
#  Copyright (c) 2012, ARM Ltd. All rights reserved.<BR>
#  Copyright (c) 2021, Hewlett Packard Enterprise Development LP.<BR>
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
	mv x2, x0
	mv x0, x1

	// Jump to Virtual function
	jalr x2
