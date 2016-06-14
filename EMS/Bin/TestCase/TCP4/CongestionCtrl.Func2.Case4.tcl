#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
#
################################################################################
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT

#
# test case Name, category, description, GUID...
#
CaseGuid          8ED62D4E-B85D-4522-9039-9F3DF7CDE694
CaseName          CongestionCtrl.Func2.Case4
CaseCategory      TCP
CaseDescription   {This item is to test the [EUT] correctly performs the       \
                   the NewReno Modification to TCP's Fast Recovery Algorithm.  \
                   After the first fast recovery, when an ACK arrives that     \
                   acknowledges new data, this ACK is partial acknowledgements \
                   (details please refer RFC3782).}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  global RST
 
  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket TCB
 
  DestroyTcb
  DestroyPacket
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Tcp4Handle, &@R_Status"
  GetAck
 
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
  GetAck

  EndLogPacket
  EndScope _TCP4_RFC_COMPATIBILITY_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope on ENTS.
#
BeginScope _TCP4_RFC_COMPATIBILITY_

BeginLogPacket CongestionCtrl.Func2.Case4 "host $DEF_EUT_IP_ADDR and host      \
                                                $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
set    L_FragmentLength1         5120
set    L_FragmentLength2         10240

UINTN                            R_Status
UINTN                            R_Tcp4Handle
UINTN                            R_Context

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

EFI_TCP4_COMPLETION_TOKEN        R_Connect_CompletionToken
EFI_TCP4_CONNECTION_TOKEN        R_Connect_ConnectionToken

EFI_TCP4_IO_TOKEN                R_Transmit_IOToken
EFI_TCP4_COMPLETION_TOKEN        R_Transmit_CompletionToken

Packet                           R_Packet_Buffer
EFI_TCP4_TRANSMIT_DATA           R_TxData
EFI_TCP4_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer1($L_FragmentLength1)
CHAR8                            R_FragmentBuffer2($L_FragmentLength2)

#
# Initialization of TCB related on OS side.
#
CreateTcb TCB $DEF_ENTS_IP_ADDR $DEF_ENTS_PRT $DEF_EUT_IP_ADDR $DEF_EUT_PRT
BuildTcpOptions MssOption -m 512
CreatePayload OneBytePayload  Data 1  0x01

LocalEther  $DEF_ENTS_MAC_ADDR
RemoteEther $DEF_EUT_MAC_ADDR
LocalIp     $DEF_ENTS_IP_ADDR
RemoteIp    $DEF_EUT_IP_ADDR

#
# Add an entry in ARP cache.
#
AddEntryInArpCache

#
# Create Tcp4 Child.
#
Tcp4ServiceBinding->CreateChild "&@R_Tcp4Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Tcp4Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4SBP.CreateChild - Create Child 1."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure TCP instance.
#
SetVar R_Configure_AccessPoint.UseDefaultAddress      FALSE
SetIpv4Address R_Configure_AccessPoint.StationAddress $DEF_EUT_IP_ADDR
SetIpv4Address R_Configure_AccessPoint.SubnetMask     $DEF_EUT_MASK
SetVar R_Configure_AccessPoint.StationPort            $DEF_EUT_PRT
SetIpv4Address R_Configure_AccessPoint.RemoteAddress  $DEF_ENTS_IP_ADDR
SetVar R_Configure_AccessPoint.RemotePort             $DEF_ENTS_PRT
SetVar R_Configure_AccessPoint.ActiveFlag             TRUE

SetVar R_Configure_Tcp4ConfigData.TypeOfService       0
SetVar R_Configure_Tcp4ConfigData.TimeToLive          128
SetVar R_Configure_Tcp4ConfigData.AccessPoint         @R_Configure_AccessPoint
SetVar R_Configure_Tcp4ConfigData.ControlOption       0

Tcp4->Configure {&@R_Configure_Tcp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 1."                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Tcp4.Connect for an active TCP instance.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Connect_ConnectionToken.CompletionToken @R_Connect_CompletionToken
SetVar R_Connect_ConnectionToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION

Tcp4->Connect {&@R_Connect_ConnectionToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Connect - Open an active connection."                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Handles the three-way handshake.
#
ReceiveTcpPacket TCB 5

set L_TcpFlag [expr $SYN | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag -o MssOption
SendTcpPacket TCB

ReceiveTcpPacket TCB 5

#
# Call Tcp4.Transmit to transmit data segments of the first stage.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Transmit_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_TxData.Push                      FALSE
SetVar R_TxData.Urgent                    FALSE
SetVar R_TxData.DataLength                $L_FragmentLength1
SetVar R_TxData.FragmentCount             1

SetVar R_FragmentTable.FragmentLength     $L_FragmentLength1
SetVar R_FragmentTable.FragmentBuffer     &@R_FragmentBuffer1
SetVar R_TxData.FragmentTable(0)          @R_FragmentTable

SetVar R_Packet_Buffer.TxData  &@R_TxData

SetVar R_Transmit_IOToken.CompletionToken @R_Transmit_CompletionToken
SetVar R_Transmit_IOToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION
SetVar R_Transmit_IOToken.Packet_Buffer   @R_Packet_Buffer

Tcp4->Transmit {&@R_Transmit_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Transmit - Transmit a packet."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# OS get the transmitted data segments of the fist stage, then begin the
# second stage data transmission.
#
set expect_r_seq 1
set expect_r_len 512

for { set i 0} { $i < 10 } { incr i } {
  ReceiveTcpPacket TCB 5
  if { ${TCB.received} == 1 } {
    if { ${TCB.r_f_ack} != 1 } {
      set assert fail
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "EUT doesn't send out the data segment correctly."
      CleanUpEutEnvironment
      return
    } else {
        if { ${TCB.r_seq} != $expect_r_seq || ${TCB.r_ack} != 1} {
          set assert fail
          RecordAssertion $assert $GenericAssertionGuid                        \
                          "The sequence number or acknowledge number of the data\
                           segment is not correct."
          CleanUpEutEnvironment
          return
        }
        if { ${TCB.r_len} != $expect_r_len } {
         	set assert fail
          RecordAssertion $assert $GenericAssertionGuid                        \
                          "The data length of the data segment is not correct"
          CleanUpEutEnvironment
          return
        }
        set expect_r_seq [expr $expect_r_seq + $expect_r_len]
      }
    set assert pass
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "The EUT send out the data segment correctly."
  } else {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out any segment."
    CleanUpEutEnvironment
    return
  }
  UpdateTcpSendBuffer TCB -c $ACK
  SendTcpPacket TCB
}

#
# Check the token status of Tranmist interface.
#
while {1 > 0} {
  Stall 1
  GetVar R_Transmit_IOToken.CompletionToken.Status
 
  if { ${R_Transmit_IOToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Transmit_IOToken.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      RecordAssertion $assert $GenericAssertionGuid                            \
                              "Receive data segment error."                    \
                               ExpectedStatus - $EFI_SUCCESS"
      CleanUpEutEnvironment
      return
    } else {
      RecordAssertion $assert $GenericAssertionGuid                            \
                              "Receive data segment successfully."             \
                              "ReturnStatus - ${R_Transmit_IOToken.CompletionToken.Status},\
                               ExpectedStatus - $EFI_SUCCESS"
      break
    }
  }
}

#
# Call Tcp4.Transmit to transmit data segments of the second stage.
#
BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
GetAck
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Transmit_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_TxData.Push                      FALSE
SetVar R_TxData.Urgent                    FALSE
SetVar R_TxData.DataLength                $L_FragmentLength2
SetVar R_TxData.FragmentCount             1

SetVar R_FragmentTable.FragmentLength     $L_FragmentLength2
SetVar R_FragmentTable.FragmentBuffer     &@R_FragmentBuffer2
SetVar R_TxData.FragmentTable(0)          @R_FragmentTable

SetVar R_Packet_Buffer.TxData  &@R_TxData

SetVar R_Transmit_IOToken.CompletionToken        @R_Transmit_CompletionToken
SetVar R_Transmit_IOToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION
SetVar R_Transmit_IOToken.Packet_Buffer          @R_Packet_Buffer

Tcp4->Transmit {&@R_Transmit_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $CongestionCtrlFunc2AssertionGuid004                   \
                "Tcp4.Transmit - Transmit a packet."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# The cwnd should be expanded to 11*SMSS after the 1st stage data transmission.
# The second stage of data transmission includes 8192 (16*MSS) bytes data.
# Configure the OS to generate consecutive duplicate ACKs.
#
# Need to watch the packet capture result manually.
#
ReceiveTcpPacket TCB 1
UpdateTcpSendBuffer TCB -c $ACK

for { set i 0} { $i < 10 } { incr i } {
  SendTcpPacket TCB
}

set i 0
while { 0 < 1} {
  ReceiveTcpPacket TCB 0
  if { ${TCB.received} == 1 } {
    set r_ack_list($i) ${TCB.r_seq}
    incr i
    continue
  } else {
    break
  }
}

#
# Configure the OS to acknowledge the middle data segment. This kind of
# partial ACK can trigger NewReno algorithm.
#
# Observe the capture packet to check whether it follows the NewReno algorithm.
#
set temp_r_ack [expr $r_ack_list(2) + ${TCB.r_isn}]
UpdateTcpSendBuffer TCB -c $ACK -a $temp_r_ack
SendTcpPacket TCB

set temp_r_ack [expr $r_ack_list(5) + ${TCB.r_isn}]
UpdateTcpSendBuffer TCB -c $ACK -a $temp_r_ack
SendTcpPacket TCB

set temp_r_ack [expr $r_ack_list(8) + ${TCB.r_isn}]
UpdateTcpSendBuffer TCB -c $ACK -a $temp_r_ack
SendTcpPacket TCB

Stall 10
#
# Clean up the environment on EUT side.
#

CleanUpEutEnvironment
