## @file
#
#  Copyright 2010 - 2012 Unified EFI, Inc.<BR>
#  Copyright (c) 2023, Loongson Technology Corporation Limited. All rights reserved.<BR>
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

ASM_GLOBAL ASM_PFX(JumpToTestFunc)

#------------------------------------------------------------------------------
# VOID
# JumpToTestFunc (
#   IN  UINTN  FuncPointer,
#   IN  UNITN  ConfigInfo
#   )
#
ASM_PFX(JumpToTestFunc):
  move  $ra, $a0
  move  $a0, $a1

  // Jump to Virtual function
  jirl  $zero, $ra, 0
  .end
