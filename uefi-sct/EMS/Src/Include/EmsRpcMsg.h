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
  
    EmsRpcMsg.h
    
Abstract:

    Incude header files for EMS RPC functions

--*/

#ifndef __EMS_MSG_H__
#define __EMS_MSG_H__

#include <sys/types.h>
#include "EmsTypes.h"
#include <errno.h>

#define MSG_PRI_NORMAL  1
#define MSG_PRI_URGENT  2
#define MSG_BUF_SIZE    100

#ifndef WAIT_FOREVER
#define WAIT_FOREVER  0xFFFFFFFF
#endif
//
// Data Structure: message send buffer
//
typedef struct _MSG_QUEUE {
  INT8              *Message;
  UINT32            Length;
  UINT32            Priority;
  struct _MSG_QUEUE *Next;
} MSG_QUEUE;

//
// Prototype of function
//
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
;

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
;

INT32
EmsMsgQSend (
  INT8  *Buf,
  INT32 Length,
  INT32 Priority
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
;

INT32
EmsMsgQReceive (
  INT8  *Buf,
  UINT32 Length
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
;

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
;

#endif
