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
CaseGuid        8FA160C5-7264-4990-B70C-B429715F8925
CaseName        Routes.Conf2.Case1
CaseCategory    Udp4
CaseDescription {Test the Routes Conformance of UDP4 - Invoke Routes() to delete\
                 a route not in the routing table.The return status should be  \
                 EFI_NOT_FOUND.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _UDP4_ROUTES_CONFORMANCE2_CASE1_

set hostmac            "0:2:3:4:5:6"
set targetmac          "0:3:4:5:6:7"
set targetip           192.168.88.1
set hostip             192.168.88.2
set R_SubnetMask       255.255.255.0
set targetport         4000
set hostport           4000
set arg_destaddrss     172.16.220.3
set arg_subnetaddrss   172.16.220.0
set arg_subnetmask     $R_SubnetMask
set arg_gatewayaddress $hostip

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_UDP4_CONFIG_DATA             R_Udp4ConfigData
UINTN                            R_Context
EFI_UDP4_COMPLETION_TOKEN        R_Token
EFI_IPv4_ADDRESS                 R_SubnetAddress
EFI_IPv4_ADDRESS                 R_SubnetMask
EFI_IPv4_ADDRESS                 R_GatewayAddress

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar   [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Routes - Conf - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Udp4ConfigData.AcceptBroadcast             TRUE
SetVar R_Udp4ConfigData.AcceptPromiscuous           FALSE
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
SetIpv4Address R_Udp4ConfigData.RemoteAddress       $arg_destaddrss
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

#
# Delete route to $arg_destaddrss. It is not in the routing table.
#
SetIpv4Address R_SubnetAddress  $arg_subnetaddrss
SetIpv4Address R_SubnetMask     $arg_subnetmask
SetIpv4Address R_GatewayAddress $arg_gatewayaddress

Udp4->Routes {TRUE, &@R_SubnetAddress, &@R_SubnetMask,                         \
              &@R_GatewayAddress, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $Udp4RoutesConf2AssertionGuid001                       \
                "Udp4.Routes - Conf - Delete route with R_GatewayAddress       \
                arg_gatewayaddress"                                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

#
# EndScope
#
EndScope _UDP4_ROUTES_CONFORMANCE2_CASE1_

#
# End Log
#
EndLog

