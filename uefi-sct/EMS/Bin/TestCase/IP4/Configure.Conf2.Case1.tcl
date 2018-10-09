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
CaseGuid        2453814E-4768-4ca5-B0C8-EF3F169977E8
CaseName        Configure.Conf2.Case1
CaseCategory    IP4
CaseDescription {Test the Configure Conformance of IP4 - Invoke Configure() to \
                 change the StationAddress/SubnetMask while the instance has been\
                 configured before, the return status should be EFI_ALREADY_STARTED.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# Begin scope ...
#
BeginScope   _IP4_CONFIGURE_CONFORMANCE2_CASE1_

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
SetIpv4Address R_IpConfigData.StationAddress    "172.16.210.102"
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
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Configure - Conf - Config Child"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetIpv4Address R_IpConfigData.StationAddress "172.16.210.103"

Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ALREADY_STARTED]
RecordAssertion $assert $Ip4ConfigureConf2AssertionGuid001                     \
                "Ip4.Configure - Conf - Config Child again(StationAddr)"       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ALREADY_STARTED"

SetIpv4Address R_IpConfigData.SubnetMask "255.255.0.0"

Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ALREADY_STARTED]
RecordAssertion $assert $Ip4ConfigureConf2AssertionGuid002                     \
                "Ip4.Configure - Conf - Config Child(SubnetMask)"              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ALREADY_STARTED"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip4ConfigureConf2AssertionGuid001                     \
                "Ip4.Configure - Conf - Destroy Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

VifDown 0

#
# Begin scope ...
#
EndScope   _IP4_CONFIGURE_CONFORMANCE2_CASE1_

#
# End Log
#
EndLog
