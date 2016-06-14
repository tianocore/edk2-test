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
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
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
CaseGuid        131b866c-94f5-43b8-b848-3ed35681a54b
CaseName        RenewRebind.Func2.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
                -- Extend Lease Time in Asynchronous Mode Using BROADCAST --   \
                sequence A.}

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
  EndScope _DHCP4_RENEWREBIND_FUNC2
  EndLog
}

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_RENEWREBIND_FUNC2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_DHCP4_CONFIG_DATA            R_ConfigData
UINT32                           R_Timeout(2)
POINTER                          R_OptionPtr
UINT8                            R_ClientIdOpt(9)
EFI_DHCP4_MODE_DATA              R_ModeData
UINTN                            R_Event
UINTN                            R_Context

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
# o	RequestRetryCount=2, RequestTimeout=5,10
# o	ClientAddress=192.168.1.1
# o	Dhcp4CallBack=NULL
# o	OptionCount=1, OptionList=ClientIdentifier
#
SetVar  R_Timeout(0)                        5
SetVar  R_Timeout(1)                        10
SetVar  R_ConfigData.DiscoverTryCount       2
SetVar  R_ConfigData.DiscoverTimeout        &@R_Timeout
SetVar  R_ConfigData.RequestTryCount        2
SetVar  R_ConfigData.RequestTimeout         &@R_Timeout
SetIpv4Address  R_ConfigData.ClientAddress  "192.168.2.4"
SetVar  R_ConfigData.Dhcp4Callback          0
SetVar  R_ConfigData.CallbackContext        0

#
# Build an option of ClientIdentifier
#
SetVar    R_ClientIdOpt                     {61 7 1 0 1 2 3 4 5}
SetVar    R_OptionPtr                       &@R_ClientIdOpt
SetVar    R_ConfigData.OptionCount          1
SetVar    R_ConfigData.OptionList           &@R_OptionPtr

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Configure Child 1"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Create Event for Dhcp4->RenewRebind.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                &@R_Event, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Start to start DHCP4 configuration process.
# o	CompletionEvnet = NULL
#
set L_Filter "udp src port 68 and ether host $targetmac"
StartCapture CCB $L_Filter

Dhcp4->Start "0, &@R_Status"

#
# "	On manager side
# Step4: Respond to DHCP Client in the following message sequence
# 1). Capture DHCPREQUEST message
#
ReceiveCcbPacket CCB RequestPacket 15
if { ${CCB.received} == 0} {
	set assert fail
  GetAck
  RecordAssertion $assert $GenericAssertionGuid                                \
                "Dhcp4.Start - No DHCPREQUEST packet Captured."
  
	CleanUpEutEnvironment 
  return
} else {
  ParsePacket RequestPacket -t dhcp -dhcp_xid xid -dhcp_htype htype            \
              -dhcp_ciaddr ciaddr -dhcp_hlen hlen  -dhcp_chaddr chaddr         \
              -dhcp_options request1_option1
  ParsePacket RequestPacket -t eth -eth_src eth_src -eth_dst eth_dst

  CreateDhcpOpt request1_opt1 mesg_type 3;    #Message Type = DHCPREQUEST
  CreateDhcpOpt request1_opt2 req_ip_addr "192.168.2.4"
  ConcatPayload request1_opt1 request1_opt1 request1_opt2
  set result1 [DhcpOptOpt request1_option1 request1_opt1]
  if {$result1 != 0} {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPREQUEST Packets"

EndCapture

#
# 2). Respond with DHCPACK message
# "	On agent side
#
LocalEther   0:3:5:6:6:7
RemoteEther  $eth_src
LocalIp      192.168.2.1

CreateDhcpOpt ack1_opt1 mesg_type 5;    #Message Type = DHCPACK
CreateDhcpOpt ack1_opt2 server_id "192.168.2.1"
CreateDhcpOpt ack1_opt3 req_ip_addr "192.168.2.4"
ConcatPayload ack1_opt1 ack1_opt1 ack1_opt2 ack1_opt3
CreatePacket  ack1 -t dhcp -dhcp_xid $xid -dhcp_op 2 -dhcp_htype $htype        \
              -dhcp_hlen $hlen -dhcp_chaddr $chaddr -dhcp_yiaddr 192.168.2.4   \
              -dhcp_options ack1_opt1
SendPacket    ack1

#
# Check ACK of Start
#
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Func - Check ACK of Start."                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check ModeData.State after configuration process complete
#
Dhcp4->GetModeData  "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State  

  if { ${R_ModeData.State} != $Dhcp4Bound } {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.GetModeData - Get Mode Date to verify the State"        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "CurState - ${R_ModeData.State}, ExpectedState - $Dhcp4Bound." \



#
# Check Point: Call [DHCP4] -> RenewRebind to extend lease time.
# o	RebindRequest = TRUE
# o	CompletionEvent = SignalEvent
# 1). Capture and validate broadcast DHCPREQUEST message
#
set L_Filter "udp src port 68 and ether host $targetmac"
StartCapture CCB $L_Filter

Dhcp4->RenewRebind "TRUE, @R_Event, &@R_Status"
GetAck

#
# Check DHCPREQUEST packet Captured
#
ReceiveCcbPacket CCB RequestPacket 15
if { ${CCB.received} == 0} {
	set assert fail
  RecordAssertion $assert $Dhcp4RenewRebindFunc2AssertionGuid001               \
                "Dhcp4.RenewRebind - No DHCPREQUEST packet Captured."          \

	CleanUpEutEnvironment 
  return
} else {
  ParsePacket   RequestPacket -t dhcp -dhcp_options request2_option1
  ParsePacket   RequestPacket -t eth -eth_src eth_src -eth_dst eth_dst
  ParsePacket   RequestPacket -t ip -ipv4_dst ip_dst
  CreateDhcpOpt request2_opt1 mesg_type 3;    #Message Type = DHCPREQUEST
  set result1 [DhcpOptOpt request2_option1 request2_opt1]
  if { $result1 != 0 } {
    set assert fail
  } else {
    if { [string compare -nocase $eth_dst "ff:ff:ff:ff:ff:ff"] != 0 } {
      set assert fail
    }
    if { [string compare -nocase $ip_dst "255.255.255.255"] != 0 } {
      set assert fail
    }
  }
}

RecordAssertion $assert $Dhcp4RenewRebindFunc2AssertionGuid001                 \
                "Dhcp4.RenewRebind - Func - Check broadcast DHCPREQUEST packet \
                in Rebind process."

#
# 2). Respond with DHCPACK
#
SendPacket  ack1
DestroyPacket

#
# Check ACK of RenewRebind
#
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar    R_Context
  if { $R_Context != 1 } {
    set assert fail
  }
}

RecordAssertion $assert $Dhcp4RenewRebindFunc2AssertionGuid001                 \
                "Dhcp4.RenewRebind - Func - Check ACK of RenewRebind."         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check ModeDate.State = Dhcp4Bound
#
Dhcp4->GetModeData  "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State  
  if { ${R_ModeData.State} != $Dhcp4Bound } {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.GetModeData - Get Mode Date to verify the State"        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "CurState - ${R_ModeData.State}, ExpectedState - $Dhcp4Bound." \

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
