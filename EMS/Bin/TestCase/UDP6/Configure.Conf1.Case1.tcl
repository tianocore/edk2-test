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
CaseGuid        A9AF4598-C61E-4b5e-809D-F246D5FCFDF6
CaseName        Configure.Conf1.Case1
CaseCategory    UDP6
CaseDescription {Test the Configure Conformance of UDP6 - Invoke Configure() with \
                 SourceAddress invalid.EFI_INVALID_PARAMETER should be returned.}
################################################################################

Include  UDP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope _UDP6_CONFIGURE_CONF1_

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
# Check point: Call Configure with StationAddress invalid.
#              EFI_INVALID_PARAMETER should be returned.
#
SetVar  R_Udp6ConfigData.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData.TrafficClass           0
SetVar  R_Udp6ConfigData.HopLimit               64
SetVar  R_Udp6ConfigData.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData.StationAddress "2000::1"
SetVar  R_Udp6ConfigData.StationPort            999
SetIpv6Address  R_Udp6ConfigData.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData.RemotePort             666
  
Udp6->Configure "&@R_Udp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Udp6ConfigureConf1AssertionGuid001         \
                "Udp6.Configure - Call Configure with Udp6ConfigData.StationAddress invalid." \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

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
EndScope    _UDP6_CONFIGURE_CONF1_
#
# End Log 
#
EndLog