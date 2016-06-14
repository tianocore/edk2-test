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
# Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR> 
#
#
################################################################################
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT

#
# test case Name, category, description, GUID...
#
CaseGuid          C1A0C7D7-E6C3-4502-977E-89395435CBED
CaseName          Receive.Conf11.Case1
CaseCategory      TCP
CaseDescription   {This case is to test the conformance - EFI_CONNECTION_FIN   \
                  -- The communication peer has closed the connection and there\
                  is no any buffered data in the receive buffer of this instance.}
################################################################################

Include TCP6/include/Tcp6.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  global RST DEF_ENTS_PRT
  set L_FlagAck [expr {$RST}]
  CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $DEF_ENTS_PRT -tcp_seq 1 -tcp_dp 6666 -tcp_control $L_FlagAck -IP_ver 0x06
  SendPacket P_Tcp6PacketAck -c 1

  Tcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck
  
  #
  # Close transmittion mechanism for EUT
  #
  EUTClose
}

proc CleanUpEutEnvironmentEnd {} {
  DestroyPacket
  EndCapture
  EndLogPacket
  EndScope _TCP6_SPEC_CONFORMANCE_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _TCP6_SPEC_CONFORMANCE_

BeginLogPacket Receive.Conf11.Case1 "host $DEF_EUT_IP_ADDR and host             \
                                             $DEF_ENTS_IP_ADDR"


#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context

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


EUTSetup

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
# Call Tcp6.Connect for an active TCP instance.
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
                "Tcp6.Connect - Open an active connection."                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Handles the three-way handshake.
#
#
# EUT : SYN
#
ReceiveCcbPacket CCB L_Packet 5
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                \
                  "TCP6.Connect - No SYN sent."
  CleanUpEUTEnvironmentBegin
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
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
  CleanUpEUTEnvironmentBegin
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
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
  CleanUpEUTEnvironmentBegin
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
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
                  "Tcp6.Connect - No ACK sent."
  CleanUpEUTEnvironmentBegin
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentEnd
  return
}

#
# Configure the [OS] to initiate the connection closing.
#
set L_FlagAck [expr $FIN | $ACK]
CreatePacket P_Tcp6PacketAckFin -t tcp -tcp_sp $DEF_ENTS_PRT -tcp_seq 1 -tcp_dp 6666 -tcp_control $L_FlagAck -IP_ver 0x06
SendPacket P_Tcp6PacketAckFin -c 1

ReceiveCcbPacket CCB L_Packet 5

if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                \
                  "TCP6.Connect - No ACK sent."
  CleanUpEUTEnvironmentBegin
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
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
                  "Tcp6.Connect - No ACK sent."
  CleanUpEUTEnvironmentBegin
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  CleanUpEUTEnvironmentEnd
  return
}

#set L_Flag [lrange $L_Tcp6Packet 8 11]
#set L_Flag [format "%#08x" $L_Flag]
#if {[string compare $L_Flag 0x00000002] != 0} {
#  set assert fail
#  RecordAssertion $assert $GenericAssertionGuid                          \
#                  "The acknowledge number of ACK segment is not correct."
#  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
#  GetAck
#    CleanUpEUTEnvironmentBegin
#  CleanUpEUTEnvironmentEnd
#  return
#}


#
# Call Tcp6.Receive to receive a packet.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Receive_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_RxData.UrgentFlag                FALSE
SetVar R_RxData.DataLength                $L_FragmentLength
SetVar R_RxData.FragmentCount             1

SetVar R_FragmentTable.FragmentLength     $L_FragmentLength
SetVar R_FragmentTable.FragmentBuffer     &@R_FragmentBuffer
SetVar R_RxData.FragmentTable(0)          @R_FragmentTable

SetVar R_Packet_Buffer.RxData  &@R_RxData

SetVar R_Receive_IOToken.CompletionToken  @R_Receive_CompletionToken
SetVar R_Receive_IOToken.Packet_Buffer    @R_Packet_Buffer
SetVar R_Receive_IOToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION
Tcp6->Receive {&@R_Receive_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_CONNECTION_FIN]
RecordAssertion $assert $Tcp6ReceiveConf11AssertionGuid001                      \
                "Tcp6.Receive - Receive a packet."                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_CONNECTION_FIN"
#
# Clean up the environment on EUT side.
#

CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
BS->CloseEvent "@R_Receive_CompletionToken.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
