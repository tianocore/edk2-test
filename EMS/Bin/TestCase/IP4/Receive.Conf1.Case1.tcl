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
CaseGuid        C4F61B63-AAE0-4216-8AE1-10DECBF961CE
CaseName        Receive.Conf1.Case1
CaseCategory    IP4
CaseDescription {Test the Receive Conformance of IP4 - Invoke Receive() with   \
                 the parameter Token being NULL or Token.Event being NULL. The \
                 return status all should be EFI_INVALID_PARAMETER.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_RECEIVE_CONFORMANCE1_CASE1_

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_IP4_CONFIG_DATA              R_IpConfigData
UINTN                            R_Context
EFI_IP4_COMPLETION_TOKEN         R_Token

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Receive - Conf - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol             0
SetVar R_IpConfigData.AcceptAnyProtocol           TRUE
SetVar R_IpConfigData.AcceptIcmpErrors            TRUE
SetVar R_IpConfigData.AcceptBroadcast             TRUE
SetVar R_IpConfigData.AcceptPromiscuous           TRUE
SetVar R_IpConfigData.UseDefaultAddress           FALSE
SetIpv4Address R_IpConfigData.StationAddress      "172.16.210.102"
SetIpv4Address R_IpConfigData.SubnetMask          "255.255.255.0"
SetVar R_IpConfigData.TypeOfService               0
SetVar R_IpConfigData.TimeToLive                  16
SetVar R_IpConfigData.DoNotFragment               TRUE
SetVar R_IpConfigData.RawData                     FALSE
SetVar R_IpConfigData.ReceiveTimeout              0
SetVar R_IpConfigData.TransmitTimeout             0

Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Receive - Conf - Config Child"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# check point
#
Ip4->Receive {NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4ReceiveConf1AssertionGuid001                       \
                "Ip4.Receive - Conf - With R_Token invalid"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# check point
#
Ip4->Receive {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4ReceiveConf1AssertionGuid002                       \
                "Ip4.Receive - Conf - With Event invalid"                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Receive - Conf - Destroy Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

VifDown 0

# BeginScope
#
EndScope _IP4_RECEIVE_CONFORMANCE1_CASE1_

#
# End Log
#
EndLog
