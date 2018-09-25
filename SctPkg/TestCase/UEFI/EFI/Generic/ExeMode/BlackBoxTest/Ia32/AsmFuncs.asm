;; @file
; 
;  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
;  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
; 
;  This program and the accompanying materials
;  are licensed and made available under the terms and conditions of the BSD License
;  which accompanies this distribution.  The full text of the license may be found at 
;  http://opensource.org/licenses/bsd-license.php
; 
;  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
;  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
; 
;

.686
.MODEL          FLAT, C

.XMM
.CODE


;------------------------------------------------------------------------------
;  EFI_STATUS
;  GetFpuControlWord (
;    OUT  UINT16  *Reg              
;    )
;------------------------------------------------------------------------------
GetFpuControlWord PROC    PUBLIC Reg:PTR DWORD
     
     push edi
     mov    eax, 0
     
     mov    edi, DWORD PTR Reg 
     
     fstcw  [edi]

     pop edi
     ret
GetFpuControlWord  ENDP

;------------------------------------------------------------------------------
;  EFI_STATUS
;  GetMxCsr (
;    OUT  UINT32  *Reg              
;    )
;------------------------------------------------------------------------------
GetMxCsr PROC    PUBLIC Reg:PTR DWORD

     push  ebx
     mov  eax, 080000003h
     ;
     ; Use CpuId instructuion (CPUID.01H:EDX.SSE[bit 25] = 1) to test
     ; whether the processor supports SSE instruction.
     ;
     mov     eax, 1
     cpuid
     bt      edx, 25
     jnc     Done
     
     mov  eax, 0
     
     push  edi
     
     mov    edi, DWORD PTR Reg 
     stmxcsr  [edi]
     
     pop   edi
Done:
     pop     ebx     
     ret
GetMxCsr  ENDP

END



