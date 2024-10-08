/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   
  (C) Copyright 2021 Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DebugSupportProtocol.h

Abstract:

  DebugSupport protocol and supporting definitions as defined in the EFI 1.1
  specification.

  The DebugSupport protocol is used by source level debuggers to abstract the
  processor and handle context save and restore operations.

--*/

#ifndef _DEBUG_SUPPORT_FOR_TEST_H_
#define _DEBUG_SUPPORT_FOR_TEST_H_

//
// Debug Support protocol {2755590C-6F3C-42FA-9EA4-A3BA543CDA25}
//

#define EFI_DEBUG_SUPPORT_PROTOCOL_GUID \
  { 0x2755590C, 0x6F3C, 0x42FA, {0x9E, 0xA4, 0xA3, 0xBA, 0x54, 0x3C, 0xDA, 0x25 }}

//
// Debug Support definitions
//
typedef INTN                               EFI_EXCEPTION_TYPE;

//
//  EBC Exception types
//
#define   EXCEPT_EBC_UNDEFINED             0
#define   EXCEPT_EBC_DIVIDE_ERROR          1
#define   EXCEPT_EBC_DEBUG                 2
#define   EXCEPT_EBC_BREAKPOINT            3
#define   EXCEPT_EBC_OVERFLOW              4
#define   EXCEPT_EBC_INVALID_OPCODE        5
#define   EXCEPT_EBC_STACK_FAULT           6
#define   EXCEPT_EBC_ALIGNMENT_CHECK       7
#define   EXCEPT_EBC_INSTRUCTION_ENCODING  8
#define   EXCEPT_EBC_BAD_BREAK             9
#define   EXCEPT_EBC_SINGLE_STEP          10

//
//  IA-32 processor exception types
//
#define   EXCEPT_IA32_DIVIDE_ERROR         0
#define   EXCEPT_IA32_DEBUG                1
#define   EXCEPT_IA32_NMI                  2
#define   EXCEPT_IA32_BREAKPOINT           3
#define   EXCEPT_IA32_OVERFLOW             4
#define   EXCEPT_IA32_BOUND                5
#define   EXCEPT_IA32_INVALID_OPCODE       6
#define   EXCEPT_IA32_DOUBLE_FAULT         8
#define   EXCEPT_IA32_INVALID_TSS         10
#define   EXCEPT_IA32_SEG_NOT_PRESENT     11
#define   EXCEPT_IA32_STACK_FAULT         12
#define   EXCEPT_IA32_GP_FAULT            13
#define   EXCEPT_IA32_PAGE_FAULT          14
#define   EXCEPT_IA32_FP_ERROR            16
#define   EXCEPT_IA32_ALIGNMENT_CHECK     17
#define   EXCEPT_IA32_MACHINE_CHECK       18
#define   EXCEPT_IA32_SIMD                19

//
//  X64 processor exception types
//
#define   EXCEPT_X64_DIVIDE_ERROR          0
#define   EXCEPT_X64_DEBUG                 1
#define   EXCEPT_X64_NMI                   2
#define   EXCEPT_X64_BREAKPOINT            3
#define   EXCEPT_X64_OVERFLOW              4
#define   EXCEPT_X64_BOUND                 5
#define   EXCEPT_X64_INVALID_OPCODE        6
#define   EXCEPT_X64_DOUBLE_FAULT          8
#define   EXCEPT_X64_INVALID_TSS          10
#define   EXCEPT_X64_SEG_NOT_PRESENT      11
#define   EXCEPT_X64_STACK_FAULT          12
#define   EXCEPT_X64_GP_FAULT             13
#define   EXCEPT_X64_PAGE_FAULT           14
#define   EXCEPT_X64_FP_ERROR             16
#define   EXCEPT_X64_ALIGNMENT_CHECK      17
#define   EXCEPT_X64_MACHINE_CHECK        18
#define   EXCEPT_X64_SIMD                 19

//
//  IPF processor exception types
//
#define    EXCEPT_IPF_VHTP_TRANSLATION               0
#define    EXCEPT_IPF_INSTRUCTION_TLB                1
#define    EXCEPT_IPF_DATA_TLB                       2
#define    EXCEPT_IPF_ALT_INSTRUCTION_TLB            3
#define    EXCEPT_IPF_ALT_DATA_TLB                   4
#define    EXCEPT_IPF_DATA_NESTED_TLB                5
#define    EXCEPT_IPF_INSTRUCTION_KEY_MISSED         6
#define    EXCEPT_IPF_DATA_KEY_MISSED                7
#define    EXCEPT_IPF_DIRTY_BIT                      8
#define    EXCEPT_IPF_INSTRUCTION_ACCESS_BIT         9
#define    EXCEPT_IPF_DATA_ACCESS_BIT               10
#define    EXCEPT_IPF_BREAKPOINT                    11
#define    EXCEPT_IPF_EXTERNAL_INTERRUPT            12
// 13 - 19 reserved
#define    EXCEPT_IPF_PAGE_NOT_PRESENT              20
#define    EXCEPT_IPF_KEY_PERMISSION                21
#define    EXCEPT_IPF_INSTRUCTION_ACCESS_RIGHTS     22
#define    EXCEPT_IPF_DATA_ACCESS_RIGHTS            23
#define    EXCEPT_IPF_GENERAL_EXCEPTION             24
#define    EXCEPT_IPF_DISABLED_FP_REGISTER          25
#define    EXCEPT_IPF_NAT_CONSUMPTION               26
#define    EXCEPT_IPF_SPECULATION                   27
// 28 reserved
#define    EXCEPT_IPF_DEBUG                         29
#define    EXCEPT_IPF_UNALIGNED_REFERENCE           30
#define    EXCEPT_IPF_UNSUPPORTED_DATA_REFERENCE    31
#define    EXCEPT_IPF_FP_FAULT                      32
#define    EXCEPT_IPF_FP_TRAP                       33
#define    EXCEPT_IPF_LOWER_PRIVILEGE_TRANSFER_TRAP 34
#define    EXCEPT_IPF_TAKEN_BRANCH                  35
#define    EXCEPT_IPF_SINGLE_STEP                   36
// 37 - 44 reserved
#define    EXCEPT_IPF_IA32_EXCEPTION                45
#define    EXCEPT_IPF_IA32_INTERCEPT                46
#define    EXCEPT_IPF_IA32_INTERRUPT                47


//
//  EBC processor context definition
//
typedef
struct {
  UINT64        R0, R1, R2, R3, R4, R5, R6, R7;
  UINT64        Flags;
  UINT64        ControlFlags;
  UINT64        Ip;
} EFI_SYSTEM_CONTEXT_EBC;

//
//  IA-32 processor context definition
//

//
// FXSAVE_STATE
// FP / MMX / XMM registers (see fxrstor instruction definition)
//
typedef
struct {
  UINT16              Fcw;
  UINT16              Fsw;
  UINT16              Ftw;
  UINT16              Opcode;
  UINT32              Eip;
  UINT16              Cs;
  UINT16              Reserved1;
  UINT32              DataOffset;
  UINT16              Ds;
  UINT8               Reserved2[10];
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  UINT8   St0Mm0[10], Reserved3[6];
  UINT8   St1Mm1[10], Reserved4[6];
  UINT8   St2Mm2[10], Reserved5[6];
  UINT8   St3Mm3[10], Reserved6[6];
  UINT8   St4Mm4[10], Reserved7[6];
  UINT8   St5Mm5[10], Reserved8[6];
  UINT8   St6Mm6[10], Reserved9[6];
  UINT8   St7Mm7[10], Reserved10[6];
  UINT8   Xmm0[16];
  UINT8   Xmm1[16];
  UINT8   Xmm2[16];
  UINT8   Xmm3[16];
  UINT8   Xmm4[16];
  UINT8   Xmm5[16];
  UINT8   Xmm6[16];
  UINT8   Xmm7[16];
  UINT8   Reserved11[14 * 16];
} EFI_FX_SAVE_STATE_IA32;
#else
  UINT8               St0Mm0[10], Reserved3[6];
  UINT8               St0Mm1[10], Reserved4[6];
  UINT8               St0Mm2[10], Reserved5[6];
  UINT8               St0Mm3[10], Reserved6[6];
  UINT8               St0Mm4[10], Reserved7[6];
  UINT8               St0Mm5[10], Reserved8[6];
  UINT8               St0Mm6[10], Reserved9[6];
  UINT8               St0Mm7[10], Reserved10[6];
  UINT8               Reserved11[22 * 16];
} EFI_FX_SAVE_STATE;
#endif

