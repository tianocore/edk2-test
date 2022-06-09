/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
 
  EftpPacket.h
 
Abstract:
  Eftp Packet buffer for send
 
--*/

#ifndef _EFI_EFTP_PACKET_H_
#define _EFI_EFTP_PACKET_H_

#define EFTP_TOKEN_SIGNATURE          EFI_SIGNATURE_32 ('M', 'T', 'T', 'O')
#define EFTP_TOKEN_RECYCLE_SIGNATURE  EFI_SIGNATURE_32 ('M', 'T', 'T', 'R')

//
// In order to improve the performance of packet buffer, two pool of buffers are defined,
// One pool contains all the buffer with DataSize < EFTP_BUFFER_DIV.
// The other pool contains all the buffer bigger than that.
//
#define EFTP_BUFFER_DIV               (2 * 1024)
#define EFTP_MAX_BUFFER_SIZE          (2 * 1024 * 1024)
#define EFTP_MINI_PACKET_BUFFER_SIZE  256

//
// Structure for a packet buffer
//
typedef struct _EFTP_PACKET_BUFFER {
  EFTP_COMPLETION_TOKEN             EftpToken;
  EFI_MANAGED_NETWORK_TRANSMIT_DATA EftpMnpTxData;
  EFI_EFTP_PACKET                   *Packet;
  UINT32                            DataSize; // Udp tx data buffer size
  UINT32                            PacketSize;
  UINT32                            RefCnt;
  NET_LIST_ENTRY                    List;
} EFTP_PACKET_BUFFER;

EFTP_PACKET_BUFFER  *
EftpAllocPacket (
  IN UINT32 DataSize
  )
/*++

Routine Description:

  Allocate a packet buffer from the pool first. If not available, from the system memory.

Arguments:

  DataSize - The size of the buffer to hold packet, not including the structure size

Returns:

  NULL                       - Failed to allocate the data
  Point to new packet buffer - Successfully allocated and initialized the buffer

--*/
;

EFI_STATUS
EFIAPI
EftpSendPacket (
  EFTP_IO_PRIVATE    *Private,
  EFTP_PACKET_BUFFER *Buf
  )
/*++

Routine Description:

  Send out a packet to the session's UDP port.
  Since Eftp client doesn't send packet to multicast address,
  the UDP port isn't a explict parameter.

Arguments:

  Private  - The eftp session's private data
  Buf      - Packet to send
  
Returns:

  EFI_SUCCESS - Packet is successfully sent.
  Others      - Failed to send the packet.

--*/
;

BOOLEAN
EntryInList (
  IN NET_LIST_ENTRY*Head,
  IN NET_LIST_ENTRY*Entry
  )
/*++

Routine Description:

  Check whether the Entry is in the list of Head.

Arguments:

  Head   - The list's head to be checked against.
  Entry  - The entry.

Returns:

  TRUE   - Entry is in the list
  FALSE  - Entry not in the list

--*/
;

VOID
EftpInitPacketBuffer (
  VOID
  )
/*++

Routine Description:

  Initialize the packet buffer pool

Arguments:

  None

Returns:

  None

--*/
;

VOID
EftpClosePacketBuffer (
  VOID
  )
/*++

Routine Description:

  Release packet buffer pools and all the associated packet buffers

Arguments:

  None

Returns:

  None

--*/
;

VOID
EftpReleasePacket (
  IN EFTP_PACKET_BUFFER*Buf
  )
/*++

Routine Description:

  Release the packet to the eftp buffer, if the buffer occupies too 
  much resource, release it to the system memory

Arguments:

  Buf  - Point to the packet buffer

Returns:

  None

--*/
;

VOID
EftpHoldPacket (
  IN EFTP_PACKET_BUFFER*Buf
  )
/*++

Routine Description:

  Increase the packet buffer's reference count

Arguments:

  Buf  - Point to the packet buffer
  
Returns:

  None

--*/
;

EFTP_PACKET_BUFFER  *
EftpBuildErrorPacket (
  IN EFTP_IO_PRIVATE  *Private,
  IN EFTP_ERRINFO     *Err,
  IN EFI_EVENT_NOTIFY Func
  )
/*++

Routine Description:

  Build an error packet.

Arguments:

  Private   - Eftp session's private data
  Err       - The error information to add to the packet.
  Func      - Event function to call when recycled.

Returns:

  NULL                - Failed to allocate the packet.
  Point to new packet - Successfully allocated a new packet buffer and initialized it.
  
--*/
;

EFTP_PACKET_BUFFER  *
EftpBuildRequest (
  IN EFTP_IO_PRIVATE              *Private,
  IN UINT16                       OpCode,
  IN CHAR8                        *Filename,
  IN CHAR8                        *Mode,
  IN UINT32                       NOption,
  IN EFI_EFTP_OPTION              *OptionList,
  IN EFI_EVENT_NOTIFY             Func
  )
/*++

Routine Description:

  Build a request packet, be it a RRQ/WRQ.

Arguments:

  Private    - Eftp session's private data
  OpCode     - OpCode to use, for example : RRQ/WRQ/READ_DIRECTORY
  Filename   - File name to read or write
  Mode       - Transfer mode, default to octet
  NOption    - The Number of options in the option list
  OptionList - Option list, it is a group of name/value pairs
  Func       - Event function to call when recycled

Returns:

  NULL                - Failed to allocate new packet buffer for the request packet.
  Point to new packet - Successfully allocated and initialized the packet.

--*/
;

EFI_STATUS
EFIAPI
EftpStartRcv (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Start receiving packet on the session's unicast port.

Arguments:

  Private  - Eftp session's private data

Returns:

  EFI_SUCCESS - Successfully started receiving on the udp port
  Others      - Failed to start receiving on the UDP port.
  
--*/
;

EFI_STATUS
EFIAPI
EftpSendError (
  IN EFTP_IO_PRIVATE  *Private,
  IN EFTP_ERRINFO     *Err,
  IN EFI_EVENT_NOTIFY Func
  )
/*++

Routine Description:

  Build an error packet, then send it

Arguments:

  Private    - The Eftp session's private data
  Err        - Error information to be included in the packet
  Func       - Event function to call when recycled.

Returns:

  EFI_OUT_OF_RESOURCES - Failed to allocate memory for new packet.
  EFI_SUCCESS          - Successfully built and sent the packet 
  Others               - Failed to send the packet
  
--*/
;

EFI_STATUS
EFIAPI
EftpResendPacket (
  IN EFTP_IO_PRIVATE     *Private,
  IN EFTP_PACKET_BUFFER  *Buf,
  IN BOOLEAN             Copy,
  IN EFI_EVENT_NOTIFY    Func
  )
/*++

Routine Description:

  Retransmit the packet, if necessary copy it.

Arguments:

  Private   - The Eftp session's private data
  Buf       - The packet to transmit.
  Copy      - Whether it is necessary to copy it.
  Func      - Event function to call when recycled.

Returns:

  EFI_SUCCESS             - Packet is successfully retransmitted.
  EFI_OUT_OF_RESOURCES    - Failed to allocate memory to copy the packet
  Others                  - Failed to build or send the packet.
  
--*/
;

UINT16
EftpCkSum (
  UINT16 *buf,
  UINT32 nwords
  )
/*++

Routine Description:

  Caculate checksum for Eftp packet.

Arguments:

  buf    - Buffer to be caculated.
  nwords - Length of the buffer in 2 octets.

Returns:

  Checksum result.

--*/
;

#endif
