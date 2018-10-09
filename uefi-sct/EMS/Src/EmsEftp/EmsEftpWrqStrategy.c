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
  
    EmsEftpWrqStrategy.c
    
Abstract:

    

--*/

#include "EmsEftp.h"
#include "EmsEftpSession.h"
#include "EmsEftpStrategy.h"
#include "EmsEftpWrqStrategy.h"

INT32
EmsEftpWrqStrategyOpen (
  Eftp_Strategy       *Strategy,
  CONST INT8          *FileName
  )
/*++

Routine Description:

  Open an Eftp write request strategy

Arguments:

  Strategy  - The strategy should be opened
  FileName  - The name of the file which will be accessed

Returns:

  -1 Failure
  0  Success

--*/
{
  /* Get the filename */
  strcpy (Strategy->FileName, FileName);

  /* Open this file for writing */
  if (NULL == (Strategy->Fp = fopen (Strategy->FileName, "wb"))) {
    /* Some error happens */
    EFTP_DEBUG_MSG ("EmsEftpWrqStrategyOpen: Open file %s failed \n", Strategy->FileName);
    Strategy->Close (Strategy);
    return -1;
  }

  Strategy->BlockSizeInBytes  = FILE_BLK_SIZE;
  Strategy->NextBlkNo         = 1;

  return 0;
}

VOID
EmsEftpWrqStrategyHandlePkt (
  Eftp_Strategy *Strategy,
  CONST INT8    *PktBuffer,
  INT32         Len
  )
/*++

Routine Description:

  The routine be used to process packages which corresponding to write
  request

Arguments:

  Strategy  - The session's strategy
  PktBuffer - The data buffer of packet
  Length    - The length of the data buffer of packet

Returns:

  None

--*/
{
  UINT32        WriteLength;
  UINT32        SendPktLen;
  INT8          SendPkt[MAX_EFTP_BUF_LEN];
  UINT16        OpCode;
  UINT16        BlkNo;
  UINT16        Length;
  Eftp_Session  *Session;

  Session = StrategyToSession (Strategy);
  Session->GetOpCode (PktBuffer, &OpCode);

  switch (OpCode) {
  case EFTP_WRQ:
    /* Build Ack(Blk0) and send */
    SendPktLen = Session->BuildPkt (Session, SendPkt, EFTP_TYPE, EFTP_ACK, 0, NULL, 0);
    Session->SendData (Session, SendPkt, SendPktLen);
    break;

  case EFTP_DATA:
    /* Get the BlkNo from the data pkt */
    Session->GetBlkNo (PktBuffer, &BlkNo);

    /*
     * Block(Strategy->NextBlkNo - 1) was received before,
     * and we just resend the Ack(NextBlkNo-1) to the client
     */
    if (BlkNo != Strategy->NextBlkNo) {
      SendPktLen = Session->BuildPkt (Session, SendPkt, EFTP_TYPE, EFTP_ACK, Strategy->NextBlkNo - 1, NULL, 0);
      Session->SendData (Session, SendPkt, SendPktLen);
      return ;
    }

    /* get the pkt except and write file */
    Session->GetLength (PktBuffer, &Length);
    fseek (Strategy->Fp, Strategy->BlockSizeInBytes * (BlkNo - 1), SEEK_SET);
    if ((WriteLength = fwrite (PktBuffer + DATA_OFFSET, 1, Length - EFTP_HEADER_LEN, Strategy->Fp)) !=
          (Length - EFTP_HEADER_LEN)
          ) {
      /* write error */
      EFTP_DEBUG_MSG ("EmsEftpWrqStrategyHandlePkt: Write file failure \n");
      Session->SilentShutdown (Session);
      return ;
    }

    /* write file finished and send ACK */
    Strategy->NextBlkNo += 1;
    SendPktLen = Session->BuildPkt (Session, SendPkt, EFTP_TYPE, EFTP_ACK, BlkNo, NULL, 0);
    Session->SendData (Session, SendPkt, SendPktLen);

    break;

  case EFTP_ERROR:
  default:
    /* Something goes wrong */
    Session->SilentShutdown (Session);
  }
}

VOID
EmsEftpWrqStrategyClose (
  Eftp_Strategy *Strategy
  )
/*++

Routine Description:

  Close the EMS Eftp write requeset strategy

Arguments:

  Strategy  - The strategy should be closed

Returns:

  None

--*/
{
  if (Strategy->Fp != NULL) {
    fclose (Strategy->Fp);
  }

  EmsEftpRequestSignal ();
  memset (Strategy, 0x0, sizeof (Eftp_Strategy));
}
