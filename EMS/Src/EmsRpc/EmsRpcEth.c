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
  
    EmsRpcEth.c
    
Abstract:

    This file contains functions for RPC using ethernet
    Functions to implement network communication related function

--*/

#include "EmsMain.h"
#include "EmsUtilityMain.h"
#include "EmsRpcMsg.h"
#include "EmsTclInit.h"
#include "EmsRpcMain.h"
#include "EmsRpcEth.h"
#include "EmsRpcTarget.h"
#include "EmsLogUtility.h"

extern HANDLE EmsTimerMutex;
extern HANDLE EmsListenMutex;
extern INT8   *EmsInterface;

BOOLEAN       ProbAckReceived    = FALSE;
BOOLEAN       CleanupAckReceived = FALSE;

typedef struct _ETH_PACKET_STRUCT {
  UINT32  Len;
  UINT8   *Buffer;
} ETH_PACKET_T;

//
// A little tricky in the variable RecvPacket,
// because we want to enqueue the received the RIVL message to a SystemV queue
// Because SystemV Queue, 4 bytes need to fill mtype
// Hence, we leave aside 4 bytes not to fill data, len count for actual data,
// (not include 4 bytes reserved for mtype)
//
STATIC ETH_PACKET_T RecvPacket;
STATIC ETH_PACKET_T SendPacket;
__time64_t      DueTime;

STATIC UINT8    EmsMacAddr[6];
STATIC UINT8    EasMacAddr[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

STATIC UINT32   LastSendSeq;
STATIC UINT32   LastRecvSeq;
STATIC UINT32   FragSeq;
STATIC INT32    CurState;

STATIC pcap_t   *Des;
BOOLEAN         EthernetListenRun     = FALSE;
BOOLEAN         EthernetTimerRun      = FALSE;

BOOLEAN         EthernetListenRunning = FALSE;

extern DWORD    EmsIfIndex;

STATIC libnet_t *LibnetHandle = NULL;

/************************ Local Function Definition ***************************/
STATIC
INT32
GetLocalMac (
  VOID_P
  );

STATIC
INT32
AnalyzeEthHeader (
  INT32           NRead,
  INT8            *Buffer,
  INT8            *SrcMac,
  INT8            *DstMac,
  UINT16          *ProtoId
  );

STATIC
INT32
AnalyzeRivlHeader (
  INT32            NRead,
  INT8             *Buffer,
  UINT8            *OpCode,
  UINT32           *SeqId,
  BOOLEAN          *More,
  UINT16           *Offset
  );

STATIC
INT32
ReassemblePacket (
  INT32            NRead,
  INT8             *Buffer,
  BOOLEAN          More,
  INT32            SeqId,
  INT32            Offset
  );

STATIC
VOID_P
FillEtherHeader (
  INT8             *Buffer,
  INT8             *DestMac,
  UINT16           ProtId
  );

STATIC
VOID_P
FillCnlLlFlag (
  INT8             *Buffer,
  UINT32           SeqId,
  UINT8            OpCode,
  UINT16           Offset,
  BOOLEAN          More
  );

STATIC
INT32
ProcessFin (
  VOID_P
  );

STATIC
INT32
RecycleSendPacket (
  VOID_P
  );

STATIC
INT32
SendOutPacket (
  INT32       DataLen,
  INT8        *Buffer
  );

STATIC
INT32
SendOutData (
  INT32         DataLen,
  INT8          *Buffer
  );

VOID_P
HandlePacket (
  IN u_char                   *UserStr,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  );

/***********************Local Function Definition ****************************/
STATIC
INT32
SendOutAck (
  UINT32      SeqId
  )
/*++

Routine Description:

  Send an ACK packet to target machine

Arguments:

  SeqId - The sequence ID

Returns:

  -1 Failure
  0  Success

--*/
{
  UINT8 Packet[LLC_HEAD_LENGTH];

  FillCnlLlFlag (Packet, SeqId, LINK_OPERATION_DATA_ACK, 0, FALSE);

  return SendOutPacket (LLC_HEAD_LENGTH, Packet);
}

STATIC
INT32
SendOutData (
  INT32         DataLen,
  INT8          *Buffer
  )
/*++

Routine Description:

  Send a Data packet to target machine

Arguments:

  DataLen - The size of the data
  Buffer  - The buffer contain the data

Returns:

  0 Surccess

--*/
{
  UINT8       Packet[ETH_FRAME_LEN];
  INT32       Len;
  INT32       Start;
  INT32       templen;
  __time64_t  NowTime;

  Len   = DataLen;
  Start = 0;

  while (Len > 0) {
    templen = (Len > MAX_DATA_FRAME_LEN) ? MAX_DATA_FRAME_LEN : Len;
    FillCnlLlFlag (Packet, LastSendSeq, LINK_OPERATION_DATA, Start, (Len > MAX_DATA_FRAME_LEN) ? TRUE : FALSE);
    memcpy (Packet + LLC_HEAD_LENGTH, Buffer + Start, templen);
    SendOutPacket (templen + LLC_HEAD_LENGTH, Packet);
    Len -= templen;
    Start += templen;
  }
  //
  // Get current time, and Compute timeout timestamp
  //
  _time64 (&NowTime);
  DueTime = NowTime + REXMIT_INTERVAL;

  return 0;
}

STATIC
INT32
RecycleSendPacket (
  VOID_P
  )
/*++

Routine Description:

  Cancel the packet sending

Arguments:

  None

Returns:

  0 Success

--*/
{

  WaitForSingleObject (EmsTimerMutex, INFINITE);
  SendPacket.Len = 0;
  ReleaseMutex (EmsTimerMutex);
  return 0;
}

STATIC
INT32
ProcessFin (
  VOID_P
  )
/*++

Routine Description:

  enqueue incoming Fin to receive queue

Arguments:

  None

Returns:

  -1 Failure
  0  Success

--*/
{
  //
  // enqueue incoming Fin to receive queue
  //
  if (EmsMsgQSend (
        RecvPacket.Buffer,
        RecvPacket.Len,
        MSG_PRI_NORMAL
        ) < 0) {
    return -1;
  }

  return 0;
}

STATIC
INT32
AnalyzeEthHeader (
  INT32         NRead,
  INT8          *Buffer,
  INT8          *SrcMac,
  INT8          *DstMac,
  UINT16        *ProtoId
  )
/*++

Routine Description:

  Analyze the header of Ethernet packet

Arguments:

  NRead   - The number character should be read
  Buffer  - Data buffer
  SrcMac - Get the source MAC address
  DstMac - Get destinate MAC address
  ProtoId - Get the protId

Returns:

  0 Success

--*/
{
  memcpy (DstMac, Buffer, 6);
  memcpy (SrcMac, Buffer + 6, 6);
  *ProtoId = ntohs (*((UINT16 *) (Buffer + 12)));
  return 0;
}

STATIC
INT32
AnalyzeRivlHeader (
  INT32            NRead,
  INT8             *Buffer,
  UINT8            *OpCode,
  UINT32           *SeqId,
  BOOLEAN          *More,
  UINT16           *Offset
  )
/*++

Routine Description:

  Analyze RIVL packet header

Arguments:

  NRead   - The number character should be read
  Buffer  - Data buffer
  OpCode  - Get the Opcode from packet
  SeqId   - Get the Sequence ID from packet
  More    - Get the infomation about whether the packet has more data
  Offset  - Get the offset of the data

Returns:

  0

--*/
{
  EAS_RIVL_LL_FLAG  LlFlag;

  memcpy (&LlFlag, Buffer + LL_POS, sizeof (UINT64));
  *OpCode = LlFlag.Flag.OpCode;
  *SeqId  = ntohl (LlFlag.Flag.SeqId);
  *More   = LlFlag.Flag.Mf;
  *Offset = ntohs (LlFlag.Flag.Offset);

  return 0;
}

STATIC
INT32
ReassemblePacket (
  INT32            NRead,
  INT8             *Buffer,
  BOOLEAN          More,
  INT32            SeqId,
  INT32            Offset
  )
/*++

Routine Description:

  Reassemble the packet

Arguments:

  NRead   - The number character should be read
  Buffer  - Data buffer
  More    - Get the infomation about whether the packet has more data
  SeqId   - Get the Sequence ID from packet
  Offset  - Get the offset of the data

Returns:

  -1 Failure
  0  Success

--*/
{
  //
  // check frag_SeqId
  //
  if (FragSeq == 0) {
    FragSeq = SeqId;
  } else {
    if (FragSeq != SeqId) {
      RecordMessage (
        EMS_VERBOSE_LEVEL_DEFAULT,
        "EMS: Receive an fragment with ErrorExit SeqId.  Expected Id =%x, Actual Id=%x \n",
        FragSeq,
        SeqId
        );
      return -1;
    }
  }

  if (NULL == RecvPacket.Buffer) {
    return -1;
  }

  if (Offset == 0) {
    RecvPacket.Len = 0;
  }
  //
  // re-assemble all packets, assume no out-of-sequence fragment
  //
  if (RecvPacket.Len != Offset) {
    //
    // out-of-sequence packet incoming
    //
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS: Receive an out-of-sequence Packet"
      );
    return -1;
  }

  memcpy (RecvPacket.Buffer + RecvPacket.Len, Buffer + DATA_POS, (NRead - DATA_POS));
  RecvPacket.Len = RecvPacket.Len + (NRead - DATA_POS);

  return 0;
}

