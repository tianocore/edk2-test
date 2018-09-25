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
CaseGuid        0E12D2E9-5AF2-4367-BC3A-9E97CB73F5C8
CaseName        MCastIpToMac.Conf3.Case1
CaseCategory    MNP
CaseDescription {Test Conformance of MCastIPToMac of MNP - Call McastlpToMac() \
	               with the parameter Ipv6Flag is TRUE. The return status should \
	               be EFI_UNSUPPORTED.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _MNP_MCASTIPTOMAC_CONFORMANCE3_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA   R_MnpConfData
EFI_IP_ADDRESS                    R_IpAddr
EFI_MAC_ADDRESS                   R_MacAddr
#
# Create child R_Handle
#
MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.MCaseIpToMac - Conf1 - create child"                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"	
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

SetIpv4Address      R_IpAddr.v4  "234.1.1.1"

#
# Configure this child 
#
SetMnpConfigData R_MnpConfData 0 0 0 TRUE FALSE TRUE TRUE FALSE FALSE TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.MCaseIpToMac - Invalid parameter - Configure"             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call MCastIpToMac with invalid parameters
# D). Ipv6Flag=TRUE
#
Mnp->MCastIpToMac   "TRUE, &@R_IpAddr, &@R_MacAddr, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $MnpMCastIpToMacConf3AssertionGuid001                  \
                "Mnp.MCastIpToMac - Invalid Parameter - Ipv6Flag=TRUE"               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

DestructVar R_IpAddr R_MacAddr

#
# Destroy child R_Handle
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.MCaseIpToMac - Conf1 - destroy child"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

DestructVar R_Status R_Handle R_MnpConfData

EndScope  _MNP_MCASTIPTOMAC_CONFORMANCE3_CASE1_

#
# End log
#
EndLog
