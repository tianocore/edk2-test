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
CaseGuid        4f94bd03-2f46-4c02-bf21-987b16eaa043
CaseName        Configure.Func2.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
                -- A) Access denied when another DHCP instance is already in a \
                valid state.                                                   \
                   B)if one instance wants to make it possible for another     \
                 instance, it must call Dhcp4->Configure with  DhcpCfgData     \
                 set to Null. }

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
  GetAck

  Dhcp4ServiceBinding->DestroyChild "@R_Handle2, &@R_Status"
  GetAck

  EndScope _DHCP4_CONFIGURE_FUNC2
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_CONFIGURE_FUNC2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                                           R_Status
UINTN                                           R_Handle1
UINTN                                           R_Handle2
UINT32                                          R_Timeout(2)
EFI_DHCP4_CONFIG_DATA                           R_ConfigData
EFI_DHCP4_MODE_DATA                             R_ModeData

#
# Call [DHCP4SBP] -> CreateChild to create child 1.
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1

#
# Call [DHCP4] -> Configure () to initialize Child 1.
#
SetVar    R_Timeout(0)                          1
SetVar    R_Timeout(1)                          2
SetVar    R_ConfigData.DiscoverTryCount         2
SetVar    R_ConfigData.DiscoverTimeout          &@R_Timeout
SetVar    R_ConfigData.RequestTryCount          2
SetVar    R_ConfigData.RequestTimeout           &@R_Timeout
SetVar    R_ConfigData.OptionCount              0
SetVar    R_ConfigData.OptionList               0                   
SetIpv4Address  R_ConfigData.ClientAddress      "192.168.1.1"
SetVar    R_ConfigData.Dhcp4Callback            0;  # CallbackList[1] = Abort
SetVar    R_ConfigData.CallbackContext          0;

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Initialize Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4SBP] -> CreateChild () to create DHCP Child2
#
Dhcp4ServiceBinding->CreateChild "&@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.CreateChild - Create Child 2"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2

#
# Check Point: Call [DHCP4] -> Configure () to initialize Child2
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ACCESS_DENIED]
RecordAssertion $assert $Dhcp4ConfigureFunc2AssertionGuid001                   \
                "Dhcp4.CreateChild - Initialzie Child 2"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ACCESS_DENIED"

#
# Check Point: Call [DHCP4] -> Configure () to reset Child1
#
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
Dhcp4->Configure "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4ConfigureFunc2AssertionGuid001                   \
                "Dhcp4.CreateChild - Reset Child 1"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call [DHCP4] -> Configure () to initialize Child2
#
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4ConfigureFunc2AssertionGuid001                   \
                "Dhcp4.CreateChild - Initialize Child 2"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment