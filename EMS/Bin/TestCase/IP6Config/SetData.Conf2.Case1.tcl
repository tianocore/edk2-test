#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
#
################################################################################
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        A9BBCC37-3ED5-4c11-B6B6-BE52A1131568
CaseName        SetData.Conf2.Case1
CaseCategory    IP6Config
CaseDescription {SetData must not succeed when one or more fields in data is invalid.}

################################################################################
Include IP6Config/Include/Ip6Config.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP6CONFIG_SETDATA_CONF2

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
		EndScope _IP6CONFIG_SETDATA_CONF2
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
  EndScope _IP6CONFIG_SETDATA_CONF2
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
  EndScope _IP6CONFIG_SETDATA_CONF2
  EndLog
  return
}
RecordAssertion $assert $GenericAssertionGuid        \
                      "Set manual policy succeeds(event is signaled correctly and data correct)."

#
# Check Point : Set Manual Address with "::"
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
SetIpv6Address R_Temp_Ip6ConfigManualAddress.Address "::"
SetVar R_Ip6ConfigManualAddress @R_Temp_Ip6ConfigManualAddress

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip6ConfigSetDataConf2AssertionGuid001                   \
                "Ip6Config.SetData - Call SetData to set manual address (Not Unicast or Linklocal)."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

DelVar R_Ip6ConfigManualAddress

#
# Check Point : Set Manual Address with duplication of list entries
#
set L_ManualListLen    3
EFI_IP6_CONFIG_MANUAL_ADDRESS    R_Ip6ConfigManualAddress($L_ManualListLen)
set L_UnitLen [Sizeof EFI_IP6_CONFIG_MANUAL_ADDRESS]
set L_ListLen [expr {$L_UnitLen * $L_ManualListLen}]
SetVar R_Ip6ConfigDataType   $IP6CDT(ManualAddress)
SetVar R_Ip6ConfigDataSize   $L_ListLen

SetVar R_Temp_Ip6ConfigManualAddress.IsAnycast FALSE
SetVar R_Temp_Ip6ConfigManualAddress.PrefixLength 64
SetIpv6Address R_Temp_Ip6ConfigManualAddress.Address "2002::5000"
SetVar R_Ip6ConfigManualAddress(0) @R_Temp_Ip6ConfigManualAddress

SetVar R_Temp_Ip6ConfigManualAddress.IsAnycast FALSE
SetVar R_Temp_Ip6ConfigManualAddress.PrefixLength 64
SetIpv6Address R_Temp_Ip6ConfigManualAddress.Address "2002::5001"
SetVar R_Ip6ConfigManualAddress(1) @R_Temp_Ip6ConfigManualAddress

SetVar R_Temp_Ip6ConfigManualAddress.IsAnycast FALSE
SetVar R_Temp_Ip6ConfigManualAddress.PrefixLength 64
SetIpv6Address R_Temp_Ip6ConfigManualAddress.Address "2002::5000"
SetVar R_Ip6ConfigManualAddress(2) @R_Temp_Ip6ConfigManualAddress

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip6ConfigSetDataConf2AssertionGuid002                   \
                "Ip6Config.SetData - Call SetData to set manual address (duplication of list entries)."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

DelVar R_Ip6ConfigManualAddress

#
# Check Points : Set Gateway with "ff02::1" (multicast address)
#
set L_GatewayListLen   1
EFI_IPv6_ADDRESS                 R_Temp_Ip6ConfigGateway
EFI_IPv6_ADDRESS                 R_Ip6ConfigGateway
set L_UnitLen [Sizeof EFI_IPv6_ADDRESS]
set L_ListLen [expr {$L_UnitLen * $L_GatewayListLen}]
SetVar R_Ip6ConfigDataType   $IP6CDT(Gateway)
SetVar R_Ip6ConfigDataSize   $L_ListLen

