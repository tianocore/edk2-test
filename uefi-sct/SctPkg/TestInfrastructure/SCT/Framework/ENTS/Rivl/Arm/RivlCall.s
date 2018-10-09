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
;------------------------------------------------------------------------------
;
;
;------------------------------------------------------------------------------

	EXPORT RivlCall
	AREA RivlCallC, CODE, READONLY

;-------------------------------------------------------------------------------------------------------
; UINTN RivlCall (VOID *FuncAddr, UINTN CallingType, UINTN Number, UINTN *StackTop, UINTN *StackBottom);
;-------------------------------------------------------------------------------------------------------

RivlCall
     STMFD sp!, {r4 - r12, lr}
     
     MOV   v1, a1
     MOV   v2, a4
     MOV   v3, a3
     MOV   v4, #0
     LDR   a1, [v2]
     ADD   v2, v2, #4
     LDR   a2, [v2]
     ADD   v2, v2, #4
     LDR   a3, [v2]
     ADD   v2, v2, #4
     LDR   a4, [v2]
     CMP   v3, #0
     BEQ   ready
     CMP   v3, #1
     BEQ   ready
     CMP   v3, #2
     BEQ   ready
     CMP   v3, #3
     BEQ   ready
     CMP   v3, #4
     BEQ   ready

     ;
     ; if arg num > 4, save it in stack
     ;
     ADD   v3, v3, #-4
     MOV   v4, #4
     MUL   v4, v3, v4
     ADD   v2, v2, v4
tostack
     LDR   v4, [v2]
     STR   v4, [sp, #-4]!
     ADD   v3, v3, #-1
     ADD   v2, v2, #-4
     CMP   v3, #0
     BEQ   tostack

ready
     ;BL    v1
     MOV   lr, pc
     MOV   pc, v1

     ADD   sp, sp, v4
     LDMFD sp!, {r4 - r12, pc}

	END
