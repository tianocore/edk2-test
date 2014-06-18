/*++
  The material contained herein is not a license, either
  expressly or impliedly, to any intellectual property owned
  or controlled by any of the authors or developers of this
  material or to any contribution thereto. The material
  contained herein is provided on an "AS IS" basis and, to the
  maximum extent permitted by applicable law, this information
  is provided AS IS AND WITH ALL FAULTS, and the authors and
  developers of this material hereby disclaim all other
  warranties and conditions, either express, implied or
  statutory, including, but not limited to, any (if any)
  implied warranties, duties or conditions of merchantability,
  of fitness for a particular purpose, of accuracy or
  completeness of responses, of results, of workmanlike
  effort, of lack of viruses and of lack of negligence, all
  with regard to this material and any contribution thereto.
  Designers must not rely on the absence or characteristics of
  any features or instructions marked "reserved" or
  "undefined." The Unified EFI Forum, Inc. reserves any
  features or instructions so marked for future definition and
  shall have no responsibility whatsoever for conflicts or
  incompatibilities arising from future changes to them. ALSO,
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY
  CONTRIBUTION THERETO.

  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF
  THE POSSIBILITY OF SUCH DAMAGES.

  Copyright 2006 - 2012 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2013-2014, ARM Ltd. All rights reserved.

--*/

#include "SctLibInternal.h"

UINT64
SctLShiftU64 (
  IN UINT64                         Operand,
  IN UINTN                          Count
  )
{
  __asm {
  
    mov    eax, dword ptr Operand[0]
    mov    edx, dword ptr Operand[4]
  
    ;
    ; CL is valid from 0 - 31. shld will move EDX:EAX by CL times but EAX is not touched
    ; For CL of 32 - 63, it will be shifted 0 - 31 so we will move eax to edx later. 
    ;
    mov    ecx, Count
    and    ecx, 63
    shld   edx, eax, cl
    shl    eax, cl
  
    ;
    ; Since Count is 32 - 63, eax will have been shifted  by 0 - 31                                                     
    ; If shifted by 32 or more, set lower 32 bits to zero.
    ;
    cmp    ecx, 32
    jc     short _LShiftU64_Done
  
    mov    edx, eax
    xor    eax, eax

_LShiftU64_Done:
  }
}

UINT64
SctRShiftU64 (
  IN UINT64                         Operand,
  IN UINTN                          Count
  )
{
  __asm {
  
    mov    eax, dword ptr Operand[0]
    mov    edx, dword ptr Operand[4]
  
    ;
    ; CL is valid from 0 - 31. shld will move EDX:EAX by CL times but EDX is not touched
    ; For CL of 32 - 63, it will be shifted 0 - 31 so we will move edx to eax later. 
    ;
    mov    ecx, Count
    and    ecx, 63
    shrd   eax, edx, cl
    shr    edx, cl

    cmp    ecx, 32
    jc     short _RShiftU64_Done

    ;
    ; Since Count is 32 - 63, edx will have been shifted  by 0 - 31                                                     
    ; If shifted by 32 or more, set upper 32 bits to zero.
    ;
    mov    eax, edx
    xor    edx, edx

_RShiftU64_Done:
  }
}

UINT64
SctMultU64x32 (
  IN UINT64                         Multiplicand,
  IN UINTN                          Multiplier
  )
{
  __asm {
    mov    eax, dword ptr Multiplicand[0]
    mul    Multiplier
    push   eax
    push   edx
    mov    eax, dword ptr Multiplicand[4]
    mul    Multiplier
    ;
    ; The value in edx stored by second multiplication overflows
    ; the output and should be discarded. So here we overwrite it
    ; with the edx value of first multiplication.
    ;
    pop    edx
    add    edx, eax
    pop    eax
  }
}

UINT64
SctDivU64x32 (
  IN UINT64                         Dividend,
  IN UINTN                          Divisor,
  OUT UINTN                         *Remainder OPTIONAL
  )
{
  __asm {
    xor edx, edx                    ; Clear EDX

    mov eax, dword ptr Dividend[4]  ; Put high 32 bits of 64-bit dividend in EAX
    mov ecx, Divisor                ; Put 32 bits divisor in ECX
    div ecx                         ; Dividend   Divisor  Quoitent...Remainder
                                    ;  0:EAX  /  ECX   =  EAX      EDX   

    push eax                        ; Push quoitent in stack

    mov eax, dword ptr Dividend[0]  ; Put low 32 bits of 64-bit dividend in EAX              
    div ecx                         ; Leave the REMAINDER in EDX as High 32-bit of new dividend
                                    ; Dividend   Divisor  Quoitent...Remainder              
                                    ;  EDX:EAX  /  ECX   =  EAX      EDX               

    mov ecx, Remainder              ; Put &REMAINDER to ecx

    jecxz Label1                    ; If ecx == 0, no remainder exist, return with quoitent in EDX directly 
    mov dword ptr [ecx], edx        ; Put EDX through REMAINDER pointer in ECX 

Label1:
    pop edx                         ; Pop High 32-bit QUOITENT to EDX
  }
}
