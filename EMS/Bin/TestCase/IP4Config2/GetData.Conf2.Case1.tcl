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
CaseGuid        CE3AFB19-25C7-4822-9C3E-D0190131A8DE
CaseName        GetData.Conf2.Case1
CaseCategory    IP4Config2
CaseDescription {GetData must not succeed when data is NULL if data size is not zero.}

################################################################################
Include IP4Config2/Include/Ip4Config2.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_GETDATA_CONF2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN     R_Status
UINTN     R_Ip4Config2DataSize
UINT32    R_Ip4ConfigD2ataType

#
# Check Point: Call Ip4Config2->GetData with data is NULL.
#
SetVar R_Ip4ConfigD2ataType $IP4C2DT(InterfaceInfo)
SetVar R_Ip4Config2DataSize [Sizeof EFI_IP4_CONFIG2_INTERFACE_INFO]

Ip4Config2->GetData "@R_Ip4ConfigD2ataType,&@R_Ip4Config2DataSize,NULL,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4Config2GetDataConf2AssertionGuid001    \
                "Ip4Config2.GetData - Call GetData with Data NULL."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

EndScope _IP4CONFIG2_GETDATA_CONF2

EndLog