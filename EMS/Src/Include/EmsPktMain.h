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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsPktMain.h
    
Abstract:

    Data definition for packet related functions

--*/

#ifndef __EMS_PACKET_H__
#define __EMS_PACKET_H__

#include "EmsTypes.h"
#include "EmsNet.h"

#define PACKET_NAME_SIZE  32

typedef struct _PACKET_T {
  INT8              Name[PACKET_NAME_SIZE]; // packet name
  UINT8             *Data;                  // packet content
  UINT32            DataLen;                // packet length
  struct timeval    Time;                   // time when captured the packet
  struct _PACKET_T  *Next;                  // next
} PACKET_T;

extern PACKET_T *PacketQueue;               /* Global packet queue */

PACKET_T        *
EmsPacketCreate (
  CONST INT8       *Name,
  UINT8            *Data,
  UINT32           Len,
  struct timeval   *Time
  )
/*++

Routine Description:

  Create a packet_t structure.

Arguments:

  Name  - packet name
  Data  - packet content
  Len   - packet length
  Time  - time when captured the packet

Returns:

  the pointer to packet created

--*/
;

PACKET_T        *
EmsPacketFindByName (
  CONST INT8 *Name
  )
/*++

Routine Description:

  Remove packet according to name

Arguments:

  Name  - Packet name

Returns:

  None

--*/
;

VOID_P
EmsPacketRemoveByName (
  INT8 *Name
  )
/*++

Routine Description:

  Remove packet according to name

Arguments:

  Name  - Packet name

Returns:

  None

--*/
;

VOID_P
EmsPacketRemove (
  PACKET_T *Packet
  )
/*++

Routine Description:

  Remove packet from the queue of packet

Arguments:

  Packet  - The pointer to the packet

Returns:

  None

--*/
;

VOID_P
EmsPacketAdd (
  PACKET_T *Packet
  )
/*++

Routine Description:

  Add a packet to the packet queue

Arguments:

  Packet  - The packet

Returns:

  None

--*/
;

VOID_P
EmsPacketDestroy (
  PACKET_T *Packet
  )
/*++

Routine Description:

  Destroy a packet

Arguments:

  Packet  - The pointer to the packet

Returns:

  None

--*/
;

VOID_P
EmsPacketDump (
  INT8     *Buff,
  PACKET_T *Packet
  )
/*++

Routine Description:

  Dump the content of a packet

Arguments:

  Buff    - The data buffer for the packet
  Packet  - The pointer to the packet

Returns:

  None

--*/
;

PACKET_T        *
EmsPacketCreateAdd (
  CONST INT8      *Name,
  UINT8           *Data,
  UINT32          Len
  )
/*++

Routine Description:

  Create a packet and add it to packet queue

Arguments:

  Name  - Packet name
  Data  - The data of the packet
  Len   - The size of the packet data

Returns:

  The pointer to the new packet

--*/
;

VOID_P
EmsPacketQueueDestroy (
  VOID_P
  )
/*++

Routine Description:

  Destroy the packet queue

Arguments:

  None

Returns:

  None

--*/
;

#endif
