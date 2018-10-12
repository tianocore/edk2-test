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
CaseGuid          02EB1F9B-713E-456c-85BA-8C2BD7B3B1A6
CaseName          Configure.Conf2.Case1
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_INVALID_PARAMETER\
                   -- HttpConfigData->IPv4Node is NULL when  \
                   HttpConfigData->LocalAddressIsIPv6 is FALSE.}
################################################################################

Include HTTP/include/Http.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _CONFIGURE_CONF2_CASE1_


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
#              with null IPv4Node when
#              HttpConfigData->LocalAddressIsIPv6 is FALSE
#
SetVar R_Configure_AccessPoint.IPv4Node  0


SetVar R_Configure_HttpConfigData.HttpVersion               $HttpVersion10
SetVar R_Configure_HttpConfigData.TimeOutMillisec           128
SetVar R_Configure_HttpConfigData.LocalAddressIsIPv6        FALSE
SetVar R_Configure_HttpConfigData.AccessPoint               @R_Configure_AccessPoint

Http->Configure {&@R_Configure_HttpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $HttpConfigureConf2AssertionGuid001    \
                "Http.Configure - Call Configure() with IPv4Node is NULL."    \
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
EndScope _CONFIGURE_CONF2_CASE1_

#
# End Log
#
EndLog