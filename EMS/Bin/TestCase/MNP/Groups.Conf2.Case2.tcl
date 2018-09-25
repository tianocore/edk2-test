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
CaseGuid        24BDCC37-4360-4d6f-9778-AF27D9635B13
CaseName        Groups.Conf2.Case2
CaseCategory    MNP
CaseDescription {Test the conformance of Groups function - Call MNP.Groups()   \
	               with the parameter *MacAddress being a invalid multicast MAC  \
	               address. The return status should be EFI_INVALID_PARAMETER.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _MNP_GROUPS_CONFORMANCE2_CASE2_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfData
EFI_MAC_ADDRESS                  R_MacAddr

#
# Create child R_Handle
# 
MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Conf1 - create child"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar          [subst $ENTS_CUR_CHILD]  @R_Handle

SetEthMacAddress  R_MacAddr "01:00:5e:00:00:01"

#
# Configure this child
#
SetMnpConfigData R_MnpConfData 0 0 0 TRUE FALSE TRUE TRUE FALSE FALSE TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Conf1 - Configure"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Groups with invalid parameter
# *MacAddress is not a valid multicast MAC address
#
SetEthMacAddress R_MacAddr "00:01:01:01:01:01"
Mnp->Groups "TRUE, &@R_MacAddr, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $MnpGroupsConf2AssertionGuid002                        \
                "Mnp.Groups - Conf1 - Call Groups with invalid parameter -     \
                MacAddress is not a valid multicast MAC address."              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy child R_Handle
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Groups - Conf1 - destroy child"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope _MNP_GROUPS_CONFORMANCE2_CASE2_

#
# End log
#
EndLog
