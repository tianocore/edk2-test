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
CaseGuid           ED14AEB0-C793-4fa3-A35F-7B674CC260F1
CaseName           Routes.Conf5.Case1
CaseCategory       IP6
CaseDescription    { Test the Routes Function of IP6 - invoke Routes()              \
                     when GateWayAddress is one of configured local IPv6 addresses  \
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
BeginScope        IP6_ROUTES_CONF5_CASE1_

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

EFI_IP6_CONFIG_DATA                R_Ip6ConfigData
SetVar            R_Ip6ConfigData.DefaultProtocol     0x11;     #Next Header: UDP
SetVar            R_Ip6ConfigData.AcceptAnyProtocol   FALSE
SetVar            R_Ip6ConfigData.AcceptIcmpErrors    TRUE
SetVar            R_Ip6ConfigData.AcceptPromiscuous   FALSE
SetIpv6Address    R_Ip6ConfigData.DestinationAddress  "::"
SetIpv6Address    R_Ip6ConfigData.StationAddress      "::"
SetVar            R_Ip6ConfigData.TrafficClass        0
SetVar            R_Ip6ConfigData.HopLimit            64
SetVar            R_Ip6ConfigData.FlowLabel           0
SetVar            R_Ip6ConfigData.ReceiveTimeout      50000
SetVar            R_Ip6ConfigData.TransmitTimeout     50000

#
# Configure the child with valid parameter.
#
Ip6->Configure  "&@R_Ip6ConfigData, &@R_Status"
GetAck
set assert       [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion  $assert   $GenericAssertionGuid              \
                 "Ip6->Configure - Conf - Configure Child "                \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

EFI_IP6_MODE_DATA                 R_Ip6ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA   R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE           R_SnpModeData

#
# Call GetModeData Function to get the link_local Address.
#
Ip6->GetModeData "&@R_Ip6ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status"
GetAck
set assert       [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion  $assert  $GenericAssertionGuid                \
                 "Ip6->GetModeData -Conf - Get  link_local Address"        \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
GetVar                R_Ip6ModeData

EFI_IP6_ADDRESS_INFO  R_Ip6AddressList
UINTN                 R_CopyLen
SetVar     R_CopyLen  [Sizeof R_Ip6AddressList]

BS->CopyMem           "&@R_Ip6AddressList, @R_Ip6ModeData.AddressList, @R_CopyLen, &@R_Status"
GetAck

EFI_IPv6_ADDRESS      R_GatewayAddress
SetIpv6Address        R_GatewayAddress   [GetIpv6Address R_Ip6AddressList.Address]
BOOLEAN                                  R_DeleteRoute
SetVar                R_DeleteRoute      FALSE
EFI_IPv6_ADDRESS                         R_Destination
SetIpv6Address        R_Destination      "::"
UINT8                                    R_PrefixLength
SetVar                R_PrefixLength     16

#
# Check point:Call Routes Function when *GatewayAddress is one of configured local IPv6 addresses.
#            EFI_INVALID_PARAMETER should be returned.
#
Ip6->Routes     "@R_DeleteRoute, &@R_Destination, @R_PrefixLength, &@R_GatewayAddress,&@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip6RoutesConf5AssertionGuid001                  \
                "Ip6->Routes - Conf - Add  Route "                                \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_INVALID_PARAMETER "
#
# Destroy Child
#
Ip6ServiceBinding->DestroyChild  "@R_Handle, &@R_Status"
GetAck
set assert        [VerifyReturnStatus  R_Status $EFI_SUCCESS]
RecordAssertion   $assert  $GenericAssertionGuid                 \
                  "Ip6SB->DestroyChild - Conf - Destroy Child"              \
                  "RetrunStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# End scope
#
EndScope          IP6_ROUTES_CONF5_CASE1_
#
# End log
#
EndLog
