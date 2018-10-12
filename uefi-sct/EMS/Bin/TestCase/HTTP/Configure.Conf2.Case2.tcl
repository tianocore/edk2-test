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
CaseGuid          1F800B6F-943A-4b5e-9E55-9C3E0DAE320B
CaseName          Configure.Conf2.Case2
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_INVALID_PARAMETER\
                   -- HttpConfigData->IPv6Node is NULL when  \
                   HttpConfigData->LocalAddressIsIPv6 is TRUE.}
################################################################################

Include HTTP/include/Http.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _CONFIGURE_CONF2_CASE2_


UINTN        R_Status
UINTN        R_Handle

EFI_HTTP_CONFIG_DATA_ACCESSPOINT        R_Configure_AccessPoint
EFI_HTTP_CONFIG_DATA                    R_Configure_HttpConfigData

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
# Check Point: Call Http.Configure() to configure the HTTP instance,
#              with null IPv6Node when
#              HttpConfigData->LocalAddressIsIPv6 is TRUE
#
SetVar R_Configure_AccessPoint.IPv6Node  0

SetVar R_Configure_HttpConfigData.HttpVersion               $HttpVersion10
SetVar R_Configure_HttpConfigData.TimeOutMillisec           128
SetVar R_Configure_HttpConfigData.LocalAddressIsIPv6        TRUE
SetVar R_Configure_HttpConfigData.AccessPoint               @R_Configure_AccessPoint


Http->Configure {&@R_Configure_HttpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $HttpConfigureConf2AssertionGuid002    \
                "Http.Configure - Call Configure() with IPv6Node is NULL."    \
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
EndScope _CONFIGURE_CONF2_CASE2_

#
# End Log
#
EndLog






















