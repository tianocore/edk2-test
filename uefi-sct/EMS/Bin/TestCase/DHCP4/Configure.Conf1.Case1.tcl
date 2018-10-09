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
CaseGuid        20a758ca-c031-4c00-80e4-5bb63e413a73
CaseName        Configure.Conf1.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_ACCESS_DENIED      \
	              -- This driver instance was not in the Dhcp4Stopped, Dhcp4Init,\
	              Dhcp4InitReboot, or Dhcp4Bound state.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_CONFIGURE_CONF1
  EndLog
}

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_CONFIGURE_CONF1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                   R_Status
UINTN                                   R_Handle

EFI_DHCP4_CONFIG_DATA                   R_ConfigData
UINT32                                  R_Timeout(2)

EFI_DHCP4_MODE_DATA                     R_ModeData

UINTN                                   R_Event
UINTN                                   R_Context
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
# Call [DHCP4] -> Configure to initialize this child
# o	DiscoverRetryCount=2, DiscoverTimeout=10,20
# o	RequestRetryCount=2, RequestTimeout=10,20
# o	ClientAddress=0.0.0.0
# o	Dhcp4CallBack=NULL
# o	OptionCount=0, OptionList=NULL
#
SetVar  R_Timeout(0)                           10
SetVar  R_Timeout(1)                           20
SetVar  R_ConfigData.DiscoverTryCount          2
SetVar  R_ConfigData.DiscoverTimeout           &@R_Timeout
SetVar  R_ConfigData.RequestTryCount           0
SetVar  R_ConfigData.RequestTimeout            0
SetIpv4Address R_ConfigData.ClientAddress      "0.0.0.0"

Dhcp4->Configure  "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Start Child"                                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Start to start DHCP4 configuration process, 
#        require to signal event when DHCP4 configuration process complete.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                &@R_Event, &@R_Status"
GetAck

set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Dhcp4->Start  "@R_Event, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Start DHCP4 config process"                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Configure to change DHCP4 operation parameter 
#        before DHCP4 configuration process complete.
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.GetModeData - Get Mode Data."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar  R_ModeData.State
SetVar  R_ConfigData.RequestTryCount    2
SetVar  R_ConfigData.RequestTimeout     &@R_Timeout

#
# Check Point: Call Dhcp4.Configure when the state is not in the Dhcp4Stopped, 
#              Dhcp4Init, Dhcp4InitReboot, or Dhcp4Bound state.
#
Dhcp4->Configure  "&@R_ConfigData, &@R_Status"
GetAck
set assert pass
GetVar     R_Context
if { $R_Context > 0 } {
  set assert fail
}

GetVar    R_Status
if { [string compare -nocase $assert "pass"] == 0 } {
  set assert [VerifyReturnStatus R_Status $EFI_ACCESS_DENIED]
}
RecordAssertion $assert $Dhcp4ConfigureConf1AssertionGuid001                   \
                "Dhcp4.Configure - Configure to change while in                \
                DHCP config process"                                           \
                "ReturnedStatus - $R_Status, ExpectedStatus -                  \
                $EFI_ACCESS_DENIED"                                            \
                "Event signed:  Returned - $R_Context, Expected - 0"           \
                "State: Returned - ${R_ModeData.State}, Expected - 2"          \

#
# Call [DHCP4] -> Stop to stop the DHCP Driver
#
Dhcp4->Stop "&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Stop - Stop Driver."                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Close Event
#
BS->CloseEvent "@R_Event, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CloseEvent."                                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment