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
