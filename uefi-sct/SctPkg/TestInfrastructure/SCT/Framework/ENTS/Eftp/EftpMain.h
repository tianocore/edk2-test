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
 
  EftpMain.h
 
Abstract:

  Eftp Implementation
 
--*/

#ifndef _EFI_EFTP_MAIN_H_
#define _EFI_EFTP_MAIN_H_

#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (Eftp)

#include EFI_PROTOCOL_DEFINITION (ManagedNetwork)

#define _EFTP_STAT_ 1

typedef struct _EFTP_IO_PRIVATE EFTP_IO_PRIVATE;

#include "EftpCommon.h"
#include "EftpPacket.h"
#include "EftpOption.h"
#include "EftpRRQ.h"
#include "EftpWRQ.h"

#define EFTP_IO_PRIVATE_SIGNATURE     EFI_SIGNATURE_32 ('M', 'T', 'F', 'T')
#define EFTP_IO_PRIVATE_FROM_THIS(a)  CR ((a), EFTP_IO_PRIVATE, Eftp, EFTP_IO_PRIVATE_SIGNATURE)

#define NET_RAISE_TPL(x)          (tBS->RaiseTPL (x))
#define NET_RESTORE_TPL(x)        (tBS->RestoreTPL (x))

extern UINT32                       mEftpDebugLevel;
extern EFI_DRIVER_BINDING_PROTOCOL  gEftpDriverBinding;
extern CHAR8                        *mSupportedOptions[EFTP_SUPPORTED_OPTIONS_COUNT];
extern CHAR8                        *mUnsupportedOptions[EFTP_UNSUPPORTED_OPTIONS_COUNT];

struct _EFTP_IO_PRIVATE {
  UINTN                         Signature;
  NET_LIST_ENTRY                List;
  EFI_EFTP_PROTOCOL             Eftp;

  //
  // Boolean Flag used to mark if this instance is destroyed
  //
  BOOLEAN                       Destroyed;

  //
  // Vars to handle protocols
  //
  EFI_HANDLE                    ParentController;
  EFI_HANDLE                    Handle;
  EFI_HANDLE                    MulticastChildHandle;

  //
  // User configured data for the session
  //
  EFI_EFTP_TOKEN                *Token;
  EFI_EFTP_CONFIG_DATA          ConfigData;
  BOOLEAN                       Configured;
  BOOLEAN                       UserEvtFired; // Used for debug. The user event should be fired twice in the design
  BOOLEAN                       SynFinished;

  UINTN                         MaxNRetry;
  EFI_IPv4_ADDRESS              GateWay;

  EFTP_OPTION                   Option;

  //
  // Vars common to RRQ and WRQ
  //
  EFTP_STATE                    State;
  EFI_STATUS                    Result; // return status to the client in asynchronous transfer mode
  EFTP_PEER_ADDR                Server; // Server port to send data or ack, not the initial port
  //
  // Initial Server port used to send control words
  //
  EFTP_PEER_ADDR                InitialServer;
  EFI_MANAGED_NETWORK_PROTOCOL  *ManagedNetwork;
  EFTP_COMPLETION_TOKEN         UniToken;       // Tokens to receive data. There is at most one receive pending
  UINTN                         NRetry;

  EFTP_PACKET_BUFFER            *Request;       // Saved request packet in cast that we need to retransmit it
  EFTP_PACKET_BUFFER            *LastCtrl;      // Last control packet sent
  UINT64                        NextBlkNo;      // We are expecting this blkno
  BOOLEAN                       Eof;            // received or transmitted the last block
  UINT64                        LastBlkNo;      // LastBlkNo, used by smart client
  UINTN                         NPendingPacket; // The number of sent-not-recycled packets
  NET_LIST_ENTRY                PendingPacketList;

  EFI_EVENT                     TimeoutEvent;
  UINT16                        Timeout;        // Timeout time, this time is initialized according to Timeou, and TransferType option
  EFTP_RRQ_STATE                *RrqState;
  EFTP_WRQ_STATE                *WrqState;

#ifdef _EFTP_STAT_

  UINT64                        RcvdPkts;

  UINT64                        DroppedPkts;

  UINT64                        Timeouts;

#endif

};

//
// API Prototype declare
//
EFI_STATUS
EFIAPI
EftpReadFile (
  IN EFI_EFTP_PROTOCOL  *This,
  IN EFI_EFTP_TOKEN     *Token
  )
/*++

Routine Description:

  EftpReadFile interface routine

Arguments:

  This    - Eftp Protocol
  Token   - User-provided token to specify the session's action

Returns:

  EFI_INVALID_PARAMETER   - Invalid parameter provided.
  EFI_NOT_STARTED         - Session isn't configured
  EFI_ACCESS_DENIED       - Session is busy
  EFI_DEVICE_ERROR        - Failed to config the underlying network stack

--*/
;

EFI_STATUS
EFIAPI
EftpWriteFile (
  IN EFI_EFTP_PROTOCOL          *This,
  IN EFI_EFTP_TOKEN             *Token
  )
/*++

Routine Description:

  EftpWriteFile interface routine

Arguments:

  This    - Eftp Protocol
  Token   - User-provided token to specify the session's action

Returns:

  EFI_INVALID_PARAMETER   - Invalid parameter provided.
  EFI_NOT_STARTED         - Session isn't configured
  EFI_ACCESS_DENIED       - Session is busy
  EFI_DEVICE_ERROR        - Failed to config the underlying network stack

--*/
;

EFI_STATUS
EFIAPI
EftpReadDirectory (
  IN EFI_EFTP_PROTOCOL  *This,
  IN EFI_EFTP_TOKEN     *Token
  )
/*++

Routine Description:

  EftpReadDirectory interface routine

Arguments:

  This    - Eftp Protocol
  Token   - User-provided token to specify the session's action

Returns:

  EFI_UNSUPPORTED  - This feature is not supported.

--*/
;

EFI_STATUS
EFIAPI
EftpConfigure (
  IN EFI_EFTP_PROTOCOL      * This,
  IN EFI_EFTP_CONFIG_DATA   * EftpConfigData OPTIONAL
  )
/*++

Routine Description:

  Config the eftp session. A eftp session must be configed first to read 
  or write file. If no EftpConfigData is provided, the session is cleaned up.

Arguments:

  This           - The Eftp protocol to configure
  EftpConfigData - Eftp configuration data

Returns:

  EFI_INVALID_PARAMETER  - Invalid parameters provided.
  EFI_ACCESS_DENIED      - The eftp session is busy.
  EFI_SUCCESS            - Successfully configured the session.

--*/
;

EFI_STATUS
EFIAPI
EftpGetInfo (
  IN EFI_EFTP_PROTOCOL        * This,
  IN EFI_EFTP_OVERRIDE_DATA   * OverrideData,
  IN CHAR8                    *Filename,
  IN CHAR8                    *ModeStr,
  IN UINT8                    OptionCount,
  IN EFI_EFTP_OPTION          * OptionList,
  OUT UINT32                  *PacketLength,
  OUT EFI_EFTP_PACKET         **Packet OPTIONAL
  )
/*++

Routine Description:

  EftpGetInfo interface routine. GetInfo is impletemented with EftpReadFile.
  It provides the ReadFile with a callback, that is EftpGetInfoCheckPacket, which will 
  terminate the EftpReadFile after enough information is retrieved.

Arguments:

  This           - Eftp protocol
  OverrideData   - Data used to override UDP configuration
  Filename       - File to retrieve
  ModeStr        - Operation mode
  OptionCount    - The number of options in the option list
  OptionList     - The name/value pairs of the options
  PacketLength   - The length of the packet buffer
  Packet         - Packet buffer to return information

Returns:

  EFI_UNSUPPORTED  - This feature is not supported.

--*/
;

EFI_STATUS
EFIAPI
EftpGetModeData (
  IN EFI_EFTP_PROTOCOL      *This,
  OUT EFI_EFTP_MODE_DATA    *ModeData
  )
/*++

Routine Description:

  Get the session's configuration data.

Arguments:

  This       - The eftp protocol
  ModeData   - Data structure to save configuration information

Returns:

  EFI_INVALID_PARAMETER   - Invalid parameters provided.
  EFI_NO_MAPPING          - Session not configured
  EFI_SUCCESS             - Information retrieved

--*/
;

EFI_STATUS
EFIAPI
EftpParseOptions (
  IN EFI_EFTP_PROTOCOL     * This,
  IN UINT32                PacketLen,
  IN EFI_EFTP_PACKET       * Packet,
  IN OUT UINT32            *OptionCount,
  OUT EFI_EFTP_OPTION      **OptionList OPTIONAL
  )
/*++

Routine Description:

  Interface function to parse a packet for options.

Arguments:

  This          - The eftp protocol
  PacketLen     - The length of the packet
  Packet        - The packet
  OptionCount   - Point to variable to save option count
  OptionList    - Variable to store the allocated option list

Returns:

  EFI_INVALID_PARAMETER - Invalid parameters provided.
  EFI_PROTOCOL_ERROR    - Mal-form packet provided
  EFI_SUCCESS           - Options are successfully parsed
  Others                - Failed to allocate memory for the buffer.

--*/
;

EFI_STATUS
EFIAPI
EftpPoll (
  IN EFI_EFTP_PROTOCOL *This
  )
/*++

Routine Description:

  Interface function to poll the network stack

Arguments:

  This   - The eftp protocol

Returns:

  EFI_INVALID_PARAMETER   - Invalid parameters provided. 
  EFI_NOT_STARTED         - The session isn't configured

--*/
;

EFI_STATUS
EFIAPI
EftpSetTimer (
  IN EFTP_IO_PRIVATE   *Private,
  UINTN                Sec,
  UINTN                MSec
  )
/*++

Routine Description:

  Set the session's timer. It first cancels the old setting, then set it again with 
  new timeout value.

Arguments:

  Private  - The eftp session's private data
  Sec      - The "second" of timeout
  MSec     - The milliseconf of timeout

Returns:

  EFI_SUCCESS - Timer is successfully set

--*/
;

#endif
