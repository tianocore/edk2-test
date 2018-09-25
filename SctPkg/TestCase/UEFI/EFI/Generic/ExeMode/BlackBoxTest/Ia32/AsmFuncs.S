## @file
#
#  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
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

ASM_GLOBAL ASM_PFX(GetFpuControlWord)
#------------------------------------------------------------------------------
#  EFI_STATUS
#  GetFpuControlWord (
#    OUT  UINT16  *Reg              
#    )
#------------------------------------------------------------------------------
ASM_PFX(GetFpuControlWord):
  push  %ebp
  mov   %esp,%ebp
  push  %edi
  mov   $0x0,%eax
  mov   0x8(%ebp),%edi
  fstcw (%edi)
  pop   %edi
  leave
  ret


ASM_GLOBAL ASM_PFX(GetMxCsr)
#------------------------------------------------------------------------------
#  EFI_STATUS
#  GetMxCsr (
#    OUT  UINT32  *Reg              
#    )
#------------------------------------------------------------------------------
ASM_PFX(GetMxCsr):
  push  %ebp
  mov   %esp,%ebp
  push  %ebx
  mov   $0x80000003,%eax
  mov   $0x1,%eax
  cpuid
  bt    $0x19,%edx
  jae   Done
  mov   $0x0,%eax
  push  %edi
  mov   0x8(%ebp),%edi
  stmxcsr (%edi)
  pop   %edi
Done:
  pop   %ebx
  leave
  ret






