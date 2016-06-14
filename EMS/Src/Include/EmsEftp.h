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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
