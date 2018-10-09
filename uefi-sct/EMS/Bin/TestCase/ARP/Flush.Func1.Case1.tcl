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

#
# test case Name, category, description, GUID...
#
CaseGuid        EC2E9F90-C94E-432b-B3EC-BE387897D234
CaseName        Flush.Func1.Case1
CaseCategory    ARP
CaseDescription {This case is to test the function of ARP.Flush}
################################################################################

#
# Begin log ...
#
BeginLog

Include ARP/include/Arp.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0
BeginScope _ARP_FUNC_CONFORMANCE_

UINTN                            R_Status
UINTN                            R_Handle
EFI_IP_ADDRESS                   R_StationAddress
EFI_ARP_CONFIG_DATA              R_ArpConfigData
EFI_IP_ADDRESS                   R_TargetSwAddress(4)
EFI_MAC_ADDRESS                  R_TargetHwAddress(4)
EFI_IP_ADDRESS                   R_IpAddressBuffer(4)
EFI_MAC_ADDRESS                  R_MacAddressBuffer(4)
UINT32                           R_EntryLength
UINT32                           R_EntryCount
POINTER                          R_EntriesPtr

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

SetIpv4Address R_TargetSwAddress(0).v4 "172.16.210.161"
SetEthMacAddress R_TargetHwAddress(0)  "00:02:03:04:05:06"
SetIpv4Address R_TargetSwAddress(1).v4 "172.16.210.160"
SetEthMacAddress R_TargetHwAddress(1)  "6:5:4:3:2:1"
SetIpv4Address R_TargetSwAddress(2).v4 "172.16.210.159"
SetEthMacAddress R_TargetHwAddress(2)  "00:02:03:04:05:07"
SetIpv4Address R_TargetSwAddress(3).v4 "172.16.210.158"
SetEthMacAddress R_TargetHwAddress(3)  "8:5:4:3:2:1"

SetVar R_IpAddressBuffer @R_TargetSwAddress
SetVar R_MacAddressBuffer @R_TargetHwAddress

Arp->Add {FALSE, &@R_TargetSwAddress(0), &@R_TargetHwAddress(0), 0, TRUE,      \
	        &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Add - Add normal entry"                                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Arp->Add {FALSE, &@R_TargetSwAddress(1), &@R_TargetHwAddress(1), 500000000,    \
	         TRUE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Add - Add normal entry"                                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Arp->Add {TRUE, &@R_TargetSwAddress(2), NULL, 0, TRUE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Add - Add normal entry"                                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Arp->Add {TRUE, &@R_TargetSwAddress(3), NULL, 500000000, TRUE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Add - Add normal entry"                                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point
#
Arp->Flush {&@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $ArpFlushFuncAssertionGuid001                          \
                 "Arp.flush - flush the entry"                                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Arp->Find {TRUE, &@R_IpAddressBuffer(0), &@R_EntryLength, &@R_EntryCount,      \
	             &@R_EntriesPtr, FALSE, &@R_Status}
GetAck

GetVar R_EntryCount
set assert pass
if {$R_EntryCount != 0x1} {
  set assert fail
}

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Find - Find the entry"                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

if {$R_EntryCount > 0x0} {
	BS->FreePool {@R_EntriesPtr, &@R_Status}
  GetAck
}

Arp->Find {FALSE, &@R_MacAddressBuffer(0), &@R_EntryLength, &@R_EntryCount,    \
	          &@R_EntriesPtr, FALSE, &@R_Status}
GetAck

GetVar R_EntryCount
set assert pass
if {$R_EntryCount != 0x1} {
  set assert fail
}

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Find - Find the entry"                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

if {$R_EntryCount > 0x0} {
	BS->FreePool {@R_EntriesPtr, &@R_Status}
  GetAck
}

Arp->Find {TRUE, &@R_IpAddressBuffer(1), &@R_EntryLength, &@R_EntryCount,      \
	           &@R_EntriesPtr, FALSE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Find - Find the entry"                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

Arp->Find {FALSE, &@R_MacAddressBuffer(1), &@R_EntryLength, &@R_EntryCount,    \
	          @R_EntriesPtr, FALSE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Find - Find the entry"                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

Arp->Find {TRUE, &@R_IpAddressBuffer(2), &@R_EntryLength, &@R_EntryCount,      \
	          &@R_EntriesPtr, FALSE, &@R_Status}
GetAck

GetVar R_EntryCount
set assert pass
if {$R_EntryCount != 0x1} {
  set assert fail
}

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Find - Find the entry"                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

if {$R_EntryCount > 0x0} {
	BS->FreePool {@R_EntriesPtr, &@R_Status}
  GetAck
}

Arp->Find {TRUE, &@R_IpAddressBuffer(3), &@R_EntryLength, &@R_EntryCount,      \
	           &@R_EntriesPtr, FALSE, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Find - Find the entry"                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

Arp->Delete {TRUE, NULL, &@R_Status}
GetAck

Arp->Delete {FALSE, NULL, &@R_Status}
GetAck

ArpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

EndScope _ARP_FUNC_CONFORMANCE_
VifDown 0

#
# End Log
#
EndLog