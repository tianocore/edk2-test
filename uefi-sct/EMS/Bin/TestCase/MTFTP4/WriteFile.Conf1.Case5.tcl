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
CaseGuid        52C38A9A-879D-48d0-A59D-970101FAA961
CaseName        WriteFile.Conf1.Case5
CaseCategory    MTFTP4
CaseDescription {This case is to test the EFI_INVALID_PARAMETER conformance of \
                 Mtftp4.WriteFile with Token->OverrideData being invalid.}
################################################################################

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_WRITEFILE_CONFORMANCE1_CASE5_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MTFTP4_CONFIG_DATA           R_MtftpConfigData

UINT64                           R_BufferSize
UINT64                           R_Buffer(1000)
EFI_MTFTP4_TOKEN                 R_Token
EFI_MTFTP4_OVERRIDE_DATA         OverrideData

Mtftp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_MtftpConfigData.UseDefaultSetting   FALSE
SetIpv4Address R_MtftpConfigData.StationIp   "192.168.88.88"
SetIpv4Address R_MtftpConfigData.SubnetMask  "255.255.255.0"
SetVar R_MtftpConfigData.LocalPort           2048
SetIpv4Address R_MtftpConfigData.GatewayIp   "0.0.0.0"
SetIpv4Address R_MtftpConfigData.ServerIp    "192.168.88.1"
SetVar R_MtftpConfigData.InitialServerPort   69
SetVar R_MtftpConfigData.TryCount            2
SetVar R_MtftpConfigData.TimeoutValue        2

Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4.Configure - Normal operation."                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Token.ModeStr     NULL
SetVar R_Token.OptionCount  2
SetVar R_Token.OptionList   NULL
SetVar R_BufferSize         1000
SetVar R_Token.BufferSize   @R_BufferSize
SetVar R_Token.Buffer       &@R_Buffer

#check point
SetIpv4Address OverrideData.GatewayIp      "255.255.255.255"
SetIpv4Address OverrideData.ServerIp       "192.168.88.1"
SetVar OverrideData.ServerPort             69
SetVar OverrideData.TryCount               2
SetVar OverrideData.TimeoutValue           2

SetVar R_Token.OverrideData                  &@OverrideData

Mtftp4->WriteFile {&@R_Token, 1, 1, 1, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp4WriteFileConfAssertionGuid005                   \
                "Mtftp4.WriteFile - returns EFI_INVALID_PARAMETER with         \
                 OverrideData.GatewayIp is invalid."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"


#check point
SetIpv4Address OverrideData.GatewayIp      "0.0.0.0"
SetIpv4Address OverrideData.ServerIp       "255.255.255.255"
SetVar OverrideData.ServerPort             69
SetVar OverrideData.TryCount               2
SetVar OverrideData.TimeoutValue           2

SetVar R_Token.OverrideData                &@OverrideData

Mtftp4->WriteFile {&@R_Token, 1, 1, 1, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp4WriteFileConfAssertionGuid006                   \
                "Mtftp4.WriteFile - returns EFI_INVALID_PARAMETER with         \
                 OverrideData.ServerIp is invalid."                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"
# 
# check point
#
SetIpv4Address OverrideData.GatewayIp      "172.16.220.110"
SetIpv4Address OverrideData.ServerIp       "192.168.88.1"
SetVar OverrideData.ServerPort             69
SetVar OverrideData.TryCount               2
SetVar OverrideData.TimeoutValue           2

SetVar R_Token.OverrideData                &@OverrideData

Mtftp4->WriteFile {&@R_Token, 1, 1, 1, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp4WriteFileConfAssertionGuid007                   \
                "Mtftp4.WriteFile - returns EFI_INVALID_PARAMETER for          \
                 OverrideData.GatewayIp is not in the same subnet with         \
                 stationIP."                                                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"
 
Mtftp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.DestroyChild - Destroy Child 1"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope _MTFTP4_WRITEFILE_CONFORMANCE1_CASE5_

#
# End Log
#
EndLog
