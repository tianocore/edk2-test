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
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        BEEE9A82-5989-496A-A8F8-3F9BB8412E5F
CaseName        Configure.Func7.Case1
CaseCategory    Udp4
CaseDescription {Test the Configure Function of UDP4 - Invoke Configure() to   \
                 check if the parameter TimeToLive can effect the sending out  \
                 of the packet.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

proc CleanUpEutEnvironment {} {
  DelEntryInArpCache
  Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
  GetAck

  BS->CloseEvent "@R_Token.Event, &@R_Status"
  GetAck  

  EndCapture
  
  VifDown 0
  
  EndScope _UDP4_CONFIGURE_FUNCTION7_CASE1_
  
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# Begin scope
#
BeginScope _UDP4_CONFIGURE_FUNCTION7_CASE1_

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]
set targetip   192.168.88.1
set hostip     192.168.88.2
set subnetmask 255.255.255.0
set targetport 4000
set hostport   4000

VifUp 0 $hostip

set test_ttl   111

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_UDP4_CONFIG_DATA             R_Udp4ConfigData
UINTN                            R_Context
EFI_UDP4_COMPLETION_TOKEN        R_Token
EFI_UDP4_TRANSMIT_DATA           R_TxData
EFI_UDP4_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer(600)

#
# Add an entry in ARP cache.
#
AddEntryInArpCache

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar   [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Configure - Func - Create Child"                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Udp4ConfigData.AcceptBroadcast             TRUE
SetVar R_Udp4ConfigData.AcceptPromiscuous           FALSE
SetVar R_Udp4ConfigData.AcceptAnyPort               TRUE
SetVar R_Udp4ConfigData.AllowDuplicatePort          TRUE
SetVar R_Udp4ConfigData.TypeOfService               0
SetVar R_Udp4ConfigData.TimeToLive                  $test_ttl
SetVar R_Udp4ConfigData.DoNotFragment               TRUE
SetVar R_Udp4ConfigData.ReceiveTimeout              0
SetVar R_Udp4ConfigData.TransmitTimeout             0
SetVar R_Udp4ConfigData.UseDefaultAddress           FALSE
SetIpv4Address R_Udp4ConfigData.StationAddress      $targetip
SetIpv4Address R_Udp4ConfigData.SubnetMask          $subnetmask
SetVar R_Udp4ConfigData.StationPort                 $targetport
SetIpv4Address R_Udp4ConfigData.RemoteAddress       $hostip
SetVar R_Udp4ConfigData.RemotePort                  $hostport

#
# check point
#
Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4ConfigureFunc7AssertionGuid001                    \
                "Udp4.Configure - Func - Config Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

SetVar R_TxData.DataLength      20
SetVar R_TxData.FragmentCount   1
SetVar R_TxData.UdpSessionData  0 ;#NULL
SetVar R_TxData.GatewayAddress  0 ;#NULL

SetVar R_FragmentBuffer                 "UdpConfigureTest" 
SetVar R_FragmentTable.FragmentBuffer   &@R_FragmentBuffer
SetVar R_FragmentTable.FragmentLength   20
SetVar R_TxData.FragmentTable           @R_FragmentTable
SetVar R_Token.Packet                   &@R_TxData

set L_Filter "udp port $targetport"
StartCapture CCB $L_Filter

Udp4->Transmit {&@R_Token, &@R_Status}

ReceiveCcbPacket CCB aaa 10

if { ${CCB.received} == 0} {
  #
  # If have not captured the packet. Fail
  #
  GetAck
  GetVar R_Status
  GetVar R_Token.Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Udp4.Configure - Func - Transmit a packet"                  \
                  "Packet not captured, R_Status - $R_Status, R_Token.Status - \
                  ${R_Token.Status}"

  CleanUpEutEnvironment
  
  return
}

#
# If have captured the packet.
#
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Configure - Func - Transmit a packet"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Verify R_Token.Status
#
GetVar R_Token.Status
if {${R_Token.Status} == $EFI_SUCCESS} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Configure - Func - check R_Token.Status"                 \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"

#
# Verify the Event
#
GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Configure - Func - check Event"                          \
                "Return R_Context - $R_Context, Expected R_Context - 1"

#
# Verify the IP header in the packet
#
ParsePacket aaa -t ip -Ipv4_ttl ttl

if {$ttl == $test_ttl } {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Configure - Func - check the packet's IP header"         \
                "Actual IP TOS - $ttl,Expected IP TOS - $test_ttl"

#Stall 2
CleanUpEutEnvironment
