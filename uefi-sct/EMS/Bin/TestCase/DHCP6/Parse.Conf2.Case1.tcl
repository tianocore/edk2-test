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
############################################
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        01B72C18-A1A4-4a6c-AC7A-670F38CEC096
CaseName        Parse.Conf2.Case1
CaseCategory    DHCP6
CaseDescription {Test the Parse Conformance of DHCP6 - Invoke Parse() \
                 when Packet is not Well-formed DHCP packet - Length too small. \
                 EFI_INVALID_PARAMETER should be returned.}
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope _DHCP6_PARSE_CONF2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                   R_Status
UINTN                                   R_Handle

#
# Create child.
#
Dhcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Dhcp6SB.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

EFI_DHCP6_PACKET                        R_Packet
SetVar  R_Packet.Size                   1024
#
# Length too small
#
SetVar  R_Packet.Length                 2
SetVar  R_Packet.Dhcp6.Header.MessageType 2
SetVar  R_Packet.Dhcp6.Header.TransactionId {0x1d 0xdc 0xd6}
SetVar  R_Packet.Dhcp6.Option           {0x00 0x01 0x00 0x0e 0x00 0x01 0x00 0x01 \
                                         0x0f 0x7c 0x5b 0x70 0x00 0x0e 0x0c 0xb7 0x88 0x8a}

UINT32                                  R_OptionCount
SetVar R_OptionCount                    1

EFI_DHCP6_PACKET_OPTION                 R_PacketOption0
POINTER                                 R_PacketOptionPointer(3)
SetVar R_PacketOptionPointer(0)         &@R_PacketOption0

#
# Check Point: Call Parse() while Length too small
#
Dhcp6->Parse "&@R_Packet, &@R_OptionCount, @R_PacketOptionPointer, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp6ParseConf2AssertionGuid001            \
                "Dhcp6.Parse - Conf - Packet is not a well-formed DHCP6 packet."   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy child.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# EndScope
#
EndScope _DHCP6_PARSE_CONF2
#
# End Log 
#
EndLog