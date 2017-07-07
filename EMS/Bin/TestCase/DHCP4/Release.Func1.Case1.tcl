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
# Copyright 2006 - 2017 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR> 
#
#
################################################################################
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        1f9e4a60-09b4-4b50-b268-65da75945aa5
CaseName        Release.Func1.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
	              -- in then DhcpBound State.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

proc CleanUpEutEnvironment {} {
	Dhcp4->Stop "&@R_Status"
  GetAck
  
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndCapture
  EndScope _DHCP4_RELEASE_FUNC1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_RELEASE_FUNC1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

EFI_DHCP4_CONFIG_DATA            R_ConfigData
UINT32                           R_Timeout(2)
EFI_DHCP4_MODE_DATA              R_ModeData

#
# Call [DHCP4SBP] -> CreateChild to create child.
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Call [DHCP4] -> Configure to configure this child.
# o	DiscoverRetryCount=2, DiscoverTimeout=5,10
# o	RequestRetryCount=2, RequestTimeout=5,10
# o	ClientAddress=192.168.2.4
# o	Dhcp4CallBack=NULL
# o	OptionCount=0, OptionList=NULL
#
SetVar  R_Timeout(0)                         5
SetVar  R_Timeout(1)                         10
SetVar  R_ConfigData.DiscoverTryCount        2
SetVar  R_ConfigData.DiscoverTimeout         &@R_Timeout
SetVar  R_ConfigData.RequestTryCount         2
SetVar  R_ConfigData.RequestTimeout          &@R_Timeout
SetIpv4Address  R_ConfigData.ClientAddress   "0.0.0.0"

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Conf - Configure Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Mode Data Afer Config
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State
  set tempaddr [GetIpv4Address  R_ModeData.ConfigData.ClientAddress]
  if [string compare -nocase $tempaddr "0.0.0.0"] {
    set assert fail
  } else {
    if { ${R_ModeData.State} != $Dhcp4Init } {
      set assert fail
    }
  }
  unset tempaddr
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Release - Func - CHeck IP-addr in Dhcp4InitReboot State"\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "Cur State - ${R_ModeData.State}, Expected State - $Dhcp4Init" \

#
# Call [DHCP4] -> Start to start DHCP4 configuration process.
#
set L_Filter "udp src port 68 and ether host $targetmac"
StartCapture CCB $L_Filter

Dhcp4->Start "0, &@R_Status"

ReceiveCcbPacket CCB  DiscoverPacket   15

set assert pass

if { ${CCB.received} == 0 } {
  set assert fail
  GetAck
	RecordAssertion $assert $GenericAssertionGuid                                \
                  "Dhcp4.Start - No DHCPDISCOVER packet Captured."
  
  CleanUpEutEnvironment
  return
} else {
  ParsePacket DiscoverPacket -t dhcp -dhcp_xid xid -dhcp_htype htype -dhcp_hlen\
              hlen -dhcp_chaddr chaddr -dhcp_options options
  ParsePacket DiscoverPacket -t eth -eth_src eth_src
  CreateDhcpOpt opt1 mesg_type 1;       #Message Type = DHCPDISCOVER
  set resul [DhcpOptOpt options opt1]
  if { $resul != 0} {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPDISCOVER Packets"


#
# 2). Send one | more DHCPOFFER packet to agent
#
LocalEther   0:3:5:6:6:7
RemoteEther  $eth_src
LocalIp      192.168.2.1

CreateDhcpOpt offer1_opt1 mesg_type   2;    #Message Type = DHCPOFFER
CreateDhcpOpt offer1_opt2 server_id   "192.168.2.1"
CreateDhcpOpt offer1_opt3 ip_lease_t  120
CreateDhcpOpt offer1_opt4 req_ip_addr "192.168.2.4"
CreateDhcpOpt offer1_opt5 subnet_mask "255.255.255.0"
ConcatPayload offer1_opt1 offer1_opt1 offer1_opt2 offer1_opt3 offer1_opt4 offer1_opt5
CreatePacket  offer1 -t dhcp -dhcp_xid $xid -dhcp_op 2 -dhcp_htype $htype      \
              -dhcp_hlen $hlen -dhcp_chaddr $chaddr -dhcp_yiaddr 192.168.2.4   \
              -dhcp_options offer1_opt1

SendPacket    offer1

#
# 3). Capture and validate DHCPREQUEST packet
#
ReceiveCcbPacket CCB  RequestPacket   15

set assert pass
if { ${CCB.received} == 0 } {
  set assert fail
  GetAck
	RecordAssertion $assert $GenericAssertionGuid                                \
                  "Dhcp4.Start - No DHCPREQUEST packet Captured."
  
  CleanUpEutEnvironment
  return
} else {
  ParsePacket RequestPacket -t dhcp -dhcp_options options
  CreateDhcpOpt opt1 mesg_type 3;          #Message Type = DHCPREQUEST
  set resul [DhcpOptOpt options opt1]
  if { $resul != 0} {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPREQUEST Packets"

#
# 4). Send DHCPACK packet to agent
#
CreateDhcpOpt req1_opt1 mesg_type   5;        #Message Type = DHCPACK
CreateDhcpOpt req1_opt2 server_id   "192.168.2.1"
CreateDhcpOpt req1_opt3 req_ip_addr "192.168.2.4"
ConcatPayload req1_opt1 req1_opt1 req1_opt2 req1_opt3
CreatePacket  ack -t dhcp -dhcp_xid $xid -dhcp_op 2 -dhcp_htype $htype         \
              -dhcp_hlen $hlen -dhcp_yiaddr 192.168.2.4 -dhcp_chaddr $chaddr   \
              -dhcp_options req1_opt1

SendPacket    ack
DestroyPacket

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Func - Send DHCPACK packet to the client."      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# "	On agent side
# Now, the agent has been in DHCP4Bind state.
# Check Mode Data Before Release
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State
  set tempaddr [GetIpv4Address  R_ModeData.ClientAddress]
  if [string compare -nocase $tempaddr "192.168.2.4"] {
    set assert fail
  } else {
    if { ${R_ModeData.State} != $Dhcp4Bound } {
      set assert fail
    }
  }
  unset tempaddr
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Release - Func - CHeck IP-addr in Dhcp4Bound State."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "Cur State - ${R_ModeData.State}, Expected State - $Dhcp4Bound"\

set L_Filter1 "arp and ether host $targetmac"
StartCapture CCB1 $L_Filter1


CreatePacket arprepquest -t arp -arp_hrd 0x01 -arp_pro 0x0800 -arp_hln 6       \
	           -arp_pln 4 -arp_op 0x0001 -arp_sha [GetMac] -arp_spa 192.168.2.1  \
	           -arp_tha 0:0:0:0:0:0 -arp_tpa 192.168.2.4
SendPacket   arprepquest

#
# Check Point: Call [DHCP4] -> Release in Dhcp4Bound State to release 
#              current address configuration.
#
Dhcp4->Release "&@R_Status"

#
# Check ARPREQUEST packet Captured
#
ReceiveCcbPacket CCB1 arprequest 5
if { ${CCB1.received} == 0} {
	set assert fail
	GetAck
  RecordAssertion $assert $Dhcp4RenewRebindFunc1AssertionGuid001               \
                "Dhcp4.RenewRebind - No ARPREQUEST packet Captured."           \

	CleanUpEutEnvironment 
  return
} else {
  set assert pass
  ParsePacket  arprequest -t eth -eth_src eth_src 
	CreatePacket arpreply -t arp -arp_hrd 0x01 -arp_pro 0x0800 -arp_hln 6        \
	             -arp_pln 4 -arp_op 0x0002 -arp_sha [GetMac] -arp_spa 192.168.2.1\
	             -arp_tha $eth_src -arp_tpa 192.168.2.4

	SendPacket   arpreply
}

RecordAssertion $assert $Dhcp4RenewRebindFunc1AssertionGuid001                 \
                "Dhcp4.RenewRebind - Func - Check ARPREQUEST in Renew process."

#
# Check DHCPRELEASE packet Captured
#
ReceiveCcbPacket CCB  ReleasePacket   15

set assert pass
if { ${CCB.received} == 0 } {
  set assert fail
  GetAck
	RecordAssertion $assert $GenericAssertionGuid                                \
                  "Dhcp4.Start - No DHCPRELEASE packet Captured."
  
  CleanUpEutEnvironment
  return
} else {
	CreateDhcpOpt   opt1 mesg_type 7;       #Message Type = DHCPRELEASE
  ParsePacket ReleasePacket -t dhcp -dhcp_options options
  set resul [DhcpOptOpt options opt1]
  if {$resul != 0} {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPRELEASE Packets"
#
# Check Ack of Dhcp4.Release
#
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4ReleaseFunc1AssertionGuid001                     \
                "Dhcp4.Release - Func - Check ACK in Dhcp4Bound State."        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Mode Data After Release
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State
  if { ${R_ModeData.State} != $Dhcp4Init } {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Release - Func - CHeck driver in Dhcp4Init State."      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "Cur State - ${R_ModeData.State}, Expected State - $Dhcp4Init"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment