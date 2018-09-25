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
CaseGuid        51EBE71C-4BE7-44DE-B760-CE57B93FC514
CaseName        SetData.Conf2.Case1
CaseCategory    IP4Config2
CaseDescription {SetData must not succeed when data type is not supported and should return EFI_UNSUPPORTED.}

################################################################################
Include IP4Config2/Include/Ip4Config2.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_SETDATA_CONF2_CASE1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN     R_Status
UINTN     R_Ip4Config2DataSize
UINT32    R_Ip4Config2DataType
UINT32    R_Ip4Config2Maximum
#
# Check Point: Call Ip4Config2->SetData when data type is not supported.
#
SetVar R_Ip4Config2DataType $IP4C2DT(Maximum)
SetVar R_Ip4Config2DataSize [Sizeof UINT32]

Ip4Config2->SetData "@R_Ip4Config2DataType,@R_Ip4Config2DataSize,&@R_Ip4Config2Maximum,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_UNSUPPORTED]
RecordAssertion $assert $Ip4Config2SetDataConf2AssertionGuid001    \
                "Ip4Config2.SetData - Call SetData with the data type not supported."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_UNSUPPORTED"

EndScope _IP4CONFIG2_SETDATA_CONF2_CASE1

EndLog