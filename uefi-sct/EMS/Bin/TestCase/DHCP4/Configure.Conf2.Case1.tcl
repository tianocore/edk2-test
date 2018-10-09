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
CaseGuid        1e99388c-42ad-4607-bde0-a4b8fb54a9dd
CaseName        Configure.Conf2.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_ACCESS_DENIED      \
	              -- Another instance is already in a valid configured state.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
	Dhcp4ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
  GetAck
     
  Dhcp4ServiceBinding->DestroyChild "@R_Handle2, &@R_Status"
  GetAck  

  EndScope _DHCP4_CONFIGURE_CONF2
  EndLog
}

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_CONFIGURE_CONF2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_Handle1
UINTN                             R_Handle2

EFI_DHCP4_CONFIG_DATA             R_ConfigData
UINT32                            R_Timeout(2)

#
# Call [DHCP4SBP] -> CreateChild to create Child1
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1

#
# Call [DHCP4SBP] -> CreateChild to create Child2
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle2, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Create Child 2"                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Configure to initialize Child1
#


SetVar    R_Timeout(0)                    2
SetVar    R_Timeout(1)                    5
SetVar    R_ConfigData.DiscoverTryCount   2
SetVar    R_ConfigData.DiscoverTimeout    &@R_Timeout

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Configure Child 1"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Configure () to initialize child2
#
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2

#
# Check Point: Call Dhcp4.Configure Configure Child 2 While Child 1 Control.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ACCESS_DENIED]
RecordAssertion $assert $Dhcp4ConfigureConf2AssertionGuid001                   \
                "Dhcp4.Configure - Configure Child 2 While Child 1 Control"    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ACCESS_DENIED"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment