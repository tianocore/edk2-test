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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsPktMain.c
    
Abstract:

    Implementation for packet related TCL commands

--*/

#include "EmsUtilityString.h"
#include "EmsPktMain.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

PACKET_T  *PacketQueue = NULL;

PACKET_T *
EmsPacketCreate (
  CONST INT8        *Name,
  UINT8             *Data,
  UINT32            Len,
  struct timeval    *Time
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
{
  PACKET_T  *PacketPointer;

  PacketPointer = malloc (sizeof (PACKET_T));

  memcpy (&(PacketPointer->Time), Time, sizeof (struct timeval));
  strcpy (PacketPointer->Name, Name);

  PacketPointer->Data = (UINT8 *) malloc (Len);
  memcpy (PacketPointer->Data, Data, sizeof (UINT8) * Len);

  PacketPointer->DataLen  = Len;
  PacketPointer->Next     = NULL;

  return PacketPointer;
}

PACKET_T *
EmsPacketFindByName (
  CONST INT8 *Name
  )
/*++

Routine Description:

  Find packet according to name

Arguments:

  Name  - The name of the packet

Returns:

  the pointer to packet found

--*/
{
  PACKET_T  *PacketPointer;
  PacketPointer = PacketQueue;
  while (PacketPointer) {
    if (0 == strcmp (Name, PacketPointer->Name)) {
      break;
    }

    PacketPointer = PacketPointer->Next;
  }

  return PacketPointer;
}

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
{
  PACKET_T  *PacketPointer;

  if (PacketQueue == NULL) {
    return ;
  }

  if (strcmp (Name, PacketQueue->Name)) {
    PacketQueue = PacketQueue->Next;
    return ;
  }

  for (PacketPointer = PacketQueue; PacketPointer && PacketPointer->Next; PacketPointer = PacketPointer->Next) {
    if (0 == strcmp (Name, PacketPointer->Next->Name)) {
      PacketPointer->Next = PacketPointer->Next->Next;
      return ;
    }
  }
}

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
{
  PACKET_T  *PacketPointer;

  if (Packet == NULL) {
    return ;
  }

  if (PacketQueue == Packet) {
    PacketQueue = PacketQueue->Next;
    return ;
  }

  for (PacketPointer = PacketQueue; PacketPointer && PacketPointer->Next; PacketPointer = PacketPointer->Next) {
    if (PacketPointer->Next == Packet) {
      PacketPointer->Next = PacketPointer->Next->Next;
      return ;
    }
  }
}

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
{
  PACKET_T  *PacketPointer;
  if (Packet == NULL) {
    return ;
  }

  if (PacketQueue == NULL) {
    PacketQueue   = Packet;
    Packet->Next  = NULL;
    return ;
  }

  for (PacketPointer = PacketQueue; PacketPointer->Next; PacketPointer = PacketPointer->Next)
    ;
  PacketPointer->Next = Packet;
  Packet->Next        = NULL;
  return ;
}

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
{
  if (Packet) {
    free (Packet->Data);
    free (Packet);
  }
}

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
{
  PACKET_T  *PacketPointer;
  PACKET_T  *PacketPointer1;

  PacketPointer = PacketQueue;
  while (PacketPointer) {
    PacketPointer1  = PacketPointer;
    PacketPointer   = PacketPointer->Next;
    EmsPacketDestroy (PacketPointer1);
  }

  PacketQueue = NULL;
}

PACKET_T *
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
{
  PACKET_T        *PacketPointer;
  struct timeval  Time;
  PacketPointer = EmsPacketFindByName (Name);
  if (NULL == PacketPointer) {
    PacketPointer = EmsPacketCreate (Name, NULL, 0, &Time);
    EmsPacketAdd (PacketPointer);
  }

  if (PacketPointer->Data) {
    free (PacketPointer->Data);
  }

  PacketPointer->Data     = Data;
  PacketPointer->DataLen  = Len;

  return PacketPointer;
}

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
{
  struct tm *dtime;
  INT8      Str[256];
  UINT32    Index;

  sprintf (Buff, "Name: %s\n", Packet->Name);

  dtime = localtime ((const time_t *)&Packet->Time.tv_sec);
  strftime (Str, sizeof (Str), "%H:%M:%S", dtime);
  strcat (Buff, Str);
  sprintf (Str, "%.6ld Len:%d \n", (Packet->Time).tv_usec, Packet->DataLen);
  strcat (Buff, Str);

  for (Index = 0; Index < Packet->DataLen; Index++) {
    sprintf (Str, "%02x ", Packet->Data[Index]);
    strcat (Buff, Str);
  }

  strcat (Buff, "\n");
}
