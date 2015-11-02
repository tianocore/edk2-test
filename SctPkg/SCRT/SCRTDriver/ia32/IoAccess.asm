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
  title   CpuIoAccess.asm
;------------------------------------------------------------------------------
;*   Module Name:
;*     Io.asm
;* 
;*   Abstract: 
;*     Supports IA32 CPU IO operation
;*  
;------------------------------------------------------------------------------
;
;
;------------------------------------------------------------------------------

  .686
  .MODEL FLAT,C
  .CODE


UINT8    TYPEDEF    BYTE
UINT16   TYPEDEF    WORD
UINT32   TYPEDEF    DWORD
UINT64   TYPEDEF    QWORD
UINTN    TYPEDEF    UINT32



;------------------------------------------------------------------------------
;  UINT8
;  CpuIoRead8 (
;    IN  UINT16  Port
;    )
;------------------------------------------------------------------------------
CpuIoRead8 PROC    PUBLIC Port:UINT16
    mov    dx,  Port
    in     al,  dx
    ret
CpuIoRead8  ENDP

;------------------------------------------------------------------------------
;  UINT16
;  CpuIoRead16 (
;    IN  UINT16  Port
;    )
;------------------------------------------------------------------------------
CpuIoRead16 PROC    PUBLIC Port:UINT16
    mov    dx,  Port
    in     ax,  dx
    ret
CpuIoRead16  ENDP

;------------------------------------------------------------------------------
;  UINT32
;  CpuIoRead32 (
;    IN  UINT16  Port
;    )
;------------------------------------------------------------------------------
CpuIoRead32 PROC    PUBLIC Port:UINT16
    mov   dx,  Port
    in    eax, dx
    ret
CpuIoRead32  ENDP



;------------------------------------------------------------------------------
;  VOID
;  CpuIoWrite8 (
;    IN  UINT16  Port,
;    IN  UINT32  Data
;    )
;------------------------------------------------------------------------------
CpuIoWrite8 PROC    PUBLIC Port:UINT16, Data:UINT32
    mov    eax, Data
    mov    dx,  Port
    out    dx,  al
    ret
CpuIoWrite8  ENDP


;------------------------------------------------------------------------------
;  VOID
;  CpuIoWrite16 (
;    IN  UINT16  Port,
;    IN  UINT32  Data
;    )
;------------------------------------------------------------------------------
CpuIoWrite16 PROC    PUBLIC Port:UINT16, Data:UINT32
    mov    eax, Data
    mov    dx,  Port
    out    dx,  ax
    ret
CpuIoWrite16  ENDP


;------------------------------------------------------------------------------
;  VOID
;  CpuIoWrite32 (
;    IN  UINT16  Port,
;    IN  UINT32  Data
;    )
;------------------------------------------------------------------------------
CpuIoWrite32 PROC    PUBLIC Port:UINT16, Data:UINT32
    mov    eax, Data
    mov    dx,  Port
    out    dx,  eax
    ret
CpuIoWrite32  ENDP


END