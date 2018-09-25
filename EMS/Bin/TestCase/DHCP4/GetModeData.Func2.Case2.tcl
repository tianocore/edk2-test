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
CaseGuid        e1e160f3-697f-41e8-87a9-dc127b65ba01
CaseName        GetModeData.Func2.Case2
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
 	              -- During the Configuration Process}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

proc CleanUpEutEnvironment {} {
  Dhcp4->Stop "&@R_Status"
  GetAck

  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  BS->CloseEvent "@R_Event, &@R_Status"
  GetAck

  EndCapture
  EndScope _DHCP4_GETMODEDATA_FUNC2
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_GETMODEDATA_FUNC2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

UINTN                            R_Event
UINTN                            R_Context

EFI_DHCP4_CONFIG_DATA            R_ConfigData
UINT32                           R_Timeout(2)
EFI_DHCP4_MODE_DATA              R_ModeData
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
# create Event.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                &@R_Event, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  "BS.CreateEvent."               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Configure to start Child, set its operational parameter
# to the following setting.
# o	DiscoverRetryCount=2, DiscoverTimeout=5,10
# o	RequestRetryCount=2, RequestTimeout=5,10
# o	ClientAddress=0.0.0.0
# o	Dhcp4CallBack=NULL
# o	OptionCount=1, OptionList=ClientIdentifier
#
SetVar  R_Timeout(0)                          5
SetVar  R_Timeout(1)                          10
SetVar  R_ConfigData.DiscoverTryCount         2
SetVar  R_ConfigData.DiscoverTimeout          &@R_Timeout
SetVar  R_ConfigData.RequestTryCount          2
SetVar  R_ConfigData.RequestTimeout           &@R_Timeout
SetIpv4Address  R_ConfigData.ClientAddress    "192.168.1.24"
SetVar  R_ConfigData.Dhcp4Callback            0;  # CallbackList[1] = Abort
SetVar  R_ConfigData.CallbackContext          0

#
# Build an option of ClientIdentifier
#
UINT8     R_ClientIdOpt(9)
SetVar    R_ClientIdOpt                       {61 7 1 0 1 2 3 4 5}
POINTER   R_OptionPtr
SetVar    R_OptionPtr                         &@R_ClientIdOpt
SetVar    R_ConfigData.OptionCount            1
SetVar    R_ConfigData.OptionList             &@R_OptionPtr

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Configure Child 1"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Dhcp4.GetModeData to verify in the Dhcp4InitReboot State.
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar    R_ModeData.State
  if { ${R_ModeData.State} != $Dhcp4InitReboot } {
    set assert fail
  }
}
RecordAssertion $assert $Dhcp4GetModeDataFunc2AssertionGuid002                 \
                "Dhcp4.GetModeData - Get Mode Data in Dhcp4InitReboot State"   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "Cur State - ${R_ModeData.State}, Expected State -             \
                $Dhcp4InitReboot"

#
# Call [DHCP4] -> Start to start DHCP4 Configuration process
# setfilter to verify to capture DHCPDISCOVER packet
#
set L_Filter "udp src port 68 and ether host $targetmac"
StartCapture CCB $L_Filter

Dhcp4->Start  "@R_Event, &@R_Status"
GetAck

#
# "	On manager side
# Respond in the following message sequence
# Step4: Sequence A
# 	1). Capture and validate DHCPREQUEST packet
# 	2). Respond with DHCPOACKS packet to DHCP client
#
ReceiveCcbPacket CCB discoverpacket 15
if { ${CCB.received} == 0} {
	set assert fail

	CleanUpEutEnvironment 
  return
} else {
  set assert pass
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPREQUEST Packets"

#
# Check Ack for Dhcp4->Start
#
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Start DHCP4 config process"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Dhcp4.GetModeData to verify in the Dhcp4Rebooting State.
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar    R_ModeData.State
  if { ${R_ModeData.State} != $Dhcp4Rebooting } {
    set assert fail
  }
}
RecordAssertion $assert $Dhcp4GetModeDataFunc2AssertionGuid002                 \
                "Dhcp4.GetModeData - Get Mode Data in Dhcp4Rebooting State"    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "Cur State - ${R_ModeData.State}, Expected State -             \
                $Dhcp4Rebooting"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
