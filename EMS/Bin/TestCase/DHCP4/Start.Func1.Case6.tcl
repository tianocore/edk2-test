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
############################################
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        ae6b5ed6-c8d5-433d-b6ce-952f33539dd0
CaseName        Start.Func1.Case6
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
	              -- Call Start in Dhcp4InitReboot State and Asynchronous Mode. -\
	              Sequence C.}

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
# o	ClientAddress=192.168.2.4
# o	Dhcp4CallBack=NULL
# o	OptionCount=0, OptionList=NULL
#
SetVar  R_Timeout(0)                           5
SetVar  R_Timeout(1)                           10
SetVar  R_ConfigData.DiscoverTryCount          2
SetVar  R_ConfigData.DiscoverTimeout           &@R_Timeout
SetVar  R_ConfigData.RequestTryCount           2
SetVar  R_ConfigData.RequestTimeout            &@R_Timeout
SetVar  R_ConfigData.Dhcp4Callback             0
SetVar  R_ConfigData.CallbackContext           0
SetIpv4Address R_ConfigData.ClientAddress      "192.168.2.4"

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
# 1).Capture and validate DHCPREQUEST packet 
# 
Dhcp4->Start "@R_Event, &@R_Status"
GetAck

ReceiveCcbPacket CCB  RequestPacket   15

set assert pass
if { ${CCB.received} == 0 } {
  set assert fail
	RecordAssertion $assert $Dhcp4StartFunc1AssertionGuid006                     \
                  "Dhcp4.Start - No RequestPacket packet Captured."
  
  CleanUpEutEnvironment
  return
} else {
  ParsePacket RequestPacket -t dhcp -dhcp_xid xid -dhcp_htype htype -dhcp_hlen\
              hlen -dhcp_chaddr chaddr -dhcp_options options
  ParsePacket RequestPacket -t eth -eth_src eth_src
  CreateDhcpOpt opt1 mesg_type 3;       #Message Type = DHCPREQUEST
  set result1 [DhcpOptOpt options opt1]
  if { $result1 != 0} {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPREQUEST Packets"

#
# 2). Send DHCPNAK packet to DHCP client
#
LocalEther   0:3:5:6:6:7
RemoteEther  $eth_src
LocalIp      192.168.2.1

CreateDhcpOpt nack1_opt1 mesg_type 6
CreateDhcpOpt nack1_opt2 server_id "192.168.2.1"
CreateDhcpOpt nack1_opt3 ip_lease_t 120
ConcatPayload nack1_opt1 nack1_opt1 nack1_opt2 nack1_opt3
CreatePacket  nack -t dhcp -dhcp_xid $xid -dhcp_op 2 -dhcp_htype $htype        \
              -dhcp_hlen $hlen -dhcp_chaddr $chaddr -dhcp_yiaddr 192.168.2.4   \
              -dhcp_options nack1_opt1

SendPacket    nack
DestroyPacket

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4StartFunc1AssertionGuid006                       \
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
  if { ${R_ModeData.State} != $Dhcp4Selecting } {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Func - Check the DHCP instance State"           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "CurState - ${R_ModeData.State}, ExpectState - $Dhcp4Selecting"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
