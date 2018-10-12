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
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        B2AD20DF-2325-42B2-A199-A49ADF04A5DD
CaseName        SetData.Func1.Case2
CaseCategory    IP4Config2
CaseDescription {SetData must succeed When DataSize is 0 and
                Data is NULL,and existing configuration is cleared.}

################################################################################
Include IP4Config2/Include/Ip4Config2.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_SETDATA_FUNC1_CASE2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN     R_Status
UINTN     R_Context
UINTN     R_DoneEvent
UINTN     R_Ip4Config2DataSize
UINT32    R_Ip4Config2DataType
UINT32    R_Ip4Config2Policy

#
# Check Point: Call Ip4Config2->SetData to set Static policy
#
SetVar R_Ip4Config2DataType   $IP4C2DT(Policy)
SetVar R_Ip4Config2DataSize   [Sizeof UINT32]
SetVar R_Ip4Config2Policy     $IP4C2P(Static)

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_NOTIFY, 1, &@R_Context,\
                &@R_DoneEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "BS.CreateEvent."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4Config2->RegisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip4Config2.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2Policy,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid001    \
                  "Ip4Config2.SetData - Call SetData to set Static policy."    \
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
      RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid001    \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."    \
                      "TIMEOUT value is $L_TimeOut (sec), "
      SetVar R_Ip4Config2DataType   $IP4C2DT(Policy)
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid001    \
                  "Ip4Config2.SetData - Call SetData to set Static policy."    \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip4Config2DataType   $IP4C2DT(Policy)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}


Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2Policy,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                        "Ip4Config2.GetData - Call GetData to get policy value."        \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
GetVar R_Ip4Config2Policy
if { $R_Ip4Config2Policy == $IP4C2P(Static) } {
  set assert pass
} else {
  set assert fail

  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid002    \
                  "Set Static policy succeeds(event is signaled correctly and data correct)."
  SetVar R_Ip4Config2Policy   $IP4C2DT(Policy)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}

Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid002    \
                "Set Static policy succeeds(event is signaled correctly and data correct)."

#
# Check Point : Set Manual Address
#
EFI_IP4_CONFIG2_MANUAL_ADDRESS    R_Temp_Ip4Config2ManualAddress
EFI_IP4_CONFIG2_MANUAL_ADDRESS    R_Ip4Config2ManualAddress
SetVar R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
SetVar R_Ip4Config2DataSize   [Sizeof EFI_IP4_CONFIG2_MANUAL_ADDRESS]
SetIpv4Address R_Temp_Ip4Config2ManualAddress.Address       "10.239.9.15"
SetIpv4Address R_Temp_Ip4Config2ManualAddress.SubnetMask    "255.255.255.0"
SetVar R_Ip4Config2ManualAddress @R_Temp_Ip4Config2ManualAddress

SetVar R_Context 0
Ip4Config2->RegisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Ip4Config2.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2ManualAddress,&@R_Status"
GetAck
GetVar R_Status

if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid003    \
                  "Ip4Config2.SetData - Call SetData to set Manual Address."    \
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
      RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid003    \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."    \
                      "TIMEOUT value is $L_TimeOut (sec), "
      SetVar R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid003    \
                  "IP4Config2.SetData - Call SetData to set Manual Address."    \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}


Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2ManualAddress,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                        "Ip4Config2.GetData - Call GetData to get Manual Address."    \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


EFI_IPv4_ADDRESS  R_Addr1
EFI_IPv4_ADDRESS  R_Addr2
set R_Addr1 [GetIpv4Address R_Ip4Config2ManualAddress.Address]
puts "R_Addr1 - $R_Addr1"
set R_Addr2 [GetIpv4Address R_Ip4Config2ManualAddress.SubnetMask]
puts "R_Addr1 - $R_Addr2"

if {[string compare -nocase $R_Addr1 10.239.9.15] == 0} {
  if {[string compare -nocase $R_Addr2 255.255.255.0] == 0} {
    set assert pass
  } else {
    set assert fail
    RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid004    \
                    "Set ManualAddress succeeds(event is signaled correctly and data correct)."
    Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
    GetAck
    BS->CloseEvent {@R_DoneEvent,&@R_Status}
    GetAck
    EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
    EndLog
    return
  }
} else {
  set assert fail

  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid004    \
                  "Set ManualAddress succeeds(event is signaled correctly and data correct)."
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}

Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid004    \
                "Set ManualAddress succeeds(event is signaled correctly and data correct)."

#
# Check Points : Set Gateway
#
EFI_IPv4_ADDRESS               R_Ip4Config2Gateway
SetVar R_Ip4Config2DataType    $IP4C2DT(Gateway)
SetVar R_Ip4Config2DataSize    [Sizeof EFI_IPv4_ADDRESS]
SetIpv4Address R_Ip4Config2Gateway "10.239.9.241"

SetVar R_Context 0
Ip4Config2->RegisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip4Config2.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2Gateway,&@R_Status"
GetAck
GetVar R_Status

if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid005    \
                  "Ip4Config2.SetData - Call SetData to set Gateway Address."    \
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
      RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid005    \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."    \
                      "TIMEOUT value is $L_TimeOut (sec), "
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid005    \
                  "Ip4Config2.SetData - Call SetData to set Gateway Address."    \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}


Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2Gateway,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                        "Ip4Config2.GetData - Call GetData to get Gateway Address."        \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EFI_IPv4_ADDRESS  R_Addr3
set R_Addr3 [GetIpv4Address R_Ip4Config2Gateway]
puts "R_Addr3 - $R_Addr3"

if {[string compare -nocase $R_Addr3 10.239.9.241] == 0} {
  set assert pass
} else {
  set assert fail

  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid006    \
                  "Set Gateway succeeds(event is signaled correctly and data correct)."
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}

Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid006    \
                "Set Gateway succeeds(event is signaled correctly and data correct)."

#
# Check Point : Set Dns Server
#
EFI_IPv4_ADDRESS               R_Ip4Config2DnsServer
SetVar R_Ip4Config2DataType    $IP4C2DT(DnsServer)
SetVar R_Ip4Config2DataSize    [Sizeof EFI_IPv4_ADDRESS]
SetIpv4Address R_Ip4Config2DnsServer "10.248.2.5"

SetVar R_Context 0
Ip4Config2->RegisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip4Config2.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2DnsServer,&@R_Status"
GetAck
GetVar R_Status

if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid007    \
                  "Ip4Config2.SetData - Call SetData to set Dns Address."    \
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
      RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid007    \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."    \
                      "TIMEOUT value is $L_TimeOut (sec), "
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid007    \
                  "Ip4Config2.SetData - Call SetData to set Dns Address."    \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}


Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2DnsServer,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                        "Ip4Config2.GetData - Call GetData to get Dns Address."        \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EFI_IPv4_ADDRESS  R_Addr4
set R_Addr4 [GetIpv4Address R_Ip4Config2DnsServer]
puts "R_Addr4 - $R_Addr4"

if {[string compare -nocase $R_Addr4 10.248.2.5] == 0} {
  set assert pass
} else {
  set assert fail

  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid008    \
                  "Set Dns succeeds(event is signaled correctly and data correct)."
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}

Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid008    \
                "Set Dns succeeds(event is signaled correctly and data correct)."



#
# Clean up - Call SetData when DataSize is 0 and Data is NULL
#



#
# Set Manual Address
#

SetVar R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
SetVar R_Ip4Config2DataSize   0



SetVar R_Context 0
Ip4Config2->RegisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Ip4Config2.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,NULL,&@R_Status"
GetAck
GetVar R_Status

if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid012    \
                  "Ip4Config2.SetData - Call SetData to clear Manual Address."    \
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
      RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid012    \
                      "SetData to clear Manual Address failed.(event hasn't been signaled before TIMEOUT)."    \
                      "TIMEOUT value is $L_TimeOut (sec), "
      SetVar R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid012    \
                  "IP4Config2.SetData - Call SetData to clear Manual Address."    \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}

Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

SetVar R_Ip4Config2DataSize   [Sizeof EFI_IP4_CONFIG2_MANUAL_ADDRESS]
Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2ManualAddress,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $GenericAssertionGuid    \
                        "Ip4Config2.GetData - Call GetData to get Manual Address."    \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

#
# Set Gateway Address
#


SetVar R_Ip4Config2DataType    $IP4C2DT(Gateway)
SetVar R_Ip4Config2DataSize    0

SetVar R_Context 0
Ip4Config2->RegisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip4Config2.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,NULL,&@R_Status"
GetAck
GetVar R_Status

if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid013    \
                  "Ip4Config2.SetData - Call SetData to clear Gateway Address."    \
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
      RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid013    \
                      "SetData to clear Gateway Address failed.(event hasn't been signaled before TIMEOUT)."    \
                      "TIMEOUT value is $L_TimeOut (sec), "
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid013    \
                  "Ip4Config2.SetData - Call SetData to clear Gateway Address."    \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}

Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

SetVar R_Ip4Config2DataSize    [Sizeof EFI_IPv4_ADDRESS]
Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2Gateway,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $GenericAssertionGuid    \
                        "Ip4Config2.GetData - Call GetData to get Gateway Address."        \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"


#
# Check Point : Set Dns Server
#

SetVar R_Ip4Config2DataType    $IP4C2DT(DnsServer)
SetVar R_Ip4Config2DataSize    0

SetVar R_Context 0
Ip4Config2->RegisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip4Config2.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,NULL,&@R_Status"
GetAck
GetVar R_Status

if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid014    \
                  "Ip4Config2.SetData - Call SetData to clear Dns Address."    \
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
      RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid014    \
                      "SetData to clear Dns Address failed.(event hasn't been signaled before TIMEOUT)."    \
                      "TIMEOUT value is $L_TimeOut (sec), "
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $Ip4Config2SetDataFunc1AssertionGuid014    \
                  "Ip4Config2.SetData - Call SetData to clear Dns Address."    \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2
  EndLog
  return
}

Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

SetVar R_Ip4Config2DataSize    [Sizeof EFI_IPv4_ADDRESS]
Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2DnsServer,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $GenericAssertionGuid    \
                        "Ip4Config2.GetData - Call GetData to get Dns Address."        \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"



EndScope _IP4CONFIG2_SETDATA_FUNC1_CASE2

EndLog