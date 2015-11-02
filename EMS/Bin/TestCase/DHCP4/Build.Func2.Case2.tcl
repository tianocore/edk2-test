#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
#
################################################################################
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        6D4A6D02-2606-44f2-9565-E431A6D154F9
CaseName        Build.Func2.Case2
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
                -- Delete an not-defined option }

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
# 	Parameter B:                                               
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

SetVar  R_DeleteList {0x3c 0x35 0x3d}

Dhcp4->Build "&@R_Packet, 3, &@R_DeleteList, 0, NULL, &@R_NewPacket, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4BuildFunc2AssertionGuid002                       \
                "Dhcp4.Build - Func - Del Option(Opt not defined) - CallBuild" \
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
  if { $R_OptionCount != 1 } {
    set assert fail
  }
}

if { [string compare -nocase $assert "pass"] == 0 } {
  UINT8   R_RemainOpt(11)
  UINTN   R_Result
  SetVar  R_RemainOpt {0x0c 0x09 0x72 0x6c 0x69 0x36 0x2d 0x6d 0x6f 0x62 0x6c}
  BS->CopyMem "&@R_RemainOpt, @R_OptionList(0), 11, &@R_Result"
  GetAck

  GetVar    R_Result
  if { $R_Result != 0 } {
    set assert fail
  }
}
RecordAssertion $assert $Dhcp4BuildFunc2AssertionGuid002                       \
                "Dhcp4.Build - Func-Del Option(Opt not defined) - ChkNewPacket"\
                "ExpectedStatus - $EFI_SUCCESS, ReturnedStatus - $R_Status"    \
                "ExpectedOptionCount - 1, ReturnedOptionCount - $R_OptionCount"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment