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
CaseGuid        ce6b14ee-7930-4d4d-90fb-19791cee9b50
CaseName        GetData.Conf2.Case1
CaseCategory    IP4Config
CaseDescription {This case is to test the Conformance - EFI_NOT_READY          \
                -- EFI IPv4 Protocol driver configuration is still running.}

################################################################################

Include IP4Config/include/Ip4Config.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG_GETDATA_CONF2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_DoneContext
UINTN                            R_ReconfigContext
UINTN                            R_DoneEvent
UINTN                            R_ReconfigEvent
UINTN                            R_Ip4IpConfigDataSize
EFI_IP4_IPCONFIG_DATA            R_Ip4IpConfigData

#
# Make sure the configuration policy for the EFI IPv4 Protocol driver is not running
#
Ip4Config->Stop "&@R_Status"
GetAck

VifUp 0 172.16.210.162 255.255.255.0

#
# Create Event for DoneEvent
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_DoneContext,    \
                &@R_DoneEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Create Event for ReconfigEvent
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_ReconfigContext,\
                &@R_ReconfigEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Ip4Config->Start to start configuration.
#
Ip4Config->Start "@R_DoneEvent, @R_ReconfigEvent, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4Config.Start - Start Config"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Ip4IpConfigDataSize 0x24

#
# Check Point: Call Ip4Config->GetData to Get data when not ready.
#
Ip4Config->GetData "&@R_Ip4IpConfigDataSize, &@R_Ip4IpConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_READY]
RecordAssertion $assert $Ip4ConfigGetDataConf2AssertionGuid001                 \
                "Ip4Config.GetData - Call GetData when not ready."             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_READY"

#
# Call Ip4Config->Stop to Stop configuration.
#
Ip4Config->Stop "&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4Config.Stop - Stop Config"                                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Close Event for DoneEvent
#
BS->CloseEvent "@R_DoneEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CloseEvent."                                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Close Event for ReconfigEvent
#
BS->CloseEvent "@R_ReconfigEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CloseEvent."                                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
#
VifDown 0

EndScope _IP4CONFIG_GETDATA_CONF2

EndLog