typedef
struct {
  UINT32              ExceptionData;
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  EFI_FX_SAVE_STATE_IA32   FxSaveState;
#else
  EFI_FX_SAVE_STATE  FxSaveState;
#endif
  UINT32              Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
  UINT32              Cr0, Cr1 /* Reserved */, Cr2, Cr3, Cr4;
  UINT32              Eflags;
  UINT32              Ldtr, Tr;
  UINT32              Gdtr[2], Idtr[2];
  UINT32              Eip;
  UINT32              Gs, Fs, Es, Ds, Cs, Ss;
  UINT32              Edi, Esi, Ebp, Esp, Ebx, Edx, Ecx, Eax;
} EFI_SYSTEM_CONTEXT_IA32;

//
//  X64 processor context definition
//
// FXSAVE_STATE
// FP / MMX / XMM registers (see fxrstor instruction definition)
//
typedef struct {
  UINT16  Fcw;
  UINT16  Fsw;
  UINT16  Ftw;
  UINT16  Opcode;
  UINT64  Rip;
  UINT64  DataOffset;
  UINT8   Reserved1[8];
  UINT8   St0Mm0[10], Reserved2[6];
  UINT8   St1Mm1[10], Reserved3[6];
  UINT8   St2Mm2[10], Reserved4[6];
  UINT8   St3Mm3[10], Reserved5[6];
  UINT8   St4Mm4[10], Reserved6[6];
  UINT8   St5Mm5[10], Reserved7[6];
  UINT8   St6Mm6[10], Reserved8[6];
  UINT8   St7Mm7[10], Reserved9[6];
  UINT8   Xmm0[16];
  UINT8   Xmm1[16];
  UINT8   Xmm2[16];
  UINT8   Xmm3[16];
  UINT8   Xmm4[16];
  UINT8   Xmm5[16];
  UINT8   Xmm6[16];
  UINT8   Xmm7[16];
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  //
  // NOTE: UEFI 2.0 spec definition as follows. It should be updated 
  // after spec update. (It is copy from R8 implementation, for it is not defined in EFI1.1 Spec)
  //
  UINT8   Reserved11[14 * 16];
#else
  UINT8   Xmm8[16];
  UINT8   Xmm9[16];
  UINT8   Xmm10[16];
  UINT8   Xmm11[16];
  UINT8   Xmm12[16];
  UINT8   Xmm13[16];
  UINT8   Xmm14[16];
  UINT8   Xmm15[16];
  UINT8   Reserved10[6 * 16];
#endif
} EFI_FX_SAVE_STATE_X64;

