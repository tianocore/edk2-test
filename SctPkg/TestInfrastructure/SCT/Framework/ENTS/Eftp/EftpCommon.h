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
 
  EftpCommon.h
 
Abstract:
  Common defination for eftp client
 
--*/

#ifndef _EFI_EFTP_COMMON_H_
#define _EFI_EFTP_COMMON_H_

#include <Library/NetDebug.h>

#define EFTP_DEFAULT_TIMEOUT  3
#define EFTP_DEFAULT_RETRY    5
#define EFTP_DEFAULT_BLKSIZE  1024
#define EFTP_MIN_TIMEOUT      1
//
// See RFC 2349
//
#define EFTP_MAX_TIMEOUT                255
#define EFTP_SUPPORTED_OPTIONS_COUNT    3
#define EFTP_UNSUPPORTED_OPTIONS_COUNT  6
//
// ms
//
#define EFTP_TIMEWAIT_TIME        500
#define EFTP_CLOSEING_TIME        2

#define EFTP_TSIZE_OPTION_OFFSET  3
#define EFTP_HEADER_LEN           8
#define EFTP_PROGRAM_ERROR        0

#define TICKS_PER_SECOND          10000000
#define TICKS_PER_MILLISECOND     10000
#define TICKS_PER_MICROSECOND     10

#ifdef EFI_NETWORK_STACK_DEBUG
#define EFTP_DEBUG_PACKET(PrintArg) \
  NET_DEBUG_FL ( \
  EFI_NETWORK_DEBUGLEVEL_PACKET, \
  EFI_NETWORK_DEBUG_SOURCE_EFTP, \
  EFI_NETWORK_SUBMODULE_EFTP, \
  PrintArg \
  )

#define EFTP_DEBUG_ERROR(PrintArg) \
  NET_DEBUG_FL ( \
  EFI_NETWORK_DEBUGLEVEL_ERROR, \
  EFI_NETWORK_DEBUG_SOURCE_EFTP, \
  EFI_NETWORK_SUBMODULE_EFTP, \
  PrintArg \
  )

#define EFTP_DEBUG_WARN(PrintArg) \
  NET_DEBUG_FL ( \
  EFI_NETWORK_DEBUGLEVEL_WARNING, \
  EFI_NETWORK_DEBUG_SOURCE_EFTP, \
  EFI_NETWORK_SUBMODULE_EFTP, \
  PrintArg \
  )

#define EFTP_DEBUG_VERBOSE(PrintArg) \
  NET_DEBUG_FL ( \
  EFI_NETWORK_DEBUGLEVEL_TRACE, \
  EFI_NETWORK_DEBUG_SOURCE_EFTP, \
  EFI_NETWORK_SUBMODULE_EFTP, \
  PrintArg \
  )

#else
#define EFTP_DEBUG_PACKET(PrintArg)
#define EFTP_DEBUG_ERROR(PrintArg)
#define EFTP_DEBUG_WARN(PrintArg)
#define EFTP_DEBUG_VERBOSE(PrintArg)
/*
#define EFTP_DEBUG_PACKET(PrintArg)               SctPrint PrintArg
#define EFTP_DEBUG_ERROR(PrintArg)                SctPrint PrintArg
#define EFTP_DEBUG_WARN(PrintArg)                 SctPrint PrintArg
#define EFTP_DEBUG_VERBOSE(PrintArg)              SctPrint PrintArg
*/
#endif
//
// Eftp states
//
typedef enum {
  EFTP_INIT           = 1,
  EFTP_TIME_WAIT, // Wait the transmission and receive to complete, and signal user event
  EFTP_RRQ_SENT,
  EFTP_RRQ_ESTABLISHED,
  EFTP_RRQ_CLOSEING,

  EFTP_WRQ_SENT,
  EFTP_WRQ_ESTABLISHED,
  EFTP_WRQ_CLOSEING,
} EFTP_STATE;

typedef struct _EFTP_PEER_ADDR {
  UINT8 DstMac[NET_ETHER_ADDR_LEN];
} EFTP_PEER_ADDR;

typedef struct _EFTP_COMPLETION_TOKEN {
  UINTN                                 Signature;
  EFI_MANAGED_NETWORK_COMPLETION_TOKEN  MnpToken;
  EFTP_IO_PRIVATE                       *Private;
} EFTP_COMPLETION_TOKEN;

typedef struct _EFTP_ERRINFO {
  UINT16  Code;
  CHAR8   *Desc;
} EFTP_ERRINFO;

#endif
