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
CaseGuid        71A540BE-CC76-4e9a-AA65-EA3B7749DCE4
CaseName        Configure.Conf1.Case1
CaseCategory    IP4
CaseDescription {Test the Configure Conformance of IP4 - Invoke Configure()    \
                 with the parameter StationAddress being not a unicast IPv4    \
                 address, the return status should be EFI_INVALID_PARAMETER.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# Begin scope ...
#
BeginScope   _IP4_CONFIGURE_CONFORMANCE1_CASE1_

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

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SB.Configure - Conf - Create Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol           0
SetVar R_IpConfigData.AcceptAnyProtocol         TRUE
SetVar R_IpConfigData.AcceptIcmpErrors          TRUE
SetVar R_IpConfigData.AcceptBroadcast           TRUE
SetVar R_IpConfigData.AcceptPromiscuous         TRUE
SetVar R_IpConfigData.UseDefaultAddress         FALSE
SetIpv4Address R_IpConfigData.StationAddress    "172.16.210.255"
SetIpv4Address R_IpConfigData.SubnetMask        "255.255.255.0"
SetVar R_IpConfigData.TypeOfService             0
SetVar R_IpConfigData.TimeToLive                16
SetVar R_IpConfigData.DoNotFragment             TRUE
SetVar R_IpConfigData.RawData                   FALSE
SetVar R_IpConfigData.ReceiveTimeout            0
SetVar R_IpConfigData.TransmitTimeout           0

#
# check point
#
Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4ConfigureConf1AssertionGuid001                     \
                "Ip4.Configure - Conf - With station address invalid"          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

SetVar R_IpConfigData.DefaultProtocol          0
SetVar R_IpConfigData.AcceptAnyProtocol        TRUE
SetVar R_IpConfigData.AcceptIcmpErrors         TRUE
SetVar R_IpConfigData.AcceptBroadcast          TRUE
SetVar R_IpConfigData.AcceptPromiscuous        TRUE
SetVar R_IpConfigData.UseDefaultAddress        FALSE
SetIpv4Address R_IpConfigData.StationAddress   "255.255.255.255"
SetIpv4Address R_IpConfigData.SubnetMask       "255.255.255.0"
SetVar R_IpConfigData.TypeOfService            0
SetVar R_IpConfigData.TimeToLive               16
SetVar R_IpConfigData.DoNotFragment            TRUE
SetVar R_IpConfigData.RawData                  FALSE
SetVar R_IpConfigData.ReceiveTimeout           0
SetVar R_IpConfigData.TransmitTimeout          0

#
# check point
#
Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4ConfigureConf1AssertionGuid001                     \
                "Ip4.Configure - Conf - With station address invalid"          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

SetVar R_IpConfigData.DefaultProtocol          0
SetVar R_IpConfigData.AcceptAnyProtocol        TRUE
SetVar R_IpConfigData.AcceptIcmpErrors         TRUE
SetVar R_IpConfigData.AcceptBroadcast          TRUE
SetVar R_IpConfigData.AcceptPromiscuous        TRUE
SetVar R_IpConfigData.UseDefaultAddress        FALSE
SetIpv4Address R_IpConfigData.StationAddress   "234.16.210.102"
SetIpv4Address R_IpConfigData.SubnetMask       "255.255.255.0"
SetVar R_IpConfigData.TypeOfService            0
SetVar R_IpConfigData.TimeToLive               16
SetVar R_IpConfigData.DoNotFragment            TRUE
SetVar R_IpConfigData.RawData                  FALSE
SetVar R_IpConfigData.ReceiveTimeout           0
SetVar R_IpConfigData.TransmitTimeout          0

#
# check point
#
Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4ConfigureConf1AssertionGuid001                     \
                "Ip4.Configure - Conf - With station address invalid"          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"
 
Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SB.Configure - Conf - Destroy Child"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

VifDown 0

#
# End scope
#
EndScope _IP4_CONFIGURE_CONFORMANCE1_CASE1_

#
# End Log
#
EndLog
