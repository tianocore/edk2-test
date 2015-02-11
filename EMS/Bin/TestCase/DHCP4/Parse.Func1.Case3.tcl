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
CaseGuid        404eabb1-a4d1-4648-a26f-021f60549a53
CaseName        Parse.Func1.Case3
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
                -- Pad Option Include in packet.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_PARSE_FUNC1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_PARSE_FUNC1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

POINTER                          R_OptionList(5)
UINT32                           R_OptionCnt
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
# NOTES: IN Windos, Call ipconfig /renew, and capture the relative DHCPREQUEST
#
SetVar  R_Packet.Size                     [Sizeof EFI_DHCP4_PACKET]
SetVar  R_Packet.Length                   [expr [Sizeof EFI_DHCP4_HEADER] + 32]
SetVar  R_Packet.Dhcp4.Magik              0x63538263
SetVar  R_Packet.Dhcp4.Header.OpCode      1
SetVar  R_Packet.Dhcp4.Header.HwType      1
SetVar  R_Packet.Dhcp4.Header.HwAddrLen   6
SetVar  R_Packet.Dhcp4.Header.Xid         0xe139e46c
SetIpv4Address  R_Packet.Dhcp4.Header.ClientAddr    "172.16.220.21"
SetVar  R_Packet.Dhcp4.Option  {0x35 0x01 0x03 0x00 0x00 0x00 0x00 0x3d 0x07   \
                              0x01 0x00 0x0d 0x60 0x36 0x87 0x49 0x0c 0x09 0x72\
                              0x6c 0x69 0x36 0x2d 0x6d 0x6f 0x62 0x6c 0xff}
SetVar  R_OptionCnt           5

#
# Check Point: Call Dhcp4->Parse while  Pad Option Include in packet.
#
Dhcp4->Parse "&@R_Packet, &@R_OptionCnt, &@R_OptionList, &@R_Status"
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4ParseFunc1AssertionGuid003                       \
                "Dhcp4.Parse - Func - Chk Return Status."                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar  R_OptionCnt
set assert pass
if { $R_OptionCnt != 3 } {
  set assert fail
}
RecordAssertion $assert $Dhcp4ParseFunc1AssertionGuid003                       \
                "Dhcp4.Parse - Func - With Option - Chk Returned OptionCnt."   \
                "Return - $R_OptionCnt, Expected - 3"

if { [string compare -nocase $assert "pass"] == 0} {
  #
  # Continue check parsed option list
  #
  INTN    R_Result(3)
  UINT8   R_Option1(3)
  UINT8   R_Option2(9)
  UINT8   R_Option3(11)
  SetVar  R_Option1 {0x35 0x01 0x03}
  SetVar  R_Option2 {0x3d 0x07 0x01 0x00 0x0d 0x60 0x36 0x87 0x49}
  SetVar  R_Option3 {0x0c 0x09 0x72 0x6c 0x69 0x36 0x2d 0x6d 0x6f 0x62 0x6c}
  GS->MemCmp {&@R_Option1, @R_OptionList(0), 3,  &@R_Result(0)}
  GetAck
  GS->MemCmp {&@R_Option2, @R_OptionList(1), 9,  &@R_Result(1)}
  GetAck
  GS->MemCmp {&@R_Option3, @R_OptionList(2), 11, &@R_Result(2)}
  GetAck
  GetVar  R_Result

  if { $R_Result(0) != 0 || $R_Result(1) != 0 || $R_Result(2) != 0 } {
    set assert fail
  }
  RecordAssertion $assert $Dhcp4ParseFunc1AssertionGuid003                     \
                  "Dhcp4.Parse - Func - With Option - Chk Parsed Option."      \
                  "Option Match: $R_Result(0), $R_Result(1),$R_Result(2)"
}

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment