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
CaseGuid        484238BD-EAAA-4ed6-808B-92E6B1FEAA44
CaseName        ParseOptions.Conf6.Case1
CaseCategory    MTFTP6
CaseDescription {Test ParseOptions Conformance of MTFTP6 - Invoke ParseOptions()\
                 when one or more options is invalid in packet.\
                 EFI_PROTOCOL_ERROR should be returned.}
################################################################################

Include MTFTP6/include/Mtftp6.inc.tcl
#
# Begin log ...
#
BeginLog

BeginScope _MTFTP6_PARSEOPTIONS_CONFORMANCE6_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child
#
Mtftp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                    \
                "Mtftp6SB.CreateChild - Create Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Check Point: Call Configure function with valid parameters.\
#              EFI_SUCCESS should be returned.
#
EFI_MTFTP6_CONFIG_DATA      R_Mtftp6ConfigData
SetIpv6Address    R_Mtftp6ConfigData.StationIp         "2002::4321" 
SetVar            R_Mtftp6ConfigData.LocalPort         1780
SetIpv6Address    R_Mtftp6ConfigData.ServerIp          "2002::2"
SetVar            R_Mtftp6ConfigData.InitialServerPort 0
SetVar            R_Mtftp6ConfigData.TryCount          3
SetVar            R_Mtftp6ConfigData.TimeoutValue      3

Mtftp6->Configure "&@R_Mtftp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Mtftp6.Configure -conf- Call Configure with valid parameters"  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# check point:Call ParseOptions when one or more options is invalid in packet.\
#             EFI_PROTOCOL_ERROR should be returned.
#
UINT32                      R_PacketLen
SetVar R_PacketLen          26
EFI_MTFTP6_PACKET           R_Packet
SetVar R_Packet.OpCode      0x0600
SetVar R_Packet.Oack.OpCode 0x0600
SetVar R_Packet.Oack.Data   "0x74 0x69 0x6d 0x65 0x6f 0x75 0x74 0xff 0x36 0xff \
                                                                 0x62 0x6c 0x6b 0x73 0x69 0x7a 0x65 0xff 0x31 0x30 \
                                                                 0x32 0x34 0xaa"

UINT32                      R_OptionCount
POINTER                     R_OptionList

Mtftp6->ParseOptions "@R_PacketLen, &@R_Packet, &@R_OptionCount,&@R_OptionList, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_PROTOCOL_ERROR]
RecordAssertion $assert $Mtftp6ParseOptionsConf6AssertionGuid001     \
               "Mtftp6.ParseOptions() -Conf- Call ParseOption when one or more options is invalid in packet." \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_PROTOCOL_ERROR"

#
# Destroy child
#
Mtftp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp6SB.DestroyChild - Destroy Child 1"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EUTClose
				
EndScope _MTFTP6_PARSEOPTIONS_CONFORMANCE6_CASE1_

#
# End Log
#
EndLog

