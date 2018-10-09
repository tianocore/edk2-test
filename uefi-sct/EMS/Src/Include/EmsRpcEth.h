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
  
    EmsRpcEth.h
    
Abstract:

    Incude header files for RPC functions

--*/

#ifndef __EMS_ETH_H__
#define __EMS_ETH_H__

#include <tcl.h>
#include <EmsTypes.h>
#include <EmsNet.h>

#pragma pack(1)
typedef union {
  struct {
    UINT32  SeqId : 32;
    UINT32  Offset : 16;
    UINT32  OpCode : 8;
    UINT32  Rsvd : 7;
    UINT32  Mf : 1;
  } Flag;
  UINT64  llFlag;
} EAS_RIVL_LL_FLAG;
#pragma pack()

#define LINK_OPERATION_PROBE			0x01
#define LINK_OPERATION_PROBE_ACK		0x02
#define LINK_OPERATION_CLEANUP			0x21
#define LINK_OPERATION_CLEANUP_ACK	0x22
#define LINK_OPERATION_DATA			0x11
#define LINK_OPERATION_DATA_ACK		0x12

#define RIVL_LISTENING            1
#define RIVL_SENDING              2

#define LL_POS                    14
#define DATA_POS                  22

#define ETHER_HEAD_LENGTH         14
#define LLC_HEAD_LENGTH           sizeof (EAS_RIVL_LL_FLAG)

#define EMS_PROTO_ID              0x1234
//
// #define MTYPE_LEN			      4
//
#define REXMIT_INTERVAL 2

#ifndef MAX_RIVL_MESSAGE_LEN
#define MAX_RIVL_MESSAGE_LEN  4096
#endif
#define MAX_DATA_FRAME_LEN      1492
#define MIN_ETHERNET_PACKET_LEN 46

#ifndef MIN_ETH_FRAME_LEN
#define MIN_ETH_FRAME_LEN 60
#endif

#ifndef ETH_FRAME_LEN
#define ETH_FRAME_LEN 1514
#endif

#ifndef NETSWAP64
#define NETSWAP64(x)  \
  ((UINT64)((((UINT64)(x) & 0xFF              ) << 56) | \
           (((UINT64)(x) & 0xFF00            ) << 40) | \
           (((UINT64)(x) & 0xFF0000          ) << 24) | \
           (((UINT64)(x) & 0xFF000000        ) << 8 ) | \
           (((UINT64)(x) & 0xFF00000000      ) >> 8 ) | \
           (((UINT64)(x) & 0xFF0000000000    ) >> 24) | \
           (((UINT64)(x) & 0xFF000000000000  ) >> 40) | \
           (((UINT64)(x) & 0xFF00000000000000) >> 56)   \
          ))
#endif

DWORD
WINAPI
EthernetListen (
  LPVOID lpParameter
  )
/*++

Routine Description:

  The thread routine of capturing packet

Arguments:

  lpParameter - The parameter of the thread

Returns:

  -1 Failure
  0  Success

--*/
;
DWORD
WINAPI
ResendTimeHandler (
  LPVOID lpParameter
  )
/*++

Routine Description:

  The callback function of resending packet

Arguments:

  lpParameter - The parameter of the callback function

Returns:

  0

--*/
;

VOID_P
EthernetListenExit (
  VOID_P
  )
/*++

Routine Description:

  Stop the packet capturing

Arguments:

  None
  
Returns:

  None

--*/
;

INT32
SendRivlMessage (
  INT8        *Buffer,
  INT32       DataLen
  )
/*++

Routine Description:

  The function of sending a RIVL message

Arguments:

  Buffer  - The data buffer
  DataLen - The size of data buffer

Returns:

  0 Success

--*/
;

INT32
GetEasMac (
  INT8           *Mac
  )
/*++

Routine Description:

  Get the EAS MAC address

Arguments:

  None

Returns:

  -1 Failure
  0  Success

--*/
;

INT32
SetEasMac (
  INT8           *Mac
  )
/*++

Routine Description:

  Set the EAS MAC address

Arguments:

  Mac - The MAC address

Returns:

  -1 Failure
  0  Success

--*/
;

INT32
SendOutProbe (
  INT8          *dest_mac
  )
/*++

Routine Description:

  The function of sending a "Probe" RIVL message

Arguments:

  DestMac  - The MAC address of target machine

Returns:

  -1 Failure
  0  Success

--*/
;

INT32
SendOutCleanup(
  UINT8         *TargetMac
  )
/*++

Routine Description:

  The function of sending a "cleanup" RIVL message

Arguments:

  Buffer  - The buffer 
  DataLen - The size of data buffer

Returns:

  0 Success

--*/
;

VOID
RestoreEmsRpcEnv(
  VOID
  )
/*++

Routine Description:

  Restore the environment of EMS rpc

Arguments:

  None

Returns:

  None

--*/
;

#endif
