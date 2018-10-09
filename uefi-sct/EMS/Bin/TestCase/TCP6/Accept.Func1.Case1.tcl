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
CaseGuid          64865677-6432-4dee-80DF-14DE6173B67B
CaseName          Accept.Func1.Case1
CaseCategory      TCP6
CaseDescription   {Accept must succeed with valid parameters in passive mode.}
################################################################################

Include Tcp6/include/Tcp6.inc.tcl

proc CheckModeData {} {
  global TCS DEF_EUT_IP_ADDR DEF_EUT_MAC_ADDR DEF_EUT_PRT DEF_ENTS_IP_ADDR DEF_ENTS_MAC_ADDR DEF_ENTS_PRT
  global assert
  global R_Configure_Tcp6ConnectionState
  global R_Configure_Tcp6ConfigData
  global {R_Configure_Tcp6ConfigData.TrafficClass}
  global {R_Configure_Tcp6ConfigData.HopLimit}
  global {R_Configure_Tcp6ConfigData.ControlOption}
  global {R_Configure_Tcp6ConfigData.AccessPoint}
  global {R_Proc_AccessPoint.StationPort}
  global {R_Proc_AccessPoint.RemotePort}
  global {R_Proc_AccessPoint.ActiveFlag}
  global {R_Proc_AccessPoint.StationAddress}
  global {R_Proc_AccessPoint.RemoteAddress}
  
  EFI_TCP6_ACCESS_POINT R_Proc_AccessPoint
  UINTN R_Proc_MemSize
  UINTN R_Proc_Status
  
  GetVar  R_Configure_Tcp6ConfigData
  if { ${R_Configure_Tcp6ConfigData.TrafficClass} != 0 } {
    set assert fail
    return
  }
  if { ${R_Configure_Tcp6ConfigData.HopLimit} != 128 } {
    set assert fail
    return
  }
  if { ${R_Configure_Tcp6ConfigData.ControlOption} != 0 } {
    set assert fail
    return
  }
  
  SetVar R_Proc_MemSize  [Sizeof R_Proc_AccessPoint]
  BS->CopyMem " &@R_Proc_AccessPoint, &@R_Configure_Tcp6ConfigData.AccessPoint, @R_Proc_MemSize, &@R_Proc_Status"
  GetAck
  GetVar R_Proc_AccessPoint
  
  if { ${R_Proc_AccessPoint.RemotePort} != $DEF_ENTS_PRT } {
    set assert fail
    DelVar R_Proc_AccessPoint
    DelVar R_Proc_MemSize
    DelVar R_Proc_Status
    return
  }
  if { ${R_Proc_AccessPoint.StationPort} != 6666 } {
    set assert fail
    DelVar R_Proc_AccessPoint
    DelVar R_Proc_MemSize
    DelVar R_Proc_Status
    return
  }
  if { [string compare ${R_Proc_AccessPoint.ActiveFlag} true] != 0 } {
    set assert fail
    DelVar R_Proc_AccessPoint
    DelVar R_Proc_MemSize
    DelVar R_Proc_Status
    return
  }
  set L_Proc_Ipv6Address [GetIpv6Address {R_Proc_AccessPoint.StationAddress}]
  if { [string compare $L_Proc_Ipv6Address $DEF_EUT_IP_ADDR] != 0} {
    set assert fail
    DelVar R_Proc_AccessPoint
    DelVar R_Proc_MemSize
    DelVar R_Proc_Status
    return
  }
  set L_Proc_Ipv6Address [GetIpv6Address {R_Proc_AccessPoint.RemoteAddress}]
  if { [string compare $L_Proc_Ipv6Address $DEF_ENTS_IP_ADDR] != 0} {
    set assert fail
    DelVar R_Proc_AccessPoint
    DelVar R_Proc_MemSize
    DelVar R_Proc_Status
    return
  }
  
  DelVar R_Proc_AccessPoint
  DelVar R_Proc_MemSize
  DelVar R_Proc_Status
  return
}

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
  EndScope _TCP6_ACCEPT_FUNC1_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _TCP6_ACCEPT_FUNC1_CASE1_

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

#
# Create Child for TCP6 protocol
#
Tcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar [subst $ENTS_CUR_CHILD]    @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp6SBP.CreateChild - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure Tcp6 Instance
#
EFI_TCP6_ACCESS_POINT    R_Configure_AccessPoint
SetIpv6Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetVar          R_Configure_AccessPoint.StationPort        6666
SetIpv6Address  R_Configure_AccessPoint.RemoteAddress      $DEF_ENTS_IP_ADDR
SetVar          R_Configure_AccessPoint.RemotePort         $DEF_ENTS_PRT
SetVar          R_Configure_AccessPoint.ActiveFlag         FALSE

EFI_TCP6_CONFIG_DATA    R_Configure_Tcp6ConfigData
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
EFI_TCP6_COMPLETION_TOKEN    R_Accept_CompletionToken
SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Accept_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                               \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EFI_TCP6_LISTEN_TOKEN    R_Accept_ListenToken
SetVar R_Accept_CompletionToken.Status $EFI_INCOMPATIBLE_VERSION
SetVar R_Accept_ListenToken.CompletionToken @R_Accept_CompletionToken

