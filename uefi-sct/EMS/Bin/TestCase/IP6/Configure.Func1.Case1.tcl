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
CaseGuid        2C81EF47-F9DB-4caa-BD5E-A601FD6D3483
CaseName        Configure.Func1.Case1
CaseCategory    IP6
CaseDescription {Test the Configure Function of IP6 - Invoke Configure() \
                 and call GetModeData() to check its ConfigData.}
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin Log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope   _IP6_CONFIGURE_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child.
#
Ip6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Ip6SB.CreateChild - Create Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar [subst $ENTS_CUR_CHILD]          @R_Handle

#
# Address Configuration
#
UINTN                                       R_Ip6ConfigDataSize
UINT32                                      R_Ip6ConfigDataType
UINT32                                      R_Ip6ConfigPolicy
EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS    R_Ip6ConfigDadTransmits
EFI_IP6_CONFIG_MANUAL_ADDRESS               R_Ip6ConfigManualAddress

SetVar R_Ip6ConfigDataType   2
SetVar R_Ip6ConfigDataSize   4
SetVar R_Ip6ConfigPolicy     $IP6CP(Manual)
  
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigPolicy,&@R_Status"
GetAck

SetVar R_Ip6ConfigDataType   3
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS]
SetVar R_Ip6ConfigDadTransmits.DupAddrDetectTransmits 0
  
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigDadTransmits,&@R_Status"
GetAck
  
SetVar R_Ip6ConfigDataType   4
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_MANUAL_ADDRESS]
SetVar R_Ip6ConfigManualAddress.IsAnycast    FALSE
SetVar R_Ip6ConfigManualAddress.PrefixLength 64
SetIpv6Address R_Ip6ConfigManualAddress.Address $DEF_EUT_IP_ADDR
  
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck

EFI_IP6_CONFIG_DATA                           R_Ip6ConfigData
SetVar R_Ip6ConfigData.DefaultProtocol        0x11;        #Next Header: UDP
SetVar R_Ip6ConfigData.AcceptAnyProtocol      FALSE
SetVar R_Ip6ConfigData.AcceptIcmpErrors       TRUE
SetVar R_Ip6ConfigData.AcceptPromiscuous      FALSE
SetIpv6Address R_Ip6ConfigData.DestinationAddress     "::"
SetIpv6Address R_Ip6ConfigData.StationAddress         "::"
SetVar R_Ip6ConfigData.TrafficClass           0
SetVar R_Ip6ConfigData.HopLimit               64
SetVar R_Ip6ConfigData.FlowLabel              0
SetVar R_Ip6ConfigData.ReceiveTimeout         50000
SetVar R_Ip6ConfigData.TransmitTimeout        50000

#
# Check point: Configure this child with valid parameter.
#              EFI_SUCCESS should be returned.
#
Ip6->Configure "&@R_Ip6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6ConfigureFunc1AssertionGuid001       \
                "Ip6.Configure - Func - Configure child with valid parameter"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Call GetModeData to varify the configuration.
#
EFI_IP6_MODE_DATA                             R_Ip6ModeData
Ip6->GetModeData "&@R_Ip6ModeData, NULL, NULL, &@R_Status"
GetAck
RecordAssertion $assert $Ip6ConfigureFunc1AssertionGuid002       \
                "Ip6.GetModeData -  Get Mode Data after child configured"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Ip6ModeData
#
# Verify Ip6ModeData.ConfigData
#
set assert pass
if { ${R_Ip6ModeData.ConfigData.DefaultProtocol} != 0x11 } {
    set assert fail
}

if { ${R_Ip6ModeData.ConfigData.AcceptAnyProtocol} != false } {
    set assert fail
}

if { ${R_Ip6ModeData.ConfigData.AcceptIcmpErrors} != true } {
    set assert fail
}

if { ${R_Ip6ModeData.ConfigData.AcceptPromiscuous} != false } {
    set assert fail
}

if { ${R_Ip6ModeData.ConfigData.TrafficClass} != 0 } {
    set assert fail
}

if { ${R_Ip6ModeData.ConfigData.HopLimit} != 64 } {
    set assert fail
}

if { ${R_Ip6ModeData.ConfigData.ReceiveTimeout} != 50000 } {
    set assert fail
}

if { ${R_Ip6ModeData.ConfigData.TransmitTimeout} != 50000 } {
    set assert fail
}

RecordAssertion $assert $Ip6ConfigureFunc1AssertionGuid003       \
                "Ip6.Configure - Func -  Verify R_Ip6ModeData.ConfigData"

#
# Call Configure with NULL
#
Ip6->Configure "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6ConfigureFunc1AssertionGuid004       \
                "Ip6.Configure - Func - Configure child with NULL"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call GetModeData to varify the configuration
#
EFI_IP6_MODE_DATA                             R_Ip6ModeData1
Ip6->GetModeData "&@R_Ip6ModeData1, NULL, NULL, &@R_Status"
GetAck
#set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
#RecordAssertion $assert $Ip6ConfigureFunc1AssertionGuid005       \
                "Ip6.GetModeData -  Get Mode Data after child configured"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Ip6ModeData1.IsConfigured
set assert fail
if { ${R_Ip6ModeData1.IsConfigured} == false} {
    set assert pass
}
RecordAssertion $assert $GenericAssertionGuid                    \
               "Ip6.Configure - Func -  Verify R_Ip6ModeData.ConfigData"       \
#
# DestroyChild.
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# End scope
#
EndScope _IP6_CONFIGURE_FUNCTION1_CASE1_
#
# End Log
#
EndLog