typedef struct {
  UINT64                ExceptionData;
  EFI_FX_SAVE_STATE_X64 FxSaveState;
  UINT64                Dr0;
  UINT64                Dr1;
  UINT64                Dr2;
  UINT64                Dr3;
  UINT64                Dr6;
  UINT64                Dr7;
  UINT64                Cr0;
  UINT64                Cr1;  /* Reserved */
  UINT64                Cr2;
  UINT64                Cr3;
  UINT64                Cr4;
  UINT64                Cr8;
  UINT64                Rflags;
  UINT64                Ldtr;
  UINT64                Tr;
  UINT64                Gdtr[2];
  UINT64                Idtr[2];
  UINT64                Rip;
  UINT64                Gs;
  UINT64                Fs;
  UINT64                Es;
  UINT64                Ds;
  UINT64                Cs;
  UINT64                Ss;
  UINT64                Rdi;
  UINT64                Rsi;
  UINT64                Rbp;
  UINT64                Rsp;
  UINT64                Rbx;
  UINT64                Rdx;
  UINT64                Rcx;
  UINT64                Rax;
  UINT64                R8;
  UINT64                R9;
  UINT64                R10;
  UINT64                R11;
  UINT64                R12;
  UINT64                R13;
  UINT64                R14;
  UINT64                R15;
} EFI_SYSTEM_CONTEXT_X64;

//
//  IPF processor context definition
//
typedef
struct {
//
// The first reserved field is necessary to preserve alignment for the correct
// bits in UNAT and to insure F2 is 16 byte aligned..
//
  UINT64          Reserved;
  UINT64          R1;
  UINT64          R2;
  UINT64          R3;
  UINT64          R4;
  UINT64          R5;
  UINT64          R6;
  UINT64          R7;
  UINT64          R8;
  UINT64          R9;
  UINT64          R10;
  UINT64          R11;
  UINT64          R12;
  UINT64          R13;
  UINT64          R14;
  UINT64          R15;
  UINT64          R16;
  UINT64          R17;
  UINT64          R18;
  UINT64          R19;
  UINT64          R20;
  UINT64          R21;
  UINT64          R22;
  UINT64          R23;
  UINT64          R24;
  UINT64          R25;
  UINT64          R26;
  UINT64          R27;
  UINT64          R28;
  UINT64          R29;
  UINT64          R30;
  UINT64          R31;

  UINT64          F2[2];
  UINT64          F3[2];
  UINT64          F4[2];
  UINT64          F5[2];
  UINT64          F6[2];
  UINT64          F7[2];
  UINT64          F8[2];
  UINT64          F9[2];
  UINT64          F10[2];
  UINT64          F11[2];
  UINT64          F12[2];
  UINT64          F13[2];
  UINT64          F14[2];
  UINT64          F15[2];
  UINT64          F16[2];
  UINT64          F17[2];
  UINT64          F18[2];
  UINT64          F19[2];
  UINT64          F20[2];
  UINT64          F21[2];
  UINT64          F22[2];
  UINT64          F23[2];
  UINT64          F24[2];
  UINT64          F25[2];
  UINT64          F26[2];
  UINT64          F27[2];
  UINT64          F28[2];
  UINT64          F29[2];
  UINT64          F30[2];
  UINT64          F31[2];

  UINT64          Pr;

  UINT64          B0;
  UINT64          B1;
  UINT64          B2;
  UINT64          B3;
  UINT64          B4;
  UINT64          B5;
  UINT64          B6;
  UINT64          B7;

//
// application registers
//
  UINT64          ArRsc;
  UINT64          ArBsp;
  UINT64          ArBspstore;
  UINT64          ArRnat;

  UINT64          ArFcr;

  UINT64          ArEflag;
  UINT64          ArCsd;
  UINT64          ArSsd;
  UINT64          ArCflg;
  UINT64          ArFsr;
  UINT64          ArFir;
  UINT64          ArFdr;

  UINT64          ArCcv;

  UINT64          ArUnat;

  UINT64          ArFpsr;

