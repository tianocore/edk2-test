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
CaseGuid        51934F81-A289-40C4-959D-211E5D02BCC7
CaseName        SetData.Conf4.Case1
CaseCategory    IP4Config2
CaseDescription {SetData must not succeed when data size does not match the data type and should return EFI_BAD_BUFFER_SIZE.}

################################################################################
Include IP4Config2/Include/Ip4Config2.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_SETDATA_CONF4_CASE1

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

SetVar R_Ip4Config2DataSize   [Sizeof UINT16]
Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2Policy,&@R_Status"
GetAck
GetVar R_Status
set assert [VerifyReturnStatus R_Status $EFI_BAD_BUFFER_SIZE]
RecordAssertion $assert $Ip4Config2SetDataConf4AssertionGuid001    \
                        "Ip4Config2.SetData - Call SetData to set Static policy but the datasize is incorrect."    \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_BAD_BUFFER_SIZE"

SetVar R_Ip4Config2DataSize   [Sizeof UINT32]
Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2Policy,&@R_Status"
GetAck
GetVar R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $GenericAssertionGuid    \
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
      RecordAssertion $assert $GenericAssertionGuid    \
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."    \
                      "TIMEOUT value is $L_TimeOut (sec), "
      SetVar R_Ip4Config2DataType   $IP4C2DT(Policy)
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      EndScope _IP4CONFIG2_SETDATA_CONF4_CASE1
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid    \
                  "Ip4Config2.SetData - Call SetData to set Static policy."    \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar R_Ip4Config2DataType   $IP4C2DT(Policy)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_CONF4_CASE1
  EndLog
  return
}

Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2Policy,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                        "Ip4Config2.GetData - Call GetData to get policy value."    \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
GetVar R_Ip4Config2Policy
if { $R_Ip4Config2Policy == $IP4C2P(Static) } {
  set assert pass
} else {
  set assert fail

  RecordAssertion $assert $GenericAssertionGuid    \
                  "Set Static policy succeeds(event is signaled correctly and data correct)."
  SetVar R_Ip4Config2Policy   $IP4C2DT(Policy)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_SETDATA_CONF4_CASE1
  EndLog
  return
}
RecordAssertion $assert $GenericAssertionGuid    \
                        "Set Static policy succeeds(event is signaled correctly and data correct)."

#
# Check Point : Set Manual Address with wrong data size
#
EFI_IP4_CONFIG2_MANUAL_ADDRESS    R_Temp_Ip4Config2ManualAddress
EFI_IP4_CONFIG2_MANUAL_ADDRESS    R_Ip4Config2ManualAddress
SetVar R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
SetVar R_Ip4Config2DataSize   [Sizeof EFI_IP4_CONFIG2_MANUAL_ADDRESS]
SetIpv4Address R_Temp_Ip4Config2ManualAddress.Address       "10.239.9.15"
SetIpv4Address R_Temp_Ip4Config2ManualAddress.SubnetMask    "255.255.255.0"
SetVar R_Ip4Config2ManualAddress @R_Temp_Ip4Config2ManualAddress
SetVar R_Ip4Config2DataSize    2

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2ManualAddress,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_BAD_BUFFER_SIZE]
RecordAssertion $assert $Ip4Config2SetDataConf4AssertionGuid002    \
                "Ip4Config2.SetData - Call SetData to set manual address with wrong data size."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_BAD_BUFFER_SIZE"
DelVar R_Ip4Config2ManualAddress

#
# Check Points : Set Gateway with wrong data size
#
EFI_IPv4_ADDRESS               R_Ip4Config2Gateway
SetVar R_Ip4Config2DataType    $IP4C2DT(Gateway)
SetVar R_Ip4Config2DataSize    [Sizeof EFI_IPv4_ADDRESS]
SetIpv4Address R_Ip4Config2Gateway "10.239.9.241"
SetVar R_Ip4Config2DataSize    2

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2Gateway,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_BAD_BUFFER_SIZE]
RecordAssertion $assert $Ip4Config2SetDataConf4AssertionGuid003    \
                "Ip4Config2.SetData - Call SetData to set gateway with wrong data size."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_BAD_BUFFER_SIZE"

DelVar R_Ip4Config2Gateway

#
# Check Point : Set Dns Server with wrong data size
#
EFI_IPv4_ADDRESS               R_Ip4Config2DnsServer
SetVar R_Ip4Config2DataType    $IP4C2DT(DnsServer)
SetVar R_Ip4Config2DataSize    [Sizeof EFI_IPv4_ADDRESS]
SetIpv4Address R_Ip4Config2DnsServer "10.248.2.5"
SetVar R_Ip4Config2DataSize    2

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2DnsServer,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_BAD_BUFFER_SIZE]
RecordAssertion $assert $Ip4Config2SetDataConf4AssertionGuid004    \
                "Ip4Config2.SetData - Call SetData to set dns server with wrong data size."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_BAD_BUFFER_SIZE"

DelVar R_Ip4Config2DnsServer


#
# Clean up
#
SetVar R_Ip4Config2DataType   $IP4C2DT(Policy)
Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Ip4Config2.UnregisterDataNotify - Unregister notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

EndScope _IP4CONFIG2_SETDATA_CONF4_CASE1

EndLog