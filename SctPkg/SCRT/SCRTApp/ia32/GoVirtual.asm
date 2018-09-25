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
    .586p
    .model  flat,C
    .mmx
    .code

;------------------------------------------------------------------------------
; VOID
; EnablePageTable (
;   IN  UINTN  HighAddress,
;   IN  UINTN  PageTables, 
;   IN  UINTN  FuncPointer,
;   IN  UNITN  ConfigInfo
;   )
;
; Abstract: initialize CR3 (page directory entry table base address) to point to the base
;

HIGHBASE  EQU  80000000h 

EnablePageTable PROC    C PUBLIC HighAddress: BYTE, PageTables:DWORD, FuncPointer:DWORD, ConfigInfo:DWORD,

		mov bl, HighAddress  ; HighAddress =1, above 2G; HighAddress=0, below 2G.
                mov edx, PageTables
		mov esi, FuncPointer
		mov edi, ConfigInfo
                ;
                ; Initialize CR3 with Page-Directory Entry Table Base Address (Physical Address).
                ;
                mov cr3, edx

                ;
                ;  Enable 4-MBytes Page mode (set CR4.PSE=1)
                ;
                mov eax, cr4            ; Read CR4.
                bts eax,  4             ; Set PSE=1.
                mov cr4, eax            ; Write CR4.

                ;
	        ;  Enable paging mode (set CR0.PG=1)
	        ;
                mov eax, cr0            ; Read CR0.
                bts eax, 31             ; Set PG=1.
                mov cr0, eax            ; Write CR0.
               
                ;
                ; Caculate the virtual address.
                ;
                mov   eax, new_address
                mov   ecx, HIGHBASE

                ;
                ; If we are running now below 2GBytes address,by default 
                ; Virtual Address 0-2G, 2-4G both map to Physical Address 0-2G.
                ; Jump to virtual address above 2G.
                ;
                cmp   bl, 0    	
                jne   Above2G
                add   eax, ecx          ; Running below 2G, so jump to > 2G.
               
                jmp   Next
Above2G:               
                sub   eax, ecx          ; Running above 2G, so jump to < 2G.
Next:                
		;
		; Jump the target virtual address
		;
       		jmp  eax

new_address:
                cmp  bl, 0
                jne  Bigger
                ;
                ; Now we are running in Virtual address above 2G, it is safe to remap Virtual
                ; address 0-2G to Physical address 2-4G.
                ;
                mov eax, HIGHBASE
                add edx, eax
                mov ecx, 0
                add eax, 083h      ; ReadWrite, Present, PageSize =4M                
again0:                
                mov [edx + ecx],eax
                add eax, 0400000h
                add ecx, 04h
                cmp ecx, 800h
                jne again0

                jmp SwitchEsp

Bigger:
                ;
                ; Now we are running in Virtual address below 2G, it is safe to remap Virtual
                ; address 2-4G to Physical address 0-2G.
                ;
                mov eax, HIGHBASE
                sub edx, eax
                
                mov eax, 0
                mov ecx, 0
                add  eax, 083h     ; ReadWrite, Present, PageSize =4M
again1:                
                mov [edx + ecx +0800h],eax
                add eax, 0400000h
                add ecx, 04h
                cmp ecx, 800h
                jne again1

SwitchEsp:
                cmp esp, HIGHBASE
                jae SubEsp
                add esp, HIGHBASE
                add ebp, HIGHBASE
                push edi             ; Push Configuration Data
                push edi             ; Push stub return address
                jmp CallTestFunction
SubEsp:
		sub esp, HIGHBASE
		sub ebp, HIGHBASE
                push edi             ; Push Configuration Data
                push edi             ; Push stub return address
                jmp CallTestFunction

CallTestFunction:
                
    	        jmp  esi

       		ret
EnablePageTable  ENDP
     END
