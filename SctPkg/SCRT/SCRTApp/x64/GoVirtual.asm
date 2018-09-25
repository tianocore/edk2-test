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
;;
;/*++
;
;Module Name:
;
;  GoVirtual.asm
;
;--*/
    .code

HIGHBASE  EQU  0800000000h

; VOID
; LoadNewPageTable (
;   VOID                  *FuncPointer
;   UINTN                 ConfigInfo
; )

LoadNewPageTable  PROC
  ;
  ; set the entries for virtual address above 4GB
  ;
  mov   rax, cr3
  mov   rax, [rax]
  and   ax,  0f000h
  mov   r8 , rax
  
  ;
  ; Create mapping entry for 32G-64G
  ; 0-32G & 32G-64G have identical phycial address mapping
  ;
  push  rcx
  push  rdx
  mov   rcx,  0    
again:  
  mov   rbx, [rax + rcx]
  and   bx,  0ffdfh                 ; clear access flag
  mov   [rax + rcx + 100h], rbx
  add   rcx,  08h                   ; point to next entry
  cmp   rcx,  100h                  ; get 32GB (1GB per entry)
  jne   again

  ;
  ; Change ConfigInfo to rcx to pass it to callee
  ;
  pop   rcx  
  pop   rdx

  ;
  ; jmp to the virtual address above 4GB 
  ;
  mov   rax, new_address
  mov   rbx, HIGHBASE
  add   rax, rbx
  jmp   rax

new_address:
  mov   rbx, HIGHBASE
  add   rsp, rbx

  ;
  ; It is safe time to destroy 0-32G virtual mapping
  ;
  mov   r9,  0
  mov   r10, 0
Kill:  
  mov   [r8 + r9], r10
  add   r9,  08h                   ; point to next entry
  cmp   r9,  100h                  ; get 32GB (1GB per entry)
  jne   Kill


  push  rdx
  ret

  ;jmp   qword ptr [rcx]

LoadNewPageTable ENDP

END
