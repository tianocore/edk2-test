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
        EftpWRQ.c
 
Abstract:
	Eftp WRQ process routines
--*/
#include "Efi.h"
#include "EftpMain.h"

VOID
EFIAPI
EftpWrqTxCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  );

STATIC
EFI_STATUS
EFIAPI
EftpWrqRcvAck (
  IN EFTP_IO_PRIVATE  *Private,
  IN EFI_EFTP_PACKET  *Packet,
  IN UINTN            PacketLen
  );

STATIC
EFI_STATUS
EFIAPI
EftpWrqRcvError (
  IN EFTP_IO_PRIVATE  *Private,
  IN EFI_EFTP_PACKET  *Packet,
  IN UINTN            PacketLen
  );

STATIC
EFI_STATUS
EFIAPI
EftpWrqRcvOack (
  IN EFTP_IO_PRIVATE   *Private,
  IN EFI_EFTP_PACKET   *Packet,
  IN UINT32            PacketLen
  );

STATIC
EFTP_PACKET_BUFFER  *
EftpWrqBuildData (
  IN EFTP_IO_PRIVATE  *Private,
  IN UINT64           BlkNo
  );

EFTP_WRQ_STATE *
EftpInitWrqState (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Init a Eftp instance for WRQ, or uploading

Arguments:

  Private - Eftp instance private data

Returns:

  NULL: Failed to allocate buffer for WRQ state
  Point to the newly allocated WRQ data structure: On success

--*/
{
  EFTP_WRQ_STATE  *Wrq;

  Wrq = NetAllocateZeroPool (sizeof (EFTP_WRQ_STATE));

  if (Wrq == NULL) {
    EFTP_DEBUG_ERROR ((L"EftpInitWrqState: failed to create WRQ data\n"));

    Private->Result = EFI_OUT_OF_RESOURCES;
    return NULL;
  }

  return Wrq;

}

EFI_STATUS
EFIAPI
EftpBuildWrq (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Build a WRQ packet from the user info, and save it at Private->Request

Arguments:

  Private - Eftp instance private data

Returns:

  EFI_OUT_OF_RESOURCES: Failed to allocate buffer for WRQ packet
  EFI_SUCCESS : WRQ packet allocated and initialized

--*/
{
  EFI_EFTP_TOKEN      *Token;
  EFTP_PACKET_BUFFER  *Buf;

  ASSERT (Private && Private->Token);

  Token = Private->Token;

  Buf = EftpBuildRequest (
          Private,
          EFI_EFTP_OPCODE_WRQ,
          Token->Filename,
          Token->ModeStr,
          Token->OptionCount,
          Token->OptionList,
          EftpWrqTxCallback
          );

  if (Buf == NULL) {
    EFTP_DEBUG_ERROR ((L"EftpBuildWrq: failed to build a request packet"));
    return EFI_OUT_OF_RESOURCES;
  }

  if (Private->Request) {
    EftpReleasePacket (Private->Request);

  }

  Private->Request = Buf;

  return EFI_SUCCESS;

}

VOID
EftpWrqRxCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Callback function by UDP when it receives packets for the instance.
  It will dispatch the packet to different routines for process.

Arguments:

  Event   : Event signalled by UDP
  Context : Event's context, it is a point to EFTP_COMPLETION_TOKEN

Returns:

  None

--*/
{
  EFTP_IO_PRIVATE                   *Private;
  EFI_EFTP_PACKET                   *Packet;
  EFTP_PACKET_BUFFER                *Buf;
  EFTP_COMPLETION_TOKEN             *Token;
  EFI_MANAGED_NETWORK_RECEIVE_DATA  *RxData;
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

  ASSERT (Private->Signature == EFTP_IO_PRIVATE_SIGNATURE);
  ASSERT (Private->State != EFTP_INIT);
  ASSERT (Token == &Private->UniToken);

  if (EFI_ERROR (Token->MnpToken.Status)) {
    EFTP_DEBUG_ERROR (
      (L"EftpWrqRxCallback: receive failed, token's status is %r\n",
      Token->MnpToken.Status)
      );

    //
    // BUGBUG: When MnpToken.Status is EFI_ICMP_ERROR, the udp port received a ICMP error packet
    // other than unreachable errors, for example TTL exceeded error. Just ignore it
    //
    if ((Token->MnpToken.Status == EFI_TIMEOUT) ||
        (Token->MnpToken.Status == EFI_ABORTED) ||
        (Token->MnpToken.Status == EFI_ICMP_ERROR)
        ) {

      Status = EFI_SUCCESS;
      goto CleanUp;

    } else {

      if (Private->State != EFTP_TIME_WAIT && Private->State != EFTP_WRQ_CLOSEING) {
        Private->Result = (Token->MnpToken.Status == EFI_DEVICE_ERROR ? EFI_DEVICE_ERROR : EFI_ICMP_ERROR);

      }

      Status = EFI_DEVICE_ERROR;

      WRQ_SILENT_SHUTDOWN (Private);
      goto CleanUp;

    }

  }

  RxData = Token->MnpToken.Packet.RxData;
  ASSERT (RxData);

  if ((RxData->DataLength < EFTP_HEADER_LEN) || (!RxData->PacketData)) {
    EFTP_DEBUG_ERROR (
      (L"EftpWrqRxCallback: Get a packet which is too short %d, ignore it\n",
      RxData->DataLength)
      );

    Status = EFI_SUCCESS;
    goto CleanUp;

  }

  Packet    = (EFI_EFTP_PACKET *) RxData->PacketData;
  PacketLen = NTOHS (Packet->Hdr.Length);
  OpCode    = NTOHS (Packet->Hdr.OpCode);

  //
  // BUGBUG: Need reivew.
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

  if ((OpCode == EFI_EFTP_OPCODE_OACK || OpCode == EFI_EFTP_OPCODE_ERROR) &&
      Private->Token &&
      Private->Token->CheckPacket
      ) {

    EFTP_DEBUG_VERBOSE (
      (L"EftpWrqRxCallback: call user's CheckPacket function %x for packet %d.\n",
      Private->Token->CheckPacket,
      OpCode)
      );

    Status = Private->Token->CheckPacket (&Private->Eftp, Private->Token, (UINT16) PacketLen, Packet);

    if (EFI_ERROR (Status)) {
      //
      // User cancel current TFTP process
      //
      EFTP_DEBUG_ERROR ((L"EftpWrqRxCallback: User canceled the process with %r returned.\n", Status));
      Private->Result = EFI_ABORTED;

      //
      // Do NOT send an error packet when received one. Error packet will end the process
      //
      if (OpCode == EFI_EFTP_OPCODE_ERROR) {
        EFTP_DEBUG_WARN ((L"EftpWrqRxCallback: User canceled the process when received an error packet\n"));

        WRQ_SILENT_SHUTDOWN (Private);
        goto CleanUp;

      }
      //
      // This situation will NOT happen, because once WRQ is in TIME_WAIT, it will
      // NOT restart receiveing. Just leave this as a safe guard
      //
      if (Private->State == EFTP_TIME_WAIT) {
        EFTP_DEBUG_WARN ((L"EftpWrqRxCallback: User canceled the process in TIME_WAIT state\n"));

        goto CleanUp;

      }

      Err.Code  = EFI_EFTP_ERRORCODE_NOT_DEFINED;
      Err.Desc  = "User caceled download";

      TmpStatus = EftpSendError (Private, &Err, EftpWrqTxCallback);

      if (EFI_ERROR (TmpStatus)) {
        EFTP_DEBUG_ERROR ((L"EftpWrqRxCallback: double error occured when deal with user cancellation\n"));

        WRQ_SILENT_SHUTDOWN (Private);
        goto CleanUp;
      }

      WRQ_LOUD_SHUTDOWN (Private);
      goto CleanUp;

    }
  }
  //
  // a WRQ client only expects to receive ACK/ACK8/ERROR/OACK packets
  //
  switch (OpCode) {
  case EFI_EFTP_OPCODE_ACK:
    if (PacketLen != (UINTN) (EFTP_HEADER_LEN)) {
      EFTP_DEBUG_VERBOSE ((L"EftpWrqRxCallback: Got a bad ACK, ignore it!\n"));
      Status = EFI_SUCCESS;
      break;
    }

    Status = EftpWrqRcvAck (Private, Packet, PacketLen);

    if (!EFI_ERROR (Status)) {
      Private->NRetry = 0;

    }

    EFTP_DEBUG_VERBOSE ((L"EftpWrqRxCallback: EftpWrqRcvAck returns \r.\n", Status));
    break;

  case EFI_EFTP_OPCODE_ERROR:
    if (PacketLen < (UINTN) (EFTP_HEADER_LEN + 1)) {
      EFTP_DEBUG_VERBOSE ((L"EftpWrqRxCallback: Got a bad Error, ignore it!\n"));
      Status = EFI_SUCCESS;
      break;
    }

    Status = EftpWrqRcvError (Private, Packet, PacketLen);

    EFTP_DEBUG_VERBOSE ((L"EftpWrqRxCallback: EftpWrqRcvError returns \r.\n", Status));
    break;

  case EFI_EFTP_OPCODE_OACK:
    if (PacketLen < (UINTN) (EFTP_HEADER_LEN)) {
      EFTP_DEBUG_VERBOSE ((L"EftpWrqRxCallback: Got a bad OACK, ignore it!\n"));
      Status = EFI_SUCCESS;
      break;
    }

    Status = EftpWrqRcvOack (Private, Packet, PacketLen);

    EFTP_DEBUG_VERBOSE ((L"EftpWrqRxCallback: EftpWrqRcvOack returns \r.\n", Status));
    break;

  default:
    EFTP_DEBUG_ERROR (
      (L"EftpWrqRxCallback: Get an unexpected packet, opcode=%d, ignore it.\n",
      OpCode)
      );

    Status = EFI_SUCCESS;
    break;

  }

CleanUp:
  if (Buf) {
    EftpReleasePacket (Buf);

  }

  if (RxData) {
    tBS->SignalEvent (RxData->RecycleEvent);
  }

  if (!EFI_ERROR (Status)) {
    Status = EftpStartRcv (Private);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpWrqRxCallback: failed to restart the receive, status is %r.\n", Status));

      WRQ_SILENT_SHUTDOWN (Private);
    }
  }

}

VOID
EFIAPI
EftpWrqTxCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Callback function called by UDP when it finishes to send packet.
  It will release the packet, and when instance finishes, it will also
  destory the instance

Arguments:

  Event  : Event signaled by UDP
  Context : The event's context. It's a point to EFTP_PACKET_BUFFER.

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

  case EFTP_WRQ_SENT:
  case EFTP_WRQ_ESTABLISHED:
  case EFTP_WRQ_CLOSEING:
    Private->NPendingPacket--;

    ASSERT (EntryInList (&Private->PendingPacketList, &Buf->List));
    LIST_REMOVE_ENTRY (&Buf->List);

    EftpReleasePacket (Buf);
    break;

  case EFTP_TIME_WAIT:
    Private->NPendingPacket--;

    ASSERT (EntryInList (&Private->PendingPacketList, &Buf->List));
    LIST_REMOVE_ENTRY (&Buf->List);

    EftpReleasePacket (Buf);

    if (Private->NPendingPacket == 0) {
      EftpWrqCleanUp (Private);

    }

    break;
  }

}

