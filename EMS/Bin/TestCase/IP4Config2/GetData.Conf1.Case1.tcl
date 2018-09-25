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
CaseGuid        D29DF0D8-65EF-47F0-8767-C39C784B5C69
CaseName        GetData.Conf1.Case1
CaseCategory    Ip4Config2
CaseDescription {GetData must not succeed when data size is NULL.}

################################################################################
Include IP4Config2/Include/Ip4Config2.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_GETDATA_CONF1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
EFI_IP4_CONFIG2_INTERFACE_INFO   R_Ip4Config2InterfaceInfo
UINT32                           R_Ip4Config2DataType
UINTN                            R_Ip4Config2DataSize

#
# Check Point: Call Ip4Config2->GetData with datasize is NULL.
#
SetVar R_Ip4Config2DataType $IP4C2DT(InterfaceInfo)
SetVar R_Ip4Config2DataSize [Sizeof EFI_IP4_CONFIG2_INTERFACE_INFO]

Ip4Config2->GetData "@R_Ip4Config2DataType,NULL,&@R_Ip4Config2InterfaceInfo,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4Config2GetDataConf1AssertionGuid001    \
                "Ip4Config2.GetData - Call GetData with DataSize NULL."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

EndScope _IP4CONFIG2_GETDATA_CONF1

EndLog