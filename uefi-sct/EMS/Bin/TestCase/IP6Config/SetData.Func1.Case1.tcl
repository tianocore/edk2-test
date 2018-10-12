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
CaseGuid        EF8FF5B4-8855-4fbd-87C5-C28C7312302A
CaseName        SetData.Func1.Case1
CaseCategory    IP6Config
CaseDescription {SetData must succeed with valid parameters.}

################################################################################
Include IP6Config/Include/Ip6Config.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP6CONFIG_SETDATA_FUNC1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Context
UINTN                            R_Context1
UINTN                            R_DoneEvent
UINTN                            R_DoneEvent1
UINTN                            R_Ip6ConfigDataSize
UINT32                            R_Ip6ConfigDataType
EFI_IP6_CONFIG_INTERFACE_INFO    R_Ip6ConfigInterfaceInfo
EFI_IP6_CONFIG_INTERFACE_ID      R_Ip6ConfigInterfaceId
UINT32                            R_Ip6ConfigPolicy
EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS    R_Ip6ConfigDadTransmits

#
# Check Point: Call Ip6Config->SetData to set AltInterfaceId
#
SetVar R_Ip6ConfigDataType   $IP6CDT(AltInterfaceId)
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_INTERFACE_ID]
SetVar R_Ip6ConfigInterfaceId.Id(0) 0
SetVar R_Ip6ConfigInterfaceId.Id(1) 1
SetVar R_Ip6ConfigInterfaceId.Id(2) 2
SetVar R_Ip6ConfigInterfaceId.Id(3) 3
SetVar R_Ip6ConfigInterfaceId.Id(4) 4
SetVar R_Ip6ConfigInterfaceId.Id(5) 5
SetVar R_Ip6ConfigInterfaceId.Id(6) 6
SetVar R_Ip6ConfigInterfaceId.Id(7) 7

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_NOTIFY, 1, &@R_Context,\
                &@R_DoneEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                      \
                "BS.CreateEvent."                                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip6Config->RegisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip6Config.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigInterfaceId,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip6ConfigSetDataFunc1AssertionGuid001                   \
                "Ip6Config.SetData - Call SetData to set AltInterfaceId."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
} elseif { $R_Status == $EFI_NOT_READY } {
  set i 0
  set L_TimeOut 30
  while { 1 > 0 } {
    GetVar R_Context
	if { $R_Context == 1 } {
		break
	} elseif { $i == $L_TimeOut } {
		set assert fail
		RecordAssertion $assert $Ip6ConfigSetDataFunc1AssertionGuid001         \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(AltInterfaceId)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC1
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip6ConfigSetDataFunc1AssertionGuid001                   \
               "Ip6Config.SetData - Call SetData to set AltInterfaceId."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


  SetVar R_Ip6ConfigDataType   $IP6CDT(AltInterfaceId)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC1
  EndLog
  return
}

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigInterfaceId,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                      "Ip6Config.GetData - Call GetData to get AltInterfaceId value."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
GetVar R_Ip6ConfigInterfaceId
if { ${R_Ip6ConfigInterfaceId.Id(0)} == 0 && ${R_Ip6ConfigInterfaceId.Id(1)} == 1 && ${R_Ip6ConfigInterfaceId.Id(2)} == 2 && ${R_Ip6ConfigInterfaceId.Id(3)} == 3 && ${R_Ip6ConfigInterfaceId.Id(4)} == 4 && ${R_Ip6ConfigInterfaceId.Id(5)} == 5 && ${R_Ip6ConfigInterfaceId.Id(6)} == 6 && ${R_Ip6ConfigInterfaceId.Id(7)} == 7} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Ip6ConfigSetDataFunc1AssertionGuid002        \
                      "Set AltInterfaceId succeeds(event is signaled correctly and data correct)."

#
# Check Point: Call Ip6Config->SetData to set DadXmits
#
SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS]
SetVar R_Ip6ConfigDadTransmits.DupAddrDetectTransmits 3

SetVar R_Context1 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_NOTIFY, 1, &@R_Context1,\
                &@R_DoneEvent1, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                      \
                "BS.CreateEvent."                                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip6Config->RegisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip6Config.RegisterDataNotify - Register notification event for configuration."    \
				"ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigDadTransmits,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip6ConfigSetDataFunc1AssertionGuid003                   \
                "Ip6Config.SetData - Call SetData to set DadXmits."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
} elseif { $R_Status == $EFI_NOT_READY } {
  set i 0
  set L_TimeOut 30
  while { 1 > 0 } {
    GetVar R_Context1
	if { $R_Context1 == 1 } {
		break
	} elseif { $i == $L_TimeOut } {
		set assert fail
		RecordAssertion $assert $Ip6ConfigSetDataFunc1AssertionGuid003         \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(AltInterfaceId)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent1,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC1
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip6ConfigSetDataFunc1AssertionGuid003                   \
               "Ip6Config.SetData - Call SetData to set manual DadXmits."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(AltInterfaceId)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent1,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC1
  EndLog
}

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigDadTransmits,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                      "Ip6Config.GetData - Call GetData to get DadXmits value."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
GetVar R_Ip6ConfigDadTransmits
if { ${R_Ip6ConfigDadTransmits.DupAddrDetectTransmits} == 3 } {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Ip6ConfigSetDataFunc1AssertionGuid004        \
                      "Set DadXmits succeeds(event is signaled correctly and data correct)."

#
# Clean up
#
SetVar R_Ip6ConfigDataType   $IP6CDT(AltInterfaceId)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip6Config.UnregisterDataNotify - Unregister notification event for configuration."    \
				"ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip6Config.UnregisterDataNotify - Unregister notification event for configuration."    \
				"ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
BS->CloseEvent {@R_DoneEvent1,&@R_Status}
GetAck

EndScope _IP6CONFIG_SETDATA_FUNC1

EndLog