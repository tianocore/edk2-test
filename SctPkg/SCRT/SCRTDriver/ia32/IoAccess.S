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
# Copyright 2006 - 2016 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2016, Intel Corporation. All rights reserved.<BR> 
#
#

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