STATIC
INT32
SendOutPacket (
  INT32       DataLen,
  INT8        *Buffer
  )
/*++

Routine Description:

  Low level send function

Arguments:

  DataLen - The size of data which should be send
  Buffer  - The data buffer

Returns:

  -1 Failure
  0  Success

--*/
{
  libnet_ptag_t Tag;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  INT8          TempBuff[MIN_ETHERNET_PACKET_LEN];

  /*
   *  Initialize the libnet
   */
  if (NULL == LibnetHandle) {
    LibnetHandle = libnet_init (
                    LIBNET_LINK,
                    /* injection type */EmsInterface,
                    ErrBuf  /* errbuf */
                    );
    if (NULL == LibnetHandle) {
      RecordMessage (
        EMS_VERBOSE_LEVEL_DEFAULT,
        "EMS:  Fail to initial libnet. Error: %s",
        ErrBuf
        );
      return -1;
    }
  }

  if (DataLen < MIN_ETHERNET_PACKET_LEN) {
    memset (TempBuff, 0, MIN_ETHERNET_PACKET_LEN);
    memcpy (TempBuff, Buffer, DataLen);
    Tag = libnet_build_ethernet (
            EasMacAddr,
            /* ethernet destination */EmsMacAddr,
            /* ethernet source */EMS_PROTO_ID,
            /* protocol type */TempBuff,
            /* payload */MIN_ETHERNET_PACKET_LEN,
            /* payload size */LibnetHandle,
            /* libnet handle */0  /* libnet id */
            );
  } else {
    Tag = libnet_build_ethernet (
            EasMacAddr,
            /* ethernet destination */EmsMacAddr,
            /* ethernet source */EMS_PROTO_ID,
            /* protocol type */Buffer,
            /* payload */DataLen,
            /* payload size */LibnetHandle,
            /* libnet handle */0  /* libnet id */
            );
  }

  if (-1 == Tag) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS:  Fail to build libnet ethernet Tag - %a:%d",
      __FILE__,
      __LINE__
      );
    return -1;
  }

  if (-1 == libnet_write (LibnetHandle)) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS:  Fail to call libnet_write - %a:%d",
      __FILE__,
      __LINE__
      );
    return -1;
  }

  libnet_clear_packet (LibnetHandle);
  return 0;
}

STATIC
VOID_P
FillEtherHeader (
  INT8          *Buffer,
  INT8          *DestMac,
  UINT16        ProtId
  )
/*++

Routine Description:

  Fill the Ethernet packet header

Arguments:

  Buffer    - The data buffer
  DestMac  - The target machine MAC address
  ProtId    - The ProtoId

Returns:

  None

--*/
{
  memcpy (Buffer, DestMac, 6);
  memcpy (Buffer + 6, EmsMacAddr, 6);
  memcpy (Buffer + 12, &ProtId, 2);

  return ;
}

STATIC
VOID_P
FillCnlLlFlag (
  INT8               *Buffer,
  UINT32             SeqId,
  UINT8              OpCode,
  UINT16             Offset,
  BOOLEAN            More
  )
/*++

Routine Description:

  Fill the flag data

Arguments:

  Buffer  - Return the flag
  SeqId   - Sequence ID
  OpCode  - The OpCode of the packet
  Offset  - The offset of the data in packet
  More    - Whether the packet has more data packet

Returns:

  None

--*/
{
  EAS_RIVL_LL_FLAG  LlFlag;

  LlFlag.Flag.SeqId   = htonl (SeqId);
  LlFlag.Flag.OpCode  = OpCode;
  LlFlag.Flag.Offset  = htons (Offset);
  LlFlag.Flag.Rsvd    = 0;
  LlFlag.Flag.Mf      = More;

  memcpy (Buffer, &LlFlag, sizeof (LlFlag));
  return ;
}

STATIC
INT32
GetLocalMac (
  VOID_P
  )
/*++

Routine Description:

  Get the local machine MAC address

Arguments:

  None

Returns:

  -1 Failure
  0  Success

--*/
{
  PIP_ADAPTER_INFO  PInfo;

  PIP_ADAPTER_INFO  PInfoTem;
  ULONG             UlSize;

  PInfo     = NULL;
  PInfoTem  = NULL;
  UlSize    = 0;

  GetAdaptersInfo (PInfo, &UlSize);
  PInfoTem = PInfo = (PIP_ADAPTER_INFO) malloc (UlSize * sizeof (INT8));

  GetAdaptersInfo (PInfo, &UlSize);
  while (PInfo) {
    if (PInfo->Index != EmsIfIndex) {
      PInfo = PInfo->Next;
      continue;
    }

    memcpy (EmsMacAddr, PInfo->Address, 6);
    free (PInfoTem);
    return 0;
  }

  free (PInfoTem);
  return -1;
}

INT32
GetEasMac(
  INT8        *Mac
  )
/*++

Routine Description:

  Get the EAS MAC address

Arguments:

  None

Returns:

  -1 Failure
  0  Success

--*/
{
  if (NULL == Mac)
    return -1;

  memcpy (Mac, EasMacAddr, 6);

  return 0;
}

INT32
SetEasMac (
  INT8        *Mac
  )
/*++

Routine Description:

  Set the EAS MAC address

Arguments:

  Mac - The MAC address

Returns:

  -1 Failure
  0  Success

--*/
{
  if (!Mac) {
    return -1;
  }

  memcpy (EasMacAddr, Mac, 6);

  return 0;
}

/***********************Extern Function Definition ****************************/
INT32
SendRivlMessage (
  INT8        *Buffer,
  INT32       DataLen
  )
/*++

Routine Description:

  The function of sending a RIVL message

Arguments:

  Buffer  - The data buffer
  DataLen - The size of data buffer

Returns:

  0 Success

--*/
{
  LastSendSeq++;
  WaitForSingleObject (EmsTimerMutex, INFINITE);

  while (!SendPacket.Buffer) {
    Tcl_Sleep (1);
  }

  SendPacket.Len = DataLen;
  memcpy (SendPacket.Buffer, Buffer, DataLen);
  SendOutData (SendPacket.Len, SendPacket.Buffer);
  CurState = RIVL_SENDING;

  ReleaseMutex (EmsTimerMutex);
  return 0;
}

INT32
SendOutCleanup(
  UINT8         *TargetMac
  )
/*++

Routine Description:

  The function of sending a "cleanup" RIVL message

Arguments:

  Buffer  - The buffer 
  DataLen - The size of data buffer

Returns:

  0 Success

--*/
{
  UINT8            Packet[LLC_HEAD_LENGTH + sizeof(UINT64)];
  UINT32           Count = 0;
  SYSTEMTIME       Time;
  UINT64           TimeStamp = 0;

  GetSystemTime(&Time);

  FillCnlLlFlag(Packet, LastSendSeq, LINK_OPERATION_CLEANUP, 0, FALSE);
  TimeStamp  += ((UINT64)Time.wYear * 12 * 31 * 24 * 60 *60);
  TimeStamp  += ((UINT64)Time.wMonth * 31 * 24 * 60 *60);
  TimeStamp  += ((UINT64)Time.wDay * 24 * 60 *60);
  TimeStamp  += ((UINT64)Time.wHour * 60 * 60);
  TimeStamp  += ((UINT64)Time.wMinute * 60);
  TimeStamp  += Time.wSecond;
  TimeStamp  <<= 32;
  TimeStamp  += Time.wMilliseconds;

  *((UINT64 *)(Packet + LLC_HEAD_LENGTH)) = NETSWAP64(TimeStamp);

  CleanupAckReceived = FALSE;
  do
  {
    /* only 3 Cleanup packages */
    Count++;
    if(SendOutPacket(LLC_HEAD_LENGTH + sizeof(UINT64), Packet) != 0)
    {
      printf("SendOutCleanup SendOutPacket failure\n");
      return -1;
    }
    Tcl_Sleep(500);
  }while((CleanupAckReceived != TRUE) && (Count < 3));

  return ((CleanupAckReceived != TRUE) ? -1 : 0);
}

//
// query is different from data packet
// we don't guarantee the query can be sent reliably
//
INT32
SendOutProbe (
  INT8          *DestMac
  )
/*++

Routine Description:

  The function of sending a "Probe" RIVL message

Arguments:

  DestMac  - The MAC address of target machine

Returns:

  -1 Failure
  0  Success

--*/
{
  UINT8       Packet[LLC_HEAD_LENGTH];
  UINT32      Ret;
  __time64_t  Time;
  __time64_t  Time1;

  //
  // #ifdef WIN32
  //  WaitForSingleObject(ems_timer_mutex, INFINITE);
  // #endif
  //
  RpcTargetRemoveAll ();

  //
  // pack a probe packet
  //
  FillCnlLlFlag (Packet, 0, LINK_OPERATION_PROBE, 0, FALSE);

  ProbAckReceived = FALSE;

  Tcl_Sleep (2000);
  Ret = SendOutPacket (LLC_HEAD_LENGTH, Packet);

  _time64 (&Time);
  Time += 3;
  while (ProbAckReceived == FALSE) {
    _time64 (&Time1);
    if (Time < Time1) {
      break;
    }

    Tcl_Sleep (1);
  }
  return Ret;
}

DWORD
WINAPI
ResendTimeHandler (
  LPVOID lpParameter
  )
/*++

Routine Description:

  The callback function of resending packet

Arguments:

  lpParameter - The parameter of the callback function

Returns:

  0

--*/
{
  __time64_t  NowTime;
  EthernetTimerRun = TRUE;
  while (EthernetTimerRun) {

    WaitForSingleObject (EmsTimerMutex, INFINITE);
    //
    // if there's packet needed to be resent
    //
    if (SendPacket.Len > 0) {
      _time64 (&NowTime);
      if (DueTime < NowTime) {
        //
        // expired
        //
        SendOutData (SendPacket.Len, SendPacket.Buffer);
      }
    }

    ReleaseMutex (EmsTimerMutex);
    //Tcl_Sleep (1);
    Tcl_Sleep (150);
  }

  return 0;
}

DWORD
WINAPI
EthernetListen (
  LPVOID lpParameter
  )
/*++

Routine Description:

  The thread routine of capturing packet

Arguments:

  lpParameter - The parameter of the thread

Returns:

  -1 Failure
  0  Success

--*/
{
  time_t              Tick;
  struct bpf_program  Bp;
  INT8                TempFilter[100];
  INT32               Index;
  pcap_t              *AdHandle;
  INT8                ErrBuf[PCAP_ERRBUF_SIZE];

  Index = 0;
  //
  //  printf("EMS: Enter ethernet listen thread\n\r");
  //  RecordMessage (
  //    EMS_VERBOSE_LEVEL_DEFAULT,
  //    "EMS: Enter ethernet listen thread"
  //    );
  //
  // Get local mac address
  //
  if (GetLocalMac () < 0) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS:  Fail to get local MAC - %a:%d",
      __FILE__,
      __LINE__
      );
    return 0;
  }

  RecvPacket.Len    = 0;
  RecvPacket.Buffer = malloc (MAX_RIVL_MESSAGE_LEN);
  if (RecvPacket.Buffer == NULL) {
    return -1;
  }

  SendPacket.Len    = 0;
  SendPacket.Buffer = malloc (ETH_FRAME_LEN);
  if (SendPacket.Buffer == NULL) {
    free (RecvPacket.Buffer);
    RecvPacket.Buffer = NULL;
    return -1;
  }
  //
  // Reset SeqId
  //
  LastSendSeq = (UINT32)time (&Tick) % 0xffff;
  LastRecvSeq = 0;
  FragSeq     = 0;

  //
  // Enter Waiting at first
  //
  CurState = RIVL_LISTENING;

  /* Open the device */
  if ((
        AdHandle = pcap_open_live (
                    EmsInterface,         // name of the device
                    65536,                // portion of the packet to capture
                    0,                    // promiscuous mode
                    1,                    // read timeout
                    ErrBuf              // error buffer
                    )) == NULL) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS:  Fail to open adapter %s - %a:%d",
      EmsInterface,
      __FILE__,
      __LINE__
      );
    return -1;
  }

  sprintf (
    TempFilter,
    "ether proto 0x1234 and ether dst %02x:%02x:%02x:%02x:%02x:%02x",
    EmsMacAddr[0],
    EmsMacAddr[1],
    EmsMacAddr[2],
    EmsMacAddr[3],
    EmsMacAddr[4],
    EmsMacAddr[5]
    );
  if (-1 == pcap_compile (AdHandle, &Bp, TempFilter, 0, 0xFFFFFF)) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS:  Fail to complile the Packet Filter %s - %a:%d",
      TempFilter,
      __FILE__,
      __LINE__
      );
    goto ErrorExit;
  }

  if (-1 == pcap_setfilter (AdHandle, &Bp)) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS:  Fail to set Packet Filter %s - %a:%d",
      TempFilter,
      __FILE__,
      __LINE__
      );
    goto ErrorExit;
  }

  EthernetListenRun = TRUE;

  /* start the capture */
  while (EthernetListenRun) {
    EthernetListenRunning = TRUE;
    pcap_dispatch (AdHandle, 1, HandlePacket, NULL);
    Tcl_Sleep (1);
  }

  pcap_close (AdHandle);
  EthernetListenRunning = FALSE;
  return 0;
ErrorExit:
  return -1;
}

VOID_P
EthernetListenExit (
  VOID_P
  )
/*++

Routine Description:

  Stop the packet capturing

Arguments:

  None
  
Returns:

  None

--*/
{
  WaitForSingleObject (EmsListenMutex, INFINITE);
  if (RecvPacket.Buffer) {
    RecvPacket.Len = 0;
    free (RecvPacket.Buffer);
    RecvPacket.Buffer = NULL;
  }

  EthernetListenRun = FALSE;

  ReleaseMutex (EmsListenMutex);

  WaitForSingleObject (EmsTimerMutex, INFINITE);
  if (SendPacket.Buffer) {
    free (SendPacket.Buffer);
    SendPacket.Buffer = NULL;
    SendPacket.Len    = 0;
  }

  if (LibnetHandle) {
    libnet_cq_remove (LibnetHandle);
    libnet_destroy (LibnetHandle);
    LibnetHandle = NULL;
  }

  EthernetTimerRun = FALSE;
  ReleaseMutex (EmsTimerMutex);

  while (EthernetListenRunning) {
    Tcl_Sleep (1);
  }
}

VOID_P
HandlePacket (
  IN u_char                   *UserStr,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST u_char             *Packet
  )
/*++

Routine Description:

  The thread routine of handling packet

Arguments:

  UserStr - User string corresponds to user parameter of pcap_dispatch().
  PktHdr  - Packet header buffer.
  Packet  - Packet data buffer.

Returns:

  None

--*/
{

  INT32   NRead;
  INT8    Buffer[ETH_FRAME_LEN];
  UINT16  ProtId;
  UINT8   OpCode;
  UINT32  SeqId;
  BOOLEAN More;
  UINT16  Offset;
  INT8    SrcMac[6];
  INT8    DstMac[6];

  WaitForSingleObject (EmsListenMutex, INFINITE);

  memcpy (Buffer, Packet, PktHdr->len);
  NRead = PktHdr->len;

  if (NRead < LLC_HEAD_LENGTH + ETHER_HEAD_LENGTH) {
    RecordMessage (
      EMS_VERBOSE_LEVEL_DEFAULT,
      "EMS:  Receive a too short Packet from agent - %a:%d",
      __FILE__,
      __LINE__
      );
    goto Done;
  }

  if (AnalyzeEthHeader (NRead, Buffer, SrcMac, DstMac, &ProtId) != 0) {
    goto Done;
  }

  if (AnalyzeRivlHeader (NRead, Buffer, &OpCode, &SeqId, &More, &Offset) != 0) {
    goto Done;
  }
  //
  // re-assemble packet
  //
  if (ReassemblePacket (NRead, Buffer, More, SeqId, Offset) == -1) {
    RecvPacket.Len = 0;
    goto Done;
  }

  if (More) {
    //
    // need fragment
    //
    goto Done1;
  }

  switch (OpCode) {
  //
  //   1. Probe Ack  ==> collect active target
  //
  case LINK_OPERATION_PROBE_ACK:
    if (RpcTargetFindByMac (SrcMac) == NULL) {
      RpcTargetAddByMac (SrcMac);
    }

    ProbAckReceived = TRUE;
    break;
  case LINK_OPERATION_CLEANUP_ACK:
  	CleanupAckReceived = TRUE;
  	break;
  case LINK_OPERATION_DATA_ACK:
    switch (CurState) {
    case RIVL_SENDING:
      if (SeqId == LastSendSeq) {
        RecycleSendPacket ();
        CurState = RIVL_LISTENING;
      } else {
        RecordMessage (
          EMS_VERBOSE_LEVEL_NOISY,
          "EMS:  Ignore unexpected Seq %d - %a:%d",
          SeqId,
          __FILE__,
          __LINE__
          );
      }
      break;

    case RIVL_LISTENING:
      //
      // ignore resent DATA_ACK
      //
      if (SeqId != LastSendSeq) {
        RecordMessage (
          EMS_VERBOSE_LEVEL_DEFAULT,
          "EMS:  Unkown error - %a:%d %x != %x",
          __FILE__,
          __LINE__,
          SeqId,
          LastSendSeq
          );
      }
      break;

    default:
      RecordMessage (
        EMS_VERBOSE_LEVEL_DEFAULT,
        "EMS:  Unkown error - %a:%d",
        __FILE__,
        __LINE__
        );
      break;
    }
    break;

  case LINK_OPERATION_DATA:
    //
    // In EMS, Data must be FINISH message
    //
    switch (CurState) {
    case RIVL_SENDING:
    //
    // DATA_ACK lost
    //
    case RIVL_LISTENING:
      /*
       * if SeqId >  LastRecvSeq we get the packet
       * if SeqId == LastRecvSeq we resend the ack
       * if SeqId <  LastRecvSeq we lost the packet
       */
      if ((LastRecvSeq != 0) && (LastRecvSeq == SeqId))
	  {
        //
        // Duplicate Fin message
        //
        SendOutAck (SeqId);
      }
	  else if ((LastRecvSeq < SeqId) || (LastRecvSeq == 0))
	  {
        SendOutAck (SeqId);
        if (ProcessFin () == 0)
		{
          RecycleSendPacket ();
          LastRecvSeq = FragSeq;
          CurState    = RIVL_LISTENING;
        }
		else
		{
          RecordMessage (
            EMS_VERBOSE_LEVEL_DEFAULT,
            "EMS:  Unkown error - %a:%d",
            __FILE__,
            __LINE__
            );
        }
      }
      break;

    default:
      RecordMessage (
        EMS_VERBOSE_LEVEL_DEFAULT,
        "EMS:  Unkown error - %a:%d",
        __FILE__,
        __LINE__
        );
      break;
    }
    break;

  default:
    break;
  }

Done:
  RecvPacket.Len  = 0;
  FragSeq         = 0;
Done1:
  ReleaseMutex (EmsListenMutex);
  return ;
}

VOID
RestoreEmsRpcEnv(
  VOID
  )
/*++

Routine Description:

  Restore the environment of EMS rpc

Arguments:

  None

Returns:

  None

--*/
{
  LastRecvSeq = 0;
  FragSeq     = 0;
}
