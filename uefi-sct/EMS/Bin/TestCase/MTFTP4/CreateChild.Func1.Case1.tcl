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
CaseGuid        7F275D00-5B10-49ec-B61F-5230362DC296
CaseName        CreateChild.Func1.Case1
CaseCategory    MTFTP4
CaseDescription {This case is to test the CreateChild Function of Mtftp4SB --  \
                Create different Childs and destroy them.}
################################################################################

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_CREATECHILD_FUNCTION1_CASE1_

UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2
UINTN                            R_Handle3

EFI_MTFTP4_CONFIG_DATA           R_MtftpConfigData

SetVar R_MtftpConfigData.UseDefaultSetting   FALSE 
SetIpv4Address R_MtftpConfigData.StationIp   "192.168.88.88"
SetIpv4Address R_MtftpConfigData.SubnetMask  "255.255.255.0"
SetVar R_MtftpConfigData.LocalPort           0
SetIpv4Address R_MtftpConfigData.GatewayIp   "0.0.0.0"
SetIpv4Address R_MtftpConfigData.ServerIp    "192.168.88.1"
SetVar R_MtftpConfigData.InitialServerPort   69
SetVar R_MtftpConfigData.TryCount            1
SetVar R_MtftpConfigData.TimeoutValue        2
#
# check point
#
puts [Mtftp4ServiceBinding->CreateChild {&@R_Handle1, &@R_Status}]
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp4CreateChildFuncAssertionGuid001                 \
                "Mtftp4SBP.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4.Configure - Normal configuration."                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# check point
#
Mtftp4ServiceBinding->CreateChild {&@R_Handle2, &@R_Status}
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert  $Mtftp4CreateChildFuncAssertionGuid002                \
                "Mtftp4SBP.CreateChild - Create Child 2"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4.Configure - Normal configuration."                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


#
# check point
#
Mtftp4ServiceBinding->CreateChild {&@R_Handle3, &@R_Status}
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle3
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert Mtftp4CreateChildFuncAssertionGuid003                  \
                "Mtftp4SBP.CreateChild - Create Child 3"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4.Configure - Normal configuration."                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


Mtftp4ServiceBinding->DestroyChild {@R_Handle1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.DestroyChild - Destroy Child 1"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Mtftp4ServiceBinding->DestroyChild {@R_Handle2, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.DestroyChild - Destroy Child 2"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Mtftp4ServiceBinding->DestroyChild {@R_Handle3, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.DestroyChild - Destroy Child 3"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope _MTFTP4_CREATECHILD_FUNCTION1_CASE1_

#
# End Log
#
EndLog
