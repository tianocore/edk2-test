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
CaseGuid        5A7EB3FA-BC6C-416b-A826-04B664BD5150
CaseName        Transmit.Conf4.Case1
CaseCategory    UDP6
CaseDescription {Test the Transmit Conformance of UDP6 - Invoke Transmit() when \  
                 TxData is NULL.EFI_INVALID_PARAMETER should be returned.}
################################################################################

Include  UDP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope _UDP6_TRANSMIT_CONF4_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

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
# Call Configure function with valid parameters.EFI_SUCCESS should be returned.
#
EFI_UDP6_CONFIG_DATA                            R_Udp6ConfigData
SetVar  R_Udp6ConfigData.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData.TrafficClass           0
SetVar  R_Udp6ConfigData.HopLimit               64
SetVar  R_Udp6ConfigData.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData.StationAddress "::"
SetVar  R_Udp6ConfigData.StationPort            1780
SetIpv6Address  R_Udp6ConfigData.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData.RemotePort             1781
  
Udp6->Configure "&@R_Udp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Udp6.Configure - Configure Child with valid parameters"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

# 
# Check point: Call Transmit function with the parameter TxData \
#              is NULL.EFI_INVALID_PARAMETER should be returned.
#
EFI_UDP6_COMPLETION_TOKEN           R_Token
UINTN                               R_NotifyContext
SetVar      R_NotifyContext         0

#
# Create an Event
#
BS->CreateEvent      "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_NotifyContext, &@R_Token.Event, &@R_Status"
GetAck
set assert           [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion      $assert          $GenericAssertionGuid           \
                     "BS->CreateEvent -Conf- Create an Event "                  \
                     "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
SetVar                R_Token.Status                   "$EFI_SUCCESS"
EFI_UDP6_TRANSMIT_DATA                                 R_TxData
SetVar                R_TxData                         NULL
SetVar                R_Token.Packet                   &@R_TxData
  
Udp6->Transmit  "&@R_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Udp6TransmitConf4AssertionGuid001        \
                "Udp6.Transmit -conf- Call Transmit when TxData  is NULL "                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy child.
#
Udp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Udp6SB.DestroyChild - Destroy Child1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Close Event
#
BS->CloseEvent    "@R_Token.Event, &@R_Status"
GetAck
set assert        [VerifyReturnStatus   R_Status   $EFI_SUCCESS]
RecordAssertion   $assert     $GenericAssertionGuid             \
                  "BS->CloseEvent -Conf- Close the Event we created before"  \
                  "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
#
# EndScope
#
EndScope    _UDP6_TRANSMIT_CONF4_
#
# End Log 
#
EndLog