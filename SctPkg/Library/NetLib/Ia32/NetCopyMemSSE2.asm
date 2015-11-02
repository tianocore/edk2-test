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
;++      TITLE   NetCopyMem.asm: Optimized memory-copy routine

;------------------------------------------------------------------------------


; Module Name:
;
;   NetCopyMem.asm
; 
; Abstract:
; 
;   This is the code that supports IA32-optimized CopyMem service
;
;------------------------------------------------------------------------------

; PROC:PRIVATE
  .686P
  .XMM
  .MODEL SMALL
  .CODE

NetCommonLibCopyMem  PROTO  C Destination:PTR DWORD, Source:PTR DWORD, Count:DWORD

;------------------------------------------------------------------------------
;  VOID
;  NetCommonLibCopyMem (
;    IN VOID   *Destination,
;    IN VOID   *Source,
;    IN UINTN  Count
;    )
;------------------------------------------------------------------------------

NetCommonLibCopyMem  PROC  C Destination:PTR DWORD, Source:PTR DWORD, Count:DWORD

  ; Put source and destination pointers in esi/edi
  push  esi
  push  edi
   
  mov   ecx, Count
  mov   esi, Source
  mov   edi, Destination

  ; First off, make sure we have no overlap. That is to say,
  ;   if (Source == Destination)           => do nothing
  ;   if (Source + Count <= Destination)   => regular copy
  ;   if (Destination + Count <= Source)   => regular copy
  ;   otherwise, do a reverse copy
  
  mov   eax, esi
  add   eax, ecx                      ; Source + Count
  cmp   eax, edi
  jle   _StartByteCopy

  mov   eax, edi
  add   eax, ecx                      ; Dest + Count
  cmp   eax, esi
  jle   _StartByteCopy

  cmp   esi, edi
  je    _CopyMemDone         
  jl    _CopyOverlapped               ; too bad -- overlaps

  ; Pick up misaligned start bytes to get destination pointer 4-byte aligned
_StartByteCopy:
  cmp   ecx, 0
  je    _CopyMemDone                ; Count == 0, all done
  mov   edx, edi
  and   dl, 0fh                       ; check lower 2 bits of address
  test  dl, dl          
  je    SHORT _CopyBlocks           ; already aligned?

  ; Copy a byte
  mov   al, BYTE PTR [esi]          ; get byte from Source
  mov   BYTE PTR [edi], al          ; write byte to Destination
  dec   ecx
  inc   edi
  inc   esi
  jmp   _StartByteCopy               ; back to top of loop

_CopyBlocks:
  ; Compute how many 64-byte blocks we can clear 
  mov   eax, ecx                    ; get Count in eax
  shr   eax, 4                      ; convert to 64-byte count
  shl   eax, 4                      ; convert back to bytes
  sub   ecx, eax                    ; subtract from the original count
  shr   eax, 4                      ; and this is how many 64-byte blocks

  ; If no 64-byte blocks, then skip 
  cmp   eax, 0
  je    _CopyRemainingDWords

  
copyxmm:
  
  movdqu xmm0, OWORD PTR ds:[esi]
  movntdq OWORD PTR ds:[edi], xmm0
  lea   edi, [edi+16]  
  lea   esi, [esi+16]
  dec   eax
  jnz   copyxmm
   
  ; Copy as many DWORDS as possible
_CopyRemainingDWords:
  cmp   ecx, 4
  jb    _CopyRemainingBytes

  mov   eax, DWORD PTR [esi]        ; get data from Source
  mov   DWORD PTR [edi], eax        ; write byte to Destination
  sub   ecx, 4                      ; decrement Count
  add   esi, 4                      ; advance Source pointer
  add   edi, 4                      ; advance Destination pointer
  jmp   _CopyRemainingDWords        ; back to top

_CopyRemainingBytes:
  cmp   ecx, 0
  je    _CopyMemDone
  mov   al, BYTE PTR [esi]          ; get byte from Source
  mov   BYTE PTR [edi], al          ; write byte to Destination
  dec    ecx
  inc    esi
  inc   edi                      ; advance Destination pointer
  jmp   SHORT _CopyRemainingBytes   ; back to top of loop

  ;
  ; We do this block if the source and destination buffers overlap. To
  ; handle it, copy starting at the end of the source buffer and work
  ; your way back. Since this is the atypical case, this code has not
  ; been optimized, and thus simply copies bytes.
  ;
_CopyOverlapped:
   
  ; Move the source and destination pointers to the end of the range
  add   esi, ecx                      ; Source + Count
  dec    esi
  add   edi, ecx                      ; Dest + Count
  dec    edi

_CopyOverlappedLoop:
  cmp   ecx, 0
  je    _CopyMemDone
  mov   al, BYTE PTR [esi]          ; get byte from Source
  mov   BYTE PTR [edi], al          ; write byte to Destination
  dec    ecx
  dec    esi
  dec   edi
  jmp   _CopyOverlappedLoop         ; back to top of loop

_CopyMemDone:
  pop   edi
  pop   esi

  ret
  
NetCommonLibCopyMem  ENDP
                     
  END
