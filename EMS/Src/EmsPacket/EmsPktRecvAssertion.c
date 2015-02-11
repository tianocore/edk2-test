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
  
    EmsPktRecvAssertion.c
    
Abstract:

    

--*/

#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsPktMain.h"
#include "EmsProtocols.h"
#include "EmsLogCommand.h"
#include "EmsProtoUdp.h"
#include "EmsProtoIp.h"
#include "EmsProtoEth.h"
#include "EmsPktRecvAssertion.h"
#include "EmsThread.h"

STATIC UINT32    AssertionNum               = 0;
STATIC EmsThread *EmsRecvAssertionThreadCtl = NULL;
extern EmsThread EmsGuiThreadCtl;

VOID_P
RecvAssertionTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  RecvAssertion related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  Tcl_CreateCommand (
    Interp,
    "RecvAssertionThreadStart",
    EmsRecvAssertionPkt,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
}

INT32
EmsRecvAssertionPkt (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "RecvAssertionThreadStart" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  if(EFI_SUCCESS != EmsCreateThread(
  	                            &EmsRecvAssertionThreadCtl, 
  	                            EmsRecvAssertionThread, 
  	                            NULL, 
  	                            NULL, 
  	                            NULL
  	                            ))
  {
    printf("EmsRecvAssertionPkt EmsCreateThread EmsRecvAssertionThread Failure\n");
	return TCL_ERROR;
  }

  return TCL_OK;
}

VOID
EmsRecvAssertionThread (
  VOID * Parameter
  )
/*++

Routine Description:

  The thread routine of receiving assertion message

Arguments:

  Parameter - The parameter of the thread routine

Returns:

  None

--*/
{
  ASSERTION_PACKAGE   AssertionPkt;
  INT8                ErrBuff[PCAP_ERRBUF_SIZE * 2];
  struct bpf_program  Bp;
  INT32               Res;

  printf("======Enter EmsRecvAssertionThread\n");
  if ((AssertionPkt.Capturer = pcap_open_live (
                                EmsInterface, // name of the device
                                65536,        // portion of the packet to capture
                                1,            // PCAP_OPENFLAG_PROMISCUOUS,
                                10,           // read timeout
                                ErrBuff       // error buffer
                                )) == NULL) {
    return ;
  }
  //
  // set the filter
  //
  sprintf (
    AssertionPkt.CaptureFilter,
    "udp src port %d and dst port %d",
    ASSERTION_REMOTE_PORT,
    ASSERTION_LOCAL_PORT
    );

  if (-1 == pcap_compile (AssertionPkt.Capturer, &Bp, AssertionPkt.CaptureFilter, 0, 0xFFFFFF)) {
    return ;
  }

  if (-1 == pcap_setfilter (AssertionPkt.Capturer, &Bp)) {
    return ;
  }

  AssertionPkt.ReceiveBuff  = NULL;

  Res                       = 0;

  while (1) {
    AssertionPkt.Received = 0;
    //
    // Capture the packet
    //
    Res = pcap_dispatch (AssertionPkt.Capturer, 1, EmsRecvedAssertionPkt, (UINT8 *) (&AssertionPkt));

    if (Res == 1) {
      //
      // Got a packet
      //
    }
    //
    // Sleep for a while
    //
    Tcl_Sleep (100);
  }

  pcap_close (AssertionPkt.Capturer);
}

VOID_P
EmsRecvedAssertionPkt (
  IN UINT8                    *User,
  IN CONST struct pcap_pkthdr *PktHdr,
  IN CONST UINT8              *Packet
  )
/*++

Routine Description:

  The callback routine of receive assertion packet

Arguments:

  User    - User string corresponds to user parameter of pcap_dispatch().
  PktHdr  - Packet header buffer.
  Packet  - Packet data buffer.

Returns:

  None

--*/
{
  ASSERTION_PACKAGE *AssertionPackagePtr;

  AssertionPackagePtr = (ASSERTION_PACKAGE *) User;

  if (AssertionPackagePtr->ReceiveBuff) {
    free (AssertionPackagePtr->ReceiveBuff);
  }

  AssertionPackagePtr->ReceiveBuff = malloc (PktHdr->len);

  memcpy (AssertionPackagePtr->ReceiveBuff, Packet, PktHdr->len);

  AssertionPackagePtr->ReceiveLen = PktHdr->len;

  AssertionPackagePtr->Received   = 1;

  AssertionNum++;

  EmsParseAssertionPkt (AssertionPackagePtr);

}

INT32
EmsParseAssertionPkt (
  ASSERTION_PACKAGE *AssertionPackagePtr
  )
/*++

Routine Description:

  Parse the assertion packet

Arguments:

  AssertionPackagePtr - The pointer to the assertion packet

Returns:

  -1 Failure
  0  Success

--*/
{
  UINT8   *AssertionPkt;
  UINT32  Length;
  UINT8   TestcaseMacAddrBuf[PRINT_MAC_STRING_LEN];
  UINT8   TestcaseGuidBuf[PRINT_GUID_STRING_LEN];
  UINT8   TestcaseTypeBuf[PRINT_TYPE_STRING_LEN];
  UINT8   TestcaseResultBuf[PRINT_RESULT_STRING_LEN];
  UINT8   TestcaseDescriptionBuf[PRINT_DISC_STRING_LEN];
  UINT8   MessageBuf[20 + PRINT_MAC_STRING_LEN + PRINT_GUID_STRING_LEN + PRINT_RESULT_STRING_LEN + PRINT_DISC_STRING_LEN];
  UINT8   *TmpPtr1;
  UINT8   *TmpPtr2;
  INT8    CmdString[128];

  if (NULL == AssertionPackagePtr->ReceiveBuff) {
    return -1;
  }

  Length = AssertionPackagePtr->ReceiveLen;

  if (Length < (sizeof (UDP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
    return -1;
  }

  AssertionPackagePtr->ReceiveBuff[Length - 1] = '\0';

  AssertionPkt = (UINT8 *) (AssertionPackagePtr->ReceiveBuff + sizeof (ETH_HEADER) + sizeof (IP_HEADER) + sizeof (UDP_HEADER));

  /*
   * get MAC
   */
  TmpPtr1   = AssertionPkt + 1;
  TmpPtr2   = strchr (TmpPtr1, '|');
  *TmpPtr2  = '\0';
  memset (TestcaseMacAddrBuf, 0x0, sizeof (TestcaseMacAddrBuf));
  sprintf (TestcaseMacAddrBuf, "From Mac: %s", TmpPtr1);

  /*
   * get Type
   */
  TmpPtr1   = TmpPtr2 + 1;
  TmpPtr2   = strchr(TmpPtr1, '|');
  *TmpPtr2  = '\0';
  memset(TestcaseTypeBuf, 0x0, sizeof(TestcaseTypeBuf));
  sprintf(TestcaseTypeBuf, "%s", TmpPtr1);

  /*
   * get GUID
   */
  TmpPtr1   = TmpPtr2 + 1;
  TmpPtr2   = strchr (TmpPtr1, '|');
  *TmpPtr2  = '\0';
  memset (TestcaseGuidBuf, 0x0, sizeof (TestcaseGuidBuf));
  sprintf (TestcaseGuidBuf, "%s", TmpPtr1);

  /*
   * get Result
   */
  TmpPtr1   = TmpPtr2 + 1;
  TmpPtr2   = strchr (TmpPtr1, '|');
  *TmpPtr2  = '\0';
  memset (TestcaseResultBuf, 0x0, sizeof (TestcaseResultBuf));
  sprintf (TestcaseResultBuf, "%s", TmpPtr1);

  /*
   * get Description
   */
  TmpPtr1 = TmpPtr2 + 1;
  memset (TestcaseDescriptionBuf, 0x0, sizeof (TestcaseDescriptionBuf));
  sprintf (TestcaseDescriptionBuf, "%s", TmpPtr1);

  //
  // Integration all the information that will be displayed in the status bar
  //
  memset (MessageBuf, 0x0, sizeof (MessageBuf));

  if(_stricmp(TestcaseTypeBuf, "CASE_BEGN") == 0)
  {
    sprintf(CmdString, "RemoteExecutionSetResultBegin %s", TestcaseGuidBuf);
    ThreadCommand(&EmsGuiThreadCtl, CmdString, CMD_WAIT, NULL);
    ThreadCommand(&EmsGuiThreadCtl, "update", CMD_WAIT, NULL);
  }
  if(_stricmp(TestcaseTypeBuf, "CASE_OVER") == 0)
  {
    sprintf(CmdString, "RemoteExecutionSetResultEnd %s \"%s\"", TestcaseGuidBuf, TestcaseDescriptionBuf);
    ThreadCommand(&EmsGuiThreadCtl, CmdString, CMD_WAIT, NULL);
    ThreadCommand(&EmsGuiThreadCtl, "update", CMD_WAIT, NULL);
  }


  sprintf (
          MessageBuf,
          "EmsShowStatus {%s %s %s %s}",
          TestcaseMacAddrBuf,
          TestcaseGuidBuf,
          TestcaseResultBuf,
          TestcaseDescriptionBuf
          );

  EmsShowAssertion (MessageBuf);

  return 0;
}

INT32
EmsShowAssertion (
  UINT8 *MessageBuf
  )
/*++

Routine Description:

  Show the Assertion

Arguments:

  MessageBuf  - The data of the message to show

Returns:

  0

--*/
{
  ThreadCommand(&EmsGuiThreadCtl, MessageBuf, CMD_NOWAIT, NULL);
  ThreadCommand(&EmsGuiThreadCtl, MessageBuf, CMD_NOWAIT, NULL);
  return 0;
}
