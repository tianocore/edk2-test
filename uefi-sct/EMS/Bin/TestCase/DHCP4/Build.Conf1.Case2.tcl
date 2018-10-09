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
CaseGuid        25d3c1b2-84b8-4550-9652-592dde16566d
CaseName        Build.Conf1.Case2
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_INVALID_PARAMETER  \
                -- SeedPacket is not a well-formed DHCP packet (Magic Number   \
                Error).}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_BUILD_CONF1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_BUILD_CONF1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                                     R_Status
UINTN                                     R_Handle
EFI_DHCP4_PACKET                          R_Packet
POINTER                                   R_NewPacket
UINT8                                     R_Option1(10)
POINTER                                   R_PtrOptList

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
# NOTES: IN Windows, Call ipconfig /renew, and capture the relative DHCPREQUEST
#
SetVar  R_Packet.Size                     [Sizeof EFI_DHCP4_PACKET]
SetVar  R_Packet.Length                   [expr [Sizeof EFI_DHCP4_HEADER] + 28]

#
# error magic cookie
#
SetVar  R_Packet.Dhcp4.Magik              0x11111111 
SetVar  R_Packet.Dhcp4.Header.OpCode      1
SetVar  R_Packet.Dhcp4.Header.HwType      1
SetVar  R_Packet.Dhcp4.Header.HwAddrLen   6
SetVar  R_Packet.Dhcp4.Header.Xid         0xe139e46c
SetIpv4Address  R_Packet.Dhcp4.Header.ClientAddr    "172.16.220.21" 
SetVar  R_Packet.Dhcp4.Header.ClientHwAddr  { 0x00 0x0d 0x60 0x36 0x87 0x49}
SetVar  R_Packet.Dhcp4.Option    {0x35 0x01 0x03 0x3d 0x07 0x01 0x00 0x0d 0x60 \
                                 0x36 0x87 0x49 0x0c 0x09 0x72 0x6c 0x69 0x36  \
                                 0x2d 0x6d 0x6f 0x62 0x6c 0xff}
#
# Option 60, Vendor Class Identifier = 'MSFT 5.0'
#
SetVar  R_Option1     { 0x3c 0x08 0x4d 0x53 0x46 0x54 0x20 0x35 0x2e 0x30}
SetVar  R_PtrOptList  &@R_Option1

#
# Check Point: Call DDhcp4->Build while SeedPacket is not a well-formed DHCP
#              packet.(Magic Number Error)
#
Dhcp4->Build "&@R_Packet, 0, NULL, 1, &@R_PtrOptList, &@R_NewPacket, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4BuildConf1AssertionGuid002                       \
                "Dhcp4.Build - Call Build while SeedPacket Error -             \
                MagicNumber Error - "                                          \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment