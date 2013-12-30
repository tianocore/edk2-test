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
