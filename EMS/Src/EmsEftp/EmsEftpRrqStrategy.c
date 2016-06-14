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
