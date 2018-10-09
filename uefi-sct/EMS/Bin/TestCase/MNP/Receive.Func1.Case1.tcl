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
CaseGuid        227C7C26-4762-4bee-B79C-02BF63182548
CaseName        Receive.Func1.Case1
CaseCategory    MNP
CaseDescription {Test Receive function of MNP - Call MNP.Receive() to place an \
	               asynchronous receiving request into the receiving queue.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _MNP_RECEIVE_FUNCTION1_CASE1_

set hostmac   [GetHostMac]
set targetmac [GetTargetMac]

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                     R_Status
UINTN                                     R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA           R_MnpConfData
EFI_MANAGED_NETWORK_COMPLETION_TOKEN      R_Token
EFI_MANAGED_NETWORK_RECEIVE_DATA          R_RxData
UINTN                                     R_Context
UINTN                                     R_CopyLen
EFI_MAC_ADDRESS                           R_DestinationAddress

#
# Create child handle
#
MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Receive - Basic Func - Create"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar          [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Configure this child, Enable backgroud polling, Enable broadcast receiving.
#
SetMnpConfigData R_MnpConfData 0 0 0 TRUE FALSE FALSE FALSE FALSE FALSE TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Receive - Basic Func - Configure"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Receive function
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent - Create Event."                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Mnp->Receive {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Receive - Place an asychronous receiving request"         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Construct eth packet : BroadCast packet
#
LocalEther          $hostmac
RemoteEther         $targetmac
LocalIp             172.16.220.29
RemoteIp            172.16.220.49
CreatePayload       aaa const 512 0x01
CreatePacket        Sample1 -t udp -udp_dp 67 -udp_payload aaa

#
# Send packet
#
SendPacket          Sample1

GetVar  R_Token.Status
set assert pass
if {$EFI_SUCCESS != ${R_Token.Status}} {
  set assert fail
}
RecordAssertion $assert $MnpReceiveFunc1AssertionGuid001                       \
                "Mnp.Receive - Basic Func - Call Receive() to place an         \
                 asynchronous receiving request into the receiving queue."     \
                "Return R_Token.Status - ${R_Token.Status} Expected $EFI_SUCCESS"

SetVar R_CopyLen [Sizeof R_RxData]
GetVar R_CopyLen
puts   $R_CopyLen

BS->CopyMem {&@R_RxData, @R_Token.Packet.RxData, @R_CopyLen, &@R_Status}
GetAck

SetVar R_CopyLen [Sizeof R_DestinationAddress]
GetVar R_CopyLen
puts   $R_CopyLen

BS->CopyMem {&@R_DestinationAddress, @R_RxData.DestinationAddress, @R_CopyLen, \
  	         &@R_Status}
GetAck

set DestinationAddress [GetEthMacAddress R_DestinationAddress]
if {[string compare -nocase $DestinationAddress $targetmac] != 0} {
  set assert fail
} else {
  set assert pass
}

RecordAssertion $assert $MnpReceiveFunc1AssertionGuid002                       \
              "Mnp.Receive - Check source MAC address correction."             \
              "Return DestinationAddress - $DestinationAddress                 \
               Expected DestinationAddress - $targetmac"
#
# Destroy child handle
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Receive - Basic Func - Destroy Child"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope  _MNP_RECEIVE_FUNCTION1_CASE1_

#
# End log
#
EndLog
