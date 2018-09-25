;; @file
;
;  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
;  Copyright (c) 2012, ARM Ltd. All rights reserved.<BR>
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
	EXPORT JumpToTestFunc
;------------------------------------------------------------------------------
; VOID
; JumpToTestFunc (
;   IN  UINTN  FuncPointer,
;   IN  UNITN  ConfigInfo
;   )
;
	AREA   Helper, CODE, READONLY

JumpToTestFunc
	mov r2, r0
	mov r0, r1

	//Jump to Virtual function
	blx r2
  
  END
