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
CaseGuid           AA8F7B93-EC7C-4323-9FC7-F31D5DE2D094
CaseName           Close.Func3.Case1
CaseCategory       TCP6
CaseDescription    {The pending tokens should be signaled after a graceful close.}
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
  EndScope _TCP6_CLOSE_FUNC3_CASE1_
  EndLog
}

proc SetUpEUTEnvironment {} {
  global ENTS_CUR_CHILD  
  #
  # Setup transmittion mechanism for EUT
  #
  EUTSetup

  #
  # Create Tcp6 Child.
  #
  Tcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
  GetAck
  SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _TCP6_CLOSE_FUNC3_CASE1_

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

EFI_TCP6_IO_TOKEN                R_Receive_IOToken
EFI_TCP6_COMPLETION_TOKEN        R_Receive_CompletionToken

set  L_FragmentLength            64
Packet                           R_Packet_Buffer
EFI_TCP6_RECEIVE_DATA            R_RxData
EFI_TCP6_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer($L_FragmentLength)

EFI_TCP6_CLOSE_TOKEN             R_Close_CloseToken
EFI_TCP6_COMPLETION_TOKEN        R_Close_CompletionToken

UINTN                            R_Configure_Tcp6ConnectionState

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
# Check Point: Call Tcp6.Receive() to receive a packet
#
SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Receive_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_FragmentTable.FragmentLength     $L_FragmentLength
SetVar R_FragmentTable.FragmentBuffer     &@R_FragmentBuffer
SetVar R_RxData.FragmentTable(0)          @R_FragmentTable
SetVar R_RxData.DataLength                $L_FragmentLength
SetVar R_RxData.FragmentCount             1

SetVar R_Packet_Buffer.RxData             &@R_RxData

SetVar R_Receive_IOToken.CompletionToken  @R_Receive_CompletionToken
SetVar R_Receive_IOToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION
SetVar R_Receive_IOToken.Packet_Buffer    @R_Packet_Buffer

Tcp6->Receive {&@R_Receive_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp6ReceiveFunc1AssertionGuid001                  \
                "Tcp6.Receive - Call Receive with valid parameters."                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Receiving Token should not be signaled before any content are sent
#
GetVar R_Context
GetVar R_Receive_IOToken.CompletionToken.Status
set assert pass
if {$R_Context != 0 || ${R_Receive_IOToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                            \
                      "The Receive Token should not be signaled before any contents are sent."

  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
RecordAssertion $assert $GenericAssertionGuid                            \
                      "The Receive Token should not be signaled before any contents are sent."

#
# Check Point: Call Tcp6.Close() to close a connection with valid parameters
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context1,        \
                 &@R_Close_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Close_CompletionToken.Status  $EFI_INCOMPATIBLE_VERSION
SetVar R_Close_CloseToken.CompletionToken @R_Close_CompletionToken
SetVar R_Close_CloseToken.AbortOnClose   FALSE
SetVar R_Context1 0

Tcp6->Close {&@R_Close_CloseToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                    \
                "Tcp6.Close() Call Close with valid parameters."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set L_RetransmitCount 0

while {1} {
  ReceiveCcbPacket CCB L_Packet 5
  if { ${CCB.received} == 0} {    
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid              \
                    "TCP6.Close - No FIN|ACK sent."

    BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
    GetAck
    CleanUpEUTEnvironmentBegin
    CleanUpEUTEnvironmentEnd
    return
  }
  
  ParsePacket L_Packet -t IPv6 -IPv6_payload L_Tcp6Packet
  set L_Flag [lrange $L_Tcp6Packet 13 13]
  set L_Flag [expr {$L_Flag & 0x37}]
  set L_Flag [format "%#04x" $L_Flag]
  set L_Seq     [lrange $L_Tcp6Packet 4 7]
  set L_Ack     [lrange $L_Tcp6Packet 8 11]

  set L_FINACK  [expr {$FIN | $ACK}]
  set L_FINACK  [format "%#04x" $L_FINACK]

  if {[string compare $L_Flag $L_FINACK] != 0} {
    if {$L_RetransmitCount == 3} {
      set assert fail
      RecordAssertion $assert $GenericAssertionGuid  \
                      "Tcp6.Close - No FIN|ACK sent."

      BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
      GetAck
      BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
      GetAck
      BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
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

#
# ENTS : Send ACK and FIN/ACK
#
set L_FlagAck [expr {$ACK|$FIN}]
set L_AckAck  [expr {[Hex2Dec $L_Seq]+1}]
set L_SeqAck  [expr {[Hex2Dec $L_Ack]}]
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $L_PortSrc -tcp_dp $L_PortDst -tcp_control $L_FlagAck -IP_ver 0x06 -tcp_seq $L_SeqAck -tcp_ack $L_AckAck
SendPacket P_Tcp6PacketAck -c 1

#
# Check whether the last ACK is sent by UEFI
#
ReceiveCcbPacket CCB L_Packet 5
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid  \
                  "Tcp6.Close - No last ACK sent."

  BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
ParsePacket L_Packet -t IPv6 -IPv6_payload L_Tcp6Packet
set L_Flag [lrange $L_Tcp6Packet 13 13]
set L_Flag [expr {$L_Flag & 0x37}]
set L_Flag [format "%#04x" $L_Flag]
set L_Seq     [lrange $L_Tcp6Packet 4 7]
set L_Ack     [lrange $L_Tcp6Packet 8 11]

set L_ACK  [expr {$ACK}]
set L_ACK  [format "%#04x" $L_ACK]

if {[string compare $L_Flag $L_ACK] != 0} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid  \
                  "Tcp6.Close - No last ACK sent."

  BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
set assert pass
RecordAssertion $assert $GenericAssertionGuid  \
                "Tcp6.Close - last ACK is sent successfully."

#
# Check the Token.Status to verify the close has been finished.
#
set i 0
set L_TimeOut 30
while {1 > 0} {
  Stall 1
  GetVar R_Context1
  if { $R_Context1 == 1} {
    break
  } elseif { $i == $L_TimeOut } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid              \
                    "Close failed (event hasn't been signaled before TIMEOUT)."      \
                    "TIMEOUT value is $L_TimeOut (sec), "

    BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
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
  RecordAssertion $assert $GenericAssertionGuid        \
                  "Close failed(event status is not correct)."      \
                  "ReturnStatus - ${R_Close_CloseToken.CompletionToken.Status},\
                  ExpectedStatus - $EFI_SUCCESS"

  BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
set assert pass
RecordAssertion $assert $GenericAssertionGuid        \
                "Close success."      \
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
  RecordAssertion $assert $GenericAssertionGuid         \
                  "Tcp6 - Tcp6ConnectionState error after closed "                         \
                  "ReturnState - $R_Configure_Tcp6ConnectionState, ExpectedState - $TCS(Closed)"
}

#
# Check Point : Check whether the pending receiving token is signaled
#
GetVar R_Context
GetVar R_Receive_IOToken.CompletionToken.Status
set assert pass
if {$R_Context != 1 || ${R_Receive_IOToken.CompletionToken.Status} == $EFI_INCOMPATIBLE_VERSION} {
  set assert fail
}
RecordAssertion $assert $Tcp6CloseFunc3AssertionGuid001                            \
                "Pending tokens should be signaled after the graceful close is called."      \
                "ReturnStatus - ${R_Receive_IOToken.CompletionToken.Status},     \
                ExpectedStatus - NOT $EFI_INCOMPATIBLE_VERSION"

#
# Clean Up
#

BS->CloseEvent {@R_Close_CompletionToken.Event, &@R_Status}
GetAck
BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
GetAck
BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
GetAck
CleanUpEUTEnvironmentBegin
CleanUpEUTEnvironmentEnd
