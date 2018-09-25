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
CaseLevel          CONFORMANCE
CaseAttribute      AUTO
CaseVerboseLevel   DEFAULT
set reportfile     report.csv

#
# Test Case Name, Category, Description, GUID ...
#
CaseGuid           3859B62A-9BA9-438a-A2AE-D465C2E5596A
CaseName           Neighbors.Conf3.Case1
CaseCategory       IP6
CaseDescription    { Test the Neighbors Function of IP6 - invoke Neighbors()     \
                     when TargetLinkAddress is NULL and DeleteFlag is TRUE       \
                     EFI_INVALID_PARAMETER should be returned.
                   }
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin  log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope     IP6_NEIGHBORS_CONF3_CASE1_

# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_Handle 

#
# Create Child
#
Ip6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert       [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion  $assert $GenericAssertionGuid               \
                 "Ip6SB->CreateChild - Conf - Create Child "             \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
SetVar  [subst $ENTS_CUR_CHILD]    @R_Handle

EFI_IP6_CONFIG_DATA                                   R_Ip6ConfigData
SetVar R_Ip6ConfigData.DefaultProtocol                0x11;        #Next Header: UDP
SetVar R_Ip6ConfigData.AcceptAnyProtocol              FALSE
SetVar R_Ip6ConfigData.AcceptIcmpErrors               TRUE
SetVar R_Ip6ConfigData.AcceptPromiscuous              FALSE
SetIpv6Address R_Ip6ConfigData.DestinationAddress     "::"
SetIpv6Address R_Ip6ConfigData.StationAddress         "::"
SetVar R_Ip6ConfigData.TrafficClass                   0
SetVar R_Ip6ConfigData.HopLimit                       64
SetVar R_Ip6ConfigData.FlowLabel                      0
SetVar R_Ip6ConfigData.ReceiveTimeout                 50000
SetVar R_Ip6ConfigData.TransmitTimeout                50000

#
# Configure Child with valid parameter
#
Ip6->Configure       "&@R_Ip6ConfigData, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                \
                "Ip6->Configure - Conf - Configure Child  "               \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

BOOLEAN                                    R_DeleteFlag
SetVar                R_DeleteFlag         TRUE
EFI_IPv6_ADDRESS                           R_TargetIp6Address
SetIpv6Address        R_TargetIp6Address   "::"
EFI_MAC_ADDRESS                            R_TargetLinkAddress
SetEthMacAddress      R_TargetLinkAddress  "00:00:00:00:00:00"
UINT32                                     R_Timeout
SetVar                R_Timeout            0
BOOLEAN                                    R_Override
SetVar                R_Override           FALSE

#
#Check point: Call Neighbors when TargetLinkAddress is NULL and DeleteFlag is TRUE.
#             EFI_INVALID_PARAMETER should be returned.
#
Ip6->Neighbors   "@R_DeleteFlag, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, @R_Override, &@R_Status"
GetAck
set assert       [VerifyReturnStatus  R_Status  $EFI_INVALID_PARAMETER]
RecordAssertion  $assert $Ip6NeighborsConf3AssertionGuid001                        \
                 "Ip6->Neighbors - Conf - Add or Delete a neighbor "                            \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_INVALID_PARAMETER"

#
#Destroy Child
#
Ip6ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert        [VerifyReturnStatus  R_Status $EFI_SUCCESS]
RecordAssertion   $assert  $GenericAssertionGuid                 \
                  "Ip6SB->DestroyChild - Conf - Destroy Child"              \
                  "RetrunStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
#End scope
#
EndScope         IP6_NEIGHBORS_CONF3_CASE1_
#
#End log
#
EndLog