  UINT64          ArPfs;
  UINT64          ArLc;
  UINT64          ArEc;

//
// control registers
//
  UINT64          CrDcr;
  UINT64          CrItm;
  UINT64          CrIva;
  UINT64          CrPta;
  UINT64          CrIpsr;
  UINT64          CrIsr;
  UINT64          CrIip;
  UINT64          CrIfa;
  UINT64          CrItir;
  UINT64          CrIipa;
  UINT64          CrIfs;
  UINT64          CrIim;
  UINT64          CrIha;

//
// debug registers
//
  UINT64          Dbr0;
  UINT64          Dbr1;
  UINT64          Dbr2;
  UINT64          Dbr3;
  UINT64          Dbr4;
  UINT64          Dbr5;
  UINT64          Dbr6;
  UINT64          Dbr7;

  UINT64          Ibr0;
  UINT64          Ibr1;
  UINT64          Ibr2;
  UINT64          Ibr3;
  UINT64          Ibr4;
  UINT64          Ibr5;
  UINT64          Ibr6;
  UINT64          Ibr7;

//
// virtual registers - nat bits for R1-R31
//
  UINT64          IntNat;

} EFI_SYSTEM_CONTEXT_IPF;


///
///  ARM processor exception types.
///
#define EXCEPT_ARM_RESET                    0
#define EXCEPT_ARM_UNDEFINED_INSTRUCTION    1
#define EXCEPT_ARM_SOFTWARE_INTERRUPT       2
#define EXCEPT_ARM_PREFETCH_ABORT           3
#define EXCEPT_ARM_DATA_ABORT               4
#define EXCEPT_ARM_RESERVED                 5
#define EXCEPT_ARM_IRQ                      6
#define EXCEPT_ARM_FIQ                      7

///
/// For coding convenience, define the maximum valid ARM exception.
///
#define MAX_ARM_EXCEPTION EXCEPT_ARM_FIQ

///
///  ARM processor context definition.
///
typedef struct {
  UINT32  R0;
  UINT32  R1;
  UINT32  R2;
  UINT32  R3;
  UINT32  R4;
  UINT32  R5;
  UINT32  R6;
  UINT32  R7;
  UINT32  R8;
  UINT32  R9;
  UINT32  R10;
  UINT32  R11;
  UINT32  R12;
  UINT32  SP;
  UINT32  LR;
  UINT32  PC;
  UINT32  CPSR;
  UINT32  DFSR;
  UINT32  DFAR;
  UINT32  IFSR;
  UINT32  IFAR;
} EFI_SYSTEM_CONTEXT_ARM;


///
///  AARCH64 processor exception types.
///
#define EXCEPT_AARCH64_SYNCHRONOUS_EXCEPTIONS    0
#define EXCEPT_AARCH64_IRQ                       1
#define EXCEPT_AARCH64_FIQ                       2
#define EXCEPT_AARCH64_SERROR                    3

///
/// For coding convenience, define the maximum valid ARM exception.
///
#define MAX_AARCH64_EXCEPTION EXCEPT_AARCH64_SERROR

typedef struct {
  // General Purpose Registers
  UINT64  X0;
  UINT64  X1;
  UINT64  X2;
  UINT64  X3;
  UINT64  X4;
  UINT64  X5;
  UINT64  X6;
  UINT64  X7;
  UINT64  X8;
  UINT64  X9;
  UINT64  X10;
  UINT64  X11;
  UINT64  X12;
  UINT64  X13;
  UINT64  X14;
  UINT64  X15;
  UINT64  X16;
  UINT64  X17;
  UINT64  X18;
  UINT64  X19;
  UINT64  X20;
  UINT64  X21;
  UINT64  X22;
  UINT64  X23;
  UINT64  X24;
  UINT64  X25;
  UINT64  X26;
  UINT64  X27;
  UINT64  X28;
  UINT64  FP;   // x29 - Frame pointer
  UINT64  LR;   // x30 - Link Register
  UINT64  SP;   // x31 - Stack pointer

  // FP/SIMD Registers
  UINT64  V0[2];
  UINT64  V1[2];
  UINT64  V2[2];
  UINT64  V3[2];
  UINT64  V4[2];
  UINT64  V5[2];
  UINT64  V6[2];
  UINT64  V7[2];
  UINT64  V8[2];
  UINT64  V9[2];
  UINT64  V10[2];
  UINT64  V11[2];
  UINT64  V12[2];
  UINT64  V13[2];
  UINT64  V14[2];
  UINT64  V15[2];
  UINT64  V16[2];
  UINT64  V17[2];
  UINT64  V18[2];
  UINT64  V19[2];
  UINT64  V20[2];
  UINT64  V21[2];
  UINT64  V22[2];
  UINT64  V23[2];
  UINT64  V24[2];
  UINT64  V25[2];
  UINT64  V26[2];
  UINT64  V27[2];
  UINT64  V28[2];
  UINT64  V29[2];
  UINT64  V30[2];
  UINT64  V31[2];

  UINT64  ELR;  // Exception Link Register
  UINT64  SPSR; // Saved Processor Status Register
  UINT64  FPSR; // Floating Point Status Register
  UINT64  ESR;  // Exception syndrome register
  UINT64  FAR;  // Fault Address Register
} EFI_SYSTEM_CONTEXT_AARCH64;

