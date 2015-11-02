;
; The material contained herein is not a license, either      
; expressly or impliedly, to any intellectual property owned  
; or controlled by any of the authors or developers of this   
; material or to any contribution thereto. The material       
; contained herein is provided on an "AS IS" basis and, to the
; maximum extent permitted by applicable law, this information
; is provided AS IS AND WITH ALL FAULTS, and the authors and  
; developers of this material hereby disclaim all other       
; warranties and conditions, either express, implied or       
; statutory, including, but not limited to, any (if any)      
; implied warranties, duties or conditions of merchantability,
; of fitness for a particular purpose, of accuracy or         
; completeness of responses, of results, of workmanlike       
; effort, of lack of viruses and of lack of negligence, all   
; with regard to this material and any contribution thereto.  
; Designers must not rely on the absence or characteristics of
; any features or instructions marked "reserved" or           
; "undefined." The Unified EFI Forum, Inc. reserves any       
; features or instructions so marked for future definition and
; shall have no responsibility whatsoever for conflicts or    
; incompatibilities arising from future changes to them. ALSO,
; THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
; QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
; NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
; CONTRIBUTION THERETO.                                       
;                                                             
; IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
; ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
; THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
; PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
; CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
; UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
; WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
; DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
; THE POSSIBILITY OF SUCH DAMAGES.                            
;                                                             
; Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
; Rights Reserved, subject to all existing rights in all      
; matters included within this Test Suite, to which United    
; EFI, Inc. makes no claim of right.                          
;                                                             
; Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
;
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
  