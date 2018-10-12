# 
#  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
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

#
# test case Name, category, description, GUID...
#
CaseGuid          C076FA7C-FE7B-4393-9734-EA60606546AE
CaseName          GetModeData.Conf2.Case1
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_NOT_STARTED\
                   -- This EFI HTTP Protocol instance has not been started.}
################################################################################

Include HTTP/include/Http.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _GETMODEDATA_CONF2_CASE1_


UINTN        R_Status
UINTN        R_Handle



#
# Create Http Child.
#
HttpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "HttpSBP.CreateChild - Create Child 1"    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Http.GetModeData() before the Http.Configure() on the HTTP instance
#
EFI_HTTPv4_ACCESS_POINT        R_Configure_AccessPointv4
EFI_HTTP_CONFIG_DATA           R_Configure_HttpConfigData

SetVar R_Configure_HttpConfigData.AccessPoint.IPv4Node        &@R_Configure_AccessPointv4

Http->GetModeData {&@R_Configure_HttpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $HttpGetModeDataConf2AssertionGuid001    \
                "Http.GetModeData - Call GetModeData() before the instance is configured"    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

#
# Destroy Http Child.
#
HttpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "HttpSBP.DestroyChild - Destroy Child 1."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# EndScope
#
EndScope _GETMODEDATA_CONF2_CASE1_

#
# End Log
#
EndLog