VOID
EftpWrqTimer (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Timer function when timeout happened during uploading.
  It will either retransmit the last packet, transit the state,
  or clean up the instance
  
Arguments:

  Event   : Timer event got signaled
  Context : The event's context. It is a point to EFTP_IO_PRIVATE

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
  ASSERT (Private->Signature == EFTP_IO_PRIVATE_SIGNATURE);

  //
  // Do NOT call user's TimeoutCallback at Closing and Timewait state. Those two states'
  // timer is to enable graceful shutdown.
  //
  if (Private->Token &&
      Private->Token->TimeoutCallback &&
      (Private->State != EFTP_WRQ_CLOSEING) &&
      (Private->State != EFTP_TIME_WAIT)
      ) {

    Status = Private->Token->TimeoutCallback (&(Private->Eftp), Private->Token);

    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpWrqTimer: User cancled the upload process\n"));

      Private->Result = EFI_ABORTED;
      goto SilentShutdown;
    }
  }

  switch (Private->State) {
  case EFTP_INIT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_WRQ_SENT:
    Private->NRetry++;

    if (Private->NRetry > Private->MaxNRetry) {
      EFTP_DEBUG_ERROR ((L"EftpWrqTimer: too many retries to send request\n"));

      //
      // do NOT send out an error packet since we are still in WRQ_SENT, server port is unknown
      //
      Private->Result = EFI_TIMEOUT;
      goto SilentShutdown;
    }

    Buf = Private->Request;
    ASSERT (Buf && (Buf->RefCnt >= 1));

    Copy    = (BOOLEAN) (Buf->RefCnt > 1);

    Status  = EftpResendPacket (Private, Buf, Copy, EftpWrqTxCallback);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpWrqTimer: failed to retransmit the request, init silent shutdown\n"));

      goto SilentShutdown;
    }

    EftpSetTimer (Private, Private->Timeout, 0);
    break;

  case EFTP_WRQ_ESTABLISHED:
    Private->NRetry++;

    if (Private->NRetry > Private->MaxNRetry) {
      EFTP_DEBUG_ERROR ((L"EftpWrqTimer: too many retries to send data\n"));

      Private->Result = EFI_TIMEOUT;
      Err.Code        = EFI_EFTP_ERRORCODE_NOT_DEFINED;
      Err.Desc        = "Too many timeouts";
      goto SendErr;
    }

    ASSERT (Private->WrqState && Private->WrqState->LastData);

    Buf = Private->WrqState->LastData;
    ASSERT (Buf->RefCnt >= 1);

    Copy    = (BOOLEAN) (Buf->RefCnt > 1);
    Status  = EftpResendPacket (Private, Buf, Copy, EftpWrqTxCallback);

    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpWrqTimer: failed to retransmit the data, init silent shutdown\n"));

      goto SilentShutdown;
    }

    EftpSetTimer (Private, Private->Timeout, 0);
    break;

  case EFTP_WRQ_CLOSEING:

    EFTP_DEBUG_VERBOSE ((L"EftpWrqTimer: timeout in closing state, init silent shutdown\n"));
    goto SilentShutdown;

    break;

  case EFTP_TIME_WAIT:

    EftpWrqCleanUp (Private);
    break;
  }

  return ;

SendErr:
  Status = EftpSendError (Private, &Err, EftpWrqTxCallback);

  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"EftpRrqInitRcvOack: failed to send an error packet (OACK malformed)\n"));
    goto SilentShutdown;
  }

  WRQ_LOUD_SHUTDOWN (Private);
  return ;

SilentShutdown:
  WRQ_SILENT_SHUTDOWN (Private);
  return ;

}

EFI_STATUS
EFIAPI
EftpWrqRcvAck (
  IN EFTP_IO_PRIVATE  *Private,
  IN EFI_EFTP_PACKET  *Packet,
  IN UINTN            PacketLen
  )
/*++

Routine Description:

  Function to process ACK packet when uploading. 
  It transmits another data block. It is called by
  EftpWrqRxCallback.
  

Arguments:

  Private : Eftp private instance data
  Packet  : Packet received.
  PacketLen : The length of the received packet

Returns:

  EFI_SUCCESS : Packet is OK, and the instance is willing to receive another packet
  EFI_ABORTED : The instance is about to finish, and don't start receive again
  EFI_DEVICE_ERROR : Failed to transmit packets. Don't start receive again 

--*/
{
  EFI_STATUS          Status;
  EFTP_OPTION         *Opt;
  UINT64              AckNo;
  EFTP_ERRINFO        Err;
  EFTP_PACKET_BUFFER  *Buf;
  BOOLEAN             Copy;

  ASSERT (Private && Private->WrqState && Packet);

  Opt = &Private->Option;

  //
  // Ignore the ACK packet with wrong opcode
  //
  if (Packet->Hdr.OpCode != HTONS (EFI_EFTP_OPCODE_ACK)) {
    return EFI_SUCCESS;
  }

  AckNo = NTOHS (Packet->Ack.Block);

  switch (Private->State) {
  case EFTP_INIT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_WRQ_SENT:
    //
    // ignore all the ack packet other than ACK0
    //
    if (AckNo != Private->NextBlkNo - 1) {
      return EFI_SUCCESS;

    }

    Private->State = EFTP_WRQ_ESTABLISHED;

  //
  // Fall through to send a data packet
  //
  case EFTP_WRQ_ESTABLISHED:
    if (AckNo != Private->NextBlkNo - 1) {
      return EFI_SUCCESS;

    }
    //
    // received the ACK to last packet, happily start the silent shutdown procedure
    //
    if (Private->Eof) {
      EFTP_DEBUG_VERBOSE ((L"EftpWrqRcvAck: successfully uploaded, Cong\n"));

      Private->Result = EFI_SUCCESS;
      WRQ_SILENT_SHUTDOWN (Private);

      //
      // Return an error to make EftpWrqRxCallback NOT to start receive again
      //
      return EFI_ABORTED;
    }

    Buf = EftpWrqBuildData (Private, Private->NextBlkNo);
    if (Buf == NULL) {
      if (Private->Result == EFI_ABORTED) {

        EFTP_DEBUG_ERROR ((L"EftpWrqRcvAck: User canceled the download"));

        Err.Code  = EFI_EFTP_ERRORCODE_NOT_DEFINED;
        Err.Desc  = "User aborted the download";

        Status    = EftpSendError (Private, &Err, EftpWrqTxCallback);

        if (EFI_ERROR (Status)) {
          EFTP_DEBUG_ERROR ((L"EftpWrqRcvAck: failed to send an error packet to cancel the download\n"));

          WRQ_SILENT_SHUTDOWN (Private);
          return EFI_DEVICE_ERROR;

        }
        //
        // return EFI_SUCCESS to restart receiving
        //
        WRQ_LOUD_SHUTDOWN (Private);
        return EFI_SUCCESS;

      }

      EFTP_DEBUG_ERROR ((L"EftpWrqRcvAck: failed to retrieve data, EftpWrqBuildData returns%r\n", Private->Result));

      WRQ_SILENT_SHUTDOWN (Private);
      return EFI_ABORTED;

    }

    Status = EftpSendPacket (Private, Buf);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpWrqRcvAck: failed to send data block, EftpSendPacket returns%r\n", Status));

      EftpReleasePacket (Buf);
      WRQ_SILENT_SHUTDOWN (Private);
      return EFI_ABORTED;

    }

    if (Private->WrqState->LastData) {
      EftpReleasePacket (Private->WrqState->LastData);

    }

    Private->WrqState->LastData = Buf;

    Private->NextBlkNo++;

    EftpSetTimer (Private, Private->Timeout, 0);
    return EFI_SUCCESS;

    break;

  case EFTP_WRQ_CLOSEING:
    Buf = (Private->LastCtrl ? Private->LastCtrl : Private->WrqState->LastData);

    Buf = Private->LastCtrl;
    ASSERT (Buf && (Buf->RefCnt >= 1));

    Copy    = (BOOLEAN) (Buf->RefCnt > 1);

    Status  = EftpResendPacket (Private, Buf, Copy, EftpWrqTxCallback);
    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpWrqRcvAck: failed to retransmit the packet, init silent shutdown\n"));

      WRQ_SILENT_SHUTDOWN (Private);
      return EFI_DEVICE_ERROR;

    }
    //
    // Don't restart timer here, we will transit to TIMEWAIT once timeout
    //
    return EFI_SUCCESS;
    break;

  case EFTP_TIME_WAIT:
    //
    // Return an error to make EftpWrqRxCallback NOT to start receive again
    //
    return EFI_ABORTED;
    break;
  }

  return EFI_ABORTED;

}

