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
CaseGuid        90E149C1-7091-48fd-A464-B4B503EF0158
CaseName        Parse.Func1.Case1
CaseCategory    DHCP6

CaseDescription {Test the Parse Function of DHCP6 - Invoke Parse() to parse the option data in \
                 DHCPv6 packet while OptionCount is zero to get the number of Options.Then call\
                 Parse while the parameter *OptionCount equals what we get in first call.
                }
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope  _DHCP6_PARSE_FUNC1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child.
#
Dhcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Dhcp6SB.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]          @R_Handle

EFI_DHCP6_PACKET                            R_Packet
SetVar  R_Packet.Size                       1024
SetVar  R_Packet.Length                     38
SetVar  R_Packet.Dhcp6.Header.MessageType   1
SetVar  R_Packet.Dhcp6.Header.TransactionId {0x1d 0xdc 0xd6}
SetVar  R_Packet.Dhcp6.Option               {0x00 0x01 0x00 0x0e 0x00 0x01 0x00 0x01 0x0f 0x7c \
                                             0x5b 0x70 0x00 0x0e 0x0c 0xb7 0x88 0x8a 0x00 0x03 \
                                             0x00 0x0c 0x00 0x00 0x00 0x01 0xff 0xff 0xff 0xff \
                                             0xff 0xff 0xff 0xff \
                                            }

UINT32                                  R_OptionCount
SetVar R_OptionCount                    0

#
# Check point: Call Parse function for the first time when DHCPv6 packet's OptionCount is zero.
#
Dhcp6->Parse  "&@R_Packet, &@R_OptionCount, NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_BUFFER_TOO_SMALL]
RecordAssertion $assert $Dhcp6ParseFunc1AssertionGuid001 \
                "Dhcp6.Parse- Call Parse function to parse option data in DHCPv6 packet with its OptionCount zero"\
                "ReturnStatus-$R_Status, ExpectedStatus -$EFI_BUFFER_TOO_SMALL"

GetVar     R_OptionCount
set assert fail
if {$R_OptionCount == 2} {
    set assert pass
}
RecordAssertion  $assert   $Dhcp6ParseFunc1AssertionGuid002 \
                 "Dhcp6.Parse- the value of OptionCount should be the number of options in the DHCPv6 packet."

#
# Call Parse function  for the second time while the parameter *OptionCount equals \
# the value we get in the first call of Parse function.
#

POINTER                                 R_PacketOptionPointer(2)

Dhcp6->Parse  "&@R_Packet, &@R_OptionCount, &@R_PacketOptionPointer, &@R_Status"                      
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp6ParseFunc1AssertionGuid003 \
                "Dhcp6.Parse- Call Parse function to parse option data in DHCPv6 packet with its OptionCount not zero"\
                "ReturnStatus-$R_Status, ExpectedStatus -$EFI_SUCCESS"

#
# Check Point: When Parse packet returns, the PacketOptionList stores the options of Packet.
#
GetVar  R_PacketOptionPointer(0)
puts $R_PacketOptionPointer(0)
UINT16                                 R_OpCode
UINTN                                  R_CopyLen
SetVar R_CopyLen                       [Sizeof R_OpCode]
BS->CopyMem  "&@R_OpCode, @R_PacketOptionPointer(0), @R_CopyLen, &@R_Status"
GetAck
GetVar   R_OpCode

set  assert pass
if {[Ntohs $R_OpCode] != 1} {
   set assert  fail
}

GetVar  R_PacketOptionPointer(1)
BS->CopyMem  "&@R_OpCode, @R_PacketOptionPointer(1), @R_CopyLen, &@R_Status"
GetAck
GetVar R_OpCode
if {[Ntohs $R_OpCode] != 3} {
   set assert fail
}

RecordAssertion $assert $Dhcp6ParseFunc1AssertionGuid004 \
                "Dhcp6.Parse- the options that store in the OptionList should be the same as what in the packet."
#
# DestroyChild.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# End scope
#
EndScope _DHCP6_PARSE_FUNC1_
#
# End Log
#
EndLog

