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
CaseGuid          C23174C5-1640-4b5e-9211-7AFC1CE5653D
CaseName          Configure.Conf4.Case1
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_UNSUPPORTED\
                   -- One or more options in ConfigData are not supported\
                   in the implementation.}
################################################################################

Include HTTP/include/Http.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _CONFIGURE_CONF4_CASE1_


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

#
# Check Point: Call Http.Configure() to configure the HTTP instance,
#              with unsupported HttpVersion
#


SetIpv6Address  R_Configure_LocalAddress                      "2002::1"
SetVar          R_Configure_AccessPointv6.LocalAddress        @R_Configure_LocalAddress
SetVar          R_Configure_AccessPointv6.LocalPort           0


SetVar R_Configure_HttpConfigData.HttpVersion                 $HttpVersionUnsupported
SetVar R_Configure_HttpConfigData.TimeOutMillisec             128
SetVar R_Configure_HttpConfigData.LocalAddressIsIPv6          TRUE
SetVar R_Configure_HttpConfigData.AccessPoint.IPv6Node        &@R_Configure_AccessPointv6

Http->Configure {&@R_Configure_HttpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_UNSUPPORTED]
RecordAssertion $assert $HttpConfigureConf4AssertionGuid001    \
                "Http.Configure - Call Configure() with One or more options in    \
                ConfigData are not supported."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_UNSUPPORTED"

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
EndScope _CONFIGURE_CONF4_CASE1_

#
# End Log
#
EndLog

