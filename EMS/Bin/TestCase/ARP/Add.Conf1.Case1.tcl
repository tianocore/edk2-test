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

#
# test case Name, category, description, GUID...
#
CaseGuid        8A951373-B801-4422-BB3E-AD7D42AB0FEB
CaseName        Add.Conf1.Case1
CaseCategory    ARP
CaseDescription {This case is to test the EFI_INVALID_PARAMETER conforamce of  \
	               ARP.Add}
################################################################################

#
# Begin log ...
#

BeginLog

Include ARP/include/Arp.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0
BeginScope _ARP_SPEC_CONFORMANCE_

UINTN                            R_Status
UINTN                            R_Handle
EFI_IP_ADDRESS                   R_StationAddress
EFI_ARP_CONFIG_DATA              R_ArpConfigData
EFI_IP_ADDRESS                   R_TargetSwAddress
EFI_MAC_ADDRESS                  R_TargetHwAddress

ArpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "ArpSBP.CreateChild - Create Child 1"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetIpv4Address R_StationAddress.v4     "172.16.210.102"
SetVar R_ArpConfigData.SwAddressType   0x800
SetVar R_ArpConfigData.SwAddressLength 4
SetVar R_ArpConfigData.StationAddress  &@R_StationAddress
SetVar R_ArpConfigData.EntryTimeOut    0
SetVar R_ArpConfigData.RetryCount      0
SetVar R_ArpConfigData.RetryTimeOut    0

Arp->Configure {&@R_ArpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Configure - Config Child 1"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetIpv4Address R_TargetSwAddress.v4 "172.16.210.161"
SetEthMacAddress R_TargetHwAddress "00:02:03:04:05:06"

#
# Check point
#
Arp->Add {TRUE, NULL, NULL, 0, TRUE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $ArpAddConfAssertionGuid001                            \
                "Arp.Add - returns EFI_INVALID_PARAMETER with both DenyFlag and\
                 TargetAddress NULL."                                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Check point
#
Arp->Add {FALSE, NULL, NULL, 0, TRUE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $ArpAddConfAssertionGuid002                            \
                "Arp.Add - returns EFI_INVALID_PARAMETER with DenyFlag FALSE   \
                 and TargetAddress NULL"                                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"
#
# Check point
#
Arp->Add {FALSE, &@R_TargetSwAddress, NULL, 0, TRUE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $ArpAddConfAssertionGuid003                            \
                "Arp.Add - returns EFI_INVALID_PARAMETER with DenyFlag FALSE and\
                 TargetHwAddress NULL"                                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Check point
#
Arp->Add {FALSE, NULL, &@R_TargetHwAddress, 0, TRUE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $ArpAddConfAssertionGuid004                            \
                "Arp.Add - returns EFI_INVALID_PARAMETER with DenyFlag FALSE and\
                 TargetSwAddress NULL"                                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Check point
#
Arp->Add {TRUE, &@R_TargetSwAddress, &@R_TargetHwAddress, 0, TRUE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $ArpAddConfAssertionGuid005                            \
                "Arp.Add - returns EFI_INVALID_PARAMETER when both             \
                 TargetHwAddress and TargetSwAddress are not NULL with DenyFlag\
                 True."                                                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

Arp->Delete {TRUE, NULL, &@R_Status}
GetAck

Arp->Delete {FALSE, NULL, &@R_Status}
GetAck

ArpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

EndScope _ARP_SPEC_CONFORMANCE_
VifDown 0

#
# End Log
#
EndLog
