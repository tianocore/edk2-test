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

  ManagedNetworkMonitor.h

Abstract:

  NetworkTest Managed Network Monitor services declarations.

--*/

#ifndef _MANAGED_NETWORK_MONITOR_H_
#define _MANAGED_NETWORK_MONITOR_H_

#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (EntsMonitorProtocol)
#include EFI_PROTOCOL_DEFINITION (ManagedNetwork)

#define ENTS_VENDOR_GUID \
  { \
    0x868b4f16, 0xc83a, 0x4205, 0xa9, 0x3c, 0x3f, 0x51, 0xcf, 0x7f, 0x61, 0xc0 \
  }

#define ENTS_SERVER_MAC_ADDRESS_NAME  L"ServerMac"
#define ENTS_APP_SEQUENCE_NAME        L"AppSequence"
#define ENTS_LINK_SEQUENCE_NAME       L"LinkSequence"
#define ENTS_MNP_MONITOR_NAME         L"Mnp"

#pragma pack(1)
typedef union {
  struct {
    UINT32  SeqId : 32;
    UINT32  Offset : 16;
    UINT32  OpCode : 8;
    UINT32  Rsvd : 7;
    UINT32  MF : 1;
  } Flag;
  UINT64  LLFlag;
} EAS_MNP_FRAG_FLAG;

typedef union {
  struct {
    UINT32  SeqId : 32;
    UINT32  Reserved : 32;
  } Flag;
  UINT64  LLFlag;
} EAS_APP_FLAG;
#pragma pack()

#define LINK_OPERATION_PROBE       0x01
#define LINK_OPERATION_PROBE_ACK   0x02
#define LINK_OPERATION_DATA        0x11
#define LINK_OPERATION_DATA_ACK    0x12
#define LINK_OPERATION_CLEANUP     0x21
#define LINK_OPERATION_CLEANUP_ACK 0x22

#define MNP_BUFFER_IN_MAX          4096

//
// Unit: uSecond
//
#define LL_TIMEOUT  1000000
typedef enum {
  WaitForPacket,
  SendoutPacket,
} LINK_LAYER_STATUS;

#define HAS_FLAG_MF(Flag) (Flag & 0x0100000000000000)
#define SET_FLAG_MF(Flag) ((Flag) |= 0x0100000000000000)
#define CLR_FLAG_MF(Flag) ((Flag) &= (~0x0100000000000000))

#define MAX_PACKET_LENGTH 1492

EFI_STATUS
ManagedNetworkSaveContext (
  IN EFI_ENTS_MONITOR_PROTOCOL                 *This
  )
/*++

Routine Description:

  This func is to save the communcation context into flash 
    (now, will save ServerMacAddr, LastSendSequence & AppSequence).

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  Others               - Some failure happened.
  
--*/
;

EFI_STATUS
ManagedNetworkRestoreContext(
  IN EFI_ENTS_MONITOR_PROTOCOL                 *This
  )
/*++

Routine Description:

  This func is to load the communcation context from flash to local variable
    (now, will load ServerMacAddr, LastSendSequence & AppSequence from flash).

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  Others               - Some failure happened.
  
--*/
;

//
// External functions declarations
//
EFI_STATUS
ManagedNetworkListener (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN OUT UINTN                     *Size,
  OUT CHAR16                       **Buffer
  )
/*++

Routine Description:

  This func is to read data from MNP network.

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.
  Size    - To indicate buffer length
  Buffer  - A buffer to return data to. It must be null before entering this func.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
ManagedNetworkSender (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN CHAR16                        *Buffer
  ) /*++

Routine Description:

  This func is to write data to MNP network.

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.
  Buffer  - A buffer to return data to. It must be null before entering this func.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_ACCESS_DENIED    - Cannot send out packet in state SendOutPacket.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.
  
--*/
;

EFI_STATUS
InitManagedNetwork (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  ) /*++

Routine Description:

  Initialize MNP Network.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
ResetManagedNetwork (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  ) /*++

Routine Description:

  Reset MNP Network.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

#endif
