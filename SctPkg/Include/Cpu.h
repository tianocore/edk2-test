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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
