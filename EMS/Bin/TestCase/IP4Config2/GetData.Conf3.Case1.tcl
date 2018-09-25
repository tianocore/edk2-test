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
CaseGuid        F9160E35-78F4-4298-BD94-947ECF61D179
CaseName        GetData.Conf3.Case1
CaseCategory    IP4Config2
CaseDescription {GetData must not succeed when DataSize is too small for the data type.}

################################################################################
Include IP4Config2/Include/Ip4Config2.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_GETDATA_CONF3

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN     R_Status
UINTN     R_Context
UINTN     R_Context1
UINTN     R_DoneEvent
UINTN     R_DoneEvent1
UINTN     R_Ip4Config2DataSize
UINT32    R_Ip4Config2DataType
UINT32    R_Ip4Config2Policy


#
# Check Point: Call Ip4Config2->SetData to set Static policy
#
SetVar R_Ip4Config2DataType $IP4C2DT(Policy)
SetVar R_Ip4Config2DataSize [Sizeof UINT32]
SetVar R_Ip4Config2Policy   $IP4C2P(Static)

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
      EndScope _IP4CONFIG2_GETDATA_CONF3
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
  EndScope _IP4CONFIG2_GETDATA_CONF3
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
                  "Set Static policy failure (event is signaled correctly and data correct)."
  SetVar R_Ip4Config2DataType   $IP4C2DT(Policy)
  Ip6Config->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_GETDATA_CONF3
  EndLog
  return
}
RecordAssertion $assert $GenericAssertionGuid    \
                "Set Static policy succeeds(event is signaled correctly and data correct)."

#
# Check Point : Set Static Address with valid value
#
EFI_IP4_CONFIG2_MANUAL_ADDRESS    R_Temp_Ip4Config2ManualAddress
EFI_IP4_CONFIG2_MANUAL_ADDRESS    R_Ip4Config2ManualAddress
SetVar R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
SetVar R_Ip4Config2DataSize   [Sizeof EFI_IP4_CONFIG2_MANUAL_ADDRESS]
SetIpv4Address R_Temp_Ip4Config2ManualAddress.Address       "192.168.100.1"
SetIpv4Address R_Temp_Ip4Config2ManualAddress.SubnetMask    "255.255.255.0"
SetVar R_Ip4Config2ManualAddress @R_Temp_Ip4Config2ManualAddress

SetVar R_Context1 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_NOTIFY, 1, &@R_Context1,\
                &@R_DoneEvent1, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "BS.CreateEvent."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4Config2->RegisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent1,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Ip4Config2.RegisterDataNotify - Register notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2ManualAddress,&@R_Status"
GetAck
GetVar  R_Status
if { $R_Status == $EFI_SUCCESS } {
  set assert pass
  RecordAssertion $assert $GenericAssertionGuid    \
                  "Ip4Config2.SetData - Call SetData with valid value."    \
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
                      "SetData failed.(event hasn't been signaled before TIMEOUT)."    \
                      "TIMEOUT value is $L_TimeOut (sec), "
      SetVar  R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent1,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent1,&@R_Status}
      GetAck
      SetVar  R_Ip4Config2DataType   $IP4C2DT(Policy)
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      EndScope _IP4CONFIG2_GETDATA_CONF3
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid    \
                  "Ip4Config2.SetData - Call SetData to set manual address."    \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

  SetVar  R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent1,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent1,&@R_Status}
  GetAck
  SetVar  R_Ip4Config2DataType   $IP4C2DT(Policy)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  EndScope _IP4CONFIG2_GETDATA_CONF3
  EndLog
  return  
}

#
# Check Point : Get Manual Address with datasize too small
#
SetVar R_Ip4Config2DataType    $IP4C2DT(ManualAddress)
SetVar R_Ip4Config2DataSize    4

Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2ManualAddress,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_BUFFER_TOO_SMALL]
RecordAssertion $assert $Ip4Config2GetDataConf3AssertionGuid001    \
                "Ip4Config2.GetData - Call GetData with the datasize too small."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_BUFFER_TOO_SMALL"

GetVar R_Ip4Config2DataSize
set L_ObtainedSize [ expr { $R_Ip4Config2DataSize } ]
set L_DesiredSize [ Sizeof EFI_IP4_CONFIG2_MANUAL_ADDRESS ]
if { $L_ObtainedSize == $L_DesiredSize } {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Ip4Config2GetDataConf3AssertionGuid002    \
                "Ip4Config2.GetData - Correctly Modify the DataSize."    \
                "ReturnSize - $L_ObtainedSize, ExpectedSize - $L_DesiredSize"

#
# Clean up
#

#
# Set Dhcp policy (this will clean up all address information configured)
#
SetVar R_Ip4Config2DataType    $IP4C2DT(Policy)
SetVar R_Ip4Config2DataSize    [Sizeof UINT32]
SetVar R_Ip4Config2Policy      $IP4C2P(Dhcp)

SetVar R_Context 0

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2Policy,&@R_Status"
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

      SetVar  R_Ip4Config2DataType   $IP4C2DT(Policy)
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent,&@R_Status}
      GetAck
      SetVar  R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
      Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent1,&@R_Status"
      GetAck
      BS->CloseEvent {@R_DoneEvent1,&@R_Status}
      GetAck

      EndScope _IP4CONFIG2_GETDATA_CONF3
      EndLog
      return
    }
    incr i
    Stall 1
  }
} else {
  set assert fail

  SetVar  R_Ip4Config2DataType   $IP4C2DT(Policy)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  SetVar   R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent1,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent1,&@R_Status}
  GetAck

  EndScope _IP4CONFIG2_GETDATA_CONF3
  EndLog
  return
}

Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2Policy,&@R_Status"
GetAck
GetVar R_Ip4Config2Policy
if { $R_Ip4Config2Policy == $IP4C2P(Dhcp) } {
  set assert pass
} else {
  set assert fail

  RecordAssertion $assert $GenericAssertionGuid    \
                  "Ip4Config2.SetData - Set Dhcp policy to clean up the former configuration."    \
                  "TimeUsed - $i, TimeOut Value- $L_TimeOut"
  SetVar  R_Ip4Config2DataType   $IP4C2DT(Policy)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent,&@R_Status}
  GetAck
  SetVar  R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
  Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent1,&@R_Status"
  GetAck
  BS->CloseEvent {@R_DoneEvent1,&@R_Status}
  GetAck

  EndScope _IP4CONFIG2_GETDATA_CONF3
  EndLog
  return
}
  
RecordAssertion $assert $GenericAssertionGuid    \
                "Ip4Config2.SetData - Set Dhcp policy to clean up the former configuration."    \
                "TimeUsed - $i, TimeOut Value- $L_TimeOut"
                
#
# Unregister Event for Manual Address and close event
#
SetVar  R_Ip4Config2DataType   $IP4C2DT(ManualAddress)
Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent1,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Ip4Config2.UnregisterDataNotify - Unregister notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CloseEvent {@R_DoneEvent1,&@R_Status}
GetAck
SetVar  R_Ip4Config2DataType   $IP4C2DT(Policy)
Ip4Config2->UnregisterDataNotify "@R_Ip4Config2DataType,@R_DoneEvent,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Ip4Config2.UnregisterDataNotify - Unregister notification event for configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

EndScope _IP4CONFIG2_GETDATA_CONF3

EndLog