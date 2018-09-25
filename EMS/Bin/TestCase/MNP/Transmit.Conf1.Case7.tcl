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
CaseGuid        125E63B1-3F3B-4452-B973-44ACE2E222E5
CaseName        Transmit.Conf1.Case7
CaseCategory    MNP
CaseDescription {Test Transmit EFI_INVALID_PARAMETER conformance of MNP - Call \
                 MNP.Transmit() when (Token.TxData.HeaderLength +              \
                 Token.TxData.DataLength) is greater than MTU if the           \
                 Token.TxData.FragmentTable[] contains the media header.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope _MNP_TRANSMIT_CONFORMANCE1_CASE7_

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
TOKEN_PACKET                          R_TokenPacket
EFI_MANAGED_NETWORK_FRAGMENT_DATA     R_FragData
EFI_MANAGED_NETWORK_COMPLETION_TOKEN  R_Token
RAW_ETH_PACKET_BODY                   R_Body

MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Conf - Create Child"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar          [subst $ENTS_CUR_CHILD]  @R_Handle
                
                
#
# configure this child
#
SetMnpConfigData R_MnpConfData 0 0 0 TRUE FALSE TRUE TRUE FALSE FALSE TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck

SetEtherTestPacket R_Body "1:1:1:1:1:1" "2:2:2:2:2:2"

SetVar R_TxData.DestinationAddress    0
SetVar R_TxData.SourceAddress         0
SetVar R_TxData.ProtocolType          0
SetVar R_TxData.HeaderLength          $ETH_HDR_LEN
SetVar R_TxData.FragmentCount         1
SetVar R_TxData.DataLength            [expr [Sizeof R_Body] + 1500]

SetVar R_FragData.FragmentBuffer      &@R_Body
GetVar R_TxData.DataLength
 
SetVar R_FragData.FragmentLength      [expr $ETH_HDR_LEN + ${R_TxData.DataLength}]
SetVar R_TxData.FragmentTable         @R_FragData
SetVar R_Token.Packet.TxData          &@R_TxData

#
# (Token.TxData.HeaderLength + Token.TxData.DataLength) is greater than MTU if 
#  the Token.TxData.FragmentTable[] contains the media header
#
Mnp->Transmit "&@R_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $MnpTransmitConf1AssertionGuid007                      \
                "Mnp.Transmit - Conf - returns EFI_INVALID_PARAMETER when      \
                (Token.TxData.HeaderLength + Token.TxData.DataLength) is greater\
                 than MTU if the Token.TxData.FragmentTable[] contains the media\
                 header"                                                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy child R_Handle
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Conf - Destroy Child"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope _MNP_TRANSMIT_CONFORMANCE1_CASE7_

#
#EndLog
#
EndLog