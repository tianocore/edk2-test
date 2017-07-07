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
CaseGuid        ffca33c1-d686-47f7-bb70-65e909657b84
CaseName        Start.Func1.Case2
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
	              -- Call Start in Dhcp4Init State and Asynchronous Mode.-       \
	              Sequence B.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

proc CleanUpEutEnvironment {} {
  Dhcp4->Stop "&@R_Status"
  GetAck

  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  BS->CloseEvent "@R_Event, &@R_Status"
  GetAck

  EndCapture
  EndScope _DHCP4_START_FUNC1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_START_FUNC1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                                           R_Status
UINTN                                           R_Handle

EFI_DHCP4_CONFIG_DATA                           R_ConfigData
UINT32                                          R_Timeout(2)

UINTN                                           R_Event
UINTN                                           R_Context

EFI_DHCP4_MODE_DATA                             R_ModeData

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
# Call [DHCP4]->Configure to initialize the child with the following parameters
# o	DiscoverRetryCount=2, DiscoverTimeout=5,10
# o	RequestRetryCount=2, RequestTimeout=1,2
# o	ClientAddress=0.0.0.0
# o	Dhcp4CallBack=NULL
# o	OptionCount=0, OptionList=NULL
#
SetVar  R_Timeout(0)                           5
SetVar  R_Timeout(1)                           10
SetVar  R_ConfigData.DiscoverTryCount          2
SetVar  R_ConfigData.DiscoverTimeout           &@R_Timeout
SetVar  R_ConfigData.RequestTryCount           2
SetVar  R_ConfigData.RequestTimeout            &@R_Timeout
SetVar  R_ConfigData.Dhcp4Callback             0;  # CallbackList[1] = Abort
SetVar  R_ConfigData.CallbackContext           0
SetVar  R_ConfigData.OptionCount               0
SetIpv4Address R_ConfigData.ClientAddress      "0.0.0.0"

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Func - Configure Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Start to start DHCP4 configuration process, 
# require Signal Event when the process complete.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                &@R_Event, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set L_Filter "udp src port 68 and ether host $targetmac"
StartCapture CCB $L_Filter

#
# Check Point: Call Dhcp4->Start to validate the configure process.
# 1).Capture and validate DHCPDISCOVER packet 
# 
Dhcp4->Start "@R_Event, &@R_Status"
GetAck

ReceiveCcbPacket CCB  DiscoverPacket   15

set assert pass
if { ${CCB.received} == 0 } {
  set assert fail
	RecordAssertion $assert $Dhcp4StartFunc1AssertionGuid002                     \
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
# 2). Send one | more DHCPOFFER packet to agent
#
LocalEther   0:3:5:6:6:7
RemoteEther  $eth_src
LocalIp      192.168.2.1

CreateDhcpOpt offer1_opt1 mesg_type   2;    #Message Type = DHCPOFFER
CreateDhcpOpt offer1_opt2 server_id   "192.168.2.1"
CreateDhcpOpt offer1_opt3 ip_lease_t  120
CreateDhcpOpt offer1_opt4 subnet_mask "255.255.255.0"
ConcatPayload offer1_opt1 offer1_opt1 offer1_opt2 offer1_opt3 offer1_opt4
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
	RecordAssertion $assert $Dhcp4StartFunc1AssertionGuid001                     \
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
# 4). Send DHCPACK packet to agent
#
CreateDhcpOpt req1_opt1 mesg_type 5;      #Message Type = DHCPACK
CreateDhcpOpt req1_opt2 server_id "192.168.2.1"
CreateDhcpOpt req1_opt3 req_ip_addr "192.168.2.4"
ConcatPayload req1_opt1 req1_opt1 req1_opt2 req1_opt3
CreatePacket  ack -t dhcp -dhcp_xid $xid -dhcp_op 2 -dhcp_htype $htype         \
              -dhcp_hlen $hlen -dhcp_yiaddr 192.168.2.4 -dhcp_chaddr $chaddr   \
              -dhcp_options req1_opt1

SendPacket  ack
DestroyPacket

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar    R_Context
  if { $R_Context != 1 } {
    set assert fail
  }
}

RecordAssertion $assert $Dhcp4StartFunc1AssertionGuid002                       \
                "Dhcp4.Start - Check the config data effect."                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Mode Data After Start Exit
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State
  set tempaddr [GetIpv4Address R_ModeData.ClientAddress]
  if { ${R_ModeData.State} != $Dhcp4Bound } {
    set assert fail
  } else {
    if { [string compare -nocase $tempaddr "192.168.2.4"] != 0 } {
      set assert fail
    }
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Func - Check the DHCP instance State"           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "CurState - ${R_ModeData.State}, ExpectState - $Dhcp4Bound     \
                CurClientAddress - $tempaddr, ExpectClientAddr - 192.168.2.4."

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
