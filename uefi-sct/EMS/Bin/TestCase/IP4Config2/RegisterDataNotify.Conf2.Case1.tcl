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
CaseGuid        E8C1EF23-9E1F-44E8-9C3A-8D3DF48361AE
CaseName        RegisterDataNotify.Conf2.Case1
CaseCategory    IP4Config2
CaseDescription {RegisterDataNotify must not succeed when data type is not supported and should return EFI_UNSUPPORTED.}

################################################################################
Include IP4Config2/Include/Ip4Config2.inc.tcl


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4CONFIG2_REGISTERDATANOTIFY_CONF2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN     R_Status
UINTN     R_Context
UINTN     R_DoneEvent
UINT32    R_Ip4Config2DataType



SetVar R_Ip4Config2DataType   $IP4C2DT(Maximum)

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_NOTIFY, 1, &@R_Context,\
                &@R_DoneEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "BS.CreateEvent."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Ip4Config2->RegisterDataNotify with the datatype not supported
#
Ip4Config2->RegisterDataNotify "@R_Ip4Config2DataType, @R_DoneEvent ,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_UNSUPPORTED]
RecordAssertion $assert $Ip4Config2RegisterDataNotifyConf2AssertionGuid001    \
                "Ip4Config2.RegisterDataNotify - Register notification event with the data type not supported."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_UNSUPPORTED"

#
# Clean up
#
BS->CloseEvent {@R_DoneEvent,&@R_Status}
GetAck

EndScope _IP4CONFIG2_REGISTERDATANOTIFY_CONF2

EndLog