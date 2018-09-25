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
CaseGuid        F340A957-9345-478d-BE53-5F7C561C1866
CaseName        GetData.Conf4.Case1
CaseCategory    IP6Config
CaseDescription {GetData must not succeed when data type is not found.}

################################################################################
Include IP6Config/Include/Ip6Config.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP6CONFIG_GETDATA_CONF4

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
UINTN                            R_Ip6ConfigMaximumType
EFI_IP6_CONFIG_INTERFACE_INFO    R_Ip6ConfigInterfaceInfo
EFI_IP6_CONFIG_INTERFACE_ID      R_Ip6ConfigInterfaceId
UINT32                            R_Ip6ConfigPolicy
EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS    R_Ip6ConfigDadTransmits
EFI_IP6_CONFIG_MANUAL_ADDRESS               R_Ip6ConfigManualAddress

#
# Check Point: Call Ip6Config->GetData with the date type not existing.
#
SetVar R_Ip6ConfigDataType $IP6CDT(Maximum)
SetVar R_Ip6ConfigDataSize [Sizeof UINT32]

Ip6Config->GetData "@R_Ip6ConfigDataType,&@R_Ip6ConfigDataSize,&@R_Ip6ConfigMaximumType,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $Ip6ConfigGetDataConf4AssertionGuid001                   \
                "Ip6Config.GetData - Call GetData with Datatype not existing."            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

EndScope _IP6CONFIG_GETDATA_CONF4

EndLog