# 
#  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
################################################################################
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT

#
# test case Name, category, description, GUID...
#
CaseGuid           AE444D69-F4A2-42e4-993D-A4B3B7F95A5A
CaseName           Close.Func2.Case1
CaseCategory       TCP6
CaseDescription    {The pending tokens should be signaled after a graceful close.\
 Within the case, a packet with 2 segments will be transmitted. EMS will invoke\
 Close() immediately after the first segment. ACKs for both segments will\
 be sent in order to trigger the transmitting of FIN diagram.}
################################################################################

Include Tcp6/include/Tcp6.inc.tcl

proc CleanUpEUTEnvironmentBegin {} {
  #
  # Destroy TCP6 child
  #
  Tcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck
  
  #
  # Close transmittion mechanism for EUT
  #
  EUTClose

}

proc CleanUpEUTEnvironmentEnd {} {

  DestroyPacket
  EndCapture
  EndScope _TCP6_CLOSE_FUNC2_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _TCP6_CLOSE_FUNC2_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context
UINTN                            R_Context1

EFI_TCP6_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP6_CONFIG_DATA             R_Configure_Tcp6ConfigData

EFI_TCP6_COMPLETION_TOKEN        R_Connect_CompletionToken
EFI_TCP6_CONNECTION_TOKEN        R_Connect_ConnectionToken

EFI_TCP6_IO_TOKEN                R_Transmit_IOToken
EFI_TCP6_COMPLETION_TOKEN        R_Transmit_CompletionToken

EFI_TCP6_CLOSE_TOKEN             R_Close_CloseToken
EFI_TCP6_COMPLETION_TOKEN        R_Close_CompletionToken

UINTN                            R_Configure_Tcp6ConnectionState

set  L_FragmentLength            1600
Packet                           R_Packet_Buffer
EFI_TCP6_TRANSMIT_DATA           R_TxData
EFI_TCP6_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer($L_FragmentLength)

#
# Create Tcp6 Child.
#
Tcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp6SBP.CreateChild - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure Tcp6 Instance
#
SetIpv6Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetVar          R_Configure_AccessPoint.StationPort        $DEF_EUT_PRT
SetIpv6Address  R_Configure_AccessPoint.RemoteAddress      $DEF_ENTS_IP_ADDR
SetVar          R_Configure_AccessPoint.RemotePort         $DEF_ENTS_PRT
SetVar          R_Configure_AccessPoint.ActiveFlag         TRUE


SetVar R_Configure_Tcp6ConfigData.TrafficClass        0
SetVar R_Configure_Tcp6ConfigData.HopLimit            128
SetVar R_Configure_Tcp6ConfigData.AccessPoint         @R_Configure_AccessPoint
SetVar R_Configure_Tcp6ConfigData.ControlOption       0

Tcp6->Configure {&@R_Configure_Tcp6ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                \
                "Tcp6.Configure - Call Configure() with valid config data"         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Tcp6.Connect() for an active TCP instance
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Connect_ConnectionToken.CompletionToken @R_Connect_CompletionToken

#
# Start Capture
#
set L_Filter "ether src $DEF_EUT_MAC_ADDR and tcp"
StartCapture CCB $L_Filter
#
# Setup the packet sending parameters
#
LocalIPv6           $DEF_ENTS_IP_ADDR
RemoteIPv6          $DEF_EUT_IP_ADDR
LocalEther          $DEF_ENTS_MAC_ADDR
RemoteEther         $DEF_EUT_MAC_ADDR

Tcp6->Connect {&@R_Connect_ConnectionToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp6.Connect - Open an active connection."      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Handle Three-Way Shake
#

#
# EUT : SYN
#
ReceiveCcbPacket CCB L_Packet 5
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                \
                  "TCP6.Connect - No SYN sent."

  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}

ParsePacket L_Packet -t IPv6 -IPv6_payload L_Tcp6Packet
set L_Flag [lrange $L_Tcp6Packet 13 13]
set L_Flag [expr {$L_Flag & 0x37}]
set L_Flag [format "%#04x" $L_Flag]
if {[string compare $L_Flag $SYN] != 0} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid  \
                  "Tcp6.Connect - No SYN sent."

  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
#
# ENTS : SYN | ACK
#
set L_PortDst [lrange $L_Tcp6Packet 0 1]
set L_PortDst [Hex2Dec $L_PortDst]
set L_PortSrc [lrange $L_Tcp6Packet 2 3]
set L_PortSrc [Hex2Dec $L_PortSrc]
set L_Seq     [lrange $L_Tcp6Packet 4 7]
set L_AckAck  [expr {[Hex2Dec $L_Seq]+1}]
set L_Ack     [lrange $L_Tcp6Packet 8 11]
set L_SeqAck  0 
set L_FlagAck [expr {$SYN | $ACK}]

CreatePayload L_TcpOption Data 8 0x02 0x04 0x05 0xa0 0x01 0x03 0x03 0x06
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $L_PortSrc -tcp_dp $L_PortDst -tcp_control $L_FlagAck -tcp_seq $L_SeqAck -tcp_options L_TcpOption -IP_ver 0x06 -tcp_ack $L_AckAck
SendPacket P_Tcp6PacketAck -c 1

#
# EUT : ACK
#
ReceiveCcbPacket CCB L_Packet 5
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                \
                  "TCP6.Connect - No ACK sent."

  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}

ParsePacket L_Packet -t IPv6 -IPv6_payload L_Tcp6Packet
set L_Flag [lrange $L_Tcp6Packet 13 13]
set L_Flag [expr {$L_Flag & 0x37}]
set L_Flag [format "%#04x" $L_Flag]
if {[string compare $L_Flag $ACK] != 0} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid  \
                  "Tcp6.Connect -No ACK back sent."

  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}

