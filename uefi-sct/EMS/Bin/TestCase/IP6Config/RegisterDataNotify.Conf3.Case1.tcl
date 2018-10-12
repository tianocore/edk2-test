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
CaseGuid        B00EBD2E-F23E-434e-80E8-2A17C3BCFDFE
CaseName        RegisterDataNotify.Conf3.Case1
CaseCategory    IP6Config
CaseDescription {RegisterDataNotify must not succeed when event has already registered.}

################################################################################
Include IP6Config/Include/Ip6Config.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP6CONFIG_REGISTERDATANOTIFY_CONF3

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Context
UINTN                            R_DoneEvent
UINTN                            R_Ip6ConfigDataSize
UINT32                            R_Ip6ConfigDataType
EFI_IP6_CONFIG_INTERFACE_INFO    R_Ip6ConfigInterfaceInfo
EFI_IP6_CONFIG_INTERFACE_ID      R_Ip6ConfigInterfaceId
UINT32                            R_Ip6ConfigPolicy
EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS    R_Ip6ConfigDadTransmits

#
# Check Point: Call Ip6Config->SetData to set manual policy
#
SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
SetVar R_Ip6ConfigDataSize   [Sizeof UINT32]
SetVar R_Ip6ConfigPolicy     $IP6CP(Manual)

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_NOTIFY, 1, &@R_Context,\
                &@R_DoneEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                      \
                "BS.CreateEvent."                                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Ip6Config->RegisterDataNotify with valid parameters
#
Ip6Config->RegisterDataNotify "@R_Ip6ConfigDataType, @R_DoneEvent ,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip6Config.RegisterDataNotify - Register notification event with valid parameters."    \
				"ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
				
#
# Check Point : Call RegisterDataNotify() with the same event (has been registered)
#
Ip6Config->RegisterDataNotify "@R_Ip6ConfigDataType, @R_DoneEvent ,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ACCESS_DENIED]
RecordAssertion $assert $Ip6ConfigRegisterDataNotifyConf3AssertionGuid001     \
                "Ip6Config.RegisterDataNotify - Register notification event with the event registered already."    \
				"ReturnStatus - $R_Status, ExpectedStatus - $EFI_ACCESS_DENIED"


#
# Clean up
#
SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip6Config.UnregisterDataNotify - Unregister notification event for configuration."    \
				"ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

EndScope _IP6CONFIG_REGISTERDATANOTIFY_CONF3

EndLog