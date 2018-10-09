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
CaseGuid           5874A735-3005-4d5d-8B2F-287601BAD692
CaseName           Neighbors.Conf1.Case1
CaseCategory       IP6
CaseDescription    { Test the Neighbors Function of IP6 - invoke Neighbors()     \
                     when the instance has not been configured.                  \
                     EFI_NOT_STARTED should be returned.
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
BeginScope        IP6_NEIGHBORS_CONF1_CASE1_

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
SetVar     [subst $ENTS_CUR_CHILD]    @R_Handle

BOOLEAN                                    R_DeleteFlag
SetVar                R_DeleteFlag         FALSE
EFI_IPv6_ADDRESS                           R_TargetIp6Address
SetIpv6Address        R_TargetIp6Address   "2002::1"
EFI_MAC_ADDRESS                            R_TargetLinkAddress
SetEthMacAddress      R_TargetLinkAddress  "00:97:3B:34:CD:9A"
UINT32                                     R_Timeout
SetVar                R_Timeout            0
BOOLEAN                                    R_Override
SetVar                R_Override           FALSE

#
# Check point:Call Neighbors Function when the instance has not been configured.
#             EFI_NOT_STARTED should be returned.
#
Ip6->Neighbors   "@R_DeleteFlag, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, @R_Override, &@R_Status"
GetAck
set assert       [VerifyReturnStatus  R_Status  $EFI_NOT_STARTED]
RecordAssertion  $assert $Ip6NeighborsConf1AssertionGuid001                        \
                 "Ip6->Neighbors - Conf - Add or Delete a neighbor "                            \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_NOT_STARTED"

#
# Destroy Child
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert        [VerifyReturnStatus  R_Status $EFI_SUCCESS]
RecordAssertion   $assert  $GenericAssertionGuid                 \
                  "Ip6SB->DestroyChild - Conf - Destroy Child"              \
                  "RetrunStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
  
#
# End scope
#
EndScope         IP6_NEIGHBORS_CONF1_CASE1_
#
# End log
#
EndLog
