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
CaseGuid        9EB267CE-4A9F-486e-8774-193FBDE92C27
CaseName        ReadDirectory.Conf5.Case1
CaseCategory    MTFTP6
CaseDescription {Test ReadDirectory conformance of MTFTP6,invoke ReadDirectory() \
                 when one or more options in OptionList is wrong format.    \
                 EFI_INVALID_PARAMETER should be returned. 
                }
################################################################################

Include MTFTP6/include/Mtftp6.inc.tcl
#
# Begin log ...
#
BeginLog

BeginScope _MTFTP6_READDIRECTORY_CONFORMANCE5_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child
#
Mtftp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                      \
                "Mtftp6SB.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Initialize the environment
#
set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]
RemoteEther    $targetmac
LocalEther     $hostmac
set LocalIP    "2002::2"
set RemoteIp   "2002::4321"
LocalIPv6      $LocalIP
RemoteIPv6     $RemoteIp

#
# Check Point: Call Configure function with valid parameters. 
#              EFI_SUCCESS should be returned.
#
EFI_MTFTP6_CONFIG_DATA      R_Mtftp6ConfigData
SetIpv6Address    R_Mtftp6ConfigData.StationIp         "2002::4321" 
SetVar            R_Mtftp6ConfigData.LocalPort         1780
SetIpv6Address    R_Mtftp6ConfigData.ServerIp          "2002::2"
SetVar            R_Mtftp6ConfigData.InitialServerPort 0
SetVar            R_Mtftp6ConfigData.TryCount          3
SetVar            R_Mtftp6ConfigData.TimeoutValue      3

Mtftp6->Configure "&@R_Mtftp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Mtftp6.Configure -conf- Call Configure with valid parameters"  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call ReadDirectory when one or more options in OptionList have wrong format. \
#              EFI_INVALID_PARAMETER should be returned.
# 
EFI_MTFTP6_TOKEN                             R_Token

SetVar R_Token.Status                        $EFI_SUCCESS
SetVar R_Token.Event                         0
SetVar         R_Token.OverrideData          0
CHAR8                                        R_NameOfFile
SetVar         R_NameOfFile                  "Shell.efi"
SetVar         R_Token.Filename              &@R_NameOfFile
SetVar         R_Token.ModeStr               0
SetVar         R_Token.OptionCount           1
EFI_MTFTP6_OPTION                            R_OptionList(3)
CHAR8                                        R_OptionStr1(10)
SetVar         R_OptionStr1                   "blksize"
SetVar         R_OptionList(0).OptionStr     &@R_OptionStr1
SetVar         R_OptionList(0).ValueStr      0
SetVar         R_Token.OptionList            &@R_OptionList
SetVar         R_Token.BufferSize            3
CHAR8                                        R_Buffer(3)
SetVar         R_Token.Buffer                &@R_Buffer
SetVar         R_Token.Context               0

Mtftp6->ReadDirectory "&@R_Token, 1, 1, 1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp6ReadDirectoryConf5AssertionGuid001       \
                "Mtftp6.ReadDirectory -Conf- Call ReadDirectory when one or more options in OptionList have wrong format."  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destory child
#
Mtftp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                    \
                "Mtftp6SB.DestroyChild - Destory Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EUTClose
				
EndScope _MTFTP6_READDIRECTORY_CONFORMANCE5_CASE1_

#
# End Log
#
EndLog