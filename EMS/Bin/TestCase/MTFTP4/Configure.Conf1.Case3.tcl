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
CaseGuid          62B72667-FDEF-446f-8553-A70C637BD0E7
CaseName          Configure.Conf1.Case3
CaseCategory      MTFTP4
CaseDescription   {This case is to test the EFI_INVALID_PARAMETER conformance  \
                   of Mtftp4.Configure when MtftpConfigData->ServerIp is not a \
                   valid IPv4 unicast address.}
################################################################################

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_CONFIGURE_CONFORMANCE1_CASE3_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MTFTP4_CONFIG_DATA           R_MtftpConfigData

Mtftp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_MtftpConfigData.UseDefaultSetting    FALSE
SetIpv4Address R_MtftpConfigData.StationIp    "192.168.88.88"
SetIpv4Address R_MtftpConfigData.SubnetMask   "255.255.255.0"
SetVar R_MtftpConfigData.LocalPort            0
SetIpv4Address R_MtftpConfigData.GatewayIp    "0.0.0.0"
SetIpv4Address R_MtftpConfigData.ServerIp     "255.255.255.255"
SetVar R_MtftpConfigData.InitialServerPort    69
SetVar R_MtftpConfigData.TryCount             10
SetVar R_MtftpConfigData.TimeoutValue         2

#
# check point
#
Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp4ConfigureConfAssertionGuid003                   \
                "Mtftp4.Configure() - returns EFI_INVALID_PARAMETER when       \
                 MtftpConfigData->UseDefaultSetting is FALSE and               \
                 MtftpConfigData->ServerIp is not a valid IPv4 unicast address."\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

Mtftp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.DestroyChild - Destroy Child 1"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope _MTFTP4_CONFIGURE_CONFORMANCE1_CASE3_

#
# End Log
#
EndLog