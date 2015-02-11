#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
#
################################################################################
CaseLevel          CONFORMANCE
CaseAttribute      AUTO
CaseVerboseLevel   DEFAULT
set reportfile     report.csv

#
# Test Case Name, Category, Description, GUID ...
#
CaseGuid           F5085BB2-789F-4e3a-9078-98435B61B263
CaseName           Neighbors.Conf6.Case1
CaseCategory       IP6
CaseDescription    { Test the Neighbors Function of IP6 - invoke Neighbors()        \
                     when TargetIpAddress is one of configured local Ipv6 address   \
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
BeginScope        IP6_NEIGHBORS_CONF6_CASE1_

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
Ip6->Configure   "&@R_Ip6ConfigData, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                \
                "Ip6->Configure - Conf - Configure Child  "               \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

EFI_IP6_MODE_DATA                     R_Ip6ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA       R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE               R_SnpModeData

#
# GetModeData
#
Ip6->GetModeData  "&@R_Ip6ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                 \
                "Ip6->GetModeData - Conf - Get Child Configure in order to get link_local Address"  \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
GetVar                   R_Ip6ModeData

EFI_IP6_ADDRESS_INFO     R_Ip6AddressList
UINTN                    R_CopyLen
SetVar       R_CopyLen   [Sizeof R_Ip6AddressList]

BS->CopyMem  "&@R_Ip6AddressList, @R_Ip6ModeData.AddressList, @R_CopyLen, &@R_Status"
GetAck

BOOLEAN                                    R_DeleteFlag
SetVar                R_DeleteFlag         TRUE
EFI_IPv6_ADDRESS                           R_TargetIp6Address 
SetIpv6Address        R_TargetIp6Address   [GetIpv6Address R_Ip6AddressList.Address] 
EFI_MAC_ADDRESS                            R_TargetLinkAddress
SetEthMacAddress      R_TargetLinkAddress  $DEF_ENTS_MAC_ADDR
UINT32                                     R_Timeout
SetVar                R_Timeout            0
BOOLEAN                                    R_Override
SetVar                R_Override           FALSE

#
# Check point:Call Neighbors when *TargetIpAddress is one of configured local IPv6 address.
#             EFI_INVALID_PARAMETER should be returned.
#
Ip6->Neighbors "@R_DeleteFlag, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, @R_Override, &@R_Status"
GetAck
set assert       [VerifyReturnStatus  R_Status  $EFI_INVALID_PARAMETER]
RecordAssertion  $assert $Ip6NeighborsConf6AssertionGuid001                        \
                 "Ip6->Neighbors - Conf - Add or Delete a neighbor "                            \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_INVALID_PARAMETER"

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
EndScope          IP6_NEIGHBORS_CONF6_CASE1_
#
# End log
#
EndLog
