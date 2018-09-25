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
  
    EmsEftpSession.c
    
Abstract:

    

--*/

#include "EmsEftp.h"
#include "EmsEftpSession.h"
#include "EmsEftpRrqStrategy.h"
#include "EmsEftpWrqStrategy.h"
#include "EmsTclCleanup.h"

extern INT8         *EmsInterface;

STATIC Eftp_Session EftpSessionArray[MAX_SESSION_NUM] = { 0, };
STATIC Eftp_Session *EftpSessionFreeListHead          = EftpSessionArray;
STATIC Eftp_Session *EftpSessionActiveListHead        = NULL;

STATIC HANDLE       EmsEftpSessionOperationMutex      = NULL;

UINT32              CRCTable[256] = {
  0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535,
  0x9E6495A3, 0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD,
  0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D,
  0x6DDDE4EB, 0xF4D4B551, 0x83D385C7, 0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
  0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4,
  0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 0x35B5A8FA, 0x42B2986C,
  0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59, 0x26D930AC,
  0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
  0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB,
  0xB6662D3D, 0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F,
  0x9FBFE4A5, 0xE8B8D433, 0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB,
  0x086D3D2D, 0x91646C97, 0xE6635C01, 0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
  0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA,
  0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65, 0x4DB26158, 0x3AB551CE,
  0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB, 0x4369E96A,
  0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
  0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409,
  0xCE61E49F, 0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81,
  0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739,
  0x9DD277AF, 0x04DB2615, 0x73DC1683, 0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
  0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1, 0xF00F9344, 0x8708A3D2, 0x1E01F268,
  0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7, 0xFED41B76, 0x89D32BE0,
  0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 0xD6D6A3E8,
  0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
  0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF,
  0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703,
  0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7,
  0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D, 0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
  0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713, 0x95BF4A82, 0xE2B87A14, 0x7BB12BAE,
  0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242,
  0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777, 0x88085AE6,
  0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
  0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D,
  0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5,
  0x47B2CF7F, 0x30B5FFE9, 0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605,
  0xCDD70693, 0x54DE5729, 0x23D967BF, 0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
  0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

#define EMSEFTPSESSIONPKTPOOLMAXSIZE  0x100

STATIC EmsEftpPkt   *EmsEftpSessionPktPool      = NULL;
STATIC UINT32       EmsEftpSessionPktPoolSize   = 0;
STATIC HANDLE       EmsEftpSessionPktPoolMutex  = NULL;

STATIC
VOID
EmsEftpSessionPktPoolCreate (
  VOID
  )
/*++

Routine Description:

  Create an EMS Eftp session packet pool

Arguments:

  None

Returns:

  None

--*/
{
  EmsEftpSessionPktPoolMutex = CreateMutex (NULL, FALSE, NULL);
}

STATIC
VOID
EmsEftpSessionPktPoolDelete (
  VOID
  )
/*++

Routine Description:

  Delete an EMS Eftp session packet pool

Arguments:

  None

Returns:

  None

--*/
{
  EmsEftpPkt  *Tmp;

  Tmp = NULL;
  WaitForSingleObject (EmsEftpSessionPktPoolMutex, INFINITE);
  while (EmsEftpSessionPktPool) {
    Tmp                   = EmsEftpSessionPktPool;
    EmsEftpSessionPktPool = EmsEftpSessionPktPool->Next;
    free (Tmp);
  }

  EmsEftpSessionPktPoolSize = 0;
  ReleaseMutex (EmsEftpSessionPktPoolMutex);

  CloseHandle (EmsEftpSessionPktPoolMutex);
}

STATIC
VOID
EmsEftpSessionPktPoolPutOne (
  EmsEftpPkt *Pkt
  )
/*++

Routine Description:

  Put one packet into the pool

Arguments:

  Pkt - The packet to be put

Returns:

  None

--*/
{
  EmsEftpPkt  *Tmp;

  Tmp = NULL;

  WaitForSingleObject (EmsEftpSessionPktPoolMutex, INFINITE);
  if (EmsEftpSessionPktPoolSize > EMSEFTPSESSIONPKTPOOLMAXSIZE) {
    ReleaseMutex (EmsEftpSessionPktPoolMutex);
    free (Pkt);
    return ;
  } else {
    Pkt->Next             = EmsEftpSessionPktPool;
    EmsEftpSessionPktPool = Pkt;
    EmsEftpSessionPktPoolSize++;
  }

  ReleaseMutex (EmsEftpSessionPktPoolMutex);
}

STATIC
VOID
EmsEftpSessionPktPoolPutMass (
  EmsEftpPkt *Head,
  EmsEftpPkt *Tail,
  UINT32     NodeNum
  )
/*++

Routine Description:

  Put several packages into the pool

Arguments:

  Head    - The head of the packet list to be put
  Tail    - The tail of the packet list to be put
  NodeNum - The number of packets to be put

Returns:

  None

--*/
{
  EmsEftpPkt  *Tmp;

  Tmp = NULL;

  WaitForSingleObject (EmsEftpSessionPktPoolMutex, INFINITE);
  if (Head == NULL) {
    ReleaseMutex (EmsEftpSessionPktPoolMutex);
    return ;
  } else if (EmsEftpSessionPktPoolSize > EMSEFTPSESSIONPKTPOOLMAXSIZE) {
    while (Head) {
      Tmp   = Head;
      Head  = Head->Next;
      free (Tmp);
    }
  } else {
    Tail->Next            = EmsEftpSessionPktPool;
    EmsEftpSessionPktPool = Head;
    EmsEftpSessionPktPoolSize += NodeNum;
  }

  ReleaseMutex (EmsEftpSessionPktPoolMutex);
}

STATIC
INT32
EmsEftpSessionPktPoolGet (
  EmsEftpPkt **Pkt
  )
/*++

Routine Description:

  Get one packet from the pool

Arguments:

  Pkt - The packet to be get and return

Returns:

  0  Success
  -1 Failure

--*/
{
  WaitForSingleObject (EmsEftpSessionPktPoolMutex, INFINITE);
  if (EmsEftpSessionPktPool == NULL) {
    ReleaseMutex (EmsEftpSessionPktPoolMutex);
    if (NULL == (*Pkt = (EmsEftpPkt *) malloc (sizeof (EmsEftpPkt)))) {
      return -1;
    }
  } else {
    *Pkt                  = EmsEftpSessionPktPool;
    EmsEftpSessionPktPool = EmsEftpSessionPktPool->Next;
    EmsEftpSessionPktPoolSize--;
  }

  ReleaseMutex (EmsEftpSessionPktPoolMutex);
  return 0;
}

#undef EMSEFTPSESSIONPKTPOOLMAXSIZE

/*------------------------------------------------------------------------*/
#define EmsEftpSessionOperationLock()    WaitForSingleObject (EmsEftpSessionOperationMutex, INFINITE)
#define EmsEftpSessionOperationUnlock()  ReleaseMutex (EmsEftpSessionOperationMutex);

VOID
EMsEftpSessionPktFree (
  EmsEftpPkt *Pkt
  )
/*++

Routine Description:

  Free a packet

Arguments:

  Pkt - The packet should be free

Returns:

  None

--*/
{
  EmsEftpSessionPktPoolPutOne (Pkt);
}

INT32
EmsEftpSessionPktSave (
  EmsEftpPkt        **Pkt,
  CONST UINT8       *Buffer,
  INT32             Len
  )
/*++

Routine Description:

  Save a packet to a given buffer

Arguments:

  Pkt     - The packet to be saved
  Buffer  - The buffer used to save the content of packet
  Len     - The length of the buffer

Returns:

  -1 Failure
  0  Success

--*/
{
  if (EmsEftpSessionPktPoolGet (Pkt) != 0) {
    return -1;

  }

  memcpy ((*Pkt)->Buffer, Buffer, Len);
  (*Pkt)->Length  = Len;
  (*Pkt)->Next    = NULL;
  return 0;
}

STATIC
Eftp_Session *
EmsEftpFindSessionAccrodingMac (
  UINT8 *MacAddr
  )
/*++

Routine Description:

  Find the Session according to the given MAC address

Arguments:

  MacAddr - The MAC address which be used to find the corresponding session

Returns:

  Data structure of session if find
  NULL if not find 

--*/
{
  Eftp_Session  *Session;

  Session = NULL;

  for (Session = EftpSessionActiveListHead; Session; Session = Session->Next) {
    if (strncmp (MacAddr, Session->SrcMacAddr, 6) == 0) {
      return Session;
    }
  }

  return NULL;
}

INT32
EmsEftpSessionPktPut (
  UINT8             *SrcMacAddr,
  EmsEftpPkt        *Pkt
  )
/*++

Routine Description:

  Give a packet to the corresponding session and let the Session to 
  process it.

Arguments:

  SrcMacAddr  - The MAC address of the source machine
  Pkt         - The packet should be put

Returns:

  -1 Failure
  0  Success

--*/
{
  Eftp_Session  *Session;

  Session = NULL;

  EmsEftpSessionOperationLock ();

  /* search again, check the session is valid */
  if (NULL == (Session = EmsEftpFindSessionAccrodingMac (SrcMacAddr))) {
    printf ("######BUG: EmsEftpSessionPktPut the session is not exists\n");
    EmsEftpSessionOperationUnlock ();
    return -1;
  } else {
    if (NULL == Session->SessionPktListHead) {
      Session->SessionPktListHead = Pkt;
      Session->SessionPktListTail = Pkt;
    } else {
      Session->SessionPktListTail->Next = Pkt;
      Pkt->Next                         = NULL;
      Session->SessionPktListTail       = Pkt;
    }

    Session->SessionPktListNodeNum++;
  }

  /*
   * After save the pkt we must wait up the waiting session.
   * The session must be blocked in EmsEftpSessionSendData, 
   * EmsEftpSessionResendData or EmsEftpSessionPktGet
   */
  EmsEftpSessionSignal (Session);
  EmsEftpSessionOperationUnlock ();

  return 0;
}

VOID
EmsEftpSessionPktGet (
  Eftp_Session      *Session,
  EmsEftpPkt        **Pkt
  )
/*++

Routine Description:

  Get a packet from the packet list in the session data structure

Arguments:

  Session - The Session data structure which contain packet list
  Pkt     - The packet which be got

Returns:

  None

--*/
{
PktGetRetry:
  EmsEftpSessionOperationLock ();
  if (Session->SessionPktListHead == NULL)
  {
    EmsEftpSessionOperationUnlock ();
    EmsEftpSessionWait (Session);
    goto PktGetRetry;
  } else {
    if (Session->SessionPktListHead == Session->SessionPktListTail) {
      *Pkt                        = Session->SessionPktListHead;
      Session->SessionPktListHead = NULL;
      Session->SessionPktListTail = NULL;
    } else {
      *Pkt                        = Session->SessionPktListHead;
      Session->SessionPktListHead = Session->SessionPktListHead->Next;
    }

    Session->SessionPktListNodeNum--;
  }

  EmsEftpSessionOperationUnlock ();
}

STATIC
VOID
EmsEftpSessionPktListCreate (
  Eftp_Session      *Session
  )
/*++

Routine Description:

  Create the packet list of the session

Arguments:

  Session - The session should be create a packet list

Returns:

  None

--*/
{
  Session->SessionPktListHead     = NULL;
  Session->SessionPktListTail     = NULL;
  Session->SessionPktListNodeNum  = 0;
}

STATIC
VOID
EmsEftpSessionPktListDelete (
  Eftp_Session      *Session
  )
/*++

Routine Description:

  Delete The packet list from the session

Arguments:

  Session - The session should be deleted its packet list

Returns:

  None

--*/
{
  EmsEftpPkt  *Head, *Tail;
  UINT32      NodeNum;

  Tail = Head = NULL;
  NodeNum = 0;

  Head = Session->SessionPktListHead;
  Tail = Session->SessionPktListTail;
  NodeNum = Session->SessionPktListNodeNum;
  Session->SessionPktListHead = NULL;
  Session->SessionPktListTail = NULL;
  Session->SessionPktListNodeNum = 0;

  EmsEftpSessionPktPoolPutMass (Head, Tail, NodeNum);
}

UINT32
EmsEftpCalCrc (
  UINT8  *pt,
  UINT32 Size
  )
/*++

Routine Description:

  Compute the Crc for a packet

Arguments:

  pt    - The packet should be process
  Size  - The size fo the packet

Returns:

  values of Crc

--*/
{
  UINT32  Crc;

  //
  // compute crc
  //
  Crc = 0xffffffff;
  while (Size) {
    Crc = (Crc >> 8) ^ CRCTable[(UINT8) Crc ^ *pt];
    pt += 1;
    Size -= 1;
  }

  Crc = Crc ^ 0xffffffff;
  return (UINT32) Crc;
}

UINT16
EmsEftpCalChecksum (
  UINT16 *Buf,
  UINT32 Nwords
  )
/*++

Routine Description:

  Compute the checksum for a data buffer

Arguments:

  Buf     - Data buffer
  Nwords  - How many words does the buffer contain

Returns:

  The checksum

--*/
{
  UINT32  Sum;
  UINT32  Index;

  Sum = 0;
  if (Nwords < 0) {
    return 0xffff;
  }

  for (Index = 0; Index < Nwords; Index++) {
    Sum += (UINT16) (*Buf++);
    if (Sum & 0xFFFF0000) {
      Sum = (Sum >> 16) + (Sum & 0x0000ffff);
    }
  }

  Sum = (Sum >> 16) + (Sum & 0xffff);
  Sum += (Sum >> 16);

  return (UINT16) (~Sum);
}

STATIC
VOID
EmsSessionServiceThread (
  VOID *Arg
  )
/*++

Routine Description:

  The service thread routine of the EMS Eftp session

Arguments:

  Arg - The parameter of the thread routine

Returns:

  None

--*/
{
  Eftp_Session  *Session;
  EmsEftpPkt    *Pkt;

  Session   = (Eftp_Session *) Arg;
  Pkt       = NULL;

  while (TRUE) {
    switch (Session->State) {
    case ESTABLISHED:
      EmsEftpSessionPktGet (Session, &Pkt);
      Session->Strategy.HandlePkt (&Session->Strategy, Pkt->Buffer, Pkt->Length);
      EmsEftpSessionPktPoolPutOne (Pkt);
      break;

    case CLOSING:
      Session->ResendData (Session);
      break;

    case CLOSED:
      /* only the session be CLOSED state the thread can exit */
      EmsEftpSessionUnregister (Session);
      goto EmsSessionServiceThreadExit;

    case INVALID:
      printf ("######BUG: EmsSessionServiceThread Session State INVALID\n");
      goto EmsSessionServiceThreadExit;
    }
  }

EmsSessionServiceThreadExit:
  return ;
}

VOID
EmsEftpSessionGetOpcode (
  CONST INT8   *Pkt,
  UINT16       *OpCode
  )
/*++

Routine Description:

  Get the opcode from the packet

Arguments:

  Pkt     - The packet should be analyze
  OpCode  - The Opcode should be get and return

Returns:

  None

--*/
{
  memcpy (OpCode, Pkt + OPCODE_OFFSET, 2);
  *OpCode = ntohs ((UINT16) (*OpCode));
}

VOID
EmsEftpSessionGetBlkno (
  CONST INT8   *Pkt,
  UINT16       *BlkNo
  )
/*++

Routine Description:

  Get the block number from the packet

Arguments:

  Pkt   - The packet should be analyze
  BlkNo - The block number should be get and return

Returns:

  None

--*/
{
  memcpy (BlkNo, Pkt + BLKNO_OFFSET, 2);
  *BlkNo = ntohs ((UINT16) (*BlkNo));
}

VOID
EmsEftpSessionGetLength (
  INT8   *Pkt,
  UINT16 *Length
  )
/*++

Routine Description:

  Get the packet length from the packet

Arguments:

  Pkt     - The packet should be analyze
  Length  - The packet length should be get and return

Returns:

  None

--*/
{
  memcpy (Length, Pkt + LENGTH_OFFSET, 2);
  *Length = ntohs ((UINT16) *Length);
}

UINT32
EmsEftpSessionBuildPkt (
  Eftp_Session *Session,
  UINT8        *SendPkt,
  UINT16       Type,
  UINT16       OpCode,
  UINT16       BlkNo,
  INT8         *DataBuf,
  UINT32       DataLen
  )
/*++

Routine Description:

  The implementation to build a packet

Arguments:

  Session - The data structure of the EMS Eftp session
  SendPkt - The packet should be build
  Type    - The type of the new packet
  OpCode  - The opcode of the new packet
  BlkNo   - The block number of the new packet
  DataBuf - The content of the packet
  DataLen - The length of the packet

Returns:

  The Length of the new packet

--*/
{
  UINT32  Crc32;
  UINT32  Length;
  UINT16  CheckSum;

  //
  // Fill the Src Mac field
  //
  memcpy (SendPkt + SRC_MAC_OFFSET, Session->DesMacAddr, 6);

  //
  // Fill the Des Mac field
  //
  memcpy (SendPkt + DES_MAC_OFFSET, Session->SrcMacAddr, 6);

  //
  // Fill the Type field
  //
  Type = htons ((UINT16) Type);
  memcpy (SendPkt + TYPE_OFFSET, &Type, sizeof (UINT16));

  //
  // Fill the Length field
  //
  Length = htons ((UINT16) (EFTP_HEADER_LEN + DataLen));
  memcpy (SendPkt + LENGTH_OFFSET, &Length, sizeof (UINT16));

  //
  // Fill the Checksum field
  //
  Length    = EFTP_HEADER_LEN + DataLen;
  CheckSum  = EmsEftpCalChecksum ((UINT16 *) (SendPkt + LENGTH_OFFSET), Length / 2);
  CheckSum  = htons (CheckSum);
  memcpy (SendPkt + CHECK_SUM_OFFSET, &CheckSum, sizeof (UINT16));

  //
  // Fill the Opcode field
  //
  OpCode = htons (OpCode);
  memcpy (SendPkt + OPCODE_OFFSET, &OpCode, sizeof (UINT16));

  //
  // Fill the BlkNo field
  //
  BlkNo = htons (BlkNo);
  memcpy (SendPkt + BLKNO_OFFSET, &BlkNo, sizeof (UINT16));

  //
  // Fill the Data field if it exists
  //
  if (DataLen != 0) {
    memcpy (SendPkt + DATA_OFFSET, DataBuf, DataLen);

  }
  //
  // Fill the Crc32 field after Calculating CRC32
  //
  Length  = DATA_OFFSET + DataLen;
  Crc32   = EmsEftpCalCrc (SendPkt, Length / 2);
  Crc32   = htons ((UINT32) Crc32);
  memcpy (SendPkt + DATA_OFFSET + DataLen, &Crc32, sizeof (UINT32));

  //
  // Return the total length of the pkt
  //
  Length = DATA_OFFSET + DataLen + sizeof (UINT32);

  return Length;
}

VOID
EmsEftpSessionResendData (
  Eftp_Session *Session
  )
/*++

Routine Description:

  The routine for resending data

Arguments:

  Session - The EMS Eftp session which should resend data

Returns:

  None

--*/
{
  Session->SendData (Session, Session->LastSentMsg, Session->LastSentLen);
}

STATIC
VOID
EmsEftpSessionSendData (
  Eftp_Session *Session,
  INT8         *Pkt,
  UINT32       Len
  )
/*++

Routine Description:

  The routine for send data

Arguments:

  Session - The EMS Eftp session which should resend data
  Pkt     - The packet which should be send
  Len     - The length of the packet

Returns:

  None

--*/
{
  DWORD RetVal;
  INT32 TimeoutCount;

  TimeoutCount = Session->TimeoutCount;

  do {
    if ((RetVal = libnet_write_link (Session->LibnetHandler, Pkt, Len)) < Len) {
      /* Error */
      EFTP_DEBUG_MSG ("EmsEftpSessionSendData: Error should be %d actual ret is %d !!!!!!!!\n", Len, RetVal);
      return ;
    } else {
      memcpy (Session->LastSentMsg, Pkt, Len);
      Session->LastSentLen = Len;
    }

    switch (RetVal = EmsEftpSessionTimeWait (Session)) {
    case WAIT_TIMEOUT:
      /* send again */
      TimeoutCount--;
      break;

    case WAIT_OBJECT_0:
      return ;

    default:
      TimeoutCount--;
      printf ("######BUG EmsEftpSessionSendData EmsEftpSessionTimeWait return unexcept:%x\n", RetVal);
    }
  } while (TimeoutCount);

  if (TimeoutCount == 0) {
    Session->SilentShutdown (Session);
  }
}

STATIC
VOID
EmsEftpSessionLoudShutdown (
  Eftp_Session *Session
  )
/*++

Routine Description:

  Set the session's state to CLOSING

Arguments:

  Session - The session should loud shut down

Returns:

  None

--*/
{
  Session->State = CLOSING;
  EFTP_DEBUG_MSG ("EmsEftpSessionLoudShutdown: Session state CLOSED \n");
}

STATIC
VOID
EmsEftpSessionSilentShutdown (
  Eftp_Session *Session
  )
/*++

Routine Description:

  Set the session's state to CLOSED

Arguments:

  Session - The session should silent shut down

Returns:

  None

--*/
{
  Session->State = CLOSED;
  EFTP_DEBUG_MSG ("EmsEftpSessionSilentShutdown: Session state CLOSED \n");
}

STATIC
VOID
EmsEftpSessionClose (
  Eftp_Session *Session
  )
/*++

Routine Description:

  Close a EMS Eftp session

Arguments:

  Session - The session to be closed

Returns:

  None

--*/
{
  if (NULL != Session->LibnetHandler) {
    libnet_cq_remove(Session->LibnetHandler);
    libnet_destroy (Session->LibnetHandler);
  }

  CloseHandle (Session->SessionWaitPktEvent);
  EmsEftpSessionPktListDelete (Session);
  Session->Strategy.Close (&Session->Strategy);
  Session->State = INVALID;
}

STATIC
INT32
EmsEftpSessionOpen (
  Eftp_Session *Session,
  UINT8        *SrcMacAddr,
  UINT8        *DesMacAddr,
  UINT16       OpCode,
  INT8         *FileName
  )
/*++

Routine Description:

  Open an EMS Eftp session

Arguments:

  Session     - The session should be opened
  SrcMacAddr  - The source MAC address which is the session's attribution
  DesMacAddr  - The target MAC address which is the session's attribution
  OpCode      - The opcode of the session
  FileName    - The name of the file which the session will open

Returns:

  -1 Failure
  0  Success

--*/
{
  INT8      ErrBuf[LIBNET_ERRBUF_SIZE];
  EmsThread *Thread;

  memset (Session, 0x0, sizeof (Eftp_Session));

  Session->SessionId = Session - EftpSessionArray;
  memcpy (Session->SrcMacAddr, SrcMacAddr, MAX_MAC_LEN);
  memcpy (Session->DesMacAddr, DesMacAddr, MAX_MAC_LEN);
  Session->Timeout      = MAX_TIMEOUT_VALUE;
  Session->TimeoutCount = MAX_TIMEOUT_COUNT;
  if (NULL == (Session->LibnetHandler = libnet_init (LIBNET_LINK, EmsInterface, ErrBuf))) {
    EFTP_DEBUG_MSG ("EmsEftpSessionOpen: libnet_init Error:%s\n", ErrBuf);
    goto SessionOpenError3;
  }

  Session->GetOpCode      = EmsEftpSessionGetOpcode;
  Session->GetBlkNo       = EmsEftpSessionGetBlkno;
  Session->GetLength      = EmsEftpSessionGetLength;
  Session->SendData       = EmsEftpSessionSendData;
  Session->ResendData     = EmsEftpSessionResendData;
  Session->BuildPkt       = EmsEftpSessionBuildPkt;
  Session->SilentShutdown = EmsEftpSessionSilentShutdown;
  Session->LoudShutdown   = EmsEftpSessionLoudShutdown;

  switch (OpCode) {
  case EFTP_RRQ:
    Session->Strategy.Open      = EmsEftpRrqStrategyOpen;
    Session->Strategy.Close     = EmsEftpRrqStrategyClose;
    Session->Strategy.HandlePkt = EmsEftpRrqStrategyHandlePkt;
    break;

  case EFTP_WRQ:
    Session->Strategy.Open      = EmsEftpWrqStrategyOpen;
    Session->Strategy.Close     = EmsEftpWrqStrategyClose;
    Session->Strategy.HandlePkt = EmsEftpWrqStrategyHandlePkt;
    break;

  default:
    goto SessionOpenError2;
  }

  if (Session->Strategy.Open (&Session->Strategy, FileName) != 0) {
    goto SessionOpenError2;

  }

  Session->SessionWaitPktEvent = CreateEvent (NULL, FALSE, FALSE, NULL);
  EmsEftpSessionPktListCreate (Session);

  /*
   * Now the session initialization is almost ready so set 
   * the Session state ESTABLISHED. before this Session can 
   * not be accessed by other thread.
   */
  Session->State = ESTABLISHED;
  if (EFI_SUCCESS != EmsCreateThread (&Thread, EmsSessionServiceThread, (VOID *) Session, NULL, NULL)) {
    goto SessionOpenError1;
  }

  Session->SessionThread = Thread;

  return 0;

SessionOpenError1:
  CloseHandle (Session->SessionWaitPktEvent);
SessionOpenError2:
  libnet_cq_remove(Session->LibnetHandler);
  libnet_destroy (Session->LibnetHandler);
SessionOpenError3:
  return -1;
}

VOID
EmsEftpSessionUnregister (
  Eftp_Session *Session
  )
/*++

Routine Description:

  Unregister an EMS Eftp session

Arguments:

  Session - The session which should be unregister

Returns:

  None

--*/
{
  Eftp_Session  **Tmp;

  Tmp = NULL;

  EmsEftpSessionOperationLock ();

  /* the process of close Session must be locked */
  EmsEftpSessionClose (Session);

  if (EftpSessionActiveListHead == Session) {
    EftpSessionActiveListHead = EftpSessionActiveListHead->Next;
  } else {
    for (Tmp = &EftpSessionActiveListHead; *Tmp && (*Tmp)->Next != Session; *Tmp = (*Tmp)->Next)
      ;
    if (*Tmp) {
      (*Tmp)->Next = (*Tmp)->Next->Next;
    }
  }

  Session->Next           = EftpSessionFreeListHead;
  EftpSessionFreeListHead = Session;
  EmsEftpSessionOperationUnlock ();
}

INT32
EmsEftpSessionRegister (
  Eftp_Session **Session,
  UINT8        *SrcMacAddr,
  UINT8        *DesMacAddr,
  UINT16       OpCode,
  INT8         *FileName
  )
/*++

Routine Description:

  Register an EMS Eftp session

Arguments:

  Session     - The session should be opened
  SrcMacAddr  - The source MAC address which is the session's attribution
  DesMacAddr  - The target MAC address which is the session's attribution
  OpCode      - The opcode of the session
  FileName    - The name of the file which the session will open

Returns:

  -1 Failure
  0  Success

--*/
{
  EmsEftpSessionOperationLock ();
  if (NULL != (*Session = EmsEftpFindSessionAccrodingMac (SrcMacAddr))) {
    printf ("The Session %d is already exists!\n", *Session - EftpSessionArray);
    EmsEftpSessionOperationUnlock ();
    return -1;
  } else {
    if (NULL == EftpSessionFreeListHead) {
      EmsEftpSessionOperationUnlock ();
      return -1;
    } else {
      *Session                  = EftpSessionFreeListHead;
      EftpSessionFreeListHead   = EftpSessionFreeListHead->Next;
      (*Session)->Next          = EftpSessionActiveListHead;
      EftpSessionActiveListHead = *Session;
    }
  }

  EmsEftpSessionOpen (*Session, SrcMacAddr, DesMacAddr, OpCode, FileName);
  EmsEftpSessionOperationUnlock ();

  return 0;
}

STATIC
VOID
EmsEftpSessionArraySetup (
  VOID
  )
/*++

Routine Description:

  Setup the array for EMS Eftp's Sessions

Arguments:

  None

Returns:

  None

--*/
{
  UINT32  Idx;

  EmsEftpSessionOperationMutex = CreateMutex (NULL, FALSE, NULL);

  for (Idx = 0; Idx < MAX_SESSION_NUM - 1; Idx++) {
    EftpSessionArray[Idx].Next = EftpSessionArray + (Idx + 1);
  }

  EftpSessionArray[MAX_SESSION_NUM - 1].Next = NULL;
}

STATIC
VOID *
EmsEftpSessionModCleanup (
  VOID *Arg
  )
/*++

Routine Description:

  Cleanup The EMS Eftp Session's private data

Arguments:

  Arg - The parameter of the routine

Returns:

  NULL

--*/
{
  EmsEftpSessionPktPoolDelete ();
  return NULL;
}

VOID
EmsEftpSessionModSetup (
  VOID
  )
/*++

Routine Description:

  enable the utility of EMS Eftp Session

Arguments:

  None

Returns:

  None

--*/
{
  EmsTclResMng  *Res;

  Res = NULL;

  EmsEftpSessionArraySetup ();
  EmsEftpSessionPktPoolCreate ();

  if (NULL == (Res = (EmsTclResMng *) malloc (sizeof (EmsTclResMng)))) {
    printf ("EmsEftpSessionModSetup malloc EmsTclResMng Failure\n");
    return ;
  }

  Res->CleanupFunc  = EmsEftpSessionModCleanup;
  Res->Res          = NULL;
  EmsTclResStackPush (Res);
}
