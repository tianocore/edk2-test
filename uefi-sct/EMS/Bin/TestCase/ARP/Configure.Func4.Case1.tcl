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
CaseGuid        A7004C56-D99C-409c-ADD5-1679211C248A
CaseName        Configure.Func4.Case1
CaseCategory    ARP
CaseDescription {This case is to test the function of ARP.Configure}
################################################################################
proc ArpDestroy {} {
  Arp->Delete {TRUE, NULL, &@R_Status}
  GetAck

  Arp->Delete {FALSE, NULL, &@R_Status}
  GetAck

  ArpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
  GetAck
}

proc CleanUpEutEnvironment {} {
  EndCapture
  EndScope _ARP_FUNC_CONFORMANCE_
  VifDown 0
  EndLog
}

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
EFI_IP_ADDRESS                   R_TargetSwAddress
UINTN                            R_ResolvedEvent
EFI_MAC_ADDRESS                  R_TargetHwAddress
UINTN                            R_EventContext

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
SetVar R_ArpConfigData.RetryCount      5
SetVar R_ArpConfigData.RetryTimeOut    50000000

#
# Check point
#
Arp->Configure {&@R_ArpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Configure - Config Child 1"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_EventContext 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_EventContext,   \
                 &@R_ResolvedEvent, &@R_Status"
GetAck

set L_Filter "ether proto \\arp and src host 172.16.210.102"
StartCapture CCB $L_Filter

SetEthMacAddress R_TargetHwAddress 01:01:01:01:01:01
set R_TargetHwAddress [GetEthMacAddress R_TargetHwAddress]
puts $R_TargetHwAddress
SetIpv4Address R_TargetSwAddress.v4 "172.16.210.161"
Arp->Request {&@R_TargetSwAddress, @R_ResolvedEvent, &@R_TargetHwAddress,      \
	            &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_READY]

ReceiveCcbPacket CCB TmpPkt 6
set count ${CCB.received}
if {$count != 1} {
  set assert fail
}
ReceiveCcbPacket CCB TmpPkt 6
set count ${CCB.received}
if {$count != 1} {
  set assert fail
}
ReceiveCcbPacket CCB TmpPkt 6
set count ${CCB.received}
if {$count != 1} { 
  set assert fail
}
ReceiveCcbPacket CCB TmpPkt 6
set count ${CCB.received}
if {$count != 1} { 
  set assert fail
}
ReceiveCcbPacket CCB TmpPkt 6
set count ${CCB.received}
if {$count != 1} { 
  set assert fail
}
ReceiveCcbPacket CCB TmpPkt 6
set count ${CCB.received}
if {$count != 1} { 
  set assert fail
}

RecordAssertion $assert $ArpConfigureFuncAssertionGuid007                      \
                "Arp.Request - packet count is correct when                    \
                 ArpConfigData.RetryCount is 5"                                \
                "Expected - 5 packets in 25 seconds"                           \
#
# wait for the request signaling
Stall 5
GetVar R_EventContext
if {$R_EventContext != 1} {
  set assert fail
} else {
  set assert pass
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Request - Send request"                                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_READY,    \
                 Context - $R_EventContext, ExpectedContext - 1"

set R_TargetHwAddress [GetEthMacAddress R_TargetHwAddress]
if {[string compare -nocase $R_TargetHwAddress 00:00:00:00:00:00] == 0} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Request - TargetHwAddress is correct"                     \
                "Get - $R_TargetHwAddress, Expected - 00:00:00:00:00:00"
ArpDestroy

BS->CloseEvent "@R_ResolvedEvent, &@R_Status"
GetAck

CleanUpEutEnvironment