#
# Check Point: Call Tcp6.Transmit() to transmit a packet
#              The packet length is larger than MSS.
#

SetVar R_TxData.Push                      FALSE
SetVar R_TxData.Urgent                    FALSE
SetVar R_TxData.DataLength                $L_FragmentLength
SetVar R_TxData.FragmentCount             1

SetVar R_FragmentTable.FragmentLength     $L_FragmentLength
SetVar R_FragmentTable.FragmentBuffer     &@R_FragmentBuffer
SetVar R_TxData.FragmentTable(0)          @R_FragmentTable

SetVar R_Packet_Buffer.TxData             &@R_TxData

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context1,        \
                 &@R_Transmit_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Context1 0
SetVar R_Transmit_CompletionToken.Status  $EFI_INCOMPATIBLE_VERSION
SetVar R_Transmit_IOToken.CompletionToken @R_Transmit_CompletionToken
SetVar R_Transmit_IOToken.Packet_Buffer   @R_Packet_Buffer

Tcp6->Transmit {&@R_Transmit_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                     \
                "Tcp6.Transmit - Call Transmit() with vaild parameter."     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Receive the transmitted packet and check the token status
#
ReceiveCcbPacket CCB L_Packet 5
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                \
                  "TCP6.Transmit - No packet sent."

  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}

#
# Check Point: Call Tcp6.Close() to close a connection with valid parameters
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Close_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Close_CompletionToken.Status  $EFI_INCOMPATIBLE_VERSION
SetVar R_Close_CloseToken.CompletionToken @R_Close_CompletionToken
SetVar R_Close_CloseToken.AbortOnClose   FALSE
SetVar R_Context 0

Tcp6->Close {&@R_Close_CloseToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp6CloseFunc2AssertionGuid001                   \
                "Tcp6.Close() Call Close with valid parameters when there still pending tokens in the queue."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# 1) Because the transmit token is still pending, the graceful close cannot be executed (No
# packets sent out). 
# 2) Now, send ACK for the transmitted packets. The token will be signaled.
# 3) At this time, the graceful close could continue to finish.
#
ParsePacket L_Packet -t tcp -tcp_payload L_TcpPayload -tcp_control L_Flag -tcp_seq L_Seq -tcp_ack L_Ack
set L_Flag [format "%#04x" $L_Flag]
if {[string compare $L_Flag $ACK] != 0} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid   \
                  "Tcp6.Transmit - Flag of transmitted packet error"  \
                  "Transmitted Flag - $L_Flag, Expected Flag - $ACK"

  BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
set L_DataLength [llength $L_TcpPayload]
set L_AckAck     [expr {$L_Seq + $L_DataLength}]
set L_SeqAck     [expr {$L_Ack}]
set L_FlagAck    [expr {$ACK}]
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $L_PortSrc -tcp_dp $L_PortDst -tcp_control $L_FlagAck -IP_ver 0x06 -tcp_seq $L_SeqAck -tcp_ack $L_AckAck
SendPacket P_Tcp6PacketAck -c 1

ReceiveCcbPacket CCB L_Packet 5
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                \
                  "TCP6.Transmit - No packet sent."

  BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
ParsePacket L_Packet -t tcp -tcp_payload L_TcpPayload -tcp_control L_Flag -tcp_seq L_Seq -tcp_ack L_Ack
set L_Flag [format "%#04x" $L_Flag]
if {[string compare $L_Flag $ACK] != 0} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid   \
                  "Tcp6.Transmit - Flag of transmitted packet error"  \
                  "Transmitted Flag - $L_Flag, Expected Flag - $ACK"

  BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
set L_DataLength [llength $L_TcpPayload]
set L_AckAck     [expr {$L_Seq + $L_DataLength}]
set L_SeqAck     [expr {$L_Ack}]
set L_FlagAck    [expr {$ACK}]
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $L_PortSrc -tcp_dp $L_PortDst -tcp_control $L_FlagAck -IP_ver 0x06 -tcp_seq $L_SeqAck -tcp_ack $L_AckAck
SendPacket P_Tcp6PacketAck -c 1

#
# EMS receives the FIN packet
#

set L_RetransmitCount 0

while {1} {
  ReceiveCcbPacket CCB L_Packet 5
  if { ${CCB.received} == 0} {    
    set assert fail
    RecordAssertion $assert $Tcp6CloseFunc2AssertionGuid002              \
                    "TCP6.Close - No FIN|ACK sent."

    BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
    GetAck
    CleanUpEUTEnvironmentBegin
    CleanUpEUTEnvironmentEnd
    return
  }
  
  ParsePacket L_Packet -t IPv6 -IPv6_payload L_Tcp6Packet
  set L_Flag    [lrange $L_Tcp6Packet 13 13]
  set L_Flag    [expr {$L_Flag & 0x37}]
  set L_Flag    [format "%#04x" $L_Flag]
  set L_Seq     [lrange $L_Tcp6Packet 4 7]
  set L_Ack     [lrange $L_Tcp6Packet 8 11]

  set L_FINACK  [expr {$FIN | $ACK}]
  set L_FINACK  [format "%#04x" $L_FINACK]
  
  if {[string compare $L_Flag $L_FINACK] != 0} {
    if {$L_RetransmitCount == 10} {
      set assert fail
      RecordAssertion $assert $Tcp6CloseFunc2AssertionGuid002  \
                      "Tcp6.Close - No FIN|ACK sent."

      BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
      GetAck
      BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
      GetAck
      BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
      GetAck
      CleanUpEUTEnvironmentBegin
      CleanUpEUTEnvironmentEnd
      return
    } else {
      puts "The arriving packet might be a TCP retransmission."
      incr L_RetransmitCount 
    }
  } else {
    break
  }
}
set assert pass
RecordAssertion $assert $Tcp6CloseFunc2AssertionGuid002  \
                "Tcp6.Close - FIN|ACK is sent successfully."

#
# ENTS : Send FIN/ACK
#
set L_FlagAck [expr {$FIN|$ACK}]
set L_AckAck  [expr {[Hex2Dec $L_Seq]+1}]
set L_SeqAck  [expr {[Hex2Dec $L_Ack]}]
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $L_PortSrc -tcp_dp $L_PortDst -tcp_control $L_FlagAck -IP_ver 0x06 -tcp_seq $L_SeqAck -tcp_ack $L_AckAck
SendPacket P_Tcp6PacketAck -c 1

#
# Check the Token.Status to verify the close has been finished.
#
set i 0
set L_TimeOut 30
while {1 > 0} {
  Stall 1
  GetVar R_Context
  if { $R_Context == 1} {
    break
  } elseif { $i == $L_TimeOut } {
    set assert fail
    RecordAssertion $assert $Tcp6CloseFunc2AssertionGuid003              \
                    "Close failed (event hasn't been signaled before TIMEOUT)."      \
                    "TIMEOUT value is $L_TimeOut (sec), "

    BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
    GetAck
    CleanUpEUTEnvironmentBegin
    CleanUpEUTEnvironmentEnd
    return
  }
  incr i
}
GetVar R_Close_CloseToken.CompletionToken.Status
if { ${R_Close_CloseToken.CompletionToken.Status} != $EFI_SUCCESS} {
  set assert fail
  RecordAssertion $assert $Tcp6CloseFunc2AssertionGuid003        \
                  "Close failed(event status is not correct)."      \
                  "ReturnStatus - ${R_Close_CloseToken.CompletionToken.Status},\
                   ExpectedStatus - $EFI_SUCCESS"

  BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
set assert pass
RecordAssertion $assert $Tcp6CloseFunc2AssertionGuid003        \
                "Close succeeded (event is signaled and its status is modified correctly)."      \
                "ReturnStatus - ${R_Close_CloseToken.CompletionToken.Status},           \
                 ExpectedStatus - $EFI_SUCCESS"

Stall 5
 
#
# Check Point : Check the connection state
#
Tcp6->GetModeData {&@R_Configure_Tcp6ConnectionState,NULL,     \
                   NULL,NULL,      \
                   NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid         \
                "Tcp6 - GetModeData with valid parameters (to retrieve Tcp6ConnectionState)"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
GetVar R_Configure_Tcp6ConnectionState
if { [expr $R_Configure_Tcp6ConnectionState] != $TCS(Closed) } {
  set assert fail
  RecordAssertion $assert $Tcp6CloseFunc2AssertionGuid004         \
                  "Tcp6 - Tcp6ConnectionState error after closed "                         \
                  "ReturnState - $R_Configure_Tcp6ConnectionState, ExpectedState - $TCS(Closed)"
}

#
# Check whether the transmit token is signaled
#
GetVar R_Context1
set assert pass
if { $R_Context1 == 0 } {
  set assert fail
}
RecordAssertion $assert $Tcp6CloseFunc2AssertionGuid005         \
                "Tcp6 - After graceful close, all pending tokens are signaled."

GetVar R_Transmit_IOToken.CompletionToken.Status
puts "The Context is: $R_Context1"
puts "The Status of R_Transmit_CompletionToken is: ${R_Transmit_IOToken.CompletionToken.Status}."

#
# Clean the environment
#

BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
GetAck
BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
GetAck
BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
GetAck
CleanUpEUTEnvironmentBegin
CleanUpEUTEnvironmentEnd
