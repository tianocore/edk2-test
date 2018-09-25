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
CaseGuid        FC9837D2-B9AB-434c-8751-449CD870B84E
CaseName        Configure.Conf3.Case1
CaseCategory    UDP6
CaseDescription {Test the Configure Conformance of UDP6 - Invoke Configure()    \ 
                 when updating unchangeable fields without configure NULL first.\
                 EFI_ALREADY_STARTED should be returned.}
################################################################################

Include  UDP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope _UDP6_CONFIGURE_CONF3_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_UDP6_CONFIG_DATA             R_Udp6ConfigData

#
# Create child.
#
Udp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                  \
                "Udp6SB.CreateChild - Create Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

# 
# Check point: Call Configure function first time with Udp6ConfigData not NULL.
#
SetVar  R_Udp6ConfigData.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData.TrafficClass           0
SetVar  R_Udp6ConfigData.HopLimit               64
SetVar  R_Udp6ConfigData.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData.StationAddress "::"
SetVar  R_Udp6ConfigData.StationPort            999
SetIpv6Address  R_Udp6ConfigData.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData.RemotePort             666
  
Udp6->Configure "&@R_Udp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Udp6.Configure - Configure Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Call Configure() for the second time with the same TrafficClass, \
#              HopLimit,ReceiveTimeout and TransmitTimout.EFI_ALREADY_STARTED.
#
Udp6->Configure "&@R_Udp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ALREADY_STARTED]
RecordAssertion $assert $Udp6ConfigureConf3AssertionGuid001 \
                "Udp6.Configure - Call Configure with the same parameters as the first call of Configure."   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ALREADY_STARTED"

#
# Destroy child.
#
Udp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Udp6SB.DestroyChild - Destroy Child 1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# EndScope
#
EndScope    _UDP6_CONFIGURE_CONF3_
#
# End Log 
#
EndLog