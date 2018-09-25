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
CaseGuid        0D1A3EB1-3E43-412D-9F6F-48FBA48D2BDD
CaseName        GetData.Conf4.Case1
CaseCategory    IP4Config2
CaseDescription {GetData must not succeed when data type is not found.}

################################################################################
Include IP4Config2/Include/IP4Config2.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_GETDATA_CONF4

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN     R_Status
UINTN     R_Ip4Config2DataSize
UINT32    R_Ip4Config2DataType
UINTN     R_Ip4Config2MaximumType



#
# Check Point: Call Ip6Config->GetData with the date type not existing.
#
SetVar R_Ip4Config2DataType $IP4C2DT(Maximum)
SetVar R_Ip4Config2DataSize [Sizeof UINT32]

Ip4Config2->GetData "@R_Ip4Config2DataType,&@R_Ip4Config2DataSize,&@R_Ip4Config2MaximumType,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $Ip4Config2GetDataConf4AssertionGuid001    \
                "Ip4Config2.GetData - Call GetData with Datatype not existing."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

EndScope _IP4CONFIG2_GETDATA_CONF4

EndLog