EFI_STATUS
EFIAPI
EftpWrqRcvError (
  IN EFTP_IO_PRIVATE  *Private,
  IN EFI_EFTP_PACKET  *Packet,
  IN UINTN            PacketLen
  )
/*++

Routine Description:

  Function to process Error packet when uploading. 
  It is called by EftpWrqRxCallback.
  

Arguments:

  Private : Eftp private instance data
  Packet  : Packet received.
  PacketLen : The length of the received packet

Returns:

  EFI_SUCCESS : The instance is willing to receive another packet
  EFI_ABORTED : The instance is about to finish, and don't start receive again

--*/
{

  ASSERT (Private && Packet);

  switch (Private->State) {
  case EFTP_INIT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_WRQ_SENT:
  case EFTP_WRQ_ESTABLISHED:
  case EFTP_WRQ_CLOSEING:
    EFTP_DEBUG_WARN (
      (L"EftpWrqRcvError: received an error packet (%d) from server\n",
      Packet->Error.ErrorCode)
      );

    Private->Result = EFI_TFTP_ERROR;
    WRQ_SILENT_SHUTDOWN (Private);
    return EFI_SUCCESS;
    break;

  case EFTP_TIME_WAIT:
    //
    // Return an error to make EftpWrqRxCallback NOT to start receive again
    //
    return EFI_ABORTED;
    break;
  }

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
EftpWrqRcvOack (
  IN EFTP_IO_PRIVATE   *Private,
  IN EFI_EFTP_PACKET   *Packet,
  IN UINT32            PacketLen
  )
/*++

Routine Description:

  Function to process OACK packet. It parses the OACK
  or discards it.It is called by EftpWrqRxCallback.
  
Arguments:

  Private : Eftp private instance data
  Packet  : Packet received.
  PacketLen : The length of the received packet

Returns:

  EFI_SUCCESS : Packet is OK, and the instance is willing to receive another packet
  EFI_ABORTED : The instance is about to finish, and don't start receive again
  EFI_DEVICE_ERROR : Failed to transmit packets. Don't start receive again 

--*/
{
  EFI_STATUS      Status;
  EFI_EFTP_PACKET FakeAck;
  EFTP_ERRINFO    Err;

  ASSERT (Private && Packet);

  switch (Private->State) {
  case EFTP_INIT:
    ASSERT (EFTP_PROGRAM_ERROR);
    break;

  case EFTP_WRQ_SENT:
    Status = EftpExtractOptions (&Private->Eftp, &Private->Option, Packet, PacketLen);

    if (EFI_ERROR (Status)) {

      EFTP_DEBUG_ERROR ((L"EftpWrqRcvOack: failed to parse the OACK packet\n"));

      Err.Code  = EFI_EFTP_ERRORCODE_ILLEGAL_OPERATION;
      Err.Desc  = "Mal-formed OACK packet";

      Status    = EftpSendError (Private, &Err, EftpWrqTxCallback);

      if (EFI_ERROR (Status)) {
        EFTP_DEBUG_ERROR ((L"EftpWrqRcvOack: failed to send an error packet (OACK malformed)\n"));

        WRQ_SILENT_SHUTDOWN (Private);
        return EFI_DEVICE_ERROR;

      }

      Private->Result = EFI_DEVICE_ERROR;
      WRQ_LOUD_SHUTDOWN (Private);

      //
      // return EFI_SUCCESS to restart receiving
      //
      return EFI_SUCCESS;

    }

    Private->Timeout  = Private->Option.Timeout;
    Private->State    = EFTP_WRQ_ESTABLISHED;

    //
    // Build a fake ACK0 packet to use simplify the receive
    //
    FakeAck.Ack.OpCode  = HTONS (EFI_EFTP_OPCODE_ACK);
    FakeAck.Ack.Block   = 0;

    return EftpWrqRcvAck (Private, &FakeAck, EFTP_HEADER_LEN);
    break;

  case EFTP_WRQ_ESTABLISHED:
  case EFTP_WRQ_CLOSEING:
    EFTP_DEBUG_VERBOSE ((L"EftpWrqRcvOack: ignore the OACK in state %d\n", Private->State));

    return EFI_SUCCESS;
    break;

  case EFTP_TIME_WAIT:
    //
    // Return an error packet to stop sending
    //
    return EFI_ABORTED;
    break;
  }

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
EftpWrqReadBlk (
  IN EFTP_IO_PRIVATE     *Private,
  IN EFTP_PACKET_BUFFER  *Buf,
  IN UINT64              BlkNo
  )
/*++

Routine Description:

  Read a block from user provided buffer or call the user's function to fill it.

Arguments:

  Private  : Eftp private instance data
  Buf       : Packet to fill data in
  BlkNo    : The block number of the packet to fill.

Returns:

  EFI_ABORTED : User canceled the upload, or the data provided is longer than expected
  EFI_SUCCESS : Data filled successfully

--*/
{
  UINT64          Start;
  UINT64          End;
  EFTP_OPTION     *Opt;
  EFI_EFTP_PACKET *Pkt;
  EFI_STATUS      Status;
  UINT16          DataLen;
  UINT8           *DataBuf;

  ASSERT ((Private != NULL) && (Buf != NULL) && (Buf->Packet != NULL));
  ASSERT (Private->Token && (Private->Token->Buffer || Private->Token->PacketNeeded));

  Opt = &Private->Option;
  Pkt = Buf->Packet;

  if (Private->Token->Buffer != NULL) {
    End   = SctMultU64x32 (BlkNo, Opt->BlkSize);
    Start = End - Opt->BlkSize;

    if (End > Private->Token->BufferSize) {
      Buf->PacketSize     = (UINT32) (Private->Token->BufferSize - Start + EFTP_HEADER_LEN);

      Private->LastBlkNo  = BlkNo;
      Private->Eof        = TRUE;
      EFTP_DEBUG_VERBOSE ((L"EftpWrqReadBlk: End of the Eftp write\n"));

    } else {
      Buf->PacketSize = Opt->BlkSize + EFTP_HEADER_LEN;

    }

    NetCopyMem (
      (UINT8 *) Pkt + EFTP_HEADER_LEN,
      (UINT8 *) Private->Token->Buffer + Start,
      Buf->PacketSize - EFTP_HEADER_LEN
      );

  } else {

    DataBuf = NULL;
    DataLen = Opt->BlkSize;

    EFTP_DEBUG_VERBOSE ((L"EftpWrqReadBlk: call PacketNeeded to fill in data\n"));

    Status = Private->Token->PacketNeeded (&Private->Eftp, Private->Token, &DataLen, (VOID **) &DataBuf);

    if (EFI_ERROR (Status)) {
      EFTP_DEBUG_ERROR ((L"EftpWrqReadBlk: PacketNeeded returns %r .\n", Status));

      Private->Result = EFI_ABORTED;
      return EFI_ABORTED;

    }

    if (DataLen > Opt->BlkSize) {

      EFTP_DEBUG_ERROR ((L"EftpWrqReadBlk: PacketNeeded returns a block of %d, sick\n", DataLen));

      tBS->FreePool (DataBuf);
      Private->Result = EFI_ABORTED;
      return EFI_ABORTED;

    } else if (DataLen < Opt->BlkSize) {
      Private->Eof        = TRUE;
      Private->LastBlkNo  = BlkNo;
      EFTP_DEBUG_VERBOSE ((L"EftpWrqReadBlk: End of the Eftp write\n"));
    }

    Buf->PacketSize = DataLen + EFTP_HEADER_LEN;
    NetCopyMem ((UINT8 *) Pkt + EFTP_HEADER_LEN, DataBuf, DataLen);

    tBS->FreePool (DataBuf);
  }

  Pkt->Hdr.OpCode   = HTONS (EFI_EFTP_OPCODE_DATA);
  Pkt->Hdr.Length   = HTONS ((UINT16) Buf->PacketSize);
  Pkt->Hdr.CodeVar  = HTONS ((UINT16) BlkNo);
  Pkt->Hdr.CheckSum = 0;
  Pkt->Hdr.CheckSum = HTONS (EftpCkSum ((UINT16 *) Pkt, (UINT32) Buf->PacketSize / 2));

  //
  // BUGBUG
  //
  Buf->EftpMnpTxData.DataLength                       = Buf->PacketSize;
  Buf->EftpMnpTxData.FragmentCount                    = 1;
  Buf->EftpMnpTxData.FragmentTable[0].FragmentLength  = Buf->PacketSize;
  NetCopyMem (
    (CHAR8 *) Buf->EftpMnpTxData.FragmentTable[0].FragmentBuffer,
    Buf->Packet,
    Buf->PacketSize
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

  return EFI_SUCCESS;

}

STATIC
EFTP_PACKET_BUFFER *
EftpWrqBuildData (
  IN EFTP_IO_PRIVATE  *Private,
  IN UINT64           BlkNo
  )
/*++

Routine Description:

  The function builds a data packet to transmit

Arguments:

  Private : Eftp instance private data
  BlkNo   : Block number of the data to fill

Returns:

  NULL: Failed to build the data packet
  Point to data packet: Packet allocated and initialized successfully

--*/
{
  EFTP_PACKET_BUFFER  *Buf;
  EFI_STATUS          Status;
  UINT32              Len;

  ASSERT (Private && Private->WrqState);

  Len = EFTP_HEADER_LEN + Private->Option.BlkSize;
  Buf = EftpAllocPacket (Len);

  if (Buf == NULL) {
    EFTP_DEBUG_ERROR ((L"EftpWrqBuildData: Failed to allocate packet buffer.\n"));

    Private->Result = EFI_OUT_OF_RESOURCES;
    return NULL;

  }

  Status = EftpWrqReadBlk (Private, Buf, BlkNo);

  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"EftpWrqBuildData: Failed to allocate packet buffer.\n"));

    EftpReleasePacket (Buf);
    return NULL;

  }

  Status = tBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  NET_TPL_EVENT,
                  (EFI_EVENT_NOTIFY) EftpWrqTxCallback,
                  Buf,
                  &Buf->EftpToken.MnpToken.Event
                  );

  if (EFI_ERROR (Status)) {
    EFTP_DEBUG_ERROR ((L"EftpWrqBuildData: Failed to create event.\n"));

    Private->Result = EFI_OUT_OF_RESOURCES;
    EftpReleasePacket (Buf);
    return NULL;

  }

  return Buf;

}