Tcp6->Accept {&@R_Accept_ListenToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid001        \
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
  RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid002                \
                  "TCP6.Accept - No SYN|ACK received."
  BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
ParsePacket L_Packet -t IPv6 -IPv6_payload L_Tcp6Packet
set L_Flag [lrange $L_Tcp6Packet 13 13]
set L_Flag [expr {$L_Flag & 0x37}]
set L_FlagCompare [expr {$SYN | $ACK}]

if { $L_Flag != $L_FlagCompare } {
  set assert fail
  RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid002  \
                  "Tcp6.Accept- No SYN|ACK received."

  BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
set assert pass
RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid002                \
                "TCP6.Accept - SYN|ACK is received successfully."

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
# Check the Token.Status to verify the connection has been established.
#
set i 0
set L_TimeOut 30
while {1 > 0} {
  GetVar R_Context
  if { $R_Context == 1} {
    break
  } elseif { $i == $L_TimeOut } {
    set assert fail
    RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid003                            \
                    "Listening event hasn't been signaled before TIMEOUT."      \
                    "TIMEOUT value is $L_TimeOut (sec), "
    BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
    GetAck
    CleanUpEUTEnvironmentBegin
    CleanUpEUTEnvironmentEnd
    return
  }
  incr i
  Stall 1
}
set assert pass
RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid003                            \
                "Listening event has been signaled before TIMEOUT."      \
                "TIMEOUT value is $L_TimeOut (sec),"

GetVar R_Accept_ListenToken.CompletionToken.Status
if { ${R_Accept_ListenToken.CompletionToken.Status} != $EFI_SUCCESS} {
  set assert fail
  RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid004        \
                  "Listening event's status should be correct."      \
                  "ReturnStatus - ${R_Accept_ListenToken.CompletionToken.Status},\
                   ExpectedStatus - $EFI_SUCCESS"
  BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
set assert pass
RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid004        \
                        "Listening event's status should be correct."      \
                        "ReturnStatus - ${R_Accept_ListenToken.CompletionToken.Status},           \
                        ExpectedStatus - $EFI_SUCCESS"

#
# Get the NewChildHandle value and check its property.
#
GetVar R_Accept_ListenToken.NewChildHandle
set assert pass
if {${R_Accept_ListenToken.NewChildHandle} == 0x0} {
  set assert fail
  RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid005        \
                  "Child handle from Accept() should not be NULL."      \
                  "Return Value - ${R_Accept_ListenToken.NewChildHandle}           \
                  Expected Value - Not NULL"
  BS->CloseEvent {@R_Accept_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  return
}
RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid005        \
                "Child handle from Accept() should not be NULL."      \
                "Return Value - ${R_Accept_ListenToken.NewChildHandle}           \
                Expected Value - Not NULL"
SetVar R_ChildHandle ${R_Accept_ListenToken.NewChildHandle}
SetVar [subst $ENTS_CUR_CHILD]  @R_ChildHandle

UINT32    R_Configure_Tcp6ConnectionState
Tcp6->GetModeData {&@R_Configure_Tcp6ConnectionState, &@R_Configure_Tcp6ConfigData,     \
                   NULL,NULL,      \
                   NULL, &@R_Status}
GetAck

set assert pass
GetVar R_Configure_Tcp6ConnectionState
if {${R_Configure_Tcp6ConnectionState} != $TCS(Established)} {
  set assert fail
}
RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid006        \
                        "Child handle from Accept() should be in correct state."      \
                        "Returned Value - ${R_Configure_Tcp6ConnectionState}           \
                        Expected Value - $TCS(Established)"
set assert pass
CheckModeData
RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid007        \
                "Child handle from Accept() should be with the same configuration as its parent."

#
# Transmit data for test
#
set L_FlagAck [expr {$ACK | $PSH}]
CreatePayload L_TcpPayload String 20 {HelloWorldHelloWorld}
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $L_PortSrc -tcp_dp $L_PortDst -tcp_control $L_FlagAck -tcp_seq $L_SeqAck -IP_ver 0x06 -tcp_ack $L_AckAck -tcp_payload L_TcpPayload
SendPacket P_Tcp6PacketAck -c 1

#
# Receive the data sent with the SYN segment.
#
EFI_TCP6_COMPLETION_TOKEN    R_Receive_CompletionToken
SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Receive_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set  L_FragmentLength     64
Packet                    R_Packet_Buffer
EFI_TCP6_RECEIVE_DATA     R_RxData
EFI_TCP6_FRAGMENT_DATA    R_FragmentTable
CHAR8                     R_FragmentBuffer($L_FragmentLength)

SetVar R_FragmentTable.FragmentLength    $L_FragmentLength
SetVar R_FragmentTable.FragmentBuffer    &@R_FragmentBuffer
SetVar R_RxData.FragmentTable(0)         @R_FragmentTable
SetVar R_RxData.DataLength               $L_FragmentLength
SetVar R_RxData.FragmentCount            1

SetVar R_Packet_Buffer.RxData            &@R_RxData

EFI_TCP6_IO_TOKEN    R_Receive_IOToken
SetVar R_Receive_IOToken.CompletionToken           @R_Receive_CompletionToken
SetVar R_Receive_IOToken.CompletionToken.Status    $EFI_INCOMPATIBLE_VERSION
SetVar R_Receive_IOToken.Packet_Buffer             @R_Packet_Buffer

Tcp6->Receive {&@R_Receive_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]

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
    RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid008                            \
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
GetVar R_Receive_IOToken.CompletionToken.Status
if { ${R_Receive_IOToken.CompletionToken.Status} != $EFI_SUCCESS} {
  set assert fail
  RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid008        \
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
RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid008                  \
                "Tcp6.Receive - Call Receive with valid parameters using the returned child handle."

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
  RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid009          \
                  "Received data(length) is not correct."                     \
                  "(Expected datalength is 20, received datalength is ${R_RxData.DataLength})"
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

if { $L_FailedFlag == 0 } { set assert pass }
if { $L_FailedFlag == 1 } { set assert fail }
RecordAssertion $assert $Tcp6AcceptFunc1AssertionGuid009           \
                "Received data (content) should be correct."


Tcp6->Configure {NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                \
                "Tcp6.Configure - Call Configure() with NULL config data"         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

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
