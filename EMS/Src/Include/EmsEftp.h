/** @file
 
  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsEftp.h
    
Abstract:

    Header files for EFTP implementation.

--*/

#ifndef __EMS_EFTP_H__
#define __EMS_EFTP_H__

#include <EmsTypes.h>
#include <EmsTclInit.h>
#include <EmsNet.h>

#define EFTP_TYPE         0x8888
#define MAX_EFTP_BUF_LEN  1500
#define SRC_MAC_OFFSET    0
#define DES_MAC_OFFSET    6
#define TYPE_OFFSET       12
#define LENGTH_OFFSET     14
#define CHECK_SUM_OFFSET  16
#define OPCODE_OFFSET     18
#define BLKNO_OFFSET      20
#define DATA_OFFSET       22
#define FILE_NAME_OFFSET  DATA_OFFSET
#define MAX_MAC_LEN       6
#define MAX_FILENAME_LEN  128
#define MAX_FILEDATA_LEN  1024
#define EFTP_HEADER_LEN   8
#define MAX_TIMEOUT_COUNT 2
#define MAX_TIMEOUT_VALUE 2000
#define FILE_BLK_SIZE     1024
#define EFTP_CRC_LEN      4
#define MAX_SESSION_NUM   6

typedef struct EmsPktStruct {
  struct EmsPktStruct *Next;
  UINT32              Length;
  INT8                Buffer[MAX_EFTP_BUF_LEN];
} EmsEftpPkt;

typedef struct EmsEftpRequestStruct {
  struct EmsEftpRequestStruct *Next;
  HANDLE                      WaitEvent;
} EmsEftpRequest;

STATIC Tcl_CmdProc  TclEftpStart;

VOID
EftpTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS Eftp related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

VOID
EmsEftpModEnable (
  VOID
  )
/*++

Routine Description:

  Enable the EMS Eftp utility

Arguments:

  None

Returns:

  None

--*/
;

EmsEftpRequest *
EmsEftpRegisterRequest (
  VOID
  )
/*++

Routine Description:

  Register an EMS Eftp request

Arguments:

  None

Returns:

  The new EMS Eftp request

--*/
;

VOID
EmsEftpRequestWait (
  EmsEftpRequest *Req
  )
/*++

Routine Description:

  Wait for the EMS Eftp request

Arguments:

  Req - EMS Eftp request should wait for

Returns:

  None

--*/
;

VOID
EmsEftpRequestSignal (
  VOID
  )
/*++

Routine Description:

  Signal The EMS thread which waiting for the EMS Eftp Request

Arguments:

  None

Returns:

  None

--*/
;

#define EFTP_ERROR_MSG  printf
#define EFTP_DEBUG_MSG  printf

#endif
