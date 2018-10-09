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
;++

;--------------------- Start of InterruptMask.asm -----------------------------
    .code
;------------------------------------------------------------------------------
;  VOID
;  MaskTimerInterrupt (
;    VOID
;    )
;------------------------------------------------------------------------------
MaskTimerInterrupt PROC
    mov  al, 0ffh
    mov  dx, 021h
    out  dx, al
    ret
MaskTimerInterrupt  ENDP
;------------------------------------------------------------------------------
;  VOID
;  UnmaskTimerInterrupt (
;    VOID
;    )
;------------------------------------------------------------------------------
UnmaskTimerInterrupt PROC
    mov  al, 0feh
    mov  dx, 021h
    out  dx, al
    ret
UnmaskTimerInterrupt  ENDP

END
;--------------------- End of InterruptMask.asm --------------------------------