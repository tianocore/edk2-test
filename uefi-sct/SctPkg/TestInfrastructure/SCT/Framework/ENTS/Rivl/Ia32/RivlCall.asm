;@file
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
;++      TITLE   RivlCall.asm: Rivlcall routine


.686p
.model  flat        
.code

;-------------------------------------------------------------------------------------------------------
; UINTN RivlCall (VOID *FuncAddr, UINTN CallingType, UINTN Number, UINTN *StackTop, UINTN *StackBottom);
;-------------------------------------------------------------------------------------------------------

RivlCall PROC PUBLIC 

     push   ebp
     mov    ebp, esp
     mov    ecx, [ebp + 10h]
     mov    edi, [ebp + 18h]

@@:
     push   [edi]
     lea    edi, [edi - 4]
     loop   @B

     mov    eax, [ebp + 8]
     call   eax

     ;
     ; fix ESP for __cdecl (default)
     ; do nothing for __stdcall
     ;
     mov    ebx, [ebp + 0ch]
     cmp    ebx, 0
     jne    @@Exit
     mov    ebx, [ebp + 10h]
     shl    ebx, 3
     add    esp, ebx;

@@Exit:
     pop    ebp
     ret
RivlCall ENDP
     END