///
/// RISC-V processor exception types.
///
#define EXCEPT_RISCV_INST_MISALIGNED              0
#define EXCEPT_RISCV_INST_ACCESS_FAULT            1
#define EXCEPT_RISCV_ILLEGAL_INST                 2
#define EXCEPT_RISCV_BREAKPOINT                   3
#define EXCEPT_RISCV_LOAD_ADDRESS_MISALIGNED      4
#define EXCEPT_RISCV_LOAD_ACCESS_FAULT            5
#define EXCEPT_RISCV_STORE_AMO_ADDRESS_MISALIGNED 6
#define EXCEPT_RISCV_STORE_AMO_ACCESS_FAULT       7
#define EXCEPT_RISCV_ENV_CALL_FROM_UMODE          8
#define EXCEPT_RISCV_ENV_CALL_FROM_SMODE          9
#define EXCEPT_RISCV_ENV_CALL_FROM_HMODE          10
#define EXCEPT_RISCV_ENV_CALL_FROM_MMODE          11

#define EXCEPT_RISCV_SOFTWARE_INT       0x0
#define EXCEPT_RISCV_TIMER_INT          0x1

typedef struct {
  UINT64  X0;
  UINT64  X1;
  UINT64  X2;
  UINT64  X3;
  UINT64  X4;
  UINT64  X5;
  UINT64  X6;
  UINT64  X7;
  UINT64  X8;
  UINT64  X9;
  UINT64  X10;
  UINT64  X11;
  UINT64  X12;
  UINT64  X13;
  UINT64  X14;
  UINT64  X15;
  UINT64  X16;
  UINT64  X17;
  UINT64  X18;
  UINT64  X19;
  UINT64  X20;
  UINT64  X21;
  UINT64  X22;
  UINT64  X23;
  UINT64  X24;
  UINT64  X25;
  UINT64  X26;
  UINT64  X27;
  UINT64  X28;
  UINT64  X29;
  UINT64  X30;
  UINT64  X31;
} EFI_SYSTEM_CONTEXT_RISCV64;

//
// LoongArch processor exception types.
//
#define EXCEPT_LOONGARCH_INT   0
#define EXCEPT_LOONGARCH_PIL   1
#define EXCEPT_LOONGARCH_PIS   2
#define EXCEPT_LOONGARCH_PIF   3
#define EXCEPT_LOONGARCH_PME   4
#define EXCEPT_LOONGARCH_PNR   5
#define EXCEPT_LOONGARCH_PNX   6
#define EXCEPT_LOONGARCH_PPI   7
#define EXCEPT_LOONGARCH_ADE   8
#define EXCEPT_LOONGARCH_ALE   9
#define EXCEPT_LOONGARCH_BCE   10
#define EXCEPT_LOONGARCH_SYS   11
#define EXCEPT_LOONGARCH_BRK   12
#define EXCEPT_LOONGARCH_INE   13
#define EXCEPT_LOONGARCH_IPE   14
#define EXCEPT_LOONGARCH_FPD   15
#define EXCEPT_LOONGARCH_SXD   16
#define EXCEPT_LOONGARCH_ASXD  17
#define EXCEPT_LOONGARCH_FPE   18
#define EXCEPT_LOONGARCH_TBR   64 // For code only, there is no such type in the ISA spec, the TLB refill is defined for an independent exception.

