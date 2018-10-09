# 
#  Copyright 2006 - 2017 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
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
CaseGuid        D4594520-D163-4d09-A5BA-BD4317CADEC5
CaseName        Configure.Conf1.Case3
CaseCategory    Udp4
CaseDescription {Test the Configure Conformance of UDP4 - Invoke Configure()   \
                 with the parameter RemoteAddress being a multicast address.The\
                 return status should be EFI_INVALID_PARAMETER.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# Begin Scope
#
BeginScope _UDP4_CONFIGURE_CONFORMANCE1_CASE3_

set hostmac                    [GetHostMac]
set targetmac                  [GetTargetMac]
set targetip                   172.16.220.33
set hostip                     172.16.220.35
set subnetmask                 255.255.255.0
set targetport                 999
set hostport                   666
set invalid_remote_address     255.255.255.255

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_UDP4_CONFIG_DATA             R_Udp4ConfigData

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar   [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Configure - Conf - Create Child"                      \
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
SetIpv4Address R_Udp4ConfigData.SubnetMask          $subnetmask
SetVar R_Udp4ConfigData.StationPort                 $targetport
SetIpv4Address R_Udp4ConfigData.RemoteAddress       $invalid_remote_address
SetVar R_Udp4ConfigData.RemotePort                  $hostport

#
# Call Configure() to configure the new Udp4 instance
#
Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Udp4ConfigureConf1AssertionGuid003                    \
                "Udp4.Configure - Config Child"                                \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"


Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

#
# End scope
#
EndScope _UDP4_CONFIGURE_CONFORMANCE1_CASE3_


#
# End log
#
EndLog

