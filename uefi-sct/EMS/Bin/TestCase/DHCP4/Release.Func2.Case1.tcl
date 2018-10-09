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
CaseGuid        114f0624-aeb7-4152-af1e-299607dcbeb5
CaseName        Release.Func2.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
	              -- in DhcpInitReboot State}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
	Dhcp4->Stop "&@R_Status"
  GetAck
  
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck
  
  EndScope _DHCP4_RELEASE_FUNC1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_RELEASE_FUNC1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

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
# Call [DHCP4] -> Configure to configure this child.
# o	DiscoverRetryCount=2, DiscoverTimeout=5,10
# o	RequestRetryCount=2, RequestTimeout=5,10
# o	ClientAddress=192.168.2.4
# o	Dhcp4CallBack=NULL
# o	OptionCount=0, OptionList=NULL
#
SetVar  R_Timeout(0)                         5
SetVar  R_Timeout(1)                         10
SetVar  R_ConfigData.DiscoverTryCount        2
SetVar  R_ConfigData.DiscoverTimeout         &@R_Timeout
SetVar  R_ConfigData.RequestTryCount         2
SetVar  R_ConfigData.RequestTimeout          &@R_Timeout
SetIpv4Address  R_ConfigData.ClientAddress   "192.168.2.4"

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Conf - Configure Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Mode Data Before Release
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State
  set tempaddr [GetIpv4Address  R_ModeData.ConfigData.ClientAddress]
  if [string compare -nocase $tempaddr "192.168.2.4"] {
    set assert fail
  } else {
    if { ${R_ModeData.State} != $Dhcp4InitReboot } {
      set assert fail
    }
  }
  unset tempaddr
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Release - Func - CHeck IP-addr in Dhcp4InitReboot State"\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "Cur State - ${R_ModeData.State}, Expected State -             \
                $Dhcp4InitReboot"

#
# Check Point: Call [DHCP4] -> Release in DhcpInitReboot State to release 
#              current address configuration.
#
Dhcp4->Release "&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4ReleaseFunc2AssertionGuid001                     \
                "Dhcp4.Release - Func - Call Release in Dhcp4InitReboot State."\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Mode Data After Release
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State
  set tempaddr [GetIpv4Address  R_ModeData.ClientAddress]
  if [string compare -nocase $tempaddr "0.0.0.0"] {
    set assert fail
  } else {
    if { ${R_ModeData.State} != $Dhcp4Init } {
      set assert fail
    }
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Release - Func - in Dhcp4Init State - Check             \
                ClientAddress After Release."                                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "Cur State - ${R_ModeData.State}, Expected State - $Dhcp4Init"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment