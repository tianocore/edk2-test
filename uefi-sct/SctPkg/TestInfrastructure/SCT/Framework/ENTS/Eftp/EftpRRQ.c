/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
        EftpRRQ.c
 
Abstract:
	Eftp RRQ process routines
--*/
#include "Efi.h"
#include "EftpMain.h"

STATIC
EFI_STATUS
EFIAPI
EftpRrqSendAck (
  IN EFTP_IO_PRIVATE  *Private,
  IN UINT64           BlkNo
  );

STATIC
EFI_STATUS
EFIAPI
EftpRrqSaveBlk (
  IN EFTP_IO_PRIVATE  *Private,
  IN EFI_EFTP_PACKET  *Packet,
  IN UINTN            PacketLen
  );

STATIC
EFI_STATUS
EFIAPI
EftpRrqFlushLostBlock (
  IN EFTP_IO_PRIVATE  *Private
  );

STATIC
BOOLEAN
EftpListIntegrityCheck (
  IN NET_LIST_ENTRY*ListHead
  );

STATIC
VOID
EFIAPI
EftpRrqTxCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  );

STATIC
VOID
NumToAsciiStr (
  IN UINTN  Number,
  IN UINT8  *Buffer,
  OUT UINTN *Length
  )
/*++

Routine Description:
  Convert number to ASCII value

Arguments:
  Number  - Numeric value to convert to decimal ASCII value.
  Buffer  - Buffer to place ASCII version of the Number
  Length  - Length of Buffer.

Returns:
  None

--*/
{
  UINTN Remainder;
  UINTN Index;
  UINTN Count;
  CHAR8 Temp[20];

  Index = 0;
  Count = 0;

  while (Number != 0) {
    Remainder = Number % 10;
    Number /= 10;
    Temp[Count] = (UINT8) ('0' + Remainder);
    Count++;
  }

  while (Count != 0) {
    Buffer[Index] = Temp[Count - 1];
    Index++;
    Count--;
  }
  //
  // Deal the situation that the value of number is 0
  //
  if (Index == 0) {
    Buffer[Index] = '0';
    Index++;
  }

  Buffer[Index] = 0;
  *Length       = Index;
  return ;
}

EFTP_RRQ_STATE *
EftpInitRrqState (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Init the Eftp instance for download

Arguments:

  Private - Eftp instance private data

Returns:

  NULL                    - Failed to allocate buffer for RRQ state
  Point to EFTP_RRQ_STATE - RRQ state allocated and initialized

--*/
{
  EFTP_RRQ_STATE  *Rrq;

  ASSERT (Private);

  Rrq = NetAllocateZeroPool (sizeof (EFTP_RRQ_STATE));
  if (Rrq == NULL) {
    EFTP_DEBUG_ERROR ((L"EftpInitRrqState: failed to create RRQ data\n"));

    Private->Result = EFI_OUT_OF_RESOURCES;
    return NULL;
  }

  EFTP_DEBUG_VERBOSE ((L"EftpInitRrqState: initialize Rrq role to ROLE_INIT\n"));
  EftpRrqChangeRole (EFTP_RRQ_ROLE_INIT, Rrq);
  LIST_INIT (&Rrq->LostPacketList);

  return Rrq;

}

VOID
EftpRrqRxCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Receive callback function called by MNP when packet is available.
  It dispatches the packet according to it type.

Arguments:

  Event   - Event signaled by MNP 
  Context - The event's context, it is a point to EFTP_COMPLETION_TOKEN

Returns:

  None

--*/
{
  EFTP_IO_PRIVATE                   *Private;
  EFI_EFTP_PACKET                   *Packet;
  EFTP_COMPLETION_TOKEN             *Token;
  EFTP_PACKET_BUFFER                *Buf;
  EFI_MANAGED_NETWORK_RECEIVE_DATA  *RxData;
  EFTP_RRQ_STATE                    *Rrq;
  EFTP_ERRINFO                      Err;
  UINT32                            PacketLen;
  UINT16                            OpCode;
  EFI_STATUS                        Status;
  EFI_STATUS                        TmpStatus;

  Buf     = NULL;
  Packet  = NULL;
  RxData  = NULL;

  ASSERT (Context != NULL);

  Token = (EFTP_COMPLETION_TOKEN *) Context;
  ASSERT (Token->Signature == EFTP_TOKEN_SIGNATURE);

  Private = Token->Private;
  
  if (Private->State == EFTP_INIT) {
    return;
  }
  
  ASSERT (Private->Signature == EFTP_IO_PRIVATE_SIGNATURE);
  ASSERT (Token == &Private->UniToken);
  Rrq = Private->RrqState;

  if (EFI_ERROR (Token->MnpToken.Status)) {
    EFTP_DEBUG_ERROR (
      (L"EftpRrqRxCallback: receive failed, token's status is %r\n",
      Token->MnpToken.Status)
      );

    //
    // BUGBUG: Need check this?
    //
    if ((Token->MnpToken.Status == EFI_TIMEOUT) || (Token->MnpToken.Status == EFI_ABORTED)) {

      Status = EFI_SUCCESS;
      goto CleanUp;

    } else {
      if (Private->State != EFTP_TIME_WAIT && Private->State != EFTP_RRQ_CLOSEING) {

        Private->Result = (Token->MnpToken.Status == EFI_DEVICE_ERROR ? EFI_DEVICE_ERROR : EFI_ICMP_ERROR);

      }

      Status = EFI_ABORTED;

      RRQ_SILENT_SHUTDOWN (Private);
      goto CleanUp;

    }

  }

  RxData = Token->MnpToken.Packet.RxData;
  ASSERT (RxData);

#ifdef _EFTP_STAT_
  Private->RcvdPkts++;
#endif
  //
  // Check Packet Length
  //
  if ((RxData->DataLength < EFTP_HEADER_LEN) || (!RxData->PacketData)) {
    EFTP_DEBUG_ERROR (
      (L"EftpRrqRxCallback: Get a packet which is too short %d and no data is attached, ignore it\n",
      RxData->DataLength)
      );

#ifdef _EFTP_STAT_
    Private->DroppedPkts++;
#endif

    Status = EFI_SUCCESS;
    goto CleanUp;
  }

  EFTP_DEBUG_VERBOSE ((L"EftpRrqRxCallback: current role is %d\n", Rrq->Role.Type));

  Packet    = (EFI_EFTP_PACKET *) RxData->PacketData;
  PacketLen = NTOHS (Packet->Hdr.Length);
  OpCode    = NTOHS (Packet->Hdr.OpCode);

  //
  // BUGBUG: Need reivew, currently no checksum.
  //
#ifdef _ENABLE_EFTP_CHECKSUM_
  if (EftpCkSum ((UINT16 *) Packet, PacketLen / 2) != 0) {
    EFTP_DEBUG_ERROR (
      (L"EftpRrqRxCallback: Get a packet with wrong checksum %d\n",
      EftpCkSum ((UINT16 *) Packet,
      PacketLen / 2))
      );

#ifdef _EFTP_STAT_
    Private->DroppedPkts++;
#endif

    Status = EFI_SUCCESS;
    goto CleanUp;
  }
#endif
  //
  // call CheckPacket to packet DATA/DATA8/OACK/ERROR, and DATA/DATA8 is called at
  // DATA/DATA8 handler
  //
  if ((OpCode == EFI_EFTP_OPCODE_OACK || OpCode == EFI_EFTP_OPCODE_ERROR) &&
      Private->Token &&
      Private->Token->CheckPacket
      ) {

    EFTP_DEBUG_VERBOSE (
      (L"EftpRrqRxCallback: call user's CheckPacket function %x for packet %d.\n",
      Private->Token->CheckPacket,
      OpCode)
      );

    Status = Private->Token->CheckPacket (&Private->Eftp, Private->Token, (UINT16) PacketLen, Packet);

    if (EFI_ERROR (Status)) {
      //
      // User cancel current TFTP process
      //
      EFTP_DEBUG_ERROR ((L"EftpRrqRxCallback: User canceled the process with %r returned.\n", Status));

      Private->Result = EFI_ABORTED;

      //
      // Do NOT send an error packet when received one. Error packet will end the process
      //
      if (OpCode == EFI_EFTP_OPCODE_ERROR) {
        EFTP_DEBUG_WARN ((L"EftpRrqRxCallback: User canceled the process when received an error packet\n"));

        RRQ_SILENT_SHUTDOWN (Private);
        goto CleanUp;

      }
      //
      // When multicasting, we have two channel, the control channel and multicast channel
      // If the user application abortes the download in one channel, we can still receive
      // packet in another channel. Pay special attention when interact with user
      //
      if (Private->State == EFTP_TIME_WAIT) {
        EFTP_DEBUG_WARN ((L"EftpRrqRxCallback: User canceled the process in TIME_WAIT state\n"));

        goto CleanUp;

      }

      Err.Code  = EFI_EFTP_ERRORCODE_NOT_DEFINED;
      Err.Desc  = "User caceled download";

      TmpStatus = EftpSendError (Private, &Err, EftpRrqTxCallback);

      if (EFI_ERROR (TmpStatus)) {
        EFTP_DEBUG_ERROR ((L"EftpRrqRxCallback: double error occured when deal with user cancellation\n"));

        RRQ_SILENT_SHUTDOWN (Private);
        goto CleanUp;
      }

      RRQ_LOUD_SHUTDOWN (Private);
      goto CleanUp;

    }
  }
  //
  // a RRQ client only expects to receive DATA/DATA8/ERROR/OACK packets
  // RRQ's packet handler should return EFI_SUCCESS to restart receiveing, otherwise
  // return an EFI_ERROR(Status) to stop receiving
  //
  switch (OpCode) {
  case EFI_EFTP_OPCODE_DATA:
    if ((PacketLen > (UINTN) (EFTP_HEADER_LEN + Private->Option.BlkSize + Private->Option.BlknoLen)) ||
        (PacketLen < (UINTN) (EFTP_HEADER_LEN + Private->Option.BlknoLen))
        ) {
      EFTP_DEBUG_VERBOSE ((L"EftpRrqRxCallback: ignore a too long packet %d.\n", PacketLen));

#ifdef _EFTP_STAT_
      Private->DroppedPkts++;
#endif

      Status = EFI_SUCCESS;
      goto CleanUp;
    }

    ASSERT (Rrq->Role.EftpRrqRcvData);
    Status = Rrq->Role.EftpRrqRcvData (Private, Packet, PacketLen);

    if (!EFI_ERROR (Status)) {
      Private->NRetry = 0;

    }

    EFTP_DEBUG_VERBOSE ((L"EftpRrqRxCallback: EftpRrqRcvData returns %r.\n", Status));
    break;

  case EFI_EFTP_OPCODE_ERROR:
    //
    // The length of error Message should be 1 byte("") at least to terminate the string.
    //
    if (PacketLen < (UINTN) (EFTP_HEADER_LEN + 1)) {
      EFTP_DEBUG_VERBOSE ((L"EftpRrqRxCallback: ignore a too long packet %d.\n", PacketLen));

#ifdef _EFTP_STAT_
      Private->DroppedPkts++;
#endif

      Status = EFI_SUCCESS;
      goto CleanUp;
    }

    ASSERT (Rrq->Role.EftpRrqRcvError);
    Status = Rrq->Role.EftpRrqRcvError (Private, Packet, PacketLen);

    //
    // Return EFI_NOT_READY if server tell client to try latter
    //
    if (EFI_EFTP_ERRORCODE_TRY_LATTER == NTOHS (Packet->Error.ErrorCode)) {
      Private->Result = EFI_NOT_READY;
    }

    EFTP_DEBUG_VERBOSE ((L"EftpRrqRxCallback: EftpRrqRcvError returns %r.\n", Status));
    break;

  case EFI_EFTP_OPCODE_OACK:
    //
    // The length of OACK should be 4 bytes at least (OpCode + two null string)
    //
    if (PacketLen < (UINTN) (EFTP_HEADER_LEN)) {
      EFTP_DEBUG_VERBOSE ((L"EftpRrqRxCallback: receive a bad OACK, ignore it.\n"));

#ifdef _EFTP_STAT_
      Private->DroppedPkts++;
#endif

      Status = EFI_SUCCESS;
      goto CleanUp;
    }

    ASSERT (Rrq->Role.EftpRrqRcvOack);
    Status = Rrq->Role.EftpRrqRcvOack (Private, Packet, PacketLen);

    EFTP_DEBUG_VERBOSE ((L"EftpRrqRxCallback: EftpRrqRcvOack returns %r.\n", Status));
    break;

  default:
    EFTP_DEBUG_ERROR ((L"EftpRrqRxCallback: Get an unexpected packet, opcode=%d, ignore it.\n", OpCode));

#ifdef _EFTP_STAT_
    Private->DroppedPkts++;
#endif

    Status = EFI_SUCCESS;
    break;

  }

CleanUp:
  if (Buf) {
    EftpReleasePacket (Buf);
  }
  //
  // BUGBUG:: Need review
  //
  if (RxData && Token->MnpToken.Event) {
    //
    // BUGBUG: Need review
    // when client close mcast port or udp port , it will
    // destroy the udp instance it used and set the UdpToken.Event as
    // NULL, in this case we must not signal recycle signal, because
    // it will cause resource to be released for another times
    //
    tBS->SignalEvent (RxData->RecycleEvent);
  }

  if (!EFI_ERROR (Status)) {
    Status = EftpStartRcv (Private);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqRxCallback: failed to restart the receive, status is %r.\n", Status));

      RRQ_SILENT_SHUTDOWN (Private);
    }
  }

}

EFI_STATUS
EFIAPI
EftpBuildRrq (
  IN EFTP_IO_PRIVATE  *Private,
  IN UINT16           OpCode
  )
/*++

Routine Description:

  Build a RRQ packet from the user info, and save it at Private->Request

Arguments:

  Private - Eftp instance private data
  OpCode  - OpCode to use when build request packet. It can be a RRQ or ReadDirectory

Returns:

  EFI_OUT_OF_RESOURCES - Failed to build the request packet
  EFI_SUCCESS          - Successfully build the request packet

--*/
{
  EFI_EFTP_TOKEN      *Token;
  EFTP_PACKET_BUFFER  *Buf;

  ASSERT (Private && Private->Token);

  Token = Private->Token;

  Buf = EftpBuildRequest (
          Private,
          OpCode,
          Token->Filename,
          Token->ModeStr,
          Token->OptionCount,
          Token->OptionList,
          EftpRrqTxCallback
          );

  if (Buf == NULL) {
    EFTP_DEBUG_ERROR ((L"EftpBuildRrq: failed to build a request packet"));
    return EFI_OUT_OF_RESOURCES;
  }

  if (Private->Request) {
    EftpReleasePacket (Private->Request);

  }

  Private->Request = Buf;
  return EFI_SUCCESS;
}

VOID
EftpRrqTimer (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Timer function to deal with download timeout

Arguments:

  Event    - Event signaled 
  Context  - The context of the event, it is a point to EFTP_IO_PRIVATE

Returns:

  None

--*/
{
  EFTP_IO_PRIVATE *Private;
  EFTP_RRQ_STATE  *Rrq;
  EFI_STATUS      Status;

  ASSERT (Context != NULL);

  Private = (EFTP_IO_PRIVATE *) Context;
  ASSERT (Private->Signature == EFTP_IO_PRIVATE_SIGNATURE);

#ifdef _EFTP_STAT_
  if (Private->State != EFTP_RRQ_CLOSEING && Private->State != EFTP_TIME_WAIT) {
    Private->Timeouts++;
  }
#endif
  //
  // Do NOT call user's TimeoutCallback at Closing and Timewait state. Those two states'
  // timer is to enable graceful shutdown.
  //
  if (Private->Token &&
      Private->Token->TimeoutCallback &&
      (Private->State != EFTP_RRQ_CLOSEING) &&
      (Private->State != EFTP_TIME_WAIT)
      ) {

    EFTP_DEBUG_VERBOSE (
      (L"EftpRrqTimer: to call the user's timeout callback@%x\n",
      Private->Token->TimeoutCallback)
      );

    Status = Private->Token->TimeoutCallback (&(Private->Eftp), Private->Token);

    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqTimer: User cancled the download process\n"));

      Private->Result = EFI_ABORTED;
      RRQ_SILENT_SHUTDOWN (Private);
      return ;
    }
  }

  Rrq = Private->RrqState;
  ASSERT (Rrq && Rrq->Role.EftpRrqTimer);

  EFTP_DEBUG_VERBOSE ((L"EftpRrqTimer: current role is%d\n", Rrq->Role.Type));

  Rrq->Role.EftpRrqTimer (Event, Context);

}

VOID
EftpRrqCleanUp (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Gracefully shutdown the eftp instance. It releases the various resources
  then signal the user event.

Arguments:

  Private - Eftp instance private data

Returns:

  None
--*/
{
  EFTP_RRQ_STATE  *Rrq;

  ASSERT (Private && Private->RrqState);
  Rrq = Private->RrqState;

  ASSERT (EftpListIntegrityCheck (&Rrq->LostPacketList));

  if (!LIST_IS_EMPTY (&Rrq->LostPacketList)) {
    EftpRrqFlushLostBlock (Private);
  }

  NetFreePool (Private->RrqState);
  Private->RrqState = NULL;

  if (Private->Request) {
    EftpReleasePacket (Private->Request);
    Private->Request = NULL;
  }

  if (Private->LastCtrl) {
    EftpReleasePacket (Private->LastCtrl);
    Private->LastCtrl = NULL;
  }

  EFTP_DEBUG_VERBOSE (
    (L"EftpRrqCleanUp: number of pending packet is %d\n",
    Private->NPendingPacket)
    );

  tBS->CloseEvent (Private->TimeoutEvent);
  Private->TimeoutEvent   = NULL;

  Private->Token->Status  = Private->Result;

  ASSERT (!Private->UserEvtFired && !Private->SynFinished);

  if (Private->Token->Event) {
    Private->UserEvtFired = TRUE;
    tBS->SignalEvent (Private->Token->Event);
  }

  Private->SynFinished  = TRUE;
  Private->State        = EFTP_INIT;
}

STATIC
VOID
EFIAPI
EftpRrqTxCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Callback function called by MNP when it finishes send our packets.

  One issue of Role-based design is that when the Send-Complete-Callback
  is called, the role may has changed since the event's created
  We are lucky all the roles' Send-Complete-Callback are the same.

Arguments:

  Event   - Event signaled by MNP
  Context - The event's context, it is a point to EFTP_PACKET_BUFFER
  
Returns:

  None

--*/
{
  EFTP_IO_PRIVATE     *Private;
  EFTP_PACKET_BUFFER  *Buf;

  ASSERT (Context != NULL);

  Buf = (EFTP_PACKET_BUFFER *) Context;
  ASSERT (Buf->EftpToken.Signature == EFTP_TOKEN_SIGNATURE);

  Private = Buf->EftpToken.Private;
  ASSERT (Private->Signature == EFTP_IO_PRIVATE_SIGNATURE);

  switch (Private->State) {
  case EFTP_INIT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_SENT:
  case EFTP_RRQ_ESTABLISHED:
  case EFTP_RRQ_CLOSEING:
    ASSERT (EntryInList (&Private->PendingPacketList, &Buf->List));

    Private->NPendingPacket--;
    LIST_REMOVE_ENTRY (&Buf->List);
    EftpReleasePacket (Buf);
    break;

  case EFTP_TIME_WAIT:
    ASSERT (EntryInList (&Private->PendingPacketList, &Buf->List));

    Private->NPendingPacket--;
    LIST_REMOVE_ENTRY (&Buf->List);
    EftpReleasePacket (Buf);

    if (Private->NPendingPacket == 0) {
      EftpRrqCleanUp (Private);

    }

    break;

  default:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;
  }

}
//
// The event process routines for EFTP_ROLE_INIT
//
EFI_STATUS
EftpRrqInitRcvData (
  IN EFTP_IO_PRIVATE            *Private,
  IN EFI_EFTP_PACKET            *Packet,
  IN UINT32                     PacketLen
  )
/*++

Routine Description:

  The data packet process routine when in INIT role.

Arguments:

  Private   - Eftp instance private data
  Packet    - Packet received 
  PacketLen - Length of the received packet
  
Returns:

  EFI_SUCCESS  - Data packet is OK, and the instance is willing to receive another packet
  EFI_ABORTED  - Don't restart receiving on the port, something is wrong

--*/
{
  EFTP_OPTION         *Opt;
  EFTP_RRQ_STATE      *Rrq;
  EFTP_PACKET_BUFFER  *Buf;
  BOOLEAN             Copy;
  EFI_STATUS          Status;
  UINT64              BlkNo;

  ASSERT (Private && Private->RrqState && Packet);

  Rrq = Private->RrqState;
  Opt = &Private->Option;

  //
  // Ignore the data packet with wrong opcode
  //
  if (Packet->Hdr.OpCode != HTONS (EFI_EFTP_OPCODE_DATA)) {
    return EFI_SUCCESS;
  }

  BlkNo = NTOHS (Packet->Data.Block);

  switch (Private->State) {
  case EFTP_INIT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_SENT:
    //
    // If a DATA is used to ack the RRQ request, the server doesn't
    // support any option, start the stand procedure
    //
    if (BlkNo != Private->NextBlkNo) {
      EFTP_DEBUG_ERROR (
        (L"EftpRrqInitRcvData: ignore a unexpected data block(%ld/%ld)\n",
        BlkNo,
        Private->NextBlkNo)
        );

#ifdef _EFTP_STAT_
      Private->DroppedPkts++;
#endif

      return EFI_SUCCESS;
    }

    EftpRrqChangeRole (EFTP_RRQ_ROLE_ACTIVE, Rrq);
    Private->State = EFTP_RRQ_ESTABLISHED;

    //
    // call the active role's DATA handler to process the data.
    // attention: current state is RRQ_ESTABLISHED
    //
    Status = Rrq->Role.EftpRrqRcvData (Private, Packet, PacketLen);
    return Status;
    break;

  case EFTP_RRQ_ESTABLISHED:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_CLOSEING:
    Buf = Private->LastCtrl;
    ASSERT (Buf && (Buf->RefCnt >= 1));

    Copy    = (BOOLEAN) (Buf->RefCnt > 1);

    Status  = EftpResendPacket (Private, Buf, Copy, EftpRrqTxCallback);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqRcvAck: failed to retransmit the packet, init silent shutdown\n"));

      RRQ_SILENT_SHUTDOWN (Private);
      return EFI_ABORTED;
    }
    //
    // Don't restart timer here, we will transit to TIMEWAIT once timeout
    //
    return EFI_SUCCESS;
    break;

  case EFTP_TIME_WAIT:
    //
    // ignore the data block and stop restart receiving
    //
    return EFI_ABORTED;
    break;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EftpRrqInitRcvError (
  IN EFTP_IO_PRIVATE   *Private,
  IN EFI_EFTP_PACKET   *Packet,
  IN UINT32            PacketLen
  )
/*++
Routine Description:

  The error packet process routine when in INIT role.

Arguments:

  Private   - Eftp instance private data
  Packet    - Packet received 
  PacketLen - Length of the received packet
  
Returns:

  EFI_SUCCESS - Error packet is OK, and the instance is willing to receive another packet
  EFI_ABORTED - Don't restart receiving on the port

--*/
{
  ASSERT (Private && Packet);

  switch (Private->State) {
  case EFTP_INIT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_SENT:
  case EFTP_RRQ_CLOSEING:
    EFTP_DEBUG_WARN (
      (L"EftpRrqInitRcvError: received an error packet(%d) from server\n",
      Packet->Error.ErrorCode)
      );

    Private->Result = EFI_TFTP_ERROR;
    RRQ_SILENT_SHUTDOWN (Private);
    return EFI_ABORTED;

    break;

  case EFTP_RRQ_ESTABLISHED:

    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_TIME_WAIT:
    //
    // ignore the error packet in time wait states
    //
    return EFI_ABORTED;
    break;
  }

  return EFI_SUCCESS;

}
#if 0
STATIC
EFI_STATUS
EftpRrqInitRcvOack (
  IN EFTP_IO_PRIVATE   *Private,
  IN EFI_EFTP_PACKET   *Packet,
  IN UINT32            PacketLen
  )
/*++
Routine Description:

  The OACK packet process routine when in INIT role.

Arguments:

  Private   - Eftp instance private data
  Packet    - Packet received 
  PacketLen - Length of the received packet
  
Returns:

  EFI_SUCCESS  - OACK packet is OK, and the instance is willing to receive another packet
  EFI_ABORTED  - Don't restart receiving on the port, user aborted or something is wrong

--*/
{
  EFI_STATUS    Status;
  EFTP_OPTION   *Opt;
  EFTP_ERRINFO  Err;

  ASSERT (Private && Private->RrqState && Packet);

  Opt = &Private->Option;

  switch (Private->State) {
  case EFTP_INIT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_SENT:
    Status = EftpExtractOptions (&Private->Eftp, Opt, Packet, PacketLen);

    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqInitRcvOack: failed to parse the OACK packet\n"));

      Private->Result = EFI_DEVICE_ERROR;
      Err.Code        = EFI_EFTP_ERRORCODE_ILLEGAL_OPERATION;
      Err.Desc        = "Mal-formed OACK packet";

      goto SendErr;
    }

    if (Private->Token->Buffer && (Private->Token->BufferSize < Opt->Tsize)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqInitRcvOack: user provided buffer is too small\n"));

      Private->Token->BufferSize  = Opt->Tsize;
      Private->Result             = EFI_BUFFER_TOO_SMALL;

      Err.Code                    = EFI_EFTP_ERRORCODE_DISK_FULL;
      Err.Desc                    = "User buffer is too small";
      goto SendErr;
    }

    Private->Timeout = Opt->Timeout;

    //
    // Begin  downloading, or normal tftp procedure
    //
    EftpRrqChangeRole (EFTP_RRQ_ROLE_ACTIVE, Private->RrqState);

    //
    // Send out an ack 0 for active clients
    //
    Status = EftpRrqSendAck (Private, 0);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqInitRcvOack: failed to send ACK0\n"));

      goto SilentShutdown;
    }

    EftpSetTimer (Private, Private->Timeout, 0);
    Private->State = EFTP_RRQ_ESTABLISHED;

    return EFI_SUCCESS;
    break;

  case EFTP_RRQ_ESTABLISHED:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_CLOSEING:

    return EFI_SUCCESS;
    break;

  case EFTP_TIME_WAIT:
    //
    // ignore any packet in TIME_WAIT state and don't restart receive
    //
    return EFI_ABORTED;
    break;
  }

  return EFI_SUCCESS;

SendErr:
  Status = EftpSendError (Private, &Err, EftpRrqTxCallback);

  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"EftpRrqInitRcvOack: failed to send an error packet (OACK malformed)\n"));
    goto SilentShutdown;
  }

  RRQ_LOUD_SHUTDOWN (Private);

  //
  // return EFI_SUCCESS to restart receiving
  //
  return EFI_SUCCESS;

SilentShutdown:
  RRQ_SILENT_SHUTDOWN (Private);

  //
  // Don't restart receiving when silent shutdown
  //
  return EFI_ABORTED;

}
#else
STATIC
EFI_STATUS
EftpRrqInitRcvOack (
  IN EFTP_IO_PRIVATE   *Private,
  IN EFI_EFTP_PACKET   *Packet,
  IN UINT32            PacketLen
  )
/*++
Routine Description:

  The OACK packet process routine when in INIT role.

Arguments:

  Private   - Eftp instance private data
  Packet    - Packet received 
  PacketLen - Length of the received packet
  
Returns:

  EFI_ABORTED  - something is wrong

--*/
{
  ASSERT (Private && Private->RrqState && Packet);
  return EFI_ABORTED;
}
#endif

VOID
EFIAPI
EftpRrqInitTimer (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++
Routine Description:

  The timer process routine when in INIT role.

Arguments:

  Event   - The timer event signaled
  Context - The event's context, it is a point to EFTP_IO_PRIVATE
  
Returns:

  None
  
--*/
{
  EFTP_IO_PRIVATE     *Private;
  EFI_STATUS          Status;
  EFTP_PACKET_BUFFER  *Buf;
  BOOLEAN             Copy;

  ASSERT (Context != NULL);
  Private = (EFTP_IO_PRIVATE *) Context;

  ASSERT ((Private->Signature == EFTP_IO_PRIVATE_SIGNATURE) && Private->RrqState);

  switch (Private->State) {
  case EFTP_INIT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_SENT:
    Private->NRetry++;
    if (Private->NRetry > Private->MaxNRetry) {
      EFTP_DEBUG_ERROR ((L"EftpRrqInitTimer: too many retries to send request\n"));

      //
      // do NOT send out an error packet, server port is unknown
      //
      Private->Result = EFI_TIMEOUT;
      RRQ_SILENT_SHUTDOWN (Private);
      return ;
    }

    Buf = Private->Request;
    ASSERT (Buf && (Buf->RefCnt >= 1));

    //
    // If RefCnt ==1, it means that the request  point is the only point
    // to the packet, we can reuse it. If RefCnt>1, it maybe that the packet is
    // also in the pending list, don't reuse it
    //
    Copy    = (BOOLEAN) (Buf->RefCnt > 1);

    Status  = EftpResendPacket (Private, Buf, Copy, EftpRrqTxCallback);

    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqInitTimer: failed to retransmit the request, init silent shutdown\n"));

      RRQ_SILENT_SHUTDOWN (Private);
      return ;
    }

    EftpSetTimer (Private, Private->Timeout, 0);
    break;

  case EFTP_RRQ_ESTABLISHED:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_CLOSEING:
    RRQ_SILENT_SHUTDOWN (Private);
    break;

  case EFTP_TIME_WAIT:
    EftpRrqCleanUp (Private);
    break;

  }

  return ;

}

//
// The event process routines for ROLE_ACTIVE. The valid states for Active is
// RRQ_ESTABLISHED, RRQ_CLOSING, TIME_WAIT. This is because that we only transfer
// to active role in RRQ_ESTABLISHED state from ROLE_INIT. Also, an error packet
// will be generated upon error
//
STATIC
EFI_STATUS
EftpRrqActiveRcvData (
  IN EFTP_IO_PRIVATE              *Private,
  IN EFI_EFTP_PACKET              *Packet,
  IN UINT32                       PacketLen
  )
/*++

Routine Description:

  The data packet process routine when in ACTIVE role.

Arguments:

  Private   - Eftp instance private data
  Packet    - Packet received 
  PacketLen - Length of the received packet
  
Returns:

  EFI_SUCCESS  - Data packet is OK, and the instance is willing to receive another packet
  EFI_ABORTED  - Don't restart receiving on the port, something is wrong

--*/
{
  EFTP_OPTION         *Opt;
  EFTP_RRQ_STATE      *Rrq;
  EFTP_PACKET_BUFFER  *Buf;
  EFTP_ERRINFO        Err;
  EFI_STATUS          Status;
  BOOLEAN             Copy;
  UINT64              BlkNo;

  ASSERT (Private && Private->RrqState && Packet);

  Rrq = Private->RrqState;
  Opt = &Private->Option;

  //
  // Ignore the data packet with wrong opcode
  //
  if (Packet->Hdr.OpCode != HTONS (EFI_EFTP_OPCODE_DATA)) {
    return EFI_SUCCESS;
  }

  BlkNo = NTOHS (Packet->Data.Block);

  switch (Private->State) {
  case EFTP_INIT:
  case EFTP_RRQ_SENT:

    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_ESTABLISHED:
    if (BlkNo != Private->NextBlkNo) {
      EFTP_DEBUG_ERROR (
        (L"EftpRrqActiveRcvData: ignore a unexpected data block(%ld/%ld)\n",
        BlkNo,
        Private->NextBlkNo)
        );

#ifdef _EFTP_STAT_
      Private->DroppedPkts++;
#endif

      return EFI_SUCCESS;
    }

    Status = EftpRrqSaveBlk (Private, Packet, PacketLen);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqActiveRcvData: failed to save the block\n"));
      Err.Code  = EFI_EFTP_ERRORCODE_DISK_FULL;
      Err.Desc  = (Private->Result == EFI_ABORTED ? "User cancelled download" : "Disk full");
      goto SendErr;

    }

    Status = EftpRrqSendAck (Private, BlkNo);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqActiveRcvData: failed to send the ack, silent shutdown\n"));

      goto SilentShutdown;
    }

    Private->NextBlkNo++;
#if 0
    if (PacketLen == (UINTN) (Opt->BlkSize + EFTP_HEADER_LEN)) {
      EftpSetTimer (Private, Private->Timeout, 0);
      return EFI_SUCCESS;
    }

    Private->Eof        = TRUE;
    Private->LastBlkNo  = BlkNo;

    Private->Result     = EFI_SUCCESS;
    goto LoudShutdown;
#else
    Private->LastBlkNo  = BlkNo;
    EftpSetTimer (Private, Private->Timeout, 0);
#endif
    break;

  case EFTP_RRQ_CLOSEING:
    Buf = Private->LastCtrl;
    ASSERT (Buf && (Buf->RefCnt >= 1));

    Copy    = (BOOLEAN) (Buf->RefCnt > 1);
    Status  = EftpResendPacket (Private, Buf, Copy, EftpRrqTxCallback);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqRcvAck: failed to retransmit the packet, init silent shutdown\n"));

      goto SilentShutdown;
    }
    //
    // Don't restart timer here, we will transit to TIMEWAIT once timeout
    //
    return EFI_SUCCESS;

    break;

  case EFTP_TIME_WAIT:
    //
    // returen EFI_ABORTED to stop receiving
    //
    return EFI_ABORTED;
    break;
  }

  return EFI_SUCCESS;

SendErr:
  Status = EftpSendError (Private, &Err, EftpRrqTxCallback);

  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"EftpRrqInitRcvOack: failed to send an error packet (OACK malformed)\n"));
    goto SilentShutdown;
  }

//LoudShutdown:
  RRQ_LOUD_SHUTDOWN (Private);

  //
  // return EFI_SUCCESS to restart receiving
  //
  return EFI_SUCCESS;

SilentShutdown:
  RRQ_SILENT_SHUTDOWN (Private);

  //
  // Don't restart receiving when silent shutdown
  //
  return EFI_ABORTED;
}

STATIC
EFI_STATUS
EftpRrqActiveRcvError (
  IN EFTP_IO_PRIVATE   *Private,
  IN EFI_EFTP_PACKET   *Packet,
  IN UINT32            PacketLen
  )
/*++
Routine Description:

  The error packet process routine when in ACTIVE role.

Arguments:

  Private   - Eftp instance private data
  Packet    - Packet received 
  PacketLen - Length of the received packet
  
Returns:

  EFI_SUCCESS  - Data packet is OK, and the instance is willing to receive another packet
  EFI_ABORTED  - Don't restart receiving on the port

--*/
{
  ASSERT (Private && Packet);

  switch (Private->State) {
  case EFTP_INIT:
  case EFTP_RRQ_SENT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_ESTABLISHED:
  case EFTP_RRQ_CLOSEING:
    EFTP_DEBUG_WARN (
      (L"EftpRrqActiveRcvError: received an error packet(%d) from server\n",
      Packet->Error.ErrorMessage)
      );

    Private->Result = EFI_TFTP_ERROR;
    RRQ_SILENT_SHUTDOWN (Private);
    return EFI_ABORTED;

    break;

  case EFTP_TIME_WAIT:
    return EFI_ABORTED;
    break;

  default:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;
  }

  return EFI_SUCCESS;
}

#if 0
STATIC
EFI_STATUS
EftpRrqActiveRcvOack (
  IN EFTP_IO_PRIVATE   *Private,
  IN EFI_EFTP_PACKET   *Packet,
  IN UINT32            PacketLen
  )
/*++

Routine Description:

  The OACK packet process routine when in ACTIVE role.

Arguments:

  Private     : Eftp instance private data
  Packet      : Packet received 
  PacketLen : Length of the received packet
  
Returns:

  EFI_SUCCESS  : OACK packet is OK, and the instance is willing to receive another packet
  EFI_ABORTED  : Don't restart receiving on the port, user aborted or something is wrong

--*/
{
  ASSERT (Private && Private->RrqState && Packet);

  switch (Private->State) {
  case EFTP_INIT:
  case EFTP_RRQ_SENT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_ESTABLISHED:
  case EFTP_RRQ_CLOSEING:
    //
    // ignore it and restart receiving
    //
    return EFI_SUCCESS;
    break;

  case EFTP_TIME_WAIT:
    //
    // ignore and do NOT restart receiving
    //
    return EFI_ABORTED;
    break;
  }

  return EFI_SUCCESS;
}
#else
STATIC
EFI_STATUS
EftpRrqActiveRcvOack (
  IN EFTP_IO_PRIVATE   *Private,
  IN EFI_EFTP_PACKET   *Packet,
  IN UINT32            PacketLen
  )
/*++

Routine Description:

  The OACK packet process routine when in ACTIVE role.

Arguments:

  Private     : Eftp instance private data
  Packet      : Packet received 
  PacketLen : Length of the received packet
  
Returns:

  EFI_SUCCESS  : OACK packet is OK, and the instance is willing to receive another packet
  EFI_ABORTED  : Don't restart receiving on the port, user aborted or something is wrong

--*/
{
  ASSERT (Private && Private->RrqState && Packet);

  switch (Private->State) {
  case EFTP_INIT:
  case EFTP_RRQ_SENT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_ESTABLISHED:
    Private->Eof        = TRUE;
    Private->Result     = EFI_SUCCESS;
    RRQ_LOUD_SHUTDOWN (Private);
    break;

  case EFTP_RRQ_CLOSEING:
  case EFTP_TIME_WAIT:
    return EFI_SUCCESS;
    break;

  default:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;
  }

  return EFI_SUCCESS;
}
#endif

STATIC
VOID
EFIAPI
EftpRrqActiveTimer (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  The timer process routine when in ACTIVE role.

Arguments:

  Event    : the timer event signaled
  Context : the event's context, it is a point to EFTP_IO_PRIVATE
  
Returns:

  None
  
--*/
{
  EFTP_IO_PRIVATE     *Private;
  EFI_STATUS          Status;
  EFTP_PACKET_BUFFER  *Buf;
  EFTP_ERRINFO        Err;
  BOOLEAN             Copy;

  ASSERT (Context != NULL);

  Private = (EFTP_IO_PRIVATE *) Context;
  ASSERT ((Private->Signature == EFTP_IO_PRIVATE_SIGNATURE) && Private->RrqState);

  switch (Private->State) {
  case EFTP_INIT:
  case EFTP_RRQ_SENT:

    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_RRQ_ESTABLISHED:
    Private->NRetry++;
    if (Private->NRetry > Private->MaxNRetry) {
      EFTP_DEBUG_ERROR ((L"EftpRrqActiveTimer: too many retries to send request\n"));

      Private->Result = EFI_TIMEOUT;
      Err.Code        = EFI_EFTP_ERRORCODE_NOT_DEFINED;
      Err.Desc        = "Too many timeouts";
      goto SendErr;

    }

    Buf = Private->LastCtrl;
    ASSERT (Buf && (Buf->RefCnt >= 1));

    Copy    = (BOOLEAN) (Buf->RefCnt > 1);

    Status  = EftpResendPacket (Private, Buf, Copy, EftpRrqTxCallback);

    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqActiveTimer: failed to retransmit the request, init silent shutdown\n"));

      goto SilentShutdown;
    }

    EftpSetTimer (Private, Private->Timeout, 0);
    return ;

  case EFTP_RRQ_CLOSEING:
    EFTP_DEBUG_VERBOSE ((L"EftpRrqActiveTimer: timeout in closing state, init silent shutdown\n"));

    goto SilentShutdown;
    break;

  case EFTP_TIME_WAIT:
    EftpRrqCleanUp (Private);
    return ;

  }

  return ;

SendErr:
  Status = EftpSendError (Private, &Err, EftpRrqTxCallback);

  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"EftpRrqInitRcvOack: failed to send an error packet (OACK malformed)\n"));
    goto SilentShutdown;
  }

  RRQ_LOUD_SHUTDOWN (Private);
  return ;

SilentShutdown:
  RRQ_SILENT_SHUTDOWN (Private);
  return ;
}

VOID
EftpRrqChangeRole (
  IN EFTP_RRQ_ROLE_TYPE Type,
  IN EFTP_RRQ_STATE     *State
  )
/*++

Routine Description:

  Change the role of RRQ client

Arguments:

  Type  : The role to change to
  State : The Eftp instance's RRQ specific data

Returns:

  None

--*/
{
  EFTP_RRQ_ROLE *Role;

  ASSERT ((Type >= EFTP_RRQ_ROLE_INIT) && (Type <= EFTP_RRQ_ROLE_ACTIVE));
  ASSERT (State != NULL);

  Role = &State->Role;
  EFTP_DEBUG_VERBOSE (
    (L"EftpRrqChangeRole: role changed from %d to %d\n",
    Role->Type,
    Type)
    );

  Role->Type = Type;

  switch (Type) {
  case EFTP_RRQ_ROLE_INIT:
    Role->EftpRrqRcvData  = EftpRrqInitRcvData;
    Role->EftpRrqRcvError = EftpRrqInitRcvError;
    Role->EftpRrqRcvOack  = EftpRrqInitRcvOack;
    Role->EftpRrqTimer    = EftpRrqInitTimer;
    break;

  case EFTP_RRQ_ROLE_ACTIVE:
    Role->EftpRrqRcvData  = EftpRrqActiveRcvData;
    Role->EftpRrqRcvError = EftpRrqActiveRcvError;
    Role->EftpRrqRcvOack  = EftpRrqActiveRcvOack;
    Role->EftpRrqTimer    = EftpRrqActiveTimer;
    break;
  }

}

#define MAX_REAL_FILE_SIZE    10485760

STATIC
EFI_STATUS
EFIAPI
EftpRrqSaveBlk (
  IN EFTP_IO_PRIVATE  *Private,
  IN EFI_EFTP_PACKET  *Packet,
  IN UINTN            PacketLen
  )
/*++

Routine Description:

  Save a received data block

Arguments:

  Private      :  The instance's private data 
  Packet      :  The received packet
  PacketLen :  Packet length

Returns:

  EFI_ABORTED  : User aborted the download.
  EFI_SUCCESS  : Successfully save the block.

--*/
{
  EFI_STATUS  Status;
  EFTP_OPTION *Opt;
  UINT64      BlkNo;
  UINT64      Start;
  UINTN       DataLen;

  ASSERT (Private && Packet && Private->Token);
  Opt = &Private->Option;

  if (Private->Token->CheckPacket) {
    EFTP_DEBUG_VERBOSE (
      (L"EftpRrqSaveBlk: to call user's check packet @ %x\n",
      Private->Token->CheckPacket)
      );

    Status = Private->Token->CheckPacket (
                              &Private->Eftp,
                              Private->Token,
                              (UINT16) PacketLen,
                              Packet
                              );

    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpRrqSaveBlk: user's check packet returns %r\n", Status));

      Private->Result = EFI_ABORTED;
      return Status;
    }
  }

  if (Private->Token->Buffer != NULL) {
    BlkNo   = NTOHS (Packet->Data.Block);

    DataLen = PacketLen - EFTP_HEADER_LEN;

    Start   = SctMultU64x32 (BlkNo - 1, Opt->BlkSize);

    if (Start + DataLen > MAX_REAL_FILE_SIZE) {
      EFTP_DEBUG_ERROR ((L"EftpRrqSaveBlk: User provided buffer is too small.\n"));

      Private->Token->BufferSize  = (UINT64) -1;
      Private->Result             = EFI_BUFFER_TOO_SMALL;
      return EFI_ABORTED;
    }

    NetCopyMem (
      ((UINT8 *) Private->Token->Buffer) + Start,
      (UINT8 *) Packet + EFTP_HEADER_LEN,
      DataLen
      );

    if (DataLen <= Opt->BlkSize) {
      (Private->Token->BufferSize) = Start + DataLen;
    }

  }

  return EFI_SUCCESS;

}

STATIC
EFTP_PACKET_BUFFER *
EftpRrqBuildAck (
  IN EFTP_IO_PRIVATE  *Private,
  IN UINT64           BlkNo
  )
/*++

Routine Description:

  Build an ACK packet for the BlkNo

Arguments:

  Private   : The instance's private data
  BlkNo     : The Block No of the last data packet

Returns:

  NULL      : Failed to allocate packet buffer for the ACK
  Point to packet Buffer : Packet buffer allocated and initalized

--*/
{
  EFTP_PACKET_BUFFER  *Buf;
  EFI_EFTP_PACKET     *Packet;
  EFI_STATUS          Status;
  UINT32              Len;

  ASSERT (Private);

  Len = EFTP_HEADER_LEN;
  Buf = EftpAllocPacket (Len);

  if (Buf == NULL) {
    EFTP_DEBUG_ERROR ((L"EftpRrqBuildAck:Failed to allocate packet buffer.\n"));

    Private->Result = EFI_OUT_OF_RESOURCES;
    return NULL;
  }

  Packet = Buf->Packet;

  Status = tBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  NET_TPL_EVENT,
                  (EFI_EVENT_NOTIFY) EftpRrqTxCallback,
                  Buf,
                  &Buf->EftpToken.MnpToken.Event
                  );

  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"EftpRrqBuildAck: failed to create event\n"));

    Private->Result = EFI_OUT_OF_RESOURCES;
    EftpReleasePacket (Buf);
    return NULL;
  }

  Packet->Hdr.OpCode    = HTONS (EFI_EFTP_OPCODE_ACK);
  Packet->Hdr.CodeVar   = 0;
  Packet->Hdr.Length    = HTONS ((UINT16) Len);
  Packet->Hdr.CheckSum  = 0;
  Packet->Hdr.CheckSum  = HTONS (EftpCkSum ((UINT16 *) Packet, Len / 2));
  Packet->Ack.Block     = HTONS ((UINT16) BlkNo);

  //
  // BUGBUG: Need Review
  //
  Buf->PacketSize = Len;
  Buf->EftpMnpTxData.DataLength = Len;
  Buf->EftpMnpTxData.FragmentCount = 1;
  Buf->EftpMnpTxData.FragmentTable[0].FragmentLength = Len;
  NetCopyMem (
    (CHAR8 *) Buf->EftpMnpTxData.FragmentTable[0].FragmentBuffer,
    Packet,
    Len
    );
  Buf->EftpMnpTxData.ProtocolType       = ENTS_FILE_TRANSER_PROTOCOL_MNP_TYPE;
  Buf->EftpMnpTxData.HeaderLength       = 0;
  Buf->EftpMnpTxData.DestinationAddress = NetAllocatePool (sizeof (EFI_MAC_ADDRESS));
  Buf->EftpMnpTxData.SourceAddress      = NetAllocatePool (sizeof (EFI_MAC_ADDRESS));
  NetCopyMem (
    Buf->EftpMnpTxData.DestinationAddress,
    &Private->ConfigData.DstMac,
    NET_ETHER_ADDR_LEN
    );
  NetCopyMem (
    Buf->EftpMnpTxData.SourceAddress,
    &Private->ConfigData.SrcMac,
    NET_ETHER_ADDR_LEN
    );

  Buf->EftpToken.Private = Private;

  return Buf;
}

STATIC
EFI_STATUS
EFIAPI
EftpRrqSendAck (
  IN EFTP_IO_PRIVATE  *Private,
  IN UINT64           BlkNo
  )
/*++

Routine Description:

  Send an ACK to the Data block of BlkNo

Arguments:

  Private   : The instance's private data
  BlkNo     : The last data packet's block NO

Returns:

  EFI_OUT_OF_RESOURCES  : Failed to allocate packet buffer for the ACK
  EFI_DEVICE_ERROR          : Failed to send out the ACK packet  
  EFI_SUCCESS                    : Successfully send the ACK packet
  
--*/
{
  EFTP_PACKET_BUFFER  *Buf;
  EFI_STATUS          Status;

  Buf = EftpRrqBuildAck (Private, BlkNo);

  if (Buf == NULL) {
    EFTP_DEBUG_ERROR ((L"EftpSendAck: failed to build ACK0\n"));

    Private->Result = EFI_OUT_OF_RESOURCES;
    return EFI_OUT_OF_RESOURCES;
  }

  Status = EftpSendPacket (Private, Buf);
  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"EftpSendAck: failed to send ACK0\n"));

    EftpReleasePacket (Buf);
    Private->Result = EFI_DEVICE_ERROR;
    return EFI_DEVICE_ERROR;
  }

  if (Private->LastCtrl) {
    EftpReleasePacket (Private->LastCtrl);

  }

  Private->LastCtrl = Buf;

  return EFI_SUCCESS;
}


STATIC
EFI_STATUS
EFIAPI
EftpRrqFlushLostBlock (
  IN EFTP_IO_PRIVATE  *Private
  )
/*++

Routine Description:

  flush the lost block list when not needed

Arguments:

  Private   : The instance's private data

Returns:

  EFI_SUCCESS  : Lost block list is flushed

--*/
{
  EFTP_LOSTBLOCK_ENTRY  *LostBlockEntry;

  ASSERT (EftpListIntegrityCheck (&Private->RrqState->LostPacketList));

  while (!LIST_IS_EMPTY (&Private->RrqState->LostPacketList)) {

    LostBlockEntry = LIST_HEAD (
                      &Private->RrqState->LostPacketList,
                      EFTP_LOSTBLOCK_ENTRY,
                      Entry
                      );

    LIST_REMOVE_ENTRY (&LostBlockEntry->Entry);
    NetFreePool (LostBlockEntry);
  }

  Private->RrqState->LostListSize = 0;

  return EFI_SUCCESS;
}

STATIC
BOOLEAN
EftpListIntegrityCheck (
  IN NET_LIST_ENTRY*ListHead
  )
/*++

Routine Description:

  Check the integrity of the linked list. For debug only

Arguments:

  ListHead    : The head of the list
  
Returns:

  TRUE   : The list is wel-formed
  FALSE : The list isn't wel-formed

--*/
{
  NET_LIST_ENTRY  *Entry;
  NET_LIST_ENTRY  *PreEntry;

  PreEntry = ListHead;
  LIST_FOR_EACH (Entry, ListHead) {
    if (Entry->BackLink != PreEntry) {
      return FALSE;
    }

    PreEntry = Entry;
  }

  return TRUE;

}
