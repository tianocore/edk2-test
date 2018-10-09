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
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        7f5f1abc-76ce-4ee2-9995-9bb9a1c698cf
CaseName        GetData.Conf3.Case2
CaseCategory    IP4Config
CaseDescription {This case is to test the Conformance - EFI_BUFFER_TOO_SMALL   \
                -- IpConfigData is NULL.}

################################################################################

Include IP4Config/include/Ip4Config.inc.tcl

proc CleanUpEutEnvironment {} {
  EndCapture
  EndScope _IP4CONFIG_GETDATA_CONF3
  EndLog
}

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG_GETDATA_CONF3

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_DoneContext
UINTN                            R_ReconfigContext
UINTN                            R_DoneEvent
UINTN                            R_ReconfigEvent
UINTN                            R_Ip4IpConfigDataSize
EFI_IP4_IPCONFIG_DATA            R_Ip4IpConfigData

#
# Make sure the configuration policy for the EFI IPv4 Protocol driver is not running
#
Ip4Config->Stop "&@R_Status"
GetAck

VifUp 0 172.16.210.162 255.255.255.0

#
# Create Event for DoneEvent
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_DoneContext,    \
                &@R_DoneEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Create Event for ReconfigEvent
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_ReconfigContext,\
                &@R_ReconfigEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set L_Filter "udp src port 68 and ether host $targetmac"
StartCapture CCB $L_Filter

#
# Call Ip4Config->Start to start config process.
#
Ip4Config->Start "@R_DoneEvent, @R_ReconfigEvent, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4Config.Start - Start Config"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

ReceiveCcbPacket CCB  DiscoverPacket   15

set assert pass
if { ${CCB.received} == 0 } {
  set assert fail
	RecordAssertion $assert $GenericAssertionGuid                                \
                  "Dhcp4.Start - No DHCPDISCOVER packet Captured."

  CleanUpEutEnvironment
  return
} else {
  ParsePacket DiscoverPacket -t dhcp -dhcp_xid xid -dhcp_htype htype -dhcp_hlen\
              hlen -dhcp_chaddr chaddr -dhcp_options options
  ParsePacket DiscoverPacket -t eth -eth_src eth_src
  CreateDhcpOpt opt1 mesg_type 1;       #Message Type = DHCPDISCOVER
  set result1 [DhcpOptOpt options opt1]
  if { $result1 != 0} {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPDISCOVER Packets"

#
# Send one | more DHCPOFFER packet to agent
#
LocalEther   0:3:5:6:6:7
RemoteEther  $eth_src
LocalIp      192.168.2.1

CreateDhcpOpt offer1_opt1 mesg_type   2;    #Message Type = DHCPOFFER
CreateDhcpOpt offer1_opt2 server_id   "192.168.2.1"
CreateDhcpOpt offer1_opt3 ip_lease_t  120
ConcatPayload offer1_opt1 offer1_opt1 offer1_opt2 offer1_opt3
CreatePacket  offer1 -t dhcp -dhcp_xid $xid -dhcp_op 2 -dhcp_htype $htype      \
              -dhcp_hlen $hlen -dhcp_chaddr $chaddr -dhcp_yiaddr 192.168.2.4   \
              -dhcp_options offer1_opt1

SendPacket    offer1

#
# Capture and validate DHCPREQUEST packet
#
ReceiveCcbPacket CCB  RequestPacket   15

set assert pass
if { ${CCB.received} == 0 } {
  set assert fail
	RecordAssertion $assert $GenericAssertionGuid                                \
                  "Dhcp4.Start - No DHCPREQUEST packet Captured."
  
  CleanUpEutEnvironment
  return
} else {
  ParsePacket RequestPacket -t dhcp -dhcp_options options
  CreateDhcpOpt opt1 mesg_type 3;      #Message Type = DHCPREQUEST
  set result1 [DhcpOptOpt options opt1]
  if { $result1 != 0} {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPREQUEST Packets"

#
# Send DHCPACK packet to agent
#
CreateDhcpOpt req1_opt1 mesg_type 5;      #Message Type = DHCPACK
CreateDhcpOpt req1_opt2 server_id "192.168.2.1"
CreateDhcpOpt req1_opt3 req_ip_addr "192.168.2.4"
ConcatPayload req1_opt1 req1_opt1 req1_opt2 req1_opt3
CreatePacket  ack -t dhcp -dhcp_xid $xid -dhcp_op 2 -dhcp_htype $htype         \
              -dhcp_hlen $hlen -dhcp_yiaddr 192.168.2.4 -dhcp_chaddr $chaddr   \
              -dhcp_options req1_opt1

SendPacket    ack
DestroyPacket

SetVar R_Ip4IpConfigDataSize 0

#
# Check Point: Call Ip4Config->GetData with Ip4ConfigData NULL.
#
Ip4Config->GetData "&@R_Ip4IpConfigDataSize, NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_BUFFER_TOO_SMALL]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar R_Ip4IpConfigDataSize
  puts   "****R_Ip4IpConfigDataSize: ${R_Ip4IpConfigDataSize}"
  if { ${R_Ip4IpConfigDataSize} == 0 } {
    set assert fail
  }
}

RecordAssertion $assert $Ip4ConfigGetDataConf3AssertionGuid002                 \
                "Ip4Config.GetData - Call GetData with Ip4ConfigData NULL."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_BUFFER_TOO_SMALL"

#
# Call Ip4Config->Stop to Stop configuration.
#
Ip4Config->Stop "&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4Config.Stop - Stop Config"                                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Close Event for DoneEvent
#
BS->CloseEvent "@R_DoneEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CloseEvent."                                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Close Event for ReconfigEvent
#
BS->CloseEvent "@R_ReconfigEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CloseEvent."                                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
CleanUpEutEnvironment
