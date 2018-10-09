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
CaseGuid        CCA4E92D-851C-4ab4-A9F4-708BE23DB3BE
CaseName        Groups.Func1.Case1
CaseCategory    MNP
CaseDescription {Test the function of MNP->Group - Call MNP.Groups () to join  \
	               a multicast group.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _MNP_GROUP_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA         R_MnpConfData
EFI_MANAGED_NETWORK_COMPLETION_TOKEN    R_Token1
EFI_MANAGED_NETWORK_TRANSMIT_DATA       R_TxData
RAW_ETH_PACKET_BODY                     R_Body
EFI_MANAGED_NETWORK_FRAGMENT_DATA       R_FragData
UINTN                                   R_Context1
EFI_MANAGED_NETWORK_COMPLETION_TOKEN    R_Token2
UINTN                                   R_Context2
EFI_MANAGED_NETWORK_RECEIVE_DATA        R_RxData
EFI_MAC_ADDRESS                         R_MacAddress
UINTN                                   R_CopyLen

#
# Send multicast packet out of EFI
#
MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Basic Func - Create Child"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar    [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Configure this child, Enable multicast
#
SetMnpConfigData R_MnpConfData 0 0 0 FALSE TRUE FALSE FALSE FALSE FALSE TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
GetVar    R_Status


#
# Get Config data  we configured
#
EFI_MAC_ADDRESS     R_DstAddress
SetEthMacAddress    R_DstAddress "01:00:5e:00:00:01"
Mnp->Groups {TRUE, &@R_DstAddress, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $MnpGroupsFunc1AssertionGuid001                        \
                "Mnp.Groups - Basic Func - Call Groups() to join a multicast   \
                group - Join 01:00:5e:00:00:01."                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar  R_MnpConfData.EnableMulticastReceive  TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Basic Func - Enable Multicast"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context1,       \
                &@R_Token1.Event, &@R_Status"
GetAck

SetEtherTestPacket R_Body "01:00:5e:00:00:01" "2:2:2:2:2:2"
SetVar R_TxData.DestinationAddress    0
SetVar R_TxData.SourceAddress         0
SetVar R_TxData.ProtocolType          0
SetVar R_TxData.HeaderLength          $ETH_HDR_LEN
SetVar R_TxData.DataLength            [expr [Sizeof R_Body]-$ETH_HDR_LEN]
SetVar R_TxData.FragmentCount         1
SetVar R_FragData.FragmentBuffer      &@R_Body
SetVar R_FragData.FragmentLength      [Sizeof R_Body]
SetVar R_TxData.FragmentTable         @R_FragData
SetVar R_Token1.Packet.TxData         &@R_TxData

set L_Filter "ether dst host 01:00:5e:00:00:01"
StartCapture CCB $L_Filter

Mnp->Transmit	{&@R_Token1, &@R_Status}

#
# Set fileter in EMS
#
ReceiveCcbPacket CCB packet1 10  
DumpPacket    packet1
ValidatePacket	packet1 -t eth (eth_src=2:2:2:2:2:2)
set assert fail
if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Basic Func - Sent Multicast packet" 

EndCapture

#
# Verify returned status
#
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Sent multicast packet - Ret Code"                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Event
#
set assert [VerifyRemoteIntVal R_Context1 1]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Basic Func - Chk Xmit Context"                   \
                "Return Context - $R_Context1, Expected Context - 1"

#
# Construct Multicast eth packet
#
LocalEther          0:1:1:1:1:1
RemoteEther         01:00:5e:00:00:01
LocalIp             172.16.220.29
RemoteIp            234.0.0.1
CreatePayload       pktpayload const 512 0x01
CreatePacket        SamplePacket1 -t udp -udp_dp 67 -udp_payload pktpayload

#
# Receive Packet	
#
#
# Empty Receive Queue
#
SetVar  R_Context2   1
GetVar  R_Context2
while { $R_Context2 == 1 } {
  SetVar          R_Context2 0
  BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context2,     \
                  &@R_Token2.Event, &@R_Status"
  GetAck
  Mnp->Receive    "&@R_Token2, &@R_Status"
  GetAck
  set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
  if { [string compare -nocase $assert "fail" ] == 0} {
    EndScope  _MNP_GROUP_FUNCTION1_CASE1_
    EndLog
    exit
  }
  GetVar          R_Context2
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Recv multicast packet - Ret Code"                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
Mnp->PollPattern1 "10, &@R_Status"

#
# Sent packet to EFI
#
SendPacket          SamplePacket1
DestroyPacket       SamplePacket1

GetAck
set assert [VerifyRemoteIntVal R_Context2 1]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Basic Func - Chk Receive Context"                \
                "Return Context - $R_Context2, Expected Context - 1"

#
# Check Destination Address
#
if { $R_Context2 == 1 } {
  SetVar R_CopyLen [Sizeof R_RxData]
  GetVar R_CopyLen
  puts $R_CopyLen
 
  BS->CopyMem {&@R_RxData, @R_Token2.Packet.RxData,@R_CopyLen, &@R_Status}
  GetAck

  SetVar R_CopyLen [Sizeof R_MacAddress]
  GetVar R_CopyLen
  puts $R_CopyLen
   
  BS->CopyMem {&@R_MacAddress, @R_RxData.DestinationAddress, @R_CopyLen,       \
  	           &@R_Status}
  GetAck
  puts "Dst MacAddress : [GetEthMacAddress R_MacAddress]"

  BS->CopyMem {&@R_MacAddress, @R_RxData.SourceAddress, @R_CopyLen, &@R_Status}
  GetAck
  puts "Src MacAddress : [GetEthMacAddress R_MacAddress]"
}


#
# Delete this group
#
Mnp->Groups "FALSE, &@R_DstAddress, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $MnpGroupsFunc1AssertionGuid002                        \
                "Mnp.Groups - Call Groups() to leave Group 01:00:5e:00:00:01." \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetEthMacAddress    R_DstAddress "01:00:5e:00:00:01"
Mnp->Groups {TRUE, &@R_DstAddress, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Basic Func - Join 01:00:5e:00:00:01"             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#                
# Leave all group
#
Mnp->Groups "FALSE, NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $MnpGroupsFunc1AssertionGuid003                        \
                "Mnp.Groups - Call Groups() to leave All Groups."              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#                
# Destroy MnpChild
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}	
GetAck

EndScope  _MNP_GROUP_FUNCTION1_CASE1_

#
# End log
#
EndLog
