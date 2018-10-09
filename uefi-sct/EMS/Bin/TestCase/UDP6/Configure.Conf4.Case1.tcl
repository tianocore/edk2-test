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
CaseGuid        15E02530-BD84-43f1-9E0A-1474D14A914C
CaseName        Configure.Conf4.Case1
CaseCategory    UDP6
CaseDescription {Test the Configure Conformance of UDP6 - Invoke Configure()    \ 
                 when StationPort has already been used by another Udp6 instance.\
                 EFI_ACCESS_DENIED should be returned.}
################################################################################

Include  UDP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope _UDP6_CONFIGURE_CONF4_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2
EFI_UDP6_CONFIG_DATA             R_Udp6ConfigData1

#
# Create child1.
#
Udp6ServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                  \
                "Udp6SB.CreateChild - Create Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1

# 
# Check point: Call Configure function first time with valid parameters.\
#              EFI_SUCCESS should be returned.
#
SetVar  R_Udp6ConfigData1.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData1.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData1.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData1.TrafficClass           0
SetVar  R_Udp6ConfigData1.HopLimit               64
SetVar  R_Udp6ConfigData1.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData1.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData1.StationAddress "::"
SetVar  R_Udp6ConfigData1.StationPort            1780
SetIpv6Address  R_Udp6ConfigData1.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData1.RemotePort             666
  
Udp6->Configure "&@R_Udp6ConfigData1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Udp6.Configure - Configure Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Create child2
#
Udp6ServiceBinding->CreateChild "&@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                \
                "Udp6SB.CreateChild- Conf- Create child 2"             \
                "ReturnStatus-$R_Status, ExpectedStatus-$EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2

#
# Check point: Call Configure() to configure child2 with the same StationPort(1780) \
#              and AllowDuplicatePort(FALSE).EFI_ACCESS_DENIED should be returned.
#
EFI_UDP6_CONFIG_DATA             R_Udp6ConfigData2
SetVar  R_Udp6ConfigData2.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData2.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData2.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData2.TrafficClass           0
SetVar  R_Udp6ConfigData2.HopLimit               64
SetVar  R_Udp6ConfigData2.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData2.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData2.StationAddress "::"
SetVar  R_Udp6ConfigData2.StationPort            1780
SetIpv6Address  R_Udp6ConfigData2.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData2.RemotePort             1781

Udp6->Configure "&@R_Udp6ConfigData2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ACCESS_DENIED]
RecordAssertion $assert $Udp6ConfigureConf4AssertionGuid001 \
                "Udp6.Configure - Call Configure with the same StationPort(1780) as child1."   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ACCESS_DENIED"

#
# Destroy child1.
#
Udp6ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Udp6SB.DestroyChild - Destroy Child1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Destroy child2.
#
Udp6ServiceBinding->DestroyChild "@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Udp6SB.DestroyChild - Destroy Child 2"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# EndScope
#
EndScope    _UDP6_CONFIGURE_CONF4_
#
# End Log 
#
EndLog