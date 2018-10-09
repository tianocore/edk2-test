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
CaseGuid        c0373c1f-a728-464e-be87-e297ce3fd44c
CaseName        Start.Conf1.Case1
CaseCategory    IP4Config
CaseDescription {This case is to test the Conformance - EFI_INVALID_PARAMETER  \
                -- DoneEvent is NULL.}

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
BeginScope _IP4CONFIG_START_CONF1

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
# Check Point: Call Ip4Config->Start with DoneEvent NULL.
#
Ip4Config->Start "0, @R_ReconfigEvent, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4ConfigStartConf1AssertionGuid001                   \
                "Ip4Config.Start - Call Start with DoneEvent NULL."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

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

EndScope _IP4CONFIG_START_CONF1

EndLog