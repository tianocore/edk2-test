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
CaseGuid          75713B03-0CB1-41d9-9F8D-2941BFC1F7E7
CaseName          GetModeData.Conf1.Case3
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_INVALID_PARAMETER\
                   -- HttpConfigData->LocalAddressIsIPv6 is TRUE and HttpConfigData->IPv6Node is NULL. }
################################################################################

Include HTTP/include/Http.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _GETMODEDATA_CONF1_CASE3_


UINTN        R_Status
UINTN        R_Handle

EFI_IPv6_ADDRESS               R_Configure_LocalAddress
EFI_HTTPv6_ACCESS_POINT        R_Configure_AccessPointv6
EFI_HTTP_CONFIG_DATA           R_Configure_HttpConfigData

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


SetIpv6Address  R_Configure_LocalAddress                      "20::1"
SetVar          R_Configure_AccessPointv6.LocalAddress        @R_Configure_LocalAddress
SetVar          R_Configure_AccessPointv6.LocalPort           0


SetVar R_Configure_HttpConfigData.HttpVersion                 $HttpVersion10
SetVar R_Configure_HttpConfigData.TimeOutMillisec             128
SetVar R_Configure_HttpConfigData.LocalAddressIsIPv6          TRUE
SetVar R_Configure_HttpConfigData.AccessPoint.IPv6Node        &@R_Configure_AccessPointv6

Http->Configure {&@R_Configure_HttpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                    \
                "Http.Configure - Call Configure() with valid settings." \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"



SetVar R_Configure_HttpConfigData.AccessPoint.IPv6Node        0

#
# Check Point: Call Http.GetModeData(),
#              HttpConfigData->LocalAddressIsIPv6 is TRUE and HttpConfigData->IPv6Node is NULL.

Http->GetModeData {&@R_Configure_HttpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $HttpGetModeDataConf1AssertionGuid003    \
                "Http.GetModeData - Call GetModeData() with parameters    \
                HttpConfigData->LocalAddressIsIPv6 is TRUE and HttpConfigData->IPv6Node is NULL."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"


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
EndScope _GETMODEDATA_CONF1_CASE3_

#
# End Log
#
EndLog

