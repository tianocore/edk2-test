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
;  Port80.asm
;
;--*/

    .code

;
; VOID
; Port80 ( 
;  UINT8 Number
;  )
; Abstract: Print a Hex Number to I/O 80h
;
Port80 PROC
    mov   al, cl
	out   80h, al
    ret
Port80 ENDP

   END
