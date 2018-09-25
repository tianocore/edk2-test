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
CaseGuid          CB924870-E45A-433d-92A9-BF5319DE7140
CaseName          Receive.Func1.Case1
CaseCategory      TCP6
CaseDescription   {Receive must succeed with valid parameters to receive data.}
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
  EndScope _TCP6_RECEIVE_FUNC1_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _TCP6_RECEIVE_FUNC1_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context
UINTN                            R_ChildHandle

EFI_TCP6_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP6_CONFIG_DATA             R_Configure_Tcp6ConfigData

EFI_TCP6_LISTEN_TOKEN            R_Accept_ListenToken
EFI_TCP6_COMPLETION_TOKEN        R_Accept_CompletionToken

EFI_TCP6_IO_TOKEN                R_Receive_IOToken
EFI_TCP6_COMPLETION_TOKEN        R_Receive_CompletionToken

set  L_FragmentLength            64
Packet                           R_Packet_Buffer
EFI_TCP6_RECEIVE_DATA            R_RxData
EFI_TCP6_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer($L_FragmentLength)

#
# Create Child for TCP6 protocol
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
SetVar          R_Configure_AccessPoint.StationPort        6666
SetIpv6Address  R_Configure_AccessPoint.RemoteAddress      $DEF_ENTS_IP_ADDR
SetVar          R_Configure_AccessPoint.RemotePort         $DEF_ENTS_PRT
SetVar          R_Configure_AccessPoint.ActiveFlag         FALSE


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
# Check Point: Call Tcp6.Accept() with validate parameter
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Accept_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                               \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar R_Accept_ListenToken.CompletionToken @R_Accept_CompletionToken

Tcp6->Accept {&@R_Accept_ListenToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                "Tcp6.Accept - Call Accept() with valid parameter."           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

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

#
# Handle Three-Way Shake
#

#
# ENTS : SYN
#
set L_FlagAck [expr {$SYN}]
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $DEF_ENTS_PRT -tcp_dp 6666 -tcp_control $L_FlagAck -IP_ver 0x06
SendPacket P_Tcp6PacketAck -c 1

#
# EUT : SYN | ACK
#
ReceiveCcbPacket CCB L_Packet 5
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                \
                  "TCP6.Accept - No SYN|ACK sent."
  BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
ParsePacket L_Packet -t IPv6 -IPv6_payload L_Tcp6Packet
set L_Flag [lrange $L_Tcp6Packet 13 13]
puts abc0
puts $L_Flag
set L_Flag [expr {$L_Flag & 0x37}]
puts abc1
puts $L_Flag
puts abc2
puts $SYN
puts $ACK
set L_FlagCompare [expr {$SYN | $ACK}]
puts abc3
puts $L_FlagCompare

if { $L_Flag != $L_FlagCompare } {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid  \
                  "Tcp6.Accept -No SYN|ACK sent."
  BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}

#
# ENTS : ACK
#
set L_PortDst [lrange $L_Tcp6Packet 0 1]
set L_PortDst [Hex2Dec $L_PortDst]
set L_PortSrc [lrange $L_Tcp6Packet 2 3]
set L_PortSrc [Hex2Dec $L_PortSrc]
set L_Seq     [lrange $L_Tcp6Packet 4 7]
set L_AckAck  [expr {[Hex2Dec $L_Seq]+1}]
set L_Ack     [lrange $L_Tcp6Packet 8 11]
set L_SeqAck  [expr {[Hex2Dec $L_Ack]}]
set L_FlagAck [expr {$ACK}]

CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $L_PortSrc -tcp_dp $L_PortDst -tcp_control $L_FlagAck -tcp_seq $L_SeqAck -IP_ver 0x06 -tcp_ack $L_AckAck
SendPacket P_Tcp6PacketAck -c 1

#
# Transmit data for test
#
set L_FlagAck [expr {$ACK | $PSH}]
CreatePayload L_TcpPayload String 20 {HelloWorldHelloWorld}
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $L_PortSrc -tcp_dp $L_PortDst -tcp_control $L_FlagAck -tcp_seq $L_SeqAck -IP_ver 0x06 -tcp_ack $L_AckAck -tcp_payload L_TcpPayload
SendPacket P_Tcp6PacketAck -c 1

#
# Get the NewChildHandle value.
#
GetVar R_Accept_ListenToken.NewChildHandle
SetVar R_ChildHandle ${R_Accept_ListenToken.NewChildHandle}
SetVar [subst $ENTS_CUR_CHILD]  @R_ChildHandle

#
# Receive the data sent with the SYN segment.
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
# Check the Token.Status to verify the receive has been finished.
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
    RecordAssertion $assert $Tcp6ReceiveFunc1AssertionGuid002              \
                    "Receive failed (event hasn't been signaled before TIMEOUT)."      \
                    "TIMEOUT value is $L_TimeOut (sec), "
    Tcp6ServiceBinding->DestroyChild "@R_ChildHandle, &@R_Status"
    GetAck
    BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
    GetAck
	SetVar [subst $ENTS_CUR_CHILD]  @R_Handle
    CleanUpEUTEnvironmentBegin
    CleanUpEUTEnvironmentEnd
    return
  }
  incr i
}
RecordAssertion $assert $Tcp6ReceiveFunc1AssertionGuid002              \
                "Receive succeeded (event has been signaled in time."      \
                "TIMEOUT value is $L_TimeOut (sec), "

GetVar R_Receive_IOToken.CompletionToken.Status
if { ${R_Receive_IOToken.CompletionToken.Status} != $EFI_SUCCESS} {
  set assert fail
  RecordAssertion $assert $Tcp6ReceiveFunc1AssertionGuid003        \
                  "Receive failed(event status is not correct)."      \
                  "ReturnStatus - ${R_Receive_IOToken.CompletionToken.Status},\
                  ExpectedStatus - $EFI_SUCCESS"
    Tcp6ServiceBinding->DestroyChild "@R_ChildHandle, &@R_Status"
    GetAck
    BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
    GetAck
    BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
    GetAck
	SetVar [subst $ENTS_CUR_CHILD]  @R_Handle
    CleanUpEUTEnvironmentBegin
    CleanUpEUTEnvironmentEnd
  return
}
set assert pass
RecordAssertion $assert $Tcp6ReceiveFunc1AssertionGuid003        \
                "Receive succeeded (event status is modified correctly)."      \
                "ReturnStatus - ${R_Receive_IOToken.CompletionToken.Status},           \
                ExpectedStatus - $EFI_SUCCESS"

#
# Check the content of received packet
#
BS->CopyMem {&@R_RxData, @R_Receive_IOToken.Packet_Buffer.RxData, 64, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CopyMem - Copy memory."                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_RxData.DataLength
if {${R_RxData.DataLength} != 20} {
  set assert fail
  RecordAssertion $assert $Tcp6ReceiveFunc1AssertionGuid004          \
                  "Received data length is not correct."                     \
                  "expected datalength is 20, received datalength is ${R_RxData.DataLength}"
}

CHAR8 R_ReceivedString(20)
BS->CopyMem {&@R_ReceivedString, @R_RxData.FragmentTable(0).FragmentBuffer, 20, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                               \
                "BS.CopyMem - Copy memory."                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
GetVar R_ReceivedString
set L_ReceivedString [split "HelloWorldHelloWorld" {}]
set L_FailedFlag 0
for {set i 0} { $i < 20 } { incr i } {
  set L_Local [lindex $L_ReceivedString $i]
  set L_Remote $R_ReceivedString($i)
  if {[string compare $L_Local $L_Remote]!=0} {
    set L_FailedFlag 1
    break
  }
}
if { $L_FailedFlag==0 } { set assert pass }
if { $L_FailedFlag==1 } { set assert fail }
RecordAssertion $assert $Tcp6ReceiveFunc1AssertionGuid004           \
                "Tcp6.Receive - To verifiy the content of received payload."                \
                "ReturnStatus - $L_FailedFlag, ExpectedStatus - 0"

#
# Clean Up
#

#
# Destroy Child Handle
#
Tcp6ServiceBinding->DestroyChild "@R_ChildHandle, &@R_Status"
GetAck
#
# Close Event for Accept
#
BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.DestroyEvent. "                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Close Event for Receive
#
BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.DestroyEvent. "                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar [subst $ENTS_CUR_CHILD]  @R_Handle
CleanUpEUTEnvironmentBegin
CleanUpEUTEnvironmentEnd
