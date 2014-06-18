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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
