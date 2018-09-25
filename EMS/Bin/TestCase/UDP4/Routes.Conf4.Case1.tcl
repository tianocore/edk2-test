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
CaseGuid        2CAB6852-9B51-4c77-9A95-1A24A84459AF
CaseName        Routes.Conf4.Case1
CaseCategory    Udp4
CaseDescription {Test the EFI_NOT_STARTED Conformance of UDP4.Routes - Invoke  \
                 Routes() when the EFI UDPv4 Protocol instance has not been    \
                 started.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _UDP4_ROUTES_CONFORMANCE4_CASE1_

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

#
# Check point
#
SetIpv4Address R_SubnetAddress  $arg_subnetaddrss
SetIpv4Address R_SubnetMask     $arg_subnetmask
SetIpv4Address R_GatewayAddress $arg_gatewayaddress

Udp4->Routes {TRUE, &@R_SubnetAddress, &@R_SubnetMask,                         \
              &@R_GatewayAddress, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Udp4RoutesConf4AssertionGuid001                       \
                "Udp4.Routes - Conf - returns EFI_NOT_STARTED when the EFI UDPv4\
                 Protocol instance has not been started."                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"
                
Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

#
# EndScope
#
EndScope _UDP4_ROUTES_CONFORMANCE4_CASE1_

#
# End Log
#
EndLog