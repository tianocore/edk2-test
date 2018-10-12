# 
#  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
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
CaseGuid        79F40434-2684-459C-8EEB-DCFB822D93F7
CaseName        SetData.Func2.Case1
CaseCategory    IP6Config
CaseDescription {SetData to clear the configuration.}

################################################################################
Include IP6Config/Include/Ip6Config.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP6CONFIG_SETDATA_FUNC2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Context
UINTN                            R_DoneEvent
UINTN                            R_Ip6ConfigDataSize
UINT32                           R_Ip6ConfigDataType
EFI_IP6_CONFIG_INTERFACE_INFO    R_Ip6ConfigInterfaceInfo
EFI_IP6_CONFIG_INTERFACE_ID      R_Ip6ConfigInterfaceId
UINT32                           R_Ip6ConfigPolicy
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

Ip6Config->RegisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip6Config.RegisterDataNotify - Register notification event for configuration."    \
				"ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigPolicy,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6Config.SetData - Call SetData to set manual policy."            \
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
		RecordAssertion $assert $GenericAssertionGuid         \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC2
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                   \
               "Ip6Config.SetData - Call SetData to set manual policy."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}

SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigPolicy,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                      "Ip6Config.GetData - Call GetData to get policy value."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
GetVar R_Ip6ConfigPolicy
if { $R_Ip6ConfigPolicy == $IP6CP(Manual) } {
  set assert pass
} else {
  set assert fail
  	
  RecordAssertion $assert $GenericAssertionGuid        \
                      "Set manual policy fails(event is signaled correctly but data is incorrect)."
  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}
RecordAssertion $assert $GenericAssertionGuid        \
                      "Set manual policy succeeds(event is signaled correctly and data correct)."

#
# Check Point: Call Ip6Config->SetData to set DadXmits 20
#
SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS]
SetVar R_Ip6ConfigDadTransmits.DupAddrDetectTransmits    20

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

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigDadTransmits,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6Config.SetData - Call SetData to set DadXmits 20."            \
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
		RecordAssertion $assert $GenericAssertionGuid         \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC2
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                   \
               "Ip6Config.SetData - Call SetData to set DadXmits 20."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}

SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigDadTransmits,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                      "Ip6Config.GetData - Call GetData to get DadXmits value."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
GetVar R_Ip6ConfigDadTransmits.DupAddrDetectTransmits
if { ${R_Ip6ConfigDadTransmits.DupAddrDetectTransmits} == 20 } {
  set assert pass
} else {
  set assert fail
  	
  RecordAssertion $assert $GenericAssertionGuid        \
                      "Set DadXmits fails(event is signaled correctly but data is incorrect)."

  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}
RecordAssertion $assert $GenericAssertionGuid        \
                      "Set DadXmits succeeds(event is signaled correctly and data correct)."

Stall 30

#
# Check Point : Set Manual Address with valid parameter
#

EFI_IP6_CONFIG_MANUAL_ADDRESS    R_Temp_Ip6ConfigManualAddress

set L_ManualListLen    1
EFI_IP6_CONFIG_MANUAL_ADDRESS    R_Ip6ConfigManualAddress
set L_UnitLen [Sizeof EFI_IP6_CONFIG_MANUAL_ADDRESS]
set L_ListLen [expr {$L_UnitLen * $L_ManualListLen}]
SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
SetVar R_Ip6ConfigDataSize   $L_ListLen
SetVar R_Temp_Ip6ConfigManualAddress.IsAnycast FALSE
SetVar R_Temp_Ip6ConfigManualAddress.PrefixLength 64
SetIpv6Address R_Temp_Ip6ConfigManualAddress.Address "2002::5000"
SetVar R_Ip6ConfigManualAddress @R_Temp_Ip6ConfigManualAddress

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

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid001                   \
                "Ip6Config.SetData - Call SetData to set MANUAL ADDRESS."            \
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
		RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid001         \
                      "SetData to set MANUAL ADDRESS fail.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC2
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid001                   \
               "Ip6Config.SetData - Call SetData to set MANUAL ADDRESS."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}

SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                      "Ip6Config.GetData - Call GetData to get Manual Address."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Ip6ConfigManualAddress

set L_Proc_Ipv6Address [GetIpv6Address {R_Ip6ConfigManualAddress.Address}]
if { [string compare $L_Proc_Ipv6Address 2002:0000:0000:0000:0000:0000:0000:5000] != 0  } {
  puts $L_Proc_Ipv6Address 
  set assert fail

  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid002                     \
                  "Ip6Config.SetData - Set Gateway fail(event is signaled correctly but data is incorrect.)" 
} elseif {${R_Ip6ConfigManualAddress.PrefixLength} != 64} {
  set assert fail

  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid002                     \
                  "Ip6Config.SetData - Set Gateway fail(event is signaled correctly but data is incorrect.)" 

} elseif {${R_Ip6ConfigManualAddress.IsAnycast} != false} {
  set assert fail

  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid002                     \
                  "Ip6Config.SetData - Set Gateway fail(event is signaled correctly but data is incorrect.)" 

} else {
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid002                     \
                "Ip6Config.SetData - Set Gateway success(event is signaled correctly and data is correct.)" 
}

#
# Clear the Manual Address
#
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

Ip6Config->SetData "@R_Ip6ConfigDataType,0,NULL,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid003                   \
                "Ip6Config.SetData - Call SetData to clear MANUAL ADDRESS."            \
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
		RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid003         \
                      "SetData to clear MANUAL ADDRESS fail.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC2
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid003                   \
               "Ip6Config.SetData - Call SetData to clear MANUAL ADDRESS."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}

SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid004        \
                      "Ip6Config.GetData - Call GetData to get Manual Address."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

					  
#
# Check Point : Set Gateway with valid parameter
#

set L_GatewayListLen   1
EFI_IPv6_ADDRESS                 R_Temp_Ip6ConfigGateway
EFI_IPv6_ADDRESS                 R_Ip6ConfigGateway
set L_UnitLen [Sizeof EFI_IPv6_ADDRESS]
set L_ListLen [expr {$L_UnitLen * $L_GatewayListLen}]
SetVar R_Ip6ConfigDataType   $IP6CDT(Gateway)
SetVar R_Ip6ConfigDataSize   $L_ListLen

SetIpv6Address R_Temp_Ip6ConfigGateway "2002::5001"
SetVar R_Ip6ConfigGateway @R_Temp_Ip6ConfigGateway

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

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigGateway,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid005                   \
                "Ip6Config.SetData - Call SetData to set Gateway."            \
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
		RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid005         \
                      "SetData to set Gateway fail.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(Gateway)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC2
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid005                   \
               "Ip6Config.SetData - Call SetData to set Gateway."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(Gateway)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}

SetVar R_Ip6ConfigDataType   $IP6CDT(Gateway)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigGateway,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                      "Ip6Config.GetData - Call GetData to get Gateway."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Ip6ConfigGateway

set L_Proc_Ipv6Address [GetIpv6Address {R_Ip6ConfigGateway}]
if { [string compare $L_Proc_Ipv6Address 2002:0000:0000:0000:0000:0000:0000:5001] != 0  } {
  puts $L_Proc_Ipv6Address 
  set assert fail

  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid006                     \
                  "Ip6Config.SetData - Set Gateway fail(event is signaled correctly but data is incorrect.)" 
} else {

  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid006                     \
                "Ip6Config.SetData - Set Gateway success(event is signaled correctly and data is correct.)" 
}

#
# Clear the Gateway
#
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

Ip6Config->SetData "@R_Ip6ConfigDataType,0,NULL,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid007                   \
                "Ip6Config.SetData - Call SetData to clear Gateway."            \
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
		RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid007         \
                      "SetData to clear Gateway fail.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(Gateway)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC2
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid007                   \
               "Ip6Config.SetData - Call SetData to clear Gateway."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(Gateway)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}

SetVar R_Ip6ConfigDataType   $IP6CDT(Gateway)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigGateway,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid008        \
                      "Ip6Config.GetData - Call GetData to get Gateway."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"


#
# Check Point : Set DnsServer with valid parameter
#

set L_DnsServerListLen 1
EFI_IPv6_ADDRESS                 R_Temp_Ip6ConfigDnsServer
EFI_IPv6_ADDRESS                 R_Ip6ConfigDnsServer
set L_UnitLen [Sizeof EFI_IPv6_ADDRESS]
set L_ListLen [expr {$L_UnitLen * $L_DnsServerListLen}]
SetVar R_Ip6ConfigDataType   $IP6CDT(DnsServer)
SetVar R_Ip6ConfigDataSize   $L_ListLen

SetIpv6Address R_Temp_Ip6ConfigDnsServer "2002::5002"
SetVar R_Ip6ConfigDnsServer @R_Temp_Ip6ConfigDnsServer

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

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigDnsServer,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid009                   \
                "Ip6Config.SetData - Call SetData to set DnsServer."            \
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
		RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid009         \
                      "SetData to set DnsServer fail.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(DnsServer)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC2
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid009                   \
               "Ip6Config.SetData - Call SetData to set DnsServer."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(DnsServer)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}

SetVar R_Ip6ConfigDataType   $IP6CDT(DnsServer)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigDnsServer,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                      "Ip6Config.GetData - Call GetData to get DnsServer."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Ip6ConfigDnsServer

set L_Proc_Ipv6Address [GetIpv6Address {R_Ip6ConfigDnsServer}]
if { [string compare $L_Proc_Ipv6Address 2002:0000:0000:0000:0000:0000:0000:5002] != 0  } {
  set assert fail

  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid010                     \
                  "Ip6Config.SetData - Set DnsServer fail(event is signaled correctly but data is incorrect.)" 
} else {
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid010                     \
                "Ip6Config.SetData - Set DnsServer success(event is signaled correctly and data is correct.)" 
}

#
# Clear the DnsServer
#
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

Ip6Config->SetData "@R_Ip6ConfigDataType,0,NULL,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid011                   \
                "Ip6Config.SetData - Call SetData to clear DnsServer."            \
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
		RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid011         \
                      "SetData to clear DnsServer fail.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "

		SetVar R_Ip6ConfigDataType   $IP6CDT(DnsServer)
		Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
		GetAck
		BS->CloseEvent {@R_DoneEvent,&@R_Status}
		GetAck
		EndScope _IP6CONFIG_SETDATA_FUNC2
		EndLog
		return
	}
	incr i
	Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid011                   \
               "Ip6Config.SetData - Call SetData to clear DnsServer."            \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(DnsServer)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_SETDATA_FUNC2
  EndLog
  return
}

SetVar R_Ip6ConfigDataType   $IP6CDT(DnsServer)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigDnsServer,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $Ip6ConfigSetDataFunc2AssertionGuid012        \
                      "Ip6Config.GetData - Call GetData to get DnsServer."        \
                      "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"


EndScope _IP6CONFIG_SETDATA_FUNC2

EndLog