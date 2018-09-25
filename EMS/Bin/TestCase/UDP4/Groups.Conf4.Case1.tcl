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
CaseGuid        AB5A92BE-C68C-406c-ABD7-4B5B4961B59A
CaseName        Groups.Conf4.Case1
CaseCategory    Udp4
CaseDescription {Test the EFI_ALREADY_STARTED Conformance of UDP4.Groups - Invoke\
                 Groups() when the group address is already in the group table(\
                 when JoinFlag is TRUE.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _UDP4_GROUPS_CONFORMANCE4_CASE1_

set hostmac              [GetHostMac]
set targetmac            [GetTargetMac]
set targetip             172.16.210.33
set hostip               172.16.210.35
set subnetmask           255.255.255.0
set targetport           999
set hostport             666

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_IP_ADDRESS                   R_Valid_Group
EFI_UDP4_CONFIG_DATA             R_Udp4ConfigData

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar   [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Groups - Conf - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Udp4ConfigData.AcceptBroadcast             TRUE
SetVar R_Udp4ConfigData.AcceptPromiscuous           TRUE
SetVar R_Udp4ConfigData.AcceptAnyPort               TRUE
SetVar R_Udp4ConfigData.AllowDuplicatePort          TRUE
SetVar R_Udp4ConfigData.TypeOfService               0
SetVar R_Udp4ConfigData.TimeToLive                  1
SetVar R_Udp4ConfigData.DoNotFragment               TRUE
SetVar R_Udp4ConfigData.ReceiveTimeout              0
SetVar R_Udp4ConfigData.TransmitTimeout             0
SetVar R_Udp4ConfigData.UseDefaultAddress           FALSE
SetIpv4Address R_Udp4ConfigData.StationAddress      $targetip
SetIpv4Address R_Udp4ConfigData.SubnetMask          $subnetmask
SetVar R_Udp4ConfigData.StationPort                 $targetport
SetIpv4Address R_Udp4ConfigData.RemoteAddress       $hostip
SetVar R_Udp4ConfigData.RemotePort                  $hostport

#
# check point
#
Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Groups - Conf - Config Child"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetIpv4Address R_Valid_Group.v4 224.0.0.8

Udp4->Groups {TRUE, &@R_Valid_Group, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Groups - Conf - Join an group"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetIpv4Address R_Valid_Group.v4 224.0.0.8

Udp4->Groups {TRUE, &@R_Valid_Group, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ALREADY_STARTED]
RecordAssertion $assert $Udp4GroupsConf4AssertionGuid001                       \
                "Udp4.Groups - Conf - Invoke Groups() when the group address is\
                 already in the group table (when JoinFlag is TRUE)."          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ALREADY_STARTED"

Udp4->Groups {FALSE, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Groups - Conf - Leave all the groups"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

#
# EndScope
#
EndScope _UDP4_GROUPS_CONFORMANCE4_CASE1_

#
# End Log
#
EndLog
