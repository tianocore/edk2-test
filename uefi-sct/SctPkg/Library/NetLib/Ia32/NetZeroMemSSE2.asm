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
;++      TITLE   NetZeroMem.asm: Optimized memory-zero routine


; PROC:PRIVATE
  .686P
  .XMM
  .MODEL SMALL
  .CODE

NetCommonLibZeroMem  PROTO  C Buffer:PTR DWORD, Count:DWORD

;------------------------------------------------------------------------------
;  Procedure:  NetCommonLibZeroMem
;
;   VOID
;   NetCommonLibZeroMem (
;     IN VOID   *Buffer,
;     IN UINTN  Count
;     )
;
;  Input:  VOID   *Buffer - Pointer to buffer to clear
;          UINTN  Count  - Number of bytes to clear
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
NetCommonLibZeroMem  PROC C Buffer:PTR DWORD, Count:DWORD

  ; Save edi, then put the buffer pointer into it.
  push  edi
  mov   ecx, Count
  mov   edi, Buffer

  ; Pick up misaligned start bytes (get pointer 4-byte aligned)
_StartByteZero:
  mov   eax, edi    
  and   al, 3                       ; check lower 2 bits of address
  test  al, al
  je    _ZeroBlocks                 ; already aligned?
  cmp   ecx, 0
  je    _ZeroMemDone

  ; Clear the byte memory location
  mov   BYTE PTR [edi], 0           
  inc    edi

  ; Decrement our count
  dec    ecx
  jmp   _StartByteZero        ; back to top of loop

_ZeroBlocks:

  ; Compute how many 64-byte blocks we can clear 
  mov   edx, ecx
  shr   ecx, 6                      ; convert to 64-byte count
  shl   ecx, 6                      ; convert back to bytes
  sub   edx, ecx                    ; subtract from the original count
  shr   ecx, 6                      ; and this is how many 64-byte blocks

  ; If no 64-byte blocks, then skip 
  cmp    ecx, 0
  je    _ZeroRemaining

  xorps  xmm1, xmm1

@@:
  movdqu OWORD PTR ds:[edi], xmm1
  movdqu OWORD PTR ds:[edi+16], xmm1
  movdqu OWORD PTR ds:[edi+32], xmm1
  movdqu OWORD PTR ds:[edi+48], xmm1
   
  add    edi, 64
  dec    ecx
  jnz    @B
  

_ZeroRemaining:
  ; Zero out as many DWORDS as possible
  mov   ecx, edx
  shr   ecx, 2
  xor   eax, eax

  rep stosd

  ; Zero out remaining as bytes
  mov   ecx, edx
  and   ecx, 03

  rep   stosb
 
_ZeroMemDone:
  pop edi

  ret   
  
NetCommonLibZeroMem  ENDP
  END
