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
CaseGuid        0676460E-1B4A-4d68-B449-0F7E80106549
CaseName        Transmit.Func1.Case2
CaseCategory    Udp4
CaseDescription {Test the Transmit Function of UDP4 - TxData.GatewayAddress set.}
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
  
  EndScope _UDP4_TRANSMIT_FUNCTION1_CASE2_
  
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _UDP4_TRANSMIT_FUNCTION1_CASE2_

set hostmac              [GetHostMac]
set targetmac            [GetTargetMac]
set targetip             192.168.88.1
set hostip               192.168.88.2
set subnetmask           255.255.255.0
set targetport           4000
set hostport             4000
set arg_destaddrss       172.16.220.3
set arg_subnetaddrss     172.16.220.0
set arg_subnetmask       $subnetmask
set arg_gatewayaddress   $hostip

VifUp 0 $hostip

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
EFI_IPv4_ADDRESS                 R_GatewayAddress
EFI_UDP4_TRANSMIT_DATA           R_TxData
EFI_UDP4_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer(600)
EFI_UDP4_SESSION_DATA            R_SessionData

#
# Add an entry in ARP cache.
#
AddEntryInArpCache

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar   [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Transmit - Conf - Create Child"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Udp4ConfigData.AcceptBroadcast             TRUE
SetVar R_Udp4ConfigData.AcceptPromiscuous           FALSE
SetVar R_Udp4ConfigData.AcceptAnyPort               TRUE
SetVar R_Udp4ConfigData.AllowDuplicatePort          TRUE
SetVar R_Udp4ConfigData.TypeOfService               0
SetVar R_Udp4ConfigData.TimeToLive                  1
SetVar R_Udp4ConfigData.DoNotFragment               TRUE
SetVar R_Udp4ConfigData.ReceiveTimeout              0
SetVar R_Udp4ConfigData.TransmitTimeout             0
SetVar R_Udp4ConfigData.UseDefaultAddress           FALSE
SetIpv4Address R_Udp4ConfigData.StationAddress      $targetip
SetIpv4Address R_Udp4ConfigData.SubnetMask          $subnetmask
SetVar R_Udp4ConfigData.StationPort                 $targetport
SetIpv4Address R_Udp4ConfigData.RemoteAddress       $arg_destaddrss
SetVar R_Udp4ConfigData.RemotePort                  $hostport

#
#check point
#
Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Transmit - Conf - Config Child"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                                
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck
                
SetVar         R_TxData.DataLength              21
SetVar         R_TxData.FragmentCount           1
SetVar         R_FragmentBuffer                 "UdpConfigureTest" 
SetVar         R_FragmentTable.FragmentBuffer   &@R_FragmentBuffer
SetVar         R_FragmentTable.FragmentLength   21
SetVar         R_TxData.FragmentTable           @R_FragmentTable
SetVar         R_TxData.UdpSessionData          0 
SetIpv4Address R_GatewayAddress                 $hostip
SetVar         R_TxData.GatewayAddress          &@R_GatewayAddress
SetVar         R_Token.Packet                   &@R_TxData

set L_Filter "udp port $targetport"
StartCapture CCB $L_Filter

Udp4->Transmit {&@R_Token, &@R_Status}

ReceiveCcbPacket CCB TempPacket 10

if { ${CCB.received} == 0} {
  #
  # If have not captured the packet. Fail
  #
  GetAck
  GetVar R_Status
  GetVar R_Token.Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Udp4.Transmit - Func - Transmit a packet"                   \
                  "Packet not captured, R_Status - $R_Status,                  \
                   R_Token.Status - ${R_Token.Status}"

  CleanUpEutEnvironment
  
  return
}

#
# If have captured the packet.
#
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4TransmitFunc1AssertionGuid002                     \
                "Udp4.Transmit - Func - TxData.GatewayAddress set."            \
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
                "Udp4.Transmit - Func - Check R_Token.Status"                  \
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
                "Udp4.Transmit - Func - check Event"                           \
                "Return R_Context - $R_Context, Expected R_Context - 1"

#
# Verify the eth header in the packet
#
if {[ValidatePacket	TempPacket -t eth (eth_src=$targetmac)AND(eth_dst=$hostmac)]== 0 } {
  set assert pass
} else {
  set assert fail
}	
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Transmit - Func - check the packet's eth header"         \
                "Expected Source MAC - $targetmac; Expected Dest MAC - $hostmac"
                
#
# Verify the IP header in the packet
#
if {[ValidatePacket TempPacket -t ip (ipv4_src=$targetip)AND(ipv4_dst=$arg_destaddrss)]== 0 } {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Transmit - Func - check the packet's IP header"          \
                "Expected Source IP - $targetip; Expected Dest IP - $arg_destaddrss"

#
# Verify the UDP header in the packet
#
if {[ValidatePacket TempPacket -t udp (udp_sp=$targetport)AND(udp_dp=$hostport)] == 0 } {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Transmit - Func - check the packet's UDP header"         \
                "Expected Source Port - $targetport; Expected Dest Port - $hostport"
                
CleanUpEutEnvironment                             
