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
CaseGuid        B8AE0BCD-EDA2-4616-9D9B-935866880477
CaseName        Routes.Conf1.Case5
CaseCategory    Udp4
CaseDescription {Test the Routes Conformance of UDP4 - Invoke Routes() with the\
                 parameter *GatewayAddress being invalid unicast IP address.The\
                 return status should be EFI_INVALID_PARAMETER.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _UDP4_ROUTES_CONFORMANCE1_CASE5_

set hostmac                  [GetHostMac]
set targetmac                [GetTargetMac]
set targetip                 172.16.220.33
set hostip                   172.16.220.35
set R_SubnetMask             255.255.255.0
set targetport               999
set hostport                 666
set arg_subnetaddrss         172.16.220.0
set arg_subnetmask           255.255.255.0
set arg_gatewayaddress       $hostip
set invalid_gatewayaddress   224.0.0.1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_IPv4_ADDRESS                 R_SubnetAddress
EFI_IPv4_ADDRESS                 R_SubnetMask
EFI_IPv4_ADDRESS                 R_GatewayAddress
EFI_UDP4_CONFIG_DATA             R_Udp4ConfigData

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar   [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Routes - Conf - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Udp4ConfigData.AcceptBroadcast             TRUE
SetVar R_Udp4ConfigData.AcceptPromiscuous           TRUE
SetVar R_Udp4ConfigData.AcceptAnyPort               TRUE
SetVar R_Udp4ConfigData.AllowDuplicatePort          TRUE
SetVar R_Udp4ConfigData.TypeOfService               0
SetVar R_Udp4ConfigData.TimeToLive                  1
SetVar R_Udp4ConfigData.DoNotFragment               TRUE
SetVar R_Udp4ConfigData.ReceiveTimeout              0
SetVar R_Udp4ConfigData.TransmitTimeout             0
SetVar R_Udp4ConfigData.UseDefaultAddress           FALSE
SetIpv4Address R_Udp4ConfigData.StationAddress      $targetip
SetIpv4Address R_Udp4ConfigData.SubnetMask          $R_SubnetMask
SetVar R_Udp4ConfigData.StationPort                 $targetport
SetIpv4Address R_Udp4ConfigData.RemoteAddress       $hostip
SetVar R_Udp4ConfigData.RemotePort                  $hostport

#
#check point
#
Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Routes - Conf - Config Child"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetIpv4Address R_SubnetAddress  $arg_subnetaddrss
SetIpv4Address R_SubnetMask     $arg_subnetmask
SetIpv4Address R_GatewayAddress $invalid_gatewayaddress

Udp4->Routes {FALSE, &@R_SubnetAddress, &@R_SubnetMask,                        \
              &@R_GatewayAddress, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Udp4RoutesConf1AssertionGuid005                       \
                "Udp4.Routes - Conf - Add route with invalid R_GatewayAddress  \
                $invalid_gatewayaddress"                                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

#
# EndScope
#
EndScope _UDP4_ROUTES_CONFORMANCE1_CASE5_

#
# End Log
#
EndLog

