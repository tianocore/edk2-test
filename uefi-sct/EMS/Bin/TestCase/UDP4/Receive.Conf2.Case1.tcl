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
CaseGuid        EF1AC4B5-5CA8-4e2e-AB6F-53A19AA6E0E1
CaseName        Receive.Conf2.Case1
CaseCategory    Udp4
CaseDescription {Test the Receive Conformance of UDP4 - Invoke Receive() when  \
	               this EFI UDPv4 Protocol instance has not been started. The    \
	               return status should be EFI_NOT_STARTED.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _UDP4_RECEIVE_CONFORMANCE2_CASE1_

set hostmac            [GetHostMac]
set targetmac          [GetTargetMac]
set targetip           172.16.220.33
set hostip             172.16.220.35
set subnetmask         255.255.255.0
set targetport         999
set hostport           666

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_Handle
EFI_UDP4_CONFIG_DATA              R_Udp4ConfigData
UINTN                             R_Context
EFI_UDP4_COMPLETION_TOKEN         R_Token

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar   [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Receive - Conf - Create Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

Udp4->Receive {&@R_Token, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Udp4ReceiveConf2AssertionGuid001                      \
                "Udp4.Receive - Conf - Invoke Receive() when this EFI UDPv4    \
                 Protocol instance has not been started."                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"


Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

#
# EndScope
#
EndScope _UDP4_RECEIVE_CONFORMANCE2_CASE1_

#
#End Log
#
EndLog
