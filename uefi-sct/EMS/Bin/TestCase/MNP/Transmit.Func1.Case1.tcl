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
CaseGuid        E674B6C3-4331-477c-A994-5BB1390EC476
CaseName        Transmit.Func1.Case1
CaseCategory    MNP
CaseDescription {Test Transmit function of ManagedNetwork - Call MNP.Transmit()\
	               with transmit data specified. }
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope 	_MNP_TRANSMIT_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                 R_Status
UINTN                                 R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA       R_MnpConfData
EFI_MAC_ADDRESS                       R_DstAddr
EFI_MAC_ADDRESS                       R_SrcAddr
EFI_MANAGED_NETWORK_TRANSMIT_DATA     R_TxData
EFI_MANAGED_NETWORK_FRAGMENT_DATA     R_FragData
EFI_MANAGED_NETWORK_COMPLETION_TOKEN  R_Token
RAW_ETH_PACKET_BODY                   R_Body
UINTN                                 Context

MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Create Child"                                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
SetVar          [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Configure this child
#
SetMnpConfigData R_MnpConfData 0 0 0 TRUE FALSE TRUE TRUE FALSE FALSE TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Configure"                                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Transmit 
#
#
# Send unicast packet
#
SetEthMacAddress  R_DstAddr "1:1:1:1:1:1" 
SetEthMacAddress  R_SrcAddr "2:2:2:2:2:2"
SetEtherTestPacket R_Body "1:1:1:1:1:1" "2:2:2:2:2:2"

SetVar R_TxData.DestinationAddress    &@R_DstAddr
SetVar R_TxData.SourceAddress         &@R_SrcAddr
SetVar R_TxData.ProtocolType          0x0800
SetVar R_TxData.HeaderLength          0
SetVar R_TxData.DataLength            [Sizeof R_Body]
SetVar R_TxData.FragmentCount         1
SetVar R_FragData.FragmentBuffer      &@R_Body
SetVar R_FragData.FragmentLength      [Sizeof R_Body]
SetVar R_TxData.FragmentTable         @R_FragData
SetVar R_Token.Packet.TxData          &@R_TxData

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@Context,          \
                &@R_Token.Event, &@R_Status"
GetAck

set L_Filter "ether dst host 1:1:1:1:1:1"
StartCapture CCB $L_Filter

Mnp->Transmit {&@R_Token, &@R_Status}

#
# Capture packet and verify packet 
#
ReceiveCcbPacket CCB Packet1 10

DumpPacket    Packet1
ValidatePacket Packet1 -t eth (eth_src=2:2:2:2:2:2)
set assert fail
if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
}
RecordAssertion $assert $MnpTransmitFunc1AssertionGuid001                      \
                "Mnp.Transmit - Basic Func - Validate Packet" 

#
# Check Returned status code
#
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Basic Func - Dst specified"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
#
# Check Event, Context should be 1
#
GetVar  Context
set assert pass
if {1 != $Context} {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Basic Func - Dst specified"                    \
                "Return Context - $Context, Expected Context - 1"
BS->CloseEvent  "@R_Token.Event, &@R_Status"
GetAck
      
EndCapture
      
#                
# Call transmit with optional parameter not specified
#
SetVar R_TxData.DestinationAddress    0
SetVar R_TxData.SourceAddress         0
SetVar R_TxData.ProtocolType          0
SetVar R_TxData.HeaderLength          $ETH_HDR_LEN
SetVar R_TxData.DataLength            [expr [Sizeof R_Body]-$ETH_HDR_LEN]

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@Context,          \
                &@R_Token.Event, &@R_Status"
GetAck

SetVar R_Token.Packet.TxData          &@R_TxData

set L_Filter "ether dst host 1:1:1:1:1:1"
StartCapture CCB $L_Filter

Mnp->Transmit {&@R_Token, &@R_Status}

#
# Capture packet and verify packet 
#
ReceiveCcbPacket CCB Packet2 10                 
DumpPacket    Packet2 
ValidatePacket Packet2 -t eth (eth_src=2:2:2:2:2:2)
set assert fail
if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Func - Dst not specified - Validate Packet" 

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $MnpTransmitFunc1AssertionGuid002                       \
                "Mnp.Transmit - Func - Dst not specified - Chk R_Status"       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar  R_Token
set temp1 ${R_Token.Status}
if {$temp1 == $EFI_SUCCESS} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Func - Dst not specified - Chk R_Token.Status" \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"

GetVar  Context
set assert pass
if {2 != $Context} {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Basic Func - Dst specified"                    \
                "Return Context - $Context, Expected Context - 2"

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

Mnp->Poll "&@R_Status"
GetAck

MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Basic Func - Dst specified"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndCapture
EndScope 	_MNP_TRANSMIT_FUNCTION1_CASE1_

#
# EndLog
#
EndLog
                                                                                                                                                
