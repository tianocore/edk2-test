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
