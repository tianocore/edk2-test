/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2014, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

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
