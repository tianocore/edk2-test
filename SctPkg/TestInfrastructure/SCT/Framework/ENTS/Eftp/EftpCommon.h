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
