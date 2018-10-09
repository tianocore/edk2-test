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
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        c2dc9dbe-992e-4f99-b08c-848d63429204
CaseName        Build.Func2.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
                -- Delete an already-defined option }

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_BUILD_FUNC2
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_BUILD_FUNC2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

EFI_DHCP4_PACKET                 R_Packet
POINTER                          R_NewPacket

UINT32                           R_OptionCount 
UINT8                            R_DeleteList(3)
POINTER                          R_OptionList(2)
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
# Call [DHCP4] -> Build to build DHCP packet, the parameter is as the following
# 	Parameter A:                                               
# "	SeedPacket:	An initial packet(In this packet, include option A,B,C)                                     
# "	DeleteCount:	3                                            
# "	DeleteList:	Option A,B,C                                   
# "	AppendCount:	0                                            
# "	AppendList:	NULL                                           
# "	NewPacket:	Point to pointer of NewPacket                  
#

#
# NOTES: IN Windows, Call ipconfig /renew, and capture the relative DHCPREQUEST
#
SetVar  R_Packet.Size                     [Sizeof EFI_DHCP4_PACKET]
SetVar  R_Packet.Length                   [expr [Sizeof EFI_DHCP4_HEADER] + 28]
SetVar  R_Packet.Dhcp4.Magik              0x63538263
SetVar  R_Packet.Dhcp4.Header.OpCode      1
SetVar  R_Packet.Dhcp4.Header.HwType      1
SetVar  R_Packet.Dhcp4.Header.HwAddrLen   6
SetVar  R_Packet.Dhcp4.Header.Xid         0xe139e46c
SetIpv4Address  R_Packet.Dhcp4.Header.ClientAddr "172.16.220.21" 
SetVar  R_Packet.Dhcp4.Header.ClientHwAddr      { 0x00 0x13 0x72 0xb1 0x58 0xff}
#
# Include Option 60 - Vendor Class, Option 53 - Message Type, 
# Option 12 - Host Name
#
SetVar  R_Packet.Dhcp4.Option    {0x35 0x01 0x03 0x3c 0x07 0x01 0x00 0x0d 0x60 \
                                  0x36 0x87 0x49 0x0c 0x09 0x72 0x6c 0x69 0x36 \
                                  0x2d 0x6d 0x6f 0x62 0x6c 0xff}


SetVar  R_DeleteList {0x3c 0x35 0x0c}

Dhcp4->Build "&@R_Packet, 3, &@R_DeleteList, 0, NULL, &@R_NewPacket, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4BuildFunc2AssertionGuid001                       \
                "Dhcp4.Build - Func - Del Option(Opt defined) - CallBuild"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check NewPacket, No Option remains in the NewPacket
#
SetVar  R_OptionCount   2
GetVar  R_NewPacket

Dhcp4->Parse "@R_NewPacket, &@R_OptionCount, &@R_OptionList, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
GetVar R_OptionCount
if { [string compare -nocase $assert "pass"] == 0 } {
  if { $R_OptionCount != 0 } {
    set assert fail
  }
}
RecordAssertion $assert $Dhcp4BuildFunc2AssertionGuid001                       \
                "Dhcp4.Build - Func - Del Option(Opt defined) - ChkNewPacket"  \
                "ExpectedStatus - $EFI_SUCCESS, ReturnedStatus - $R_Status"    \
                "ExpectedOptionCount - 0, ReturnedOptionCount - $R_OptionCount"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment