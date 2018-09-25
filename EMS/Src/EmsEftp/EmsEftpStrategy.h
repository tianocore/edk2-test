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
  
    EmsEftpStrategy.h
    
Abstract:

    Incude header files EMS Eftp

--*/

#ifndef __EMS_EFTP_STRATEGY_H__
#define __EMS_EFTP_STRATEGY_H__

typedef struct Eftp_Strategy_Struct {
  INT8                          FileName[MAX_FILENAME_LEN];
  FILE                          *Fp;
  INT32                         FileSizeInBytes;
  INT32                         FileMaxBlkNo;
  INT32                         BlockSizeInBytes;
  INT32                         NextBlkNo;
  INT32                         LastAckNo;

  VOID_P (*HandlePkt) (struct Eftp_Strategy_Struct *, CONST INT8 *, INT32 );
  INT32 (*Open) (struct Eftp_Strategy_Struct *, CONST INT8 *);
  VOID_P (*Close) (struct Eftp_Strategy_Struct *);
}Eftp_Strategy;

#define StrategyToSession(Strategy)  ((Eftp_Session *)((UINT8 *)(Strategy) - (UINT32)&(((Eftp_Session *)0)->Strategy)))

#endif
