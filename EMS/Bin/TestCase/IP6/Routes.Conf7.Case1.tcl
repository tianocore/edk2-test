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
CaseGuid           063A2D3A-53F9-4548-8AE3-BA5FEE3A8EA1
CaseName           Routes.Conf7.Case1
CaseCategory       IP6
CaseDescription    { Test the Routes Function of IP6 - invoke Routes()                           \
                     when DeleteRoute is FALSE and the entry is already in current routing table \
                     EFI_ACCESS_DENIED should be returned.
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
BeginScope        IP6_ROUTES_CONF7_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                       R_Status
UINTN                       R_Handle 

#
# Create child.
#
Ip6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Ip6SB.CreateChild - Create Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar [subst $ENTS_CUR_CHILD]          @R_Handle

#
# Address Configuration
#
UINTN                                       R_Ip6ConfigDataSize
UINT32                                      R_Ip6ConfigDataType
UINT32                                      R_Ip6ConfigPolicy
EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS    R_Ip6ConfigDadTransmits
EFI_IP6_CONFIG_MANUAL_ADDRESS               R_Ip6ConfigManualAddress

SetVar R_Ip6ConfigDataType   2
SetVar R_Ip6ConfigDataSize   4
SetVar R_Ip6ConfigPolicy     $IP6CP(Manual)
  
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigPolicy,&@R_Status"
GetAck

SetVar R_Ip6ConfigDataType   3
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS]
SetVar R_Ip6ConfigDadTransmits.DupAddrDetectTransmits 0
  
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigDadTransmits,&@R_Status"
GetAck
  
SetVar R_Ip6ConfigDataType   4
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_MANUAL_ADDRESS]
SetVar R_Ip6ConfigManualAddress.IsAnycast    FALSE
SetVar R_Ip6ConfigManualAddress.PrefixLength 64
SetIpv6Address R_Ip6ConfigManualAddress.Address $DEF_EUT_IP_ADDR
puts $DEF_EUT_IP_ADDR
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck

EFI_IP6_CONFIG_DATA                           R_Ip6ConfigData
SetVar R_Ip6ConfigData.DefaultProtocol        0x11;        #Next Header: UDP
SetVar R_Ip6ConfigData.AcceptAnyProtocol      FALSE
SetVar R_Ip6ConfigData.AcceptIcmpErrors       TRUE
SetVar R_Ip6ConfigData.AcceptPromiscuous      FALSE
SetIpv6Address R_Ip6ConfigData.DestinationAddress     "::"
SetIpv6Address R_Ip6ConfigData.StationAddress         $DEF_EUT_IP_ADDR
SetVar R_Ip6ConfigData.TrafficClass           0
SetVar R_Ip6ConfigData.HopLimit               64
SetVar R_Ip6ConfigData.FlowLabel              0
SetVar R_Ip6ConfigData.ReceiveTimeout         50000
SetVar R_Ip6ConfigData.TransmitTimeout        50000

#
# Configure this child with valid parameter.
#
Ip6->Configure "&@R_Ip6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6.Configure - Func - Configure child with valid parameter"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Add a Neighbor cache
# Call Neighbors with 
#                         DeleteFlag = FALSE
#                         TargetIp6Address = 
#                         TargetLinkAddress = 
#                         Timeout = 0
#                         Override = TRUE
#              EFI_SUCCESS should be returned.
#
EFI_IPv6_ADDRESS                              R_TargetIp6Address
SetIpv6Address R_TargetIp6Address             $DEF_ENTS_IP_ADDR
EFI_MAC_ADDRESS                               R_TargetLinkAddress             
SetEthMacAddress R_TargetLinkAddress          $DEF_ENTS_MAC_ADDR
UINT32                                        R_Timeout
SetVar R_Timeout                              0

Ip6->Neighbors "FALSE, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, TRUE, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6.Neighbors - Func - Add a neighbor entry"               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Add a route cache
# Call Routes with DeleteRoute = FALSE and *Destination = 2002::2
#              and PrefixLength = 16 and *GatewayAddress = 2002::1
#              EFI_SUCCESS should be returned.
#
EFI_IPv6_ADDRESS                              R_Destination
SetIpv6Address R_Destination                  "2002::2"
UINT8                                         R_PrefixLength
SetVar R_PrefixLength                         16
EFI_IPv6_ADDRESS                              R_GatewayAddress
SetIpv6Address R_GatewayAddress               "2002::1"
Ip6->Routes "FALSE, &@R_Destination, @R_PrefixLength, &@R_GatewayAddress, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6->Routes - Conf - Add Route "                        \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

#
# Check Point: Call Routes again,EFI_ACCESS_DENIED should be returned
#
Ip6->Routes "FALSE, &@R_Destination, @R_PrefixLength, &@R_GatewayAddress, &@R_Status"
GetAck
set assert      [VerifyReturnStatus  R_Status  $EFI_ACCESS_DENIED]
RecordAssertion $assert $Ip6RoutesConf7AssertionGuid001            \
                "Ip6->Routes -Conf- Call Routes again"                        \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_ACCESS_DENIED"

#
# Check Point: Call Routes to delete the route that has added to avoid influenting other cases.
#
Ip6->Routes "TRUE, &@R_Destination, @R_PrefixLength, &@R_GatewayAddress, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6->Routes - Conf - Delete Route "                        \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

#
# Clean: Delete the neighbor cache
#
Ip6->Neighbors "TRUE, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, TRUE, &@R_Status"
GetAck
                
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
EndScope          IP6_ROUTES_CONF7_CASE1_
#
# End log
#
EndLog
