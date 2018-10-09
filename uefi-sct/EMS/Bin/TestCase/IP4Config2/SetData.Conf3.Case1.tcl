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
CaseGuid        54431C3F-B28B-42E3-A8DC-61502DC057B0
CaseName        SetData.Conf3.Case1
CaseCategory    IP4Config2
CaseDescription {SetData must not succeed when data is read-only type and should return EFI_WRITE_PROTECTED.}

################################################################################
Include IP4Config2/Include/IP4Config2.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_SETDATA_CONF3_CASE1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_Ip4Config2DataSize
UINT32                            R_Ip4Config2DataType
EFI_IP4_CONFIG2_INTERFACE_INFO    R_Ip4Config2InterfaceInfo

#
# Check Point: Call Ip4Config2->SetData with data is read only.
#
SetVar R_Ip4Config2DataType $IP4C2DT(InterfaceInfo)
SetVar R_Ip4Config2DataSize [Sizeof EFI_IP4_CONFIG2_INTERFACE_INFO]

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2InterfaceInfo,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_WRITE_PROTECTED]
RecordAssertion $assert $Ip4Config2SetDataConf3AssertionGuid001    \
                "Ip4Config2.SetData - Call SetData with data is read only."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_WRITE_PROTECTED"

EndScope _IP4CONFIG2_SETDATA_CONF3_CASE1

EndLog