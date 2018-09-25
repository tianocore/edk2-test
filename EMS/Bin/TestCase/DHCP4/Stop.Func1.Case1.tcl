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
############################################
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        593ba48d-fb3f-447f-9237-8a3f4690fbd2
CaseName        Stop.Func1.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
	              -- Call Stop in DhcpInitReboot State.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_STOP_FUNC1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_STOP_FUNC1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                                           R_Status
UINTN                                           R_Handle

EFI_DHCP4_CONFIG_DATA                           R_ConfigData
UINT32                                          R_Timeout(2)

EFI_DHCP4_MODE_DATA                             R_ModeData

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
# o	RequestRetryCount=2, RequestTimeout=1,2
# o	ClientAddress=192.168.2.4
# o	Dhcp4CallBack=NULL
# o	OptionCount=0, OptionList=NULL
#
SetVar  R_Timeout(0)                           5
SetVar  R_Timeout(1)                           10
SetVar  R_ConfigData.DiscoverTryCount          2
SetVar  R_ConfigData.DiscoverTimeout           &@R_Timeout
SetVar  R_ConfigData.RequestTryCount           2
SetVar  R_ConfigData.RequestTimeout            &@R_Timeout
SetVar  R_ConfigData.Dhcp4Callback             0;  # CallbackList[1] = Abort
SetVar  R_ConfigData.CallbackContext           0
SetVar  R_ConfigData.OptionCount               0
SetIpv4Address R_ConfigData.ClientAddress      "192.168.2.4"

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Func - Configure Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Mode Data After Start Exit
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State
  set tempaddr [GetIpv4Address R_ModeData.ClientAddress]
  if { ${R_ModeData.State} != $Dhcp4InitReboot } {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Func - Check the DHCP instance State"           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "CurState - ${R_ModeData.State}, ExpectState - $Dhcp4InitReboot"

#  
# Check Point: Call [DHCP4] -> Stop to stop DHCP4 configuration process
#
Dhcp4->Stop  "&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4StopFunc1AssertionGuid001                        \
                "Dhcp4.Stop - Function - Stop Driver In DhcpInitReboot State." \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment