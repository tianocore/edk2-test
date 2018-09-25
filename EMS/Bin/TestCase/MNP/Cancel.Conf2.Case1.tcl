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
CaseGuid        73F7ADF5-880D-4082-BD2A-517365FAB8CE
CaseName        Cancel.Conf2.Case1
CaseCategory    MNP
CaseDescription {Test the Cancel  Conformance of MNP - Aborts an asynchronous  \
	               transmit or receive request - Call MNP.Cancel() when Token is \
	               not NULL, but the asynchronous I/O request was not found in   \
	               transmit or receive queue.. The return status should be       \
	               EFI_NOT_FOUND.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
#Begin log ...
#
BeginLog
BeginScope _MNP_CANCEL_CONFORMANCE2_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS	Side Parameter"
#
UINTN                                 R_Status
UINTN                                 R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA       R_MnpConfData
EFI_MANAGED_NETWORK_TRANSMIT_DATA     R_TxData
EFI_MANAGED_NETWORK_FRAGMENT_DATA     R_FragData
EFI_MANAGED_NETWORK_COMPLETION_TOKEN  R_Token
RAW_ETH_PACKET_BODY                   R_Body

#
# Create Child
#
MnpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Conf - Create Child"                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# configure this child
#
SetMnpConfigData R_MnpConfData 0 0 0 FALSE FALSE TRUE FALSE FALSE FALSE TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Conf - Configure"                                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Transmit 
# transmit 
#
#
# Send unicast packet
#
SetEtherTestPacket R_Body "1:1:1:1:1:1" "2:2:2:2:2:2"

SetVar R_TxData.HeaderLength          $ETH_HDR_LEN
SetVar R_TxData.DataLength            [expr [Sizeof R_Body]-$ETH_HDR_LEN]
SetVar R_TxData.FragmentCount         1
SetVar R_FragData.FragmentBuffer      &@R_Body
SetVar R_FragData.FragmentLength      [Sizeof R_Body]
SetVar R_TxData.FragmentTable         @R_FragData
SetVar R_Token.Packet.TxData          &@R_TxData


Mnp->Cancel "&@R_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $MnpCancelConf2AssertionGuid001                        \
                "Mnp.Cancel - Conf - Call Cancle when R_Token is not NULL,the    \
                asynchronous I/O request was not found in transmit or receive  \
                queue."                                                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

#
# Destroy Child
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.Cancel - Conf - Destroy Child1"                         \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"

EndScope  _MNP_CANCEL_CONFORMANCE2_CASE1_

#
# EndLog
#
EndLog