SetIpv6Address R_Temp_Ip6ConfigGateway "ff02::1"
SetVar R_Ip6ConfigGateway @R_Temp_Ip6ConfigGateway
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigGateway,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip6ConfigSetDataConf2AssertionGuid003                   \
                "Ip6Config.SetData - Call SetData to set gateway with multicast address."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

DelVar R_Ip6ConfigGateway

#
# Check Point : Set Gateway with duplication of list entries
# 
set L_GatewayListLen   3
EFI_IPv6_ADDRESS                 R_Ip6ConfigGateway($L_GatewayListLen)
set L_UnitLen [Sizeof EFI_IPv6_ADDRESS]
set L_ListLen [expr {$L_UnitLen * $L_GatewayListLen}]
SetVar R_Ip6ConfigDataType   $IP6CDT(Gateway)
SetVar R_Ip6ConfigDataSize   $L_ListLen

SetIpv6Address R_Temp_Ip6ConfigGateway "2002::5000"
SetVar R_Ip6ConfigGateway(0) @R_Temp_Ip6ConfigGateway
SetIpv6Address R_Temp_Ip6ConfigGateway "2002::5001"
SetVar R_Ip6ConfigGateway(1) @R_Temp_Ip6ConfigGateway
SetIpv6Address R_Temp_Ip6ConfigGateway "2002::5000"
SetVar R_Ip6ConfigGateway(2) @R_Temp_Ip6ConfigGateway

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigGateway,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip6ConfigSetDataConf2AssertionGuid004                   \
                "Ip6Config.SetData - Call SetData to set gateway with duplication of list entries."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

DelVar R_Ip6ConfigGateway

#
# Check Point : Set Dns Server with "ff02::1" (link local address)
#
set L_DnsServerListLen 1
EFI_IPv6_ADDRESS                 R_Temp_Ip6ConfigDnsServer
EFI_IPv6_ADDRESS                 R_Ip6ConfigDnsServer
set L_UnitLen [Sizeof EFI_IPv6_ADDRESS]
set L_ListLen [expr {$L_UnitLen * $L_DnsServerListLen}]
SetVar R_Ip6ConfigDataType   $IP6CDT(DnsServer)
SetVar R_Ip6ConfigDataSize   $L_ListLen

SetIpv6Address R_Temp_Ip6ConfigDnsServer "ff02::1"
SetVar R_Ip6ConfigDnsServer @R_Temp_Ip6ConfigDnsServer

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigDnsServer,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip6ConfigSetDataConf2AssertionGuid005                   \
                "Ip6Config.SetData - Call SetData to set dns server with multicast address."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

DelVar R_Ip6ConfigDnsServer

#
# Check Point : Set Dns Server with duplication of list entries
#
set L_DnsServerListLen 3
EFI_IPv6_ADDRESS                 R_Ip6ConfigDnsServer($L_DnsServerListLen)
set L_UnitLen [Sizeof EFI_IPv6_ADDRESS]
set L_ListLen [expr {$L_UnitLen * $L_DnsServerListLen}]
SetVar R_Ip6ConfigDataType   $IP6CDT(DnsServer)
SetVar R_Ip6ConfigDataSize   $L_ListLen

SetIpv6Address R_Temp_Ip6ConfigDnsServer "2002::5000"
SetVar R_Ip6ConfigDnsServer(0) @R_Temp_Ip6ConfigDnsServer

SetIpv6Address R_Temp_Ip6ConfigDnsServer "2002::5001"
SetVar R_Ip6ConfigDnsServer(1) @R_Temp_Ip6ConfigDnsServer

SetIpv6Address R_Temp_Ip6ConfigDnsServer "2002::5000"
SetVar R_Ip6ConfigDnsServer(2) @R_Temp_Ip6ConfigDnsServer

Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigDnsServer,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip6ConfigSetDataConf2AssertionGuid006                   \
                "Ip6Config.SetData - Call SetData to set dns server with duplication of list entries."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

DelVar R_Ip6ConfigDnsServer

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

EndScope _IP6CONFIG_SETDATA_CONF2

EndLog