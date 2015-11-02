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
