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
CaseGuid        7D041B9B-4F68-434a-A0C6-63FDC415D078
CaseName        RegisterDataNotify.Func1.Case1
CaseCategory    IP6Config
CaseDescription {RegisterDataNotify must succeed with valid parameters when one event registered on one data type.}

################################################################################
Include IP6Config/Include/Ip6Config.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Context
UINTN                            R_DoneEvent
UINTN                            R_Context1
UINTN                            R_DoneEvent1
UINTN                            R_Context2
UINTN                            R_DoneEvent2
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
      EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
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
  EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
  EndLog
  return
}

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
                  "Set manual policy succeeds(event is signaled correctly and data correct)."
  SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
  EndLog
  return
}
RecordAssertion $assert $GenericAssertionGuid        \
                "Set manual policy succeeds(event is signaled correctly and data correct)."

#
# Check Point: Call Ip6Config->SetData to set DadXmits 0
#
SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS]
SetVar R_Ip6ConfigDadTransmits.DupAddrDetectTransmits    0

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
  RecordAssertion $assert $GenericAssertionGuid                   \
                 "Ip6Config.SetData - Call SetData to set DadXmits 0."            \
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
      RecordAssertion $assert $GenericAssertionGuid         \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."      \
                      "TIMEOUT value is $L_TimeOut (sec), "
      SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
      Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
      Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent1,&@R_Status}
      GetAck
      EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                   \
                  "Ip6Config.SetData - Call SetData to set DadXmits 0."            \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
               
  SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent1,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
  EndLog
  return
}

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigDadTransmits,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                "Ip6Config.GetData - Call GetData to get DadXmits value."        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
GetVar R_Ip6ConfigDadTransmits.DupAddrDetectTransmits
if { ${R_Ip6ConfigDadTransmits.DupAddrDetectTransmits} == 0 } {
  set assert pass
} else {
  set assert fail

  RecordAssertion $assert $GenericAssertionGuid        \
                  "Set DadXmits succeeds(event is signaled correctly and data correct)."
  SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent1,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
  EndLog
  return
}
RecordAssertion $assert $GenericAssertionGuid        \
                "Set DadXmits succeeds(event is signaled correctly and data correct)."

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
#
# Register Event for Manual Address
#
SetVar R_Context2 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_NOTIFY, 1, &@R_Context2,\
                &@R_DoneEvent2, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                      \
                "BS.CreateEvent."                                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip6Config->RegisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent2,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6ConfigRegisterDataNotifyFunc1AssertionGuid001     \
                "Ip6Config.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $GenericAssertionGuid                   \
                  "Ip6Config.SetData - Call SetData to set manual address."            \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
} elseif { $R_Status == $EFI_NOT_READY } {
  set i 0
  set L_TimeOut 30
  while { 1 > 0 } {
    GetVar R_Context2
    if { $R_Context2 == 1 } {
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
      SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
      Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent1,&@R_Status}
      GetAck
      SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
      Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent2,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent2,&@R_Status}
      GetAck
      EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                   \
                  "Ip6Config.SetData - Call SetData to set manual address."            \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent1,&@R_Status}
  GetAck
  SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent2,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent2,&@R_Status}
  GetAck
  EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
  EndLog
  return
}

#
# Check Events for registered datatype
#
GetVar R_Context2
if { $R_Context2 == 1 } {
  set assert pass 
} else {
  set assert fail
}
RecordAssertion $assert $Ip6ConfigRegisterDataNotifyFunc1AssertionGuid002     \
                "Ip6Config.RegisterDataNotify - Registered event is signaled."

#
# GetData to verfiy the data setting
#
Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                "Ip6Config.GetData - Call GetData to get manual address."        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Ip6ConfigManualAddress.IsAnycast
if { ${R_Ip6ConfigManualAddress.IsAnycast} == FALSE } {
  set assert pass
} else {
  set assert fail
}
GetVar R_Ip6ConfigManualAddress.PrefixLength
if { ${R_Ip6ConfigManualAddress.PrefixLength} == 64 } {
  set assert pass
} else {
  set assert fail
}
GetVar R_Ip6ConfigManualAddress.Address
set L_ManualAddress "2002:0000:0000:0000:0000:0000:0000:5000"
set L_RemoteAddress [ GetIpv6Address {R_Ip6ConfigManualAddress.Address} ]
if { [ string compare $L_RemoteAddress $L_ManualAddress ] == 0 } {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid        \
                "Set ManualAddress succeeds(event is signaled correctly and data correct)."

#
# Set automatic policy (this will clean up all address information configured)
#
SetVar R_Ip6ConfigDataType   $IP6CDT(Policy)
SetVar R_Ip6ConfigDataSize   [Sizeof UINT32]
SetVar R_Ip6ConfigPolicy     $IP6CP(Automatic)

SetVar R_Context 0

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigPolicy,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
} elseif { $R_Status == $EFI_NOT_READY } {
  set i 0
  set L_TimeOut 30
  set assert pass
  while { 1 > 0 } {
    GetVar R_Context
    if { $R_Context == 1 } {
      break
    } elseif { $i == $L_TimeOut } {
      set assert fail

      SetVar  R_Ip6ConfigDataType   $IP6CDT(Policy)
      Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      SetVar   R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
      Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent1,&@R_Status}
      GetAck
      SetVar   R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
      Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent2,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent2,&@R_Status}
      GetAck

      EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail

  SetVar  R_Ip6ConfigDataType   $IP6CDT(Policy)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  SetVar   R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent1,&@R_Status}
  GetAck
  SetVar   R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
  Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent2,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent2,&@R_Status}
  GetAck

  EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1
  EndLog
  return
}

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigPolicy,&@R_Status"
GetAck
GetVar R_Ip6ConfigPolicy
if { $R_Ip6ConfigPolicy == $IP6CP(Automatic) } {
  set assert pass
} else {
  set assert fail
}
  
RecordAssertion $assert $GenericAssertionGuid                     \
                "Ip6Config.SetData - Set automatic policy to clean up the former configuration."            \
                "TimeUsed - $i, TimeOut Value- $L_TimeOut"
                
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

SetVar R_Ip6ConfigDataType   $IP6CDT(DupAddrDetectTransmits)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent1,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip6Config.UnregisterDataNotify - Unregister notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
BS->CloseEvent {@R_DoneEvent1,&@R_Status}
GetAck

SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
Ip6Config->UnregisterDataNotify "@R_Ip6ConfigDataType,@R_DoneEvent2,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip6Config.UnregisterDataNotify - Unregister notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CloseEvent {@R_DoneEvent2,&@R_Status}
GetAck

EndScope _IP6CONFIG_REGISTERDATANOTIFY_FUNC1_CASE1

EndLog