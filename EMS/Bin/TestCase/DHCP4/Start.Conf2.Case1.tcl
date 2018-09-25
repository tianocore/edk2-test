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
CaseGuid        d7a98ef7-0170-44cf-bc98-e1e2ee89e893
CaseName        Start.Conf2.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the the Conformance - EFI_TIMEOUT        \
	              -- No Response with in the specified timeout value.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

proc CleanUpEutEnvironment {} {	
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

	EndCapture
  EndScope _DHCP4_START_CONF2
  EndLog
}

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_START_CONF2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                       R_Status
UINTN                                       R_Handle

EFI_DHCP4_CONFIG_DATA                       R_ConfigData
UINT32                                      R_Timeout(2)

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
# Call [DHCP4]->Configure to initialize the child with the following parameters
# o	DiscoverRetryCount=2, DiscoverTimeout=5,10
# o	RequestRetryCount=2, RequestTimeout=5,10
# o	ClientAddress=0.0.0.0
# o	Dhcp4CallBack=NULL
# o	OptionCount=1, OptionList=ClientIdentifier
#                                            
SetVar  R_Timeout(0)                        5
SetVar  R_Timeout(1)                        10
SetVar  R_ConfigData.DiscoverTryCount       2
SetVar  R_ConfigData.DiscoverTimeout        &@R_Timeout
SetVar  R_ConfigData.RequestTryCount        2
SetVar  R_ConfigData.RequestTimeout         &@R_Timeout
SetIpv4Address  R_ConfigData.ClientAddress  "0.0.0.0"
SetVar  R_ConfigData.Dhcp4Callback          0;  # CallbackList[1] = Abort
SetVar  R_ConfigData.CallbackContext        0


Dhcp4->Configure  "&@R_ConfigData, &@R_Status"
GetAck
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Create Child 1"                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Start to start DHCP4 configuration process.
# o	CompletionEvnet = NULL
#
set L_Filter "udp src port 68 and ether host $targetmac"
StartCapture CCB $L_Filter

#
# Check Point: Call Dhcp4.Start when No Response with in the specified 
#              timeout value.
#
Dhcp4->Start "0, &@R_Status"

#
# "	On manager side
#  Respond to the DHCP4 Client in the following message sequence
#  A). Capture and validate DHCPDISCOVER packet 
#  B). Not respond to the DHCPDISCOVER packet
#
ReceiveCcbPacket CCB discoverpacket 30
if { ${CCB.received} == 0} {
	set assert fail
	GetAck
	RecordAssertion $assert $Dhcp4StartConf2AssertionGuid001                     \
                  "Dhcp4.Start - No DHCPDISCOVER packet Captured."
	
	CleanUpEutEnvironment 
  return
} else {
  set assert pass
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPDISCOVER Packets"

#
# GetAck from EFI
#
Stall      30
GetAck
set assert [VerifyReturnStatus R_Status $EFI_TIMEOUT]
RecordAssertion $assert $Dhcp4StartConf2AssertionGuid001                       \
                "Dhcp4.Start - No Response with in the specified timeout value"\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_TIMEOUT"

#
# R_ModeData.State shoudle be "DhcpInit"
#
EFI_DHCP4_MODE_DATA     R_ModeData
Dhcp4->GetModeData  "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
GetVar      R_ModeData.State
if {${R_ModeData.State} != $Dhcp4Init} {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.GetModeData - Get Mode Date to verify the State"        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS,      \
                ExpectDHCPStatus - $Dhcp4Init, CurDHCPStatus -                 \
                ${R_ModeData.State}"

#
# Call Dhcp4->Stop to stop the driver
#
Dhcp4->Stop "&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Stop - Stop Driver."                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment