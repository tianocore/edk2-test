/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Cpu.h

Abstract:

  GVIII Ratio/Vid definitions. Now data for Dothan processor is included.

--*/

#ifndef _CPU_H_
#define _CPU_H_

#define B_FAMILY_MODEL_STEPPING       0x00000FFF

#define EFI_MSR_IA32_PERF_STS         0x198
#define EFI_MSR_IA32_PERF_CTL         0x199
#define EFI_MSR_IA32_CLOCK_MODULATION 0x19A
#define EFI_MSR_IA32_THERM_STATUS     0x19C
#define EFI_MSR_GV_THERM              0x19D

#define B_BS_VID                      0x0000003F
#define N_BS_VID                      0
#define B_BS_RATIO                    0x00001F00
#define N_BS_RATIO                    8

//
// UINT64 workaround
//
// The MS compiler doesn't handle QWORDs very well.  I'm breaking
// them into DWORDs to circumvent the problems.  Converting back
// shouldn't be a big deal.
//
#pragma pack(1)
typedef union _MSR_REGISTER {
  UINT64  Qword;

  struct _DWORDS {
    UINT32  Low;
    UINT32  High;
  } Dwords;

  struct _BYTES {
    UINT8 FirstByte;
    UINT8 SecondByte;
    UINT8 ThirdByte;
    UINT8 FouthByte;
    UINT8 FifthByte;
    UINT8 SixthByte;
    UINT8 SeventhByte;
    UINT8 EighthByte;
  } Bytes;

} MSR_REGISTER;
#pragma pack()

typedef struct _FVID_HEADER {
  UINT16  Stepping;     // Matches value returned by CPUID function 1
  UINT16  MaxVid;       // Matches VID_MAX field in PERF_STS_MSR
  UINT16  MaxBusRatio;  // Matches BUS_RATIO_MAX field in PERF_STS_MSR
  UINT16  Gv3States;    // Number of states of FVID (N)
} FVID_HEADER;

typedef struct _FVID_STATE {
  UINT16  State;        // State Number (0 - N-1)
  UINT16  Vid;          // VID_SEL value to be written to PERF_CTL
  UINT16  BusRatio;     // BUS_RATIO_SEL value to be written to PERF_CTL
  UINT16  Power;        // Typical power consumed by CPU in this state
} FVID_STATE;

typedef union _FVID_TABLE {
  FVID_HEADER FvidHeader;
  FVID_STATE  FvidState;
  UINT64      FvidData;
} FVID_TABLE;

#endif
