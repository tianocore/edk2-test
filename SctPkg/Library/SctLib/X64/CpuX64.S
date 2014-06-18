#/*++
#
#Copyright (c) 2006 - 2010, Intel Corporation. All rights reserved.<BR>
#This program and the accompanying materials                          
#are licensed and made available under the terms and conditions of the BSD License         
#which accompanies this distribution.  The full text of the license may be found at        
#http://opensource.org/licenses/bsd-license.php                                            
#                                                                                          
#THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
#WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             
#
#Module Name:
#
#  CpuIA32.c
#
#Abstract:
#
#--*/

#---------------------------------------------------------------------------
    .586p: 
    #.MODEL flat,C
    .code: 

#---------------------------------------------------------------------------

.globl ASM_PFX(SctReadTsc)

#UINT64
#SctReadTsc (
#  VOID
#  )
ASM_PFX(SctReadTsc):
    rdtsc
    ret
#EfiReadTsc ENDP