//
// LoongArch processor Interrupt types.
//
#define EXCEPT_LOONGARCH_INT_SIP0   0
#define EXCEPT_LOONGARCH_INT_SIP1   1
#define EXCEPT_LOONGARCH_INT_IP0    2
#define EXCEPT_LOONGARCH_INT_IP1    3
#define EXCEPT_LOONGARCH_INT_IP2    4
#define EXCEPT_LOONGARCH_INT_IP3    5
#define EXCEPT_LOONGARCH_INT_IP4    6
#define EXCEPT_LOONGARCH_INT_IP5    7
#define EXCEPT_LOONGARCH_INT_IP6    8
#define EXCEPT_LOONGARCH_INT_IP7    9
#define EXCEPT_LOONGARCH_INT_PMC    10
#define EXCEPT_LOONGARCH_INT_TIMER  11
#define EXCEPT_LOONGARCH_INT_IPI    12

//
// For coding convenience, define the maximum valid
// LoongArch interrupt.
//
#define MAX_LOONGARCH_INTERRUPT  14

typedef struct {
  UINT64    R0;
  UINT64    R1;
  UINT64    R2;
  UINT64    R3;
  UINT64    R4;
  UINT64    R5;
  UINT64    R6;
  UINT64    R7;
  UINT64    R8;
  UINT64    R9;
  UINT64    R10;
  UINT64    R11;
  UINT64    R12;
  UINT64    R13;
  UINT64    R14;
  UINT64    R15;
  UINT64    R16;
  UINT64    R17;
  UINT64    R18;
  UINT64    R19;
  UINT64    R20;
  UINT64    R21;
  UINT64    R22;
  UINT64    R23;
  UINT64    R24;
  UINT64    R25;
  UINT64    R26;
  UINT64    R27;
  UINT64    R28;
  UINT64    R29;
  UINT64    R30;
  UINT64    R31;

  UINT64    CRMD;  // CuRrent MoDe information
  UINT64    PRMD;  // PRe-exception MoDe information
  UINT64    EUEN;  // Extended component Unit ENable
  UINT64    MISC;  // MISCellaneous controller
  UINT64    ECFG;  // Exception ConFiGuration
  UINT64    ESTAT; // Exception STATus
  UINT64    ERA;   // Exception Return Address
  UINT64    BADV;  // BAD Virtual address
  UINT64    BADI;  // BAD Instruction
} EFI_SYSTEM_CONTEXT_LOONGARCH64;

//
// Universal EFI_SYSTEM_CONTEXT definition
//
typedef
union {
  EFI_SYSTEM_CONTEXT_EBC                  *SystemContextEbc;
  EFI_SYSTEM_CONTEXT_IA32                 *SystemContextIa32;
  EFI_SYSTEM_CONTEXT_X64                  *SystemContextX64;
  EFI_SYSTEM_CONTEXT_IPF                  *SystemContextIpf;
  EFI_SYSTEM_CONTEXT_ARM                  *SystemContextArm;
  EFI_SYSTEM_CONTEXT_AARCH64              *SystemContextAArch64;
  EFI_SYSTEM_CONTEXT_RISCV64              *SystemContextRiscV64;
  EFI_SYSTEM_CONTEXT_LOONGARCH64          *SystemContextLoongArch64;
} EFI_SYSTEM_CONTEXT;

//
// DebugSupport callback function prototypes
//
typedef
VOID
(* EFI_EXCEPTION_CALLBACK) (
  IN     EFI_EXCEPTION_TYPE               ExceptionType,
  IN OUT EFI_SYSTEM_CONTEXT               SystemContext
  );

typedef
VOID
(* EFI_PERIODIC_CALLBACK) (
  IN OUT EFI_SYSTEM_CONTEXT               SystemContext
  );

//
// Machine type definition
//
#define IMAGE_FILE_MACHINE_I386            0x014C
#define IMAGE_FILE_MACHINE_X64             0x8664
#define IMAGE_FILE_MACHINE_IA64            0x0200
#define IMAGE_FILE_MACHINE_EBC             0x0EBC
#define IMAGE_FILE_MACHINE_ARMTHUMB_MIXED  0x01c2
#define IMAGE_FILE_MACHINE_ARM64           0xAA64
#define IMAGE_FILE_MACHINE_RISCV64         0x5064
#define IMAGE_FILE_MACHINE_LOONGARCH64     0x6264


typedef
enum {
  IsaIa32 = IMAGE_FILE_MACHINE_I386,
  IsaX64  = IMAGE_FILE_MACHINE_X64,  	
  IsaIpf  = IMAGE_FILE_MACHINE_IA64,
  IsaEbc  = IMAGE_FILE_MACHINE_EBC,
  IsaArm  = IMAGE_FILE_MACHINE_ARMTHUMB_MIXED,       ///< 0x01c2
  IsaAArch64  = IMAGE_FILE_MACHINE_ARM64,            ///< 0xAA64
  IsaRiscv64  = IMAGE_FILE_MACHINE_RISCV64,          ///< 0x5064
  IsaLoongArch64  = IMAGE_FILE_MACHINE_LOONGARCH64   ///< 0x6264
} EFI_INSTRUCTION_SET_ARCHITECTURE;

typedef struct _EFI_DEBUG_SUPPORT_PROTOCOL EFI_DEBUG_SUPPORT_PROTOCOL;;

//
// DebugSupport member function definitions
//
typedef
EFI_STATUS
(EFIAPI *EFI_GET_MAXIMUM_PROCESSOR_INDEX) (
  IN EFI_DEBUG_SUPPORT_PROTOCOL          *This,
  OUT UINTN                              *MaxProcessorIndex
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_PERIODIC_CALLBACK) (
  IN EFI_DEBUG_SUPPORT_PROTOCOL          *This,
  IN UINTN                               ProcessorIndex,
  IN EFI_PERIODIC_CALLBACK               PeriodicCallback
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_EXCEPTION_CALLBACK) (
  IN EFI_DEBUG_SUPPORT_PROTOCOL          *This,
  IN UINTN                               ProcessorIndex,
  IN EFI_EXCEPTION_CALLBACK              ExceptionCallback,
  IN EFI_EXCEPTION_TYPE                  ExceptionType
  );

typedef
EFI_STATUS
(EFIAPI *EFI_INVALIDATE_INSTRUCTION_CACHE) (
  IN EFI_DEBUG_SUPPORT_PROTOCOL          *This,
  IN UINTN                               ProcessorIndex,
  IN VOID                                *Start,
  IN UINT64                              Length
  );

//
// DebugSupport protocol definition
//
struct _EFI_DEBUG_SUPPORT_PROTOCOL {
  EFI_INSTRUCTION_SET_ARCHITECTURE        Isa;
  EFI_GET_MAXIMUM_PROCESSOR_INDEX         GetMaximumProcessorIndex;
  EFI_REGISTER_PERIODIC_CALLBACK          RegisterPeriodicCallback;
  EFI_REGISTER_EXCEPTION_CALLBACK         RegisterExceptionCallback;
  EFI_INVALIDATE_INSTRUCTION_CACHE        InvalidateInstructionCache;
};

extern EFI_GUID gBlackBoxEfiDebugSupportProtocolGuid;

#endif /* _DEBUG_SUPPORT_FOR_TEST_H_ */

