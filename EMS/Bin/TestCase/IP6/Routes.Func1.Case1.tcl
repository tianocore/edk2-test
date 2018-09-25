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
CaseGuid        D9E56181-F23B-463d-92AE-25EAE2589D4A
CaseName        Routes.Func1.Case1
CaseCategory    IP6
CaseDescription {Test the Routes Function of IP6 - Invoke Routes() \
                 to add and delete a route entry.}
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin Log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope   _IP6_ROUTES_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

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
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6RoutesFunc1AssertionGuid001         \
                "Ip6.Routes - Func - Add a route entry"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Call GetModeData to check the added route entry.
#
EFI_IP6_MODE_DATA                             R_Ip6ModeData
Ip6->GetModeData "&@R_Ip6ModeData, NULL, NULL, &@R_Status"
GetAck

#
# Verify Ip6ModeData.RouteCount
#
GetVar R_Ip6ModeData
set assert fail

if { ${R_Ip6ModeData.RouteCount} > 0 } {
    set assert pass
}

RecordAssertion $assert $Ip6RoutesFunc1AssertionGuid002       \
                "Ip6.Routes - Func - Check Ip6ModeData.RouteCount field"

#
# Verify Ip6ModeData.RouteTable
#
EFI_IP6_ROUTE_TABLE                           R_RouteTable(10)
UINTN                                         R_CopyLen
#
# Copy all the RouteTable items to R_RouteTable() according to RouteCount
#
set L_RouteCount ${R_Ip6ModeData.RouteCount}

SetVar R_CopyLen [ expr {$L_RouteCount * [Sizeof EFI_IP6_ROUTE_TABLE]}]
BS->CopyMem "&@R_RouteTable, @R_Ip6ModeData.RouteTable, @R_CopyLen, &@R_Status"
GetAck
GetVar R_RouteTable

#
# Search all the RouteTable, to find the added entry
#
set assert fail
EFI_IP6_ROUTE_TABLE R_RouteTableTemp
SetVar R_CopyLen [Sizeof EFI_IP6_ROUTE_TABLE]
puts "RouteCount= $L_RouteCount"
set GatewayString [GetIpv6Address R_GatewayAddress]
set DestinationString [GetIpv6Address R_Destination]
GetVar R_PrefixLength 
set assert fail
for {set i 0} {$i < $L_RouteCount} {incr i} {  
  BS->CopyMem "&@R_RouteTableTemp, &@R_RouteTable($i), @R_CopyLen, &@R_Status"
  GetAck
  GetVar R_RouteTableTemp
  #
  # verify Gateway, Destination and PrefixLength
  #
  set GatewayString1 [GetIpv6Address R_RouteTableTemp.Gateway]
  set DestinationString1 [GetIpv6Address R_RouteTableTemp.Destination]
  
  puts "Gateway Set:        $GatewayString"
  puts "Gateway Get         $GatewayString1"
  puts "Destination Set     $DestinationString"
  puts "Destination Get     $DestinationString1"
  puts "PrefixLength Set   ${R_PrefixLength}"
  puts "PrefixLength Get   ${R_RouteTableTemp.PrefixLength}"
   
  if {[string compare -nocase $GatewayString $GatewayString1] == 0} {    
    if {${R_RouteTableTemp.PrefixLength} == ${R_PrefixLength}} {
      set assert pass
      break
    }  
  }
}

RecordAssertion $assert $Ip6RoutesFunc1AssertionGuid003       \
                "Ip6.Routes - Func - Check Ip6ModeData.RouteTable field"


#
# Check point: Call Routes with DeleteRoute = TRUE and Destination = 2002::2
#              and PrefixLength = 16 and GatewayAddress = 2002::1
#              EFI_SUCCESS should be returned.
#
SetIpv6Address R_Destination                 "2002::2"
Ip6->Routes "TRUE, &@R_Destination, @R_PrefixLength, &@R_GatewayAddress, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6RoutesFunc1AssertionGuid004         \
                "Ip6.Routes - Func - Delete a route entry"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Call GetModeData to check the deleted route entry.
#
Ip6->GetModeData "&@R_Ip6ModeData, NULL, NULL, &@R_Status"
GetAck

#
# Verify Ip6ModeData.RouteCount
#
GetVar R_Ip6ModeData
set assert fail
if {[expr {$L_RouteCount - ${R_Ip6ModeData.RouteCount}}] == 1} {
  set assert pass
}
RecordAssertion $assert $Ip6RoutesFunc1AssertionGuid005       \
                "Ip6.Routes - Func - Check Ip6ModeData.RouteCount field after delete"


#
# Clean: Delete the neighbor cache
#
Ip6->Neighbors "TRUE, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, TRUE, &@R_Status"
GetAck

#
# DestroyChild.
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# End scope
#
EndScope _IP6_ROUTES_FUNCTION1_CASE1_
#
# End Log
#
EndLog