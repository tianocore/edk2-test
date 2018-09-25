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
CaseGuid        12AA904D-2948-4676-BF2B-4EBDFFF9578C
CaseName        GetModeData.Conf1.Case1
CaseCategory    UDP6
CaseDescription {Test the GetModeData Conformance of UDP6 - Invoke GetModeData() \
                 with Udp6ConfigData not NULL while the instance has not been configured. \
                 EFI_NOT_STARTED should be returned.}
################################################################################

Include  UDP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope _UDP6_GETMODEDATA_CONF1_

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
# Check point: Call GetModeData with Udp6ConfigData not NULL.
#              EFI_NOT_STARTED should be returned.
#
SetVar  R_Udp6ConfigData.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData.TrafficClass           0
SetVar  R_Udp6ConfigData.HopLimit               64
SetVar  R_Udp6ConfigData.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData.StationAddress "2002::4321"
SetVar  R_Udp6ConfigData.StationPort            999
SetIpv6Address  R_Udp6ConfigData.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData.RemotePort             666
  
Udp6->GetModeData "&@R_Udp6ConfigData, NULL, NULL, NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Udp6GetModeDataConf1AssertionGuid001         \
                "Udp6.GetModeData - GetModeData with Udp6ConfigData not NULL." \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

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
EndScope    _UDP6_GETMODEDATA_CONF1_
#
# End Log 
#
EndLog