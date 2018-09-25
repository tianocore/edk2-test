# 
#  Copyright 2017 Unified EFI, Inc.<BR> 
#  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
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
CaseGuid        B8787A3A-BA2E-4A4B-B935-F0FA3C7ACC0B
CaseName        UnregisterDataNotify.Conf2.Case1
CaseCategory    IP4Config2
CaseDescription {UnregisterDataNotify must not succeed when then event has not been registered for the data type ever and should return EFI_NOT_FOUND.}

################################################################################
Include IP4Config2/Include/Ip4Config2.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_UNREGISTERDATANOTIFY_CONF2_CASE1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN     R_Status
UINTN     R_Context
UINTN     R_DoneEvent
UINT32    R_Ip4Config2DataType

#
# Check Point: Call Ip6Config->UnregisterDataNotify with the event not registered
#
SetVar R_Ip4Config2DataType   $IP4C2DT(Policy)

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_NOTIFY, 1, &@R_Context,\
                &@R_DoneEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "BS.CreateEvent."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType, @R_DoneEvent ,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $Ip4Config2UnregisterDataNotifyConf2AssertionGuid001     \
                "Ip4Config2.UnregisterDataNotify - Unregister notification event with the event not registered."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

#
# Clean up
#
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

EndScope _IP4CONFIG2_UNREGISTERDATANOTIFY_CONF2_CASE1

EndLog