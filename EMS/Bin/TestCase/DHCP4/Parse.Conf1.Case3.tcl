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
CaseGuid        522e3f34-b580-4729-aeb0-3a0f87cc33f9
CaseName        Parse.Conf1.Case3
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_INVALID_PARAMETER  \
                -- Packet is not Well-formed DHCP packet - Magic Number error.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_PARSE_CONF1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_PARSE_CONF1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

UINT32                           R_OptionCnt
POINTER                          R_PtrOptions(3)
EFI_DHCP4_PACKET                 R_Packet

#
# Call [DHCP4SBP] -> CreateChild to create child.
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Call [DHCP4] -> Parse with the invalid parameters
# o	MagicNumber error

#
# NOTES: IN Windos, Call ipconfig /renew, and capture the relative DHCPREQUEST
#
SetVar  R_Packet.Size                     [Sizeof EFI_DHCP4_PACKET]
SetVar  R_Packet.Length                   [expr [Sizeof EFI_DHCP4_HEADER] + 28]
SetVar  R_Packet.Dhcp4.Magik              0x11111111
SetVar  R_Packet.Dhcp4.Header.OpCode      1
SetVar  R_Packet.Dhcp4.Header.HwType      1
SetVar  R_Packet.Dhcp4.Header.HwAddrLen   6
SetVar  R_Packet.Dhcp4.Header.Xid         0xe139e46c
SetIpv4Address  R_Packet.Dhcp4.Header.ClientAddr    "172.16.220.21" 
SetVar  R_Packet.Dhcp4.Header.ClientHwAddr  { 0x00 0x0d 0x60 0x36 0x87 0x49}
SetVar  R_Packet.Dhcp4.Option     {0x35 0x01 0x03 0x3d 0x07 0x01 0x00 0x0d 0x60\
                                  0x36 0x87 0x49 0x0c 0x09 0x72 0x6c 0x69 0x36 \
                                  0x2d 0x6d 0x6f 0x62 0x6c 0xff}
SetVar  R_OptionCnt               5

#
# Check Point: Call Dhcp4->Parse while MagicNumber error.
#
Dhcp4->Parse "&@R_Packet, &@R_OptionCnt, &@R_PtrOptions, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4ParseConf1AssertionGuid003                       \
                "Dhcp4.Parse - Conf - (InvalidPara)MagicNumber error."         \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment