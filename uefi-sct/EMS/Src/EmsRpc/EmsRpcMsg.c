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
  
    EmsRpcMsg.c
    
Abstract:

    

--*/

#include "stdlib.h"
#include "memory.h"

#include "EmsUtilityString.h"
#include "EmsPktMain.h"
#include "EmsRpcMsg.h"
#include "EmsLogUtility.h"

MSG_QUEUE *EmsMsgQueue = NULL;
HANDLE    EmsMsgMutex;

INT32
EmsMsgQCreate (
  VOID_P
  )
/*++

Routine Description:

  create an EMS message queue

Arguments:

  None.

Returns:

  1

--*/
{
  EmsMsgMutex = CreateMutex (NULL, FALSE, NULL);
  return 1;
}

VOID_P
EmsMsgDestroy (
  MSG_QUEUE *PacketPointer
  )
/*++

Routine Description:

  Destroy an EMS message

Arguments:

  PacketPointer - The poninter ot the packet

Returns:

  None

--*/
{
  if (PacketPointer) {
    free (PacketPointer->Message);
    free (PacketPointer);
  }
}

INT32
EmsMsgQDelete (
  VOID_P
  )
/*++

Routine Description:

  delete an EMS message queue

Arguments:

  None.

Returns:

  0

--*/
{
  EmsMsgQEmpty ();
  return 0;
}

INT32
EmsMsgQSend (
  INT8        *Buf,
  INT32       Length,
  INT32       Priority
  )
/*++

Routine Description:

  sent a message to an EMS message queue

Arguments:

  Buf       - raw data in message.
  Length    - message Length
  Priority  - The Priority of the message

Returns:

  If succeed, return 0, else return -1

--*/
{
  MSG_QUEUE *PacketPointer;
  MSG_QUEUE *PacketPointer1;
  INT32     Ret;
  WaitForSingleObject (EmsMsgMutex, INFINITE);

  PacketPointer = (MSG_QUEUE *) malloc (sizeof (MSG_QUEUE));
  if (NULL == PacketPointer) {
    Ret = -1;
    goto Done;
  }

  PacketPointer->Message = (INT8 *) malloc (Length);
  if (NULL == PacketPointer->Message) {
    free (PacketPointer);
    Ret = -1;
    goto Done;
  }

  memcpy (PacketPointer->Message, Buf, Length);

  PacketPointer->Length   = Length;
  PacketPointer->Priority = Priority;
  PacketPointer->Next     = NULL;

  if (EmsMsgQueue == NULL) {
    EmsMsgQueue = PacketPointer;
    Ret         = 0;
    goto Done;
  }

  for (PacketPointer1 = EmsMsgQueue; PacketPointer1->Next; PacketPointer1 = PacketPointer1->Next)
    ;
  PacketPointer1->Next  = PacketPointer;
  Ret                   = 0;

Done:
  ReleaseMutex (EmsMsgMutex);
  return Ret;
}

INT32
EmsMsgQReceive (
  INT8            *Buf,
  UINT32           Length
  )
/*++

Routine Description:

  receive message from an EMS message queue

Arguments:

  Buf     - Buffer to receive message
  Length  - the Length of input Buffer

Returns:

   If succeed, return message Length (not include reserved mtype), 
   else return -1

--*/
{
  MSG_QUEUE *PacketPointer;
  INT32     Ret;

  WaitForSingleObject (EmsMsgMutex, INFINITE);

  if (NULL == EmsMsgQueue) {
    Ret = -1;
    goto Done;
  }

  PacketPointer = EmsMsgQueue;
  EmsMsgQueue   = EmsMsgQueue->Next;

  if (Length < PacketPointer->Length) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS:  Receive a too long Message from agent "
      );
    Ret = -1;
    goto Done;
  }

  memcpy (Buf, PacketPointer->Message, PacketPointer->Length);
  Ret = PacketPointer->Length;
  EmsMsgDestroy (PacketPointer);
Done:
  ReleaseMutex (EmsMsgMutex);
  return Ret;
}

INT32
EmsMsgQEmpty (
  VOID_P
  )
/*++

Routine Description:

  Empty an EMS message queue

Arguments:

  None.

Returns:

  0

--*/
{
  MSG_QUEUE *PacketPointer;
  MSG_QUEUE *PacketPointer1;

  WaitForSingleObject (EmsMsgMutex, INFINITE);

  PacketPointer = EmsMsgQueue;
  while (PacketPointer) {
    PacketPointer1  = PacketPointer;
    PacketPointer   = PacketPointer->Next;
    EmsMsgDestroy (PacketPointer1);
  }

  EmsMsgQueue = NULL;

  ReleaseMutex (EmsMsgMutex);

  return 0;
}