VOID
EftpWrqCleanUp (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Gracefully shutdown the Eftp instance: release various resources
  and signal the user event

Arguments:

  Private : Eftp instance private data

Returns:

  None

--*/
{
  ASSERT (Private && Private->WrqState);

  if (Private->Request) {
    EftpReleasePacket (Private->Request);
    Private->Request = NULL;
  }

  if (Private->LastCtrl) {
    EftpReleasePacket (Private->LastCtrl);
    Private->LastCtrl = NULL;
  }

  if (Private->WrqState->LastData) {
    EftpReleasePacket (Private->WrqState->LastData);
    Private->WrqState->LastData = NULL;
  }

  NetFreePool (Private->WrqState);
  Private->WrqState = NULL;

  EFTP_DEBUG_VERBOSE (
    (L"EftpWrqCleanUp: number of pending packet is %d\n",
    Private->NPendingPacket)
    );

  tBS->CloseEvent (Private->TimeoutEvent);
  Private->TimeoutEvent   = NULL;

  Private->Token->Status  = Private->Result;

  ASSERT (!Private->UserEvtFired && !Private->SynFinished);

  if (Private->Token->Event) {
    tBS->SignalEvent (Private->Token->Event);
    Private->UserEvtFired = TRUE;
  }

  Private->SynFinished  = TRUE;

  Private->State        = EFTP_INIT;
}
