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
;
;++      TITLE   NetSetMem.asm: Optimized setmemory routine



; PROC:PRIVATE
  .686P
  .MMX
  .XMM
  .MODEL SMALL
  .CODE

NetCommonLibSetMem  PROTO  C Buffer:PTR DWORD, Count:DWORD, Value:BYTE

;------------------------------------------------------------------------------
;  Procedure:  NetCommonLibSetMem
;
;   VOID
;   NetCommonLibSetMem (
;     IN VOID   *Buffer,
;     IN UINTN  Count,
;     IN UINT8  Value
;     )
;
;  Input:  VOID   *Buffer - Pointer to buffer to write
;          UINTN  Count   - Number of bytes to write
;          UINT8  Value    - Value to write
;
;  Output: None.
;
;  Saves:
;
;  Modifies:
;
;  Description:  This function is an optimized zero-memory function.
;
;  Notes:  This function tries to zero memory 8 bytes at a time. As a result, 
;          it first picks up any misaligned bytes, then words, before getting 
;          in the main loop that does the 8-byte clears.
;
;------------------------------------------------------------------------------
NetCommonLibSetMem  PROC C Buffer:PTR DWORD, Count:DWORD, Value:BYTE
  LOCAL  QWordValue:QWORD
  LOCAL  MmxSave:QWORD

  
  mov edx, Count
  test edx, edx
  je _SetMemDone

  push edi
  push ebx
  
  mov eax, Buffer
  mov bl, Value
  mov edi, eax
  mov  bh, bl
  
  cmp edx, 256
  jb _SetRemindingByte
  
  and al, 0fh
  test al, al
  je _SetBlock
  
  mov eax, edi
  shr eax, 4
  inc eax
  shl eax, 4
  sub eax, edi
  cmp eax, edx
  jnb _SetRemindingByte
  
  sub edx, eax
  mov ecx, eax

  mov al, bl
  rep stosb

_SetBlock:
  mov eax, edx
  shr eax, 7
  test eax, eax
  je _SetRemindingByte

  shl eax, 7
  sub edx, eax
  shr eax, 7

  mov  WORD PTR QWordValue[0], bx
  mov  WORD PTR QWordValue[2], bx
  mov  WORD PTR QWordValue[4], bx
  mov  WORD PTR QWordValue[6], bx
 
  
  movq  MmxSave, mm0
  movq  mm0, QWordValue

  movq2dq  xmm1, mm0
  pshufd   xmm1, xmm1, 0

@@:
  movdqa  OWORD PTR ds:[edi], xmm1
  movdqa  OWORD PTR ds:[edi+16], xmm1
  movdqa  OWORD PTR ds:[edi+32], xmm1
  movdqa  OWORD PTR ds:[edi+48], xmm1
  movdqa  OWORD PTR ds:[edi+64], xmm1
  movdqa  OWORD PTR ds:[edi+80], xmm1
  movdqa  OWORD PTR ds:[edi+96], xmm1
  movdqa  OWORD PTR ds:[edi+112], xmm1
  add edi, 128
  dec eax
  jnz @B
  
; Restore mm0
  movq  mm0, MmxSave
  emms                                 ; Exit MMX Instruction
  
_SetRemindingByte:
  mov ecx, edx

  mov eax, ebx
  shl eax, 16
  mov ax, bx
  shr ecx, 2
  rep stosd
  
  mov ecx, edx
  and ecx, 3
  rep stosb
  
  pop ebx
  pop edi

_SetMemDone:
  ret 0

NetCommonLibSetMem  ENDP
  END
  