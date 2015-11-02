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
