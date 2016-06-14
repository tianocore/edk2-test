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

ASM_GLOBAL ASM_PFX(EnablePageTable)
#------------------------------------------------------------------------------
#  UINT8
#  EnablePageTable (
#    IN  UINTN  HighAddress,
#    IN  UINTN  PageTables,
#    IN  UINTN  FuncPointer,
#    IN  UNITN  ConfigInfo
#    )
#------------------------------------------------------------------------------
ASM_PFX(EnablePageTable):
  push   %ebp
  mov    %esp,%ebp
  mov    0x8(%ebp),%bl
  mov    0xc(%ebp),%edx
  mov    0x10(%ebp),%esi
  mov    0x14(%ebp),%edi
  mov    %edx,%cr3
  mov    %cr4,%eax
  bts    $0x4,%eax
  mov    %eax,%cr4
  mov    %cr0,%eax
  bts    $0x1f,%eax
  mov    %eax,%cr0
  mov    $new_address,%eax
  mov    $0x80000000,%ecx
  cmp    $0x0,%bl
  jne    Above2G
  add    %ecx,%eax
  jmp    Next

Above2G:
  sub    %ecx,%eax

Next:
  jmp    *%eax

#ASM_GLOBAL ASM_PFX(new_address)
new_address:
  cmp    $0x0,%bl
  jne    Bigger
  mov    $0x80000000,%eax
  add    %eax,%edx
  mov    $0x0,%ecx
  add    $0x83,%eax

again0:
  mov    %eax,(%ecx,%edx,1)
  add    $0x400000,%eax
  add    $0x4,%ecx
  cmp    $0x800,%ecx
  jne    again0
  jmp    SwitchEsp

Bigger:
  mov    $0x80000000,%eax
  sub    %eax,%edx
  mov    $0x0,%eax
  mov    $0x0,%ecx
  add    $0x83,%eax

again1:
  mov    %eax,0x800(%ecx,%edx,1)
  add    $0x400000,%eax
  add    $0x4,%ecx
  cmp    $0x800,%ecx
  jne    again1

SwitchEsp:
  cmp    $0x80000000,%esp
  jae    SubEsp
  add    $0x80000000,%esp
  add    $0x80000000,%ebp
  push   %edi
  push   %edi
  jmp    CallTestFunction

SubEsp:
  sub    $0x80000000,%esp
  sub    $0x80000000,%ebp
  push   %edi
  push   %edi
  jmp    CallTestFunction

CallTestFunction:
  jmp    *%esi
  leave  
  ret  
