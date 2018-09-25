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

  NetDebug.h

Abstract:

  Header file of Network Debugging

--*/

//
// Definition of debug level, internal used by network stack testing
//


#ifndef NET_DEBUG_H_D1965E9417AD4B77BA036AFB9D58E725
#define NET_DEBUG_H_D1965E9417AD4B77BA036AFB9D58E725

///////////////////////////////////////////////////////////////////////
//
// Usage Model:
// 
// 
// 1 Get current time starting from machine resetting,
//   You should define your CPU frequency and the unit of time in file
//   "NetDebug.h" first.
//
//    MS for millisecond and TK for Tick
//
//    #define CPU_FREQU 2200000
//    #define PERFORMANCE_DATA_IN_MS or PERFORMANCE_DATA_IN_TK
//
//    usage: GET_CURRENT_TIME(a)      // UINT64 a;


/*
//
// Macros for performance testing
//
#define PERFORMANCE_DATA_IN_MS
#define CPU_FREQU 2200000


#ifdef PERFORMANCE_DATA_IN_MS
#define GET_CURRENT_TIME(time) GET_CURRENT_TIME_IN_MS(time)

#else

#ifdef PERFORMANCE_DATA_IN_TK
#define GET_CURRENT_TIME(time) GET_CURRENT_TIME_IN_TK(time)
#else
#define GET_CURRENT_TIME(time)
#endif

#endif


//
// Helper function and macros
//
VOID
GET_CURRENT_TICK (
  OUT UINT64 *time
  );


UINT64
NetDebugDivU64x32 (
  IN UINT64   Dividend,
  IN UINTN    Divisor,
  OUT UINTN   *Remainder OPTIONAL
  );

#define GET_CURRENT_TIME_IN_TK(time) { \
  GET_CURRENT_TICK (&(time)); \
}

#define GET_CURRENT_TIME_IN_MS(time) { \
  GET_CURRENT_TIME_IN_TK(time); \
  time = NetDebugDivU64x32(time, CPU_FREQU, NULL); \
}
*/

#ifdef EFI_SYS_LOG

#include EFI_PROTOCOL_CONSUMER (NetDebugConfig)

#define EFI_NETWORK_MAX_PRINT_BUFFER 80*4

extern EFI_NET_DEBUG_CONFIG_PROTOCOL  *NetDebugConfigProtocol;

extern EFI_NET_DEBUG_CONFIG * NetDebugConfig;


EFI_NET_DEBUG_CONFIG *
NetDbgGetCfg (
);

VOID
NetDbgDump (
);

BOOLEAN 
NetDbgCheck(
  IN UINT8  Level,
  IN UINT16 Source,
  IN UINT32 SubModule
  );

INTN 
NetDbgOutput(
  IN UINT8  Level,
  IN UINT16 Source,
  IN UINT32 SubModule,
  IN CHAR8  *FileName,
  IN UINT32 LineNumber,
  IN CHAR16 *Description
  );

CHAR16* NetDbgSPrint (CHAR16 *Format, ... );

INTN 
NetDbgAssert(
  IN CHAR16 *FileName,
  IN UINT32 LineNumber,
  IN CHAR16 *Description
  );

#endif //EFI_SYS_LOG

#ifdef EFI_DEBUG_MEMORY_LEAK

#define NET_DEBUG_MAX_FILE_NAME 128
#define DBG_POOL_INFO_SIGNATURE EFI_SIGNATURE_32('D','P','I','F')

//structure to hold debug information
typedef struct _DBG_POOL_INFO
{
  SCT_LIST_ENTRY          Entry;
  UINT32                  Signature;
  CHAR16                  FileName[ NET_DEBUG_MAX_FILE_NAME ];
  UINTN                   Line;
  UINTN                   Size;
}DBG_POOL_INFO;


VOID*
EFIAPI
AllocatePoolDbg(
  IN UINTN            Size,
  IN CHAR16           *FileName,
  IN UINTN            Line
  );

VOID*
EFIAPI
AllocateZeroPoolDbg(
  IN UINTN            Size,
  IN CHAR16           *FileName,
  IN UINTN            Line
  );

VOID
EFIAPI
FreePoolDbg (
  IN VOID            *Buffer
  );

#endif //EFI_DEBUG_MEMORY_LEAK

#endif
