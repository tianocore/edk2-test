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
CaseGuid          1B0A0EAA-086A-42d1-8B77-37862EEBD411
CaseName          Configure.Conf3.Case1
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_ALREADY_STARTED \
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
BeginScope _CONFIGURE_CONF3_CASE1_


UINTN        R_Status
UINTN        R_Handle

EFI_IPv4_ADDRESS                    R_Configure_LocalAddress
EFI_IPv4_ADDRESS                    R_Configure_SubnetMask
EFI_HTTPv4_ACCESS_POINT             R_Configure_AccessPointv4
EFI_HTTP_CONFIG_DATA                R_Configure_HttpConfigData
EFI_HTTP_CONFIG_DATA_ACCESSPOINT    R_Configure_AccessPoint

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
# Check Point: Call Http.Configure() to configure the HTTP instance
#
SetIpv4Address  R_Configure_LocalAddress                     "192.168.88.88"
SetIpv4Address  R_Configure_SubnetMask                       "255.255.255.0"
SetVar          R_Configure_AccessPointv4.UseDefaultAddress  FALSE
SetVar          R_Configure_AccessPointv4.LocalAddress       @R_Configure_LocalAddress
SetVar          R_Configure_AccessPointv4.LocalSubnet        @R_Configure_SubnetMask
SetVar          R_Configure_AccessPointv4.LocalPort          6666
SetVar          R_Configure_AccessPoint.IPv4Node             &@R_Configure_AccessPointv4


SetVar R_Configure_HttpConfigData.HttpVersion                $HttpVersion10
SetVar R_Configure_HttpConfigData.TimeOutMillisec            10
SetVar R_Configure_HttpConfigData.LocalAddressIsIPv6         FALSE
SetVar R_Configure_HttpConfigData.AccessPoint                @R_Configure_AccessPoint


Http->Configure {&@R_Configure_HttpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Http.Configure - Call Configure() with the valid settings."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetIpv4Address        R_Configure_LocalAddress   "172.16.210.102"

Http->Configure {&@R_Configure_HttpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ALREADY_STARTED]
RecordAssertion $assert $HttpConfigureConf3AssertionGuid001    \
                "Http.Configure - Call Configure() to reinitialize it ."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ALREADY_STARTED"


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
EndScope _CONFIGURE_CONF3_CASE1_

#
# End Log
#
EndLog





