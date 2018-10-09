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
  
    EmsEftpRrqStrategy.c
    
Abstract:

    

--*/

#include "EmsEftp.h"
#include "EmsEftpSession.h"
#include "EmsEftpStrategy.h"
#include "EmsEftpRrqStrategy.h"

VOID
EmsEftpRrqStrategyClose (
  Eftp_Strategy *Strategy
  )
/*++

Routine Description:

  Close the EMS Eftp read requeset strategy

Arguments:

  Strategy  - The strategy should be closed

Returns:

  None

--*/
{
  if (Strategy->Fp != NULL) {
    fclose (Strategy->Fp);
  }

  memset (Strategy, 0x0, sizeof (Eftp_Strategy));
}

INT32
EmsEftpRrqStrategyOpen (
  Eftp_Strategy       *Strategy,
  CONST INT8          *FileName
  )
/*++

Routine Description:

  Open an Eftp read request strategy

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

  if (NULL == (Strategy->Fp = fopen (Strategy->FileName, "rb"))) {
    EFTP_DEBUG_MSG ("EmsEftpRrqStrategyOpen: Open file %s failed - %s\n", Strategy->FileName, strerror (errno));
    Strategy->Close (Strategy);
    return -1;
  }

  /* Get the file size */
  fseek (Strategy->Fp, 0, SEEK_END);
  Strategy->FileSizeInBytes   = ftell (Strategy->Fp);
  Strategy->BlockSizeInBytes  = FILE_BLK_SIZE;
  Strategy->NextBlkNo         = 1;
  Strategy->FileMaxBlkNo      = (Strategy->FileSizeInBytes + Strategy->BlockSizeInBytes - 1) / Strategy->BlockSizeInBytes;

  return 0;
}

VOID
EmsEftpRrqStrategyHandlePkt (
  Eftp_Strategy *Strategy,
  CONST INT8    *PktBuffer,
  INT32         Length
  )
/*++

Routine Description:

  The routine be used to process packages which corresponding to read
  request

Arguments:

  Strategy  - The session's strategy
  PktBuffer - The data buffer of packet
  Length    - The length of the data buffer of packet

Returns:

  None

--*/
{
  INT8          FileContent[FILE_BLK_SIZE];
  UINT32        ReadLength;
  UINT32        SendPktLen;
  INT8          SendPkt[MAX_EFTP_BUF_LEN];
  UINT16        OpCode;
  UINT16        BlkNo;
  INT32         TmpLen;
  Eftp_Session  *Session;

  Session = NULL;
  Session = StrategyToSession (Strategy);
  Session->GetOpCode (PktBuffer, &OpCode);

  switch (OpCode) {
  case EFTP_RRQ:
    fseek (Strategy->Fp, 0, SEEK_SET);
    memset (FileContent, 0, sizeof (FileContent));
    if ((ReadLength = fread (FileContent, 1, Strategy->BlockSizeInBytes, Strategy->Fp)) <= 0) {
      EFTP_ERROR_MSG ("EmsEftpRrqStrategyHandlePkt: OpCode EFTP_RRQ file read error SilentShutdown\n");
      Session->SilentShutdown (Session);
      return ;
    }

    SendPktLen = Session->BuildPkt (
                            Session,
                            SendPkt,
                            EFTP_TYPE,
                            EFTP_DATA,
                            Strategy->NextBlkNo,
                            FileContent,
                            ReadLength
                            );
    Session->SendData (Session, SendPkt, SendPktLen);
    Strategy->NextBlkNo = 2;

    break;

  case EFTP_ACK:
    Session->GetBlkNo (PktBuffer, &BlkNo);

    if (BlkNo > Strategy->NextBlkNo - 1) {
      Strategy->NextBlkNo = BlkNo + 1;
      Strategy->LastAckNo = BlkNo;

      if (BlkNo >= Strategy->FileMaxBlkNo) {
        if (BlkNo == Strategy->FileMaxBlkNo || BlkNo == Strategy->FileMaxBlkNo + 1) {
          /*
           * silent shutdown the session because the data transfer was completed
           * since we got to the end of the file
           */
          Session->SilentShutdown (Session);
          return ;
        } else {
          /* send the error Pkt */
          TmpLen = sizeof ("Invalid block number to get file");
          memcpy (FileContent, "Invalid block number to get file", TmpLen);

          SendPktLen = Session->BuildPkt (
                                  Session,
                                  SendPkt,
                                  EFTP_TYPE,
                                  EFTP_ERROR,
                                  ERR_ILLEGAL_OPERATION,
                                  FileContent,
                                  TmpLen
                                  );
          Session->LoudShutdown (Session);
          Session->SendData (Session, SendPkt, SendPktLen);
          return ;
        }
      }
    } else if (BlkNo == Strategy->NextBlkNo - 1) {
      Strategy->LastAckNo = BlkNo;

      if ((0 == fseek (Strategy->Fp, Strategy->BlockSizeInBytes * BlkNo, SEEK_SET)) &&
          ((ReadLength = fread (FileContent, 1, Strategy->BlockSizeInBytes, Strategy->Fp)) > 0)
          ) {
        SendPktLen = Session->BuildPkt (
                                Session,
                                SendPkt,
                                EFTP_TYPE,
                                EFTP_DATA,
                                Strategy->NextBlkNo,
                                FileContent,
                                ReadLength
                                );
        Session->SendData (Session, SendPkt, SendPktLen);
        Strategy->NextBlkNo += 1;
      } else {
        /* Error or Eof then send OACK */
        TmpLen = sizeof ("File EOF");
        memcpy (FileContent, "File EOF", TmpLen);

        SendPktLen = Session->BuildPkt (
                                Session,
                                SendPkt,
                                EFTP_TYPE,
                                EFTP_OACK,
                                Strategy->NextBlkNo,
                                FileContent,
                                TmpLen
                                );
        /* Close current session */
        EFTP_ERROR_MSG ("EmsEftpRrqStrategyHandlePkt: OpCode EFTP_ACK Read file SilentShutdown\n");
        Session->SilentShutdown (Session);
        Session->SendData (Session, SendPkt, SendPktLen);
        return ;
      }
    } else {
      /* Resend the data if the Ack is relating to a previous Pkt */
      Session->ResendData (Session);
    }

    break;

  case EFTP_ERROR:
  default:
    Session->SilentShutdown (Session);
  }
}
